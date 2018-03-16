/* $Id: wmisc.c,v 4.1 1997/08/29 08:31:13 peter Exp $ */

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
#include <string.h>
#include "global.h"
#include "writer.h"
#define MAXSTRINGLEN 5000
#define TILDE 0176
#define DEL 0177
#define QUOTE '"'

void WError(E)
WErrType E;
{	switch (E) {
	case ErrNullNode:
		IDLout("**Null Node**");
		fprintf(stderr,"Writer Error: null node\n");
		break;
	case ErrPortMode:
		fprintf(stderr,"Writer error: bad port mode\n");
		break;
	case ErrBadClassType:
		IDLout("**Bad Node For Class**");
		fprintf(stderr,"Writer error: bad class type\n");
		break;
	}
}

void WBoolean(b)
Boolean b;
{	if (b)	IDLout("TRUE");
	else	IDLout("FALSE");
}

void WString(S)
register String S;
{	
	char *check_string();

	if (S == NULL) {
	    IDLoutC(DoubleQuote );
	    IDLoutC(DoubleQuote );
	}
	else if (strlen(S)==0) {
	    IDLoutC(DoubleQuote );
	    IDLoutC(DoubleQuote );
	}
	else {
	    IDLoutC(DoubleQuote );
	    S = check_string(S);
	    IDLout(S);
	    IDLoutC(DoubleQuote );
	}
}

/**********************
void WSETBoolean (SB)
register SETBoolean SB;
{	IDLoutC( OpenBrace );
	if (SB.true) {
	    WBoolean(TRUE);
	    if (SB.false) {
		IDLoutC (ListLink);
		WBoolean(FALSE);
	    }
	}
	else if (SB.false) WBoolean(FALSE);
	IDLoutC ( CloseBrace );
}
************************/

char *check_string(S)
String	S;
{

	static char stringbuf[MAXSTRINGLEN];
	register char *	result;
	int len;
	
	if ((len = strlen(S)) >= MAXSTRINGLEN)
	    result = (char *)GetHeap(len + 1);
	else result = stringbuf;

	while (*S != '\0')
	{
	    if((*S > 0) && (*S <= 037))	  /* character is between '@' and '_' */
	    {
		*result++ = '~';
		*result++ = *S + '@';
	    }
	    else if(*S == TILDE)  
	    	 {
		     *result++ = '~';
		     *result++ = '~';
	    	 }
	    else if(*S == DEL)
		 {
		     *result++ = '~';
		     *result++ = '{';
		 }
	    else if(*S == QUOTE)
	         {
		     *result++ = '"';
		     *result++ = '"';
		 }
	    else *result++ = *S;
	    ++S;
	}

	*result = '\0';

	return(stringbuf);
}
