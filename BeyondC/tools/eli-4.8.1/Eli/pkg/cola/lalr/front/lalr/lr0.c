/*
** $Id: lr0.c,v 1.8 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: lr0.c,v 1.8 1997/08/29 08:38:08 mjung Exp $";

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
/* File: lr0.c		First Edit: 08.02.89	  Last Edit: 29.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	23.01.90	From: Karl-Josef Prott			   */
/* 		14.02.90	From: Kalle				   */
/* 		28.02.90	From: Kalle				   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"

#include "parserlib.h"
#include "lr0.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif

/**************************************************************************/
/*definitions of types, constants, macros and functions local to this file*/
/**************************************************************************/

/********** local typedefinitions **********/

typedef struct inter
  {
    unsigned short	stateind;
    statetype		state;
    struct inter	*next;
  }  intermedtype;		/* intermediate represenatation of states */

typedef intermedtype	*SEQintermedtype;	/* sequence of states */

typedef SEQintermedtype	*ARRSEQintmedtype;	/* dynamic array of states */


/********** local constant-definition **********/


/********** variable-definitions local to this file but global 	**********/
/********** to all functions of it. 				**********/

/* initialized in CLOSURE() */
unsigned short	MAXITEMNO = 0;

/* initialized in ITEMS() and used in CLOSURE() */
unsigned short	*ADDED = NULL;	/* dynamic array indexed by nonterminals
				 * here: unsigned short <==> Boolean,
				 *       but don't change to Boolean */
Indextype	*ADDEDSTACK = NULL;	/* stack of indices i with
					 * ADDED[i] == TRUE */
Indextype	TOP = 0;	/* auxiliary to stack ADDEDSTACK */

/* initialized in cmrtl_compute_LR0automat() and used in cmp() */
SID	ORDERSID;	/* sid of the order-name in COMAR */


/********** local macro- and function-definition **********/

/* routines for ADDED and ADDEDSTACK */
#define	topadded()	(ADDEDSTACK[TOP])
#define pushadded(el)	(ADDEDSTACK[++TOP] = el)
#define popadded()	(--TOP)
#define emptyadded()	(!TOP)

void	createadded()
{
  if ( (ADDED = (unsigned short *)calloc(MAXNTERM+1,sizeof(unsigned short)))
	== NULL )
    {
      INT_ALLOC_ERR("createadded()");
      exit(1);
    }
  if ( (ADDEDSTACK = (Indextype *)calloc(MAXNTERM+1,sizeof(Indextype)))
	== NULL)
    {
      INT_ALLOC_ERR("createadded()");
      exit(1);
    }
}

void	freeadded()
{
  free((char *)ADDEDSTACK);
  free((char *)ADDED);
}


/* routines for handling with objects of type 'SEQintermedtype' and
 * 'intermedtype', where (l: SEQintermedtype, *el: intermedtype).
 */
#define initSEQintermed()	((SEQintermedtype)NULL)
#define emptySEQintermed(l)	((l) == (SEQintermedtype)NULL)
#define hdSEQintermed(l)	(*l)		/* result: intermedtype */
#define tlSEQintermed(l)	((l)->next)	/* result: SEQintermedtype */

intermedtype	*mkintermed(elem)
elemtype	*elem;
{
  intermedtype	*result;

  if ( (result = (intermedtype *)malloc((unsigned)sizeof(intermedtype)))
       == NULL )
    {
      INT_ALLOC_ERR("mkintermed()");
      exit(1);
    }

  result->next = initSEQintermed();
  result->state.Kernel = (SEQitemtype)elem;
  result->state.Goto = initSEQshift();
  result->stateind = MAXSTATE;

  return(result);

}  /* end of mkintermed() */

SEQintermedtype	insSEQintermed(l, el)
SEQintermedtype	l;
intermedtype	*el;
{
  el->next = l;
  return(el);
}  /* end of insSEQintermed() */

SEQintermedtype	rekdelSEQintermed(l)
SEQintermedtype	l;
{
  SEQintermedtype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return((SEQintermedtype)NULL);

}

/*********   implementation of the four below declared functions  *********/
/** for use in GOTO(), CLOSURE(), ITEMS() and cmrtl_compute_LR0automat()  **/

