/*
** $Id: purdom.c,v 1.10 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: purdom.c,v 1.10 1997/08/29 08:38:08 mjung Exp $";

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
/* File: purdom.c	First Edit: 19.04.89	  Last Edit: 02.05.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 26.01.90	From: Karl-Josef Prott			   */
/* 		14.02.90	From: Kalle				   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"
#include "comar_func.h"
#include "name.h"

#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"

#include "first1.h"

#include "parserlib.h"
#include "lr0forpurdom.h"
#include "ctx.h"
#include "purdom.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif

/* Set DEBUG_FREE to get connections on all free positions. *
#define	DEBUG_FREE
*/
/* Set DEBUG_FORBIDDEN to get connections on all forbidden positions. *
#define	DEBUG_FORBIDDEN
*/
/* Set DEBUG_CONTINGENT to get connections on all contingent positions. *
#define DEBUG_CONTINGENT
*/

/************************************************************************/
/* Not exported typedefinitions used subsequently.			*/
/************************************************************************/

typedef struct
  {
    itemtype	*itptr;
    BitSet	lookahead;
    DID		shiftsymb;
    short	pos;
  }	situationtype;

typedef  struct
  {
    unsigned short	actlg;  /* Greatest index of an item in item[] */
    unsigned short	mainno; /* Greates index of a main-item in item[] */
    situationtype	*item;  /* item[0..actlg] : all items	*/
  }	PurStatetype;


typedef unsigned short	nodetype;
typedef struct succ
  {
    nodetype	node;
    struct succ	*next;
  }			succtype;
typedef	succtype *	SEQnodetype;
typedef	nodetype *	ARRnodetype;
typedef	SEQnodetype *	ARRSEQnodetype;



/************************************************************************/
/* Not exported global variables used in the subsequent functions.	*/
/************************************************************************/

PurStatetype	STATE;		/* Actual investigated state, array	*/
				/* State.item[] has MAXITEMNO elements	*/
ARRSEQnodetype	SUCC;		/* SUCC[i] == successors of node i,	*/
				/* ROOT <= i <= FINAL			*/
unsigned short	SIZE;		/* == MAXITEMNO+4, size of SUCC[] and 	*/
				/* other arrays of type 'ARRSEQnodetype'*/
Boolean		*NODE;		/*NODE[i] <==> i is in the actual subgraph*/
BitSet		EMPTYSET;	/* an empty bitset of size MAXTERM	*/
SEQnodetype	GARBAGE = (SEQnodetype)NULL;
				/* a garbage for elem. of a SEQnodetype-*/
				/* list to avoid often (de-)allocation 	*/
ARRBitSet	FirstOfRule;	/* FirstOfRule[i] == FIRST(u) and u is	*/
				/* the right side of rule with DID i	*/


/* IsElemInSet(i,ISFREE[j])  <==>  position (i,j) is free		*/
ARRBitSet	ISFREE;

/* a) ! IsElemInSet(i,ISFREE[j]) && IsElemInSet(i,ISFORBID[j]) <==>	*/
/*					position (i,j) is forbidden	*/
/* b) ! IsElemInSet(i,ISFREE[j]) && ! IsElemInSet(i,ISFORBID[j]) <==>	*/
/*					position (i,j) is contingent	*/
ARRBitSet	ISFORBID;

#define	ROOT	1		/* root of investigated graph		*/
#define	FINAL	(STATE.actlg+3)	/* final node of investigated graph	*/

/************************************************************************/

#ifdef DEBUG_PUR
#include "purdebug.c"
#endif

/************************************************************************/
/* Functions for handling with datas of type (ARRSEQ-, SEQ-)nodetype	*/
/************************************************************************/

void	inssucc(succ, node, son)
ARRSEQnodetype	succ;
nodetype	node, son;
{
  succtype	*elem;

  if ( GARBAGE )
    {
      elem = GARBAGE;
      GARBAGE = GARBAGE->next;
    }
  else if ( (elem = (succtype *)malloc(sizeof(succtype)))
	    ==  (succtype *)NULL )
    {
      INT_ALLOC_ERR("inssucc()");
      exit(1);
    }
  elem->node = son;
  elem->next = succ[node];
  succ[node] = elem;

  return;
}  /* end of inssucc() */


void	freesucc(succ, maxnode)
ARRSEQnodetype	succ;
nodetype	maxnode;
{
  nodetype	i;
  SEQnodetype	*nodelist;
  SEQnodetype	help;

  for (i=0, nodelist=succ; i<maxnode; i++, nodelist++)
    if ( *nodelist )
      {
	for ( help = *nodelist; help->next; help = help->next );
	help->next = GARBAGE;
	GARBAGE = *nodelist;
	*nodelist = NULL;
      }

  return;
}  /* end of freesucc() */




SEQnodetype	delsucc(list)
SEQnodetype	list;
{
  SEQnodetype	result;

  result = list->next;
  list->next = GARBAGE;
  GARBAGE = list;
  return(result);
}  /* end of delsucc() */


