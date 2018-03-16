/*
** $Id: bitset.c,v 1.10 2007/02/23 12:29:57 peter Exp $
*/
static char rcs_id[]= "$Id: bitset.c,v 1.10 2007/02/23 12:29:57 peter Exp $";

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
/**     Last Edit:	02.05.89  durch Karl Prott                      **/
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"

BitSet
MakeEmptySet(size)
int size;
{
  BitSet Temp;
  int     i;
			/* sizeof(*Temp) includes the size of one char */
  Temp 		= (BitSet)malloc((int)((size-1)/8)+sizeof(*Temp));
  Temp->size    = size;
  for(i=(size-1)/8; i>=0; i--)
    Temp->s[i] = 0;
  return(Temp);
}

BitSet
MakeFullSet(size)
int size;
{
  BitSet Temp;
  int     i;

  Temp = (BitSet)malloc((int)((size-1)/8)+sizeof(*Temp));
  Temp->size    = size;
  for(i=size/8-1; i>=0; i--)
    Temp->s[i] = 255;
  if(size%8>0)
    Temp->s[size/8] = (1<<size%8)-1;
  return(Temp);
}


BitSet
AddSetToSet(set1, set2)
BitSet set1, set2;
{ char *t1, *t2;
  int	i;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'AddSetToSet'\n");
#endif

  i  = set1->size;
  t1 = set1->s;
  t2 = set2->s;
  while(i>0)
  { *(t2) |= *(t1++);
    t2++;
    i -= 8;
  }
  return(set2);
}

BitSet
SubSetFromSet(set1, set2)
BitSet set1, set2;
{ char *t1, *t2;
  int	i;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'SubSetFromSet'\n");
#endif

  i  = set1->size;
  t1 = set1->s;
  t2 = set2->s;
  while(i>0)
  { *t2 = ~(*t1++) & *t2;
    t2++;
    i -= 8;
  }
  return(set2);
}

BitSet
IntersectSet(set1, set2)
BitSet set1, set2;
{ char *t1, *t2;
  int	i;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'Schnittmenge'\n");
#endif

  i  = set1->size;
  t1 = set1->s;
  t2 = set2->s;
  while(i>0)
  { *(t2) &= *(t1++);
    t2++;
    i -= 8;
  }
  return(set2);
}

BitSet
AddElemToSet(i, s)
int	i;
BitSet  s;
{
#ifdef DEBUG_BIT
  if(i<0 || s->size<=i)
    fprintf(stderr, "Error: Elem out of range in 'AddElemToSet'\n");
#endif

  s->s[i/8] |= (1<<(i%8));
  return(s);
}

BitSet
SubElemFromSet(i, s)
int    i;
BitSet s;
{
#ifdef DEBUG_BIT
  if(i<0 || s->size<=i)
    fprintf(stderr, "Error: Elem out of range in 'SubElemFromSet'\n");
#endif

  s->s[i/8] &= ~(1<<(i%8));
  return(s);
}

BitSet
MakeSetCopy(set)
BitSet set;
{
  BitSet Temp;
  int    i;

  Temp = (BitSet)malloc((int)((set->size-1)/8)+sizeof(*Temp));
  Temp->size = set->size;
  for(i=(set->size-1)/8; i>=0; i--)
    Temp->s[i] = set->s[i];
  return(Temp);
}

BitSet
InitSetToSet(set1, set2)
BitSet set1, set2;
{ char *t1, *t2;
  int	i;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'InitSetToSet'\n");
#endif

  i  = set1->size;
  t1 = set1->s;
  t2 = set2->s;
  while(i>0)
  { *(t2) = *(t1++);
    t2++;
    i -= 8;
  }
  return(set2);
}


/*		(Makro in cg_set.h)
Bool
IsElemInSet(i, s)
int	i;
BitSet  s;
{
  return( (s->s[i/8] & 1<<i%8) != 0);
}
*/

Bool
IsSingleElemInSet(elem, set)
int    elem;
BitSet set;
{
  int i;

  i = -1;
  while(i<elem-8)
  { if(set->s[i/8] != 0) return(FALSE);
    i += 8;
  }
  if(set->s[i/8] != 1<<elem%8) return(FALSE);
  i += 8;
  while(i<set->size)
  { if(set->s[i/8] != 0) return(FALSE);
    i += 8;
  }
  return(TRUE);
}

Bool
IsPartSet(set1, set2)
BitSet set1, set2;
{
  char *t1, *t2;
  int  size;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'IsPartSet'\n");
#endif

  size = set1->size;
  t1   = set1->s;
  t2   = set2->s;
  while(size>0)
  { if((*(t1++) & ~(*(t2++))) != 0)  return(FALSE);
    size -= 8;
  }
  return(TRUE);
}

Bool
IsEqualSet(set1, set2)
BitSet set1, set2;
{
  char *t1, *t2;
  int  size;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'IsEqualSet'\n");
#endif

  size = set1->size;
  t1   = set1->s;
  t2   = set2->s;
  while(size>0)
  { if(*(t1++) != *(t2++))  return(FALSE);
    size -= 8;
  }
  return(TRUE);
}

Bool
DoIntersectSet(set1, set2)
BitSet set1, set2;
{
  char *t1, *t2;
  int  size;

#ifdef DEBUG_BIT
  if(set1->size != set2->size)
    fprintf(stderr, "Error: Different sets in 'DoIntersectSet'\n");
#endif

  size = set1->size;
  t1   = set1->s;
  t2   = set2->s;
  while(size>0)
  { if(*(t1++) & *(t2++))  return(TRUE);
    size -= 8;
  }
  return(FALSE);
}

Bool
IsEmptySet(set)
BitSet set;
{
  int i;

  i = set->size-1;
  while(i>=0)
  { if(set->s[i/8] != 0) return(FALSE);
    i -= 8;
  }
  return(TRUE);
}

/*	(Makro in cg_set.h)
void
FreeSet(Set)
BitSet Set;
{
  free(Set);
}
*/

unsigned short	EvalBitSet(indexarr, set)
unsigned short	*indexarr;
BitSet	set;
{
  unsigned short
	result = 0,
	index = 0,
	i, j;
  unsigned short
	size, byteno;
  char	part;

  size = set->size;
  byteno = (unsigned short)(size - (unsigned short)1)  /  ((unsigned short)8);
  for ( i = 0; i <= byteno; i++ ) 	/* byte by byte */
    {
      part = set->s[i];
      for ( j=0; j<8; j++ )		/* bit by bit */
	{
          if ( part % 2 )		/* if part is odd */
	    indexarr[result++] = index;
	  part = part >> 1;
	  if ( size < ++index )
	    break;
	}  /* end of for */
    }  /* end of for */

  return(result);
}  /* end of EvalBitSet() */

#ifdef DEBUG_BIT

char	*PrintSet(set)
BitSet set;
{ int i, j;
  static char out[512];

  i = set->size;
  for(j=0; j<i; j++)
    if(IsElemInSet(j, set)) out[j] = 'X';
		       else out[j] = '0';
  out[j] = 0;
  return(out);
}

#endif
