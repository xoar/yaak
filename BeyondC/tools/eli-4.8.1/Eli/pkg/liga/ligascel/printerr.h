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
#if defined(__cplusplus) || defined(__STDC__)
extern void err_setpos(int line, int col);
extern void err_print_error(char *message);
extern void err_print_warning(char *message);
extern void err_print_deadly(char *message);
extern void err_print_note(char *message);
#else
extern void err_setpos();
extern void err_print_error();
extern void err_print_warning();
extern void err_print_deadly();
extern void err_print_note();
#endif

#define ERR_BUFF_LEN  300
