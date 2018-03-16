/* $Id: dj.h,v 1.27 2013/11/12 18:48:28 profw Exp $ */
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "err.h"

extern FILE *Ft;	/* CaseTbl and ScanTbl tables */
extern FILE *Fc;	/* C code of FSM */
extern FILE *FlexStateFd;
extern int Nstates;extern int *AcceptStates;
extern char *Targets;

/* see Ch 2 of D.S. and Network algorithms R.E. Tarjan */
struct el {
	int parent;
	int rank;
	int size;
	};

extern unsigned char * SetMemArr;

struct p_head {
	struct p_head *next;	/* only used for out partitions */
	short	desttarget;
	short 	setsize;
	char	flag;
	short	ch;
	long	first;		/* index into SetMemArr[] */
	};

struct state_head {
	struct p_head p_jam;
	struct p_head p_loop;
	struct p_head p_out;
	short	numout;		/* number of out sets */
	short   Yindex;		/* index into Yextcode, Yauxscanner ... */
	};

extern int NonLitCount; /* number of non-literal patterns */
extern int LitCount;    /* number of literal patterns */
extern int NTokens;     /* sum of LitCount and NonLitCount */

extern char **YauxScanner;
extern char **Yprocessor;
extern char **Ypattern;
extern short *YextCode;
extern int EofCode;		/* value returned on EOF */

#define NORETURN 15001  /* hopefully no one will ever want this extcode */
#define BOGUS 15002     /* hopefully no one will ever want this extcode */
#define UNDEF -1
#define TRUE 1
#define FALSE 0
#define SET_ONE 1
#define SET_CONSECUTIVE 2
#define SET_LIST 3
extern int NDistinctSets;		/* # of sets in SetHead array */
#define SETSIZE 256	/* ISO-8859-1 */
extern struct el DjSets[SETSIZE];
extern short Next[SETSIZE];
extern short SetHead[SETSIZE];
extern short SetTarget[SETSIZE];	/* state to which transition goes */
extern short SetHeadJam;
extern short SetHeadLoop;

extern struct state_head *StateHead;


extern FILE *Ft, *Fc;

#define ANYOUTTRANS(s)	(StateHead[s].numout)
#define SELFLOOP(s)	(StateHead[s].p_loop.setsize)
#define ISNEXTFINAL(sh)	(StateHead[sh->desttarget].Yindex )


#define ClearSet(SS) {register int cc; for(cc=0; cc<SETSIZE; cc++) SS[cc] = 0; }
#define AddElmToSet(elm, SS) 	SS[elm] = 1

#define FROMINITIAL 1
#define NOTINITIAL  0
#define NORETURN 15001  /* also in glamain.c? */


extern short CaseTbl[SETSIZE];	/* initial switch for tokens */
extern short ExtCodeTbl[SETSIZE]; /* map single char token to extcode */

/* print ascii character in a visible manner. Be prepared for non-ascii */
#define GPNT(fp,ch,front,back) if(isprint(ch)) \
				fprintf(fp,"%s%c%s",front,ch,back); \
			      else \
                                fprintf(fp,"%s%3d.%s",front,ch,back)

/************************* FUNCTION  DECLARATIONS **************************/
				/* gcc -ansi will use the prototypes */
#if defined(__cplusplus) || defined(__STDC__)

extern unsigned char *allocate_character_array(int);
extern unsigned char *reallocate_character_array(unsigned char*, int);

extern void flexfatal(char*);
extern void outScanTbl(void);

extern void genCases(void);
extern void genPartition(int state, int par, struct p_head *sh, int init);
extern void genBody(int init, int state);
extern void doElseFinal(FILE *fp, int state, char *pvalue);
extern int createSet(char *SetArray, int *bitOff, int *tblOff);
extern void outScanTbl(void);
extern void printElsOfSet(FILE *fp, char set[SETSIZE]);
extern void pBoolean(char array[], char *name, int elsize, int max, FILE *fp);
extern void prtTrans(void);
extern void outShortArray(FILE *fd, char *str, short A[], int len);
extern void loadSetFromPart(struct p_head *sh, char set[SETSIZE]);

extern void bubble( short v[], int n);

extern void mkDJSetFromTransition(int state, int flexstate[SETSIZE]);
extern void makeAllPartitions(void);
extern void prtAllPartitions(void);
extern void prtPartitions(void);

/* from djsets.c */
extern void makeDJsets(void);
extern int findWhichSet(int x);
extern int linkSets(int x,int y);
extern void pntDJset(FILE *);

/* from glamain.c */
extern void diags(void);
extern void writeConstants(FILE *fp);
extern void writeFiles(FILE *fd);
extern void yyerror(char *s);
extern int yyparse(void);

extern void initBuf(const char* infile, int f);
extern void refillBuf(const char*);
extern int glalex(void *);

#else

extern unsigned char *allocate_character_array();
extern unsigned char *reallocate_character_array();

extern void flexfatal();
extern void outScanTbl();

extern void genCases();
extern void genPartition();
extern void genBody();
extern void doElseFinal();
extern int createSet();
extern void outScanTbl();
extern void printElsOfSet();
extern void pBoolean();
extern void prtTrans();
extern void outShortArray();
extern void loadSetFromPart();

extern void bubble();

extern void mkDJSetFromTransition();
extern void makeAllPartitions();
extern void prtAllPartitions();
extern void prtPartitions();

/* from djsets.c */
extern void makeDJsets();
extern int findWhichSet();
extern int linkSets();
extern void pntDJset();

/* from glamain.c */
extern void diags();
extern void writeConstants();
extern void writeFiles();
extern void yyerror();
extern int yyparse();

extern void initBuf();
extern void refillBuf();
extern int glalex();
#endif
