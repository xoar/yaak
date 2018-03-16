/*
** $Id: lalr.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* File: lalr.h		First Edit: 27.02.89	  Last Edit: 17.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 31.03.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#ifndef lalr_DEF
#define lalr_DEF

#include	"first1.h"	/* for typedefinitons */
#include	"cmrlib.h"
#include	"bitset.h"
#include	"privatlib.h"	/* for error codes */

/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*				executing 'cmrtl_compute_LALR1()' .        */
/***************************************************************************/


/* global variables defined in "cmrlib" */
extern	SEQdef_entry	NTERM_SEQ; /* initialized by cmrlib_arrangedefs() */
extern	SEQdef_entry	PROD_SEQ;

extern	Indextype	MAXNTERM;  /* init. by cmrlib_compute_globarrs() */
extern	Indextype	MAXTERM;
extern	ARRIndextype	INDEX;
extern	ARRSEQdef_entry	PRODWITHLHS;

/* 'CMR' will be used by cmrtl_compute_LALR1() but needn't be init. before */
extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */


/* global variable defined in "first1" */
extern	ARRBitSet	FIRSTSETS;	/* FIRSTSETS need not be computed */


/***************************************************************************/
/* Exported errorcode and function:					   */
/***************************************************************************/

/* possible errorcodes: LALR_AMBEPS */

extern	ERR	cmrtl_compute_LALR1(/* p_comar c; ARRstatetype automat */);

#endif  /* of lalr_DEF */

