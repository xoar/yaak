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
#include "inc/InpKind_.h"
#include "inc/FilPVal.h"
#include "inc/FileName.h"
#include "inc/FKind_.h"
#include "inc/Flag_.h"


int		num_FilPValS = 0;


static void
WriteFilPVal(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   WritePValInf(&FilPVal->PValInf, FilPVal->LocPVal);
   }/*WriteFilPVal*/


static tp_LocPVal
Alloc_PValInf(GMC_ARG_VOID)
{
   return (tp_LocPVal) Alloc(sizeof(tps_PValInf));
   }/*Alloc_PValInf*/


tp_FilPVal
New_FilPVal(GMC_ARG_VOID)
{
   tp_FilPVal FilPVal;

   FilPVal = (tp_FilPVal)malloc(sizeof(tps_FilPVal));
   num_FilPValS += 1;
   FilPVal->LocPVal = NIL;
   FilPVal->NextHash = NIL;

   FilPVal->PValInf.Father = NIL;
   FilPVal->PValInf.Brother = NIL;
   FilPVal->PValInf.Son = NIL;

   FilPVal->PValInf.LocHdr = NIL;
   FilPVal->PValInf.ValLocPVal = NIL;
   FilPVal->PValInf.DataLocHdr = NIL;

   FilPVal->Father = NIL;
   FilPVal->Brother = NIL;
   FilPVal->Son = NIL;
   return FilPVal;
   }/*New_FilPVal*/


boolean
IsRootFilPVal(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   return (FilPVal->Father == NIL);
   }/*IsRootFilPVal*/


static tp_FilPVal
Read_PValLayer(
   GMC_ARG(tp_LocPVal, LocPVal),
   GMC_ARG(tp_FilPVal, FatherFilPVal)
   )
   GMC_DCL(tp_LocPVal, LocPVal)
   GMC_DCL(tp_FilPVal, FatherFilPVal)
{
   tps_PValInf _PValInf; tp_PValInf PValInf = &_PValInf;
   tp_FilPVal FilPVal;

   if (LocPVal == NIL) {
      return NIL; }/*if*/;
   FORBIDDEN(FatherFilPVal->Son != NIL);
   ReadPValInf(PValInf, LocPVal);
   FilPVal = New_FilPVal();
   FilPVal->PValInf = *PValInf;
   FilPVal->Father = FatherFilPVal;
   FilPVal->Brother =
      Read_PValLayer(FilPVal->PValInf.Brother, FatherFilPVal);   
   Hash_Item((tp_Item)FilPVal, (tp_Loc)LocPVal);
   return FilPVal;
   }/*Read_PValLayer*/


tp_FilPVal
Add_PValInf(
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_LocHdr, LocHdr),
   GMC_ARG(tp_LocPVal, LocPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_LocHdr, LocHdr)
   GMC_DCL(tp_LocPVal, LocPVal)
{
   tp_FilPVal TmpFPV;

   FORBIDDEN(FilPVal == ERROR || (LocHdr == ERROR && LocPVal == ERROR));

   if (FilPVal->Son == NIL && FilPVal->PValInf.Son != NIL) {
      FilPVal->Son = Read_PValLayer(FilPVal->PValInf.Son, FilPVal); }/*if*/;

   for (TmpFPV = FilPVal->Son; TmpFPV != NIL; TmpFPV = TmpFPV->Brother) {
      if (TmpFPV->PValInf.LocHdr == LocHdr
	  && TmpFPV->PValInf.ValLocPVal == LocPVal) {
	 return TmpFPV; }/*if*/; }/*for*/;
   TmpFPV = New_FilPVal();
   TmpFPV->PValInf.LocHdr = LocHdr;
   TmpFPV->PValInf.ValLocPVal = LocPVal;
   TmpFPV->Father = FilPVal;
   TmpFPV->Brother = FilPVal->Son; FilPVal->Son = TmpFPV;
   return TmpFPV;
   }/*Add_PValInf*/


