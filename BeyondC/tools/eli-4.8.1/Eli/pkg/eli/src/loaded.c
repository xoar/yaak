static char rcsid[] = "$Id: loaded.c,v 1.19 2004/08/01 01:44:25 profw Exp $";
/* Print names of files necessary to resolve undefined references
   Copyright 1991, The Regents of the University of Colorado */

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

/* read_symbols is based on code from Jim Larus' AE */

#include <stdio.h>
#include "symbinfo.h"
#include "obstack.h"
#include "err.h"

static struct obstack text;	/* Character forms of the file names */
static struct obstack files;	/* Pointers to file names on the current contour */

/**/
static char **
#if defined(__cplusplus) || defined(__STDC__)
GetFiles(char *list)
#else
GetFiles(list)
char *list;
#endif
/* Get a list of files
 *    On entry-
 *       list=name of the file containing the list of files
 *    On exit-
 *       GetFiles points to an array of the file names
 **/
{
   char *empty = NULL;
   int c;
   FILE *f;

   if ((f = fopen(list, "r")) == (FILE *)NULL) {
      (void)fprintf(stderr, "loaded: Could not open file %s for reading\n",
		    list);
      exit(1);
   }

   while ((c = getc(f)) != EOF) {
      if (c != '\n' && c != '\r') obstack_1grow(&text, c);
      else {
         char *name;

         obstack_1grow(&text, 0); name = (char *)obstack_finish(&text);
         obstack_grow(&files, &name, sizeof(char *));

         if (c == '\r') {
            if ((c = getc(f)) != '\n') ungetc(c, f);
         }
      }
   }

   return (char **)obstack_copy(&files, &empty, sizeof(char *));
}

int
#if defined(__cplusplus) || defined(__STDC__)
main(int argc, char *argv[])
#else
main (argc, argv)
int argc; char *argv[];
#endif
{
	int i, NoMain;

	/* check args */
	if (argc < 4) {
		(void)fprintf (stderr, "usage: %s [-n] symbols obj src [obj src]...\n",
			argv[0]);
		return 1;
	}

	ErrorInit(1,0,0);
	SymbInit();
	obstack_init(&files); obstack_init(&text);

        if (strcmp(argv[1], "-n") == 0) {
          NoMain = 1;
          i = 3;
        } else {
          NoMain = 0;
          i = 2;
        }

	for ( ; i < argc; i += 2) {
		char **objfile, **srcfile;

		objfile = GetFiles(argv[i]); srcfile = GetFiles(argv[i+1]);
		AddFiles(objfile, srcfile);
		obstack_free(&files, objfile);
	}

        if (NoMain)
	  OutFiles(argv[2], 1);
        else
          OutFiles(argv[1], 0);

	return 0;
}
