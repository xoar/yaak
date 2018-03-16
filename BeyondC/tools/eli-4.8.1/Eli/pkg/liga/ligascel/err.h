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
/* $Id: err.h,v 4.2 1998/04/28 14:23:01 ludi Exp $ */
/* Copyright, 1989, The Regents of the University of Colorado */

#ifndef ERR_DEF
#define ERR_DEF

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

	/* Error report classification */

#define NOTE	0	/* Nonstandard construct */
#define COMMENT	1	/* Criticism of programming style */
#define WARNING	2	/* Possible error */
#define ERROR	3	/* Repairable error */
#define FATAL	4	/* Unrepairable error */
#define DEADLY	5	/* Compiler error */


	/* Types exported by the Error Module */

typedef struct {	/* Source listing coordinates */
	int line;	   /* Line number */
	int col;	   /* Character position */
} POSITION;


	/* Variables exported by the Error Module */

extern int ErrorCount[];
extern POSITION curpos;	/* Current source text position */


	/* Routines exported by the Error Module */

#if defined(__cplusplus) || defined(__STDC__) 
extern void ErrorInit(int ImmOut, int AGout, int ErrLimit);
#else
extern ErrorInit();
#endif 
/* Initialize the error module 
 *    On entry- 
 *       ImmOut=1 if immediate error output required 
 *       AGout=1 to print AG line number on error reports 
 *       ErrLimit=1 to limit the number of errors reported
 ***/



#if defined(__cplusplus) || defined(__STDC__)
extern void message(int severity, char *Msgtext, int grammar, POSITION *source);
#else
extern void message();
#endif
/* Report an error
 *    On entry-
 *      severity=error severity
 *      Msgtext=message text
 *      grammar=identification of the test that failed
 *      source=source coordinates at which the error was detected
 ***/

#endif
