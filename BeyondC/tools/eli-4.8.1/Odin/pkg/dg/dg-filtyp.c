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
#include "inc/FilTyp.h"
#include "inc/FTClass_.h"
#include "inc/InpSpc.h"
#include "inc/InpKind_.h"
#include "inc/ISKind_.h"
#include "inc/MemEdg.h"
#include "inc/PrmTypLst.h"
#include "inc/SrcTyp.h"
#include "inc/Str.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"


tp_FilTyp		FilTypS = NIL;
tp_FilTyp		LastFilTyp = NIL;
int			num_FilTypS = 0;

tp_SrcTyp		SrcTypS = NIL;
int			num_SrcTypS = 0;

tp_FilTyp	ObjectFilTyp;
tp_FilTyp	FileFilTyp;
tp_FilTyp	ListFilTyp;
tp_FilTyp	VoidFilTyp;
tp_FilTyp	ReferenceFilTyp;
tp_FilTyp	ExecFilTyp;
tp_FilTyp	GenericFilTyp;
tp_FilTyp	PipeFilTyp;
tp_FilTyp	DrvDirFilTyp;

static tp_FilTyp	ExpandHooksFilTyp;
static tp_FilTyp	TargetsPtrFilTyp;
static tp_FilTyp	TargetsFilTyp;
static tp_FilTyp	ActTargetsFilTyp;
static tp_FilTyp	VirTargetsFilTyp;
static tp_FilTyp	VirDirFilTyp;
tp_FilTyp	CopyFilTyp;
static tp_FilTyp	PrmValuesFilTyp;
static tp_FilTyp	ViewSpecFilTyp;
static tp_FilTyp	FirstFilTyp;
tp_FilTyp	ApplyFilTyp;
tp_FilTyp	NoInputFilTyp;
static tp_FilTyp	FatherFilTyp;


static tp_FilTyp
Init_SystemFilTyp(FTName)
   tp_FTName FTName;
{
   tp_FilTyp FilTyp;

   FilTyp = Lookup_FilTyp(Sym_Str(Str_Sym(FTName)));
   FORBIDDEN(FilTyp->Desc != NIL);
   FilTyp->Desc = "";
   FilTyp->HelpLevel = 3;
   return FilTyp;
   }/*Init_SystemFilTyp*/


void
Init_FilTyps()
{
   NoInputFilTyp = Init_SystemFilTyp(":noinput");
   ObjectFilTyp = Init_SystemFilTyp("OBJECT");
   FileFilTyp = Init_SystemFilTyp("FILE");
   ListFilTyp = Init_SystemFilTyp("LIST");
   VoidFilTyp = Init_SystemFilTyp("VOID");
   ReferenceFilTyp = Init_SystemFilTyp("REFERENCE");
   ExecFilTyp = Init_SystemFilTyp("EXECUTABLE");
   GenericFilTyp = Init_SystemFilTyp("GENERIC");
   PipeFilTyp = Init_SystemFilTyp("PIPE");
   DrvDirFilTyp = Init_SystemFilTyp("DERIVED-DIRECTORY");

   Add_CastEdg(FileFilTyp, ObjectFilTyp);
   Add_CastEdg(ListFilTyp, ObjectFilTyp);
   Add_CastEdg(VoidFilTyp, ObjectFilTyp);
   Add_CastEdg(ReferenceFilTyp, ObjectFilTyp);
   Add_CastEdg(ExecFilTyp, FileFilTyp);
   Add_CastEdg(GenericFilTyp, FileFilTyp);
   Add_CastEdg(PipeFilTyp, FileFilTyp);
   Add_CastEdg(DrvDirFilTyp, FileFilTyp);

   ExpandHooksFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*expand_hooks")));
   TargetsPtrFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*targets_ptr")));
   TargetsFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*targets")));
   ActTargetsFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*act_tgt.list")));
   VirTargetsFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*vir_tgt.list")));
   VirDirFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*vir_dir")));
   CopyFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*copy")));
   PrmValuesFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*prm_values")));
   ViewSpecFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*view_spec")));
   FirstFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("first")));
   ApplyFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*apply")));
   FatherFilTyp = Lookup_FilTyp(Sym_Str(Str_Sym("odin*abstract")));
   }/*Make_StandardFilTyps*/


void
Set_Tool(FilTyp, Tool)
   tp_FilTyp FilTyp;
   tp_Tool Tool;
{
   FORBIDDEN(FilTyp == ERROR);
   FilTyp->Tool = Tool;
   }/*Set_Tool*/


