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
/* $Id: expref.c,v 4.2 1998/04/28 14:26:13 ludi Exp $ */
static char rcs_id[] = "$Id: expref.c,v 4.2 1998/04/28 14:26:13 ludi Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expref.c					*
*	File:		expref.c					*
*	Contents:	function to handle the reference table		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	13 Dec 1990					*
*	Last change:	25 Sep 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "LIGAMacros.h"

#include "middle_mem.h"
#include "expconst.h"
#include "exp_types.h"
#include "expand.h"
#include "expref.h"
#include "expidl.h"

/* * GLOBAL VARIABLES */

/* reference table for definitions	 */
struct RefEntry *exp_ref_tab;

/* number of defined symbols and rules	 */
int DefSymbNum, DefRuleNum;

/* did of the root symbol		 */
int root_sid;

/* maximal did of all definitions	 */
int max_did;

/* * LOCAL VARIABLES */

/* * LOCAL FUNCTIONS */

static
#ifdef __STDC__
void
ins_ldown(SNode sptr)
#else
void
ins_ldown(sptr)
   SNode sptr;
#endif
/* append a symbol node at the end of the lhs symbol list		 */
{
   SNode searchp;

   searchp = symbldown(sptr->symbdid);
   if (searchp == NULL)
   {
      /* the same-name symbol list was empty */
      symbldown(sptr->symbdid) = sptr;
   }
   /* if */
   else
   {
      /* search for the end of the list */
      while (searchp->down)
	 searchp = searchp->down;
      /* append symbol node to the list */
      searchp->down = sptr;
   }	/* else */
}/* ins_ldown() */

static
#ifdef __STDC__
void
ins_rdown(SNode sptr)
#else
void
ins_rdown(sptr)
   SNode sptr;
#endif
/* append a symbol node at the end of the rhs symbol list		 */
{
   SNode searchp;

   searchp = symbrdown(sptr->symbdid);
   if (searchp == NULL)
   {
      /* the same-name symbol list was empty */
      symbrdown(sptr->symbdid) = sptr;
   }
   /* if */
   else
   {
      /* search for the end of the list */
      while (searchp->down)
	 searchp = searchp->down;
      /* append symbol node to the list */
      searchp->down = sptr;
   }	/* else */
}/* ins_rdown() */

static
#ifdef __STDC__
void
sl_cons(int pid)
#else
void
sl_cons(pid)
   int pid;
#endif
/* construct the linked symbol list for production with number pid	 */
/* and build the links through those symbol occurrences with the same	 */
/* symbol name (did)							 */
{
   SNode sptr;
   SNode cursn;
   SEQEntity tmp;
   Entity entity;

   /* initialize symbol node entry for the left hand side */
   sptr = (SNode) middle_tempMalloc(__FILE__, __LINE__, sizeof(struct SNode));
   if (!sptr)
      deadly("expand: out of memory\n");
   sptr->prodid = pid;
   sptr->symbdid = lhsOfProd(prodref(pid));
   sptr->right = NULL;
   sptr->down = NULL;

   /* put symbol node as first entry into symbol list of this production */
   prodright(pid) = sptr;

   /* put symbol node into list of lhs occurrences of this symbol */
   ins_ldown(sptr);

   /* initialize pointer to current symbol node */
   cursn = sptr;

   /* process symbols from the right hand side of this production */
   foreachinSEQEntity(rhsOfProd(prodref(pid)), tmp, entity)
   {
      switch (typeof(entity))
      {
      case KOpt:
      case KStar:
      case KPlus:
      case KDelim:
      case KDelopt:
      case KLiteral:
	 break;

      case KSymbol:
	 /* initialize symbol node entry */
	 sptr = (SNode) middle_tempMalloc(__FILE__, __LINE__, sizeof(struct SNode));
	 if (!sptr)
	    deadly("expand: out of memory\n");
	 sptr->prodid = pid;
	 sptr->symbdid = didOfSymbol(EntityToSymbol(entity));
	 sptr->right = NULL;
	 sptr->down = NULL;

	 /* append entry to list */
	 cursn->right = sptr;
	 cursn = sptr;
	 ins_rdown(sptr);
	 break;

      default:
	 (void) fprintf(ProtocolFile,
			"*** NOTE:  wrong entity in sl_cons()\n");
	 break;
      }	/* switch */
   }	/* foreachinSEQEntity */
}/* sl_cons() */

