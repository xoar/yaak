static char rcsid[]="$Id: err_tab.c,v 1.7 2007/02/21 15:10:00 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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

FILE *fopen();

static FILE *out;
static char OutFileName[BUFSIZ];

int
#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char **argv)
#else
main(argc,argv)
int argc; char *argv[];
#endif
{
   char FileLine[BUFSIZ];
   int FileLineNumber, NextLineNumber, IncludeFlag, Offset;
   FILE *f;

   if (argc != 3) {
      (void)fprintf(stderr, "Usage %s file output\n", argv[0]);
      return 1;
   }


   if ((f = fopen(argv[1], "r")) == NULL) {
           (void)fprintf(stderr, "Could not open input file %s\n", argv[1]);
           return 1;
        }

   if ((out = fopen(argv[2], "w")) == NULL) {
           (void)fprintf(stderr, "Could not open output file %s\n", argv[2]);
           return 1;
        }

   OutFileName[0] = '\0';

   FileLineNumber = 1;

   while (fgets(FileLine, BUFSIZ, f) != NULL) {
      if (FileLine[0] == '#') {
         IncludeFlag = 0;
         (void)sscanf(FileLine, "# %d \"%[^\"]\" %d",
            &NextLineNumber, OutFileName, &IncludeFlag);
	 Offset = -FileLineNumber + NextLineNumber -1;
	 (void)fprintf(out,"%d %d %s\n", FileLineNumber, Offset, OutFileName);
      }
      FileLineNumber++;
   }

   return 0;
}
