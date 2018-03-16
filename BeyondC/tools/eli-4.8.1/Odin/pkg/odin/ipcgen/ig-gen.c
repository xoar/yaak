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
#include "inc/NodTyp_.h"


Gen_InStub(FilDsc, Root)
   tp_FilDsc FilDsc;
   tp_Nod Root;
{
   tp_Nod StubNod, MsgNod;
   int MsgNum;
   boolean IsServer;

   Writeln(FilDsc, "#include \"inc/GMC.h\"");
   Writeln(FilDsc, "#include \"inc/Str.h\"\n");
   Writeln(FilDsc, "extern boolean IPC_Do_Return;");
   Writeln(FilDsc, "extern int *IPC_IArg1, *IPC_IArg2, *IPC_IArg3;");
   Writeln(FilDsc, "extern tp_Str IPC_SArg1, IPC_SArg2, IPC_SArg3;\n");
   FOREACH_SON(StubNod, Root) {
      Writeln(FilDsc, "");
      Get_MsgNod(&MsgNod, &IsServer, StubNod);
      Write_ServerIfDef(FilDsc, IsServer);
      /*select*/{
	 if (Nod_NodTyp(MsgNod) == NOD_splitrequest) {
	    Write_SplitInMsg(FilDsc, MsgNod);
	 }else{
	    Write_InMsg(FilDsc, MsgNod); };}/*select*/;
      Writeln(FilDsc, "#endif"); }/*for*/;

   Writeln(FilDsc, "void");
   Writeln(FilDsc, "IPC_Do_Msg(");
   Writeln(FilDsc, "   GMC_ARG(boolean*, IPC_AbortPtr),");
   Writeln(FilDsc, "   GMC_ARG(int, MsgType)");
   Writeln(FilDsc, "   )");
   Writeln(FilDsc, "   GMC_DCL(boolean*, IPC_AbortPtr)");
   Writeln(FilDsc, "   GMC_DCL(int, MsgType)");
   Writeln(FilDsc, "{");
   Writeln(FilDsc, "   switch (MsgType) {");
   Writeln(FilDsc, "      case 1: {");
   Writeln(FilDsc, "         IPC_Do_Return = TRUE;");
   Writeln(FilDsc, "         *IPC_AbortPtr = FALSE;");
   Writeln(FilDsc, "         break; }/*case*/;");
   MsgNum = 1;
   FOREACH_SON(StubNod, Root) {
      MsgNum += 1;
      Get_MsgNod(&MsgNod, &IsServer, StubNod);
      Write(FilDsc, "      case ");
      WriteInt(FilDsc, MsgNum);
      Writeln(FilDsc, ": {");
      Write_ServerIfDef(FilDsc, IsServer);
      Write(FilDsc, "         ");
      Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
      Writeln(FilDsc, "_Msg(IPC_AbortPtr);");
      Writeln(FilDsc, "#else");
      Writeln(FilDsc, "         *IPC_AbortPtr = TRUE;");
      Writeln(FilDsc, "#endif");
      Writeln(FilDsc, "         break; }/*case*/;"); }/*for*/;
   Writeln(FilDsc, "      default: {");
   Writeln(FilDsc, "         FATALERROR(\"Unexpected message type\"); };}/*switch*/;");
   Writeln(FilDsc, "   }/*IPC_Do_Msg*/");
   }/*Gen_InStub*/


Gen_OutStub(FilDsc, Root)
   tp_FilDsc FilDsc;
   tp_Nod Root;
{
   tp_Nod StubNod, MsgNod;
   int MsgNum;
   boolean IsServer;

   Writeln(FilDsc, "#include \"inc/GMC.h\"\n");
   Writeln(FilDsc, "extern boolean IPC_Do_Return;");
   Writeln(FilDsc, "extern int *IPC_IArg1, *IPC_IArg2, *IPC_IArg3;");
   Writeln(FilDsc, "extern tp_Str IPC_SArg1, IPC_SArg2, IPC_SArg3;");
   MsgNum = 1;
   FOREACH_SON(StubNod, Root) {
      Writeln(FilDsc, "");
      MsgNum += 1;
      Get_MsgNod(&MsgNod, &IsServer, StubNod);
      Write_ServerIfDef(FilDsc, !IsServer);
      Write_OutMsg(FilDsc, MsgNod, MsgNum, IsServer);
      Writeln(FilDsc, "#endif"); }/*for*/;
   }/*Gen_OutStub*/