tp_Desc
FilTyp_Desc(FilTyp)
   tp_FilTyp FilTyp;
{
   if (FilTyp == ERROR) return ERROR;
   return FilTyp->Desc;
   }/*FilTyp_Desc*/


void
Set_FilTyp_Desc(FilTyp, Desc, Hidden)
   tp_FilTyp FilTyp;
   tp_Desc Desc;
   boolean Hidden;
{
   FORBIDDEN(FilTyp == ERROR || Desc == ERROR);
   FORBIDDEN(FilTyp->Desc != NIL);
   FilTyp->Desc = Desc;
   FilTyp->HelpLevel = (Hidden ? 2 : 1);
   }/*Set_FilTyp_Desc*/


static tp_FilTyp
New_FilTyp(FTName)
   tp_FTName FTName;
{
   tp_FilTyp FilTyp;

   FilTyp = (tp_FilTyp)malloc(sizeof(tps_FilTyp));
   FilTyp->FTClass = 0;
   FilTyp->FTName = FTName;
   FilTyp->Desc = NIL;
   FilTyp->HelpLevel = 0;
   FilTyp->ArgFilTyp = 0;
   FilTyp->Tool = 0;
   FilTyp->MemEdg = 0;
   FilTyp->InpLink = 0;
   FilTyp->EqvEdg = 0;
   FilTyp->FrmEqvEdg = 0;
   FilTyp->CastEdg = 0;
   FilTyp->FrmCastEdg = 0;
   FilTyp->DrvEdg = 0;
   FilTyp->FrmDrvEdg = 0;
   FilTyp->MapPrmTypLst = 0;
   FilTyp->IsCopy = FALSE;
   FilTyp->IsGrouping = FALSE;
   FilTyp->IsGroupingInput = FALSE;
   FilTyp->Pos = 0;
   FilTyp->NextOrder = NIL;
   FilTyp->NextBackOrder = NIL;
   FilTyp->Index = num_FilTypS;
   /*select*/{
      if (LastFilTyp == NIL) {
	 FilTypS = FilTyp;
      }else{
	 LastFilTyp->Link = FilTyp; };}/*select*/;
   FilTyp->BackLink = LastFilTyp;
   FilTyp->Link = NIL;
   LastFilTyp = FilTyp;
   num_FilTypS++;
   return FilTyp;
   }/*New_FilTyp*/


static tp_FilTyp
New_SecOrdFilTyp(FTName, ArgFilTyp)
   tp_FTName FTName;
   tp_FilTyp ArgFilTyp;
{
   tp_FilTyp FilTyp;
   tp_Tool Tool;
   tp_InpSpc InpSpc;

   FilTyp = New_FilTyp(FTName);
   FilTyp->ArgFilTyp = ArgFilTyp;

   Tool = New_Tool();
   Set_Tool(FilTyp, Tool);
   Tool->FilTyp = FilTyp;
   Tool->Package = Sym_Str(Str_Sym("odin"));
   /*select*/{
      if (strcmp(FTName, "lookup") == 0) {
	 Tool->TClass = TC_DerefPrmVal;
	 Add_EqvEdg(FilTyp, ReferenceFilTyp);
      }else if (strcmp(FTName, "map") == 0) {
	 Tool->TClass = TC_Map;
	 Add_EqvEdg(FilTyp, ListFilTyp);
      }else if (strcmp(FTName, "recurse") == 0) {
	 Tool->TClass = TC_Recurse;
	 Add_EqvEdg(FilTyp, ListFilTyp);
      }else if (strcmp(FTName, "extract") == 0) {
	 Tool->TClass = TC_Extract;
	 Add_EqvEdg(FilTyp, ListFilTyp);
      }else if (strcmp(FTName, "delete") == 0) {
	 Tool->TClass = TC_Delete;
	 Add_EqvEdg(FilTyp, ListFilTyp);
      }else{
	 SystemError("Must be lookup, map, recurse, extract, or delete: %s");
	 return ObjectFilTyp; };}/*select*/;

   InpSpc = New_InpSpc();
   InpSpc->ISKind = ISK_Drv;
   InpSpc->FilTyp = ObjectFilTyp;
   Add_InpEdg(InpSpc, IK_TransName, TRUE, Tool);

   FilTyp->Desc = "";
   FilTyp->HelpLevel = 2;
   return FilTyp;
   }/*New_SecOrdFilTyp*/


tp_FilTyp
Create_StructFilTyp(Package, FTName)
   tp_Package Package;
   tp_FTName FTName;
{
   tp_FilTyp FilTyp;
   tps_Str StrBuf;

   (void)sprintf(StrBuf, "%s*%s*composite", Package, FTName);
   FilTyp = New_FilTyp(Sym_Str(Str_Sym(StrBuf)));
   FilTyp->FTClass = FTC_Struct;
   FilTyp->Desc = "";
   FilTyp->HelpLevel = 3;
   return FilTyp;
   }/*Create_StructFilTyp*/


