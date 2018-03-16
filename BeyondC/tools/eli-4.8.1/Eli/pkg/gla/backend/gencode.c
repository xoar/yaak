static char RCSid[] = "$Id: gencode.c,v 1.22 2009/04/19 20:33:57 profw Exp $";
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

/* Stack stuff */
int Sp = 0;
short * Stk;
char * Done;
#define PUSH(a)	{if(Sp>=Nstates-1) printf("GLA stk ovrflo\n");\
		Stk[Sp++] = a; }
#define POP	Stk[--Sp]
#define EMPTY	( Sp<=0 )

static short DefStateTbl[SETSIZE]; /* map default char to state */
short CaseTbl[SETSIZE];	/* initial switch for tokens */
short ExtCodeTbl[SETSIZE]; /* map single char token to extcode */

extern struct state_head *StateHead;

#define ISFINAL(s)	(StateHead[s].Yindex)
#define SCAN(s)		(YauxScanner[StateHead[s].Yindex])
#define PROC(s)		( Yprocessor[StateHead[s].Yindex])
#define EXTCODE(s)	(   YextCode[StateHead[s].Yindex])


void unexpectedEntry(ch)	/* unexpected entry in CaseTbl */
unsigned char ch;
{
	if(ch==' ' )		return;
	else if(ch=='\t')	return;
	else if(ch=='\n')	return;
	else if(ch=='\r')	return;
	else			GPNT(stderr, ch, "", " ");

	fprintf(stderr, "occurred in a regular expression; check .gla spec\n");
	fprintf(stderr, " for explicit character, or wildcard (DOT) or range [x-y]\n");
	exit(4);
}

/* Generate head of switch statement.  This is here rather than in 
   the scanner frame so that we avoid generating a .h file with
   mismatched braces.  Some compilers like gcc warn about that. */

void genHead () 
{
    fprintf (Fc, "switch (CaseTbl[c = *p++]) {\n");
    fprintf (Fc, "case 0:	/* sentinel - probably EOB */\n");
    fprintf (Fc, "  if (c == '\\0') {\n");
    fprintf (Fc, "    p = TokenStart = TokenEnd = auxNUL(TokenStart, 0);\n");
    fprintf (Fc, "    if (*p) extcode = NORETURN;\n");
    fprintf (Fc, "    else {\n");
    fprintf (Fc, "      p = TokenStart = TokenEnd = auxEOF(TokenStart, 0);\n");
    fprintf (Fc, "      if (*p) extcode = NORETURN;\n");
    fprintf (Fc, "      else { extcode = EOFTOKEN; EndOfText(p, 0, &extcode, v); }\n");
    fprintf (Fc, "    }\n");
    fprintf (Fc, "    goto done;\n");
    fprintf (Fc, "  } else {\n");
    fprintf (Fc, "    obstack_grow(Csm_obstk, \"char '\", 6);\n");
    fprintf (Fc, "    obstack_cchgrow(Csm_obstk, c);\n");
    fprintf (Fc, "    message(\n");
    fprintf (Fc, "      ERROR,\n");
    fprintf (Fc, "      (char *)obstack_copy0(Csm_obstk, \"' is not a token\", 16),\n");
    fprintf (Fc, "      0,\n");
    fprintf (Fc, "      &curpos);\n");
    fprintf (Fc, "    TokenEnd = p;\n");
    fprintf (Fc, "    continue;\n");
    fprintf (Fc, "  }\n");
    fprintf (Fc, "  \n");
    fprintf (Fc, "case 1:	/* space */\n");
    fprintf (Fc, "  while (scanTbl[c = *p++] & 1<<0) ;\n");
    fprintf (Fc, "  TokenEnd = p - 1;\n");
    fprintf (Fc, "  continue;\n");

    fprintf (Fc, "case 2:	/* tab */\n");
    fprintf (Fc, "  do { StartLine -= TABSIZE(p - StartLine); }\n");
    fprintf (Fc, "  while (scanTbl[c = *p++] & 1<<1);\n");
    fprintf (Fc, "  TokenEnd = p - 1;\n");
    fprintf (Fc, "  continue;\n");

    fprintf (Fc, "case 4:	/* carriage return */\n");
    fprintf (Fc, "  if (*p == '\\n') { TokenEnd = p; continue; }\n");

    fprintf (Fc, "case 3:	/* newline */\n");
    fprintf (Fc, "  do { LineNum++; } while (scanTbl[c = *p++] & 1<<2);\n");
    fprintf (Fc, "  StartLine = (TokenEnd = p - 1) - 1;\n");
    fprintf (Fc, "  continue;\n");
}


