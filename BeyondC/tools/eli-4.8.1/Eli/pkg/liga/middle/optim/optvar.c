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
static char rcs_id[] = "$Id: optvar.c,v 4.9 2002/09/30 15:25:55 uwe Exp peter $";

/************************************************/
/* Module  : optvar.c                     */
/* */
/* Contains the routines to decide        */
/* wheter an attribute is GLOB VAR,       */
/* GLOB STACK or TREE NODE                */
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
#include "optfct.h"
#include "optidl.h"

#include "optdid.h"

#include "printerr.h"
#include "chkbu.h"
#include "ligaconsts.h"
#include "optvar.h"
#include "list.h"

/************************************************/
/* defines                   */
/************************************************/

#define		SYNTLOWERCONTEXT	0
#define         SYNTUPPERCONTEXT        1
#define		INHLOWERCONTEXT		2
#define		INHUPPERCONTEXT		3

#define		MAX(a,b)	( (a) > (b) ? (a) : (b) )



/************************************************/
/* functions                  */
/************************************************/

int TermLifetimeBegin( /* Attributes, Visit_Seq, Prod */ );
int TermLifetimeEnd( /* Attributes, SEQAction */ );

Boolean IsTermSingleVisit( /* Visit_Sequences, Attributes */ );
Boolean IsTermGlobVar( /* Visit_Sequences, Attributes */ );

void InitCanEval( /* Visit_Seq, Can_Eval, int */ );
void HoistUp( /* Can_Eval, Can_Eval */ );
void ComputeCanEval( /* Visit_Sequences */ );

Boolean CheckGlobVarProperty( /* Visit_Seq, Attributes */ );
Boolean IsGlobVar( /* Attributes */ );

int GetLeaveIndex( /* Visit_Seq, int */ );
int LifetimeBegin( /* Attributes,Visit_Seq,Boolean,Boolean,int,int */ );
int GetDeathLeaveOrd( /* int, SEQAction */ );
int GetSpansVisitOrd( /* Attributes, int, SEQAction */ );

Boolean SpansLeave( /* Attributes, SEQAction */ );

void InhEvalDeath( /* Visit_Sequences, Attributes */ );
void LetDieByLeave( /* Visit_Sequences, Attributes, int */ );
void LetDieBehindVisit( /* Visit_Sequences, Attributes, int, Boolean */ );

void SyntLowerContextLifetime( /* Visit_Sequences,Attributes,int,Boolean */ );
void SyntUpperContextLifetime( /* Visit_Sequences,Attributes,int,Boolean */ );
void InhLowerContextLifetime( /* Visit_Sequences,Attributes,int,Boolean */ );
void InhUpperContextLifetime( /* Visit_Sequences,Attributes,int,Boolean */ );

Boolean IsSingleVisit( /* Visit_Sequences, Attributes */ );

void AnalyzeAttributes( /* Visit_Sequences */ );





/*************************************************************************/
/* TermLifetimeBegin                            */
/* */
/*************************************************************************/

int 
TermLifetimeBegin(attr, thisvs, prod)
   Attributes attr;
   Visit_Seq thisvs;
   Prod prod;
{
   SEQEntity X;
   Entity entity;
   SEQAction Y;
   Action thisaction;
   Def def;
   Visits visit;
   int symbid = attr->symbid, symbno = attr->symbno;
   int actioncounter = 0, entitycounter = 0, nontermid = -1, birth = -1;

   foreachinSEQEntity(prod->rhs, X, entity)
   {
      entitycounter++;
      if (entitycounter == symbno)
      {
	 break;
      } else
      {
	 if (typeof(entity.VUnit) == KSymbol)
	 {
	    def = lookup_def(entity.VUnit.VSymbol->did);
	    if (def.VSymb->tornt == SYMBNONT)
	    {
	       nontermid = entity.VUnit.VSymbol->did;
	    }
	 }
      }
   }
   if (nontermid == -1)
   {
      return (1);
   } else
   {
      foreachinSEQAction(thisvs->actions, Y, thisaction)
      {
	 actioncounter++;
	 if (typeof(thisaction) == KVisits)
	 {
	    visit = thisaction.VVisits;
	    if (visit->symbid == symbid)
	    {
	       birth = actioncounter;
	       break;
	    }
	 }
      }
      if (birth == -1)
      {
	 char errmsgbuff[ERR_BUFF_LEN];
	 err_setpos(0, 0);
	 sprintf(errmsgbuff,
		 "no lifetimebegin for Attr. %s[%d].%s in Prod. %s found !",
		 attr->sname, symbno, attr->aname, prod->dname);
	 err_print_error(errmsgbuff);
	 fprintf(ProtocolFile, "*** ERROR: no lifetimebegin for Attr. ");
	 fprintf(ProtocolFile, "%s[%d].%s ", attr->sname, symbno, attr->aname);
	 fprintf(ProtocolFile, "in Prod. %s found !\n", prod->dname);
	 exit(5);
         return 0;
      } else
      {
	 return (birth);
      }
   }

}/* end of TermLifetimeBegin */





/*************************************************************************/
/* TermLifetimeEnd                              */
/* */
/*************************************************************************/