SEQnodetype	pushsucc(list, node)
SEQnodetype	list;
nodetype	node;
{
  succtype	*elem;

  if ( GARBAGE )
    {
      elem = GARBAGE;
      GARBAGE = GARBAGE->next;
    }
  else if ( (elem = (succtype *)malloc(sizeof(succtype)))
	    ==  (succtype *)NULL )
    {
      INT_ALLOC_ERR("pushsucc()");
      exit(1);
    }
  elem->node = node;
  elem->next = list;

  return(elem);
}  /* end of pushsucc() */


#define	topsucc(list)	(list->node)


void	freeGarbage()
{
  SEQnodetype	help;

  while ( GARBAGE )
    {
      help = GARBAGE;
      GARBAGE = GARBAGE->next;
      free( (char *)help );
    }

  return;
}  /* end of freeGarbage() */


ARRnodetype	createARRnodetype(number)
unsigned short	number;
{
  ARRnodetype	result;

  if ( (result = (ARRnodetype)calloc(number, sizeof(nodetype)))
	==  (ARRnodetype)NULL  )
    {
      INT_ALLOC_ERR("createARRnodetype(): ");
      exit(1);
    }

  return(result);
}  /* end of createARRnodetype() */

/************************************************************************/
/* Functions for computing the above defined global variables.		*/
/************************************************************************/

void	FreeFirstOfRule()
{
  short	i;

  for ( i=0; (Indextype) i < MAXPROD; i++ )
    FreeSet(FirstOfRule[i]);

  free( (char *)FirstOfRule );

  return;
}  /* end of FreeFirstOfRule() */


void	ComputeFirstOfRule(epsind)
Indextype	epsind;
{
  SEQdef_entry	travel;
  def_entry	prod;

  if ( (FirstOfRule = (ARRBitSet)calloc(MAXPROD, sizeof(BitSet)))
	== (ARRBitSet)NULL )
    {
      INT_ALLOC_ERR("computeFirstOfRule()");
      exit(1);
    }

  foreachinSEQdef_entry(PROD_SEQ, travel, prod)
    {
#ifdef DEBUG_PUR
      if ( typeof(prod) != Kp_prod )
	INT_TAG_ERR("ComputeFirstOfRule()", typeof(prod));
      if ( INDEX[prod.Vp_prod->did] > MAXPROD )
	INT_ERR("ComputeFirstOfRule()");
#endif
      FirstOfRule[INDEX[prod.Vp_prod->did]] =
		MakeSetCopy(FirstOfRhs(epsind, prod.Vp_prod->rhs));
    }  /* end of for */

  return;

}  /* end of ComputeFirstOfRule() */


void	InitISFREEandISFORBID()
{
  SEQdef_entry	travel;
  def_entry	prod;
  SEQunit	rhstail;
  unsigned short tag, lgrhs;

  ISFREE   = (ARRBitSet)malloc(MAXPROD * sizeof(BitSet));
  ISFORBID = (ARRBitSet)malloc(MAXPROD * sizeof(BitSet));
  if ( ISFREE == (ARRBitSet)NULL  ||  ISFORBID == (ARRBitSet)NULL )
    {
      INT_ALLOC_ERR("InitISFREEandISFORBID()");
      exit(1);
    }

  foreachinSEQdef_entry(PROD_SEQ, travel, prod )
    {
      lgrhs = 0;
      rhstail = prod.Vp_prod->rhs;
      getfirstpos(&rhstail, &tag);
      while ( rhstail )
	{
	  getnextpos(&rhstail, &tag);
	  lgrhs++;
	}
      ISFREE[INDEX[prod.Vp_prod->did]] = MakeFullSet(lgrhs+1);
      ISFORBID[INDEX[prod.Vp_prod->did]] = MakeEmptySet(lgrhs+1);
    }  /* end of for */

  return;
}  /* end of InitISFREEandISFORBID() */


void	InitGlobVar(epsind)
Indextype	epsind;
{
  short		i;
  situationtype	*situation;

  SIZE = MAXITEMNO + 4;

  /* MAXPROD, because of use in ComputeForbidPos(), later unneccessary
   * storage will be made free with 'ReInitSUCCandN()'. */
  if ( SIZE > MAXPROD )
    SUCC = (ARRSEQnodetype)createARRSEQ(SIZE);
  else
    SUCC = (ARRSEQnodetype)createARRSEQ(MAXPROD);

  if ( (NODE = (Boolean *)calloc(SIZE, sizeof(Boolean)))
	==  (Boolean *)NULL  )
    {
      INT_ALLOC_ERR("InitGlobVar(): NODE");
      exit(1);
    }
  NODE[ROOT] = TRUE;

  STATE.actlg = STATE.mainno = 0;
  if ( (STATE.item=(situationtype *)calloc(MAXITEMNO,sizeof(situationtype)))
	==  (situationtype *)NULL  )
    {
      INT_ALLOC_ERR("InitGlobVar(): STATE");
      exit(1);
    }
  for ( i=0, situation=STATE.item; (unsigned short) i < MAXITEMNO; i++, situation++)
    situation->lookahead = MakeEmptySet(MAXTERM);
  EMPTYSET = MakeEmptySet(MAXTERM);

  ComputeFirstOfRule(epsind);

  return;
}  /* end of InitGlobVar() */


