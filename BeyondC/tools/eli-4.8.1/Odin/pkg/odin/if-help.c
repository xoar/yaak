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
#include "inc/OC_NodTyp_.h"
#include "inc/Str.h"


static tp_Str
Get_DrvOprName(
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(tp_Nod, Root)
{
   tp_Nod Brother;

   for (Brother = Root; Brother != NIL; Brother = Nod_Brother(Brother)) {
      if (Nod_NodTyp(Brother) == DRVOPR
	  && Nod_NodTyp(Nod_Son(1, Brother)) == WORD) {
	 return Sym_Str(Nod_Sym(Nod_Son(1, Brother))); }/*if*/; }/*for*/;
   return (tp_Str)NIL;
   }/*Get_DrvOprName*/


void
Do_Help(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(boolean*, IsHelpPtr),
   GMC_ARG(boolean*, IsHandledPtr),
   GMC_ARG(tp_Nod, Root)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(boolean*, IsHelpPtr)
   GMC_DCL(boolean*, IsHandledPtr)
   GMC_DCL(tp_Nod, Root)
{
   tp_Str DrvOprName;
   tps_Str StrBuf;
   tp_Nod Son;

   *AbortPtr = FALSE;
   *IsHelpPtr = FALSE;
   *IsHandledPtr = FALSE;
   if (Root == NIL) {
      return; }/*if*/;
   switch (Nod_NodTyp(Root)) {
      case HELP: {
	 *IsHelpPtr = TRUE; break; }/*case*/;
      case PFHELP: {
	 *IsHelpPtr = TRUE;
	 *IsHandledPtr = TRUE;
	 TopLevelCI(AbortPtr, "() :prefix_help>");
	 break; }/*case*/;
      case SFHELP: {
	 *IsHelpPtr = TRUE;
	 *IsHandledPtr = TRUE;
	 TopLevelCI(AbortPtr, "() :suffix_help>");
	 break; }/*case*/;
      case EPHELP: {
	 *IsHelpPtr = TRUE;
	 *IsHandledPtr = TRUE;
	 Writeln(StdOutFD, "?*? An arbitrary string of characters.");
	 Writeln(StdOutFD, "?*? ( an initial special character must be escaped with a \\ )"); break; }/*case*/;
      case STRING: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Write(StdOutFD, "?*? An arbitrary string of characters");
	       Writeln(StdOutFD, " (special characters must be escaped).");
	       }/*if*/; }/*if*/; break; }/*case*/;
      case WORD: case HOSTWD: case NULLCD: case DIROPR: case EMPFIL:
      case ARTFIL: case OBJTID: {
	 break; }/*case*/;
      case CMANDS: {
	 for (Son=Nod_FirstSon(Root); Son!=NIL; Son=Nod_Brother(Son)) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Son);
	    if (*IsHelpPtr) {
	       return; }/*if*/; }/*for*/; break; }/*case*/;
      case DRVFIL: {
	 Son = Nod_Son(1, Root);
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Son);
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr && Nod_NumSons(Root) > 1) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD, "*?* An Odin expression."); }/*if*/;
	    return; }/*if*/;
	 for (Son = Nod_Brother(Son); Son != NIL; Son = Nod_Brother(Son)) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Son);
	    if (*IsHelpPtr) {
	       if (!*IsHandledPtr) {
		  *IsHandledPtr = TRUE;
		  OC_Unparse(StrBuf, Root);
		  /*select*/{
		     if (Nod_NodTyp(Son) == DRVOPR) {
			(void)strcat(StrBuf, " :drv_help>");
			TopLevelCI(AbortPtr, StrBuf);
		     }else{
			DrvOprName = Get_DrvOprName(Nod_Brother(Son));
			if (DrvOprName != NIL) {
			   (void)strcat(StrBuf, " +prm_help=");
			   Unlex(Tail(StrBuf), DrvOprName); }/*if*/;
			(void)strcat(StrBuf, ":prm_help>");
			TopLevelCI(AbortPtr, StrBuf);
			};}/*select*/;
		     return; }/*if*/;
	       return; }/*if*/; }/*for*/; break; }/*case*/;
      case COPYTR: case COPYTL: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD, "*?* An Odin expression."); }/*if*/;
	    return; }/*if*/;
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An Odin expression or can be left blank.");
	    }/*if*/; break; }/*case*/;
      case DISPLY: case EDIT: case EXECUT: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An Odin expression.");
	    return; }/*if*/;
	 if (Nod_NumSons(Root) > 1) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	    }/*if*/; break; }/*case*/;
      case UTILTY: {
	 if (Nod_NumSons(Root) == 1) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	    if (*IsHelpPtr && !*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       UtilityDefaultHelp(); }/*if*/;
	    return; }/*if*/;
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD, "*?* An Odin expression."); }/*if*/;
	    return; }/*if*/;
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    UtilityHelp(); }/*if*/; break; }/*case*/;
      case VARVAL: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    ShowVars(); }/*if*/; break; }/*case*/;
      case VARSET: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       ShowVars(); }/*if*/;
	    return; }/*if*/;
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    HelpVar(Root); }/*if*/; break; }/*case*/;
      case SEGOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* A virtual name.");
	    }/*if*/; break; }/*case*/;
      case ABSFIL: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* A file in the root directory.");
	    }/*if*/; break; }/*case*/;
      case PRMOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    return; }/*if*/;
	 if (Nod_NumSons(Root) > 1) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	    if (*IsHelpPtr && !*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD, "*?* A sequence of parameter values.");
	       return; }/*if*/; }/*for*/; break; }/*case*/;
      case APLOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An Odin expression.");
	    return; }/*if*/; break; }/*case*/;
      case PRMVLS: {
	 for (Son=Nod_Son(1, Root); Son!=NIL; Son=Nod_Brother(Son)) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Son);
	    if (*IsHelpPtr && !*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD,
		"*?* A word or an Odin expression in parentheses.");
	       return; }/*if*/; }/*for*/; break; }/*case*/;
      case DRVOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root)); break; }/*case*/;
      case HODOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr) {
	    if (!*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Write(StdOutFD, "*?* \"lookup\", \"map\", \"recurse\", ");
	       Writeln(StdOutFD, "\"extract\", or \"delete\"."); }/*if*/;
	    return; }/*if*/;
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(2, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An Odin derivation type.");
	    }/*if*/; break; }/*case*/;
      case ELMOPR: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An element of the directory.");
	    }/*if*/; break; }/*case*/;
      case OPRTNS: {
	 for (Son=Nod_Son(1, Root); Son!=NIL; Son=Nod_Brother(Son)) {
	    Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Son);
	    if (*IsHelpPtr && !*IsHandledPtr) {
	       *IsHandledPtr = TRUE;
	       Writeln(StdOutFD, "*?* An Odin operation.");
	       return; }/*if*/; }/*for*/; break; }/*case*/;
      case PVLFIL: {
	 Do_Help(AbortPtr, IsHelpPtr, IsHandledPtr, Nod_Son(1, Root));
	 if (*IsHelpPtr && !*IsHandledPtr) {
	    *IsHandledPtr = TRUE;
	    Writeln(StdOutFD, "*?* An Odin expression.");
	    }/*if*/; break; }/*case*/;
      default: {
	 FATALERROR("Unexpected NodTyp"); };}/*switch*/;
   }/*Do_Help*/


void
Local_Next_OdinFile(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   WriteInt(StdOutFD, ID);
   Write(StdOutFD, "\t- ");
   WriteLine(StdOutFD, OdinExpr);
   }/*Local_Next_OdinFile*/

