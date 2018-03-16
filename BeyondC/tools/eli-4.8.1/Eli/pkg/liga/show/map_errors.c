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
/* Map line numbers to the proper lines of component files */

static char     rcsid[] = "$Id: map_errors.c,v 4.5 2008/08/15 12:42:56 peter Exp $";

#include <stdio.h>
#include <string.h>
#include "obstack.h"
#define obstack_strgrow(obs, dat) obstack_grow(obs, dat, strlen(dat))
#define obstack_strcpy(obs, dat) obstack_copy0(obs, dat, strlen(dat))

typedef struct {
	char           *FileName;
	int             Limit, Increment;
}               Block;

static Block   *linemap = 0;
static int      TopEntry;

static Obstack  FileNames;
static Obstack  BlockStorage;

#if defined (__cplusplus) || defined(__STDC__)
void 
ErrTabInit(FILE * lm)
#else
void 
ErrTabInit(lm)
	FILE           *lm;
#endif
{

	int             more;
	char            filename[BUFSIZ];

	if (linemap)		/* already initialized */
		return;

	obstack_init(&FileNames);
	obstack_init(&BlockStorage);
	obstack_blank(&BlockStorage, sizeof(Block));
	linemap = (Block *) obstack_base(&BlockStorage);
	TopEntry = 0;
	linemap[0].FileName = "<no file>";
	linemap[0].Limit = 0;
	linemap[0].Increment = 0;
	TopEntry++;

	do {
		obstack_blank(&BlockStorage, sizeof(Block));
		linemap = (Block *) obstack_base(&BlockStorage);

		more = fscanf(lm, "%d %d %s\n",
		 &(linemap[TopEntry].Limit), &(linemap[TopEntry].Increment),
			      filename) == 3;
		if (more) {
			linemap[TopEntry].FileName = obstack_strcpy(&FileNames, filename);
			TopEntry++;
		}
	} while (more);
}

#if defined (__cplusplus) || defined(__STDC__)
void
MapCoord(int linein, int *findex, int *line)
#else
void 
MapCoord(linein, findex, line)
	int             linein;
	int            *findex, *line;
#endif
{
	int             ind = 0, search = 1;
	while (search && (ind <= TopEntry))
		if (linein >= linemap[ind].Limit)
			ind++;
		else
			search = 0;

	(*findex) = ind - 1;
	(*line) = linein + linemap[ind - 1].Increment;
}				/* MapCoord */

#if defined (__cplusplus) || defined(__STDC__)
char *
GetErrMapFileName(int ind)
#else
char *
GetErrMapFileName(ind)
	int             ind;
#endif
{
	if ((ind < 0) || (ind >= TopEntry))
		return ("");
	return (linemap[ind].FileName);
}				/* GetErrMapFileName */