void	FreeGlobVar()
{
  short		i;
  situationtype	*situation;

  FreeSet(EMPTYSET);
  for ( i=0, situation=STATE.item; (unsigned short) i < MAXITEMNO; i++, situation++)
    free( (char *)situation->lookahead );
  free( (char *)STATE.item );
  free( (char *)SUCC );
  free( (char *)NODE );
  freeGarbage();

  return;
}  /* end of FreeGlobVar() */

/************************************************************************/
/* Functions for building up the partial state position graph.		*/
/************************************************************************/

short	GivePos(ruleno, rhstail)
DID	ruleno;
SEQunit	rhstail;
{
  SEQunit	rhs;
  unsigned short tag;
  short	result = 0;

#ifdef DEBUG_PUR
  if ( typeof(DEFTBL[ruleno]) != Kp_prod )
    {
      INT_TAG_ERR("GivePos()", typeof(DEFTBL[ruleno]));
      return(0);
    }
#endif

  rhs = DEFTBL[ruleno].Vp_prod->rhs;
  getfirstpos(&rhs, &tag);
  while ( rhs != rhstail )
    {
      result++;
      getnextpos(&rhs, &tag);
    }

  return(result);

}  /* end of GivePos() */


#define	GiveSymb(rhs)	((DID)rhs->value.Vp_elunit->did)


SEQitemtype	ComputeMainItems(items)
SEQitemtype	items;
{
  situationtype	 *situation;
  itemtype	it;

  STATE.mainno = 0;
  for ( situation = STATE.item;
	!emptySEQitem(items);
	items = tlSEQitem(items), situation++ )
    {
      it = hdSEQitem(items);
      situation->pos = GivePos(rulenoofitem(it), ruleposofitem(it));
      switch ( tagofitem(it) )
	{
	  case Kshnterm:
	  case Kshterm : situation->itptr = &(items->item);
			 situation->shiftsymb = GiveSymb(ruleposofitem(it));
			 break;
	  case Kred    : if ( ! situation->pos ) /*if it isn't a main item */
			   return(items);	/* no more main items */
			 situation->itptr = &(items->item);
			 situation->shiftsymb = UNDEF;
			 break;
#ifdef DEBUG_PUR
	  default      : INT_TAG_ERR("ComputeMainItems()", tagofitem(it));
			 break;
#endif
	}  /* end of switch */
      STATE.mainno++;
    }  /* end of for */

#ifdef DEBUG_PUR
  if ( STATE.mainno == 0 )
    INT_ERR("ComputeMainItems()");
#endif
  return( (SEQitemtype)NULL );

}  /* end of ComputeMainItems() */

itemtype	*SearchItem(items, ruleno)
SEQitemtype	items;
DID		ruleno;
{
  for ( ; !emptySEQitem(items); items = tlSEQitem(items) )
    if ( rulenoofitem( hdSEQitem(items) )  ==  ruleno )
      return(&items->item);

#ifdef DEBUG_PUR
  INT_ERR("SearchItem()");
#endif

  return(NULL);
}  /* end of SearchItem() */


void	BuildState(kernel)
SEQitemtype	kernel;
{
  SEQitemtype	epsitems;
  nodetype	index, son;
  unsigned short tag;
  itemtype	*itemptr;
  unit		NT;
  Indextype	ind;
  SEQdef_entry	travel;
  def_entry	prod;
  SEQunit	rhs;
  commontype	*commonptr;

  epsitems = ComputeMainItems(kernel);
  STATE.actlg = --STATE.mainno;

  for ( index=0; index<=STATE.actlg; index++)
    {
      itemptr = STATE.item[index].itptr;
      if ( tagofitem((*itemptr)) == Kshnterm )
	{

	  NT = headSEQunit(ruleposofitem((*itemptr)));
#ifdef DEBUG_PUR
	  if ( typeof(NT) != Kp_elunit )
	    INT_TAG_ERR("BuildState_0()",typeof(NT));
	  if ( typeof(DEFTBL[NT.Vp_elunit->did]) != Kp_nterm )
	    INT_TAG_ERR("BuildState_1()",typeof(DEFTBL[NT.Vp_elunit->did]));
#endif

	  ind = INDEX[NT.Vp_elunit->did];
	  if ( !ADDED[ind] )
	    {
	      ADDED[ind] = STATE.actlg + 3;
	      pushadded(ind);

	      foreachinSEQdef_entry(PRODWITHLHS[ind], travel, prod)
		{
#ifdef DEBUG_PUR
		  if ( typeof(prod) != Kp_prod )
		    INT_TAG_ERR("BuildState_2()",typeof(prod));
#endif
		  STATE.actlg++;
		  rhs = prod.Vp_prod->rhs;
		  getfirstpos(&rhs, &tag);
		  STATE.item[STATE.actlg].pos = 0;
		  InitSetToSet(EMPTYSET, STATE.item[STATE.actlg].lookahead);
		  if ( rhs )	/* if it isn't a reduce-item */
		    {
		      STATE.item[STATE.actlg].shiftsymb = GiveSymb(rhs);
		      commonptr = mkcommon(tag,(DID)prod.Vp_prod->did,rhs);
		      STATE.item[STATE.actlg].itptr = (itemtype *)commonptr;
		    }  /* end of if then */
		  else
		    {
		      STATE.item[STATE.actlg].shiftsymb = UNDEF;
		      STATE.item[STATE.actlg].itptr =
				SearchItem(epsitems, (DID)prod.Vp_prod->did);
		    }  /* end of else */
		  /* index must be < than STATE.actlg */
		  inssucc(SUCC, index+2, STATE.actlg+2);
		}  /* end of for */
	    }  /* end of if then */
	  else
	    {
	      son = ADDED[ind];
	      foreachinSEQdef_entry(PRODWITHLHS[ind], travel, prod)
		{
#ifdef DEBUG_PUR
		  if ( typeof(prod) != Kp_prod )
		    INT_TAG_ERR("BuildState_2()",typeof(prod));
#endif
		  /* if (no edge from a node to itself) */
		  if ( index+2 != son )
		    inssucc(SUCC, index+2, son);
		  son++;
		}  /* end of for */
	    }  /* end of else */
	}  /* end  of if */
    }  /* end of for */

  while ( !emptyadded() )
    {
      ADDED[topadded()] = FALSE;
      popadded();
    }

  return;
}  /* end of BuildState() */