int 
TermLifetimeEnd(attr, thisvs)
   Attributes attr;
   Visit_Seq thisvs;
{
   SEQAction X, actionseq = thisvs->actions;
   Action thisaction;
   Eval eval;
   SEQAttributes Y;
   Attributes thisparam;
   Def def;
   int i, death = -1, actioncounter = attr->birth;
   int attrid = attr->attrid, symbno = attr->symbno;

   for (i = 0; i < attr->birth; i++)
      actionseq = tailSEQAction(actionseq);
   foreachinSEQAction(actionseq, X, thisaction)
   {
      actioncounter++;
      if (typeof(thisaction) == KEval)
      {
	 eval = thisaction.VEval;
	 foreachinSEQAttributes(eval->params, Y, thisparam)
	    if (thisparam->attrid == attrid && thisparam->symbno == symbno)
	    death = actioncounter;
      }
   }
   if (death == -1)
   {
      char errmsgbuff[ERR_BUFF_LEN];

      def = lookup_def(thisvs->prodid);
      err_setpos(def.VProd->row, def.VProd->col);
      sprintf(errmsgbuff,
	      "no lifetimeend for Attr. %s[%d].%s in Prod. %s found",
	      attr->sname, symbno, attr->aname, def.VProd->dname);
      err_print_error(errmsgbuff);
      fprintf(ProtocolFile, "*** ERROR: no lifetimeend for Attr. ");
      fprintf(ProtocolFile, "%s[%d].%s ", attr->sname, symbno, attr->aname);
      fprintf(ProtocolFile, "in Prod. %s found !\n", def.VProd->dname);
      exit(5);
      return 0;
   } else
   {
      return (death);
   }


}/* end of TermLifetimeEnd */





/*************************************************************************/
/* IsTermSingleVisit                            */
/* */
/*************************************************************************/

Boolean 
IsTermSingleVisit(root, attr)
   Visit_Sequences root;
   Attributes attr;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   Def def;
   SEQAttributes Y;
   Attributes thisattr;
   Action action;
   int attrid = attr->attrid;
   Boolean multivisit = FALSE;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      foreachinSEQAttributes(thisvs->attrs, Y, thisattr)
      {
	 if (thisattr->attrid == attrid)
	 {
	    thisattr->birth = TermLifetimeBegin(thisattr, thisvs, def.VProd);
	    thisattr->death = TermLifetimeEnd(thisattr, thisvs);
	    multivisit = SpansLeave(thisattr, thisvs->actions);
	    ithinSEQAction(thisvs->actions, thisattr->birth, action);
	    appendrearSEQAttributes(action.IDLclassCommon->birth, thisattr);
	    ithinSEQAction(thisvs->actions, thisattr->death, action);
	    appendrearSEQAttributes(action.IDLclassCommon->obituary, thisattr);
	 }
	 if (multivisit)
	 {
	    break;
	 }
      }
      if (multivisit)
      {
	 break;
      }
   }

   return (!multivisit);

}/* end of IsTermSingleVisit */





/*************************************************************************/
/* IsTermGlobVar                              */
/* */
/*************************************************************************/

Boolean 
IsTermGlobVar(root, attr)
   Visit_Sequences root;
   Attributes attr;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   SEQAttributes Y;
   Attributes thisattr;
   SEQAction Z, actionseq;
   Action action;
   int i, actioncounter;
   int attrid = attr->attrid;
   Boolean globvar = TRUE;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      foreachinSEQAttributes(thisvs->attrs, Y, thisattr)
      {
	 if (thisattr->attrid == attrid)
	 {
	    ithinSEQAction(thisvs->actions, thisattr->birth, action);
	    if (lengthSEQAttributes(action.IDLclassCommon->birth) != 1)
	    {
	       globvar = FALSE;
	    }
	    actionseq = thisvs->actions;
	    for (i = 0; i < thisattr->birth; i++)
	    {
	       actionseq = tailSEQAction(actionseq);
	    }
	    actioncounter = thisattr->birth;
	    foreachinSEQAction(actionseq, Z, action)
	    {
	       if (typeof(action) == KEval)
	       {
		  if (action.VEval->attrid == attrid)
		  {
		     globvar = FALSE;
		  }
	       }
	       if (++actioncounter >= thisattr->death)
	       {
		  break;
	       }
	    }
	 }
	 if (!globvar)
	 {
	    break;
	 }
      }
      if (!globvar)
      {
	 break;
      }
   }

   return (globvar);

}/* end of IsTermGlobVar */





/************************************************/
/* InitCanEval                  */
/************************************************/

void 
InitCanEval(thisvs, thisCE, v)
   Visit_Seq thisvs;
   Can_Eval thisCE;
   int v;
{
   SEQAction X, actionseq = thisvs->actions;
   Action thisaction;
   Visits visit;
   Marked mark;
   Boolean leave_v_found = FALSE;
   int i, index;

   index = GetLeaveIndex(thisvs, v);
   for (i = 0; i < index; i++)
      actionseq = tailSEQAction(actionseq);
   foreachinSEQAction(actionseq, X, thisaction)
   {
      switch (typeof(thisaction))
      {
      case KEval:
	 if (!eval_considered[thisaction.VEval->attrid])
	 {  eval_considered[thisaction.VEval->attrid] = TRUE;
	    appendrearSEQAction(thisCE->actions, thisaction);
	 }
	 break;
      case KVisits:
	 if (thisaction.VVisits->symbno == LEAVE)
	 {
	    leave_v_found = TRUE;
	 } else
	 {
	    visit = thisaction.VVisits;
	    if (!visit_considered[visit->symbid][visit->ord])
	    {
	       visit_considered[visit->symbid][visit->ord] = TRUE;
	       mark = NMarked;
	       mark->symbid = thisaction.VVisits->symbid;
	       mark->ord = thisaction.VVisits->ord;
	       if (thisaction.VVisits->symbid == ParentId(thisvs) &&
		   thisaction.VVisits->ord == v)
	       {
		  mark->flag = TRUE;
	       } else
	       {
		  mark->flag = FALSE;
	       }
	       appendrearSEQMarked(thisCE->marks, mark);
	       appendrearSEQAction(thisCE->actions, thisaction);
	    }
	 }
	 break;
      default:
	 break;
      }	/* end of switch */
      if (leave_v_found)
      {
	 break;
      }
   }

}/* end of InitCanEval */





