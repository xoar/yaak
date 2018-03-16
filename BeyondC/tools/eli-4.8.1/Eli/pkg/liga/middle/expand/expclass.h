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
/* $Id: expclass.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expclass.c					*
*	File:		expclass.h					*
*	Contents:	functions to classify attributes		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	09 Jan 1991					*
*	Last change:	13 Mar 1991					*
*									*
\***********************************************************************/

#ifndef _EXPCLASS_H_INCL
#define _EXPCLASS_H_INCL

/* * MACROS */

/* * GLOBAL VARIABLES */

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern Attrdef get_symb_attr(int symbdid, int attr_did);
extern void set_attr_class(int symbdid, int attr_did, int newclass);
extern void calc_classes(void);
extern void set_term_classes(void);
extern void check_classes(void);
#else
extern Attrdef get_symb_attr();
extern void set_attr_class();
extern void calc_classes();
extern void set_term_classes();
extern void check_classes();
#endif

#endif

/***********************\
* end of expclass.h	*
\***********************/

/* HaDeS */