Write_InMsg(FilDsc, MsgNod)
   tp_FilDsc FilDsc;
   tp_Nod MsgNod;
{
   tp_Nod ArgDclsNod, ArgDclNod;
   tp_NodTyp ArgKind;
   boolean IsFirst;

   Writeln(FilDsc, "static void");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Writeln(FilDsc, "_Msg(");
   Writeln(FilDsc, "   GMC_ARG(boolean*, IPC_AbortPtr)");
   Writeln(FilDsc, "   )");
   Writeln(FilDsc, "   GMC_DCL(boolean*, IPC_AbortPtr)");
   Writeln(FilDsc, "{");
   ArgDclsNod = Nod_Son(3, MsgNod);
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ;/*select*/{
	 if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	    Write(FilDsc, "   int ");
	 }else{
	    Write(FilDsc, "   tps_Str "); };}/*select*/;
      Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
      Writeln(FilDsc, ";"); }/*for*/;
   Writeln(FilDsc, "");

   Writeln(FilDsc, "   *IPC_AbortPtr = FALSE;");
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_in || ArgKind == NOD_inout) {
	 /*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "   IPC_Read_Int(IPC_AbortPtr, &");
	    }else{
	       Write(FilDsc, "   IPC_Read_Str(IPC_AbortPtr, "); };}/*select*/;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ");");
	 Writeln(FilDsc, "   if (*IPC_AbortPtr) return;");
	 }/*if*/; }/*for*/;

   Write(FilDsc, "   Local_");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Write(FilDsc, "(");
   IsFirst = TRUE;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      if (!IsFirst) Write(FilDsc, ", ");
      IsFirst = FALSE;
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	 if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	    Write(FilDsc, "&"); }/*if*/; }/*if*/;
      Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod)); }/*for*/;
   Writeln(FilDsc, ");");
   
   if (Nod_NodTyp(MsgNod) == NOD_request) {
      Writeln(FilDsc, "   IPC_Write_Int(IPC_AbortPtr, 1);");
      Writeln(FilDsc, "   if (*IPC_AbortPtr) return;");
      FOREACH_SON(ArgDclNod, ArgDclsNod) {
	 ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
	 if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	    /*select*/{
	       if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
		  Write(FilDsc, "   IPC_Write_Int(IPC_AbortPtr, ");
	       }else{
		  Write(FilDsc, "   IPC_Write_Str(IPC_AbortPtr, ");
		  };}/*select*/;
	    Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	    Writeln(FilDsc, ");");
	    Writeln(FilDsc, "   if (*IPC_AbortPtr) return;");
	    }/*if*/; }/*for*/; }/*if*/;
   Writeln(FilDsc, "}");
   }/*Write_InMsg*/


