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

#include <stdio.h>
#include "inc/GMC.h"
#include "inc/CastEdg.h"
#include "inc/DrvEdg.h"
#include "inc/Entry.h"
#include "inc/EqvEdg.h"
#include "inc/InpSpc.h"
#include "inc/InpKind_.h"
#include "inc/ISKind_.h"
#include "inc/FilTyp.h"
#include "inc/InpEdg.h"
#include "inc/MemEdg.h"
#include "inc/PrmTypLst.h"
#include "inc/Tool.h"



static tp_InpEdg		InpEdgS = NIL;
static tp_InpEdg		LastInpEdg = NIL;
int			num_InpEdgS = 0;

static tp_MemEdg		MemEdgS = NIL;
static tp_MemEdg		LastMemEdg = NIL;
int			num_MemEdgS = 0;

static tp_EqvEdg		EqvEdgS = NIL;
static tp_EqvEdg		LastEqvEdg = NIL;
int			num_EqvEdgS = 0;

static tp_CastEdg		CastEdgS = NIL;
static tp_CastEdg		LastCastEdg = NIL;
int			num_CastEdgS = 0;

tp_DrvEdg		DrvEdgS = NIL;
static tp_DrvEdg		LastDrvEdg = NIL;
int			num_DrvEdgS = 0;


void
Clear_EdgFlags()
{
   tp_DrvEdg DrvEdg;

   for (DrvEdg = DrvEdgS; DrvEdg != NIL; DrvEdg = DrvEdg->Link) {
      DrvEdg->Flag = FALSE; }/*for*/;
   }/*Clear_EdgFlags*/


static tp_InpEdg
New_InpEdg()
{
   tp_InpEdg InpEdg;

   InpEdg = (tp_InpEdg)malloc(sizeof(tps_InpEdg));
   /*select*/{
      if (LastInpEdg == NIL) {
	 InpEdgS = InpEdg;
      }else{
	 LastInpEdg->Link = InpEdg; };}/*select*/;
   LastInpEdg = InpEdg;
   InpEdg->InpKind = 0;
   InpEdg->FilTyp = 0;
   InpEdg->InpSpc = 0;
   InpEdg->Next = 0;
   InpEdg->Tool = 0;
   InpEdg->InpLink = 0;
   InpEdg->Done = FALSE;
   InpEdg->Index = num_InpEdgS;
   InpEdg->Link = NIL;
   num_InpEdgS++;
   return InpEdg;
   }/*New_InpEdg*/


static tp_InpEdg
New_HomInpEdg()
{
   tp_InpEdg InpEdg;

   InpEdg = (tp_InpEdg)malloc(sizeof(tps_InpEdg));
   InpEdg->InpKind = 0;
   InpEdg->FilTyp = 0;
   InpEdg->InpSpc = 0;
   InpEdg->Next = 0;
   InpEdg->Tool = 0;
   InpEdg->InpLink = 0;
   InpEdg->Index = -1;
   InpEdg->Link = NIL;
   return InpEdg;
   }/*New_HomInpEdg*/


static tp_MemEdg
New_MemEdg()
{
   tp_MemEdg MemEdg;

   MemEdg = (tp_MemEdg)malloc(sizeof(tps_MemEdg));
   /*select*/{
      if (LastMemEdg == NIL) {
	 MemEdgS = MemEdg;
      }else{
	 LastMemEdg->Link = MemEdg; };}/*select*/;
   LastMemEdg = MemEdg;
   MemEdg->FilTyp = 0;
   MemEdg->Next = 0;
   MemEdg->Index = num_MemEdgS;
   MemEdg->Link = NIL;
   num_MemEdgS++;
   return MemEdg;
   }/*New_MemEdg*/


static tp_EqvEdg
New_EqvEdg()
{
   tp_EqvEdg EqvEdg;

   EqvEdg = (tp_EqvEdg)malloc(sizeof(tps_EqvEdg));
   /*select*/{
      if (LastEqvEdg == NIL) {
	 EqvEdgS = EqvEdg;
      }else{
	 LastEqvEdg->Link = EqvEdg; };}/*select*/;
   LastEqvEdg = EqvEdg;
   EqvEdg->FrmFilTyp = 0;
   EqvEdg->FilTyp = 0;
   EqvEdg->FrmNext = 0;
   EqvEdg->Next = 0;
   EqvEdg->Link = NIL;
   EqvEdg->Index = num_EqvEdgS;
   num_EqvEdgS++;
   return EqvEdg;
   }/*New_EqvEdg*/


