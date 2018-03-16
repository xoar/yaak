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

int		num_ParseErrors = 0;

int		num_NodS = 0;

static tp_Nod	FreeNod = NIL;

typedef struct _tps_Nod {
   tp_NodTyp NodTyp;
   tp_Sym Sym;
   tp_Nod Brother;
   tp_Nod Son;
#ifdef NODATT
   tp_Nod Att;
#endif
   }				tps_Nod;


tp_Nod
New_Nod(GMC_ARG_VOID)
{
   tp_Nod Nod;

   /*select*/{
      if (FreeNod == NIL) {
	 Nod = (tp_Nod)malloc(sizeof(tps_Nod));
	 num_NodS += 1;
      }else{
	 Nod = FreeNod;
	 FreeNod = FreeNod->Brother; };}/*select*/;
   Nod->NodTyp = NIL;
   Nod->Son = NIL;
   Nod->Brother = NIL;
   Nod->Sym = NIL;
   return Nod;
   }/*New_Nod*/


void
Ret_Nod(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   if (Nod == NIL) {
      return; }/*if*/;
   Ret_Nod(Nod->Son);
   Ret_Nod(Nod->Brother);
   Nod->Brother = FreeNod;
   FreeNod = Nod;
   }/*Ret_Nod*/


tp_NodTyp
Nod_NodTyp(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   if (Nod == ERROR) return ERROR;
   return Nod->NodTyp;
   }/*Nod_NodTyp*/


void
Set_Nod_NodTyp(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_NodTyp, NodTyp)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_NodTyp, NodTyp)
{
   Nod->NodTyp = NodTyp;
   }/*Set_Nod_NodTyp*/


tp_Nod
Nod_FirstSon(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   if (Nod == ERROR) return ERROR;
   return Nod->Son;
   }/*Nod_FirstSon*/


void
Set_Nod_FirstSon(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_Nod, FirstSon)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_Nod, FirstSon)
{
   Nod->Son = FirstSon;
   }/*Set_Nod_FirstSon*/


tp_Nod
Nod_Brother(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   if (Nod == ERROR) return ERROR;
   return Nod->Brother;
   }/*Nod_Brother*/


void
Set_Nod_Brother(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_Nod, Brother)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_Nod, Brother)
{
   Nod->Brother = Brother;
   }/*Set_Nod_Brother*/


int
Nod_NumSons(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   tp_Nod SonNod;
   int NumSons;

   FORBIDDEN(Nod == ERROR);
   NumSons = 0;
   for (SonNod = Nod->Son; SonNod != NIL; SonNod = SonNod->Brother) {
      NumSons += 1; }/*for*/;
   return NumSons;
   }/*Nod_NumSons*/


tp_Nod
Nod_Son(
   GMC_ARG(int, I),
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(int, I)
   GMC_DCL(tp_Nod, Nod)
{
   tp_Nod SonNod;
   int i;

   if (Nod == ERROR) return ERROR;
   FORBIDDEN(Nod == ERROR);
   FORBIDDEN(I <= 0);
   SonNod = Nod->Son;
   for (i=1; i<I; i++) {
      if (SonNod == NIL) {
	 return NIL; }/*if*/;
      SonNod = SonNod->Brother; }/*for*/;
   return SonNod;
   }/*Nod_Son*/


tp_Sym
Nod_Sym(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   if (Nod == ERROR) return ERROR;
   return Nod->Sym;
   }/*Nod_Sym*/


void
Set_Nod_Sym(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_Sym, Sym)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_Sym, Sym)
{
   Nod->Sym = Sym;
   }/*Set_Nod_Sym*/


#ifdef NODATT

tp_Nod
Get_NodAtt(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   FORBIDDEN(Nod == ERROR);
   return (Nod->Att);
   }/*Get_NodAtt*/


tp_Nod
Set_NodAtt(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_Nod, Att)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_Nod, Att)
{
   FORBIDDEN(Nod == ERROR);
   Nod->Att = Att;
   }/*Set_NodAtt*/


void
Set_All_NodAtts(
   GMC_ARG(tp_Nod, Nod),
   GMC_ARG(tp_Nod, Att)
   )
   GMC_DCL(tp_Nod, Nod)
   GMC_DCL(tp_Nod, Att)
{
   FORBIDDEN(Nod == ERROR);
   Nod->Att = Att;
   if (Nod->Son != NIL) Set_All_NodAtts(Nod->Son, Att);
   if (Nod->Brother != NIL) Set_All_NodAtts(Nod->Brother, Att);
   }/*Set_All_NodAtts*/

