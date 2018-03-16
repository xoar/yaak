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
#include "inc/FileName.h"
#include "inc/FilHdr.h"
#include "inc/FKind_.h"
#include "inc/Flag_.h"
#include "inc/SKind_.h"
#include "inc/Status_.h"
#include "inc/Str.h"


tp_Date		PendingDate = 0;


boolean
IsSource_FKind(
   GMC_ARG(tp_FKind, FKind)
   )
   GMC_DCL(tp_FKind, FKind)
{
   switch (FKind) {
      case FK_SrcReg: case FK_SrcDir: case FK_SymLinkReg: case FK_SymLinkDir:
      case FK_BoundSrc: case FK_BoundSymLink: {
	 return TRUE; }/*case*/;
      case FK_User: case FK_Instance: case FK_Str:
      case FK_DrvDirElm: case FK_VirDirElm:
      case FK_PntrHo: case FK_InpPntr: case FK_PntrElm:
      case FK_ActTgtText: case FK_VirTgtText:
      case FK_ActTgtExText: case FK_VirTgtExText:
      case FK_VirTgt: case FK_VirCmdTgt: case FK_ActTgt: case FK_ActCmdTgt: {
	 return FALSE; }/*case*/;
      default: {
	 FATALERROR("unknown FKind"); };}/*switch*/;
   /* NOTREACHED */
   return FALSE;
   }/*IsSource_FKind*/


boolean
IsSource(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return IsSource_FKind(FilHdr->HdrInf.FKind);
   }/*IsSource*/


boolean
IsSymLink(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_SymLinkReg
	   || FilHdr->HdrInf.FKind == FK_SymLinkDir
	   || FilHdr->HdrInf.FKind == FK_BoundSymLink);
   }/*IsSymLink*/


boolean
IsDir(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_SrcDir
	   || FilHdr->HdrInf.FKind == FK_SymLinkDir);
   }/*IsDir*/


boolean
IsStr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_Str);
   }/*IsStr*/


boolean
IsBound(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_BoundSrc
	   || FilHdr->HdrInf.FKind == FK_BoundSymLink);
   }/*IsBound*/


boolean
IsATgt(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return IsATgt_FKind(FilHdr->HdrInf.FKind);
   }/*IsATgt*/


boolean
IsVTgt(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return IsVTgt_FKind(FilHdr->HdrInf.FKind);
   }/*IsVTgt*/


boolean
IsVTgtText(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return IsVTgtText_FKind(FilHdr->HdrInf.FKind);
   }/*IsVTgtText*/


boolean
IsDfltTgtVal(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->FilTyp == ActTargetsFilTyp);
   }/*IsDfltTgtVal*/


boolean
IsPntr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FKind FKind;

   FORBIDDEN(FilHdr == ERROR);
   FKind = FilHdr->HdrInf.FKind;
   return (IsPntr_FKind(FKind)
	   || (FKind == FK_User && IsPntr_FilTyp(FilHdr->FilTyp)));
   }/*IsPntr*/


boolean
IsGeneric(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_User
	   && IsGeneric_FilTyp(FilHdr->FilTyp));
   }/*IsGeneric*/


boolean
IsPipe(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_User
	   && IsPipe_FilTyp(FilHdr->FilTyp));
   }/*IsPipe*/


boolean
IsInstance(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_Instance);
   }/*IsInstance*/


boolean
IsAtmc(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   switch (FilHdr->HdrInf.FKind) {
      case FK_SrcReg: case FK_SrcDir: case FK_SymLinkReg: case FK_SymLinkDir:
      case FK_BoundSrc: case FK_BoundSymLink:
      case FK_DrvDirElm: case FK_Instance:
      case FK_ActTgtText: case FK_VirTgtText:
      case FK_ActTgtExText: case FK_VirTgtExText: {
	 return TRUE; }/*case*/;
      case FK_User: case FK_Str: {
	 return IsAtmc_FilTyp(FilHdr->FilTyp); }/*case*/;
      case FK_ActTgt: case FK_ActCmdTgt: case FK_VirTgt: case FK_VirCmdTgt:
      case FK_PntrHo: case FK_PntrElm: case FK_InpPntr: case FK_VirDirElm: {
	 return FALSE; }/*case*/;
      default: {
	 FATALERROR("Unexpected FKind"); };}/*switch*/;
   /*NOTREACHED*/
   return FALSE;
   }/*IsAtmc*/


