/* (C) Copyright 1997 University of Paderborn */

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

#include "global.h"
#include <stdio.h>
#include <stdlib.h>

static char rcsid[]="$Id: alloc.c,v 1.7 1997/08/29 08:38:08 mjung Exp $";

someptr GetHeap(size)
int size;
{
    someptr storage;
    static int count=0;

    storage = (someptr)malloc(size);
#ifdef DEBUG
    if ((++count % 1000)==0) {
	if (malloc_verify()!=1) {
	    printf("heap corrupted\n");
	    exit(-1);
	}
    }
#endif

    if (!storage) {
	fprintf(stderr, "******Ran out of heap storage*****\n");
	exit(1);
    }

    else return(storage);
}
