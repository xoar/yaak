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
/* $Id: linemap.h,v 4.1 1997/08/29 09:07:44 peter Exp $ */

#ifndef LINEMAP_H
#define LINEMAP_H
#include <stdio.h>

#if defined (__cplusplus) || defined(__STDC__)
extern void build_linemap(FILE *lm);
#else 
extern void build_linemap();
#endif

#if defined (__cplusplus) || defined(__STDC__)
extern int map_line(int line);
#else 
extern int map_line();
#endif

#if defined (__cplusplus) || defined(__STDC__)
extern char * map_file(int line);
#else 
extern int map_file();
#endif

#endif
