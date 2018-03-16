static char RCSid[] = "$Id: mk_include.c,v 1.6 2013/11/11 03:11:22 profw Exp $";
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
#include <stdlib.h>
#include <string.h>


int
main(argc, argv)
int argc; char *argv[];
/* Merge file names with their Odin keys
 *    On entry-
 *       argv[1]=name of the file containing the file names
 *       argv[2]=name of the file containing the Odin keys
 *       argv[3]=name of the output file
 *    On exit
 *       Each line of the output file has the form
 *          name@key
 */
{
   char FileName[BUFSIZ];
   FILE *namefile, *keyfile, *mergefile;

   if (argc < 4) {
      (void)fprintf(stderr,
         "mk_include: Usage %s namefile keyfile mergefile\n",
         argv[0]);
      return 1;
   }

   if ((namefile = fopen(argv[1], "r")) == NULL) {
      (void)fprintf(stderr,
         "mk_include: Could not open namefile %s\n",
         argv[1]);
      return 1;
   }

   if ((keyfile = fopen(argv[2], "r")) == NULL) {
      (void)fprintf(stderr,
         "mk_include: Could not open keyfile %s\n",
         argv[2]);
      return 1;
   }

   if ((mergefile = fopen(argv[3], "w")) == NULL) {
      (void)fprintf(stderr,
         "mk_include: Could not open mergefile %s\n",
         argv[3]);
      return 1;
   }

   while (fgets(FileName, BUFSIZ, namefile) != NULL) {
      char *q = FileName + strlen(FileName);

      do q--; while (*q <= ' ');
      *(q+1) = '@';
      if (fgets(q+2, BUFSIZ - ((q+2) - FileName), keyfile) == NULL) {
         (void)fprintf(stderr, "mk_include: More file names than keys\n");
         return 1;
      }
      (void)fputs(FileName, mergefile);
   }
   (void)fclose(namefile); (void)fclose(keyfile); (void)fclose(mergefile);

   return 0;
}
