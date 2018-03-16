static char rcsid[] = "$Id: signals.c,v 1.11 2005/07/29 21:47:28 profw Exp $";

/* signals.c

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

#include "../../../config.h" 
#include <unistd.h>
#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif
#include "info.h"

extern char *widest_line;
extern int terminal_rows, terminal_lines;
extern IWINDOW_LIST *window_stack;

typedef void (*SigFunction) ELI_ARG((int));

#ifdef SIGTSTP
SigFunction old_stop;		/* last value of SIGSTOP. */
SigFunction old_cont;		/* last value of SIGCONT. */
#endif

#ifdef SIGWINCH
SigFunction old_winch; 		/* last value of SIGWINCH. */
#endif


void
#if defined(_AIX) || defined(__STDC__)
#ifdef PROTO_OK
info_signal_handler(int sig)
#else
info_signal_handler(sig) int sig;
#endif
#else
#ifdef PROTO_OK
info_signal_handler(int sig, int arg1, int arg2)
#else
info_signal_handler(sig, arg1, arg2) int sig, arg1, arg2;
#endif
#endif
{
  /* Do the right thing with this signal. */

  switch (sig)
    {

#ifdef SIGTSTP
    case SIGTSTP:
      echo (); nocrmode ();
      signal (SIGTSTP, old_stop);
      (void)kill (getpid (), SIGSTOP);
      break;

    case SIGCONT:
      /* Try to win some more.  Reset IO state, and stuff
         like that. */
      noecho (); crmode ();
      wrefresh (curscr);
      signal (SIGTSTP, info_signal_handler);
      break;
#endif /* SIGTSTP */

    case SIGINT:
      endwin();
      exit (1);
      break;
    }
}

void
#ifdef PROTO_OK
install_signals(void)
#else
install_signals()
#endif
{
#ifdef SIGTSTP
  old_stop = (SigFunction) signal (SIGTSTP, info_signal_handler);
  old_cont = (SigFunction) signal (SIGCONT, info_signal_handler);
#endif /* SIGTSTP */

#ifdef SIGWINCH
  old_winch = (SigFunction) signal (SIGWINCH, info_signal_handler);
#endif

  signal (SIGINT, info_signal_handler);
}
