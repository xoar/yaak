static char rcsid[] = "$Id: count.c,v 1.2 1994/08/25 19:13:19 waite Exp $";
/* Counting operations */

#include <stdio.h>

static int count = 0;		/* Initially no words have been seen */

void
#if defined(__cplusplus)
CountWord(char *, int, int *, int *)
#else
CountWord()
#endif
/* Increment the counter when a word is found */
{ count++; }

void
CountFinl()
/* Counter finalization: Print the total */
{ (void)printf("%d words\n", count); }
