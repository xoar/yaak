/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 1,
or (at your option) any later version (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"
#include "inc/CastEdg.h"
#include "inc/DPType_.h"
#include "inc/DrvEdg.h"
#include "inc/EqvEdg.h"
#include "inc/FilTyp.h"
#include "inc/FKind_.h"
#include "inc/FTClass_.h"
#include "inc/InpSpc.h"
#include "inc/InpEdg.h"
#include "inc/InpKind_.h"
#include "inc/ISKind_.h"
#include "inc/MemEdg.h"
#include "inc/PrmTyp.h"
#include "inc/Str.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"

extern tp_Tool		ToolS;

extern tp_FilTyp	FilTypS;
extern tp_FilTyp	LastFilTyp;
extern int		num_FilTypS;

extern tp_DrvEdg	DrvEdgS;


static tp_FilTyp		Ordered_FilTypS = NIL;
static tp_FilTyp		LastOrdered_FilTyp = NIL;
static int			num_Ordered_FilTypS = 0;

static tp_FilTyp		BackOrdered_FilTypS = NIL;
static tp_FilTyp		LastBackOrdered_FilTyp = NIL;
static int			num_BackOrdered_FilTypS = 0;


static tp_PrmTypLst	GenericMapPrmTypLst = NIL;


static void Set_MapPrmTypLst(GMC_P1(boolean *) GMC_PN(tp_FilTyp));
static void Set_DrvEdg_PrmTypLst(GMC_P1(boolean *) GMC_PN(tp_DrvEdg));


static void
Clear_Flags()
{
   Clear_FilTypFlags();
   Clear_ToolFlags();
   }/*Clear_Flags*/


static tp_Str
FTClass_Str(FTClass)
   tp_FTClass FTClass;
{
   switch (FTClass) {
      case FTC_None: {
	 return "OBJECT"; }/*case*/;
      case FTC_Atmc: {
	 return "FILE"; }/*case*/;
      case FTC_List: {
	 return "LIST"; }/*case*/;
      case FTC_Void: {
	 return "VOID"; }/*case*/;
      case FTC_Pntr: {
	 return "REFERENCE"; }/*case*/;
      case FTC_Exec: {
	 return "EXECUTABLE"; }/*case*/;
      case FTC_Generic: {
	 return "GENERIC"; }/*case*/;
      case FTC_Pipe: {
	 return "PIPE"; }/*case*/;
      case FTC_DrvDir: {
	 return "DERIVED-DIRECTORY"; }/*case*/;
      case FTC_Struct: {
	 return "RECORD"; }/*case*/;
      default: {
	 FATALERROR("unknown FTClass.\n"); };}/*switch*/;
   /*NOTREACHED*/
   return "";
   }/*FTClass_Str*/


static void
Broadcast_FTClass(FilTyp, FTClass)
   tp_FilTyp FilTyp;
   tp_FTClass FTClass;
{
   tp_EqvEdg EqvEdg;
   tp_CastEdg CastEdg;

   if (FilTyp->FTClass != 0) {
      if (!(FTClass == FilTyp->FTClass
	    || (FTClass == FTC_Atmc && (FilTyp->FTClass == FTC_Pntr
					|| FilTyp->FTClass == FTC_Exec
					|| FilTyp->FTClass == FTC_Generic
					|| FilTyp->FTClass == FTC_Pipe
					|| FilTyp->FTClass == FTC_DrvDir)))) {
	 SystemError(":%s cannot be a subtype of both :%s and :%s.\n",
		     FilTyp->FTName, FTClass_Str(FilTyp->FTClass),
		     FTClass_Str(FTClass)); }/*if*/;
      return; }/*if*/;
   FilTyp->FTClass = FTClass;
   for (EqvEdg=FilTyp->FrmEqvEdg; EqvEdg!=NIL; EqvEdg=EqvEdg->FrmNext) {
      Broadcast_FTClass(EqvEdg->FrmFilTyp, FTClass); }/*for*/;
   for (CastEdg=FilTyp->FrmCastEdg; CastEdg!=NIL; CastEdg=CastEdg->FrmNext) {
      Broadcast_FTClass(CastEdg->FrmFilTyp, FTClass); }/*for*/;
   }/*Broadcast_FTClass*/


static void
Broadcast_IsCopy(FilTyp)
   tp_FilTyp FilTyp;
{
   tp_EqvEdg EqvEdg;
   tp_CastEdg CastEdg;

   if (FilTyp->IsCopy) {
      return; }/*if*/;
   FilTyp->IsCopy = TRUE;
   for (EqvEdg=FilTyp->FrmEqvEdg; EqvEdg!=NIL; EqvEdg=EqvEdg->FrmNext) {
      Broadcast_IsCopy(EqvEdg->FrmFilTyp); }/*for*/;
   for (CastEdg=FilTyp->FrmCastEdg; CastEdg!=NIL; CastEdg=CastEdg->FrmNext) {
      Broadcast_IsCopy(CastEdg->FrmFilTyp); }/*for*/;
   }/*Broadcast_IsCopy*/


static void
Broadcast_IsGrouping(FilTyp)
   tp_FilTyp FilTyp;
{
   tp_EqvEdg EqvEdg;

   if (FilTyp->IsGrouping) {
      return; }/*if*/;
   FilTyp->IsGrouping = TRUE;
   for (EqvEdg=FilTyp->EqvEdg; EqvEdg!=NIL; EqvEdg=EqvEdg->Next) {
      Broadcast_IsGrouping(EqvEdg->FilTyp); }/*for*/;
   }/*Broadcast_IsGrouping*/


static void
Broadcast_IsGroupingInput(FilTyp)
   tp_FilTyp FilTyp;
{
   tp_EqvEdg EqvEdg;

   if (FilTyp->IsGroupingInput) {
      return; }/*if*/;
   FilTyp->IsGroupingInput = TRUE;
   for (EqvEdg=FilTyp->EqvEdg; EqvEdg!=NIL; EqvEdg=EqvEdg->Next) {
      Broadcast_IsGroupingInput(EqvEdg->FilTyp); }/*for*/;
   }/*Broadcast_IsGroupingInput*/


boolean
Is_Output(FilTyp, Tool)
   tp_FilTyp FilTyp;
   tp_Tool Tool;
{
   tp_EqvEdg EqvEdg;
   tp_Tool TmpTool;

   for (EqvEdg=FilTyp->FrmEqvEdg; EqvEdg!=NIL; EqvEdg=EqvEdg->FrmNext) {
      TmpTool = EqvEdg->FrmFilTyp->Tool;
      if (TmpTool == Tool
	  || (TmpTool != NIL && TmpTool->TClass == TC_StructMem
	      && (TmpTool->InpEdg->InpSpc->FilTyp->Tool == Tool))) {
	 return TRUE; }/*if*/; }/*for*/;
   return FALSE;
   }/*Is_Output*/


static boolean
Is_Reached(FilTyp, Tool)
   tp_FilTyp FilTyp;
   tp_Tool Tool;
{
   return (FilTyp == NIL || FilTyp->Reach || Is_Output(FilTyp, Tool));
   }/*Is_Reached*/


static void
Order_FilTyp(AbortPtr, FilTyp, BackFlag)
   boolean *AbortPtr;
   tp_FilTyp FilTyp;
   boolean BackFlag;
{
   tp_InpEdg InpEdg;
   tp_MemEdg MemEdg;
   tp_EqvEdg EqvEdg;

   *AbortPtr = FALSE;
   if (FilTyp->Done) {
      return; }/*if*/;
   if (FilTyp->Active) {
      Print_FilTyp(StdErrFD, FilTyp);
      Writeln(StdErrFD, " is recursive");
      Print_FilTyp(StdErrFD, FilTyp);
      *AbortPtr = TRUE;
      return;}/*if*/;

   FilTyp->Active = TRUE;
   for (InpEdg = FilTyp->InpLink;
	InpEdg != 0;
	InpEdg = InpEdg->InpLink) {
      if (!Is_Output(FilTyp, InpEdg->Tool)) {
	 Order_FilTyp(AbortPtr, InpEdg->Tool->FilTyp, BackFlag);
	 if (*AbortPtr) {
	    Write(StdErrFD, " <= ");
	    Print_FilTyp(StdErrFD, FilTyp);
	    return; }/*if*/; }/*if*/; }/*for*/;
   for (MemEdg = FilTyp->MemEdg;
	MemEdg != 0;
	MemEdg = MemEdg->Next) {
      Order_FilTyp(AbortPtr, MemEdg->FilTyp, BackFlag);
      if (*AbortPtr) {
	 Write(StdErrFD, " <= ");
	 Print_FilTyp(StdErrFD, FilTyp);
	 return; }/*if*/; }/*for*/;
   for (EqvEdg = FilTyp->EqvEdg;
	EqvEdg != 0;
	EqvEdg = EqvEdg->Next) {
      Order_FilTyp(AbortPtr, EqvEdg->FilTyp, BackFlag);
      if (*AbortPtr) {
	 Write(StdErrFD, " <= ");
	 Print_FilTyp(StdErrFD, FilTyp);
	 return; }/*if*/; }/*for*/;
   FilTyp->Active = FALSE;

   /*select*/{
      if (BackFlag) {
	 /*select*/{
	    if (LastBackOrdered_FilTyp == NIL) {
	       BackOrdered_FilTypS = FilTyp;
	    }else{
	       LastBackOrdered_FilTyp->NextBackOrder = FilTyp; };}/*select*/;
	 FORBIDDEN(FilTyp->NextBackOrder != NIL);
	 LastBackOrdered_FilTyp = FilTyp;
	 num_BackOrdered_FilTypS += 1;
      }else{
	 /*select*/{
	    if (LastOrdered_FilTyp == NIL) {
	       Ordered_FilTypS = FilTyp;
	    }else{
	       LastOrdered_FilTyp->NextOrder = FilTyp;
	       };}/*select*/;
	 FORBIDDEN(FilTyp->NextOrder != NIL);
	 LastOrdered_FilTyp = FilTyp;
	 num_Ordered_FilTypS += 1; };}/*select*/;
   FilTyp->Done = TRUE;
   }/*Order_FilTyp*/


static void
Mark_NewReach(ChangedPtr)
   boolean *ChangedPtr;
{
   tp_Tool Tool;
   tp_InpEdg InpEdg;
   boolean CanRun;
   tp_FilTyp FilTyp;

   *ChangedPtr = FALSE;
   for (Tool = ToolS;
	Tool != NIL;
	Tool = Tool->Link) {
      if (!Tool->Flag && !IsDummy_Tool(Tool)) {
	 FORBIDDEN(Tool->InpEdg == NIL);
	 CanRun = TRUE;
	 for (InpEdg = Tool->InpEdg;
	      InpEdg != 0 && CanRun;
	      InpEdg = InpEdg->Next) {
	    if (!Is_Reached(InpEdg->FilTyp, Tool)) {
	       CanRun = FALSE; }/*if*/; }/*for*/;
	 for (InpEdg = Tool->HomInpEdg;
	      InpEdg != 0 && CanRun;
	      InpEdg = InpEdg->Next) {
	    if (!Is_Reached(InpEdg->FilTyp, Tool)) {
	       CanRun = FALSE; }/*if*/; }/*for*/;
	 if (CanRun) {
	    Tool->Flag = TRUE;
	    FilTyp = Tool->FilTyp;
	    FORBIDDEN(FilTyp->Reach);
	    FilTyp->NewReach = TRUE ;
	    *ChangedPtr = TRUE; }/*if*/; }/*if*/;}/*for*/;
   }/*Mark_NewReach*/


static void
Mark_Reach(FrmFilTyp)
   tp_FilTyp FrmFilTyp;
{
   tp_EqvEdg EqvEdg;
   tp_DrvEdg DrvEdg;

   if (FrmFilTyp->Reach) return;
   FORBIDDEN(FrmFilTyp->NewReach);
   FrmFilTyp->Reach = TRUE;
   if (FrmFilTyp->Tool != NIL) {
      FrmFilTyp->Tool->Flag = TRUE; }/*if*/;

   for (EqvEdg = FrmFilTyp->EqvEdg; EqvEdg != 0; EqvEdg = EqvEdg->Next) {
      Mark_Reach(EqvEdg->FilTyp); }/*for*/;

   for (DrvEdg = FrmFilTyp->DrvEdg; DrvEdg != 0; DrvEdg = DrvEdg->Next) {
      Mark_Reach(DrvEdg->FilTyp); }/*for*/;
   }/*Mark_Reach*/


static void
Add_DrvEdgs(FrmFilTyp)
   tp_FilTyp FrmFilTyp;
{
   boolean Changed;
   tp_FilTyp FilTyp;

   Mark_Reach(FrmFilTyp);
   Mark_NewReach(&Changed);
   while (Changed) {
      for (FilTyp = BackOrdered_FilTypS;
	   FilTyp != NIL;
	   FilTyp = FilTyp->NextBackOrder) {
	 if (FilTyp->NewReach) {
	    FORBIDDEN(FilTyp->Reach);
	    Add_DrvEdg(FrmFilTyp, FilTyp);
	    FilTyp->NewReach = FALSE;
	    Mark_Reach(FilTyp);
	    FrmFilTyp->Reach = TRUE; }/*if*/; }/*for*/;
      Mark_NewReach(&Changed); }/*while*/;
   }/*Add_DrvEdgs*/


void
Make_DrvEdgs()
{
   tp_FilTyp FilTyp;
   boolean Abort;

   Add_EqvEdg(ObjectFilTyp, NoInputFilTyp);

   Clear_Flags();
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      Order_FilTyp(&Abort, FilTyp, FALSE);
      if (Abort) {
	 SystemError(".\n");
	 return; }/*if*/; }/*for*/;
   FORBIDDEN(num_Ordered_FilTypS != num_FilTypS);

   Clear_Flags();
   for (FilTyp = LastFilTyp; FilTyp != NIL; FilTyp = FilTyp->BackLink) {
      Order_FilTyp(&Abort, FilTyp, TRUE);
      if (Abort) {
	 SystemError(".\n");
	 return; }/*if*/; }/*for*/;
   FORBIDDEN(num_BackOrdered_FilTypS != num_FilTypS);

   for (FilTyp = Ordered_FilTypS; FilTyp != NIL; FilTyp = FilTyp->NextOrder) {
      Clear_Flags();
      Add_DrvEdgs(FilTyp); }/*for*/;

   Clear_Flags();
   Mark_Reach(ObjectFilTyp);
   Add_DrvEdgs(ListFilTyp);

   Clear_Flags();
   Mark_Reach(ObjectFilTyp);
   Add_DrvEdgs(FileFilTyp);

   for (FilTyp = Ordered_FilTypS; FilTyp != NIL; FilTyp = FilTyp->NextOrder) {
      Clear_Flags();
      /*select*/{
         if (IsStruct_FilTyp(FilTyp)) {
         }else if (IsList_FilTyp(FilTyp)) {
	    Mark_Reach(ObjectFilTyp);
	    Mark_Reach(ListFilTyp);
	 }else{
	    Mark_Reach(ObjectFilTyp);
	    Mark_Reach(FileFilTyp); };}/*select*/;
      Add_DrvEdgs(FilTyp); }/*for*/;
   }/*Make_DrvEdgs*/


