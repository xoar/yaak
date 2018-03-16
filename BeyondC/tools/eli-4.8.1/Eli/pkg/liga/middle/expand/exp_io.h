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
/* $Id: exp_io.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		exp_io.c					*
*	File:		exp_io.h					*
*	Contents:	input/output functions of the expand pass	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	12 Dec 1990					*
*	Last change:	04 Mar 1991					*
*									*
\***********************************************************************/

#ifndef	_EXP_IO_H_INCL
#define	_EXP_IO_H_INCL

/* * GLOBAL VARIABLES */

extern OptCollect expand_opts;
extern OptCollect optim_opts;
extern OptOption attrspez;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern void eval_exp_opt(void);
extern void OptionOut(OptCollect opts, FILE * optim_file);
#else
extern void eval_exp_opt();
extern void OptionOut();
#endif

#endif

/***********************\
* end of exp_io.h	*
\***********************/

/* HaDeS */
