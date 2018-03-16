/*
** $Id: absparser.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* File: absparser.h	First Edit: 28.03.89	  Last Edit: 06.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 02.05.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#ifndef absparser_DEF
#define absparser_DEF

#include	"cmrlib.h"	/* for typedefinitons */

/***************************************************************************/
/* Exported errorcodes, variables and function:				   */
/***************************************************************************/

/* possible errorcodes:
#define	LR0_NOORDER	-41
#define	LR0_GRNOTBNF	-42
#define	LR0_PRODNOORDER	-43
#define	LR0_DEFTBLERR	-44
#define	LR0_NOSTART	-45
#define	LALR_AMBEPS	-46
#define	ISNOTLALR1	-49 */

extern	absparsertype	ABSPRS;	/* Global variable containing the abstract
				 * parser after computing it with
				 *		'cmrtl_compute_absparser()'
				 */
extern	ARRstatetype	AUTOM;	/* Global variable containing the state-
				 * tables after computing it with
				 *		'cmrtl_compute_absparser()'
				 */

/* With parameter 'opt' one can suppress what will be executed by
 * 'cmrtl_compute_absparser()':
 * Let be the i-th bit that one, which has the value (2 power (i-1)).
 * 1st til 3rd bit == 0: perform the complete construction of the abstract
 *			 parser.
 * 1st bit == 1: perform only the construction of the LR(0)-automaton.
 * 2nd bit == 1: perform the construction of the LALR(1)-automaton ( this
 *		 includes obviously the constr. of the LR(0)-aut.).
 * 3rd bit == 1: perform the construction of the LALR(1)-automaton and
 *		 the LALR(1)-analyze (modifications are possible now!).
 * 4th bit == 1: output of the state-tables of the LR(0)-automaton.
 * 5th bit == 1: output of the state-tables of the LALR(1)-automaton.
 * 6th bit == 1: output of the state-tables of the LALR(1)-automaton after.
 *		 the LALR(1)-analyze (modifications are possible now!).
 * 7th bit == 1: output of the abstract parser in an external ASCII-
 *		 representation defined by IDL.
 */

/* 'cmrtl_compute_absparser()' computes an abstract parser.
 * filename: "filename" concatenated with an extension yields the filenames
 *	     of possible outputs.
 * c	   : COMAR-datastructure of a grammar.
 * opt	   : as above defined
 * exe_purdom: algorithm of Purdom and Brown should be executed, if TRUE
 *
 * return == CMR_SUCCESS or one of the above errorcodes
 */
extern ERR cmrtl_compute_absparser(/*p_comar c;String filename;
					short opt; Boolean exe_purdom */);

#endif  /* of absparser_DEF */
