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
/* $Id: option.c,v 4.9 1998/04/28 14:28:56 ludi Exp $ */
static char rcs_id[] = "$Id: option.c,v 4.9 1998/04/28 14:28:56 ludi Exp $";

/****************************************************************
*                                                               *
*       Module  : option.c                                      *
*       Author  : Jiyang Liu                                    *
*                                                               *
*       Contains routines for reading and processing order      *
*       options and esp. the arrange options			*
*                                                               *
****************************************************************/

#include "option_enums.h"
#include "option_types.h"
#include "opt_input.h"

#include "printerr.h"
#include "do_order.h"
#include "reftab.h"
#include "depmod.h"
#include "allocate.h"

#include "option.h"
#ifdef GORTO
#include "../../gorto/Misc.h"
#endif

/* switches for processing: */
/* default for switches set by lcl options
   PARSE_TIME is unused, TREE_TOP_DOWN is not implemented: */

bool  AUTOMATICALLY = FALSE,
      ARRANGE = FALSE,
      PART_EARLY = FALSE,
      PART_LATE = TRUE,
      TREE_BOTTOM_UP = FALSE,       /* attr.eval during tree construction */  
      TREE_COMPLETE = FALSE,        /* construct complete tree */
      TREE_TOP_DOWN = FALSE,        /* obsolete */
      PARSE_TIME = FALSE;           /* obsolete */

#ifndef GORTO
/* switches for info output: */
bool
      PRINT_SYMBOL_DIRECT = FALSE,
      PRINT_SYMBOL_TRANSITIV = FALSE,
      PRINT_SYMBOL_INDUCED = FALSE,
      PRINT_RULE_DIRECT = FALSE,
      PRINT_RULE_TRANSITIV = FALSE,
      PRINT_RULE_INDUCED = FALSE,
      PRINT_PARTITION = FALSE,
      PRINT_RULE_PARTITIONED = FALSE,
      PRINT_VISITSEQUENCE = FALSE;
#endif 

/* The PrintList is filled with the did of the graphs in each state
   to be printed.
   PrintList is exported to ordout.
*/
SEQint PrintList;

/* global variables: */
#ifdef GORTO
static FILE *order_optionfile; 
#endif
static OptCollect order_opts;


/*********************************************
* enter_depSymbol                            *
*********************************************/

void enter_depSymbol (Ptr) ArrangeHelp Ptr;
{
   int fromAttrPos, toAttrPos;

   if (Ptr != NULL)
   {
      fromAttrPos = ref_tab[Ptr->fromAttrId].entry.attr.pos;
      toAttrPos = ref_tab[Ptr->toAttrId].entry.attr.pos;

      /* fromAttr is required to be evaluated BEFORE toAttr, therefor an edge
       * from toAttr to fromAttr should be introduced in symbol graph.
       * In case of gorto an Arrange node is prepared.
       */
#ifndef GORTO

      if (DSDependson (Ptr->fromSymbId, toAttrPos, fromAttrPos))
      {
	 char errmsgbuff[ERR_BUFF_LEN];
	 err_setpos(ref_tab[Ptr->toAttrId].entry.attr.attr_def->row,
		    ref_tab[Ptr->toAttrId].entry.attr.attr_def->col);
	 sprintf(errmsgbuff, "Arrange: '%s' already depends on '%s'",
		 ref_tab[Ptr->toAttrId].entry.attr.attr_def->name,
		 ref_tab[Ptr->fromAttrId].entry.attr.attr_def->name);
	 err_print_warning(errmsgbuff);
	 (void) fprintf(ProtocolFile, "*** WARNING *** %s\n", errmsgbuff);

      } else if (DSDependson (Ptr->fromSymbId, fromAttrPos, toAttrPos))
      {
	 char errmsgbuff[ERR_BUFF_LEN];
	 err_setpos(ref_tab[Ptr->toAttrId].entry.attr.attr_def->row,
		    ref_tab[Ptr->toAttrId].entry.attr.attr_def->col);
	 sprintf(errmsgbuff, "Arrange: Dependency of '%s' on '%s'; it would cause a cycle.",
		 ref_tab[Ptr->toAttrId].entry.attr.attr_def->name,
		 ref_tab[Ptr->fromAttrId].entry.attr.attr_def->name);
	 err_print_warning(errmsgbuff);
	 (void) fprintf(ProtocolFile, "*** WARNING *** %s\n", errmsgbuff);

      } else
          DSSetDepend (Ptr->fromSymbId, toAttrPos, fromAttrPos);
#else
      MakeArrangeNode(Ptr->fromSymbId,
		      (SLNODE *) NULL, (SLNODE *) NULL,
		      Ptr->fromAttrId,
		      Ptr->toAttrId, False);
#endif

   }
#ifndef GORTO
   (void) fprintf(ProtocolFile, "\n");
#endif
   return;
}/* enter_depSymbol() */