#define	RuleIndexOf(sit)	INDEX[((commontype *)sit->itptr)->ruleno]


BitSet	ComputeERC(nterm, epsind)
DID		nterm;
Indextype	epsind;
{
  nodetype	index;
  situationtype	*situation;
  BitSet	set;
  SEQunit	rhstail;
  unsigned short tag;

static  BitSet	result = (BitSet)NULL;

  if ( ! result )
    result = MakeEmptySet(MAXTERM);

  (void)InitSetToSet(EMPTYSET, result);

  for ( index=0, situation = STATE.item;
	index <= STATE.mainno;
	index++, situation++ )
    if ( tagofitem( (*situation->itptr) ) ==  Kshnterm
         &&
	 (set = GetValueSet(CTX,INDEX[situation->shiftsymb],INDEX[nterm]))
	 					!=  (BitSet)NULL
       ) {
      if ( IsElemInSet(epsind, set) )
	{
	  if ( IsEmptySet(situation->lookahead) )
	    {
	      rhstail = ruleposofitem((*situation->itptr));
	      getnextpos(&rhstail, &tag);
	      (void)InitSetToSet(FirstOfRhs(epsind,rhstail),
				 situation->lookahead);
	      if ( IsElemInSet(epsind, situation->lookahead) )
		{
		  (void)SubElemFromSet(epsind, situation->lookahead);
		  (void)AddSetToSet(situation->itptr->red.erc,
				    situation->lookahead);
		}
	    }  /* end of if */
	  (void)AddSetToSet(set, situation->lookahead);
	  (void)SubElemFromSet(epsind, situation->lookahead);
	  (void)AddSetToSet(situation->lookahead, result);
	}  /* end of if then */
      else 
	(void)AddSetToSet(set, result);
  } /* end of for and if */

  return(result);

}  /* end of ComputeERC() */


void	ComputeLookaheads(epsind)
Indextype	epsind;
{
  short		index;
  situationtype	*situation;
  BitSet	set;


  for ( index = STATE.actlg, situation = &STATE.item[index];
	index >= 0;
	index--, situation-- )
    switch ( tagofitem( (*situation->itptr) ) )
      {
	case Kred    :	(void)InitSetToSet(situation->itptr->red.erc,
					   situation->lookahead);
			break;
	case Kshterm :	(void)AddElemToSet(INDEX[situation->shiftsymb],
					   situation->lookahead);
			break;
	case Kshnterm:
	    if ( (unsigned short) index > STATE.mainno )
	      {
		(void)InitSetToSet(FirstOfRule[RuleIndexOf(situation)],
				   situation->lookahead);
		if ( IsElemInSet(epsind, situation->lookahead) )
		  {
		   (void)SubElemFromSet(epsind, situation->lookahead);
		   (void)AddSetToSet(ComputeERC(situation->shiftsymb,epsind),
				     situation->lookahead);
		  }
	      }  /* end of if then */
	    else
	      {
		/* if ( FirstOfRhs(epsind, tail(rulepos)) isn't computed ) */
		if ( IsEmptySet(situation->lookahead) )
		  {
		    set = FirstOfRhs(epsind,
				     ruleposofitem((*situation->itptr)));
		    (void)InitSetToSet(set, situation->lookahead);
		    if ( IsElemInSet(epsind, situation->lookahead) )
		      {
		        (void)SubElemFromSet(epsind, situation->lookahead);
		        (void)AddSetToSet(situation->itptr->red.erc,
				          situation->lookahead);
		      }
		  }  /* end of if then */
		else
		  {
		    set = FIRSTSETS[INDEX[situation->shiftsymb]];
		    if ( IsElemInSet(epsind, set) )
		      {
			(void)AddSetToSet(set, situation->lookahead);
			(void)SubElemFromSet(epsind, situation->lookahead);
		      }
		   else
		     InitSetToSet(set, situation->lookahead);
		  }  /* end of else */
	      }  /* end of else */

      }  /* end of switch */

  return;
}  /* end of ComputeLookaheads() */