/* declaration of the functions implemented in this section */
shstacktype  compute_shifts(/* SEQitemtype items */);
DID	ComputeErrsymb(/* statetype state, SEQitemtype itemlist */);
ARRSEQintmedtype	createARRSEQintmed();
ERR	checkandsort_prods(/* String orderstr, SID ordersid */);


shstacktype	compute_shifts(items)
SEQitemtype	items;
{
  shstacktype	result;
  itemtype	item;
  unit		symb;

  result = shcreate();
  for ( ; !emptySEQitem(items); items = tlSEQitem(items) )
    {
      item = hdSEQitem(items);
      if ( tagofitem(item) != Kred )
	{		/* item must be Kshterm or Kshnterm */
#ifdef DEBUG_LR0
      	  if ( tagofitem(item) != Kshnterm  &&  tagofitem(item) != Kshterm )
	    INT_TAG_ERR("compute_shifts_1()", tagofitem(item));
#endif
	  symb = headSEQunit(ruleposofitem(item));
#ifdef DEBUG_LR0
	  if ( typeof(symb) != Kp_elunit )
	    INT_TAG_ERR("compute_shifts_2()", typeof(symb));
#endif
	  if ( !shisin(result, (sheltype)symb.Vp_elunit->did) )
	    result = shpush(result, (sheltype)symb.Vp_elunit->did);
	}  /* end of if */
    }  /* end of for */

return(result);

}  /* end of compute_shifts() */


DID	ComputeErrsymb(itemlist)
SEQitemtype	itemlist;
{
  unit	un;

  for ( ; !emptySEQitem(itemlist); itemlist = tlSEQitem(itemlist) )
    switch ( tagofitem(hdSEQitem(itemlist)) )
      {
	case Kshnterm:	break;
	case Kshterm :	un = headSEQunit(ruleposofitem(hdSEQitem(itemlist)));
			return( (DID)un.Vp_elunit->did );
	case Kred    :	return(UNDEF);
#ifdef DEBUG_LR0
	default      :	INT_TAG_ERR("ComputeErrsymb()",
				    tagofitem(hdSEQitem(itemlist)) );
			return(UNDEF);
#endif
      }  /* end of switch */

#ifdef DEBUG_LR0
  INT_ERR("ComputeErrsymb()");
#endif
  return(UNDEF);
}  /* end of ComputeErrsymb() */


/* only used in checkandsort_prods() */
Boolean	cmp(gr, sm)
p_prod	gr, sm; /* type changed from def_entry to p_prod to be compatible */
		/* with function IDLListSort from the IDL-library */
{
  p_prop_val	grprop, smprop;

#ifdef DEBUG_LR0
      def_entry	def1, def2;

      def1.Vp_prod = gr;
      def2.Vp_prod = sm;
      if ( typeof(def1) != Kp_prod )
	INT_TAG_ERR("cmp_1()", typeof(def1));
      if ( typeof(def2) != Kp_prod )
	INT_TAG_ERR("cmp_2()", typeof(def2));
#endif

  grprop = cmrlib_sidtopropval(gr->prop, ORDERSID);
  smprop = cmrlib_sidtopropval(sm->prop, ORDERSID);

#ifdef DEBUG_LR0
  if ( grprop == NULL  ||  smprop == NULL )
    {
      fprintf(stderr, "There exists a rule without ruleorder-property.\n");
      exit(1);
    }
#endif

  return( smprop->val.Vp_nval->val >= grprop->val.Vp_nval->val );
}


ARRSEQintmedtype	createARRSEQintmed()
{
  ARRSEQintmedtype	result;

  if ( (result = (ARRSEQintmedtype)calloc(MAXPROD,sizeof(SEQintermedtype)))
	== NULL )
    {
	INT_ALLOC_ERR("createARRSEQintmed()");
	exit(1);
    }

  return(result);
}

/* missing declaration( needed for the following sortSEQdef_entry() call*/
pGenList IDLListSort();

