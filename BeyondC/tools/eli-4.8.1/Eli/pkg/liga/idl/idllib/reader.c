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

static char rcsid[] = "$Id: reader.c,v 1.5 1997/10/13 11:24:50 peter Exp $";

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "reader.h"


#ifdef EBUG
#define DEBUG(x) printf x
#else
#define DEBUG(x)
#endif

FILE * Input;
Lexeme Lex;
int OK;

ntype *IDLAllNodeTypes;
natype *IDLNodeAttributes;
int IDLnum_nodetypes;
PF_NodeType	GenericNodeAlloc;
PF_AttrStore	GenericAttrStore;

int FindNodeType(str)
register char *str;
{
	int b, e;

	int med, cmpresult;

	b=0;
	e=IDLnum_nodetypes-1;

	while (1) {
		if (b>e){
			Error(ErrBadNodeType, Lex.Pos);
			return(-1);
		}
		else if (b==e) {
			if (!strcmp(str, IDLAllNodeTypes[b].nodetypename)) {
			   return(IDLAllNodeTypes[b].nodetypeconstant);
			}
			else {
			    Error(ErrBadNodeType, Lex.Pos);
			    return(-1);
			}
		}
		else {
			med = (int)((e+b)/2) + 1;
			cmpresult = strcmp(str, IDLAllNodeTypes[med].nodetypename);
			if (cmpresult<0)
			    e = med-1;
			else if (cmpresult == 0) {
			    return(IDLAllNodeTypes[med].nodetypeconstant);
			}
			else
			    b = med+1;

		}
	}
}


AttrDesc FindAttribute(N, s)
register int N;
register char *s;
{
	int node_index, i;

	node_index = N/2 - 1;
	for (i=0; IDLNodeAttributes[node_index].attributes[i] != NULL; i++){
		if (!strcmp(s, IDLNodeAttributes[node_index].attributes[i])){
			return(i+1);
		}
	}

	Error(ErrBadAttribute, Lex.Pos);
	return(0);
}


void RelLex()
/*	Release the dynamically-allocated portions of a	lexeme.
	Parameters:	Lex: Lexeme to be released
*/
{
	if ( Lex.Token != NULL ) {
		FreeHeap(Lex.Token); 
		Lex.Token = NULL;
	}
}

void NextLex()
/* Cover function for calls on the lexer. */
{ 
	Lex = GetLex(Input); 
}

int IsLex(Expected)
LexType Expected;
{
	/*	Test whether the current lexeme is a particular type,
		and advance to the next lexeme if so.  Used in common
		case of recognizing a simple lexeme (i.e., one for
		which no token need be saved)
	*/
	if ( Lex.Kind==Expected	)
	{ 
		RelLex();
		NextLex();
		return(1);
	}
	else return(0);
}

void SkipLex(LexWanted,CloseLex,OpenLex)
LexType LexWanted,CloseLex,OpenLex;
/*	Skip over lexemes until a particular one is found.
	LexWanted:	The lexeme to look for.
	CloseLex:	Lexeme that closes the environment
			in which LexWanted may be found.
	OpenLex:	Open lexeme corresponding to CloseLex.
*/
{
	int CloseCount;

	CloseCount = 1;
	while (CloseCount > 0)
	    {
		RelLex(); 
		NextLex();
		if ( Lex.Kind==CloseLex ) CloseCount=CloseCount-1;
		else if ( Lex.Kind==OpenLex ) CloseCount=CloseCount+1;
		else if ( (Lex.Kind == LexWanted) && (CloseCount==1) )
			CloseCount = 0;
		else if ( Lex.Kind == LexEOF )
		{
			Error(ErrEOF,Lex.Pos);
			CloseCount=0;
		}
	}
	Error(ErrSkipStopped,Lex.Pos);
	if ( Lex.Kind == LexWanted )
	{ 
		RelLex(); 
		NextLex() ;
	}
}

RepType PValue();

