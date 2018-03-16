/* $Id: prop.h,v 1.3 1997/08/28 17:29:32 waite Exp $ */
/* Property query and update module interface
   Copyright 1994, The Regents of the University of Colorado */

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

#define ProgramProp 1
#define SourceProp 2
#define ObjectProp 3
#define UsesProp 4
#define MemberProp 5


#define GetSource(x,y) GetFile(x,SourceProp,y)
#define SetSource(x,y) SetFile(x,SourceProp,y)
#define GetObject(x,y) GetFile(x,ObjectProp,y)
#define SetObject(x,y) SetFile(x,ObjectProp,y)

#if defined(__cplusplus) || defined(__STDC__)
extern int GetMember(DefTableKey key);
/* Query the member property
 *    If the member property is set then on exit-
 *       GetMember=1
 *    Else on exit-
 *       GetMember=0
 ***/


extern void SetMember(DefTableKey key);
/* Set the member property
 ***/


extern char * GetFile(DefTableKey key, int prop, char *dfltval);
/* Query the file property
 *    On exit-
 *       GetFile=source file containing this program
 ***/


extern void SetFile(DefTableKey key, int prop, char *add);
/* Update the file property
 *    On entry-
 *       add=source file containing this program
 ***/


extern int * GetUses(DefTableKey key, int *dfltval);
/* Query the uses property
 *    On exit-
 *       GetUses=identifiers used in this program
 ***/


extern void SetUses(DefTableKey key, int *add);
/* Update the uses property
 *    On entry-
 *       add=identifiers used in this program
 ***/


extern DefTableKey GetProgram(DefTableKey key, DefTableKey dfltval);
/* Query the program property of a symbol
 *    On exit-
 *       GetProgram=key for the program containing this symbol
 ***/


extern void SetProgram(DefTableKey key, DefTableKey add);
/* Update the program property of a symbol
 *    On entry-
 *       add=key for the program containing this symbol
 ***/
#else
extern int GetMember();
extern void SetMember();
extern char *GetFile();
extern void SetFile();
extern int * GetUses();
extern void SetUses();
extern DefTableKey GetProgram();
extern void SetProgram();
#endif
