/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"
#include "inc/CastEdg.h"
#include "inc/DrvEdg.h"
#include "inc/EqvEdg.h"
#include "inc/MemEdg.h"
#include "inc/InpEdg.h"
#include "inc/InpKind_.h"


tp_PrmTypLst
DrvEdg_PrmTypLst(
   GMC_ARG(tp_DrvEdg, DrvEdg)
   )
   GMC_DCL(tp_DrvEdg, DrvEdg)
{
   FORBIDDEN(DrvEdg == ERROR);
   return DrvEdg->PrmTypLst;
   }/*DrvEdg_PrmTypLst*/


tp_InpSpc
InpEdg_InpSpc(
   GMC_ARG(tp_InpEdg, InpEdg)
   )
   GMC_DCL(tp_InpEdg, InpEdg)
{
   FORBIDDEN(InpEdg == ERROR);
   return InpEdg->InpSpc;
   }/*InpEdg_InpSpc*/


tp_InpKind
InpEdg_InpKind(
   GMC_ARG(tp_InpEdg, InpEdg)
   )
   GMC_DCL(tp_InpEdg, InpEdg)
{
   FORBIDDEN(InpEdg == ERROR);
   return InpEdg->InpKind;
   }/*InpEdg_InpKind*/


boolean
InpEdg_IsUserArg(
   GMC_ARG(tp_InpEdg, InpEdg)
   )
   GMC_DCL(tp_InpEdg, InpEdg)
{
   FORBIDDEN(InpEdg == ERROR);
   return InpEdg->IsUserArg;
   }/*InpEdg_IsUserArg*/


tp_InpEdg
InpEdg_Next(
   GMC_ARG(tp_InpEdg, InpEdg)
   )
   GMC_DCL(tp_InpEdg, InpEdg)
{
   FORBIDDEN(InpEdg == ERROR);
   return InpEdg->Next;
   }/*InpEdg_Next*/


tp_FilTyp
EqvEdg_FilTyp(
   GMC_ARG(tp_EqvEdg, EqvEdg)
   )
   GMC_DCL(tp_EqvEdg, EqvEdg)
{
   return EqvEdg->FilTyp;
   }/*EqvEdg_FilTyp*/


tp_FilTyp
MemEdg_FilTyp(
   GMC_ARG(tp_MemEdg, MemEdg)
   )
   GMC_DCL(tp_MemEdg, MemEdg)
{
   return MemEdg->FilTyp;
   }/*MemEdg_FilTyp*/


static boolean
InpKind_IsName(
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_InpKind, InpKind)
{
   return (InpKind == IK_Name);
   }/*InpKind_IsName*/


static boolean
InpKind_IsTransName(
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_InpKind, InpKind)
{
   return (InpKind == IK_TransName);
   }/*InpKind_IsTransName*/


static boolean
InpKind_IsTrans(
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_InpKind, InpKind)
{
   return (InpKind == IK_Trans || InpKind == IK_AnyOK);
   }/*InpKind_IsTrans*/


boolean
InpKind_IsAnyOK(
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_InpKind, InpKind)
{
   return (InpKind == IK_AnyOK);
   }/*InpKind_IsAnyOK*/


boolean
NeedsData(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   return !(InpKind_IsName(InpKind)
	    || (InpKind_IsTransName(InpKind) && !IsRef(FilHdr)));
   }/*NeedsData*/


boolean
NeedsElmData(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   return ((InpKind_IsTrans(InpKind) && IsList(FilHdr))
	   || (InpKind != IK_Pntr && InpKind != IK_TransName
	       && IsPntr(FilHdr)));
   }/*NeedsElmData*/


boolean
NeedsElmNameData(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   return (InpKind_IsTransName(InpKind) && IsRef(FilHdr));
   }/*NeedsElmNameData*/


int
NumInputs(
   GMC_ARG(tp_FilTyp, FilTyp)
   )
   GMC_DCL(tp_FilTyp, FilTyp)
{
   int i;
   tp_InpEdg InpEdg;
   boolean IsUserArg;

   IsUserArg = TRUE;
   i = 0;
   for (InpEdg = Tool_InpEdg(FilTyp_Tool(FilTyp));
	InpEdg != NIL;
	InpEdg = InpEdg->Next) {
      /*select*/{
	 if (InpEdg->IsUserArg) {
	    FORBIDDEN(!IsUserArg);
	    i++;
	 }else{
	    IsUserArg = FALSE; };}/*select*/; }/*while*/;
   return i;
   }/*NumInputs*/


void
GetOutTyps(
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_OutTyps, OutTyps),
   GMC_ARG(int*, NumOutputsPtr)
   )
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_OutTyps, OutTyps)
   GMC_DCL(int*, NumOutputsPtr)
{
   int i;
   tp_MemEdg MemEdg;

   if (!IsStruct_FilTyp(FilTyp)) {
      OutTyps[0] = FilTyp;
      *NumOutputsPtr = 1;
      return; }/*if*/;

   for (i = 0, MemEdg = FilTyp_MemEdg(FilTyp);
	MemEdg != NIL;
	i += 1, MemEdg = MemEdg->Next) {
      OutTyps[i] = MemEdg->FilTyp; }/*for*/;
   *NumOutputsPtr = i;
   }/*GetOutTyps*/


void
SetEqvEdg_Marks(
   GMC_ARG(tp_EqvEdg, EqvEdg),
   GMC_ARG(boolean, CastFlag),
   GMC_ARG(boolean, PrmTypFlag)
   )
   GMC_DCL(tp_EqvEdg, EqvEdg)
   GMC_DCL(boolean, CastFlag)
   GMC_DCL(boolean, PrmTypFlag)
{
   tp_EqvEdg TmpEE;

   for (TmpEE = EqvEdg; TmpEE != NIL; TmpEE = TmpEE->Next) {
      if (!PrmTypFlag) SetFilTyp_Mark(TmpEE->FilTyp);
      SetFilTyp_Marks(TmpEE->FilTyp, CastFlag, PrmTypFlag); }/*for*/;
   }/*SetEqvEdg_Marks*/


void
SetCastEdg_Marks(
   GMC_ARG(tp_CastEdg, CastEdg),
   GMC_ARG(boolean, PrmTypFlag)
   )
   GMC_DCL(tp_CastEdg, CastEdg)
   GMC_DCL(boolean, PrmTypFlag)
{
   tp_CastEdg TmpCE;

   for (TmpCE = CastEdg; TmpCE != NIL; TmpCE = TmpCE->Next) {
      if (!PrmTypFlag) SetFilTyp_Mark(TmpCE->FilTyp);
      SetFilTyp_Marks(TmpCE->FilTyp, TRUE, PrmTypFlag); }/*for*/;
   }/*SetCastEdg_Marks*/


void
SetDrvEdg_Marks(
   GMC_ARG(tp_DrvEdg, DrvEdg),
   GMC_ARG(boolean, PrmTypFlag)
   )
   GMC_DCL(tp_DrvEdg, DrvEdg)
   GMC_DCL(boolean, PrmTypFlag)
{
   tp_DrvEdg TmpDE;

   for (TmpDE = DrvEdg; TmpDE != NIL; TmpDE = TmpDE->Next) {
      ;/*select*/{
	 if (PrmTypFlag) {
	    SetPrmTypLst_Marks(TmpDE->PrmTypLst);
	 }else{
	    SetFilTyp_Mark(TmpDE->FilTyp); };}/*select*/;
      SetFilTyp_Marks(TmpDE->FilTyp, FALSE, PrmTypFlag); }/*for*/;
   }/*SetDrvEdg_Marks*/



