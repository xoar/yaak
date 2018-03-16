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

#include <stdio.h>

#include "inc/GMC.h"
#include "inc/Str.h"
#include "inc/AttTyp_.h"
#include "inc/TokTyp_.h"


int	NextChar;

boolean	LastEOL;
int	LineNum;
int	TokNum;


int
GetChar()
{
   int Ch;

   if (LastEOL) {
      LineNum += 1;
      TokNum = 0;
      LastEOL = FALSE; }/*if*/;
   Ch = getchar();
   if (Ch == '\n') LastEOL = TRUE;
   return Ch;
   }/*GetChar*/


void
Init_Lex()
{
   tp_Sym Sym;
   tp_Att Attribute;

   LineNum = 0;
   TokNum = 0;
   LastEOL = TRUE;
   NextChar = GetChar();

   Sym = Str_Sym("EOF"); Attribute.Int = TOK_EOF_;
   Set_Att(ATP_Keyword, Sym, Attribute);
   Sym = Str_Sym("ERR"); Attribute.Int = TOK_ERR_;
   Set_Att(ATP_Keyword, Sym, Attribute);
   Sym = Str_Sym("INCLUDE"); Attribute.Int = TOK_INCLUDE;
   Set_Att(ATP_Keyword, Sym, Attribute);
   Sym = Str_Sym("SCANNER"); Attribute.Int = TOK_SCANNER;
   Set_Att(ATP_Keyword, Sym, Attribute);
   Sym = Str_Sym("NODES"); Attribute.Int = TOK_NODES;
   Set_Att(ATP_Keyword, Sym, Attribute);
   Sym = Str_Sym("RULES"); Attribute.Int = TOK_RULES;
   Set_Att(ATP_Keyword, Sym, Attribute);
   }/*Init_Lex*/


void
EndLex()
{
   SystemError("Unexpected call to EndLex");
   }/*EndLex*/


int
YY_Lex()
{
   int Chr;
   tps_Str Str;
   int iStr;
   tp_Sym Sym;
   int SymTok;

   TokNum += 1;
   while (TRUE) {
      Chr = NextChar;
      if (Chr != EOF) NextChar = GetChar();
      switch (Chr) {
	 case EOF :{
	    return TOK_EOF;
	    break;}/*case*/;
	 case ' ' : case '\t' : case '\n' :{
	    break;}/*case*/;
	 case '#' :{
	    while (NextChar != '\n' && NextChar != EOF) NextChar = GetChar();
	    if (NextChar == EOF) ParseError("Unterminated comment");
	    break;}/*case*/;
         case '=' :{
	    if (NextChar == '>') {
	       NextChar = GetChar();
	       return TOK_DoubleArrow; }/*if*/;
	    return TOK_Equals;
	    break;}/*case*/;
         case '-' :{
	    if (NextChar != '>') {
	       return TOK_ERR; }/*if*/;
	    NextChar = GetChar();
	    return TOK_SingleArrow;
	    break;}/*case*/;
         case '+' :{
	    return TOK_Plus;
	    break;}/*case*/;
         case '*' :{
	    return TOK_Star;
	    break;}/*case*/;
         case '/' :{
	    if (NextChar != '/') {
	       return TOK_ERR; }/*if*/;
	    NextChar = GetChar();
	    return TOK_DoubleSlash;
	    break;}/*case*/;
         case ';' :{
	    return TOK_SemiColon;
	    break;}/*case*/;
         case '?' :{
	    return TOK_Question;
	    break;}/*case*/;
         case '(' :{
	    return TOK_LeftParen;
	    break;}/*case*/;
         case ')' :{
	    return TOK_RightParen;
	    break;}/*case*/;
	 case '\\' :{
	    /*select*/{
	       if (NextChar == '\n') {
		  NextChar = GetChar();
	       }else{
		  ParseError("\\ should be followed by <CR>");
		  };}/*select*/;
	    break;}/*case*/;
	 case '\'' :{
	    iStr = 0;
	    while (NextChar != '\'' && NextChar != EOF) {
	       if (NextChar == '\\') {
		  NextChar = GetChar();
		  if (NextChar == EOF) {
		     ParseError("Unterminated string");
		     return TOK_ERR; }/*if*/; }/*if*/;
	       Str[iStr] = NextChar; iStr += 1;
	       NextChar = GetChar(); }/*while*/;
	    if (NextChar == EOF) {
	       ParseError("Unterminated string");
	       return TOK_ERR; }/*if*/;
	    NextChar = GetChar();
	    Str[iStr] = 0;
	    Sym = Str_Sym(Str);
	    Push_SymStack(Sym);
	    return TOK_AString;
	    break;}/*case*/;
	 case '"' :{
	    iStr = 0;
	    while (NextChar != '"' && NextChar != EOF) {
	       if (NextChar == '\\') {
		  NextChar = GetChar();
		  if (NextChar == EOF) {
		     ParseError("Unterminated string");
		     return TOK_ERR; }/*if*/; }/*if*/;
	       Str[iStr] = NextChar; iStr += 1;
	       NextChar = GetChar(); }/*while*/;
	    if (NextChar == EOF) {
	       ParseError("Unterminated string");
	       return TOK_ERR; }/*if*/;
	    NextChar = GetChar();
	    Str[iStr] = 0;
	    Sym = Str_Sym(Str);
	    Push_SymStack(Sym);
	    return TOK_QString;
	    break;}/*case*/;
	 default :{
	    if (IsNameChr(Chr)) {
	       iStr = 0;
	       Str[iStr] = Chr; iStr += 1;
	       while (NextChar != EOF && IsNameChr(NextChar)) {
		  Str[iStr] = NextChar; iStr += 1;
		  NextChar = GetChar(); }/*while*/;
	       Str[iStr] = 0;
	       Sym = Str_Sym(Str);
	       SymTok = Get_Att(ATP_Keyword, Sym).Int;
	       if (SymTok != 0) {
		  return SymTok; }/*if*/;
	       Push_SymStack(Sym);
	       return TOK_Name; }/*if*/;
	    ParseError("Unexpected character");
	    };}/*switch*/; }/*while*/;
   }/*YY_Lex*/


boolean
IsNameChr(Chr)
   char Chr;
{
   switch (Chr) {
      case 'a' : case 'b' : case 'c' : case 'd' : case 'e' : case 'f' :
      case 'g' : case 'h' : case 'i' : case 'j' : case 'k' : case 'l' :
      case 'm' : case 'n' : case 'o' : case 'p' : case 'q' : case 'r' :
      case 's' : case 't' : case 'u' : case 'v' : case 'w' : case 'x' :
      case 'y' : case 'z' :
      case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : case 'F' :
      case 'G' : case 'H' : case 'I' : case 'J' : case 'K' : case 'L' :
      case 'M' : case 'N' : case 'O' : case 'P' : case 'Q' : case 'R' :
      case 'S' : case 'T' : case 'U' : case 'V' : case 'W' : case 'X' :
      case 'Y' : case 'Z' :
      case '0' : case '1' : case '2' : case '3' : case '4' :
      case '5' : case '6' : case '7' : case '8' : case '9' :
      case '-' : case '_' : case '.' : case '/' : case ',' :{
	 return TRUE;
	 break;}/*case*/;
      default :{
	 return FALSE; };}/*switch*/;
/* NOTREACHED */
   }/*IsNameChr*/


void
ParseError(Str)
   tp_Str Str;
{
   SystemError("%s at line %d, token %d.\n", Str, LineNum, TokNum);
   }/*ParseError*/