ERR	checkandsort_prods(orderstr, startstr, ordersid, startprod)
String	orderstr, startstr;
SID	*ordersid;
p_prod	*startprod;
{
  p_string	ordersym, startsym;
  short		i;
  SEQdef_entry	travel;
  def_entry	prod;

  if ( (ordersym = cmrlib_strtopstring(CMR->symbols, orderstr)) == NULL )
    return(LR0_NOORDER);
  *ordersid = ordersym->sid;

  if ( (startsym = cmrlib_strtopstring(CMR->symbols, startstr)) == NULL )
    return(LR0_NOSTART);
  *startprod = (p_prod)NULL;

  for (i = 0; (Indextype) i < MAXNTERM; i++)
    {
      foreachinSEQdef_entry(PRODWITHLHS[i], travel, prod)
	{
	  if ( !cmrlib_isbnfprod(prod.Vp_prod) )
	    return(LR0_GRNOTBNF);
	  if ( cmrlib_sidtopropval(prod.Vp_prod->prop,*ordersid)  ==  NULL )
	    return(LR0_PRODNOORDER);
	  if ( cmrlib_sidtoprop(prod.Vp_prod->prop,(SID)startsym->sid)  !=  NULL )
	    *startprod = prod.Vp_prod;

	}

      sortSEQdef_entry(PRODWITHLHS[i], cmp);
    }

  if ( *startprod == (p_prod)NULL )
    return(LR0_NOSTART);

  return(CMR_SUCCESS);

}  /* end of checkandsort_prods() */


/***************************************************************************/
/*	implementation of GOTO(), CLOSURE() and ITEMS()			   */
/***************************************************************************/

SEQitemtype	GOTO(I, X, isSR)
SEQitemtype	I;
DID		X;
unsigned short	*isSR;
{
  SEQitemtype		result, last;
  itemtype		item;
  unsigned short	tag, length;
  elemtype		*elem;
  SEQunit		rhstail;
  unit			un;

#ifdef	STATISTIK
  StatistGOTOcalls++;
#endif

  *isSR = FALSE;
  length = 0;
  last = result = initSEQitem();

  while ( !emptySEQitem(I) )
    {
      item = hdSEQitem(I);
      I = tlSEQitem(I);

      if ( tagofitem(item) != Kred )
	{
	  rhstail = ruleposofitem(item);
#ifdef DEBUG_LR0
	  if (emptySEQunit(rhstail))
	    {
	      INT_ERR("successor()");
	      exit(1);
	    }
#endif

	  un = headSEQunit(rhstail);
#ifdef DEBUG_LR0
	  if ( typeof(un) != Kp_elunit )
	    {
	      INT_TAG_ERR("successor()",typeof(un));
	      fprintf(stderr, "If grammar is not in BNF ");
	      fprintf(stderr, "it could be the reason.\n");
	      exit(1);
	    }
#endif

	  if ( X == un.Vp_elunit->did )
	    {
	      getnextpos(&rhstail, &tag);
	      elem = mkelem(tag, rulenoofitem(item), rhstail);
	      last = insbehindSEQitem(last, elem);
	      if ( emptySEQitem(result) )
		result = last;
	      length++;
	     } /* of if */
	} /* of if */
    } /* end of while */

  if ( length == 1  &&  tagofitem(hdSEQitem(result)) == Kred )
    {
      *isSR = rulenoofitem(hdSEQitem(result));
      result = rekdelSEQitem(result);
    }

  return(result);

}  /* end of GOTO() */


/* modify == TRUE:  items of the form A->. will be added to I (and the result)
 *           FALSE: I will not be modified
 *		    (already containing items of the form A->.)
 */
