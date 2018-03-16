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
#include "inc/Str.h"
#include "inc/DPType_.h"


static void
Find_HookClose(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FilDsc, OutFD),
   GMC_ARG(tp_FilDsc, InFD)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FilDsc, OutFD)
   GMC_DCL(tp_FilDsc, InFD)
{
   int i;

   while (!EndOfFile(InFD)) {
      i = Readch(InFD);
      ;/*select*/{
	 if ((char)i == '(') {
	    if (OutFD != NIL) Writech(OutFD, (char)i);
	    i = Readch(InFD);
	    if (OutFD != NIL) Writech(OutFD, (char)i);
	    if ((char)i == '|') {
	       Find_HookClose(AbortPtr, OutFD, InFD);
	       if (OutFD != NIL) Write(OutFD, "|)");
	       if (*AbortPtr) {
		  return; }/*if*/; }/*if*/;
	 }else if ((char)i == '|') {
	    i = Readch(InFD);
	    if ((char)i == ')') {
	       *AbortPtr = FALSE;
	       return; }/*if*/;
	    if (OutFD != NIL) {
	       Writech(OutFD, '|'); Writech(OutFD, (char)i); }/*if*/;
	 }else if ((char)i == '\\') {
	    if (OutFD != NIL) Writech(OutFD, (char)i);
	    i = Readch(InFD);
	    if (OutFD != NIL) Writech(OutFD, (char)i);
	 }else{
	    if (OutFD != NIL) Writech(OutFD, (char)i);
	    };}/*select*/; }/*while*/;
   *AbortPtr = TRUE;
   }/*Find_HookClose*/


static tp_DrvPth
Get_HookDrvPth(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilTyp, FilTyp)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilTyp, FilTyp)
{
   tp_DrvPth DrvPth, TmpDP;
   boolean HasDrv;

   HasDrv = FALSE;
   DrvPth = Get_DrvPth(FilHdr, FilTyp);
   for (TmpDP = DrvPth; TmpDP != ERROR; TmpDP = DrvPth_Next(TmpDP)) {
      switch (DrvPth_DPType(TmpDP)) {
	 case DPT_Cast: {
	    Ret_DrvPth(DrvPth);
	    return ERROR;
	    break; }/*case*/;
	 case DPT_Eqv: {
	    break; }/*case*/;
	 case DPT_Drv: {
	    if (HasDrv) {
	       Ret_DrvPth(DrvPth);
	       return ERROR; }/*if*/;
	    HasDrv = TRUE;
	    break; }/*case*/;
	 default: {
	    FATALERROR("Unknown DPType"); };}/*switch*/; }/*for*/;
   return DrvPth;
   }/*Get_HookDrvPth*/


static void
Get_Hook(
   GMC_ARG(tp_FilHdr*, FilHdrPtr),
   GMC_ARG(tp_FilDsc, OutFD),
   GMC_ARG(tp_FilHdr, HookValsFilHdr),
   GMC_ARG(tp_FilDsc, InFD),
   GMC_ARG(tp_FilPrm, FilPrm),
   GMC_ARG(int, HookNum)
   )
   GMC_DCL(tp_FilHdr*, FilHdrPtr)
   GMC_DCL(tp_FilDsc, OutFD)
   GMC_DCL(tp_FilHdr, HookValsFilHdr)
   GMC_DCL(tp_FilDsc, InFD)
   GMC_DCL(tp_FilPrm, FilPrm)
   GMC_DCL(int, HookNum)
{
   int i, iStr;
   tps_Str StrBuf;
   tp_Str HookNumStr;
   tp_FilHdr FilHdr, HookValFilHdr;
   tp_FilTyp HookFilTyp;
   tp_DrvPth DrvPth;
   tp_FilPrm HookFilPrm;
   boolean Abort;

   *FilHdrPtr = ERROR;
   i = Readch(InFD);
   iStr = 0;
   while ((char)i != '|' && !EndOfFile(InFD)) {
      StrBuf[iStr] = (char)i;
      iStr += 1;
      i = Readch(InFD); }/*while*/;
   StrBuf[iStr] = 0;
   FilHdr = DataFileName_FilHdr(StrBuf);
   if (FilHdr == ERROR) {
      SystemError("Bad Hook FileName : <%s>.\n", StrBuf);
      return; }/*if*/;

   i = Readch(InFD);
   iStr = 0;
   while ((char)i != '|' && !EndOfFile(InFD)) {
      StrBuf[iStr] = (char)i;
      iStr += 1;
      i = Readch(InFD); }/*while*/;
   StrBuf[iStr] = 0;
   if (EndOfFile(InFD)) {
      SystemError("** Error: Hook terminated by EOF\n");
      Ret_FilHdr(FilHdr);
      return; }/*if*/;
   HookFilTyp = FTName_FilTyp(StrBuf);
   if (HookFilTyp == ERROR) {
      SystemError("Bad Hook Type : <%s>.\n", StrBuf);
      Ret_FilHdr(FilHdr);
      return; }/*if*/;

   (void)sprintf(StrBuf, "%d", HookNum);
   HookNumStr = StrBuf;
   Write(OutFD, "%"); Write(OutFD, HookNumStr);
   Writeln(OutFD, " == << \\\\\n|HOOK-VALUE-TAG|");
   Find_HookClose(&Abort, OutFD, InFD);
   Writeln(OutFD, "\n|HOOK-VALUE-TAG|\n");
   if (Abort) {
      SystemError("** Error: Hook terminated by EOF\n");
      Ret_FilHdr(FilHdr);
      return; }/*if*/;

   HookValFilHdr = Do_VTgt(Copy_FilHdr(HookValsFilHdr), HookNumStr);
   HookFilPrm = Append_PrmInf(FilPrm, HookValPrmTyp,
			      FilHdr_LocHdr(HookValFilHdr), (tp_LocPVal)NIL);
   DrvPth = Get_HookDrvPth(FilHdr, HookFilTyp);
   while (DrvPth == ERROR && !IsSource(FilHdr)) {
      HookFilPrm = Append_FilPrm(FilHdr_FilPrm(FilHdr), HookFilPrm);
      FilHdr = FilHdr_Father(FilHdr);
      DrvPth = Get_HookDrvPth(FilHdr, HookFilTyp); }/*while*/;
   /*select*/{
      if (DrvPth == ERROR) {
	 Ret_FilHdr(FilHdr);
	 FilHdr = Copy_FilHdr(HookValFilHdr);
      }else{
	 FilHdr = Do_DrvPth(FilHdr, HookFilPrm, RootFilPrm, DrvPth);
	 Ret_DrvPth(DrvPth); };}/*select*/;
   Ret_FilHdr(HookValFilHdr);
   FilHdr = Do_Deriv(FilHdr, HookFilPrm, RootFilPrm, ExpandHooksFilTyp);
   FORBIDDEN(FilHdr == ERROR);
   *FilHdrPtr = FilHdr;
   }/*Get_Hook*/


