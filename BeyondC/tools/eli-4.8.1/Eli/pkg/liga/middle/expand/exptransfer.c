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
/* $Id: exptransfer.c,v 4.1 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: exptransfer.c,v 4.1 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		exptransfer.c					*
*	File:		exptransfer.c					*
*	Contents:	functions to expand attribute transfers		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	28 Jan 1991					*
*	Last change:	24 Sep 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "LIGAMacros.h"

#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "expand.h"
#include "expref.h"
#include "expidl.h"
#include "exptransfer.h"
#include "middle_mem.h"

/* **** EXPANSION OF TRANSFER SHORTHANDS *
 * 
 * To expand the TRANSFER shorthands this pass first calls the function *
 * unabbrev_transfers(). It searches for all TRANSFER rules in all
 * attributions. * It then calls unabbrev_tf() for each rule found. This
 * function then replaces * the rule by a set of nodes of which each stands
 * for an attribute that should * be transferred from the lhs symbol to a rhs
 * symbol or vice versa. All nodes * are linked into a list for this
 * production in the reference table. This is * done by calling ins_new_tf().
 * Then the control returns to the function * unabbrev_transfers(), where the
 * original rules are deleted. *  After building the list, expand_transfers()
 * is called to expand the nodes. * In an iterating step, it is tried to
 * expand all nodes left. The iteration * ends when no more nodes could be
 * expanded. To expand a node, expand_tf() is * called. This function looks
 * at the classes of the corresponding attributes on * the lhs and rhs side.
 * If both attributes have fixed and matching classes, a * normal expansion
 * takes place. If the class of one attribute is unknown, it * will become
 * the class of the corresponding attribute and an expansion takes * place.
 * If both attributes have different classes, an error message is printed *
 * and the node is marked as cancelled. If both attributes have unknow
 * classes, * the expansion of this node is delayed to the next iteration
 * when one of the * classes may have become available by simply doing
 * nothing. *  A node is expanded by generating an assignment. This is done
 * by * calling tf_assign(). After an expansion of a synthesized attribute
 * the * function check_more_tf() is called to check if more transfer nodes
 * for the * same attribute exist. *
 * 
****
 * 
 */

/* * GLOBAL VARIABLES */

/* * LOCAL VARIABLES */

/* * LOCAL FUNCTIONS */

static
#ifdef __STDC__
void 
tf_assign(
	  Attribution attrib,
	  TfNode tf,
	  int s1no,
	  char *s1name,
	  Attrdef a1def,
	  int s2no,
	  char *s2name,
	  Attrdef a2def)
#else
void 
tf_assign(attrib, tf, s1no, s1name, a1def, s2no, s2name, a2def)
   Attribution attrib;
   TfNode tf;
   int s1no, s2no;
   char *s1name, *s2name;
   Attrdef a1def, a2def;
