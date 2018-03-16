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
#include "inc/FilElm.h"
#include "inc/ElmInf.h"


int		num_FilElmS = 0;

tp_FilElm	ModFilElm = NIL;

static tps_FilElm _UsedFilElm;
static tp_FilElm		UsedFilElm = &_UsedFilElm;
static tps_FilElm _FreeFilElm;
static tp_FilElm		FreeFilElm = &_FreeFilElm;


void
Init_FilElms(GMC_ARG_VOID)
{
   UsedFilElm->PrevFree = UsedFilElm;
   UsedFilElm->NextFree = UsedFilElm;

   FreeFilElm->PrevFree = FreeFilElm;
   FreeFilElm->NextFree = FreeFilElm;
   }/*Init_FilElms*/


static void
Transfer_FilElm(
   GMC_ARG(tp_FilElm, FilElm),
   GMC_ARG(tp_FilElm, FilElmLst)
   )
   GMC_DCL(tp_FilElm, FilElm)
   GMC_DCL(tp_FilElm, FilElmLst)
{
   FilElm->PrevFree->NextFree = FilElm->NextFree;
   FilElm->NextFree->PrevFree = FilElm->PrevFree;
   FilElm->PrevFree = FilElmLst->PrevFree;
   FilElm->NextFree = FilElmLst;
   FilElm->PrevFree->NextFree = FilElm;
   FilElm->NextFree->PrevFree = FilElm;
   }/*Transfer_FilElm*/


static tp_FilElm
Copy_FilElm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   if (FilElm == ERROR) return ERROR;
   if (FilElm->Cnt == 0) {
      Transfer_FilElm(FilElm, UsedFilElm); }/*if*/;
   FilElm->Cnt += 1;
   return FilElm;
   }/*Copy_FilElm*/


void
Ret_FilElm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   if (FilElm == ERROR) return;
   FilElm->Cnt -= 1;
   FORBIDDEN(FilElm->Cnt < 0);
   }/*Ret_FilElm*/


void
Free_FilElms(GMC_ARG_VOID)
{
   tp_FilElm FilElm, NextFilElm;

   NextFilElm = UsedFilElm->NextFree;
   while (NextFilElm != UsedFilElm) {
      FilElm = NextFilElm;
      NextFilElm = NextFilElm->NextFree;
      if (FilElm->Cnt == 0) {
	 Transfer_FilElm(FilElm, FreeFilElm); }/*if*/; }/*while*/;
   }/*Free_FilElms*/


static void
UnHash_FilElm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   UnHash_Item((tp_Item)FilElm);
   FilElm->FilPrm = ERROR;
   }/*UnHash_FilElm*/


static tp_FilElm
New_FilElm(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_FilElm FilElm;
   tp_ElmInf ElmInf;

   FilElm = FreeFilElm->NextFree;
   /*select*/{
      if (FilElm == FreeFilElm) {
	 FilElm = (tp_FilElm)malloc(sizeof(tps_FilElm));
	 num_FilElmS += 1;
	 ElmInf = &(FilElm->ElmInf);
	 ElmInf->LocHdr = NIL;
	 ElmInf->BackLink = NIL;
	 ElmInf->Link = NIL;
	 ElmInf->LocPrm = NIL;
	 ElmInf->ListLocHdr = NIL;
	 ElmInf->Next = NIL;
	 
	 FilElm->LocElm = NIL;
	 FilElm->FilPrm = NIL;
	 FilElm->Cnt = 0;
	 FilElm->Modified = FALSE;
	 FilElm->PrevFree = FreeFilElm->PrevFree;
	 FilElm->NextFree = FreeFilElm;
	 FilElm->PrevFree->NextFree = FilElm;
	 FilElm->NextFree->PrevFree = FilElm;
      }else if (FilElm->LocElm != NIL) {
	 FORBIDDEN(FilElm->Cnt != 0);
	 if (FilElm->Modified) WriteFilElms();
	 FORBIDDEN(FilElm->Modified);
	 UnHash_FilElm(FilElm); };}/*select*/;
   Hash_Item((tp_Item)FilElm, (tp_Loc)LocElm);
   return Copy_FilElm(FilElm);
   }/*New_FilElm*/


static tp_FilElm
Lookup_FilElm(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   return Copy_FilElm((tp_FilElm)Lookup_Item(LocElm));
   }/*Lookup_FilElm*/


