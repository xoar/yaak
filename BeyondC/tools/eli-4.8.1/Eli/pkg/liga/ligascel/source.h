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
/* $Id: source.h,v 4.2 1997/09/08 11:23:00 cogito Exp $ */


#ifndef SOURCE_H
#define SOURCE_H

extern char SourceName[];	/* to remember the name of the source file */
extern int LineNum;		/* in source file */
extern char *TokenEnd;		/* current pos in buffer, also marks tokenend */
extern char *TokenStart;	/* mark start of a token */
extern char *StartLine;		/* used to calculate column position */

#if defined(__cplusplus) || defined(__STDC__)

extern void initBuf(const char *infile, int f);
/* Initialize the source text module
 *   On entry-
 *     infile is the symbolic name of the input file
 *     f is the descriptor for the input file
 *     The input file has been opened successfully
 *   If the input file is empty then on exit-
 *     TokenEnd points to a NUL character
 *   Otherwise on exit-
 *     An integral number of lines of the input file, including their
 *       terminating newline characters, occupy successive character positions
 *       in memory starting with the location pointed to by TokenEnd.
 *     If the file contains no newline, one is supplied after the last
 *       character of the file.
 *     The character position after the terminating newline of the last
 *       line contains a NUL character
 ***/

extern void refillBuf(char *p);
/* Obtain additional information from the input file
 *   On entry-
 *     p addresses a NUL following the terminating newline of the last
 *       line currently in memory
 *   If there is no more information in the input file then on exit-
 *     TokenEnd points to a NUL character
 *   Otherwise on exit- 
 *     An integral number of lines of the input file, including their
 *       terminating newline characters, occupy successive character positions
 *       in memory starting with the location pointed to by TokenEnd.
 *     If the file contains no newline, one is supplied after the last
 *       character of the file.
 *     The character position after the terminating newline of the last
 *       line contains a NUL character 
 ***/

#else
extern void refillBuf();
extern void initBuf();
#endif

#endif
