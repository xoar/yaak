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
#include "inc/Flag_.h"
#include "inc/InpKind_.h"
#include "inc/LogLevel_.h"
#include "inc/ModKind_.h"
#include "inc/Status_.h"


static int AnyOKDepth = 1;
static int ElmDepth = 1;


static void GetReqs(GMC_P1(tp_FilHdr) GMC_PN(boolean) GMC_PN(boolean) GMC_PN(int *));


static boolean
Is_CopyDone(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr OrigFilHdr, DestFilHdr;
   boolean OK;

   DestFilHdr = Deref_SymLink(Get_Copy_DestFilHdr(Copy_FilHdr(FilHdr)));
   if (DestFilHdr == NIL) {
      return FALSE; }/*if*/;
   OrigFilHdr = Deref(FilHdr_Father(Copy_FilHdr(FilHdr)));
   OrigFilHdr = Deref_SymLink(OrigFilHdr);
   OK = (FilHdr_LocHdr(OrigFilHdr) == FilHdr_OrigLocHdr(DestFilHdr)
	 && FilHdr_ModDate(OrigFilHdr) == FilHdr_OrigModDate(DestFilHdr));
   Ret_FilHdr(OrigFilHdr); Ret_FilHdr(DestFilHdr);
   return OK;
   }/*Is_CopyDone*/


