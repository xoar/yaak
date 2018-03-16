/* (C) Copyright 1997 University of Paderborn */

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

static char rcsid[]="$Id: scanner.c,v 1.4 1997/08/29 08:38:08 mjung Exp $";

# include "global.h"
# include <stdio.h>

#define QUOTE	'\042'
#define TILDE	'\176'
#define DEL	'\177'

#define BUFFERSIZE 8000
char C;
int Line;
char BUFFER[BUFFERSIZE];
int BUFLEN;

char *BufCopy()
{	register char *S;
	register int i;
	String RetrieveReaderString();

	/* if S is not a node or attribute name, allocate storage */
	BUFFER[BUFLEN] = '\0';
	if ((S = RetrieveReaderString(BUFFER)) == NULL) {
	    S = (char *) GetHeap(BUFLEN+1);
	    for (i=0; i<BUFLEN; ++i) S[i] = BUFFER[i];
	    S[i] = '\0';
	}
	return S;
}

#define AddBuffer(c)	\
	{if (BUFLEN<BUFFERSIZE) BUFFER[BUFLEN++] = c; \
	else {fprintf(stderr, "idlreader: Insufficient buffer space\n"); exit(1);}}

# include "reader.h"

void LexInit(F)
FILE *F;
{	
	Line = 1;
	C = getc(F);
}

void escape_check(MyFile, Ret)
FILE	*MyFile;
Lexeme Ret;
{
	char	nc;			/* next character */

	nc = getc(MyFile);
	if(nc >= '@' && nc <= '_')	/* next char is '@' - '_' */
	{
	    nc = nc - '@';
	    AddBuffer(nc);
	}
	else if(nc == '~'){		/* next char is '~'  */
	    AddBuffer(TILDE);
	}
	else if(nc == '{'){		/* next char is '{' */
	    AddBuffer(DEL);
	}
	else {
	    Error(ErrBadEscapedChar,Ret.Pos);
	}
}

Lexeme GetLex(MyFile)
FILE * MyFile;
{	
	Lexeme Ret;

	Ret.Token = NULL;
	BUFLEN = 0;
	Ret.Pos.line = Line;

Start:	
	if ( feof(MyFile) )
	{
		Ret.Kind = LexEOF;
		goto Term;
	}
	else switch (C) {
	case '"':
	{
		Ret.Kind = LexString;
		C = getc(MyFile);
		goto InString;
	}

	/* white space */

	case ' ':	
		{
			C = getc(MyFile);
			goto Start;
		}
	case '	':
		{
			C = getc(MyFile);
			goto Start;
		}
	case '\n':	
		{
			C = getc(MyFile);
			Line++;
			Ret.Pos.line = Line;
			goto Start;
		}

	/* punctuation */

	case '{':	
		{
			Ret.Kind =  LexOpenBrace;
			C = getc(MyFile);
			goto Term;
		}
	case '}':	
		{
			Ret.Kind =  LexCloseBrace;
			C = getc(MyFile);
			goto Term;
		}
	case '<':	
		{
			Ret.Kind =  LexOpenAngleBracket;
			C = getc(MyFile);
			goto Term;
		}
	case '>':	
		{
			Ret.Kind =  LexCloseAngleBracket;
			C = getc(MyFile);
			goto Term;
		}
	case '[':	
		{
			Ret.Kind =  LexOpenSquareBracket;
			C = getc(MyFile);
			goto Term;
		}
	case ']':	
		{
			Ret.Kind =  LexCloseSquareBracket;
			C = getc(MyFile);
			goto Term;
		}
	case ';':	
		{
			Ret.Kind =  LexSemiColon;
			C = getc(MyFile);
			goto Term;
		}
	case '+':	
		{
			AddBuffer(C);
			C = getc(MyFile);
			goto Sign;
		}
	case '-':	
		{
			C = getc(MyFile);
			if (C == '-') {
			    /* comment so eat up rest of line and go to start*/
			    while ((C != '\n') && (!feof(MyFile)))
				C = getc(MyFile);
			    BUFLEN = 0;
			    goto Start;
			}
			else {
			    AddBuffer('-');
			    goto Sign;
			}
		}
	case '#':	/* soft EOF */
		{	Ret.Kind = LexEOF;
			goto Term;
		}
	default:	
		if ( (C == '0') || ((C >= '1') && (C <= '9')) )
		{
			Ret.Kind = LexInteger;
			AddBuffer(C);
			C = getc(MyFile);
			goto INT;
		}
		else if ( ((C >= 'a') && (C <= 'z'))
		    || ((C >= 'A') && (C <= 'Z')) )
		{
			Ret.Kind = LexName;
			AddBuffer(C);
			C = getc(MyFile);
			goto NAME;
		}
		else	Error(ErrBadLex,Ret.Pos);
	}

Sign:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		Ret.Kind = LexInteger;
		AddBuffer(C);
		C = getc(MyFile);
		goto INT;
	}
	else	Error(ErrBadLex,Ret.Pos);

