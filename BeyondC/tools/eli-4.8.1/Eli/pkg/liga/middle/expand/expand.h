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
/* $Id: expand.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expand.c					*
*	File:		expand.h					*
*	Contents:	main function of expand pass			*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	12 Dec 1990					*
*	Last change:	17 Apr 1991					*
*									*
\***********************************************************************/

#ifndef _EXPAND_H_INCL
#define _EXPAND_H_INCL

/* * MACROS */
#include <stdio.h>

#define	protout	if (EXP_PROT) (void)fprintf

/* * GLOBAL VARIABLES */

extern FILE *InputFile;
extern FILE *OutputFile;
extern FILE *ProtocolFile;
extern FILE *ExpOptFile;
extern FILE *OptOutFile;

extern char *CONST_ATTR;
extern int EXP_PROT;
extern int EXP_INCL;
extern char *INCL_ATTR;
extern int IDENT_INCL;
extern char *CHAIN_PRE_ATTR;
extern char *CHAIN_POST_ATTR;

extern char *NULL_FUNC;
extern char *CREAT_FUNC;
extern char *CONCAT_FUNC;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern void deadly(char *msg);
extern void fatal(char *msg);
extern void print_err(int row, int col, char *str, int id);
extern void print_warn(int row, int col, char *str, int id);
extern void print_note(int row, int col, char *str);
#else
extern void deadly();
extern void fatal();
extern void print_err();
extern void print_warn();
extern void print_note();
#endif

#endif

/***********************\
* end of expand.h	*
\***********************/

/* HaDeS */
