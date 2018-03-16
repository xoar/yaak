/*
** $Id: grammarcomp.h,v 1.6 1997/08/29 08:38:08 mjung Exp $
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
/* File: grammarcomp.h	First Edit: 18.11.88	  Last Edit: 17.02.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	10.08.89 from Kalle					   */
/***************************************************************************/

#ifndef	grammarcomp_DEF
#define	grammarcomp_DEF


/***************************************************************************/
/* Imported variables, which MUST(!) be initialized before executing	   */
/*		   the exported functions except 'cmrtl_grammar_comp()'.   */
/***************************************************************************/

/* Global variables defined in "cmrlib" */

extern	SEQdef_entry	TERM_SEQ; /* initialized by cmrlib_arrangedefs() */
extern	SEQdef_entry	NTERM_SEQ;
extern	SEQdef_entry	OTHER_SEQ;
extern	SEQdef_entry	PROD_SEQ;

/* The following variables are not used by 'cmrtl_compute_startprod()' */
extern	Indextype	MAXNTERM;  /* init. by cmrlib_compute_globarrs() */
extern	ARRIndextype	INDEX;
extern	ARRSEQdef_entry	PRODWITHLHS;
extern	ARRdef_entry	DEFTBL;

/* 'CMR' will be used by all follow. functions but needn't be init. before */
extern	p_comar	CMR;		  /* init. by cmrlib_changeglobalcmrvar() */


/***************************************************************************/
/* Exported headlines, errorcodes and functions:			   */
/***************************************************************************/

#define CMR_HEADLINE_ALL	"GRAMMAR IS AUGMENTED, REDUCED AND ORDERED"
#define CMR_HEADLINE_ST		"GRAMMAR IS AUGMENTED"
#define CMR_HEADLINE_RED	"GRAMMAR IS AUGMENTED AND REDUCED"
#define CMR_HEADLINE_ORD	"GRAMMAR HAS A PARTITIAL RULEORDER"
#define CMR_HEADLINE_ORDST	"GRAMMAR IS AUGMENTED AND ORDERED"

extern	p_prod	STARTPROD; /* Computed of cmrtl_grammar_comp(c,TRUE,X,Y) */


/* SECTION 1 */

/* possible errorcodes:
 *	ST_NOSTSYM, ST_AMBSTSYM, ST_AMBSTPROD, ST_NOTBNFSTPROD, ST_EOFNOTERM,
 *	ST_AMBEOF, ST_EOFERR
 */

/* 'cmrtl_compute_startprod()' computes the startproduction of the grammar
 * encoded in COMAR-structure 'c':
 * 	*startprod: the computed startproduction, except if
 *		    return == ( ST_NOSTSYM || ST_AMBSTSYM || ST_AMBSTPROD )
 * return == CMR_SUCCESS, if 'c' contains a correct startproduction
 *        == one of the above errorcodes, otherwise
 */
extern	ERR	cmrtl_compute_startprod(/* p_comar c, p_prod *startprod */);


/* SECTION 2 */

/* possible errorcodes: GR_NOTREACH */

/* 'cmrtl_reachibility()' checks whether all nonterminals are reachable
 * in a derivation from startsymbol with index 'startdid':
 * return == CMR_SUCCESS , if check yields a positiv answer
 * 	  == GR_NOTREACH , otherwise
 * Output of the unreachable nonterminals on stderr!
 */
extern	ERR	cmrtl_reachibility(/* p_comar c, DID startdid */);


/* SECTION 3 */

/* possible errorcodes: GR_NOTBNF, GR_NODEFAULT, GR_NTHASNOPROD, GR_ORDER_EXIST
 */

extern	ERR	cmrtl_partitial_ruleorder(/* p_comar c */);


#endif		/* of grammarcomp_DEF */


/* SECTION 4 */

/* possible errorcodes: GR_NOTREDUCED and all of the above functions */

/* Note:
 *  'cmrtl_grammar_comp()' initializes itself the above imported variables.
 *
 *  if ( start ):	'cmrtl_compute_startprod()' will be executed.
 *  if ( reach ):	'cmrtl_reachibility()' and
 *			'cmrtl_default_for_grammar()' will be executed.
 *  if ( order ):	'cmrtl_partitial_ruleorder()' will be executed.
 *
 *  return == if error, one of all above or in "default.h" errorcodes
 *	      oterwise, CMR_SUCCESS
 */
extern	ERR	cmrtl_grammar_comp(/*p_comar c; Boolean start, reach, order;*/);
