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
/* $Id: expidl.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expidl.c					*
*	File:		expidl.h					*
*	Contents:	functions for the IDL data structures		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	18 Feb 1991					*
*	Last change:	24 Sep 1991					*
*									*
\***********************************************************************/

#define	LIST_SUFFIX	"list"

/* * GLOBAL VARIABLES */

extern AttrEval IdlStruct;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern int ith_symbol_of_prod(int index, int pid);
extern void
gen_assign(
	   Attribution attrib,
	   int row, int col,
	   int s1no, int a1did,
	   int s2no, int a2did,
	   int isvoid);
extern void gen_incl_attr(int sid, IncNode incptr);
extern void gen_chain_attr(int sid, char *name1, char *name2, int typeid);
extern void gen_constit_attr(int sid, ConstNode cptr);
extern int list_typeid(int tid, char **name);
extern int name_typeid(char *name);
#else
extern int ith_symbol_of_prod();
extern void gen_assign();
extern void gen_incl_attr();
extern void gen_chain_attr();
extern void gen_constit_attr();
extern int list_typeid();
extern int name_typeid();
#endif

/*****************\
* end of expidl.h *
\*****************/

/* HaDeS */
