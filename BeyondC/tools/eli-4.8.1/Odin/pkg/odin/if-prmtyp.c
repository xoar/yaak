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
#include "inc/Client.h"
#include "inc/FKind_.h"
#include "inc/PrmTyp.h"
#include "inc/Str.h"


extern int		num_PrmTypS;
extern tp_PrmTyp	PrmTypS;


tp_PTName
PrmTyp_PTName(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   if (PrmTyp == ERROR) return ERROR;
   return PrmTyp->PTName;
   }/*PrmTyp_PTName*/


static tp_PrmTyp
PTName_PrmTyp(
   GMC_ARG(tp_PTName, PTName)
   )
   GMC_DCL(tp_PTName, PTName)
{
   int i;
   tp_PrmTyp PrmTyp;

   if (PTName == ERROR) {
      return ERROR; }/*if*/;
   for (i=0; i<num_PrmTypS; i++) {
      PrmTyp = &PrmTypS[i];
      if (strcmp(PTName, PrmTyp->PTName) == 0) {
	 return PrmTyp; }/*if*/; }/*for*/;
   return ERROR;
   }/*PTName_PrmTyp*/


tp_FilTyp
PrmTyp_FilTyp(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   if (PrmTyp == ERROR) return ERROR;
   return PrmTyp->FilTyp;
   }/*PrmTyp_FilTyp*/


boolean
IsFirst_PrmTyp(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   FORBIDDEN(PrmTyp == ERROR);
   return (PrmTyp->FilTyp == FirstFilTyp);
   }/*IsFirst_PrmTyp*/


int
PrmTyp_I(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   FORBIDDEN(PrmTyp == ERROR);
   return PrmTyp->IPrmTyp;
   }/*PrmTyp_I*/


void
SetPrmTyp_Mark(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   PrmTyp->Mark = TRUE;
   }/*SetPrmTyp_Mark*/


tp_FilHdr
PrmTyp_StrDirFilHdr(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   tp_FilHdr FilHdr;

   if (PrmTyp == ERROR) {
      return ERROR; }/*if*/;
   if (PrmTyp->StrDirLocHdr == NIL) {
      FilHdr = Extend_FilHdr(Copy_FilHdr(StrDirFilHdr), FK_Str,
			     ObjectFilTyp, RootFilPrm, PrmTyp_PTName(PrmTyp));
      PrmTyp->StrDirLocHdr = FilHdr_LocHdr(FilHdr);
      return FilHdr; }/*if*/;
   return LocHdr_FilHdr(PrmTyp->StrDirLocHdr);
   }/*PrmTyp_StrDirFilHdr*/


tp_FilPVal
PrmTyp_RootFilPVal(
   GMC_ARG(tp_PrmTyp, PrmTyp)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
{
   tp_FilPVal FilPVal;
   tp_LocPVal LocPVal;

   if (PrmTyp->RootLocPVal == NIL) {
      FilPVal = New_FilPVal();
      LocPVal = FilPVal_LocPVal(FilPVal);
      Add_RootLocPVal(PrmTyp, LocPVal);
      PrmTyp->RootLocPVal = LocPVal; }/*if*/;
   return LocPVal_FilPVal(PrmTyp->RootLocPVal);
   }/*PrmTyp_RootFilPVal*/


void
SetPrmTyp_RootLocPVal(
   GMC_ARG(tp_PrmTyp, PrmTyp),
   GMC_ARG(tp_LocPVal, LocPVal)
   )
   GMC_DCL(tp_PrmTyp, PrmTyp)
   GMC_DCL(tp_LocPVal, LocPVal)
{
   FORBIDDEN(PrmTyp->RootLocPVal != NIL || LocPVal == NIL);
   PrmTyp->RootLocPVal = LocPVal;
   }/*SetPrmTyp_RootLocPVal*/


void
SetFilHdr_PrmTypMarks(
   GMC_ARG(tp_FilHdr, FilHdr)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
{
   SetFilHdr_Marks(FilHdr, TRUE);
   }/*SetFilHdr_PrmTypMarks*/


void
Clr_PrmTypMarks(GMC_ARG_VOID)
{
   int i;

   for (i=0; i<num_PrmTypS; i++) {
      PrmTypS[i].Mark = FALSE; }/*for*/;
   Clr_FilTypMarks();
   }/*Clr_PrmTypMarks*/


void
WriteMarkedPrmTyps(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   int i;
   tp_PrmTyp PrmTyp;
   boolean Found;

   Found = FALSE;
   for (i=0; i<num_PrmTypS; i++) {
      PrmTyp = &PrmTypS[i];
      if (PrmTyp->Mark && CurrentClient->HelpLevel >= PrmTyp->HelpLevel) {
	 WriteNameDesc(FilDsc, PrmTyp->PTName, PrmTyp->Desc);
	 Found = TRUE; }/*if*/; }/*for*/;
   if (!Found) {
      Writeln(FilDsc, "(none)"); }/*if*/;
   }/*WriteMarkedPrmTyps*/


tp_PrmTyp
Nod_PrmTyp(
   GMC_ARG(tp_Nod, DrvTyp_Nod)
   )
   GMC_DCL(tp_Nod, DrvTyp_Nod)
{
   tp_Str Str;
   tp_PrmTyp PrmTyp;

   Str = Sym_Str(Nod_Sym(DrvTyp_Nod));
   PrmTyp = PTName_PrmTyp(Str);
   if (PrmTyp == ERROR) SystemError("No parameter type, <%s>.\n", Str);
   return PrmTyp;
   }/*Nod_PrmTyp*/


