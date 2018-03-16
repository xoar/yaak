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
/***************/
/* do_optim.h */
/***************/


#ifndef DO_OPTIM_H
#define DO_OPTIM_H

#include <stdio.h>

#ifdef __STDC__
extern void do_optim(AttrEval idlstruct, FILE *ctlfile1, FILE *ctlfile2);
#else
extern void do_optim();
#endif

#ifdef __STDC__
extern void optim_deadly(char * msg);
#else
extern void optim_deadly();
#endif

#ifdef __STDC__
extern void do_opt_commandline(int argc, char *argv[]);
#else
extern void do_opt_commandline();
#endif

#endif

