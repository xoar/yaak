static char rcsid[] = "$Id: symbinfo.c,v 1.17 2008/11/12 04:58:28 profw Exp $";
/* Symbol information database */
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

#include "deftbl.h"
#include "prop.h"
#include "envmod.h"
#include "obstack.h"
#include "rdsymb.h"
#include "idn.h"
#include "csm.h"
#include "symbinfo.h"

static Environment env;	/* Contour model for symbol definition */

static struct obstack UsedSym;	/* Symbols used in each program */
static int NoSymbol;		   /* (array terminated by NoSymbol) */

static DefTableKey *Programs;	/* Programs in most recent contour */
static struct obstack ProgStk;	   /* (array terminated by NoKey) */


static DefTableKey PgmKey;	/* Program currently being examined */

#ifdef DEBUG
void
#if defined(__cplusplus) || defined(__STDC__)
Log (DefTableKey pkey, char *symbstr)
#else
Log (pkey, symbstr)
DefTableKey pkey;
char *symbstr;
#endif
{
   printf ("file %s used due to: %s\n",
	   GetSource (pkey, "Missing file name"),
	   symbstr);
}
#endif

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
SymbolInfo(char *string, int external)
#else
SymbolInfo(string, external)
char *string; int external;
#endif
/* Obtain information about a single symbol
 *    On entry-
 *       string=character form of the symbol
 *       external=0 if the symbol is defined in the current file
 *                nonzero otherwise
 ***/
{
   int type = 1, Symbol;

#ifdef DEBUG
   printf("--- %s is %s\n", string, external == 0 ? "defined" : "external");
#endif
   mkidn(string, strlen(string), &type, &Symbol);

   if (external) obstack_grow(&UsedSym, &Symbol, sizeof(int));
   else SetProgram(DefineIdn(env, Symbol), PgmKey);
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
AddFiles(char **obj, char **src)
#else
AddFiles(obj, src)
char **obj, **src;
#endif
/* Add symbol information to the data base
 *    On entry-
 *       obj=array of object file names, terminated by null
 *       src=array of source file names parallel to obj
 ***/
{
   env = NewScope(env);
   obstack_free(&ProgStk, Programs);

   while (*obj) {
      PgmKey = NewKey();
      obstack_grow(&ProgStk, &PgmKey, sizeof(DefTableKey));
      SetSource(PgmKey,*src++);
      SetObject(PgmKey,*obj);
      read_symbols(*obj++);
      SetUses(PgmKey,(int *)obstack_copy(&UsedSym, &NoSymbol, sizeof(int)));
   }

   PgmKey = NoKey;
   Programs = (DefTableKey*)obstack_copy(&ProgStk,&PgmKey,sizeof(DefTableKey));
}


static FILE *source;	/* Source file names for required programs */
static FILE *object;	/* Object file names for required programs */

/**/
static void
#if defined(__cplusplus) || defined(__STDC__)
NeedProgram(DefTableKey pkey)
#else
NeedProgram(pkey)
DefTableKey pkey;
#endif
/* Make certain a program is in the set of required programs
 *    On entry-
 *       pkey=definition table key for the required program
 *    On exit-
 *       All programs defining symbols used in this program are in the set
 *          of required programs
 **/
{  char *obj;
   int *sym;

   if (GetMember(pkey)) return;
   SetMember(pkey);

   if ((obj = GetObject(pkey, "Missing file name")) != (char *)0) {
      (void)fprintf(source, "%s\n", GetSource(pkey, "Missing file name"));
      (void)fprintf(object, "%s\n", GetObject(pkey, obj));
   }

   if ((sym = GetUses(pkey, (int *)NULL)) == (int *)NULL) return;

   while (*sym != NoSymbol) {
      DefTableKey key = GetProgram(KeyInEnv(env, *sym), NoKey);

      if (key != NoKey) {
         NeedProgram(key);
#ifdef DEBUG
	 Log(key, StringTable(*sym));
#endif
     }
      sym++;
   }
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
OutFiles(char *symfile, int NoMain)
#else
OutFiles(symfile, NoMain)
char *symfile;
int NoMain;
#endif
/* Output the source and object file names of the required programs
 *    On entry-
 *       symfile defines the symbols that must be satisfied
 *       NoMain is 1 if a main isn't being generated and we want to make
 *         sure to include everything from the innermost contour.  Otherwise
 *         only programs required by symfile are included.
 ***/
{
   DefTableKey *p;

   if ((source = fopen("source", "w")) == NULL) {
      (void)fputs("Could not open file source\n", stderr);
      exit(1);
   }

   if ((object = fopen("object", "w")) == NULL) {
      (void)fputs("Could not open file object\n", stderr);
      exit(1);
   }

   PgmKey = NewKey();
   SetObject(PgmKey,(char *)0);
#ifdef DEBUG
   SetSource(PgmKey,"reqsyms");
#endif
   read_symbols(symfile);
   SetUses(PgmKey,(int *)obstack_copy(&UsedSym, &NoSymbol, sizeof(int)));
   NeedProgram(PgmKey);

   /* If NoMain is set, include all programs in the innermost contour */
   if (NoMain) {
     for (p = Programs; *p != NoKey; p++) {
       NeedProgram(*p);
#ifdef DEBUG
       Log(*p, "innermost contour");
#endif
     }
   }
}

/***/
void
SymbInit()
/* Initialize the symbol data base
 ***/
{
   env = NewEnv();
   obstack_init(&UsedSym);
   obstack_init(&ProgStk);
				/* Establish the Non-existent symbol */
   NoSymbol = stostr(" ", 1);
				/* Establish the invariant for Programs */
   PgmKey = NoKey;
   Programs = (DefTableKey*)obstack_copy(&ProgStk,&PgmKey,sizeof(DefTableKey));
}
