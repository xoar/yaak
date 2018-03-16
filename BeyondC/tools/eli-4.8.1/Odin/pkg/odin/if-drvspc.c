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
#include "inc/DPType_.h"
#include "inc/DrvSpc.h"
#include "inc/FKind_.h"
#include "inc/Str.h"


static tp_DrvSpc	FreeDrvSpc;
int		num_DrvSpcS;


static tp_DrvSpc
New_DrvSpc(GMC_ARG_VOID)
{
   tp_DrvSpc DrvSpc;

   /*select*/{
      if (FreeDrvSpc == NIL) {
	 DrvSpc = (tp_DrvSpc)malloc(sizeof(tps_DrvSpc));
	 num_DrvSpcS += 1;
	 DrvSpc->InUse = FALSE;
      }else{
	 DrvSpc = FreeDrvSpc;
	 FreeDrvSpc = FreeDrvSpc->Next; };}/*select*/;

   DrvSpc->FilPrm = NIL;
   DrvSpc->FilTyp = NIL;
   DrvSpc->Key = NIL;
   DrvSpc->FilHdr = NIL;
   DrvSpc->Next = NIL;
   FORBIDDEN(DrvSpc->InUse);
   DrvSpc->InUse = TRUE;
   return DrvSpc;
   }/*New_DrvSpc*/


static void
Ret_DrvSpc(
   GMC_ARG(tp_DrvSpc, DrvSpc)
   )
   GMC_DCL(tp_DrvSpc, DrvSpc)
{
   tp_DrvSpc DrvSpcElm, LastDrvSpc;

   if (DrvSpc == NIL) {
      return; }/*if*/;
   LastDrvSpc = DrvSpc;
   for (DrvSpcElm = DrvSpc; DrvSpcElm != NIL; DrvSpcElm = DrvSpcElm->Next) {
      FORBIDDEN(!DrvSpcElm->InUse);
      DrvSpcElm->InUse = FALSE;
      Ret_FilHdr(DrvSpcElm->FilHdr);
      LastDrvSpc = DrvSpcElm; }/*for*/;

   LastDrvSpc->Next = FreeDrvSpc;
   FreeDrvSpc = DrvSpc;
   }/*Ret_DrvSpc*/


static tp_DrvSpc
Last_DrvSpc(
   GMC_ARG(tp_DrvSpc, DrvSpc)
   )
   GMC_DCL(tp_DrvSpc, DrvSpc)
{
   tp_DrvSpc LastDrvSpc;

   FORBIDDEN(DrvSpc == ERROR);
   LastDrvSpc = DrvSpc;
   while (LastDrvSpc->Next != NIL) LastDrvSpc = LastDrvSpc->Next;
   return LastDrvSpc;
   }/*Last_DrvSpc*/


static void
ShiftLeft_DrvSpc(
   GMC_ARG(tp_DrvSpc, LeftDrvSpc),
   GMC_ARG(tp_DrvSpc*, RiteDrvSpcPtr)
   )
   GMC_DCL(tp_DrvSpc, LeftDrvSpc)
   GMC_DCL(tp_DrvSpc*, RiteDrvSpcPtr)
{
   tp_DrvSpc LastDrvSpc;

   FORBIDDEN(LeftDrvSpc == NIL || *RiteDrvSpcPtr == NIL);

   LastDrvSpc = Last_DrvSpc(LeftDrvSpc);
   LastDrvSpc->Next = *RiteDrvSpcPtr;

   *RiteDrvSpcPtr = (*RiteDrvSpcPtr)->Next;
   LastDrvSpc->Next->Next = NIL;
   }/*ShiftLeft_DrvSpc*/


static void
Print_DrvSpc(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_DrvSpc, DrvSpc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_DrvSpc, DrvSpc)
{
   tp_Str OprStr, Word;

   FORBIDDEN(((FilDsc == NIL) == (Str == NIL)) || DrvSpc == ERROR);
   
   if (Str != NIL) (void)strcpy(Str, "");

   if (DrvSpc->FilTyp == ApplyFilTyp) {
      return; }/*if*/;

   /*select*/{
      if (IsVTgt_FKind(DrvSpc->FKind) || IsVTgtText_FKind(DrvSpc->FKind)) {
	 OprStr = "%"; Word = DrvSpc->Key;
      }else if (HasKey_FKind(DrvSpc->FKind)) {
	 OprStr = "/"; Word = DrvSpc->Key;
      }else{
	 OprStr = " :"; Word = FilTyp_FTName(DrvSpc->FilTyp);
	 };}/*select*/;
   /*select*/{
      if (FilDsc != NIL) {
	 Write(FilDsc, OprStr);
	 Print_Unlex(FilDsc, Word);
      }else{
	 (void)strcat(Str, OprStr);
	 Unlex(Tail(Str), Word); };}/*select*/;

   if (IsSecOrd_FilTyp(DrvSpc->FilTyp)) {
      Word = FilTyp_FTName(FilTyp_ArgFilTyp(DrvSpc->FilTyp));
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, "=:");
	    Print_Unlex(FilDsc, Word);
	 }else{
	    (void)strcat(Str, "=:");
	    Unlex(Tail(Str), Word); };}/*select*/; }/*if*/;
   }/*Print_DrvSpc*/


