/*
** $Id: purdom.h,v 1.5 1997/08/29 08:38:08 mjung Exp $
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
/* File: purdom.h	First Edit: 19.04.89	  Last Edit: 26.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: ??.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#ifndef purdom_DEF
#define purdom_DEF

/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before 		   */
/*					executing 'cmrtl_purdom()'.        */
/***************************************************************************/


/* global variables defined in "cmrlib" */
extern	SEQdef_entry	PROD_SEQ; /* initialized by cmrlib_arrangedefs() */

extern	Indextype	MAXTERM;  /* init. by cmrlib_compute_globarrs() */
extern	Indextype	MAXPROD;
extern	ARRIndextype	INDEX;
extern	ARRSEQdef_entry	PRODWITHLHS;
extern	ARRdef_entry	DEFTBL;

extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */

/* global variable defined in "lr0" */
extern	unsigned short	MAXSTATE;  /* init. by cmrtl_compute_LR0automat() */
extern	unsigned short	MAXITEMNO;

/* global variable defined in "first1" */
extern	ARRBitSet	FIRSTSETS;	/* init. by computeFIRSTSETS() */


/***************************************************************************/
/* Exported errorcode and function:					   */
/***************************************************************************/

/* CONTINGENT and FORBIDDEN are names of OTHER-objects inserted by
 * cmrtl_purdom() in the definition-table and the right side of productions.
 * Don't insert connections into grammar-positions marked as FORBIDDEN
 * and avoid it in positions marked as CONTINGENT. The first one will
 * destroy the LALR(1)-property surely and the second one very often.
 */
#ifndef CONTINGENT
#define	CONTINGENT	"_CONTINGENT"
#define	FORBIDDEN	"_FORBIDDEN"
#endif

/* possible error codes: LALR_AMBEPS */
extern	ERR	cmrtl_purdom(/* p_comar c; ARRstatetype autom */);

#endif  /* of purdom_DEF */

