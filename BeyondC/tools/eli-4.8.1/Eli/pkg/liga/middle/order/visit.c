/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
/* $Id: visit.c,v 4.11 1998/04/28 14:28:56 ludi Exp $ */
static char rcs_id[] = "$Id: visit.c,v 4.11 1998/04/28 14:28:56 ludi Exp $";

/****************************************************************
*	Module  : visit.c					*
*	compute the visit sequences for the rules.		*
****************************************************************/

#include "printerr.h"
#include "ligaconsts.h"
#include "initdp.h"
#include "option.h"
#include "do_order.h"
#include "reftab.h"
#include "allocate.h"
#include "liga_func.h"
#include "bottomup.h"
/* the next two for replace including options: */
#include "option_enums.h"
#include "option_types.h"

#include "visit.h"

#define INACTIVE -1
#define ODD(x)          ((x)%2 == 1)
#define EVEN(x)         ((x)%2 == 0)
#define sgl 0x00000001

/* global variables */

static bool afterBUvisits = FALSE;
	/* controls message for code computation in virtual BU phase */

static bool insertplain = FALSE;
         /* controls insertion of plain computations after first leave */

static PRODENTRY *prod;
static SYMBENTRY *symb;

VSPTR rulevisitseq, lastvisitel;
int maxsymbno;
bool nocyclicsymbs;
int pid, setsize;
static BITVECTOR eval, noteval, evaluable;

static VSPTR *symbvsvect = NULL; /* dynamically allocated array*/
int *atvect; /* dynamically allocated array*/

/********************************************************/
#define NoCall ((Call)NULL)

Call FindComputation (prodid, symbno, attrid) int prodid, symbno, attrid;
/* find an assign computation in context prodid for attr (symbno, attrid);
   ignore those marked MULTMARK if there is a real one;
   return NoCall if there is no such assign.
*/
{ Attrrule attrrule; SEQAttrrule remattrrule;
  Call foundcomp = NoCall;

  foreachinSEQAttrrule
    (ref_tab[prodid].entry.prod.computations, remattrrule, attrrule)
  if ((typeof(attrrule) == KCall) &&
      (strcmp(nameOfCall (AttrruleToCall (attrrule)), ASSIGNFCT) == 0))
  { Call ca = AttrruleToCall (attrrule);
    Expr ex; Attracc attracc;

    retrievefirstSEQExpr (paramsOfCall (ca), ex);
    attracc = ExprToAttracc (ex);
    if ((symbnoOfAttracc (attracc) == symbno) &&
        (attridOfAttracc (attracc) == attrid))
    /* found an assign (symbno, attrid): */
    { SEQExpr marks; Expr mark;
      int realcomp = 1;
      foundcomp = ca;

      /* check computation marks for MULTMARK: */
      marks = tailSEQExpr (tailSEQExpr (paramsOfCall (ca)));
      while (marks != NULL)
      { retrievefirstSEQExpr (marks, mark);
        if (typeof(mark) == KName &&
	    strcmp (MULTMARK, mark.VName->n) == 0)
		 realcomp = 0;
        marks = tailSEQExpr (marks);
      }
      if (realcomp) break; /* found the comp; terminate the search */
    }
  }
  /* one of the following cases hold for the value of foundcomp:
     assign (symbno, attrid) without MULTMARK
     assign (symbno, attrid) with MULTMARK and there is no such
           assign without MULTMARK
     NoCall and there is no assign (symbno, attrid) at all
  */
  return foundcomp;
}/* FindComputation */

/********************************************************
*  VSPTR createcondition()
********************************************************/

VSPTR createcondition (pid, call) int pid; Call call;
{ VSPTR cond;
  int prodsetsize = ref_tab[pid].entry.prod.check_col;

  if (prodsetsize < 0 ) prodsetsize = 0;

   cond = (VSELEM *) Allocate(__FILE__,__LINE__,sizeof(VSELEM));
   cond->vscls = VSCOND;
   cond->deps = mkemptyset(prodsetsize);
   cond->vsinfo.cond.idldef = call;
   cond->next = ref_tab[pid].entry.prod.visitseq;
   ref_tab[pid].entry.prod.visitseq = cond;

   return cond;
}

void VSSetDepend (vselem, symptr, attrpos)
	VSPTR vselem; SLNODE *symptr; int attrpos;
{
  vselem->deps
    [symptr->start_col + attrpos / WORD_LENGTH]
    |= sgl << attrpos % WORD_LENGTH;
}

/********************************************************
*	void insertconditions()				*
*	insert currently computable conditions into	*
*	the list headed by rulevisitseq for the 	*
*	current rule.					*
********************************************************/
static
void insertconditions()
{
   VSPTR cond, notinserted, notchecked;

   notinserted = NULL;
   notchecked = ref_tab[pid].entry.prod.visitseq;

   while (notchecked != NULL)
   {
      cond = notchecked;
      notchecked = notchecked->next;
      if (issubset(cond->deps, eval, setsize))
      {
	 if (rulevisitseq == NULL)
	    rulevisitseq = cond;
	 else
	    lastvisitel->next = cond;
	 lastvisitel = cond;
	 cond->next = NULL;
      } else
      {
	 cond->next = notinserted;
	 notinserted = cond;
      }
   }
   ref_tab[pid].entry.prod.visitseq = notinserted;
}/* insertconditions() */