void		/* called once from glamain */
genCases()
{
char defaultSet[SETSIZE];	/* used to collect single char def tokens */
char miscS[SETSIZE];		/* used for misc purposed */
short targetState;		/* from the initial state */
short compactCaseLabel;		/* compact case labels */
int i;


	Stk  = (short *)malloc((unsigned) Nstates* sizeof(short));
	Done = (char *) malloc((unsigned) Nstates);
	if( Stk==NULL || Done==NULL) {
		printf("cannot malloc stack space \n");
		exit(22);
		}
	for(i=0; i<Nstates; i++)
		Done[i] = 0;


        genHead ();     /* generate start of switch */


	/*
	** create bitvectors for space, tab and newlines.  The code
	** for these (glahead.c) is constant and therefore the
	** reference parameters (i) are dummy placeholders.
	*/
	compactCaseLabel = 1;
#define STDCASES(ch) \
	CaseTbl[ch] = compactCaseLabel++;\
	ClearSet(miscS);\
	AddElmToSet(ch, miscS);\
	(void)createSet(miscS, &i, &i)
	STDCASES(' ');
	STDCASES('\t');
	STDCASES('\n');

	/*
	** Add a carriage return to the table of initial characters.
	** No bit vector is needed because there is no loop processing
	** these characters.
	*/
	CaseTbl['\r'] = compactCaseLabel++;

	ClearSet(defaultSet);	/* for DefaultCase of generated code */

	/*
	** One of two possibilities: either this partition warrents a
	** case label to itself, or they can all be lumped into the
	** default case (no special scanning, processing or continue required.
	*/
	{ /*scope */
	struct p_head *cur = &StateHead[0].p_out;
	int ssize;
	int j;
	/* for each possible out transition from initial state */
	for(i=0; i<StateHead[0].numout; i++){
		targetState = cur->desttarget;
		ssize = cur->setsize;
		if( ANYOUTTRANS(targetState) ==0  &&
		    SELFLOOP(targetState) ==0 &&
		    ISFINAL(targetState)  &&
		    PROC(targetState)==NULL    &&
		    SCAN(targetState)==NULL    &&
		    EXTCODE(targetState) != NORETURN
		    /*
		    ** these are single char tokens that are not the head
		    ** of any other token.  Also, no scanner or processor
		    ** or continue.  Need to collect the characters,
		    ** and their associated external codes.  DefStateTbl
		    ** later helps us go from a char to extcode.
		    */
		  ) {			/* GATHER INTO "default" */
			if(ssize == 1){
#define GATHER(chr)\
				AddElmToSet((chr), defaultSet);\
				DefStateTbl[chr] = targetState;\
				ExtCodeTbl[chr] = EXTCODE(targetState)
				GATHER(cur->ch);
				}
			else {
				if(cur->flag == SET_CONSECUTIVE)
					for(j=0; j<ssize; j++){
					    GATHER(cur->ch+j);
					    }
				else /* SET_LIST */
					{
					for(j=0; j<ssize; j++){
					    GATHER(SetMemArr[cur->first + j]);
					    }
					} /* endelse */
				} /* endelse */
			} /* endif ... && ... && ...*/
		else {				/* NEED a case label */
			if(Done[targetState])
				printf("From INIT, Target Done[%d] part=%d lab=%d\n",
						targetState, i,compactCaseLabel);
			else
				Done[targetState] = 1;
			fprintf(Fc,"\ncase %d:\t/* Entered on: ", compactCaseLabel);
			if(ssize == 1){
				if(CaseTbl[cur->ch] != 0)
					unexpectedEntry(cur->ch);
				CaseTbl[cur->ch] = compactCaseLabel;
				GPNT(Fc,cur->ch,"", "");
				}
			else {
				if(cur->flag == SET_CONSECUTIVE){
					GPNT(Fc,cur->ch,"", "-");
					GPNT(Fc,cur->ch+ssize-1,"", "");
					for(j=0; j<ssize; j++){
					  if(CaseTbl[cur->ch+j] != 0)
					  	unexpectedEntry(cur->ch+j);
					  CaseTbl[cur->ch+j] = compactCaseLabel;
					  }
					}
				else /* SET_LIST */
					{
					ClearSet(miscS);  /* for diag printing */
					for(j=0; j<ssize; j++){
					  if(CaseTbl[SetMemArr[cur->first +j]] != 0)
					    unexpectedEntry(SetMemArr[cur->first +j]);
					  CaseTbl[SetMemArr[cur->first +j]] = compactCaseLabel;
					  AddElmToSet(SetMemArr[cur->first +j], miscS);
					  }
					printElsOfSet(Fc, miscS);
					}
				} /*endelse*/
			compactCaseLabel++;
			fprintf(Fc," */\n");
			genBody(FROMINITIAL, targetState);
			} /*end else*/
		cur = cur->next;
		}/* endfor i=0; i<StateHead[0].p_out */
	}/*endscope*/

	/* load CaseTbl for default cases */
	for(i=0; i<SETSIZE; i++)
		if( defaultSet[i] ){
			if(CaseTbl[i] != 0)
				unexpectedEntry(i);
			CaseTbl[i] = compactCaseLabel;
			}

	outShortArray(Ft, "CaseTbl",    CaseTbl,    SETSIZE);
	outShortArray(Ft, "ExtCodeTbl", ExtCodeTbl, SETSIZE);

	fprintf(Fc,"\n\ndefault: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /* ");
	printElsOfSet(Fc, defaultSet);
	fprintf(Fc," */\n}\n");

	/* the rest is not really part of genCases and should be moved up */
	while (! EMPTY) {
		targetState = POP;	/* genBody does the PUSHing */
		/*   why would this be true????
		**   gencases PUSHES work to be done later, 
		**    a later gencase does this state
		**   So it doesn't need to be done again.
		if(Done[targetState])
			printf("GLA: NOTE POP Done[%d]\n", targetState);
		else{
		*/
		if(! (Done[targetState])){
			Done[targetState] = 1;
			genBody(NOTINITIAL, targetState);
			}
		}

	outScanTbl();

}

