static char RCSid[] = "$Id: djset.c,v 1.6 2013/11/12 18:48:28 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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

/* see Ch 2 of D.S. and Network algorithms R.E. Tarjan */

#include "dj.h"

struct el DjSets[SETSIZE];
short Next[SETSIZE];	/* to chain together elements in a set */
int NDistinctSets = 0;

void
makeDJsets()	/* make SETSIZE singleton sets */
{
int x;

	NDistinctSets = SETSIZE;

	for(x=0; x<SETSIZE; x++) {
		Next[x] = x;
		DjSets[x].parent = x;
		DjSets[x].rank = 0;
		DjSets[x].size = 1;
		}
}


int
findWhichSet(x)   /* pathcompression as a side effect */
/*findWhichSet(DjSets,x)
struct el DjSets[];*/
int x;
	{
	if( x != DjSets[x].parent)
	  DjSets[x].parent = findWhichSet(DjSets[x].parent);
	return (DjSets[x].parent);
	}

int
linkSets(x,y)
/*linkSets(DjSets,x,y)
struct el DjSets[];*/
int x,y;
	{
	int t;
	int i;
	if(DjSets[x].rank > DjSets[y].rank)
		{ t=x; x=y; y=t; }	/* swap so x is not larger */
	else if((DjSets[x].rank = DjSets[y].rank))
		DjSets[y].rank++;		/* log of num elements */

	/* update next array.
	** Walk down chain of smaller set to its end and set link to
	** the Next of larger set.
	** Store Next head of smaller set.
	*/
	i = Next[x];
	while(i != Next[i])
		i = Next[i];
	Next[i] = Next[y];	/* link chains together */
	Next[y] = x;

	--NDistinctSets;
	DjSets[y].size += DjSets[x].size;
	return(DjSets[x].parent = y);
	}


void
pntDJset(fp)
FILE *fp;
{
int c;
for(c=0; c<SETSIZE; c++) {
	GPNT(fp,c, "", "");
	fprintf(fp,"  Next[c]=%d parent=%d size=%d\n",
			Next[c], DjSets[c].parent, DjSets[c].size);
	}
}

#ifdef TEST
main()
{
makeDJsets();
linkSets(2,4);
pntDJset(stdout);
}
#endif
