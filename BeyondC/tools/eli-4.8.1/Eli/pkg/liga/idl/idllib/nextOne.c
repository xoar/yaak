/* $Id: nextOne.c,v 4.1 1997/08/29 08:31:13 peter Exp $ */

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
int _nextOne(set,offset,max)
int set[];
int offset,max;
{	register int i,j,k;
# ifdef DEBUG
for (i=0; i<max/WordWidth; ++i) printf("%x\n",set[i]);
# endif
	if (offset == -1) k=0;
	else k=offset/WordWidth;
	for (; k <= max/WordWidth; ++k)
		for (i=1,j=0; j < WordWidth; ++j, i<<=1)
			if ((i&set[k])&&(j+k*WordWidth > offset))
				return j+k*WordWidth;
	return -1;	/* fell off the end */
}