#endif

typedef char *			tp_Value;
typedef struct _tps_StackElm *	tp_StackElm;
typedef struct _tps_StackElm {
   tp_Value Value;
   int Count;
   tp_StackElm Next;
   }				tps_StackElm;

int			num_StackElmS = 0;
static tp_StackElm	FreeStackElm = NIL;

static tp_StackElm
New_StackElm(GMC_ARG_VOID)
{
   tp_StackElm StackElm;

   if (FreeStackElm == NIL) {
      num_StackElmS += 1;
      return (tp_StackElm)malloc(sizeof(tps_StackElm)); }/*if*/;
   StackElm = FreeStackElm;
   FreeStackElm = FreeStackElm->Next;
   return StackElm;
   }/*New_StackElm*/


static tp_StackElm	SymStack = NIL;

static boolean
Empty_SymStack(GMC_ARG_VOID)
{
   return (SymStack == NIL);
   }/*Empty_SymStack*/


void
Push_SymStack(
   GMC_ARG(tp_Sym, Sym)
   )
   GMC_DCL(tp_Sym, Sym)
{
   tp_StackElm StackElm;

   FORBIDDEN(Sym == ERROR);
   StackElm = New_StackElm();
   StackElm->Value = (tp_Value)Sym;
   StackElm->Next = SymStack;
   SymStack = StackElm;
   }/*Push_SymStack*/


static tp_Sym
TopOf_SymStack(GMC_ARG_VOID)
{
   FORBIDDEN(SymStack == NIL);
   return (tp_Sym)SymStack->Value;
   }/*TopOf_SymStack*/


static void
Pop_SymStack(GMC_ARG_VOID)
{
   tp_StackElm OldFreeStackElm;

   FORBIDDEN(SymStack == NIL);
   OldFreeStackElm = FreeStackElm;
   FreeStackElm = SymStack;
   SymStack = SymStack->Next;
   FreeStackElm->Next = OldFreeStackElm;
   }/*Pop_SymStack*/


static tp_StackElm	NodStack = NIL;

static boolean
Empty_NodStack(GMC_ARG_VOID)
{
   return (NodStack == NIL);
   }/*Empty_NodStack*/


static void
Push_NodStack(
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Nod, Nod)
{
   tp_StackElm StackElm;

   FORBIDDEN(Nod == ERROR);
   StackElm = New_StackElm();
   StackElm->Value = (tp_Value)Nod;
   StackElm->Next = NodStack;
   NodStack = StackElm;
   }/*Push_NodStack*/


static tp_Nod
TopOf_NodStack(GMC_ARG_VOID)
{
   FORBIDDEN(NodStack == NIL);
   return (tp_Nod)NodStack->Value;
   }/*TopOf_NodStack*/


static void
Pop_NodStack(GMC_ARG_VOID)
{
   tp_StackElm OldFreeStackElm;

   FORBIDDEN(NodStack == NIL);
   OldFreeStackElm = FreeStackElm;
   FreeStackElm = NodStack;
   NodStack = NodStack->Next;
   FreeStackElm->Next = OldFreeStackElm;
   }/*Pop_NodStack*/


static tp_StackElm	SonStack = NIL;

static boolean
Empty_SonStack(GMC_ARG_VOID)
{
   return (SonStack == NIL);
   }/*Empty_SonStack*/


static void
Push_SonStack(
   GMC_ARG(int, NumSons)
   )
   GMC_DCL(int, NumSons)
{
   tp_StackElm StackElm;

   FORBIDDEN(NumSons < 0);
   StackElm = New_StackElm();
   StackElm->Count = NumSons;
   StackElm->Next = SonStack;
   SonStack = StackElm;
   }/*Push_SonStack*/


static int
TopOf_SonStack(GMC_ARG_VOID)
{
   FORBIDDEN(SonStack == NIL);
   return SonStack->Count;
   }/*TopOf_SonStack*/


static void
Pop_SonStack(GMC_ARG_VOID)
{
   tp_StackElm OldFreeStackElm;

   FORBIDDEN(SonStack == NIL);
   OldFreeStackElm = FreeStackElm;
   FreeStackElm = SonStack;
   SonStack = SonStack->Next;
   FreeStackElm->Next = OldFreeStackElm;
   }/*Pop_SonStack*/


