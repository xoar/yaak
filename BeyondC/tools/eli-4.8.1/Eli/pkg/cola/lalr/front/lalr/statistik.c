/*
** $Id: statistik.c,v 1.7 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: statistik.c,v 1.7 1997/08/29 08:38:08 mjung Exp $";

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
/* File: statistik.c	First Edit: 05.05.89	  Last Edit: 13.07.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 26.01.90	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"

#include "parserlib.h"
#include "ctx.h"
#include "prsiface.h"

#include "statistik.h"

/* On Grammar */
int	StatistNTno;
int	StatistTno;
int	StatistProdno;
int	StatistMaxlrhs;
int	StatistSumlrhs;
int	StatistEpsprodno;
int	StatistProdRelL;

/* On parserlib */
int	StatistFirstOfRhsCalls = 0;
int	StatistFirstOfRhsLoops = 0;
int	StatistgetfirstposCalls = 0;


/* On LR(0)-automaton */
int	StatistStateno;
int	StatistShredStateno;
int	StatistMaxKernel = 0;
int	StatistSumKernel = 0;
int	StatistMaxitemno;
int	StatistSumitemno = 0;
int	StatistStatenoNterm = 0;
int	StatistMaxWithoutRed = 0;
int	StatistSumWithoutRed = 0;
int	StatistSumKernelNterm = 0;
int	StatistMaxC0lg = 0;
int	StatistGOTOcalls = 0;  /* <==> summary of the length of all Gotolists */

/* On LALR(1)-automaton */
int	StatistCTXno;
int	StatistMaxCTXlist;
int	StatistValueno;
int	StatistMaxValuelist;
int	StatistCTXloopno;

int	StatistSETno;
int	StatistERCno;
int	StatistStatesWithSubset;
int	StatistSubsetno;
int	StatistS_inclno;
int	StatistE_inclno;
int	StatistL_inclno;


/* On LALR(1)-interface */
int	StatistReduceSituations;
int	StatistSumTableEntries;
int	StatistShiftTableEntries;
int	StatistRedTableEntries;
int	StatistShredTableEntries;
int	StatistSavedByAnyEntry;
int	StatistShiftNT;		/* includes shiftredNT */
int	StatistShiftT;		/* includes shiftredT */


/* On classification-algorithm of Purdom and Brown */
int	StatistFree;
int	StatistContingent;
int	StatistForbidden;


void	statist_ongrammar(rules)
SEQdef_entry	rules;
{
  SEQdef_entry	travel;
  def_entry	prod;
  SEQunit	rhs;
  unsigned short tag, lgrhs;

  StatistNTno = MAXNTERM;
  StatistTno = MAXTERM;
  StatistProdno = MAXPROD;
  StatistEpsprodno = StatistProdRelL =
  StatistMaxlrhs = StatistSumlrhs = 0;

  foreachinSEQdef_entry(rules, travel, prod)
    {
      lgrhs = 0;
      rhs = prod.Vp_prod->rhs;
      getfirstpos(&rhs, &tag);
      if ( tag  ==  Kshnterm )
	StatistProdRelL++;
      else if ( tag  ==  Kred )
	StatistEpsprodno++;
      while ( !emptySEQunit(rhs) )
	{
	  getnextpos(&rhs,&tag);
	  lgrhs++;
	}
      if ( lgrhs > (unsigned short) StatistMaxlrhs )
	StatistMaxlrhs = lgrhs;
      StatistSumlrhs += lgrhs;
    }  /* end of for */

  return;
}  /* end of statist_ongrammar() */


int	statist_shredno(autom,rules)
ARRstatetype	autom;
SEQdef_entry	rules;
{
  int		result = 0;
  Boolean	*prodarr;
  SEQshifttype	list;
  unsigned short q;

  if ( (prodarr = (Boolean*)calloc(MAXPROD, sizeof(Boolean)))  ==
	(Boolean*)NULL )
    {
      INT_ALLOC_ERR("statist_shredno()");
      exit(1);
    }

  for ( q = 1; q <= MAXSTATE; q++ )
    for ( list = autom[q].Goto;
	  !emptySEQshift(list);
	  list = tlSEQshift(list) )
      if ( list->staterule < (short)0 )
	prodarr[INDEX[- list->staterule]] = TRUE;

  for ( q = 0; q < MAXPROD; q++ )
    if ( prodarr[q] )
      result++;

  free( (char *)prodarr );

  return(result);
}  /* end of statist_shredno() */