short	PossibleTerms(indexarr)
Indextype	*indexarr;
{
  nodetype	index;
  situationtype	*situation;

static  BitSet	unionset = (BitSet)NULL;

  if ( unionset )
    (void)InitSetToSet(EMPTYSET, unionset);
  else
    unionset = MakeEmptySet(MAXTERM);

  for ( index = 0, situation = STATE.item;
	index <= STATE.mainno;
	index++, situation++
      )
    (void)AddSetToSet(situation->lookahead, unionset);

  return( EvalBitSet(indexarr, unionset) );

}  /* end of PossibleTerms() */

void	CompRootAndFinalNode()
{
  nodetype	index;

  for ( index = 0; index <= STATE.actlg; index++ )
    {
      if ( tagofitem( (*(STATE.item[index].itptr)) ) != Kshnterm )
        inssucc(SUCC, index+2, FINAL);
      if ( index <= STATE.mainno )
        inssucc(SUCC, ROOT, index+2);
    }  /* end of for */

  NODE[FINAL] = TRUE;
  return;

}  /* end of CompRootAndFinalNode() */

void	ComputePartialState(ind)
Indextype	ind;
{
  nodetype	index;
  situationtype	*situation;
  Boolean	*nodeptr;

  for ( index = 0, situation = STATE.item, nodeptr = &NODE[2];
	index <= STATE.actlg;
	index++, situation++, nodeptr++
      )
    *nodeptr = IsElemInSet(ind, situation->lookahead);

  return;

}  /* end of ComputePartialState() */


void	DeleteLookaheads()
{
  nodetype	index;
  situationtype	*situation;


  for ( index = 0, situation = STATE.item;
	index <= STATE.actlg;
	index++, situation++
      )
    (void)InitSetToSet(EMPTYSET, situation->lookahead);

  return;

}  /* end of DeleteLookaheads() */

/************************************************************************/
/* Functions for performing Step 3 of PaB's algorithm.			*/
/************************************************************************/

#define	MarkAsContingent(no)	\
   (void)SubElemFromSet(STATE.item[no].pos, \
			ISFREE[INDEX[rulenoofitem((*STATE.item[no].itptr))]])


void	EvalDominators(root, final, idom)
nodetype	root, final;
ARRnodetype	idom;
{
  nodetype	node;

  for ( node=idom[final]; node > root; node=idom[node] )
#ifdef DEBUG_PUR
    if ( !NODE[node] )
      INT_ERR("EvalDominators_1()");
    else
#endif
      NODE[node] = FALSE;

  for ( node = root+1; node < final; node++ )
    if ( NODE[node] )
#ifdef DEBUG_PUR
      if ( node < 2  ||  node-2 > STATE.actlg )
        INT_ERR("EvalDominators_2()");
      else
#endif
	{
	  MarkAsContingent(node-2);
	  NODE[node] = FALSE;
	}

  return;
}  /* end of EvalDominators() */

/************************************************************************/
/* Functions to transfer the results of PaB's algorithm into COMAR.	*/
/************************************************************************/

void	DelOthersWithDidFromGram(did)
DID	did;
{
  SEQdef_entry	d_travel;
  def_entry	prod;
  SEQunit	*u_travel;
  unit		un;

  foreachinSEQdef_entry(PROD_SEQ, d_travel, prod )
    {
      manipulSEQunit(prod.Vp_prod->rhs, u_travel, un)
	while ( un.Vp_elunit->did  ==  did )
	  {
	    removefirstSEQunit(*u_travel);
	    un = headSEQunit(*u_travel);
	  }  /* end of while and manipulSEQunit */
    }  /* end of for */

  return;
}  /* end of DelOthersWithDidFromGram() */


DID	LookForOtherWithSid(sid)
SID	sid;
{
  SEQdef_entry	others;
  def_entry	new;
  unsigned short numb;

  others = cmrlib_sidtoothers(OTHER_SEQ, sid);
  numb = lengthSEQdef_entry(others);
  switch ( numb )
    {
      case 0 :	new.Vp_other = cmrlib_newother(sid);
		break;
      case 1 :	new = headSEQdef_entry(others);
		DelOthersWithDidFromGram((DID)new.Vp_other->did);
		break;
      default:	fprintf(stderr, "There are several OTHER-Objects with ");
		fprintf(stderr, "SID: %d in the COMAR-Definition-Table.\n",
			sid);
		exit(1);
    }  /* end of switch */

  return(new.Vp_other->did);
}  /* end of LookForOtherWithSid() */

#if defined(DEBUG_FREE) || defined(DEBUG_FORBIDDEN) || defined(DEBUG_CONTINGENT)
#define	__CONNECTION__
#endif

