/*
** $Id: lr0forpurdom.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
/* File: lr0forpurdom.h	First Edit: 19.04.89	  Last Edit: 24.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	??.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/

/* This file is only written for "purdom.c" to export 
 * macros, variables and functions also used by "purdom.c".
 * They are very special and not of global interest.
 */

/* global variables */
extern	unsigned short	*ADDED;		/* dynamic boolean array indexed by
				 	 * nonterminals  */
extern	Indextype	*ADDEDSTACK;	/* stack of indices i with
					 * ADDED[i] == TRUE */
extern	Indextype	TOP;		/* auxiliary to stack ADDEDSTACK */

extern	unsigned short	MAXITEMNO;	/* maximum number of items in a
					 * state: main it. + derived it. */


/********** macro- and function-declarations **********/

/* routines for ADDED and ADDEDSTACK */
#define	topadded()	(ADDEDSTACK[TOP])
#define pushadded(el)	(ADDEDSTACK[++TOP] = el)
#define popadded()	(--TOP)
#define emptyadded()	(!TOP)

extern	void	createadded(/*  */);
extern	void	freeadded(/*  */);

