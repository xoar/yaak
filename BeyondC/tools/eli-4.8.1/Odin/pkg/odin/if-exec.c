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
#include "inc/Str.h"
#include "inc/FileName.h"
#include "inc/Job.h"
#include "inc/LogLevel_.h"
#include "inc/ExecSpc.h"
#include "inc/Status_.h"


void
Exec(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr OrigFilHdr, DestFilHdr, OrigElmFH, DestElmFH, TgtValFilHdr;
   tps_ExecSpc _ExecSpc; tp_ExecSpc ExecSpc = &_ExecSpc;
   tp_Job Job;
   int i;
   tps_FileName FileName;
   boolean Abort;

   FORBIDDEN(FilHdr_Status(FilHdr) != STAT_Ready);
   Set_ListStatus(FilHdr, STAT_Busy);
   FORBIDDEN(FilHdr_DepStatus(FilHdr) <= STAT_Error);
   if (IsCopy(FilHdr)) {
      DestFilHdr = Get_Copy_DestFilHdr(Copy_FilHdr(FilHdr));
      if (DestFilHdr != NIL) {
	 Abort = FALSE;
	 OrigFilHdr = FilHdr_Father(Copy_FilHdr(FilHdr));
	 if (IsBound(DestFilHdr)) {
	    TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(DestFilHdr));
	    if (TgtValFilHdr != FilHdr) {
	       Do_Log("Cannot copy into a file target", DestFilHdr,
		      LOGLEVEL_Abort);
	       Abort = TRUE; }/*if*/;
	    Ret_FilHdr(TgtValFilHdr); }/*if*/;
	 if (!Abort) {
	    DestElmFH = Deref_SymLink(Copy_FilHdr(DestFilHdr));
	    OrigElmFH = Deref_SymLink(Deref(Copy_FilHdr(OrigFilHdr)));
	    if (FilHdr_Status(DestElmFH) == STAT_Busy) {
	       Do_Log("Aborted", FilHdr, LOGLEVEL_Abort);
	       Do_Log("Currently copying to", DestFilHdr, LOGLEVEL_Abort);
	       Abort = TRUE; }/*if*/;
	    if (!Abort) {
	       Set_Status(DestElmFH, STAT_Ready);
	       Set_OrigLocHdr(DestElmFH, FilHdr_LocHdr(OrigElmFH));
	       Set_DepModDate(DestElmFH, FilHdr_ModDate(OrigElmFH));
	       Set_Status(DestElmFH, STAT_Busy);
	       Broadcast(DestElmFH, STAT_Pending);
	       Set_Status(DestFilHdr, STAT_Busy); }/*if*/;
	    Ret_FilHdr(OrigElmFH); Ret_FilHdr(DestElmFH); }/*if*/;
	 Ret_FilHdr(OrigFilHdr); Ret_FilHdr(DestFilHdr);
	 if (Abort) {
	    Set_ListStatus(FilHdr, STAT_Unknown);
	    Local_Do_Interrupt(FALSE);
	    return; }/*if*/; }/*if*/; }/*if*/;
   FilHdr_ExecSpc(ExecSpc, FilHdr);
   Job = Add_Job(FilHdr);
   ExecSpc->Job = Job;
   for (i=0; i<ExecSpc->NumInps; i++) {
      FilHdr_DataFileName(FileName, ExecSpc->InpFilHdrs[i]);
      Add_BuildArg(FileName); }/*for*/;
   Do_Log("Generating", FilHdr, LOGLEVEL_Generate);
   JobID_LogFileName(FileName, Job->JobID);
   Do_Build(Job->JobID, Job->JobDirName, FileName);
   Ret_ExecSpc(ExecSpc);
   }/*Exec*/


static tp_Status
Get_ExecStatus(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Job, Job)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Job, Job)
{
   tp_Status Status;

   Status = STAT_OK;
   if (Exists(Job->WarningFN)) {
      /*select*/{
	 if (Empty(Job->WarningFN)) {
	    Remove(Job->WarningFN);
	 }else{
	    Add_StatusFile(FilHdr, STAT_Warning, Job->WarningFN);
	    Status = STAT_Warning; };}/*select*/; }/*if*/;
   if (Exists(Job->ErrorFN)) {
      /*select*/{
	 if (Empty(Job->ErrorFN)) {
	    Remove(Job->ErrorFN);
	 }else{
	    Add_StatusFile(FilHdr, STAT_Error, Job->ErrorFN);
	    Status = STAT_Error; };}/*select*/; }/*if*/;
   return Status;
   }/*Get_ExecStatus*/