/********************************************************
*	void findevaluable()				*
*	for a given set eval				*
*	find those attributes that are ready to 	*
*	be computed i.e. whose depended attributes	*
*	have been computed.				*
********************************************************/
static
void findevaluable()
{
   SLNODE *slnptr;
   int atno;
   bool changed;

   copyset (eval, evaluable, setsize);

   do
   {
      changed = FALSE;

      if (prod->check_row >= 1)	/* there are attribute occ. in this rule */
	 for (slnptr = prod->hdright; slnptr != NULL; slnptr = slnptr->right)
	 {
	    symb = &ref_tab[slnptr->sid].entry.symb;
	    for (atno = 0; atno < symb->attr_num; atno++)
	       if (atvect[atno + slnptr->start_row] != INACTIVE)
                   /* this attr has a computation in this context;
                      check whether it is not yet in evaluable and
                      all its dependencies are in evaluable */
#ifndef GORTO
		  if (!ismemberset (atno % WORD_LENGTH, 
                                    slnptr->start_col + atno / WORD_LENGTH, 
                                    evaluable))
		     if (issubset (prod->dp[atno + slnptr->start_row], 
                                   evaluable, setsize))
		     {
			addtoset (atno % WORD_LENGTH, 
                                  slnptr->start_col + atno / WORD_LENGTH, 
                                  evaluable);
			changed = TRUE;
		     }
	 }
#else
		  if (!ismemberset (atno % WORD_LENGTH, 
                                    slnptr->start_col + atno / WORD_LENGTH, 
                                    evaluable))
		     if (dep_is_subset (prod->dp[atno + slnptr->start_row], 
                                        evaluable, prod))
		     {
			addtoset (atno % WORD_LENGTH, 
                                  slnptr->start_col + atno / WORD_LENGTH, 
                                  evaluable);
			changed = TRUE;
		     }
	 }
#endif
   } while (changed);
}/* findevaluable */


/********************************************************
*	void appendsem()				*
*	append a visitseqence element of class VSASSIG	*
*	to the end of the list headed by rulevisitseq	*
********************************************************/
static
void appendsem (atno, symbno) int atno, symbno;
{
   VSPTR semnodeptr;
   SLNODE *slnptr;
   int aid, sno;
   Call foundcomputation;

   slnptr = prod->hdright;
   for (sno = 0; sno < symbno; sno++)
      slnptr = slnptr->right;

   aid = atvect[atno + slnptr->start_row];
   atvect[atno + slnptr->start_row] = INACTIVE;

   foundcomputation = FindComputation (pid, symbno, aid);

   /* modify sets eval and noteval */
   addtoset 
     (atno % WORD_LENGTH, 
      slnptr->start_col + atno / WORD_LENGTH, 
      eval);
   delfromset
     (atno % WORD_LENGTH, 
      slnptr->start_col + atno / WORD_LENGTH, 
      noteval);

   if (foundcomputation == NoCall)
      /* there is no computation to be inserted */
      return;

   /* make a new node */
   semnodeptr = (VSPTR) Allocate (__FILE__,__LINE__,sizeof(VSELEM));
   semnodeptr->deps = mkemptyset(setsize);

   /* complete the items of this node */

#ifndef GORTO
   copyset(prod->dp[atno + slnptr->start_row], semnodeptr->deps, setsize);
#else
   copy_dep_to_set(prod->dp[atno + slnptr->start_row], semnodeptr->deps, prod);
#endif

   semnodeptr->vscls = VSASSIG;
   semnodeptr->next = NULL;

   semnodeptr->vsinfo.assig.aid = aid;
   semnodeptr->vsinfo.assig.apos = atno;
   semnodeptr->vsinfo.assig.sid = slnptr->sid;
   semnodeptr->vsinfo.assig.sno = symbno;
   semnodeptr->vsinfo.assig.idldef = foundcomputation;

   if (!afterBUvisits && NeedsCode (foundcomputation))
   { err_setpos (rowOfCall (foundcomputation),
                 colOfCall (foundcomputation)
		);
     err_print_error ("computation may not be scheduled BOTTOMUP");
     fprintf (ProtocolFile,
	      "*** ERROR *** computation may not be scheduled BOTTOMUP\n");
   }
   
   /* append semnodeptr to the end of rulevisitseq */
   if (rulevisitseq == NULL)
      rulevisitseq = semnodeptr;
   else
      lastvisitel->next = semnodeptr;
   lastvisitel = semnodeptr;
}/* appendsem() */


