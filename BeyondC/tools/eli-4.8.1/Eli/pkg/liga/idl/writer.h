/* $Id: writer.h,v 4.2 1998/04/28 14:19:17 ludi Exp $ */
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
#ifndef WRITER_DEF
#define WRITER_DEF
#include "global.h"
String RetIDLfloat();

# define Wdouble(v)	IDLout(RetIDLfloat(v))
# define Wfloat(v)	IDLout(RetIDLfloat((double)v))
# define WInteger(v)	IDLout(itoa(v))
# define Wchar(v)	IDLout(itoa((int) v))
# define Wuchar(v)	IDLout(itoa((int) v))
# define Wint(v)	IDLout(itoa(v))
# define Wuint(v)	IDLout(itoa((int) v))
# define Wshort(v)	IDLout(itoa((int) v))
# define Wushort(v)	IDLout(itoa((int) v))
# define Wlong(v)	IDLout(ltoa((long) v))
# define Wulong(v)	IDLout(ultoa((unsigned long) v))
# define IDLout(v)	fputs(v,IDLcurrentFile)
# define IDLoutC(c)	putc(c,IDLcurrentFile)
# define IDLoutLabel(v)	(IDLout("L"),IDLout(ultoa((unsigned long) v)))

# define itoa(v)	(sprintf(charBuf,"%d",(v)),charBuf)
# define ultoa(v)	(sprintf(charBuf,"%lu",(v)),charBuf)
# define ltoa(v)	(sprintf(charBuf,"%ld",(v)),charBuf)
# define dtoa(v)	(sprintf(charBuf,"%g",(v)),charBuf)
# define CBSIZ	256
static char charBuf[CBSIZ];

# define MBoolean(X)
# define MString(X)
#define MInteger(X)
# define Mchar(X)
# define Muchar(X)
# define Mshort(X)
# define Mushort(X)
# define Mint(X)
# define Muint(X)
# define Mlong(X)
# define Mulong(X)
# define Mdouble(X)
# define Mfloat(X)

void WSetInteger(),WAInteger();
void WSetDouble(),WAdouble();
void WSetFloat(),WAfloat();
void WSetBoolean(),WABoolean();
void Wboolean(), WString();
void WIDLfloat();

extern FILE * IDLcurrentFile;
extern int IDLportState;

typedef enum { ErrPortMode, ErrNullNode, ErrBadClassType } WErrType;

# define DoubleQuote '"'
# define ListLink ' '
# define OpenAngle '<'
# define CloseAngle '>'
# define OpenBrace '{'
# define CloseBrace '}'
# define CloseBracket ']'
# define UpArrow '^'
# define Colon ':'
# define OpenBracket '['
# define AttrSep '\t'

# define P0 0

void WError();
void WBoolean();
void O_Node();

#endif /* WRITER_DEF */
