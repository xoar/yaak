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
#include "inc/Flag_.h"
#include "inc/InpKind_.h"
#include "inc/Status_.h"
#include "inc/Str.h"


static void Get_ElmReport(GMC_P1(tp_FilDsc) GMC_PN(tp_FilHdr) GMC_PN(boolean) GMC_PN(tp_Status));


static void
Do_Report(
   GMC_ARG(tp_FilDsc, ReportFD),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Status, Status),
   GMC_ARG(tp_Status, ReportStatus)
   )
   GMC_DCL(tp_FilDsc, ReportFD)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Status, Status)
   GMC_DCL(tp_Status, ReportStatus)
{
   boolean MsgFlag;
   tps_FileName WarningFileName, ErrorFileName;
   tp_FilDsc FilDsc;

   if (Status == STAT_SysAbort) {
      return; }/*if*/;

   MsgFlag = FALSE;
   if (ReportStatus >= STAT_TgtValError
       && FilHdr_HasErrStatus(FilHdr, STAT_Error)) {
      MsgFlag = TRUE;
      Write(ReportFD, "--- <");
      Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
      Writeln(ReportFD, "> generated errors ---");
      FilHdr_ErrorFileName(ErrorFileName, FilHdr);
      FilDsc = FileName_RFilDsc(ErrorFileName, TRUE);
      FileCopy(ReportFD, FilDsc);
      Close(FilDsc); }/*if*/;

   if (ReportStatus >= STAT_Warning
       && FilHdr_HasErrStatus(FilHdr, STAT_Warning)) {
      MsgFlag = TRUE;
      Write(ReportFD, "--- <");
      Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
      Writeln(ReportFD, "> generated warnings ---");
      FilHdr_WarningFileName(WarningFileName, FilHdr);
      FilDsc = FileName_RFilDsc(WarningFileName, TRUE);
      FileCopy(ReportFD, FilDsc);
      Close(FilDsc);
      return; }/*if*/;

   if (MsgFlag || ReportStatus < Status) {
      return; }/*if*/;

   switch (Status) {
      case STAT_Unknown: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> has unknown status ---");  break;}/*case*/;
      case STAT_Pending: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> has pending status ---");  break;}/*case*/;
      case STAT_Ready: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> has ready status ---");  break;}/*case*/;
      case STAT_Busy: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> has busy status ---");  break;}/*case*/;
      case STAT_SysAbort: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> has system abort status ---");  break;}/*case*/;
      case STAT_NoFile: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> does not exist ---"); break;}/*case*/;
      case STAT_Circular: {
	 Write(ReportFD, "--- <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> depends on itself ---"); break;}/*case*/;
      case STAT_ElmCircular: {
	 Write(ReportFD, "--- An element of <");
	 Print_FilHdr(ReportFD, (tp_Str)NIL, FilHdr);
	 Writeln(ReportFD, "> depends on itself ---");  break;}/*case*/;
      case STAT_Error: case STAT_TgtValError: case STAT_Warning: {
	 break;}/*case*/;
      default: {
	 FATALERROR("Bad status"); };}/*switch*/;
   }/*Do_Report*/


