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
/* $Id: expconst.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expconst.h					*
*	File:		expconst.h					*
*	Contents:	global constants for all modules of expand	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	08 Jan 1991					*
*	Last change:	03 Jul 1991					*
*									*
\***********************************************************************/

#ifndef _EXPCONST_H_INCL
#define _EXPCONST_H_INCL

/* * CONSTANTS */

/* error ids - these are given in error messages to identify error class */
#define	NO_ERRID	(0)
/* no specific error, internal or otherwise */
#define	ROOT_ERRID	(0)
/* error while searching for the root symbol of the grammar */
#define	ATCL_ERRID	(0)
/* error in attribute classification */
#define	ASGN_ERRID	(0)
/* error in assignment */
#define	TFCL_ERRID	(0)
/* error in TRANSFER classes */
#define	TFEX_ERRID	(0)
/* conflict between explicit assignment and TRANSFER rule */
#define	TFMS_ERRID	(0)
/* multiple attributes for TRANSFER of synthesized attributes */
#define TF_ERRID	(0)
/* error in transfer rule */
#define	INRT_ERRID	(0)
/* INCLUDING construct found in root production */
#define	NAII_ERRID	(0)
/* no attributes in INCLUDING construct */
#define	TSIN_ERRID	(0)
/* terminal attribute in INCLUDING construct */
#define	IMSO_ERRID	(0)
/* symbol occured more than once in list of INCLUDING attributes */
#define	ITYP_ERRID	(0)
/* type conflict in list of INCLUDING attributes */
#define	OPIN_ERRID	(0)
/* open INCLUDING construct, root marked as transfer symbol */
#define	NISC_ERRID	(0)
/* no source context for attribute to be included */
#define	CHST_ERRID	(0)
/* error in CHAINSTART */
#define	CHACC_ERRID	(0)
/* no accesses to CHAIN */
#define	CHDEF_ERRID	(0)
/* no definitions of CHAIN */
#define	CHTS_ERRID	(0)
/* chain leads through or starts at a terminal symbol */
#define	OPCH_ERRID	(0)
/* open CHAIN, root marked as chain symbol */
#define	CONR_ERRID	(0)
/* no CONSTITUENT symbol found in subtree */
#define	COML_ERRID	(0)
/* multiple CONSTITUENT symbols found in subtree */
#define	NAIC_ERRID	(0)
/* no attributes in CONSTITUENT(S) construct */
#define	CMSO_ERRID	(0)
/* symbol occured more than once in list of CONSTITUENT attributes */
#define	CTYP_ERRID	(0)
/* type conflict in list of CONSTITUENT(S) attributes */

/* warning ids - these are given in warning to identify warning class */
#define	CHUSE_WARNID	(0)
/* no use is made of a defined chain */
#define	CHNU_WARNID	(0)
/* no use access was found for a chain */
#define	CONS_WARNID	(0)
/* no CONSTITUENTS symbols found in subtree, list is always empty */

/* flags for productions */
#define	no_pflag	(0)
#define	start_prod	(1)
#define	trans_prod	(2)
#define	target_prod	(4)

/* flags for symbols */
#define	no_sflag	(0)
#define	chainstart_symb	(1)
#define	chain_symb	(2)
#define	trnsp_symb	(4)
#define src_symb	(1)
#define shield_symb	(2)

#endif

/***********************\
* end of expconst.h	*
\***********************/

/* HaDeS */