/******************************************************************/
/* HoistUp                             */
/* */
/* */
/******************************************************************/

void 
HoistUp(targetCE, sourceCE)
   Can_Eval targetCE, sourceCE;
{
   SEQAction X;
   Action thisaction;
   Visits visit;
   Marked mark;
   Can_Eval newsourceCE;

   foreachinSEQAction(sourceCE->actions, X, thisaction)
      switch (typeof(thisaction))
   {
   case KEval:
      if (!eval_considered[thisaction.VEval->attrid])
      {
	 eval_considered[thisaction.VEval->attrid] = TRUE;
	 appendrearSEQAction(targetCE->actions, thisaction);
      }
      break;
   case KVisits:
      visit = thisaction.VVisits;
      if (!visit_considered[visit->symbid][visit->ord])
      {
	 visit_considered[visit->symbid][visit->ord] = TRUE;
	 appendrearSEQAction(targetCE->actions, thisaction);
	 mark = NMarked;
	 mark->symbid = visit->symbid;
	 mark->ord = visit->ord,
	    mark->flag = TRUE;
	 appendrearSEQMarked(targetCE->marks, mark);
	 mark_array[visit->symbid][visit->ord] = mark;
	 newsourceCE = LookupCE(visit->symbid, visit->ord);
	 (void) HoistUp(targetCE, newsourceCE);
      } else
      {
	 mark = LookupMark(visit->symbid, visit->ord);
	 if (!mark->flag)
	 {
	    mark->flag = TRUE;
	    newsourceCE = LookupCE(visit->symbid, visit->ord);
	    (void) HoistUp(targetCE, newsourceCE);
	 }
      }
      break;
   default:
      break;
   }	/* end of switch */

}/* end of HoistUp */





/************************************************/
/* ComputeCanEval                 */
/************************************************/

void 
ComputeCanEval(root)
   Visit_Sequences root;
/* on exit: X.a is element of SEQCan_Eval[S,v], iff X.a can be evaluated   */
/* during visit v to symbol S.                                    */
{
   SEQSymbols X;
   Symbols thissymb;
   SEQVisit_Seq Y;
   Visit_Seq thisvs;
   SEQCan_Eval Z;
   Can_Eval thisCE, sourceCE;
   SEQAction A;
   Action thisaction;
   Visits visit;
   Marked mark;
   int i;

   (void) InitLookupArrays();
   foreachinSEQSymbols(optimroot->symbs, X, thissymb)
   {

      for (i = 1; i <= thissymb->parts; i++)
      {
	 foreachinSEQVisit_Seq(root->vi_seq, Y, thisvs)
	 {
	    if (ParentId(thisvs) == thissymb->symbid)
	    {
	       thisCE = LookupCE(thissymb->symbid, i);
	       if (thisCE == NULL)
	       {
		  thisCE = MkCanEval(thissymb->symbid, i);
	       }
	       (void) InitCanEval(thisvs, thisCE, i);
	       CE_array[thissymb->symbid][i] = thisCE;
	    }
	 }
	 appendrearSEQCan_Eval(root->caneval, thisCE);
	 (void) ResetEvalVisit(thisCE);
      }
   }
   foreachinSEQCan_Eval(root->caneval, Z, thisCE)
   {
      (void) InitEvalVisit(thisCE);
      (void) InitMarkArray(thisCE);
      foreachinSEQAction(thisCE->actions, A, thisaction)
      {
	 if (typeof(thisaction) == KVisits)
	 {
	    visit = thisaction.VVisits;
	    mark = LookupMark(visit->symbid, visit->ord);
	    if (!mark->flag)
	    {
	       mark->flag = TRUE;
	       sourceCE = LookupCE(visit->symbid, visit->ord);
	       (void) HoistUp(thisCE, sourceCE);
	    }
	 }
      }
      (void) ResetEvalVisit(thisCE);
      (void) ResetMarkArray(thisCE);
   }

}/* end of ComputeCanEval */





/************************************************/
/* CheckGlobVarProperty              */
/************************************************/

Boolean 
CheckGlobVarProperty(thisvs, thisattr)
   Visit_Seq thisvs;
   Attributes thisattr;
{
   SEQAction X, actionseq = thisvs->actions;
   Action thisaction;
   Can_Eval thisCE;
   Eval eval;
   int i, action_counter = thisattr->birth;

   for (i = 0; i < thisattr->birth; i++)
   {
      actionseq = tailSEQAction(actionseq);
   }
   foreachinSEQAction(actionseq, X, thisaction)
   {
      if (++action_counter >= thisattr->death)
      {
	 break;
      }
      /* consider each action within the delimited lifetime   */
      switch (typeof(thisaction))
      {
	 /* if the action can evaluate another X.a, then X.a cannot be	 */
	 /* a global variable						 */
      case KEval:
	 if (thisaction.VEval->attrid == thisattr->attrid)
	    return (FALSE);
	 break;
      case KVisits:
	 /* possible only if X is parent. will be checked in upper	 */
	 /* production if another X.a overlaps this one.		 */
	 if (thisaction.VVisits->symbno)
	 {
	    thisCE = LookupCE(thisaction.VVisits->symbid, thisaction.VVisits->ord);
	    if (thisCE == NULL)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];

	       err_setpos(0, 0);
	       sprintf(errmsgbuff, "no CAN_EVAL set found for CAN_EVAL [ %d, %d ]",
		       thisaction.VVisits->symbid, thisaction.VVisits->ord);
	       err_print_error(errmsgbuff);
	       fprintf(ProtocolFile,
	       "*** ERROR: no CAN_EVAL set found for CAN_EVAL [ %d, %d ] \n",
		       thisaction.VVisits->symbid, thisaction.VVisits->ord);
	       break;
	    }
	    eval = NEval;
	    eval->attrid = thisattr->attrid;
	    IDLtempAction.VEval = eval;
	    if (InSeqAction(thisCE->actions, IDLtempAction))
	       return (FALSE);
	 }
	 break;
      default:
	 break;
      }	/* end of switch */
   }	/* end of for */

   return (TRUE);

}/* end of CheckGlobVarProperty */





