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
/* $Id: OutStr.c,v 4.2 1998/04/28 14:23:01 ludi Exp $ */
/* Copyright, 1992, AG-Kastens, University Of Paderborn */

#include <stdio.h>
#include "OutStr.h"

#define	SQ	'\''

void C_outstr(fs, s)
  FILE *fs;
  char *s;
{
	char c;

	(void)fprintf(fs,"\"");

	while ((c = *s++)) {
		if (c == '\\') (void)fputs("\\\\", fs);
		else if (c == '"') (void)fputs("\\\"", fs);
		else if (c >= ' ') (void)fputc(c, fs);
		else switch (c) {
		case '\n': (void)fputs("\\n", fs); break;
		case '\t': (void)fputs("\\t", fs); break;
		case '\b': (void)fputs("\\b", fs); break;
		case '\r': (void)fputs("\\r", fs); break;
		case '\f': (void)fputs("\\f", fs); break;
		default: (void)fprintf(fs, "\\%03hho", c); }
	}

	(void)fprintf(fs,"\"");
	return;
}

void C_outchar(fs, s)
  FILE *fs;
  char *s;
{
        char c;

        (void)fputc(SQ, fs);

	if ((c = *s & 0377)) {
		if (c >= '\177') (void)fprintf(fs, "\\%3o", c);
		else if (c == '\\') (void)fputs("\\\\", fs);
		else if (c == '"') (void)fputs("\\\"", fs);
		else if (c >= ' ') (void)fputc(c, fs);
		else switch (c) {
		case '\n': (void)fputs("\\n", fs); break;
		case '\t': (void)fputs("\\t", fs); break;
		case '\b': (void)fputs("\\b", fs); break;
		case '\r': (void)fputs("\\r", fs); break;
		case '\f': (void)fputs("\\f", fs); break;
		default: (void)fprintf(fs, "\\%3o", c); }
	}

	(void)fputc(SQ, fs);
	return;
}

void P_outstr(fs, s)
  FILE *fs;
  char *s;
{
	char c;

	(void)fputc(SQ, fs);

	while ((c = *s++ & 0177)) {
		if (c == '\'') (void)fputs("''", fs);
		else (void)fputc(c, fs);
	}

	(void)fputc(SQ, fs);
	return;
}

void outstr(fs, s)
  FILE *fs;
  char *s;
{
        fprintf(fs,"%s",s);
        return;
}
