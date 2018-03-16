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

#include "inc/GMC.h"

tp_Str		Author = "odin-build-users@lists.sourceforge.net";


main()
{
   tp_Nod Root;
   tp_FilDsc FilDsc;

   DumpCore = (getenv("DUMPCORE") != 0);

   Init_IO();
   Init_Err();

   Root = YY_Parse();
   if (Num_Errors() > 0) return 101;

/*
   Analyze(Root);
   if (Num_Errors() > 0) return 102;
*/

   FilDsc = FileName_WFilDsc("OUT.c"); 
   Gen_OutStub(FilDsc, Root);
   Close(FilDsc);
   if (Num_Errors() > 0) return 103;

   FilDsc = FileName_WFilDsc("IN.c"); 
   Gen_InStub(FilDsc, Root);
   Close(FilDsc);
   if (Num_Errors() > 0) return 104;

   return 0;
   }/*main*/


