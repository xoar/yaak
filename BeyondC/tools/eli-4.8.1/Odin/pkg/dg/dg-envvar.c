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
#include "inc/EnvVar.h"
#include "inc/EnvVarLst.h"
#include "inc/FilTyp.h"
#include "inc/InpSpc.h"
#include "inc/ISKind_.h"
#include "inc/PrmTyp.h"
#include "inc/Str.h"


tp_EnvVar		EnvVarS = NIL;
static tp_EnvVar		LastEnvVar = NIL;
int			num_EnvVarS = 0;

static tp_EnvVarLst		EnvVarLstS = NIL;
static tp_EnvVarLst		LastEnvVarLst = NIL;
int			num_EnvVarLstS = 0;

tp_EnvVarLst		DfltEnvVarLst;


static tp_EnvVarLst
New_EnvVarLst()
{
   tp_EnvVarLst EnvVarLst;

   EnvVarLst = (tp_EnvVarLst)malloc(sizeof(tps_EnvVarLst));
   /*select*/{
      if (LastEnvVarLst == NIL) {
	 EnvVarLstS = EnvVarLst;
      }else{
	 LastEnvVarLst->Link = EnvVarLst; };}/*select*/;
   LastEnvVarLst = EnvVarLst;
   EnvVarLst->EnvVar = 0;
   EnvVarLst->Next = 0;
   EnvVarLst->Brother = 0;
   EnvVarLst->Son = 0;
   EnvVarLst->Index = num_EnvVarLstS;
   EnvVarLst->Link = NIL;
   num_EnvVarLstS++;
   return EnvVarLst;
   }/*New_EnvVarLst*/


void
Init_EnvVars()
{
   DfltEnvVarLst = New_EnvVarLst();
   }/*Init_EnvVars*/


static tp_EnvVar
New_EnvVar()
{
   tp_EnvVar EnvVar;

   EnvVar = (tp_EnvVar)malloc(sizeof(tps_EnvVar));
   /*select*/{
      if (LastEnvVar == NIL) {
	 EnvVarS = EnvVar;
      }else{
	 LastEnvVar->Link = EnvVar; };}/*select*/;
   LastEnvVar = EnvVar;
   EnvVar->Name = NIL;
   EnvVar->Desc = NIL;
   EnvVar->HelpLevel = 0;
   EnvVar->Default = NIL;
   EnvVar->IsFile = FALSE;
   EnvVar->Index = num_EnvVarS;
   EnvVar->Link = NIL;
   num_EnvVarS++;
   return EnvVar;
   }/*New_EnvVar*/


static tp_EnvVar
Create_EnvVar(Name)
   tp_Str Name;
{
   tp_EnvVar EnvVar;

   EnvVar = New_EnvVar();
   EnvVar->Name = Name;
   return EnvVar;
   }/*Create_EnvVar*/


tp_EnvVar
Lookup_EnvVar(Name)
   tp_Str Name;
{
   tp_EnvVar EnvVar;

   for (EnvVar = EnvVarS; EnvVar != NIL; EnvVar = EnvVar->Link) {
      if (Name == EnvVar->Name) {
	 return EnvVar; }/*if*/; }/*for*/;
   return Create_EnvVar(Name);
   }/*Lookup_EnvVar*/


tp_Desc
EnvVar_Desc(EnvVar)
   tp_EnvVar EnvVar;
{
   if (EnvVar == ERROR) return ERROR;
   return EnvVar->Desc;
   }/*EnvVar_Desc*/


void
Set_EnvVar_Desc(EnvVar, Desc, Hidden)
   tp_EnvVar EnvVar;
   tp_Desc Desc;
   boolean Hidden;
{
   FORBIDDEN(EnvVar == ERROR || Desc == ERROR);
   FORBIDDEN(EnvVar->Desc != NIL);
   EnvVar->Desc = Desc;
   EnvVar->HelpLevel = (Hidden ? 2 : 1);
   }/*Set_EnvVar_Desc*/


void
Set_EnvVar_Default(EnvVar, Default, IsFile)
   tp_EnvVar EnvVar;
   tp_Str Default;
   boolean IsFile;
{
   FORBIDDEN(EnvVar == ERROR || Default == ERROR);
   FORBIDDEN(EnvVar->Default != NIL);
   EnvVar->Default = Default;
   EnvVar->IsFile = IsFile;
   }/*Set_EnvVar_Default*/


