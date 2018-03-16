static char rcsid[] = "$Id: prop.c,v 1.5 1997/08/28 17:29:31 waite Exp $";
/* Property query and update module
   Copyright 1994, Th Regents of the University of Colorado */

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

#include "deftbl.h"
#include "prop.h"

/***/
int
#if defined(__cplusplus) || defined(__STDC__)
GetMember(DefTableKey key)
#else
GetMember(key)
DefTableKey key;
#endif
/* Query the member property
 *    If the member property is set then on exit-
 *       GetMember=1
 *    Else on exit-
 *       GetMember=0
 ***/
{
   Entry r;

   return (find(key,MemberProp,&r,0));
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
SetMember(DefTableKey key)
#else
SetMember(key)
DefTableKey key;
#endif
/* Set the member property
 ***/
{
   Entry r;

   if (key != NoKey) (void)find(key,MemberProp,&r,sizeof(struct PropElt));
}


typedef struct {		/* Properties of a defined entity */
   struct PropElt *next;	   /* The next property */
   int selector;		   /* Which property */
   char *PropVal;		   /* Property value */
} StringElt;

/***/
char *
#if defined(__cplusplus) || defined(__STDC__)
GetFile(DefTableKey key, int prop, char *dfltval)
#else
GetFile(key, prop, dfltval)
DefTableKey key; int prop; char *dfltval;
#endif
/* Query the file property
 *    On exit-
 *       GetFile=source file containing this program
 ***/
{
   Entry r;

   if (find(key,prop,&r,0)) return ((StringElt *)r)->PropVal;
   return dfltval;
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
SetFile(DefTableKey key, int prop, char *add)
#else
SetFile(key, prop, add)
DefTableKey key; int prop; char *add;
#endif
/* Update the file property
 *    On entry-
 *       add=source file containing this program
 ***/
{
   Entry r;

   if (key == NoKey) return;
   if (!find(key,prop,&r,sizeof(StringElt)))
      ((StringElt *)r)->PropVal = add;
}


typedef struct {		/* Properties of a defined entity */
   struct PropElt *next;	   /* The next property */
   int selector;		   /* Which property */
   int *PropVal;		   /* Property value */
} UsesElt;

/***/
int *
#if defined(__cplusplus) || defined(__STDC__)
GetUses(DefTableKey key, int *dfltval)
#else
GetUses(key, dfltval)
DefTableKey key; int *dfltval;
#endif
/* Query the uses property
 *    On exit-
 *       GetUses=identifiers used in this program
 ***/
{
   Entry r;

   if (find(key,UsesProp,&r,0)) return ((UsesElt *)r)->PropVal;
   return dfltval;
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
SetUses(DefTableKey key, int *add)
#else
SetUses(key, add)
DefTableKey key; int *add;
#endif
/* Update the uses property
 *    On entry-
 *       add=identifiers used in this program
 ***/
{
   Entry r;

   if (key == NoKey) return;
   (void)find(key,UsesProp,&r,sizeof(UsesElt));
   ((UsesElt *)r)->PropVal = add;
}


typedef struct {		/* Properties of a defined entity */
   struct PropElt *next;	   /* The next property */
   int selector;		   /* Which property */
   DefTableKey PropVal;		   /* Property value */
} DefTableElt;

/***/
DefTableKey
#if defined(__cplusplus) || defined(__STDC__)
GetProgram(DefTableKey key, DefTableKey dfltval)
#else
GetProgram(key, dfltval)
DefTableKey key; DefTableKey dfltval;
#endif
/* Query the program property of a symbol
 *    On exit-
 *       GetProgram=key for the program containing this symbol
 ***/
{
   Entry r;

   if (find(key,ProgramProp,&r,0)) return ((DefTableElt *)r)->PropVal;
   return dfltval;
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
SetProgram(DefTableKey key, DefTableKey add)
#else
SetProgram(key, add)
DefTableKey key, add;
#endif
/* Update the program property of a symbol
 *    On entry-
 *       add=key for the program containing this symbol
 ***/
{
   Entry r;

   if (key == NoKey) return;
   if (!find(key, ProgramProp, &r, sizeof(DefTableElt))) 
      ((DefTableElt *)r)->PropVal = add;
}