/********************************************************
*	void appendnextvs(symbno)			*
*	schedule a visit to the symbol occurrence symbno*
*	prior to it schedule all required computations	*
********************************************************/
static
void appendnextvs (symbno) int symbno;
{
   int atno, sno;
   VSPTR vsnode;
   BITVECTOR neweval, tmpset;
   SLNODE *slnptr;

   if (symbvsvect[symbno] == NULL)
   {
      err_setpos(0, 0);
      err_print_error ("System error in appendnextvs: symbvsvect == NULL");
      fprintf
       (ProtocolFile, 
        "*** ERROR *** in appendnextvs: symbvsvect == NULL\n");
      exit(5);
   }

/* neweval := vsnode->deps - eval */
   neweval = mkemptyset(setsize);
   vsnode = symbvsvect[symbno];
   copyset (vsnode->deps, neweval, setsize);
   diffset (eval, neweval, setsize);	

/* tmpset := evaluable + eval */
   tmpset = mkemptyset(setsize);
   copyset (evaluable, tmpset, setsize);
   unionset (eval, tmpset, setsize);

   if (!issubset (vsnode->deps, tmpset, setsize))
   {
      err_setpos(0, 0);
      err_print_error ("System error in appendnextvs: schedule problem");
      fprintf
        (ProtocolFile, 
         "*** ERROR *** in appendnextvs: schedule problem\n");
      exit(5);
   }

/* schedule computations of attributes that are required by the visit: */
   do
   {
      if (prod->check_row >= 1)	/* there are attr occ. in this rule */
	 for (sno = 0, slnptr = prod->hdright; 
              slnptr != NULL; sno++, slnptr = slnptr->right)
	 {
	    symb = &ref_tab[slnptr->sid].entry.symb;
	    for (atno = 0; atno < symb->attr_num; atno++)
	       if (ismemberset 
                     (atno % WORD_LENGTH, 
                      slnptr->start_col + atno / WORD_LENGTH, 
                      neweval))
#ifndef GORTO
		  if (issubset 
                        (prod->dp[atno + slnptr->start_row], 
                         eval, setsize))
#else
		  if (dep_is_subset 
                        (prod->dp[atno + slnptr->start_row], 
                         eval, prod))
#endif
		  {
		     appendsem (atno, sno);
		     delfromset
                       (atno % WORD_LENGTH, 
                        slnptr->start_col + atno / WORD_LENGTH, 
                        neweval);
		  }
	 }
   } while (!isemptyset (neweval, setsize));

   if (insertplain) insertconditions();

   /* append this visit node */
   if (rulevisitseq == NULL)
      rulevisitseq = vsnode;
   else
      lastvisitel->next = vsnode;
   lastvisitel = vsnode;

   /* modify the symbvsvect array */
   symbvsvect[symbno] = vsnode->next;
   vsnode->next = NULL;

   /* update eval, noteval: */
   unionset (vsnode->vsinfo.visit.evalset, eval, setsize);
   diffset (eval, noteval, setsize);

   if (insertplain) insertconditions();

   findevaluable ();
}/* appendnextvs() */


/********************************************************
*	void createvisit()				*
*	create a visit node and insert it into		*
*	symbvsvect[symbno]				*
********************************************************/
static
void createvisit (sid, sno, actpartno) int sid, sno, actpartno;

{
   VSPTR vsnode;

   vsnode = (VSELEM *) Allocate(__FILE__,__LINE__,sizeof(VSELEM));
   vsnode->deps = mkemptyset(setsize);

   vsnode->vscls = VSVISIT;
   vsnode->vsinfo.visit.evalset = mkemptyset(setsize);
   vsnode->vsinfo.visit.vssid = sid;
   vsnode->vsinfo.visit.vssno = sno;

   vsnode->vsinfo.visit.vsord = (actpartno + 1) / 2;

   vsnode->next = symbvsvect[sno];
   symbvsvect[sno] = vsnode;
}/* createvisit() */

static int IsRootRule; /* set by visitseqinit; used by visitstrategy */