tp_EnvVarLst
EnvVarLst_Next(EnvVarLst)
   tp_EnvVarLst EnvVarLst;
{
   return EnvVarLst->Next;
   }/*EnvVarLst_Next*/


static tp_EnvVarLst
Add_EnvVar(EnvVarLst, EnvVar)
   tp_EnvVarLst EnvVarLst;
   tp_EnvVar EnvVar;
{
   tp_EnvVarLst SonEnvVarLst;

   for (SonEnvVarLst = EnvVarLst->Son;
	SonEnvVarLst != 0;
	SonEnvVarLst = SonEnvVarLst->Brother) {
      if (EnvVar == SonEnvVarLst->EnvVar) {
	 return SonEnvVarLst; }/*if*/; }/*for*/;
   SonEnvVarLst = New_EnvVarLst();
   SonEnvVarLst->EnvVar = EnvVar;
   SonEnvVarLst->Next = EnvVarLst;
   SonEnvVarLst->Brother = EnvVarLst->Son;
   EnvVarLst->Son = SonEnvVarLst;
   return SonEnvVarLst;
   }/*Add_EnvVar*/


tp_EnvVarLst
Make_EnvVarLst(EnvVar)
   tp_EnvVar EnvVar;
{
   return Add_EnvVar(DfltEnvVarLst, EnvVar);
   }/*Make_EnvVarLst*/


tp_EnvVarLst
Union_EnvVarLst(EnvVarLst1, EnvVarLst2)
   tp_EnvVarLst EnvVarLst1, EnvVarLst2;
{
   tp_EnvVarLst EnvVarLst;
   tp_EnvVar EnvVar;

   FORBIDDEN(EnvVarLst1 == ERROR || EnvVarLst2 == ERROR);
   if (EnvVarLst1 == DfltEnvVarLst) return EnvVarLst2;
   if (EnvVarLst2 == DfltEnvVarLst) return EnvVarLst1;
   /*select*/{
      if (EnvVarLst1->EnvVar == EnvVarLst2->EnvVar) {
	 EnvVarLst = Union_EnvVarLst(EnvVarLst1->Next, EnvVarLst2->Next);
	 EnvVar = EnvVarLst1->EnvVar;
      }else if (EnvVarLst1->EnvVar->Index < EnvVarLst2->EnvVar->Index) {
	 EnvVarLst = Union_EnvVarLst(EnvVarLst1->Next, EnvVarLst2);
	 EnvVar = EnvVarLst1->EnvVar;
      }else{
	 EnvVarLst = Union_EnvVarLst(EnvVarLst1, EnvVarLst2->Next);
	 EnvVar = EnvVarLst2->EnvVar; };}/*select*/;
   return Add_EnvVar(EnvVarLst, EnvVar);
   }/*Union_EnvVarLst*/


void
Print_EnvVarLst(FilDsc, EnvVarLst)
   tp_FilDsc FilDsc;
   tp_EnvVarLst EnvVarLst;
{
   tp_EnvVarLst EnvVarElm;

   for (EnvVarElm = EnvVarLst; EnvVarElm != DfltEnvVarLst; EnvVarElm = EnvVarElm->Next) {
      Write(FilDsc, " $");
      Write(FilDsc, EnvVarElm->EnvVar->Name); }/*for*/;
   }/*Print_EnvVarLst*/


void
Write_EnvVars(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_EnvVar EnvVar;
   tp_EnvVarLst EnvVarLst;
   int iEnvVar, iNext;
   tps_EntryStr sEnvVar, sNext;

   DG_FOREACH(EnvVar)
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, ".%s\1 .%s\1 %d .%s\1 %d\n",
       EnvVar->Name, EnvVar->Desc, EnvVar->HelpLevel, EnvVar->Default,
       EnvVar->IsFile);
      (void)fprintf(DG_C_FILE, "{\"%s\", \"%s\", %d, \"%s\", %d}",
       EnvVar->Name, EnvVar->Desc, EnvVar->HelpLevel, EnvVar->Default,
       EnvVar->IsFile);
      DG_END_FOREACH(EnvVar);

   DG_FOREACH(EnvVarLst)
      DG_ENTRY(EnvVarLst,EnvVar,EnvVar);
      if (EnvVarLst->Next == DfltEnvVarLst) EnvVarLst->Next = 0;
      DG_ENTRY(EnvVarLst,Next,EnvVarLst);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d\n", iEnvVar, iNext);
      (void)fprintf(DG_C_FILE, "{%s, %s}", sEnvVar, sNext);
   DG_END_FOREACH(EnvVarLst);
   }/*Write_EnvVarLsts*/


