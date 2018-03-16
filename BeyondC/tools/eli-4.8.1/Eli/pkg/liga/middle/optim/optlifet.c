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

/* $Id: optlifet.c,v 4.5 1998/04/28 14:27:42 ludi Exp $ */
static char rcs_id[] = "$Id: optlifet.c,v 4.5 1998/04/28 14:27:42 ludi Exp $";

/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optlifet.c                   */
/* */
/* Contains the routines to build         */
/* lifetime vs and liftime grammar        */
/* */
/************************************************/




/************************************************/
/* includes                   */
/************************************************/

#include <stdio.h>
#include "lookup_idl.h"
#include "OPTIM.h"
#include "OPTIMMacros.h"
#include "middle_mem.h"
#include "option_enums.h"
#include "option_types.h"

#include "optglobal.h"
#include "optidl.h"
#include "optfct.h"

#include "printerr.h"
#include "ligaconsts.h"
#include "optlifet.h"
#include "list.h"

/************************************************/
/* defines                    */
/************************************************/


#define		NOT_USED	0
#define		DUMMY		0

#define		EMPTY		0
#define		DEFINITION	1
#define		LASTUSE		2
#define		BLANK		4





/************************************************/
/* global types and variables          */
/************************************************/

typedef int Bitset;

int insert_index;
int compare_fct_counter;

typedef Terminal a_Terminal[MAX_VISITS];
a_Terminal *term_array;
typedef Nonterminal a_Nonterminal[MAX_VISITS];
a_Nonterminal *nonterm_array;
a_Boolean *needed_nonterm;

/************************************************/
/* functions                  */
/************************************************/

Boolean AppAttribute( /* int, int */ );
Boolean DefAttribute( /* int, int */ );
Boolean EqualAttributes( /* Attributes, Attributes */ );
Boolean EqualTerminals( /* Terminal, Terminal */ );
Boolean EqualNonterminals( /* Nonterminal, Nonterminal */ );
Boolean EqualRules( /* Rule, Rule */ );
Boolean CompareFct( /* Action, Action */ );
Boolean NewRule( /* SEQRule, Rule */ );
Boolean LastuseAlwaysBnNF( /* SEQVSL, Attributes */ );
Boolean CheckDLStarCondition( /* Grammar */ );

Attributes MkAttr( /* Attrdef, int */ );
Eval MkEval( /* Eval */ );
Terminal MkTerminal( /* int, int */ );
Nonterminal MkNonterminal( /* int, int */ );

void RemNonBnNFUse( /* SEQVSL, Attributes */ );
void RemDoubleInstances( /* SEQAction, Attributes, int */ );
void RemEqualParams( /* Eval, Attributes, int */ );

void InitRule( /* Rule, int, int */ );

int CompUseCounter( /* SEQAction, Attributes */ );
int CompInsertIndex( /* SEQAction, Attributes */ );
int CompLastuse( /* SEQAction, Attributes */ );
int CompVisitIndex( /* SEQVSL, Attributes */ );
int StartSymbId( /* no parameter */ );

SEQAction GetActions( /* Visit_Seq, SEQAction */ );
SEQAttributes GetNonBnNFAttrs( /* SEQVSL */ );

void GetAppDefAttrs( /* Visit_Seq, VSL */ );
void InsertArtificialOcc( /* VSL, Attributes */ );
void InsertNonBnNFOcc( /* VSL, Attributes, int */ );
void GetRules( /* Grammar */ );

VSL MkVslp( /* Visit_Seq */ );

void ReleaseTerminals( /* Grammar */ );
void PutTerminals( /* Grammar, int */ );
void RemRules( /* Grammar */ );
void PutRules( /* Grammar, Grammar, int */ );

Grammar MkLtGrammar( /* no parameter */ );
Grammar PrepareProjGrammar( /* Grammar, Grammar, int */ );
Grammar MkProjGrammar( /* Grammar */ );

void InitFirstSets( /* Grammar */ );
void InitFollowSets( /* Grammar */ );
void ComputeFirstSets( /* Grammar */ );
void ComputeFollowSets( /* Grammar */ );

Boolean AnalyzeGrammar( /* Grammar */ );

void VslCorrection( /* SEQVSL, Attributes */ );
void NonBnNFCorrection( /* SEQVSL */ );

void GrammarLifetimeAnalysis(/* attrlist */);





/************************************************/
/* AppAttribute                 */
/************************************************/

Boolean 
AppAttribute(class, symbno)
   int class, symbno;
{

   return ((class == ATCLSYNT && symbno > 0) || (class == ATCLINH && !symbno));

}/* end of AppAttribute */





/************************************************/
/* DefAttribute                 */
/************************************************/

Boolean 
DefAttribute(class, symbno)
   int class, symbno;
{

   return ((class == ATCLSYNT && !symbno) || (class == ATCLINH && symbno > 0));

}/* end of DefAttribute */





/************************************************/
/* EqualAttributes                */
/************************************************/

Boolean 
EqualAttributes(X, Y)
   Attributes X, Y;
{

   return (X->attrid == Y->attrid && X->symbno == Y->symbno);

}/* end of EqualAttributes */





/************************************************/
/* EqualTerminals                */
/************************************************/

Boolean 
EqualTerminals(X, Y)
   Terminal X, Y;
{

   return (X->attrid == Y->attrid && X->occ == Y->occ);

}/* end of EqualTerminals */





/************************************************/
/* EqualNonterminals               */
/************************************************/

Boolean 
EqualNonterminals(X, Y)
   Nonterminal X, Y;
{

   return (X->symbid == Y->symbid && X->index == Y->index);

}/* end of EqualNonterminals */





/************************************************/
/* EqualRules                  */
/************************************************/