static void
Set_ElmVisit(
   GMC_ARG(boolean*, DoneFlagPtr),
   GMC_ARG(boolean*, DataFlagPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind)
   )
   GMC_DCL(boolean*, DoneFlagPtr)
   GMC_DCL(boolean*, DataFlagPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
{
   *DoneFlagPtr = FALSE;
   *DataFlagPtr = NeedsElmData(FilHdr, InpKind);
   if (!(*DataFlagPtr || NeedsElmNameData(FilHdr, InpKind))) {
      *DoneFlagPtr = TRUE;
      return; }/*if*/;
   /*select*/{
      if (*DataFlagPtr) {
	 if (FilHdr_Flag(FilHdr, FLAG_ElmVisit)) {
	    *DoneFlagPtr = TRUE;
	    return; }/*if*/;
	 Set_Flag(FilHdr, FLAG_ElmVisit);
	 if (!FilHdr_Flag(FilHdr, FLAG_ElmNameVisit)) {
	    Set_Flag(FilHdr, FLAG_ElmNameVisit); }/*if*/;
      }else{
	 if (FilHdr_Flag(FilHdr, FLAG_ElmNameVisit)) {
	    *DoneFlagPtr = TRUE;
	    return; }/*if*/;
	 Set_Flag(FilHdr, FLAG_ElmNameVisit); };}/*select*/;
   }/*Set_ElmVisit*/


static void
Get_Report(
   GMC_ARG(tp_FilDsc, ReportFD),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind),
   GMC_ARG(tp_Status, ReportStatus)
   )
   GMC_DCL(tp_FilDsc, ReportFD)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
   GMC_DCL(tp_Status, ReportStatus)
{
   tp_Status Status, InpStatus;
   tp_FilHdr TgtValFilHdr;
   tp_FilInp FilInp;
   tp_FilHdr InpFilHdr;
   boolean DataFlag, DoneFlag;

   FORBIDDEN(FilHdr == ERROR);

   if (!NeedsData(FilHdr, InpKind)) {
      return; }/*if*/;


   if (!FilHdr_Flag(FilHdr, FLAG_Visit)) {
      Set_Flag(FilHdr, FLAG_Visit);
      Status = FilHdr_Status(FilHdr);
      if (IsSource(FilHdr)) {
	 if (FilHdr_TgtValStatus(FilHdr) <= ReportStatus) {
	    TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
	    if (FilHdr_Status(TgtValFilHdr) > STAT_Busy) {
	       Get_Report(ReportFD, TgtValFilHdr, IK_Simple, ReportStatus);
	       }/*if*/;
	    Ret_FilHdr(TgtValFilHdr); }/*if*/;
	 if (FilHdr_TgtValStatus(FilHdr) >= STAT_Warning
	     && Status <= ReportStatus) {
	    Do_Report(ReportFD, FilHdr, Status, ReportStatus); }/*if*/;
	 return; }/*if*/;

      if (Status <= ReportStatus) {
	 for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	      FilInp != NIL;
	      FilInp = FilInp_NextFilInp(FilInp)) {
	    InpFilHdr = FilInp_FilHdr(FilInp);
	    Get_Report(ReportFD, InpFilHdr, FilInp_InpKind(FilInp), ReportStatus);
	    InpStatus = FilHdr_MinStatus(InpFilHdr, FilInp_InpKind(FilInp));
	    Ret_FilHdr(InpFilHdr); }/*for*/; }/*if*/;

      if (Status <= ReportStatus
	  && !(IsStructMem(FilHdr)
	       && ((FilHdr_MinErrStatus(FilHdr) == STAT_OK
		    && Status == STAT_Circular)
		   || InpStatus == STAT_Error))) {
	 Do_Report(ReportFD, FilHdr, Status, ReportStatus); }/*if*/; }/*if*/;

   Set_ElmVisit(&DoneFlag, &DataFlag, FilHdr, InpKind);
   if (DoneFlag) {
      return; }/*if*/;
   /*select*/{
      if (DataFlag) {
	 if (FilHdr_ElmStatus(FilHdr) == STAT_ElmCircular) {
	    Do_Report(ReportFD, FilHdr, STAT_ElmCircular, ReportStatus); }/*if*/;
	 if (FilHdr_ElmStatus(FilHdr) <= ReportStatus) {
	    Get_ElmReport(ReportFD, FilHdr, TRUE, ReportStatus); }/*if*/;
      }else{
	 if (FilHdr_ElmNameStatus(FilHdr) == STAT_ElmCircular) {
	    Do_Report(ReportFD, FilHdr, STAT_ElmCircular, ReportStatus);
	    }/*if*/;
	 if (FilHdr_ElmNameStatus(FilHdr) <= ReportStatus) {
	    Get_ElmReport(ReportFD, FilHdr, FALSE, ReportStatus);
	    }/*if*/; };}/*select*/;

   }/*Get_Report*/


