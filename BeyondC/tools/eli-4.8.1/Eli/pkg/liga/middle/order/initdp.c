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
/* $Id: initdp.c,v 4.12 2005/07/21 10:49:06 peter Exp peter $ */
static char rcs_id[] = "$Id: initdp.c,v 4.12 2005/07/21 10:49:06 peter Exp peter $";

/************************************************************************
* 	Module  : initdp.c    						*
*       Author  : Jiyang Liu						*
*									*
*       Contains routines for Building the direct attribute dependency  *
*       graphs for  Rules, checking the consistency and completeness    *
*       of the AG, and routines for cycle checking.		        *
************************************************************************/

/* includes */

#include "ligaconsts.h"
#include "printerr.h"
#include "depmod.h"
#include "bottomup.h"
#include "do_order.h"
#include "reftab.h"
#include "visit.h"

#include "initdp.h"  

static int FailVar = 0;
#define FailAfterInit(i) FailVar = i

/****************************************************************
*       void enter_cond_deps(seqexpr, pid)                      *
*       enter the depended attributes of a condition. 		*
****************************************************************/
static
void enter_cond_deps (seqexpr, cond, pid)
   SEQExpr seqexpr;
   VSPTR cond;
   int pid;
{
   SEQExpr exprs;
   Expr expr;

   foreachinSEQExpr(seqexpr, exprs, expr)
   switch (typeof(expr))
   {
   case KAttracc:
      VSSetDepend (cond,
		   GetSymbOfProd (pid, expr.VAttracc->symbno),
		   GetSymAttrPos (expr.VAttracc->attrid));
      break;

   case KIncluding:
      /* genattr is one of the inherited attr's of lhs */
      VSSetDepend (cond,
		   GetSymbOfProd (pid, 0),
		   GetSymAttrPos (expr.VIncluding->genattrid));
      break;

   case KCall:
      if (expr.VCall->params != NULL)
	 enter_cond_deps (expr.VCall->params, cond, pid);
      break;

   case KConstit:
      {  err_setpos(expr.VConstit->row, expr.VConstit->col);
	 err_print_error("system error: CONSTITUENT(S) not expanded");
	 fprintf(ProtocolFile, "system error: CONSTITUENT(S) not expanded\n");
	 exit(3);	/* exit is ok here */
      }
      break;

   default:
      break;
   }	/* switch */
}/* enter_cond_deps() */

