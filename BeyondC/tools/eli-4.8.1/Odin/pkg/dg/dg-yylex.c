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
#include "inc/Str.h"
#include "inc/TokTyp_.h"
#include "inc/NodTyp_.h"


tp_FileName	ParseFN;
tp_FilDsc	ParseFD;
int		*ParseLNPtr;
static tp_Str		PrevParseStr;
static tp_Str		ParseStr;

static tps_Str		StrBuf;


void
Init_Parse()
{
   tp_Sym Sym;

   Sym = Str_Sym("BANNER");
   Set_Sym_Att(Sym, TOK_BANNER);
   Sym = Str_Sym("NEEDS");
   Set_Sym_Att(Sym, TOK_NEEDS);
   }/*Init_Parse*/


static void
FileError(Str)
   tp_Str Str;
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
ParseError(Str)
   tp_Str Str;
{
   FileError(Str);
   SystemError(" at <%s>.\n", PrevParseStr);
   }/*ParseError*/


static void
NextChar()
{
   int Length;

   if (*ParseStr == '\0') {
      return; }/*if*/;
   ParseStr += 1;
   if (*ParseStr == '\0') {
      ParseStr = ReadLine(StrBuf, ParseFD);
      PrevParseStr = ParseStr;
      if (ParseStr == NIL) {
	 ParseStr = "";
	 return; }/*if*/;
      Length = strlen(ParseStr);
      ParseStr[Length] = '\n'; ParseStr[Length+1] = '\0'; }/*while*/;
   }/*NextChar*/


void
Init_Lex()
{
   ParseStr = ".";
   NextChar();
   }/*Init_Lex*/


void
EndLex()
{
   SystemError("Unexpected call to EndLex.\n");
   }/*EndLex*/


static boolean
YY_IsWordChr(Chr)
   char Chr;
{
   switch (Chr) {
      case '\0': case ' ': case '\t': case '\n': case '#': case '\'':
      case ':': case '+': case '=': case '(': case ')': 
      case '%': case '/': case ';': case '?': case '<': case '>': 
      case '&': case '@': case '*': case '\\': {
	 return FALSE;
	 break;}/*case*/;
      default: {
	 return TRUE; };}/*switch*/;
/* NOTREACHED */
   }/*YY_IsWordChr*/


