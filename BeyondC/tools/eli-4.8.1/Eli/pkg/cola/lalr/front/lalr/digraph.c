/* $Id: digraph.c,v 1.4 1997/08/29 08:06:16 mjung Exp $ */

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


#include <stdio.h>

#include "bitset.h"
#include "global.h"	/* needed for privatlib.h: types String and Boolean */
#include "comar.h"
#include "cmrlib.h"
#include "digraph.h"
#include "privatlib.h"

static char rcsid[] = "$Id: digraph.c,v 1.4 1997/08/29 08:06:16 mjung Exp $";

static	stacktype	*R=(stacktype *)NULL;	/* relation R: array of lists */

/* N[x]=0	: vertex x is unmarked
 * 0<N[x]<Infinity: vertex x is under active consideration
 * N[x]=Infinity: the SCC (strong connectly component) of x 
 *		  has already been found
 */
static	Cardinal	*N;	/* N[0...Max-1]: see DiGraph and Traverse */
#define	Infinity	((Cardinal) -1)

static	BitSet	*F;	/* F[0...Max-1]: array of equal sized bitsets */


void	InitRelation(card)
Cardinal	card;
{
  if ( (R = (stacktype *)calloc(card, sizeof(stacktype))) == (stacktype *)NULL )
    {
      INT_ALLOC_ERR("InitRelation()");
      exit(1);
    }
  return;
}  /* of InitRelation() */


void    AddToRelation(a,b)
Cardinal	a,b;
{
  R[a] = push(R[a], (eltype)(unsigned long)b);
  return;
} /* of AddToRelation() */


void	FreeRelation()
{
  (void)free(R);
  R = (stacktype *)NULL;
} /* of FreeRelation() */


static	void	Traverse(x)
Cardinal	x;
{
  Cardinal	d, y;

static	Cardinal	depth = 0;
/* let S be an initially empty stack of elements of X */
static	stacktype S = (stacktype)NULL;

  S = push(S,(eltype)(unsigned long)x);	/* Push x on S */
  N[x] = d = ++depth;		/* d: Depth of S; assign N[x] <- d */

  while ( !empty(R[x]) )	/* for all y of X such that xRy */
  {				/* do */
    y = (Cardinal)(unsigned long)top(R[x]);
    R[x] = pop(R[x]);

    if ( N[y] == 0 )		/* if N[y]=0 then call Traverse y fi */
	Traverse(y);
    if ( N[x] > N[y] )		/* assign N[x] <- Min(N[x],N[y]) */
	N[x] = N[y];
    (void)AddSetToSet(F[y],F[x]); /* F[x] <- F[x] union F[y] */
  }				/* od */

  if ( N[x] == d )		/* if N[x]=d then */
    do
    {
	y = (Cardinal)(unsigned long)top(S);
	S = pop(S);
	depth--;
	N[y] = Infinity;	/* repeat assign N(Top of S) <- Infinity */
	(void)AddSetToSet(F[x],F[y]);	/* F(Top of S) <- F[x] */
    }  while ( y != x );	/* until (Pop of S) = x */

  return;
   
}  /* of Traverse() */


void	DiGraph(Max, F0)
Cardinal	Max;
BitSet	*F0;	/* F0[0...Max-1] */
{
  Cardinal	x;

  /* let N be an array (of size Max) of zeros indexed by elements of X */
  if ( (N = (Cardinal *)calloc(Max, sizeof(Cardinal))) == (Cardinal *)NULL )
    {
      INT_ALLOC_ERR("DiGraph()");
      exit(1);
    }

  /* for all x of X assign F[x] <- F0[x] */
  F = F0;

  /* for all x of X such that N[x]=0 do call Traverse x od */ 
  for (x=0; x<Max; x++)
    if ( N[x] == 0 )
	Traverse(x);

  (void)free(N);
  return;
}  /* of DiGraph() */



