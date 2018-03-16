static char rcsid[] = "$Id: system.c,v 1.9 1998/02/11 16:43:29 waite Exp $";

/* system.c

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

#include <unistd.h>
#include "info.h"
#include "file.h"
#include "driver.h"
#include "system.h"

void *
#if defined(__cplusplus) || defined(__STDC__)
xmalloc(size_t bytes)
#else
xmalloc(bytes)
size_t bytes;
#endif
{
  void *temp = (void *)malloc(bytes);

  if (!temp) opsys_abort("Out of virtual memory!\n", 2);
  return (temp);
}

void *
#if defined(__cplusplus) || defined(__STDC__)
xrealloc(char *pointer, size_t bytes)
#else
xrealloc (pointer, bytes)
char *pointer; size_t bytes;
#endif
{
  void *temp = (void *)realloc(pointer, bytes);
  if (!temp) opsys_abort("Out of virtual memory!\n", 2);
  return (temp);
}

void
#if defined(__cplusplus) || defined(__STDC__)
background(char *cmd, char *file)
#else
background(cmd, file)
char *cmd, *file;
#endif
{
  /* run a command in the background */
  /* if file!=NULL then file is deleted after the command runs */
  /* get one more process here than we need, but it's easy this way */

  int i, n;

  switch (fork()) {
  case 0:
#if !defined(hpux) && !defined(__SVR4) && !defined(__svr4__)
    /* Sever our connection with the info reader's files */
    n = getdtablesize();
    for (i = 3; i < n; i++) (void)close(i);
#endif
    (void)system(cmd);
    if ( file ) (void)deletefile(file);
    exit(0);
  case -1:
    display_error("Fork for a background job failed");
    if ( file ) (void)deletefile(file);
  default:
    ;
  }
}