void	statist_evalVALUEandCTX(VALUE, CTX)
ARRSEQctxtype	VALUE, CTX;
{
  Indextype	nt;
  unsigned short lg;
  SEQctxtype	ctxlist;

  StatistCTXno = StatistMaxCTXlist =
  StatistValueno = StatistMaxValuelist = 0;

  for ( nt = 0; nt < MAXNTERM; nt++ )
    {
      lg = 0;
      for ( ctxlist=CTX[nt];
	    !emptySEQctx(ctxlist);
	    ctxlist=tlSEQctx(ctxlist) )
	lg++;
      if ( (int) lg > StatistMaxCTXlist )
	StatistMaxCTXlist = lg;
      StatistCTXno += lg;
    }  /* end of for */

  for ( nt = 0; nt < MAXNTERM; nt++ )
    {
      lg = 0;
      for ( ctxlist=VALUE[nt];
	    !emptySEQctx(ctxlist);
	    ctxlist=tlSEQctx(ctxlist) )
	lg++;
      if ( (int) lg > StatistMaxValuelist )
	StatistMaxValuelist = lg;
      StatistValueno += lg;
    }  /* end of for */

  return;
}  /* end of statist_evalVALUEandCTX() */


void	statist_onautomaton(prs)
absparsertype	prs;
{

static short 	states[1000];
static short	prods[1000];
static short 	statesNT[1000];
static short	prodsNT[1000];
static short	NT[1000];
  ARRRowtype	travel1;
  Rowtype	row;
  ARREntrytype	travel2;
  Entrytype	entr;
  short		i;

  StatistShiftNT = StatistShiftT = StatistSavedByAnyEntry = 0;

  foreachinSEQRowtype(prs->ParsingTab, travel1, row)
    foreachinSEQEntrytype(row->Entries, travel2, entr)
      switch ( typeof(entr) )
      {
	case Kreduce:
	case Kaccept: break;
	case Kshift : if ( typeof(DEFTBL[entr.Vshift->CMR_DT_index])
			    ==  Kp_nterm )
			{
			  StatistShiftNT++;
			  states[entr.Vshift->NextState]++;
			  statesNT[entr.Vshift->NextState] =
					INDEX[entr.Vshift->CMR_DT_index];
			}
		      else StatistShiftT++;
		      break;
	case Kshiftred: if ( typeof(DEFTBL[entr.Vshiftred->CMR_DT_index])
			    ==  Kp_nterm )
			{
			  StatistShiftNT++;
			  prods[INDEX[entr.Vshiftred->Rule]]++;
			  prodsNT[INDEX[entr.Vshiftred->Rule]] =
					INDEX[entr.Vshiftred->CMR_DT_index];
			}
		      else StatistShiftT++;
		      break;
      }
  for ( i=0; i<= StatistStateno; i++)
      if ( states[i] > 0 && NT[statesNT[i]] < states[i] )
	NT[statesNT[i]] = states[i];
  for ( i=0; (Indextype) i < MAXPROD; i++)
      if ( prods[i] > 0 && NT[prodsNT[i]] < prods[i] )
	NT[prodsNT[i]] = prods[i];
  for ( i=0; (Indextype) i< MAXNTERM; i++)
      if ( NT[i] > 0 )
	StatistSavedByAnyEntry += (NT[i]-1);
/*    else fprintf(stderr,"Statisterr!\n");	*/

  return;
}