tp_FilTyp
Create_OutputFilTyp(Package, ToolPackage, FTName)
   tp_Package Package, ToolPackage;
   tp_FTName FTName;
{
   tps_Str StrBuf;
   tp_FilTyp FilTyp;

   (void)sprintf(StrBuf, "%s*%s", ToolPackage, FTName);
   FilTyp = Lookup_FilTyp(Sym_Str(Str_Sym(StrBuf)));
   if (ToolPackage == Package) {
      if (FilTyp_Desc(FilTyp) != NIL) {
	 SystemError
	  ("File type :%s produced by multiple tools in package %s.\n",
	   FTName, Package); }/*if*/;
      FilTyp->Desc = "";
      FilTyp->HelpLevel = 3; }/*if*/;
   return FilTyp;
   }/*Create_OutputFilTyp*/


static tp_FilTyp
FTName_FilTyp(FTName)
   tp_FTName FTName;
{
   tp_FilTyp FilTyp;

   if (FTName == ERROR) {
      return ERROR; }/*if*/;
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      if (FTName == FilTyp->FTName) {
	 return FilTyp; }/*if*/; }/*for*/;
   return ERROR;
   }/*FTName_FilTyp*/


static tp_FilTyp
FTName_SecOrdFilTyp(FTName, ArgFilTyp)
   tp_FTName FTName;
   tp_FilTyp ArgFilTyp;
{
   tp_FilTyp FilTyp;

   if (FTName == ERROR || ArgFilTyp == ERROR) {
      return ERROR; }/*if*/;
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      if ((FTName == FilTyp->FTName)
	  && ArgFilTyp == FilTyp->ArgFilTyp) {
	 return FilTyp; }/*if*/; }/*for*/;
   return ERROR;
   }/*FTName_SecOrdFilTyp*/


tp_FilTyp
Lookup_FilTyp(FTName)
   tp_FTName FTName;
{
   tp_FilTyp FilTyp;

   FORBIDDEN(FTName == ERROR);
   FilTyp = FTName_FilTyp(FTName);
   if (FilTyp != ERROR) {
      return FilTyp; }/*if*/;
   return New_FilTyp(FTName);
   }/*Lookup_FilTyp*/


tp_FilTyp
Lookup_SecOrdFilTyp(FTName, ArgFilTyp)
   tp_FTName FTName;
   tp_FilTyp ArgFilTyp;
{
   tp_FilTyp FilTyp;

   FORBIDDEN(FTName == ERROR || ArgFilTyp == ERROR);
   FilTyp = FTName_SecOrdFilTyp(FTName, ArgFilTyp);
   if (FilTyp != ERROR) {
      return FilTyp; }/*if*/;
   return New_SecOrdFilTyp(FTName, ArgFilTyp);
   }/*Lookup_SecOrdFilTyp*/


static boolean
Is_LaterSrcTyp(Pattern1, IsPrefix1, Pattern2, IsPrefix2)
   tp_Pattern Pattern1;
   boolean IsPrefix1;
   tp_Pattern Pattern2;
   boolean IsPrefix2;
{
   if (IsPrefix1 != IsPrefix2) {
      return !IsPrefix1; }/*if*/;
   if (strlen(Pattern1) != strlen(Pattern2)) {
      return ((int)strlen(Pattern1) < (int)strlen(Pattern2)); }/*if*/;
   return (strcmp(Pattern1, Pattern2) > 0);
   }/*Is_LaterSrcTyp*/



tp_SrcTyp
Lookup_SrcTyp(Pattern, IsPrefix)
   tp_Pattern Pattern;
   boolean IsPrefix;
{
   tp_SrcTyp SrcTyp, PrevSrcTyp, NextSrcTyp;

   PrevSrcTyp = NIL, NextSrcTyp = SrcTypS;
   while (NextSrcTyp != NIL
	  && Is_LaterSrcTyp(Pattern, IsPrefix,
			    NextSrcTyp->Pattern, NextSrcTyp->IsPrefix)) {
      PrevSrcTyp = NextSrcTyp;
      NextSrcTyp = NextSrcTyp->Link; }/*while*/;
   if (NextSrcTyp != NIL
       && strcmp(Pattern, NextSrcTyp->Pattern) == 0
       && IsPrefix == NextSrcTyp->IsPrefix) {
      return NextSrcTyp; }/*if*/;
   SrcTyp = (tp_SrcTyp)malloc(sizeof(tps_SrcTyp));
   /*select*/{
      if (PrevSrcTyp == NIL) {
	 SrcTypS = SrcTyp;
      }else{
	 PrevSrcTyp->Link = SrcTyp; };}/*select*/;
   SrcTyp->Pattern = Pattern;
   SrcTyp->IsPrefix = IsPrefix;
   SrcTyp->FilTyp = NIL;
   SrcTyp->Link = NextSrcTyp;
   num_SrcTypS++;
   return SrcTyp;
   }/*New_SrcTyp*/


