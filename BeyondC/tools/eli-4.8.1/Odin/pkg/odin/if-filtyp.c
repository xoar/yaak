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
#include "inc/Client.h"
#include "inc/FilTyp.h"
#include "inc/FTClass_.h"
#include "inc/NodTyp_.h"
#include "inc/SrcTyp.h"
#include "inc/Str.h"
#include "inc/Status_.h"
#include "inc/TClass_.h"
#include "inc/Tool.h"


extern int		num_SrcTypS;
extern tp_SrcTyp	SrcTypS;

extern int		num_FilTypS;
extern tp_FilTyp	FilTypS;


tp_TClass
Tool_TClass(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   return Tool->TClass;}

tp_InpEdg
Tool_InpEdg(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   return Tool->InpEdg;}

tp_Package
Tool_Package(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   return Tool->Package;}


boolean
IsDerefInput_Tool(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   switch (Tool->TClass) {
      case TC_PrmValues: case TC_First:
      case TC_External: case TC_CopyCmd:
      case TC_ReadList: case TC_SrcNames: case TC_OpNames:
      case TC_ViewSpec: case TC_CmptView: case TC_FileName:
      case TC_DerefPrmVal: case TC_PntrElm:
      case TC_ExpandHooks: case TC_NestedHooks:
      case TC_TargetsPtr: case TC_TargetsInc: case TC_Targets:
      case TC_ActTargets: case TC_TextDef: case TC_VirTargets:
      case TC_VirDir: case TC_Directory:
      case TC_DrvHelp: case TC_PrmHelp: {
	 return TRUE; break;}/*case*/;
      case TC_Name: case TC_Names:
      case TC_Union: case TC_FileNames: case TC_Cat:
      case TC_Apply: case TC_Map: case TC_Recurse:
      case TC_Extract: case TC_Delete:
      case TC_PntrHo: case TC_DrvDirElm: case TC_VirDirElm:
      case TC_Label: case TC_Labels: case TC_Id: case TC_Collect:
      case TC_StructMem:
      case TC_Str: case TC_Error: case TC_Warning: case TC_InternalPntr:
      case TC_Depend:
      case TC_PrefixHelp: case TC_SuffixHelp: {
	 return FALSE; break;}/*case*/;
      default: {
	 FATALERROR("illegal ToolClass"); };}/*switch*/;
   /*NOTREACHED*/
   return FALSE;
   }/*IsDerefInput_Tool*/


boolean
IsReport_Tool(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   FORBIDDEN(Tool == ERROR);
   return (Tool->TClass == TC_Error || Tool->TClass == TC_Warning);
   }/*IsReport_Tool*/


boolean
IsDerefPrmVal_Tool(
   GMC_ARG(tp_Tool, Tool)
   )
   GMC_DCL(tp_Tool, Tool)
{
   FORBIDDEN(Tool == ERROR);
   return (Tool->TClass == TC_DerefPrmVal);
   }/*IsDerefPrmVal_Tool*/