void
Init_ConstructTree(GMC_ARG_VOID)
{
   while (!Empty_SymStack()) {
      Pop_SymStack(); }/*while*/;
   while (!Empty_NodStack()) {
      Ret_Nod(TopOf_NodStack());
      Pop_NodStack(); }/*while*/;
   while (!Empty_SonStack()) {
      Pop_SonStack(); }/*while*/;
   }/*Init_ConstructTree*/


static void
MakeLeaf(
   GMC_ARG(tp_NodTyp, NodTyp),
   GMC_ARG(tp_Sym, Sym)
   )
   GMC_DCL(tp_NodTyp, NodTyp)
   GMC_DCL(tp_Sym, Sym)
{
   tp_Nod Nod;

   if (NodTyp == 0) {
      return; }/*if*/;
   Nod = New_Nod();
   Nod->NodTyp = NodTyp; Nod->Sym = Sym; Nod->Son = NIL; Nod->Brother = NIL;
   Push_NodStack(Nod); Push_SonStack(1);
   }/*MakeLeaf*/


static void
MakeEmptyNod(
   GMC_ARG(tp_NodTyp, NodTyp)
   )
   GMC_DCL(tp_NodTyp, NodTyp)
{
   tp_Nod Nod;

   if (NodTyp == 0) return;
   Nod = New_Nod();
   Nod->NodTyp = NodTyp; Nod->Sym = NIL; Nod->Son = NIL; Nod->Brother = NIL;
   Push_NodStack(Nod); Push_SonStack(1);
   }/*MakeEmptyNod*/


static void
MakeNod(
   GMC_ARG(int, Typ)
   )
   GMC_DCL(int, Typ)
{
   tp_NodTyp NodTyp;
   tp_Nod Nod, NewNod, Brother;
   int NumSons, i;

   NodTyp = Typ;
   NumSons = TopOf_SonStack();
   if (Typ < 0) {
      if (NumSons == 1) {
	 return; }/*if*/;
      NodTyp = -Typ; }/*if*/;
   Pop_SonStack();
   if (NumSons == 0) {
      MakeEmptyNod(NodTyp);
      return; }/*if*/;
   Brother = NIL;
   for (i=0; i<NumSons; i++) {
      NewNod = TopOf_NodStack(); Pop_NodStack();
      NewNod->Brother = Brother;
      Brother = NewNod; }/*for*/;
   Nod = New_Nod();
   Nod->NodTyp = NodTyp; Nod->Sym = NIL; Nod->Son = Brother; Nod->Brother = NIL;
   Push_NodStack(Nod); Push_SonStack(1);
   }/*MakeNod*/


static void
CollectSons(
   GMC_ARG(int, Number)
   )
   GMC_DCL(int, Number)
{
   int NumSons, i;

   FORBIDDEN(Number < 0);
   NumSons = 0;
   for (i=0; i<Number; i++) {
      NumSons = NumSons + TopOf_SonStack();
      Pop_SonStack(); }/*for*/;
   Push_SonStack(NumSons);
   }/*CollectSons*/


tp_Nod
End_ConstructTree(GMC_ARG_VOID)
{
   tp_Nod Root;

   if (num_ParseErrors > 0 || Empty_NodStack()) {
      while (!Empty_NodStack()) Pop_NodStack();
      while (!Empty_SonStack()) Pop_SonStack();
      return ERROR; }/*if*/;
   Root = TopOf_NodStack();
   Pop_NodStack();
   Pop_SonStack();
   return Root;
   }/*End_ConstructTree*/


void
Action(
   GMC_ARG(int, Typ),
   GMC_ARG(int, NumSons)
   )
   GMC_DCL(int, Typ)
   GMC_DCL(int, NumSons)
{
   tp_Sym Sym;

   if (num_ParseErrors > 0) return;
   /*select*/{
      if (NumSons < 0) {
	 /*select*/{
	    if (Typ < 0) {
	       CollectSons(-NumSons);
	       MakeNod(-Typ);
	       EndLex();
	    }else{
	       Sym = TopOf_SymStack(); Pop_SymStack();
	       MakeLeaf(Typ, Sym); };}/*select*/;
      }else if (NumSons == 0) {
	 /*select*/{
	    if (Typ < 0) {
	       CollectSons(NumSons);
	       MakeNod(-Typ);
	       EndLex();
	    }else if (Typ == 0) {
	       CollectSons(NumSons);
	    }else{
	       MakeEmptyNod(Typ); };}/*select*/;
      }else{
	 if (NumSons > 1) CollectSons(NumSons);
	 if (Typ != 0) MakeNod(Typ);
	 };}/*select*/;
   }/*Action*/