tp_FilTyp
EqvEdg_FilTyp(EqvEdg)
   tp_EqvEdg EqvEdg;
{
   return EqvEdg->FilTyp;
   }/*EqvEdg_FilTyp*/


tp_EqvEdg
EqvEdg_Next(EqvEdg)
   tp_EqvEdg EqvEdg;
{
   return EqvEdg->Next;
   }/*EqvEdg_Next*/


tp_FilTyp
EqvEdg_FrmFilTyp(EqvEdg)
   tp_EqvEdg EqvEdg;
{
   return EqvEdg->FrmFilTyp;
   }/*EqvEdg_FrmFilTyp*/


tp_EqvEdg
EqvEdg_FrmNext(EqvEdg)
   tp_EqvEdg EqvEdg;
{
   return EqvEdg->FrmNext;
   }/*EqvEdg_FrmNext*/


static tp_CastEdg
New_CastEdg()
{
   tp_CastEdg CastEdg;

   CastEdg = (tp_CastEdg)malloc(sizeof(tps_CastEdg));
   /*select*/{
      if (LastCastEdg == NIL) {
	 CastEdgS = CastEdg;
      }else{
	 LastCastEdg->Link = CastEdg; };}/*select*/;
   LastCastEdg = CastEdg;
   CastEdg->FrmFilTyp = 0;
   CastEdg->FilTyp = 0;
   CastEdg->FrmNext = 0;
   CastEdg->Next = 0;
   CastEdg->Index = num_CastEdgS;
   CastEdg->Link = NIL;
   num_CastEdgS++;
   return CastEdg;
   }/*New_CastEdg*/


tp_FilTyp
CastEdg_FilTyp(CastEdg)
   tp_CastEdg CastEdg;
{
   return CastEdg->FilTyp;
   }/*CastEdg_FilTyp*/


tp_CastEdg
CastEdg_Next(CastEdg)
   tp_CastEdg CastEdg;
{
   return CastEdg->Next;
   }/*CastEdg_Next*/


static tp_DrvEdg
New_DrvEdg()
{
   tp_DrvEdg DrvEdg;

   DrvEdg = (tp_DrvEdg)malloc(sizeof(tps_DrvEdg));
   /*select*/{
      if (LastDrvEdg == NIL) {
	 DrvEdgS = DrvEdg;
      }else{
	 LastDrvEdg->Link = DrvEdg; };}/*select*/;
   LastDrvEdg = DrvEdg;
   DrvEdg->FrmFilTyp = 0;
   DrvEdg->FilTyp = 0;
   DrvEdg->PrmTypLst = 0;
   DrvEdg->FrmNext = 0;
   DrvEdg->Next = 0;
   DrvEdg->Index = num_DrvEdgS;
   DrvEdg->Link = NIL;
   num_DrvEdgS++;
   return DrvEdg;
   }/*New_DrvEdg*/


tp_FilTyp
DrvEdg_FrmFilTyp(DrvEdg)
   tp_DrvEdg DrvEdg;
{
   return DrvEdg->FrmFilTyp;
   }/*DrvEdg_FrmFilTyp*/


tp_DrvEdg
DrvEdg_FrmNext(DrvEdg)
   tp_DrvEdg DrvEdg;
{
   return DrvEdg->FrmNext;
   }/*DrvEdg_FrmNext*/


tp_DrvEdg
DrvEdg_Next(DrvEdg)
   tp_DrvEdg DrvEdg;
{
   return DrvEdg->Next;
   }/*DrvEdg_Next*/