void
Set_SrcTyp_FilTyp(SrcTyp, FilTyp)
   tp_SrcTyp SrcTyp;
   tp_FilTyp FilTyp;
{
   FORBIDDEN(SrcTyp == ERROR || FilTyp == ERROR);
   SrcTyp->FilTyp = FilTyp;
   }/*Set_SrcTyp_FilTyp*/


tp_FilTyp
SrcTyp_FilTyp(SrcTyp)
   tp_SrcTyp SrcTyp;
{
   if (SrcTyp == ERROR) return ERROR;
   return SrcTyp->FilTyp;
   }/*SrcTyp_FilTyp*/


tp_FilTyp
Key_FilTyp(Key)
   tp_Key Key;
{
   tp_SrcTyp SrcTyp;
   int Length;

   FORBIDDEN(Key == ERROR);

   for (SrcTyp = SrcTypS; SrcTyp != NIL; SrcTyp = SrcTyp->Link) {
      Length = strlen(SrcTyp->Pattern);
      /*select*/{
	 if (SrcTyp->IsPrefix) {
	    if (strncmp(Key, SrcTyp->Pattern, Length) == 0) {
	       return SrcTyp->FilTyp; }/*if*/;
	 }else{
	    if (strcmp(&Key[strlen(Key)-Length], SrcTyp->Pattern) == 0) {
	       return SrcTyp->FilTyp; }/*if*/; };}/*select*/; }/*for*/;
   return FileFilTyp;
   }/*Key_FilTyp*/


void
Clear_FilTypFlags()
{
   tp_FilTyp FilTyp;

   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      FilTyp->Flag = FALSE;
      FilTyp->Done = FALSE;
      FilTyp->Active = FALSE;
      FilTyp->Reach = FALSE;
      FilTyp->NewReach = FALSE; }/*for*/;
   }/*Clear_FilTypFlags*/


void
Print_Info(FilDsc)
   tp_FilDsc FilDsc;
{
   tp_FilTyp FilTyp;
   tp_DrvEdg DrvEdg;
   tp_EqvEdg EqvEdg;
   tp_CastEdg CastEdg;

   Writeln(FilDsc, "Possible Derivations :");
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      Print_FilTyp(FilDsc, FilTyp);
      if (FilTyp->MapPrmTypLst != DfltPrmTypLst) {
	 Write(FilDsc, " Map(");
	 Print_PrmTypLst(FilDsc, FilTyp->MapPrmTypLst);
	 Write(FilDsc, " )"); }/*if*/;
      Writeln(FilDsc, "");
      for (DrvEdg = FilTyp->DrvEdg;
	   DrvEdg != 0;
	   DrvEdg = DrvEdg_Next(DrvEdg)) {
	 Print_DrvEdg(FilDsc, DrvEdg); }/*for*/; }/*for*/;

   Writeln(FilDsc, "Equivalence Edges :");
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      if (FilTyp->EqvEdg != 0) {
	 Print_FilTyp(FilDsc, FilTyp);
	 for (EqvEdg = FilTyp->EqvEdg;
	      EqvEdg != 0;
	      EqvEdg = EqvEdg_Next(EqvEdg)) {
	    Write(FilDsc, " == ");
	    Print_FilTyp(FilDsc, EqvEdg_FilTyp(EqvEdg)); }/*for*/;
	 Writeln(FilDsc, ""); }/*if*/; }/*for*/;

   Writeln(FilDsc, "Possible Casts :");
   for (FilTyp = FilTypS; FilTyp != NIL; FilTyp = FilTyp->Link) {
      for (CastEdg = FilTyp->CastEdg;
	   CastEdg != 0;
	   CastEdg = CastEdg_Next(CastEdg)) {
	 Write(FilDsc, "   ");
	 Print_FilTyp(FilDsc, FilTyp);
	 Write(FilDsc, " -> ");
	 Print_FilTyp(FilDsc, CastEdg_FilTyp(CastEdg));
	 Writeln(FilDsc, ""); }/*for*/; }/*for*/;
   }/*Print_Info*/


