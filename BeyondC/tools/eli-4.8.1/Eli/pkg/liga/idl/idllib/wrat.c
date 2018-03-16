/* $Id: wrat.c,v 4.1 1997/08/29 08:31:13 peter Exp $ */
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

/* write a Rational to stdout. meant for Pascal programs */
/* (changes the 'e' to 'E') */
void WIDLfloat(f)
double f;
{
	char buf[256];
	register char *p;

	sprintf(buf, "%g", f);
	for (p=buf; *p != '\0'; ++p)
	    if (*p == 'e') {
		*p = 'E';
		break;
	    }

	fprintf(stdout, "%s", buf);
}

/* return a string containing a Rational (changes the 'e' to 'E') */
/* meant for C programs */
char *RetIDLfloat(f)
double f;
{
	static char buf[256];
	register char *p;

	sprintf(buf, "%g", f);
	for (p=buf; *p != '\0'; ++p)
	    if (*p == 'e') {
		*p = 'E';
		break;
	    }
	    

	return(buf);
}
