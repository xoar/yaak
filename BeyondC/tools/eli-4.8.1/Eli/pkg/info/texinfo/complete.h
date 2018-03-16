#ifndef COMPLETER_H
#define COMPLETER_H
/* $Id$

   Copyright 1998, The Regents of the University of Colorado

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

#include "info.h"

extern void init_completer ELI_ARG((void));
extern void remember_completion ELI_ARG((COMP_ENTRY *));
extern boolean complete ELI_ARG((char *, COMP_ENTRY *));
extern boolean try_complete ELI_ARG((char *));
extern void help_possible_completions ELI_ARG((char *));
extern boolean readline ELI_ARG((char *, char *, int, boolean));

#endif