boolean
IsList(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_User
	   && IsList_FilTyp(FilHdr->FilTyp));
   }/*IsList*/


boolean
IsViewSpec(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_User
	   && FilHdr->FilTyp == ViewSpecFilTyp);
   }/*IsViewSpec*/


boolean
IsStruct(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return IsStruct_FilTyp(FilHdr->FilTyp);
   }/*IsStruct*/


boolean
IsStructMem(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return IsStructMem_FilTyp(FilHdr->FilTyp);
   }/*IsStructMem*/


boolean
IsVoid(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (IsStr(FilHdr) || IsVoid_FilTyp(FilHdr->FilTyp));
   }/*IsVoid*/


boolean
IsTargetsPtr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return (FilHdr->FilTyp == TargetsPtrFilTyp);
   }/*IsTargetsPtr*/


boolean
IsTargets(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return (FilHdr->FilTyp == TargetsFilTyp);
   }/*IsTargets*/


boolean
IsDrvDir(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return IsDrvDir_FilTyp(FilHdr->FilTyp);
   }/*IsDrvDir*/


boolean
IsDrvDirElm(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_DrvDirElm);
   }/*IsDrvDirElm*/


boolean
IsVirDir(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return (FilHdr->FilTyp == VirDirFilTyp);
   }/*IsVirDir*/


boolean
IsKeyList(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilTyp FilTyp;

   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   FilTyp = FilHdr->FilTyp;
   return ((IsDrvDir_FilTyp(FilTyp) && FilTyp != VirDirFilTyp)
	   || FilTyp == ActTargetsFilTyp || FilTyp == VirTargetsFilTyp);
   }/*IsKeyList*/


boolean
IsKeyListElm(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (FilHdr->HdrInf.FKind == FK_DrvDirElm
	   || FilHdr->HdrInf.FKind == FK_VirDirElm
	   || IsATgt_FKind(FilHdr->HdrInf.FKind)
	   || IsVTgt_FKind(FilHdr->HdrInf.FKind));
   }/*IsKeyListElm*/


boolean
IsCopy(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.FKind != FK_User) {
      return FALSE; }/*if*/;
   return IsCopy_FilTyp(FilHdr->FilTyp);
   }/*IsCopy*/


boolean
IsAutoExec(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr TgtValFilHdr;
   boolean Flag;

   if (IsExec_FilTyp(FilHdr->FilTyp)
       || FilHdr->HdrInf.FKind == FK_ActCmdTgt
       || FilHdr->HdrInf.FKind == FK_VirCmdTgt) {
      return TRUE; }/*if*/;
   if (!IsBound(FilHdr)) {
      return FALSE; }/*if*/;
   TgtValFilHdr = FilHdr_Father(FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr)));
   FORBIDDEN(TgtValFilHdr == NIL);
   Flag = IsAutoExec(TgtValFilHdr);
   Ret_FilHdr(TgtValFilHdr);
   return Flag;
   }/*IsAutoExec*/


boolean
HasKey_FKind(
   GMC_ARG(tp_FKind, FKind)
   )
   GMC_DCL(tp_FKind, FKind)
{
   FORBIDDEN(FKind == ERROR);
   return (FKind == FK_DrvDirElm || FKind == FK_VirDirElm
	   || FKind == FK_PntrElm || IsSource_FKind(FKind)
	   || IsATgt_FKind(FKind) || IsVTgt_FKind(FKind)
	   || IsATgtText_FKind(FKind) || IsVTgtText_FKind(FKind));
   }/*HasKey_FKind*/


