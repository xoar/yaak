/*
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 1,
or (at your option) any later version (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

geoff@boulder.colorado.edu
*/

#include <stdio.h>
#include "inc/GMC.h"
#include "inc/Entry.h"
#include "inc/FilTyp.h"
#include "inc/PrmTyp.h"
#include "inc/PrmTypLst.h"
#include "inc/Tool.h"


tp_PrmTyp		PrmTypS = NIL;
static tp_PrmTyp	LastPrmTyp = NIL;
int			num_PrmTypS = 0;

static tp_PrmTyp	NullPrmTyp;
static tp_PrmTyp	HookValPrmTyp;
static tp_PrmTyp	CopyDestPrmTyp;
tp_PrmTyp	ApplyPrmTyp;

static tp_PrmTypLst	PrmTypLstS = NIL;
static tp_PrmTypLst	LastPrmTypLst = NIL;
int			num_PrmTypLstS = 0;

tp_PrmTypLst		DfltPrmTypLst;

static tp_FTName	DfltPTName = ".";


static tp_PrmTyp
Make_SystemPrmTyp(PTName)
   tp_PTName PTName;
{
   return Lookup_PrmTyp(Sym_Str(Str_Sym(PTName)));
   }/*Make_SystemPrmTyp*/


static tp_PrmTyp
New_PrmTyp()
{
   tp_PrmTyp PrmTyp;

   PrmTyp = (tp_PrmTyp)malloc(sizeof(tps_PrmTyp));
   /*select*/{
      if (LastPrmTyp == NIL) {
	 PrmTypS = PrmTyp;
      }else{
	 LastPrmTyp->Link = PrmTyp; };}/*select*/;
   LastPrmTyp = PrmTyp;
   PrmTyp->PTName = DfltPTName;
   PrmTyp->Desc = NIL;
   PrmTyp->HelpLevel = 0;
   PrmTyp->FilTyp = ListFilTyp;
   PrmTyp->Index = num_PrmTypS;
   PrmTyp->Link = NIL;
   num_PrmTypS++;
   return PrmTyp;
   }/*New_PrmTyp*/


static tp_PrmTypLst
New_PrmTypLst()
{
   tp_PrmTypLst PrmTypLst;

   PrmTypLst = (tp_PrmTypLst)malloc(sizeof(tps_PrmTypLst));
   /*select*/{
      if (LastPrmTypLst == NIL) {
	 PrmTypLstS = PrmTypLst;
      }else{
	 LastPrmTypLst->Link = PrmTypLst; };}/*select*/;
   LastPrmTypLst = PrmTypLst;
   PrmTypLst->PrmTyp = 0;
   PrmTypLst->Next = 0;
   PrmTypLst->Brother = 0;
   PrmTypLst->Son = 0;
   PrmTypLst->Index = num_PrmTypLstS;
   PrmTypLst->Link = NIL;
   num_PrmTypLstS++;
   return PrmTypLst;
   }/*New_PrmTypLst*/


void
Init_PrmTyps()
{
   NullPrmTyp = Make_SystemPrmTyp("null");
   HookValPrmTyp = Make_SystemPrmTyp("hookvalue");
   CopyDestPrmTyp = Make_SystemPrmTyp("copy_dest");
   ApplyPrmTyp = Make_SystemPrmTyp("apply");

   DfltPrmTypLst = New_PrmTypLst();
   }/*Init_PrmTyps*/


tp_PTName
PrmTyp_PTName(PrmTyp)
   tp_PrmTyp PrmTyp;
{
   FORBIDDEN(PrmTyp == ERROR);
   return PrmTyp->PTName;
   }/*PrmTyp_PTName*/


tp_Desc
PrmTyp_Desc(PrmTyp)
   tp_PrmTyp PrmTyp;
{
   FORBIDDEN(PrmTyp == ERROR);
   return PrmTyp->Desc;
   }/*PrmTyp_Desc*/


void
Set_PrmTyp_Desc(PrmTyp, Desc, Hidden)
   tp_PrmTyp PrmTyp;
   tp_Desc Desc;
   boolean Hidden;
{
   FORBIDDEN(PrmTyp == ERROR || Desc == ERROR);
   FORBIDDEN(PrmTyp->Desc != NIL);
   PrmTyp->Desc = Desc;
   PrmTyp->HelpLevel = (Hidden ? 2 : 1);
   }/*Set_PrmTyp_Desc*/


tp_FilTyp
PrmTyp_FilTyp(PrmTyp)
   tp_PrmTyp PrmTyp;
{
   if (PrmTyp == ERROR) return ERROR;
   return PrmTyp->FilTyp;
   }/*PrmTyp_FilTyp*/


void
Set_PrmTyp_FilTyp(PrmTyp, FilTyp)
   tp_PrmTyp PrmTyp;
   tp_FilTyp FilTyp;
{
   FORBIDDEN(PrmTyp == ERROR || FilTyp == ERROR);
   PrmTyp->FilTyp = FilTyp;
   }/*Set_PrmTyp_FilTyp*/


static tp_PrmTyp
Create_PrmTyp(PTName)
   tp_PTName PTName;
{
   tp_PrmTyp PrmTyp;

   PrmTyp = New_PrmTyp();
   PrmTyp->PTName = PTName;
   return PrmTyp;
   }/*Create_PrmTyp*/


tp_PrmTyp
Lookup_PrmTyp(PTName)
   tp_PTName PTName;
{
   tp_PrmTyp PrmTyp;

   for (PrmTyp = PrmTypS; PrmTyp != NIL; PrmTyp = PrmTyp->Link) {
      if (PTName == PrmTyp->PTName) {
	 return PrmTyp; }/*if*/; }/*for*/;
   return Create_PrmTyp(PTName);
   }/*Lookup_PrmTyp*/


