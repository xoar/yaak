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
#include "inc/AttTyp_.h"
#include "inc/Lex_.h"
#include "inc/NodTyp_.h"


#define				MAX_Dummys 100


void
Gen_Grammar(FilDsc, Includes_Nod, Scanner_Nod, Rules_Nod)
   tp_FilDsc FilDsc;
   tp_Nod Includes_Nod, Scanner_Nod, Rules_Nod;
{
   tp_Nod Include_Nod, LexDef_Nod, LexName_Nod;
   tp_Nod Rule_Nod, Name_Nod, AltList_Nod, Alternative_Nod;
   tp_Nod NodeName_Nod, Node;
   tp_Sym Symbol;
   tp_Str Str;
   int i, i1, Num;
   int Offset, NumSons;
   int NodeType;

   Writeln(FilDsc, "%{");
   for (i=1; i<=Nod_NumSons(Includes_Nod); i++) {
      Include_Nod = Nod_Son(i, Includes_Nod);
      Write(FilDsc, "#include ");
      Write(FilDsc, ((Nod_NodTyp(Include_Nod) == KSTRNG) ? "\"" : "<"));
      Write(FilDsc, Sym_Str(Nod_Sym(Include_Nod)));
      Writeln(FilDsc, ((Nod_NodTyp(Include_Nod) == KSTRNG) ? "\"" : ">"));
      }/*for*/;
   Writeln(FilDsc, "extern int num_ParseErrors;");
   Writeln(FilDsc, "tp_Nod YY_Parse() {tp_Nod Nod;");
   Writeln(FilDsc, "num_ParseErrors = 0; Init_Lex(); Init_ConstructTree();");
   Writeln(FilDsc, "(void)yyparse(); Nod = End_ConstructTree();");
   Writeln(FilDsc, "return Nod;}");
   Writeln(FilDsc, "void yyerror(GMC_ARG(char*, s)) GMC_DCL(char*, s) ");
   Writeln(FilDsc, "{num_ParseErrors++; ParseError(s);}");
   Writeln(FilDsc, "int yylex() {return YY_Lex();}");
   Writeln(FilDsc, "%}\n");

   Writeln(FilDsc, "%token");
   Num = 2;
   for (i=1; i<=Nod_NumSons(Scanner_Nod); i++) {
      LexDef_Nod = Nod_Son(i, Scanner_Nod);
      if (Is_UserLeafDef(LexDef_Nod)) {
	 LexName_Nod = Nod_Son(2, LexDef_Nod);
	 Write(FilDsc, Sym_Str(Nod_Sym(LexName_Nod)));
	 Write(FilDsc, " ");
	 WriteInt(FilDsc, Num);
	 Num += 1;
	 Writeln(FilDsc, ""); }/*if*/; }/*for*/;
   Write(FilDsc, "\n%%");

   for (i=1; i<=Nod_NumSons(Rules_Nod); i++) {
      Rule_Nod = Nod_Son(i, Rules_Nod);
      Name_Nod = Nod_Son(1, Rule_Nod);
      Symbol = Nod_Sym(Name_Nod);
      Offset = 0;
      Gen_LHS(FilDsc, Symbol, Offset);
      AltList_Nod = Nod_Son(2, Rule_Nod);
      for (i1=1; i1<Nod_NumSons(AltList_Nod); i1++) {
	 Alternative_Nod = Nod_Son(i1, AltList_Nod);
	 NumSons = 0;
	 Gen_Seq(FilDsc, Nod_Son(1, Alternative_Nod), Symbol, TRUE, &Offset, &NumSons);
	 Gen_Act(FilDsc, Alternative_Nod, NumSons);
	 Writeln(FilDsc, "|"); }/*for*/;
      Alternative_Nod = Nod_Son(Nod_NumSons(AltList_Nod), AltList_Nod);
      Node = Nod_Son(1, Alternative_Nod);
      NumSons = 0;
      /*select*/{
	 if (Nod_NumSons(Alternative_Nod) == 1) {
	    Gen_Rule(FilDsc, Node, Symbol, &Offset, &NumSons);
	 }else{
	    Gen_Seq(FilDsc, Node, Symbol, TRUE, &Offset, &NumSons);
	    Gen_Act(FilDsc, Alternative_Nod, NumSons);
	    Writeln(FilDsc, ";");
	    };}/*select*/;

      while (!Empty_DummyStack()) {
	 Pop_DummyStack(&Node, &Offset);
	 Gen_LHS(FilDsc, Symbol, Offset);
	 Offset = Offset * MAX_Dummys;
	 NumSons = 0;
	 Gen_Rule(FilDsc, Node, Symbol, &Offset, &NumSons); 
	 }/*while*/; }/*for*/;
   
   for (i=1; i<=Nod_NumSons(Scanner_Nod); i++) {
      LexDef_Nod = Nod_Son(i, Scanner_Nod);
      if (Nod_NodTyp(LexDef_Nod) == LEAFDF) {
	 LexName_Nod = Nod_Son(1, LexDef_Nod);
	 Str = Sym_Str(Get_Att(ATP_LexType, Nod_Sym(LexName_Nod)).Sym);
	 Write(FilDsc, "\n ");
	 Write(FilDsc, Str);
	 Write(FilDsc, "leaf : ");
	 Write(FilDsc, Str);
	 NodeName_Nod = Nod_Son(3, LexDef_Nod);
	 NodeType = Get_Att(ATP_Nodes, Nod_Sym(NodeName_Nod)).Int;
	 if (NodeType == 0) {
	    Increment_Errors();
	    Str = Sym_Str(Nod_Sym(NodeName_Nod));
	    SystemError("Tree node \"%s\" not declared.\n", Str); }/*if*/;
	 Write_Act(FilDsc, NodeType, -1);
	 Writeln(FilDsc, ";"); }/*if*/; }/*for*/;

   Writeln(FilDsc, "\n%%");
   }/*Gen_Grammar*/


