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
#include "inc/NodTyp_.h"


void
Gen_LexTypes(FilDsc, Scanner_Nod)
   tp_FilDsc FilDsc;
   tp_Nod Scanner_Nod;
{
   tp_Nod LexDef_Nod;
   int i, Son, Num;

   Writeln(FilDsc, "#ifndef TP_YYTOKTYP\n#define TP_YYTOKTYP\n");
   i = 2;
   for (LexDef_Nod = Nod_Son(1, Scanner_Nod);
	LexDef_Nod != NIL;
	LexDef_Nod = Nod_Brother(LexDef_Nod)) {
      /*select*/{
	 if (Nod_NodTyp(LexDef_Nod) == EOFLDF) {
	    Son = 1; Num = 0;
	 }else if (Nod_NodTyp(LexDef_Nod) == ERRLDF) {
	    Son = 1; Num = 1;
	 }else{
	    Son = 2; Num = i; i += 1; };}/*select*/;
      Write(FilDsc, "#define ");
      Write(FilDsc, Sym_Str(Nod_Sym(Nod_Son(Son, LexDef_Nod))));
      Write(FilDsc, " ");
      WriteInt(FilDsc, Num);
      Writeln(FilDsc, ""); }/*for*/;
   Writeln(FilDsc, "\n#endif");
   }/*Gen_LexTypes*/
   

boolean
Is_UserLeafDef(Nod)
   tp_Nod Nod;
{
   return (Nod_NodTyp(Nod) != EOFLDF && Nod_NodTyp(Nod) != ERRLDF);
   }/*Is_UserLeafDef*/


