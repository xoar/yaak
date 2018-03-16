static char RCSid[] = "$Id: M2int.c,v 1.8 2009/09/09 19:31:57 profw Exp $";
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
#include <errno.h>
#include "err.h"

void
#if defined(__cplusplus) || defined(__STDC__)
modula_mkint(const char *c, int l, int *t, int *p)
#else
modula_mkint(c, l, t, p) char *c; int l, *t; int *p;
#endif
/* Make an internal integer value from a string of digits
 *   On entry-
 *     c points to a digit string of length l
 *   On exit-
 *     A value of type int representing the digit string
 *       has been stored at the location pointed to by p
 ***/
{ char save, *bad;
  long result;

  save = c[l - 1];
  if (save == 'B' || save == 'C') {
    c[l - 1] = '\0';
    *p = result = strtol(c, &bad, 8);
    c[l - 1] = save;
    if (bad != c + l - 1) message(ERROR, "Invalid digit string", 0, &curpos);
  } else if (save == 'H') {
    c[l - 1] = '\0';
    *p = result = strtol(c, &bad, 16);
    c[l - 1] = save;
    if (bad != c + l - 1) message(ERROR, "Invalid digit string", 0, &curpos);
  } else {
    save = c[l]; c[l] = '\0';
    *p = result = strtol(c, &bad, 10);
    c[l] = save;
    if (bad != c + l) message(ERROR, "Invalid digit string", 0, &curpos);
  }

  if (((errno == ERANGE) && (result == LONG_MIN || result == LONG_MAX))
      || result != *p)
    message(ERROR, "Integer too large", 0, &curpos);
}