static void
GetFile(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr TgtValFilHdr, InpFilHdr;
   tp_Status Status, MinStatus, InpStatus;
   tp_Date ModDate, MaxSonModDate;
   tp_Tool Tool;
   boolean DataFlag, NameFlag;
   tp_FilInp FilInp;
   tp_InpKind InpKind;

   if (IsUpToDate(FilHdr)) {
      return; }/*if*/;

   Status = FilHdr_Status(FilHdr);
   if (Status == STAT_Ready || Status == STAT_Busy) {
      FORBIDDEN(FilHdr_DepStatus(FilHdr) <= STAT_Error && !IsSource(FilHdr));
      Set_Status(FilHdr, Status);
      Set_PndFlag(FilHdr, FALSE);
      if (!IsTgtValUpToDate(FilHdr)) {
	 Set_TgtValStatus(FilHdr, FilHdr_TgtValStatus(FilHdr));
	 Set_TgtValPndFlag(FilHdr, FALSE); }/*if*/;
      Push_ToDo(Copy_FilHdr(FilHdr));
      return; }/*if*/;

   if (IsSource(FilHdr)) {
      if (!IsSrcUpToDate(FilHdr)) {
	 Update_SrcFilHdr(FilHdr, TRUE); }/*if*/;
      Set_Status(FilHdr, FilHdr_Status(FilHdr));
      if (!IsTgtValUpToDate(FilHdr)) {
	 TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
	 Status = STAT_OK;
	 if (TgtValFilHdr != NIL) {
	    FORBIDDEN(IsSource(TgtValFilHdr));
	    AnyOKDepth += 1;
	    GetReqs(TgtValFilHdr, FALSE, FALSE, (int *)0);
	    AnyOKDepth -= 1;
	    Status = FilHdr_MinStatus(TgtValFilHdr, IK_Simple);
	    /*select*/{
	       if (Status == STAT_Unknown) {
		  Status = STAT_OK;
		  Push_Pending(Copy_FilHdr(TgtValFilHdr), IK_Simple);
	       }else if (IsAllDone(TgtValFilHdr, IK_Simple)) {
		  if (Status <= STAT_TgtValError) {
		     Status = (Is_TgtValErrStatus(TgtValFilHdr)
			       ? STAT_TgtValError : STAT_OK);
		     }/*if*/; };}/*select*/;
	    Ret_FilHdr(TgtValFilHdr); }/*if*/;
	 Set_TgtValStatus(FilHdr, Status); }/*if*/;
      Set_PndFlag(FilHdr, FALSE);
      Set_TgtValPndFlag(FilHdr, FALSE);
      return; }/*if*/;

   if (FilHdr_Flag(FilHdr, FLAG_Get)) {
      FORBIDDEN(FilHdr_AnyOKDepth(FilHdr) == 0);
      FORBIDDEN(FilHdr_ElmDepth(FilHdr) != 0);
      Status = ((AnyOKDepth > FilHdr_AnyOKDepth(FilHdr))
		? STAT_Unknown : STAT_Circular);
      Set_ListStatus(FilHdr, Status);
      Set_ListPndFlag(FilHdr, FALSE);
      return; }/*if*/;
   Set_Flag(FilHdr, FLAG_Get);


   MinStatus = STAT_OK;
   MaxSonModDate = 1;

   for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	FilInp != NIL;
	FilInp = FilInp_NextFilInp(FilInp)) {
      InpFilHdr = FilInp_FilHdr(FilInp);
      InpKind = FilInp_InpKind(FilInp);

      if (NeedsData(InpFilHdr, InpKind)) {
	 if (InpKind_IsAnyOK(InpKind)) {
	    AnyOKDepth += 1; }/*if*/;
	 DataFlag = NeedsElmData(InpFilHdr, InpKind);
	 NameFlag = (DataFlag || NeedsElmNameData(InpFilHdr, InpKind));
	 GetReqs(InpFilHdr, NameFlag, DataFlag, (int *)0);
	 if (InpKind_IsAnyOK(InpKind)) {
	    AnyOKDepth -= 1; }/*if*/;

         InpStatus = FilHdr_TgtValMinStatus(InpFilHdr);
         ModDate = FilHdr_ModDate(InpFilHdr);
         if (MaxSonModDate < ModDate) MaxSonModDate = ModDate;

	 /*select*/{
	    if (NeedsElmData(InpFilHdr, InpKind)) {
	       Status = FilHdr_ElmStatus(InpFilHdr);
	       if (InpStatus > Status) InpStatus = Status;
	       ModDate = FilHdr_ElmModDate(InpFilHdr);
	       if (MaxSonModDate < ModDate) MaxSonModDate = ModDate;
	    }else if (NeedsElmNameData(InpFilHdr, InpKind)) {
	       Status = FilHdr_ElmNameStatus(InpFilHdr);
	       if (InpStatus > Status) InpStatus = Status;
	       ModDate = FilHdr_ElmNameModDate(InpFilHdr);
	       if (MaxSonModDate < ModDate) MaxSonModDate = ModDate;
	       };}/*select*/;
	 if (InpKind_IsAnyOK(InpKind)) {
	    /*select*/{
	       if (InpStatus == STAT_Unknown) {
		  InpStatus = STAT_OK;
		  Push_Pending(Copy_FilHdr(InpFilHdr), InpKind);
	       }else if (InpStatus < STAT_TgtValError
			 && !Is_PRB_Status(InpStatus)) {
		  InpStatus = STAT_TgtValError; };}/*select*/; }/*if*/;
         if (MinStatus > InpStatus) {
	    MinStatus = InpStatus; }/*if*/; }/*if*/;
      Ret_FilHdr(InpFilHdr); }/*for*/;
   FORBIDDEN(MinStatus < STAT_Unknown);

   if (MinStatus == STAT_Unknown) {
      Do_Log("Pending circular computation for", FilHdr, LOGLEVEL_Circular);
      Set_ListStatus(FilHdr, STAT_Unknown);
      goto done; }/*if*/;
   if (IsUpToDate(FilHdr)) {
      FORBIDDEN(!(IsStructMem(FilHdr) || IsKeyListElm(FilHdr) || FilHdr_Status(FilHdr) == STAT_Circular));
      if (Is_PRB_Status(MinStatus)) {
	 Set_ListStatus(FilHdr, STAT_Pending);
	 Broadcast_Mod(FilHdr, MODKIND_Input, STAT_Pending); }/*if*/;
      goto done; }/*if*/;
   Tool = FilHdr_Tool(FilHdr);
   MinStatus = Get_ToolStatus(Tool, MinStatus);
   if (MinStatus < STAT_Error) {
      Do_Log((MinStatus == STAT_Pending) ? "Pending" : "Aborting",
	     FilHdr, LOGLEVEL_Process);
      Set_ListStatus(FilHdr, MinStatus);
      goto done; }/*if*/;
   if (IsReport_Tool(Tool)) {
      MaxSonModDate = CurrentDate; }/*if*/;

   if ((FilHdr_ModDate(FilHdr) > 0
	&& FilHdr_ConfirmDate(FilHdr) >= MaxSonModDate)
       || (IsCopy(FilHdr) && Is_CopyDone(FilHdr))) {
      Do_Log("Verifying", FilHdr, LOGLEVEL_Process);
      if (MinStatus > FilHdr_MinErrStatus(FilHdr)) {
	 MinStatus = FilHdr_MinErrStatus(FilHdr); }/*if*/;
      if (MinStatus == STAT_Error && IsTargets(FilHdr)) {
	 MinStatus = STAT_TgtValError; }/*if*/;
      Set_Status(FilHdr, MinStatus);
      Set_ConfirmDate(FilHdr, MaxSonModDate);
      Set_DrvDirConfirm(FilHdr, MinStatus);
      goto done; }/*if*/;

   if (IsExternal_Tool(Tool)) {
      Set_ListStatus(FilHdr, STAT_Ready);
      Set_DepStatus(FilHdr, MinStatus);
      Set_DepModDate(FilHdr, MaxSonModDate);
      Push_ToDo(Copy_FilHdr(FilHdr));
      goto done; }/*if*/;

   ExecInternal(FilHdr, MinStatus, MaxSonModDate);