#ifdef DEBUG
static
#ifdef __STDC__
void
show_attainable_graph(void)
#else
void
show_attainable_graph()
#endif
/* show the attainable graph of the grammar				 */
{
   SEQDef tmp;
   Def def;
   SNode sn;

   (void) fprintf(ProtocolFile, "ATTAINABLE GRAPH:\n");
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, def)
   {
      switch (typeof(def))
      {
      case KSymb:
	 (void) fprintf(ProtocolFile,
			"\tSymbol %s:\n",
			dnameOfSymb(symbref(didOfDef(def))));
	 (void) fprintf(ProtocolFile,
			"\t\tappears on lhs of following productions:  ");
	 for (sn = symbldown(didOfDef(def)); sn; sn = sn->down)
	 {
	    (void) fprintf(ProtocolFile,
			   "%s ",
			   dnameOfProd(prodref(sn->prodid)));
	 }	/* for */
	 (void) fprintf(ProtocolFile,
			"\n\t\tappears on rhs of following productions:  ");
	 for (sn = symbrdown(didOfDef(def)); sn; sn = sn->down)
	 {
	    (void) fprintf(ProtocolFile,
			   "%s ",
			   dnameOfProd(prodref(sn->prodid)));
	 }	/* for */
	 (void) fprintf(ProtocolFile, "\n");
	 break;
      case KProd:
	 (void) fprintf(ProtocolFile,
			"\tRule %s:\n",
			dnameOfProd(prodref(didOfDef(def))));
	 (void) fprintf(ProtocolFile,
			"\t\t%s ::=",
			dnameOfSymb(symbref(
				       prodright(didOfDef(def))->symbdid)));
	 for (sn = prodright(didOfDef(def))->right;
	      sn; sn = sn->right)
	 {
	    (void) fprintf(ProtocolFile,
			   " %s",
			   dnameOfSymb(symbref(sn->symbdid)));
	 }	/* for */
	 (void) fprintf(ProtocolFile, "\n");
	 break;
      }	/* switch */
   }	/* foreachinSEQDef */
}/* show_attainable_graph() */
#endif

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
void
expand_init_ref_tab(void)
#else
void
expand_init_ref_tab()
#endif
/* initialize the reference table from idl data structure		 */
{
   int did;
   SEQDef tmp1;
   Def def;
   SEQAttribution tmp2;
   Attribution attrib;
   SEQAttrdef tmp3;
   Attrdef ad;

   /* determine max_did */
   max_did = 0;
   did = 0;
   DefSymbNum = 0;
   DefRuleNum = 0;

   /* enter all symbols */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (didOfDef(def) > max_did)
      {
	 max_did = didOfDef(def);
      }	/* if */
      if (typeof(def) == KSymb)
      {
	 did = didOfSymb(DefToSymb(def));
	 foreachinSEQAttrdef(attrsOfSymb(DefToSymb(def)),
			     tmp3, ad)
	 {
	    if (didOfAttrdef(ad) > max_did)
	    {
	       max_did = didOfAttrdef(ad);
	    }	/* if */
	 }	/* foreachinSEQAttrdef */
      }	/* if */
   }	/* foreachinSEQDef */


   exp_ref_tab = (struct RefEntry *)
      middle_tempMalloc(__FILE__, __LINE__, (max_did + 1) * sizeof(struct RefEntry));

   for (did = 0; did <= max_did; did++)
      exp_ref_tab[did].entry_tag = empty_entry;

   did = 0;
   DefSymbNum = 0;
   DefRuleNum = 0;

   /* enter all symbols */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (typeof(def) == KSymb)
      {
	 did = didOfSymb(DefToSymb(def));
	 DefSymbNum++;
	 if (exp_ref_tab[did].entry_tag != empty_entry)
	 {
	    deadly("illegal entry in reference table");
	 }	/* if */
	 exp_ref_tab[did].entry_tag = symbol_entry;
	 symbref(did) = DefToSymb(def);
	 symbldown(did) = NULL;
	 symbrdown(did) = NULL;
      }	/* if */
   }	/* foreachinSEQDef */

   /* enter all productions */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (typeof(def) == KProd)
      {
	 did = didOfProd(DefToProd(def));
	 DefRuleNum++;
	 if (exp_ref_tab[did].entry_tag != empty_entry)
	 {
	    deadly("illegal entry in reference table");
	 }	/* if */
	 exp_ref_tab[did].entry_tag = prod_entry;
	 prodref(did) = DefToProd(def);
	 prodattrib(did) = NULL;
	 prodright(did) = NULL;
	 prodtrns(did) = NULL;
	 prodflag(did) = no_pflag;
	 sl_cons(did);
      }	/* if */
   }	/* foreachinSEQDef */

   /* search attributions for all productions */
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp2, attrib)
   {
      did = prodidOfAttribution(attrib);
      if (prodattrib(did) != (Attribution) NULL)
      {
	 print_err(
		   rowOfProd(prodref(did)),
		   colOfProd(prodref(did)),
		   "multiple attributions for production",
		   NO_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
			"multiple attributions for production %s\n",
			dnameOfProd(prodref(did)));
      }	/* if */
      prodattrib(did) = attrib;
   }	/* foreachinSEQAttribution */

   /* check all production entries */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (typeof(def) == KProd && !prodattrib(didOfDef(def)))
      {
	 print_note(
		    rowOfProd(prodref(did)),
		    colOfProd(prodref(did)),
		    "no attribution for production");
	 (void) fprintf(ProtocolFile, "\n*** NOTE  ");
	 (void) fprintf(ProtocolFile,
			"no attribution for production %s\n",
			dnameOfProd(prodref(did)));
      }	/* if */
   }	/* foreachinSEQDef */

