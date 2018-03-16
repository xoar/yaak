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


extern tp_Str		PrevParseStr;
extern tp_Str		ParseStr;
extern tp_FileName	ParseFN;
extern int		*ParseLNPtr;


tp_Nod
OC_Parser(
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(int*, LNPtr)
   )
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(int*, LNPtr)
{
   if (Str == ERROR) return ERROR;
   PrevParseStr = Str;
   ParseStr = Str;
   ParseFN = FileName;
   ParseLNPtr = LNPtr;
   return OC_Parse();
   }/*OC_Parser*/


int
OC_Lex(GMC_ARG_VOID)
{
   IsCmdLex = TRUE;
   return Lex();
   }/*OC_Lex*/


void
OC_Unparse(
   GMC_ARG(tp_Str, Str),
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_Str, Str)
   GMC_DCL(tp_Nod, Nod)
{
   tp_Nod Son;
   tp_Str SubStr;

   switch (Nod_NodTyp(Nod)) {
      case DRVFIL: {
	 Son = Nod_Son(1, Nod);
	 OC_Unparse(Str, Son);
	 SubStr = Tail(Str);
	 for (Son = Nod_Brother(Son); Son != NIL; Son = Nod_Brother(Son)) {
	    if (Nod_NodTyp(Nod_Son(1, Son)) == HELP) {
	       return; }/*if*/;
	    if (Nod_NodTyp(Son) != ELMOPR && Nod_NodTyp(Son) != DIROPR) {
	       (void)strcat(SubStr, " "); }/*if*/;
	    SubStr = Tail(SubStr);
	    OC_Unparse(SubStr, Son); }/*for*/;
	 break; }/*case*/;
      case WORD: {
	 Unlex(Str, Sym_Str(Nod_Sym(Nod)));
	 break; }/*case*/;
      case HOSTWD: {
	 (void)strcpy(Str, "!");
	 Unlex(Tail(Str), Sym_Str(Nod_Sym(Nod)));
	 break; }/*case*/;
      case EMPFIL: {
	 (void)strcpy(Str, "()");
	 break; }/*case*/;
      case ARTFIL: {
	 (void)strcpy(Str, "/");
	 break; }/*case*/;
      case OBJTID: {
	 (void)strcpy(Str, "\\0");
	 Unlex(Tail(Str), Sym_Str(Nod_Sym(Nod)));
	 break; }/*case*/;
      case ABSFIL: {
	 (void)strcpy(Str, "/");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case STRING: {
	 (void)strcpy(Str, "=");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case PRMOPR: {
	 (void)strcpy(Str, "+");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 if (Nod_NumSons(Nod) > 1) {
	    (void)strcpy(Tail(Str), "=");
	    OC_Unparse(Tail(Str), Nod_Son(2, Nod)); }/*if*/;
	 break; }/*case*/;
      case APLOPR: {
	 (void)strcpy(Str, "+(");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 (void)strcat(Str, ")");
	 break; }/*case*/;
      case PRMVLS: {
	 OC_Unparse(Str, Nod_Son(1, Nod));
	 for (Son = Nod_Son(2, Nod); Son != NIL; Son = Nod_Brother(Son)) {
	    (void)strcpy(Tail(Str), " ");
	    OC_Unparse(Tail(Str), Son); }/*for*/;
	 break; }/*case*/;
      case DRVOPR: {
	 (void)strcpy(Str, ":");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case HODOPR: {
	 (void)strcpy(Str, ":");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 (void)strcpy(Tail(Str), "=:");
	 OC_Unparse(Tail(Str), Nod_Son(2, Nod));
	 break; }/*case*/;
      case ELMOPR: {
	 (void)strcpy(Str, "/");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case SEGOPR: {
	 (void)strcpy(Str, "%");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break;}/*case*/;
      case DIROPR: {
	 (void)strcpy(Str, "/");
	 break; }/*case*/;
      case OPRTNS: {
	 (void)strcpy(Str, "(");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 for (Son = Nod_Son(2, Nod); Son != NIL; Son = Nod_Brother(Son)) {
	    (void)strcpy(Tail(Str), " ");
	    OC_Unparse(Tail(Str), Son); }/*for*/;
	 (void)strcat(Str, ")");
	 break; }/*case*/;
      case PVLFIL: {
	 (void)strcpy(Str, "(");
	 OC_Unparse(Tail(Str), Nod_Son(1, Nod));
	 (void)strcat(Str, ")");
	 break; }/*case*/;
      default: {
	 FATALERROR("Unexpected NodTyp"); };}/*switch*/;
   }/*OC_Unparse*/

