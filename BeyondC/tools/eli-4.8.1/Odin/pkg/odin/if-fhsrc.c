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
#include "inc/FileName.h"
#include "inc/Flag_.h"
#include "inc/Status_.h"
#include "inc/Str.h"


void
Deref_Pntrs(
   GMC_ARG(tp_FilHdr*, FilHdrPtr),
   GMC_ARG(tp_FilPrm*, FilPrmPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, IgnoreStatus)
   )
   GMC_DCL(tp_FilHdr*, FilHdrPtr)
   GMC_DCL(tp_FilPrm*, FilPrmPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, IgnoreStatus)
{
   tp_FilPrm FilPrm;
   tp_FilElm FilElm;

   *FilHdrPtr = (tp_FilHdr)NIL;
   *FilPrmPtr = (tp_FilPrm)NIL;
   if (FilHdr == ERROR) {
      return; }/*if*/;
   if (FilHdr_Flag(FilHdr, FLAG_DeRef)) {
      FilHdr_Error("<%s> is circular.\n", FilHdr);
      Ret_FilHdr(FilHdr);
      return; }/*if*/;
   if (!(IsPntr(FilHdr)
	 && (FilHdr_Status(FilHdr) > STAT_Error || IgnoreStatus))) {
      *FilHdrPtr = FilHdr;
      *FilPrmPtr = RootFilPrm;
      return; }/*if*/;
   FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
   if (IgnoreStatus && FilElm == NIL) {
      Ret_FilHdr(FilHdr);
      return; }/*if*/;
   FORBIDDEN(!IgnoreStatus && (FilElm == NIL || FilElm_Next(FilElm) != NIL));
   *FilHdrPtr = FilElm_FilHdr(FilElm);
   FilPrm = FilElm_FilPrm(FilElm);
   Ret_FilElm(FilElm);
   Set_Flag(FilHdr, FLAG_DeRef);
   Deref_Pntrs(FilHdrPtr, FilPrmPtr, *FilHdrPtr, IgnoreStatus);
   Clr_Flag(FilHdr, FLAG_DeRef);
   *FilPrmPtr = Append_FilPrm(*FilPrmPtr, FilPrm);
   Ret_FilHdr(FilHdr);
   }/*Deref_Pntrs*/


tp_FilHdr
Deref(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilPrm FilPrm;

   Deref_Pntrs(&FilHdr, &FilPrm, FilHdr, FALSE);
   return FilHdr;
   }/*Deref*/


tp_FilHdr
Deref_SymLink(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr ElmFilHdr;

   if (FilHdr == ERROR) {
      return ERROR; }/*if*/;
   if (!IsSymLink(FilHdr) || FilHdr_Status(FilHdr) == STAT_Circular) {
      return FilHdr; }/*if*/;
   ElmFilHdr = FilHdr_ElmFilHdr(FilHdr);
   FORBIDDEN(IsSymLink(ElmFilHdr) || !IsSource(ElmFilHdr));
   return ElmFilHdr;
   }/*Deref_SymLink*/


void
Local_Test(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   tp_FilHdr FilHdr, SymLinkFH;

   FilHdr = OdinExpr_FilHdr(FileName);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   if (IsSource(FilHdr)) {
      SymLinkFH = Deref_SymLink(Copy_FilHdr(FilHdr));
      Set_Status(SymLinkFH, STAT_Unknown);
      Ret_FilHdr(SymLinkFH);
      Update_SrcFilHdr(FilHdr, FALSE); }/*if*/;
   Ret_FilHdr(FilHdr);
   }/*Local_Test*/


void
Local_Test_All(GMC_ARG_VOID)
{
   tp_Client OldCurrentClient;
   tp_FilHdr FilHdr;
   boolean AllDone;

   CurrentDate += 1;
   VerifyDate = CurrentDate;
   OldCurrentClient = CurrentClient;
   FOREACH_CLIENT(CurrentClient) {
      FilHdr = Client_FilHdr(CurrentClient);
      if (FilHdr != NIL) {
	 Ret_ToDo();
	 Push_AllReqs(&AllDone);
	 Ret_FilHdr(FilHdr); }/*if*/; }/*for*/;
   CurrentClient = OldCurrentClient;
   }/*Local_Test_All*/