boolean
IsRef(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return (IsList(FilHdr) || IsPntr(FilHdr));
   }/*IsRef*/


tp_LocHdr
FilHdr_LocHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   return FilHdr->LocHdr;
   }/*FilHdr_LocHdr*/


tp_LocHdr
FilHdr_AliasLocHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   return FilHdr->HdrInf.AliasLocHdr;
   }/*FilHdr_AliasLocHdr*/


void
Set_AliasLocHdr(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_LocHdr, LocHdr)
{

   FORBIDDEN(FilHdr == ERROR);
   if (LocHdr == FilHdr->HdrInf.AliasLocHdr) {
      return; }/*if*/;
   FilHdr->HdrInf.AliasLocHdr = LocHdr;
   SetModified(FilHdr);
   }/*Set_AliasLocHdr*/


tp_FilHdr
FilHdr_AliasFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr AliasFilHdr;

   if (FilHdr->HdrInf.AliasLocHdr == NIL) {
      return FilHdr; }/*if*/;
   AliasFilHdr = LocHdr_FilHdr(FilHdr->HdrInf.AliasLocHdr);
   Ret_FilHdr(FilHdr);
   FORBIDDEN(AliasFilHdr->HdrInf.AliasLocHdr != NIL);
   return AliasFilHdr;
   }/*FilHdr_AliasFilHdr*/


tp_FKind
FilHdr_FKind(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   return FilHdr->HdrInf.FKind;
   }/*FilHdr_FKind*/


void
Set_FKind(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FKind, FKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FKind, FKind)
{
   FORBIDDEN(FilHdr == ERROR || FKind == ERROR);
   if (FilHdr->HdrInf.FKind != FKind) {
      FilHdr->HdrInf.FKind = FKind;
      SetModified(FilHdr); }/*if*/;
   }/*Set_FKind*/


tp_FilTyp
FilHdr_FilTyp(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   return FilHdr->FilTyp;
   }/*FilHdr_FilTyp*/


tp_FilPrm
FilHdr_FilPrm(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   FORBIDDEN(FilHdr->FilPrm == NIL);
   return FilHdr->FilPrm;
   }/*FilHdr_FilPrm*/


tp_Ident
FilHdr_Ident(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   return FilHdr->Ident;
   }/*FilHdr_Ident*/


