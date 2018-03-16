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

typedef tp_Att tps_AttArr [MAX_ATP];
typedef tp_Att * tp_AttArr;

#define MAX_AttS	4000
tps_AttArr AttS [MAX_AttS];
int iAttS = 1;


void
Reset_Att(AttTyp)
   tp_AttTyp AttTyp;
{
   int i;

   if (AttTyp < 1 || AttTyp > MAX_ATP) fatal_err("bad AttTyp");
   for (i=0; i<iAttS; i++) (AttS[i][AttTyp-1]).Int = 0;
   }/*Reset_Att*/


tp_Att
Get_Att(AttTyp, Sym)
   tp_AttTyp AttTyp;
   tp_Sym Sym;
{
   int AttArr;
   tp_Att Null;

   if (AttTyp < 1 || AttTyp > MAX_ATP) fatal_err("bad AttTyp");
   AttArr = Sym_Att(Sym);
   if (AttArr == 0) {
      Null.Nod=(tp_Nod)0;
      return Null; }/*if*/;
   return AttS[AttArr][AttTyp-1];
   }/*Get_Att*/


void
Set_Att(AttTyp, Sym, Att)
   tp_AttTyp AttTyp;
   tp_Sym    Sym;
   tp_Att   Att;
{
   int AttArr;

   if (AttTyp < 1 || AttTyp > MAX_ATP) fatal_err("bad AttTyp");
   AttArr = Sym_Att(Sym);
   if (AttArr == 0) {
      if (iAttS == MAX_AttS) fatal_err("no room for more AttS");
      AttArr = iAttS;
      Set_Sym_Att(Sym, AttArr);
      iAttS += 1; }/*if*/;
   AttS[AttArr][AttTyp-1] = Att;
   }/*Set_Att*/