RepType ValueList()
/*	Parse a list of potentially labelled values.	*/
{	RepType ThisVal;
	int Unresolved;
	RepType Ret;
	RepType FakeRef;
	int TempOK;

	Unresolved = 0;
	TempOK = OK;
	OK = 1;
	Ret = MakeSeq((SeqType)NULL,Lex.Pos);
	while (OK)
	    {
		ThisVal = PValue();
		if ( OK ) {
			Ret->UnionField.seqVal =
				AddSeq(Ret->UnionField.seqVal,ThisVal);
			if ( ThisVal->Kind == RepLabelRef ) {
				if ( Unresolved==0 )
					FakeRef = FakeLabel(Ret);
				Unresolved = Unresolved+1;
				DelaySeqRef(
					Ret->UnionField.seqVal,
					ThisVal->UnionField.LabelField,
					FakeRef->UnionField.LabelField,
					ThisVal->Pos);
			}
		}
	}
	if ( Unresolved != 0 )
	{	FakeRef->UnionField.LabelField->Unresolved = Unresolved;
		Ret = FakeRef;
	}
	OK = TempOK;
	return(Ret);
}

RepType Node();	/*	Parse a node.	*/

RepType Value()
/*	Parse a value.  In this routine, tokens must not be
	released by RelLex, since they are used to form
	string values.
*/
{
	RepType Val;

	OK = 1;
	if ( Lex.Kind == LexInteger )
	{ 
		Val = MakeVal(AtrInteger,Lex); 
		NextLex() ;
	}
	else if ( Lex.Kind == LexRational )
	{ 
		Val = MakeVal(AtrRational,Lex); 
		NextLex() ;
	}
	else if ( Lex.Kind == LexString )
	{ 
		Val = MakeVal(AtrString,Lex); 
		NextLex() ;
	}
	else if ( IsLex(LexTrue) ) Val = MakeBool(1,Lex.Pos);
	else if ( IsLex(LexFalse) ) Val = MakeBool(0,Lex.Pos);
	else if ( IsLex(LexOpenBrace) ) {
		Val = ValueList();
		if ( ! IsLex(LexCloseBrace) ) {
			OK = 0;
			Error(ErrBraceExpected,Lex.Pos);
		}
	}
	else if ( IsLex(LexOpenAngleBracket) ) {
		Val = ValueList();
		if ( ! IsLex(LexCloseAngleBracket) ) {
			OK = 0;
			Error(ErrAngleExpected,Lex.Pos);
		}
	}
	else Val = Node();
	if (OK) DEBUG(("Value returns Kind %d, Line %d, String %s\n",Val->Kind,
		Val->Pos.line, Val->StringField));
	return(Val);
}

RepType PValue()
/*	Parse potentially labelled values.	*/
{
	RepType Val;
	int Labelled;
	Lexeme Name;

	if ( Lex.Kind == LexLabelRef ) {
		Val = LabelRef(Lex); 
		OK = 1;
		NextLex();
	}
	else {
		if ( Lex.Kind == LexLabelDef ) {
			Labelled = 1;
			Name = Lex;
			NextLex();
		}
		else Labelled = 0;
		Val = Value();
		if ( OK ) if ( Labelled)
		{	SaveLabel(Name,Val);
			if (Val->Kind == RepLabelRef)
				Val = Val->UnionField.LabelField->Val;
		}
	}
	return(Val);
}

struct Name_Val { Lexeme Name; RepType Val; };

struct Name_Val Pair()
/*	Parse an attribute/value pair.	*/
{
	struct Name_Val Ret;

	if ( Lex.Kind == LexName ) {
		Ret.Name = Lex;
		NextLex();
		Ret.Val = PValue();
		if ( ! OK )
			Error(ErrValueExpected,Ret.Name.Pos);
	}
	else OK = 0;
	DEBUG(("Pair returns Name=%s\n",Ret.Name.Token));
	return(Ret);
}

RepType ParseAttributes(A,Ref)
int A;
RepType Ref;
/*	Parse attributes for a node.
	A:	Node kind of node read
*/
{
	PosType ThisPos;
	RepType FakeRef;
	AttrDesc Desc;
	int Unresolved;
	struct Name_Val NV;

	Unresolved = 0;
	FakeRef = NULL;
	while (! IsLex(LexCloseSquareBracket))
	    {
		ThisPos = Lex.Pos;
		NV = Pair();
		if ( OK ) { /* each attr/value pair */
			Desc = FindAttribute(A,NV.Name.Token);
			if ( OK ) {
				if ( NV.Val->Kind == RepLabelRef ) {
					if ( Unresolved==0 )
						FakeRef = FakeLabel(Ref);
					Unresolved = Unresolved+1;
					DelayedRef(
					Ref->UnionField.NodeField,
					Desc,
					NV.Val->UnionField.LabelField,
					FakeRef->UnionField.LabelField,
					ThisPos);
				}
				else (*GenericAttrStore)(Ref->UnionField.NodeField,
				Desc,NV.Val);
			}
		}
		if ( ! IsLex(LexSemiColon) )
		{
			if ( Lex.Kind!=LexCloseSquareBracket ) {
				Error(ErrSemiColonExpected,Lex.Pos);
				SkipLex(LexSemiColon,
				LexCloseSquareBracket,
				LexOpenSquareBracket);
			}
		}
	}
	if ( Unresolved != 0 ) {
		Ref = FakeRef;
		Ref->UnionField.LabelField->Unresolved = Unresolved;
	}
	return Ref;
}