INT:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto INT;
	}
	else switch(C) {
	case '#':
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S1;
	}
	case 'E':
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S2;
	}
	case '.':
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S3;
	}
	default:
	{	Ret.Token = BufCopy();
		goto Term;
	}
}

S1:	
	if ( (C == '0') || ((C >= '1') && (C <= '9'))
	    || ((C >= 'A') && (C <= 'F')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S4;
	}
	else	Error(ErrBadLex,Ret.Pos);

S2:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		Ret.Kind = LexRational;
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat2;
	}
	else if ((C == '+') || (C == '-')) {
		AddBuffer(C);
		C = getc(MyFile);
		goto S2;
	}
	else	Error(ErrBadLex,Ret.Pos);

S3:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		Ret.Kind = LexRational;
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat1;
	}
	else	Error(ErrBadLex,Ret.Pos);

S4:	
	if ( (C == '0') || ((C >= '1') && (C <= '9'))
	    || ((C >= 'A') && (C <= 'F')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S4;
	}
	else switch(C) {
	case '#':
	{
		Ret.Kind = LexRational;
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat3;
	}
	case '.':
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S5;
	}
	default:
		Error(ErrBadLex,Ret.Pos);
	}

S5:	
	if ( (C == '0') || ((C >= '1') && (C <= '9'))
	    || ((C >= 'A') && (C <= 'F')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S6;
	}
	else	Error(ErrBadLex,Ret.Pos);

S6:	
	if ( (C == '0') || ((C >= '1') && (C <= '9'))
	    || ((C >= 'A') && (C <= 'F')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S6;
	}
	else if (C=='#')
	{
		Ret.Kind = LexRational;
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat3;
	}
	else	Error(ErrBadLex,Ret.Pos);

BRat1:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat1;
	}
	else if ( C == 'E' )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S2;
	}
	else
	{	Ret.Token = BufCopy();
		goto Term;
	}

BRat2:	
	if ( (C == '0') || ((C >= '1') && (C <= '9')) )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto BRat2;
	}
	else
	{	Ret.Token = BufCopy();
		goto Term;
	}

BRat3:	
	if ( C == 'E' )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto S2;
	}
	else
	{	Ret.Token = BufCopy();
		goto Term;
	}

NAME:	
	if ( ((C >= 'a') && (C <= 'z')) || ((C >= 'A') && (C <= 'Z'))
	    || (C == '0') || ((C >= '1') && (C <= '9'))
	    || (C == '_') )
	{
		AddBuffer(C);
		C = getc(MyFile);
		goto NAME;
	}
	else if ( C == '^' )
	{
		C = getc(MyFile);
		goto LRef;
	}
	else if ( C == ':' )
	{
		C = getc(MyFile);
		goto LDef;
	}
	else if ( C == ' ' )
	{
		C = getc(MyFile);
		goto NWS;
	}
	else if ( C == '	' )
	{
		C = getc(MyFile);
		goto NWS;
	}
	else	goto NCheck;

NWS:	
	if ( C == '^' )
	{
		C = getc(MyFile);
		goto LRef;
	}
	else if ( C == ':' )
	{
		C = getc(MyFile);
		goto LDef;
	}
	else if ( C == ' ' )
	{
		C = getc(MyFile);
		goto NWS;
	}
	else if ( C == '	' )
	{
		C = getc(MyFile);
		goto NWS;
	}
	else if ( C == '\n' )
	{
		Line++;
		C = getc(MyFile);
		goto NWS;
	}
	else	goto NCheck;	/* if no case matches */

LDef:	
	Ret.Kind = LexLabelDef;
	Ret.Token = BufCopy();
	goto Term;

LRef:	
	Ret.Kind = LexLabelRef;
	Ret.Token = BufCopy();
	goto Term;

NCheck:	
	if (BUFLEN == 4)
	{
		if ( (BUFFER[0] == 'T') &&
		    (BUFFER[1] == 'R') &&
		    (BUFFER[2] == 'U') &&
		    (BUFFER[3] == 'E') )
		{	Ret.Kind = LexTrue;
			goto Term;
		}
	}
	else if ( BUFLEN == 5 )
	{
		if ( (BUFFER[0] == 'F') &&
		    (BUFFER[1] == 'A') &&
		    (BUFFER[2] == 'L') &&
		    (BUFFER[3] == 'S') &&
		    (BUFFER[4] == 'E') )
		{	Ret.Kind = LexFalse;
			goto Term;
		}
	}
	Ret.Token = BufCopy();
	goto Term;

InString:
	if(C != '"')
	{
		if (C == '~')
		    escape_check(MyFile, Ret);
		else AddBuffer(C);
		C = getc(MyFile);
		goto InString;
	}
	else  /* QUOTE */
	{
		C = getc(MyFile);
		if(C == '"')
		{
		    AddBuffer(C);
		    C = getc(MyFile);
		    goto InString;
		}
		else 
		{
		    Ret.Token = BufCopy();
		    goto Term;
		}
	}

Term:
	return(Ret);
}

		
