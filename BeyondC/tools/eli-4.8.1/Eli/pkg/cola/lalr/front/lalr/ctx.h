/*
** $Id: ctx.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
/* File: ctx.h		First Edit: 24.04.89	  Last Edit: 24.04.89      */
/*	 								   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 25.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/

/***************************************************************************/
/* The ctx-sets are used in "purdom.c" and "lalr.c". Therefore they are in */
/* an own module. For another programmer this module isn't interesting.    */
/* Note: There are not obvious dependencies with other modules.		   */
/***************************************************************************/



/* Typedefinitions of the data-structure representing the CTX-sets. */
  typedef struct ctx
    {
      Indextype		ntind;
      BitSet		set;
      struct ctx	*next;
    }  ctxtype;

typedef ctxtype		*SEQctxtype;
typedef SEQctxtype	*ARRSEQctxtype;


/* CTX is a dynamic array of SEQctxtype. Let ctx one element of CTX[X].
 * Then is: (ctx.ntind == Y  <==> X L* Y)  and (ctx.set == CTX(X,Y))
 */
extern	ARRSEQctxtype	CTX;


/* macros and functions for handling with 'SEQctx', where
 * (l: SEQctxtype, *el: ctxtype, result: SEQctxtype)
 */
#define initSEQctx()		((SEQctxtype)NULL)
#define emptySEQctx(l)		((l) == (SEQctxtype)NULL)
#define hdSEQctx(l)		(*l)	/* result: ctxtype */
#define tlSEQctx(l)		((l)->next)

extern	SEQctxtype	insSEQctx(/* SEQctxtype list; ctxtype *el */);
extern	ctxtype		*mkctx(/* Indextype ntind; BitSet set */);
extern	void		FreeARRSEQctx(/* ARRSEQctxtype arrctx */);


/* return == arr(A,B), if existing in array 'arr'
 *	  == (BitSet)NULL, if not existing in array 'arr'
 * ( for example: CTX(A,B) if called with CTX as 'arr' )
 */
extern	BitSet	GetValueSet(/* ARRSEQctxtype arrctx; Indextype A, B */);

/* 'ComputeCTX()' computes the CTX-sets in global variable 'CTX' */
extern	void	ComputeCTX(/* Indextype epsind */);
