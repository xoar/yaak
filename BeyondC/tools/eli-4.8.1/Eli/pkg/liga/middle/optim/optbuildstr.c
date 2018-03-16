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
/* $Id: optbuildstr.c,v 4.6 1998/04/28 14:27:42 ludi Exp $ */
static char rcs_id[] = "$Id: optbuildstr.c,v 4.6 1998/04/28 14:27:42 ludi Exp $";

/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optbuildstr.c                */
/* */
/* Contains the routines to build an      */
/* internal data structure for module     */
/* liga.optim                             */
/* */
/************************************************/



/************************************************/
/* includes                   */
/************************************************/


#include <stdio.h>
#include <string.h>

#include "option_enums.h"
#include "option_types.h"

#include "lookup_idl.h"
#include "OPTIM.h"
#include "OPTIMMacros.h"
#include "optglobal.h"
#include "optidl.h"
#include "optfct.h"

#include "printerr.h"
#include "ligaconsts.h"
#include "optbuildstr.h"
#include "list.h"


/************************************************/
/* functions                  */
/************************************************/

void CheckIncluding( /* Including */ );

Eval CheckCallParams( /* Visit_Seq, Eval, SEQExpr */ );
Eval InitEval( /* Visit_Seq, Call */ );

Visit_Seq InitVs( /* Prod */ );

void CompleteSymbInfo( /* Visit_Seq */ );
void BuildVs( /* AttrEval */ );
void GetSymbsAndAttrs( /* AttrEval */ );
void InitOptimStructure( /* no parameter */ );






/************************************************/
/* CheckIncluding              */
/************************************************/

void
CheckIncluding(incl)
   Including incl;
{
   SEQSymbattr X;
   Symbattr symbattr;
   Attrdef attrdef;
   Def def;
   Attributes attr;

   if (exp_incl_option)
   {
      err_setpos(incl->row, incl->col);
      err_print_error("not expanded INCLUDING found");

      fprintf(ProtocolFile, "*** ERROR row: %d, col: %d not expanded INCLUDING found\n",
	      incl->row, incl->col);
      exit(5);
   } else
   {
      foreachinSEQSymbattr(incl->inclattrs, X, symbattr)
      {
	 attrdef = lookup_attrdef(symbattr->attrdef);
	 def = lookup_def(symbattr->symbdef);
	 attr = MkAttribute(attrdef, def.VSymb);
	 attr->gen = NOT_EXPANDED_INCLUDING;
	 if (!InSeqAttrs(optimroot->tree_attrs, attr->attrid))
	 {
	   appendfrontSEQAttributes(optimroot->tree_attrs, attr);
	   if (typeidOfAttrdef(attrdef) != DIDVOID  &&
	       typeidOfAttrdef(attrdef) != DIDVOLI)
	     inclattrcounter += 1;
	 }
       }
   }

}/* end of CheckIncluding */





/************************************************/
/* CheckCallParams              */
/************************************************/

Eval
CheckCallParams(vs, eval, exprseq)
   Visit_Seq vs;
   Eval eval;
   SEQExpr exprseq;
{
   SEQExpr X;
   Expr paramexpr;
   Attracc attracc;
   Attrdef attrdef;
   Def def;
   Attributes paramattr;

   foreachinSEQExpr(exprseq, X, paramexpr)
   {
      switch (typeof(paramexpr))
      {
      case KAttracc:
	 attracc = paramexpr.VAttracc;
	 attrdef = lookup_attrdef(attracc->attrid);
	 def = lookup_def(SymbId(vs, attracc->symbno));
	 paramattr = MkAttribute(attrdef, def.VSymb);
	 paramattr->symbno = attracc->symbno;
	 appendrearSEQAttributes(eval->params, paramattr);
	 if (NewInstance(vs, paramattr))
	    appendrearSEQAttributes(vs->attrs, paramattr);
	 break;
      case KIncluding:
	 (void) CheckIncluding(paramexpr.VIncluding);
	 break;
      case KCall:
	 eval = CheckCallParams(vs, eval, paramexpr.VCall->params);
	 break;
      default:
	 break;
      }	/* end of switch */
   }

   return (eval);

}/* end of CheckCallParams */





