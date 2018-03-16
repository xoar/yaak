#ifndef NDXMATH_H
#define NDXMATH_H

/* $Id: ndxmath.h,v 1.3 2009/09/09 19:31:57 profw Exp $ */
/* Copyright 2008, The Regents of the University of Colorado */

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


#include "err.h"
#include "eliproto.h"

int ndxoneop ELI_ARG((char* (*)(const char*,int),int,int,CoordPtr));
/* Apply a monadic operator to a string in the string table
 *   On entry-
 *     f points to the strmath function to be applied
 *     r=index of the operand
 *     b=radix of the operand
 *     c=coordinates at which any error is to be reported
 *   If no errors were detected then on exit-
 *     ndxoneop=string table index of the result
 *   Else on exit-
 *     ndxoneop=NoStrIndex
 *     The error has been reported at c
 ***/

int ndxtwoop ELI_ARG((char* (*)(const char*,const char*,int),int,int,int,CoordPtr));
/* Apply a dyadic operator to two strings in the string table
 *   On entry-
 *     f points to the strmath function to be applied
 *     l=index of the left operand
 *     r=index of the right operand
 *     b=radix of the operands
 *     c=coordinates at which any error is to be reported
 *   If no errors were detected then on exit-
 *     ndxoneop=string table index of the result
 *   Else on exit-
 *     ndxoneop=NoStrIndex
 *     The error has been reported at c
 ***/

int ndxnorml ELI_ARG((int r, int o, int n, char *s, CoordPtr c));
/* Normalize a string in the string table
 *   On entry-
 *     r=index of the operand
 *     o=radix of the operand
 *     n=radix of the result
 *     c=coordinates at which any error is to be reported
 *   If no errors were detected then on exit-
 *     ndxoneop=string table index of the result
 *   Else on exit-
 *     ndxoneop=NoStrIndex
 *     The error has been reported at c
 ***/

#endif
