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
#include "err.h"

POSITION aktpos = {0, 0};

static int doerrinit = 1;

void 
err_setpos(line, col)
   int line;
   int col;
{
   aktpos.line = line;
   aktpos.col = col;
}

void 
err_print_error(mesg)
   char *mesg;
{
   if (doerrinit) ErrorInit (1, 0, 0); /* immediate, no AG, no limit */
   doerrinit = 1;
   message(ERROR, mesg, 0, &aktpos);
}

void 
err_print_warning(mesg)
   char *mesg;
{
   if (doerrinit) ErrorInit (1, 0, 0); /* immediate, no AG, no limit */
   doerrinit = 1;
   message(WARNING, mesg, 0, &aktpos);
}

void 
err_print_note(mesg)
   char *mesg;
{
   if (doerrinit) ErrorInit (1, 0, 0); /* immediate, no AG, no limit */
   doerrinit = 1;
   message(NOTE, mesg, 0, &aktpos);
}

void 
err_print_deadly(mesg)
   char *mesg;
{
   if (doerrinit) ErrorInit (1, 0, 0); /* immediate, no AG, no limit */
   doerrinit = 1;
   message(DEADLY, mesg, 0, &aktpos);
}
