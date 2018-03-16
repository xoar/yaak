/*
** $Id: statistik.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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

/***************************************************************************/
/* File: statistik.h	First Edit: 05.05.89	  Last Edit: 08.05.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 26.01.90	From: Karl-Josef Prott			   */
/***************************************************************************/

#ifndef statistik_DEF
#define statistik_DEF


/* On Grammar */
extern	int	StatistNTno;
extern	int	StatistTno;
extern	int	StatistProdno;
extern	int	StatistMaxlrhs;
extern	int	StatistSumlrhs;
extern	int	StatistEpsprodno;
extern	int	StatistProdRelL;

/* On parserlib */
extern	int	StatistFirstOfRhsCalls;
extern	int	StatistFirstOfRhsLoops;
extern	int	StatistgetfirstposCalls;


/* On LR(0)-automaton */
extern	int	StatistStateno;
extern	int	StatistShredStateno;
extern	int	StatistMaxKernel;
extern	int	StatistSumKernel;
extern	int	StatistMaxitemno;
extern	int	StatistSumitemno;
extern	int	StatistStatenoNterm;
extern	int	StatistMaxWithoutRed;
extern	int	StatistSumWithoutRed;
extern	int	StatistSumKernelNterm;
extern	int	StatistMaxC0lg;
extern	int	StatistGOTOcalls;
  /* <==> summary of the length of all Gotolists */

/* On LALR(1)-automaton */
extern	int	StatistCTXno;
extern	int	StatistMaxCTXlist;
extern	int	StatistValueno;
extern	int	StatistMaxValuelist;
extern	int	StatistCTXloopno;

extern	int	StatistSETno;
extern	int	StatistERCno;
extern	int	StatistStatesWithSubset;
extern	int	StatistSubsetno;
extern	int	StatistS_inclno;
extern	int	StatistE_inclno;
extern	int	StatistL_inclno;


/* On LALR(1)-interface */
extern	int	StatistReduceSituations;
extern	int	StatistSumTableEntries;
extern	int	StatistShiftTableEntries;
extern	int	StatistRedTableEntries;
extern	int	StatistShredTableEntries;
extern	int	StatistSavedByAnyEntry;
extern	int	StatistShiftNT;		/* includes shiftredNT */
extern	int	StatistShiftT;		/* includes shiftredT */


/* On classification-algorithm of Purdom and Brown */
extern	int	StatistFree;
extern	int	StatistContingent;
extern	int	StatistForbidden;


void	statist_ongrammar(/* SEQdef_entry rules */);
int	statist_shredno(/* ARRstatetype autom, SEQdef_entry rules */);
void	statist_evalVALUEandCTX(/* ARRSEQctxtype VALUE, CTX */);
void	statist_onautomaton(/* absparsertype parser */);
void	statistPrintResult(/* String filename */);
void	statist_pred(/* ARRSEQnodetype succ, unsigned short root, final */);


#endif	/* of  statistik_DEF */
