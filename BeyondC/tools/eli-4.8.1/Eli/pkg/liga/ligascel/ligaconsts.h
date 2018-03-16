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
/* $Id: ligaconsts.h,v 4.3 1999/07/08 16:49:52 uwe Exp $ */

/***********************************************************************\
*									*
*	File:		ligaconsts.h					*
*	Contents:	global constants to be used by all LIGA passes	*
*	Author:		Hans-Detlef Siewert				*
*	Creation date:	01 Mar 1991					*
*	Last change:	24 Sep 1991					*
*									*
\***********************************************************************/

#ifndef _ligaconsts_h
#define _ligaconsts_h

/*
** CONSTANTS
*/

/* symbol classes */
#define	SYMBNONT	(0)	/* nonterminal */
#define	SYMBTERM	(1)	/* terminal */

/* attribute classes */
#define	ATCLSYNT	(0)
#define	ATCLINH		(1)
#define	ATCLUNKN	(2)

/* predefined definition-ids */
#define	DIDNON		(0)
#define	FIRSTDID	(1)
#define	DIDVOID		(FIRSTDID)	/* VOID */
#define	DIDVOLI		(FIRSTDID+1)	/* VOID_LIST */
#define	DIDINT		(FIRSTDID+2)
#define	DIDBOOL		(FIRSTDID+3)
#define	DIDSYMB		(FIRSTDID+4)
#define	DIDCOORD	(FIRSTDID+5)
#define DIDNODE         (FIRSTDID+6)

/* names of predefined types */
#define	TNVOID		"VOID"
#define	TNINT		"int"
#define	TNCOORD		"POSITION"
#define TNNODE          "NODEPTR"
#define	TNBOOL		"$BOOL"
#define	TNSYMB		"$SYMB"
#define	TNVOLI		"$VOID_LIST"
			/* new meaning: attrs of this type need not
			   be computed in all contexts; should be
			   unified with rule attrs
			*/
#define TNBUMARK        "$BUMARK"
			/* used for a type def to indicate that backend
			   has to produce bottom-up visit-sequence code
			*/

/* values for fields of Attrdef structure */
	/* storeOfAttrdef */
#define	STORGLVA	(0)	/* store in global variable */
#define	STORGLST	(1)	/* store in global stack */
#define	STORTRAT	(2)	/* store in tree node */
#define	STORUNKN	(3)	/* unknown storage */

	/* genOfAttrdef */
#define	GENORIG		(0)	/* original attribute */
#define	GENINCL		(1)	/* generated while expanding INCLUDING */
#define	GENCONST	(2)	/* generated while expanding CONSTITUENT(S) */
#define	GENCHAIN	(3)	/* generated while expanding CHAIN */
#define	GENTERM         (4)	/* generated for storing terminals or coords */

/* special function names */
#define	ASSIGNFCT	"$ASSIGN"
#define	DEPFCT		"$DEP"
#define	ORDERFCT	"ORDER"
#define	IFFCT		"IF"
#define	VOIDFCT		"$VOID"
#define	WITHFCT		"$WITH"
#define IDFCT		"$ID"
#define BOTTOMUPFCT	"$BU"
#define SHIELDFCT	"$SHIELD"
#define LOOPFCT		"$LOOP"
#define INITCYCLEFCT	"$INITCYCLE"
#define CHARFCT         "$CHAR"
#define STRINGFCT       "$STRING"
#define FLOATFCT        "$FLOAT"
#define TERMFCT		"$TERM"
#define OLDTERMFCT	"$OLDTERM"
#define LINEACCFCT	"$LINEACC"
#define COLACCFCT	"$COLACC"
#define ADRFCT		"$ADR"

/* special attribute names */
#define GENTREEATTR	"GENTREE"

/* marks appended to the arguments of attr ASSIGNs: */
#define MULTMARK	"$MULTI"
			/* there may be several ASSIGNs to one attribute
			   in one context to add dependences;
			   at most one has a real computation
			*/

#endif

/***********************\
* end of ligaconsts.h	*
\***********************/

