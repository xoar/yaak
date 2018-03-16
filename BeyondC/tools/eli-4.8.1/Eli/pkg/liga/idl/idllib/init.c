/* $Id: init.c,v 4.1 1997/08/29 08:31:13 peter Exp $ */
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

# include "global.h"

n_type N_INIT(n,i,size)
n_type n;
int i, size;
{ 
	int *ptr;
	char *ptr2;
/* Initialize common part */
	n->IDLhidden.TypeID = i;
	n->IDLhidden.Touched = 0;
	n->IDLhidden.Shared = 0;
/* Initialize attributes (assume that they are all attributed nodes) */
	ptr2 = (char *) n;	/* so that we can add sizeof correctly */
	for (ptr = &(n->attributes); ptr < (int *)(ptr2 + size); ptr++) 
		*ptr = 0;
	return n;
}
