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
/* $Id: expref.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expref.c					*
*	File:		expref.h					*
*	Contents:	function to handle the reference table		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	13 Dec 1990					*
*	Last change:	16 Apr 1991					*
*									*
\***********************************************************************/

#ifndef	_EXPREF_H_INCL
#define	_EXPREF_H_INCL

/* * MACROS */

/* shorthands for reference table access */
#define symbref(did)		(exp_ref_tab[did].entry.symb.symb_def)
#define	symbldown(did)		(exp_ref_tab[did].entry.symb.ldown)
#define	symbrdown(did)		(exp_ref_tab[did].entry.symb.rdown)
#define	symbflag(did)		(exp_ref_tab[did].entry.symb.flag)
#define	symbvisited(did)	(exp_ref_tab[did].entry.symb.visited)
#define	symbcompletechk(did)	(exp_ref_tab[did].entry.symb.completechk)
#define	symbprodvisited(did)	(exp_ref_tab[did].entry.symb.prodvisited)
#define prodref(did)		(exp_ref_tab[did].entry.prod.prod_def)
#define prodattrib(did)		(exp_ref_tab[did].entry.prod.attrib)
#define	prodright(did)		(exp_ref_tab[did].entry.prod.right)
#define	prodtrns(did)		(exp_ref_tab[did].entry.prod.trns)
#define	prodflag(did)		(exp_ref_tab[did].entry.prod.flag)

/* generate new did for new definitions */
#define	newdid()	(++max_did)

/* * GLOBAL VARIABLES */

extern struct RefEntry *exp_ref_tab;
extern int max_did;
extern int root_sid;

extern int DefSymbNum, DefRuleNum;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern void expand_init_ref_tab(void);
extern void expand_finl_ref_tab(void);
extern void find_root(void);
extern void clear_psflags(void);
#else
extern void expand_init_ref_tab();
extern void find_root();
extern void clear_psflags();
#endif

#endif

/***********************\
* end of expref.h	*
\***********************/

/* HaDeS */
