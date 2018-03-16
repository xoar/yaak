static char RCSid[] = "$Id: coordAdjust.c,v 1.6 2004/08/01 01:44:25 profw Exp $";
/* Copyright 1993, The Regents of the University of Colorado */

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
#include "gla.h"
#include "tabsize.h"

/* Adjust the coordinates for a new line
 *  Returns pointer to first character beyond newline.
 */

char *
#if defined(__STDC__) || defined(__cplusplus)
coordAdjust(char *start, int length)
#else
coordAdjust(start, length)
char * start;	/* start of characters recognized by reg expr */
int length;	/* length of what was recognized in reg expr */
#endif
{
  register char c, *p = start, *q = start + length;

  while (p < q) {
    if ((c = *p++) == '\t') {
      /* p addresses the character following the tab
       * so at most we go 7 more cols, modulo-8 gives us this- 0-7
       */
      StartLine -= TABSIZE(p - StartLine);
    }

    if (c == '\r' && *p == '\n') c = *p++;
    if (c == '\n' || c == '\r') {
      LineNum++;
      StartLine = p-1;
    }
  }

  return(p);
}