Boolean 
EqualRules(rule1, rule2)
   Rule rule1, rule2;
{
   SEQVocabulary X;
   Vocabulary entry1, entry2;
   int index = 0;

   if (!EqualNonterminals(rule1->lhs, rule2->lhs))
      return (FALSE);
   if (lengthSEQVocabulary(rule1->rhs) != lengthSEQVocabulary(rule2->rhs))
      return (FALSE);
   foreachinSEQVocabulary(rule1->rhs, X, entry1)
   {
      ithinSEQVocabulary(rule2->rhs, ++index, entry2);
      if (typeof(entry1) != typeof(entry2))
	 return (FALSE);
      else if (typeof(entry1) == KNonterminal)
      {
	 if (!(EqualNonterminals(entry1.VNonterminal, entry2.VNonterminal)))
	    return (FALSE);
      } else if (!EqualTerminals(entry1.VTerminal, entry2.VTerminal))
	 return (FALSE);
   }

   return (TRUE);

}/* end of EqualRules */





/************************************************/
/* CompareFct                  */
/************************************************/

Boolean 
CompareFct(action1, action2)
   Action action1, action2;
{
   return (++compare_fct_counter == insert_index);
}/* end of CompareFct */





/************************************************/
/* NewRule                    */
/************************************************/

Boolean 
NewRule(ruleseq, rule)
   SEQRule ruleseq;
   Rule rule;
{
   SEQRule X;
   Rule thisrule;

   foreachinSEQRule(ruleseq, X, thisrule)
      if (EqualRules(thisrule, rule))
      return (FALSE);

   return (TRUE);
}/* end of NewRule */





/************************************************/
/* LastuseAlwaysBnNF              */
/************************************************/

Boolean 
LastuseAlwaysBnNF(vslseq, attr)
   SEQVSL vslseq;
   Attributes attr;
{
   SEQVSL X;
   VSL thisvsl;
   int lastuse, i;
   SEQAction Y, actionseq;
   Action thisaction;
   Visits visit;
   Boolean lastuse_in_BnNF;

   foreachinSEQVSL(vslseq, X, thisvsl)
   {
      lastuse = CompLastuse(thisvsl->actions, attr);
      if (lastuse > NOT_USED)
      {
	 actionseq = thisvsl->actions;
	 for (i = 0; i < lastuse; i++)
	    actionseq = tailSEQAction(actionseq);
	 foreachinSEQAction(actionseq, Y, thisaction)
	    if (typeof(thisaction) == KVisits)
	 {
	    visit = thisaction.VVisits;
	    if (visit->symbno == LEAVE && attr->class == ATCLSYNT)
	    {
	       if (visit->ord == attr->part)
	       {
		  lastuse_in_BnNF = TRUE;
		  break;
	       } else
	       {
		  lastuse_in_BnNF = FALSE;
		  break;
	       }
	    }
	    if (visit->symbno != LEAVE && attr->class == ATCLINH)
	    {
	       if (visit->ord == attr->part)
	       {
		  lastuse_in_BnNF = TRUE;
		  break;
	       } else
	       {
		  lastuse_in_BnNF = FALSE;
		  break;
	       }
	    }
	 }
	 if (!lastuse_in_BnNF)
	 {
	    break;
	 }
      }
   }

   return (lastuse_in_BnNF);

}/* end of LastuseAlwaysBnNF */





/************************************************/
/* CheckDLStarCondition            */
/************************************************/

Boolean 
CheckDLStarCondition(grammar)
   Grammar grammar;
{
   SEQTerminal X;
   Terminal thisterm;
   Nonterminal startsymb;

   startsymb = nonterm_array[grammar->startsymb->symbid]
      [grammar->startsymb->index];
   if (startsymb->first & LASTUSE)
      return FALSE;
   foreachinSEQTerminal(grammar->terms, X, thisterm)
      if (thisterm->occ == DEFINITION)
   {
      if (thisterm->follow & thisterm->occ)
	 return (FALSE);
   }
   return (TRUE);
}/* end of CheckDLStarCondition */



/************************************************/
/* MkAttr                   */
/************************************************/

Attributes 
MkAttr(attrdef, symbno)
   Attrdef attrdef;
   int symbno;
{
   Attributes newattr;

   newattr = NAttributes;
   newattr->attrid = attrdef->did;
   newattr->class = attrdef->class;
   newattr->part = attrdef->part;
   newattr->typeid = attrdef->typeid;
   newattr->gen = attrdef->gen;
   newattr->symbno = symbno;

   return (newattr);

}/* end of MkAttr */





/************************************************/
/* MkEval                   */
/************************************************/

Eval 
MkEval(oldeval)
   Eval oldeval;
{
   Eval eval;
   SEQAttributes X;
   Attributes thisparam, newattr;
   Attrdef attrdef;

   eval = NEval;
   initializeSEQAttributes(eval->params);
   eval->attrid = oldeval->attrid;
   eval->symbno = oldeval->symbno;
   foreachinSEQAttributes(oldeval->params, X, thisparam)
   {
      attrdef = lookup_attrdef(thisparam->attrid);
      newattr = MkAttr(attrdef, thisparam->symbno);
      appendrearSEQAttributes(eval->params, newattr);
   }

   return (eval);

}/* end of MkEval */





/************************************************/
/* MkTerminal                 */
/************************************************/

Terminal 
MkTerminal(id, occ)
   int id, occ;
{
   Terminal newterm;

   newterm = NTerminal;
   newterm->attrid = id;
   newterm->occ = occ;

   return (newterm);

}/* end of MkTerminal */





/************************************************/
/* MkNonterminal                */
/************************************************/

Nonterminal 
MkNonterminal(id, index)
   int id, index;
{
   Nonterminal newnt;

   newnt = NNonterminal;
   newnt->symbid = id;
   newnt->index = index;
   newnt->first = 0;

   return (newnt);

}/* end of MkNonterminal */





/************************************************/
/* RemNonBnNFUse                */
/************************************************/

