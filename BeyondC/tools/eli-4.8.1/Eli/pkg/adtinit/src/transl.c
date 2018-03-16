static char RCSid[] = "$Id: transl.c,v 1.11 2009/09/10 16:49:46 profw Exp $";
/* Copyright 1989, The Regents of the University of Colorado */

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

#if defined(__cplusplus) || defined(__STDC__)
int
main(int argc, char **argv)
#else
int
main(argc,argv)
int argc; char **argv;
#endif
{
   char line[BUFSIZ], data[BUFSIZ], *text[BUFSIZ];
   int code, i, j, l, key[BUFSIZ], newkey[BUFSIZ], next;
   FILE *f;

   if (argc != 2) {
      (void)fprintf(stderr,"Usage %s newCodes\n", *argv);
      exit(1);
   }
   if ((f = fopen(argv[1], "r")) == NULL) {
      (void)fprintf(stderr, "%s: Cannot open file %s\n", *argv, argv[1]);
      exit(1);
   }

   for (i = 0; i < BUFSIZ; i++) key[i] = i;   /* Default is same code */

   next = 0;
   while (fgets(line, BUFSIZ, f) != NULL) {
      (void)sscanf(line, "%d %d %d %d%*c%[^\n]", &code, &i, &j, &l, data);
      (void)getc(f);   /* Skip the space that precedes the symbol */
      if (code == 5 && i == 1) {
         char *p, *q;

         /* Symbol exists only in the concrete grammar */
         newkey[next] = j;
         text[next] = (char *)malloc((unsigned) (l+1));
         p = text[next]; q = data;
         while (l--) *p++ = *q++;
         *p = '\0';
         next++;
      } else {
         /* Symbol found in the abstract grammar */
         key[i] = j;
      }
   }

   while (fgets(line, BUFSIZ, stdin) != NULL) {
      if (line[strlen(line)-1] != '\n') {
         (void)fprintf(stderr, "%s: \"%s\" too long\n", *argv, line);
         exit(1);
      }
      (void)sscanf(line, " %d %d%*c%[^\n]", &i, &l, data);
      (void)printf("%d %d %s\n", key[i], l, data);
   }

   while (next-- > 0) {
      (void)printf("%d %d %s\n",
            newkey[next], (int)strlen(text[next]), text[next]);
   }

   return 0;
}