#include <ctype.h>

void  				/* implement decision table */
genPartition(state, par, sh, init)
int state;
int par;
struct p_head *sh;
int init;

{
int j,k;
char genParSet[SETSIZE];
	assert(ANYOUTTRANS(state));
	/* FOUR different combinations for the test : */

	if(    par==0 && sh->setsize==1){
		fprintf(Fc,"\t\tif((c= *p++) ==%d) {", sh->ch);
		}

	else if(par>0 && sh->setsize==1){
		fprintf(Fc,"\t\telse if(c ==%d) {", sh->ch);
		}
	
	else if(par==0 && sh->setsize>1){
#define VECTORMATCH(str)\
		ClearSet(genParSet);\
		loadSetFromPart(sh, genParSet);\
		(void)  createSet(genParSet, &j, &k);\
		fprintf(Fc,str, k*SETSIZE,   j);\
		printElsOfSet(Fc,genParSet);\
		fprintf(Fc," */\n")
		VECTORMATCH("\t\tif( scanTbl[(c= *p++)+%d] & 1<<%2d){ /* ");
		}
	
	else if(par>0 && sh->setsize>1){
		VECTORMATCH("\t\telse if( scanTbl[c+%d] & 1<<%2d){ /* ");
		}
	else
		fprintf(stderr,"error in genPartition\n");
	

	if (init == FROMINITIAL && !ISFINAL(state) && !ISNEXTFINAL(sh) )  
		fprintf(Fc,
		"\n\t\tTokenEnd = TokenStart; /* prepare for error fallback */\n");

/* XXX will next condition override prev???? */

	if( ISFINAL(state) && !ISNEXTFINAL(sh) ) {
	    fprintf(Fc,"\t\textcode = %d;/* remember fallback*/\n", EXTCODE(state));
	    fprintf(Fc,"\t\tTokenEnd = p-1;\n");
	    if(SCAN(state) != NULL )
		fprintf(Fc,"\n\t\tscan = %s;\n", SCAN(state));
	    else
		fprintf(Fc,"\n\t\tscan = NULL;\n");
	    if(PROC(state) != NULL )
		fprintf(Fc,"\t\tproc = %s;\n", PROC(state));
	    else{
		fprintf(Fc,"\t\tproc = NULL;\n");
		}
	    }
		

	fprintf(Fc,"\t\t\tgoto St_%d;}\n", sh->desttarget);
}