/*********************************************
* return_symbNo                              *
*********************************************/
static
bool return_symbNo(pid, sid, ord, slnptr)
   int pid, sid, ord;
   SLNODE **slnptr;
{
   SLNODE *p;

   p = ref_tab[pid].entry.prod.hdright;

   while (p != NULL)

      if (p->sid == sid)
      {	/* if the wanted symbol is found */
	 if (ord == 1)
	 {
	    *slnptr = p;
	    return (TRUE);
	 } else
	 {
	    ord -= 1;
	    p = p->right;
	 }
      } else	/* if the wanted symbol is not yet found */
	 p = p->right;

   return (FALSE);

}/* return_symbNo() */


/*********************************************
* enter_depRule                              *
*********************************************/
static
void enter_depRule (Ptr) ArrangeHelp Ptr;
{
   bool ok = TRUE;
   SLNODE *fromSymbPtr, *toSymbPtr;
   int toAttrPos, fromAttrPos;

   if (Ptr != NULL)
   {
      if (return_symbNo(Ptr->prodId,
			Ptr->fromSymbId,
			Ptr->fromOrd,
			&fromSymbPtr))
	 fromAttrPos = ref_tab[Ptr->fromAttrId].entry.attr.pos;
      else
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 err_setpos(ref_tab[Ptr->fromAttrId].entry.attr.attr_def->row,
		    ref_tab[Ptr->fromAttrId].entry.attr.attr_def->col);
	 sprintf(errmsgbuff, "Arrange: Wrong ORD-Value for Symbol '%s'",
		 ref_tab[Ptr->fromAttrId].entry.attr.attr_def->name);
	 err_print_warning(errmsgbuff);
	 (void) fprintf(ProtocolFile, "*** WARNING *** WRONG ORD-VALUE FOR THE FIRST SYMBOL\n");
	 ok = FALSE;
      }

      if (return_symbNo(Ptr->prodId,
			Ptr->toSymbId,
			Ptr->toOrd,
			&toSymbPtr))
	 toAttrPos = ref_tab[Ptr->toAttrId].entry.attr.pos;
      else
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 err_setpos(ref_tab[Ptr->toAttrId].entry.attr.attr_def->row,
		    ref_tab[Ptr->toAttrId].entry.attr.attr_def->col);
	 sprintf(errmsgbuff, "Arrange: Wrong ORD-Value for Symbol '%s'",
		 ref_tab[Ptr->toAttrId].entry.attr.attr_def->name);
	 err_print_warning(errmsgbuff);

	 (void) fprintf(ProtocolFile, "*** WARNING *** WRONG ORD-VALUE FOR THE SECOND SYMBOL\n");
	 ok = FALSE;
      }

      if (ok)
      {
#ifndef GORTO
	 if (DPDependson (Ptr->prodId,
			  toSymbPtr, toAttrPos,
			  fromSymbPtr, fromAttrPos))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(ref_tab[Ptr->toAttrId].entry.attr.attr_def->row,
		       ref_tab[Ptr->toAttrId].entry.attr.attr_def->col);
	    sprintf(errmsgbuff, "Arrange: '%s' already depends on '%s'",
		    ref_tab[Ptr->toAttrId].entry.attr.attr_def->name,
		    ref_tab[Ptr->fromAttrId].entry.attr.attr_def->name);
	    err_print_warning(errmsgbuff);
	    (void) fprintf(ProtocolFile, "*** WARNING *** DEPENDENCY ALREADY EXISTS\n");
	 } else if (DPDependson (Ptr->prodId,
				 fromSymbPtr, fromAttrPos,
				 toSymbPtr, toAttrPos))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(ref_tab[Ptr->toAttrId].entry.attr.attr_def->row,
		       ref_tab[Ptr->toAttrId].entry.attr.attr_def->col);
	    sprintf(errmsgbuff, "Arrange: Dependency of '%s' on '%s'; it would cause a cycle.",
		    ref_tab[Ptr->toAttrId].entry.attr.attr_def->name,
		    ref_tab[Ptr->fromAttrId].entry.attr.attr_def->name);
	    err_print_warning(errmsgbuff);

	    (void) fprintf(ProtocolFile, "*** WARNING *** DEPENDENCY IS NOT INTRODUCED, IT WOULD CAUSE A CYCLE\n");
	 } else
	    DPSetDepend (Ptr->prodId,
			 toSymbPtr, toAttrPos,
			 fromSymbPtr, fromAttrPos,
			 0, 0);