/********************************************************
*	void visitseqinit()				*
*	initializations of the global data structures	*
*	used in the module 				*
********************************************************/
static
void visitseqinit()
{
   int currpartno;
   int atno, aid;
   int sno;
   bool isdefpart;
   SLNODE *slnptr;

   rulevisitseq = NULL;
   lastvisitel = NULL;

   /* check whether we are in root context (used in visitstrategy): */
   IsRootRule = 
     (ref_tab[prod->hdright->sid].entry.symb.hddown->down == NULL);

   for (sno = 0; sno <= MaxRhsLen; sno++)
      symbvsvect[sno] = NULL;

   if (prod->check_row >= 1)
      for (atno = 0; atno < prod->check_row; atno++)
	 atvect[atno] = INACTIVE;

/* a triple of set variables characterizes the attribute evaluation
   state during visit-sequence scheduling:
   eval+noteval		all attributes of the rule
   eval			evaluated attributes
   noteval		not yet evaluated attributes
   evaluable		attributes ready to be evaluated
*/
   eval = mkemptyset(setsize);
   evaluable = mkemptyset(setsize);
   noteval = mkemptyset(setsize);

   if (prod->check_row >= 1) /* there are attr occs in this rule */
      for (slnptr = prod->hdright; slnptr != NULL; slnptr = slnptr->right)
      {
	 symb = &ref_tab[slnptr->sid].entry.symb;
	 for (atno = 0; atno < symb->attr_num; atno++)
	    addtoset
              (atno % WORD_LENGTH, 
               slnptr->start_col + atno / WORD_LENGTH, 
               noteval);
      }

   slnptr = prod->hdright;

/* All visits of this rule are to be constructed and stored in the
   symbvsvect[i] for the ith symbol occurrence.
   Each visit has 2 attribute sets:
   symbvsvect[i]->deps                    to be valuated before this visit
   symbvsvect[sno]->vsinfo.visit.evalset  evaluated in this visit
*/

/* create the last visit to ancestor, the first one will be removed: */
   createvisit (slnptr->sid, 0, ref_tab[slnptr->sid].entry.symb.part_num);
   /* last visit to ancestor requires all attributes to be evaluated: */
   copyset (noteval, symbvsvect[0]->deps, setsize);

/* create the visits for each symbol occurrence: */
   for (sno = 0, slnptr = prod->hdright; 
        slnptr != NULL; slnptr = slnptr->right, sno++)
   {
      symb = &ref_tab[slnptr->sid].entry.symb;
#ifndef GORTO
      nocyclicsymbs = nocyclicsymbs && !(symb->cyclic);
#else
      nocyclicsymbs = nocyclicsymbs && !(symb->state & S_CYCLIC);
#endif

      /* consider the partitions for the symbol: */
      for (currpartno = symb->part_num; currpartno >= 0; currpartno--)
      {
	 isdefpart = ((sno == 0) && ODD(currpartno)) || 
                     ((sno > 0) && EVEN(currpartno));

	 if (!isdefpart)
	    createvisit (slnptr->sid, sno, currpartno);

         /* consider each attribute in this partition: */
	 for (atno = 0; atno < symb->attr_num; atno++)
	 {
	    aid = lookup_attr(slnptr->sid, atno);
	    if (ref_tab[aid].entry.attr.part == currpartno)
	    {  if (isdefpart)
	       {  /* attribute atno has a computation in this rule: */

		  atvect[atno + slnptr->start_row] = aid;

		  /* symbvsvect[sno]->deps += [atno] + attr->deps 
                     i.e. previously constructed visit
		     must not be executed before this atno is evaluated
                  */
		  addtoset
                    (atno % WORD_LENGTH, 
                     slnptr->start_col + atno / WORD_LENGTH, 
                     symbvsvect[sno]->deps);
#ifndef GORTO
		  unionset
                    (prod->dp[atno + slnptr->start_row], 
                     symbvsvect[sno]->deps, 
                     setsize);
#else
		  dep_unionset
                    (prod->dp[atno + slnptr->start_row], 
                     symbvsvect[sno]->deps, 
                     prod);
#endif
	       } else
                  /* attribute atno is evaluated in that visit: */
		  addtoset
                    (atno % WORD_LENGTH, 
                     slnptr->start_col + atno / WORD_LENGTH, 
                     symbvsvect[sno]->vsinfo.visit.evalset);
	    }/* in currpartno */
	 }/* for atno */
      }	/* for currpartno */
   }/* for sno, slnptr */

   maxsymbno = sno - 1;


/* The first ancestor visit is removed.
   Its attributes are evaluated before this context is reached
   the first time from above:
*/
   unionset (symbvsvect[0]->vsinfo.visit.evalset, eval, setsize);
   diffset (eval, noteval, setsize);
   symbvsvect[0] = symbvsvect[0]->next;

   findevaluable ();
}/* visitseqinit() */

/********************************************************
*	void visitstrategy()				*
********************************************************/
static
void visitstrategy()
/* A visit-sequence is constructed by scheduling the visits
   using appendnextvs(symbno). 
   It allocates the necessary computations prior to the visit.
   Plain computations are scheduled immediately 
   before and after visits.
*/
{
   int symbno;
   bool foundancestor;
   BITVECTOR tmpset;

   /* tmpset := evaluable + eval */
   tmpset = mkemptyset (setsize);
   copyset (eval, tmpset, setsize);
   unionset (evaluable, tmpset, setsize);	

   if (TREE_BOTTOM_UP)
   {  /* virtual bottom-up phase: */

      /* if code computations are to be scheduled here,
         a message is to be given: */
      afterBUvisits = FALSE;

      /* plain computations are not scheduled here: */
      insertplain = FALSE;

      /* the rhs symbols are visited once from left to right: */
      for (symbno = 1; symbno <= maxsymbno; symbno++)
      {
	    if (issubset (symbvsvect[symbno]->deps, tmpset, setsize))
            {
	       appendnextvs (symbno);

               /* tmpset := evaluable + eval */
	       copyset (eval, tmpset, setsize);
	       unionset (evaluable, tmpset, setsize);
	    }
	    else
	    {
	       char errmsgbuff[ERR_BUFF_LEN];
	       err_setpos(prod->prod_def->row, prod->prod_def->col);
	       sprintf
                 (errmsgbuff,
		  "System error: can not schedule virtual visit to symb %d in RULE %s",
		  symbno, prod->prod_def->dname);
	       err_print_error(errmsgbuff);

	       fprintf
                 (ProtocolFile,
		  "*** SYSTEM *** can not schedule virtual visit to symb %d RULE %s\n",
		  symbno, prod->prod_def->dname);
	       exit(5);
	    }	/* if issubset */
      }	/* for */

      afterBUvisits = TRUE;
      /* end of virtual bottom-up phase 
         We now try to reach the first ancestor visit soon,
         if not in root context:
      */
      if (IsRootRule)
         goto normalstrategy;

      foundancestor = FALSE;
      symbno = 1 % (maxsymbno + 1);
      while (!foundancestor)
      {
        if (symbvsvect[0] != NULL &&
	    issubset (symbvsvect[0]->deps, tmpset, setsize))
        { appendnextvs (0);
          /* tmpset := evaluable + eval */
          copyset (eval, tmpset, setsize);
          unionset (evaluable, tmpset, setsize);
          foundancestor = TRUE;
	} else
        { if (maxsymbno > 0)
          {  /* find a subtree visit: */
             for (symbno=1; symbno<=maxsymbno; symbno++)
             if (symbvsvect[symbno] != NULL &&
	         issubset (symbvsvect[symbno]->deps, tmpset, setsize))
             { appendnextvs (symbno);
               copyset (eval, tmpset, setsize);
               unionset (evaluable, tmpset, setsize);
               break;
	     }
	  } else
          {
	       char errmsgbuff[ERR_BUFF_LEN];
	       err_setpos(prod->prod_def->row, prod->prod_def->col);
	       sprintf
                 (errmsgbuff,
		  "System error: can not schedule leave in RULE %s",
		  prod->prod_def->dname);
	       err_print_error(errmsgbuff);

	       fprintf
                 (ProtocolFile,
		  "*** SYSTEM *** can not schedule leave in RULE %s\n",
		  prod->prod_def->dname);
	       exit(5);
	  }
	}
      }/* foundancestor */

    /* The visit-sequence upto first ancestor visit is done.
       The partition of lhs bottomup attributes guarantees
       that their computations are scheduled.
    */
   }/* if TREE_BOTTOM_UP */

normalstrategy:

   /* Now we schedule without bottom-up consideration.
      if TREE_BOTTOM_UP afterBUvisits is already set before.
   */
   afterBUvisits = TRUE;
   /* Now we are ready for plain computations */
   insertplain = TRUE;

   /* we try to schedule as many subtree visits as possible
      before an ancestor visit is scheduled.
      Try visit of X[1] first, if exists 
   */
   symbno = 1 % (maxsymbno + 1);	

   foundancestor = TRUE;
   do
   {
      if (symbno == 0)
	 foundancestor = FALSE;

      if (symbvsvect[symbno] == NULL)
         /* no more visits to this one */
	 symbno = (symbno + 1) % (maxsymbno + 1);
      else
      {
	 if (issubset (symbvsvect[symbno]->deps, tmpset, setsize))
	 {
	    appendnextvs (symbno);
            /* tmpset := evaluable + eval */
	    copyset (eval, tmpset, setsize);
	    unionset (evaluable, tmpset, setsize);	

	    if (symbno == 0)
	       foundancestor = TRUE;

            /* start another round of search for subtree visits: */
	    symbno = 1 % (maxsymbno + 1);
	 } else
            /* try next subtree if any, else try ancestor: */
	    symbno = (symbno + 1) % (maxsymbno + 1);
      }
   } while (foundancestor);
}/* visitstrategy() */

