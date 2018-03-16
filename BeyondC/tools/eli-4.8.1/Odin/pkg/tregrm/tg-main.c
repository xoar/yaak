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

tp_Str		Author = "geoff@cs.colorado.edu";


#define		MAX_Dummys 100


int
main()
{
   tp_Nod Root, Includes_Nod, Scanner_Nod, Nodes_Nod, Rules_Nod;
   tp_FilDsc FilDsc;

   DumpCore = (getenv("DUMPCORE") != 0);

   Init_IO();
   Init_Err();

   Root = YY_Parse();
   if (Num_Errors() > 0) return 101;

   Includes_Nod = Nod_Son(1, Root);
   Scanner_Nod = Nod_Son(2, Root);
   Nodes_Nod = Nod_Son(3, Root);
   Rules_Nod = Nod_Son(4, Root);

   Analyze(Scanner_Nod, Nodes_Nod, Rules_Nod);
   if (Num_Errors() > 0) return 102;

   FilDsc = FileName_WFilDsc("LEX_TAB", FALSE);
   Gen_LexTypes(FilDsc, Scanner_Nod);
   Close(FilDsc);
   if (Num_Errors() > 0) return 103;

   FilDsc = FileName_WFilDsc("NOD_TAB", FALSE);
   Gen_NodeTypes(FilDsc, Nodes_Nod);
   Close(FilDsc);
   if (Num_Errors() > 0) return 104;

   FilDsc = FileName_WFilDsc("GRM_TAB", FALSE);
   Gen_Grammar(FilDsc, Includes_Nod, Scanner_Nod, Rules_Nod);
   Close(FilDsc);
   if (Num_Errors() > 0) return 105;

   Write_Node_Grammar(StdOutFD, Rules_Nod);
   if (Num_Errors() > 0) return 106;

   return 0;
   }/*main*/