tp_FilPVal
Append_PValInf(
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_LocHdr, LocHdr),
   GMC_ARG(tp_LocPVal, ValLocPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_LocHdr, LocHdr)
   GMC_DCL(tp_LocPVal, ValLocPVal)
{
   tp_FilPVal TmpFPV;

   FORBIDDEN(FilPVal == ERROR || (LocHdr == ERROR && ValLocPVal == ERROR));

   if (ValLocPVal != NIL && IsRootFilPVal(LocPVal_FilPVal(ValLocPVal))) {
      return FilPVal; }/*if*/;
   for (TmpFPV = FilPVal; !IsRootFilPVal(TmpFPV); TmpFPV = TmpFPV->Father) {
      if (TmpFPV->PValInf.LocHdr == LocHdr
	  && TmpFPV->PValInf.ValLocPVal == ValLocPVal) {
	 return FilPVal; }/*if*/; }/*for*/;
   return Add_PValInf(FilPVal, LocHdr, ValLocPVal);
   }/*Append_PValInf*/


tp_FilPVal
Append_FilPVal(
   GMC_ARG(tp_FilPVal, FilPVal1),
   GMC_ARG(tp_FilPVal, FilPVal2)
   )
   GMC_DCL(tp_FilPVal, FilPVal1)
   GMC_DCL(tp_FilPVal, FilPVal2)
{
   if (FilPVal1 == ERROR || FilPVal2 == ERROR) return ERROR;
   if (IsRootFilPVal(FilPVal1)) {
      return FilPVal2; }/*if*/;
   if (IsRootFilPVal(FilPVal2)) {
      return FilPVal1; }/*if*/;
   return Append_PValInf(Append_FilPVal(FilPVal1, FilPVal2->Father),
			 FilPVal2->PValInf.LocHdr,
			 FilPVal2->PValInf.ValLocPVal);
   }/*Append_FilPVal*/


tp_LocPVal
FilPVal_LocPVal(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;
   if (FilPVal->LocPVal == NIL) {
      Hash_Item((tp_Item)FilPVal, (tp_Loc)Alloc_PValInf());
      if (FilPVal->Father != NIL) {
	 FilPVal->PValInf.Father = FilPVal_LocPVal(FilPVal->Father);
	 FilPVal->PValInf.Brother = FilPVal->Father->PValInf.Son;
	 FilPVal->Father->PValInf.Son = FilPVal->LocPVal;
	 WriteFilPVal(FilPVal->Father); }/*if*/;
      WriteFilPVal(FilPVal); }/*if*/;
   return FilPVal->LocPVal;
   }/*FilPVal_LocPVal*/


static tp_FilPVal
Lookup_FilPVal(
   GMC_ARG(tp_LocPVal, LocPVal)
   )
   GMC_DCL(tp_LocPVal, LocPVal)
{
   return (tp_FilPVal)Lookup_Item(LocPVal);
   }/*Lookup_FilPVal*/


tp_FilPVal
LocPVal_FilPVal(
   GMC_ARG(tp_LocPVal, LocPVal)
   )
   GMC_DCL(tp_LocPVal, LocPVal)
{
   tp_FilPVal FilPVal, FatherFilPVal;
   tps_PValInf _PValInf; tp_PValInf PValInf = &_PValInf;

   if (LocPVal == ERROR) return ERROR;

   FilPVal = Lookup_FilPVal(LocPVal);
   if (FilPVal != ERROR) {
      return FilPVal; }/*if*/;

   ReadPValInf(PValInf, LocPVal);
   if (PValInf->Father == NIL) {
      FORBIDDEN(PValInf->LocHdr != NIL);
      FilPVal = New_FilPVal();
      FilPVal->PValInf = *PValInf;
      Hash_Item((tp_Item)FilPVal, (tp_Loc)LocPVal);
      FORBIDDEN(!IsRootFilPVal(FilPVal));
      return FilPVal; }/*if*/;
   FatherFilPVal = LocPVal_FilPVal(PValInf->Father);
   FORBIDDEN(FatherFilPVal->Son != NIL || FatherFilPVal->PValInf.Son == NIL);
   FatherFilPVal->Son
      = Read_PValLayer(FatherFilPVal->PValInf.Son, FatherFilPVal);
   FilPVal = Lookup_FilPVal(LocPVal);
   FORBIDDEN(FilPVal == ERROR);
   return FilPVal;
   }/*LocPVal_FilPVal*/


