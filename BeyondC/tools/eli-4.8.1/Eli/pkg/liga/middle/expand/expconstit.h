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
/* $Id: expconstit.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expconstit.c					*
*	File:		expconstit.h					*
*	Contents:	functions to expand CONSTITUENT and		*
*			CONSTITUENTS					*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	02 Apr 1991					*
*	Last change:	11 Apr 1991					*
*									*
\***********************************************************************/

#ifndef	_EXPCONSTIT_H_INCL
#define	_EXPCONSTIT_H_INCL

/* * GLOBAL VARIABLES */

extern ConstNode constituents;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern void find_constits(void);
extern void expand_constits(void);
#else
extern void find_constits();
extern void expand_constits();
#endif

#endif

/***********************\
* end of expconstit.h	*
\***********************/

/* HaDeS */
