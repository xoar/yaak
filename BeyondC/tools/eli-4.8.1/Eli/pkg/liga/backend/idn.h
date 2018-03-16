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
#ifndef IDN_H
#define IDN_H
/* $Id: idn.h,v 4.1 1997/08/29 07:54:24 peter Exp $ */
/* Copyright 1989, The Regents of the University of Colorado
 * Permission is granted to use any portion of this file for any purpose,
 * commercial or otherwise, provided that this notice remains unchanged.
 */

	/* Type exported by the Identifier Table Module */

typedef int INTERNIDN;
#define NoIdn 0


#ifndef NOFOLD
	/* Variable exported by the Identifier Table Module */

extern int dofold;
#endif


	/* Routines exported by the Identifier Table Module */

#if defined(__cplusplus) || defined(__STDC__)
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
extern void prtidnv(FILE *d, int i);
#else
extern void prtidnv(/* FILE *d; int i; */);
#endif
/* Print an identifier
 *    On exit-
 *       The identifier encoded by i has been added to the current
 *          line of d.
 ***/


#if defined(__cplusplus) || defined(__STDC__)
extern void saveidn(FILE *d);
#else
extern void saveidn(/* FILE *d; */);
#endif
/* Save the current identifier table state
 *    On exit-
 *       File d is a symbolic encoding of the current state, suitable
 *          for inclusion in the identifier table module
 ***/


#if defined(__cplusplus) || defined(__STDC__)
extern void dmpidn(FILE *d);
#else
extern void dmpidn(/* FILE *d; */);
#endif
/* Dump the identifier table
 *    On exit-
 *       The entire identifier table has been written to d
 ***/


#if defined(__cplusplus) || defined(__STDC__)
extern void mkidn(char *c, int l, int *t, int *s);
#else
extern void mkidn(/* char *c; int l, *t; int *s; */);
#endif
/* Obtain the internal coding of an identifier or keyword
 *    On entry-
 *       c points to the identifier or keyword
 *       l=length of the identifier or keyword
 *       t points to a location containing the initial terminal code
 *    If the identifier or keyword has appeared previously then on exit-
 *       t has been set to the terminal code given on its first appearance
 *       s has been set to the internal coding set on its first appearance
 *    Otherwise on exit-
 *       t remains unchanged
 *       s has been set to a new internal coding
 ***/

#endif
