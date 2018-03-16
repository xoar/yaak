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

#ifndef READER_DEF
#define READER_DEF

/* $Id: reader.h,v 1.7 1997/08/29 08:38:08 mjung Exp $ */

#include <stdlib.h>

typedef enum {
LexCloseAngleBracket, LexCloseBrace, LexCloseSquareBracket, LexEOF, LexFalse,
LexTrue, LexInteger, LexLabelDef, LexLabelRef, LexName, LexOpenAngleBracket,
LexOpenBrace, LexOpenSquareBracket, LexRational, LexSemiColon, LexString }
LexType;

typedef struct {
	int line;
} PosType;

typedef int AttrDesc;

typedef enum {SeqLabel, NodeLabel} LabelKind;
typedef struct LabelRecord *LabelType;
typedef struct LabelRefRecord *LabelRefType;
typedef struct RecRepType *RepType;
struct LabelRefRecord {
	LabelRefType next;	/* for collision resolution by chaining */
	LabelType RefList;
	int Unresolved;
	int Generated;
	String Name;
	RepType Val;
};
struct LabelRecord
{	LabelType next;
	LabelRefType parent;
	PosType Pos;
	LabelKind Kind;
	union
	{	RepType *SLabel;	/* pointer to where to put it */
		struct
		{	NodeType NodeField;
			AttrDesc Desc;
		} NLabel;
	} UnionField;
};

typedef struct {
	LexType Kind;
	PosType Pos;
	String Token;
} Lexeme;

typedef struct CellType *SeqType;

typedef enum {
RepLabelRef, RepNode, AtrInteger, AtrRational, AtrString, AtrBoolean,
AtrSequence, RepPrivate
} RepKind;

struct RecRepType {
	PosType Pos;
	String StringField;
	RepKind Kind;
	int Labelled;
	union {
		SeqType seqVal;
		int boolVal;
		LabelRefType LabelField;
		NodeType NodeField;
		int PrivateField;
	}	UnionField;
};

struct CellType {
	SeqType next;
	RepType value;
};

typedef enum {
	ErrAngleExpected, ErrBraceExpected, ErrEOF, ErrSemiColonExpected,
	ErrSkipStopped, ErrValueExpected, ErrBadNodeType, ErrNodeExpected,
	ErrEOFExpected, ErrBadRootType, ErrNoRoot, ErrBadLex, ErrBadAttribute,
	ErrBadClassNode, ErrBadEscapedChar }
ErrType;

typedef struct {
	char *nodetypename;
	int nodetypeconstant;
} ntype;

#define MAXATTRIBUTES 100
typedef struct {
	char *attributes[MAXATTRIBUTES];
} natype;
NodeType Reader ();

/* error functions */
void ErrInit();
void ErrFinish();
void Error();

/* sequence functions */

SeqType AddSeq();

/* functions to create RepTypes */

RepType MakeVal();

RepType MakeBool();

RepType MakeNode();

RepType MakeSeq();

/* is the input root in the root set for the port? */

int InRootSet();

/* attribute table functions */

AttrDesc FindAttribute();

int FindNodeType();

/* lexical functions */

Lexeme GetLex();

void LexInit();

/* label functions */

RepType FakeLabel();

void DelaySeqRef();

RepType LabelRef();

void SaveLabel();

void DelayedRef();

void LabelInit();

int LabelFinish();

/* process-specific functions */

void AttrStore();

NodeType NodeAlloc();

/* misc. reader funcs */

void DelRep();

extern int OK;
extern Lexeme Lex;
String GString();
# define GInteger(R) Gint(R)
# define Gint(R) (atoi((R)->StringField))
# define Guint(R) Gint(R)
# define Gchar(R) Gint(R)
# define Guchar(R) Gint(R)
# define Gshort(R) Gint(R)
# define Gushort(R) Gint(R)
# define Glong(R) Gint(R)
# define Gulong(R) Gint(R)
# define Gfloat(R) (atof((R)->StringField))
# define Gdouble(R) Gfloat(R)

typedef NodeType (*PF_NodeType)();	/* ptr to function returning NodeType */
typedef void (*PF_AttrStore)();		/* ptr to function returning void */

#endif /* READER_DEF */