void
Update_SrcFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, InitOnly)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, InitOnly)
{
   tp_Date OldModDate;
   boolean Changed;
   tp_SKind SKind;
   tp_FKind FKind;
   tp_HdrInf HdrInf;
   tp_Status Status;
   tps_FileName FileName, SymLinkFileName;
   int SysModTime;
   tp_FilHdr DirFilHdr, SymLinkFH;
   tp_FilElm FilElm;
   tp_LocHdr SymLocHdr;


   FORBIDDEN(FilHdr == ERROR);
   FORBIDDEN(!IsSource(FilHdr));
   HdrInf = &(FilHdr->HdrInf);

   if (FilHdr == RootFilHdr) {
      Set_Status(FilHdr, STAT_OK);
      return; }/*if*/;

   if (FilHdr_Flag(FilHdr, FLAG_SymLink)) {
      Set_Status(FilHdr, STAT_Circular);
      return; }/*if*/;
   Set_Flag(FilHdr, FLAG_SymLink);

   OldModDate = HdrInf->ModDate;
   IsAny_ReadyServerAction = TRUE;

   DirFilHdr = FilHdr_Father(Copy_FilHdr(FilHdr));
   if (!IsSrcUpToDate(DirFilHdr)) {
      Update_SrcFilHdr(DirFilHdr, InitOnly); }/*if*/;

   Changed = FALSE;
   SymLinkFH = NIL;
   /*select*/{
      if (IsSymLink(DirFilHdr)) {
	 SymLinkFH = Extend_FilHdr
	    (Deref_SymLink(Copy_FilHdr(DirFilHdr)), FK_SrcReg,
	     FilHdr->FilTyp, RootFilPrm, FilHdr->Ident);
      }else{
	 FilHdr_DataFileName(FileName, FilHdr);
	 Get_FileInfo(&SKind, &SysModTime, FileName);
	 if (HdrInf->SysModTime != SysModTime || HdrInf->ModDate == 0) {
	    Changed = TRUE; }/*if*/;
	 switch (SKind) {
	    case SK_NoFile: case SK_Reg: case SK_Exec: case SK_Special: {
	       FKind = (IsBound(FilHdr) ? FK_BoundSrc : FK_SrcReg);
	       Status = ((SKind == SK_NoFile) ? STAT_NoFile : STAT_OK);
	       break;}/*case*/;
	    case SK_Dir: {
	       FKind = FK_SrcDir;
	       Status = STAT_OK; break;}/*case*/;
	    case SK_SymLink: {
	       Push_ContextFilHdr(Copy_FilHdr(DirFilHdr));
	       FileName_SymLinkFileName(SymLinkFileName, FileName);
	       SymLinkFH = HostFN_FilHdr(SymLinkFileName);
	       /*select*/{
		  if (SymLinkFH == ERROR) {
		     FKind = FK_SrcReg;
		     Status = STAT_NoFile;
		  }else if (!IsSource(SymLinkFH)) {
		     SystemError("Symbolic link into cache ignored: %s\n",
				 SymLinkFileName);
		     Ret_FilHdr(SymLinkFH);
		     SymLinkFH = ERROR;
		     FKind = FK_SrcReg;
		     Status = STAT_NoFile; };}/*select*/;
	       Pop_ContextFilHdr(); break;}/*case*/;
	    default: {
	       FATALERROR("Unexpected SKind"); };}/*switch*/; };}/*select*/;

   if (SymLinkFH != NIL) {
      if (!IsSrcUpToDate(SymLinkFH)) {
	 Update_SrcFilHdr(SymLinkFH, InitOnly); }/*if*/;
      SymLinkFH = Deref_SymLink(SymLinkFH);
      if (!IsSrcUpToDate(SymLinkFH)) {
	 Update_SrcFilHdr(SymLinkFH, InitOnly); }/*if*/;
      SymLinkFH = Deref_SymLink(SymLinkFH);
      if (HdrInf->ModDate < SymLinkFH->HdrInf.ModDate) {
	 Changed = TRUE; }/*if*/;

      FilElm = LocElm_FilElm(HdrInf->LocElm);
      SymLocHdr = FilElm_LocHdr(FilElm);
      Ret_FilElm(FilElm);
      if (SymLocHdr != SymLinkFH->LocHdr) {
	 Set_LocElm(FilHdr, Make_LocElm(SymLinkFH, RootFilPrm, FilHdr));
	 Changed = TRUE; }/*if*/;

      if (HdrInf->AliasLocHdr != NIL) {
	 if (SymLinkFH->HdrInf.AliasLocHdr == NIL) {
	    Set_AliasLocHdr(SymLinkFH, HdrInf->AliasLocHdr); }/*if*/;
	 Set_AliasLocHdr(FilHdr, (tp_LocHdr)NIL); }/*if*/;

      FKind = (IsBound(FilHdr) ? FK_BoundSymLink :
	       (IsDir(SymLinkFH) ? FK_SymLinkDir : FK_SymLinkReg));
      Status = SymLinkFH->HdrInf.Status;
      Ret_FilHdr(SymLinkFH); }/*if*/;

   if (HdrInf->FKind == FK_SrcDir && FKind == FK_SymLinkDir) {
      FilHdr_Error("<%s> has changed from a directory to a symbolic link.\n",
		   FilHdr);
      SystemError("The cache should be reset with the -r option.\n");
      FKind = FK_SrcDir; }/*if*/;

   if (Changed || HdrInf->FKind != FKind) {
      Set_ModDate(FilHdr);
      HdrInf->SysModTime = SysModTime;
      HdrInf->FKind = FKind;
      if (!IsSymLink(FilHdr)) {
	 Set_LocElm(FilHdr, (tp_LocElm)NIL); }/*if*/; }/*if*/;

   /*select*/{
      if (IsDir(FilHdr)) {
	 Set_TgtValLocElm(FilHdr, (tp_LocElm)NIL);
      }else if (FilHdr_TgtValLocElm(FilHdr) == NIL) {
	 Set_DfltTgtValLocElm(FilHdr); };}/*select*/;

   if (OldModDate != 0
       && (HdrInf->ModDate != OldModDate
	   || (HdrInf->Status != STAT_Unknown && HdrInf->Status != Status))) {
      /*select*/{
	 if (InitOnly) {
	    Push_ToBroadcast(Copy_FilHdr(FilHdr));
	 }else{
	    Broadcast(FilHdr, STAT_Unknown);};}/*select*/; }/*if*/;

   Ret_FilHdr(DirFilHdr);
   Set_Status(FilHdr, Status);
   Clr_Flag(FilHdr, FLAG_SymLink);
   }/*Update_SrcFilHdr*/


