/*
** $Id: lalr.c,v 1.9 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: lalr.c,v 1.9 1997/08/29 08:38:08 mjung Exp $";

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
/* File: lalr.c		First Edit: 27.02.89	  Last Edit: 31.03.89      */
/*	 								   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 05.05.89	From: Karl-Josef Prott			   */
/***************************************************************************/

/* Table of Contents:
 *	SECTION 1: Functions and types for use in all following sections
 *	SECTION 2: Formerly: Implementation of 'ComputeCTX()' and its
 *		   (sub-)functions and types
 *		   Now: you will find it in module "ctx"
 *	SECTION 3: Implementation of 'Digraph()' and its (sub-)functions
 *		   and types
 *	SECTION 4: Implementation of 'IVE()' the most (!) important function
 *		   in this file and all its (sub-)functions not listed above
 *	SECTION 5: Implementation of 'cmrtl_compute_LALR1()', the only 
 *		   exported function (It calls 'IVE()' and before it takes
 *		   care of, that the "environment" for 'IVE()' is correct.)
 */

#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"

#include "prsiface.h"
#include "parserlib.h"
#include "absparser.h"		/* for AUTOM */
#include "first1.h"
#include "ctx.h"
#include "lalr.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif


/***************************************************************************/
/* SECTION 1: Functions and types for use in all following sections	   */
/***************************************************************************/

/********** local typedefinitions **********/

  typedef struct sub
    {
      DID		nterm;
      BitSet		set;
      SEQsettype	s_include;
      struct sub	*next;
    }	subtype;

typedef subtype		*SEQsubtype;
typedef SEQsubtype	*ARRSEQsubtype;


/********** variable-definitions local to this file but global 	**********/
/********** to all functions of it.				**********/

ARRSEQsubtype	SubSet;	/* all SET(Q,C) existing of more than one ERC(Q,C) */


/********** local function-definitions **********/

/* functions for handling with subtype, SEQsubtype, ARRSEQsubtype */

static	SEQsubtype	insSEQsub(list, el)
SEQsubtype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQsub() */

static	subtype	*mksub(nt,set,setlist)
DID		nt;
BitSet		set;
SEQsettype	setlist;
{
  subtype	*result;

  if ( (result = (subtype *)malloc(sizeof(subtype)))  ==  (subtype *)NULL )
     {
      INT_ALLOC_ERR("mksub()");
      exit(1);
    }
  result->nterm = nt;
  result->set = set;
  result->s_include = setlist;
  result->next = (subtype *)NULL;
  return(result);
}  /* end of mksub() */

static	void	AddToSubSet(subset, q, nterm)
ARRSEQsubtype	subset;
unsigned short	q;
shnterm_itemtype nterm;
{
  unit		nt;
  SEQsubtype	list;

  nt = headSEQunit(nterm.common.rulepos);
  for ( list=subset[q]; list!=(SEQsubtype)NULL; list=list->next )
    {
      if  ( list->nterm  == nt.Vp_elunit->did )
	{
	  (void)AddSetToSet(nterm.erc, list->set);

#ifdef	STATISTIK
	  StatistS_inclno += lengthSEQset(list->s_include);
	  StatistS_inclno += lengthSEQset(nterm.e_include);
#endif

	  list->s_include = mixSEQset( list->s_include,
				       copySEQset(nterm.e_include) );
#ifdef	STATISTIK
	  StatistS_inclno -= lengthSEQset(list->s_include);
	  StatistSETno--;
#endif

	  return;
	}  /* end of if */
    }  /* end of for */

  subset[q] = insSEQsub(subset[q], mksub( (DID)nt.Vp_elunit->did,
					   MakeSetCopy(nterm.erc),
					   copySEQset(nterm.e_include) )
			);
#ifdef	STATISTIK
  StatistSubsetno++;
#endif

  return;
}  /* end of AddToSubSet() */


/* functions with general tasks */