/************************************************/
/* IsGlobVar                 */
/************************************************/

Boolean 
IsGlobVar(thisattr)
   Attributes thisattr;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   SEQAttributes Y;
   Attributes vsattr;

   /* find those single visit attributes with overlapping lifetime   */
   foreachinSEQVisit_Seq(optimroot->vi_seq, X, thisvs)
   /* consider each production with an occurence of this_sv_attr   */
      foreachinSEQAttributes(thisvs->attrs, Y, vsattr)
      if ((vsattr->attrid == thisattr->attrid)
	  && (!CheckGlobVarProperty(thisvs, vsattr)))
      return (FALSE);

   return (TRUE);
}/* IsGlobVar */





/*************************************************************************/
/* GetLeaveIndex                              */
/* */
/*************************************************************************/

int 
GetLeaveIndex(thisvs, v)
   Visit_Seq thisvs;
   int v;
{
   int counter = 0;
   SEQAction X;
   Action action;

   foreachinSEQAction(thisvs->actions, X, action)
   {
      counter++;
      if (typeof(action) == KVisits)
	 if (action.VVisits->symbno == LEAVE && action.VVisits->ord == v - 1)
	    return (counter);
   }
   return 0; /* should not occur */
}/* end of GetLeaveIndex */





/*************************************************************************/
/* LifetimeBegin                              */
/* */
/* determines the index of the lifetimebegin of attr in thisvs and     */
/* returns it; if attr is used also in thisvs, sets appfound and       */
/* used to TRUE, usedindex to actioncounter where attr is used         */
/*************************************************************************/

int 
LifetimeBegin(attr, thisvs, appoccfound, usedindex, key)
   Attributes attr;
   Visit_Seq thisvs;
   Boolean *appoccfound;
   int *usedindex, key;
{
   SEQAction X;
   Action thisaction;
   Def def;
   Eval eval;
   Visits visit;
   int evalbirth = -1, visitbirth = -1, actioncounter = 0;
   int attrid = attr->attrid, symbno = attr->symbno;
   Boolean evaluated = FALSE;

   foreachinSEQAction(thisvs->actions, X, thisaction)
   {
      actioncounter++;
      switch (typeof(thisaction))
      {
      case KEval:
	 eval = thisaction.VEval;
	 if (eval->attrid == attrid && eval->symbno == symbno)
	 {
	    evaluated = TRUE;
	    evalbirth = actioncounter;
	 } else if (AttrInstanceInSet(attrid, symbno, eval->params))
	 {
	    *usedindex = actioncounter;
	    *appoccfound = TRUE;
	 }
	 break;
      case KVisits:
	 visit = thisaction.VVisits;
	 if (key == SYNTUPPERCONTEXT)
	 {
	    if (visit->symbno == symbno && visit->ord == attr->part)
	    {
	       visitbirth = actioncounter;
	    }
	 } else if (key == INHLOWERCONTEXT)
	 {
	    if (visit->symbno == LEAVE && visit->ord == attr->part - 1)
	    {
	       visitbirth = actioncounter;
	    }
	 }
	 break;
      default:
	 break;
      }	/* end of switch */
   }

   if (key == SYNTLOWERCONTEXT || key == INHUPPERCONTEXT)
   {
      if (!evaluated)
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 def = lookup_def(thisvs->prodid);
	 err_setpos(def.VProd->row, def.VProd->col);
	 sprintf(errmsgbuff, "attribute %s[%d].%s in Prod. %s is not evaluated",
		 attr->sname, symbno, attr->aname, def.VProd->dname);
	 err_print_error(errmsgbuff);
	 fprintf(ProtocolFile, "*** ERROR: attribute %s[%d].%s in Prod. %s is not evaluated\n",
		 attr->sname, symbno, attr->aname, def.VProd->dname);
	 exit(5);
      } else
      {
	 return (evalbirth);
      }
   }
   if (key == SYNTUPPERCONTEXT || key == INHLOWERCONTEXT)
   {
      if (visitbirth == -1)
      {
	 char errmsgbuff[ERR_BUFF_LEN];

	 def = lookup_def(thisvs->prodid);
	 err_setpos(def.VProd->row, def.VProd->col);
	 sprintf(errmsgbuff, "attribute %s[%d].%s in Prod. %s is not evaluated",
		 attr->sname, symbno, attr->aname, def.VProd->dname);
	 err_print_error(errmsgbuff);

	 fprintf(ProtocolFile, "*** ERROR: attribute %s[%d].%s in Prod. %s is not evaluated\n",
		 attr->sname, symbno, attr->aname, def.VProd->dname);
	 exit(5);
      } else
      {
	 return (visitbirth);
      }
   }
   return 0; /* should not occur */
}/* end of LifetimeBegin */





/*************************************************************************/
/* GetDeathLeaveOrd                           */
/* */
/* returns the next leave ord which ends a lifetime            */
/*************************************************************************/

