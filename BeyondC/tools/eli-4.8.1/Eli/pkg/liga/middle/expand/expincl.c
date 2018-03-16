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
/* $Id: expincl.c,v 4.2 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: expincl.c,v 4.2 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expincl.c					*
*	File:		expincl.c					*
*	Contents:	functions to expand the INCLUDING construct	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	07 Feb 1991					*
*	Last change:	22 Apr 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "LIGAMacros.h"

#include "middle_mem.h"
#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "expref.h"
#include "expidl.h"
#include "expand.h"
#include "exptrav.h"
#include "expincl.h"
#include "exp_prot.h"

/* **** EXPANSION OF INCLUDING CONSTRUCTS *
 * 
 * To expand the INCLUDING construct this pass first calls the function *
 * find_includings(). It searches for all INCLUDING constructs by calling *
 * the recursive function incl_in_call() for all CALL rules at the top level *
 * of the attribution for all productions. The function is recursive because *
 * CALL rules could be nested. All constructs that are found are checked for *
 * various error conditions in the function check_incl() and added to a
 * global * list by calling append_incl(). Identical constructs (the lists of
 * attributes * to be included must match) are collected in special lists. *
 * The next step is to call expand_includings(). This function runs through *
 * the list of INCLUDING constructs. For each construct and its identical *
 * constructs first all flags on productions and symbols are cleared and then *
 * mark_including() is called. All productions with symbols that carry *
 * attributes on the left hand side that should be included are marked as
 * start * productions. All productions containing one of the INCLUDING
 * constructs are * marked as target productions. For each target production
 * mark_incl_trans() is * called to find a path to one of the start
 * productions. The function * mark_incl_trans() marks the lhs symbol as
 * transport symbol and calls itself * recursively to mark all productions
 * containing the symbol on the right hand * side as transport productions.
 * The recursion terminates at either the root * symbol or at a start
 * production. *  After the productions and symbols have been marked, the
 * function * expand_including() is called by the function
 * expand_includings(). This * functions runs through the attributions of all
 * productions and generates * the appropriate assignments in start,
 * transport and target productions by * calling the functions
 * incl_src_assign(), incl_trns_assign() and * incl_target_assign()
 * respectively. *
 * 
***
 * 
 */


/* * GLOBAL VARIABLES */

IncNode includings;	/* global list of all INCLUDING constructs	 */


/* * LOCAL VARIABLES */

static int trans_assigns;	/* number of new assignments for transport */
static int source_assigns;	/* number of new assignments from sources */
static int newassigns;	        /* total number of new assignments	 */


/* * LOCAL FUNCTIONS */
#if defined (__cplusplus) || defined(__STDC__)
extern void prot_incl(FILE *prot, Including inc)
#else
extern void prot_incl(prot, inc)
FILE *prot;
Including inc;
#endif
{ SEQSymbattr tmp1;
  SEQAttrdef tmp2;
  Symbattr sa;
  Attrdef ad;
  int attrid;

  fprintf(prot, "INCLUDING (");
  foreachinSEQSymbattr(inclattrsOfIncluding(inc), tmp1, sa)
    { fprintf(prot, "%s", dnameOfSymb(symbref(symbdefOfSymbattr(sa))));
      attrid=attrdefOfSymbattr(sa);
      foreachinSEQAttrdef(attrsOfSymb(symbref(symbdefOfSymbattr(sa))),tmp2,ad)
        { if (didOfAttrdef(ad) == attrid) 
            { fprintf(prot, ".%s", nameOfAttrdef(ad));
              break;
            }
        }
      if (tmp1->next != NULL) /* there's another one */
         fprintf(prot, ", ");
    }
  fprintf(prot, ")\n");
}

static
#ifdef __STDC__
void
show_including(IncNode incptr)
#else
void
show_including(incptr)
   IncNode incptr;
