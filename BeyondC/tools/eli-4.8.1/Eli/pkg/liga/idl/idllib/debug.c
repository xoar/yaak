/* $Id: debug.c,v 4.2 2000/07/17 14:06:29 peter Exp $ */
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
#include "reader.h"
#include <stdio.h>


/* for printing out label table */
/* print only entries which have values */

#define LTABSIZ 1024

void
PrintLabelTable(LabelTable)
LabelRefType LabelTable[LTABSIZ];
{

	int i;
	LabelRefType R;

	fprintf(stderr, "LABEL TABLE\n");
	for (i=0; i<LTABSIZ; i++) {
	    
	    R = LabelTable[i];
	    if (R) fprintf(stderr, "\n %d: ", i);
	    while (R) {
		fprintf(stderr, "%s ", R->Name);
		R = R->next;
	    }
	}
	fprintf(stderr, "\n\n");
	fflush(stderr);
}