SEQitemtype	CLOSURE(I, modify)
SEQitemtype	I;
int		modify;
{
  SEQitemtype	allitems, notseen;
  itemtype	item;
  SEQunit	rhs;
  unit		NT;
  Indextype	ind;
  unsigned short tag;
  elemtype	*elem;
  SEQdef_entry	travel;
  def_entry	prod;
  short		itemno = 0;

  allitems = notseen = copySEQitem(I);

  while ( !emptySEQitem(notseen) )
    {
      item = hdSEQitem(notseen);

      if ( tagofitem(item) == Kshnterm )
	{
	  NT = headSEQunit(ruleposofitem(item));
	  ind = INDEX[NT.Vp_elunit->did];
	  if ( !ADDED[ind] )
	    {
	      ADDED[ind] = TRUE;
	      pushadded(ind);

	      foreachinSEQdef_entry(PRODWITHLHS[ind], travel, prod)
		{
#ifdef DEBUG_LR0
	  if ( typeof(prod) != Kp_prod )
	    INT_TAG_ERR("CLOSURE_2()",typeof(prod));
#endif
		  rhs = prod.Vp_prod->rhs;
		  getfirstpos(&rhs, &tag);
		  elem = mkelem(tag, (DID)prod.Vp_prod->did, rhs);
		  if ( tag == Kred )		/* elem is of form [A->.] */
		    if ( modify )	/* item is already in I and notseen */
		    {
			(void)insrearSEQitem(I,copySEQitem(elem));
		    	(void)insbehindSEQitem(notseen, elem);
		    }
		    else ;
		  else
		    (void)insbehindSEQitem(notseen, elem);
		}  /* end of for */
	    }  /* end of if */
	}  /* end of if */

      notseen = tlSEQitem(notseen);
      itemno++;

    }  /* end of while */

  while ( !emptyadded() )
    {
      ADDED[topadded()] = FALSE;
      popadded();
    }

  if ((unsigned short) itemno > MAXITEMNO )
    MAXITEMNO = itemno;

#ifdef	STATISTIK
{
  Boolean	HasNterm = FALSE;

  StatistSumitemno += itemno;
  itemno = lengthSEQitem(I);
  StatistSumKernel += itemno;
  if ( itemno > StatistMaxKernel )
    StatistMaxKernel = itemno;
  while ( !emptySEQitem(I) )
    {
      switch ( tagofitem(hdSEQitem(I)) )
	{
	  case	Kred	: itemno--;  break;
	  case	Kshterm : break;
	  case	Kshnterm: StatistSumKernelNterm++;
			  HasNterm = TRUE;
	}
      I = tlSEQitem(I);
    }
  StatistSumWithoutRed += itemno;
  if ( itemno > StatistMaxWithoutRed )
    StatistMaxWithoutRed = itemno;
  if ( HasNterm )
    StatistStatenoNterm++;
}
#endif

  return(allitems);

}  /* end of CLOSURE() */