#endif
/* show this INCLUDING construct and it's similar constructs		 */
{
   IncNode sameinc;

   if (!incptr)
      return;

   protout(ProtocolFile, "\nINCLUDING construct:\n   ");
   prot_incl(ProtocolFile, incptr->incl);

   if (!incptr->same) 
   {  protout(ProtocolFile, "Occurrence:\n   ");
   }
   else 
   {  protout(ProtocolFile, "Occurrence 1:\n   ");
   }
   prot_position(ProtocolFile, 
		 rowOfIncluding(incptr->incl),
		 colOfIncluding(incptr->incl));
   protout(ProtocolFile, "   RULE ");
   prot_rule(ProtocolFile, incptr->prodid);

   sameinc = incptr->same;
   if (sameinc)
   { int occnt = 2;
      for (; sameinc; sameinc = sameinc->same)
      {
	protout(ProtocolFile, "Occurrence %d:\n   ", occnt++);
	prot_position(ProtocolFile, 
			 rowOfIncluding(sameinc->incl),
			 colOfIncluding(sameinc->incl));
	protout(ProtocolFile, "   RULE ");
	prot_rule(ProtocolFile, sameinc->prodid);
      }	/* for */
   }	/* if */
 }/* show_including() */

static
#ifdef __STDC__
void
mark_including(IncNode incptr)
#else
void
mark_including(incptr)
   IncNode incptr;
#endif
/* mark symbols and productions for expansion of INCLUDING		 */
{
   IncNode incnode;
   SEQSymbattr tmp;
   Symbattr sa;
   SNode symbs;

   /* mark source productions */
   foreachinSEQSymbattr(inclattrsOfIncluding(incptr->incl), tmp, sa)
   {
      /* mark all productions with the symbol on the lhs */
      for (symbs = symbldown(symbdefOfSymbattr(sa));
	   symbs; symbs = symbs->down)
      {
	 prodflag(symbs->prodid) |= start_prod;
      }	/* for */
   }	/* foreachinSEQSymbattr */

   markedsymbs = 0;
   markedprods = 0;
   protout(ProtocolFile, "Transport attributes:\n");
   /* mark transport symbols and productions */
   /* for all identical constructs */
   for (incnode = incptr; incnode; incnode = incnode->same)
   {
      /* mark production as target production */
      prodflag(incnode->prodid) |= target_prod;

      /* mark symbols and productions for transport */
      mark_incl_trans(lhsOfProd(prodref(incnode->prodid)), incnode);
   }	/* for */
/*    protout(ProtocolFile,
	   "   marked for transport: %d symbols, %d productions\n",
	   markedsymbs, markedprods);
*/
}/* mark_including() */

static
#ifdef __STDC__
void
incl_src_assign(IncNode incptr, Attribution attrib)
#else
void
incl_src_assign(incptr, attrib)
   IncNode incptr;
   Attribution attrib;
