#ifndef OILADT2B_H
#define OILADT2B_H

/* $Id: oiladt2b.h,v 1.3 1997/09/04 18:21:06 waite Exp $ */
/* Oil database dump module interface
   Copyright 1989, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include <stdio.h>
#include "oiladt2.h"

#if defined(cplusplus) || defined(__STDC__)
extern void OilDumpType(tOilType t);
extern void OilDumpSig(tOilArgSig t);
extern void OilDumpOp(tOilOp t);
extern void OilDumpCoercionCost(tOilCoercionSeq t);
extern void OilDumpTypeSet(tOilTypeSet t);
extern void OilDumpSetOilArgSig(tOilSetSig t);
extern void OilDumpOpId(tOilOpIdentification t);
extern void OilDumpArgDesc(tOilClassArgSig t);
extern void OilDumpClassOpId(tOilClassOpId t);
extern void OilDumpClassOp(tOilClassOp t);
extern void OilDumpClass(tOilClass t);
extern FILE *OilDumpInit(char *fname);
#else
extern void OilDumpType();
extern void OilDumpSig();
extern void OilDumpOp();
extern void OilDumpCoercionCost();
extern void OilDumpTypeSet();
extern void OilDumpSetOilArgSig();
extern void OilDumpOpId();
extern void OilDumpArgDesc();
extern void OilDumpClassOpId();
extern void OilDumpClassOp();
extern void OilDumpClass();
extern FILE *OilDumpInit();
#endif

#endif