void
FilHdr_Error(
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tps_Str ObjName;

   SPrint_FilHdr(ObjName, FilHdr);
   SystemError(Str, ObjName);
   }/*FilHdr_Error*/


boolean
IsAllDone(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   return (IsAllUpToDate(FilHdr, InpKind)
	   && !Is_PRB_Status(FilHdr_MinStatus(FilHdr, InpKind)));
   }/*IsAllDone*/


boolean
IsAllUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   if (!IsUpToDate(FilHdr)) {
      return FALSE; }/*if*/;
   if (!IsTgtValUpToDate(FilHdr)) {
      return FALSE; }/*if*/;
   if (NeedsElmData(FilHdr, InpKind)) {
      return IsElmUpToDate(FilHdr); }/*if*/;
   if (NeedsElmNameData(FilHdr, InpKind)) {
      return IsElmNameUpToDate(FilHdr); }/*if*/;
   return TRUE;
   }/*IsAllUpToDate*/


boolean
IsSrcUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.VerifyDate < VerifyDate) {
      return FALSE; }/*if*/;
   return (FilHdr->HdrInf.Status > STAT_Unknown);
   }/*IsSrcUpToDate*/


boolean
IsUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (FilHdr->HdrInf.VerifyDate < VerifyDate) {
      return FALSE; }/*if*/;
   if (!IsTgtValUpToDate(FilHdr)
       || ((Is_PRB_Status(FilHdr->HdrInf.Status) || FilHdr->PndFlag)
	   && FilHdr->HdrInf.VerifyDate < PendingDate)) {
      return FALSE; }/*if*/;
   return (FilHdr->HdrInf.Status > STAT_Unknown);
   }/*IsUpToDate*/


boolean
IsElmNameUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   FORBIDDEN(!IsRef(FilHdr));
   if (FilHdr->HdrInf.Status <= STAT_Error) {
      return TRUE; }/*if*/;
   if (FilHdr->HdrInf.ElmNameVerifyDate < VerifyDate) {
      return FALSE; }/*if*/;
   if ((Is_PRB_Status(FilHdr->HdrInf.ElmNameStatus) || FilHdr->ElmNamePndFlag)
       && FilHdr->HdrInf.ElmNameVerifyDate < PendingDate) {
      return FALSE; }/*if*/;
   return (FilHdr->HdrInf.ElmNameStatus > STAT_Unknown);
   }/*IsElmNameUpToDate*/