void
Gen_LHS(FilDsc, Symbol, Offset)
   tp_FilDsc FilDsc;
   tp_Sym Symbol;
   int Offset;
{
   Write(FilDsc, "\n x");
   Write(FilDsc, Sym_Str(Symbol));
   if (Offset > 0) {
      Write(FilDsc, "_");
      WriteInt(FilDsc, Offset); }/*if*/;
   Writeln(FilDsc, " :");
   }/*Gen_LHS*/


void
Gen_Rule(FilDsc, Node, Symbol, Offset_Ptr, NumSons_Ptr)
   tp_FilDsc FilDsc;
   tp_Nod Node;
   tp_Sym Symbol;
   int *Offset_Ptr, *NumSons_Ptr;
{
   tp_Nod nodson, ndson1, ndson2;
   int ioftmp;

   switch (Nod_NodTyp(Node)) {
      case SEQ: case NAME: case DSTRNG: case KSTRNG: {
	 Gen_Seq(FilDsc, Node, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Writeln(FilDsc, ";");
	 break;}/*case*/;
      case PLUS: {
	 Write(FilDsc, "\n    ");
	 Gen_DummySym(FilDsc, Symbol, *Offset_Ptr/MAX_Dummys);
	 *NumSons_Ptr = 1;
	 nodson = Nod_Son(1, Node);
	 ioftmp = *Offset_Ptr;
	 Gen_Seq(FilDsc, nodson, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Write(FilDsc, "|\n    ");
	 *NumSons_Ptr = 0;
	 Gen_Seq(FilDsc, nodson, Symbol, FALSE, &ioftmp, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Writeln(FilDsc, ";");
	 break;}/*case*/;
      case STAR: {
	 Write(FilDsc, "\n    ");
	 Gen_DummySym(FilDsc, Symbol, *Offset_Ptr/MAX_Dummys);
	 *NumSons_Ptr = 1;
	 nodson = Nod_Son(1, Node);
	 ioftmp = *Offset_Ptr;
	 Gen_Seq(FilDsc, nodson, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Write(FilDsc, "|\n\n    ");
	 Write_Act(FilDsc, 0, 0);
	 Writeln(FilDsc, ";");
	 break;}/*case*/;
      case QUESTION: {
	 Write(FilDsc, "\n    ");
	 *NumSons_Ptr = 0;
	 nodson = Nod_Son(1, Node);
	 ioftmp = *Offset_Ptr;
	 Gen_Seq(FilDsc, nodson, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Write(FilDsc, "|\n\n    ");
	 Write_Act(FilDsc, 0, 0);
	 Writeln(FilDsc, ";");
	 break;}/*case*/;
      case LIST: {
	 Write(FilDsc, "\n    ");
	 Gen_DummySym(FilDsc, Symbol, *Offset_Ptr/MAX_Dummys);
	 *NumSons_Ptr = 1;
	 ndson1 = Nod_Son(1, Node);
	 ndson2 = Nod_Son(2, Node);
	 Gen_Seq(FilDsc, ndson2, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 ioftmp = *Offset_Ptr;
	 Gen_Seq(FilDsc, ndson1, Symbol, TRUE, Offset_Ptr, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Write(FilDsc, "|\n    ");
	 *NumSons_Ptr = 0;
	 Gen_Seq(FilDsc, ndson1, Symbol, FALSE, &ioftmp, NumSons_Ptr);
	 Write_Act(FilDsc, 0, *NumSons_Ptr);
	 Writeln(FilDsc, ";");
	 break;}/*case*/;
      default: {
	 fatal_err("illegal node type in Gen"); };}/*switch*/;
   }/*Gen_Rule*/


void
Gen_Seq(FilDsc, Node, Symbol, ensymf, Offset_Ptr, NumSons_Ptr)
   tp_FilDsc FilDsc;
   tp_Nod Node;
   tp_Sym Symbol;
   boolean ensymf;
   int *Offset_Ptr, *NumSons_Ptr;
{
   int i;

   if (Nod_NodTyp(Node) != SEQ) {
      Gen_Token(FilDsc, Node, Symbol, ensymf, Offset_Ptr, NumSons_Ptr);
      return; }/*if*/;

   for (i=1; i<=Nod_NumSons(Node); i++) {
      Gen_Token(FilDsc, Nod_Son(i, Node), Symbol, ensymf, Offset_Ptr, NumSons_Ptr);
      }/*for*/;
   }/*Gen_Seq*/


void
Gen_Token(FilDsc, Node, Symbol, ensymf, Offset_Ptr, NumSons_Ptr)
   tp_FilDsc FilDsc;
   tp_Nod Node;
   tp_Sym Symbol;
   boolean ensymf;
   int *Offset_Ptr, *NumSons_Ptr;
{
   tp_Str Str;
   tp_Sym Sym;

   Write(FilDsc, "\n    ");
   switch(Nod_NodTyp(Node)) {
      case NAME: {
	 Sym = Nod_Sym(Node);
	 Str = Sym_Str(Sym);
	 if (Get_Att(ATP_NonTerminal, Sym).Int == 0) {
	    Increment_Errors();
	    SystemError("Nonterminal \"%s\" not defined.\n", Str); }/*if*/;
	 Write(FilDsc, "x");
	 Write(FilDsc, Str);
	 *NumSons_Ptr += 1; 
	 break;}/*case*/;
      case DSTRNG: {
	 Sym = Nod_Sym(Node);
	 if (Get_Att(ATP_Lexical, Sym).Int != LX_NonLeaf) {
	    Increment_Errors();
	    SystemError("\"%s\" used but not defined as a non-leaf token.\n",
			Sym_Str(Sym)); }/*if*/;
	 Write(FilDsc, Sym_Str(Get_Att(ATP_LexType, Sym).Sym));
	 break;}/*case*/;
      case KSTRNG: {
	 Sym = Nod_Sym(Node);
	 if (Get_Att(ATP_Lexical, Sym).Int != LX_Leaf) {
	    Increment_Errors();
	    SystemError("\"%s\" used but not defined as a leaf token.\n",
			Sym_Str(Sym)); }/*if*/;
	 Write(FilDsc, Sym_Str(Get_Att(ATP_LexType, Sym).Sym));
	 Write(FilDsc, "leaf");
	 *NumSons_Ptr += 1;
	 break;}/*case*/;
      case SEQ: case PLUS: case STAR: case QUESTION: case LIST: {
	 *Offset_Ptr += 1;
	 if (*Offset_Ptr % MAX_Dummys == 0) {
	    Increment_Errors();
	    Str = Sym_Str(Symbol);
	    SystemError("The rule for \"%s\" is too complex.\n", Str);
	    fatal_err("Dummy Overflow"); }/*if*/;
	 Gen_DummySym(FilDsc, Symbol, *Offset_Ptr);
	 *NumSons_Ptr += 1;
	 if (ensymf) Push_DummyStack(Node, *Offset_Ptr);
	 break;}/*case*/;
      default :{
	 fatal_err("illegal node type in Gen_Token"); };}/*default*/;
   }/*Gen_Token*/


void
Gen_DummySym(FilDsc, Symbol, Offset)
   tp_FilDsc FilDsc;
   tp_Sym Symbol;
   int Offset;
{
   Write(FilDsc, "x");
   Write(FilDsc, Sym_Str(Symbol));
   if (Offset > 0) {
      Write(FilDsc, "_");
      WriteInt(FilDsc, Offset); }/*if*/;
   }/*Gen_DummySym*/


void
Gen_Act(FilDsc, Alternative_Nod, NumSons)
   tp_FilDsc FilDsc;
   tp_Nod Alternative_Nod;
   int NumSons;
{
   tp_Nod NodeName_Nod;
   int NodeType;
   tp_Str Str;

   if (Nod_NumSons(Alternative_Nod) == 1) {
      Write_Act(FilDsc, 0, NumSons);
      return; }/*if*/;

   NodeName_Nod = Nod_Son(2, Alternative_Nod);
   switch (Nod_NodTyp(NodeName_Nod)) {
      case KSTRNG: {
	 NodeType = Get_Att(ATP_Nodes, Nod_Sym(NodeName_Nod)).Int;
	 Write_Act(FilDsc, NodeType, NumSons);
	 break;}/*case*/;
      case OPTNAL: {
	 NodeName_Nod = Nod_Son(1, NodeName_Nod);
	 NodeType = Get_Att(ATP_Nodes, Nod_Sym(NodeName_Nod)).Int;
	 Write_Act(FilDsc, -NodeType, NumSons);
	 break;}/*case*/;
      case OUTNOD: {
	 NodeName_Nod = Nod_Son(1, NodeName_Nod);
	 NodeType = Get_Att(ATP_Nodes, Nod_Sym(NodeName_Nod)).Int;
	 Write_Act(FilDsc, -NodeType, -NumSons);
	 break;}/*case*/;
      default :{
	 fatal_err("illegal node type in Gen_Act");
	 };}/*switch*/;

   if (NodeType == 0) {
      Increment_Errors();
      Str = Sym_Str(Nod_Sym(NodeName_Nod));
      SystemError("Tree Node \"%s\" not declared.\n", Str); }/*if*/;
   }/*Gen_Act*/


void
Write_Act(FilDsc, NodeType, NumSons)
   tp_FilDsc FilDsc;
   int NodeType, NumSons;
{
   if (NodeType == 0 && NumSons == 1) {
      return; }/*if*/;
   Write(FilDsc, " {Action(");
   WriteInt(FilDsc, NodeType);
   Write(FilDsc, ",");
   WriteInt(FilDsc, NumSons);
   Write(FilDsc, ");} ");
   }/*Write_Act*/


void
Write_Lex(FilDsc, Str)
   tp_FilDsc FilDsc;
   tp_Str Str;
{
   tp_Str StrPtr;

   Write(FilDsc, "'.");
   StrPtr = Str;
   for (StrPtr=Str; *StrPtr!=NIL; StrPtr+=1) {
      if (*StrPtr == '\'') Writech(FilDsc, '\\');
      Writech(FilDsc, *StrPtr); }/*for*/;
   Write(FilDsc, "'");
   }/*Write_Lex*/

