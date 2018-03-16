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

int errno;

extern int *IPC_IArg1, *IPC_IArg2, *IPC_IArg3;
extern tp_Str IPC_SArg1, IPC_SArg2, IPC_SArg3;
extern int yydebug, ocdebug;

extra(
   GMC_ARG(tp_FilHdr, FilHdr),
   GMC_ARG(tp_Sym, Sym),
   GMC_ARG(tp_Nod, Nod)
   )
   GMC_DCL(tp_FilHdr, FilHdr)
   GMC_DCL(tp_Sym, Sym)
   GMC_DCL(tp_Nod, Nod)
{
   yydebug = 0; ocdebug = 0;
   IPC_IArg1 = IPC_IArg3; IPC_SArg2 = IPC_SArg3;
   (void)Num_Errors();
   Set_Nod_NodTyp(Nod, 0);
   Set_Nod_FirstSon(Nod, Nod_FirstSon(Nod));
   Set_Nod_Brother(Nod, Nod_Brother(Nod));
   Set_Nod_Sym(Nod, Sym);
   Set_Sym_Att(Sym, Sym_Att(Sym));
   Rewind((tp_FilDsc)0); SymLink(IPC_IArg1, "", "");
   printte((tp_LocHdr)0);
   extra(FilHdr, Sym, Nod);
   }/*extra*/