#else
	 MakeArrangeNode(Ptr->prodId, fromSymbPtr, toSymbPtr,
			 Ptr->fromAttrId,
			 Ptr->toAttrId, False);
#endif
      }	/* end ok */
   }	/* end if NULL */
#ifndef GORTO
   (void) fprintf(ProtocolFile, "\n");
#endif
}/* enter_depRule() */


/*********************************************
* read_orderOption                           *
*********************************************/

#ifndef GORTO
void read_orderOption()
#else
void read_orderOption (fname) char *fname;
#endif
{
   OrdList ordp;

   order_opts =
   (OptCollect) Allocate
       (__FILE__,__LINE__,sizeof(struct _optcollect));

   order_opts->ord_opts = (OrdList) NULL;
#ifndef GORTO
   OptionInput(order_opts, OrdOptFile);
   fclose(OrdOptFile);
#else
   if (!(order_optionfile = fopen(fname, "r")))
   {
      err_setpos(0, 0);
      err_print_error("Cannot open order_option file");
      (void) fprintf(stderr, "*** ERROR *** can't open order_option file\n");
   }
    /* if */ 
   else
   {
      OptionInput(order_opts, order_optionfile);
      fclose(order_optionfile);
   }    /* else */

#endif

   for (ordp = order_opts->ord_opts; ordp; ordp = ordp->next)
   {
      switch (ordp->entry->flag)
      {
      case part_early:
	 PART_EARLY = TRUE;
	 PART_LATE = FALSE;
	 break;
      case part_late:
	 PART_LATE = TRUE;
	 PART_EARLY = FALSE;
	 break;
      case top_early:	/* currently not in use */
	 break;
      case top_late:	/* currently not in use */
	 break;
#ifndef GORTO
      case direct_symb:
	 PRINT_SYMBOL_DIRECT = TRUE;
	 break;
      case trans_symb:
	 PRINT_SYMBOL_TRANSITIV = TRUE;
	 break;
      case ind_symb:
	 PRINT_SYMBOL_INDUCED = TRUE;
	 break;
      case direct_rule:
	 PRINT_RULE_DIRECT = TRUE;
	 break;
      case trans_rule:
	 PRINT_RULE_TRANSITIV = TRUE;
	 break;
      case ind_rule:
	 PRINT_RULE_INDUCED = TRUE;
	 break;
      case part_rule:
	 PRINT_RULE_PARTITIONED = TRUE;
	 break;
      case partition:
	 PRINT_PARTITION = TRUE;
	 break;
      case visit_seq:
	 PRINT_VISITSEQUENCE = TRUE;
	 break;
#endif
      case tree_compl:
	/* option should be stated by maptool only,
	   if implicit chain productions are used
	*/
	 TREE_COMPLETE = TRUE;
	 break;
      case tree_up:
	/* option is ignored; 
	   BOTTOMUP is requested by computations only
	*/
	 break;
      case tree_down:
	 /* not implemented */
	 break;
      case arr_auto:
	 AUTOMATICALLY = TRUE;
	 break;
      case arr_fast:
	 AUTOMATICALLY = FALSE;
	 break;
      case for_symb:
	 ARRANGE = TRUE;
	 break;
      case in_rule:
	 ARRANGE = TRUE;
	 break;
      case ordopt_error:
      default:
	 break;
      }	/* switch */
   }	/* for */

}/* read_orderOption() */