Write_SplitInMsg(FilDsc, MsgNod)
   tp_FilDsc FilDsc;
   tp_Nod MsgNod;
{
   tp_Nod ArgDclsNod, ArgDclNod, ArgTypeNod;
   tp_NodTyp ArgKind;
   boolean IsFirst;
   int i;

   Writeln(FilDsc, "static void");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Writeln(FilDsc, "_Msg(");
   Writeln(FilDsc, "   GMC_ARG(boolean*, IPC_AbortPtr)");
   Writeln(FilDsc, "   )");
   Writeln(FilDsc, "   GMC_DCL(boolean*, IPC_AbortPtr)");
   Writeln(FilDsc, "{");
   ArgDclsNod = Nod_Son(3, MsgNod);
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_in || ArgKind == NOD_inout) {
	 ;/*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "   int ");
	    }else{
	       Write(FilDsc, "   tps_Str "); };}/*select*/;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ";"); }/*if*/; }/*for*/;
   Writeln(FilDsc, "");

   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_in || ArgKind == NOD_inout) {
	 /*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "   IPC_Read_Int(IPC_AbortPtr, &");
	    }else{
	       Write(FilDsc, "   IPC_Read_Str(IPC_AbortPtr, "); };}/*select*/;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ");");
	 Writeln(FilDsc, "   if (*IPC_AbortPtr) return;");
	 }/*if*/; }/*for*/;

   Write(FilDsc, "   Local_");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Write(FilDsc, "(");
   IsFirst = TRUE;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_in || ArgKind == NOD_inout) {
	 if (!IsFirst) Write(FilDsc, ", ");
	 IsFirst = FALSE;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod)); }/*if*/; }/*for*/;
   Writeln(FilDsc, ");\n}\n");

   Writeln(FilDsc, "void");
   Write(FilDsc, "LocalEnd_");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Write(FilDsc, "(");

   IsFirst = TRUE;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	 if (!IsFirst) Write(FilDsc, ",");
	 IsFirst = FALSE;
	 Writeln(FilDsc, "");
	 Write(FilDsc, "   GMC_ARG(");
	 ArgTypeNod = Nod_Son(3, ArgDclNod);
	 /*select*/{
	    if (Nod_NodTyp(ArgTypeNod) == NOD_pointer) {
	       Write_NodSym(FilDsc, Nod_Son(1, ArgTypeNod));
	    }else{
	       Write_NodSym(FilDsc, ArgTypeNod); };}/*select*/;
	 Write(FilDsc, ", ");
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
         Write(FilDsc, ")"); }/*if*/; }/*for*/;
   /*select*/{
      if (IsFirst) {
	 Writeln(FilDsc, "GMC_ARG_VOID)");
      }else{
	 Writeln(FilDsc, "");
	 Writeln(FilDsc, "   )"); };}/*select*/;

   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	 Write(FilDsc, "   GMC_DCL(");
	 ArgTypeNod = Nod_Son(3, ArgDclNod);
	 /*select*/{
	    if (Nod_NodTyp(ArgTypeNod) == NOD_pointer) {
	       Write_NodSym(FilDsc, Nod_Son(1, ArgTypeNod));
	    }else{
	       Write_NodSym(FilDsc, ArgTypeNod); };}/*select*/;
	 Write(FilDsc, ", ");
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ")"); }/*if*/; }/*for*/;

   Writeln(FilDsc, "{");
   Writeln(FilDsc, "   boolean IPC_Abort;\n");

   Writeln(FilDsc, "   if (IsServer && Is_LocalClient(CurrentClient)) {");
   i = 0;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      i += 1;
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	 ;/*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "      *IPC_IArg");
	       WriteInt(FilDsc, i);
	       Write(FilDsc, " = ");
	       Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	       Writeln(FilDsc, ";");
	    }else{
	       Write(FilDsc, "      (void)strcpy(IPC_SArg");
	       WriteInt(FilDsc, i);
	       Write(FilDsc, ", ");
	       Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	       Writeln(FilDsc, ");"); };}/*select*/; }/*if*/; }/*for*/;
   Writeln(FilDsc, "      FORBIDDEN(IPC_Do_Return);\n");
   Writeln(FilDsc, "      IPC_Do_Return = TRUE;\n");
   Writeln(FilDsc, "      return; };\n");

   Writeln(FilDsc, "   IPC_Write_Int(&IPC_Abort, 1);");
   Writeln(FilDsc, "   if (IPC_Abort) IPC_Do_Abort();");
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	 /*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "   IPC_Write_Int(&IPC_Abort, ");
	    }else{
	       Write(FilDsc, "   IPC_Write_Str(&IPC_Abort, "); };}/*select*/;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ");");
	 Writeln(FilDsc, "   if (IPC_Abort) IPC_Do_Abort();");
	 }/*if*/; }/*for*/;
   Writeln(FilDsc, "}");
   }/*Write_SplitInMsg*/