void	ResultTransferToComar()
{
  DID		contdid, forbdid;
  unsigned short posrhs, typ;
  SEQdef_entry	d_travel;
  def_entry	prod;
  SEQunit	*u_travel;
  unit		un, help;
#ifdef __CONNECTION__
  def_entry	other;
  static SID	connectsid = 0;
  p_string	connectstring;


  if ( connectsid == 0 )
    {
      if ( (connectstring = cmrlib_strtopstring(CMR->symbols, CONNECTION))
	     == NULL )
	connectstring = cmrlib_newstring(CONNECTION);
      connectsid = connectstring->sid;
    }
#endif
#ifdef	STATISTIK
  StatistFree = StatistContingent = StatistForbidden = 0;
#endif

  contdid = LookForOtherWithSid( (SID)(cmrlib_newstring(CONTINGENT))->sid );
  forbdid = LookForOtherWithSid( (SID)(cmrlib_newstring(FORBIDDEN))->sid );

#ifdef	 DEBUG_CONTINGENT
  (void)cmrlib_newprop(cmrlib_getdef(CMR->definitions,contdid), connectsid);
#endif
#ifdef	 DEBUG_FORBIDDEN
  (void)cmrlib_newprop(cmrlib_getdef(CMR->definitions,forbdid), connectsid);
#endif

  foreachinSEQdef_entry(PROD_SEQ, d_travel, prod )
    {
      posrhs = 0;

      manipulSEQunit(prod.Vp_prod->rhs, u_travel, un)
	{
	  typ = typeof(DEFTBL[un.Vp_elunit->did]);
	  if ( typ == Kp_term  ||  typ == Kp_nterm )
	    {
	      if ( !IsElemInSet(posrhs, ISFREE[INDEX[prod.Vp_prod->did]]) )
	      {
		if ( IsElemInSet(posrhs,ISFORBID[INDEX[prod.Vp_prod->did]]) )
		  {
		    help.Vp_elunit = Mkp_elunit(forbdid);
		    appendfrontSEQunit(*u_travel, help);
		  }
		else
		  {
		    help.Vp_elunit = Mkp_elunit(contdid);
		    appendfrontSEQunit(*u_travel, help);
		  }
		u_travel = &(*u_travel)->next;
#ifdef	STATISTIK
 		if ( IsElemInSet(posrhs,ISFORBID[INDEX[prod.Vp_prod->did]]) )
		  StatistForbidden++;
		else
		  StatistContingent++;
		StatistFree--;
#endif
	      }  /* end of if */
#ifdef DEBUG_FREE
	      else
	      {
	        other.Vp_other = cmrlib_genOther("_FREE");
	        (void)cmrlib_newprop(other, connectsid);
		help.Vp_elunit =Mkp_elunit(other.Vp_other->did);
		appendfrontSEQunit(*u_travel, help);
		u_travel = &(*u_travel)->next;
	      }
#endif
#ifdef	STATISTIK
	      StatistFree++;
#endif
	      posrhs++;
	    }  /* end of if then */
	  else if ( typ == Kp_other )
	    ;
	  else
	    {
	      INT_TAG_ERR("ResultTransferToComar()", typ);
	      exit(1);
	    }
	}  /* end of manipulSEQunit */
    }  /* end of for */

  return;
}  /* end of ResultTransferToComar() */

/************************************************************************/
/* Functions for performing Step 2 of PaB's algorithm: the dominator-	*/
/* algorithm of Th. Lengauer, TOPLAS 1(1), p. 121-141, 1979		*/
/************************************************************************/

/* Global variables only for the dominator-algorithm.		*/
ARRnodetype	parent, ancestor, vertex; /* array[1..SIZE-1] of integer */
ARRnodetype	label, semi;		  /* array[0..SIZE-1] of integer */
ARRSEQnodetype	pred, bucket;		/* array[1..SIZE-1] of integer set */
nodetype	MAXDFSNUM;

void	InitForDominators()
{
  parent = createARRnodetype(SIZE);
  ancestor = createARRnodetype(SIZE);
  /* MAXPROD, because of use in ComputeForbidPos(), later unneccessary
   * storage will be made free with 'ReInitSUCCandN()'. */
  if ( SIZE > MAXPROD )
    vertex = createARRnodetype(SIZE);
  else
    vertex = createARRnodetype(MAXPROD);
  label = createARRnodetype(SIZE);
  semi = createARRnodetype(SIZE);
  pred = (ARRSEQnodetype)createARRSEQ(SIZE);
  bucket = (ARRSEQnodetype)createARRSEQ(SIZE);

  return;
}  /* end of InitForDominators() */

void	FreeDominatorArrs()
{
  freesucc(pred, SIZE);
  freesucc(bucket, SIZE);

  free( (char *)parent );
  free( (char *)ancestor );
  free( (char *)vertex );
  free( (char *)label );
  free( (char *)semi );
  free( (char *)pred );
  free( (char *)bucket );

  return;
}  /* end of FreeDominatorArrs() */


void	DFS(v)
nodetype	v;
{
  SEQnodetype	travel;
  nodetype	w;

  semi[v] = ++MAXDFSNUM;
  vertex[MAXDFSNUM] = label[v] = v;
  ancestor[v] = 0;
  for ( travel=SUCC[v]; travel!=(SEQnodetype)NULL; travel=travel->next )
    if ( NODE[w = travel->node] )
      {
        if ( semi[w]  ==  0 )
	  {
	    parent[w] = v;
	    DFS(w);
	  }
        inssucc(pred, w, v);
      }  /* end of if */
  return;
}  /* end of DFS() */

