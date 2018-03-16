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
#include "inc/LogLevel_.h"
#include "inc/OC_NodTyp_.h"
#include "inc/Status_.h"
#include "inc/Str.h"


static int CommandNesting = 0;
static int MaxCommandNesting = 100;


static void
Execute(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(boolean, Interactive)
{
   tp_FilDsc InFD;
   tp_Nod Nod;
   tps_Str StrBuf, DirName;
   tp_Str Str;
   int LineNum;
   boolean Abort;

   if (IsExecutable(FileName)) {
      SystemExecCmdWait(AbortPtr, FileName, Interactive);
      if (*AbortPtr) {
	 SystemError("\"%s\": exec failed with non-zero status.\n", OdinExpr);
	 }/*if*/;
      return; }/*if*/;

   InFD = FileName_RFilDsc(FileName, FALSE);
   if (InFD == ERROR) {
      SystemError("\"%s\": cannot read.\n", FileName);
      *AbortPtr = TRUE;
      return; }/*if*/;
   LineNum = 0;

   Push_Context(DirName, FileName);

   ChangeDir(AbortPtr, DirName);
   if (*AbortPtr) {
      SystemError("\"%s\": cd failed.\n", DirName);
      goto done; }/*if*/;

   Unblock_Signals();
   Str = ReadLine(StrBuf, InFD);
   Block_Signals();
   if (Str == NIL) {
      goto done; }/*if*/;

   while (Str != NIL && !Signalled) {
      if (LogLevel >= LOGLEVEL_OdinCommand) {
	 Write(StdOutFD, "<> ");
	 WriteLine(StdOutFD, Str); }/*if*/;
      Nod = OC_Parser(Str, FileName, &LineNum);
      if (Nod == ERROR) {
	 *AbortPtr = TRUE;
	 goto done; }/*if*/;
      CommandInterpreter(AbortPtr, Nod, FALSE);
      Ret_Nod(Nod);
      if (*AbortPtr) {
	 goto done; }/*if*/;
      Unblock_Signals();
      Str = ReadLine(StrBuf, InFD);
      Block_Signals(); }/*while*/;

done:;
   if (Signalled) {
      *AbortPtr = TRUE; }/*if*/;
   Pop_Context(DirName);

   ChangeDir(&Abort, DirName);
   if (Abort) {
      SystemError("\"%s\": cd failed.\n", DirName);
      *AbortPtr = TRUE; }/*if*/;
   Close(InFD);
   }/*Execute*/


static boolean
IsStatus_MsgLevel(
   GMC_ARG(int, Level)
   )
   GMC_DCL(int, Level)
{
   return (Level > 0);
   }/*IsStatus_MsgLevel*/


boolean
IsIncremental_MsgLevel(
   GMC_ARG(int, Level)
   )
   GMC_DCL(int, Level)
{
   return (Level == 2 || Level == 4);
   }/*IsIncremental_MsgLevel*/


static boolean
IsSummary_MsgLevel(
   GMC_ARG(int, Level)
   )
   GMC_DCL(int, Level)
{
   return (Level > 2);
   }/*IsSummary_MsgLevel*/


static void
Report_Status(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(tp_Status, Status),
   GMC_ARG(tp_Status, ElmStatus)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(tp_Status, Status)
   GMC_DCL(tp_Status, ElmStatus)
{
   tp_Str Message;

   if (!((Status <= STAT_Warning && IsStatus_MsgLevel(WarnLevel))
	 || (Status <= STAT_TgtValError && IsStatus_MsgLevel(ErrLevel)))) {
      return; }/*if*/;

   switch((Status < ElmStatus) ? Status : ElmStatus) {
      case STAT_Unknown: {
	 Message = "--- <%s> is not up-to-date ---\n";
	 break;}/*case*/;
      case STAT_Pending: {
	 Message = "--- <%s> is pending input computations ---\n";
	 break;}/*case*/;
      case STAT_Ready: {
	 Message = "--- <%s> is ready to be computed ---\n";
	 break;}/*case*/;
      case STAT_Busy: {
	 Message = "--- <%s> is being computed ---\n";
	 break;}/*case*/;
      case STAT_SysAbort: {
	 Message = "--- System abort status set for <%s> ---\n";
	 break;}/*case*/;
      case STAT_NoFile: {
	 Message = ((Status == STAT_NoFile)
		    ? "--- <%s> does not exist ---\n"
		    : "--- An element of <%s> does not exist ---\n");
	 break;}/*case*/;
      case STAT_ElmCircular: {
	 Message = "--- An element of <%s> depends on itself ---\n";
	 break;}/*case*/;
      case STAT_Circular: {
	 Message = "--- <%s> depends on itself ---\n";
	 break;}/*case*/;
      case STAT_Error: {
	 Message = "--- Error status set for <%s> ---\n";
	 break;}/*case*/;
      case STAT_TgtValError: {
	 Message = "--- Target-Error status set for <%s> ---\n";
	 break;}/*case*/;
      case STAT_Warning: {
	 Message = "--- Warning status set for <%s> ---\n";
	 break;}/*case*/;
      case STAT_OK: {
	 Message = NIL;
	 break;}/*case*/;
      default: {
	 FATALERROR("bad status"); };}/*switch*/;
   if (Message != NIL) {
      SystemError(Message, OdinExpr); }/*if*/;
   }/*Report_Status*/


static void
ShowStatus(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(tp_Status, Status),
   GMC_ARG(tp_Status, ElmStatus)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(tp_Status, Status)
   GMC_DCL(tp_Status, ElmStatus)
{
   tp_Str DerivStr;
   tp_Status RepStatus;
   tps_FileName FileName;
   tp_FilDsc FilDsc;
   boolean ExecFlag;

   if (Status == STAT_Unknown) {
      return; }/*if*/;

   /*select*/{
      if (Status <= STAT_Warning && IsSummary_MsgLevel(WarnLevel)) {
	 DerivStr = ":warn";
      }else if (Status <= STAT_TgtValError && IsSummary_MsgLevel(ErrLevel)) {
	 DerivStr = ":err";
      }else{
	 DerivStr = 0; };}/*select*/;
   if (DerivStr != 0) {
      (void)strcat(OdinExpr, DerivStr);
      Get_OdinFile(FileName, &RepStatus, &ExecFlag, OdinExpr, TRUE);
      if (RepStatus == STAT_OK) {
	 FORBIDDEN(FileName[0] == 0);
	 FilDsc = FileName_RFilDsc(FileName, FALSE);
	 /*select*/{
	    if (FilDsc == ERROR) {
	       SystemError("\"%s\": could not read error file.\n", FileName);
	    }else{
	       FileCopy(StdOutFD, FilDsc);
	       Close(FilDsc); };}/*select*/; }/*if*/;
      return; }/*if*/;

   Report_Status(OdinExpr, Status, STAT_OK);
   }/*ShowStatus*/


static void
Do_ShowStatus(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
{
   tps_Str OdinExpr;
   tp_Status Status;
   tps_FileName FileName;
   boolean ExecFlag, Abort;

   OC_Unparse(OdinExpr, Root);
   Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, FALSE);
   *AbortPtr = (Status <= STAT_TgtValError);
   if (ExecFlag && !*AbortPtr) {
      if (LogLevel >= LOGLEVEL_OdinCommand) {
	 Write(StdOutFD, "<> ");
	 Write(StdOutFD, OdinExpr);
	 Writeln(StdOutFD, " !"); }/*if*/;
      Execute(&Abort, FileName, OdinExpr, FALSE);
      if (Abort) {
	 *AbortPtr = TRUE; }/*if*/; }/*if*/;
   ShowStatus(OdinExpr, Status, STAT_OK);
   }/*Do_ShowStatus*/


static void
Display(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
{
   tps_Str OdinExpr;
   tp_Status Status;
   tps_FileName FileName;
   tp_FilDsc InFD;
   boolean ExecFlag;

   OC_Unparse(OdinExpr, Nod_Son(1, Root));
   Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, TRUE);
   *AbortPtr = (Status < STAT_TgtValError);
   if (*AbortPtr) {
      goto done; }/*if*/;
   if (strcmp(FileName, "") == 0) {
      SystemError("No file value associated with: %s\n", OdinExpr);
      *AbortPtr = TRUE;
      goto done; }/*if*/;
   if (!Exists(FileName)) {
      goto done; }/*if*/;
   if (IsDirectory_FileName(FileName)) {
      SystemError("\"%s\": cannot display a directory.\n", OdinExpr);
      goto done; }/*if*/;
   InFD = FileName_RFilDsc(FileName, FALSE);
   if (InFD == ERROR) {
      if (Exists(FileName)) {
	 SystemError("\"%s\": cannot read.\n", OdinExpr);
	 *AbortPtr = TRUE; }/*if*/;
      goto done; }/*if*/;
   Unblock_Signals();
   FileCopy(StdOutFD, InFD);
   Block_Signals();
   Close(InFD);
   if (Signalled) {
      *AbortPtr = TRUE; }/*if*/;
done:;
   ShowStatus(OdinExpr, Status, STAT_OK);
   }/*Display*/


static void
Copy(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, FromNod),
   GMC_ARG(tp_Nod, ToNod)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, FromNod)
   GMC_DCL(tp_Nod, ToNod)
{
   tps_Str OdinExpr;
   tps_FileName FileName;
   tp_Status Status;
   boolean ExecFlag;

   *AbortPtr = FALSE;
   OC_Unparse(OdinExpr, FromNod);
   (void)strcat(OdinExpr, "+copy_dest_desc=(");
   OC_Unparse(Tail(OdinExpr), ToNod);
   (void)strcat(OdinExpr, "):copy_cmd");
   Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, FALSE);
   *AbortPtr = (Status < STAT_TgtValError);
   ShowStatus(OdinExpr, Status, STAT_OK);
   }/*Copy*/


static void
Edit(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
   GMC_DCL(boolean, Interactive)
{
   tps_FileName FileName;
   tp_Status Status;
   tp_Str Editor;
   tps_Str CmdStr, OdinExpr;
   boolean ExecFlag;

   Editor = GetEnv("EDITOR");
   if (Editor == NIL) Editor = "vi";

   OC_Unparse(OdinExpr, Nod_Son(1, Root));
   Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, TRUE);
   *AbortPtr = (Status < STAT_NoFile);
   if (*AbortPtr) {
      ShowStatus(OdinExpr, Status, STAT_OK);
      return; }/*if*/;
   if (strcmp(FileName, "") == 0) {
      SystemError("No file value associated with: %s\n", OdinExpr);
      *AbortPtr = TRUE;
      return; }/*if*/;

   (void)strcpy(CmdStr, Editor);
   (void)strcat(CmdStr, " ");
   (void)strcat(CmdStr, FileName);
   SystemExecCmdWait(AbortPtr, CmdStr, Interactive);
   Test(OdinExpr);
   Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, TRUE);
   ShowStatus(OdinExpr, Status, STAT_OK);
   }/*Edit*/


