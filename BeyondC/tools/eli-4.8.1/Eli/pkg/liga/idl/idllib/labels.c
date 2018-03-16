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

static char rcsid[] = "$Id: labels.c,v 1.4 1997/08/29 08:38:08 mjung Exp $";

#include <stdio.h>
#include <string.h>
#include "global.h"
#include "reader.h"

#undef FreeHeap
#define FreeHeap(x)
#define LTABSIZ 1024

LabelRefType LabelTable[LTABSIZ];
extern PF_AttrStore GenericAttrStore;

int hash(S)
register char *S;
{	register int i;
	for (i=0 ; *S ; i += (*S) * (*S) , S++);
	return(i & (LTABSIZ-1));
}

# ifdef TEST
main()
{	char s[30];
	scanf("%s",s);
	while ( ! feof(stdin) )
	{	printf("%s hashes to %d\n",s,hash(s));
		scanf("%s",s);
	}
}
# else

/* label handling functions */

enum LErrType { ErrUnresolvedLabel, ErrUnresolvedKids, ErrBadLabelType };

void LError(E,S)
enum LErrType E;
String S;
{	switch(E) {
	case ErrUnresolvedLabel:
		fprintf(stderr,"Label Error: Unresolved label (%s)\n",S);
		break;
	case ErrUnresolvedKids:
		fprintf(stderr,
		"Label Error: generated label with unresolved elements (%s)\n",
		S);
		break;
	case ErrBadLabelType:
		fprintf(stderr,
		"Label Error: bad label type in forward reference\n");
		break;
	default:
		fprintf(stderr,"Label Error: unknown error type %d (%s)\n",
			E,S);
	}
}

void FixUpRefs(MyLabel,P)
LabelRefType MyLabel;
PosType P;
/* Fix up each forward reference with the given value.
 * Decrement the Unresolved member of the parent of each forward reference;
 * if it's 0, then call FixUpRefs on the parent, since it can now be safely
 * generated.  Delete each forward reference.
 */
{	register LabelType tmp;
	register LabelType L;
	register RepType Value;

	L = MyLabel->RefList;
	MyLabel->RefList = NULL;
	Value = MyLabel->Val;
	while (L != NULL)
	{	switch(L->Kind) {
		case SeqLabel:	*(L->UnionField.SLabel) = Value;
				break;
		case NodeLabel:	(*GenericAttrStore)(L->UnionField.NLabel.NodeField,
					L->UnionField.NLabel.Desc,
					Value);
				break;
		default:	LError(ErrBadLabelType,NULL);
		}
		switch (L->parent->Unresolved) {
		case 0:	break;
		case 1:	L->parent->Unresolved = 0;
			FixUpRefs(L->parent,P);
			if (L->parent->Name == NULL) FreeHeap(L->parent);
			break;
		default: -- L->parent->Unresolved;
		}
		tmp = L->next;
		FreeHeap(L);
		L = tmp;
	}
}

/* blank label used to initialize new labels */
struct LabelRefRecord BlankLabel = { NULL, NULL, 0, 0, NULL, NULL };

/* find the label in the LabelTable, if it is not found create a new
   entry in the appropriate position. The label is hashed to find the 
   index into the table. Collisions are resolved by chaining. The labels
   in a chain are sorted in reverse alphabetic order			*/

LabelRefType FindLabel(Lex)
Lexeme Lex;
{	register LabelRefType R,P;
	register int cmp,h;


	h = hash(Lex.Token);
	R = LabelTable[h];
	if (R == NULL)		/* create new entry in table */
	{	R = (LabelRefType)
			GetHeap(sizeof(struct LabelRefRecord));
		LabelTable[h] = R;
		P = NULL;
	}
		/* check if it is equal to first in list */
	else if ((cmp = strcmp(R->Name,Lex.Token)) == 0) 
	{	/* FreeHeap(Lex.Token); */
		return R;
	}
		/* check if it should go before 1st in list */
	else if (cmp < 0)	
	{	P = R;
		R = (LabelRefType)
			GetHeap(sizeof(struct LabelRefRecord));
		LabelTable[h] = R;
	}
		/* find the label or the one it goes before */
	else
	{	P = R;
		R = R->next;
		cmp = 1;
		while ((R != NULL) && ((cmp = strcmp(R->Name,Lex.Token)) > 0))
		{	P = R;
			R = R->next;
		}
		if (cmp!=0)	/* didn't find it */
		{	P->next = (LabelRefType)
				GetHeap(sizeof(struct LabelRefRecord));
			P->next->next = R;
			R = P->next;
			P = R->next;
		}
		else	/* found it */
		{	/* FreeHeap(Lex.Token); */
			return R;
		}
	}
	*R = BlankLabel;	/* initialize new to blank label */
	R->next = P;
	R->Name = NewString(Lex.Token);
	return R;
}

void ReplaceLabel(Old,New)
register LabelRefType Old, New;
{	register LabelRefType R, P;
	int h;

	h = hash(Old->Name);
	P = NULL;
	R = LabelTable[h];
	while (R != Old)
	{	P = R;
		R = R->next;
	}
	if (P == NULL)	/* Old was first */
		LabelTable[h] = New;
	else	/* Old appeared later in chain */
		P->next = New;
	New->next = R->next;
	New->Name = R->Name;
	New->RefList = R->RefList;
	FreeHeap(R);
	return;
}