int
YY_Lex()
{
   tps_Str Str;
   int iStr;
   tp_Sym Sym;
   boolean KeywordFlag;
   int SymTok;

   PrevParseStr = ParseStr;
   while (TRUE) {
      switch (*ParseStr) {
	 case 0: {
	    return TOK_EOF;
	    break;}/*case*/;
	 case ' ': case '\t': {
	    NextChar();
	    break;}/*case*/;
	 case '\n': {
	    NextChar();
	    if (ParseLNPtr != NIL) *ParseLNPtr = *ParseLNPtr + 1;
	    break;}/*case*/;
	 case '#': {
	    while (*ParseStr != '\0' && *ParseStr != '\n') NextChar();
	    break;}/*case*/;
         case ':' :{
	    NextChar();
	    return TOK_Colon;
	    break;}/*case*/;
         case '+' :{
	    NextChar();
	    return TOK_Plus;
	    break;}/*case*/;
         case '=' :{
	    NextChar();
	    return TOK_Equals;
	    break;}/*case*/;
         case '(' :{
	    NextChar();
	    return TOK_LeftParen;
	    break;}/*case*/;
         case ')' :{
	    NextChar();
	    return TOK_RightParen;
	    break;}/*case*/;
         case '%' :{
	    NextChar();
	    return TOK_Percent;
	    break;}/*case*/;
         case '/' :{
	    NextChar();
	    return TOK_Slash;
	    break;}/*case*/;
         case ';' :{
	    NextChar();
	    return TOK_Semicolon;
	    break;}/*case*/;
         case '?' :{
	    NextChar();
	    return TOK_Question;
	    break;}/*case*/;
         case '<' :{
	    NextChar();
	    return TOK_LeftAngle;
	    break;}/*case*/;
         case '>' :{
	    NextChar();
	    return TOK_RightAngle;
	    break;}/*case*/;
         case '&' :{
	    NextChar();
	    return TOK_Ampersand;
	    break;}/*case*/;
         case '@' :{
	    NextChar();
	    return TOK_At;
	    break;}/*case*/;
         case '*' :{
	    NextChar();
	    return TOK_Asterisk;
	    break;}/*case*/;
         case '$' :{
	    NextChar();
	    return TOK_Dollar;
	    break;}/*case*/;
	 default: {
	    KeywordFlag = TRUE;
	    iStr = 0;
	    while (TRUE) {
	       /*select*/{
		  if (YY_IsWordChr(*ParseStr)) {
		     Str[iStr] = *ParseStr; iStr += 1;
		     NextChar();
		  }else if (*ParseStr == '\\') {
		     KeywordFlag = FALSE;
		     NextChar();
		     if (*ParseStr == '\0') {
			ParseError("backslash followed by EOF");
			return TOK_ERR; }/*if*/;
		     if (*ParseStr == '\n' && ParseLNPtr != NIL) {
			*ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
		     Str[iStr] = *ParseStr; iStr += 1;
		     NextChar();
		  }else if (*ParseStr == '\'') {
		     KeywordFlag = FALSE;
		     NextChar();
		     while (*ParseStr != '\'') {
			if (*ParseStr == '\\') {
			   NextChar(); }/*if*/;
			if (*ParseStr == '\0') {
			   ParseError("Unterminated string");
			   return TOK_ERR; }/*if*/;
			if (*ParseStr == '\n' && ParseLNPtr != NIL) {
			   *ParseLNPtr = *ParseLNPtr + 1; }/*if*/;
			Str[iStr] = *ParseStr; iStr += 1;
			NextChar(); }/*while*/;
		     NextChar();
		  }else{
		     Str[iStr] = '\0';
		     Sym = Str_Sym(Str);
		     if (KeywordFlag) {
			SymTok = Sym_Att(Sym);
			if (SymTok != 0) {
			   return SymTok; }/*if*/; }/*if*/;
		     Push_SymStack(Sym);
		     return TOK_Word;
		     };}/*select*/; }/*while*/; };}/*switch*/; }/*while*/;
   }/*YY_Lex*/


static void
Unlex(OutStr, InStr)
   tp_Str OutStr, InStr;
{
   if (*InStr == 0) {
      (void)strcpy(OutStr, "''");
      return; }/*if*/;
   if (*InStr == '~' || !YY_IsWordChr(*InStr)) *OutStr++ = '\\';
   *OutStr++ = *InStr++;
   while (*InStr != 0) {
      if (!YY_IsWordChr(*InStr)) *OutStr++ = '\\';
      *OutStr++ = *InStr++; }/*while*/;
   *OutStr = 0;
   }/*Unlex*/


void
YY_Unparse(Str, Nod)
   tp_Str Str;
   tp_Nod Nod;
{
   tp_Nod Son;
   tp_Str SubStr;

   switch (Nod_NodTyp(Nod)) {
      case NOD_OdinExpr: case NOD_Oprs: {
	 (void)strcpy(Str, "(");
	 Son = Nod_Son(1, Nod);
	 YY_Unparse(Tail(Str), Son);
	 for (Son = Nod_Brother(Son), SubStr = Tail(Str);
	      Son != NIL;
	      Son = Nod_Brother(Son), SubStr = Tail(SubStr)) {
	    YY_Unparse(SubStr, Son); }/*for*/;
	 (void)strcat(SubStr, ")");
	 break; }/*case*/;
      case NOD_VarWord: {
	 (void)strcpy(Str, "$");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case NOD_Word: {
	 Unlex(Str, Sym_Str(Nod_Sym(Nod)));
	 break; }/*case*/;
      case NOD_EmptyFile: {
	 (void)strcpy(Str, "()");
	 break; }/*case*/;
      case NOD_AbsRoot: {
	 (void)strcpy(Str, "/");
	 break; }/*case*/;
      case NOD_AbsFile: {
	 (void)strcpy(Str, "/");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case NOD_PrmInput: {
	 (void)strcpy(Str, "+");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case NOD_PrmOpr: {
	 (void)strcpy(Str, "+");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 if (Nod_NumSons(Nod) > 1) {
	    (void)strcpy(Tail(Str), "=");
	    YY_Unparse(Tail(Str), Nod_Son(2, Nod)); }/*if*/;
	 break; }/*case*/;
      case NOD_AplOpr: {
	 (void)strcpy(Str, "+(");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 (void)strcat(Str, ")");
	 break; }/*case*/;
      case NOD_PrmVals: {
	 YY_Unparse(Str, Nod_Son(1, Nod));
	 for (Son = Nod_Son(2, Nod); Son != NIL; Son = Nod_Brother(Son)) {
	    (void)strcpy(Tail(Str), " ");
	    YY_Unparse(Tail(Str), Son); }/*for*/;
	 break; }/*case*/;
      case NOD_DrvInput: case NOD_DrvOpr: {
	 (void)strcpy(Str, ":");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case NOD_SecOrdDrvOpr: {
	 (void)strcpy(Str, ":");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 (void)strcpy(Tail(Str), "=:");
	 YY_Unparse(Tail(Str), Nod_Son(2, Nod));
	 break; }/*case*/;
      case NOD_SelOpr: {
	 (void)strcpy(Str, "/");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break; }/*case*/;
      case NOD_VirSelOpr: {
	 (void)strcpy(Str, "%");
	 YY_Unparse(Tail(Str), Nod_Son(1, Nod));
	 break;}/*case*/;
      case NOD_DirOpr: {
	 (void)strcpy(Str, "/");
	 break; }/*case*/;
      default: {
	 FATALERROR("Unexpected NodTyp"); };}/*switch*/;
   }/*YY_Unparse*/