void
Add_InpEdg(InpSpc, InpKind, IsUserArg, Tool)
   tp_InpSpc InpSpc;
   tp_InpKind InpKind;
   boolean IsUserArg;
   tp_Tool Tool;
{
   tp_InpEdg NewInpEdg, InpEdg;

   FORBIDDEN(InpSpc == NIL || InpKind == NIL || Tool == NIL);

   NewInpEdg = New_InpEdg();
   NewInpEdg->InpKind = InpKind;
   NewInpEdg->FilTyp = ((InpSpc->ISKind == ISK_Drv) ? InpSpc->FilTyp : NIL);
   NewInpEdg->IsUserArg = IsUserArg;
   NewInpEdg->InpSpc = InpSpc;
   NewInpEdg->Next = 0;
   /*select*/{
      if (Tool->InpEdg == 0) {
	 Tool->InpEdg = NewInpEdg;
      }else{
	 InpEdg = Tool->InpEdg;
	 while (InpEdg->Next != 0) InpEdg = InpEdg->Next;
	 InpEdg->Next = NewInpEdg; };}/*select*/;
   NewInpEdg->Tool = Tool;
   if (NewInpEdg->FilTyp != NIL) {
      /* InpLink could be changed to be ordered as Tool.InpEdg as above */
      NewInpEdg->InpLink = NewInpEdg->FilTyp->InpLink;
      NewInpEdg->FilTyp->InpLink = NewInpEdg; }/*if*/;
   }/*Add_InpEdg*/


void
Add_HomInpEdg(InpSpc, Tool)
   tp_InpSpc InpSpc;
   tp_Tool Tool;
{
   tp_InpEdg NewInpEdg;

   NewInpEdg = New_HomInpEdg();
   NewInpEdg->InpKind = IK_Trans;
   NewInpEdg->FilTyp = ((InpSpc->ISKind == ISK_Drv) ? InpSpc->FilTyp : NIL);
   NewInpEdg->IsUserArg = FALSE;
   NewInpEdg->Next = Tool->HomInpEdg;
   Tool->HomInpEdg = NewInpEdg;
   NewInpEdg->Tool = Tool;
   if (NewInpEdg->FilTyp != NIL) {
      NewInpEdg->InpLink = NewInpEdg->FilTyp->InpLink;
      NewInpEdg->FilTyp->InpLink = NewInpEdg; }/*if*/;
   }/*Add_HomInpEdg*/


boolean
HasInput(Tool)
   tp_Tool Tool;
{
   tp_InpEdg InpEdg;

   for (InpEdg = Tool->InpEdg; InpEdg != NIL; InpEdg = InpEdg->Next) {
      if (InpEdg->FilTyp != NIL && !Is_Output(InpEdg->FilTyp, Tool)) {
	 return TRUE; }/*if*/; }/*for*/;
   for (InpEdg = Tool->HomInpEdg; InpEdg != NIL; InpEdg = InpEdg->Next) {
      if (InpEdg->FilTyp != NIL && !Is_Output(InpEdg->FilTyp, Tool)) {
	 return TRUE; }/*if*/; }/*for*/;
   return FALSE;
   }/*HasInput*/


void
Set_SystemTool_InpKinds(Tool, InpKind)
   tp_Tool Tool;
   tp_InpKind InpKind;
{
   tp_InpEdg InpEdg;

   for (InpEdg = Tool->InpEdg; InpEdg != NIL; InpEdg = InpEdg->Next) {
      /*select*/{
	 if (InpEdg->InpKind == InpKind
	     || (InpEdg->InpKind == IK_AnyOK && InpKind == IK_Trans)) {
	 }else if (InpEdg->InpKind == IK_Trans) {
	    InpEdg->InpKind = InpKind;
	 }else{
	    SystemError("Bad input kind for tool : %s.\n", Tool_Name(Tool));
	    };}/*select*/; }/*for*/;
   }/*Set_SystemTool_InpKinds*/


void
Set_SystemTool_InpKind(Tool, InpNum, InpKind)
   tp_Tool Tool;
   int InpNum;
   tp_InpKind InpKind;
{
   tp_InpEdg InpEdg;
   int i;

   InpEdg = Tool->InpEdg; i = 1;
   while (i < InpNum) {
      FORBIDDEN(InpEdg == NIL);
      InpEdg=InpEdg->Next;
      i += 1; }/*while*/;
   if (!(InpEdg->InpKind == IK_Trans || InpEdg->InpKind == InpKind)) {
      SystemError("Bad input kind for tool : %s.\n", Tool_Name(Tool)); }/*if*/;
   InpEdg->InpKind = InpKind;
   }/*Set_SystemTool_InpKind*/