int 
GetDeathLeaveOrd(birth, actionseq)
   int birth;
   SEQAction actionseq;
{
   SEQAction X;
   Action thisaction;
   Visits visit;
   int i, actioncounter = birth, ord = -1;

   for (i = 0; i < birth; i++)
   {
      actionseq = tailSEQAction(actionseq);
   }
   foreachinSEQAction(actionseq, X, thisaction)
   {
      actioncounter++;
      if (typeof(thisaction) == KVisits)
      {
	 visit = thisaction.VVisits;
	 if (visit->symbno == LEAVE)
	 {
	    ord = visit->ord;
	    break;
	 }
      }
   }

   if (ord == -1)
   {
      err_setpos(0, 0);
      err_print_error("no death leave ord found !");
      fprintf(ProtocolFile, "*** ERROR: no death leave ord found ! \n");
      exit(5);
   } else
   {
      return (ord);
   }

}/* end of GetDeathLeaveOrd */





/*************************************************************************/
/* GetSpansVisitOrd                           */
/* */
/* returns the ord of a spanned visit if such an visit exist       */
/*************************************************************************/

int 
GetSpansVisitOrd(attr, death, actionseq)
   Attributes attr;
   int death;
   SEQAction actionseq;
{
   SEQAction X;
   Action thisaction;
   Visits visit;
   int i, actioncounter = attr->birth, ord = -1;

   for (i = 0; i < attr->birth; i++)
   {
      actionseq = tailSEQAction(actionseq);
   }
   foreachinSEQAction(actionseq, X, thisaction)
   {
      if (++actioncounter >= death)
      {
	 break;
      }
      if (typeof(thisaction) == KVisits)
      {
	 visit = thisaction.VVisits;
	 if (visit->symbno == attr->symbno)
	 {
	    ord = visit->ord;
	 }
      }
   }

   return (ord);

}/* end of GetSpansVisitOrd */





/************************************************************************/
/* SpansLeave				 */
/* */
/* checks whether the lifetime of attr spans a leave		 */
/************************************************************************/

Boolean 
SpansLeave(attr, actionseq)
   Attributes attr;
   SEQAction actionseq;
{
   SEQAction X;
   Action thisaction;
   Visits visit;
   int i, birth = attr->birth, death = attr->death, actioncounter = attr->birth;

   for (i = 0; i < birth; i++)
      actionseq = tailSEQAction(actionseq);
   foreachinSEQAction(actionseq, X, thisaction)
   {
      if (++actioncounter >= death)
	 return (FALSE);
      if (typeof(thisaction) == KVisits)
      {
	 visit = thisaction.VVisits;
	 if (visit->symbno == LEAVE)
	    return (TRUE);
      }
   }

   return (FALSE);

}/* end of SpansLeave */





/*************************************************************************/
/* InhEvalDeath                             */
/* */
/* determines lifetimeend of attr in upper contexts by an eval      */
/*************************************************************************/

void 
InhEvalDeath(root, attr)
   Visit_Sequences root;
   Attributes attr;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   Def def;
   Attributes thisattr;
   SEQAction Y;
   Action thisaction;
   Eval eval;
   Visits visit;
   int attrid = attr->attrid, symbid = attr->symbid;
   int actioncounter, leavedeath = -1;
   Boolean appoccfound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      if (def.VProd->lhs == symbid)
      {
	 thisattr = GetAttrInstance(attrid, 0, thisvs->attrs);
	 appoccfound = FALSE;
	 leavedeath = -1;
	 actioncounter = 0;
	 foreachinSEQAction(thisvs->actions, Y, thisaction)
	 {
	    actioncounter++;
	    switch (typeof(thisaction))
	    {
	    case KEval:
	       eval = thisaction.VEval;
	       if (AttrInstanceInSet(attrid, 0, eval->params))
	       {
		  appoccfound = TRUE;
		  thisattr->death = actioncounter;
	       }
	       break;
	    case KVisits:
	       visit = thisaction.VVisits;
	       if (visit->symbno == LEAVE && visit->ord == attr->part - 1)
	       {
		  leavedeath = actioncounter;
		  break;
	       }
	       break;
	    default:
	       break;
	    }	/* end of switch */
	 }
	 if (!appoccfound)
	 {
	    if (leavedeath == -1)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];

	       def = lookup_def(thisvs->prodid);
	       err_setpos(def.VProd->row, def.VProd->col);
	       sprintf(errmsgbuff,
		       "no lifetimeend for Attr. %s[0].%s in Prod. %s found",
		       attr->sname, attr->aname, def.VProd->dname);
	       err_print_error(errmsgbuff);
	       fprintf(ProtocolFile, "*** ERROR: no lifetimeend for Attr. %s[0].%s in Prod. %s found !\n",
		       attr->sname, attr->aname, def.VProd->dname);
	       exit(5);
	    } else
	    {
	       thisattr->death = leavedeath;
	    }
	 }
      }
   }

}/* end of InhEvalDeath */





/*************************************************************************/
/* LetDieByLeave                            */
/* */
/* determines lifetimeend of attr in lower contexts by a leave      */
/*************************************************************************/