done:;
   Set_ListPndFlag(FilHdr, FALSE);
   Clr_Flag(FilHdr, FLAG_Get);
   }/*GetFile*/


static void
ClearAll_SCC(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, DataFlag)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, DataFlag)
{
   tp_FilElm FilElm;
   tp_FilHdr SCC_FilHdr, ElmFilHdr;
   boolean ViewSpecFlag;

   if (FilHdr_ElmDepth(FilHdr) != ElmDepth) {
      FORBIDDEN(FilHdr_ElmDepth(FilHdr) != 0 && FilHdr_ElmDepth(FilHdr) > ElmDepth);
      return; }/*if*/;
   Set_ElmDepth(FilHdr, 0);
   Set_ElmTag(FilHdr, 0);

   SCC_FilHdr = FilHdr_SCC(FilHdr);
   Set_ElmNameStatus(FilHdr, FilHdr_ElmNameStatus(SCC_FilHdr));
   Set_ElmNameModDate(FilHdr, FilHdr_ElmNameModDate(SCC_FilHdr));
   Set_ElmNameConfirmDate(FilHdr);
   Set_ElmNamePndFlag(FilHdr, FALSE);
   if (DataFlag) {
      Set_ElmStatus(FilHdr, FilHdr_ElmStatus(SCC_FilHdr));
      Set_ElmModDate(FilHdr, FilHdr_ElmModDate(SCC_FilHdr));
      Set_ElmConfirmDate(FilHdr);
      Set_ElmPndFlag(FilHdr, FALSE); }/*if*/;
   Ret_FilHdr(SCC_FilHdr);

   ViewSpecFlag = IsViewSpec(FilHdr);
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);
      ClearAll_SCC(ElmFilHdr, DataFlag);
      if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) != STAT_NoFile) {
	 FilElm = FilElm_NextStrFilElm(FilElm); }/*if*/;
      Ret_FilHdr(ElmFilHdr); }/*for*/;

   Set_SCC(FilHdr, (tp_FilHdr)NIL);
   }/*ClearAll_SCC*/