static void
Set_DrvPth_PrmTypLst(ReDoPtr, PrmTypLstPtr, PntrHoPtr, FailPtr, FrmFKind, FrmFilTyp, ToFilTyp)
   boolean *ReDoPtr;
   tp_PrmTypLst *PrmTypLstPtr;
   boolean *PntrHoPtr;
   boolean *FailPtr;
   tp_FKind FrmFKind;
   tp_FilTyp FrmFilTyp;
   tp_FilTyp ToFilTyp;
{
   tp_DrvPth DrvPth, DrvPthElm;
   boolean IsGeneric;
   tp_DrvEdg DrvEdg;
   tp_FilTyp FilTyp;

   *PntrHoPtr = FALSE;
   *FailPtr = FALSE;
   if (FrmFilTyp == ToFilTyp) {
      return; }/*if*/;
   Do_Search(&DrvPth, &IsGeneric, FrmFKind, FrmFilTyp, ToFilTyp);
   if (IsGeneric) {
      Ret_DrvPth(DrvPth);
      DrvPth = ERROR; }/*if*/;
   if (DrvPth == ERROR) {
      *FailPtr = TRUE;
      return; }/*if*/;
   for (DrvPthElm = DrvPth;
	DrvPthElm != 0;
	DrvPthElm = DrvPth_Next(DrvPthElm)) {
      FORBIDDEN(*PntrHoPtr);
      DrvEdg = DrvPth_DrvEdg(DrvPthElm);
      if (DrvPth_FKind(DrvPthElm) == FK_PntrHo) {
	 *PntrHoPtr = TRUE; }/*if*/;
      ;/*select*/{
	 if (DrvEdg != NIL) {
	    Set_DrvEdg_PrmTypLst(ReDoPtr, DrvEdg);
	    *PrmTypLstPtr = Union_PrmTypLst(*PrmTypLstPtr, DrvEdg->PrmTypLst);
	 }else if (*PntrHoPtr) {
	    FilTyp = DrvPth_FilTyp(DrvPthElm);
	    Set_MapPrmTypLst(ReDoPtr, FilTyp);
	    *PrmTypLstPtr = Union_PrmTypLst(*PrmTypLstPtr, FilTyp->MapPrmTypLst);
	    };}/*select*/; }/*for*/;
   Ret_DrvPth(DrvPth);
   }/*Set_DrvPth_PrmTypLst*/


