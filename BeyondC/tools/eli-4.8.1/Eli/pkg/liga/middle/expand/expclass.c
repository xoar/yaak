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
/* $Id: expclass.c,v 4.4 2000/09/05 07:18:11 cogito Exp $ */
static char rcs_id[] = "$Id: expclass.c,v 4.4 2000/09/05 07:18:11 cogito Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expclass.c					*
*	File:		expclass.c					*
*	Contents:	functions to classify attributes		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	09 Jan 1991					*
*	Last change:	24 Sep 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>
#include "middle_mem.h"
#include "LIGA.h"
#include "LIGAMacros.h"

#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "expref.h"
#include "expidl.h"
#include "expand.h"
#include "expclass.h"

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
Attrdef
get_symb_attr(int symbdid, int attr_did)
#else
Attrdef
get_symb_attr(symbdid, attr_did)
   int symbdid, attr_did;
#endif
/* get the definition of the attribute specified by the ids		 */
{
   Symb symb_def;
   Attrdef attr_def;
   SEQAttrdef ads;

   /* check entry of reference table */
   if (exp_ref_tab[symbdid].entry_tag != symbol_entry)
   {
      print_err(0, 0, "Internal error #2 in expclass.c", NO_ERRID);
      return ((Attrdef) NULL);
   }	/* if */
   /* search definition of attribute in definition of symbol */
   symb_def = symbref(symbdid);
   foreachinSEQAttrdef(attrsOfSymb(symb_def), ads, attr_def)
      if (didOfAttrdef(attr_def) == attr_did)
      return (attr_def);

   /* if the loop terminated unsuccessfully */
   return ((Attrdef) NULL);
}/* get_symb_attr() */

#ifdef __STDC__
void
set_attr_class(int symbdid, int attr_did, int newclass)
#else
void
set_attr_class(symbdid, attr_did, newclass)
   int symbdid, attr_did, newclass;
#endif
{
   Attrdef attr_def;

   attr_def = get_symb_attr(symbdid, attr_did);
   if (!attr_def)
   {
      print_err(0, 0, "Internal error #3 in expclass.c", NO_ERRID);
      return;
   }	/* if */
   classOfAttrdef(attr_def) = newclass;
}/* set_attr_class() */

#ifdef __STDC__
void
calc_classes(void)
#else
void
calc_classes()
#endif
/* compute classes for attributes by looking at "assign" calls		 */
{
   SEQAttribution sa;
   Attribution prod_attr;
   SEQAttrrule sar;
   Attrrule attrib;

   int assign_symb;
   Expr lhs_attr;
   Attrdef attribute;
   int class;

   /* search for all "assign" calls */
   foreachinSEQAttribution(IdlStruct->attrrules, sa, prod_attr)
   {
      foreachinSEQAttrrule(prod_attr->attrrules, sar, attrib)
      {
	 if (typeof(attrib) == KCall
	     && !strcmp(nameOfCall(AttrruleToCall(attrib)), ASSIGNFCT))
	 {

	    /* compute class of lhs attribute in assignment	 */
	    retrievefirstSEQExpr(
				 paramsOfCall(AttrruleToCall(attrib)),
				 lhs_attr);
	    /* lhs expression must be attribute access	 */
	    if (typeof(lhs_attr) != KAttracc)
	    {
	       /* print error message if access is not valid	 */
	       if (typeof(lhs_attr) != KChainacc)
		  print_err(
			    rowOfCall(AttrruleToCall(attrib)),
			    colOfCall(AttrruleToCall(attrib)),
			    "Illegal lhs in assignment", ASGN_ERRID);
	    } else
	    {
	       assign_symb = ith_symbol_of_prod(
				   symbnoOfAttracc(ExprToAttracc(lhs_attr)),
					    prodidOfAttribution(prod_attr));
	       /* check symbol on lhs of assignment */
	       if (!assign_symb
		   || exp_ref_tab[assign_symb].entry_tag != symbol_entry)
	       {
		  print_err(
			    rowOfCall(AttrruleToCall(attrib)),
			    colOfCall(AttrruleToCall(attrib)),
			    "Internal error #3 in expclass.c", NO_ERRID);
		  continue;
	       }	/* if */
	       attribute = get_symb_attr(
					 assign_symb,
				  attridOfAttracc(ExprToAttracc(lhs_attr)));

	       /* determinate class of attribute:			 */
	       /* an assignment to an attribute of the lhs symbol	 */
	       /* specifies it as synthesized, otherwise inherited	 */
	       class = (symbnoOfAttracc(ExprToAttracc(lhs_attr))) ?
		  ATCLINH : ATCLSYNT;
	       if (classOfAttrdef(attribute) == ATCLUNKN)
	       {
		  classOfAttrdef(attribute) = class;
/*		  (void) fprintf(ProtocolFile, "*** INFO  ");
		  (void) fprintf(ProtocolFile,
				 "setting class of attribute %s.%s to %s\n",
				 dnameOfSymb(symbref(assign_symb)),
				 nameOfAttrdef(attribute),
			  (class == ATCLINH) ? "INHERITED" : "SYNTHESIZED");
*/
		}	/* if */
	       if (classOfAttrdef(attribute) != class)
	       {
		  char *msg;
		  msg = (char *) middle_tempMalloc(__FILE__, __LINE__, 48
				 + strlen(dnameOfSymb(symbref(assign_symb)))
					+ strlen(nameOfAttrdef(attribute)));
		  (void) sprintf(msg,
				 "class conflict for attribute %s.%s",
				 dnameOfSymb(symbref(assign_symb)),
				 nameOfAttrdef(attribute));
		  print_err(
			    rowOfCall(AttrruleToCall(attrib)),
			    colOfCall(AttrruleToCall(attrib)),
			    msg, ATCL_ERRID);
		  protout(ProtocolFile,
			  "\n*** ERROR  %s in line %d, column %d\n\n",
			  msg,
			  rowOfCall(AttrruleToCall(attrib)),
			  colOfCall(AttrruleToCall(attrib)));
		  /* ambiguous attributes are set to class SYNTHESIZED */
		  classOfAttrdef(attribute) = ATCLSYNT;
	       }	/* if */
	    }	/* if */
	 }	/* if */
      }	/* foreachinSEQAttrrule */
   }	/* foreachinSEQAttribution */
}/* calc_classes() */