static	void	GetNodeValues(Fx,s_incl,q,nt)
BitSet		*Fx;
SEQsettype	*s_incl;
unsigned short	q;
DID		nt;
{
  Boolean	found = FALSE;
  SEQsubtype	list;
  SEQitemtype	itemlist;
  unit		un;

  for ( list=SubSet[q]; list!=(SEQsubtype)NULL; list=list->next )
    if ( list->nterm == nt )
      {
	*Fx = list->set;
	*s_incl = list->s_include;
	found = TRUE;
	return;
      }  /* end of if */

  if ( !found )
    for ( itemlist=AUTOM[q].Kernel;
	  !emptySEQitem(itemlist);
	  itemlist=tlSEQitem(itemlist) )
      if ( tagofitem(hdSEQitem(itemlist))  ==  Kshnterm )
	{
	  un = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
	  if ( un.Vp_elunit->did  ==  nt )
	    {
	      *Fx = hdSEQitem(itemlist).shnterm.erc;
	      *s_incl = hdSEQitem(itemlist).shnterm.e_include;
	      /* if *Fx == NULL, there must be another item with nt right */
	      /*		 of the dot and 'erc' != NULL.		  */
	      if ( *Fx != (BitSet)NULL )
		return;
	    }  /* end of if */
	}  /* end of if */
  /* end of if */

  *Fx = (BitSet)NULL;
  *s_incl = (SEQsettype)NULL;
  return;

}  /* end of GetNodeValues() */


/***************************************************************************/
/* SECTION 2: look at module "ctx"	 				   */
/***************************************************************************/


/***************************************************************************/
/* SECTION 3: Implementation of 'Digraph()' and its (sub-)functions	   */
/*	      and types	   						   */
/***************************************************************************/

/********** local constant-definition **********/

#define	MAXUNSIGNED	-1

/********** local typedefinitions **********/

typedef struct N
  {
    DID			nterm;
    unsigned short	value;
    struct N		*next;
  }	Ntype;

typedef Ntype		*SEQNtype;
typedef SEQNtype	*ARRSEQNtype;


/********** variable-definitions local to this file but global 	**********/
/********** to all functions of it.				**********/

ARRSEQNtype	N;	/* representing function N of algorithm Digraph */


/********** local macro- and function-definitions **********/


/* functions for handling with Ntype, SEQNtype or ARRSEQNtype */

static	SEQNtype	insSEQN(list, el)
SEQNtype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQN() */

static	Ntype	*mkN(nt,val)
DID		nt;
unsigned short val;
{
  Ntype	*result;

  if ( (result = (Ntype *)malloc(sizeof(Ntype)))  ==  (Ntype *)NULL )
     {
      INT_ALLOC_ERR("mkN()");
      exit(1);
    }
  result->nterm = nt;
  result->value = val;
  result->next = (Ntype *)NULL;
  return(result);
}  /* end of mkN() */

static	Ntype	*GetN(q,nt)
unsigned short	q;
DID		nt;
{
  SEQNtype	list;

  for ( list=N[q]; list!=(SEQNtype)NULL; list=list->next )
    if ( list->nterm  ==  nt )
      return(list);

  return( (Ntype *)NULL );

}  /* end of GetN() */

static	Boolean	AddToN(N,q,nt)
ARRSEQNtype	N;
unsigned short	q;
DID		nt;
{
  SEQNtype	*list;

  for (list= (&N[q]); *list!=(SEQNtype)NULL; list= (&(*list)->next) )
    if ( (*list)->nterm > nt )
      ;
    else if ( (*list)->nterm < nt )
      {
        *list = insSEQN(*list,mkN(nt,0));
	return(TRUE);
      }
    else
      return(FALSE);
  /* end of for */

  *list = insSEQN(*list,mkN(nt,0));
  return(TRUE);

}  /* end of AddToN() */


/* functions with general tasks */