tp_FilTyp
MemEdg_FilTyp(MemEdg)
   tp_MemEdg MemEdg;
{
   return MemEdg->FilTyp;
   }/*MemEdg_FilTyp*/


void
Add_MemEdg(FilTyp, MemFilTyp)
   tp_FilTyp FilTyp, MemFilTyp;
{
   tp_MemEdg NewMemEdg, MemEdg;

   NewMemEdg = New_MemEdg();
   NewMemEdg->FilTyp = MemFilTyp;
   NewMemEdg->Next = 0;
   /*select*/{
      if (FilTyp->MemEdg == 0) {
	 FilTyp->MemEdg = NewMemEdg;
      }else{
	 MemEdg = FilTyp->MemEdg;
	 while (MemEdg->Next != 0) MemEdg = MemEdg->Next;
	 MemEdg->Next = NewMemEdg; };}/*select*/;
   }/*Add_MemEdg*/


void
Add_EqvEdg(FrmFilTyp, FilTyp)
   tp_FilTyp FrmFilTyp, FilTyp;
{
   tp_EqvEdg EqvEdg, PrevEqvEdg;

   if (FilTyp == ObjectFilTyp || FilTyp == FileFilTyp || FilTyp == ListFilTyp
       || FilTyp == VoidFilTyp || FilTyp == ReferenceFilTyp
       || FilTyp == ExecFilTyp || FilTyp == DrvDirFilTyp) {
      Add_CastEdg(FrmFilTyp, FilTyp);
      return; }/*if*/;

   PrevEqvEdg = NIL;
   for (EqvEdg = FrmFilTyp->EqvEdg; EqvEdg!=NIL; EqvEdg = EqvEdg->Next) {
      PrevEqvEdg = EqvEdg;
      if (EqvEdg->FilTyp == FilTyp) {
	 return; }/*if*/; }/*for*/;

   EqvEdg = New_EqvEdg();
   EqvEdg->FrmFilTyp = FrmFilTyp;
   EqvEdg->FilTyp = FilTyp;
   /*select*/{
      if (PrevEqvEdg == NIL) {
	 FrmFilTyp->EqvEdg = EqvEdg;
      }else{
	 PrevEqvEdg->Next = EqvEdg; };}/*select*/;
   EqvEdg->FrmNext = FilTyp->FrmEqvEdg;
   FilTyp->FrmEqvEdg = EqvEdg;
   }/*Add_EqvEdg*/


void
Add_CastEdg(FrmFilTyp, FilTyp)
   tp_FilTyp FrmFilTyp;
   tp_FilTyp FilTyp;
{
   tp_CastEdg CastEdg, PrevCastEdg;

   PrevCastEdg = NIL;
   for (CastEdg = FrmFilTyp->CastEdg; CastEdg!=NIL; CastEdg = CastEdg->Next) {
      PrevCastEdg = CastEdg;
      if (CastEdg->FilTyp == FilTyp) {
	 return; }/*if*/; }/*for*/;

   CastEdg = New_CastEdg();
   CastEdg->FrmFilTyp = FrmFilTyp;
   CastEdg->FilTyp = FilTyp;
   /*select*/{
      if (PrevCastEdg == NIL) {
	 FrmFilTyp->CastEdg = CastEdg;
      }else{
	 PrevCastEdg->Next = CastEdg; };}/*select*/;
   CastEdg->FrmNext = FilTyp->FrmCastEdg;
   FilTyp->FrmCastEdg = CastEdg;
   }/*Add_CastEdg*/


void
Add_DrvEdg(FrmFilTyp, FilTyp)
   tp_FilTyp FrmFilTyp;
   tp_FilTyp FilTyp;
{
   tp_DrvEdg DrvEdg;

   for (DrvEdg = FrmFilTyp->DrvEdg; DrvEdg!=NIL; DrvEdg = DrvEdg->Next) {
      if (DrvEdg->FilTyp == FilTyp) {
	 return; }/*if*/; }/*for*/;

   DrvEdg = New_DrvEdg();
   DrvEdg->FrmFilTyp = FrmFilTyp;
   DrvEdg->FilTyp = FilTyp;

   DrvEdg->Next = FrmFilTyp->DrvEdg;
   FrmFilTyp->DrvEdg = DrvEdg;

   DrvEdg->FrmNext = FilTyp->FrmDrvEdg;
   FilTyp->FrmDrvEdg = DrvEdg;
   }/*Add_DrvEdg*/