boolean
IsElmUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   FORBIDDEN(!IsRef(FilHdr));
   if (FilHdr->HdrInf.Status <= STAT_Error) {
      return TRUE; }/*if*/;
   if (FilHdr->HdrInf.ElmVerifyDate < VerifyDate) {
      return FALSE; }/*if*/;
   if ((Is_PRB_Status(FilHdr->HdrInf.ElmStatus) || FilHdr->ElmPndFlag)
       && FilHdr->HdrInf.ElmVerifyDate < PendingDate) {
      return FALSE; }/*if*/;
   return (FilHdr->HdrInf.ElmStatus > STAT_Unknown);
   }/*IsElmUpToDate*/


boolean
IsTgtValUpToDate(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);
   if (!IsSource(FilHdr)) {
      return TRUE; }/*if*/;
   if (FilHdr->HdrInf.ElmVerifyDate < VerifyDate) {
      return FALSE; }/*if*/;
   if ((Is_PRB_Status(FilHdr->HdrInf.ElmStatus) || FilHdr->ElmPndFlag)
       && FilHdr->HdrInf.ElmVerifyDate < PendingDate) {
      return FALSE; }/*if*/;
   return (FilHdr->HdrInf.ElmStatus > STAT_Unknown);
   }/*IsTgtValUpToDate*/


tp_FilHdr
FilHdr_Father(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_LocHdr FatherLocHdr;

   FORBIDDEN(FilHdr == ERROR);
   FatherLocHdr = FilHdr->HdrInf.Father;
   Ret_FilHdr(FilHdr);
   return LocHdr_FilHdr(FatherLocHdr);
   }/*FilHdr_Father*/


tp_FilHdr
FilHdr_SrcFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_LocHdr SrcLocHdr;

   while (!IsSource(FilHdr)) {
      SrcLocHdr = FilHdr->HdrInf.Father;
      FORBIDDEN(SrcLocHdr == ERROR);
      Ret_FilHdr(FilHdr);
      FilHdr = LocHdr_FilHdr(SrcLocHdr); }/*while*/;
   return FilHdr;
   }/*FilHdr_SrcFilHdr*/


tp_FilHdr
FilHdr_DirFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr DirFilHdr;

   DirFilHdr = FilHdr_SrcFilHdr(FilHdr);
   if (DirFilHdr == RootFilHdr) {
      return DirFilHdr; }/*if*/;
   return FilHdr_Father(DirFilHdr);
   }/*FilHdr_DirFilHdr*/


tp_Str
FilHdr_Key(
   GMC_ARG(tp_Str, StrBuf),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_Str, StrBuf)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr == ERROR);

   if (!HasKey_FKind(FilHdr->HdrInf.FKind)) {
      return NIL; }/*if*/;
   return FilHdr_Label(StrBuf, FilHdr, FALSE);
   }/*FilHdr_Key*/


tp_Label
FilHdr_Label(
   GMC_ARG(tp_Str, StrBuf),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, UniqueFlag)
   )
   GMC_DCL(tp_Str, StrBuf)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, UniqueFlag)
{
   FORBIDDEN(FilHdr == ERROR);

   if (HasKey_FKind(FilHdr_FKind(FilHdr)) && !UniqueFlag) {
      (void)strcpy(StrBuf, FilHdr->Ident);
      return StrBuf; }/*if*/;
   Build_Label(StrBuf, FilHdr->Ident, FilHdr->FilTyp, FilHdr_LocHdr(FilHdr),
	       UniqueFlag);
   return StrBuf;
   }/*FilHdr_Label*/


tp_FilHdr
FilHdr_ElmFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilElm FilElm;
   tp_FilHdr ElmFilHdr;

   FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
   FORBIDDEN(FilElm != NIL && FilElm_Next(FilElm) != NIL);
   ElmFilHdr = FilElm_FilHdr(FilElm);
   Ret_FilHdr(FilHdr); Ret_FilElm(FilElm);
   return ElmFilHdr;
   }/*FilHdr_ElmFilHdr*/