void	Compress(v)
nodetype	v;
{
  if ( ancestor[ancestor[v]] )	/* if ( ancestor[v] != 0 ) */
    {
      Compress(ancestor[v]);
      if ( semi[label[ancestor[v]]] < semi[label[v]] )
	label[v] = label[ancestor[v]];
      ancestor[v] = ancestor[ancestor[v]];
    }  /* end of if */
  return;
}  /* end of Compress() */


nodetype	Eval(v)
nodetype	v;
{
  if ( ancestor[v] )	/* if ( ancestor[v] != 0 ) */
    {
      Compress(v);
      return(label[v]);
    }
  else
    return(v);
}  /* end of Eval() */

#define	Link(v,w)	(ancestor[w] = v)


void	Dominators(root, final, dom)
nodetype	root, final;
ARRnodetype	dom;
{
  nodetype	i, u, v, w;
  SEQnodetype	travel, *firstptr;

  /* Step 1 */
  freesucc(pred, final+1);	/* for v:=1 until n do pred[v]:={} */
  freesucc(bucket, final+1);	/* for v:=1 until n do bucket[v]:={} */
  for ( v = 1; v <= final; v++ )
    semi[v] = 0;

  MAXDFSNUM = 0;
  DFS(root);
  for ( i = MAXDFSNUM; i > 1; i-- )
    {
      w = vertex[i];

  /* Step 2 */
      for ( travel=pred[w]; travel!=(SEQnodetype)NULL; travel=travel->next )
        {
	  u = Eval(travel->node);
	  if ( semi[u] < semi[w] )
	    semi[w] = semi[u];
	}  /* end of for */
      inssucc(bucket, vertex[semi[w]], w);
      Link(parent[w], w);

  /* Step 3 */
      firstptr = &bucket[parent[w]];
      /* for each v of bucket[parent[w]] */
      while ( *firstptr != (SEQnodetype)NULL )
	{
	  v = (*firstptr)->node;
	  *firstptr = delsucc(*firstptr); /*delete v from bucket[parent[w]]*/
	  u = Eval(v);
	  dom[v] = (semi[u] < semi[v])?  u : parent[w];
	}  /* end of while */

    }  /* end of for */

  /* Step 4 */
  for ( w = vertex[i=2]; i <= MAXDFSNUM; w = vertex[++i] )
    if ( dom[w]  !=  vertex[semi[w]] )
      dom[w] = dom[dom[w]];

  dom[root] = 0;

}  /* end of Dominators() */

/************************************************************************/
/* Functions for performing Step 1 of PaB's algorithm: modified version	*/
/* of Tarjan's Depth-First-Search algorithm to find cycles in digraphs.	*/
/************************************************************************/

#define N	vertex	/* type ARRnodetype	*/

SEQnodetype	Stack = (SEQnodetype)NULL;
SEQnodetype	Forblist = (SEQnodetype)NULL;
nodetype	Infinity;
nodetype	Depth = 0;

void	ReInitSUCCandN()
{
  freesucc(SUCC,MAXPROD);
  if ( MAXPROD > SIZE )
    {
      SUCC = (ARRSEQnodetype)realloc(SUCC,SIZE*sizeof(SEQnodetype));
      vertex = (ARRnodetype)realloc(vertex, SIZE*sizeof(nodetype));
    }

  return;
}  /* end of ReInitSUCCandN() */

Boolean	FirstSymbIsNT(rhs, ntptr)
SEQunit	rhs;
DID	*ntptr;
{
  unsigned short tag;
  unit		 un;

  getfirstpos(&rhs, &tag);
  if ( tag == Kshnterm )
    {
      un = headSEQunit(rhs);
      *ntptr = (DID)un.Vp_elunit->did;
      return(TRUE);
    }

  return(FALSE);
}  /* end of FirstSymbIsNT() */


void	BuildGrammarGraph()
{
  SEQdef_entry	travel1, travel2;
  def_entry	prod1, prod2;
  DID		NT;

  foreachinSEQdef_entry(PROD_SEQ, travel1, prod1)
    {
      if ( FirstSymbIsNT(prod1.Vp_prod->rhs, &NT) )
        foreachinSEQdef_entry(PRODWITHLHS[INDEX[NT]], travel2, prod2)
	  inssucc(SUCC, INDEX[prod1.Vp_prod->did], INDEX[prod2.Vp_prod->did]);
    }  /* end  of for */

  return;
}  /* end of BuildGrammarGraph() */


