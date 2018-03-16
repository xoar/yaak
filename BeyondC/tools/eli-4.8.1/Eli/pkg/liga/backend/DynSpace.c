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
#include <stdio.h>
#include <stdlib.h>
#include "obstack.h"
#include "DynSpace.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

#if defined(__STDC__) || defined(__cplusplus)
void *DynAlloc (void *space, int size)
#else
void* DynAlloc (space, size)
	void*	space;
	int	size;
#endif
{
    DynP spc;

    spc = (DynP) space;
    return ((void*)obstack_alloc(&(spc->space), size));
}/* DynAlloc */

#if defined(__STDC__) || defined(__cplusplus)
void DynClear(void *space)
#else
void DynClear (space)
     void *space;
#endif
{
    DynP spc;

    spc = (DynP) space;
    obstack_free(&(spc->space), spc->baseptr);
    spc->baseptr = obstack_alloc(&(spc->space), 0);
} /* DynClear */

#if defined(__STDC__) || defined(__cplusplus)
void *InitDynSpace(void)
#else
void* InitDynSpace ()
#endif
{
    DynP New;

    New = (DynP) malloc (sizeof(Dyn));
    if (!New) {
	fprintf (stderr, "no space for DynSpace\n");
	exit (1);
    }

    obstack_init(&(New->space));
    New->baseptr = obstack_alloc(&(New->space), 0);

    return ((void*)New);
}/* InitDynSpace */