void
Write_ENV()
{
   tp_FilDsc FilDsc;
   tp_Str Str;
   tp_EnvVar EnvVar;

   FilDsc = FileName_WFilDsc("ENV", FALSE);
   if (FilDsc == ERROR) {
      SystemError("Cannot open ENV file.\n");
      exit(1); }/*if*/;
   (void)fprintf((FILE *)FilDsc, "%d\n", num_EnvVarS);
   for (EnvVar = EnvVarS; EnvVar != NIL; EnvVar = EnvVar->Link) {
      Str = GetEnv(EnvVar->Name);
      if (Str == NIL) Str = EnvVar->Default;
      (void)fprintf((FILE *)FilDsc, "%s=%s\1\n", EnvVar->Name, Str); }/*for*/;
   Close(FilDsc);
   }/*Write_ENV*/


static tp_InpSpc		InpSpcS = NIL;
static tp_InpSpc		LastInpSpc = NIL;
int			num_InpSpcS = 0;


tp_InpSpc
New_InpSpc()
{
   tp_InpSpc InpSpc;

   InpSpc = (tp_InpSpc)malloc(sizeof(tps_InpSpc));
   /*select*/{
      if (LastInpSpc == NIL) {
	 InpSpcS = InpSpc;
      }else{
	 LastInpSpc->Link = InpSpc; };}/*select*/;
   LastInpSpc = InpSpc;
   InpSpc->ISKind = NIL;
   InpSpc->FilTyp = NIL;
   InpSpc->PrmTyp = NIL;
   InpSpc->Str = NIL;
   InpSpc->IsEnvVar = FALSE;
   InpSpc->InpSpc = NIL;
   InpSpc->Next = NIL;
   InpSpc->Index = num_InpSpcS;
   InpSpc->Link = NIL;
   num_InpSpcS++;
   return InpSpc;
   }/*New_InpSpc*/


static tp_FilTyp
InpSpc_FilTyp(InpSpc)
   tp_InpSpc InpSpc;
{
   return InpSpc->FilTyp;
   }/*InpSpc_FilTyp*/


void
Write_InpSpcs(DRVGRF_FILE, DG_C_FILE)
   FILE *DRVGRF_FILE, *DG_C_FILE;
{
   tp_InpSpc InpSpc;
   int iFilTyp, iPrmTyp, iInpSpc, iNext;
   tps_EntryStr sFilTyp, sPrmTyp, sInpSpc, sNext;
   tps_Str sStr;

   DG_FOREACH(InpSpc)
      DG_ENTRY(InpSpc,FilTyp,FilTyp);
      DG_ENTRY(InpSpc,PrmTyp,PrmTyp);
      (void)strcpy(sStr, ((InpSpc->Str == NIL) ? "\2" : InpSpc->Str));
      DG_ENTRY(InpSpc,InpSpc,InpSpc);
      DG_ENTRY(InpSpc,Next,InpSpc);
      DG_ENTRY_SEPARATOR();
      (void)fprintf(DRVGRF_FILE, "%d %d %d .%s\1 %d %d %d\n",
       InpSpc->ISKind, iFilTyp, iPrmTyp, sStr, InpSpc->IsEnvVar,
       iInpSpc, iNext);
      if (InpSpc->Str == NIL) sprintf(sStr, "0");
      else sprintf(sStr, "\"%s\"", InpSpc->Str);
      (void)fprintf(DG_C_FILE, "{%d, %s, %s, %s, %d, %s, %s}",
       InpSpc->ISKind, sFilTyp, sPrmTyp, sStr, InpSpc->IsEnvVar,
       sInpSpc, sNext);
      DG_END_FOREACH(InpSpc);
   }/*Write_InpSpcs*/