void 
RemNonBnNFUse(vslseq, attr)
   SEQVSL vslseq;
   Attributes attr;
{
   SEQVSL X;
   VSL thisvsl;
   SEQAction Y;
   Action thisaction;
   Eval eval;
   SEQAttributes Z;
   Attributes thisparam;

   foreachinSEQVSL(vslseq, X, thisvsl)
      foreachinSEQAction(thisvsl->actions, Y, thisaction)
      if (typeof(thisaction) == KEval)
   {
      eval = thisaction.VEval;
      foreachinSEQAttributes(eval->params, Z, thisparam)
	 if (EqualAttributes(thisparam, attr))
      {
	 removeSEQAttributes(eval->params, thisparam);
      }
   }
}/* end of RemNonBnNFUse */





/************************************************/
/* RemDoubleInstances                */
/************************************************/

void 
RemDoubleInstances(actionseq, attr, usecounter)
   SEQAction actionseq;
   Attributes attr;
   int usecounter;
{
   SEQAction X;
   Action thisaction;
   Eval eval;
   SEQAttributes Y;
   Attributes thisparam;
   int remcounter = 0;

   foreachinSEQAction(actionseq, X, thisaction)
   {
      if (remcounter + 1 == usecounter)
      {
	 break;
      }
      if (typeof(thisaction) == KEval)
      {
	 eval = thisaction.VEval;
	 foreachinSEQAttributes(eval->params, Y, thisparam)
	    if (EqualAttributes(attr, thisparam))
	 {
	    removeSEQAttributes(eval->params, thisparam);
	    remcounter++;
	 }
      }
   }

}/* end of RemDoubleInstances */





/************************************************/
/* RemEqualParams                 */
/************************************************/

void 
RemEqualParams(eval, attr, number)
   Eval eval;
   Attributes attr;
   int number;
{
   SEQAttributes X;
   Attributes thisparam;
   int counter = 0;

   foreachinSEQAttributes(eval->params, X, thisparam)
   {
      if (counter + 1 == number)
	 break;
      if (EqualAttributes(attr, thisparam))
      {
	 removeSEQAttributes(eval->params, thisparam);
	 counter++;
      }
   }

}/* end of RemEqualParams */





/************************************************/
/* InitRule                    */
/************************************************/

void 
InitRule(rule, id, index)
   Rule rule;
   int id, index;
{
   Def def;
   Prod prod;

   rule->prodid = id;
   def = lookup_def(id);
   prod = def.VProd;
   rule->lhs = MkNonterminal(prod->lhs, index);
   initializeSEQVocabulary(rule->rhs);

}/* end of InitRule */





/************************************************/
/* CompUseCounter                */
/************************************************/

int 
CompUseCounter(actionseq, attr)
   SEQAction actionseq;
   Attributes attr;
{
   SEQAction X;
   Action thisaction;
   Eval eval;
   SEQAttributes Y;
   Attributes thisparam;
   int paramcount = 0, counter = NOT_USED;

   foreachinSEQAction(actionseq, X, thisaction)
      if (typeof(thisaction) == KEval)
   {
      eval = thisaction.VEval;
      foreachinSEQAttributes(eval->params, Y, thisparam)
	 if (EqualAttributes(thisparam, attr))
      {
	 counter++;
	 paramcount++;
      }
      if (paramcount > 1)
      {
	 counter = counter - paramcount + 1;
	 (void) RemEqualParams(eval, attr, paramcount);
      }
      paramcount = 0;
   }
   return (counter);

}/* end of CompUseCounter */





/************************************************/
/* CompInsertIndex                */
/************************************************/

int 
CompInsertIndex(actionseq, attr)
   SEQAction actionseq;
   Attributes attr;
{
   SEQAction X;
   Action thisaction;
   Visits visit;
   /* Boolean     found = FALSE; */
   int counter = 0;

   switch (attr->class)
   {
   case ATCLSYNT:
      foreachinSEQAction(actionseq, X, thisaction)
      {
	 counter++;
	 if (typeof(thisaction) == KVisits)
	 {
	    visit = thisaction.VVisits;
	    if (visit->symbno == attr->symbno && visit->ord == attr->part)
	    {	/* found = TRUE; */
	       break;
	    }
	 }
      }
      break;
   case ATCLINH:
      if (attr->part > 1)
	 foreachinSEQAction(actionseq, X, thisaction)
      {
	 counter++;
	 if (typeof(thisaction) == KVisits)
	 {
	    visit = thisaction.VVisits;
	    if (visit->symbno == 0 && visit->ord == attr->part - 1)
	    {
	       /* found = TRUE; */
	       break;
	    }
	 }
      }
      break;
   default:
      break;
   }	/* end of switch */

   return (++counter);

}/* end of CompInsertIndex */





/************************************************/
/* CompLastuse                  */
/************************************************/

int 
CompLastuse(actionseq, attr)
   SEQAction actionseq;
   Attributes attr;
{
   SEQAction X;
   Action thisaction;
   Eval eval;
   SEQAttributes Y;
   Attributes thisparam;
   int counter = 0, index = NOT_USED;

   foreachinSEQAction(actionseq, X, thisaction)
   {
      counter++;
      if (typeof(thisaction) == KEval)
      {
	 eval = thisaction.VEval;
	 foreachinSEQAttributes(eval->params, Y, thisparam)
	    if (EqualAttributes(thisparam, attr))
	 {
	    index = counter;
	 }
      }
   }

   return (index);

}/* end of CompLastuse */





/************************************************/
/* CompVisitIndex                 */
/************************************************/

