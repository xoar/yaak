static char RCSid[] = "$Id: Ctext.c,v 2.8 2004/08/01 01:44:25 profw Exp $";
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
#include "source.h"
#include "tabsize.h"
#include "gla.h"
#include "ScanProc.h"

typedef enum {			/* Scanner states */
   InText,
   InComment,
   InCharacter,
   InString
} States;

typedef enum {			/* Last character flags */
   Uninteresting,
   Backslash,
   Slash,
   Star
} Flags;

/***/
char *
#if defined(__cplusplus) || defined(__STDC__)
Ctext(char *start, int len)
#else
Ctext(start, len)
char *start; int len;
#endif
/* Scan a C compound statement after the opening brace
 *    On entry
 *       start points to the opening brace
 *       len=length of the opening delimiter
 *    On exit-
 *       Ctext points to the character position following the
 *          closing brace
 ***/
{
   register char c ;
   register char *p = start + len;
   int nest = 0;
   States state = InText;
   Flags last = Uninteresting;

   for (;;) {
      if (*p == '\0') {
         int current = p - start;
	 TokenStart = start = auxNUL(start, current);
         p = start + current;
         if (*p == '\0') {
            message(ERROR,"file ends in C text",0,&curpos);
            return p;
         }
      }
      c = *p++;

      if (c == '\r' && *p == '\n') c = *p++;
      if (c == '\n' || c == '\r') { LineNum++; StartLine = p - 1; }
      else if (c == '\t') StartLine -= TABSIZE(p - StartLine);

      switch (last) {
      case Backslash:
         last = Uninteresting; continue;
      case Slash:
         last = Uninteresting;
         if (c == '*') { state = InComment; continue; }
         break;
      case Star:
         last = Uninteresting;
         if (c == '/') { state = InText; continue; }
      default:
         ;
      }

      switch (c) {
      case '\"':
         if (state == InText) state = InString;
         else if (state == InString) state = InText;
         break;
      case '\'':
         if (state == InText) state = InCharacter;
         else if (state == InCharacter) state = InText;
         break;
      case '\\':
         if (state == InCharacter || state == InString) last = Backslash;
         break;
      case '/':
         if (state == InText) last = Slash;
         break;
      case '*':
         if (state == InComment) last = Star;
         break;
      case '{':
         if (state == InText) nest++;
         break;
      case '}':
         if (state == InText) {
            if (nest == 0) {
		return p;
	    }
            nest--;
         }
         break;
      default:
         ;
      }
   }
}