tp_FilElm
LocElm_FilElm(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_FilElm FilElm;
   tp_ElmInf ElmInf;

   if (LocElm == ERROR) {
      return ERROR; }/*if*/;

   FilElm = Lookup_FilElm(LocElm);
   if (FilElm != ERROR) {
      return FilElm; }/*if*/;

   FilElm = New_FilElm(LocElm);
   ElmInf = &(FilElm->ElmInf);
   ReadElmInf(ElmInf, LocElm);
   return FilElm;
   }/*LocElm_FilElm*/


static void
SetFilElmModified(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   if (FilElm->Modified) return;
   FilElm->Modified = TRUE;
   FilElm->NextMod = ModFilElm;
   ModFilElm = FilElm;
   }/*SetFilElmModified*/


static void
WriteFilElm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   WriteElmInf(&(FilElm->ElmInf), FilElm->LocElm);
   }/*WriteFilElm*/


void
WriteFilElms(GMC_ARG_VOID)
{
   while (ModFilElm != NIL) {
      FORBIDDEN(!ModFilElm->Modified);
      ModFilElm->Modified = FALSE;
      WriteFilElm(ModFilElm);
      ModFilElm = ModFilElm->NextMod; }/*while*/;
   }/*WriteFilElms*/


static void
Link_LocElm(
   GMC_ARG(tp_LocElm, LocElm),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_LocElm, LocElm)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilElm FilElm, RiteFilElm, LeftFilElm;
   tp_ElmInf ElmInf;
   tp_LocElm RiteLocElm, LeftLocElm;

   RiteLocElm = FilHdr_ElmLink(FilHdr);
   /*select*/{
      if (RiteLocElm == NIL) {
	 Set_ElmLink(FilHdr, LocElm);
	 LeftLocElm = LocElm;
	 RiteLocElm = LocElm;
      }else{
	 RiteFilElm = LocElm_FilElm(RiteLocElm);
	 FORBIDDEN(RiteFilElm->ElmInf.LocHdr != FilHdr_LocHdr(FilHdr));
	 LeftLocElm = RiteFilElm->ElmInf.BackLink;
	 RiteFilElm->ElmInf.BackLink = LocElm;
	 SetFilElmModified(RiteFilElm);
	 Ret_FilElm(RiteFilElm);

	 LeftFilElm = LocElm_FilElm(LeftLocElm);
	 LeftFilElm->ElmInf.Link = LocElm;
	 SetFilElmModified(LeftFilElm);
	 Ret_FilElm(LeftFilElm);
	 };}/*select*/;
   FilElm = LocElm_FilElm(LocElm);
   ElmInf = &(FilElm->ElmInf);
   FORBIDDEN(ElmInf->LocHdr != ERROR);
   FORBIDDEN(ElmInf->BackLink != NIL || ElmInf->Link != NIL);
   ElmInf->LocHdr = FilHdr_LocHdr(FilHdr);
   ElmInf->BackLink = LeftLocElm;
   ElmInf->Link = RiteLocElm;
   FORBIDDEN(ElmInf->LocHdr == ERROR);
   FORBIDDEN(ElmInf->BackLink == NIL || ElmInf->Link == NIL);
   SetFilElmModified(FilElm);
   Ret_FilElm(FilElm);
   }/*Link_LocElm*/


static void
Unlink_LocElm(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_FilElm FilElm, LeftFilElm, RiteFilElm;
   tp_ElmInf ElmInf;
   tp_FilHdr FilHdr;
   tp_LocHdr LocHdr;
   tp_LocElm LeftLocElm, RiteLocElm;

   FilElm = LocElm_FilElm(LocElm);
   ElmInf = &(FilElm->ElmInf);
   LocHdr = ElmInf->LocHdr;
   LeftLocElm = ElmInf->BackLink;
   RiteLocElm = ElmInf->Link;
   ElmInf->LocHdr = ERROR;
   ElmInf->BackLink = NIL;
   ElmInf->Link = NIL;
   SetFilElmModified(FilElm);
   Ret_FilElm(FilElm);
   FORBIDDEN(LeftLocElm == NIL || RiteLocElm == NIL || LocHdr == ERROR);

   FilHdr = LocHdr_FilHdr(LocHdr);
   /*select*/{
      if (LeftLocElm == LocElm) {
	 FORBIDDEN(RiteLocElm != LocElm);
	 Set_ElmLink(FilHdr, (tp_LocElm)NIL);
      }else{
	 if (FilHdr_ElmLink(FilHdr) == LocElm) {
	    Set_ElmLink(FilHdr, LeftLocElm); }/*if*/;

	 LeftFilElm = LocElm_FilElm(LeftLocElm);
	 LeftFilElm->ElmInf.Link = RiteLocElm;
	 SetFilElmModified(LeftFilElm);
	 Ret_FilElm(LeftFilElm);

	 RiteFilElm = LocElm_FilElm(RiteLocElm);
	 RiteFilElm->ElmInf.BackLink = LeftLocElm;
	 SetFilElmModified(RiteFilElm);
	 Ret_FilElm(RiteFilElm);
	 };}/*select*/;
   Ret_FilHdr(FilHdr);
   }/*Unlink_LocElm*/


