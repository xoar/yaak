/*
** $Id: parserlib.h,v 1.5 1997/08/29 08:38:08 mjung Exp $
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
/* File: parserlib.h	First Edit: 08.02.89	  Last Edit: 21.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	13.07.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#ifndef parserlib_DEF
#define parserlib_DEF

#include "bitset.h" /* definition of BitSet */
#include "first1.h" /* definition of ARRBitSet */


/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*					executing functions of this file.  */
/***************************************************************************/

/* global variables defined in "cmrlib" */
extern	ARRdef_entry	DEFTBL;  /* init. by cmrlib_compute_globarrs() */
extern	p_comar	CMR;		 /* init. by cmrlib_changeglobalcmrvar() */

/* global variable defined in "first1.h", which must be initialized with
 * 'computeFIRSTSETS()' before you can use function 'FirstOfRhs()'
 */
extern	ARRBitSet	FIRSTSETS;


/***************************************************************************/
/* Exported constants, types, variables, macros and functions:		   */
/***************************************************************************/

#define Kred		0	/* tag number of a reduce-item */
#define Kshterm		1	/* tag number of a shiftterminal-item */
#define Kshnterm	2	/* tag number of a shiftnonterminal-item */

#define	SR		0	/* index of a dummy-state representing all
			 	 * shiftreduce-optimized states */
#define UNDEF		0	/* undefined value */


	    typedef struct set_type
	      {
		unsigned short	stateno;
		DID		ntermind;
		struct set_type	*next;
	      } settype;

	    typedef settype	*SEQsettype;


	typedef struct
	  {
	    unsigned short	tag;
	    DID			ruleno;
	    SEQunit		rulepos;
	  } commontype;

	typedef struct
	  {
	    commontype	common;
	    BitSet	erc;
	    SEQsettype	l_include;
	  } red_itemtype;

	typedef struct
	  {
	    commontype	common;
	  } shterm_itemtype;

	typedef struct
	  {
	    commontype	common;
	    BitSet	erc;
	    SEQsettype	e_include;
	  } shnterm_itemtype;

    typedef union
      {
        commontype	 common;
        red_itemtype	 red;
        shterm_itemtype	 shterm;
        shnterm_itemtype shnterm;
      } itemtype;

    typedef struct el_type
      {
	itemtype	item;
	struct el_type	*next;
      } elemtype;

    typedef elemtype	*SEQitemtype;


    
	/* staterule > 0  <==>  Shift-Action and staterule is index of
	 *			the next state
	 * staterule < 0  <==>  Shiftreduce-Action and staterule is a
	 *			CMR-index of a production
	 * staterule = 0  <==>  undefined
	 */
    typedef struct sh_type
      {
	DID		symbol; 
	short		staterule;
	struct sh_type	*next;
      } shifttype;

    typedef shifttype	*SEQshifttype;


typedef struct
  {
    SEQitemtype	 Kernel;
    SEQshifttype Goto;
    DID		 Errsymb;
  } statetype;

/* dynamic array with MAXSTATE+1 elements */
typedef	statetype	*ARRstatetype;	/* MAXTSTATE+1 elements */


extern	unsigned short	MAXSTATE;	/* number of states */


/**************************************************************************/


/* macros for handling with 'item', where
 * (it: itemtype, result: unsigned short)
 */
#define ruleposofitem(it)	(it.common.rulepos)
#define rulenoofitem(it)	(it.common.ruleno)
#define tagofitem(it)		(it.common.tag)



/* macros for handling with 'SEQitem', where
 * (l: SEQitemtype, *el: elemtype, result: SEQitemtype)
 */
#define initSEQitem()		((SEQitemtype)NULL)
#define emptySEQitem(l)		((l) == (SEQitemtype)NULL)
#define hdSEQitem(l)		((l)->item)	/* result: itemtype */
#define tlSEQitem(l)		((l)->next)

#define insbehindSEQitem(l,el)	/* instead of insbehindSEQitem(&l,el) */ \
		( emptySEQitem(l)?  (el->next = NULL, l=el) : \
				    (el->next = l->next, l->next = el) )


extern	elemtype       *mkelem(/*u_short tag;DID ruleno;SEQunit rulepos*/);
extern	commontype     *mkcommon(/*u_short tag;DID ruleno;SEQunit rulepos*/);
extern	SEQitemtype	delfirstSEQitem(/* SEQitemtype l */);
extern	SEQitemtype	rekdelSEQitem(/* SEQitemtype l */);
extern	SEQitemtype	insSEQitem(/* SEQitemtype l, itemtype *el */);
extern	SEQitemtype	insrearSEQitem(/* SEQitemtype l, itemtype *el */);
extern	SEQitemtype	copySEQitem(/* SEQitemtype l */);
extern	Boolean		isequalSEQitem(/* SEQitemtype l1, l2 */);
extern	unsigned short	lengthSEQitem(/* SEQitemtype l */);


/**************************************************************************/


/* macros for handling with 'SEQset', where
 * (l: SEQsettype, *el: settype, result: SEQsettype)
 */
#define initSEQset()		((SEQsettype)NULL)
#define emptySEQset(l)		((l) == (SEQsettype)NULL)
#define hdSEQset(l)		(*l)	/* result: shifttype */
#define tlSEQset(l)		((l)->next)

