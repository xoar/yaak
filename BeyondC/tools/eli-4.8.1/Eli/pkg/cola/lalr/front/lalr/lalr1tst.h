/*
** $Id: lalr1tst.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* File: lalr1tst.h	First Edit: 16.03.89	  Last Edit: 20.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 31.03.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#ifndef lalr1tst_DEF
#define lalr1tst_DEF

#include	"parserlib.h"	/* for typedefinitons */
#include	"cmrlib.h"

/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*					executing 'cmrtl_lalr1tst()'.      */
/***************************************************************************/

/* global variables defined in "cmrlib" */
extern	Indextype	MAXTERM;  /* init. by cmrlib_compute_globarrs() */
extern	ARRIndextype	INDEX;
extern	ARRdef_entry	DEFTBL;

/* 'CMR' will be used by 'cmrtl_lalr1tst()' but needn't be init. before */
extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */


/* global variable defined in "parserlib" */
extern	unsigned short	MAXSTATE;	/* number of states */


/* The following variables must NOT be initalized. */

/* global variables defined in "parserlib" */
extern	ARRSEQconflicttype	CONFLICTSTATES;
extern	Boolean			ISLALR1;
extern	SEQmodiftype		MODIFICATIONS;



/***************************************************************************/
/* Exported errorcode and function:					   */
/***************************************************************************/


/* possible errorcodes: ISNOTLALR1 */

/* return == CMR_SUCCESS, if automat represents a LALR(1)-automaton
 *	  == ISNOTLALR1	, otherwise
 * Note: if 'info', further information about conflict-states,if existing,
 *	 will be computed and stored in CONFLICTSTATES of "parserlib"
 */
extern ERR cmrtl_lalr1tst(/*p_comar c; ARRstatetype automat; Boolean info*/);

#endif  /* of lalr1tst_DEF */