static void
Get_ElmReport(
   GMC_ARG(tp_FilDsc, ReportFD),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(boolean, DataFlag),
   GMC_ARG(tp_Status, ReportStatus)
   )
   GMC_DCL(tp_FilDsc, ReportFD)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(boolean, DataFlag)
   GMC_DCL(tp_Status, ReportStatus)
{
   boolean ViewSpecFlag;
   tp_FilElm FilElm;
   tp_FilHdr ElmFilHdr, TgtValFilHdr;
   tp_InpKind InpKind;

   if (FilHdr_Status(FilHdr) <= STAT_Error) {
      return; }/*if*/;

   ViewSpecFlag = IsViewSpec(FilHdr);
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);
      if (DataFlag || IsRef(ElmFilHdr)) {
	 /*select*/{
	    if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) == STAT_NoFile) {
	       if (FilHdr_TgtValStatus(ElmFilHdr) != STAT_OK) {
		  TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(ElmFilHdr));
		  Get_Report(ReportFD, TgtValFilHdr, IK_Simple, ReportStatus);
		  Ret_FilHdr(TgtValFilHdr); }/*if*/;
	    }else{
	       InpKind = (DataFlag ? IK_Trans : IK_TransName);
	       Get_Report(ReportFD, ElmFilHdr, InpKind, ReportStatus);
	       };}/*select*/; }/*if*/;
      if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) != STAT_NoFile) {
	 FilElm = FilElm_NextStrFilElm(FilElm); }/*if*/;
      Ret_FilHdr(ElmFilHdr); }/*for*/;
   }/*Get_ElmReport*/


static void
Clr_VisitFlags(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilInp FilInp;
   tp_FilElm FilElm;
   tp_FilHdr TgtValFilHdr, InpFilHdr, ElmFilHdr;

   if (!FilHdr_Flag(FilHdr, FLAG_Visit)) {
      return; }/*if*/;
   Clr_Flag(FilHdr, FLAG_Visit);
   if (FilHdr_Flag(FilHdr, FLAG_ElmVisit)) {
      Clr_Flag(FilHdr, FLAG_ElmVisit); }/*if*/;
   if (FilHdr_Flag(FilHdr, FLAG_ElmNameVisit)) {
      Clr_Flag(FilHdr, FLAG_ElmNameVisit); }/*if*/;
   if (IsSource(FilHdr)) {
      TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
      if (TgtValFilHdr != NIL) {
	 Clr_VisitFlags(TgtValFilHdr);
	 Ret_FilHdr(TgtValFilHdr); }/*if*/; }/*if*/;
   for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	FilInp != NIL;
	FilInp = FilInp_NextFilInp(FilInp)) {
      InpFilHdr = FilInp_FilHdr(FilInp);
      Clr_VisitFlags(InpFilHdr);
      Ret_FilHdr(InpFilHdr); }/*for*/;
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      Clr_VisitFlags(ElmFilHdr);
      TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(ElmFilHdr));
      if (TgtValFilHdr != NIL) {
	 Clr_VisitFlags(TgtValFilHdr);
	 Ret_FilHdr(TgtValFilHdr); }/*if*/;
      Ret_FilHdr(ElmFilHdr); }/*for*/;
   }/*Clr_VisitFlags*/


void
WriteReport(
   GMC_ARG(tp_FilDsc, StatusFD),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Status, ReportStatus)
   )
   GMC_DCL(tp_FilDsc, StatusFD)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Status, ReportStatus)
{
   if (FilHdr_MinStatus(FilHdr, IK_Trans) > ReportStatus) {
      return; }/*if*/;

   Write(StatusFD, "** Summary of ");
   switch (ReportStatus) {
      case STAT_Warning: {
	 Write(StatusFD, "warning and error"); break;}/*case*/;
      case STAT_TgtValError: {
	 Write(StatusFD, "error"); break;}/*case*/;
      default: {
	 FATALERROR("Unexpected status"); };}/*select*/;
   Write(StatusFD, " messages for ");
   Print_FilHdr(StatusFD, (tp_Str)NIL, FilHdr);
   Writeln(StatusFD, "");

   Get_Report(StatusFD, FilHdr, IK_Trans, ReportStatus);
   Clr_VisitFlags(FilHdr);
   }/*WriteReport*/