static tp_FilElm
Alloc_ElmInf(GMC_ARG_VOID)
{
   tp_FilElm FilElm;
   tp_LocPrm LocElm;

   if (FreeLocElm != NIL) {
      LocElm = FreeLocElm;
      FilElm = LocElm_FilElm(LocElm);
      FORBIDDEN(FilElm->ElmInf.ListLocHdr != NIL);
      FreeLocElm = FilElm->ElmInf.Next;
      FilElm->ElmInf.Next = NIL;
      SetFilElmModified(FilElm);
      if (DebugLocElm) Debug_Alloc_ElmInf(LocElm, FreeLocElm);
      return FilElm; }/*if*/;
   return New_FilElm((tp_LocElm)Alloc(sizeof(tps_ElmInf)));
   }/*Alloc_ElmInf*/


void
DeAlloc_ElmInf(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_FilElm FilElm;
   tp_ElmInf ElmInf;
   tp_LocElm TmpLocElm, LastLocElm;

   if (LocElm == NIL) {
      return; }/*if*/;
   TmpLocElm = LocElm;
   LastLocElm = LocElm;
   while (TmpLocElm != NIL) {
      if (DebugLocElm) Debug_Ret_ElmInf(TmpLocElm);
      Unlink_LocElm(TmpLocElm);
      FilElm = LocElm_FilElm(TmpLocElm);
      ElmInf = &FilElm->ElmInf;
      FORBIDDEN(ElmInf->ListLocHdr == NIL);
      ElmInf->LocPrm = RootLocPrm;
      ElmInf->ListLocHdr = NIL;
      SetFilElmModified(FilElm);
      LastLocElm = TmpLocElm;
      TmpLocElm = ElmInf->Next;
      Ret_FilElm(FilElm); }/*while*/;
   FilElm = LocElm_FilElm(LastLocElm);
   ElmInf->Next = FreeLocElm;
   SetFilElmModified(FilElm);
   Ret_FilElm(FilElm);
   FreeLocElm = LocElm;
   }/*DeAlloc_ElmInf*/


boolean
FilElms_InUse(GMC_ARG_VOID)
{
   tp_FilElm FilElm;

   FilElm = UsedFilElm->NextFree;
   while (FilElm != UsedFilElm) {
      Write(StdOutFD, "LocElm=");
      WriteInt(StdOutFD, (int)FilElm->LocElm);
      Write(StdOutFD, ", Cnt=");
      WriteInt(StdOutFD, FilElm->Cnt);
      Writeln(StdOutFD, "");
      FilElm = FilElm->NextFree; }/*while*/;
   return (UsedFilElm->NextFree != UsedFilElm);
   }/*FilElms_InUse*/


tp_LocHdr
FilElm_LocHdr(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   if (FilElm == ERROR) return ERROR;
   return FilElm->ElmInf.LocHdr;
   }/*FilElm_LocHdr*/


tp_FilHdr
FilElm_FilHdr(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   tp_FilHdr FilHdr;

   if (FilElm == ERROR) {
      return ERROR; }/*if*/;
   FORBIDDEN(FilElm->ElmInf.LocHdr == NIL);
   FilHdr = LocHdr_FilHdr(FilElm->ElmInf.LocHdr);
   return FilHdr;
   }/*FilElm_FilHdr*/


tp_LocHdr
FilElm_ListLocHdr(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   return FilElm->ElmInf.ListLocHdr;
   }/*FilElm_ListLocHdr*/


tp_FilHdr
FilElm_ListFilHdr(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr(FilElm->ElmInf.ListLocHdr);
   return FilHdr;
   }/*FilElm_ListFilHdr*/


tp_FilPrm
FilElm_FilPrm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   FORBIDDEN(FilElm == ERROR);
   if (FilElm->FilPrm == NIL) FilElm->FilPrm = LocPrm_FilPrm(FilElm->ElmInf.LocPrm);
   FORBIDDEN(FilElm->FilPrm == ERROR);
   return FilElm->FilPrm;
   }/*FilElm_FilPrm*/