void
NestedHooks(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilHdr, HookValsFilHdr),
   GMC_ARG(tp_FilDsc, OutFD),
   GMC_ARG(tp_FilDsc, InFD),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilHdr, HookValsFilHdr)
   GMC_DCL(tp_FilDsc, OutFD)
   GMC_DCL(tp_FilDsc, InFD)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   int i, HookNum;
   tp_LocElm FirstLE, LastLE, LocElm;
   tp_FilHdr ElmFilHdr;

   HookNum = 0;
   i = Readch(InFD);
   FirstLE = NIL; LastLE = NIL;
   while (!EndOfFile(InFD)) {
      ;/*select*/{
	 if ((char)i == '(') {
	    i = Readch(InFD);
	    if ((char)i == '|') {
	       HookNum += 1;
	       Get_Hook(&ElmFilHdr, OutFD, HookValsFilHdr,
			InFD, FilPrm, HookNum);
	       if (ElmFilHdr == ERROR) {
		  DeAlloc_ElmInf(FirstLE);
		  Set_LocElm(FilHdr, (tp_LocElm)NIL);
		  return; }/*if*/;
	       LocElm = Make_LocElm(ElmFilHdr, RootFilPrm, FilHdr);
	       Ret_FilHdr(ElmFilHdr);
	       Chain_LocElms(&FirstLE, &LastLE, LocElm);
	       i = Readch(InFD); }/*if*/;
	 }else if ((char)i == '\\') {
	    i = Readch(InFD);
	    if ((char)i == '(') {
	       i = Readch(InFD);
	       if ((char)i == '|') {
		  i = Readch(InFD); }/*if*/; }/*if*/;
	 }else{
	    i = Readch(InFD); };}/*select*/; }/*while*/;
   Set_LocElm(FilHdr, FirstLE);
   }/*NestedHooks*/


void
ExpandHooks(
   GMC_ARG(tp_FilDsc, OutFD),
   GMC_ARG(tp_FilDsc, InFD),
   GMC_ARG(tp_FilHdr, HooksFilHdr)
   )
   GMC_DCL(tp_FilDsc, OutFD)
   GMC_DCL(tp_FilDsc, InFD)
   GMC_DCL(tp_FilHdr, HooksFilHdr)
{
   int i;
   tp_LocElm LocElm;
   tp_FilElm FilElm;
   tps_FileName FileName;
   tp_FilHdr HookFilHdr;
   tp_FilDsc HookFD;
   boolean Abort;

   i = Readch(InFD);
   LocElm = FilHdr_LocElm(HooksFilHdr);
   while (!EndOfFile(InFD)) {
      ;/*select*/{
	 if ((char)i == '(') {
	    i = Readch(InFD);
	    ;/*select*/{
	       if ((char)i == '|') {
		  FORBIDDEN(LocElm == NIL);
		  FilElm = LocElm_FilElm(LocElm);
		  HookFilHdr = Deref(FilElm_FilHdr(FilElm));
		  LocElm = FilElm_Next(FilElm);
		  Ret_FilElm(FilElm);
		  FilHdr_DataFileName(FileName, HookFilHdr);
		  Ret_FilHdr(HookFilHdr);
		  HookFD = FileName_RFilDsc(FileName, TRUE);
		  FileCopy(OutFD, HookFD);
		  Close(HookFD);
		  Find_HookClose(&Abort, (tp_FilDsc)NIL, InFD);
		  FORBIDDEN(Abort);
		  i = Readch(InFD);
	       }else{
		  Writech(OutFD, '('); };}/*select*/;
	 }else if ((char)i == '\\') {
	    i = Readch(InFD);
	    ;/*select*/{
	       if ((char)i == '(') {
		  i = Readch(InFD);
		  ;/*select*/{
		     if ((char)i == '|') {
			Write(OutFD, "(|");
			i = Readch(InFD);
		     }else{
			Write(OutFD, "\\("); };}/*select*/;
	       }else{
		  Writech(OutFD, '\\'); };}/*select*/;
	 }else{
	    Writech(OutFD, (char)i);
	    i = Readch(InFD); };}/*select*/; }/*while*/;
   FORBIDDEN(LocElm != NIL);
   }/*ExpandHooks*/