static void
Do_Execute(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
   GMC_DCL(boolean, Interactive)
{
   tp_Nod TgtNod, CmdNod;
   tps_FileName FileName;
   tp_Status Status;
   tp_Str Cmd;
   tps_Str CmdStr, OdinExpr;
   boolean ExecFlag;

   CmdNod = Nod_Son(1, Root);
   if (CmdNod == NIL) {
      Get_Commands(AbortPtr);
      return; }/*if*/;

   TgtNod = NIL;
   if (Nod_NodTyp(CmdNod) == DRVFIL) {
      TgtNod = CmdNod;
      CmdNod = Nod_Brother(CmdNod);
      OC_Unparse(OdinExpr, TgtNod);
      Get_OdinFile(FileName, &Status, &ExecFlag, OdinExpr, TRUE);
      *AbortPtr = (Status < STAT_NoFile);
      if (*AbortPtr) {
	 goto done; }/*if*/;
      if (strcmp(FileName, "") == 0) {
	 SystemError("No file value associated with: %s\n", OdinExpr);
	 *AbortPtr = TRUE;
	 goto done; }/*if*/;
      if (CmdNod == NIL) {
	 if (Status <= STAT_Error) {
	    *AbortPtr = TRUE;
	    goto done; }/*if*/;
	 Execute(AbortPtr, FileName, OdinExpr, Interactive);
	 goto done; }/*if*/; }/*if*/;

   FORBIDDEN(Nod_NodTyp(CmdNod) != HOSTWD);
   Cmd = Sym_Str(Nod_Sym(CmdNod));
   (void)strcpy(CmdStr, Cmd);
   if (TgtNod != NIL) {
      (void)strcat(CmdStr, " ");
      (void)strcat(CmdStr, FileName); }/*if*/;
   SystemExecCmdWait(AbortPtr, CmdStr, Interactive);
   if (Signalled) {
      *AbortPtr = TRUE; }/*if*/;
   if (TgtNod == NIL) {
      return; }/*if*/;
   Test(OdinExpr);

done:;
   ShowStatus(OdinExpr, Status, STAT_OK);
   }/*Do_Execute*/


void
UtilityHelp(GMC_ARG_VOID)
{
   Writeln(StdOutFD, "*?* test redo inputs outputs elements elements-of alias");
   }/*UtilityHelp*/


static void
Utility(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
{
   int OdinFileID;
   tp_Str Cmd;
   tps_Str OdinExpr;
   tp_Status Status, ElmStatus;

   *AbortPtr = FALSE;
   if (Nod_NumSons(Root) == 1) {
      Cmd = Sym_Str(Nod_Sym(Nod_Son(1, Root)));
      /*select*/{
	 if (strcmp(Cmd, "test") == 0) {
	    Test_All();
	 }else if (strcmp(Cmd, "quit") == 0) {
	    Exit(0);
	 }else{
	    SystemError("Unknown default utility <%s>.\n", Cmd);
	    *AbortPtr = TRUE; };}/*select*/;
      return; }/*if*/;
   Cmd = Sym_Str(Nod_Sym(Nod_Son(2, Root)));
   OC_Unparse(OdinExpr, Nod_Son(1, Root));
   /*select*/{
      if (strlen(Cmd) == 2) {
	 OdinFileID = Str_PosInt(OdinExpr);
	 if (OdinFileID <= 0) {
	    SystemError("<%s> seen where a number was expected.\n", OdinExpr);
	    *AbortPtr = TRUE;
	    return; }/*if*/;
	 ID_OdinExpr(OdinExpr, OdinFileID);
      }else{
	 OdinExpr_ID(&OdinFileID, OdinExpr);
	 if (OdinFileID == 0) {
	    *AbortPtr = TRUE;
	    return; }/*if*/; };}/*select*/;
   ;/*select*/{
      if (strcmp(Cmd, "name") == 0 || strcmp(Cmd, "NA") == 0) {
	 WriteInt(StdOutFD, OdinFileID);
	 Write(StdOutFD, "\t- ");
	 Writeln(StdOutFD, OdinExpr);
      }else if (strcmp(Cmd, "long-name") == 0 || strcmp(Cmd, "LN") == 0) {
	 ID_LongOdinExpr(OdinExpr, OdinFileID);
	 Writeln(StdOutFD, OdinExpr);
      }else if (strcmp(Cmd, "elements") == 0 || strcmp(Cmd, "EL") == 0) {
	 Get_Elements(OdinFileID);
      }else if (strcmp(Cmd, "element-of") == 0 || strcmp(Cmd, "EO") == 0) {
	 Get_ElementsOf(OdinFileID);
      }else if (strcmp(Cmd, "inputs") == 0 || strcmp(Cmd, "IN") == 0) {
	 Get_Inputs(OdinFileID);
      }else if (strcmp(Cmd, "outputs") == 0 || strcmp(Cmd, "OU") == 0) {
	 Get_Outputs(OdinFileID);
      }else if (strcmp(Cmd, "dpath") == 0 || strcmp(Cmd, "DP") == 0) {
	 Get_DPath(OdinExpr);
      }else if (strcmp(Cmd, "redo") == 0 || strcmp(Cmd, "RE") == 0) {
	 Redo(OdinExpr);
	 return;
      }else if (strcmp(Cmd, "test") == 0 || strcmp(Cmd, "TE") == 0) {
	 Test(OdinExpr);
      }else if (strcmp(Cmd, "alias") == 0) {
	 Do_Alias(OdinExpr, TRUE);
      }else{
	 SystemError("Unknown utility <%s>.\n", Cmd);
	 *AbortPtr = TRUE;
	 return; };}/*select*/;
   Get_Status(&Status, &ElmStatus, OdinFileID);
   Report_Status(OdinExpr, Status, ElmStatus);
   }/*Utility*/


void
UtilityDefaultHelp(GMC_ARG_VOID)
{
   Writeln(StdOutFD, "*?* test\n");
   }/*UtilityDefaultHelp*/


static void
Do_SetVar(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
{
   tp_Str VarStr, ValStr;
   tp_Nod ValNod;
   tps_Str ValBuf;

   VarStr = Sym_Str(Nod_Sym(Nod_Son(1, Root)));
   ValNod = Nod_Son(2, Root);
   if (Nod_NodTyp(ValNod) == HOSTWD) {
      Set_HostVar(AbortPtr, VarStr, Sym_Str(Nod_Sym(ValNod)));
      return; }/*if*/;
   OC_Unparse(ValBuf, ValNod);
   ValStr = Sym_Str(Str_Sym(ValBuf));
   SetVar(AbortPtr, VarStr, ValStr);
   }/*Do_SetVar*/


void
Print_Banner(GMC_ARG_VOID)
{
   tps_Str Banner;

   Get_Banner(Banner);
   Writeln(StdOutFD, Banner);
   }/*Print_Banner*/


static void
Do_Command(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
   GMC_DCL(boolean, Interactive)
{
   tp_Nod Nod;

   *AbortPtr = FALSE;
   switch (Nod_NodTyp(Root)) {
      case NULLCD: {
	 break;}/*case*/;
      case CMANDS: {
	 for (Nod=Nod_FirstSon(Root); Nod!=NIL; Nod=Nod_Brother(Nod)) {
	    Do_Command(AbortPtr, Nod, Interactive);
	    if (Signalled) {
	       return; }/*if*/; }/*for*/;
	 break;}/*case*/;
      case EXECUT: {
	 Do_Execute(AbortPtr, Root, Interactive);
	 break;}/*case*/;
      case DRVFIL: {
	 Do_ShowStatus(AbortPtr, Root);
	 break;}/*case*/;
      case DISPLY: {
	 Display(AbortPtr, Root);
	 break;}/*case*/;
      case COPYTR: {
	 Copy(AbortPtr, Nod_Son(1, Root), Nod_Son(2, Root));
	 break;}/*case*/;
      case EDIT: {
	 Edit(AbortPtr, Root, Interactive);
	 break;}/*case*/;
      case COPYTL: {
	 Copy(AbortPtr, Nod_Son(2, Root), Nod_Son(1, Root));
	 break;}/*case*/;
      case UTILTY: {
	 Utility(AbortPtr, Root);
	 break;}/*case*/;
      case VARVAL: {
	 ShowVar(Root);
	 break;}/*case*/;
      case VARSET: {
	 Do_SetVar(AbortPtr, Root);
	 break;}/*case*/;
      default: {
	 SystemError("Illegal command type.\n"); };}/*switch*/;
   }/*Do_Command*/


void
CommandInterpreter(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Nod, Root),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Nod, Root)
   GMC_DCL(boolean, Interactive)
{
   tp_Nod Nod;
   boolean IsHelp, IsHandled;

   FORBIDDEN(Root == ERROR);

   Do_Help(AbortPtr, &IsHelp, &IsHandled, Root);
   if (*AbortPtr) {
      return; }/*if*/;

   if (IsHelp) {
      if (!IsHandled) {
	 Nod = OC_Parser(".:odin_help!", (tp_FileName)NIL, (int *)NIL);
	 FORBIDDEN(Nod == ERROR);
	 CommandInterpreter(AbortPtr, Nod, Interactive);
	 Ret_Nod(Nod); }/*if*/;
      return; }/*if*/;
   Nod = Root;
   if (CommandNesting > MaxCommandNesting) {
      SystemError("Maximum CommandNesting (%d) exceeded.\n",
		  MaxCommandNesting);
      *AbortPtr = TRUE;
      return; }/*if*/;
   CommandNesting += 1;
   Do_Command(AbortPtr, Nod, Interactive);
   CommandNesting -= 1;
   }/*CommandInterpreter*/