#endif
/* insert 'assign' call into attribution of a production		 */
{
   Expr expr;
   SEQAttrrule tmp;
   Attrrule rule;

   /* check if tf node was already cancelled */
   if (tf->cancelled)
   {
     /*      (void) fprintf(ProtocolFile,
		     "\tno assignment generated due to previous error\n");
     */
     return;
   }	/* if */
   /* check if the types of both attributes match */
   if (typeidOfAttrdef(a1def) != typeidOfAttrdef(a2def))
   {
      print_err(tf->row, tf->col,
		"type conflict in assignment", ASGN_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  type conflict in assignment, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d\n\n", tf->row, tf->col);
      tf->cancelled = TRUE;
      return;
   }	/* if */
   /* search for another assignment to the same attribute */
   foreachinSEQAttrrule(attrrulesOfAttribution(attrib), tmp, rule)
   {
      if (typeof(rule) != KCall
	  || strcmp(nameOfCall(AttrruleToCall(rule)), ASSIGNFCT))
	 continue;
      retrievefirstSEQExpr(paramsOfCall(AttrruleToCall(rule)), expr);
      if (attridOfAttracc(ExprToAttracc(expr)) == didOfAttrdef(a1def)
	  && symbnoOfAttracc(ExprToAttracc(expr)) == s1no)
      {
	 print_err(tf->row, tf->col,
		   "explicit assignment overrides TRANSFER",
		   TFEX_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
		    "explicit assignment to %s<%d>.%s overrides TRANSFER, ",
			s1name, s1no + 1, nameOfAttrdef(a1def));
	 (void) fprintf(ProtocolFile,
			"line %d, col %d\n\n", tf->row, tf->col);
	 return;
      }	/* if */
   }	/* foreachinSEQAttrrule */

/*   protout(ProtocolFile,
	   "\t\t%s<%d>.%s := %s<%d>.%s;\n",
	   s1name, s1no + 1, nameOfAttrdef(a1def),
	   s2name, s2no + 1, nameOfAttrdef(a2def));
*/
   gen_assign(attrib, tf->row, tf->col,
	      s1no, didOfAttrdef(a1def),
	      s2no, didOfAttrdef(a2def),
	      (typeidOfAttrdef(a1def) == DIDVOID));
}/* tf_assign() */

static
#ifdef __STDC__
void 
check_more_tf(int pid, TfNode tf)
#else
void 
check_more_tf(pid, tf)
   int pid;
   TfNode tf;
#endif
/* check if more TRANSFER rules for the same attribute exist		 */
{
   TfNode tptr;
   int mesg;

   /* check if tf node was already cancelled */
   if (tf->cancelled)
      return;

   mesg = TRUE;
   /* check all following transfer rules */
   for (tptr = prodtrns(pid); tptr; tptr = tptr->next)
   {
      /* check if the attributes of the lhs symbols match */
      if (tptr != tf && tptr->lhs_attr == tf->lhs_attr)
      {
	 if (mesg)
	 {
	    print_err(tf->row, tf->col,
		      "multiple attributes for synthesized TRANSFER",
		      TFMS_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "multiple attributes for synthesized TRANSFER, ");
	    (void) fprintf(ProtocolFile,
			   "line %d, col %d\n\n", tf->row, tf->col);
	    mesg = FALSE;
	 }	/* if */
	 tptr->cancelled = TRUE;
      }	/* if */
   }	/* for */
}/* check_more_tf() */


static
#ifdef __STDC__
void 
ins_new_tf(
	   int pid,
	   int sid,
	   int sno,
	   Attrdef lad,
	   Attrdef rad,
	   int row,
	   int col)
#else
void 
ins_new_tf(pid, sid, sno, lad, rad, row, col)
   int pid;
   int sid, sno;
   Attrdef lad, rad;
   int row, col;
#endif
/* insert a transfer rule into production entry				 */
{
   TfNode new;

   /* allocate memory for new tf node */
   new = (TfNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct TfNode));
/*   protout(ProtocolFile,
	   "\t\tTRANSFER %s WITH %s<%d>\n",
	   nameOfAttrdef(rad), dnameOfSymb(symbref(sid)), sno + 1);
*/
   /* initialize new tf node */
   new->row = row;
   new->col = col;
   new->symbdid = sid;
   new->symb_no = sno;
   new->lhs_attr = lad;
   new->rhs_attr = rad;
   new->cancelled = FALSE;

   /* insert new tf node */
   new->next = prodtrns(pid);
   prodtrns(pid) = new;
}/* ins_new_tf() */


static
#ifdef __STDC__
void 
unabbrev_tf(int pid, Attrrule rule)
#else
void 
unabbrev_tf(pid, rule)
   int pid;
   Attrrule rule;
