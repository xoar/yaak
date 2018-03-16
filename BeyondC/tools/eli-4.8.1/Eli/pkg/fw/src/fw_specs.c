static char rcsid[] = "$Id: fw_specs.c,v 1.6 1997/08/30 17:57:45 waite Exp $";
/* Copyright 1991-1997, The Regents of the University of Colorado */

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

/***/
#if defined(__cplusplus) || defined(__STDC__)
int
main(int argc, char **argv)
#else
int
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
   char line[BUFSIZ], *p, *q, *r;

   if (argc != 3) {
      (void)fprintf(stderr, "Usage: %s cache fwName\n", argv[0]);
      exit(1);
   }

   while (fgets(line, BUFSIZ, stdin)) {
      p = line + strlen(line) - 1;
      if (!feof(stdin)) {
	if (*p != '\n') {
	  (void)fprintf(stderr, "%s: \"%s\" too long\n", argv[0], line);
	  exit(1);
	} else
	  *p = '\0';
      }
      if (*line == '#')
         continue;
      for (p = line; *p && (*p == ' ' || *p == '\t'); p++) ;
      for (q = p; *q; q++) if (*q != ' ' && *q != '\t') r = q;
      if (p == q) continue;
      r[1] = '\0';
      for (;(r != p) && (*r != '.'); r--);
      if (p[0] == '$' && p[1] == '/') (void)printf("%s%s\n", argv[1], p+1);
      else if (*p == '/' || *p == '$') (void)puts(p);
      else (void)printf("%s/%s\n", argv[2], p);
   }

   return 0;
}