RepType Node()
/*	Parse a node.	*/
{
	RepType Ref;
	int A;
	NodeType TempRef;

	OK = 1;
	if ( Lex.Kind != LexName ) OK = 0;
	else { /* parse the node */
		A = FindNodeType(Lex.Token);
		if ( OK ) TempRef = (*GenericNodeAlloc)(A);
		else {
			TempRef = NULL;
			Error(ErrBadNodeType,Lex.Pos);
		}
		Ref = MakeNode(TempRef,Lex.Pos);
		RelLex();
		NextLex();
		if ( IsLex(LexOpenSquareBracket) )
		{ /* find attributes */
			if ( OK ) Ref = ParseAttributes(A,Ref);
			else SkipLex(LexCloseSquareBracket,
			LexEOF, LexEOF);
		}
	}
	return(Ref);
}

int LValueList()
/*	Parse a list of (potentially) labelled values
	Returns TRUE if there were no problems during parsing.
*/
{
	int Ret;
	Lexeme Name;
	RepType TempVal;

	Ret = 1;
	while (Lex.Kind == LexLabelDef)
	    {
		Name = Lex;
		NextLex();
		TempVal = Value();
		if ( OK ) SaveLabel(Name,TempVal);
		else Ret = 0;
	}
	return(Ret);
}

RepType NodeRef()
/*	Parse a node reference.	*/
{
	RepType Ref;
	if ( Lex.Kind==LexLabelRef ) {
		Ref = LabelRef(Lex);
		NextLex();
		OK = 1;
	}
	else if ( Lex.Kind==LexLabelDef ) {
		Lexeme Name;
		Name = Lex;
		NextLex();
		Ref = Node();
		if ( OK )
		{	SaveLabel(Name,Ref);
			if (Ref->Kind == RepLabelRef)
				Ref = Ref->UnionField.LabelField->Val;
		}
	}
	else if ( Lex.Kind==LexEOF ) {
		Error(ErrNodeExpected,Lex.Pos);
		OK = 0;
	}
	else Ref = Node();
	return(Ref);
}

NodeType Reader(InFile)
FILE * InFile;
{	NodeType Root;
	int CallOK;
	RepType TempRoot;
	Lexeme TempLex;
	int c;

	/*	Main body of reader
		Read a data structure from standard input && return its root
	*/


	/* check if there are any characters in the input file,
	   if not, return a NULL				*/
	
	while (isspace(c = getc(InFile))) ;
	if ((c == EOF) || (c == '#')){	/* empty input file */
	    OK = 0;
	    return (NULL);
	}
	else ungetc(c, InFile);	/* put character back */

	ErrInit();
	LexInit(InFile);
	Input = InFile;
	NextLex();
	TempLex.Pos = Lex.Pos;
	LabelInit();
	TempRoot = NodeRef();
	CallOK = OK;
	TempLex.Token = NULL;
	OK = 0;
	if ( CallOK ) { /* check list of labelled values */
		if ( TempRoot->Kind==RepLabelRef )
			TempLex.Token = TempRoot->UnionField.LabelField->Name;
		if ( Lex.Kind == LexEOF ) OK = 1;
		else OK = LValueList();
	}
	if ( Lex.Kind != LexEOF ) Error(ErrEOFExpected,Lex.Pos);
	if ( CallOK ) {
		if ( TempLex.Token != NULL ) TempRoot = LabelRef(TempLex);
		if ( ! LabelFinish() ) OK = 0;
		if ( TempRoot->Kind == RepNode )
		{	Root = TempRoot->UnionField.NodeField;
		}
		else {
			Root = NULL; /*root is unresolved forward ref*/
			Error(ErrNoRoot,TempLex.Pos);
			OK = 0;
		}
	}
	else
		if ( ! LabelFinish() ) OK = 0;
	Lex = TempLex;
	RelLex();
	ErrFinish();
	return(Root);
}