static	void	InitForDigraph(N, SubSet, epsind)
ARRSEQNtype	*N;
ARRSEQsubtype	*SubSet;
Indextype	epsind;
{
  shstacktype	S;	/* S contains nonterminals. If the actual state
			 * consists of several items with the dot before
			 * the same nonterminal X, X will be pushed into S.
			 */
  SEQitemtype	itemlist;
  unsigned short q;
  unit		nt;

  *N = (ARRSEQNtype)createARRSEQ(MAXSTATE+1);
  *SubSet = (ARRSEQsubtype)createARRSEQ(MAXSTATE+1);
  S = shcreate();

  for ( q=1; q<=MAXSTATE; q++ )
    {
      for ( itemlist=AUTOM[q].Kernel;
	    !emptySEQitem(itemlist);
	    itemlist=tlSEQitem(itemlist) )
        if ( tagofitem(hdSEQitem(itemlist))  ==  Kshnterm
	     &&  hdSEQitem(itemlist).shnterm.erc != (BitSet)NULL
	   )
	  {
	    (void)SubElemFromSet(epsind,hdSEQitem(itemlist).shnterm.erc);
	    nt = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
	    if ( !AddToN(*N, q, (DID)nt.Vp_elunit->did) )
	      if ( !shisin(S, (sheltype)nt.Vp_elunit->did) )
		S = shpush(S, (sheltype)nt.Vp_elunit->did);
	  }  /* end of if */
      /* end of for */

#ifdef	STATISTIK
      if ( !shempty(S) )
	StatistStatesWithSubset++;
#endif

      while ( !shempty(S) )
	{
	  for ( itemlist=AUTOM[q].Kernel;
	        !emptySEQitem(itemlist);
	        itemlist=tlSEQitem(itemlist) )
	    if ( tagofitem(hdSEQitem(itemlist))  ==  Kshnterm
	         &&  hdSEQitem(itemlist).shnterm.erc != (BitSet)NULL
	       )
	      {
	        nt = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
		if ( (DID)nt.Vp_elunit->did  ==  (DID)shtop(S) )
	          AddToSubSet(*SubSet, q, hdSEQitem(itemlist).shnterm);
	      }  /* end of if */
	  S = shpop(S);
	}  /* end of while */
    }  /* end of for */
  return;
}  /* end of InitForDigraph() */


static	BitSet	Traverse(q,x)
unsigned short	q;
Ntype		*x;
{
  BitSet	Fx, Fy;
  SEQsettype	s_incl, dummy;
  Ntype		*y;
  unsigned short d;

static	unsigned short	depth = 0;
static	stacktype	S = (stacktype)NULL;
static	shstacktype	Q = (shstacktype)NULL;

  S = push(S, (eltype)x);
  Q = shpush(Q, (sheltype)q);
  x->value = d = ++depth;

  GetNodeValues(&Fx, &s_incl, q, x->nterm);
#ifdef DEBUG_LALR
  if ( Fx == (BitSet)NULL )
    INT_ERR("Traverse_1()");
#endif
  for ( ; !emptySEQset(s_incl); s_incl=tlSEQset(s_incl) )
    {
      y = GetN(hdSEQset(s_incl).stateno, hdSEQset(s_incl).ntermind);
#ifdef DEBUG_LALR
      if ( y == (Ntype *)NULL )
        INT_ERR("Traverse_2()");
#endif
      if ( y->value  ==  0 )
	(void)AddSetToSet(Traverse(hdSEQset(s_incl).stateno,y), Fx);
      else
	{
	  GetNodeValues(&Fy, &dummy, hdSEQset(s_incl).stateno, y->nterm);
	  (void)AddSetToSet(Fy, Fx);
	}  /* end of else */
      x->value = (x->value < y->value)? x->value : y->value;
    }  /* end of for */

  if ( x->value == d )
    do
      {
	y = (Ntype *)top(S);
	GetNodeValues(&Fy, &dummy, (DID)shtop(Q), y->nterm);
#ifdef DEBUG_LALR
        if ( ! IsPartSet(Fy, Fx) )
          INT_ERR("Traverse_3()");
#endif
	(void)AddSetToSet(Fx, Fy);
	y->value = (unsigned short)MAXUNSIGNED;
	S = pop(S);
	Q = shpop(Q);
	depth--;
      }
    while ( y != x );

  return(Fx);

}  /* end of Traverse() */