#endif
/* create assignments from INCLUDING attribute to transport attributes	 */
{
   int pid;
   int lhsymb;
   SEQSymbattr tmp1;
   Symbattr sa;
   int attrid;
   SEQAttrdef tmp2;
   Attrdef ad;
   Attrdef tad;
   SNode sn;
   int sno;
   int source_used;

   /* get dids of the production and its left hand symbol */
   pid = prodidOfAttribution(attrib);
   lhsymb = prodright(pid)->symbdid;

   /* search for source attribute */
   attrid = -1;
   foreachinSEQSymbattr(inclattrsOfIncluding(incptr->incl), tmp1, sa)
   {
      if (symbdefOfSymbattr(sa) == lhsymb)
      {
	 attrid = attrdefOfSymbattr(sa);
	 break;
      }	/* if */
   }	/* foreachinSEQSymbattr */

   if (attrid == -1)
   {
      /* this case should never occur */
      print_err(
		rowOfIncluding(incptr->incl),
		colOfIncluding(incptr->incl),
		"expincl.c: internal error #1", NO_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  expincl.c: internal error #1, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfIncluding(incptr->incl),
		     colOfIncluding(incptr->incl),
		     dnameOfProd(prodref(pid)));
   }	/* if */
   /* search for definition of included attribute */
   foreachinSEQAttrdef(attrsOfSymb(symbref(lhsymb)), tmp2, ad)
   {
      if (didOfAttrdef(ad) == attrid)
	 break;
   }	/* foreachinSEQAttrdef */

   protout(ProtocolFile, "   RULE ");
   if (EXP_PROT)
     prot_rule(ProtocolFile, pid);
   source_used = FALSE;

   /* search all transport symbols on the right hand side */
   sno = 0;
   for (sn = prodright(pid)->right; sn; sn = sn->right)
   {
      sno++;
      if (symbflag(sn->symbdid) == trnsp_symb)
      {
	 /* generate assignment to transport symbol */
	 retrievefirstSEQAttrdef(attrsOfSymb(symbref(sn->symbdid)), tad);

	 /* transport attribute was first attribute of this symbol */
	 if (strcmp(nameOfAttrdef(tad), genattrOfIncluding(incptr->incl)))
	 {
	    print_err(
		      rowOfIncluding(incptr->incl),
		      colOfIncluding(incptr->incl),
		      "expincl.c: internal error #2", NO_ERRID);
	    (void) fprintf(ProtocolFile,
			   "\n*** ERROR  expincl.c: internal error #2, ");
	    (void) fprintf(ProtocolFile,
			   "line %d, col %d in production %s\n\n",
			   rowOfIncluding(incptr->incl),
			   colOfIncluding(incptr->incl),
			   dnameOfProd(prodref(pid)));
	 }	/* if */
	 protout(ProtocolFile,
		 "      %s<%d>.%s = %s<1>.%s;\n",
		 dnameOfSymb(symbref(sn->symbdid)), sno + 1,
		 nameOfAttrdef(tad), dnameOfSymb(symbref(lhsymb)),
		 nameOfAttrdef(ad));
	 gen_assign(attrib,
		    rowOfIncluding(incptr->incl),
		    colOfIncluding(incptr->incl),
		    sno, didOfAttrdef(tad),
		    0, didOfAttrdef(ad),
		    (incptr->typeid == DIDVOID || incptr->dep));
	 source_assigns++;
	 newassigns++;
	 source_used = TRUE;
      }	/* if */
   }	/* for */
   if (EXP_PROT && !source_used)
   {
      (void) fprintf(ProtocolFile,
		     "      value from this source context will not be accessed\n");
   }	/* if */
}/* incl_src_assign() */

static
#ifdef __STDC__
void
incl_trns_assign(IncNode incptr, Attribution attrib)
#else
void
incl_trns_assign(incptr, attrib)
   IncNode incptr;
   Attribution attrib;
