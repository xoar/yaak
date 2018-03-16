static char rcsid[] = "$Id: strbuild.c,v 1.2 1998/02/11 16:43:28 waite Exp $";

#include <stdio.h>
#include "strbuild.h"

char fmtarea[BUFSIZ];		/* Area to receive the results of sprintf */
struct obstack textarea;	/* Area in which to build the complete text */

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
textstr(char *s)
#else
textstr(s) char *s;
#endif
/* Add a string to the text area
 *    On entry-
 *       s=string to be added
 *    On exit-
 *       The text area contains the composite string, properly terminated
 ***/
{
	obstack_grow(&textarea, (s), strlen(s)+1);
	textarea.next_free--;
}
