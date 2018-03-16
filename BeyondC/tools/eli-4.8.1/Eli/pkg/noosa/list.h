/*
 * $Id: list.h,v 1.9 1999/10/20 08:34:02 tony Exp $
 * Copyright (c) 1994-1997 Anthony M. Sloane
 */

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

#ifndef LIST_H
#define LIST_H

extern int n_llistCmd _ANSI_ARGS_ ((ClientData clientData,
		   	            Tcl_Interp *interp, int argc,
				    char *argv[]));

#endif
