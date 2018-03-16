static char RCSid[] = "$Id: auxScanEOL.c,v 1.19 2004/08/01 01:44:25 profw Exp $";
/* Copyright 1989, The Regents of the University of Colorado */

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

#include "eliproto.h"
#include "err.h"
#include "gla.h"
#include "source.h"
#include "ScanProc.h"

/*
**  Scan to end of line, handle bookeeping.
**  Returns pointer to first character beyond newline.
*/

char *
#ifdef PROTO_OK
auxEOL(char *start, int length)
#else
auxEOL(start, length)
char *start; int length;
#endif
{ register char c;
  register char *p = start + length; /* first char not yet processed */

  if (*p == '\0') return p;

  while((c = *p++) != '\n' && c != '\r') ;
  if (c == '\r' && *p == '\n') p++;

  if (*p == '\0') {
    int length = p - start;
    start = TokenStart = auxNUL(start, length);
    p = start + length;
  }

  LineNum++;
  StartLine = p - 1;

  return p;
}
