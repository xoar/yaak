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


void
Gen_NodeTypes(FilDsc, Nodes_Nod)
   tp_FilDsc FilDsc;
   tp_Nod Nodes_Nod;
{
   tp_Nod NodeType_Nod;
   int i;

   Write(FilDsc, "#ifndef TP_YYNODTYP\n#define TP_YYNODTYP\n\n");
   for (i=1; i<=Nod_NumSons(Nodes_Nod); i++) {
      NodeType_Nod = Nod_Son(i, Nodes_Nod);
      Write(FilDsc, "#define ");
      Write(FilDsc, Sym_Str(Nod_Sym(NodeType_Nod)));
      Write(FilDsc, " ");
      WriteInt(FilDsc, i);
      Writeln(FilDsc, ""); }/*for*/;
   Write(FilDsc, "\n#endif\n");
   }/*Gen_NodeTypes*/