Write_OutMsg(FilDsc, MsgNod, MsgNum, IsServer)
   tp_FilDsc FilDsc;
   tp_Nod MsgNod;
   int MsgNum;
   boolean IsServer;
{
   tp_Nod ArgDclsNod, ArgDclNod, ArgTypeNod;
   tp_NodTyp ArgKind;
   int i;
   boolean IsFirst;
   tp_Str ArgStr;

   Writeln(FilDsc, "void");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));

   ArgDclsNod = Nod_Son(3, MsgNod);

   Write(FilDsc, "(");
   IsFirst = TRUE;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      if (!IsFirst) Write(FilDsc, ",");
      IsFirst = FALSE;
      Writeln(FilDsc, "");
      Write(FilDsc, "   GMC_ARG(");
      ArgTypeNod = Nod_Son(3, ArgDclNod);
      /*select*/{
	 if (Nod_NodTyp(ArgTypeNod) == NOD_pointer) {
	    Write_NodSym(FilDsc, Nod_Son(1, ArgTypeNod));
	    Write(FilDsc, "*");
	 }else{
	    Write_NodSym(FilDsc, ArgTypeNod); };}/*select*/;
      Write(FilDsc, ", ");
      Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
      Write(FilDsc, ")"); }/*for*/;
   /*select*/{
      if (IsFirst) {
	 Writeln(FilDsc, "GMC_ARG_VOID)");
      }else{
	 Writeln(FilDsc, "");
	 Writeln(FilDsc, "   )"); };}/*select*/;

   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      Write(FilDsc, "   GMC_DCL(");
      ArgTypeNod = Nod_Son(3, ArgDclNod);
      /*select*/{
	 if (Nod_NodTyp(ArgTypeNod) == NOD_pointer) {
	    Write_NodSym(FilDsc, Nod_Son(1, ArgTypeNod));
	    Write(FilDsc, "*");
	 }else{
	    Write_NodSym(FilDsc, ArgTypeNod); };}/*select*/;
      Write(FilDsc, ", ");
      Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
      Writeln(FilDsc, ")"); }/*for*/;

   Writeln(FilDsc, "{");
   Writeln(FilDsc, "   boolean IPC_Abort;\n");
   if (Nod_NodTyp(MsgNod) == NOD_request
       || Nod_NodTyp(MsgNod) == NOD_splitrequest) {
      Writeln(FilDsc, "   boolean IPC_Cmd_Abort;\n"); }/*if*/;

   Write_ServerIfDef(FilDsc, IsServer);
   Writeln(FilDsc, "   if (IsServer && Is_LocalClient(CurrentClient)) {");
   if (Nod_NodTyp(MsgNod) == NOD_splitrequest) {
      Writeln(FilDsc, "      FORBIDDEN(IPC_Do_Return);");
      i = 0;
      FOREACH_SON(ArgDclNod, ArgDclsNod) {
	 i += 1;
	 ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
	 if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	    ArgStr = (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int
		      ? "IPC_IArg" : "IPC_SArg");
	    Write(FilDsc, "      FORBIDDEN(");
	    Write(FilDsc, ArgStr);
	    WriteInt(FilDsc, i);
	    Writeln(FilDsc, " != NIL);");

	    Write(FilDsc, "      ");
	    Write(FilDsc, ArgStr);
	    WriteInt(FilDsc, i);
	    Write(FilDsc, " = ");
	    Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	    Writeln(FilDsc, ";"); }/*if*/; }/*for*/; }/*if*/;

   Write(FilDsc, "      Local_");
   Write_NodSym(FilDsc, Nod_Son(1, MsgNod));
   Write(FilDsc, "(");
   IsFirst = TRUE;
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (!(Nod_NodTyp(MsgNod) == NOD_splitrequest && ArgKind == NOD_out)) {
	 if (!IsFirst) Write(FilDsc, ", ");
	 IsFirst = FALSE;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod)); }/*if*/; }/*for*/;
   Writeln(FilDsc, ");");

   if (Nod_NodTyp(MsgNod) == NOD_splitrequest) {
      Writeln(FilDsc, "      if (!IPC_Do_Return) {");
      Writeln(FilDsc, "         IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);");
      Writeln(FilDsc, "         FORBIDDEN(IPC_Cmd_Abort);");
      Writeln(FilDsc, "         FORBIDDEN(!IPC_Do_Return); }/*if*/;");
      Writeln(FilDsc, "      IPC_Do_Return = FALSE;");
      i = 0;
      FOREACH_SON(ArgDclNod, ArgDclsNod) {
	 i += 1;
	 ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
	 if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	    ArgStr = (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int
		      ? "IPC_IArg" : "IPC_SArg");
	    Write(FilDsc, "      ");
	    Write(FilDsc, ArgStr);
	    WriteInt(FilDsc, i);
	    Writeln(FilDsc, " = NIL;"); }/*if*/; }/*for*/; }/*if*/;
   Writeln(FilDsc, "   }else{");
   Writeln(FilDsc, "#endif");

   Write(FilDsc, "   IPC_Write_Int(&IPC_Abort, ");
   WriteInt(FilDsc, MsgNum);
   Writeln(FilDsc, ");");
   Writeln(FilDsc, "   if (IPC_Abort) IPC_Do_Abort();");
   FOREACH_SON(ArgDclNod, ArgDclsNod) {
      ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
      if (ArgKind == NOD_in || ArgKind == NOD_inout) {
	 /*select*/{
	    if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
	       Write(FilDsc, "   IPC_Write_Int(&IPC_Abort, ");
	       if (ArgKind == NOD_inout) Write(FilDsc, "*");
	    }else{
	       Write(FilDsc, "   IPC_Write_Str(&IPC_Abort, "); };}/*select*/;
	 Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	 Writeln(FilDsc, ");");
	 Writeln(FilDsc, "   if (IPC_Abort) IPC_Do_Abort();");
	 }/*if*/; }/*for*/;
   if (Nod_NodTyp(MsgNod) == NOD_request
       || Nod_NodTyp(MsgNod) == NOD_splitrequest) {
      Writeln(FilDsc, "   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);");
      Writeln(FilDsc, "   FORBIDDEN(IPC_Cmd_Abort);");
      Writeln(FilDsc, "   FORBIDDEN(!IPC_Do_Return);");
      Writeln(FilDsc, "   IPC_Do_Return = FALSE;");
      FOREACH_SON(ArgDclNod, ArgDclsNod) {
	 ArgKind = Nod_NodTyp(Nod_Son(1, ArgDclNod));
	 if (ArgKind == NOD_out || ArgKind == NOD_inout) {
	    /*select*/{
	       if (Nod_NodTyp(Nod_Son(2, ArgDclNod)) == NOD_int) {
		  Write(FilDsc, "   IPC_Read_Int(&IPC_Abort, ");
	       }else{
		  Write(FilDsc, "   IPC_Read_Str(&IPC_Abort, "); };}/*select*/;
	    Write_NodSym(FilDsc, Nod_Son(4, ArgDclNod));
	    Writeln(FilDsc, ");");
	    Writeln(FilDsc, "   if (IPC_Abort) IPC_Do_Abort();");
	    }/*if*/; }/*for*/; }/*if*/;

   Write_ServerIfDef(FilDsc, IsServer);
   Writeln(FilDsc, "   };");
   Writeln(FilDsc, "#endif");
   Writeln(FilDsc, "   }");
   }/*Write_OutMsg*/


