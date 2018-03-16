static char RCSid[] = "$Id: part.c,v 1.8 2009/09/10 16:49:46 profw Exp $";
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

/*       1         2         3         4         5         6         7
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
#include "dj.h"

short SetHead[SETSIZE];
short SetTarget[SETSIZE];	/* state to which transition goes */
short SetHeadJam;
short SetHeadLoop;

struct state_head *StateHead;

#define MEMBER_SPACE 1024	/* Initially room for this many characters,
				** thereafter, double space each realloc.
				*/

int    CurSetMemberSize = MEMBER_SPACE;
unsigned char * SetMemArr;
int    SetMemIdx;	/* first free spot in array */

#define NOTINITIALSTATE	(state>1)

/* bubble - bubble sort a short array in increasing order
 *
 * synopsis
 *   short v[n], n;
 *   bubble( v, n );
 *
 * description
 *   sorts the first n elements of array v and replaces them in
 *   increasing order.
 *
 * passed
 *   v - the array to be sorted
 *   n - the number of elements of 'v' to be sorted
 */

void
bubble( v, n )
short v[];
int n;

{
register int i, j, k;

for ( i = n-1; i > 0; --i )
for ( j = 0; j < i; ++j )
    if ( DjSets[v[j]].size > DjSets[v[j + 1]].size )	/* compare */
	{
	k = v[j];	/* exchange */
	v[j] = v[j + 1];
	v[j + 1] = k;
	}
}



void
mkDJSetFromTransition(state, flexstate)
int state;
int  flexstate[SETSIZE];
{
	register int  c;
	int i;

	static short * Seen = NULL;

	/* alloc some space once */
	if(Seen == NULL) {
		Seen = (short *) malloc((unsigned)Nstates * sizeof(short));
		if(Seen == NULL) {
			(void)fprintf(stderr, "no memory\n"); exit(5);
		}
	}

	/* initialize every time we make partitions*/
	SetHeadJam = -1;
	SetHeadLoop = -1;
	for(i=0; i<Nstates; i++)
		Seen[i] = UNDEF;

	makeDJsets();	/* make SETSIZE singleton sets */
/*   
targets here???? */

	/*
	** link sets with common target transitions.
	*/
	for(c=0; c<SETSIZE; c++){
		int dest;
		dest = flexstate[c];
		SetTarget[c] = dest;/* remem the target destination of c */
		if(Seen[dest]== UNDEF)
			Seen[dest] = c;
		else
			(void)linkSets( c, findWhichSet(Seen[dest]) );
		}

	/* get pointer to current sets.  Make SetHeadJam the jam partition*/
	i = 0;
	for(c=0; c<SETSIZE; c++)
		if(DjSets[c].parent == c){	/* canonical element of the set */
			if( flexstate[c] == 0){	/* error transitions */
				SetHeadJam = c;
				NDistinctSets--;
				}
			else if( flexstate[c] == state){/* selfloop transitions */
				SetHeadLoop = c;
				NDistinctSets--;
				}
			else			/* out transitions */
				SetHead[i++] = c;
			}
	if(i != NDistinctSets)
		printf("Problem, i=%d, NDistinctSets=%d\n", i, NDistinctSets);

	/* sort out partitions in increasing size order */
	bubble(SetHead, NDistinctSets);
}


