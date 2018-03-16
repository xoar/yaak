static char RCSid[] = "$Id: cat-n.c,v 1.6 2013/11/08 22:11:45 profw Exp $";
/* Implementation of cat -n */
/* Copyright 1992, The Regents of the University of Colorado */

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

/***/
int
main()
/* Attach a sequence number to each line of a file
 *    On entry-
 *       stdin is a text file with each line having the form:
 *             data\n
 *    On exit-
 *       stdout is a text file with each line having the form:
 *             seq\tdata\n
 *          seq is the integer sequence number of the line
 *          data is unchanged from stdin
 ***/
{
  int c;
  int seq = 1;

  while ((c = getchar()) != EOF) {
    (void)printf("%d\t", seq++);
    while ((c != EOF) && (c != '\n') && (c != '\r')) {
         (void)putchar(c); 
         c = getchar(); 
    } 
    if (c == '\n') (void)putchar('\n');
    else if (c == '\r') {
      (void)putchar('\r');
      if ((c = getchar()) == '\n') (void)putchar('\n');
      else ungetc(c, stdin);
    }
  }

  return 0;
}
