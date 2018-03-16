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

/* $Id: name.h,v 1.8 1997/08/29 08:38:08 mjung Exp $ */
/* This file defines, how modifications and connections are inserted
 * in the symbol-table of COMAR. Tools using them must be adjusted to
 * the EBNF-COMAR transformator, which is the first introducing them, to
 * avoid interface problems. Below are the definitons as used in the
 * LALR(1)-parsergenerator.
 */

#ifndef NAME_H
#define NAME_H

/* boolean property */
#define CONNECTION	"connect"	/* name and symbol-type of	*/
#define CONNECTTYPE	Kp_string	/* connections in COMAR		*/

/* properties with dval-value */
#define	REDUCE		"reducemod"	/* name and symbol-type of	 */
#define	REDUCETYPE	Kp_string	/* reduce-modifications in COMAR */

#define	NOREDUCE	"noreducemod"	/* name and symbol-type of	   */
#define	NOREDUCETYPE	Kp_string	/* noreduce-modifications in COMAR */

/* name and symbol-type of a default end-of-file symbol */
#define EOFSTRING	"EOF"
#define EOFTYPE		Kp_name

/* name of 'p_prop'-property to indicate the startproduction */
#define START   "_START"      /* Inserted as 'p_string' in symbol-table */

/* Inserted as 'p_string' in symbol-table REDUCED indicates that
 * the grammar is reduced.
 */
#define REDUCED "_REDUCED"

/* Inserted as 'p_string' in symbol-table TERMINALIZE indicates that
 * all nonterminals of the grammar can be terminalized.
 */
#define	TERMINALIZE	"_TERMINALIZE"

/* nval-value property associated with productions: value 1 indicates
 * that its productions is contained in the continuation grammar
 */
#define	ORDER	"_ORDER"

/* property names of the new pgs2cmr frontend */
/* boolean properties */
#define GRAMNAME "_GRAMNAME" /* Inserted as 'p_string' in symbol-table */
#define STOP	"_STOP"      /* Inserted as 'p_string' in symbol-table */
#define SEPA	"_SEPA"	      /* Inserted as 'p_string' in symbol-table */
#define BRACKET	"_BRACKET"      /* Inserted as 'p_string' in symbol-table */
#define	SKIP	"_SKIP"      /* Inserted as 'p_string' in symbol-table */

/* property with nval-value */
#define CODE	"_CODE"      /* Inserted as 'p_string' in symbol-table */

/* CONTINGENT and FORBIDDEN are names of OTHER-objects inserted by
 * cmrtl_purdom() in the definition-table and the right side of productions.
 * Don't insert connections into grammar-positions marked as FORBIDDEN
 * and avoid it in positions marked as CONTINGENT. The first one will
 * destroy the LALR(1)-property surely and the second one very often.
 */
#define CONTINGENT      "_CONTINGENT"
#define FORBIDDEN       "_FORBIDDEN"


/* For each nonterminal the First(1)-sets are stored as property "_FIRST1"
   with a list-value containing dvalues (dids of the terminals). The empty
   symbol is a p_term object (not contained in rules).
 */
#define	FIRST1	"_FIRST1"	/* Inserted as 'p_string' in symbol-table */

#endif