#ifdef DEBUG
   show_attainable_graph();
#endif
}/* expand_init_ref_tab() */

void
expand_finl_ref_tab()
{
}


#ifdef __STDC__
void
find_root(void)
#else
void
find_root()
#endif
/* search the root symbol of the grammar				 */
{
   int root_count;
   SEQDef tmp;
   Def def;
   int did;
   Symb firstsymb;

/*   (void) fprintf(ProtocolFile, "\nroot symbol of the grammar:\n");
*/
   root_count = 0;
   firstsymb = (Symb) NULL;
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, def)
   {
      if (typeof(def) == KSymb)
      {
	 if (!firstsymb)
	    firstsymb = DefToSymb(def);
	 did = didOfSymb(DefToSymb(def));
	 if (exp_ref_tab[did].entry_tag != symbol_entry)
	 {
	    deadly("illegal entry in reference table");
	 }	/* if */
	 /* root symbol must not appear on rhs of productions */
	 if (!symbrdown(did))
	 {
	    root_sid = did;
/*	    (void) fprintf(ProtocolFile, "\t%s\n",
			   dnameOfSymb(symbref(did)));
*/	    root_count++;
	 }	/* if */
      }	/* if */
   }	/* foreachinSEQDef */

   /* check number of candidates for the root symbol */
   if (!root_count)
   {
      /* no root symbols found */
      print_err(0, 0, "no candidates for root symbol found",
		ROOT_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  no candidates for root symbol found\n");
      /* select first symbol as root symbol (arbitrary) */
      root_sid = didOfSymb(firstsymb);
      (void) fprintf(ProtocolFile,
		     "\nchoosing %s as root symbol\n\n",
		     dnameOfSymb(symbref(root_sid)));
   }
   /* if */
   else if (root_count > 1)
   {
      /* to much candidates */
      print_err(0, 0, "ambiguous root symbol", ROOT_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  ambiguous root symbol\n");
      /* last found candidate is selected */
      (void) fprintf(ProtocolFile,
		     "\nchoosing %s as root symbol\n\n",
		     dnameOfSymb(symbref(root_sid)));
   }	/* if */
}/* find_root() */

#ifdef __STDC__
void
clear_psflags(void)
#else
void
clear_psflags()
#endif
/* clear all production and symbol flags				 */
{
   SEQDef tmp;
   Def def;

   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, def)
   {
      if (typeof(def) == KSymb)
      {
	 symbflag(didOfDef(def)) = no_sflag;
	 symbvisited(didOfDef(def)) = FALSE;
	 symbcompletechk(didOfDef(def)) = FALSE;
	 symbprodvisited(didOfDef(def)) = FALSE;
      }
      /* if */
      else if (typeof(def) == KProd)
      {
	 prodflag(didOfDef(def)) = no_pflag;
      }	/* else if */
   }	/* foreachinSEQDef */
}/* clear_psflags() */

/***********************\
* end of expref.c	*
\***********************/

/* HaDeS */
