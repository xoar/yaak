/*
** $Id: mkiface.c,v 1.7 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: mkiface.c,v 1.7 1997/08/29 08:38:08 mjung Exp $";

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
/* File: mkiface.c	First Edit: 04.04.89	  Last Edit: 06.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 10.08.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"

#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"

#include "parserlib.h"
#include "prsiface.h"
#include "mkiface.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif


short	CompReduces(redacts,actlg,reditem)
SEQshifttype	redacts;
short		actlg;
red_itemtype	reditem;
{
static  SEQshifttype	rear = initSEQshift();	/* Insert behind rear! */
static	Indextype	*TermArr = (Indextype *)NULL;/* Array of terminals */
static	DID		*TermInv; /*Inverse function of INDEX for terminals*/
	short		no,	/* Actual number of elements in TermArr */
			i;
	shifttype	*newshift = (shifttype *)NULL;

  /* Initializations */
  if ( TermArr == (Indextype *)NULL )
    {
      /* executed only at the first call of this function */
      if ( (TermArr = (Indextype *)malloc(MAXTERM*sizeof(Indextype)))
	   == (Indextype *)NULL )
        {
	  INT_ALLOC_ERR("CompReduces");
	  exit(1);
        }
      TermInv = cmrlib_INDEX_Invers(Kp_term);
    }  /* end of if */

  if ( emptySEQshift(rear) || actlg == 0 )
    rear = redacts;

  no = EvalBitSet(TermArr, reditem.erc);

  for (i=0; i<no; i++)
  {
    if ( emptySEQshift(tlSEQshift(rear)) )
	{
	  newshift = mkshift(TermInv[TermArr[i]], (short)reditem.common.ruleno);
	  rear = insbehindSEQshift(rear, newshift);
	}
    else
	{
	  rear = tlSEQshift(rear);
	  rear->symbol = TermInv[TermArr[i]];
	  rear->staterule = reditem.common.ruleno;
	}
  }
  return(actlg+no);

}  /* end of CompReduces() */


void	EvalActions(row, actions, start, onlyreduces, actlg)
Rowtype		row;
SEQshifttype	actions;
DID		start;
Boolean		onlyreduces;
short		actlg;
{
  short		tag;
  Entrytype	entry;

  for ( ; actlg; actlg--, actions = tlSEQshift(actions) )
    {
      if ( onlyreduces )
	if ( hdSEQshift(actions).staterule == start )
	  tag = Kaccept;
	else
	  tag = Kreduce;
      else
	if ( hdSEQshift(actions).staterule > (short)0 )
	  tag = Kshift;
#ifdef DEBUG_ABS
	else if ( hdSEQshift(actions).staterule == (short)0 )
	  INT_ERR("EvalActions()");
#endif
	else if ( - hdSEQshift(actions).staterule == start )
	  tag = Kaccept;
	else
	  tag = Kshiftred;
      /* end of if */

      switch ( tag )
	{
	  case Kshift   :
		entry.Vshift = Nshift;
		entry.Vshift->NextState = hdSEQshift(actions).staterule;
#ifdef	STATISTIK
	        StatistShiftTableEntries++;
#endif
		break;
	  case Kreduce  :
		entry.Vreduce = Nreduce;
		entry.Vreduce->Rule = hdSEQshift(actions).staterule;
		break;
	  case Kshiftred:
		entry.Vshiftred = Nshiftred;
		entry.Vshiftred->Rule =  - hdSEQshift(actions).staterule;
#ifdef	STATISTIK
	        StatistShredTableEntries++;
#endif
		break;
	  case Kaccept  :
		entry.Vaccept = Naccept;
		break;
	  default	:
		INT_TAG_ERR("EvalActions()",tag);
		break;
	}  /* end of switch */

      entry.IDLclassCommon->CMR_DT_index = hdSEQshift(actions).symbol;
      appendrearSEQEntrytype(row->Entries, entry);
    } /* end of for */

}  /* end of EvalActions() */

/* Computes abstract interface containing the transition table
 * 	- reduction to startproduction is replaced with accept
 */
void	 cmrtl_compute_interface(c, automat, startprod, parser)
p_comar		c;
ARRstatetype	automat;
DID		startprod;
absparsertype	*parser;
{
  p_comar	sav;
  absparsertype	prs;
  statetype	*state;
  SEQshifttype	redacts = initSEQshift();
  short		actlg, actionno;
  SEQitemtype	itemlist;
  itemtype	item;
  Rowtype	RowOfq;
  unsigned short q;

#ifdef	STATISTIK
  StatistSumTableEntries = StatistShiftTableEntries = StatistReduceSituations =
  StatistRedTableEntries = StatistShredTableEntries = 0;
#endif
  /* Initializations */
  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */
  prs = Nabsparsertype;
  {
    /* the same as 'IDLInitializeArray(prs->ParsingTab, MAXSTATE);',
     * but avoiding warnings of the C-compiler
     */
    if ( MAXSTATE )
      prs->ParsingTab.array = (Rowtype *)IDLNewArray(MAXSTATE);
    prs->ParsingTab.size = MAXSTATE;
    prs->ParsingTab.length = 0;
    prs->IsDeterm = ISLALR1;
  }

  redacts = insSEQshift(redacts, mkshift(UNDEF, UNDEF)); /* dummy-element */

  /* Computing the abstract parser interface */
  for (q=1, state=automat+1; q<=MAXSTATE; q++, state++)
    {
      /* Computing all possible reduce-actions in q */
      actlg = 0;
      for ( itemlist=state->Kernel;
	    !emptySEQitem(itemlist);
	    itemlist=tlSEQitem(itemlist) )
	{
	  item = hdSEQitem(itemlist);
	  if ( tagofitem(item) == Kred )
	    {
#ifdef	STATISTIK
	      StatistReduceSituations++;
#endif
	      actlg = CompReduces(redacts,actlg,item.red);
	    }  /* end of if */

	}  /* end of for */

      /* Creation of a new row in the parsing-table */
      RowOfq = NRowtype;
      RowOfq->Errsymb = state->Errsymb;
      actionno = lengthSEQshift(state->Goto) + actlg;

#ifdef	STATISTIK
      StatistSumTableEntries += actionno;
      StatistRedTableEntries += actlg;
#endif

      {
	/* the same as 'IDLInitializeArray(RowOfq->Entries,actionno);',
	 * but avoiding warnings of the C-compiler
	 */
	if ( actionno )
	  RowOfq->Entries.array = (Entrytype *)IDLNewArray(actionno);
	RowOfq->Entries.size = actionno;
	RowOfq->Entries.length = 0;
      }

      EvalActions(RowOfq, state->Goto, startprod, FALSE, actionno - actlg);
      EvalActions(RowOfq, tlSEQshift(redacts), startprod, TRUE, actlg);

      appendrearSEQRowtype(prs->ParsingTab, RowOfq);
    }  /* end of for */

  *parser = prs;

#ifdef	STATISTIK
   statist_onautomaton(prs);
#endif

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return;
}  /* end of cmrtl_compute_interface() */