/************************************************/
/* InitEval                   */
/************************************************/

Eval
InitEval(vs, call)
   Visit_Seq vs;
   Call call;
{
   Eval neweval;
   SEQExpr exprseq;
   Expr firstexpr;
   Attracc attracc;
   Attrdef attrdef;
   Def def;
   Attributes newattr;

   neweval = NEval;
   initializeSEQAttributes(neweval->params);
   neweval->row = call->row;
   neweval->col = call->col;
   if (strcmp(call->name, ASSIGNFCT) == 0)
   {
      retrievefirstSEQExpr(call->params, firstexpr);
      attracc = firstexpr.VAttracc;
      neweval->attrid = attracc->attrid;
      neweval->symbno = attracc->symbno;
      attrdef = lookup_attrdef(attracc->attrid);
      def = lookup_def(SymbId(vs, attracc->symbno));
      newattr = MkAttribute(attrdef, def.VSymb);
      newattr->symbno = attracc->symbno;
      appendrearSEQAttributes(vs->attrs, newattr);
      exprseq = tailSEQExpr(call->params);
   } else
   {	/* CONDITION found */
      neweval->attrid = neweval->symbno = CONDITION;
      exprseq = call->params;
   }

   neweval = CheckCallParams(vs, neweval, exprseq);

   return (neweval);

}/* end of InitEval */





/************************************************/
/* InitVs                   */
/************************************************/

Visit_Seq
InitVs(prod_def)
   Prod prod_def;
{
   Visit_Seq newvs;
   Symb symb_def;
   Symbols newsymb;
   SEQEntity X;
   Entity thisentity;
   Def def;
   int symbno = 0;

   newvs = NVisit_Seq;
   initializeSEQAction(newvs->actions);
   initializeSEQSymbols(newvs->symbs);
   initializeSEQAttributes(newvs->attrs);
   newvs->prodid = prod_def->did;
   def = lookup_def(prod_def->lhs);
   symb_def = def.VSymb;
   newsymb = optim_MkSymbol(symb_def, symbno++);
   appendrearSEQSymbols(newvs->symbs, newsymb);
   foreachinSEQEntity(prod_def->rhs, X, thisentity)
   {
      if (typeof(thisentity) == KSymbol)
      {
	 def = lookup_def(thisentity.VUnit.VSymbol->did);
	 symb_def = def.VSymb;
	 newsymb = optim_MkSymbol(symb_def, symbno++);
	 appendrearSEQSymbols(newvs->symbs, newsymb);
      }
   }

   return (newvs);

}/* end of InitVs */





/************************************************/
/* CompleteSymbInfo               */
/************************************************/

void
CompleteSymbInfo(vs)
   Visit_Seq vs;
{
   Action lastaction;
   SEQSymbols X;
   Symbols thissymb;
   Def def;
   int parentsymbid, max;

   parentsymbid = ParentId(vs);
   retrievelastSEQAction(vs->actions, lastaction);
   if (typeof(lastaction) == KVisits && lastaction.VVisits->symbno == LEAVE)
   {
      max = lastaction.VVisits->ord;
   } else
   {
      char errmsgbuff[ERR_BUFF_LEN];

      def = lookup_def(vs->prodid);
      err_setpos(def.VProd->row, def.VProd->col);
      sprintf(errmsgbuff, "last action in VS %s is not a LEAVE", def.VProd->dname);
      err_print_error(errmsgbuff);

      fprintf(ProtocolFile, "*** ERROR: last action in VS %s is not a LEAVE \n",
	      def.VProd->dname);
      exit(5);
   }
   foreachinSEQSymbols(vs->symbs, X, thissymb)
   {
      if (thissymb->symbid == parentsymbid)
      {
	 thissymb->parts = max;
      }
   }
   foreachinSEQSymbols(optimroot->symbs, X, thissymb)
   {
      if (thissymb->symbid == parentsymbid)
      {
	 thissymb->parts = max;
      }
   }

}/* end of CompleteSymbInfo */