void 
LetDieByLeave(root, attr, ord)
   Visit_Sequences root;
   Attributes attr;
   int ord;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   Def def;
   Attributes thisattr;
   SEQAction Y;
   Action thisaction;
   Visits visit;
   int attrid = attr->attrid, symbid = attr->symbid, actioncounter;
   Boolean deathleavefound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      if (def.VProd->lhs == symbid)
      {
	 thisattr = GetAttrInstance(attrid, 0, thisvs->attrs);
	 actioncounter = 0;
	 deathleavefound = FALSE;
	 foreachinSEQAction(thisvs->actions, Y, thisaction)
	 {
	    actioncounter++;
	    if (typeof(thisaction) == KVisits)
	    {
	       visit = thisaction.VVisits;
	       if (visit->symbno == LEAVE && visit->ord == ord)
	       {
		  deathleavefound = TRUE;
		  thisattr->death = actioncounter;
		  break;
	       }
	    }
	 }
	 if (!deathleavefound)
	 {
	    char errmsgbuff[ERR_BUFF_LEN];

	    err_setpos(def.VProd->row, def.VProd->col);
	    sprintf(errmsgbuff,
		    "no lifetimeend for Attr. %s[0].%s in Prod. %s found",
		    attr->sname, attr->aname, def.VProd->dname);
	    err_print_error(errmsgbuff);

	    fprintf(ProtocolFile,
		    "*** ERROR: no lifetimeend for Attr. %s[0].%s in Prod. %s found !\n",
		    attr->sname, attr->aname, def.VProd->dname);
	    exit(5);
	 }
      }
   }

}/* end of LetDieByLeave */





/*************************************************************************/
/* LetDieBehindVisit                          */
/* */
/* determines lifetimeend of attr in upper contexts behind a visit with */
/* ord-counter equal 'ord'                                              */
/*************************************************************************/

void 
LetDieBehindVisit(root, attr, ord, singlevisit)
   Visit_Sequences root;
   Attributes attr;
   int ord;
   Boolean *singlevisit;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   SEQSymbols Y;
   Symbols thissymb;
   Attributes thisattr;
   SEQAction Z;
   Action thisaction;
   Eval eval;
   Visits visit;
   Def def;
   int attrid = attr->attrid, symbid = attr->symbid;
   int symbno, actioncounter, evaldeath, visitdeath;
   Boolean multivisit = FALSE;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      foreachinSEQSymbols(thisvs->symbs, Y, thissymb)
      {
	 symbno = thissymb->symbno;
	 if (thissymb->symbid == symbid && symbno != 0)
	 {
	    thisattr = GetAttrInstance(attrid, symbno, thisvs->attrs);
	    actioncounter = 0;
	    evaldeath = visitdeath = -1;
	    foreachinSEQAction(thisvs->actions, Z, thisaction)
	    {
	       actioncounter++;
	       switch (typeof(thisaction))
	       {
	       case KEval:
		  eval = thisaction.VEval;
		  if (AttrInstanceInSet(attrid, symbno, eval->params))
		  {
		     evaldeath = actioncounter;
		  }
		  break;
	       case KVisits:
		  visit = thisaction.VVisits;
		  if (visit->symbno == symbno && visit->ord == ord)
		  {
		     visitdeath = actioncounter;
		  }
		  break;
	       default:
		  break;
	       }	/* end of switch */
	    }
	    if (evaldeath == -1 && visitdeath == -1)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];

	       def = lookup_def(thisvs->prodid);
	       err_setpos(def.VProd->row, def.VProd->col);
	       sprintf(errmsgbuff,
		     "no lifetimeend for Attr. %s[%d].%s in Prod. %s found",
		       attr->sname, symbno, attr->aname, def.VProd->dname);
	       err_print_error(errmsgbuff);

	       fprintf(ProtocolFile, "*** ERROR: no lifetimeend for Attr. %s[%d].%s in Prod. %s found !\n",
		       attr->sname, symbno, attr->aname, def.VProd->dname);
	       exit(5);
	    }
	    if (evaldeath > visitdeath)
	    {
	       thisattr->death = evaldeath;
	    } else
	    {
	       thisattr->death = visitdeath;
	    }
	    multivisit = SpansLeave(thisattr, thisvs->actions);
	    if (multivisit)
	    {
	       *singlevisit = FALSE;
	       break;
	    }
	 }
      }
      if (multivisit)
      {
	 break;
      }
   }

}/* end of LetDieBehindVisit */





/*************************************************************************/
/* SyntLowerContextLifetime                      */
/* */
/* determines lifetimebegin of attr in lower contexts, determines also  */
/* the latest leaveord where an instance of attr dies                   */
/*************************************************************************/

void 
SyntLowerContextLifetime(root, attr, deathleaveord, used)
   Visit_Sequences root;
   Attributes attr;
   int *deathleaveord;
   Boolean *used;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   Def def;
   Attributes thisattr;
   int attrid = attr->attrid, symbid = attr->symbid;
   int usedindex, ord = -1, maxord = -1;
   Boolean appoccfound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      if (def.VProd->lhs == symbid)
      {	/* lower context of attr. found */
	 thisattr = GetAttrInstance(attrid, 0, thisvs->attrs);
	 if (thisattr == NULL)
	 {
	    char errmsgbuff[ERR_BUFF_LEN];

	    err_setpos(def.VProd->row, def.VProd->col);
	    sprintf(errmsgbuff,
		    "attribute %s[0].%s in Prod. %s is not evaluated.",
		    attr->sname, attr->aname, def.VProd->dname);
	    err_print_error(errmsgbuff);
	    fprintf(ProtocolFile, "*** ERROR: attribute %s[0].%s in Prod. %s is not evaluated",
		    attr->sname, attr->aname, def.VProd->dname);
	    exit(5);
	 }
	 appoccfound = FALSE;
	 usedindex = -1;
	 thisattr->birth = LifetimeBegin(thisattr,
					 thisvs,
					 &appoccfound,
					 &usedindex,
					 SYNTLOWERCONTEXT);
	 if (appoccfound)
	 {
	    ord = GetDeathLeaveOrd(usedindex, thisvs->actions);
	    *used = TRUE;
	 } else
	 {
	    ord = GetDeathLeaveOrd(thisattr->birth, thisvs->actions);
	 }
	 maxord = MAX(ord, maxord);
      }
   }

   if (maxord != -1)
   {
      *deathleaveord = maxord;
   }
}/* end of SyntLowerContextLifetime */





