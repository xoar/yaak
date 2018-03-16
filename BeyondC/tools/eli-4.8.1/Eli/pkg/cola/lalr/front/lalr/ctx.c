/*
** $Id: ctx.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: ctx.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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
/* File: ctx.c		First Edit: 24.04.89	  Last Edit: 24.04.89      */
/*	 								   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 03.08.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"

#include "parserlib.h"
#include "ctx.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif


/* CTX is a dynamic array of SEQctxtype. Let ctx one element of CTX[X].
 * Then is: (ctx.ntind == Y  <==> X L* Y)  and (ctx.set == CTX(X,Y))
 */
ARRSEQctxtype	CTX;

/***************************************************************************/
/* Implementation of exported functions for handling with SEQctxtype	   */
/***************************************************************************/

SEQctxtype	insSEQctx(list, el)
SEQctxtype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQctx() */

ctxtype	*mkctx(ntind,set)
Indextype	ntind;
BitSet		set;
{
  ctxtype	*result;

  if ( (result = (ctxtype *)malloc(sizeof(ctxtype)))  ==  (ctxtype *)NULL )
     {
      INT_ALLOC_ERR("mkctx()");
      exit(1);
    }
  result->ntind = ntind;
  result->set = set;
  result->next = (ctxtype *)NULL;
  return(result);
}  /* end of mkctx() */

void	rekdelSEQctx(list)
SEQctxtype	list;
{
  SEQctxtype	help;

  while ( !emptySEQctx(list) )
    {
      help = list;
      list = tlSEQctx(list);
      free( (char *)help );
    }

  return;
}  /* end of rekdelSEQctx() */

void	FreeARRSEQctx(arrctx)
ARRSEQctxtype	arrctx;
{
  unsigned short i;

  for ( i=0; i<MAXNTERM; i++ )
    rekdelSEQctx(arrctx[i]);

  free( (char *)arrctx );

}  /* end of FreeARRSEQctx() */


/* return == arr(A,B), if existing in array 'arr'
 *	  == (BitSet)NULL, if not existing in array 'arr'
 * ( for example: CTX(A,B) if called with CTX as 'arr' )
 */
BitSet	GetValueSet(arr,A,B)
ARRSEQctxtype	arr;
Indextype	A, B;
{
  SEQctxtype	ctxlist;

  for (ctxlist=arr[A]; !emptySEQctx(ctxlist); ctxlist=tlSEQctx(ctxlist))
    if ( hdSEQctx(ctxlist).ntind == B )
      return( hdSEQctx(ctxlist).set );

  return( (BitSet)NULL );

}  /* end of GetValueSet() */

/***************************************************************************/
/* Implementation of 'ComputeCTX()' and its (sub-)functions		   */
/***************************************************************************/

/********** variable-definitions local to this file but global 	**********/
/********** to all functions of it.				**********/

/* VALUE is a dynamic array of SEQctxtype. Let ctx one element of VALUE[X].
 * Then is: (ctx.ntind == Y  <==> X L Y)  and (ctx.set == VALUE(X,Y))
 */
ARRSEQctxtype	VALUE;


/********** local function-definition **********/

void	ComputeValue(epsind)
Indextype	epsind;
{
  SEQdef_entry	travel;
  def_entry	prod;
  SEQunit	rhstail;
  unit		un;
  unsigned short tag;
  Indextype	B, X;
  BitSet	oldset;

  VALUE = (ARRSEQctxtype)createARRSEQ(MAXNTERM);

  foreachinSEQdef_entry(PROD_SEQ, travel, prod)		/* Step 1 */
    {
      B = INDEX[prod.Vp_prod->lhsdid];			/* Step 2 */
      rhstail = prod.Vp_prod->rhs;	/* rhstail == X beta */
      getfirstpos(&rhstail, &tag);
      if ( tag == Kshnterm )				/* Step 3 */
	{
	  un = headSEQunit(rhstail);
	  X = INDEX[un.Vp_elunit->did];			/* Step 2 */
	  rhstail = tailSEQunit(rhstail);  /* rhstail == beta: Step 2 */

	  if ( (oldset = GetValueSet(VALUE,B,X))  ==  (BitSet)NULL )
							/* Step 4 */
	    VALUE[B] = insSEQctx(VALUE[B],
				 mkctx(X, MakeSetCopy(FirstOfRhs(epsind,
								 rhstail))
				      )
				);			/* Step 6, 7 */
	  else
	    (void)AddSetToSet(FirstOfRhs(epsind,rhstail), oldset);
							/* Step 5 */
	}  /* end of if */
    }  /* end of for */
  return;						/* Step 8 */
}  /* end of ComputeValue() */