int 
CompVisitIndex(vslseq, attr)
   SEQVSL vslseq;
   Attributes attr;
{
   SEQVSL X;
   VSL thisvsl;
   SEQAction Y;
   Action thisaction;
   Visits visit;
   int lastuse, counter, latest_BnNF_visit_index = 0;

   foreachinSEQVSL(vslseq, X, thisvsl)
   {
      lastuse = CompLastuse(thisvsl->actions, attr);
      if (lastuse > NOT_USED)
      {
	 counter = 0;
	 foreachinSEQAction(thisvsl->actions, Y, thisaction)
	 {
	    if (++counter == lastuse)
	       break;
	    if (typeof(thisaction) == KVisits)
	    {
	       visit = thisaction.VVisits;
	       if (attr->class == ATCLSYNT && visit->symbno == LEAVE)
		  if (visit->ord > latest_BnNF_visit_index)
		     latest_BnNF_visit_index = visit->ord;
	       if (attr->class == ATCLINH && visit->symbno == attr->symbno)
		  if (visit->ord > latest_BnNF_visit_index)
		     latest_BnNF_visit_index = visit->ord;
	    }
	 }
      }
   }

   return (latest_BnNF_visit_index);

}/* end of CompVisitIndex */





/************************************************/
/* StartSymbId                  */
/************************************************/

int 
StartSymbId()
{
   SEQSymbols X;
   Symbols thissymb;
   SEQDef Y;
   Def thisdef;
   SEQEntity Z;
   Entity entity;
   Prod prod;
   int startsymbid, startsymbcounter = 0;
   Boolean found;

   foreachinSEQSymbols(optimroot->symbs, X, thissymb)
   {
      found = FALSE;
      foreachinSEQDef(ligaroot->defseq, Y, thisdef)
      {
	 if (typeof(thisdef) == KProd)
	 {
	    prod = thisdef.VProd;
	    foreachinSEQEntity(prod->rhs, Z, entity)
	       if (entity.VUnit.VSymbol->did == thissymb->symbid)
	    {
	       found = TRUE;
	       break;
	    }
	 }
	 if (found)
	    break;
      }
      if (!found)
      {
	 startsymbid = thissymb->symbid;
	 startsymbcounter++;
      }
      if (startsymbcounter > 1)
      {
	 err_setpos(0, 0);
	 err_print_error("AG contains more than one STARTSYMBOL ! \n");
	 fprintf(ProtocolFile, "*** ERROR: AG contains more than one STARTSYMBOL !\n");
      }
   }

   return (startsymbid);

}/* end of StartSymbId */





/************************************************/
/* GetActions                  */
/************************************************/

SEQAction 
GetActions(thisvs, actionseq)
   Visit_Seq thisvs;
   SEQAction actionseq;
{
   SEQAction X;
   Action thisaction;
   Visits visit, newvisit;
   Eval eval, neweval;

   foreachinSEQAction(tailSEQAction(thisvs->actions), X, thisaction)
      switch (typeof(thisaction))
   {
   case KVisits:
      visit = thisaction.VVisits;
      newvisit = optim_MkVisit(visit->symbno, visit->ord, visit->symbid);
      IDLtempAction.VVisits = newvisit;
      appendrearSEQAction(actionseq, IDLtempAction);
      break;
   case KEval:
      eval = thisaction.VEval;
      neweval = MkEval(eval);
      IDLtempAction.VEval = neweval;
      appendrearSEQAction(actionseq, IDLtempAction);
      break;
   default:
      break;
   }	/* end of switch */

   return (actionseq);

}/* end of GetActions */





/************************************************/
/* GetNonBnNFAttrs               */
/************************************************/

SEQAttributes 
GetNonBnNFAttrs(vslpseq)
   SEQVSL vslpseq;
{
   Eval dummy, eval;
   SEQVSL X;
   VSL thisvsl;
   SEQAction Y;
   Action thisaction;
   SEQAttributes Z, ZZ;
   Attributes thisparam, thisattr, attr;
   Attrdef attrdef;
   Boolean found = FALSE;

   dummy = NEval;
   initializeSEQAttributes(dummy->params);
   foreachinSEQVSL(vslpseq, X, thisvsl)
      foreachinSEQAction(thisvsl->actions, Y, thisaction)
      if (typeof(thisaction) == KEval)
   {
      eval = thisaction.VEval;
      foreachinSEQAttributes(eval->params, Z, thisparam)
      {
	 if (DefAttribute(thisparam->class, thisparam->symbno))
	 {
	    found = FALSE;
	    foreachinSEQAttributes(dummy->params, ZZ, thisattr)
	       if (EqualAttributes(thisattr, thisparam))
	    {
	       found = TRUE;
	    }
	    if (!found)
	    {
	       attrdef = lookup_attrdef(thisparam->attrid);
	       attr = MkAttr(attrdef, thisparam->symbno);
	       appendrearSEQAttributes(dummy->params, attr);
	    }
	 }
      }
   }
   return (dummy->params);

}/* end of GetNonBnNFAttrs */





/************************************************/
/* GetAppDefAttrs               */
/************************************************/

void 
GetAppDefAttrs(thisvs, vslp)
   Visit_Seq thisvs;
   VSL vslp;
{
   SEQSymbols X;
   Symbols thissymb;
   Symb symbdef;
   SEQAttrdef Y;
   Def def;
   Attrdef attrdef;
   Attributes newattr;

   foreachinSEQSymbols(thisvs->symbs, X, thissymb)
   {
      def = lookup_def(thissymb->symbid);
      symbdef = def.VSymb;
      foreachinSEQAttrdef(symbdef->attrs, Y, attrdef)
      {
	 newattr = MkAttr(attrdef, thissymb->symbno);
	 if (AppAttribute(attrdef->class, thissymb->symbno))
	    appendrearSEQAttributes(vslp->app_attrs, newattr);
	 else if (DefAttribute(attrdef->class, thissymb->symbno))
	    appendrearSEQAttributes(vslp->def_attrs, newattr);
      }
   }

}/* end of GetAppDefAttrs */





/************************************************/
/* InsertArtificialOcc             */
/************************************************/