tp_Status
Get_ToolStatus(
   GMC_ARG(tp_Tool, Tool),
   GMC_ARG(tp_Status, DepStatus)
   )
   GMC_DCL(tp_Tool, Tool)
   GMC_DCL(tp_Status, DepStatus)
{
   tp_Status MinStatus;

   FORBIDDEN(DepStatus <= STAT_Unknown);

   if (Is_PRB_Status(DepStatus)) {
      return STAT_Pending; }/*if*/;

   switch (Tool_TClass(Tool)) {
      case TC_External: case TC_PrmValues: case TC_First:
      case TC_Name: case TC_Names:
      case TC_FileName: case TC_FileNames: case TC_Cat: case TC_Union:
      case TC_Apply: case TC_DerefPrmVal:
      case TC_Map: case TC_Recurse: case TC_Extract: case TC_Delete:
      case TC_PntrHo:
      case TC_Label: case TC_Labels: case TC_Collect:
      case TC_ReadList: case TC_SrcNames: case TC_OpNames:
      case TC_ViewSpec: case TC_CmptView:
      case TC_Directory: case TC_CopyCmd:
      case TC_ExpandHooks: case TC_NestedHooks:
      case TC_TargetsInc: case TC_Targets: case TC_VirTargets:
      case TC_TextDef: case TC_VirDir:
      case TC_PrefixHelp: case TC_SuffixHelp:
      case TC_DrvHelp: case TC_PrmHelp: {
	 MinStatus = ((DepStatus > STAT_Error) ? DepStatus : STAT_SysAbort);
	 break;}/*case*/;
       case TC_PntrElm: case TC_DrvDirElm: case TC_VirDirElm: {
	 MinStatus = ((DepStatus == STAT_NoFile) ? STAT_NoFile
		      : ((DepStatus > STAT_Error) ? DepStatus : STAT_SysAbort));
	 break;}/*case*/;
      case TC_TargetsPtr: case TC_ActTargets: {
	 MinStatus = ((DepStatus == STAT_NoFile) ? STAT_OK
		      : ((DepStatus > STAT_Error) ? DepStatus : STAT_SysAbort));
	 break;}/*case*/;
      case TC_StructMem: {
	 MinStatus = DepStatus;
	 break;}/*case*/;
      case TC_Str: case TC_Error: case TC_Warning: case TC_InternalPntr:
      case TC_Id: {
	 MinStatus = STAT_OK;
	 break;}/*case*/;
      case TC_Depend: {
	 MinStatus = ((DepStatus < STAT_OK) ? STAT_Warning : STAT_OK);
	 break;}/*case*/;
      default: {
	 FATALERROR("illegal ToolClass"); };}/*switch*/;

   return MinStatus;
   }/*Get_ToolStatus*/


tp_FilTyp
Key_FilTyp(
   GMC_ARG(tp_Key, Key)
   )
   GMC_DCL(tp_Key, Key)
{
   tp_SrcTyp SrcTyp;
   int Length, i;

   FORBIDDEN(Key == ERROR);

   for (i=0; i<num_SrcTypS; i++) {
      SrcTyp = &SrcTypS[i];
      Length = strlen(SrcTyp->Pattern);
      /*select*/{
	 if (SrcTyp->IsPrefix) {
	    if (strncmp(Key, SrcTyp->Pattern, Length) == 0) {
	       return SrcTyp->FilTyp; }/*if*/;
	 }else{
	    int Start = strlen(Key)-Length;
	    if (Start >= 0 && strcmp(&Key[Start], SrcTyp->Pattern) == 0) {
	       return SrcTyp->FilTyp; }/*if*/; };}/*select*/; }/*for*/;
   return FileFilTyp;
   }/*Key_FilTyp*/


void
Key_InstanceLabel(
   GMC_ARG(tp_Str, Label),
   GMC_ARG(tp_Key, Key)
   )
   GMC_DCL(tp_Str, Label)
   GMC_DCL(tp_Key, Key)
{
   tp_SrcTyp SrcTyp;
   int Length, i;

   FORBIDDEN(Key == ERROR);

   for (i=0; i<num_SrcTypS; i++) {
      SrcTyp = &SrcTypS[i];
      Length = strlen(SrcTyp->Pattern);
      /*select*/{
	 if (SrcTyp->IsPrefix) {
	    if (strncmp(Key, SrcTyp->Pattern, Length) == 0) {
	       (void)strcpy(Label, &Key[strlen(SrcTyp->Pattern)]);
	       return; }/*if*/;
	 }else{
	    int Start = strlen(Key)-Length;
	    if (Start >= 0 && strcmp(&Key[Start], SrcTyp->Pattern) == 0) {
	       (void)strcpy(Label, Key);
	       Label[strlen(Key)-Length] = '\0';
	       return; }/*if*/; };}/*select*/; }/*for*/;
   (void)strcpy(Label, Key);
   }/*Key_InstanceLabel*/


tp_FilTyp
FTName_FilTyp(
   GMC_ARG(tp_FTName, FTName)
   )
   GMC_DCL(tp_FTName, FTName)
{
   int i;
   tp_FilTyp FilTyp;

   if (FTName == ERROR) {
      return ERROR; }/*if*/;
   for (i=0; i<num_FilTypS; i++) {
      FilTyp = &FilTypS[i];
      if (strcmp(FTName, FilTyp->FTName) == 0) {
	 return FilTyp; }/*if*/; }/*for*/;
   return ERROR;
   }/*FTName_FilTyp*/