static void
Set_Tool_PrmTypLst(ReDoPtr, Tool)
   boolean * ReDoPtr;
   tp_Tool Tool;
{
   tp_FilTyp FrmFilTyp;
   tp_PrmTypLst PrmTypLst;
   tp_InpSpc InpSpc;
   tp_InpEdg InpEdg;
   tp_FKind FrmFKind;
   boolean PntrHoFlag, FailFlag;
   tp_Str InpName;

   if (Tool->Flag && Tool->PrmTypLst != ERROR) return;
   if (Tool->Flag) {
      Tool->PrmTypLst = Tool->BasePrmTypLst;
      return; }/*if*/;
   Tool->Flag = TRUE;

   PrmTypLst = Tool->BasePrmTypLst;
   FORBIDDEN(PrmTypLst == ERROR);
   for (InpEdg = Tool->InpEdg;
	InpEdg != 0;
	InpEdg = InpEdg->Next) {
      FrmFKind = FK_User;
      FrmFilTyp = ObjectFilTyp;
      InpSpc = InpEdg->InpSpc;
      switch (InpSpc->ISKind) {
	 case ISK_EmptyFile: {
	    FrmFilTyp = FileFilTyp;
	    InpName = "()";
	    break;}/*case*/;
	 case ISK_Str: {
	    InpName = InpSpc->Str;
	    break;}/*case*/;
	 case ISK_Key: case ISK_Sel: case ISK_VTgt: {
	    InpName = "/";
	    if (InpSpc->Str != NIL) {
	       FrmFilTyp = Key_FilTyp(InpSpc->Str);
	       InpName = InpSpc->Str; }/*if*/;
	    break;}/*case*/;
	 case ISK_Drv: {
	    FrmFilTyp = InpSpc->FilTyp;
	    InpName = FrmFilTyp->FTName;
	    break;}/*case*/;
	 case ISK_Prm: {
	    FrmFilTyp = InpSpc->PrmTyp->FilTyp;
	    InpName = InpSpc->PrmTyp->PTName;
	    break;}/*case*/;
	 default: {
	    FATALERROR("bad ISKind.\n"); };}/*switch*/;

      for (InpSpc = InpSpc->Next;
	   InpSpc != 0;
	   InpSpc = InpSpc->Next) {
	 switch (InpSpc->ISKind) {
	    case ISK_Key: case ISK_Sel: case ISK_VTgt: {
	       FrmFKind = FK_User;
	       FrmFilTyp = ObjectFilTyp;
	       InpName = "/";
	       if (InpSpc->Str != NIL) {
		  FrmFilTyp = Key_FilTyp(InpSpc->Str);
		  InpName = InpSpc->Str; }/*if*/;
	       break;}/*case*/;
	    case ISK_Drv: {
	       Set_DrvPth_PrmTypLst(ReDoPtr, &PrmTypLst, &PntrHoFlag, &FailFlag,
				    FrmFKind, FrmFilTyp, InpSpc->FilTyp);
	       if (FailFlag && !InpEdg->Done) {
		  SystemError(
		   "In package %s: cannot perform derivation from :%s to :%s.\n",
		   Tool->Package, FrmFilTyp->FTName, InpSpc->FilTyp->FTName);
		  }/*if*/;
	       if (InpSpc->FilTyp->ArgFilTyp != NIL) {
		  Set_MapPrmTypLst(ReDoPtr, InpSpc->FilTyp->ArgFilTyp);
		  PrmTypLst = Union_PrmTypLst
		   (PrmTypLst, InpSpc->FilTyp->ArgFilTyp->MapPrmTypLst);
		  }/*if*/;
	       FrmFKind = (PntrHoFlag ? FK_PntrHo : FK_User);
	       FrmFilTyp = InpSpc->FilTyp;
	       InpName = FrmFilTyp->FTName;
	       break;}/*case*/;
	    case ISK_Prm: {
	       break;}/*case*/;
	    default: {
	       FATALERROR("bad ISKind.\n"); };}/*switch*/; }/*for*/;
      if (InpEdg->IsUserArg && !InpEdg->Done && IsExternal_Tool(Tool)
	  && IsList_FilTyp(FrmFilTyp)) {
	 SystemError(
	  "In package %s: argument \"%s\" to EXEC cannot be a list.\n",
	  Tool->Package, InpName); }/*if*/;
      InpEdg->Done = TRUE; }/*for*/;
   if (Tool->PrmTypLst != ERROR && Tool->PrmTypLst != PrmTypLst) {
      Write(StdOutFD, "Recomputing parameters for recursive derivation : ");
      Print_FilTyp(StdOutFD, Tool->FilTyp);
      Writeln(StdOutFD, "");
      *ReDoPtr = TRUE; }/*if*/;
   Tool->PrmTypLst = PrmTypLst;
   }/*Set_Tool_PrmTypLst*/