tp_LocElm
FilElm_Next(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   FORBIDDEN(FilElm == ERROR);
   return FilElm->ElmInf.Next;
   }/*FilElm_Next*/


tp_FilElm
FilElm_NextFilElm(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   tp_LocElm LocElm;

   FORBIDDEN(FilElm == ERROR);
   LocElm = FilElm->ElmInf.Next;
   Ret_FilElm(FilElm);
   return LocElm_FilElm(LocElm);
   }/*FilElm_NextFilElm*/


tp_LocElm
FilElm_Link(
   GMC_ARG(tp_FilElm, FilElm)
   )
   GMC_DCL(tp_FilElm, FilElm)
{
   return FilElm->ElmInf.Link;
   }/*FilElm_Link*/


tp_LocElm
Make_LocElm(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(tp_FilHdr, ListFilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(tp_FilHdr, ListFilHdr)
{
   tp_FilElm FilElm;
   tp_ElmInf ElmInf;
   tp_LocElm LocElm;

   FORBIDDEN(FilHdr == ERROR || FilPrm == ERROR || ListFilHdr == ERROR);

   FilElm = Alloc_ElmInf();
   LocElm = FilElm->LocElm;
   FilElm->FilPrm = FilPrm;
   ElmInf = &(FilElm->ElmInf);
   ElmInf->LocHdr = ERROR;
   ElmInf->BackLink = NIL;
   ElmInf->Link = NIL;
   ElmInf->LocPrm = FilPrm_LocPrm(FilPrm);
   ElmInf->ListLocHdr = FilHdr_LocHdr(ListFilHdr);
   ElmInf->Next = NIL;

   SetFilElmModified(FilElm);
   Ret_FilElm(FilElm);

   Link_LocElm(LocElm, FilHdr);

   return LocElm;
   }/*Make_LocElm*/


void
Chain_LocElms(
   GMC_ARG(tp_LocElm*, FirstLEPtr),
   GMC_ARG(tp_LocElm*, LastLEPtr),
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm*, FirstLEPtr)
   GMC_DCL(tp_LocElm*, LastLEPtr)
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_FilElm PrvFilElm;

   FORBIDDEN(LocElm == NIL);
   if (*FirstLEPtr == NIL) {
      FORBIDDEN(*LastLEPtr != NIL);
      *FirstLEPtr = LocElm;
      *LastLEPtr = LocElm;
      return; }/*if*/;
   PrvFilElm = LocElm_FilElm(*LastLEPtr);
   PrvFilElm->ElmInf.Next = LocElm;
   SetFilElmModified(PrvFilElm);
   Ret_FilElm(PrvFilElm);
   *LastLEPtr = LocElm;
   }/*Chain_LocElms*/


boolean
IsEquiv_LocElms(
   GMC_ARG(tp_LocElm, LocElm1),
   GMC_ARG(tp_LocElm, LocElm2)
   )
   GMC_DCL(tp_LocElm, LocElm1)
   GMC_DCL(tp_LocElm, LocElm2)
{
   tp_FilElm FilElm1, FilElm2;
   tp_FilPrm FilPrm1, FilPrm2;

   if (LocElm1 == LocElm2) {
      return TRUE; }/*if*/;

   for (FilElm1 = LocElm_FilElm(LocElm1), FilElm2 = LocElm_FilElm(LocElm2);
	FilElm1 != NIL && FilElm2 != NIL;
	FilElm1 = FilElm_NextFilElm(FilElm1),
	 FilElm2 = FilElm_NextFilElm(FilElm2)) {
      FORBIDDEN(FilElm1->ElmInf.ListLocHdr != FilElm2->ElmInf.ListLocHdr);
      if (FilElm1->ElmInf.LocHdr != FilElm2->ElmInf.LocHdr) {
	 Ret_FilElm(FilElm1); Ret_FilElm(FilElm2);
	 return FALSE; }/*if*/;
      FilPrm1 = LocPrm_FilPrm(FilElm1->ElmInf.LocPrm);
      FilPrm2 = LocPrm_FilPrm(FilElm2->ElmInf.LocPrm);
      FORBIDDEN(FilPrm1 == ERROR || FilPrm2 == ERROR);
      if (!Equal_FilPrm(FilPrm1, FilPrm2)) {
	 Ret_FilElm(FilElm1); Ret_FilElm(FilElm2);
	 return FALSE; }/*if*/; }/*for*/;

   Ret_FilElm(FilElm1); Ret_FilElm(FilElm2);
   return (FilElm1 == FilElm2);
   }/*IsEquiv_LocElms*/



