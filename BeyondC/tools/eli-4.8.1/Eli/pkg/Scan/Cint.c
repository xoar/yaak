static char RCSid[] = "$Id: Cint.c,v 2.8 2009/09/09 19:31:57 profw Exp $";
/* Copyright 1996, The Regents of the University of Colorado */

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

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "err.h"

static char DigitValue[] = {
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  0,   1,   2,   3,   4,   5,   6,   7,
  8,   9,   100, 100, 100, 100, 100, 100,
  100, 10,  11,  12,  13,  14,  15,  100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  99,  100, 100, 100, 100, 100, 100, 100,
  100, 10,  11,  12,  13,  14,  15,  100,
  100, 100, 100, 100, 100, 100, 100, 100,
  100, 100, 100, 100, 100, 100, 100, 100,
  99,  100, 100, 100, 100, 100, 100, 100
};

void
#if defined(__cplusplus) || defined(__STDC__)
c_mkint(const char *c, int l, int *t, int *p)
#else
c_mkint(c, l, t, p) char *c; int l, *t; int *p;
#endif
/* Make an internal integer value from a string of digits
 *   On entry-
 *     c points to a digit string of length l
 *   On exit-
 *     A value of type int representing the digit string
 *       has been stored at the location pointed to by p
 ***/
{ register int result = 0;
  register int radix;

  if (l < 2 || c[0] != '0') radix = 10;
  else if (DigitValue[c[1]] != 99) radix = 8;
  else { radix = 16; c += 2; l -= 2; }

  while (l-- > 0) {
    register int digit = DigitValue[*c++];

    if (digit >= radix || result > (INT_MAX - digit) / radix) {
      message(ERROR, "Cannot convert this", 0, &curpos);
      return;
    }
    result = result * radix + digit;
  }

  *p = result;
}
