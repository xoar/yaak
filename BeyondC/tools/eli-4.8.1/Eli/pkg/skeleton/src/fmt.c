static char rcsid[] = "$Id: fmt.c,v 1.6 2004/08/01 04:51:49 profw Exp $";
/* Copyright 1993, The Regents of the University of Colorado */

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

#define DEFAULT_LIMIT 70

/**/
void
OutSeg(first, limit)
char *first, *limit;
/* Output a saved segment
 *   On entry-
 *     first points to the first character to be output
 *     limit points to the character beyond the last character to be output
 *   On exit-
 *     The segment has been added to the current line
 **/
{ while (first != limit) (void)putchar(*first++); }

/***/
#if defined(__STDC__) || defined(__cplusplus)
int
main(int argc, char **argv)
#else
int
main(argc, argv)
int argc;
char **argv;
#endif
/* Assemble lines not exceeding LIMIT characters
 *   On entry-
 *     stdin = input text to be assembled
 *   On exit-
 *     stdout = sequence of assembled lines
 *     If a line is longer than LIMIT then it has no internal white space
 ***/
{
  char *Segment, *p;
  int Current, State = 0, Count, limit;

  if (argc > 1)
    limit = atoi(argv[1]);
  else
    limit = DEFAULT_LIMIT;

  if (!(Segment = (char *)malloc(limit))) {
    fprintf(stderr, "%s: malloc error\n", argv[0]);
    exit(1);
  }  

  while ((Current = getchar()) != EOF) {
    switch (State) {
    case 0:	/* No information */
      if (Current > ' ') { Count = 0; p = Segment; State = 1; }
      else break;
    case 1:	/* Holding initial segment */
      if (Current > ' ') {
        Count++; *p++ = Current;
        if (Count == limit) { OutSeg(Segment, p); p = Segment; }
        break;
      } else { OutSeg(Segment, p); State = 2; }
    case 2:	/* Inter-segment white space */
      if (Current > ' ') { Count++; p = Segment; State = 3; }
      else break;
    case 3:	/* Holding non-initial segment */
      if (Current > ' ') {
        Count++; *p++ = Current;
        if (Count >= limit) {
          (void)putchar('\n'); Count = (p - Segment); State = 1;
        }
      } else { (void)putchar(' '); OutSeg(Segment, p); State = 2; }
    }
  }
  if (State) (void)putchar('\n');

  return 0;
}