static tp_DrvSpc
FilHdr_DrvSpc(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr TmpFilHdr;
   tp_DrvSpc DrvSpc, NewDrvSpc;
   tps_Str KeyBuf;

   FORBIDDEN(FilHdr == ERROR);

   DrvSpc = NIL;
   for (TmpFilHdr = Copy_FilHdr(FilHdr);
	!IsSource(TmpFilHdr);
	TmpFilHdr = FilHdr_Father(TmpFilHdr)) {
      if (!IsInstance(TmpFilHdr)) {
	 NewDrvSpc = New_DrvSpc();
	 NewDrvSpc->FKind = FilHdr_FKind(TmpFilHdr);
	 NewDrvSpc->FilTyp = FilHdr_FilTyp(TmpFilHdr);
	 NewDrvSpc->FilPrm = FilHdr_FilPrm(TmpFilHdr);
	 NewDrvSpc->Key = Sym_Str(Str_Sym(FilHdr_Key(KeyBuf, TmpFilHdr)));
	 NewDrvSpc->FilHdr = Copy_FilHdr(TmpFilHdr);
	 NewDrvSpc->Next = DrvSpc;
	 DrvSpc = NewDrvSpc; }/*if*/; }/*for*/;

   Ret_FilHdr(TmpFilHdr);
   return DrvSpc;
   }/*FilHdr_DrvSpc*/


static boolean
CheckCompact(
   GMC_ARG(tp_DrvSpc, DrvSpc),
   GMC_ARG(tp_DrvSpc, NextDrvSpc),
   GMC_ARG(tp_DrvPth, DrvPth),
   GMC_ARG(tp_FilPrm, FilPrm)
   )
   GMC_DCL(tp_DrvSpc, DrvSpc)
   GMC_DCL(tp_DrvSpc, NextDrvSpc)
   GMC_DCL(tp_DrvPth, DrvPth)
   GMC_DCL(tp_FilPrm, FilPrm)
{
   tp_DrvSpc DrvSpcElm;
   tp_DrvPth DrvPthElm, GroupingDrvPthElm;
   tp_PrmTypLst PrmTypLst;
   tp_FilPrm NewFilPrm;

   FORBIDDEN(DrvSpc==ERROR||NextDrvSpc==ERROR||DrvPth==ERROR||FilPrm==ERROR);
   DrvSpcElm = DrvSpc;
   GroupingDrvPthElm = Find_GroupingDrvPthElm(DrvPth);
   for (DrvPthElm = DrvPth;
	DrvPthElm != NIL;
	DrvPthElm = DrvPth_Next(DrvPthElm)) {
      if (DrvPth_DPType(DrvPthElm) == DPT_Drv) {
	 if (DrvSpcElm == NIL) {
	    DrvSpcElm = NextDrvSpc;
	    NextDrvSpc = NIL; }/*if*/;
	 FORBIDDEN(DrvSpcElm == NIL);
	 FORBIDDEN(DrvSpcElm->Key != NIL && NextDrvSpc != NIL);
	 if (DrvPth_FilTyp(DrvPthElm) != DrvSpcElm->FilTyp) {
	    return FALSE; }/*if*/;
	 if (DrvPth_FKind(DrvPthElm) != DrvSpcElm->FKind) {
	    return FALSE; }/*if*/;
	 PrmTypLst = DrvPth_PrmTypLst(DrvPthElm);
	 NewFilPrm = FilPrm;
	 /* if is Grouping, should strip inhfilprm, but don't know it here */
	 if (!(IsGroupingInput_FilTyp(DrvSpcElm->FilTyp)
	       || DrvPthElm == GroupingDrvPthElm)) {
	    NewFilPrm = Strip_FilPrm(FilPrm, PrmTypLst); }/*if*/;
	 if (!Equal_FilPrm(DrvSpcElm->FilPrm, NewFilPrm)) {
	    return FALSE; }/*if*/;
	 DrvSpcElm = DrvSpcElm->Next; }/*if*/; }/*for*/;
   return (NextDrvSpc == NIL);
   }/*CheckCompact*/


static boolean
CanCompact(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_DrvSpc, DrvSpc),
   GMC_ARG(tp_DrvSpc, NextDrvSpc)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_DrvSpc, DrvSpc)
   GMC_DCL(tp_DrvSpc, NextDrvSpc)
{
   tp_DrvPth DrvPth;
   tp_FilPrm FilPrm;
   tp_DrvSpc DrvSpcElm;
   boolean Can;

   FORBIDDEN(FilHdr == ERROR || DrvSpc == ERROR);

   if (FilHdr_FilTyp(FilHdr) == NextDrvSpc->FilTyp) {
      return FALSE; }/*if*/;

   DrvPth = Get_DrvPth(FilHdr, NextDrvSpc->FilTyp);
   if (DrvPth == ERROR) {
      return FALSE; }/*if*/;

   FilPrm = RootFilPrm;
   for (DrvSpcElm = DrvSpc; DrvSpcElm != NIL; DrvSpcElm = DrvSpcElm->Next) {
      FilPrm = Append_FilPrm(FilPrm, DrvSpcElm->FilPrm); }/*for*/;
   FilPrm = Append_FilPrm(FilPrm, NextDrvSpc->FilPrm);
   Can = CheckCompact(DrvSpc, NextDrvSpc, DrvPth, FilPrm);

   Ret_DrvPth(DrvPth);

   return Can;
   }/*CanCompact*/


