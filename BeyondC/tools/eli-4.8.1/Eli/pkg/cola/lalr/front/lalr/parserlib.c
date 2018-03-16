/*
** $Id: parserlib.c,v 1.9 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: parserlib.c,v 1.9 1997/08/29 08:38:08 mjung Exp $";

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
/* File: parserlib.c	First Edit: 08.02.89	  Last Edit: 21.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	13.07.89	From: Karl-Josef Prott			   */
/*		28.02.90	From: Kalle				   */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"

#include "first1.h"
#include "parserlib.h"

#ifdef	STATISTIK
#include "statistik.h"
#endif


/***** EXPORTED VARIABLES *****/

/* This variable will be computed in cmrtl_compute_LR0automat(). */
unsigned short	MAXSTATE = 0;


/* These variables will be computed in cmrtl_lalr1tst()	   */
ARRSEQconflicttype	CONFLICTSTATES = (ARRSEQconflicttype)NULL;
Boolean		ISLALR1 = TRUE;

SEQmodiftype	MODIFICATIONS = initSEQmodif();

/**************************************************************************/

elemtype	*mkelem(tag,ruleno,rulepos)
unsigned short	tag, ruleno;
SEQunit		rulepos;
{
  elemtype	*new;

  if ( (new = (elemtype *)malloc(sizeof(elemtype)))  ==  (elemtype *)NULL )
    {
      INT_ALLOC_ERR("mkelem()");
      exit(1);
    }

  new->item.common.tag = tag;
  new->item.common.ruleno = ruleno;
  new->item.common.rulepos = rulepos;

  switch(tag)
    {
      case Kred		: new->item.red.erc = NULL;
			  new->item.red.l_include = initSEQset();
			  break;
      case Kshterm	: break;
      case Kshnterm	: new->item.shnterm.erc = NULL;
			  new->item.shnterm.e_include = initSEQset();
			  break;
#ifdef DEBUG_PRSLIB
      default	: INT_TAG_ERR("mkelem",tag);
#endif
    } /* end of switch */

  new->next = NULL;
  return(new);
} /* end of mkelem() */


elemtype	*copyelem(item)
itemtype	item;
{
  elemtype	*new;

  if ( (new = (elemtype *)malloc(sizeof(elemtype)))  ==  (elemtype *)NULL )
    {
      INT_ALLOC_ERR("copyelem()");
      exit(1);
    }

  new->item = item;
  new->next = NULL;
  return(new);
}  /* end of copyelem() */


commontype	*mkcommon(tag,ruleno,rulepos)
unsigned short	tag, ruleno;
SEQunit		rulepos;
{
  commontype	*new;

  if ( (new = (commontype*)malloc(sizeof(commontype))) == (commontype*)NULL )
    {
      INT_ALLOC_ERR("mkcommon()");
      exit(1);
    }

  new->tag = tag;
  new->ruleno = ruleno;
  new->rulepos = rulepos;

  return(new);
} /* end of mkcommon() */


SEQitemtype	delfirstSEQitem(l)
SEQitemtype	l;
{
  SEQitemtype	result;

  result = l->next;
  free((char *)l);

  return(result);
} /* end of delfirstSEQitem() */


SEQitemtype	rekdelSEQitem(l)
SEQitemtype	l;
{
  SEQitemtype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return( (SEQitemtype)NULL );
}  /* end of rekdelSEQitem() */


SEQitemtype	insSEQitem(list, el)
SEQitemtype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQitem() */


SEQitemtype	insrearSEQitem(list, el)
SEQitemtype	list, el;
{
  SEQitemtype	travel;

  el->next = (SEQitemtype)NULL;
  if ( emptySEQitem(list) )
    return(el);
  else
    {
      travel = list;
      while ( !emptySEQitem(tlSEQitem(travel)) )
	travel = tlSEQitem(travel);
      travel->next = el;
      return(list);
    }  /* end of else */
}  /* end of insrearSEQitem() */


SEQitemtype	copySEQitem(l)
SEQitemtype	l;
{
  SEQitemtype	last = initSEQitem(), result = initSEQitem();
  elemtype	*elem;

  if ( !emptySEQitem(l) )
    {
      elem = copyelem(hdSEQitem(l));
      result = insbehindSEQitem(result,elem);
      l = tlSEQitem(l);
    }
  last = result;
  while ( !emptySEQitem(l) )
    {
      elem = copyelem(hdSEQitem(l));
      last = insbehindSEQitem(last,elem);
      l = tlSEQitem(l);
    }
  return(result);
}

