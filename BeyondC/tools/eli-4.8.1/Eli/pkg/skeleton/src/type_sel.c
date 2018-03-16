static char rcsid[] = "$Id: type_sel.c,v 1.6 2013/11/08 22:03:21 profw Exp $";
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
#include <string.h>

/****/
int
main(argc, argv)
int argc; char *argv[];
/* Filter to select Odin objects of a specific type
 *    On entry-
 *       argv[1]="extract" if the selected objects are output
 *               "delete"  if the non-selected objects are output
 *       argv[2]=type to be selected
 *       argv[3]=name of the file containing the labels of the objects
 *       argv[4]=name of the file containing the Odin names of the objects
 *    If there are no errors then on exit-
 *       type_sel.exe returns completion code 0
 *       standard output contains the names of the objects selected
 *          (possibly none)
 *    Else on exit-
 *       type_sel.exe returns completion code 1
 *       standard error contains the error report
 ****/
{
   char label[BUFSIZ], *l, name[BUFSIZ], *n;
   int extract, delete, keylen;
   FILE *labels, *names;

   if (argc != 5) {
      (void)fprintf(stderr,
         "Usage: %s operation type_key label_file name_file\n",
         *argv);
      return 1;
   }

   if (strcmp(argv[1], "extract") == 0) { extract = 1; delete = 0; }
   else if (strcmp(argv[1], "delete") == 0) { extract = 0; delete = 1; }
   else {
      (void)fprintf(stderr,
         "type_sel: first argument must be either \"extract\" or \"delete\"\n");

      return 1;
   }

   keylen = strlen(argv[2]);

   if ((labels = fopen(argv[3], "r")) == NULL) {
      (void)fprintf(stderr, "type_sel: label file %s not found\n", argv[3]);
      return 1;
   }

   if ((names = fopen(argv[4], "r")) == NULL) {
      (void)fprintf(stderr, "type_sel: name file %s not found\n", argv[4]);
      return 1;
   }

   l = fgets(label, BUFSIZ, labels);
   n = fgets(name, BUFSIZ, names);
   while (l && n) {
      int lblen, typndx, select;

      lblen = strlen(label)-1; label[lblen] = '\0';
      select = (typndx = lblen - keylen) >= 2
         && label[typndx-1] == '.'
         && strcmp(label + typndx, argv[2]) == 0;
      if ((select && extract) || (!select && delete)) (void)fputs(name, stdout);
      l = fgets(label, BUFSIZ, labels);
      n = fgets(name, BUFSIZ, names);
   }

   if (l != n) {
      (void)fprintf(stderr, "type_sel: label and name file lengths differ\n");
      return 1;
   }

   return 0;
}