/* The algorithm to find cycles is analogous the 'Digraph'-algorithm of	*/
/* DeRemer and Pennello, TOPLAS 4(4), p. 625, 1982.			*/
void	DFS_Cycle(x)
nodetype	x;
{
  nodetype	d;
  SEQnodetype	*travel;
  nodetype	y;
  Boolean	iscycle;

  Stack = pushsucc(Stack, x);
  N[x] = d = ++Depth;

  for ( travel = &SUCC[x];
	*travel != (SEQnodetype)NULL;
	travel = &(*travel)->next )
    {
      y = (*travel)->node;
      if ( x == y )
	{	/* Cycle consisting of one edge is found. */
	  *travel = delsucc(*travel);
	  Forblist = pushsucc(Forblist, x);
	  if ( *travel  ==  (SEQnodetype)NULL )
	    break;
	}  /* of if then */
      else
	{
	  if ( N[y]  ==  0 )
	    DFS_Cycle(y);
	  if ( N[y] < N[x] )
	    N[x] = N[y];
	}  /* of else */
    }  /* end of for */

  /* if ( iscycle  &&  N[x] ==d ),
   * a cycle consisting of at least two egdes is found. */
  iscycle =  topsucc(Stack) != x;
  if ( N[x]  ==  d )
    do
      {
	N[y = topsucc(Stack)] = Infinity;
        Stack = delsucc(Stack);
	Depth--;
	if ( iscycle )
	  Forblist = pushsucc(Forblist, y);
      }
    while ( y != x );

  return;
}  /* end of DFS_Cycle() */


void	MarkAsForbidden(ruleind)
Indextype	ruleind;
{
  (void)SubElemFromSet(0, ISFREE[ruleind]);
  (void)AddElemToSet(0, ISFORBID[ruleind]);

  return;
}


void	ComputeForbidPos()
{
  nodetype	node;

  Infinity = MAXPROD;

  for ( node = 0; node < MAXPROD; node++ )
    if ( N[node] == 0 )
      DFS_Cycle(node);

  while ( Forblist ) /*Label as forbidden each position that derives itself*/
    {
      MarkAsForbidden(Forblist->node);
      Forblist = delsucc(Forblist);
    }  /* end of while */

  return;
}  /* end of ComputeForbidPos() */

#undef	N

/**************************************************************************/
/* The algorithm of Purdom and Brown, Acta Informatica 14, p.299-315, 1980*/
/**************************************************************************/

/* Purdom and Brown's (PaB's) algorithm */
void	PurdomAndBrown(autom, epsind)
ARRstatetype	autom;
Indextype	epsind;
{
  unsigned short q,	/* a state number */
		 i,	/* index of TermArr */
		number;	/* number of elements in 'TermArr[]' */
  Indextype	*TermArr; /* TermArr[0..number-1] are indices of terminals */
  ARRnodetype	dom;	/* dom[i]==j <==> j is an immediate dominator of i */

  /* Allocation and initialization of all used arrays and other variables */
  InitGlobVar(epsind);
  if ( (TermArr = (Indextype *)malloc(MAXTERM*sizeof(Indextype)))
	   == (Indextype *)NULL )
    {
      INT_ALLOC_ERR("PurdomAndBrown()");
      exit(1);
    }
  InitForDominators();
  dom = createARRnodetype(SIZE);
  createadded();
  InitISFREEandISFORBID();	/* Includes Step 4 of PaB's algorithm */

#ifdef	DEBUG_PUR
      DebugInit();
#endif

  /* Step 1 of PaB's algorithm */
  BuildGrammarGraph();
  ComputeForbidPos();
  ReInitSUCCandN();

  /* Execution of Purdom and Brown's algorithm state by state */
  for ( q = 1; q <= MAXSTATE; q++ )
    {
      /* Building up the partial state position graph of state q */
      BuildState(autom[q].Kernel);
      ComputeLookaheads(epsind);
      number = PossibleTerms(TermArr);
      CompRootAndFinalNode();

#ifdef	DEBUG_PUR
      DebugState(q, STATE, SUCC, FINAL);
#endif

      /* PaB's algorithm will be performed subgraph by subgraph. */
      for ( i=0; i<number; i++ )
	{
	  /* Building the subgraph associated with terminal represent by i */
	  ComputePartialState(TermArr[i]);

	  /* Step 2 of PaB's algorithm, the predominators are coded in dom */
	  Dominators(ROOT, FINAL, dom);	/* the dominator algorithm */

#ifdef	DEBUG_PUR
	  DebugSubgraph(TermArr[i], FINAL, NODE, dom);
#endif

	  /* Step 3 of PaB's algorithm */
	  EvalDominators(ROOT, FINAL, dom);
	}  /* end of for */

      /* Preparing SUCC and STATE for the next state */
      freesucc(SUCC, FINAL+1);
      DeleteLookaheads();
      NODE[FINAL] = FALSE;
    }  /* end of for */

#ifdef	DEBUG_PUR
      DebugClose();
#endif

  /* Transfer the results of PaB's algorithm in the COMAR-datastructure. */
  ResultTransferToComar();

  /* Deallocation of all space */
  freeadded();
  free( (char *)TermArr );
  free( (char *)dom );
  FreeDominatorArrs();
  FreeGlobVar();

  return;
}  /* end of PurdomAndBrown() */

/* Only exported function: Interface of PaB's algorithm	*/
ERR	cmrtl_purdom(c, autom)
p_comar		c;
ARRstatetype	autom;
{
  p_comar	sav;
  SEQdef_entry	epslist;
  def_entry	eps;

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

  PurdomAndBrown(autom, INDEX[eps.Vp_term->did]);

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return(CMR_SUCCESS);
}  /* end of cmrtl_purdom() */
