static char rcsid[]="$Id: map_errors.c,v 1.4 2007/02/21 15:10:00 profw Exp $";
/* Attribute error messages to the proper lines of component files */
/* Copyright 1990, The Regents of the University of Colorado */

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
#include <string.h>

FILE *fopen();

static FILE *xt;
static char FileName[BUFSIZ], NextFile[BUFSIZ];
static int Another, NextIncr, Limit, Increment;

/**/
void
NextBreak()
/* Advance to the next breakpoint
 * On entry-
 *    NextFile=File name from the next table line
 *    NextIncr=Increment from the next table line
 * On exit-
 *    FileName=Name of the file from which the next text was taken
 *    Increment=Line number correction
 *    If there is another breakpoint then
 *       Another != 0
 *       Limit=next breakpoint
 *       NextFile=next file name
 *       NextIncr=next line number correction
 *    else
 *       Another == 0
 **/
{
   (void)strcpy(FileName, NextFile); Increment = NextIncr;
   Another = (fscanf(xt, "%d %d %s\n", &Limit, &NextIncr, NextFile) != EOF);
}

int
main(argc,argv)
int argc; char *argv[];
{
   int c, ErrorLineNumber;

   if (argc != 2) {
      (void)fprintf(stderr, "Usage %s errtab\n", argv[0]);
      return 1;
   }

   if ((xt = fopen(argv[1], "r")) == NULL) {
      (void)fprintf(stderr, "Could not open table %s\n", argv[1]);
      return 1;
   }
   (void)strcpy(NextFile, "."); NextIncr = 0;
   NextBreak();

   while (scanf("%d", &ErrorLineNumber) != EOF) {
      while (Another && ErrorLineNumber >= Limit) NextBreak();
      (void)printf("%s %d", FileName, ErrorLineNumber + Increment);
      while ((c = getchar()) != EOF && c != '\n' && c != '\r') putchar(c);
      if (c == EOF) { putchar('\n'); break; }
      putchar(c);
      if (c == '\r') {
         if ((c = getchar()) == '\n') putchar('\n');
         else ungetc(c, stdin);
      }
   }
}
