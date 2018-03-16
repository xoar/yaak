/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"
#include "inc/FileName.h"
#include "inc/FilElm.h"
#include "inc/FilHdr.h"
#include "inc/FilInp.h"
#include "inc/FKind_.h"
#include "inc/HdrInf.h"
#include "inc/LogLevel_.h"
#include "inc/ModKind_.h"
#include "inc/NodTyp_.h"
#include "inc/Outputs.h"
#include "inc/Status_.h"
#include "inc/Str.h"


extern int	num_FHLstS;
extern int	num_DrvPthS;
extern int	num_DrvSpcS;
extern int	num_StrS;
extern int	num_FilHdrS;
extern int	num_FilElmS;
extern int	num_FilInpS;
extern int	num_FilPrmS;
extern int	num_FilPValS;
extern int	num_PosS;
extern int	num_NodS;
extern int	num_StackElmS;
extern int	num_PrmFHdrS;

boolean			DebugLocElm = FALSE;

static tp_FilDsc	DebugFD = NIL;


static void
Local_Redo1(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr TmpFilHdr;

   if (FilHdr == ERROR) {
      return; }/*if*/;

   TmpFilHdr = Copy_FilHdr(FilHdr);
   if (IsInstance(TmpFilHdr)) {
      TmpFilHdr = FilHdr_Father(TmpFilHdr); }/*if*/;
   if (IsKeyListElm(TmpFilHdr)) {
      TmpFilHdr = FilHdr_Father(TmpFilHdr); }/*if*/;
   if (IsStructMem(TmpFilHdr)) {
      TmpFilHdr = FilHdr_Father(TmpFilHdr); }/*if*/;
   Clr_Status(TmpFilHdr);
   Clr_ConfirmDate(TmpFilHdr);
   Broadcast(TmpFilHdr, STAT_Unknown);
   if (IsPntr(TmpFilHdr)) {
      TmpFilHdr = FilHdr_ElmFilHdr(TmpFilHdr);
      if (FilHdr_Status(TmpFilHdr) != STAT_Unknown
	  || FilHdr_ConfirmDate(TmpFilHdr) != 0) {
	 Local_Redo1(TmpFilHdr); }/*if*/; }/*if*/;
   Ret_FilHdr(TmpFilHdr);
   }/*Local_Redo1*/


void
Local_Redo(
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(tp_Str, OdinExpr)
{
   tp_FilHdr FilHdr;

   FilHdr = OdinExpr_FilHdr(OdinExpr);
   Local_Redo1(FilHdr);
   Ret_FilHdr(FilHdr);
   }/*Local_Redo*/


void
Local_OdinExpr_ID(
   GMC_ARG(int*, IDPtr),
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(int*, IDPtr)
   GMC_DCL(tp_Str, OdinExpr)
{
   tp_FilHdr FilHdr;

   FilHdr = OdinExpr_FilHdr(OdinExpr);
   if (FilHdr == ERROR) {
      *IDPtr = 0;
      return; }/*if*/;
   *IDPtr = (int)FilHdr_LocHdr(FilHdr);
   Ret_FilHdr(FilHdr);
   }/*Local_OdinExpr_ID*/


void
Local_ID_OdinExpr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr((tp_LocHdr)ID);
   if (FilHdr == ERROR) {
      (void)strcpy(OdinExpr, "");
      return; }/*if*/;
   SPrint_FilHdr(OdinExpr, FilHdr);
   Ret_FilHdr(FilHdr);
   }/*Local_ID_OdinExpr*/


void
Local_ID_LongOdinExpr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr((tp_LocHdr)ID);
   if (FilHdr == ERROR) {
      (void)strcpy(OdinExpr, "");
      return; }/*if*/;
   VerboseSPrint_FilHdr(OdinExpr, FilHdr);
   Ret_FilHdr(FilHdr);
   }/*Local_ID_LongOdinExpr*/


void
Do_Log(
   GMC_ARG(tp_Str, Message),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_LogLevel, LogLevel)
   )
   GMC_DCL(tp_Str, Message)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_LogLevel, LogLevel)
{
   tps_Str StrBuf;

   if (Client_LogLevel(CurrentClient) < LogLevel) {
      return; }/*if*/;
   (void)sprintf(StrBuf, "** %s ", Message);
   SPrint_FilHdr(Tail(StrBuf), FilHdr);
   LogMessage(StrBuf);
   }/*Do_Log*/


tp_FilHdr
OdinExpr_FilHdr(
   GMC_ARG(const char*, OdinExpr)
   )
   GMC_DCL(char*, OdinExpr)
{
   tp_Nod DS_Nod;
   tp_PrmFHdr PrmFHdr;
   tp_FilHdr FilHdr;
   tp_FilPrm FilPrm;

   DS_Nod = YY_Parser(OdinExpr, (tp_FileName)NIL, (int *)NIL);
   PrmFHdr = Nod_PrmFHdr(DS_Nod);
   Ret_Nod(DS_Nod);
   Use_PrmFHdr(&FilHdr, &FilPrm, PrmFHdr);
   return FilHdr;
   }/*OdinExpr_FilHdr*/