void
Print_FilTyp(FilDsc, FilTyp)
   tp_FilDsc FilDsc;
   tp_FilTyp FilTyp;
{
   Write(FilDsc, FilTyp->FTName);
   if (FilTyp->ArgFilTyp != NIL) {
      Write(FilDsc, "=:");
      Write(FilDsc, FilTyp->ArgFilTyp->FTName); }/*if*/;
   if (FilTyp->MemEdg != 0) Print_MemEdgs(FilDsc, FilTyp->MemEdg);
   }/*Print_FilTyp*/


void
Write_FilTyps(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_SrcTyp SrcTyp;
   int iFilTyp;
   tps_EntryStr sFilTyp;
   tp_FilTyp FilTyp;
   int iArgFilTyp, iTool, iMapPrmTypLst;
   int iMemEdg, iEqvEdg, iCastEdg, iDrvEdg;
   tps_EntryStr sArgFilTyp, sTool, sMapPrmTypLst;
   tps_EntryStr sMemEdg, sEqvEdg, sCastEdg, sDrvEdg;

   DG_FOREACH(SrcTyp)
      DG_ENTRY(SrcTyp,FilTyp,FilTyp);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, ".%s\1 %d %d\n",
       SrcTyp->Pattern, SrcTyp->IsPrefix, iFilTyp);
      (void)fprintf(DG_C_FILE, "{\"%s\", %d, %s}",
       SrcTyp->Pattern, SrcTyp->IsPrefix, sFilTyp);
      DG_END_FOREACH(SrcTyp);

   DG_FOREACH(FilTyp)
      DG_ENTRY(FilTyp,ArgFilTyp,FilTyp);
      DG_ENTRY(FilTyp,Tool,Tool);
      DG_ENTRY(FilTyp,MemEdg,MemEdg);
      DG_ENTRY(FilTyp,EqvEdg,EqvEdg);
      DG_ENTRY(FilTyp,CastEdg,CastEdg);
      DG_ENTRY(FilTyp,DrvEdg,DrvEdg);
      if (FilTyp->MapPrmTypLst == DfltPrmTypLst) FilTyp->MapPrmTypLst = 0;
      DG_ENTRY(FilTyp,MapPrmTypLst,PrmTypLst);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d .%s\1 .%s\1 %d %d %d %d %d %d %d %d %d %d %d\n",
       FilTyp->FTClass, FilTyp->FTName, FilTyp->Desc,
       FilTyp->HelpLevel, iArgFilTyp, iTool, iMemEdg, iEqvEdg, iCastEdg,
       iDrvEdg, iMapPrmTypLst, FilTyp->IsCopy, FilTyp->IsGrouping,
       FilTyp->IsGroupingInput);
      (void)fprintf(DG_C_FILE, "{%d, \"%s\", \"%s\", %d, %s, %s, %s, %s, %s, %s, %s, %d, %d, %d, 0, 0, 0, %d}",
       FilTyp->FTClass, FilTyp->FTName, FilTyp->Desc,
       FilTyp->HelpLevel, sArgFilTyp, sTool, sMemEdg, sEqvEdg, sCastEdg,
       sDrvEdg, sMapPrmTypLst, FilTyp->IsCopy, FilTyp->IsGrouping,
       FilTyp->IsGroupingInput, FilTyp->Index);
      DG_END_FOREACH(FilTyp);

   DG_CONST(GenericFilTyp,FilTyp);
   DG_CONST(PipeFilTyp,FilTyp);
   DG_CONST(ListFilTyp,FilTyp);
   DG_CONST(FileFilTyp,FilTyp);
   DG_CONST(ObjectFilTyp,FilTyp);
   DG_CONST(NoInputFilTyp,FilTyp);

   DG_CONST(ExpandHooksFilTyp,FilTyp);
   DG_CONST(TargetsPtrFilTyp,FilTyp);
   DG_CONST(TargetsFilTyp,FilTyp);
   DG_CONST(ActTargetsFilTyp,FilTyp);
   DG_CONST(VirTargetsFilTyp,FilTyp);
   DG_CONST(VirDirFilTyp,FilTyp);
   DG_CONST(CopyFilTyp,FilTyp);
   DG_CONST(PrmValuesFilTyp,FilTyp);
   DG_CONST(ViewSpecFilTyp,FilTyp);
   DG_CONST(FirstFilTyp,FilTyp);
   DG_CONST(ApplyFilTyp,FilTyp);
   DG_CONST(FatherFilTyp,FilTyp);
   }/*Write_FilTyps*/


