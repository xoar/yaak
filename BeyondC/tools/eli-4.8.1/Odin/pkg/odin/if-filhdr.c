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
#include "inc/FilHdr.h"
#include "inc/HdrInf.h"
#include "inc/FilTyp.h"
#include "inc/FKind_.h"
#include "inc/LogLevel_.h"
#include "inc/Status_.h"
#include "inc/FileName.h"


int			num_FilHdrS = 0;

tp_FilHdr		ModFilHdr = NIL;

tp_FilHdr		RootFilHdr;
tp_FilHdr		NetRootFilHdr;
tp_FilHdr		OdinDirFilHdr;
tp_FilHdr		CacheDirFilHdr;
tp_FilHdr		PrmDataDirFilHdr;
tp_FilHdr		StrDirFilHdr;
tp_FilHdr		NilStrFilHdr;
tp_FilHdr		FlagPrmFilHdr;
tp_FilHdr		EmptyFilHdr;

tp_Ident		DfltIdent = NIL;

static tps_FilHdr _UsedFilHdr;
static tp_FilHdr		UsedFilHdr = &_UsedFilHdr;
static tps_FilHdr _FreeFilHdr;
static tp_FilHdr		FreeFilHdr = &_FreeFilHdr;


void
Init_FilHdrs(GMC_ARG_VOID)
{
   UsedFilHdr->PrevFree = UsedFilHdr;
   UsedFilHdr->NextFree = UsedFilHdr;

   FreeFilHdr->PrevFree = FreeFilHdr;
   FreeFilHdr->NextFree = FreeFilHdr;
   ModFilHdr = NIL;
   }/*Init_FilHdrs*/


void
Init_FilHdrTree(GMC_ARG_VOID)
{
   RootFilHdr = LocHdr_FilHdr(RootLocHdr);
   NetRootFilHdr = Do_Key(Copy_FilHdr(RootFilHdr), "");
   OdinDirFilHdr = HostFN_FilHdr(OdinDirName);
   CacheDirFilHdr = HostFN_FilHdr(CacheDirName);
   PrmDataDirFilHdr = Do_Key(Copy_FilHdr(OdinDirFilHdr), "PRM");
   StrDirFilHdr = Do_Key(Copy_FilHdr(OdinDirFilHdr), "STR");
   NilStrFilHdr = Extend_FilHdr(Copy_FilHdr(StrDirFilHdr), FK_Str,
				ObjectFilTyp, RootFilPrm, "");
   FlagPrmFilHdr = Str_FilHdr(" ", NullPrmTyp);
   EmptyFilHdr = Do_Key(Copy_FilHdr(OdinDirFilHdr), "EMPTY");
   }/*Init_FilHdrTree*/


tp_LocHdr
Alloc_HdrInf(GMC_ARG_VOID)
{
   return (tp_LocHdr) Alloc(sizeof(tps_HdrInf));
   }/*Alloc_HdrInf*/


static void
Transfer_FilHdr(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilHdr, FHLst)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilHdr, FHLst)
{
   FilHdr->PrevFree->NextFree = FilHdr->NextFree;
   FilHdr->NextFree->PrevFree = FilHdr->PrevFree;
   FilHdr->PrevFree = FHLst->PrevFree;
   FilHdr->NextFree = FHLst;
   FilHdr->PrevFree->NextFree = FilHdr;
   FilHdr->NextFree->PrevFree = FilHdr;
   }/*Transfer_FilHdr*/


tp_FilHdr
Copy_FilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return ERROR;
   if (FilHdr->Cnt == 0) {
      Transfer_FilHdr(FilHdr, UsedFilHdr); }/*if*/;
   FilHdr->Cnt += 1;
   return FilHdr;
   }/*Copy_FilHdr*/


void
Ret_FilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr == ERROR) return;
   FilHdr->Cnt -= 1;
   FORBIDDEN(FilHdr->Cnt < 0);
   }/*Ret_FilHdr*/