Get_MsgNod(MsgNodPtr, IsServerPtr, StubNod)
   tp_Nod *MsgNodPtr;
   boolean *IsServerPtr;
   tp_Nod StubNod;
{
   switch (Nod_NodTyp(StubNod)) {
      case NOD_server: {
	 *IsServerPtr = TRUE;
	 break; }/*case*/;
      case NOD_client: {
	 *IsServerPtr = FALSE;
	 break; }/*case*/;
      default: {
	 FATALERROR("Unexpected Stub NodTyp"); };}/*switch*/;
   *MsgNodPtr = Nod_Son(1, StubNod);
   }/*Get_MsgNod*/


Write_ServerIfDef(FilDsc, IsServer)
   tp_FilDsc FilDsc;
   boolean IsServer;
{
   if (IsServer) {
      Writeln(FilDsc, "#ifndef CLIENT_ONLY");
      return; }/*if*/;
   Writeln(FilDsc, "#ifndef SERVER_ONLY");
   }/*Write_ServerIfDef*/


Write_Args(FilDsc, ArgsNod)
   tp_FilDsc FilDsc;
   tp_Nod ArgsNod;
{

   }/*Write_Args*/


Write_NodSym(FilDsc, Nod)
   tp_FilDsc FilDsc;
   tp_Nod Nod;
{
   Write(FilDsc, Sym_Str(Nod_Sym(Nod)));
   }/*Write_NodSym*/