/*********************************************
* lookupSymbByName                           *
*********************************************/

Symb lookupSymbByName (name) String name;
{
   Def def;
   SEQDef sdef;
   Symb symb;

   foreachinSEQDef(ISexp->defseq, sdef, def)
   {
      if ((typeof(def) == KSymb) && (!strcmp(def.VSymb->dname, name)))
      {
	 symb = def.VSymb;
	 return (symb);
      }
   }
   return (NULL);
}/* lookupSymbByName() */


/*********************************************
* lookupProdByName                           *
*********************************************/

Prod lookupProdByName (name) String name;
{
   Def def;
   SEQDef sdef;
   Prod prod;

   foreachinSEQDef(ISexp->defseq, sdef, def)
   {
      if ((typeof(def) == KProd) && (strcmp(def.VProd->dname, name) == 0))
      {
	 prod = def.VProd;
	 return (prod);
      }
   }
   return (NULL);
}/* lookupProdByName() */

#define KArrangeHelp 2
#define NArrangeHelp ((ArrangeHelp)calloc(1, sizeof(struct RArrangeHelp)))

/*********************************************
* MkArrangeHelp                              *
*********************************************/
static
ArrangeHelp MkArrangeHelp
  (pprodId, pfromSymbId, pfromOrd, ptoSymbId, ptoOrd, pfromAttrId, ptoAttrId)
   int pprodId;
   int pfromSymbId;
   int pfromOrd;
   int ptoSymbId;
   int ptoOrd;
   int pfromAttrId;
   int ptoAttrId;
{
   ArrangeHelp n;

   n = NArrangeHelp;
   n->prodId = pprodId;
   n->fromSymbId = pfromSymbId;
   n->fromOrd = pfromOrd;
   n->toSymbId = ptoSymbId;
   n->toOrd = ptoOrd;
   n->fromAttrId = pfromAttrId;
   n->toAttrId = ptoAttrId;
   return (n);
}/* MkArrangeHelp() */


/*********************************************
* getIdArrangeSymbol                         *
*********************************************/