static	void	Digraph()
{
  unsigned short q;
  Ntype		 *x;

  for ( q=1; q<=MAXSTATE; q++ )
    for ( x=N[q]; x!=(SEQNtype)NULL; x=x->next )
      if ( x->value  ==  0 )
	(void)Traverse(q, x);

  return;

}  /* end of Digraph() */


/***************************************************************************/
/* SECTION 4: Implementation of 'IVE()' the most (!) important function	   */
/*	      in this file and all its (sub-)functions not listed above	   */
/***************************************************************************/

static	void	FreeNandSubSet()
{
  unsigned short q;
  SEQNtype	list, el;
  SEQsubtype	sublist, subel;

  for ( q=1; q<=MAXSTATE; q++ )
    {
      list=N[q];
      while ( list != (SEQNtype)NULL )
	{
	  el = list;
	  list=list->next;
	  free((char *)el);
	}  /* end of while */

      sublist=SubSet[q];
      while ( sublist != (SEQsubtype)NULL )
	{
	  (void)rekdelSEQset(sublist->s_include);
	  subel = sublist;
	  sublist=sublist->next;
	  free((char *)subel);
	}  /* end of while */
    }  /* end of for */

  return;

}  /* end of FreeNandSubSet() */


/* return  > 0 : return is the next state under symbol 'symb'
 * 	   < 0 : next state is SR-optimized, -return is a rulenumber
 *        == 0 : undefined, 'symb' isn't a valid symbol in this state
 */
static	unsigned short	GetNextState(succ, symb)
SEQshifttype	succ;
DID		symb;
{
  for (; !emptySEQshift(succ); succ=tlSEQshift(succ) )
    if ( hdSEQshift(succ).symbol  ==  symb )
#ifdef DEBUG_LALR
      if ( hdSEQshift(succ).staterule  ==  0 )
	INT_ERR("GetNextState()");
      else
#endif
        return( (hdSEQshift(succ).staterule < (short)0)?
				0 : hdSEQshift(succ).staterule );

  return(UNDEF);
}  /* end of GetNextState() */


static	elemtype	*addSGLtoERC(SGL,items,rhstail)
BitSet		SGL;
SEQitemtype	items;
SEQunit		rhstail;
{
  for (; !emptySEQitem(items); items=tlSEQitem(items) )
    if ( ruleposofitem(hdSEQitem(items))  ==  rhstail )
      {
#ifdef DEBUG_LALR
	if ( tagofitem(hdSEQitem(items)) != Kshnterm )
	  INT_TAG_ERR("addSGLtoERC",tagofitem(hdSEQitem(items)));
#endif
	if ( hdSEQitem(items).shnterm.erc  ==  (BitSet)NULL )
	  {
#ifdef	STATISTIK
	    StatistERCno++;
#endif
	    hdSEQitem(items).shnterm.erc = MakeSetCopy(SGL);
	  }
	else
	  (void)AddSetToSet(SGL, hdSEQitem(items).shnterm.erc);

	return(items);
      }  /* end of if */

#ifdef DEBUG_LALR
  INT_ERR("addSGLtoERC()");
#endif
  return( (elemtype *)NULL );
}  /* end of addSGLtoERC() */


static	void	addE_include(item,stateind,ntdid)
elemtype	*item;
unsigned short		stateind;
DID			ntdid;
{
  SEQsettype	*list;
  settype	elem;

#ifdef DEBUG_LALR
  if ( item == (elemtype *)NULL )
    return;		/* Internal Error: already known */

  if ( tagofitem(item->item) != Kshnterm )
    INT_TAG_ERR("addE_include()",tagofitem(item->item));
#endif

  for ( list= &item->item.shnterm.e_include;
	!emptySEQset(*list);
	list= &tlSEQset(*list) )
    {
      elem = hdSEQset(*list);
      if ( elem.stateno > stateind )
	;
      else if ( elem.stateno < stateind )
	break;
      else
	if ( elem.ntermind == ntdid )
	  return;
	else if ( elem.ntermind > ntdid )
	  ;
	else
	  break;
    }  /* end of for */

#ifdef	STATISTIK
  StatistE_inclno++;
#endif

  *list = insSEQset(*list, mkset(stateind,ntdid));
  return;
}  /* end of addE_include() */