void 
InsertArtificialOcc(vslp, attr)
   VSL vslp;
   Attributes attr;
{
   Eval dummyeval;
   Attrdef attrdef;
   Attributes artificial_occ;

   dummyeval = NEval;
   dummyeval->attrid = dummyeval->symbno = DUMMY;
   initializeSEQAttributes(dummyeval->params);
   attrdef = lookup_attrdef(attr->attrid);
   artificial_occ = MkAttr(attrdef, attr->symbno);
   appendrearSEQAttributes(dummyeval->params, artificial_occ);
   insert_index = CompInsertIndex(vslp->actions, attr);
   compare_fct_counter = 0;
   IDLtempAction.VEval = dummyeval;
   orderedinsertSEQAction(vslp->actions, IDLtempAction, CompareFct);

}/* end of InsertArtificialOcc */





/************************************************/
/* InsertNonBnNFOcc              */
/************************************************/

void 
InsertNonBnNFOcc(vslp, attr, index)
   VSL vslp;
   Attributes attr;
   int index;
{
   Eval dummyeval;
   Attrdef attrdef;
   Attributes artificial_occ;
   SEQAction X;
   Action thisaction;
   Visits visit;
   int counter = 0;

   dummyeval = NEval;
   dummyeval->attrid = dummyeval->symbno = DUMMY;
   initializeSEQAttributes(dummyeval->params);
   attrdef = lookup_attrdef(attr->attrid);
   artificial_occ = MkAttr(attrdef, attr->symbno);
   appendrearSEQAttributes(dummyeval->params, artificial_occ);
   insert_index = 0;
   foreachinSEQAction(vslp->actions, X, thisaction)
   {
      counter++;
      if (typeof(thisaction) == KVisits)
      {
	 visit = thisaction.VVisits;
	 if (attr->class == ATCLSYNT && visit->symbno == LEAVE && visit->ord == index)
	 {
	    insert_index = counter + 1;
	    compare_fct_counter = 0;
	    IDLtempAction.VEval = dummyeval;
	    orderedinsertSEQAction(vslp->actions, IDLtempAction, CompareFct);
	    /* old version : { insert_index = counter + 1; break; } */
	 }
	 if (attr->class == ATCLINH && visit->symbno == attr->symbno && visit->ord == index)
	 {
	    insert_index = counter + 1;
	    compare_fct_counter = 0;
	    IDLtempAction.VEval = dummyeval;
	    orderedinsertSEQAction(vslp->actions, IDLtempAction, CompareFct);
	    /* old version : { insert_index = counter + 1; break; } */
	 }
      }
   }

   /* old version : compare_fct_counter = 0;
    * orderedinsertSEQAction(vslp->actions, dummyeval, CompareFct); */

}/* end of InsertNonBnNFOcc */





/************************************************/
/* GetRules                  */
/************************************************/

void 
GetRules(grammar)
   Grammar grammar;
{
   SEQVSL X;
   VSL thisvslp;
   Rule rule;
   SEQAction Y;
   Action thisaction;
   Eval eval;
   Visits visit;
   SEQAttributes Z;
   Attributes thisparam;
   Terminal term;
   Nonterminal nonterm;
   int index;

   foreachinSEQVSL(optimroot->vsl, X, thisvslp)
   {
      index = 1;
      rule = NRule;
      (void) InitRule(rule, thisvslp->prodid, index);
      foreachinSEQAction(thisvslp->actions, Y, thisaction)
	 switch (typeof(thisaction))
      {
      case KVisits:
	 visit = thisaction.VVisits;
	 if (visit->symbno == LEAVE)
	 {
	    if (NewRule(grammar->rules, rule))
	       appendrearSEQRule(grammar->rules, rule);
	    else
	    {	/* (void) release_rule(rule); */
	    }
	    rule = NRule;
	    (void) InitRule(rule, thisvslp->prodid, ++index);
	 } else
	 {
	    nonterm = MkNonterminal(visit->symbid, visit->ord);
	    IDLtempVocabulary.VNonterminal = nonterm;
	    appendrearSEQVocabulary(rule->rhs, IDLtempVocabulary);
	 }
	 break;
      case KEval:
	 eval = thisaction.VEval;
	 foreachinSEQAttributes(eval->params, Z, thisparam)
	 {
	    term = MkTerminal(thisparam->attrid, LASTUSE);
	    IDLtempVocabulary.VTerminal = term;
	    appendrearSEQVocabulary(rule->rhs, IDLtempVocabulary);
	 }
	 if (eval->attrid > DUMMY)
	 {
	    term = MkTerminal(eval->attrid, DEFINITION);
	    IDLtempVocabulary.VTerminal = term;
	    appendrearSEQVocabulary(rule->rhs, IDLtempVocabulary);
	 }
	 break;
      default:
	 break;
      }	/* end of switch */
   }

}/* end of GetRules */





/************************************************/
/* MkVslp                   */
/************************************************/

VSL 
MkVslp(thisvs)
   Visit_Seq thisvs;
{
   VSL vslp;
   SEQAttributes X;
   Attributes thisattr;
   int usecounter;

   vslp = NVSL;
   initializeSEQAction(vslp->actions);
   initializeSEQAttributes(vslp->app_attrs);
   initializeSEQAttributes(vslp->def_attrs);
   vslp->prodid = thisvs->prodid;
   (void) GetAppDefAttrs(thisvs, vslp);
   vslp->actions = GetActions(thisvs, vslp->actions);
   foreachinSEQAttributes(vslp->app_attrs, X, thisattr)
   {
      usecounter = CompUseCounter(vslp->actions, thisattr);
      if (usecounter == NOT_USED)
      {
	 (void) InsertArtificialOcc(vslp, thisattr);
      } else
      {
	 if (usecounter > 1)
	 {
	    (void) RemDoubleInstances(vslp->actions, thisattr, usecounter);
	 }
      }
   }

   return (vslp);

}/* end of MkVslp */