void	statistPrintResult(filename)
String	filename;
{
  FILE	*f;

  if ( (f = fopen(filename, "w"))  ==  (FILE *)NULL )
    {
      INT_ERR("statistPrintResult()");
      exit(1);
    }

  fprintf(f, "G R A M M E R\n");
  fprintf(f, "*************\n");
  fprintf(f, "    Number of nonterminals: %d, terminals: %d\n",
	  StatistNTno, StatistTno);
  fprintf(f, "    Number of productions: %d, epsilon-productions: %d\n",
	  StatistProdno, StatistEpsprodno);
  fprintf(f, "    Number of productions involving one L-edge: %d\n",
	  StatistProdRelL);
  fprintf(f, "    Maximum-length of a production: %d\n", StatistMaxlrhs);
  fprintf(f, "    Summary-length of all productions: %d\n\n",StatistSumlrhs);
  fprintf(f, "\n");

  fprintf(f, "P A R S E R L I B\n");
  fprintf(f, "*****************\n");
  fprintf(f, "    Number of FirstOfRhsCalls: %d\n", StatistFirstOfRhsCalls);
  fprintf(f, "    Number of FirstOfRhsLoops: %d\n", StatistFirstOfRhsLoops);
  fprintf(f, "    Number of getfirstposCalls: %d\n",StatistgetfirstposCalls);
  fprintf(f, "\n");

  fprintf(f, "L R (0) - A U T O M A T O N\n");
  fprintf(f, "***************************\n");
  fprintf(f, "    Number of states: %d\n", StatistStateno);
  fprintf(f, "    Number of LR(0)-reducestates: %d\n", StatistShredStateno);
  fprintf(f, "    Number of states with a BasisShiftNtermSit: %d\n",
		  StatistStatenoNterm);
  fprintf(f, "    Maximum of basis-situations: %d\t", StatistMaxKernel);
  fprintf(f, "    without reduce-sitations: %d\n", StatistMaxWithoutRed);
  fprintf(f, "    Summary of basis-situations: %d\t",StatistSumKernel);
  fprintf(f, "    without reduce-sitations: %d\n", StatistSumWithoutRed);
  fprintf(f, "    Summary of basis-ShiftNtermsituations: %d\n\n",
		  StatistSumKernelNterm);
  fprintf(f, "    Maximum of situations: %d\n", StatistMaxitemno);
  fprintf(f, "    Summary of situations: %d\n\n",StatistSumitemno);
  fprintf(f, "    Maximum-length of a C0-list: %d\n", StatistMaxC0lg);
  fprintf(f, "    Number of GOTO calls: %d\n\n", StatistGOTOcalls);

  fprintf(f, "L A L R (1) - A U T O M A T O N\n");
  fprintf(f, "*******************************\n");
  fprintf(f, "    Number of ctx-sets: %d\n", StatistCTXno);
  fprintf(f, "    Number of ctx-loops: %d\n", StatistCTXloopno);
  fprintf(f, "    Number of value-sets: %d\n", StatistValueno);
  fprintf(f, "    Maximum-length of a ctx-list: %d\n", StatistMaxCTXlist);
  fprintf(f, "    Maximum-length of a value-list: %d\n",StatistMaxValuelist);
  fprintf(f, "\n");
  fprintf(f, "    Number of SET-sets: %d\n", StatistSETno);
  fprintf(f, "    Number of ERC-sets: %d\n", StatistERCno);
  fprintf(f, "    Number of states with SUB-sets: %d\n",
	  StatistStatesWithSubset);
  fprintf(f, "    Number of SUB-sets: %d\n", StatistSubsetno);
  fprintf(f, "    Number of S_include-edges: %d\n", StatistS_inclno);
  fprintf(f, "    Number of E_include-edges: %d\n", StatistE_inclno);
  fprintf(f, "    Number of L_include-edges: %d\n", StatistL_inclno);
  fprintf(f, "\n");

  fprintf(f, "L A L R (1) - I N T E R F A C E\n");
  fprintf(f, "*******************************\n");
  fprintf(f, "    Number of reduce-situations (LA-sets): %d\n",
	  StatistReduceSituations);
  fprintf(f, "    Number of all entries: %d\n", StatistSumTableEntries);
  fprintf(f, "    Number of shift-entries: %d\n", StatistShiftTableEntries);
  fprintf(f, "    Number of reduce-entries: %d\n", StatistRedTableEntries);
  fprintf(f, "    Number of shiftreduce-entries: %d\n",
	  StatistShredTableEntries);
  fprintf(f, "    Number of shift-NT: %d\n", StatistShiftNT);
  fprintf(f, "    Number of shift-T: %d\n", StatistShiftT);
  fprintf(f, "    Number of entries saved by any: %d\n",
	  StatistSavedByAnyEntry);
  fprintf(f, "\n");


  fprintf(f, "C L A S S I F I C A T I O N\n");
  fprintf(f, "***************************\n");
  fprintf(f, "    Number of free positions: %d\n", StatistFree);
  fprintf(f, "    Number of contingent positions: %d\n", StatistContingent);
  fprintf(f, "    Number of forbidden positions: %d\n", StatistForbidden);
  fprintf(f, "\n");

  fclose(f);
  return;
}  /*  end of statistPrintResult() */