static	elemtype *addSGLtoLookah(SGL,items,proddid)
BitSet		SGL;
SEQitemtype	items;
DID		proddid;
{
  for (; !emptySEQitem(items); items=tlSEQitem(items) )
    {
      if ( rulenoofitem(hdSEQitem(items)) == proddid  &&
	   tagofitem(hdSEQitem(items)) == Kred )
        {
	  if ( hdSEQitem(items).red.erc  ==  (BitSet)NULL )
	    hdSEQitem(items).red.erc = MakeSetCopy(SGL);
	  else
	    (void)AddSetToSet(SGL, hdSEQitem(items).red.erc);

	  return(items);
        }  /* end of if */
    }  /* end of for */

#ifdef DEBUG_LALR
  INT_ERR("addSGLtoLookah()");
#endif
  return( (elemtype *)NULL );
}  /* end of addSGLtoLookah() */


static	void	addL_include(item,stateind,ntdid)
elemtype	*item;
unsigned short	stateind;
DID		ntdid;
{
  SEQsettype	list;

#ifdef DEBUG_LALR
  if ( item == (elemtype *)NULL )
    return;		/* Internal Error: already known */

  if ( tagofitem(item->item) != Kred )
    INT_TAG_ERR("addE_include()",tagofitem(item->item));
#endif

  for (list=item->item.red.l_include;!emptySEQset(list);list=tlSEQset(list))
    if ( hdSEQset(list).stateno == stateind  &&
	 hdSEQset(list).ntermind == ntdid )
      return;		/* Set(stateind,ntdid) is already in list */

#ifdef	STATISTIK
  StatistL_inclno++;
#endif

  item->item.red.l_include =
		insSEQset(item->item.red.l_include,mkset(stateind,ntdid));
  return;
}  /* end of addL_include() */


static	DID	CompleteErrsymb(set)
BitSet	set;
{
  SEQdef_entry	travel;
  def_entry	term;

  foreachinSEQdef_entry(TERM_SEQ, travel, term)
#ifdef DEBUG_LALR
    if ( typeof(term)  !=  Kp_term )
      INT_TAG_ERR("CompleteErrsymb()",typeof(term));
    else
#endif
      if ( IsElemInSet(INDEX[term.Vp_term->did], set) )
        return( term.Vp_term->did );

#ifdef DEBUG_LALR
  INT_ERR("CompleteErrsymb()");
#endif
  return(UNDEF);
}  /* end of CompleteErrsymb() */