static void
Print_FilPValLocHdr(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_LocHdr, LocHdr)
{
   tp_FilHdr FilHdr;

   FilHdr = LocHdr_FilHdr(LocHdr);
   /*select*/{
      if (IsStr(FilHdr)) {
	 /*select*/{
	    if (FilDsc != NIL) {
	       Print_Unlex(FilDsc, FilHdr_Ident(FilHdr));
	    }else{
	       Unlex(Str, FilHdr_Ident(FilHdr)); };}/*select*/;
      }else{
	 /*select*/{
	    if (FilDsc != NIL) {
	       Write(FilDsc, "(");
	       Print_FilHdr(FilDsc, Str, FilHdr);
	       Write(FilDsc, ")");
	    }else{
	       (void)sprintf(Str, "(\\0%d)", (int)LocHdr);
	       };}/*select*/; };}/*select*/;
   Ret_FilHdr(FilHdr);
   }/*Print_FilPValLocHdr*/


static void
Print_ValFilPVal(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_FilPVal, FilPVal)
{
   FORBIDDEN(IsRootFilPVal(FilPVal));

   if (!IsRootFilPVal(FilPVal->Father)) {
      Print_ValFilPVal(FilDsc, Str, FilPVal->Father);
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, " ");
	 }else{
	    (void)strcat(Str, " "); };}/*select*/; }/*if*/;
   Print_FilPValLocHdr(FilDsc, Tail(Str), FilPVal->PValInf.LocHdr);
   }/*Print_ValFilPVal*/


static void
Print_FilPVal1(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_PrmTyp, PrmTyp),
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_PrmTyp, PrmTyp)
   GMC_DCL(tp_FilPVal, FilPVal)
{
   tp_Str TailStr;
   tp_FilHdr FilHdr;

   FORBIDDEN(FilPVal == ERROR);

   if (IsRootFilPVal(FilPVal)) {
      if (FilDsc == NIL) {
	 (void)strcpy(Str, ""); }/*if*/;
      return; }/*if*/;

   Print_FilPVal1(FilDsc, Str, PrmTyp, FilPVal->Father);

   TailStr = Tail(Str);
   /*select*/{
      if (FilDsc != NIL) {
	 Write(FilDsc, " +");
      }else{
	 (void)strcat(TailStr, " +"); };}/*select*/;

   if (PrmTyp == ApplyPrmTyp) {
      FORBIDDEN(FilPVal->PValInf.LocHdr == NIL);
      FilHdr = LocHdr_FilHdr(FilPVal->PValInf.LocHdr);
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, "(");
	 }else{
	    (void)strcat(TailStr, "("); };}/*select*/;
      TailStr = Tail(Str);
      Print_FilHdr(FilDsc, TailStr, FilHdr);
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, ")");
	 }else{
	    (void)strcat(TailStr, ")"); };}/*select*/;
      Ret_FilHdr(FilHdr);
      return; }/*if*/;

   /*select*/{
      if (FilDsc != NIL) {
	 Print_Unlex(FilDsc, PrmTyp_PTName(PrmTyp));
	 Write(FilDsc, "=");
      }else{
	 Unlex(Tail(TailStr), PrmTyp_PTName(PrmTyp));
	 (void)strcat(TailStr, "=");
	 };}/*select*/;
   
   if (FilPVal->PValInf.LocHdr != NIL) {
      Print_FilPValLocHdr(FilDsc, Tail(TailStr), FilPVal->PValInf.LocHdr);
      return; }/*if*/;

   Print_ValFilPVal(FilDsc, Tail(TailStr),
		    LocPVal_FilPVal(FilPVal->PValInf.ValLocPVal));
   }/*Print_FilPVal1*/