static void
GetReqs(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, NameFlag),
   GMC_ARG(boolean, DataFlag),
   GMC_ARG(int*, ETPtr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, NameFlag)
   GMC_DCL(boolean, DataFlag)
   GMC_DCL(int*, ETPtr)
{
   boolean DepthSet, ListFlag, ViewSpecFlag;
   int ElmTagInit, ElmTag, *ElmTagPtr;
   tp_FilElm FilElm;
   tp_FilHdr ElmFilHdr, SCC_ElmFilHdr, SCC_FilHdr, DerefFilHdr;
   tp_Status Status, MinStatus, MinNameStatus;
   tp_Date ModDate, MaxModDate, MaxNameModDate;

   DepthSet = FALSE;
   if (FilHdr_AnyOKDepth(FilHdr) == 0) {
      Set_AnyOKDepth(FilHdr, AnyOKDepth);
      DepthSet = TRUE; }/*if*/;

   ElmDepth += 1;
   GetFile(FilHdr);
   ElmDepth -= 1;

   if (!((NameFlag || DataFlag) && IsRef(FilHdr))) {
      goto done; }/*if*/;

   ViewSpecFlag = IsViewSpec(FilHdr);

   ElmTagPtr = ETPtr;
   if (ElmTagPtr == 0) {
      ElmTagInit = 1;
      ElmTagPtr = &ElmTagInit; }/*if*/;

   if (FilHdr_ElmDepth(FilHdr) != 0 && FilHdr_ElmDepth(FilHdr) != ElmDepth) {
      FORBIDDEN(FilHdr_AnyOKDepth(FilHdr) == 0);
      Status = ((AnyOKDepth > FilHdr_AnyOKDepth(FilHdr))
		? STAT_Unknown : STAT_ElmCircular);
      if (FilHdr_ElmNameStatus(FilHdr) > Status) {
	 Set_ElmNameStatus(FilHdr, Status); }/*if*/;
      if (FilHdr_ElmStatus(FilHdr) > Status) {
	 Set_ElmStatus(FilHdr, Status); }/*if*/;
      goto done; }/*if*/;

   if (DataFlag ? IsElmUpToDate(FilHdr) : IsElmNameUpToDate(FilHdr)) {
      goto done; }/*if*/;

   FORBIDDEN(FilHdr_Status(FilHdr) <= STAT_Error);

   FORBIDDEN(FilHdr_ElmDepth(FilHdr) != 0);
   Set_ElmDepth(FilHdr, ElmDepth);
   *ElmTagPtr += 1;
   ElmTag = *ElmTagPtr;
   FORBIDDEN(FilHdr_ElmTag(FilHdr) != 0);
   Set_ElmTag(FilHdr, ElmTag);
   Set_SCC(FilHdr, FilHdr);

   MinNameStatus = STAT_OK;
   Set_ElmNameStatus(FilHdr, MinNameStatus);
   MaxNameModDate = 1;
   Set_ElmNameModDate(FilHdr, MaxNameModDate);
   if (DataFlag) {
      MinStatus = STAT_OK;
      Set_ElmStatus(FilHdr, MinStatus);
      MaxModDate = 1;
      Set_ElmModDate(FilHdr, MaxModDate); }/*if*/;

   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);

      ListFlag = IsRef(ElmFilHdr);

      if (DataFlag || ListFlag) {

	 GetReqs(ElmFilHdr, NameFlag, DataFlag, ElmTagPtr);

	 if (FilHdr_ElmTag(ElmFilHdr) != 0) {
	    SCC_ElmFilHdr = FilHdr_SCC(ElmFilHdr);
	    if (ElmTag > FilHdr_ElmTag(SCC_ElmFilHdr)) {
	       Set_SCC(FilHdr, SCC_ElmFilHdr);
	       ElmTag = FilHdr_ElmTag(SCC_ElmFilHdr); }/*if*/;
	    Ret_FilHdr(SCC_ElmFilHdr); }/*if*/;

	 Status = FilHdr_TgtValMinStatus(ElmFilHdr);
	 if (ViewSpecFlag && Status == STAT_NoFile) {
	    Status = ((FilHdr_TgtValStatus(ElmFilHdr) < STAT_OK)
		      ? STAT_TgtValError : STAT_OK); }/*if*/;
	 ModDate = FilHdr_ModDate(ElmFilHdr);

	 if (DataFlag) {
	    if (MinStatus > Status) MinStatus = Status;
	    if (MaxModDate < ModDate) MaxModDate = ModDate;
	    }/*if*/;

	 if (ListFlag) {
	    if (MinNameStatus > Status) MinNameStatus = Status;
	    if (MaxNameModDate < ModDate) MaxNameModDate = ModDate;

	    Status = FilHdr_ElmNameStatus(ElmFilHdr);
	    if (ViewSpecFlag && Status == STAT_NoFile) Status = STAT_OK;
	    if (MinNameStatus > Status) MinNameStatus = Status;
	    ModDate = FilHdr_ElmNameModDate(ElmFilHdr);
	    if (MaxNameModDate < ModDate) MaxNameModDate = ModDate;

	    if (DataFlag) {
	       Status = FilHdr_ElmStatus(ElmFilHdr);
	       if (ViewSpecFlag && Status == STAT_NoFile) Status = STAT_OK;
	       if (MinStatus > Status) MinStatus = Status;
	       ModDate = FilHdr_ElmModDate(ElmFilHdr);
	       if (MaxModDate < ModDate) MaxModDate = ModDate;
	       }/*if*/; }/*if*/;

	 if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) != STAT_NoFile) {
	    FilElm = FilElm_NextStrFilElm(FilElm); }/*if*/; }/*if*/;

      Ret_FilHdr(ElmFilHdr); }/*for*/;

   if (MinNameStatus == STAT_SysAbort
       && FilHdr_ElmNameStatus(FilHdr) == STAT_ElmCircular) {
      MinNameStatus = STAT_ElmCircular; }/*if*/;
   if (DataFlag) {
      if (MinStatus == STAT_SysAbort
	  && FilHdr_ElmStatus(FilHdr) == STAT_ElmCircular) {
	 MinStatus = STAT_ElmCircular; }/*if*/; }/*if*/;
   if (MinNameStatus > STAT_ElmCircular && IsPntr(FilHdr)) {
      DerefFilHdr = Deref(Copy_FilHdr(FilHdr));
      /*select*/{
	 if (DerefFilHdr == NIL) {
	    MinNameStatus = STAT_ElmCircular;
	 }else{
	    Ret_FilHdr(DerefFilHdr); };}/*select*/; }/*if*/;

   /*select*/{
      if (ElmTag == *ElmTagPtr) {
	 Set_ElmNameStatus(FilHdr, MinNameStatus);
	 Set_ElmNameModDate(FilHdr, MaxNameModDate);
	 if (DataFlag) {
	    Set_ElmStatus(FilHdr, MinStatus);
	    Set_ElmModDate(FilHdr, MaxModDate); }/*if*/;
      }else{
	 SCC_FilHdr = FilHdr_SCC(FilHdr);
	 if (MinNameStatus < FilHdr_ElmNameStatus(SCC_FilHdr)
	     || (MinNameStatus == STAT_ElmCircular
		 && FilHdr_ElmNameStatus(SCC_FilHdr) == STAT_SysAbort)) {
	    Set_ElmNameStatus(SCC_FilHdr, MinNameStatus); }/*if*/;
	 if (MaxNameModDate > FilHdr_ElmNameModDate(SCC_FilHdr)) {
	    Set_ElmNameModDate(SCC_FilHdr, MaxNameModDate); }/*if*/;
	 if (DataFlag) {
	    if (MinStatus < FilHdr_ElmStatus(SCC_FilHdr)
		|| (MinStatus == STAT_ElmCircular
		    && FilHdr_ElmStatus(SCC_FilHdr) == STAT_SysAbort)) {
	       Set_ElmStatus(SCC_FilHdr, MinStatus); }/*if*/;
	    if (MaxModDate > FilHdr_ElmModDate(SCC_FilHdr)) {
	       Set_ElmModDate(SCC_FilHdr, MaxModDate); }/*if*/; }/*if*/;
	 Ret_FilHdr(SCC_FilHdr); };}/*select*/;

   SCC_FilHdr = FilHdr_SCC(FilHdr);
   if (FilHdr == SCC_FilHdr) {
      ClearAll_SCC(FilHdr, DataFlag); }/*if*/;
   Ret_FilHdr(SCC_FilHdr);

done:;
   if (DepthSet) {
      Set_AnyOKDepth(FilHdr, 0); }/*if*/;
   }/*GetReqs*/


void
GetAllReqs(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   boolean DataFlag, NameFlag;

   DataFlag = NeedsElmData(FilHdr, InpKind);
   NameFlag = (DataFlag || NeedsElmNameData(FilHdr, InpKind));

   while (!IsAllUpToDate(FilHdr, InpKind)) {
      GetReqs(FilHdr, NameFlag, DataFlag, (int *)0);
      Do_ToBroadcast(); }/*while*/;
   }/*GetAllReqs*/


