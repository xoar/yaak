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
/* $Id: middle_mem.c,v 4.3 1998/03/03 08:11:37 peter Exp $ */
static char rcs_id[] = "$Id: middle_mem.c,v 4.3 1998/03/03 08:11:37 peter Exp $";

/********************************************************
*	Module	: middle_mem.c				*
*	Contains functions for allocation  and  	*
*       deallocation of  spaces				*
********************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define obstack_chunk_alloc MyMalloc
#define obstack_chunk_free MyFree
#endif

#include "obstack.h"
#include "middle_mem.h"
#include "err.h"

#ifdef DEBUG
#if defined(__STDC__) || defined(__cplusplus)
void *MyMalloc(size_t size)
#else
void *MyMalloc(size)
size_t size;
#endif
{ void *res;
  res = (void*) malloc(size);

  fprintf(stderr, "   allocating %d bytes addr = %ld \n", size, (long int)res);

  return res;
}

#if defined(__STDC__) || defined(__cplusplus)
void MyFree(void *p)
#else 
void MyFree(p)
void *p;
#endif
{ 
  fprintf(stderr, "freeing one chunk addr = %ld\n", (long int)p);
  free(p);
}
#endif /* of DEBUG */

/* two memory areas: "permanent" is not cleared after a liga middle end
   phase. It contains storage allocated for the idl data structure
   which is the interface between the liga middle end phases.
   "temporary" is an arean of storage wich is deallocated after each
   liga middle end phase. "temphandle" is an zero-sized memory object
   on "temporary" used to deallocate storage.
*/

static Obstack permanent;
static Obstack temporary;
static int *temphandle;

#if defined(__STDC__) || defined(__cplusplus)
void init_middle_mem(void)
#else 
void init_middle_mem()
#endif
{ 
#if DEBUG
  fprintf(stderr, "init_middle_mem()\n");
#endif
  obstack_init(&permanent);
  obstack_init(&temporary);
  temphandle= (int*) obstack_alloc(&temporary,0);
}

#if defined(__STDC__) || defined(__cplusplus)
void finish_middle_mem(void)
#else
void finish_middle_mem()
#endif
{ 
#if DEBUG
  fprintf(stderr, "finish_middle_mem()\n");
#endif
  obstack_free(&temporary,temphandle);
}

#if defined(__STDC__) || defined(__cplusplus)
char *middle_Malloc(char *file, int line, unsigned int size)
#else
char *middle_Malloc(file, line, size)
   char *file;
   int line;
   unsigned size;
#endif
{
   char *p = obstack_alloc(&permanent,size);

#if DEBUG
   fprintf(stderr, "%d: middle_Malloc (%s, %d) size = %d \n",
                     (int)p, file, line, size);
#endif

   if (p == NULL)
   { char msg[80];
      sprintf(msg,"No more memory (file %s, line %d)\n", file, line);
      message(DEADLY, msg, 0, &curpos);
   }	/* if */
   return (p);
}/* exp_Malloc() */


#if defined(__STDC__) || defined(__cplusplus)
char * middle_tempMalloc(char *file, int line, unsigned int size)
#else 
char * middle_tempMalloc(file, line, size)
   char *file;
   int line;
   unsigned size;
#endif
{
   char *p = obstack_alloc(&temporary,size);

#if DEBUG
   fprintf(stderr, "%d: middle_tempMalloc (%s, %d) size = %d \n",
                     (int)p, file, line, size);
#endif

   if (p == NULL)
   {  char msg[80];
      sprintf(msg,"No more memory (file %s, line %d)\n", file, line);
      message(DEADLY, msg, 0, &curpos);
   }	/* if */
   return (p);
} 

#if defined(__STDC__) || defined(__cplusplus)
void middle_Free(char *file, int line, void *p)
#else
void middle_Free(file, line, p)
   char *file;
   int line;
   void *p;
#endif
{
#if DEBUG
   fprintf(stderr, "%d: middle_Free (%s, %d) \n",
                     (int)p, file, line);
#endif
/*   obstack_free(&permanent, p); */
} 

#if defined(__STDC__) || defined(__cplusplus)
void middle_tempFree(char *file, int line, void*p)
#else 
void middle_tempFree(file, line, p)
   char *file;
   int line;
   void*p;
#endif
{
#if DEBUG
   fprintf(stderr, "%d: middle_tempFree (%s, %d) \n",
                     (int)p, file, line);
#endif
/*   obstack_free(&temporary, p); */
} 


