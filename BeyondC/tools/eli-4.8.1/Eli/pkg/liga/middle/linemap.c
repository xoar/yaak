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
/* $Id: linemap.c,v 4.3 1997/08/29 09:07:44 peter Exp $ */
static char rcs_id[] = "$Id: linemap.c,v 4.3 1997/08/29 09:07:44 peter Exp $";

#include <stdio.h>
#include <string.h>
#include "obstack.h"
#define obstack_strcpy(obs, dat) obstack_copy0(obs, dat, strlen(dat))

typedef struct 
{
    char *FileName;
    int Limit, Increment;
} Block;

static Block *linemap = 0;
static int TopEntry;

static Obstack FileNames;
static Obstack BlockStorage;

#if defined (__cplusplus) || defined(__STDC__)
void build_linemap(FILE *lm)
#else 
void build_linemap(lm)
FILE *lm;
#endif
{	
    
    int	more;
    char filename[BUFSIZ];
    
    if (linemap)   /* already initialized */
	return;
    
    obstack_init(&FileNames);
    obstack_init(&BlockStorage);
    obstack_blank(&BlockStorage, sizeof(Block));
    linemap = (Block *)obstack_base(&BlockStorage);
    TopEntry = 0;
    linemap[0].FileName = "<no file>";
    linemap[0].Limit = 0;
    linemap[0].Increment = 0;
    TopEntry++;
    
    do 
    {
	obstack_blank(&BlockStorage, sizeof(Block));
	linemap = (Block *)obstack_base(&BlockStorage);
	
   	more = fscanf(lm, "%d %d %s\n", 
		      &(linemap[TopEntry].Limit), &(linemap[TopEntry].Increment), 
		      filename) == 3;
	if (more) 
	{
	    linemap[TopEntry].FileName = obstack_strcpy(&FileNames, filename);
	    TopEntry++;
	}
    } while (more);

/* input test only
for (more=0; more<TopEntry; more++)
printf(" %d %d %s\n", Limit[more], Increment[more], FileName[more]);
exit(1);
*/
}

#if defined (__cplusplus) || defined(__STDC__)
int map_line(int line)
#else 
int map_line(line)
int line;
#endif
{ int	ind = 0, search = 1;
  while (search && (ind < TopEntry))
	if (line >= linemap[ind].Limit) ind++; else search = 0;
 return line + linemap[ind-1].Increment;
}


#if defined (__cplusplus) || defined(__STDC__)
char *map_file(int line)
#else 
char *map_file(line)
int line;
#endif
{ int ind = 0;
  int search = 1;
  while (search && (ind < TopEntry))
     if (line >= linemap[ind].Limit) 
	ind++; 
     else search = 0;
  return (linemap[ind-1].FileName);
}