/************************************************/
/* ReleaseTerminals             */
/************************************************/

void 
ReleaseTerminals(grammar)
   Grammar grammar;
{
   SEQTerminal X;
   Terminal thisterm;

   foreachinSEQTerminal(grammar->terms, X, thisterm)
   {
      removeSEQTerminal(grammar->terms, thisterm);
      DTerminal(thisterm);
   }

}/* end of ReleaseTerminals */





/************************************************/
/* PutTerminals               */
/************************************************/

void 
PutTerminals(grammar, id)
   Grammar grammar;
   int id;
{
   Terminal term;

   term = MkTerminal(id, DEFINITION);
   appendrearSEQTerminal(grammar->terms, term);
   term = MkTerminal(id, LASTUSE);
   appendrearSEQTerminal(grammar->terms, term);

}/* end of PutTerminals */





/************************************************/
/* RemRules                  */
/************************************************/

void 
RemRules(grammar)
   Grammar grammar;
{
   SEQRule X;
   Rule thisrule;
   SEQVocabulary Y;
   Vocabulary entry;

   foreachinSEQRule(grammar->rules, X, thisrule)
      foreachinSEQVocabulary(thisrule->rhs, Y, entry)
      removeSEQVocabulary(thisrule->rhs, entry);

}/* end of RemRules */





/************************************************/
/* PutRules                 */
/************************************************/

void 
PutRules(targetgrammar, sourcegrammar, id)
   Grammar targetgrammar, sourcegrammar;
   int id;
{
   SEQRule X;
   Rule thisrule, targetrule;
   SEQVocabulary Y;
   Vocabulary entry;
   int index = 0;

   foreachinSEQRule(sourcegrammar->rules, X, thisrule)
   {
      ithinSEQRule(targetgrammar->rules, ++index, targetrule);
      foreachinSEQVocabulary(thisrule->rhs, Y, entry)
      {
	 if (typeof(entry) == KNonterminal)
	    appendrearSEQVocabulary(targetrule->rhs, entry);
	 else if (entry.VTerminal->attrid == id)
	    appendrearSEQVocabulary(targetrule->rhs, entry);
      }
   }

}/* end of PutRules */





/************************************************/
/* MkLtGrammar                 */
/************************************************/

Grammar 
MkLtGrammar()
{
   Grammar grammar;
   SEQSymbols X;
   Symbols thissymb;
   SEQAttributes Y;
   Attributes thisattr;
   int i;
   Terminal term;
   Nonterminal nonterm;

   grammar = NGrammar;
   initializeSEQNonterminal(grammar->nonterms);
   initializeSEQTerminal(grammar->terms);
   initializeSEQRule(grammar->rules);
   grammar->startsymb = MkNonterminal((int) StartSymbId(), 1);
   foreachinSEQSymbols(optimroot->symbs, X, thissymb)
      for (i = 1; i <= thissymb->parts; i++)
   {
      nonterm = MkNonterminal(thissymb->symbid, i);
      appendrearSEQNonterminal(grammar->nonterms, nonterm);
   }
   foreachinSEQAttributes(optimroot->attrs, Y, thisattr)
   {
      term = MkTerminal(thisattr->attrid, DEFINITION);
      appendrearSEQTerminal(grammar->terms, term);
      term = MkTerminal(thisattr->attrid, LASTUSE);
      appendrearSEQTerminal(grammar->terms, term);
   }
   (void) GetRules(grammar);

   return (grammar);

}/* end of MkLtGrammar */





/************************************************/
/* PrepareProjGrammar             */
/************************************************/

Grammar 
PrepareProjGrammar(ltgrammar, projgrammar, id)
   Grammar ltgrammar, projgrammar;
   int id;
{

   /* nothing to do for startsymbol and nonterminal sequence, */
   /* because they are equal for each proj_grmmar             */

   (void) ReleaseTerminals(projgrammar);
   (void) PutTerminals(projgrammar, id);
   (void) RemRules(projgrammar);
   (void) PutRules(projgrammar, ltgrammar, id);

   return (projgrammar);

}/* end of PrepareProjGrammar */





/************************************************/
/* MkProjGrammar                */
/************************************************/

Grammar 
MkProjGrammar(ltgrammar)
   Grammar ltgrammar;
{
   Grammar projgrammar;
   SEQRule X;
   Rule thisrule, rule;

   projgrammar = NGrammar;
   initializeSEQNonterminal(projgrammar->nonterms);
   initializeSEQTerminal(projgrammar->terms);
   initializeSEQRule(projgrammar->rules);

   projgrammar->startsymb = ltgrammar->startsymb;
   projgrammar->nonterms = ltgrammar->nonterms;

   foreachinSEQRule(ltgrammar->rules, X, thisrule)
   {
      rule = NRule;
      (void) InitRule(rule, thisrule->prodid, thisrule->lhs->index);
      appendrearSEQRule(projgrammar->rules, rule);
   }

   return (projgrammar);

}/* end of MkProjGrammar */





/************************************************/
/* InitFirstSets                  */
/************************************************/

void 
InitFirstSets(grammar)
   Grammar grammar;
{
   SEQTerminal X;
   Terminal thisterm;
   SEQNonterminal Y;
   Nonterminal thisnt;

   foreachinSEQTerminal(grammar->terms, X, thisterm)
   {
      thisterm->first = thisterm->occ;
      term_array[thisterm->attrid][thisterm->occ] = thisterm;
   }
   foreachinSEQNonterminal(grammar->nonterms, Y, thisnt)
   {
      thisnt->first = EMPTY;
      nonterm_array[thisnt->symbid][thisnt->index] = thisnt;
   }

}/* end of InitFirstSets */





/************************************************/
/* InitFollowSets                  */
/************************************************/