void
Free_FilHdrs(GMC_ARG_VOID)
{
   tp_FilHdr FilHdr, NextFilHdr;

   NextFilHdr = UsedFilHdr->NextFree;
   while (NextFilHdr != UsedFilHdr) {
      FilHdr = NextFilHdr;
      NextFilHdr = NextFilHdr->NextFree;
      if (FilHdr_PndFlag(FilHdr)) {
	 Do_Log("PndFlag clearing status of", FilHdr, LOGLEVEL_Status);
	 Set_PndFlag(FilHdr, FALSE);
	 Set_Status(FilHdr, STAT_Unknown); }/*if*/;
      if (FilHdr_ElmNamePndFlag(FilHdr)) {
	 Do_Log("PndFlag clearing elm-name-status of", FilHdr, LOGLEVEL_Status);
	 Set_ElmNamePndFlag(FilHdr, FALSE);
	 Set_ElmNameStatus(FilHdr, STAT_Unknown); }/*if*/;
      if (FilHdr_ElmPndFlag(FilHdr)) {
	 Do_Log("PndFlag clearing elm-status of", FilHdr, LOGLEVEL_Status);
	 Set_ElmPndFlag(FilHdr, FALSE);
	 Set_ElmStatus(FilHdr, STAT_Unknown); }/*if*/;
      if (FilHdr_TgtValPndFlag(FilHdr)) {
	 Do_Log("PndFlag clearing TgtVal-status of", FilHdr, LOGLEVEL_Status);
	 Set_TgtValPndFlag(FilHdr, FALSE);
	 Set_TgtValStatus(FilHdr, STAT_Unknown); }/*if*/;
      if (FilHdr_Status(FilHdr) == STAT_Ready) {
	 Set_Status(FilHdr, STAT_Unknown); }/*if*/;
      if (FilHdr->Cnt == 0) {
	 FORBIDDEN(FilHdr->Flag != 0);
	 FORBIDDEN(FilHdr->AnyOKDepth != 0);
	 FORBIDDEN(FilHdr->ElmDepth != 0);
	 FORBIDDEN(FilHdr->ElmTag != 0);
	 FORBIDDEN(FilHdr->SCC != NIL);
	 Transfer_FilHdr(FilHdr, FreeFilHdr); }/*if*/; }/*while*/;
   }/*Free_FilHdrs*/


static void
UnHash_FilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   FORBIDDEN(FilHdr->Modified);
   UnHash_Item((tp_Item)FilHdr);
   FilHdr->FilPrm = ERROR;
   }/*UnHash_FilHdr*/


tp_FilHdr
New_FilHdr(GMC_ARG_VOID)
{
   tp_FilHdr FilHdr;

   FilHdr = FreeFilHdr->NextFree;
   /*select*/{
      if (FilHdr == FreeFilHdr) {
	 FilHdr = (tp_FilHdr)malloc(sizeof(tps_FilHdr));
	 num_FilHdrS += 1;
	 FilHdr->FilTyp = ERROR;
	 FilHdr->FilPrm = ERROR;
	 FilHdr->Ident = ERROR;
	 FilHdr->Cnt = 0;
	 FilHdr->PrevFree = FreeFilHdr->PrevFree;
	 FilHdr->PrevFree->NextFree = FilHdr;
	 FilHdr->NextFree = FreeFilHdr;
	 FilHdr->NextFree->PrevFree = FilHdr;
	 FilHdr->Modified = FALSE;
	 FilHdr->NextMod = NIL;
	 FilHdr->Flag = NIL;
	 FilHdr->AnyOKDepth = 0;
	 FilHdr->ElmDepth = 0;
	 FilHdr->ElmTag = 0;
	 FilHdr->SCC = (tp_FilHdr)NIL;
	 FilHdr->PndFlag = FALSE;
	 FilHdr->ElmNamePndFlag = FALSE;
	 FilHdr->ElmPndFlag = FALSE;
      }else if (FilHdr->LocHdr != NIL) {
	 FORBIDDEN(FilHdr->Cnt != 0);
	 if (FilHdr->Modified) WriteFilHdrs();
	 FORBIDDEN(FilHdr->Modified);
	 UnHash_FilHdr(FilHdr); };}/*select*/;
   FilHdr->LocHdr = NIL;
   FilHdr->DepStatus = STAT_Unknown;
   FilHdr->DepModDate = 0;
   return Copy_FilHdr(FilHdr);
   }/*New_FilHdr*/


static tp_FilHdr
Lookup_FilHdr(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   return Copy_FilHdr((tp_FilHdr)Lookup_Item(LocHdr));
   }/*Lookup_FilHdr*/


