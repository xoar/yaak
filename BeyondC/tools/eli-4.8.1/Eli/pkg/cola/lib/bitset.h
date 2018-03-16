/*
** $Id: bitset.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
*/

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

/*************************************************************************/
/**	Modul:		zur Verwaltung von Bit-Mengen			**/
/**	Datum:		9.12.1988					**/
/**	Autor:		Rainer Sievers					**/
/**	Last Edit:	24.04.89 durch Karl Prott			**/
/*************************************************************************/

#ifndef bitset_DEF
#define bitset_DEF



typedef struct
	{ short  size;
	  char s[1];
	} *BitSet;

typedef char Bool;

#define TRUE	1
#define FALSE	0


#define IsElemInSet(elem, set)	((set)->s[(int)((elem)/8)] & 1<<(elem)%8)
#define FreeSet(set)		(free((char *)set))

extern BitSet	MakeEmptySet  (/* size: int */);
extern BitSet	MakeFullSet   (/* size: int */);
extern BitSet	AddSetToSet   (/* from, to: BitSet */); /* to = from + to */
extern BitSet	SubSetFromSet (/* from, to: BitSet */); /* to = to - from */
extern BitSet	IntersectSet  (/* from, to: BitSet */); /* to = to & from */
extern BitSet	AddElemToSet  (/* elem: int, set: BitSet */);
extern BitSet	SubElemFromSet(/* elem: int, set: BitSet */);
extern BitSet	MakeSetCopy   (/* set: BitSet */);
extern BitSet	InitSetToSet  (/* from, to: BitSet */); /* to = from */
/*
extern Bool	IsElemInSet   (   elem: int, set: BitSet   ); MAKRO! */
extern Bool	IsSingleElemInSet
			      (/* elem: int, set: BitSet */);
extern Bool	IsPartSet     (/* set1, set2: BitSet */);
extern Bool	DoIntersectSet(/* set1, set2: BitSet */);
extern Bool	IsEqualSet    (/* set1, set2: BitSet */);
extern Bool	IsEmptySet    (/* set */);

/* arr[0],...,arr[EvalBitSet()-1] are all elements, which are in 'set' */
extern unsigned short	EvalBitSet(/* short arr[set->size]; BitSet set */);

#ifdef DEBUG_BIT
extern char	*PrintSet      (/* set: BitSet */);
#endif


#endif  /* of bitset_DEF */
