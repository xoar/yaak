static char RCSid[] = "$Id: match.c,v 1.10 2005/03/30 00:02:01 profw Exp $";
/* Keyword matching module */
/* Copyright 1992, The Regents of the University of Colorado */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <stdio.h>
#include "err.h"
#include "csm.h"
#include "source.h"
#include "obstack.h"
#include "scanops.h"
#include "tabsize.h"
#include "gla.h"
#include "match.h"

#define NORETURN 15001	/* hopefully, no one needs this as a token code */

#include "xtables.h"

extern char *auxNUL ELI_ARG((char *, int));
extern char *auxEOF ELI_ARG((char *, int));
extern void EndOfText ELI_ARG((char *, int, int *, int *));

int ResetScan = 1;      /* Initialization switch */
char *StartLine = 0;    /* Adjusted beginning of the current line */
char *TokenStart = 0;   /* First character position of the current token */
char *TokenEnd = 0;     /* First character position beyond the current token */

/**/
static void
#if PROTO_OK
obstack_octgrow(ObstackP obstack, int data_char)
#else
obstack_octgrow(obstack, data_char)
ObstackP obstack; int data_char;
#endif
/* Store the octal coding of a C character into an obstack
 *   On exit-
 *     The octal coding for data_char has been added to obstack
 **/
{
  obstack_1grow(obstack, '\\');

  if (data_char >= 64) {
    obstack_1grow(obstack, '0' + data_char / 64);
    data_char %= 8;
  } else obstack_1grow(obstack, '0');

  if (data_char >= 8) {
    obstack_1grow(obstack, '0' + data_char / 8);
    data_char %= 8;
  } else obstack_1grow(obstack, '0');

  obstack_1grow(obstack, '0' + data_char);
}

/**/
static void
#if PROTO_OK
obstack_cchgrow(ObstackP obstack, int data_char)
#else
obstack_cchgrow(obstack, data_char)
ObstackP obstack; int data_char;
#endif
/* Store a C character into an obstack
 *   On exit-
 *     The C form of data_char has been added to obstack
 **/
{
  if (data_char >= '\177') obstack_octgrow(obstack, data_char);
  else if (data_char == '\\') obstack_grow(obstack, "\\\\", 2);
  else if (data_char == '"') obstack_grow(obstack, "\\\"", 2);
  else if (data_char >= ' ') obstack_1grow(obstack, data_char);
  else switch (data_char) {
  case '\n': obstack_grow(obstack, "\\n", 2); break;
  case '\t': obstack_grow(obstack, "\\t", 2); break;
  case '\b': obstack_grow(obstack, "\\b", 2); break;
  case '\r': obstack_grow(obstack, "\\r", 2); break;
  case '\f': obstack_grow(obstack, "\\f", 2); break;
  default: obstack_octgrow(obstack, data_char); }
}

int
#if PROTO_OK
glalex(int *v)
#else
glalex(v) int *v;
#endif
{
register char c;		/* hold current char */
int     extcode;	/* external token repr */
register unsigned char *scanTbl = ScanTbl;/* this holds the base in a register */
register char *p = TokenEnd;	/* most current working pointer */

#if PROTO_OK
	char *(*scan)(char *, int);
	void  (*proc)(char *, int, int *, char *);
#else
	char *(*scan)();
	void  (*proc)();
#endif

  do {
        if (CaseTbl[c = *p] >= 0 && CaseTbl[c] <= 3) return 1;

		/****************************/
		/* generated code goes here */
		/****************************/
#include "xcode.h"

  } while (0);

fallback:
done:
	return 1;

}

/***/
char
#if defined(__STDC__) || defined(__cplusplus)
match(char *v)
#else
match(v) char *v;
#endif
/* Check whether a string is in a given set of tokens
 *    On entry-
 *       v addresses the string to be matched
 *    If the string matched a token completely then on exit-
 *       match=1
 *    Else on exit-
 *       match=0
 ***/
{
	int *dummy = (int *)0;

	TokenStart = TokenEnd = v;
	glalex(dummy);
	return *TokenEnd == '\0';
}
