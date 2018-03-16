static char rcsid[]="$Id: err_map.c,v 1.7 2013/11/08 22:12:53 profw Exp $";
/* File name mapping for C error reports */
/* Copyright, 1991, The Regents of the University of Colorado */

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
#include "obstack.h"

#define WIDTH 8				/* Number of hash bits used */

static struct obstack Map;		/* Storage for the string map */
static struct obstack Chains;		   /* String definitions */

					/* Hash table */
#define BUCKETS (1<<WIDTH)		   /* Number of entries */
#define HASHMASK (BUCKETS-1)		   /* Mask for extracting offset */
typedef struct chainelt {		   /* List elements */
   struct chainelt *nxt;		      /* Chain link */
   int len;				      /* String length */
   char *dat;				      /* String pointer */
   char *map;				      /* Result string */
} CHAIN;
static CHAIN *hash[BUCKETS] = {		   /* List headers */
   (CHAIN *)0
};

/**/
char **
PtrLoc(local)
char *local;
/* Map a string to the location of a string pointer
 *    On entry-
 *       local points to the string to be mapped
 *    On exit-
 *       PtrLoc is the location of the string pointer
 ***/
{
   register CHAIN *ent;
   register int test;
   int l = strlen(local);

   /* check for null string */
   if (l == 0) return (char **)0;

   /* remove leading ./ from string */
   if ((local[0] == '.') && (local[1] == '/')) {
       local += 2;
       l -= 2;
   }

   {
      register char *cr = local;
      register int key = 0;
      register int lr = l;

      do key += *cr++; while (--lr);
      ent = (CHAIN *) &hash[key & HASHMASK];
   }

   test = 1;
   do {
      if (ent->nxt == (CHAIN *)0) break;
      ent = ent->nxt;
      if ((test = l - ent->len) == 0) {
         register char *cr = local;
         register char *p = ent->dat;
         register int lr = l;

         do ; while (*cr++ == *p++ && --lr);
         test = cr[-1] - p[-1];
      }
   } while (test > 0);

   if (test != 0) {
      CHAIN *temp = (CHAIN *)obstack_alloc(&Chains, sizeof(CHAIN));

      temp->nxt = ent->nxt; ent->nxt = temp;
      if (test < 0) { temp->len = ent->len; temp->dat = ent->dat;
		      temp->map = ent->map; }
      else ent = temp;
      ent->len = l; ent->dat = obstack_copy0(&Map, local, strlen(local));
      ent->map = (char *)0;
   }

   return &(ent->map);
}

int
main(argc,argv)
int argc; char *argv[];
/* Map the local file names of error reports to complete paths
 *    On entry-
 *       argv[1]=name of the file containing local file names
 *       argv[2]=name of the file containing complete paths
 *       argv[3]=name of the file containing error reports with local names
 *    On exit-
 *       standard output=error reports with complete paths
 */
{
   char line[BUFSIZ];
   int count;
   FILE *f, *g, *fopen();

   if (argc != 4) {
      (void)fprintf(stderr, "Usage %s locals paths reports\n", argv[0]);
      return 1;
   }

   if ((f = fopen(argv[1], "r")) == NULL) {
      (void)fprintf(stderr, "Could not open file %s\n", argv[1]);
      return 1;
   }

   if ((g = fopen(argv[2], "r")) == NULL) {
      (void)fprintf(stderr, "Could not open file %s\n", argv[2]);
      return 1;
   }

   obstack_init(&Map);
   obstack_init(&Chains);

   while (fgets(line, BUFSIZ, f) != NULL) {
      char **location;

      line[strlen(line)-1] = '\0';
      location = PtrLoc(line);

      if (fgets(line, BUFSIZ, g) == NULL) {
         (void)fprintf(stderr, "%s: unexpected EOF\n", argv[2]);
         return 1;
      }
      *location = obstack_copy0(&Map, line, strlen(line)-1);
   }

   if (fgets(line, BUFSIZ, g) != NULL) {
      (void)fprintf(stderr, "%s: unexpected EOF\n", argv[1]);
      return 1;
   }
   (void)fclose(f); (void)fclose(g);

   if ((f = fopen(argv[3], "r")) == NULL) {
      (void)fprintf(stderr, "Could not open file %s\n", argv[3]);
      return 1;
   }

   while ((count = fscanf(f, "%s", line)) != EOF) {
     if (count == 0) {
       (void)fgets(line, BUFSIZ, f);
       (void)fprintf(stderr, "Invalid error report: %s\n", line);
     } else {
       char **location = PtrLoc(line);
       if (*location) {
	 (void)fgets(line, BUFSIZ, f);
	 (void)printf("%s%s", *location, line);
       } else {
	 (void)printf("%s", line);
	 (void)fgets(line, BUFSIZ, f);
	 (void)printf("%s", line);
       }
     }
   }

   return 0;
}