static void
Set_DrvEdg_PrmTypLst(ReDoPtr, DrvEdg)
   boolean * ReDoPtr;
   tp_DrvEdg DrvEdg;
{
   tp_FilTyp FrmFilTyp, ToFilTyp, FilTyp;
   tp_Tool Tool;
   tp_PrmTypLst PrmTypLst;
   tp_InpEdg InpEdg;
   boolean PntrHoFlag, FailFlag;

   if (DrvEdg->Flag && DrvEdg->PrmTypLst != ERROR) return;
   if (DrvEdg->Flag) {
      DrvEdg->PrmTypLst = DfltPrmTypLst;
      return; }/*if*/;
   DrvEdg->Flag = TRUE;
   FrmFilTyp = DrvEdg->FrmFilTyp;
   ToFilTyp = DrvEdg->FilTyp;
   Tool = ToFilTyp->Tool;
   Set_Tool_PrmTypLst(ReDoPtr, Tool);
   PrmTypLst = Tool->PrmTypLst;
   FORBIDDEN(PrmTypLst == ERROR);
   for (InpEdg = Tool->InpEdg;
	InpEdg != 0;
	InpEdg = InpEdg->Next) {
      FilTyp = InpEdg->FilTyp;
      if (FilTyp != NIL && FilTyp != FrmFilTyp) {
	 Set_DrvPth_PrmTypLst(ReDoPtr, &PrmTypLst, &PntrHoFlag, &FailFlag,
			     FK_User, FrmFilTyp, FilTyp);
	 FORBIDDEN(FailFlag); }/*if*/; }/*for*/;
   for (InpEdg = Tool->HomInpEdg;
	InpEdg != 0;
	InpEdg = InpEdg->Next) {
      FilTyp = InpEdg->FilTyp;
      if (FilTyp != NIL && FilTyp != FrmFilTyp) {
	 Set_DrvPth_PrmTypLst(ReDoPtr, &PrmTypLst, &PntrHoFlag, &FailFlag,
			     FK_User, FrmFilTyp, FilTyp);
	 FORBIDDEN(FailFlag); }/*if*/; }/*for*/;
   if (DrvEdg->PrmTypLst != ERROR && DrvEdg->PrmTypLst != PrmTypLst) {
      Write(StdOutFD, "Recomputing parameters for recursive derivation : ");
      Print_DrvEdg(StdOutFD, DrvEdg);
      Writeln(StdOutFD, "");
      *ReDoPtr = TRUE; }/*if*/;
   DrvEdg->PrmTypLst = PrmTypLst;
   }/*Set_DrvEdg_PrmTypLst*/