ArrangeHelp getIdArrangeSymbol (a, b, c) String a, b, c;
{
   Attrdef adef;
   SEQAttrdef sadef;
   ArrangeHelp result;

   bool ok = TRUE;
   Symb symb = NULL;
   int first = 0, second = 0;

#ifndef GORTO
   (void) fprintf(ProtocolFile, "ARRANGE: FOR SYMBOL %s EVAL %s BEFORE %s\n", a, b, c);
#endif

   symb = lookupSymbByName(a);

   if (symb == NULL)
   {
      char errmsgbuff[ERR_BUFF_LEN];

      sprintf(errmsgbuff, "Arrange: '%s' is not a Symbol.", a);
      err_setpos(0, 0);
      err_print_warning(errmsgbuff);
      (void) fprintf(ProtocolFile, "*** WARNING *** NOT A SYMBOL\n");
      ok = FALSE;
   } else
   {
      foreachinSEQAttrdef(symb->attrs, sadef, adef)
      {
	 if (strcmp(b, adef->name) == 0)
	    first = adef->did;

	 if (strcmp(c, adef->name) == 0)
	    second = adef->did;

	 if (first * second != 0)
	    break;
      }

      if (first * second == 0)
      {
	 err_setpos(adef->row, adef->col);
	 if (first == 0)
	 {
	    err_print_warning("Arrange: Not an attribute of the symbol");
	    (void) fprintf(ProtocolFile, "*** WARNING *** NOT AN ATTRIBUTE OF THE SYMBOL\n");
	 }
	 if (second == 0)
	 {
	    err_print_warning("Arrange: Not an attribute of the symbol");
	    (void) fprintf(ProtocolFile, "*** WARNING *** NOT AN ATTRIBUTE OF THE SYMBOL\n");
	 }
	 ok = FALSE;
      }
   }
   if (ok)
      result = MkArrangeHelp(0, symb->did, 0, 0, 0, first, second);
   else
      result = NULL;
   return (result);
}/* getIdArrangeSymbol() */


/*********************************************
* getIdArrangeRule                           *
*********************************************/
static
ArrangeHelp getIdArrangeRule
  (prodName, fromSymbName, fromOrd, toSymbName, toOrd, fromAttrName, toAttrName)
   String prodName, fromSymbName, toSymbName, fromAttrName, toAttrName;
   int fromOrd, toOrd;
{
   int ruleid = 0, symb1id = 0, symb2id = 0, adef1id = 0, adef2id = 0;

   Def def;
   SEQDef sdef;
   Symb symb;
   SEQAttrdef sadef;
   Attrdef adef;
   bool ok = TRUE;

   ArrangeHelp result;

#ifndef GORTO
   (void) fprintf(ProtocolFile, "ARRANGE: IN RULE %s EVAL %s[%d].%s BEFORE %s[%d].%s\n",
		  prodName, fromSymbName, fromOrd, fromAttrName,
		  toSymbName, toOrd, toAttrName);
#endif


   foreachinSEQDef(ISexp->defseq, sdef, def)
   {
      if ((typeof(def) == KProd) &&
	  (strcmp(def.VProd->dname, prodName) == 0))
      {
	 ruleid = def.VProd->did;
	 break;
      }
   }

   if (ruleid == 0)
   {
      char errmsgbuff[ERR_BUFF_LEN];

      err_setpos(0, 0);
      sprintf(errmsgbuff, "Arrange: Rule '%s' does not exist.", prodName);
      err_print_warning(errmsgbuff);
      (void) fprintf(ProtocolFile, "*** WARNING *** RULE '%s' DOES NOT EXIST\n", prodName);
      ok = FALSE;
   }
   symb = lookupSymbByName(fromSymbName);

   if (symb == NULL)
   {
      char errmsgbuff[ERR_BUFF_LEN];

      err_setpos(0, 0);
      sprintf(errmsgbuff, "Arrange: Symbol %s does not exist in Rule %s",
	      fromSymbName, prodName);
      err_print_warning(errmsgbuff);

      (void) fprintf(ProtocolFile, "*** WARNING *** FIRST SYMBOL DOES NOT EXIST\n");
      ok = FALSE;
   } else
   {
      symb1id = symb->did;

      foreachinSEQAttrdef(symb->attrs, sadef, adef)
      {
	 if (strcmp(adef->name, fromAttrName) == 0)
	 {
	    adef1id = adef->did;
	    break;
	 }
      }
      if (adef1id == 0)
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 err_setpos(0, 0);
	 sprintf(errmsgbuff, "Arrange: '%s' is not an attribute of '%s'",
		 fromAttrName, fromSymbName);
	 err_print_warning(errmsgbuff);
	 (void) fprintf(ProtocolFile, "*** WARNING *** IS NOT AN ATTRIBUT OF THE FIRST SYMBOL\n");
	 ok = FALSE;
      }
   }

   symb = lookupSymbByName(toSymbName);
   if (symb == NULL)
   {
      char errmsgbuff[ERR_BUFF_LEN];

      err_setpos(0, 0);
      sprintf(errmsgbuff, "Arrange: Symbol %s does not exist in Rule %s",
	      toSymbName, prodName);
      err_print_warning(errmsgbuff);

      (void) fprintf(ProtocolFile, "*** WARNING *** SECOND SYMBOL DOES NOT EXIST\n");
      ok = FALSE;
   } else
   {
      symb2id = symb->did;

      foreachinSEQAttrdef(symb->attrs, sadef, adef)
      {
	 if (strcmp(adef->name, toAttrName) == 0)
	 {
	    adef2id = adef->did;
	    break;
	 }
      }
      if (adef2id == 0)
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 err_setpos(0, 0);
	 sprintf(errmsgbuff, "Arrange: '%s' is not an attribute of '%s'",
		 toAttrName, toSymbName);
	 err_print_warning(errmsgbuff);

	 (void) fprintf(ProtocolFile, "*** WARNING *** IS NOT AN ATTRIBUT OF THE SECOND SYMBOL\n");
	 ok = FALSE;
      }
   }

   if (ok)
      result = MkArrangeHelp(ruleid,
			     symb1id,
			     fromOrd,	/* Ord of from */
			     symb2id,
			     toOrd,	/* Ord of to */
			     adef1id,
			     adef2id);
   else
      result = NULL;

   return (result);
}/* getIdArrangeRule() */


