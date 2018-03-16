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
/* $Id: idntbl.h,v 4.1 1997/08/29 07:54:24 peter Exp $ */
/* Copyright 1989, The Regents of the University of Colorado
 * Permission is granted to use any portion of this file for any purpose,
 * commercial or otherwise, provided that this notice remains unchanged.
 */


#define HTSIZE 256		/* Hash table size */

static CHAIN *hash[HTSIZE]={NULL};/* Hash table */

int dofold = 0;			/* Distinguish upper and lower case letters */
