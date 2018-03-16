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
#include "inc/Str.h"
#include "inc/TokTyp_.h"


boolean		IsCmdLex;

tp_FileName	ParseFN;
int		*ParseLNPtr;
tp_Str		PrevParseStr;
tp_Str		ParseStr;


void
FileError(
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_Str, Str)
{
   if (ParseFN == NIL) {
      FORBIDDEN(ParseLNPtr != NIL);
      SystemError(Str);
      return; }/*if*/;
   if (ParseLNPtr == NIL) {
      SystemError("\"%s\": %s", ParseFN, Str);
      return; }/*if*/;
   SystemError("\"%s\", line %d: %s", ParseFN, *ParseLNPtr, Str);
   }/*FileError*/


void
ParseError(
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_Str, Str)
{
   FileError(Str);
   SystemError(" at <%s>.\n", PrevParseStr);
   }/*ParseError*/


void
Init_Lex(GMC_ARG_VOID)
{
   if (ParseLNPtr != NIL) *ParseLNPtr = *ParseLNPtr + 1;
   }/*Init_Lex*/


void
EndLex(GMC_ARG_VOID)
{
   SystemError("Unexpected call to EndLex.\n");
   }/*EndLex*/


static void
ExpandVar(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Str*, RestStrPtr),
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Str*, RestStrPtr)
   GMC_DCL(tp_Str, Str)
{
   tp_Str TmpStr, VarStr, ValStr;
   tps_Str VarStrBuf;

   FORBIDDEN(*Str != '$');
   *AbortPtr = FALSE;
   TmpStr = Str;
   VarStr = VarStrBuf;
   for (TmpStr = Str+1; IsWordChr(*TmpStr); TmpStr += 1) {
      *VarStr = *TmpStr; VarStr += 1; }/*while*/;
   *VarStr = 0;
   if (!(IsCmdLex || IsDef_EnvVar(VarStrBuf))) {
      SystemError("Environment variable must be declared in a package.\n");
      *AbortPtr = TRUE;
      return; }/*if*/;
   ValStr = GetEnv(VarStrBuf);
   if (ValStr == NIL) ValStr = "";
   StrShift(Str, strlen(ValStr) - (TmpStr-Str));
   (void)strncpy(Str, ValStr, strlen(ValStr));
   *RestStrPtr = &Str[strlen(ValStr)];
   }/*ExpandVar*/


static void
ExpandHome(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Str, Str)
{
   tp_Str TmpStr, HomeStr, ValStr;
   tps_Str HomeStrBuf;

   FORBIDDEN(*Str != '~');
   *AbortPtr = FALSE;
   if (!IsCmdLex) {
      SystemError("Cannot use ~ in Odinfile filenames.\n");
      *AbortPtr = TRUE;
      return; }/*if*/;
   TmpStr = Str;
   HomeStr = HomeStrBuf;
   for (TmpStr = Str+1; IsWordChr(*TmpStr); TmpStr += 1) {
      *HomeStr = *TmpStr; HomeStr += 1; }/*while*/;
   *HomeStr = 0;
   ValStr = GetHome(HomeStrBuf);
   if (ValStr == NIL) {
      SystemError("Home directory ~%s not found.\n", HomeStrBuf);
      *AbortPtr = TRUE;
      return; }/*if*/;
   StrShift(Str, strlen(ValStr) - (TmpStr-Str));
   (void)strncpy(Str, ValStr, strlen(ValStr));
   }/*ExpandHome*/