void
Local_Job_Done(
   GMC_ARG(tp_JobID, JobID),
   GMC_ARG(boolean, Abort)
   )
   GMC_DCL(tp_JobID, JobID)
   GMC_DCL(boolean, Abort)
{
   tps_OutFilHdrs OutFilHdrs;
   tp_Job Job;
   int i, NumOuts;
   tp_FilHdr FilHdr, DestFilHdr, DestElmFH;
   tp_Status DepStatus, Status;
   tp_Date DepModDate, OrigModDate;
   tps_FileName WorkDirName;

   IsAny_ReadyServerAction = TRUE;
   Job = Get_Job(JobID);
   FilHdr = Job_FilHdr(Job);
   Get_OutFilHdrs(OutFilHdrs, &NumOuts, FilHdr);

   FORBIDDEN(FilHdr_Status(FilHdr) != STAT_Busy);

   if (Abort) {
      Do_Log("Aborted", FilHdr, LOGLEVEL_Abort);
      if (IsCopy(FilHdr)) {
	 DestFilHdr = Get_Copy_DestFilHdr(Copy_FilHdr(FilHdr));
	 if (DestFilHdr != NIL) {
	    DestElmFH = Deref_SymLink(Copy_FilHdr(DestFilHdr));
	    Set_Status(DestElmFH, STAT_Unknown);
	    Set_Status(DestFilHdr, STAT_Unknown);
	    Ret_FilHdr(DestElmFH); Ret_FilHdr(DestFilHdr); }/*if*/; }/*if*/;
      for (i=0; i<NumOuts; i++) {
	 if (IsDrvDir(OutFilHdrs[i])) {
	    Get_WorkFileName(WorkDirName, Job, FilHdr);
	    ClearDir(WorkDirName);
	    RemoveDir(WorkDirName); }/*if*/; }/*for*/;
      Set_Status(FilHdr, STAT_Unknown);
      Local_Do_Interrupt(FALSE);
      goto done; }/*if*/;

   Clr_ErrStatus(FilHdr);
   for (i=0; i<NumOuts; i++) {
      Clr_ErrStatus(OutFilHdrs[i]); }/*for*/;
   DepModDate = FilHdr_DepModDate(FilHdr);
   DepStatus = FilHdr_DepStatus(FilHdr);
   FORBIDDEN(DepStatus <= STAT_Error);
   Status = Get_ExecStatus(FilHdr, Job);
   if (Status > DepStatus) Status = DepStatus;

   Do_Update(FilHdr, OutFilHdrs, NumOuts, Job, Status, DepModDate, FALSE);

   if (Job->Canceled) {
      Set_ListStatus(FilHdr, STAT_Unknown);
      if (IsStruct(FilHdr)) {
	 for (i=0; i<NumOuts; i++) {
	    Set_ListStatus(OutFilHdrs[i], STAT_Unknown);
	    }/*for*/; }/*if*/; }/*if*/;
   if (IsCopy(FilHdr)) {
      DestFilHdr = Get_Copy_DestFilHdr(Copy_FilHdr(FilHdr));
      if (DestFilHdr != NIL) {
	 DestElmFH = Deref_SymLink(Copy_FilHdr(DestFilHdr));
	 OrigModDate = FilHdr_DepModDate(DestElmFH);
	 Set_Status(DestElmFH, STAT_Unknown);
	 Set_Status(DestFilHdr, STAT_Unknown);
	 Update_SrcFilHdr(DestFilHdr, FALSE);
	 Set_OrigModDate(DestElmFH, OrigModDate);
	 Ret_FilHdr(DestElmFH); Ret_FilHdr(DestFilHdr); }/*if*/; }/*if*/;

done:;
   for (i=0; i<NumOuts; i++) Ret_FilHdr(OutFilHdrs[i]);
   Ret_FilHdr(FilHdr);
   Del_Job(Job);
   }/*Local_Job_Done*/