void
makeAllPartitions()
{
	register int i, j, k;
	int m, state, size;
	int flexstate[SETSIZE];
	size_t count;
	char set[SETSIZE];
	int  tmpIdx;
	struct p_head *cur;
	struct p_head *prev = NULL;

	StateHead =
	    (struct state_head *) malloc((unsigned)Nstates * sizeof(struct state_head));
	if(StateHead == NULL) {
		(void)fprintf(stderr, "no memory for StateHead\n"); exit(8);
	}

	SetMemIdx = 0;
	SetMemArr = allocate_character_array(MEMBER_SPACE);

	/*
	** Create a boolean array to indicate which states
	** are targets of goto transitions.  IE, all non-initial,
	** non-selfloop transitions of the goto matrix.
	*/
	Targets = (char *) malloc((unsigned) Nstates * sizeof(char));
	if(Targets == NULL) {
		(void)fprintf(stderr, "no memory for targets\n"); exit(9);
	}
	for(i=0; i<Nstates; i++)	/* initialize */
		Targets[i] = 0;


	/* for each state ... */
	for(state=0; state<Nstates; state++) {

		count=fread((char *)flexstate, sizeof(int), (size_t)SETSIZE, FlexStateFd);
		if(count != SETSIZE) {
			(void)fprintf(stderr, "Error in Flexreading: count=%d, state=%d\n",(int)count,state);
			exit(10);
			}

		mkDJSetFromTransition(state, flexstate);

		/* assume all are empty */
		StateHead[state].p_jam.setsize = 0;
		StateHead[state].p_loop.setsize = 0;
		StateHead[state].p_out.setsize = 0;

		/*  This maps flex states into GLA index for extcode, pattern
		**  processor and auxscanner.  We assume that flex numbers
		**  accepting states in order encountered starting with 1.
		**  These must match the yy_act case labels in flex.yy.c.
		*/
		StateHead[state].Yindex = AcceptStates[state];


		/*
		** The SetMember storage below needs a little explaination.
		** If the current index plus the size of the set is bigger
		** than the current storage, we need more space.
		** Make CurSetMemberSize twice as big.  Then
		** realloc more space.
		*/

#define CODEBLOCK(L, R) \
		L desttarget = SetTarget[R];\
		L setsize = size = DjSets[R].size;\
		L ch = R;\
		if(size == 1){\
			L flag = SET_ONE;\
			}\
		/* try to use consecutive storage */\
		else	{\
			if(SetMemIdx+size >= CurSetMemberSize){\
			    CurSetMemberSize *= 2;\
			    SetMemArr = reallocate_character_array(\
					SetMemArr,CurSetMemberSize);}\
			ClearSet(set);\
			j = R;		/* load set array */\
			for(k=0; k<size; k++) {\
				AddElmToSet(j, set);\
				j = Next[j];\
				}\
			tmpIdx = SetMemIdx;\
			/* while we are in loop, assume non-consecutive */\
			for(i=0; i<SETSIZE; i++)  /* get first */\
				if(set[i])\
					SetMemArr[SetMemIdx++] = i;\
			/* test for consecutiveness: LAST-FIRST+1 == size */\
			if(SetMemArr[SetMemIdx-1] - SetMemArr[tmpIdx] +1 == size){\
				L flag = SET_CONSECUTIVE;\
				SetMemIdx = tmpIdx;	/* set back */\
				}\
			else {\
				L flag = SET_LIST;\
				L first = tmpIdx;\
				}\
			}

	if(SetHeadJam >=0){
		CODEBLOCK(StateHead[state].p_jam. , SetHeadJam);
		}

	if(SetHeadLoop >=0){
		CODEBLOCK(StateHead[state].p_loop. , SetHeadLoop);
		}

/****begin*out*****/
	StateHead[state].numout = NDistinctSets;
	for(m=0; m<NDistinctSets-1; m++){	/* all but the last */
		/* first alloc, and link in previous */
		cur = (struct p_head *) malloc((unsigned)sizeof(struct p_head));
		if(cur == NULL) {
			(void)fprintf(stderr, "out of mem \n"); exit(19);
		}
		cur->next = prev;

		if(NOTINITIALSTATE)
			Targets[SetTarget[SetHead[m]]] = 1;
		CODEBLOCK(cur-> , SetHead[m]);
		prev = cur;
		} /* endfor m */

	/* the last */
	if(NDistinctSets>0) {  /* there is at least one */
		StateHead[state].p_out.next = prev;
		if(NOTINITIALSTATE)
			Targets[SetTarget[SetHead[m]]] = 1;
		CODEBLOCK(StateHead[state].p_out. , SetHead[m]);
		}
/****end*out***/

	}/* end for each state */
}


void
prtAllPartitions()
{
	register int i;
	int state;
	struct p_head *sh;
	int prtflag;
	char pset[SETSIZE]; /* set for printing */

	printf("char space used = %d of %d\n", SetMemIdx, CurSetMemberSize);
	for(state=0; state<Nstates; state++) {
		prtflag=0;
		/* only print jams if interesting */
		if( (sh= &StateHead[state].p_jam)->setsize && 
				sh->setsize < SETSIZE-1){
#define CLRLOADPNT(str) \
		printf("%s%d	",str, state);\
		printf("%3d %strans to state %3d\t", sh->setsize, str,sh->desttarget);\
		ClearSet(pset);\
		loadSetFromPart(sh, pset);\
		printElsOfSet(stdout, pset);\
		printf("\n");\
		prtflag=1;
		CLRLOADPNT("JAM");
		}

		if( (sh= &StateHead[state].p_loop)->setsize ) {
			CLRLOADPNT("LOOP");
			}

		sh = &StateHead[state].p_out;
		for(i=0; i<StateHead[state].numout; i++){
			printf("reg%d,%d	",state,i);
			CLRLOADPNT("REG");
			sh = sh->next;
			prtflag=1;
			}
		if(prtflag)
			printf("\n");
		}/* end for state=0 */
}




#ifdef Debuging
void
prtPartitions()
{
	register int i, j, k;
	char msgbuf[10];


#define pnt(ii,x) if(isgraph(x))\
			printf("%s	%c	%d	%d	%d\t",\
			  ii, x, SetTarget[x], DjSets[x].rank, DjSets[x].size, Next[x]);\
		else\
			printf("%s	%d.	%d	%d	%d\t",\
			  ii, x, SetTarget[x], DjSets[x].rank, DjSets[x].size, Next[x])

	printf("Out transitions to %d different states\n", NDistinctSets);
	printf("	canon	target	rank	size	next\n");
	for(i=0; i<NDistinctSets; i++){
		sprintf(msgbuf, "%d", i);
		pnt(msgbuf, SetHead[i]);
		j = SetHead[i];
		for(k=0; k<DjSets[SetHead[i]].size; k++) {
			if(isgraph(j)) printf("%c ", j);
			else printf("%d. ", j);
			j = Next[j];
			}
		printf("\n");
		}
	if(SetHeadJam >=0){
		sprintf(msgbuf, "Jam");
		pnt(msgbuf, SetHeadJam);
		j = SetHeadJam;
		for(k=0; k<DjSets[SetHeadJam].size; k++) {
			if(isgraph(j)) printf("%c ", j);
			else printf("%d. ", j);
			j = Next[j];
			}
		printf("\n");
		}
	if(SetHeadLoop >=0){
		sprintf(msgbuf, "Loop");
		pnt(msgbuf, SetHeadLoop);
		j = SetHeadLoop;
		for(k=0; k<DjSets[SetHeadLoop].size; k++) {
			if(isgraph(j)) printf("%c ", j);
			else printf("%d. ", j);
			j = Next[j];
			}
		printf("\n");
		}
}
#endif
