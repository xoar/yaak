static char rcsid[] = "$Id: cpp_specs.c,v 2.6 2004/08/01 01:44:25 profw Exp $";
/* Copyright 1991, The Regents of the University of Colorado */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

/***/
int
#if defined(__cplusplus) || defined(__STDC__)
main(int argc, char **argv)
#else
main(argc,argv)
int argc; char **argv;
#endif
/* Creates a set of file names
 *    On entry-
 *       stdin=cpp-processed .specs file
 *    On exit-
 *       stdout=sequence of complete path names for specified files
 ***/
{
   char dir[BUFSIZ];

   if (argc != 3) {
      (void)fprintf(stderr, "Usage: %s specsdir cache\n", argv[0]);
      return 1;
   }

   *dir = '\0';
   initBuf("stdin", 0);
   while (*TEXTSTART) {
      register char *p;

      while (*TEXTSTART == ' ' || *TEXTSTART == '\t') TEXTSTART++;
      p = TEXTSTART;
      while (*TEXTSTART != '\n' && *TEXTSTART != '\r') TEXTSTART++;
      if (*TEXTSTART++ == '\r' && *TEXTSTART != '\n') TEXTSTART++;

      /* p points to the first significant character */
      if (*p != '\n' && *p != '\r' &&
         (*p != '#' || (p[2] >= '0' && p[2] <= '9'))) {
         register char *q;

         for (q = TEXTSTART - 2; *q == ' ' || *q == '\t'; q--) ;
   
         /* q points to the last significant character */
         q[1] = '\0';
         if (*p == '#') continue;
         while (q != p && *q != '.') q--;
         if (p[0] == '$' && p[1] == '/') (void)printf("%s%s\n", argv[2], p+1);
         else if (*p == '/' || *p == '$') (void)puts(p);
         else (void)printf("%s/%s\n", argv[1], p);
      }

      if (!*TEXTSTART) refillBuf(TEXTSTART);
   }

   return 0;
}