unsigned short	lengthSEQitem(l)
SEQitemtype	l;
{
  unsigned short result = 0;

  for ( ; !emptySEQitem(l); l = tlSEQitem(l) )
    result++;

  return(result);
}  /* end of lengthSEQitem() */


/* returns TRUE if hd(l) is not a kernel item */
Boolean	iskernelSEQitem(l)
SEQitemtype	l;
{
  SEQunit	rhstail;
  unsigned short tag;

  rhstail = DEFTBL[rulenoofitem(hdSEQitem(l))].Vp_prod->rhs;
  getfirstpos(&rhstail,&tag);

 /* rhstail==NULL (==TRUE) <==> epsilon-production
  *  <==> hdSEQitem(l) is not a kernel item
  */
  return( rhstail == (SEQunit)NULL );
}  /* end of iskernelSEQitem() */

Boolean	isequalSEQitem(l1, l2)
SEQitemtype	l1, l2;
{
  while ( !emptySEQitem(l1)  &&  !emptySEQitem(l2) )
    {
      if ( ruleposofitem(hdSEQitem(l1))  != ruleposofitem(hdSEQitem(l2))
	   ||  rulenoofitem(hdSEQitem(l1))  != rulenoofitem(hdSEQitem(l2))
	 )
	return(FALSE);
      l1 = tlSEQitem(l1);
      l2 = tlSEQitem(l2);
    }

  /* l1 or l2 must be empty! */
  if ( !emptySEQitem(l1) )
    return( iskernelSEQitem(l1) );	/* l1 and l2 are equal <==> (only) the  */
  if ( !emptySEQitem(l2) )	  	/* kernel items of l1 and l2 are equal. */
    return( iskernelSEQitem(l2) );	/* nonkernel items are always at the end*/

  /* l1 and l2 must be empty! */
  return(TRUE);

}  /* end of isequalSEQitem() */

/**************************************************************************/

shifttype	*mkshift(symb,index)
DID	symb;
short	index;
{
  shifttype	*result;

  if ( (result = (shifttype *)malloc((unsigned)sizeof(shifttype))) == NULL )
    {
      INT_ALLOC_ERR("mkshift()");
      exit(1);
    }

  result->symbol = symb;
  result->staterule = index;
  result->next = (shifttype *)NULL;

  return(result);

}  /* end of mkshift() */


SEQshifttype	delfirstSEQshift(l)
SEQshifttype	l;
{
  SEQshifttype	result;

  result = l->next;
  free((char *)l);

  return(result);
} /* end of delfirstSEQshift() */


SEQshifttype	rekdelSEQshift(l)
SEQshifttype	l;
{
  SEQshifttype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return((SEQshifttype)NULL);
} /* end of rekdelSEQshift() */


SEQshifttype	insSEQshift(list, el)
SEQshifttype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQshift() */


unsigned short	lengthSEQshift(list)
SEQshifttype	list;
{
  short	result = 0;

  for ( ; !emptySEQshift(list); list = tlSEQshift(list) )
    result++;

  return(result);
}  /* end of lengthSEQshift() */

SEQshifttype    deltermSEQshift(list, term)
SEQshifttype list; 
DID term;
{
  SEQshifttype travel;

  if ( emptySEQshift(list) )
	return(list);
  if ( emptySEQshift(tlSEQshift(list)) )
	return( (list->symbol == term)? (SEQshifttype)NULL : list );
  for ( travel = list; 
	!emptySEQshift(tlSEQshift(travel)); 
	travel = tlSEQshift(travel) 
      )
	if ( tlSEQshift(travel)->symbol == term )
	{
		tlSEQshift(travel) = tlSEQshift(tlSEQshift(travel));
		return (list);
	}
#ifdef DEBUG_PRSLIB
  INT_ERR("deltermSEQshift()");
#endif
  return( (SEQshifttype)NULL );
}  /* end of deltermSEQshift() */


/**************************************************************************/

SEQsettype	delfirstSEQset(l)
SEQsettype	l;
{
  SEQsettype	result;

  result = l->next;
  free((char *)l);

  return(result);
} /* end of delfirstSEQset() */


SEQsettype	rekdelSEQset(l)
SEQsettype	l;
{
  SEQsettype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return((SEQsettype)NULL);
}  /* end of rekdelSEQset() */


SEQsettype	insSEQset(list, el)
SEQsettype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQset() */