void
WritePrmOdinExpr(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   Print_FilHdr(FilDsc, (tp_Str)NIL, FilHdr);
   Print_FilPrm(FilDsc, (tp_Str)NIL, FilPrm);
   Writeln(FilDsc, "");
   }/*WritePrmOdinExpr*/


void
Local_Set_Debug(
   GMC_ARG(tp_Str, DebugName)
   )
   GMC_DCL(tp_Str, DebugName)
{
   tps_FileName DebugFileName;

   /*select*/{
      if (strcasecmp(DebugName, "sizes") == 0) {
	 SystemError("num_CWDFilHdrS = %d\n", num_FHLstS);
	 SystemError("num_DrvPthS = %d\n", num_DrvPthS);
	 SystemError("num_DrvSpcS = %d\n", num_DrvSpcS);
	 SystemError("num_StrS = %d\n", num_StrS);
	 SystemError("num_FilHdrS = %d\n", num_FilHdrS);
	 SystemError("num_FilElmS = %d\n", num_FilElmS);
	 SystemError("num_FilInpS = %d\n", num_FilInpS);
	 SystemError("num_FilPrmS = %d\n", num_FilPrmS);
	 SystemError("num_FilPValS = %d\n", num_FilPValS);
	 SystemError("num_PosS = %d\n", num_PosS);
	 SystemError("num_NodS = %d\n", num_NodS);
	 SystemError("num_StackElmS = %d\n", num_StackElmS);
	 SystemError("num_PrmFHdrS = %d\n", num_PrmFHdrS);
      }else if (strcasecmp(DebugName, "symbols") == 0) {
	 Write_Syms(StdOutFD);
      }else if (strcasecmp(DebugName, "locelm") == 0) {
	 if (DebugFD == NIL) {
	    Get_DebugFileName(DebugFileName);
	    DebugFD = FileName_AFilDsc(DebugFileName, FALSE); }/*if*/;
	 DebugLocElm = TRUE;
      }else{
	 SystemError("** Unknown debug request.\n"); };}/*select*/;
   }/*Local_Set_Debug*/


void
Local_Get_Status(
   GMC_ARG(tp_Status*, StatusPtr),
   GMC_ARG(tp_Status*, ElmStatusPtr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Status*, StatusPtr)
   GMC_DCL(tp_Status*, ElmStatusPtr)
   GMC_DCL(int, ID)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr((tp_LocHdr)ID);
   if (FilHdr == ERROR) {
      *StatusPtr = STAT_Error;
      *ElmStatusPtr = STAT_Error;
      return; }/*if*/;
   *StatusPtr = FilHdr_TgtValMinStatus(FilHdr);
   *ElmStatusPtr = FilHdr_ElmStatus(FilHdr);
   Ret_FilHdr(FilHdr);
   }/*Local_Get_Status*/


static void
Print_ElmLink(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;
   tp_LocElm LocElmLink, FirstElmLink, NxtLocElmLink;
   tp_FilElm FilElmLink;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   LocElmLink = FilHdr_ElmLink(FilHdr);
   FirstElmLink = LocElmLink;
   NxtLocElmLink = NIL;
   while (NxtLocElmLink != FirstElmLink) {
      FilElmLink = LocElm_FilElm(LocElmLink);
      Print_OdinExpr(FilElm_ListLocHdr(FilElmLink), RootFilPrm);
      FORBIDDEN(FilElmLink->ElmInf.LocHdr != LocHdr);
      NxtLocElmLink = FilElm_Link(FilElmLink);
      Ret_FilElm(FilElmLink);
      LocElmLink = NxtLocElmLink; }/*while*/;
   Ret_FilHdr(FilHdr);
   }/*Print_ElmLink*/


static void
Print_LocElm(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr, TgtValFilHdr;
   tp_FilElm FilElm;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   TgtValFilHdr = FilHdr_TgtValFilHdr(Copy_FilHdr(FilHdr));
   if (TgtValFilHdr != NIL) {
      FORBIDDEN(!IsSource(FilHdr));
      Print_OdinExpr(TgtValFilHdr->LocHdr, RootFilPrm);
      Ret_FilHdr(TgtValFilHdr); }/*if*/;
   if (!(IsRef(FilHdr) || IsSymLink(FilHdr))) {
      SystemError("** Not a list or pointer file.\n");
      Ret_FilHdr(FilHdr);
      return; }/*if*/;
   if (!IsUpToDate(FilHdr)) {
      SystemError("** Warning: element list is not up-to-date.\n"); }/*if*/;
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      FORBIDDEN(FilElm_ListLocHdr(FilElm) != LocHdr);
      Print_OdinExpr(FilElm->ElmInf.LocHdr, FilElm_FilPrm(FilElm)); }/*for*/;
   Ret_FilHdr(FilHdr);
   }/*Print_LocElm*/