ARRstatetype	ITEMS(startprod)
p_prod	startprod;
{

  stacktype	M;		/* stack containing all incompleted states */
  shstacktype	shiftsymbols;	/* stack containing all symbols being able
				 * to read in the state just worked on */
  ARRSEQintmedtype C0;		/* dynamic array indexed by the INDEX-dids
				 * of productions, containing all computed
				 * (completed and incompleted) states */
  ARRstatetype	result;		/* the complete LR(0)-automaton coded in the
				 * main internal data-structure 'LALR1_PDA'*/
  SEQunit	rhs;		/* right side of a COMAR-production */
  unsigned short tag, i;	/* auxiliary-variables */
  short		stateind;	/* auxiliary-variable  */
  intermedtype	*intmed, *actstate;/* states coded in an intermediate
				    * data-structure of states */
  SEQitemtype	allitems, next;	/* the items of a state coded typically */
  unsigned short isSR;		/* reporting a state as shiftred-optimized */
  SEQintermedtype list;		/* auxiliary-variable of a list of states */


  createadded();	/* allocation and initialization of the global
			 * variables ADDED and ADDEDSTACK used in closure()*/

  /* allocation and initialization of important variables */
  M = create();
  C0 = createARRSEQintmed(); /* C0[INDEX[i]] includes all states of which
			      * the first item is derived of production i */

  /* C0 = M = { [S->.x] / S->x is startproduction in grammar G } */
  MAXSTATE = 1;
  rhs = startprod->rhs;
  getfirstpos(&rhs, &tag);
  intmed = mkintermed(mkelem(tag,(DID)startprod->did,rhs));
  C0[INDEX[startprod->did]] = insSEQintermed(C0[INDEX[startprod->did]],intmed);
  M = push(M, (eltype)intmed);


  while ( !empty(M) ) /* as in documentation */
    {
      /* I = one_element_of(M); M = delete(M,I); */
      actstate = (intermedtype *)top(M);
      M = pop(M);

      /* all = closure(I); */
      allitems = CLOSURE(actstate->state.Kernel, TRUE);

      /* for_each X which can be read in the state represented by allitems */
      shiftsymbols = compute_shifts(allitems);
      while ( !shempty(shiftsymbols) )
	{
	  stateind = UNDEF;

	  /* next = goto(all,X), next must be <> { } */
	  next = GOTO(allitems, (DID)shtop(shiftsymbols), &isSR);

	  if ( !isSR )	/* if next <> {SR} */
	    {
	      /* searching next in C0 */
	      i = INDEX[rulenoofitem(hdSEQitem(next))];
	      list = C0[i];
	      while ( !emptySEQintermed(list) )
		{
		  if ( isequalSEQitem(next,hdSEQintermed(list).state.Kernel))
		    {
		      stateind = hdSEQintermed(list).stateind;
		      break; /* go out of while */
		    }
		  list = tlSEQintermed(list);
		}  /* end of while */

	      if ( stateind == UNDEF )  /* if next isn't an element of C0 */
		{
		  /* M = M union {next};  C0 = C0 union {next} */
		  MAXSTATE++;
		  intmed = mkintermed(next);
		  M = push(M, (eltype)intmed);
		  C0[i] = insSEQintermed(C0[i], intmed);
		  stateind = MAXSTATE;
		}  /* end of if */
	    }  /* end of if then */
	  else
	    stateind = - (short)isSR;

	  /* built_up_datastructure(I,X,next) */
	  actstate->state.Goto =
		insSEQshift(actstate->state.Goto,
			    mkshift( (DID)shtop(shiftsymbols),stateind) );

	  shiftsymbols = shpop(shiftsymbols);
	} /* end of while */

      actstate->state.Errsymb = ComputeErrsymb(allitems);

      (void)rekdelSEQitem(allitems);

    } /* end of while */

  /* deallocation: ADDED and ADDEDSTACK will be no longer used */
  freeadded();

  /* allocation of result */
  if ( (result = (ARRstatetype)malloc((MAXSTATE+1) * sizeof(statetype)))
	== (ARRstatetype)NULL )
    {
      INT_ALLOC_ERR("ITEMS()");
      exit(1);
    }

  /* coding the LR(0)-automaton in the correct data-structure */
  for (i=0; i<MAXPROD; i++)
    {
      for (list = C0[i]; !emptySEQintermed(list); list = tlSEQintermed(list))
	result[hdSEQintermed(list).stateind] = hdSEQintermed(list).state;

#ifdef	STATISTIK
     {
      int help = 0;

      for (list = C0[i]; !emptySEQintermed(list); list = tlSEQintermed(list))
	help++;
      if ( help > StatistMaxC0lg )
	StatistMaxC0lg = help;
     }
#endif

      (void)rekdelSEQintermed(C0[i]);
    }  /* end of for */
  result[0].Goto = NULL;
  result[0].Kernel = NULL;

  free((char *)C0);	/* deallocation: C0 will be no longer used */

  return(result);	/* return(C0) */

}  /* end of ITEMS() */


/***************************************************************************/
/*    implementation of the main function: cmrtl_compute_LR(0)automat()	   */
/***************************************************************************/

/* main fuction for computimg the ordered LR(0)-automaton */
ERR	cmrtl_compute_LR0automat(c,startname,ordername,LR0autom,startprod)
p_comar		c;
String		startname, ordername;
ARRstatetype	*LR0autom;
p_prod		*startprod;
{
  p_comar	sav;
  short		stat;

#ifdef	STATISTIK
  statist_ongrammar(PROD_SEQ);
#endif

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  if ( DEFTBL[0].IDLclassCommon != UNDEF && typeof(DEFTBL[0]) == Kp_prod )
    return(LR0_DEFTBLERR);
  if ( (stat = checkandsort_prods(ordername,startname,&ORDERSID,startprod))
	!=  CMR_SUCCESS )
    return(stat);

  *LR0autom = ITEMS(*startprod);

#ifdef	STATISTIK
  StatistShredStateno = statist_shredno(*LR0autom,PROD_SEQ);
  StatistStateno = MAXSTATE;
  StatistMaxitemno = MAXITEMNO;
#endif

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return(CMR_SUCCESS);

}  /* end of cmrtl_compute_LR(0)automat() */