#ifdef __STDC__
void
set_term_classes(void)
#else
void
set_term_classes()
#endif
/* set unknown classes of terminal attributes to SYNTHESIZED		 */
{
   SEQDef x;
   Def symb;
   SEQAttrdef y;
   Attrdef attribute;

   foreachinSEQDef(defseqOfAttrEval(IdlStruct), x, symb)
   {
      /* look for symbol definition */
      if (typeof(symb) == KSymb)
      {
	 /* look for terminal symbol */
	 if (torntOfSymb(DefToSymb(symb)) == SYMBTERM)
	 {
	    /* set all attributes of the terminal symbol */
	    foreachinSEQAttrdef(attrsOfSymb(DefToSymb(symb)), y, attribute)
	    {
	       if (classOfAttrdef(attribute) == ATCLUNKN)
	       {
		  classOfAttrdef(attribute) = ATCLSYNT;
/*		  (void) fprintf(ProtocolFile, "*** INFO  ");
		  (void) fprintf(ProtocolFile,
			"setting class of terminal attribute %s.%s to %s\n",
				 dnameOfSymb(DefToSymb(symb)),
				 nameOfAttrdef(attribute),
				 "SYNTHESIZED");
*/
		}	/* if */
	    }	/* foreachinSEQAttrdef */
	 }	/* if */
      }	/* if */
   }	/* foreachinSEQDef */
}/* set_term_classes() */

#ifdef __STDC__
void
check_classes(void)
#else
void
check_classes()
#endif
/* check classes of all attributes and report classes			 */
{
   SEQDef tmp1;
   Def def;
   SEQAttrdef tmp2;
   Attrdef attrdef;

/*   protout(ProtocolFile, "\nSymbol classes:\n");
*/
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (typeof(def) == KSymb)
      {
/*	 protout(ProtocolFile,
		 "\t%s %s:\n",
		 torntOfSymb(DefToSymb(def)) == SYMBTERM ?
		 "terminal" : "nonterminal",
		 dnameOfSymb(DefToSymb(def)));
*/
	 foreachinSEQAttrdef(attrsOfSymb(DefToSymb(def)), tmp2, attrdef)
	 {
	    if (EXP_PROT)
	    {
/*	       (void) fprintf(ProtocolFile,
			      "\t\tattribute %s is ",
			      nameOfAttrdef(attrdef));
*/
/*	       switch (classOfAttrdef(attrdef))
	       {
	       case ATCLSYNT:
		  (void) fprintf(ProtocolFile, "SYNTHESIZED\n");

		 break;
	       case ATCLINH:
		  (void) fprintf(ProtocolFile, "INHERITED\n");
		  break;
	       case ATCLUNKN:
		  (void) fprintf(ProtocolFile, "UNKNOWN\n");
		  break;
	       default:
		  (void) fprintf(ProtocolFile, "???\n");
		  break;
		  }  
*/
	    }	/* if */
	    if (classOfAttrdef(attrdef) == ATCLUNKN)
	    {
	       char *msg;

	       msg = (char *) middle_Malloc(__FILE__, __LINE__, 64
				     + strlen(dnameOfSymb(DefToSymb(def)))
				     + strlen(nameOfAttrdef(attrdef)));
	       (void) sprintf(msg,
			      "there is no computation of attribute %s.%s",
			      dnameOfSymb(DefToSymb(def)),
	 		      nameOfAttrdef(attrdef));
	       print_err(rowOfSymb(DefToSymb(def)), 
			 colOfSymb(DefToSymb(def)),
			 msg, ATCL_ERRID);
	       (void) fprintf(ProtocolFile, "*** ERROR  %s\n", msg);
	    }	/* if */
	 }	/* foreachinSEQAttrdef */
      }	/* if */
   }	/* foreachinSEQDef */
}/* check_classes() */

/***********************\
* end of expclass.c	*
\***********************/

/* HaDeS */