static void
Set_MapPrmTypLst(ReDoPtr, FilTyp)
   boolean * ReDoPtr;
   tp_FilTyp FilTyp;
{
   tp_PrmTypLst PrmTypLst, NewPrmTypLst;
   tp_FilTyp FrmFilTyp;
   tp_DrvEdg FrmDrvEdg;
   tp_EqvEdg FrmEqvEdg;

   if (FilTyp->Flag && FilTyp->MapPrmTypLst != ERROR) return;
   if (FilTyp->Flag) {
      FilTyp->MapPrmTypLst = GenericMapPrmTypLst;
      return; }/*if*/;

   FilTyp->Flag = TRUE;
   PrmTypLst = GenericMapPrmTypLst;

   for (FrmDrvEdg = FilTyp->FrmDrvEdg;
	FrmDrvEdg != 0;
	FrmDrvEdg = DrvEdg_FrmNext(FrmDrvEdg)) {
      Set_DrvEdg_PrmTypLst(ReDoPtr, FrmDrvEdg);
      NewPrmTypLst = DrvEdg_PrmTypLst(FrmDrvEdg);
      PrmTypLst = Union_PrmTypLst(PrmTypLst, NewPrmTypLst);

      FrmFilTyp = DrvEdg_FrmFilTyp(FrmDrvEdg);
      Set_MapPrmTypLst(ReDoPtr, FrmFilTyp);
      NewPrmTypLst = FilTyp_MapPrmTypLst(FrmFilTyp);
      PrmTypLst = Union_PrmTypLst(PrmTypLst, NewPrmTypLst); }/*for*/;

   for (FrmEqvEdg = FilTyp->FrmEqvEdg;
	FrmEqvEdg != 0;
	FrmEqvEdg = EqvEdg_FrmNext(FrmEqvEdg)) {
      FrmFilTyp = EqvEdg_FrmFilTyp(FrmEqvEdg);
      Set_MapPrmTypLst(ReDoPtr, FrmFilTyp);
      NewPrmTypLst = FilTyp_MapPrmTypLst(FrmFilTyp);
      PrmTypLst = Union_PrmTypLst(PrmTypLst, NewPrmTypLst); }/*for*/;

   if (FilTyp->MapPrmTypLst != ERROR && FilTyp->MapPrmTypLst != PrmTypLst) {
      Write(StdOutFD, "Recomputing parameters for recursive derivation : ");
      Print_FilTyp(StdOutFD, FilTyp);
      Writeln(StdOutFD, "");
      *ReDoPtr = TRUE; }/*if*/;
   FilTyp->MapPrmTypLst = PrmTypLst;
   }/*Set_MapPrmTypLst*/