int
Lex(GMC_ARG_VOID)
{
   tps_Str Str;
   tp_Str RestStr;
   int iStr;
   tp_Sym Sym;
   boolean Abort;

   PrevParseStr = ParseStr;
   while (TRUE) {
      switch (*ParseStr) {
	 case 0: {
	    return EOFTOK;
	    break;}/*case*/;
	 case ' ': case '\t': {
	    ParseStr += 1;
	    break;}/*case*/;
	 case '\n': {
	    ParseStr += 1;
	    if (ParseLNPtr != NIL) *ParseLNPtr = *ParseLNPtr + 1;
	    break;}/*case*/;
	 case '#': {
	    while (*ParseStr != 0 && *ParseStr != '\n') ParseStr += 1;
	    break;}/*case*/;
         case '(': {
	    ParseStr += 1;
	    return LPAREN;
	    break;}/*case*/;
         case ')': {
	    ParseStr += 1;
	    return RPAREN;
	    break;}/*case*/;
         case ':': {
	    ParseStr += 1;
	    return COLON;
	    break;}/*case*/;
         case '=': {
	    ParseStr += 1;
	    return EQUALS;
	    break;}/*case*/;
         case '/': {
	    ParseStr += 1;
	    return SLASH;
	    break;}/*case*/;
         case '+': {
	    ParseStr += 1;
	    return PLUS;
	    break;}/*case*/;
         case '<': {
	    ParseStr += 1;
	    return LANGLE;
	    break;}/*case*/;
         case '>': {
	    ParseStr += 1;
	    return RANGLE;
	    break;}/*case*/;
         case ';': {
	    ParseStr += 1;
	    return SCOLON;
	    break;}/*case*/;
         case '?': {
	    ParseStr += 1;
	    return QUESMK;
	    break;}/*case*/;
         case '%': {
	    ParseStr += 1;
	    return PERCNT;
	    break;}/*case*/;
         case '!': {
	    ParseStr += 1;
	    while (*ParseStr == ' ' || *ParseStr == '\t'
		   || *ParseStr == '\n') {
	       if (*ParseStr == '\n' && ParseLNPtr != NIL) {
		  *ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
	       ParseStr += 1; }/*while*/;
	    if (*ParseStr == ':' || *ParseStr == '=' || *ParseStr == '<'
		|| *ParseStr == ';' || *ParseStr == 0) {
	       return EXCLPT; }/*if*/;
	    if (*ParseStr == '\\') {
	       ParseStr += 1; }/*if*/;
	    iStr = 0;
	    while (*ParseStr != 0) {
	       if (*ParseStr == '\n' && ParseLNPtr != NIL) {
		  *ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
	       Str[iStr] = *ParseStr; iStr += 1;
	       ParseStr += 1; }/*while*/;
	    Str[iStr] = 0;
	    Sym = Str_Sym(Str);
	    Push_SymStack(Sym);
	    return HOSTWD;
	    break;}/*case*/;
	 case '$': {
	    ExpandVar(&Abort, &RestStr, ParseStr);
	    if (Abort) {
	       ParseStr += 1;
	       return ERRTOK; }/*if*/;
	    break;}/*case*/;
	 case '~': {
	    ExpandHome(&Abort, ParseStr);
	    if (Abort) {
	       ParseStr += 1;
	       return ERRTOK; }/*if*/;
	    break;}/*case*/;
	 default: {
	    iStr = 0;
	    if (ParseStr[0] == '\\' && ParseStr[1] == '0') {
	       ParseStr += 2;
	       if (!isdigit(*ParseStr)) {
		  ParseError("Object-ID expected following \\0");
		  return ERRTOK; }/*if*/;
	       while (isdigit(*ParseStr)) {
		  Str[iStr] = *ParseStr; iStr += 1;
		  ParseStr += 1; }/*while*/;
	       Str[iStr] = 0;
	       Sym = Str_Sym(Str);
	       Push_SymStack(Sym);
	       return OBJTID; }/*if*/;
	    while (TRUE) {
	       /*select*/{
		  if (IsWordChr(*ParseStr)) {
		     Str[iStr] = *ParseStr; iStr += 1;
		     ParseStr += 1;
		  }else if (*ParseStr == '\\') {
		     ParseStr += 1;
		     if (*ParseStr == 0) {
			ParseError("backslash followed by EOF");
			return ERRTOK; }/*if*/;
		     if (*ParseStr == '\n' && ParseLNPtr != NIL) {
			*ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
		     Str[iStr] = *ParseStr; iStr += 1;
		     ParseStr += 1;
		  }else if (*ParseStr == '\'') {
		     ParseStr += 1;
		     while (*ParseStr != '\'') {
			if (*ParseStr == '\\') {
			   ParseStr += 1; }/*if*/;
			if (*ParseStr == 0) {
			   ParseError("Unterminated string");
			   return ERRTOK; }/*if*/;
			if (*ParseStr == '\n' && ParseLNPtr != NIL) {
			   *ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
			Str[iStr] = *ParseStr; iStr += 1;
			ParseStr += 1; }/*while*/;
		     ParseStr += 1;
		     if (*ParseStr == '$') {
			ExpandVar(&Abort, &RestStr, ParseStr);
			if (Abort) {
			   ParseStr += 1;
			   return ERRTOK; }/*if*/;
			while (ParseStr != RestStr) {
			   Str[iStr] = *ParseStr; iStr += 1;
			   ParseStr += 1; }/*while*/; }/*if*/;
		  }else if (*ParseStr == '$') {
		     ExpandVar(&Abort, &RestStr, ParseStr);
		     if (Abort) {
			ParseStr += 1;
			return ERRTOK; }/*if*/;
		  }else{
		     Str[iStr] = 0;
		     Sym = Str_Sym(Str);
		     Push_SymStack(Sym);
		     return WORDTK;
		     };}/*select*/; }/*while*/; };}/*switch*/; }/*while*/;
   /*NOTREACHED*/
   }/*Lex*/


boolean
IsWordChr(
   GMC_ARG(char, Chr)
   )
   GMC_DCL(char, Chr)
{
   switch (Chr) {
      case '\0': case ' ': case '\t': case '\n': case '#':
      case ';': case '?': case '!': case '%': case '<': case '>':
      case '(': case ')': case ':': case '=': case '/': case '+':
      case '\\': case '\'': case '$': {
	 return FALSE;
	 break;}/*case*/;
      default: {
	 return TRUE; };}/*switch*/;
/* NOTREACHED */
   }/*IsWordChr*/


void
Unlex(
   GMC_ARG(tp_Str, OutStr),
   GMC_ARG(tp_Str, InStr)
   )
   GMC_DCL(tp_Str, OutStr)
   GMC_DCL(tp_Str, InStr)
{
   if (*InStr == 0) {
      (void)strcpy(OutStr, "''");
      return; }/*if*/;
   if (*InStr == '~' || !IsWordChr(*InStr)) *OutStr++ = '\\';
   *OutStr++ = *InStr++;
   while (*InStr != 0) {
      if (!IsWordChr(*InStr)) *OutStr++ = '\\';
      *OutStr++ = *InStr++; }/*while*/;
   *OutStr = 0;
   }/*Unlex*/


void
Print_Unlex(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, InStr)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, InStr)
{
   if (*InStr == 0) {
      Write(FilDsc, "''");
      return; }/*if*/;
   if (*InStr == '~' || !IsWordChr(*InStr)) Writech(FilDsc, '\\');
   Writech(FilDsc, *InStr++);
   while (*InStr != 0) {
      if (!IsWordChr(*InStr)) Writech(FilDsc, '\\');
      Writech(FilDsc, *InStr++); }/*while*/;
   }/*Print_Unlex*/