settype	*mkset(stateind,ntdid)
unsigned short	stateind;
DID		ntdid;
{
  settype	*result;

  if ( (result = (settype *)malloc((unsigned)sizeof(settype))) == NULL )
    {
      INT_ALLOC_ERR("mkset()");
      exit(1);
    }

  result->stateno = stateind;
  result->ntermind = ntdid;
  result->next = (settype *)NULL;

  return(result);
}  /* end of mkset() */

SEQsettype	copySEQset(setlist)
SEQsettype	setlist;
{
  SEQsettype	last = initSEQset(), result = initSEQset();
  settype	*new;
  settype	hd;

  if ( !emptySEQset(setlist) )
    {
      hd = hdSEQset(setlist);
      new = mkset(hd.stateno, hd.ntermind);
      result = insbehindSEQset(result, new);
      setlist = tlSEQset(setlist);
    }
  last = result;
  while ( !emptySEQset(setlist) )
    {
      hd = hdSEQset(setlist);
      new = mkset(hd.stateno, hd.ntermind);
      last = insbehindSEQset(last, new);
      setlist = tlSEQset(setlist);
    }
  return(result);

}  /* end of copySEQset() */


SEQsettype	mixSEQset(list1, list2)
SEQsettype	list1, list2;
{
  SEQsettype	result, last, hd;

  result = initSEQset();
  last = result = insSEQset(result,mkset(0,0));	/* insert dummy-element */
  while ( !emptySEQset(list1)  &&  !emptySEQset(list2) )
    if ( ( hdSEQset(list1).stateno  >  hdSEQset(list2).stateno )  ||
		( hdSEQset(list1).stateno  ==  hdSEQset(list2).stateno  &&
		  hdSEQset(list1).ntermind  >  hdSEQset(list2).ntermind )
       )
      {
	hd = list1;
	list1 = tlSEQset(list1);
	last = insbehindSEQset(last, hd);
      }  /* end of if */
    else if ( ( hdSEQset(list1).stateno  <  hdSEQset(list2).stateno )  ||
		( hdSEQset(list1).stateno  ==  hdSEQset(list2).stateno  &&
		  hdSEQset(list1).ntermind  <  hdSEQset(list2).ntermind )
            )
      {
	hd = list2;
	list2 = tlSEQset(list2);
	last = insbehindSEQset(last, hd);
      }  /* end of else if */
    else
      {
	hd = list1;
	list1 = tlSEQset(list1);
	last = insbehindSEQset(last, hd);
	list2 = delfirstSEQset(list2);
      }  /* end of else */

  /* Only one list can be empty! */
  if ( !emptySEQset(list1) )
    last->next = list1;
  if ( !emptySEQset(list2) )
    last->next = list2;
      
  return( delfirstSEQset(result) );

}  /* end of mixSEQset() */

unsigned short	lengthSEQset(l)
SEQsettype	l;
{
  unsigned short result = 0;

  for ( ; !emptySEQset(l); l = tlSEQset(l) )
    result++;

  return(result);
}  /* end of lengthSEQset() */


/**************************************************************************/

conflicttype	*mkconflict(isredred,set,rule1,rule2)
Boolean	isredred;
BitSet	set;
DID	rule1, rule2;
{
  conflicttype	*result;

  if ( (result = (conflicttype *)malloc((unsigned)sizeof(conflicttype)))
	== (conflicttype *)NULL )
    {
      INT_ALLOC_ERR("mkconflict()");
      exit(1);
    }

  result->red_red = isredred;
  result->set = set;
  result->ruleno1 = rule1;
  result->ruleno2 = rule2;
  result->next = (conflicttype *)NULL;

  return(result);

}  /* end of mkconflict() */

SEQconflicttype	insSEQconflict(list, el)
SEQconflicttype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQconflict() */

SEQconflicttype	rekdelSEQconflict(l)
SEQconflicttype	l;
{
  SEQconflicttype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return((SEQconflicttype)NULL);
}  /* end of rekdelSEQconflict() */


/**************************************************************************/

modiftype	*mkmodif(tag, term, ruleno, stateno)
Boolean		tag;
DID		term, ruleno;
unsigned short	stateno;
{
  modiftype	*result;

  if ( (result = (modiftype *)malloc((unsigned)sizeof(modiftype)))
	== (modiftype *)NULL )
    {
      INT_ALLOC_ERR("mkmodif()");
      exit(1);
    }

  result->tag = tag;
  result->term = term;
  result->ruleno = ruleno;
  result->stateno = stateno;
  result->next = (modiftype *)NULL;

  return(result);

}  /* end of mkmodif() */