void
Make_PrmTypLsts()
{
   boolean ReDo;
   tp_DrvEdg DrvEdg;
   tp_FilTyp FilTyp;
   tp_Tool Tool;
   tp_PrmTypLst OldGenericMapPTL;

   GenericMapPrmTypLst = DfltPrmTypLst;

   ReDo = TRUE;
   OldGenericMapPTL = DfltPrmTypLst;
   while (ReDo || OldGenericMapPTL != GenericMapPrmTypLst) {
      ReDo = FALSE;
      OldGenericMapPTL = GenericMapPrmTypLst;
      Clear_Flags();
      Clear_EdgFlags();
      for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
	 if (IsGeneric_FilTyp(FilTyp)) {
	    Set_MapPrmTypLst(&ReDo, FilTyp);
	    GenericMapPrmTypLst = Union_PrmTypLst(GenericMapPrmTypLst,
						    FilTyp->MapPrmTypLst);
	    
	    }/*if*/; }/*for*/; }/*while*/;

   ReDo = TRUE;
   while (ReDo) {
      ReDo = FALSE;
      Clear_Flags();
      Clear_EdgFlags();
      for (DrvEdg = DrvEdgS; DrvEdg != NIL; DrvEdg = DrvEdg->Link) {
	 Set_DrvEdg_PrmTypLst(&ReDo, DrvEdg); }/*for*/; }/*while*/;

   ReDo = TRUE;
   while (ReDo) {
      ReDo = FALSE;
      Clear_Flags();
      for (Tool = ToolS; Tool != NIL; Tool = Tool->Link) {
	 Set_Tool_PrmTypLst(&ReDo, Tool); }/*for*/; }/*while*/;

   ReDo = TRUE;
   while (ReDo) {
      ReDo = FALSE;
      Clear_Flags();
      for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
	 Set_MapPrmTypLst(&ReDo, FilTyp); }/*for*/; }/*while*/;
   }/*Make_PrmTypLsts*/