static tp_FilTyp
FTName_SecOrdFilTyp(
   GMC_ARG(tp_FTName, FTName),
   GMC_ARG(tp_FTName, ArgFTName)
   )
   GMC_DCL(tp_FTName, FTName)
   GMC_DCL(tp_FTName, ArgFTName)
{
   int i;
   tp_FilTyp FilTyp, ArgFilTyp;

   if (FTName == ERROR || ArgFTName == ERROR) {
      return ERROR; }/*if*/;
   ArgFilTyp = FTName_FilTyp(ArgFTName);
   if (ArgFilTyp == ERROR) {
      return ERROR; }/*if*/;
   for (i=0; i<num_FilTypS; i++) {
      FilTyp = &FilTypS[i];
      if ((strcmp(FTName, FilTyp->FTName) == 0)
	  && (ArgFilTyp == FilTyp->ArgFilTyp)) {
	 return FilTyp; }/*if*/; }/*for*/;
   return ERROR;
   }/*FTName_SecOrdFilTyp*/


void
Build_Label(
   GMC_ARG(tp_Str, StrBuf),
   GMC_ARG(tp_Ident, Ident),
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(tp_LocHdr, LocHdr),
   GMC_ARG(boolean, UniqueFlag)
   )
   GMC_DCL(tp_Str, StrBuf)
   GMC_DCL(tp_Ident, Ident)
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(tp_LocHdr, LocHdr)
   GMC_DCL(boolean, UniqueFlag)
{
   (void)strcpy(StrBuf, "");
   /* Ident of RootFilHdr is NIL */
   if (Ident != NIL) {
      (void)strcat(StrBuf, Ident); }/*if*/;
   if (UniqueFlag) {
      if (StrBuf[0] != 0) {
	 (void)strcat(StrBuf, "."); }/*if*/;
      (void)sprintf(Tail(StrBuf), "%d", (int)LocHdr); }/*if*/;
   if (FilTyp != ObjectFilTyp) {
      if (StrBuf[0] != 0) {
	 (void)strcat(StrBuf, "."); }/*if*/;
      (void)strcat(StrBuf, FilTyp_ShortFTName(FilTyp)); }/*if*/;
   }/*Build_Label*/


tp_LocHdr
CacheFileName_LocHdr(
   GMC_ARG(tp_FileName, CacheFileName)
   )
   GMC_DCL(tp_FileName, CacheFileName)
{
   int i;

   i = strlen(CacheFileName);
   while (!(i < 0 || CacheFileName[i] == '/'
	    || CacheFileName[i] == '.' || CacheFileName[i] == ',')) {
      while (!((CacheFileName[i] == '.' || CacheFileName[i] == 0)
	       && isdigit(CacheFileName[i-1]))) {
	 if (i <= 0 || CacheFileName[i] == '/') {
	    return ERROR; }/*if*/;
	 i -= 1; }/*while*/;
      i -= 1;
      while (i >= 0 && isdigit(CacheFileName[i])) {
	 i -= 1; }/*while*/; }/*while*/;
   i += 1;
   return atoi(&CacheFileName[i]);
   }/*CacheFileName_LocHdr*/


void
SetFilHdr_DrvMarks(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   SetFilHdr_Marks(FilHdr, FALSE);
   }/*SetFilHdr_DrvMarks*/


void
SetFilHdr_Marks(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, PrmTypFlag)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, PrmTypFlag)
{
   tp_FilTyp FilTyp;
   tps_Str Ident, Label;

   FilTyp = FilHdr_FilTyp(FilHdr);
   SetFilTyp_Marks(FilTyp, TRUE, PrmTypFlag);
   if (IsList(FilHdr)) {
      SetFilTyp_Marks(ListFilTyp, TRUE, PrmTypFlag); }/*if*/;
   (void)strcpy(Ident, FilHdr_Ident(FilHdr));
   Key_InstanceLabel(Label, Ident);
   while (strcmp(Label, Ident) != 0) {
      SetFilTyp_Marks(Key_FilTyp(Label), TRUE, PrmTypFlag);
      (void)strcpy(Ident, Label);
      Key_InstanceLabel(Label, Ident); }/*while*/;
   }/*SetFilHdr_Marks*/


