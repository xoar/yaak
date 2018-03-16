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
#include "inc/ExecSpc.h"
#include "inc/FileName.h"
#include "inc/Job.h"
#include "inc/LogLevel_.h"
#include "inc/Status_.h"
#include "inc/Str.h"
#include "inc/TClass_.h"


void
ExecInternal(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Status, DepStatus),
   GMC_ARG(tp_Date, DepModDate)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Status, DepStatus)
   GMC_DCL(tp_Date, DepModDate)
{
   tps_ExecSpc _ExecSpc; tp_ExecSpc ExecSpc = &_ExecSpc;
   tp_Job Job;
   tp_Tool Tool;
   tp_TClass TClass;
   tp_InpFilHdrs Inputs;
   tp_OutFilHdrs Outputs;
   tp_FileName OldErrFileName;
   tp_FilDsc OldErrFD;
   tps_FileName InFileName, OutFileName;
   tps_Str StrBuf;
   tp_FilDsc InFD, OutFD;
   tp_Status MinStatus;
   tp_FilHdr ElmFilHdr, DestFilHdr, OprFilHdr;
   tp_LocElm LocElm, FirstLE, LastLE;
   tp_FilElm FilElm;
   int i;
   boolean ErrFlag, OldIsIPC;

   Do_Log("Generating", FilHdr, LOGLEVEL_IntGenerate);
   MinStatus = DepStatus;

   Tool = FilHdr_Tool(FilHdr);
   FilHdr_ExecSpc(ExecSpc, FilHdr);
   Job = New_Job();
   ExecSpc->Job = Job;
   Inputs = ExecSpc->InpFilHdrs;
   Outputs = ExecSpc->OutFilHdrs;

   Save_ErrFile(&OldErrFileName, &OldIsIPC, &OldErrFD);
   Set_ErrFile(Job->ErrorFN, FALSE, (tp_FilDsc)NIL);
   Clr_ErrStatus(FilHdr);

   TClass = Tool_TClass(Tool);
   switch (TClass) {
      case TC_Str: {
	 break;}/*case*/;
      case TC_StructMem: {
	 FATALERROR("StructMem's should always be up-to-date");
	 break;}/*case*/;
      case TC_PrmValues: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 FirstLE = NIL; LastLE = NIL;
	 FilPVal_LocElm(&FirstLE, &LastLE,
			FilPrm_FilPVal(FilHdr_FilPrm(FilHdr)), FilHdr);
	 Set_LocElm(FilHdr, FirstLE);
	 break;}/*case*/;
      case TC_First: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 /*select*/{
	    if (FilHdr_LocElm(Inputs[0]) == 0) {
	       LocElm = Make_LocElm(NilStrFilHdr, RootFilPrm, FilHdr);
	    }else{
	       FilElm = LocElm_FilElm(FilHdr_LocElm(Inputs[0]));
	       ElmFilHdr = FilElm_FilHdr(FilElm);
	       Ret_FilElm(FilElm);
	       LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr);
	       Ret_FilHdr(ElmFilHdr); };}/*select*/;
	 Set_LocElm(FilHdr, LocElm);
	 break;}/*case*/;
      case TC_DrvDirElm: {
	 if (MinStatus > STAT_NoFile) {
	    Add_ErrStatus(FilHdr, STAT_NoFile);
	    MinStatus = STAT_NoFile; }/*if*/;
	 break;}/*case*/;
      case TC_VirDirElm: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 LocElm = 0;
	 ElmFilHdr = Do_Key(FilHdr_Father(Copy_FilHdr(Inputs[0])),
			    FilHdr_Key(StrBuf, FilHdr));
	 if (ElmFilHdr != ERROR) {
	    LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr);
	    Ret_FilHdr(ElmFilHdr); }/*if*/;
	 Set_LocElm(FilHdr, LocElm);
	 break;}/*case*/;
      case TC_Collect: {
	 FORBIDDEN(ExecSpc->NumInps < 1 || ExecSpc->NumOuts != 1);
	 FirstLE = NIL; LastLE = NIL;
	 for (i=0; i<ExecSpc->NumInps; i++) {
	    LocElm = Make_LocElm(Inputs[i], FilHdr_FilPrm(FilHdr), FilHdr);
	    Chain_LocElms(&FirstLE, &LastLE, LocElm);
	    }/*for*/;
	 Set_LocElm(FilHdr, FirstLE);
	 if (IsPntr(FilHdr)) Validate_IsPntr(FilHdr);
	 break;}/*case*/;
      case TC_ReadList: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Exec_List(FilHdr, Inputs[0], FilHdr_FilPrm(FilHdr), FALSE);
	 if (IsPntr(FilHdr)) Validate_IsPntr(FilHdr);
	 break;}/*case*/;
      case TC_SrcNames: case TC_OpNames: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 FilHdr_DataFileName(InFileName, Inputs[0]);
	 WriteSrcNames(OutFD, InFileName, (TClass == TC_OpNames));
	 Close(OutFD);
	 break;}/*case*/;
      case TC_ViewSpec: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Exec_List(FilHdr, Inputs[0], RootFilPrm, FALSE);
	 Validate_ViewSpec(FilHdr);
	 break;}/*case*/;
      case TC_CmptView: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Exec_CmptView(&ErrFlag, FilHdr, Inputs[0]);
	 if (ErrFlag) {
	    Add_ErrStatus(FilHdr, STAT_TgtValError);
	    if (MinStatus > STAT_TgtValError) {
	       MinStatus = STAT_TgtValError; }/*if*/; }/*if*/;
	 break;}/*case*/;
      case TC_Directory: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 ElmFilHdr = FilHdr_DirFilHdr(Copy_FilHdr(Inputs[0]));
	 Set_LocElm(FilHdr, Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr));
	 Ret_FilHdr(ElmFilHdr);
	 break;}/*case*/;
      case TC_Name: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WritePrmOdinExpr(OutFD, Inputs[0], FilHdr_FilPrm(FilHdr));
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Names: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteNames(OutFD, Inputs[0], FilHdr_FilPrm(FilHdr));
	 Close(OutFD);
	 break;}/*case*/;
      case TC_FileName: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 /*select*/{
	    if (IsAtmc(Inputs[0])) {
	       Get_WorkFileName(OutFileName, Job, FilHdr);
	       OutFD = FileName_WFilDsc(OutFileName, TRUE);
	       FilHdr_DataFileName(InFileName, Inputs[0]);
	       Writeln(OutFD, InFileName);
	       Close(OutFD);
	    }else{
	       FilHdr_Error("Input to :filename must be atomic: <%s>.\n",
			    Inputs[0]); };}/*select*/;
	 break;}/*case*/;
      case TC_FileNames: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteFlat(OutFD, Inputs[0]);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Cat: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteCat(OutFD, Inputs[0]);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Union: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_UnionLocElm(Inputs[0], FilHdr));
	 break;}/*case*/;
      case TC_PntrHo: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_PntrHoLocElm(Inputs[0], FilHdr));
	 break;}/*case*/;
      case TC_Apply: {
	 FORBIDDEN(ExecSpc->NumInps != 2 || ExecSpc->NumOuts != 1);
	 OprFilHdr = Deref(Copy_FilHdr(Inputs[1]));
	 FilHdr_DataFileName(InFileName, OprFilHdr);
	 Push_ContextFilHdr(OprFilHdr);
	 Set_LocElm(FilHdr, Make_ApplyLocElm(Inputs[0], FilHdr, InFileName));
	 Pop_ContextFilHdr();
	 break;}/*case*/;
      case TC_DerefPrmVal: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_DerefPrmValLocElm(Inputs[0], FilHdr));
	 break;}/*case*/;
      case TC_Map: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_MapLocElm(Inputs[0], FilHdr));
	 break;}/*case*/;
      case TC_Recurse: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_RecurseLocElm(Inputs[0], FilHdr));
	 break;}/*case*/;
      case TC_Extract: case TC_Delete: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Set_LocElm(FilHdr, Make_ExDelLocElm(Inputs[0], FilHdr,
					     (TClass == TC_Extract)));
	 break;}/*case*/;
      case TC_PntrElm: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 LocElm = 0;
	 ElmFilHdr = Do_Key(Copy_FilHdr(Inputs[0]), FilHdr_Key(StrBuf, FilHdr));
	 if (ElmFilHdr != ERROR) {
	    LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr);
	    Ret_FilHdr(ElmFilHdr); }/*if*/;
	 Set_LocElm(FilHdr, LocElm);
	 break;}/*case*/;
      case TC_Error: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteReport(OutFD, Inputs[0], STAT_TgtValError);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Warning: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteReport(OutFD, Inputs[0], STAT_Warning);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Label: {
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 Writeln(OutFD, FilHdr_Label(StrBuf, Inputs[0], FALSE));
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Labels: {
	 FORBIDDEN(!IsList(Inputs[0]));
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteLabels(OutFD, Inputs[0]);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Id: {
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteInt(OutFD, (int)FilHdr_LocHdr(Inputs[0]));
	 Writeln(OutFD, "");
	 Close(OutFD);
	 break;}/*case*/;
      case TC_Depend: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 FirstLE = NIL; LastLE = NIL;
	 GetDepend(&FirstLE, &LastLE, Inputs[0], FilHdr);
	 Set_LocElm(FilHdr, FirstLE);
	 break;}/*case*/;
      case TC_InternalPntr: {
	 break;}/*case*/;
      case TC_TargetsPtr: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Exec_TargetsPtr(FilHdr, Inputs[0]);
	 break;}/*case*/;
      case TC_TargetsInc: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Exec_List(FilHdr, Inputs[0], RootFilPrm, TRUE);
	 break;}/*case*/;
      case TC_Targets: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 FilHdr_DataFileName(InFileName, Inputs[0]);
	 Push_ContextFilHdr(Copy_FilHdr(Inputs[0]));
	 Exec_Targets(OutFD, InFileName);
	 Pop_ContextFilHdr();
	 Close(OutFD);
	 break;}/*case*/;
      case TC_ActTargets: case TC_VirTargets: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 FilHdr_DataFileName(InFileName, Inputs[0]);
	 InFD = FileName_RFilDsc(InFileName, FALSE);
	 LocElm = NIL;
	 if (InFD != NIL) {
	    Push_ContextFilHdr(Copy_FilHdr(FilHdr));
	    LocElm = Make_TargetsLocElm(FilHdr, InFD, InFileName, DepModDate,
					 (TClass == TC_VirTargets));
	    Pop_ContextFilHdr();
	    Close(InFD); }/*if*/;
	 Set_LocElm(FilHdr, LocElm);
	 break;}/*case*/;
      case TC_VirDir: {
	 Exec_VirDir(FilHdr, Inputs[0]);
	 break;}/*case*/;
      case TC_CopyCmd: {
	 DestFilHdr = Deref(LocHdr_FilHdr
	    (FilPVal_LocHdr(FilPrm_FilPVal(FilHdr_FilPrm(FilHdr)))));
	 /*select*/{
	    if (DestFilHdr == ERROR) {
	       SystemError("+copydestdesc=(dest) parameter required.\n");
	    }else{
	       Exec_CopyCmd(FilHdr, DestFilHdr, Inputs[0]);
	       Ret_FilHdr(DestFilHdr); };}/*select*/;
	 break;}/*case*/;
      case TC_ExpandHooks: {
	 FORBIDDEN(ExecSpc->NumInps != 2 || ExecSpc->NumOuts != 1);
	 FilHdr_DataFileName(InFileName, Inputs[1]);
	 InFD = FileName_RFilDsc(InFileName, TRUE);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 ExpandHooks(OutFD, InFD, Inputs[0]);
	 Close(InFD); Close(OutFD);
	 break;}/*case*/;
      case TC_NestedHooks: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 2);
	 FilHdr_DataFileName(InFileName, Inputs[0]);
	 InFD = FileName_RFilDsc(InFileName, TRUE);
	 Get_WorkFileName(OutFileName, Job, Outputs[1]);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 NestedHooks(Outputs[0], Outputs[1], OutFD,
		     InFD, FilHdr_FilPrm(FilHdr));
	 Close(InFD); Close(OutFD);
	 break;}/*case*/;
      case TC_TextDef: {
	 FilHdr_DataFileName(InFileName, Inputs[0]);
	 InFD = FileName_RFilDsc(InFileName, TRUE);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteTextDef(FilHdr, OutFD, OutFileName, InFD, InFileName);
	 Close(InFD); Close(OutFD);
	 break;}/*case*/;
      case TC_PrefixHelp: case TC_SuffixHelp: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteSrcFilTyps(OutFD, (TClass == TC_PrefixHelp));
	 Close(OutFD);
	 break;}/*case*/;
      case TC_DrvHelp: {
	 FORBIDDEN(ExecSpc->NumInps != 1 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WriteDrvHelp(OutFD, Inputs[0]);
	 Close(OutFD);
	 break;}/*case*/;
      case TC_PrmHelp: {
	 FORBIDDEN(ExecSpc->NumInps > 2 || ExecSpc->NumOuts != 1);
	 Get_WorkFileName(OutFileName, Job, FilHdr);
	 OutFD = FileName_WFilDsc(OutFileName, TRUE);
	 WritePrmHelp(OutFD, Inputs[0], FilHdr_FilPrm(FilHdr));
	 Close(OutFD);
	 break;}/*case*/;
      default: {
	 FATALERROR("illegal system tool"); }}/*switch*/;

   ErrFlag = IsErr();
   Set_ErrFile(OldErrFileName, OldIsIPC, OldErrFD);
   if (ErrFlag) {
      Add_StatusFile(FilHdr, STAT_Error, Job->ErrorFN);
      if (MinStatus > STAT_Error) {
	 MinStatus = STAT_Error; }/*if*/; }/*if*/;
   if (MinStatus == STAT_Error && IsTargets(FilHdr)) {
      MinStatus = STAT_TgtValError; }/*if*/;

   Do_Update(FilHdr, ExecSpc->OutFilHdrs, ExecSpc->NumOuts, Job,
	     MinStatus, DepModDate, TRUE);

   Ret_Job(Job);
   Ret_ExecSpc(ExecSpc);
   }/*ExecInternal*/