#endif
/* create assignments for INCLUDING transport attributes		 */
{
   int pid;
   int lhsymb;
   Attrdef ad;
   SNode sn;
   int sno;
   Attrdef tad;

   pid = prodidOfAttribution(attrib);
   lhsymb = prodright(pid)->symbdid;

   /* transport attribute should be first attribute */
   retrievefirstSEQAttrdef(attrsOfSymb(symbref(lhsymb)), ad);

   if (strcmp(genattrOfIncluding(incptr->incl), nameOfAttrdef(ad)))
   {
      /* this case should never occur */
      print_err(
		rowOfIncluding(incptr->incl),
		colOfIncluding(incptr->incl),
		"expincl.c: internal error #3", NO_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  expincl.c: internal error #3, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfIncluding(incptr->incl),
		     colOfIncluding(incptr->incl),
		     dnameOfProd(prodref(pid)));
   }	/* if */
   protout(ProtocolFile, "   RULE ");
   if (EXP_PROT)
     prot_rule(ProtocolFile,pid);

   /* search all transport symbols for transport attributes */
   sno = 0;
   for (sn = prodright(pid)->right; sn; sn = sn->right)
   {
      sno++;
      if (symbflag(sn->symbdid) == trnsp_symb)
      {
	 /* generate assignment to transport symbol */
	 retrievefirstSEQAttrdef(attrsOfSymb(symbref(sn->symbdid)), tad);

	 /* transport attribute should be first attribute */
	 if (strcmp(nameOfAttrdef(tad), genattrOfIncluding(incptr->incl)))
	 {
	    print_err(
		      rowOfIncluding(incptr->incl),
		      colOfIncluding(incptr->incl),
		      "expincl.c: internal error #4", NO_ERRID);
	    (void) fprintf(ProtocolFile,
			   "\n*** ERROR  expincl.c: internal error #4, ");
	    (void) fprintf(ProtocolFile,
			   "line %d, col %d in production %s\n\n",
			   rowOfIncluding(incptr->incl),
			   colOfIncluding(incptr->incl),
			   dnameOfProd(prodref(pid)));
	 }	/* if */
	 protout(ProtocolFile,
		 "      %s<%d>.%s = %s<1>.%s;\n",
		 dnameOfSymb(symbref(sn->symbdid)), sno + 1,
		 nameOfAttrdef(tad), dnameOfSymb(symbref(lhsymb)),
		 nameOfAttrdef(ad));
	 gen_assign(attrib,
		    rowOfIncluding(incptr->incl),
		    colOfIncluding(incptr->incl),
		    sno, didOfAttrdef(tad),
		    0, didOfAttrdef(ad),
		    (incptr->typeid == DIDVOID || incptr->dep));
	 trans_assigns++;
	 newassigns++;
      }	/* if */
   }	/* for */

}/* incl_trns_assign() */

static
#ifdef __STDC__
void
incl_target_assign(IncNode incptr, Attribution attrib)
#else
void
incl_target_assign(incptr, attrib)
   IncNode incptr;
   Attribution attrib;
#endif
/* modify INCLUDING construct to access transport attribute		 */
{
   int pid;
   int lhsymb;
   Attrdef ad;
   IncNode including;
   int found;

   pid = prodidOfAttribution(attrib);
   lhsymb = prodright(pid)->symbdid;
   protout(ProtocolFile,"   RULE ");
   if (EXP_PROT)
     prot_rule(ProtocolFile, pid);
   protout(ProtocolFile, "      %s.%s carries value of INCLUDING construct\n",
	   dnameOfSymb(symbref(lhsymb)),
	   genattrOfIncluding(incptr->incl));

   /* transport attribute should be first attribute */
   retrievefirstSEQAttrdef(attrsOfSymb(symbref(lhsymb)), ad);

   if (strcmp(genattrOfIncluding(incptr->incl), nameOfAttrdef(ad)))
   {
      /* this case should never occur */
      print_err(
		rowOfIncluding(incptr->incl),
		colOfIncluding(incptr->incl),
		"expincl.c: internal error #5", NO_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  expincl.c: internal error #5, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfIncluding(incptr->incl),
		     colOfIncluding(incptr->incl),
		     dnameOfProd(prodref(pid)));
   }	/* if */
   found = FALSE;
   /* search for including constructs */
   for (including = incptr; including; including = including->same)
   {
      if (including->prodid == pid)
      {
	 found = TRUE;
	 /* enter did of transport attribute */
	 genattridOfIncluding(including->incl) = didOfAttrdef(ad);
      }	/* if */
   }	/* for */

   /* at least on construct must have been found */
   if (!found)
   {
      /* this case should never occur */
      print_err(
		rowOfIncluding(incptr->incl),
		colOfIncluding(incptr->incl),
		"expincl.c: internal error #6", NO_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  expincl.c: internal error #6, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfIncluding(incptr->incl),
		     colOfIncluding(incptr->incl),
		     dnameOfProd(prodref(pid)));
   }	/* if */
}/* incl_target_assign() */

static
#ifdef __STDC__
void
expand_including(IncNode incptr)
#else
void
expand_including(incptr)
   IncNode incptr;
