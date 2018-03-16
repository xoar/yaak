static char rcsid[] = "$Id: ndxmath.c,v 1.3 2009/10/05 03:24:06 profw Exp $";
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

#include <string.h>
#include <errno.h>
#include "csm.h"
#include "idn.h"
#include "strmath.h"
#include "ndxmath.h"

static int
#ifdef PROTO_OK
ndxstore(const char* result, CoordPtr c)
#else
ndxstore(result, c) char* result; CoordPtr c;
#endif
/* Store a result after checking for errors
 *   On entry-
 *     result=string representation of the result
 *     c=coordinates at which any error should be reported
 *     Any error detected is characterized by errno
 *   If result=NULL then on exit-
 *     ndxstore=NoStrIndex
 *     The errno has been reported at c
 *   Else on exit-
 *     ndxstore=string table index of the string result
 **/
{ int intrinsic, syncode = 0;

  if (!result) {
    message(
      ERROR,
      (const char *)obstack_copy0(
        Csm_obstk,
	strerror(errno),
	strlen(strerror(errno))),
      0,
      c);
    return NoStrIndex;
  }

  mkidn(result, strlen(result), &syncode, &intrinsic);
  return intrinsic;
}

int
#ifdef PROTO_OK
ndxoneop(char* (*f)(const char*,int), int r, int b, CoordPtr c)
#else
ndxoneop(f, r, b, c) char* (*f)(char*,int); int r; int b; CoordPtr c;
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
#endif
{ if (r == NoStrIndex) return NoStrIndex;
  return ndxstore(f(StringTable(r), b), c);
}

int
#ifdef PROTO_OK
ndxtwoop(char* (*f)(const char*,const char*,int),int l,int r,int b,CoordPtr c)
#else
ndxtwoop(f, l, r, b, c)
char* (*f)(char*,char*,int); int l,r; int b; CoordPtr c;
#endif
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
{ if (l == NoStrIndex || r == NoStrIndex) return NoStrIndex;
  return ndxstore(f(StringTable(l), StringTable(r), b), c);
}

int
#ifdef PROTO_OK
ndxnorml(int r, int o, int n, char *s, CoordPtr c)
#else
ndxnorml(r, o, n, s, c) int r, o, n; char *s; CoordPtr c;
#endif
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
{ if (r == NoStrIndex) return NoStrIndex;
  return ndxstore(strnorm(StringTable(r), o, n, s), c);
}
