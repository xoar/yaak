/*
** $Id: first1.h,v 1.2 1997/08/29 08:38:08 mjung Exp $
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
/* File: firstset.h	First Edit: 03.07.92	  Last Edit: 03.07.92      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/***************************************************************************/

#ifndef	first1_DEF
#define	first1_DEF

#include "bitset.h"	/* type BitSet */
#include "cmrlib.h"	/* type ERR */
#include "global.h"	/* type Boolean */

/***************************************************************************/
/* Exported errorcodes, types, variables and functions:			   */
/***************************************************************************/

/* possible errorcodes: */

typedef BitSet	*ARRBitSet;
typedef	Boolean	*ARRBoolean;

/* global exported variable for first-sets. */
extern	ARRBitSet	FIRSTSETS;	/* FIRSTSETS[0...MAXNTERM-1] */

/* (DEFAULT[A] == p)  <==> p is contained in continuation grammar */
extern	p_prod	*DEFAULT;	/* DEFAULT[0...MAXNTERM-1] */

/***************************************************************************/

#define	FIR_AND_DEF	0	/* DEFAULT and FIRSTSET will be computed */
#define	ONLY_FIR	1	/* Only FIRSTSET will be computed */
#define	ONLY_DEF	2	/* Only DEFAULT will be computed */

/* return == CMR_SUCCESS, the firstsets (and/or the continuation grammar)
 *			  are computed completely as needed for 
 *			  'readFIRSTSETS()' (and/or 'readDEFAULT()')
 *	  == errorcode,   otherwise
 * Note: if (filename != ""), the firstsets (and/or the continuation grammar)
 *	 are printed to file "filename"
 * c:    results will be stored in the COMAR data structure 'c'
 * version: one of the values FIR_AND_DEF, ONLY_FIR or ONLY_DEF
 */
ERR	cmrtl_first(/* p_comar c; String filename, int version */);

/* return == CMR_SUCCESS, the firstsets are printed completely
 *	  == errorcode,   otherwise
 * f:	for writing opened file
 * c:   COMAR datastructure with firstsets
 */
ERR	cmrtl_print_first(/* FILE *f, p_comar c */);

/* return == CMR_SUCCESS, the continuation grammar is printed completely
 *	  == errorcode,   otherwise
 * f:	for writing opened file
 * c:   COMAR datastructure with the continuation grammar
 */
ERR	cmrtl_print_default(/* FILE *f, p_comar c */);

/* readFIRSTSETS() transforms the first-sets of COMAR into the dynamic
 * array 'FIRSTSETS'.
 * Note: The first-set-computations must be performed with 'cmrtl_first()'
 * return == CMR_SUCCESS, if FIRSTSETS[MAXNTERM] is computed completely
 *	  == errorcode  , otherwise
 */
extern	ERR	readFIRSTSETS(/* p_comar c */);

/* freeFIRSTSETS() frees the storage of exported variable FIRSTSETS.
 * Should be used if and only if variable FIRSTSETS isn't any more used
 */
extern	void	freeFIRSTSETS();

/* readDEFAULT() initializes the dynamic array DEFAULT with the
 * corresponding information contained in the COMAR data structure 'c'.
 * Note: The default computation must be performed with 'cmrtl_first()'
 * return == CMR_SUCCESS, if DEFAULT[MAXPROD] is computed completely
 *	  == errorcode  , otherwise
 */
extern	ERR	readDEFAULT(/* p_comar c */);

/* freeDEFAULT() frees the storage of exported variable DEFAULT.
 * Should be used if and only if variable DEFAULT isn't used any more
 */
extern	void	freeDEFAULT();

#endif  /* of first1_DEF */
