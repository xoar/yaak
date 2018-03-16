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

static char rcsid[] = "$Id: rmisc.c,v 1.6 2007/02/23 10:39:02 peter Exp $";

#include <stdio.h>
#include <string.h>
#include "global.h"
#include "reader.h"

/* error functions */

void Error(What,Where)
ErrType What;
PosType Where;
{
	int lineNum;

	lineNum = Where.line;
	fprintf(stderr,"IDL Error: ");
	switch (What) {
		case ErrAngleExpected:
			fprintf(stderr,"Expected angle bracket on line %d\n",
				lineNum);
			break;
		case ErrBraceExpected:
			fprintf(stderr,"Expected square bracket on line %d\n",
				lineNum);
			break;
		case ErrEOF:
			fprintf(stderr,"Unexpected end of file on line %d\n",
				lineNum);
			break;
		case ErrSemiColonExpected:
			fprintf(stderr,"Expected semicolon on line %d\n",
				lineNum);
			break;
		case ErrSkipStopped:
			fprintf(stderr,"Resuming input parsing at %d\n",
				lineNum);
			break;
		case ErrValueExpected:
			fprintf(stderr,"Expected to see value on line %d\n",
				lineNum);
			break;
		case ErrBadNodeType:
			fprintf(stderr,"Bad node type for this port on line %d\n",
				lineNum);
			break;
		case ErrNodeExpected:
			fprintf(stderr,"Expected to see a node on line %d\n",
				lineNum);
			break;
		case ErrEOFExpected:
			fprintf(stderr,"Expected to see end of file on line %d\n",
				lineNum);
			break;
		case ErrBadRootType:
			fprintf(stderr,"Root type invalid for this port\n");
			break;
		case ErrNoRoot:
			fprintf(stderr,"No root!!!\n");
			break;
		case ErrBadAttribute:
			fprintf(stderr,"Bad attribute on line %d\n",
				lineNum);
			break;
		case ErrBadLex:
			fprintf(stderr,"Bad token in input, line %d\n",
				lineNum);
			break;
		case ErrBadClassNode:
			fprintf(stderr,"Bad class type on line %d\n",
				lineNum);
			break;
		case ErrBadEscapedChar:
			fprintf(stderr, "Illegal escaped character on line %d\n",				lineNum);
			break;
		default:
			fprintf(stderr,"Unknown error type %d on line %d\n",
				What,lineNum);
		}
		exit(1);
}

void ErrInit()
	{
	}

void ErrFinish()
	{
	}

/* sequence functions */

SeqType NewSeq()
	{
	return(NULL);
	}

SeqType AddSeq(L,V)
SeqType L;
RepType V;
{	
	SeqType t, L2;

	t = (SeqType)GetHeap(sizeof(struct CellType));
	t->next = NULL;
	if (V->Kind == RepLabelRef)
		t->value = NULL;
	else
		t->value = V;

	if (L == NULL)
	    L = t;
	else {
	    for (L2=L; L2->next != NULL; L2 = L2->next) ;
	    L2->next = t;
	}

	return(L);
}

/* functions that return RepTypes */

RepType MakeVal(Attr,Lex)
RepKind Attr;
Lexeme Lex;
{	RepType R;

	R = (RepType)GetHeap(sizeof(struct RecRepType));
	R->Pos = Lex.Pos;
	R->Labelled = 0;
	R->StringField = Lex.Token;
	R->Kind = Attr;
	return R;
}

RepType MakeBool(TorF,P)
int TorF;
PosType P;
{	RepType R;

	R = (RepType)GetHeap(sizeof(struct RecRepType));
	R->Pos = P;
	R->Kind = AtrBoolean;
	R->Labelled = 0;
	R->UnionField.boolVal = TorF;
	R->StringField = NULL;
	return(R);
}

RepType MakeNode(N,P)
NodeType N;
PosType P;
{	RepType R;

	R = (RepType)GetHeap(sizeof(struct RecRepType));
	R->Pos = P;
	R->StringField = NULL;
	R->Labelled = 0;
	R->Kind = RepNode;
	R->UnionField.NodeField = N;
	return(R);
}

RepType MakeSeq(S,P)
SeqType S;
PosType P;
{	RepType R;

	R = (RepType)GetHeap(sizeof(struct RecRepType));
	R->Pos = P;
	R->StringField = NULL;
	R->Labelled = 0;
	R->Kind = AtrSequence;
	R->UnionField.seqVal = S;
	return(R);
}

/* misc. reader functions */


String StrCopy(S)
register String S;
{	register int i;
	register String Ret;

	i = strlen(S);
	Ret = (String) GetHeap(i+1);
	(void) strncpy(Ret,S,i+1);
	return Ret;
}

String GString(R)
register RepType R;
{	register String S;

	if (R)
	{	S = NewString(R->StringField);
	} else
	{	S = NULL;
	}
	return S;
}

Boolean GBoolean(R)
register RepType R;
{	register Boolean B;

	B = R->UnionField.boolVal;
	return B;
}

void DelRep(R)
register RepType R;
{	if (R->Labelled==0)
	{	/* if (R->StringField) FreeHeap(R->StringField); */
		FreeHeap(R);
	}
}
