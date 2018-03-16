static char rcsid[]="$Id: line_err.c,v 1.3 2013/11/08 22:03:21 profw Exp $";
/* Add line_err hooks to a file with standard error reporting */
/* Copyright, 2002, The Regents of the University of Colorado */

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

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main()
/* Add line_err hooks to a file with standard error reporting
 *   On entry-
 *      stdin is a text file with lines in the form: 
 *            seq file line column text
 *         seq=irrelevant integer
 *         file=Odin file name or "."
 *         line=Decimal line number or "0"
 *         column=Decimal column number or "0" 
 *         The file is sorted by (file line column)
 *   On exit-
 *      stdout is a text file with lines grouped by file as follows:
 *         . 0 0 text
 *         ...
 *         (|file1|line_err|file1 line1 column1 text1
 *         file1 line2 column2 text2
 *         ...
 *         file1 linen columnn textn
 *         |)
 *         ...
 ***/
{ char line[BUFSIZ], file[BUFSIZ];

  *file = '\0';
  while (fgets(line, BUFSIZ, stdin) != NULL) {
    char *p = strchr(line, '/');
    char *q = strchr(line, '.');

    if (!p || (q && q<p)) p = q;
    q = strchr(p, ' '); *q++ = '\0';

    if (strcmp(file, p) != 0) {
      if (strcmp(file, ".") != 0 && *file != '\0') puts("|)");
      strcpy(file, p);
      if (strcmp(file, ".") != 0) {
        char link[BUFSIZ];
        int length = readlink(file, link, BUFSIZ);
        if (length != -1) { link[length] = '\0'; strcpy(file, link); }
        else if (errno != EINVAL) { perror(p); exit(1); }
        printf("(|%s|line_err|", file);
      }
    }
    printf("%s %s", file, q);
  }
  if (strcmp(file, ".") != 0 && *file != '\0') puts("|)");

  return 0;
}
