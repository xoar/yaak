static char rcsid[] = "$Id: help.c,v 1.7 1998/02/11 16:43:06 waite Exp $";

/* help.c

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

#include "info.h"
#include "typeout.h"

void
#ifdef PROTO_OK
help_use_info(void)
#else
help_use_info()
#endif
{
  /* Tell this person how to use Info. */

  typeout("Commands in Info\n\
\n\
h       Invoke the Info tutorial.\n\
\n\
Selecting other nodes:\n\
n       Move to the \"next\" node of this node.\n\
p       Move to the \"previous\" node of this node.\n\
u       Move \"up\" from this node.\n\
m       Pick menu item specified by name.\n\
        Picking a menu item causes another node to be selected.\n\
f       Follow a cross reference.  Reads name of reference.\n\
l       Move to the last node you were at.\n\
d       Move to the top node of the documentation tree.\n\
\n\
Moving within a node:\n\
Space   Scroll forward a page.\n\
DEL     Scroll backward a page.\n\
b       Go to the beginning of this node.\n\
\n\
Running and editing:\n\
r       Run the commands associated with this node.\n\
        See also WINRUNNER option using 'o' command.\n\
v       View the output of the last run.\n\
e       Edit the files associated with this node.\n\
        See also EDITOR and WINEDITOR options.\n\
\n\
Miscellaneous commands (C-c means \"Control-c\"):\n\
1       Pick first item in node's menu.\n\
2 - 5   Pick second ... fifth item in node's menu.\n\
c       Complain.  Send mail to documentation maintainer.\n\
g       Move to node specified by name.\n\
        You may include a filename as well, as (FILENAME)NODENAME.\n\
o       Set and/or examine info options using an interactive menu mode.\n\
q, C-c  Quit Info.\n\
s       Search through this Info file for a specified string,\n\
        and select the node in which the next occurrence is found.\n\
C-g     Abort current command or incomplete typein.\n\
?, C-h  Display this command summary.\n\
C-p     Print the CURRENT MANUAL to a laser printer.\n\
C-t     Print the contents of this node as a text file.\n\
        See also PRINTER option.\n", 0);
}