static
void allocSymbVect ()
   /* symbvsvect is allocated here to allow Gorto to call
      rulevisitsequence directly, instead of being driven
      from visitsequences()
   */
{
   if (!symbvsvect)
   { 
     symbvsvect =
        (VSPTR *) Allocate
	    (__FILE__,__LINE__,(MaxRhsLen + 1) * sizeof(VSPTR));
     atvect =
        (int *) Allocate
	    (__FILE__,__LINE__,(MaxRuleAttrs + 1) * sizeof(int));
   }
}

/********************************************************
*	void rulevisitsequence()			*
*	compute the visit sequence for the given rule	*
********************************************************/

void rulevisitsequence(did) int did;
{
   int i;

   allocSymbVect ();
   pid = did;
   prod = &ref_tab[pid].entry.prod;
#ifndef GORTO
   if (!prod->cyclic)
   {
#else
   if (!(prod->state & S_CYCLIC))
   {
      prod->state |= S_VISIT_SEQ;
#endif

      /* The global variable setsize is set here for the current rule.
	 It is used in subsequent calls of set functions.
	 setsize >= 0 is ensured.
      */
      setsize = prod->check_col;
      if (setsize < 0) setsize = 0;

      nocyclicsymbs = TRUE;

      visitseqinit();

      if (nocyclicsymbs)
      {
	 visitstrategy();

	 if (prod->visitseq != NULL)
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(prod->prod_def->row, prod->prod_def->col);
	    sprintf
	      (errmsgbuff,
	       "System error: unscheduled plain computations in RULE %s",
	       prod->prod_def->dname);
	    err_print_error(errmsgbuff);

	    fprintf
	      (ProtocolFile,
	       "*** SYSTEM *** unscheduled plain computations in RULE %s\n",
	       prod->prod_def->dname);
	    exit(5);
	 }
	 ref_tab[pid].entry.prod.visitseq = rulevisitseq;

	 for (i = 0; i <= maxsymbno; i++)
	    if (symbvsvect[i] != NULL)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];
	       err_setpos(prod->prod_def->row, prod->prod_def->col);
	       sprintf
	         (errmsgbuff,
		  "System error: unscheduled visits in RULE %s",
		  prod->prod_def->dname);
	       err_print_error(errmsgbuff);

	       fprintf
	         (ProtocolFile,
		  "*** SYSTEM *** unscheduled visits in RULE %s\n",
		  prod->prod_def->dname);
	       exit(5);
	    }
	 for (i = 0; i < prod->check_row; i++)
	    if (atvect[i] != INACTIVE)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];
	       err_setpos(prod->prod_def->row, prod->prod_def->col);
	       sprintf
	         (errmsgbuff,
		  "System error: unscheduled computations in RULE %s",
		   prod->prod_def->dname);
	       err_print_error(errmsgbuff);

	       fprintf
	         (ProtocolFile,
		  "*** SYSTEM *** unscheduled computations in RULE %s\n",
		  prod->prod_def->dname);
	       exit(5);
	    }
      }	/* nocyclicsymbs */
   }	/* !cyclic */
}/* rulevisitsequence() */