tp_FilHdr
LocHdr_FilHdr(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;
   tps_HdrInf HdrInfBuf;
   tp_HdrInf HdrInf;
   tp_FilTyp FilTyp;

   if (LocHdr == ERROR) {
      return (tp_FilHdr)ERROR; }/*if*/;

   if (LocHdr <= 0 || LocHdr > LastLoc) {
      SystemError("Bad cache object id: %d.\n", LocHdr);
      return (tp_FilHdr)ERROR; }/*if*/;

   FilHdr = Lookup_FilHdr(LocHdr);
   if (FilHdr != ERROR) {
      return FilHdr; }/*if*/;

   ReadHdrInf(&HdrInfBuf, LocHdr);
   if (HdrInfBuf.LocHdr != LocHdr) {
      SystemError("Illegal database id: %d.\n", LocHdr);
      return ERROR; }/*if*/;
   FilHdr = New_FilHdr();
   Hash_Item((tp_Item)FilHdr, (tp_Loc)LocHdr);
   FilHdr->HdrInf = HdrInfBuf;
   HdrInf = &(FilHdr->HdrInf);
   FilTyp = IFilTyp_FilTyp(HdrInf->IFilTyp);
   FORBIDDEN(FilTyp == ERROR);
   FilHdr->FilTyp = FilTyp;
   FilHdr->Ident = ReadStr(HdrInf->LocIdent);
   FilHdr->FilPrm = LocPrm_FilPrm(HdrInf->LocPrm);
   FORBIDDEN(FilHdr->FilPrm == ERROR);
   return FilHdr;
   }/*LocHdr_FilHdr*/


void
Init_HdrInf(
   GMC_ARG(tp_HdrInf, HdrInf)
   )
   GMC_DCL(tp_HdrInf, HdrInf)
{
   HdrInf->LocHdr = NIL;
   HdrInf->DataNum = 0;
   HdrInf->LocInp = NIL;
   HdrInf->Father = NIL;
   HdrInf->Brother = NIL;
   HdrInf->Son = NIL;

   HdrInf->LocElm = NIL;
   HdrInf->OldLocElm = NIL;
   HdrInf->TgtValLocElm = NIL;
   HdrInf->InpLink = NIL;
   HdrInf->ElmLink = NIL;

   HdrInf->FKind = ERROR;
   HdrInf->LocIdent = NIL;
   HdrInf->Status = STAT_Unknown;
   HdrInf->ElmNameStatus = STAT_Unknown;
   HdrInf->ElmStatus = STAT_Unknown;
   HdrInf->ErrStatusWord = 0;
   HdrInf->SysModTime = 0;
   HdrInf->ModDate = 0;
   HdrInf->ElmNameModDate = 0;
   HdrInf->ElmModDate = 0;
   HdrInf->ConfirmDate = 0;
   HdrInf->ElmNameConfirmDate = 0;
   HdrInf->ElmConfirmDate = 0;
   HdrInf->VerifyDate = 0;
   HdrInf->ElmNameVerifyDate = 0;
   HdrInf->ElmVerifyDate = 0;
   HdrInf->Size = -1;
   HdrInf->OrigLocHdr = NIL;
   HdrInf->OrigModDate = 0;
   HdrInf->AliasLocHdr = NIL;
   }/*Init_HdrInf*/


void
SetModified(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   if (FilHdr->Modified) return;
   FilHdr->Modified = TRUE;
   FilHdr->NextMod = ModFilHdr;
   ModFilHdr = FilHdr;
   }/*SetModified*/


static void
WriteFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   WriteHdrInf(&(FilHdr->HdrInf), FilHdr->LocHdr);
   }/*WriteFilHdr*/


void
WriteFilHdrs(GMC_ARG_VOID)
{
   while (ModFilHdr != NIL) {
      FORBIDDEN(!ModFilHdr->Modified);
      ModFilHdr->Modified = FALSE;
      WriteFilHdr(ModFilHdr);
      ModFilHdr = ModFilHdr->NextMod; }/*while*/;
   }/*WriteFilHdrs*/


boolean
FilHdrs_InUse(GMC_ARG_VOID)
{
   tp_FilHdr FilHdr;

   FilHdr = UsedFilHdr->NextFree;
   while (FilHdr != UsedFilHdr) {
      Write(StdOutFD, "LocHdr=");
      WriteInt(StdOutFD, (int)FilHdr->LocHdr);
      Write(StdOutFD, ", Cnt=");
      WriteInt(StdOutFD, FilHdr->Cnt);
      Write(StdOutFD, ", Flag=");
      WriteInt(StdOutFD, FilHdr->Flag);
      Writeln(StdOutFD, "");
      FilHdr = FilHdr->NextFree; }/*while*/;
   return (UsedFilHdr->NextFree != UsedFilHdr);
   }/*FilHdrs_InUse*/


void
CleanUp(GMC_ARG_VOID)
{
   Update_Info();
   Free_FilHdrs();
   Free_FilInps();
   Free_FilElms();
   }/*CleanUp*/


