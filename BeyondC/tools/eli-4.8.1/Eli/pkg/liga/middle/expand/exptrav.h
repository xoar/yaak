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
/* $Id: exptrav.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		exptrav.c					*
*	File:		exptrav.h					*
*	Contents:	functions to travel through attainable graph	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	20 Mar 1991					*
*	Last change:	25 Sep 1991					*
*									*
\***********************************************************************/

#ifndef _EXPTRAV_H_INCL
#define _EXPTRAV_H_INCL

/* * GLOBAL VARIABLES */

extern int inclcount;
extern int constscount;
extern int markedsymbs;
extern int markedprods;
extern int newattrs;
extern char *newattrname;

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
extern int incl_in_call(Call call, int pid, int dep);
extern void mark_incl_trans(int sid, IncNode incptr);
extern void chain_in_call(Call call, int pid);
extern void
mark_chain_trans(
		 int sid, ChainNode ch, ChAccNode chacc, int pid, int first);
extern int constits_in_call(Call call, int pid, int dep);
extern int mark_constit_trans(int sid, ConstNode cptr);
#else
extern int incl_in_call();
extern void mark_incl_trans();
extern void chain_in_call();
extern void mark_chain_trans();
extern int constits_in_call();
extern int mark_constit_trans();
#endif

#endif

/***********************\
* end of expchain.h	*
\***********************/

/* HaDeS */