static void
Print_InpLink(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;
   tp_LocInp LocInpLink, FirstInpLink, NxtLocInpLink;
   tp_FilInp FilInpLink;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   LocInpLink = FilHdr_InpLink(FilHdr);
   FirstInpLink = LocInpLink;
   NxtLocInpLink = NIL;
   while (NxtLocInpLink != FirstInpLink) {
      FilInpLink = LocInp_FilInp(LocInpLink);
      Print_OdinExpr(FilInp_OutLocHdr(FilInpLink), RootFilPrm);
      FORBIDDEN(FilInpLink->InpInf.LocHdr != LocHdr);
      NxtLocInpLink = FilInp_Link(FilInpLink);
      Ret_FilInp(FilInpLink);
      LocInpLink = NxtLocInpLink; }/*while*/;
   Ret_FilHdr(FilHdr);
   }/*Print_InpLink*/


static void
Print_LocInp(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;
   tp_FilInp FilInp;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   for (FilInp = LocInp_FilInp(FilHdr_LocInp(FilHdr));
	FilInp != NIL;
	FilInp = FilInp_NextFilInp(FilInp)) {
      Print_OdinExpr(FilInp->InpInf.LocHdr, RootFilPrm);
      FORBIDDEN(FilInp_OutLocHdr(FilInp) != LocHdr); }/*for*/;
   Ret_FilHdr(FilHdr);
   }/*Print_LocInp*/


void
Local_Get_Elements(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   if (ID <= 0) {
      SystemError("Bad object reference.\n");
      return; }/*if*/;
   Print_LocElm((tp_LocHdr)ID);
   }/*Local_Get_Elements*/


void
Local_Get_ElementsOf(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   if (ID <= 0) {
      SystemError("Bad object reference.\n");
      return; }/*if*/;
   Print_ElmLink((tp_LocHdr)ID);
   }/*Local_Get_ElementsOf*/


void
Local_Get_Inputs(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   if (ID <= 0) {
      SystemError("Bad object reference.\n");
      return; }/*if*/;
   Print_LocInp((tp_LocHdr)ID);
   }/*Local_Get_Inputs*/


void
Local_Get_Outputs(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   if (ID <= 0) {
      SystemError("Bad object reference.\n");
      return; }/*if*/;
   Print_InpLink((tp_LocHdr)ID);
   }/*Local_Get_Outputs*/


void
Debug_Alloc_ElmInf(
   GMC_ARG(tp_LocElm, LocElm),
   GMC_ARG(tp_LocElm, FreeLocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
   GMC_DCL(tp_LocElm, FreeLocElm)
{
   Unwind(DebugFD);
   WriteInt(DebugFD, (int)LocElm);
   Write(DebugFD, " re-allocated, new Free = ");
   WriteInt(DebugFD, (int)FreeLocElm);
   Writeln(DebugFD, "");
   Flush(DebugFD);
   }/*Debug_Alloc_ElmInf*/


void
Debug_Ret_ElmInf(
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_LocElm, LocElm)
{
   Unwind(DebugFD);
   WriteInt(DebugFD, (int)LocElm);
   Write(DebugFD, " de-allocated");
   Writeln(DebugFD, "");
   Flush(DebugFD);
   }/*Debug_Ret_ElmInf*/


void
Validate_LocElm(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_LocElm, LocElm)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_LocElm, LocElm)
{
   tp_LocHdr LocHdr;
   tp_FilElm FilElm;

   LocHdr = FilHdr_LocHdr(FilHdr);
   for (FilElm = LocElm_FilElm(LocElm);
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      FORBIDDEN(FilElm_ListLocHdr(FilElm) != LocHdr); }/*for*/;
   }/*Validate_LocElm*/


void
Print_OdinExpr(
   GMC_ARG(tp_LocHdr, LocHdr),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   tp_FilHdr FilHdr;
   tps_Str OdinExpr;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      (void)strcpy(OdinExpr, "");
      return; }/*if*/;
   SPrint_FilHdr(OdinExpr, FilHdr);
   if (FilPrm != RootFilPrm)  {
      Print_FilPrm((tp_FilDsc)NIL, Tail(OdinExpr), FilPrm); }/*if*/;
   Next_OdinFile(OdinExpr, (int)LocHdr);
   Ret_FilHdr(FilHdr);
   }/*Print_OdinExpr*/


/*for debugging*/
void
printte(
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr(LocHdr);
   if (FilHdr == ERROR) {
      return; }/*if*/;
   WriteInt(StdOutFD, (int)LocHdr);
   Write(StdOutFD, "\t- ");
   Print_FilHdr(StdOutFD, (tp_Str)NIL, FilHdr);
   Writeln(StdOutFD, "");
   Ret_FilHdr(FilHdr);
   }/*printte*/