void
Print_FilPVal(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_PrmTyp, PrmTyp),
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_PrmTyp, PrmTyp)
   GMC_DCL(tp_FilPVal, FilPVal)
{
   FORBIDDEN((FilDsc == NIL) == (Str == NIL));
   FORBIDDEN(PrmTyp == ERROR || FilPVal == ERROR);

   if (IsRootFilPVal(FilPVal)) {
      /*select*/{
	 if (FilDsc != NIL) {
	    Write(FilDsc, " +");
	    Print_Unlex(FilDsc, PrmTyp_PTName(PrmTyp));
	 }else{
	    (void)strcpy(Str, " +");
	    Unlex(Tail(Str), PrmTyp_PTName(PrmTyp)); };}/*select*/;
      return; }/*if*/;

   Print_FilPVal1(FilDsc, Str, PrmTyp, FilPVal);
   }/*Print_FilPVal*/


tp_LocHdr
FilPVal_LocHdr(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;
   return FilPVal->PValInf.LocHdr;
   }/*FilPVal_LocHdr*/


tp_LocPVal
FilPVal_ValLocPVal(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;
   return FilPVal->PValInf.ValLocPVal;
   }/*FilPVal_ValLocPVal*/


void
Set_FilPVal_DataLocHdr(
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_LocHdr, LocHdr)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_LocHdr, LocHdr)
{
   FORBIDDEN(FilPVal == ERROR);
   if (FilPVal->PValInf.DataLocHdr != LocHdr) {
      FilPVal->PValInf.DataLocHdr = LocHdr;
      WriteFilPVal(FilPVal); }/*if*/;
   }/*Set_FilPVal_DataLocHdr*/


tp_LocHdr
FilPVal_DataLocHdr(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;
   return FilPVal->PValInf.DataLocHdr;
   }/*FilPVal_DataLocHdr*/


tp_FilPVal
FilPVal_Father(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;
   return FilPVal->Father;
   }/*FilPVal_Father*/


static tp_FilPVal
Add_FilHdr_DerefPrmVal(
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_FilHdr, FilHdr)
{
   tp_FilPVal NewFilPVal;
   tp_FilElm FilElm;
   tp_FilHdr ElmFilHdr;
   
   FORBIDDEN(FilPVal == ERROR || FilHdr == ERROR);

   if (!IsRef(FilHdr) || FilHdr_Flag(FilHdr, FLAG_Union)) {
      return Add_PValInf(FilPVal, FilHdr_LocHdr(FilHdr), NIL); }/*if*/;

   NewFilPVal = FilPVal;
   FORBIDDEN(!IsElmNameUpToDate(FilHdr));
   Set_Flag(FilHdr, FLAG_Union);
   for (FilElm = LocElm_FilElm(FilHdr_LocElm(FilHdr));
	FilElm != NIL;
	FilElm = FilElm_NextFilElm(FilElm)) {
      ElmFilHdr = FilElm_FilHdr(FilElm);
      FORBIDDEN(ElmFilHdr == ERROR);
      NewFilPVal = Add_FilHdr_DerefPrmVal(NewFilPVal, ElmFilHdr);
      Ret_FilHdr(ElmFilHdr); }/*for*/;
   Clr_Flag(FilHdr, FLAG_Union);
   return NewFilPVal;
   }/*Add_FilHdr_DerefPrmVal*/