void
Print_FilHdr(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tps_Str StrBuf;
   tp_FilHdr TmpFilHdr;
   tp_DrvSpc DrvSpc, LastDrvSpc, RestDrvSpc, DrvSpcElm;
   tp_FilPrm FilPrm;

   FORBIDDEN(((FilDsc == NIL) == (Str == NIL)) || FilHdr == ERROR);

   if (IsStr(FilHdr)) {
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, "=");
	    Print_Unlex(FilDsc, FilHdr_Ident(FilHdr));
	 }else{
	    (void)strcpy(Str, "=");
	    Unlex(Tail(Str), FilHdr_Ident(FilHdr)); };}/*select*/;
      return; }/*if*/;

   TmpFilHdr = FilHdr_SrcFilHdr(Copy_FilHdr(FilHdr));
   /*select*/{
      if (FilDsc != NIL) {
	 FilHdr_HostFN(StrBuf, TmpFilHdr, TRUE);
	 Write(FilDsc, StrBuf);
      }else{
	 FilHdr_HostFN(Str, TmpFilHdr, TRUE); };}/*select*/;

   DrvSpc = NIL;
   RestDrvSpc = FilHdr_DrvSpc(FilHdr);

   while (RestDrvSpc != NIL) {

      DrvSpc = RestDrvSpc;
      RestDrvSpc = RestDrvSpc->Next;
      DrvSpc->Next = NIL;

      if (DrvSpc->Key == NIL) {
	 while (RestDrvSpc != NIL
		&& RestDrvSpc->Key == NIL
		&& CanCompact(TmpFilHdr, DrvSpc, RestDrvSpc)) {
	    ShiftLeft_DrvSpc(DrvSpc, &RestDrvSpc); }/*while*/; }/*if*/;

      FilPrm = RootFilPrm;
      for (DrvSpcElm = DrvSpc; DrvSpcElm != NIL; DrvSpcElm = DrvSpcElm->Next) {
	 FilPrm = Append_FilPrm(FilPrm, DrvSpcElm->FilPrm); }/*for*/;
      Print_FilPrm(FilDsc, Tail(Str), FilPrm);

      LastDrvSpc = Last_DrvSpc(DrvSpc);
      Ret_FilHdr(TmpFilHdr);
      TmpFilHdr = Copy_FilHdr(LastDrvSpc->FilHdr);
      if (RestDrvSpc == NIL || !IsVTgt_FKind(RestDrvSpc->FKind)) {
	 Print_DrvSpc(FilDsc, Tail(Str), LastDrvSpc); }/*if*/;
      Ret_DrvSpc(DrvSpc);
      DrvSpc = NIL; }/*while*/

   if (IsGeneric(FilHdr) || IsPipe(FilHdr)) {
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, " :");
	    Print_Unlex(FilDsc, FilTyp_FTName(FatherFilTyp));
	 }else{
	    (void)strcpy(Str, " :");
	    Unlex(Tail(Str), FilTyp_FTName(FatherFilTyp)); };}/*select*/;
      }/*if*/;

   Ret_FilHdr(TmpFilHdr);
   }/*Print_FilHdr*/


void
SPrint_FilHdr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   Print_FilHdr((tp_FilDsc)NIL, OdinExpr, FilHdr);
   }/*SPrint_FilHdr*/


void
VerboseSPrint_FilHdr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilHdr SrcFilHdr;
   tp_DrvSpc HeadDrvSpc, DrvSpc;

   FORBIDDEN(OdinExpr == ERROR || FilHdr == ERROR);

   SrcFilHdr = FilHdr_SrcFilHdr(Copy_FilHdr(FilHdr));
   FilHdr_HostFN(OdinExpr, SrcFilHdr, TRUE);
   Ret_FilHdr(SrcFilHdr);
   HeadDrvSpc = FilHdr_DrvSpc(FilHdr);
   for (DrvSpc=HeadDrvSpc; DrvSpc!=NIL; DrvSpc=DrvSpc->Next) {
      Print_FilPrm((tp_FilDsc)NIL, Tail(OdinExpr), DrvSpc->FilPrm);
      Print_DrvSpc((tp_FilDsc)NIL, Tail(OdinExpr), DrvSpc); }/*for*/;
   Ret_DrvSpc(HeadDrvSpc);
   }/*VerboseSPrint_FilHdr*/