/************************************************************************
*									*
*	consistency checks						*
*									*
************************************************************************/
static
void mult_def_msg (pid, allcomps, duplicates)
        int pid; SEQAttrrule allcomps; SEQExpr duplicates;
{
  SEQExpr dpl; Expr lhs_expr;
  foreachinSEQExpr (duplicates, dpl, lhs_expr)
  {   char errmsgbuff[ERR_BUFF_LEN];
      Attracc lhsattr = lhs_expr.VAttracc;
      int aid = lhsattr->attrid;
      int sno = lhsattr->symbno;
      int lidopos = lidoposition (sno,pid);  /* positional index */
      SLNODE *lhsattrsym = GetSymbOfProd (pid, sno);
      SEQAttrrule atrs; Attrrule atr;

      foreachinSEQAttrrule (allcomps, atrs, atr)
      if (typeof(atr) == KCall &&
          strcmp(atr.VCall->name, ASSIGNFCT) == 0)
      {  Expr cmpex; Attracc cmplhs;
         retrievefirstSEQExpr (atr.VCall->params, cmpex);
	 if (typeof(cmpex) != KAttracc) 
	    continue;
	 cmplhs = cmpex.VAttracc;
	 if (cmplhs->attrid != aid || cmplhs->symbno != sno)
	    continue;

         if (lidopos == NONE) 
	 { sprintf(errmsgbuff,
		 "computation of %s.%s occurs multiply in RULE %s",
		 ref_tab[lhsattrsym->sid].entry.symb.symb_def->dname,
		 ref_tab[aid].entry.attr.attr_def->name,
		 ref_tab[pid].entry.prod.prod_def->dname);
	   err_setpos(cmplhs->row, cmplhs->col);
	   err_print_error(errmsgbuff);
	   fprintf(ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
         } else 
	 {
	   sprintf(errmsgbuff,
		 "computation of %s[%d].%s occurs multiply in RULE %s",
		 ref_tab[lhsattrsym->sid].entry.symb.symb_def->dname,
		 lidopos,
		 ref_tab[aid].entry.attr.attr_def->name,
		 ref_tab[pid].entry.prod.prod_def->dname);
	   err_setpos(cmplhs->row, cmplhs->col);
	   err_print_error(errmsgbuff);
	   fprintf(ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
	 }
         FailAfterInit(3);
      }
  }
}

static
void check_defining_occ (pid, lhs_expr) int pid; Expr lhs_expr;
{ Attracc lhsattr = lhs_expr.VAttracc;
  int aid = lhsattr->attrid;
  int sno = lhsattr->symbno;
  if (!((sno == 0 && ref_tab[aid].entry.attr.attr_def->class == ATCLSYNT) ||
        (sno >  0 && ref_tab[aid].entry.attr.attr_def->class == ATCLINH)))
  {
      char errmsgbuff[ERR_BUFF_LEN];
      int lidopos = lidoposition(sno,pid);  /* positional index */
      if (lidopos == NONE) 
      {
        sprintf(errmsgbuff, 
	      "computation of %s.%s must not occur in RULE %s",
	      ref_tab[ref_tab[aid].entry.attr.symbdid]
		.entry.symb.symb_def->dname,
	      ref_tab[aid].entry.attr.attr_def->name,
	      ref_tab[pid].entry.prod.prod_def->dname);
        err_setpos(lhsattr->row, lhsattr->col);
        err_print_error(errmsgbuff);
        fprintf(ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
      } else 
      {
	sprintf(errmsgbuff, 
		"computation of %s[%d].%s must not occur in RULE %s",
		ref_tab[ref_tab[aid].entry.attr.symbdid]
		  .entry.symb.symb_def->dname, 
		lidopos,
		ref_tab[aid].entry.attr.attr_def->name,
		ref_tab[pid].entry.prod.prod_def->dname);
        err_setpos(lhsattr->row, lhsattr->col);
        err_print_error(errmsgbuff);
        fprintf(ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
      }
      FailAfterInit(3);
  }
}

/************************************************************************
*									*
*	check whether there are computations for all
*       defining attribute occurrences in a rule         		*
*									*
************************************************************************/

#define RAMARKER "_RuleAttr_"
static
int isRuleAttr(nam) char* nam;
{   /* identify rule attributes by their name containing RAMARKER */ 
    return strstr(nam, RAMARKER) != 0;
}

static char* StripRuleAttrMark (nam) char* nam;
{ char *startOfMark = strstr(nam, RAMARKER);
  if (startOfMark)
  { /* remove the RAMARKER substring from a rule attribute's name */ 
    char *plainname = malloc (strlen(nam));
    char *p1, *p2;
    for (p1=nam, p2=plainname; p1 != startOfMark; p1++, p2++)
      *p2 = *p1;
    *p2 = 0;
    return plainname;
  } else return nam;
}


static
void is_complete (pid) int pid;
{
   int sno, sid, aid;
   SLNODE *slnptr;
   SEQAttrdef x;
   Attrdef attrdef;

   sno = 0;
   slnptr = ref_tab[pid].entry.prod.hdright;
   while (slnptr != NULL)
   {
      sid = slnptr->sid;

      if (ref_tab[sid].entry.symb.attr_num > 0)
      foreachinSEQAttrdef(ref_tab[sid].entry.symb.symb_def->attrs, x, attrdef)
      {
	 aid = attrdef->did;
	 if ((ref_tab[aid].entry.attr.attr_def->typeid != DIDVOLI) &&
	     /* DIDVOLI attributes need not be computed in every rule */
	     ((sno == 0 && 
	       ref_tab[aid].entry.attr.attr_def->class == ATCLSYNT) ||
	      (sno >  0 &&
	       ref_tab[aid].entry.attr.attr_def->class == ATCLINH)) &&
	      !DPAttrIsDefined(pid,slnptr,aid))
	 {
	       char errmsgbuff[ERR_BUFF_LEN];
	       if (lidoposition(sno,pid) == NONE) /* symbol index */
	       {
		 if (!isRuleAttr(ref_tab[aid].entry.attr.attr_def->name))
                 {
		     sprintf(errmsgbuff,
			     "computation of %s.%s is missing in RULE %s",
			     ref_tab[sid].entry.symb.symb_def->dname,
			     ref_tab[aid].entry.attr.attr_def->name,
			     ref_tab[pid].entry.prod.prod_def->dname);
		 } else
		 { 
		     sprintf(errmsgbuff,
			     "computation of rule attribute %s is missing in RULE %s",
			     StripRuleAttrMark(ref_tab[aid].entry.attr.attr_def->name),
			     ref_tab[pid].entry.prod.prod_def->dname);
		 }
	       } else 
	       {
		 sprintf(errmsgbuff,
		       "computation of %s[%d].%s is missing in RULE %s",
		       ref_tab[sid].entry.symb.symb_def->dname,
			 lidoposition(sno,pid),
		       ref_tab[aid].entry.attr.attr_def->name,
		       ref_tab[pid].entry.prod.prod_def->dname);
	       }
	       err_setpos(ref_tab[pid].entry.prod.prod_def->row,
			  ref_tab[pid].entry.prod.prod_def->col);
	       err_print_error(errmsgbuff);
	       fprintf(ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
	       FailAfterInit(1);
	 }
      }/* foreach */

      /* next symbol occurrence */
      slnptr = slnptr->right;
      sno++;
   }/* while */
}/* is_complete() */

#ifndef GORTO
/********************************************************
*	char *pr_graphstate_text()			*
********************************************************/

static
char * pr_graphstate_text(graph_state)
   int graph_state;
{
   switch (graph_state)
   {
   case DIRECT:
      return ("DIRECT");

   case TRANSITIVE:
      return ("TRANSITIV");

   case INDUCED:
      return ("INDUCED");

   case PARTITIONED:
      return ("PARTITIONED");

   default:
      return ("UNKNOWN");
   }
} /* pr_graphstate_text() */

#endif
/************************************************************************
*									*
*	bool enter_dp_matrix()						*
*	enter the dependency relations into one row of the bit-matrix	*
*	representing the initial dependency graph of the production.    *
*									*
************************************************************************/
static
void enter_dp_matrix (seqexpr, pid, tosymptr, toaid)
	SEQExpr seqexpr; SLNODE *tosymptr; int toaid;
/*
on entry:	pid is the current rule,
		row is the graph row of the target attribute,
on exit:	for each attr in seqexpr a dependency to the target attribute
		is entered into the rule graph,
*/
#ifndef GORTO
#define DPKIND 1
#else
#define DPKIND T_DIR
#endif
{
   SEQExpr exprs;
   Expr expr;
   SLNODE *slnptr;
   int aid;

   foreachinSEQExpr(seqexpr, exprs, expr)
      switch (typeof(expr))
   {
   case KAttracc:
      DPSetDepend (pid,
		   tosymptr, GetSymAttrPos (toaid),
		   GetSymbOfProd (pid, expr.VAttracc->symbno),
		   GetSymAttrPos (expr.VAttracc->attrid),
		   DPKIND,
		   expr.VAttracc->row);
      break;

   case KIncluding:
      /* genattr is one of the inherited attr's of lhs */
      aid = expr.VIncluding->genattrid;
      slnptr = ref_tab[pid].entry.prod.hdright;

      DPSetDepend (pid,
		   tosymptr, GetSymAttrPos (toaid),
		   GetSymbOfProd (pid, 0),
		   GetSymAttrPos (expr.VIncluding->genattrid),
		   DPKIND,
		   expr.VIncluding->row);
      break;

   case KCall:
      enter_dp_matrix (expr.VCall->params, pid, tosymptr, toaid);
      break;

   case KConstit:
      {  err_setpos(expr.VConstit->row, expr.VConstit->col);
	 err_print_error("system error: CONSTITUENT(S) not expanded");
	 fprintf(ProtocolFile, "system error: CONSTITUENT(S) not expanded\n");
	 exit(3);	/* exit is ok here */
      }
      break;

   default:
      break;
   }	/* switch */
}/* enter_dp_matrix */

/*************************************************************************
*									 *
*	void cons_init_dp();						 *
*	build the initial attribute dependency graphs for all		 *
*       productions.							 *
*	and check the consistency and completeness of the AG.		 *
*									 *
*************************************************************************/

void cons_init_dp (IS) AttrEval IS;
{  SEQAttribution x; Attribution attribution;

   /* go through the sequence of all attributions */
   foreachinSEQAttribution(IS->attrrules, x, attribution)
   {  SEQExpr duplicates;
      SEQAttrrule y; Attrrule attrrule;
      int pid = attribution->prodid;

      initializeSEQExpr (duplicates);

      foreachinSEQAttrrule(attribution->attrrules, y, attrrule)
      if (typeof(attrrule) == KCall) 
      {
	    if (strcmp(attrrule.VCall->name, ASSIGNFCT) == 0)
	    {  Expr lhs_expr;

	       ChkBUComp (attrrule.VCall);
		/* all plain BOTTOMUP comps are turned into assigns 
		   by frontend
		*/

	       /* left hand side of the attrrule */
	       retrievefirstSEQExpr(attrrule.VCall->params, lhs_expr);
	       if (typeof(lhs_expr) == KAttracc)
	       {  SEQExpr rhs_exprs, marks;
		  Expr rhs_expr, mark;
		  SLNODE *slnptr;
		  int aid, sno, is_add_dep = 0;

		  aid = lhs_expr.VAttracc->attrid;
		  sno = lhs_expr.VAttracc->symbno;

		  check_defining_occ (pid, lhs_expr);

		  retrievefirstSEQExpr 
		    (tailSEQExpr(attrrule.VCall->params), rhs_expr);

		  marks = tailSEQExpr(tailSEQExpr(attrrule.VCall->params));
		  while (!emptySEQExpr (marks))
		  { retrievefirstSEQExpr (marks, mark);
		    if (typeof (mark) == KName &&
			strcmp (MULTMARK,nOfName(ExprToName(mark))) == 0)
		       is_add_dep = 1;
		    marks = tailSEQExpr (marks);
		  }

		  /* check for multiple attribute computation: */

		  slnptr = GetSymbOfProd (pid, sno);
		  if (!is_add_dep && DPAttrIsDefined (pid, slnptr, aid))
		  { int gotit = 0; SEQExpr dpl; Expr exp;
		    foreachinSEQExpr(duplicates, dpl, exp)
		      if (exp.VAttracc->attrid == aid &&
			  exp.VAttracc->symbno == sno)
		         { gotit = 1; break;}
		    if (!gotit)
			appendfrontSEQExpr (duplicates, lhs_expr);
		  }

		  if (!is_add_dep)
		     DPAttrSetDefined (pid, slnptr, aid);

		  /* the rhs sequence of expressions of the attrrule  */
		  rhs_exprs = tailSEQExpr(attrrule.VCall->params);

		  /* enter the rhs dependencies: */
		  enter_dp_matrix (rhs_exprs, pid, slnptr, aid);

	       } else
	       {
		  err_setpos(lhs_expr.VAttracc->row, lhs_expr.VAttracc->col);
		  err_print_error("Left Hand Side of attrrule is not an attribute");
		  fprintf(ProtocolFile, "*** ERROR ***  lhs of attrrule is not an attribute. ***\n");
		  exit(3);	/* exit ok here, should be DEADLY error */
	       }

	    } else {
		/* plain function call */
		/* enter call into visit-sequence list of this rule: */
		VSPTR cond;
		cond = createcondition (pid, attrrule.VCall);
		enter_cond_deps (paramsOfCall (attrrule.VCall), cond, pid);
            }
      }/* end is Call, foreachSEQAttrrule */

      /* check for consistency in this rule */
      mult_def_msg (pid, attribution->attrrules, duplicates);
      is_complete (pid);
   }

   if (FailVar != 0) exit (FailVar);
}/* end of cons_init_dp() */



/****************************************************************
*	bool check_rule_cycle(pid)           			*
*	check cycles in attribute dependency graphs of    	*
*	rules 							*
****************************************************************/
static
bool check_rule_cycle()
{
   int pid;
   SLNODE *slnptr;
   PRODENTRY *prod;
   SYMBENTRY *symb;
   int atno;
#ifndef GORTO
   int aid;
#endif
   bool firsttime = TRUE;


   for (pid = min_entry; pid <= max_entry; pid++)
      if (ref_tab[pid].etag == PROD)
      {
	 prod = &ref_tab[pid].entry.prod;
	 for (slnptr = prod->hdright; slnptr != NULL; slnptr = slnptr->right)
	 {
	    symb = &ref_tab[slnptr->sid].entry.symb;
	    for (atno = 0; atno < symb->attr_num; atno++)

               if (DPDependson (pid, slnptr, atno, slnptr, atno))
	       {
#ifndef GORTO
		  prod->cyclic = TRUE;
		  if (firsttime)
		  {
		     char errmsgbuff[ERR_BUFF_LEN];
		     err_setpos(0, 0);
		     if (graphstate == PARTITIONED)
			sprintf(errmsgbuff,
				"did not find evaluation order; see OrdInfo, add dependencies, or use gorto");
		     else
			sprintf(errmsgbuff,
			"%s cyclic dependencies; see OrdInfo, or use gorto",
				pr_graphstate_text(graphstate));

		     err_print_error(errmsgbuff);

		     fprintf(ProtocolFile, "\n\n*** ERROR *** CYCLE IN %s GRAPHS FOR RULES:\n\n",
			     pr_graphstate_text(graphstate));
		     firsttime = FALSE;
		  }
		  aid = lookup_attr(slnptr->sid, atno);

		  {
		     char errmsgbuff[ERR_BUFF_LEN];
		     err_setpos(prod->prod_def->row, prod->prod_def->col);
		     if (graphstate == PARTITIONED)
		     { sprintf(errmsgbuff, "evaluation order for %s.%s not found",
			       symb->symb_def->dname,
			       ref_tab[aid].entry.attr.attr_def->name);
		     }
		     else /* induced cycle */

		     { sprintf(errmsgbuff, "%s.%s is involved in a cyclic dependency",
			       symb->symb_def->dname,
			       ref_tab[aid].entry.attr.attr_def->name);
		     }
		     err_print_error(errmsgbuff);
		  }

		  fprintf(ProtocolFile, "*** ERROR *** RULE %s SYMBOL %s ATTRIBUTE %s\n",
			  prod->prod_def->dname, symb->symb_def->dname,
			  ref_tab[aid].entry.attr.attr_def->name);
#else
		  prod->state |= S_CYCLIC;
		  firsttime = FALSE;
#endif
	       }
	 }
      }
   return (!firsttime);	/* return TRUE if cycle exists */

}/* check_rule_cycle () */


/****************************************************************
*       bool check_symb_cycle(sid)                              *
*       check cycles in attribute dependency graphs of all      *
*       symbols                                                 *
****************************************************************/
static
bool check_symb_cycle()
{

   int sid;
   SYMBENTRY *symb;
   int atno;
   int aid;
#ifndef GORTO
#endif
   bool firsttime = TRUE;

   for (sid = min_entry; sid <= max_entry; sid++)
      if (ref_tab[sid].etag == SYMB)
      {
	 symb = &ref_tab[sid].entry.symb;

	 for (atno = 0; atno < symb->attr_num; atno++)

	    if (DSDependson (sid, atno, atno))
	    {
#ifndef GORTO
	       symb->cyclic = TRUE;
	       if (firsttime)
	       {
		  char errmsgbuff[ERR_BUFF_LEN];

		  err_setpos(0, 0);
		  if (graphstate == PARTITIONED)
		     sprintf(errmsgbuff,
			     "did not find evaluation order; see OrdInfo, add dependencies, or use gorto");
		  else
		     sprintf(errmsgbuff,
		       "%s cyclic dependencies; see OrdInfo, or use gorto",
			     pr_graphstate_text(graphstate));
		  err_print_error(errmsgbuff);

		  fprintf(ProtocolFile, "\n\n*** ERROR *** CYCLE IN %s GRAPHS FOR SYMBOLS:\n\n",
			  pr_graphstate_text(graphstate));
		  firsttime = FALSE;
	       }
	       aid = lookup_attr(sid, atno);
	       fprintf(ProtocolFile, "*** ERROR *** SYMBOL %s ATTRIBUTE %s\n",
		       symb->symb_def->dname, ref_tab[aid].entry.attr.attr_def->name);

#else
               /*UK: mark attribute cyclic
                     for not hiding in gorto */
	       aid = lookup_attr(sid, atno);            
	       ref_tab[aid].entry.attr.cyclic = TRUE;   
	       symb->state |= S_CYCLIC;
	       firsttime = FALSE;
#endif
	    }
      }
   return (!firsttime);	/* return TRUE if cycle exists */

}/* check_symb_cycle() */

/****************************************************************
*       void check_cycle                                        *
*       check cycles in attribute dependency graphs of all      *
*       symbols and rules                                       *
****************************************************************/
#ifdef GORTO
extern bool Cyclic;
#endif

void check_cycle()
{
   bool cyclic;

   cyclic = check_rule_cycle();

   cyclic = check_symb_cycle() || cyclic;

#ifndef GORTO
   if (cyclic)
   {
      fprintf (ProtocolFile,
	       "*** Error! Cycles in %s GRAPHS *****\n",
	       pr_graphstate_text(graphstate));
      exit(3);	/* exit ok here */
   }
#else
   Cyclic = cyclic;
#endif
}/* check_cycle( ) */