/********************************************/
/********** Implementation of IVE() *********/
/********************************************/
static	void	IVE(epsind)
Indextype	epsind;
{
  Indextype	A1;
  DID		C1;
  unsigned short q, p, tag;
  SEQitemtype	itemlist;
  unit		un;
  SEQunit	beta1, rhstail;
  SEQctxtype	ctxlist;
  BitSet	SGL, helpset;
  Boolean	prop;
  SEQdef_entry	travel;
  def_entry	prod;
  elemtype	*itemptr;
  SEQsubtype	sublist;
  SEQsettype	setlist, dummy;

#ifdef	STATISTIK
  StatistE_inclno = StatistL_inclno = StatistERCno = 0;
#endif

  /* FIRST-sets are already computed: variable FIRSTSETS * Step 1 */

  /* Compute CTX-sets. */
  ComputeCTX(epsind);					/* Step 2 */

  /* Compute sets Initial_SET, Initial_ERC, Initial_Lookahead
   * and relations s_include, e_include, l_include
   */
  for (q=1; q<=MAXSTATE; q++)				/* Step 3 */
    for (itemlist=AUTOM[q].Kernel;
	 !emptySEQitem(itemlist);
	 itemlist = tlSEQitem(itemlist)
	)						/* Step 4 */
      if ( tagofitem(hdSEQitem(itemlist)) == Kshnterm )
	{
	  un = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
	  C1 = un.Vp_elunit->did;
	  beta1 = tailSEQunit(ruleposofitem(hdSEQitem(itemlist)));
	  for (ctxlist=CTX[INDEX[C1]];
	       !emptySEQctx(ctxlist);
	       ctxlist=tlSEQctx(ctxlist)
	      )						/* Step 5 */
	    {
	      A1 = hdSEQctx(ctxlist).ntind;
	      SGL = MakeSetCopy(hdSEQctx(ctxlist).set);	/* Step 5.1 */
	      if ( IsElemInSet(epsind, SGL) )
		{
		  (void)SubElemFromSet(epsind, SGL);
		  (void)AddSetToSet(FirstOfRhs(epsind,beta1), SGL);
		}  /* end of if */
	      prop = IsElemInSet(epsind, SGL);		/* Step 5.2 */

	      foreachinSEQdef_entry(PRODWITHLHS[A1], travel, prod)
		{					/* Step 5.3 */
		  p = q;				/* Step 5.3.1 */
		  rhstail = prod.Vp_prod->rhs;
		  getfirstpos(&rhstail, &tag);
		  while ( !emptySEQunit(rhstail) )	/* Step 5.3.2 */
		    {
		      un = headSEQunit(rhstail);
		      p = GetNextState(AUTOM[p].Goto,
				       (DID)un.Vp_elunit->did
				      );		/* Step 5.3.2.1 */
		      getnextpos(&rhstail, &tag);
		      if ( p > 0 )		/* Step 5.3.2.2, 1th cond. */
			if ( tag == Kshnterm )	/* Step 5.3.2.2, 2nd cond. */
			  {		/* rhstail can't be empty ! */
			    helpset= FirstOfRhs(epsind,tailSEQunit(rhstail));
			    if ( IsElemInSet(epsind, helpset) )
			      {			/* Step 5.3.2.2, 3rd cond. */
				itemptr = addSGLtoERC(SGL, AUTOM[p].Kernel,
						       rhstail);
				if ( prop )
				  addE_include(itemptr, q, C1);
			      }  /* end of if */
			  }  /* end of if */
		    }  /* end of while, end of Step 5.3.2 */

		  if ( p > 0 )				/* Step 5.3.3 */
		    {
		      itemptr = addSGLtoLookah(SGL,AUTOM[p].Kernel,
					       (DID)prod.Vp_prod->did);
		      if ( prop )
			addL_include(itemptr,q,C1);
		    }  /* end of if */
		}  /* end of for, end of Step 5.3 */
	      FreeSet(SGL);
	    }  /* end of for, end of Step 5 */
	}  /* end of if */
    /* end of for, end of Step 4 */
  /* end of for, end of Step 3 */

  /* FreeARRSEQctx(CTX); */

#ifdef	STATISTIK
  StatistS_inclno = StatistE_inclno;
  StatistSETno = StatistERCno;
  StatistSubsetno = StatistStatesWithSubset = 0;
#endif

  /* Compute sets SET */
  InitForDigraph(&N, &SubSet, epsind);			/* Step 6 */
  Digraph();						/* Step 7 */

  /* Compute Sets ERC. */
  for ( q=1; q<=MAXSTATE; q++ )				/* Step 9 */
    for (sublist=SubSet[q]; sublist!=(SEQsubtype)NULL; sublist=sublist->next)
      for ( itemlist=AUTOM[q].Kernel;
	    !emptySEQitem(itemlist);
	    itemlist = tlSEQitem(itemlist) )
	if ( tagofitem(hdSEQitem(itemlist))  ==  Kshnterm )
	  {
	    un = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
	    if ( un.Vp_elunit->did  ==  sublist->nterm )
	      for ( setlist = hdSEQitem(itemlist).shnterm.e_include;
		    !emptySEQset(setlist);
		    setlist = tlSEQset(setlist)
		  )
		{
		  GetNodeValues( &helpset,&dummy,hdSEQset(setlist).stateno,
				 hdSEQset(setlist).ntermind );
		  (void)AddSetToSet(helpset,hdSEQitem(itemlist).shnterm.erc);
		}  /* end of for */
	  }  /* end of if */
  /* end of all for */

  /* Compute Lookaheads. */
  for ( q=1; q<=MAXSTATE; q++ )				/* Step 11 */
    {
      for ( itemlist=AUTOM[q].Kernel;
	    !emptySEQitem(itemlist);
	    itemlist = tlSEQitem(itemlist) )
        if ( tagofitem(hdSEQitem(itemlist))  ==  Kred )
	  {
	    for ( setlist = hdSEQitem(itemlist).red.l_include;
	          !emptySEQset(setlist);
	          setlist = tlSEQset(setlist)
	        )
	      {
	        GetNodeValues( &helpset,&dummy,hdSEQset(setlist).stateno,
			       hdSEQset(setlist).ntermind );
	        (void)AddSetToSet(helpset,hdSEQitem(itemlist).red.erc);
	      }  /* end of for */
	    (void)SubElemFromSet(epsind,hdSEQitem(itemlist).red.erc);
	  }  /* end of if */

      /* Computing of yet undefined error-symbols */
      if ( AUTOM[q].Errsymb  ==  UNDEF )
	{
          for ( itemlist=AUTOM[q].Kernel;
	        !emptySEQitem(itemlist);
	        itemlist = tlSEQitem(itemlist) )
            if ( tagofitem(hdSEQitem(itemlist))  ==  Kred )
	      {
	        AUTOM[q].Errsymb = 
			CompleteErrsymb( hdSEQitem(itemlist).red.erc );
		break;
	      }  /* end of if */
#ifdef DEBUG_LALR
	  if ( AUTOM[q].Errsymb  ==  UNDEF )
	    INT_ERR("IVE()");
#endif
	}  /* end of if */
    }  /* end of for */

  FreeNandSubSet();
  return;

}  /* end of IVE() */