/*********************************************
* set_arrangeOption                          *
*********************************************/

void set_arrangeOption ()
{
   OrdList ordp;

   for (ordp = order_opts->ord_opts; ordp; ordp = ordp->next)
   {
      switch (ordp->entry->flag)
      {
      case for_symb:
	 enter_depSymbol(getIdArrangeSymbol(
					    ordp->entry->names[0],
					    ordp->entry->names[1],
					    ordp->entry->names[2]));
	 break;

      case in_rule:
	 enter_depRule(getIdArrangeRule(
					ordp->entry->names[0],
					ordp->entry->names[1],
					ordp->entry->symbindex1,
					ordp->entry->names[3],
					ordp->entry->symbindex2,
					ordp->entry->names[2],
					ordp->entry->names[4]));
	 break;
      default:
	 break;
      }	/* switch */
   }	/* for */
}/* set_arrangeOption() */

#ifndef GORTO
/********************************************\
*    void read_printOption                   *
\********************************************/

void read_printOption (class) int class;
/* extract the lcl options that require to print
   graphs in the state given by class
*/
{
   Prod prod;
   Symb symb;
   OrdList ordp;
   int x, count;

   initializeSEQint (PrintList);
   
   for (ordp = order_opts->ord_opts; ordp; ordp = ordp->next)
   {
      if ((int) (ordp->entry->flag) == class)
      {
	 count = ordp->entry->namecount;
	 for (x = 0; x < count; x++)
	 {
	    if ((class == (int) (direct_symb))
		|| (class == (int) trans_symb)
		|| (class == (int) ind_symb)
		|| (class == (int) partition))
	    {
	       symb = lookupSymbByName(ordp->entry->names[x]);
	       if (symb && !(inSEQint (PrintList, symb->did)))
	          appendrearSEQint (PrintList, symb->did);
	    }
	     /* if */ 
	    else
	    {
	       prod = lookupProdByName(ordp->entry->names[x]);
	       if (prod && !(inSEQint (PrintList, prod->did)))
	          appendrearSEQint (PrintList, prod->did);
	    }	/* else */
	 }	/* for */
	 if (emptySEQint (PrintList))
	    appendfrontSEQint (PrintList, PRINT_ALL);
      }	/* if */
   }	/* for */
}/* read_printOption() */
#endif
