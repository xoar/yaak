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
/* $Id: expincl.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expincl.c					*
*	File:		expincl.h					*
*	Contents:	functions to expand the INCLUDING construct	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	07 Feb 1991					*
*	Last change:	11 Apr 1991					*
*									*
\***********************************************************************/

#ifndef _EXPINCL_H_INCL
#define _EXPINCL_H_INCL

/* * MACROS */

/* * GLOBAL VARIABLES */

extern IncNode includings;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern void find_includings(void);
extern void expand_includings(void);
#else
extern void find_includings();
extern void expand_includings();
#endif

#endif

/***********************\
* end of expincl.h	*
\***********************/

/* HaDeS */