void
Print_PrmTyp(FilDsc, PrmTyp)
   tp_FilDsc FilDsc;
   tp_PrmTyp PrmTyp;
{
   Write(FilDsc, PrmTyp->PTName);
   }/*Print_PrmTyp*/


tp_PrmTypLst
PrmTypLst_Next(PrmTypLst)
   tp_PrmTypLst PrmTypLst;
{
   return PrmTypLst->Next;
   }/*PrmTypLst_Next*/


static tp_PrmTypLst
Add_PrmTyp(PrmTypLst, PrmTyp)
   tp_PrmTypLst PrmTypLst;
   tp_PrmTyp PrmTyp;
{
   tp_PrmTypLst SonPrmTypLst;

   for (SonPrmTypLst = PrmTypLst->Son;
	SonPrmTypLst != 0;
	SonPrmTypLst = SonPrmTypLst->Brother) {
      if (PrmTyp == SonPrmTypLst->PrmTyp) {
	 return SonPrmTypLst; }/*if*/; }/*for*/;
   SonPrmTypLst = New_PrmTypLst();
   SonPrmTypLst->PrmTyp = PrmTyp;
   SonPrmTypLst->Next = PrmTypLst;
   SonPrmTypLst->Brother = PrmTypLst->Son;
   PrmTypLst->Son = SonPrmTypLst;
   return SonPrmTypLst;
   }/*Add_PrmTyp*/


tp_PrmTypLst
Make_PrmTypLst(PrmTyp)
   tp_PrmTyp PrmTyp;
{
   return Add_PrmTyp(DfltPrmTypLst, PrmTyp);
   }/*Make_PrmTypLst*/


tp_PrmTypLst
Union_PrmTypLst(PrmTypLst1, PrmTypLst2)
   tp_PrmTypLst PrmTypLst1, PrmTypLst2;
{
   tp_PrmTypLst PrmTypLst;
   tp_PrmTyp PrmTyp;

   FORBIDDEN(PrmTypLst1 == ERROR || PrmTypLst2 == ERROR);
   if (PrmTypLst1 == DfltPrmTypLst) {
      return PrmTypLst2; }/*if*/;
   if (PrmTypLst2 == DfltPrmTypLst) {
      return PrmTypLst1; }/*if*/;
   /*select*/{
      if (PrmTypLst1->PrmTyp == PrmTypLst2->PrmTyp) {
	 PrmTypLst = Union_PrmTypLst(PrmTypLst1->Next, PrmTypLst2->Next);
	 PrmTyp = PrmTypLst1->PrmTyp;
      }else if (PrmTypLst1->PrmTyp->Index < PrmTypLst2->PrmTyp->Index) {
	 PrmTypLst = Union_PrmTypLst(PrmTypLst1->Next, PrmTypLst2);
	 PrmTyp = PrmTypLst1->PrmTyp;
      }else{
	 PrmTypLst = Union_PrmTypLst(PrmTypLst1, PrmTypLst2->Next);
	 PrmTyp = PrmTypLst2->PrmTyp; };}/*select*/;
   return Add_PrmTyp(PrmTypLst, PrmTyp);
   }/*Union_PrmTypLst*/


void
Print_PrmTypLst(FilDsc, PrmTypLst)
   tp_FilDsc FilDsc;
   tp_PrmTypLst PrmTypLst;
{
   tp_PrmTypLst PrmTypElm;

   for (PrmTypElm = PrmTypLst;
	PrmTypElm != DfltPrmTypLst;
	PrmTypElm = PrmTypElm->Next) {
      Write(FilDsc, " +");
      Write(FilDsc, PrmTypElm->PrmTyp->PTName); }/*for*/;
   }/*Print_PrmTypLst*/


void
Write_PrmTyps(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_PrmTyp PrmTyp;
   int iFilTyp;
   tps_EntryStr sFilTyp;
   tp_PrmTypLst PrmTypLst;
   int iPrmTyp, iNext;
   tps_EntryStr sPrmTyp, sNext;

   DG_FOREACH(PrmTyp)
      DG_ENTRY(PrmTyp,FilTyp,FilTyp);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, ".%s\1 .%s\1 %d %d\n",
       PrmTyp->PTName, PrmTyp->Desc, PrmTyp->HelpLevel, iFilTyp);
      (void)fprintf(DG_C_FILE, "{\"%s\", \"%s\", %d, %s, 0, 0, 0, %d}",
       PrmTyp->PTName, PrmTyp->Desc, PrmTyp->HelpLevel,
       sFilTyp, PrmTyp->Index);
      DG_END_FOREACH(PrmTyp);

   DG_CONST(NullPrmTyp,PrmTyp);
   DG_CONST(HookValPrmTyp,PrmTyp);
   DG_CONST(CopyDestPrmTyp,PrmTyp);
   DG_CONST(ApplyPrmTyp,PrmTyp);

   DG_FOREACH(PrmTypLst)
      DG_ENTRY(PrmTypLst,PrmTyp,PrmTyp);
      if (PrmTypLst->Next == DfltPrmTypLst) PrmTypLst->Next = 0;
      DG_ENTRY(PrmTypLst,Next,PrmTypLst);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d\n", iPrmTyp, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s}", sPrmTyp, sNext);
   DG_END_FOREACH(PrmTypLst);
   }/*Write_PrmTyps*/