#define insbehindSEQset(l,el)	/* instead of insbehindSEQset(&l,el) */	\
		( emptySEQset(l)?  (el->next=NULL, l=el) : \
				   (el->next=l->next, l->next=el) )

extern	settype		*mkset(/* u_short stateind, DID ntdid */);
extern	SEQsettype	delfirstSEQset(/* SEQsettype l */);
extern	SEQsettype	rekdelSEQset(/* SEQsettype l */);
extern	SEQsettype	insSEQset(/* SEQsettype l, settype *el */);
extern	SEQsettype	copySEQset(/* SEQsettype l */);
extern	SEQsettype	mixSEQset(/* SEQsettype l1, l2 */);
extern	unsigned short	lengthSEQset(/* SEQsettype l */);


/**************************************************************************/


/* macros for handling with 'SEQshift', where
 * (l: SEQshifttype, *el: shifttype, result: SEQshifttype)
 */
#define initSEQshift()		((SEQshifttype)NULL)
#define emptySEQshift(l)	((l) == (SEQshifttype)NULL)
#define hdSEQshift(l)		(*l)	/* result: shifttype */
#define tlSEQshift(l)		((l)->next)

#define insbehindSEQshift(l,el)	/* instead of insbehindSEQshift(&l,el) */	\
		( emptySEQshift(l)?  (el->next=NULL, l=el) : \
				     (el->next=l->next, l->next=el) )


extern	shifttype	*mkshift(/* DID symb, short nextstate */);
extern	SEQshifttype	delfirstSEQshift(/* SEQshifttype l */);
extern	SEQshifttype	rekdelSEQshift(/* SEshiftQtype l */);
extern	SEQshifttype	insSEQshift(/* SEQshifttype l, shifttype *el */);
extern	unsigned short	lengthSEQshift(/* SEQshifttype l */);
extern	SEQshifttype	deltermSEQshift(/* SEQshifttype l; DID term; */);

/**************************************************************************/

  typedef struct conflict
    {
      Boolean	red_red;	/* TRUE  <==> reduce-reduce conflict
				 * FALSE <==> shift-reduce conflict  */
      BitSet	set;		/* conflict-set */
      DID	ruleno1;	/* Numbers of productions		*/
      DID	ruleno2;	/*	participating in the conflict	*/
      struct conflict *next;	/* for list-connection */
    }	conflicttype;

typedef conflicttype	*SEQconflicttype;
typedef SEQconflicttype	*ARRSEQconflicttype;

extern	ARRSEQconflicttype	CONFLICTSTATES;
extern	Boolean			ISLALR1;

/* macros for handling with 'SEQconflict', where
 * (l: SEQconflicttype, *el: conflicttype, result: SEQconflicttype)
 */
#define initSEQconflict()	((SEQconflicttype)NULL)
#define emptySEQconflict(l)	((l) == (SEQconflicttype)NULL)
#define hdSEQconflict(l)	(*l)	/* result: conflicttype */
#define tlSEQconflict(l)	((l)->next)

extern	conflicttype	*mkconflict(/* Bool isred;BitSet set;DID no1,no2 */);
extern	SEQconflicttype	insSEQconflict(/* SEQconflicttype l, el */);
extern	SEQconflicttype	rekdelSEQconflict(/* SEQconflicttype l */);


/**************************************************************************/

  typedef struct modif
    {
      Boolean		tag;
      DID		term;
      DID		ruleno;
      unsigned short	stateno;
      struct modif	*next;
    }	modiftype;

typedef	modiftype	*SEQmodiftype;

extern	SEQmodiftype	MODIFCATIONS;

/* macros for handling with 'SEQmodif', where
 * (l: SEQmodiftype, *el: modiftype, result: SEQmodiftype)
 */
#define initSEQmodif()		((SEQmodiftype)NULL)
#define emptySEQmodif(l)	((l) == (SEQmodiftype)NULL)
#define hdSEQmodif(l)		(*l)	/* result: modiftype */
#define tlSEQmodif(l)		((l)->next)

extern modiftype *mkmodif(/*Boolean tag; DID term,ruleno; u_short stateno*/);
extern	SEQmodiftype	insSEQmodif(/* SEQmodiftype l; modiftype *el */);
extern	SEQmodiftype	delfirstSEQmodif(/* SEQmodiftype l */);
extern	SEQmodiftype	rekdelSEQmodif(/* SEQmodiftype l */);


/**************************************************************************/

void	getfirstpos(/* SEQunit *rhsptr, u_short *tagptr */);

#define	getnextpos(r,t)	  if ( !emptySEQunit(*r) ) \
			    *r = tailSEQunit(*r); \
			  getfirstpos(r,t);

/* 'FirstOfRhs()' computes the First-Set of 'rhs' as a BitSet of terminals */
extern	BitSet	FirstOfRhs(/* Indextype epsind; SEQunit	rhs */);


/**************************************************************************/

typedef	char	*SEQtype;
typedef SEQtype	*ARRSEQtype;

/* 'createARRSEQ()' creates an array with 'number' elements of pointer-size,
 * usually used as sequences */
extern	ARRSEQtype	createARRSEQ(/* unsigned short number */);


#endif /* of parserlib_DEF */
