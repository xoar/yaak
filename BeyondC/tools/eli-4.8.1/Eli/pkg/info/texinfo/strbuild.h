/* $Id: strbuild.h,v 1.4 1994/06/22 06:22:38 waite Exp $ */
/* Interface for the info browser typeout module */
/* Copyright 1991, The Regents of the University of Colorado */

#include <stdlib.h>
#include "obstack.h"

extern char fmtarea[BUFSIZ];	/* Area to receive the results of sprintf */
extern struct obstack textarea;	/* Area in which to build the complete text */

#define textinit() obstack_init(&textarea)
#define textptr (textarea.object_base)
#define textfree() textarea.next_free = textarea.object_base

#if defined(__cplusplus) || defined(__STDC__)
extern void textstr(char *s);
/* Add a string to the text area
 *    On entry-
 *       s=string to be added
 *    On exit-
 *       The text area contains the composite string, properly terminated
 ***/
#else
extern void textstr();
#endif
