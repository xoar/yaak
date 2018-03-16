static char RCSid[] = "$Id: print.c,v 1.8 2013/11/12 18:48:28 profw Exp $";
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

#include "dj.h"

/* compactly print the elements of set 
** Eg.  10.a-z0-9
** Control characters are printed as decimal numbers with "."
*/
void
printElsOfSet(fp,set)
FILE *fp;
char set[SETSIZE];
{
	int i = 0;
	while(i<SETSIZE-1) {
		if( set[i] )
			if(set[i+1]) {
				GPNT(fp,i," ", "-");
				i++;
				while(i<SETSIZE-1 && set[i+1])
					i++;
				GPNT(fp,i,"", "");
				i++;
				}
			else {
				GPNT(fp,i," ", "");
				i++;
				}
		else
			i++;
		}/*endwhile*/

	if(i == SETSIZE-1 && set[i] ) {
		GPNT(fp,i," ", "");
	}
}



/* Consider "array" to be a pointer to some type of array,
** print the name first, then
** compactly print the indexes of the non-zero elements.
** "FINAL STATES 1 2 4-8 19"
*/
void
pBoolean(array, name, elsize, max,fp)
char array[];
char *name;
int elsize;
int max;
FILE *fp;
{
int i=0;
char  *C;	/* character array */
short *S;	/* short array */
long  *L;	/* long array */
#define BODY(type) \
	fprintf(fp,"%s ",name);\
	while(i<max-1) {\
		if( type[i] )\
			if(type[i+1]) {\
				fprintf(fp," %d-", i);\
				i++;\
				while(i<max-1 && type[i+1])\
					i++;\
				fprintf(fp,"%d", i++);\
				}\
			else {\
				fprintf(fp," %d", i++);\
				}\
		else\
			i++;\
		}\
	if(i == max-1 && type[i] )\
		fprintf(fp," %d", i++);\
	fprintf(fp,"\n")

switch(elsize) {
	case sizeof(char):
		C = array;
		BODY(C);
		break;
	case sizeof(short):
		S = (short *)array;
		BODY(S);
		break;
	case sizeof(long):
		L = (long *)array;
		BODY(L);
		break;
	}
}

#define JAMMED(s) (StateHead[s].p_jam.setsize==SETSIZE)
#define lexgoto(state, chr)	(transarray[state*SETSIZE+chr])
void
prtTrans()
{
	register int s, c;	/* state, character */
	register int i;
	char pset[SETSIZE];
	struct p_head *sh;
	int firstOfSet;
	short *transarray;

	/* Build a 2D trans table from the partition structure.
	** This is EXPENSIVE, but prtTrans is only used for debugging
	*/
	transarray = (short *)malloc((unsigned)(Nstates*SETSIZE*sizeof(short)));
	if(transarray == NULL) {
		printf("cannot alloc memory to print trans tbl\n");
		return;
		}

	for(s=0; s<Nstates; s++){
		if( (sh= &StateHead[s].p_loop)->setsize){
			ClearSet(pset);
			loadSetFromPart(sh, pset);
			for(c=0; c<SETSIZE; c++)
				if(pset[c])
					lexgoto(s,c) = sh->desttarget;
			}
		sh = &StateHead[s].p_out;
		for(i=0; i<StateHead[s].numout; i++) {
			ClearSet(pset);
			loadSetFromPart(sh, pset);
			for(c=0; c<SETSIZE; c++)
				if(pset[c])
					lexgoto(s,c) = sh->desttarget;
			sh = sh->next;
			}
		}/*end for(s=0; s<Nstates ...*/
		

	printf("\n\n  ");
	for(s=0; s<Nstates; s++)       /* header */
		if(!JAMMED(s)) printf("%3d",s);putchar('\n');

	c = firstOfSet = 33; /* don't bother with control chars */
	while(c<255) {
		printf("%c ", firstOfSet);
#define PNT(ch)	for(s=0; s<Nstates; s++)\
		    if(!JAMMED(s)){\
			if(lexgoto(s,ch) == 0)\
				printf("   ");\
			else\
				printf("%3d",lexgoto(s,ch));\
		    }
		PNT(firstOfSet);

more:		c++;
		for(s=0; s<Nstates; s++)
			if(lexgoto(s,c) != lexgoto(s,c-1))
				goto done;
		goto more;
done:
		printf(" %c-%c\n", firstOfSet, c-1);
		firstOfSet = c;
		}

	printf("  ");
	for(s=0; s<Nstates; s++)       /* header */
		if(!JAMMED(s)) printf("%3d",s);putchar('\n');
}


void
outIntArray(fd,str,A,len)
FILE *fd;
char *str;
int A[];
int len;
{
int c;

fprintf(fd,"\nstatic short %s[%d] = {\n", str, len);
for (c = 0; c < SETSIZE; c+=8) {
    if(c<len-8)
	fprintf(fd,"%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d, ",
	A[c],A[c+1],A[c+2],A[c+3],A[c+4],A[c+5],A[c+6],A[c+7]);
    else
	fprintf(fd,"%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d};",
	A[c],A[c+1],A[c+2],A[c+3],A[c+4],A[c+5],A[c+6],A[c+7]);
	fputs("    /* ",fd);
	GPNT(fd, c+0, " ", "");
	GPNT(fd, c+1, " ", "");
	GPNT(fd, c+2, " ", "");
	GPNT(fd, c+3, " ", "");
	GPNT(fd, c+4, " ", "");
	GPNT(fd, c+5, " ", "");
	GPNT(fd, c+6, " ", "");
	GPNT(fd, c+7, " ", "");
	fputs(" */\n",fd);
	}
}

void
outShortArray(fd,str,A,len)
FILE *fd;
char *str;
short A[];
int len;
{
int c;

fprintf(fd,"\nstatic short %s[%d] = {\n", str, len);
for (c = 0; c < SETSIZE; c+=8) {
    if(c<len-8)
	fprintf(fd,"%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d, ",
	A[c],A[c+1],A[c+2],A[c+3],A[c+4],A[c+5],A[c+6],A[c+7]);
    else
	fprintf(fd,"%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d};",
	A[c],A[c+1],A[c+2],A[c+3],A[c+4],A[c+5],A[c+6],A[c+7]);
#ifdef COMMENTS
	fputs("    /* ",fd);
	GPNT(fd, c+0, " ", "");
	GPNT(fd, c+1, " ", "");
	GPNT(fd, c+2, " ", "");
	GPNT(fd, c+3, " ", "");
	GPNT(fd, c+4, " ", "");
	GPNT(fd, c+5, " ", "");
	GPNT(fd, c+6, " ", "");
	GPNT(fd, c+7, " ", "");
	fputs(" */",fd);
#endif
	fputc('\n',fd);
	}
}



/*
** load the set array, from the partition data structure.
*/
void
loadSetFromPart(sh, set)
struct p_head *sh;
char set[SETSIZE];
{
register int i;

	ClearSet(set);

        switch(sh->flag) {
	case SET_ONE:
		AddElmToSet(sh->ch, set);
		break;
	case SET_LIST:
		for(i=0; i< sh->setsize; i++)
		    AddElmToSet(SetMemArr[sh->first + i], set);
		break;
	case SET_CONSECUTIVE:
		for(i=0; i< sh->setsize; i++)
			AddElmToSet(i + sh->ch, set);
		break;
	}

}