void 
InitFollowSets(grammar)
   Grammar grammar;
{
   SEQTerminal X;
   Terminal thisterm;
   SEQNonterminal Y;
   Nonterminal thisnt;

   foreachinSEQTerminal(grammar->terms, X, thisterm)
   {
      thisterm->follow = EMPTY;
      term_array[thisterm->attrid][thisterm->occ] = thisterm;
   }
   foreachinSEQNonterminal(grammar->nonterms, Y, thisnt)
   {
      thisnt->follow = EMPTY;
      nonterm_array[thisnt->symbid][thisnt->index] = thisnt;
      needed_nonterm[thisnt->symbid][thisnt->index] = FALSE;
   }
   thisnt = nonterm_array[grammar->startsymb->symbid][grammar->startsymb->index];
   thisnt->follow = BLANK;

}/* end of InitFollowSets */





/************************************************/
/* ComputeFirstSets               */
/************************************************/

void 
ComputeFirstSets(grammar)
   Grammar grammar;
{
   SEQRule X;
   Rule thisrule;
   int length, index;
   Bitset omega, firstset, oldfirst, first_X_i;
   Boolean ready, complete = FALSE;
   Vocabulary X_i;
   Nonterminal thisnt, nonterm;

   while (!complete)
   {
      complete = TRUE;
      foreachinSEQRule(grammar->rules, X, thisrule)
      {
	 nonterm = nonterm_array[thisrule->lhs->symbid][thisrule->lhs->index];
	 length = lengthSEQVocabulary(thisrule->rhs);
	 index = 0;
	 omega = BLANK;
	 oldfirst = firstset = nonterm->first;
	 if (length == 0)
	 {
	    firstset = firstset | omega;
	 } else
	 {
	    ready = FALSE;
	    while (!ready && index < length)
	    {
	       ithinSEQVocabulary(thisrule->rhs, ++index, X_i);
	       if (typeof(X_i) == KTerminal)
	       {
		  first_X_i = X_i.VTerminal->occ;
	       } else
	       {
		  thisnt = nonterm_array[X_i.VNonterminal->symbid][X_i.VNonterminal->index];
		  first_X_i = thisnt->first;
	       }
	       if (first_X_i < BLANK)
	       {
		  ready = TRUE;
	       }
	       omega = omega | first_X_i;
	    }
	    if (first_X_i < BLANK)
	    {
	       omega = omega - BLANK;
	    }
	    firstset = firstset | omega;
	 }
	 if (oldfirst != firstset)
	 {
	    complete = FALSE;
	    nonterm->first = firstset;
	 }
      }
   }


}/* end of ComputeFirstSets */





/************************************************/
/* ComputeFollowSets               */
/************************************************/

void 
ComputeFollowSets(grammar)
   Grammar grammar;
{
   Boolean changed, ready, goon;
   Boolean complete = FALSE, error_condition = FALSE;
   SEQRule X;
   Rule thisrule;
   int index, newindex, length;
   SEQVocabulary Y;
   Vocabulary entry, nextentry;
   Terminal term;
   Nonterminal nonterm, thisnt, lhs;
   Bitset followset, oldfollowset, firstset;

   while (!complete)
   {
      changed = FALSE;
      foreachinSEQRule(grammar->rules, X, thisrule)
      {
	 index = 0;
	 length = lengthSEQVocabulary(thisrule->rhs);
	 foreachinSEQVocabulary(thisrule->rhs, Y, entry)
	 {
	    index++;
	    if (typeof(entry) == KTerminal)
	    {
	       if (entry.VTerminal->occ == DEFINITION)
	       {
		  goon = TRUE;
		  term = term_array[entry.VTerminal->attrid][entry.VTerminal->occ];
		  followset = oldfollowset = term->follow;
	       } else
	       {
		  goon = FALSE;
	       }
	    } else
	    {
	       if (needed_nonterm[entry.VNonterminal->symbid][entry.VNonterminal->index])
	       {
		  goon = TRUE;
		  nonterm = nonterm_array[entry.VNonterminal->symbid][entry.VNonterminal->index];
		  followset = oldfollowset = nonterm->follow;
	       } else
	       {
		  goon = FALSE;
	       }
	    }
	    if (goon)
	    {
	       if (index < length)
	       {
		  ready = FALSE;
		  newindex = index;
		  while (!ready && newindex < length)
		  {
		     ithinSEQVocabulary(thisrule->rhs, newindex + 1, nextentry);
		     if (typeof(nextentry) == KTerminal)
		     {
			ready = TRUE;
			followset = followset | nextentry.VTerminal->occ;
		     } else
		     {
			thisnt = nonterm_array[nextentry.VNonterminal->symbid][nextentry.VNonterminal->index];
			firstset = thisnt->first;
			if (firstset >= BLANK)
			{
			   newindex++;
			   firstset = firstset - BLANK;
			} else
			{
			   ready = TRUE;
			}
			followset = followset | firstset;
			if (newindex == length)
			{
			   lhs = nonterm_array[thisrule->lhs->symbid][thisrule->lhs->index];
			   followset = followset | lhs->follow;
			   if (!needed_nonterm[lhs->symbid][lhs->index])
			   {
			      changed = TRUE;
			      needed_nonterm[lhs->symbid][lhs->index] = TRUE;
			   }
			}
		     }
		  }	/* end of while */
	       } else
	       {
		  lhs = nonterm_array[thisrule->lhs->symbid][thisrule->lhs->index];
		  followset = followset | lhs->follow;
		  if (!needed_nonterm[lhs->symbid][lhs->index])
		  {
		     changed = TRUE;
		     needed_nonterm[lhs->symbid][lhs->index] = TRUE;
		  }
	       }
	       if (followset != oldfollowset)
	       {
		  changed = TRUE;
		  if (typeof(entry) == KTerminal)
		  {
		     term->follow = followset;
		     error_condition = followset & entry.VTerminal->occ;
		  } else
		  {
		     nonterm->follow = followset;
		  }
	       }	/* end of if (followset != oldfollowset) */
	    }	/* end of if goon */
	    if (error_condition)
	    {
	       break;
	    }
	 }	/* end of foreachinSEQVocabulary */
	 if (error_condition)
	 {
	    break;
	 }
      }	/* end of foreachinSEQRule */
      if (changed && !error_condition)
      {
	 complete = FALSE;
      } else
      {
	 complete = TRUE;
      }
   }	/* end of while */

}/* end of ComputeFollowSets */