/*************************************************************************/
/* SyntUpperContextLifetime                      */
/* */
/* determines lifetimebegin of attr in upper contexts, determines also  */
/* the latest spanning visitord if one such exist                       */
/*************************************************************************/

void 
SyntUpperContextLifetime(root, attr, spanvisitord, used)
   Visit_Sequences root;
   Attributes attr;
   int *spanvisitord;
   Boolean *used;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   SEQSymbols Y;
   Symbols thissymb;
   Def def;
   Attrdef attrdef;
   Attributes thisattr;
   int attrid = attr->attrid, symbid = attr->symbid;
   int symbno, usedindex, ord = -1, maxord = -1;
   Boolean artificialocc, appoccfound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      foreachinSEQSymbols(thisvs->symbs, Y, thissymb)
      {
	 symbno = thissymb->symbno;
	 if (thissymb->symbid == symbid && symbno != 0)
	 {
	    artificialocc = FALSE;
	    thisattr = GetAttrInstance(attrid, symbno, thisvs->attrs);
	    if (thisattr == NULL)
	    {
	       artificialocc = TRUE;
	       def = lookup_def(symbid);
	       attrdef = lookup_attrdef(attrid);
	       thisattr = MkAttribute(attrdef, def.VSymb);
	       thisattr->symbno = symbno;
	    }
	    appoccfound = FALSE;
	    usedindex = -1;
	    thisattr->birth = LifetimeBegin(thisattr,
					    thisvs,
					    &appoccfound,
					    &usedindex,
					    SYNTUPPERCONTEXT);
	    if (appoccfound)
	    {
	       ord = GetSpansVisitOrd(thisattr, usedindex, thisvs->actions);
	       *used = TRUE;
	       maxord = MAX(ord, maxord);
	    }
	    if (artificialocc)
	    {
	       appendrearSEQAttributes(thisvs->attrs, thisattr);
	    }
	 }
      }
   }

   if (maxord != -1)
   {
      *spanvisitord = maxord;
   }
}/* end of SyntUpperContextLifetime */





/*************************************************************************/
/* InhLowerContextLifetime                      */
/* */
/* determines lifetimebegin of attr in lower contexts, determines also  */
/* the latest leaveord where an instance of attr possibly dies          */
/*************************************************************************/

void 
InhLowerContextLifetime(root, attr, latestdeathleave, used)
   Visit_Sequences root;
   Attributes attr;
   int *latestdeathleave;
   Boolean *used;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   Def def;
   Attrdef attrdef;
   Attributes thisattr;
   int attrid = attr->attrid, symbid = attr->symbid;
   int usedindex, ord = -1, maxord = -1;
   Boolean artificialocc, appoccfound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      def = lookup_def(thisvs->prodid);
      if (def.VProd->lhs == symbid)
      {	/* lower context of attr. found */
	 artificialocc = FALSE;
	 thisattr = GetAttrInstance(attrid, 0, thisvs->attrs);
	 if (thisattr == NULL)
	 {
	    artificialocc = TRUE;
	    def = lookup_def(symbid);
	    attrdef = lookup_attrdef(attrid);
	    thisattr = MkAttribute(attrdef, def.VSymb);
	    thisattr->symbno = 0;
	 }
	 appoccfound = FALSE;
	 usedindex = -1;
	 thisattr->birth = LifetimeBegin(thisattr,
					 thisvs,
					 &appoccfound,
					 &usedindex,
					 INHLOWERCONTEXT);
	 if (appoccfound)
	 {
	    ord = GetDeathLeaveOrd(usedindex, thisvs->actions);
	    *used = TRUE;
	 } else
	 {
	    ord = GetDeathLeaveOrd(thisattr->birth - 1, thisvs->actions);
	 }
	 maxord = MAX(ord, maxord);
	 if (artificialocc)
	 {
	    appendrearSEQAttributes(thisvs->attrs, thisattr);
	 }
      }
   }

   if (maxord != -1)
   {
      *latestdeathleave = maxord;
   }
}/* end of InhLowerContextLifetime */





/*************************************************************************/
/* InhUpperContextLifetime                      */
/* */
/* determines lifetimebegin of attr in upper contexts, determines also  */
/* the latest spanning visitord if such one exist                       */
/*************************************************************************/

void 
InhUpperContextLifetime(root, attr, latestspanvisit, used)
   Visit_Sequences root;
   Attributes attr;
   int *latestspanvisit;
   Boolean *used;
{
   SEQVisit_Seq X;
   Visit_Seq thisvs;
   SEQSymbols Y;
   Symbols thissymb;
   Attributes thisattr;
   Def def;
   int attrid = attr->attrid, symbid = attr->symbid;
   int symbno, usedindex, ord = -1, maxord = -1;
   Boolean appoccfound;

   foreachinSEQVisit_Seq(root->vi_seq, X, thisvs)
   {
      foreachinSEQSymbols(thisvs->symbs, Y, thissymb)
      {
	 symbno = thissymb->symbno;
	 if (thissymb->symbid == symbid && symbno != 0)
	 {
	    thisattr = GetAttrInstance(attrid, symbno, thisvs->attrs);
	    if (thisattr == NULL)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];

	       def = lookup_def(thisvs->prodid);
	       err_setpos(def.VProd->row, def.VProd->col);
	       sprintf(errmsgbuff, "attribute %s[%d].%s in Prod. %s is not evaluated",
		       attr->sname, symbno, attr->aname, def.VProd->dname);
	       err_print_error(errmsgbuff);
	       fprintf(ProtocolFile, "*** ERROR: attribute %s[%d].%s in Prod. %s is not evaluated\n",
		       attr->sname, symbno, attr->aname, def.VProd->dname);
	       exit(5);
	    }
	    appoccfound = FALSE;
	    usedindex = -1;
	    thisattr->birth = LifetimeBegin(thisattr,
					    thisvs,
					    &appoccfound,
					    &usedindex,
					    INHUPPERCONTEXT);
	    if (appoccfound)
	    {
	       ord = GetSpansVisitOrd(thisattr, usedindex, thisvs->actions);
	       *used = TRUE;
	       maxord = MAX(ord, maxord);
	    }
	 }
      }
   }

   if (maxord != -1)
   {
      *latestspanvisit = maxord;
   }
}/* end of InhUpperContextLifetime */





