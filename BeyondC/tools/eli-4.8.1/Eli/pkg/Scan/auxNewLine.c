static char RCSid[] = "$Id: auxNewLine.c,v 1.7 2009/04/03 18:44:49 profw Exp $";
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

/* Adjust the coordinates for a new line
 *  Returns pointer to first character beyond newline.
 */

char *
#if defined(__cplusplus) || defined(__STDC__)
auxNewLine(char *start, int length)
#else
auxNewLine(start, length)
char *start; int length;
#endif
{ char *p = start + length;	/* first char not yet processed */

  if (p[-1] == '\r' && p[0] == '\n')
    p++;	/* DOS file newline is "\r\n" */

  LineNum++;
  StartLine = p-1;

  return(p);
}
