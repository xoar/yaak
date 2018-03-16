static char RCSid[] = "$Id: pascalStr.c,v 1.12 2013/11/11 04:44:03 profw Exp $";
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

#include "err.h"
#include "gla.h"
#include "tabsize.h"

/*
**  Returns pointer to first character beyond string.
**  It does not handle multiline strings.
*/

char *
#if defined(__STDC__) || defined(__cplusplus)
auxPascalString(char *start, int length)
#else
auxPascalString(start, length)
char * start;	/* start of characters recognized by reg expr */
int length;	/* length of what was recognized in reg expr */
#endif
{ register char c;
  register char *p = start + length; /* first char not yet processed */

  while ((c = *p++) && c != '\n' && c != '\r') {
    if (c == '\t')
      StartLine -= TABSIZE(p - StartLine);
    else if (c == *start)
      {if (*p == *start) p++;
      else return p;
      }
  }

  message(ERROR, "newline or EOF in string", 0, &curpos);
  return p - 1;
}