#endif
/* replace a single abbreviated TRANSFER rule by tf nodes		 */
/* the task is to find all intended attributes				 */
{
   Symb lhs_symb;
   SEQAttrdef tmp1;
   Attrdef lhs_attr;

   int attr_is, with_is;
   int found;

   SEQString tmp2;
   char *name;

   int symbno;
   SNode sptr;

   SEQint tmp3;
   int no;

   SEQAttrdef tmp4;
   Attrdef attr;

   with_is = !emptySEQint(symbnoOfTransfer(AttrruleToTransfer(rule)));
   attr_is = !emptySEQString(attrsOfTransfer(AttrruleToTransfer(rule)));

/*   protout(ProtocolFile,
	   "\texploring TRANSFER at line %d, column %d in production %s\n",
	   rowOfTransfer(AttrruleToTransfer(rule)),
	   colOfTransfer(AttrruleToTransfer(rule)),
	   dnameOfProd(prodref(pid)));
*/
   /* check entry of the lhs symbol in the reference table */
   if (exp_ref_tab[lhsOfProd(prodref(pid))].entry_tag != symbol_entry)
   {
      print_err(
		rowOfTransfer(AttrruleToTransfer(rule)),
		colOfTransfer(AttrruleToTransfer(rule)),
		"Internal error #1 in exptransfer.c", NO_ERRID);
      return;
   }	/* if */
   lhs_symb = symbref(lhsOfProd(prodref(pid)));

   /* walk through all attributes of the lhs symbol */
   foreachinSEQAttrdef(attrsOfSymb(lhs_symb), tmp1, lhs_attr)
   {
      /* check if this attribute is excluded */
      if (attr_is)
      {
	 found = 0;
	 foreachinSEQString(
		      attrsOfTransfer(AttrruleToTransfer(rule)), tmp2, name)
	 {
	    if (!strcmp(nameOfAttrdef(lhs_attr), name))
	    {
	       found++;
	       break;
	    }	/* if */
	 }	/* foreachinSEQString */
	 /* proceed loop if attribute was excluded */
	 if (!found)
	    continue;
      }	/* if */
      /* examine all symbols of the right hand side */
      symbno = 0;
      for (sptr = prodright(pid)->right; sptr; sptr = sptr->right)
      {
	 symbno++;
	 /* check if this symbol is excluded by WITH construct */
	 if (with_is)
	 {
	    found = 0;
	    foreachinSEQint(
			    symbnoOfTransfer(AttrruleToTransfer(rule)),
			    tmp3, no)
	    {
	       if (no == symbno)
	       {
		  found++;
		  break;
	       }	/* if */
	    }	/* foreachinSEQInteger */
	    /* proceed loop if symbol was excluded */
	    if (!found)
	       continue;
	 }	/* if */
	 /* examine all attributes of this symbol */
	 foreachinSEQAttrdef(
			     attrsOfSymb(symbref(sptr->symbdid)), tmp4, attr)
	 {
	    /* check if names are identical */
	    if (!strcmp(
			nameOfAttrdef(lhs_attr), nameOfAttrdef(attr)))
	    {
	       /* insert explicit TRANSFER rule */
	       ins_new_tf(
			  pid,
			  sptr->symbdid,
			  symbno,
			  lhs_attr,
			  attr,
			  rowOfTransfer(AttrruleToTransfer(rule)),
			  colOfTransfer(AttrruleToTransfer(rule)));
	    }	/* if */
	 }	/* foreachinSEQAttrdef */
      }	/* for */
   }	/* foreachinSEQAttrdef */
}/* unabbrev_tf() */


static
#ifdef __STDC__
int 
expand_tf(Attribution attrib, TfNode tf)
#else
int 
expand_tf(attrib, tf)
   Attribution attrib;
   TfNode tf;