void SaveLabel(Lex,Value)
Lexeme Lex;
register RepType Value;
/* Find the label in the table.  Set the Val member to the Value arg,
 * and resolve every forward reference in the RefList member.
 */
{	register LabelRefType R;

	R = FindLabel(Lex);
	/* If we are passed a label reference as the value, it is a generated
	 * label.  All labels for which the fake label is the parent must now
	 * refer to the real label.  This is accomplished by replacing the
	 * real label that FindLabel returns with the generated label.  The
	 * forward references cannot be resolved yet, since the generated label
	 * has at least one unresolved entry.  It will be resolved when the
	 * last unresolved entry is resolved.
	 */
	if (Value->Kind == RepLabelRef)
	{	ReplaceLabel(R,Value->UnionField.LabelField);
		R = Value->UnionField.LabelField;
	}
	else
		R->Val = Value;
	R->Val->Labelled = 1;
	FixUpRefs(R,Lex.Pos);
	return;
}

RepType LabelRef(Lex)
Lexeme Lex;
/* Find the label in the label table.  If the label is defined and completely
 * resolved, return the representation of the labelled value.  If the label
 * is not defined, return the label reference associated with the label.
 */
{	register LabelRefType R;
	register RepType V;

	R = FindLabel(Lex);
	if ((R->Val) && (R->Unresolved == 0)) return(R->Val);
	else
	{	V = (RepType)GetHeap(sizeof(struct RecRepType));
		V->Pos = Lex.Pos;
		V->StringField = NULL;
		V->Kind = RepLabelRef;
		V->UnionField.LabelField = R;
		return(V);
	}
}

RepType FakeLabel(ForVal)
RepType ForVal;
/* Fake labels are what Lamb calls "generated" labels.  They are created
 * for nodes, sequences, and sets which contain unresolved labels.  The
 * effect is to treat these values as if they were themselves unresolved
 * label references, to be resolved when all their internal labelled values
 * are resolved.
 *
 * Create a new RepType with variant RepLabelRef.  Create a new
 * LabelRefRecord, with no name, Generated=true, and Val=ForVal.
 * Set the new RepType's LabelField to point to the new LabelRefRecord,
 * and return it.
 */
{	register RepType V;
	register LabelRefType R;

	R = (LabelRefType)GetHeap(sizeof(struct LabelRefRecord));
	V = (RepType)GetHeap(sizeof(struct RecRepType));
	*R = BlankLabel;
	R->Generated = 1;
	R->Val = ForVal;
	V->Pos = ForVal->Pos;
	V->StringField = NULL;
	V->Kind = RepLabelRef;
	V->UnionField.LabelField = R;
	return V;
}

void DelaySeqRef(List,MyLabel,Fake,Where)
register SeqType List;
register LabelRefType MyLabel,Fake;
PosType Where;
/* Find the end of the list.  Add a pointer to the value field of the end
 * of the list to the label table entry for MyLabel.  Its parent is set
 * to Fake, and its Pos to Where.
 */
{	register LabelType L;
	while (List->next) List = List->next;
	L = (LabelType)GetHeap(sizeof(struct LabelRecord));
	L->next = MyLabel->RefList;
	MyLabel->RefList = L;
	L->parent = Fake;
	L->Pos = Where;
	L->Kind = SeqLabel;
	L->UnionField.SLabel = &(List->value);
	return;
}

void DelayedRef(NType,Desc,MyLabel,Fake,Where)
NodeType NType;
AttrDesc Desc;
LabelRefType MyLabel, Fake;
PosType Where;
/* Add an entry with NType and the attribute number to the list of
 * forward references.  The Parent of the MyLabel entry should be Fake,
 * and its Pos should be Where.
 */
{	register LabelType L;
	L = (LabelType)GetHeap(sizeof(struct LabelRecord));
	L->next = MyLabel->RefList;
	MyLabel->RefList = L;
	L->parent = Fake;
	L->Pos = Where;
	L->Kind = NodeLabel;
	L->UnionField.NLabel.NodeField = NType;
	L->UnionField.NLabel.Desc = Desc;
	return;
}

void LabelInit()
/* Initially, the label table is initialized to all nulls by the rules of C;
 * after that, it is set to all nulls by LabelFinish.  There's nothing to do.
 */
{	
	return;
}

int LabelFinish()
/* For every entry of the label table, check for unresolved labels and
 * cause an error (and set OK = 0) if so.  Regardless, delete it and set
 * its pointer in the table to NULL.
 */
{	register int i;
	register LabelRefType R,tmp;
	int LOK;

# ifdef DEBUG
	PrintLabelTable(LabelTable);
# endif
	LOK = 1;
	for (i = 0; i < LTABSIZ; ++i)
	{	R = LabelTable[i];
		while (R != NULL)
		{	if (R->Val == NULL)
			{	LOK = 0;
				LError(ErrUnresolvedLabel,R->Name);
			}
			else
			{	R->Val->Labelled = 0;
				DelRep(R->Val);
				if (R->Unresolved)
				{	LOK = 0;
					LError(ErrUnresolvedKids,R->Name);
				}
			}
			tmp = R->next;
			/* FreeHeap(R->Name);  */
			FreeHeap(R);
			R = tmp;
		}
		LabelTable[i] = NULL;
	}
	return LOK;
}

# endif
