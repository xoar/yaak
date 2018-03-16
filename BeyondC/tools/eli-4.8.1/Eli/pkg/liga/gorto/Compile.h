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
/* $Id: Compile.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

#ifndef COMPILE_H
#define COMPILE_H

extern int sed, nbra;
extern char *loc1, *loc2, *locs;
extern int circf;

#if defined(__STDC__) || defined(__cplusplus) || defined(__TURBOC__)
char *compile(char *instring, register char *ep, char *endbuf, int seof);
int step(register char *p1, register char *p2);
int advance(char *lp, char *ep);

#else

char *compile();
int step();
int advance();

#endif

#endif