void
genBody(init, state)
int init;
int state;
{
	char loopSet[SETSIZE];
	int i,j,k;

	
	if (Targets[state])
		fprintf(Fc,"\tSt_%d:\n", state);
	else
		fprintf(Fc,"\t/*St_%d:*/\n", state);

	if( SELFLOOP(state) ){
		struct p_head *sh = &StateHead[state].p_loop;

		ClearSet(loopSet);
		loadSetFromPart(sh, loopSet);
		fprintf(Fc,"\t\t/* "); printElsOfSet(Fc, loopSet); fprintf(Fc,"*/\n");

		(void) createSet(loopSet, &j, &k);

		fprintf(Fc,"\t\twhile(scanTbl[(c= *p++)+%d] & 1<<%2d);--p;\n",
							k*SETSIZE, j);
		}


	/************* we HAVE some normal partitions ***************/

	if(ANYOUTTRANS(state) ) { 	/* if any normal partitions */
		struct p_head *sh = &StateHead[state].p_out;
		for(i=0; i<StateHead[state].numout; i++){
			genPartition(state, i, sh, init);
			/* prtSet( sh); */
			if( !Done[sh->desttarget] ) {
				/*  NOT YET DONE!!! Done[sh->desttarget] = 1;*/
				PUSH(sh->desttarget);
				}
			sh = sh->next;
			}

		/* generate the matching "else" for normal partitions */
		if( ISFINAL(state) ) {	/* do work now and return */
		    fprintf(Fc,"\t\telse {\n");
		    doElseFinal(Fc, state, "(--p)");
		    fprintf(Fc,"\t\t\t}\n");
		    }
		else {	/* NON FINAL */
		    if(init==FROMINITIAL){
		        fprintf(Fc, 
			"\t\telse {TokenEnd=TokenStart;--p; goto fallback; }\n");
		        }
		    else {
			fprintf(Fc, "\t\telse {--p; goto fallback; }\n");
			}
		    }  /* end NON FINAL */
		} /* end of any normal partitions */

	/************** we have ZERO normal partitions ***************/
	else {	/* do work now and return */
	    doElseFinal(Fc, state, "p");
	    } /* end else ZERO normal partitions */
}



void
doElseFinal(fp, state, pvalue)
FILE *fp;
int state;
char *pvalue;  /* either "p" or "(--p)" */
{
assert(ISFINAL(state));  /* FSM cannot end in nonfinal state*/

/* after this stmt, TokenEnd and p must be correct */
if(SCAN(state) != NULL )
    fprintf(fp, "\t\t\tTokenEnd=p=%s(TokenStart, %s-TokenStart);\n" ,
				SCAN(state), pvalue);
else
    fprintf(fp,"\t\t\tTokenEnd= %s; /* FINAL, no auxscan, must set */\n",
				pvalue);

fprintf(fp, "\t\t\textcode = %d;\n", EXTCODE(state));

if(PROC(state)  != NULL)
	fprintf(fp, "\t\t\t%s(TokenStart, TokenEnd-TokenStart,&extcode,v);\n",
				PROC(state));

fprintf(fp,"\t\t\tgoto done;\n");
}
/*       1         2         3         4         5         6         7
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