/********************************************************
*	void visitsequence()				*
*	compute the visit sequences for the rules	*
********************************************************/

void visitsequence()
{
   int did;

   allocSymbVect ();
   for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == PROD)
      {
	 rulevisitsequence(did);
      }	/* PROD */
}/* end of visitsequence() */

/********************************************************
  Output of the resulting interface structure

  All computations and components thereof that are non-productive 
  are removed.

  Only those definitions of attributes are kept which still
  occur in some productive computations.
********************************************************/

/* switches for including substitution from expand options: */

static int EXP_INCL;
static char *INCL_ATTR;

#ifndef GORTO
extern OptCollect expand_opts; /* imported directly from expand module */
#endif

/* For Gorto the default options for including transport are used */

static void GetInclExpOpts ()
{ 
#ifndef GORTO
    ExpList expp;
#endif

  EXP_INCL = 0; /* default: including transport is removed */
  INCL_ATTR = "_incl";

#ifndef GORTO
  if (!expand_opts) return;
  expp = expand_opts->exp_opts;
  while (expp)
  {
    switch (expp->entry->flag)
    { case incl_attr_name:
        INCL_ATTR = expp->entry->attrname;
	break;
      case including_on:
        EXP_INCL = 1;
	break;
      case including_off:
        EXP_INCL = 0;
	break;
      default:
        break;
    }
    expp = expp->next;
  }
#endif
}/* GetInclExpOpts */

/* end expand options */

static
int IsVoidAttr (atdid) int atdid;
{ Attrdef ad = ref_tab[atdid].entry.attr.attr_def;
  return typeidOfAttrdef (ad) == DIDVOID ||
         typeidOfAttrdef (ad) == DIDVOLI;
}/* IsVoidAttr */

static
void KeepAttr (atdid) int atdid;
{ Attrdef ad = ref_tab[atdid].entry.attr.attr_def;
  storeOfAttrdef (ad) = STORGLST; /* mark to be kept */
}

#define KeptAttr(ad) (storeOfAttrdef(ad) == STORGLST)
#define ResetKeptAttr(ad) storeOfAttrdef(ad) = STORUNKN

static
int IsInclGenAttr (atdid) int atdid;
{ Attrdef ad = ref_tab[atdid].entry.attr.attr_def;
  return genOfAttrdef (ad) &&
         strncmp(ad->name, INCL_ATTR, strlen (INCL_ATTR)) == 0;
}/* IsInclGenAttr */

static
void RemoveAttrDef (ae) AttrEval ae;
/* removes each attribute definition ad 
   that does not occur in computations and
   hence has not been marked to be kept
*/
{ SEQDef defs; Def def;

  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
    if (typeof (def) == KSymb)
    { Symb sydef = DefToSymb (def);
      SEQAttrdef aseq; Attrdef atdef;
      SEQAttrdef keptattrs;

      initializeSEQAttrdef (keptattrs);
      foreachinSEQAttrdef (attrsOfSymb (sydef), aseq, atdef)
        if (KeptAttr (atdef))
        { ResetKeptAttr (atdef);
          appendrearSEQAttrdef (keptattrs, atdef);
	}
      attrsOfSymb (sydef) = keptattrs;
    }/* KSymb */
}/* RemoveAttrDef */

static Expr DummyExpr;

static
int SimplifyExpr (thisexp, voidcontext, listelem) 
      Expr thisexp; int voidcontext; SEQExpr listelem;
