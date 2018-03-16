static char RCSid[] = "$Id: CchStr.c,v 1.30 2004/08/01 01:44:24 profw Exp $";
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

/*
 * scan and process C char constants and char strings
 * Updated to handle long, multi-line strings.  See gla.impl paper for info.
 */

#include <stdlib.h>
#include "err.h"
#include "source.h"
#include "gla.h"
#include "csm.h"
#include "tabsize.h"
#include "ScanProc.h"

#define BKSLASH '\\'
#define SQ	'\''

static int CharValue;	/* global to hold value of escape sequence */


static char *
#if defined(__cplusplus) || defined(__STDC__)
readescape(char *start, int m)
#else
readescape(start, m) char *start; int m;
#endif
/* Advance past an escape, obtaining the value of that escape
 *   On entry-
 *     start addresses the character following the backslash
 *     m=0 if no errors are to be reported
 *       1 if errors are to be reported
 *   On exit-
 *     readescape addresses the character following the escape
 ***/
{ register char *p = start;
  register int c = *p++;
  register int count;

  switch (CharValue = c)	/* assume simple escape like " or ' */
    {
/* HEX */
    case 'x':
      CharValue = 0;
      count = 0;
      while (1)
	{
	  c = *p++;
	  if (!(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')
	      && !(c >= '0' && c <= '9')) {
	      p--;
	      break;
	      }
	  CharValue *= 16;
	  if (c >= 'a' && c <= 'f')
	    CharValue += c - 'a' + 10;
	  if (c >= 'A' && c <= 'F')
	    CharValue += c - 'A' + 10;
	  if (c >= '0' && c <= '9')
	    CharValue += c - '0';
	  count++;
	}
      if (count == 0 && m) {
        POSITION here = curpos;
        ColOf(here) = start - StartLine;
	message (ERROR, "\\x used with no following hex digits",0,&here);
      }
      return p;

/* OCTAL */
    case '0':  case '1':  case '2':  case '3':  case '4':
    case '5':  case '6':  case '7':
      CharValue = 0;
      count = 0;
      while ((c <= '7') && (c >= '0') && (count++ < 3))
	{
	  CharValue = (CharValue * 8) + (c - '0');
	  c = *p++;
	}
      p--;
      return p;

/* MISC */
    case '\r':
      if (*p == '\n') p++;

    case '\n': case BKSLASH: case SQ: case '"': case '?':
      return p;

/* CONTROL */
    case 'a': CharValue = '\007'; return p;
    case 'n': CharValue = '\n'; return p;
    case 't': CharValue = '\t'; return p;
    case 'r': CharValue = '\r'; return p;
    case 'f': CharValue = '\f'; return p;
    case 'b': CharValue = '\b'; return p;
    case 'v': CharValue = '\v'; return p;

    } /* end switch */

  if (c == '\t') StartLine -= TABSIZE(p - StartLine);

  if (m) {
    POSITION here = curpos;
    ColOf(here) = start - StartLine;
    message(NOTE,"unknown escape sequence",0, &here);
  }
  return p;
}

/*
 * auxCString
 *
 * Scan a string literal after the opening double quote.
 *
 * On entry, start points to the opening quote, len should be 1.
 * On exit, we return the position after the closing quote.
 */

char *
#if defined(__cplusplus) || defined(__STDC__)
auxCString(char *start, int len)
#else
auxCString( start, len ) char *start; int len;
#endif
{ register char *p = start + len;
  char delim = *start;
  int escape = 0;

  for (;;) {
    register char c = *p++;

    if (c == delim) return p;

    if (c == '\n' || c == '\r') {
      POSITION here;
      LineOf(here) = LineNum; ColOf(here) = p - StartLine - 1;
      message(ERROR, "String terminated by newline", 0, &here);
      message(ERROR, "Illegal newline in string literal", 0, &curpos);
      return p - 1;
    }

    if (c == BKSLASH) {
      if (*p != '\n' && *p != '\r') p = readescape(p, 1);
      else {
        if (*p++ == '\r' && *p == '\n') p++;
        if (*p == '\0') {
          int pSave = p - start;
          size_t sSave = p - StartLine;
  
          TokenStart = start = auxNUL(start, pSave);
          p = start + pSave; StartLine = start + sSave;
  
          if (*p == '\0') {
            message(ERROR, "String terminated by end-of-file", 0, &curpos);
            return p - 1;
          }
        }
        LineNum++;
        StartLine = p - 1;
      }
    }
      
    if (c == '\t') StartLine -= TABSIZE(p - StartLine);
  }
}

        
/*
 * c_mkstr
 *
 * Make an internal string value from a character string by
 * colapsing escape sequences.
 *
 * On entry, c points to a character string of length 
 *           t points to a location containing the initial terminal code
 * On exit, t points to a location containing the correct terminal code
 *          an internal string value representing the character string has been
 *          stored at the location pointed to by v.
 */

void 
#if defined(__cplusplus) || defined(__STDC__)
c_mkstr(char *c, int length, int *t, int *v)
#else
c_mkstr(c, length, t, v)
char *c; int length, *t; int *v;
#endif
{
  char *tmp;
  int newlen;

  c++;			/* skip leading quote */
  newlen = 0;		/* keep track of how long the new string is */
  length -= 2;		/* throw away both quotes */

  for ( ; length > 0; ) {
    if (*c == BKSLASH) {
      if (c[1] == '\n' || c[1] == '\r') {
        if (c[1] == '\r' && c[2] == '\n') { length--; c++; }
        length -= 2;	/* throw away escaped NLs */
        c += 2;
      } else {
        tmp = readescape(c + 1, 0);
        if (CharValue == 0) {
           message(ERROR,"Denotation truncated due to embedded \\0",0,&curpos);
           break;
        }
        obstack_1grow(Csm_obstk, CharValue);
        ++newlen;
        length -= tmp - c;
        c = tmp;
      }
    } else {
      obstack_1grow(Csm_obstk, *c++);
      ++newlen;
      --length;
    }
  }/*endfor*/

  obstack_1grow(Csm_obstk, '\0');
  CsmStrPtr = (char *)obstack_finish(Csm_obstk);
  *v = stostr(CsmStrPtr, newlen);
}

/*
 * auxCChar
 *
 * Scan a character literal after the opening single quote.
 *
 * On entry, start points to the opening quote, len should be 1.
 * On exit, we return the position after the closing quote.
 */

char *
#if defined(__cplusplus) || defined(__STDC__)
auxCChar(char *start, int len)
#else
auxCChar( start, len )
char *start;
int len;
#endif
{ register char c;
  register char *p = start + len;
  POSITION loc;

  if ((c = *p++) == BKSLASH){
    if (*p == '\n' || *p == '\r') {
      message(ERROR, "newline in character constant", 0, &curpos);
      return p;
    }
    p = readescape(p, 1);
  } else if(c == '\n' || c == '\r') {
    message(ERROR, "newline in character constant", 0, &curpos);
    return p - 1;
  } else if(c == SQ) {
    message(ERROR, "Character constant may not be empty", 0, &curpos);
    return p;
  }

  if (*p != '\'') {
    loc = curpos; ColOf(loc) += (p - start);
    message(ERROR, "Closing quote required", 0, &loc);
    return p;
  }

  return p + 1;
}


/*
 * c_mkchar
 *
 * On entry, c points to a character string of length l
 *           t points to the initial terminal code (not used)
 * On exit, 
 *          The location v contains the value of the character literal.
 */

void
#if defined(__cplusplus) || defined(__STDC__)
c_mkchar(char *c, int l, int *t, int *v)
#else
c_mkchar(c, l, t, v)
char *c;
int l, *t;
int *v;
#endif
{
	char * tmp;
	c++;		/* skip leading single quote (')  */

	if(*c == BKSLASH){
		tmp = readescape(c + 1, 0);
		if( *tmp != SQ)
		     message(ERROR,"malformed character constant", 0,&curpos);
		*v = CharValue;
		}
	else
		*v = (int) *c;
}