SEQmodiftype	insSEQmodif(list, el)
SEQmodiftype	list, el;
{
  el->next = list;
  return(el);
}  /* end of insSEQmodif() */

SEQmodiftype	delfirstSEQmodif(l)
SEQmodiftype	l;
{
  SEQmodiftype	result;

  result = l->next;
  free((char *)l);

  return(result);
} /* end of delfirstSEQmodif() */

SEQmodiftype	rekdelSEQmodif(l)
SEQmodiftype	l;
{
  SEQmodiftype	result;

  while ( l != NULL )
    {
      result = l->next;
      free((char *)l);
      l = result;
    }

  return((SEQmodiftype)NULL);
}  /* end of rekdelSEQmodif() */


/**************************************************************************/

void	getfirstpos(rhsptr,tagptr)
SEQunit		*rhsptr;
unsigned short	*tagptr;
{
  SEQunit	travel;
  unit		un;

#ifdef	STATISTIK
  StatistgetfirstposCalls++;
#endif

  foreachinSEQunit(*rhsptr, travel, un)
    {
#ifdef DEBUG_PRSLIB
      if ( typeof(un) != Kp_elunit )
	    {
	      INT_TAG_ERR("getfirstpos()",typeof(un));
	      fprintf(stderr, "If grammar is not in BNF ");
	      fprintf(stderr, "it could be the reason.\n");
	      exit(1);
	    }
#endif

      switch ( typeof(DEFTBL[un.Vp_elunit->did]) )
	{
	  case Kp_term	: *rhsptr = travel;
			  *tagptr = Kshterm;
			  return;
	  case Kp_nterm	: *rhsptr = travel;
			  *tagptr = Kshnterm;
			  return;
	  case Kp_other	: break;
#ifdef DEBUG_PRSLIB
	  default	: 
	      INT_TAG_ERR("getfirstpos()",typeof(DEFTBL[un.Vp_elunit->did]));
#endif
	} /* end of switch */
    } /* end of for */

  *rhsptr = NULL;
  *tagptr = Kred;
  return;
} /* end of getfirstpos() */


BitSet	FirstOfRhs(epsind,rhs)
Indextype	epsind;
SEQunit		rhs;
{
  BitSet	helpset;
  SEQunit	rhstail;
  unit		un;
  unsigned short tag;

static	BitSet	initset	= (BitSet)NULL;
static	BitSet	result	= (BitSet)NULL;

#ifdef	STATISTIK
  StatistFirstOfRhsCalls++;
  StatistFirstOfRhsLoops++;
#endif

  if ( ! initset )
    {
      initset = MakeEmptySet(MAXTERM);
      (void)AddElemToSet(epsind,initset);
      result = MakeEmptySet(MAXTERM);
    }

  rhstail = rhs;
  (void)InitSetToSet(initset, result);

  getfirstpos(&rhstail, &tag);
  while ( !emptySEQunit(rhstail) )
    {
#ifdef	STATISTIK
      StatistFirstOfRhsLoops++;
#endif

      switch ( tag )
        {
	  case Kshnterm:
	    un = headSEQunit(rhstail);
	    helpset = FIRSTSETS[INDEX[un.Vp_elunit->did]];
	    if ( !IsElemInSet(epsind, helpset) )
	      {
	        rhstail = (SEQunit)NULL;    /* forces end of for */
		(void)SubElemFromSet(epsind, result);
	      }  /* of if */
	    (void)AddSetToSet(helpset, result);
	    break;
	  case Kshterm:
	    un = headSEQunit(rhstail);
	    rhstail = (SEQunit)NULL;        /* forces end of for */
	    (void)SubElemFromSet(epsind, result);
	    (void)AddElemToSet(INDEX[un.Vp_elunit->did], result);
	    break;
#ifdef DEBUG_LALR
	  case Kred:
	  default:
	    INT_TAG_ERR("ComputeValue()",tag);
#endif
        }  /* end of switch */
      getnextpos(&rhstail, &tag);
    }  /* end of while */

  return(result);

}  /* end of FirstOfRhs() */


/**************************************************************************/


ARRSEQtype	createARRSEQ(number)
unsigned short	number;	/* number of elements in the allocated array */
{
  ARRSEQtype	result;

  if ( (result = (ARRSEQtype)calloc(number,sizeof(SEQtype)))
	== (ARRSEQtype)NULL )
    {
      INT_ALLOC_ERR("createARRSEQ()");
      exit(1);
    }
  return(result);
}  /* end of createARRSEQ() */