/***************************************************/
/********** Implementation of ComputeCTX() *********/
/***************************************************/
void	ComputeCTX(epsind)
Indextype	epsind;		/* 0 <= epsind < MAXTERM */
{
  shstacktype	S1, S2;	
  SEQdef_entry	travel;	
  def_entry	nt;
  Indextype 	A, B, C;	/* 0 <= A, B, C < MAXNTERM */
  BitSet	help = (BitSet)NULL;
  BitSet	ctxAC;
  SEQctxtype	ctxlist;

#ifdef	STATISTIK
  StatistCTXloopno = 0;
#endif

  CTX = (ARRSEQctxtype)createARRSEQ(MAXNTERM);/* Allocation of global CTX */
  S1 = shcreate();
  S2 = shcreate();
  ComputeValue(epsind);		/* Computation of global VALUE */

  foreachinSEQdef_entry(NTERM_SEQ, travel, nt)		/* Step 1 */
    {
      A = INDEX[nt.Vp_nterm->did];
      S1 = shpush(S1, (sheltype)A);			/* Step 2 */
      S2 = shpush(S2, (sheltype)A);
      CTX[A] = insSEQctx(CTX[A],
			 mkctx(A, AddElemToSet(epsind,
					       MakeEmptySet(MAXTERM)
					      )
			      )
			);				/* Step 3, 4 */

      while ( !shempty(S2) )				/* Step 5 */
	{
#ifdef	STATISTIK
	  StatistCTXloopno++;
#endif

	  B = (Indextype)shtop(S2);			/* Step 6 */
	  S2 = shpop(S2);				/* Step 7 */

	  for ( ctxlist=VALUE[B];
		!emptySEQctx(ctxlist);
		ctxlist=tlSEQctx(ctxlist) )		/* Step 8 */
	    {
	      C = hdSEQctx(ctxlist).ntind;	/* It is B L C. */

	      if ( help )
		(void)InitSetToSet(hdSEQctx(ctxlist).set, help);
	      else
	        help = MakeSetCopy(hdSEQctx(ctxlist).set);/* Step 9 */
	      if ( IsElemInSet(epsind, help) )
		{
		  (void)SubElemFromSet(epsind, help);
		  (void)AddSetToSet(GetValueSet(CTX,A,B), help);
		}

	      if ( !shisin(S1, (sheltype)C) )		/* Step 10 */
		{
		  CTX[A] = insSEQctx(CTX[A], mkctx(C, help));
							/* Step 11, 12 */
		  help = (BitSet)NULL;
		  S1 = shpush(S1, (sheltype)C);		/* Step 13 */
		  S2 = shpush(S2, (sheltype)C);
		}  /* end of if then */
	      else					/* Step 14 */
		{
		  ctxAC = GetValueSet(CTX,A,C);
		  if ( !IsPartSet(help,ctxAC) )	/* Step 15 */
		    {
		      (void)AddSetToSet(help, ctxAC);/* Step 16 */
		      if ( !shisin(S2, (sheltype)C) )	/* Step 17 */
			S2 = shpush(S2, (sheltype)C);	/* Step 18 */
		    }  /* of if */
		}  /* end of else */		/* Step 19 */
	    }  /* end of for */
	}  /* end of while */
      while ( !shempty(S1) )
	S1 = shpop(S1);
    }  /* end of for */

#ifdef	STATISTIK
  statist_evalVALUEandCTX(VALUE, CTX);
#endif

  FreeARRSEQctx(VALUE);		/* VALUE will be nothing more used */
  return;
}  /* end of ComputeCTX() */

