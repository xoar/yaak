static char rcsid[] = "$Id: option.c,v 1.16 1998/02/11 16:43:21 waite Exp $";

/* option.c

   Copyright (C) 1987 Free Software Foundation, Inc.

   This file is part of GNU Info.

   GNU Info is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.  No author or distributor accepts
   responsibility to anyone for the consequences of using it or for
   whether it serves any particular purpose or works at all, unless he
   says so in writing.  Refer to the GNU Emacs General Public License
   for full details.

   Everyone is granted permission to copy, modify and redistribute
   GNU Info, but only under the conditions described in the GNU Emacs
   General Public License.   A copy of this license is supposed to
   have been given to you along with GNU Emacs so you can know your
   rights and responsibilities.  It should be in a file named COPYING.
   Among other things, the copyright notice and this notice must be
   preserved on all copies.  
*/

/* **************************************************************** */
/*								    */
/*		           Option handling			    */
/*								    */
/* **************************************************************** */

#include "info.h"
#include "option.h"
#include "system.h"

/* Useful macro for storing strings. */
#define savestring(x) (strcpy((char *)xmalloc((size_t)(1+strlen(x))),(x)))

/* The order of these options must be correctly reflected in the option
  indexes in info.h */

OPTION options[] = {
  { "EDITOR", NULL,
      "Program to use for editing." },
  { "WINEDITOR", NULL,
      "Program to use for editing in parallel." },
  { "WINRUNNER", NULL,
      "Program to use to execute the Run command." },
  { "PRINTER", NULL,
      "Printer to send any printouts to." },
  { "SEARCHINSENSITIVE", NULL,
      "Case insensitivity of search commands." },
  { NULL, NULL, NULL }
};

static void
#if defined(__cplusplus) || defined(__STDC__)
replace_option(int option, char *newvalue)
#else
replace_option(option, newvalue)
int option; char *newvalue;
#endif
{
  char **strp;

  strp = &(options[option].value);
  if (*strp != NULL)
    free(*strp);
  *strp = savestring( newvalue );
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
init_options(INIT_OPTION *opts)
#else
init_options(opts)
INIT_OPTION *opts;
#endif
/* Initialize the option data structure
 ***/
{
  int i;
  char *cp;
  INIT_OPTION *o;

  options[EDITOR].value = savestring(DEFAULT_EDITOR);
  options[PRINTER].value = savestring(DEFAULT_PRINTER);
  options[SEARCHINSENSITIVE].value = savestring(DEFAULT_SEARCHINSENSITIVE);

  if (opts != (INIT_OPTION *)NULL)
	  for (o = opts; o->index != -1; o++)
		  replace_option( o->index, o->value );

  for (i = 0; options[i].name != NULL; i++)
    if ((cp = getenv(options[i].name)) != NULL)
      replace_option( i, cp );
}
