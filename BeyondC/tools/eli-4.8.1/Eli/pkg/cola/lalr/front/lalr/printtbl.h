/*
** $Id: printtbl.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
/* File: printtbl.h	First Edit: 21.03.89	  Last Edit: 28.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/***************************************************************************/

#ifndef printtbl_DEF
#define printtbl_DEF

/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*					executing 'printARRstate()' .	   */
/***************************************************************************/

/* global variables defined in "cmrlib" */
extern	SEQdef_entry	TERM_SEQ; /* initialized by cmrlib_arrangedefs() */

extern	Indextype	MAXTERM;  /* init. by cmrlib_compute_globarrs() */
extern	ARRIndextype	INDEX;
extern	ARRdef_entry	DEFTBL;

extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */

/* global variables defined in "parserlib" */
extern	unsigned short	MAXSTATE;  /* This variable will be computed by	*/
				   /* 	cmrtl_compute_LR0automat(). 	*/

/* These variables of "parserlib" needn't be computed. */
extern	ARRSEQconflicttype	CONFLICTSTATES;	/* These variables will be */
extern	Boolean			ISLALR1;	/* 	computed in 	   */
extern	SEQmodiftype		MODIFICATIONS;	/*    cmrtl_lalr1tst()	   */




/***************************************************************************/
/* Exported constant and function:					   */
/***************************************************************************/

/* optioncodes */
#define	AFTERLR0	1	/* Indicating LR(0)-Statetables */
#define	AFTERLALR	2	/* Indicating LALR(1)-Statetables */
#define	AFTERLTST	3	/* Indicating LALR(1)-Statetables */
				/*		after LALR(1)-TEST */
#define ONLY_CONFLICTS	4	/* as 'AFTERLTST' but printing only */
				/* conflict states 		*/

/* Don't choose too small! Let MAXROW >= 50 */
#define MAXROW	79	/* max. length of a row in the outputfile */

void	printARRstate(/* ARRstatetype X, FILE *f, short opt */);


#endif /* of printtbl_DEF */