void
SetFilTyp_Marks(
   GMC_ARG(tp_FilTyp, FilTyp),
   GMC_ARG(boolean, CastFlag),
   GMC_ARG(boolean, PrmTypFlag)
   )
   GMC_DCL(tp_FilTyp, FilTyp)
   GMC_DCL(boolean, CastFlag)
   GMC_DCL(boolean, PrmTypFlag)
{
   if (FilTyp->Reach) return;
   FilTyp->Reach = TRUE;
   SetDrvEdg_Marks(FilTyp->DrvEdg, PrmTypFlag);
   SetEqvEdg_Marks(FilTyp->EqvEdg, CastFlag, PrmTypFlag) ;
   if (CastFlag) SetCastEdg_Marks(FilTyp->CastEdg, PrmTypFlag) ;
   }/*SetFilTyp_Marks*/


void
SetFilTyp_Mark(
   GMC_ARG(tp_FilTyp, FilTyp)
   )
   GMC_DCL(tp_FilTyp, FilTyp)
{
   FilTyp->Mark = TRUE;
   }/*SetFilTyp_Mark*/


void
WriteSrcFilTyps(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(boolean, IsPrefix)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(boolean, IsPrefix)
{
   int i;
   tp_SrcTyp SrcTyp;
   boolean Found;

   Found = FALSE;
   /*select*/{
      if (IsPrefix) {
	 Writeln(FilDsc, "?*? Known Prefix Types:");
      }else{
	 Writeln(FilDsc, "?*? Known Suffix Types:"); };}/*select*/;
   for (i=0; i<num_SrcTypS; i++) {
      SrcTyp = &SrcTypS[i];
      if ((IsPrefix == SrcTyp->IsPrefix)
	  && CurrentClient->HelpLevel >= SrcTyp->FilTyp->HelpLevel) {
	 WriteNameDesc(FilDsc, SrcTyp->Pattern, SrcTyp->FilTyp->Desc);
	 Found = TRUE; }/*if*/; }/*for*/;
   if (!Found) {
      Writeln(FilDsc, "(none)"); }/*if*/;
   }/*WriteSrcFilTyps*/


void
Clr_FilTypMarks(GMC_ARG_VOID)
{
   int i;

   for (i=0; i<num_FilTypS; i++) {
      FilTypS[i].Reach = FALSE;
      FilTypS[i].Mark = FALSE; }/*for*/;
   }/*Clr_FilTypMarks*/


void
WriteMarkedFilTyps(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   int i;
   tp_FilTyp FilTyp;
   boolean Found;

   Found = FALSE;
   for (i=0; i<num_FilTypS; i++) {
      FilTyp = &FilTypS[i];
      if (FilTyp->Mark && CurrentClient->HelpLevel >= FilTyp->HelpLevel
	  && !IsSecOrd_FilTyp(FilTyp)) {
	 WriteNameDesc(FilDsc, FilTyp->FTName, FilTyp->Desc);
	 Found = TRUE; }/*if*/; }/*for*/;
   if (!Found) {
      Writeln(FilDsc, "(none)"); }/*if*/;
   }/*WriteMarkedFilTyps*/


tp_FilTyp
Nod_FilTyp(
   GMC_ARG(tp_Nod, DrvTyp_Nod)
   )
   GMC_DCL(tp_Nod, DrvTyp_Nod)
{
   tp_Str Str, ArgStr;
   tp_FilTyp FilTyp;

   if (Nod_NodTyp(DrvTyp_Nod) == HODOPR) {
     Str = Sym_Str(Nod_Sym(Nod_Son(1, DrvTyp_Nod)));
     ArgStr = Sym_Str(Nod_Sym(Nod_Son(2, DrvTyp_Nod)));
     FilTyp = FTName_SecOrdFilTyp(Str, ArgStr);
     if (FilTyp == ERROR) {
       SystemError("No file type, <:%s=:%s>.\n", Str, ArgStr); }/*if*/;
     return FilTyp; }/*if*/;
     
   FORBIDDEN(Nod_NodTyp(DrvTyp_Nod) != WORD);
   Str = Sym_Str(Nod_Sym(DrvTyp_Nod));
   FilTyp = FTName_FilTyp(Str);
   if (FilTyp == ERROR) SystemError("No file type, <%s>.\n", Str);
   return FilTyp;
   }/*Nod_FilTyp*/