/************************************************/
/* AnalyzeGrammar                */
/************************************************/

Boolean 
AnalyzeGrammar(grammar)
   Grammar grammar;
{
   Boolean glob_var = TRUE;

   (void) InitFirstSets(grammar);
   (void) ComputeFirstSets(grammar);

   (void) InitFollowSets(grammar);
   (void) ComputeFollowSets(grammar);

   glob_var = CheckDLStarCondition(grammar);

   return (glob_var);

}/* end of AnalyzeGrammar */





/************************************************/
/* VslCorrection                */
/************************************************/

void 
VslCorrection(vslseq, attr)
   SEQVSL vslseq;
   Attributes attr;
{
   SEQVSL X;
   VSL thisvsl;
   SEQAction Y;
   Action thisaction;
   Eval eval;
   SEQAttributes Z;
   Attributes thisparam;
   int latest_BnNF_visit_index, usecounter;

   latest_BnNF_visit_index = CompVisitIndex(vslseq, attr);
   foreachinSEQVSL(vslseq, X, thisvsl)
   {
      if (InSeqAttrs(thisvsl->def_attrs, attr->attrid))
      {
	 usecounter = CompUseCounter(thisvsl->actions, attr);
	 if (usecounter == NOT_USED)
	 {
	    (void) InsertNonBnNFOcc(thisvsl, attr, latest_BnNF_visit_index);
	 } else if (usecounter > 1)
	 {
	    (void) RemDoubleInstances(thisvsl->actions, attr, usecounter);
	 }
      }
      if (InSeqAttrs(thisvsl->app_attrs, attr->attrid))
      {
	 foreachinSEQAction(thisvsl->actions, Y, thisaction)
	    if (typeof(thisaction) == KEval)
	 {
	    eval = thisaction.VEval;
	    foreachinSEQAttributes(eval->params, Z, thisparam)
	       if (thisparam->attrid == attr->attrid)
	    {
	       removeSEQAttributes(eval->params, thisparam);
	    }
	 }
	 (void) InsertNonBnNFOcc(thisvsl, attr, latest_BnNF_visit_index);
      }
   }

}/* end of VslCorrection */





/************************************************/
/* NonBnNFCorrection              */
/************************************************/

void 
NonBnNFCorrection(vslseq)
   SEQVSL vslseq;
{
   SEQAttributes X, list_non_BnNF_attrs;
   Attributes thisattr;

   list_non_BnNF_attrs = GetNonBnNFAttrs(optimroot->vsl);
   foreachinSEQAttributes(list_non_BnNF_attrs, X, thisattr)
   {
      if (LastuseAlwaysBnNF(vslseq, thisattr))
      {
	 (void) RemNonBnNFUse(vslseq, thisattr);
      } else
      {
	 (void) VslCorrection(vslseq, thisattr);
      }
   }


}/* end of NonBnNFCorrection */





/************************************************/
/* GrammarLifetimeAnalysis          */
/************************************************/

void 
GrammarLifetimeAnalysis(attrlist)
   SEQAttributes attrlist;	/* list of multi-visit attributes */
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   VSL new_vslp;
   SEQAttributes Y;
   Attributes thisattr;
   Grammar grammar;
   Group group;
   Boolean glob_var = TRUE;


#ifdef LIFETIME
   /* printf("\n\n\n\n\n"); test_vs_out(); printf("\n\n\n\n\n"); */
#endif

  term_array= (a_Terminal*) 
               middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1)*sizeof(Terminal)*MAX_VISITS);
  nonterm_array = (a_Nonterminal*) 
                  middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1)*sizeof(Nonterminal)*MAX_VISITS);
  needed_nonterm = (a_Boolean*) 
                  middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1)*sizeof(Boolean)*MAX_VISITS);

   foreachinSEQVisit_Seq(optimroot->vi_seq, X, thisvs)
   {
      new_vslp = MkVslp(thisvs);
      appendrearSEQVSL(optimroot->vsl, new_vslp);
   }

   (void) NonBnNFCorrection(optimroot->vsl);

   optimroot->lt_grammar = MkLtGrammar();

   grammar = MkProjGrammar(optimroot->lt_grammar);

   foreachinSEQAttributes(attrlist, Y, thisattr)
   {
      if (thisattr->termattr)
      {	/* nothing to do */
      } else
      {
	 grammar = PrepareProjGrammar(optimroot->lt_grammar, grammar, thisattr->attrid);
	 glob_var = AnalyzeGrammar(grammar);

#ifdef LIFETIME
	 printf("\n\n\n\n\n GRAMMAR FOR ATTRIBUTE %s.%s : ", thisattr->sname, thisattr->aname);
	 /* print_grammar(grammar); to be provided */
#endif

	 if (glob_var)
	 {
	    if (group_all_option)
	    {
	       group = MkGroup(thisattr, STORGLVA);
	       vargroupcounter++;
	       removeSEQAttributes(attrlist, thisattr);
	       appendrearSEQGroup(optimroot->groups, group);
	    } else
	    {
	       appendrearSEQAttributes(optimroot->glob_var, thisattr);
	       removeSEQAttributes(attrlist, thisattr);
	    }
	    globvarcounter++;
	    treeattrcounter--;
	 }
      }
   }

}/* end of GrammarLifetimeAnalysis */