/*************************************************************************/
/* IsSingleVisit                             */
/* */
/* determines wheter attr satifies the single visit property      */
/*************************************************************************/

Boolean 
IsSingleVisit(root, attr)
   Visit_Sequences root;
   Attributes attr;
{
   int deathord = -1, latestspanvisit = -1, latestleavedeath = attr->part;
   Boolean used = FALSE, singlevisit = TRUE;

   switch (attr->class)
   {
   case ATCLSYNT:
      (void) SyntLowerContextLifetime(root, attr, &latestleavedeath, &used);
      (void) SyntUpperContextLifetime(root, attr, &latestspanvisit, &used);
      deathord = MAX(latestleavedeath, latestspanvisit);
      (void) LetDieByLeave(root, attr, deathord);
      (void) LetDieBehindVisit(root, attr, deathord, &singlevisit);
      break;
   case ATCLINH:
      (void) InhLowerContextLifetime(root, attr, &latestleavedeath, &used);
      (void) InhUpperContextLifetime(root, attr, &latestspanvisit, &used);
      if (!used)
      {
	 latestleavedeath = attr->part;
      }
      if (latestspanvisit == -1 && latestleavedeath == attr->part)
      {
	 (void) InhEvalDeath(root, attr);
	 (void) LetDieBehindVisit(root, attr, latestleavedeath, &singlevisit);
      } else
      {	/* attr is not in BnNF because latest using in upper context */
	 attr->BnNF = FALSE;
	 deathord = MAX(latestleavedeath, latestspanvisit);
	 /* deathord may be 0 if there is no lower use, 
            and an upper use is before the first visit to the symbol.
	    That must be excluded because LetDieBehindVisit can not
	    refer to a visit (to a subtree) of ord 0. Hence deathord >= 1:
	 */
	 deathord = MAX(deathord, 1); /* UK changed */
	 (void) LetDieByLeave(root, attr, deathord);
	 (void) LetDieBehindVisit(root, attr, deathord, &singlevisit);
      }
      break;
   default:
      break;
   }

   if (!used)
   {
      attr->not_used = TRUE;
      neverusedcounter++;
   }
   return (singlevisit);

}/* IsSingleVisit */





/************************************************/
/* AnalyzeAttributes             */
/************************************************/

void 
AnalyzeAttributes(root)
   Visit_Sequences root;
{
   SEQAttributes X;
   Attributes thisattr;
   Boolean single_visit, global_variable;
   /* UK */
   int voidcnt = 0;
   /* UK */

   (void) ComputeCanEval(root);
   foreachinSEQAttributes(root->attrs, X, thisattr)
   {
      /* UK VTY and VLTY attributes are not globalized */
      if ((thisattr->typeid == VTY) || (thisattr->typeid == VLTY))
      {
	 single_visit = FALSE;
	 voidcnt++;
      } else if (strcmp(GENTREEATTR, anameOfAttributes(thisattr)) == 0)
	 single_visit = FALSE;
      else
	 /* UK */
      if (thisattr->termattr)
      {
	 /* terminal attrs all in tree node; INH are not yet considered for
	  * optimization; IsTermSingleVisit is only usable for top-down
	  * parsetime */
	 single_visit = FALSE;
      } else
      {
	 single_visit = IsSingleVisit(root, thisattr);
      }

      /* check single visit attributes */
      if (single_visit)
      {
	 if (thisattr->not_used)
	 {
	    global_variable = TRUE;
	 } else if (thisattr->termattr)
	 {
	    global_variable = IsTermGlobVar(root, thisattr);
	 }
	 /* IsTermGlobVar makes INH not global! */
	 else
	 {
	    global_variable = IsGlobVar(thisattr);
	 }

	 if (no_var_option)
	 {
	    global_variable = FALSE;
	 }
	 if (thisattr->not_used)
	 {
	    global_variable = TRUE;
	 }
	 /* check global variable attributes */
	 if (global_variable)
	 {
	    appendrearSEQAttributes(root->glob_var, thisattr);
	 } else if (no_stack_option)
	 {
	    appendrearSEQAttributes(root->tree_attrs, thisattr);
	 } else if (BottomUpVisits && (thisattr->part == 1))
	 {
	    appendrearSEQAttributes(root->tree_attrs, thisattr);
	 } else
	 {
	    appendrearSEQAttributes(root->single_visit, thisattr);
	 }
      } else
      {
	 appendrearSEQAttributes(root->tree_attrs, thisattr);
      }
   }

   globvarcounter = lengthSEQAttributes(optimroot->glob_var);
   globstackcounter = lengthSEQAttributes(optimroot->single_visit);
   treeattrcounter = lengthSEQAttributes(optimroot->tree_attrs);
   voidcounter = voidcnt;

#ifdef GLOBVAR
   /* test_vs_out(); */
   print_birth_death();
   /* print_can_eval(); */
#endif

   /* UK */
   if (voidcnt != 0)
      fprintf(ProtocolFile,
	      "\n %d void type attributes not globalized\n\n", voidcnt);
   /* UK */

}/* end of AnalyzeAttributes */
