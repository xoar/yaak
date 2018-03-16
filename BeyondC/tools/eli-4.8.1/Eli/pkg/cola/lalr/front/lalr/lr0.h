/*
** $Id: lr0.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* File: lr0.h		First Edit: 08.02.89	  Last Edit: 28.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	06.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#ifndef lr0_DEF
#define lr0_DEF


#include	"cmrlib.h"	/* for typedefinitons */


/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*				executing 'cmrtl_compute_LR0automat()' .   */
/***************************************************************************/

/* Global variables defined in "cmrlib" */

extern	Indextype	MAXNTERM;  /* init. by cmrlib_compute_globarrs() */
extern	Indextype	MAXPROD;
extern	ARRIndextype	INDEX;
extern	ARRdef_entry	DEFTBL;
extern	ARRSEQdef_entry	PRODWITHLHS;

/* 'CMR' will be used by 'cmrtl_compute_LR0automat()',
 * but needn't be init. before */
extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */


/* global variables defined in "parserlib" */
extern	unsigned short	MAXSTATE;  /* This variable will be computed by	*/
				   /* 	cmrtl_compute_LR0automat(). 	*/

/***************************************************************************/
/* Exported errorcodes and function:					   */
/***************************************************************************/


/* possible errorcodes: LR0_NOORDER, LR0_GRNOTBNF, LR0_PRODNOORDER,
 *	LR0_DEFTBLERR, LR0_NOSTART
 */

extern	ERR	cmrtl_compute_LR0automat(/* p_comar c,
					    String startname,
					    String ordername,
					    ARRstatetype *LR0autom,
					    p_prod *startprod
					*/);

#endif  /* of lr0_DEF */