/************************************************/
/* BuildVs                   */
/************************************************/

void
BuildVs(root)
   AttrEval root;
{
   SEQAttribution X;
   Attribution thisvs;
   Visit_Seq newvs;
   SEQAttrrule Y;
   Attrrule attrrule;
   Eval neweval;
   Visits newvisit;
   Def def;
   Prod prod;
   Visit visit;
   int id;


   foreachinSEQAttribution(root->attrrules, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      prod = def.VProd;
      newvs = InitVs(prod);
      id = SymbId(newvs, 0);
      newvisit = optim_MkVisit(0, 0, id);
      IDLtempAction.VVisits = newvisit;
      appendrearSEQAction(newvs->actions, IDLtempAction);
      foreachinSEQAttrrule(thisvs->attrrules, Y, attrrule)
	 switch (typeof(attrrule))
      {
      case KVisit:
	 visit = attrrule.VVisit;
	 id = SymbId(newvs, visit->symbno);
	 newvisit = optim_MkVisit(visit->symbno, visit->ord, id);
	 IDLtempAction.VVisits = newvisit;
	 appendrearSEQAction(newvs->actions, IDLtempAction);
	 break;
      case KCall:
	 neweval = InitEval(newvs, attrrule.VCall);
	 IDLtempAction.VEval = neweval;
	 appendrearSEQAction(newvs->actions, IDLtempAction);
	 break;
      default:
	 break;
      }	/* end of switch */
      (void) CompleteSymbInfo(newvs);
      appendrearSEQVisit_Seq(optimroot->vi_seq, newvs);
   }

}/* end of BuildVs */


/************************************************/
/* GetSymbsAndAttrs                */
/************************************************/

void
GetSymbsAndAttrs(root)
   AttrEval root;
{
   SEQDef X;
   Def thisdef;
   Symb symbdef;
   Symbols newsymbol;
   SEQAttrdef Y;
   Attrdef attrdef;
   Attributes newattr;

   foreachinSEQDef(root->defseq, X, thisdef)
   {
      if (typeof(thisdef) == KSymb)
      {
	 symbdef = thisdef.VSymb;
	 newsymbol = optim_MkSymbol(symbdef, -1);
	 appendrearSEQSymbols(optimroot->symbs, newsymbol);
	 foreachinSEQAttrdef(symbdef->attrs, Y, attrdef)
	 {
	    /* must be inserted if counting attr should not be analyzed if
	     * (attrdef->typeid == COUNTING_ATTR) { attrdef->store =
	     * STORE_COUNTING_ATTR; } else { newattr = MkAttribute(attrdef,
	     * symbdef); appendrearSEQAttributes(optimroot->attrs, newattr);
	     * } */
	    newattr = MkAttribute(attrdef, symbdef);
	    appendrearSEQAttributes(optimroot->attrs, newattr);
	 }
      }
   }

}/* end of GetSymbsAndAttrs */





/************************************************/
/* InitOptimStructure              */
/************************************************/

void
InitOptimStructure()
{
   optimroot = NVisit_Sequences;
   initializeSEQVisit_Seq(optimroot->vi_seq);
   initializeSEQCan_Eval(optimroot->caneval);
   initializeSEQAttributes(optimroot->single_visit);
   initializeSEQAttributes(optimroot->glob_var);
   initializeSEQAttributes(optimroot->tree_attrs);
   initializeSEQAttributes(optimroot->attrs);
   initializeSEQSymbols(optimroot->symbs);
   initializeSEQGroup(optimroot->groups);

   (void) GetSymbsAndAttrs(ligaroot);
   (void) BuildVs(ligaroot);

}/* end of InitOptimStructure */