/* On entry
     thisexp is a non-assign expression in the stated context
     listelem->value == thisexp
   On exit
     Any non-productive components are removed.
     If thisexp is totally non-productive DummyExpr is assigned
        to listelem->value
     In voidcontext attributes are removed.
     In non-voidcontext an attribute is kept, even if it is VOID.
     Each kept attribute is marked in its definition,
       such that it will not be deleted.
     The result is 0 iff thisexp is to be removed completely.

     Includings are replaced is corresponding option is set.
*/
{ int productiveargs;

  switch (typeof (thisexp))
  {
    case KName: /* cpp-name may be productive */
      return 1;

    case KVal:
      return !voidcontext;

    case KIncluding:
    /* VOID Includings are removed,
       a value Including may be kept without notification of
       attributes to be kept, because there are value
       assignments to them.
    */
      if (voidcontext)
      { listelem->value = DummyExpr;
        return 0;
      } else
      { Including incl = ExprToIncluding (thisexp);
        SEQSymbattr ias = inclattrsOfIncluding (incl);
        Symbattr inclattr;
        retrievefirstSEQSymbattr (ias, inclattr);
        if (IsVoidAttr (attrdefOfSymbattr (inclattr)))
        { listelem->value = DummyExpr;
          return 0;
	}

        /* Here the task of replincl is taken over: */
        if (EXP_INCL) /* substitute Including by lhs attr access */
        { Attracc acc = 
            MkAttracc (0, genattridOfIncluding (incl),
                       rowOfIncluding (incl), colOfIncluding (incl));
          KeepAttr (genattridOfIncluding (incl));
          listelem->value = AttraccToExpr (acc);
	}
        return 1;
      }

    case KAttracc: 
      if (voidcontext)
      { listelem->value = DummyExpr;
        return 0;
      } else
      { /* an attribute that is kept in a computation
           is marked to be kept in its definition:
        */
        KeepAttr (attridOfAttracc (ExprToAttracc (thisexp)));
        return 1;
      }

    case KChainacc: /* should not occur */
    case KConstit: /* should not occur */
      listelem->value = DummyExpr;
      return 0;

    case KLiteral: /* should not occur */
      return !voidcontext;

    case KCall:
    { Call ca = ExprToCall (thisexp); 
      SEQExpr params = paramsOfCall (ca);
      Expr param;

      if (strcmp (DEPFCT, nameOfCall (ca)) == 0)
      { 
        if (emptySEQExpr (params)) return 0;
        ca->params->next = NULL;
        retrievefirstSEQExpr (params, param);
        if (!(SimplifyExpr (param, voidcontext, params)))
        { listelem->value = DummyExpr;
          return 0;
	} else return 1;
      } else

      if (strcmp (VOIDFCT, nameOfCall (ca)) == 0 ||
          strcmp ("creat$VOID_LIST", nameOfCall (ca)) == 0 ||
          strcmp ("concat$VOID_LIST", nameOfCall (ca)) == 0)
         /* marked to be omitted */
      {
        listelem->value = DummyExpr;
        return 0;
      } else

      if (strcmp (IFFCT, nameOfCall (ca)) == 0)
      { 
        if (emptySEQExpr (params)) return 0;
        /* condition: */
        retrievefirstSEQExpr (params, param);
        (void) SimplifyExpr (param, 0, params);

        /* then: */
        params = tailSEQExpr (params);
        if (emptySEQExpr (params)) return 0;
        retrievefirstSEQExpr (params, param);
        (void) SimplifyExpr (param, voidcontext, params);

        /* else: */
        params = tailSEQExpr (params);
        if (emptySEQExpr (params)) 
           return 1;
        retrievefirstSEQExpr (params, param);
        (void) SimplifyExpr (param, voidcontext, params);

        return 1;
      } else

      if (strcmp (ORDERFCT, nameOfCall (ca)) == 0)
      { int isproductive;
        if (emptySEQExpr (params))
        { listelem->value = DummyExpr;
          return 0;
	}
        productiveargs = 0;
        while (params->next != NULL)
        { /* non-last argument: */
          retrievefirstSEQExpr (params, param);
          isproductive = SimplifyExpr (param, 1, params);
          productiveargs = productiveargs || isproductive;
          params = tailSEQExpr (params);
	}
        retrievefirstSEQExpr (params, param);
        isproductive = SimplifyExpr (param, voidcontext, params);
        productiveargs = productiveargs || isproductive;
        if (!productiveargs)
        { listelem->value = DummyExpr;
          return 0;
	}
        return 1;
      } else

      if (strcmp (IDFCT, nameOfCall (ca)) == 0 ||
          strcmp (BOTTOMUPFCT, nameOfCall (ca)) == 0)
      { 
        if (emptySEQExpr (params)) return 0;
        retrievefirstSEQExpr (params, param);
        if (!(SimplifyExpr (param, voidcontext, params)))
        { listelem->value = DummyExpr;
          return 0;
	}
        return 1;
      } else

      if (strcmp (LOOPFCT, nameOfCall (ca)) == 0)
      { Attracc attr;

        /* condition: */
        if (emptySEQExpr (params)) return 0;
        retrievefirstSEQExpr (params, param);
        (void) SimplifyExpr (param, 0, params);

        /* loop attr must be kept: */
        params = tailSEQExpr (params);
        if (emptySEQExpr (params)) return 0;
        retrievefirstSEQExpr (params, param);
        if (typeof (param) != KAttracc) return 0;
        attr = ExprToAttracc (param);
        KeepAttr (attridOfAttracc (attr));

        /* loop iter: */
        params = tailSEQExpr (params);
        if (emptySEQExpr (params)) return 0;
        retrievefirstSEQExpr (params, param);
        (void)SimplifyExpr 
               (param, IsVoidAttr (attridOfAttracc (attr)), params);
        return 1;
      } else

      /* any other function call is considered to be productive,
         its arguments are checked in value context: */
      { 
        while (params != NULL)
        {
          retrievefirstSEQExpr (params, param);
          (void)SimplifyExpr (param, 0, params);
          params = tailSEQExpr (params);
	}
        return 1;
      }
    }/* KCall */
    default: /* should not occur */
      return 0;
  }
}/* SimplifyExpr */