#endif
/* expand INCLUDING construct by generating assignments			 */
{
   SEQAttribution tmp;
   Attribution attrib;

   trans_assigns = 0;
   source_assigns = 0;
   /* generate assignments */
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp, attrib)
   {
      if (prodflag(prodidOfAttribution(attrib)) & start_prod)
      {
	protout(ProtocolFile, "Computations in source context:\n");
	/* an attribute in this context was included */
	 incl_src_assign(incptr, attrib);
      }	/* if */
      if (prodflag(prodidOfAttribution(attrib)) & trans_prod)
      {
	 /* transport context */
	protout(ProtocolFile, "Computations in transport context:\n");
	incl_trns_assign(incptr, attrib);
      }	/* if */
      if (prodflag(prodidOfAttribution(attrib)) & target_prod)
      {
	protout(ProtocolFile, "Access in target context:\n");
	 /* context containing INCLUDING construct */
	 incl_target_assign(incptr, attrib);
      }	/* if */
      prodflag(prodidOfAttribution(attrib)) = no_pflag;
   }	/* foreachinSEQAttribution */

}/* expand_including() */


/* * GLOBAL FUNCTIONS */


#ifdef __STDC__
void
find_includings(void)
#else
void
find_includings()
#endif
/* search all INCLUDING constructs and build a list for them		 */
{
   SEQAttribution tmp1;
   Attribution attrib;
   SEQAttrrule tmp2;
   Attrrule rule;
   int counter;

   newattrname = (char *) middle_tempMalloc(__FILE__, __LINE__, strlen(INCL_ATTR) + 8);
   if (!newattrname)
      deadly("expand: out of memory\n");
   inclcount = 0;
   includings = (IncNode) NULL;
   counter = 0;
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp1, attrib)
   {
      foreachinSEQAttrrule(attrrulesOfAttribution(attrib), tmp2, rule)
      {
	 if (typeof(rule) == KCall)
	 {
	    counter += incl_in_call(
				    AttrruleToCall(rule),
				    prodidOfAttribution(attrib),
				    FALSE);
	 }	/* if */
      }	/* foreachinSEQAttrrule */
   }	/* foreachinSEQAttribution */

/*    switch (counter)
   {
   case 0:
      (void) fprintf(ProtocolFile, "\nNo INCLUDINGs found\n");
      break;
   case 1:
      (void) fprintf(ProtocolFile, "\nOne INCLUDING found\n");
      break;
   default:
      (void) fprintf(ProtocolFile,
		     "\n%d INCLUDINGs found\n", counter);
   }	*/

}/* find_includings() */

#ifdef __STDC__
void
expand_includings(void)
#else
void
expand_includings()
#endif
/* expand all INCLUDING constructs					 */
{
   IncNode incptr;

   if (!inclcount)
      return;

   newattrs = 0;
   newassigns = 0;

   if (EXP_PROT)
     { fprintf(ProtocolFile, "Expanding INCLUDINGs\n");
       fprintf(ProtocolFile, "---------------------\n");
     }
   /* examine all including constructs in the list */
   for (incptr = includings; incptr; incptr = incptr->next)
   {
      clear_psflags();

      if (EXP_PROT)
	 show_including(incptr);

      mark_including(incptr);
      expand_including(incptr);
   }	/* for */

   includings = (IncNode) NULL;


   
   fprintf(ProtocolFile, "\nINCLUDING Expansion Summary\n");
   fprintf(ProtocolFile, "============================\n");

   fprintf(ProtocolFile, "   Number of different INCLUDINGs:   %d\n",
	   inclcount);
   
   fprintf(ProtocolFile, "   Number of new attributes:         %d\n",
	   newattrs);

   fprintf(ProtocolFile, "   Number of transport computations: %d\n",
	   newassigns);

}/* expand_includings() */

/***********************\
* end of expincl.c	*
\***********************/

/* HaDeS */