static void
GetDepend1(
   GMC_ARG(tp_LocElm*, FirstLEPtr),
   GMC_ARG(tp_LocElm*, LastLEPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind),
   GMC_ARG(tp_FilHdr, ListFilHdr)
   )
   GMC_DCL(tp_LocElm*, FirstLEPtr)
   GMC_DCL(tp_LocElm*, LastLEPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
   GMC_DCL(tp_FilHdr, ListFilHdr)
{
   tp_LocElm LocElm;
   tp_FilInp FilInp;
   tp_FilElm FilElm;
   tp_FilHdr InpFilHdr, ElmFilHdr, TgtValFilHdr;
   boolean DoneFlag, DataFlag, ViewSpecFlag;

   FORBIDDEN(FilHdr == ERROR);

   if (!NeedsData(FilHdr, InpKind)) {
      return; }/*if*/;

   if (!FilHdr_Flag(FilHdr, FLAG_Visit)) {
      Set_Flag(FilHdr, FLAG_Visit);
      if (IsSource(FilHdr)) {
	 TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
	 if (TgtValFilHdr != NIL) {
	    if (!IsDfltTgtVal(TgtValFilHdr)) {
	       GetDepend1(FirstLEPtr, LastLEPtr, TgtValFilHdr, IK_Simple,
			  ListFilHdr); }/*if*/;
	    Ret_FilHdr(TgtValFilHdr); }/*if*/;
	 LocElm = Make_LocElm(FilHdr, RootFilPrm, ListFilHdr);
	 Chain_LocElms(FirstLEPtr, LastLEPtr, LocElm);
	 return; }/*if*/;

      for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	   FilInp != NIL;
	   FilInp = FilInp_NextFilInp(FilInp)) {
	 InpFilHdr = FilInp_FilHdr(FilInp);
	 GetDepend1(FirstLEPtr, LastLEPtr, InpFilHdr, FilInp_InpKind(FilInp),
		    ListFilHdr);
	 Ret_FilHdr(InpFilHdr); }/*for*/; }/*if*/;

   Set_ElmVisit(&DoneFlag, &DataFlag, FilHdr, InpKind);
   if (DoneFlag) {
      return; }/*if*/;
   ViewSpecFlag = IsViewSpec(FilHdr);
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);
      if ((DataFlag || IsRef(ElmFilHdr))
	  && !(ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) == STAT_NoFile)) {
	 GetDepend1(FirstLEPtr, LastLEPtr, ElmFilHdr,
		    (DataFlag ? IK_Trans : IK_TransName), ListFilHdr); }/*if*/;
      if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) != STAT_NoFile) {
	 FilElm = FilElm_NextStrFilElm(FilElm); }/*if*/;
      Ret_FilHdr(ElmFilHdr); }/*for*/;
   }/*GetDepend1*/


void
GetDepend(
   GMC_ARG(tp_LocElm*, FirstLEPtr),
   GMC_ARG(tp_LocElm*, LastLEPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilHdr, ListFilHdr)
   )
   GMC_DCL(tp_LocElm*, FirstLEPtr)
   GMC_DCL(tp_LocElm*, LastLEPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilHdr, ListFilHdr)
{
   GetDepend1(FirstLEPtr, LastLEPtr, FilHdr, IK_Trans, ListFilHdr);
   Clr_VisitFlags(FilHdr);
   }/*GetDepend*/