int SimplifyAssign (thiscomp) Call thiscomp;
/* On entry:
     thiscomp is an ASSIGN (attr, rhs, markseq)
   On exit:
     0 is returned iff the computation is non-productive.
     The rhs is transformed by SimplifyExpr
     A productive VOID ASSIGN is turned into an IDFCT
*/
{   SEQExpr params = paramsOfCall (thiscomp);
    Expr lhs, rhs;
    SEQExpr marks;
    Attracc attr;
    int productiverhs, voidlhs, voidmark = 0;

    if (emptySEQExpr (params)) return 0;
    retrievefirstSEQExpr (params, lhs);
    if (emptySEQExpr (tailSEQExpr (params))) return 0;
    retrievefirstSEQExpr (tailSEQExpr (params), rhs);

  /* Some assigns are marked by appended TNVOID to the argument list:
        generated assigns for rule attrs in non-relevant contexts,
	generated assigns for GENTREEATTR in non-relevant contexts,
	expansion of remote value access used in void context.
     These may not be removed here if the attr is non-void,
     otherwise optim gets confused.
  */

    /*check marks: */
    marks = tailSEQExpr (tailSEQExpr (params));
    while (! emptySEQExpr (marks))
    { Expr mark;
      retrievefirstSEQExpr (marks, mark);
      if (typeof (mark) == KName &&
          strcmp (TNVOID, nOfName (ExprToName (mark))) == 0)
         voidmark = 1;
      marks = tailSEQExpr (marks);
    }

  /* check lhs attr: */
    if (typeof (lhs) != KAttracc) return 0;
    attr = ExprToAttracc (lhs);


  /* remove assign to generated INCL_ATTR: */
    if (!EXP_INCL && IsInclGenAttr (attridOfAttracc (attr)))
      return 0;

    voidlhs = IsVoidAttr (attridOfAttracc (attr));

  /* remove dummy assigns to void attr: */
    if (voidlhs && voidmark)
      return 0;

  /* transform rhs: */
    productiverhs = SimplifyExpr (rhs, voidlhs, tailSEQExpr (params));

  /* assign to loop attr must be kept even if VOID: */
    if (typeof (rhs) == KCall &&
        strcmp (INITCYCLEFCT, nameOfCall (ExprToCall (rhs))) == 0)
    { KeepAttr (attridOfAttracc (attr));
      return 1;
    }

    if (voidlhs)
    {
      if (productiverhs)
      {
        /* In this case we want to keep information for monitoring:
	   The rhs is wrapped into a call
	      "$MON" (rhs, Val (symbolnumber), Name("attrname"))
	*/
        Expr symbinfo, attrinfo;
        Attrdef ad = ref_tab[attridOfAttracc (attr)].entry.attr.attr_def;

	params->next->next = NULL; /* remove marks */
        nameOfCall (thiscomp) = "$MON";
	removefirstSEQExpr (paramsOfCall (thiscomp)); /* remove lhs */
        symbinfo = ValToExpr (MkVal (symbnoOfAttracc (attr), 0, 0));
	attrinfo = NameToExpr (MkName (nameOfAttrdef (ad), 0, 0));
	appendrearSEQExpr (paramsOfCall (thiscomp), symbinfo);
	appendrearSEQExpr (paramsOfCall (thiscomp), attrinfo);
	return 1;
      } else return 0;
    } else
    { /* value assign: */
      KeepAttr (attridOfAttracc (attr));
      return 1;
    }
}/* SimplifyAssign */

void write_dataStruct()
{  Attribution attribution; SEQAttribution a;
   SEQExpr GarbageSEQ;

   DummyExpr = ValToExpr (MkVal (1, 0, 0));
   GarbageSEQ = creatSEQExpr (DummyExpr);

   /* get expand options for including transformation: */
   GetInclExpOpts ();

   /* set mark for backend to generate bottom-up visits: */
   if (TREE_BOTTOM_UP)
      appendfrontSEQDef
        (defseqOfAttrEval (ISexp),
         MkDef (++ord_max_did, TNBUMARK, 1, 1,
	        TypedefToDef (MkTypedef ("",  0))));
	     
   /* construct the visit-sequences: */
   foreachinSEQAttribution(attrrulesOfAttrEval (ISexp), a, attribution)
   { VSPTR rulevisitseq, vselmptr;
     Attrrule tmpAttrrule;

     /* kill the sequence of pointers the computations: */
     initializeSEQAttrrule (attrrulesOfAttribution (attribution));

     /* rebuild the sequence of pointers the computations
        taken from the visit-sequence:
     */
     rulevisitseq = ref_tab[attribution->prodid].entry.prod.visitseq;
     for (vselmptr = rulevisitseq; vselmptr != NULL; vselmptr = vselmptr->next)
     switch (vselmptr->vscls)
     {
       case VSVISIT:
         { Visit vs = NVisit;
	   symbnoOfVisit (vs) = vselmptr->vsinfo.visit.vssno;
	   ordOfVisit (vs) = vselmptr->vsinfo.visit.vsord;
	   tmpAttrrule = VisitToAttrrule (vs);
	   appendrearSEQAttrrule
	     (attrrulesOfAttribution (attribution), tmpAttrrule);
	   break;
	 }
       case VSASSIG:
         /* attribute assign
            simplify and omit if non-productive:
         */
         if (SimplifyAssign (vselmptr->vsinfo.assig.idldef))
	 { tmpAttrrule = CallToAttrrule (vselmptr->vsinfo.assig.idldef);
	   appendrearSEQAttrrule
	      (attrrulesOfAttribution (attribution), tmpAttrrule);
	 }
         break;

       case VSCOND:
         /* plain computation
            simplify and omit if non-productive:
         */
         if (SimplifyExpr 
              (CallToExpr (vselmptr->vsinfo.cond.idldef),
               1,
               GarbageSEQ))
	 { tmpAttrrule = CallToAttrrule (vselmptr->vsinfo.cond.idldef);
           appendrearSEQAttrrule
	      (attrrulesOfAttribution (attribution), tmpAttrrule);
	 }
         break;

     }/* switch */
   }/* foreachinSEQAttribution */

   /* remove attribute definitions: */
   RemoveAttrDef (ISexp);
}/* write_dataStruct() */
