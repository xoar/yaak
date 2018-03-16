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


tp_Str		Author = "geoff@cs.colorado.edu";


int
main(argc, argv)
   int argc;
   char **argv;
{
   tp_Package Pkg;
   tps_Str StrBuf;
   tp_FilDsc FilDsc;

   DumpCore = (getenv("DUMPCORE") != 0);
   Init_IO();
   Init_Err();
   Init_Parse();
   Init_EnvVars();
   Init_FilTyps();
   Init_PrmTyps();
   Init_Tools();
   Init_InpSpcs();
   if (argc < 4 || argc > 4) {
      SystemError("Usage: dg.exe PKGS ToolDir SkipFlag \n");
      exit(102); }/*if*/;
   FilDsc = FileName_RFilDsc(argv[1], FALSE);
   for (Pkg=Readln(StrBuf, FilDsc); Pkg!=NIL; Pkg=Readln(StrBuf, FilDsc)) {
      Build_DerivationGraph(argv[2], Sym_Str(Str_Sym(Pkg))); }/*for*/;
   Write_ENV();
   if (strcmp (argv[3], "1") == 0) {
      exit(0); }/*if*/;
   Set_FTClasses();
   Make_DrvEdgs();
   Make_PrmTypLsts();
   Validate_DerivationGraph();
   if (Num_Errors() > 0) {
      exit(1); }/*if*/;
   Print_Info(StdOutFD);
   Write_DerivationGraph();
   return 0;
   }/*main*/