tp_FilHdr
Get_Copy_DestFilHdr(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilPVal FilPVal;

   FilPVal = Get_FilPVal(FilHdr_FilPrm(FilHdr), CopyDestPrmTyp);
   Ret_FilHdr(FilHdr);
   return LocHdr_FilHdr(FilPVal_LocHdr(FilPVal));
   }/*Get_Copy_DestFilHdr*/


tp_LocElm
Make_CopyLocElm(
   GMC_ARG(tp_FilHdr, OrigFilHdr),
   GMC_ARG(tp_FilHdr, DestFilHdr),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, OrigFilHdr)
   GMC_DCL(tp_FilHdr, DestFilHdr)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr ElmFilHdr;
   tp_FilPrm ElmFilPrm;
   tp_LocElm LocElm;

   ElmFilHdr = Copy_FilHdr(OrigFilHdr);
   ElmFilPrm = Append_PrmInf(RootFilPrm, CopyDestPrmTyp,
			     FilHdr_LocHdr(DestFilHdr), (tp_LocPVal)NIL);
   ElmFilHdr = Do_Deriv(ElmFilHdr, RootFilPrm, ElmFilPrm, CopyFilTyp);
   LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr);
   Ret_FilHdr(ElmFilHdr);
   return LocElm;
   }/*Make_CopyLocElm*/


static void
Get_CopyList(
   GMC_ARG(tp_LocElm*, FirstLEPtr),
   GMC_ARG(tp_LocElm*, LastLEPtr),
   GMC_ARG(tp_FilHdr, OrigFilHdr),
   GMC_ARG(tp_FilHdr, DestFilHdr),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_LocElm*, FirstLEPtr)
   GMC_DCL(tp_LocElm*, LastLEPtr)
   GMC_DCL(tp_FilHdr, OrigFilHdr)
   GMC_DCL(tp_FilHdr, DestFilHdr)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr DestElmFH, OrigElmFH;
   tp_LocElm LocElm;
   tp_FilElm FilElm;
   tps_Str StrBuf;

   if (FilHdr_Flag(OrigFilHdr, FLAG_Union)) {
      return; }/*if*/;
   Set_Flag(OrigFilHdr, FLAG_Union);

   if (!IsRef(OrigFilHdr)) {
      DestElmFH = Copy_FilHdr(DestFilHdr);
      DestElmFH = Do_Key(DestElmFH, FilHdr_Label(StrBuf, OrigFilHdr, FALSE));
      LocElm = Make_CopyLocElm(OrigFilHdr, DestElmFH, FilHdr);
      Chain_LocElms(FirstLEPtr, LastLEPtr, LocElm);
      Ret_FilHdr(DestElmFH);
      return; }/*if*/;

   for (FilElm = LocElm_FilElm(FilHdr_LocElm(OrigFilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      OrigElmFH = FilElm_FilHdr(FilElm);
      Get_CopyList(FirstLEPtr, LastLEPtr, OrigElmFH, DestFilHdr, FilHdr);
      Ret_FilHdr(OrigElmFH); }/*for*/;
   }/*Get_CopyList*/


void
Exec_CopyCmd(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilHdr, DestFilHdr),
   GMC_ARG(tp_FilHdr, OrigFilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilHdr, DestFilHdr)
   GMC_DCL(tp_FilHdr, OrigFilHdr)
{
   tp_LocElm LocElm, LastLocElm;
   tps_FileName DestFileName;

   LocElm = NIL;

   if (!IsSource(DestFilHdr)) {
      SystemError("Destination of copy must be a source file or directory.\n");
      goto done; }/*if*/;

   FilHdr_HostFN(DestFileName, DestFilHdr, FALSE);
   if (!IsDirectory_FileName(DestFileName)) {
      if (IsList(OrigFilHdr)) {
	 SystemError("List objects can only be copied to directories.\n");
	 goto done; }/*if*/;
      LocElm = Make_CopyLocElm(OrigFilHdr, DestFilHdr, FilHdr);
      goto done; }/*if*/;

   LastLocElm = NIL;
   Get_CopyList(&LocElm, &LastLocElm, OrigFilHdr, DestFilHdr, FilHdr);
   Clr_UnionFlags(OrigFilHdr);

done:;
   Set_LocElm(FilHdr, LocElm);
   }/*Exec_CopyCmd*/


