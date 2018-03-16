/* $Id: symbinfo.h,v 1.1 2002/04/25 17:17:16 waite Exp $ */
/* Symbol information database interface */
/* Copyright (c) 1991, The Regents of the University of Colorado */

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

#if defined(__cplusplus) || defined(__STDC__)
extern void SymbolInfo(char *string, int external);
/* Obtain information about a single symbol
 *    On entry-
 *       string=character form of the symbol
 *       external=0 if the symbol is defined in the current file
 *                nonzero otherwise
 ***/


extern void AddFiles(char **obj, char **src);
/* Add symbol information to the data base
 *    On entry-
 *       obj=array of object file names, terminated by null
 *       src=array of source file names parallel to obj
 ***/


extern void OutFiles(char *symfile, int NoMain);
/* Output the source and object file names of the required programs
 *    On entry-
 *       symfile defines the symbols that must be satisfied
 *       NoMain is 1 if a main isn't being generated and we want to make
 *         sure to include everything from the innermost contour.  Otherwise
 *         only programs required by symfile are included.
 ***/


extern void SymbInit();
/* Initialize the symbol data base
 ***/
#else
extern void SymbolInfo();
extern void AddFiles();
extern void OutFiles();
extern void SymbInit();
#endif