#endif
/* expand a single TRANSFER rule					 */
{
   int pid;
   char *lhs_name;
   char *symbname;
   Attrdef lad, rad;

   /* don't expand if tf node was cancelled */
   if (tf->cancelled)
      return (FALSE);

   pid = prodidOfAttribution(attrib);
   lad = tf->lhs_attr;
   rad = tf->rhs_attr;
   lhs_name = dnameOfSymb(symbref(lhsOfProd(prodref(pid))));
   symbname = dnameOfSymb(symbref(tf->symbdid));
/*   protout(ProtocolFile, "\texpanding TRANSFER %s WITH %s<%d>",
	   nameOfAttrdef(lad), symbname, tf->symb_no + 1);
   protout(ProtocolFile,
	   " in production %s\n", dnameOfProd(prodref(pid)));
*/
   /* try to find the direction of the transfer */
   switch (classOfAttrdef(lad))
   {
   case ATCLSYNT:
      switch (classOfAttrdef(rad))
      {
      case ATCLSYNT:
	 tf_assign(attrib, tf,
		   0, lhs_name, lad,
		   tf->symb_no, symbname, rad);
	 check_more_tf(pid, tf);
	 break;
      case ATCLUNKN:
	 classOfAttrdef(rad) = ATCLSYNT;
/*	 (void) fprintf(ProtocolFile, "*** INFO  ");
	 (void) fprintf(ProtocolFile,
			"setting class of attribute %s.%s to %s\n",
			symbname, nameOfAttrdef(rad), "SYNTHESIZED");
*/
	 tf_assign(attrib, tf,
		   0, lhs_name, lad,
		   tf->symb_no, symbname, rad);
	 check_more_tf(pid, tf);
	 break;
      case ATCLINH:
	 print_err(tf->row, tf->col,
		   "class conflict for TRANSFER",
		   TFCL_ERRID);
	 (void) fprintf(ProtocolFile,
			"\n*** ERROR  class conflict for TRANSFER, ");
	 (void) fprintf(ProtocolFile,
			"line %d, col %d\n\n", tf->row, tf->col);
	 tf->cancelled = TRUE;
      default:
	 return (FALSE);
      }	/* switch */
      break;
   case ATCLINH:
      switch (classOfAttrdef(rad))
      {
      case ATCLINH:
	 tf_assign(attrib, tf,
		   tf->symb_no, symbname, rad,
		   0, lhs_name, lad);
	 break;
      case ATCLUNKN:
	 classOfAttrdef(rad) = ATCLINH;
/*	 (void) fprintf(ProtocolFile, "*** INFO  ");
	 (void) fprintf(ProtocolFile,
			"setting class of attribute %s.%s to %s\n",
			symbname, nameOfAttrdef(rad), "INHERITED");
*/
	 tf_assign(attrib, tf,
		   tf->symb_no, symbname, rad,
		   0, lhs_name, lad);
	 break;
      case ATCLSYNT:
	 print_err(tf->row, tf->col,
		   "class conflict for TRANSFER",
		   TFCL_ERRID);
	 (void) fprintf(ProtocolFile,
			"\n*** ERROR  class conflict for TRANSFER, ");
	 (void) fprintf(ProtocolFile,
			"line %d, col %d\n\n", tf->row, tf->col);
	 tf->cancelled = TRUE;
      default:
	 return (FALSE);
      }	/* switch */
      break;
   case ATCLUNKN:
      switch (classOfAttrdef(rad))
      {
      case ATCLINH:
	 classOfAttrdef(lad) = ATCLINH;
/*	 (void) fprintf(ProtocolFile, "*** INFO  ");
	 (void) fprintf(ProtocolFile,
			"setting class of attribute %s.%s to %s\n",
			lhs_name, nameOfAttrdef(lad), "INHERITED");
*/
	 tf_assign(attrib, tf,
		   tf->symb_no, symbname, rad,
		   0, lhs_name, lad);
	 break;
      case ATCLSYNT:
	 classOfAttrdef(lad) = ATCLSYNT;
/*	 (void) fprintf(ProtocolFile, "*** INFO  ");
	 (void) fprintf(ProtocolFile,
			"setting class of attribute %s.%s to %s\n",
			lhs_name, nameOfAttrdef(lad), "SYNTHESIZED");
*/	 tf_assign(attrib, tf,
		   0, lhs_name, lad,
		   tf->symb_no, symbname, rad);
	 check_more_tf(pid, tf);
	 break;
      case ATCLUNKN:
/*	 protout(ProtocolFile,
		 "\t\tdirection of TRANSFER yet unknown\n");
*/
       default:
	 return (FALSE);
      }	/* switch */
      break;
   default:
      return (FALSE);
   }	/* switch */

   return (TRUE);
}/* expand_tf() */

static
#ifdef __STDC__
SEQAttrrule 
remove_tf(SEQAttrrule list)
#else
SEQAttrrule 
remove_tf(list)
   SEQAttrrule list;
#endif
{
   Attrrule elem;
   SEQAttrrule newlist;
   if (emptySEQAttrrule(list))
      return (list);
   retrievefirstSEQAttrrule(list, elem);
   newlist = remove_tf(tailSEQAttrrule(list));
   if (typeof(elem) == KTransfer)
      removefirstSEQAttrrule(list);
   else
      appendfrontSEQAttrrule(newlist, elem);
   return (newlist);
}/* remove_tf */

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
int 
unabbrev_transfers(void)
#else
int 
unabbrev_transfers()
#endif
/* replace all abbreviated TRANSFER rules by tf nodes			 */
{
   SEQAttribution tmp1;
   Attribution attrib;
   SEQAttrrule tmp2;
   Attrrule rule;
   int prodid;
   int explored;
   int foundone;

/*   (void) fprintf(ProtocolFile, "\nexploring all TRANSFER statements\n");
*/
   explored = 0;

   /* walk through all attributions of productions */
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp1, attrib)
   {
      prodid = prodidOfAttribution(attrib);
      foundone = 0;
      /* walk through list of rules in this production */
      foreachinSEQAttrrule(attrrulesOfAttribution(attrib), tmp2, rule)
      {
	 if (typeof(rule) == KTransfer)
	 {
	    /* generate explicit transfer nodes */
	    unabbrev_tf(prodid, rule);
	    foundone = 1;
	    explored++;
	 }	/* if */
      }	/* foreachinSEQAttrrule */
      /* remove abbreviated TRANSFER rules */
      if (foundone)
	 attrrulesOfAttribution(attrib) =
	    remove_tf(attrrulesOfAttribution(attrib));
   }	/* foreachinSEQAttribution */