void
Set_FTClasses()
{
   tp_FilTyp FilTyp;
   tp_TClass TClass;

   NoInputFilTyp->FTClass = FTC_None;
   ObjectFilTyp->FTClass = FTC_None;
   Broadcast_FTClass(DrvDirFilTyp, FTC_DrvDir);
   Broadcast_FTClass(GenericFilTyp, FTC_Generic);
   Broadcast_FTClass(PipeFilTyp, FTC_Pipe);
   Broadcast_FTClass(ExecFilTyp, FTC_Exec);
   Broadcast_FTClass(ReferenceFilTyp, FTC_Pntr);
   Broadcast_FTClass(VoidFilTyp, FTC_Void);
   Broadcast_FTClass(ListFilTyp, FTC_List);
   Broadcast_FTClass(FileFilTyp, FTC_Atmc);

   Broadcast_IsCopy(CopyFilTyp);
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      if (FilTyp->Tool != NIL) {
	 TClass = FilTyp->Tool->TClass;
	 if (TClass == TC_NestedHooks || TClass == TC_Map
	     || TClass == TC_DerefPrmVal || TClass == TC_Recurse) {
	    Broadcast_IsGroupingInput(FilTyp); }/*if*/;
	 if (TClass == TC_PrmValues || TClass == TC_Apply
	     || TClass == TC_Collect || TClass == TC_ReadList
	     || TClass == TC_Name || TClass == TC_Names
	     || TClass == TC_ExpandHooks) {
	    Broadcast_IsGrouping(FilTyp); }/*if*/;
	 }/*if*/; }/*for*/;
   }/*Set_FTClasses*/