/***************************************************************************/
/* SECTION 5: Implementation of 'cmrtl_compute_LALR1()', the only exported */
/*	      function (It calls 'IVE()' and before it takes care of,	   */
/*	      that the "environment" for 'IVE()' is correct.)	   	   */
/***************************************************************************/


ERR	cmrtl_compute_LALR1(c,automat)
p_comar		c;
ARRstatetype	automat;
{
  p_comar	sav;
  short		stat;
  SEQdef_entry	epslist;
  def_entry	eps;

  AUTOM = automat;	/* Initialization of AUTOM used as global variable
			 * of all functions for the automaton in this file */

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  /* Computation of an empty terminal */
  epslist = cmrlib_sidtoterms(c->definitions,S_EMPTY);
  switch ( lengthSEQdef_entry(epslist) )
    {
      case 0	: eps.Vp_term = cmrlib_newterm(S_EMPTY);
		  break;
      case 1	: eps = headSEQdef_entry(epslist);
		  removefirstSEQdef_entry(epslist);
		  break;
      default	: return(LALR_AMBEPS);
    }  /* end of switch */

  /* Computation of global variable FIRSTSETS */
  if ( FIRSTSETS == (ARRBitSet)NULL  &&
       (stat=readFIRSTSETS(CMR))  !=  CMR_SUCCESS )
    return(stat);

  /* Computation of LALR(1)-lookaheads */
  IVE(INDEX[eps.Vp_term->did]);

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  /* automat will be implicitely changed by 'IVE()' */
  return(CMR_SUCCESS);

}  /* end of cmrtl_compute_LALR1() */