/*   switch (explored)
   {
   case 0:
      (void) fprintf(ProtocolFile,
		     "No TRANSFER statements found\n\n");

     break;
   case 1:
      (void) fprintf(ProtocolFile,
		     "One TRANSFER statement found\n\n");
      break;
   default:
      (void) fprintf(ProtocolFile,
		     "%d TRANSFER statements explored\n\n", explored);
   }
*/
   return (explored);
}/* unabbrev_transfers() */


#ifdef __STDC__
int 
expand_transfers(void)
#else
int 
expand_transfers()
#endif
/* expand all attribute transfers in the attribution			 */
{
   SEQAttribution tmp;
   Attribution attrib;
   int prodid;
   int expanded, not_expanded;
   int all_expanded;
   TfNode tptr1, tptr2;
   int iteration;

/*    (void) fprintf(ProtocolFile, "\nexpanding all TRANSFER rules\n");
*/
   not_expanded = 0;
   all_expanded = 0;
   iteration = 0;
   /* iterating loop to expand transfers */
   do
   {
/*      protout(ProtocolFile, " Iteration #%d\n", iteration + 1);
*/
     expanded = 0;
      /* walk through all attributions of productions */
      foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp, attrib)
      {
	 prodid = prodidOfAttribution(attrib);
	 /* check did of production */
	 if (exp_ref_tab[prodid].entry_tag != prod_entry)
	 {
	    print_err(0, 0, "Internal error #4 in exptransfer.c",
		      NO_ERRID);
	    continue;
	 }	/* if */
	 /* walk through list of transfer rules for this production */
	 tptr1 = prodtrns(prodid);
	 while (tptr1)
	 {
	    /* try to expand this rule and check the result */
	    if (expand_tf(attrib, tptr1))
	    {
	       /* remove the tf node */
	       if ((tptr2 = prodtrns(prodid)) == tptr1)
	       {
		  prodtrns(prodid) = tptr1->next;
		  tptr1 = prodtrns(prodid);
	       }
	        /* if */ 
	       else
	       {
		  for (; tptr2; tptr2 = tptr2->next)
		  {
		     if (tptr2->next == tptr1)
		     {
			tptr2->next = tptr1->next;
			tptr1 = tptr2->next;
			break;
		     }	/* if */
		  }	/* for */
	       }	/* else */
	       expanded++;
	       if (iteration)
	       {
		  not_expanded--;
	       }	/* if */
	    }
	     /* if */ 
	    else
	    {
	       if (!iteration)
	       {
		  not_expanded++;
	       }	/* if */
	       tptr1 = tptr1->next;
	    }	/* else */
	 }	/* for */

      }	/* foreachinSEQAttribution */
      all_expanded += expanded;

      iteration++;
   } while (expanded);
   /* repeat as long as further transfers can be expanded */

/*   (void) fprintf(ProtocolFile, "TRANSFER expansion: ");

   if (all_expanded)
   {
      (void) fprintf(ProtocolFile, "%d rules expanded",
		     all_expanded);
   }
   else
   {
      (void) fprintf(ProtocolFile, "no rules expanded");
   }	

   if (not_expanded)
   {
      (void) fprintf(ProtocolFile,
		     ", %d rule(s) left unexpanded\n\n", not_expanded);
   }
 
   else
   {
      (void) fprintf(ProtocolFile, "\n\n");
   }	
*/

   /* return number of not expanded transfers */
   return (not_expanded);
}/* expand_transfers() */

/***********************\
* end of exptransfer.c	*
\***********************/

/* HaDeS */