tp_PrmTypLst
DrvEdg_PrmTypLst(DrvEdg)
   tp_DrvEdg DrvEdg;
{
   return DrvEdg->PrmTypLst;
   }/*DrvEdg_PrmTypLst*/


void
Print_DrvEdg(FilDsc, DrvEdg)
   tp_FilDsc FilDsc;
   tp_DrvEdg DrvEdg;
{
   Write(FilDsc, "   -> ");
   Print_FilTyp(FilDsc, DrvEdg->FilTyp);
   if (DrvEdg->PrmTypLst != DfltPrmTypLst) {
      Print_PrmTypLst(FilDsc, DrvEdg->PrmTypLst); }/*if*/;
   Writeln(FilDsc, "");
   }/*Print_DrvEdg*/


void
Print_MemEdgs(FilDsc, MemEdgs)
   tp_FilDsc FilDsc;
   tp_MemEdg MemEdgs;
{
   tp_MemEdg MemEdg;

   Write(FilDsc, " <");
   for (MemEdg = MemEdgs; MemEdg != 0; MemEdg = MemEdg->Next) {
      Write(FilDsc, " ");
      Print_FilTyp(FilDsc, MemEdg->FilTyp); }/*for*/;
   Write(FilDsc, " >");
   }/*Print_MemEdgs*/


void
Write_Edgs(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_InpEdg InpEdg;
   tp_MemEdg MemEdg;
   tp_EqvEdg EqvEdg;
   tp_CastEdg CastEdg;
   tp_DrvEdg DrvEdg;
   int iFilTyp, iInpSpc, iPrmTypLst, iNext;
   tps_EntryStr sFilTyp, sInpSpc, sPrmTypLst, sNext;

   DG_FOREACH(InpEdg)
      DG_ENTRY(InpEdg,InpSpc,InpSpc);
      DG_ENTRY(InpEdg,Next,InpEdg);
      (void)fprintf(DRVGRF_FILE, "%d %d %d %d\n", iInpSpc, InpEdg->InpKind, InpEdg->IsUserArg, iNext);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DG_C_FILE, "{%s, %d, %d,%s}", sInpSpc, InpEdg->InpKind, InpEdg->IsUserArg, sNext);
   DG_END_FOREACH(InpEdg);

   DG_FOREACH(MemEdg)
      DG_ENTRY(MemEdg,FilTyp,FilTyp);
      DG_ENTRY(MemEdg,Next,MemEdg);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d\n", iFilTyp, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s}", sFilTyp, sNext);
   DG_END_FOREACH(MemEdg);

   DG_FOREACH(EqvEdg)
      DG_ENTRY(EqvEdg,FilTyp,FilTyp);
      DG_ENTRY(EqvEdg,Next,EqvEdg);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d\n", iFilTyp, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s}", sFilTyp, sNext);
   DG_END_FOREACH(EqvEdg);

   DG_FOREACH(CastEdg)
      DG_ENTRY(CastEdg,FilTyp,FilTyp);
      DG_ENTRY(CastEdg,Next,CastEdg);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d\n", iFilTyp, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s}", sFilTyp, sNext);
   DG_END_FOREACH(CastEdg);

   DG_FOREACH(DrvEdg)
      DG_ENTRY(DrvEdg,FilTyp,FilTyp);
      if (DrvEdg->PrmTypLst == DfltPrmTypLst) DrvEdg->PrmTypLst = 0;
      DG_ENTRY(DrvEdg,PrmTypLst,PrmTypLst);
      DG_ENTRY(DrvEdg,Next,DrvEdg);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d %d\n", iFilTyp, iPrmTypLst, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s, %s}", sFilTyp, sPrmTypLst, sNext);
   DG_END_FOREACH(DrvEdg);

   }/*Write_Edgs*/