static void
Get_DPath1(
   GMC_ARG(boolean*, FoundPtr),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_InpKind, InpKind),
   GMC_ARG(tp_FilHdr, DepFilHdr),
   GMC_ARG(boolean, First)
   )
   GMC_DCL(boolean*, FoundPtr)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_InpKind, InpKind)
   GMC_DCL(tp_FilHdr, DepFilHdr)
   GMC_DCL(boolean, First)
{
   tp_Str Message;
   tp_FilInp FilInp;
   tp_FilHdr InpFilHdr, ElmFilHdr, TgtValFilHdr;
   boolean DoneFlag, DataFlag, ViewSpecFlag;
   tp_FilElm FilElm;

   FORBIDDEN(FilHdr == ERROR);

   *FoundPtr = FALSE;
   Message = NIL;

   if (!NeedsData(FilHdr, InpKind)) {
      return; }/*if*/;

   /*select*/{
      if (FilHdr_Flag(FilHdr, FLAG_Visit)) {
	 if (FilHdr == DepFilHdr) {
	    *FoundPtr = TRUE;
	    goto found; }/*if*/;
      }else{
	 Set_Flag(FilHdr, FLAG_Visit);

	 if (FilHdr == DepFilHdr && !First) {
	    *FoundPtr = TRUE;
	    goto found; }/*if*/;

	 if (IsSource(FilHdr)) {
	    TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
	    if (TgtValFilHdr != NIL) {
	       if (!IsDfltTgtVal(TgtValFilHdr)) {
		  Get_DPath1(FoundPtr, TgtValFilHdr, IK_Simple, DepFilHdr,
			     FALSE); }/*if*/;
	       Ret_FilHdr(TgtValFilHdr);
	       if (*FoundPtr) {
		  Message = "   is the bound value of:";
		  goto found; }/*if*/; }/*if*/;
	    return; }/*if*/;

	 for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	      FilInp != NIL;
	      FilInp = FilInp_NextFilInp(FilInp)) {
	    InpFilHdr = FilInp_FilHdr(FilInp);
	    Get_DPath1(FoundPtr, InpFilHdr,
		       FilInp_InpKind(FilInp), DepFilHdr, FALSE);
	    Ret_FilHdr(InpFilHdr);
	    if (*FoundPtr) {
	       Ret_FilInp(FilInp);
	       Message = "   is an input of:";
	       goto found; }/*if*/; }/*for*/; };}/*select*/;

   Set_ElmVisit(&DoneFlag, &DataFlag, FilHdr, InpKind);
   if (DoneFlag) {
      return; }/*if*/;
   ViewSpecFlag = IsViewSpec(FilHdr);
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);
      if ((DataFlag || IsRef(ElmFilHdr))
	  && !(ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) == STAT_NoFile
		&& FilHdr_TgtValStatus(ElmFilHdr) == STAT_OK)) {
	 Get_DPath1(FoundPtr, ElmFilHdr, (DataFlag ? IK_Trans : IK_TransName),
		    DepFilHdr, FALSE); }/*if*/;
      if (ViewSpecFlag && FilHdr_ElmStatus(ElmFilHdr) != STAT_NoFile) {
	 FilElm = FilElm_NextStrFilElm(FilElm); }/*if*/;
      Ret_FilHdr(ElmFilHdr);
      if (*FoundPtr) {
	 Ret_FilElm(FilElm);
	 Message = "   is an element of:";
	 goto found; }/*if*/; }/*for*/;
   return;

found:;
   if (Message != NIL) LogMessage(Message);
   Print_OdinExpr(FilHdr_LocHdr(FilHdr), RootFilPrm);
   }/*Get_DPath1*/


void
Local_Get_DPath(
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(tp_Str, OdinExpr)
{
   tp_Nod Root;
   tp_PrmFHdr PrmFHdr;
   tp_FilHdr FilHdr, DepFilHdr;
   tp_FilPrm FilPrm;
   boolean Found;

   Root = YY_Parser(OdinExpr, (tp_FileName)NIL, (int *)NIL);
   if (Root == ERROR) {
      return; }/*if*/;
   PrmFHdr = Nod_PrmFHdr(Root);
   Ret_Nod(Root);
   Use_PrmFHdr(&FilHdr, &FilPrm, PrmFHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;

   DepFilHdr = Deref(LocHdr_FilHdr(FilPVal_LocHdr(FilPrm_FilPVal(FilPrm))));
   if (DepFilHdr == ERROR) {
      SystemError("+depend parameter required.\n");
      Ret_FilHdr(FilHdr);
      return; }/*if*/;

   Get_DPath1(&Found, FilHdr, IK_Trans, DepFilHdr, TRUE);
   Clr_VisitFlags(FilHdr);
   Ret_FilHdr(FilHdr); Ret_FilHdr(DepFilHdr);
   }/*Local_Get_DPath*/