static tp_FilPVal
ValFilPVal_DerefPrmVal(
   GMC_ARG(tp_FilPVal, FilPVal)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
{
   tp_FilHdr FilHdr;
   tp_FilPVal ValFilPVal;
   
   FORBIDDEN(FilPVal == ERROR);

   if (IsRootFilPVal(FilPVal)) {
      return FilPVal; }/*if*/;

   ValFilPVal = ValFilPVal_DerefPrmVal(FilPVal->Father);
   FilHdr = LocHdr_FilHdr(FilPVal->PValInf.LocHdr);
   FORBIDDEN(FilHdr == ERROR);
   FORBIDDEN(FilPVal->PValInf.ValLocPVal != NIL);
   ValFilPVal = Add_FilHdr_DerefPrmVal(ValFilPVal, FilHdr);
   Ret_FilHdr(FilHdr);
   return ValFilPVal;
   }/*ValFilPVal_DerefPrmVal*/


tp_FilPVal
FilPVal_DerefPrmVal(
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   tp_FilHdr FilHdr;
   tp_FilPVal ValFilPVal, NewFilPVal;
   
   if (FilPVal == ERROR) {
      return ERROR; }/*if*/;

   if (IsRootFilPVal(FilPVal)) {
      return FilPVal; }/*if*/;

   NewFilPVal = FilPVal_DerefPrmVal(FilPVal->Father, PrmTyp);
   FilHdr = LocHdr_FilHdr(FilPVal->PValInf.LocHdr);
   if (FilHdr != NIL && !IsRef(FilHdr)) {
      Ret_FilHdr(FilHdr);
      FORBIDDEN(FilPVal->PValInf.ValLocPVal != NIL);
      return Append_PValInf(NewFilPVal, FilPVal->PValInf.LocHdr, NIL); }/*if*/;
   /*select*/{
      if (FilHdr != NIL) {
	 ValFilPVal = Add_FilHdr_DerefPrmVal
	  (PrmTyp_RootFilPVal(PrmTyp), FilHdr);
	 Ret_FilHdr(FilHdr);
      }else{
	 ValFilPVal = ValFilPVal_DerefPrmVal
	  (LocPVal_FilPVal(FilPVal->PValInf.ValLocPVal)); };}/*select*/;
   if (IsRootFilPVal(ValFilPVal)) {
      return NewFilPVal; }/*if*/;
   if (IsRootFilPVal(ValFilPVal->Father)) {
      return Append_PValInf(NewFilPVal, ValFilPVal->PValInf.LocHdr,
			    ValFilPVal->PValInf.ValLocPVal); }/*if*/;
   return Append_PValInf(NewFilPVal, NIL, FilPVal_LocPVal(ValFilPVal));
   }/*FilPVal_DerefPrmVal*/


void
Chain_FilPVal_DerefPrmVal(
   GMC_ARG(tp_LocInp*, FirstLIPtr),
   GMC_ARG(tp_LocInp*, LastLIPtr),
   GMC_ARG(tp_FilPVal, FilPVal),
   GMC_ARG(tp_FilHdr, OutFilHdr)
   )
   GMC_DCL(tp_LocInp*, FirstLIPtr)
   GMC_DCL(tp_LocInp*, LastLIPtr)
   GMC_DCL(tp_FilPVal, FilPVal)
   GMC_DCL(tp_FilHdr, OutFilHdr)
{
   tp_FilPVal TmpFPV;
   tp_FilHdr FilHdr;
   tp_LocInp LocInp;

   for (TmpFPV = FilPVal; !IsRootFilPVal(TmpFPV); TmpFPV = TmpFPV->Father) {
      /*select*/{
	 if (TmpFPV->PValInf.LocHdr != NIL) {
	    FilHdr = LocHdr_FilHdr(TmpFPV->PValInf.LocHdr);
	    if (IsRef(FilHdr)) {
	       LocInp = Make_LocInp(FilHdr, -1, IK_TransName, OutFilHdr);
	       Chain_LocInps(FirstLIPtr, LastLIPtr, LocInp); }/*if*/;
	    Ret_FilHdr(FilHdr);
	 }else{
	    Chain_FilPVal_DerefPrmVal
	     (FirstLIPtr, LastLIPtr,
	      LocPVal_FilPVal(TmpFPV->PValInf.ValLocPVal), OutFilHdr);
	    };}/*select*/; }/*for*/;
   }/*Chain_FilPVal_DerefPrmVal*/


