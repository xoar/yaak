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


void
Analyze(Scanner_Nod, Nodes_Nod, Rules_Nod)
   tp_Nod Scanner_Nod, Nodes_Nod, Rules_Nod;
{
   tp_Nod LexDef_Nod, Lex_Nod, LexType_Nod;
   tp_Nod NodeType_Nod, Rule_Nod, Name_Nod;
   tp_Sym Lex_Sym, Sym;
   tp_Att Attrib;
   int i;

   Reset_Att(ATP_Declared);
   Reset_Att(ATP_Lexical);
   for (i=1; i<=Nod_NumSons(Scanner_Nod); i++) {
      LexDef_Nod = Nod_Son(i, Scanner_Nod);
      if (Is_UserLeafDef(LexDef_Nod)) {
	 Lex_Nod = Nod_Son(1, LexDef_Nod);
	 Lex_Sym = Nod_Sym(Lex_Nod);
	 LexType_Nod = Nod_Son(2, LexDef_Nod);
	 Sym = Nod_Sym(LexType_Nod);

	 Attrib.Int = LX_NonLeaf;
	 if (Nod_NumSons(LexDef_Nod) == 3) Attrib.Int = LX_Leaf;
	 Set_Att(ATP_Lexical, Nod_Sym(Lex_Nod), Attrib);

	 if (Get_Att(ATP_Declared, Sym).Int == 1) {
	    Increment_Errors();
	    SystemError("Lexical type \"%s\" already declared.\n",
			Sym_Str(Sym)); }/*if*/;
	 Attrib.Int = 1;
	 Set_Att(ATP_Declared, Sym, Attrib);

	 if (Get_Att(ATP_LexType, Lex_Sym).Int != 0) {
	    Increment_Errors();
	    SystemError("Lexical symbol \"%s\" already declared.\n",
			Sym_Str(Lex_Sym)); }/*if*/;
	 Attrib.Sym = Sym;
	 Set_Att(ATP_LexType, Lex_Sym, Attrib); }/*if*/; }/*for*/;

   Reset_Att(ATP_Nodes);
   for (i=1; i<=Nod_NumSons(Nodes_Nod); i++) {
      NodeType_Nod = Nod_Son(i, Nodes_Nod);
      Attrib.Int = i;
      Set_Att(ATP_Nodes, Nod_Sym(NodeType_Nod), Attrib); }/*for*/;
   
   Reset_Att(ATP_NonTerminal);
   for (i=1; i<=Nod_NumSons(Rules_Nod); i++) {
      Rule_Nod = Nod_Son(i, Rules_Nod);
      Name_Nod = Nod_Son(1, Rule_Nod);
      Attrib.Int = i;
      Set_Att(ATP_NonTerminal, Nod_Sym(Name_Nod), Attrib); }/*for*/;
   }/*Analyze*/


