static char RcsId[] = "$Id: obstack.c,v 1.1.1.1 2001/04/26 20:01:49 waite Exp $";
/* obstack.c - subroutines used implicitly by object stack macros
   Copyright (C) 1988 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 1, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

In other words, you are welcome to use, share and improve this program.
You are forbidden to forbid anyone else to use, share and improve
what you give them.   Help stamp out software-hoarding!  */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if HAVE_MALLOC_H
#include <malloc.h>
#endif

#include "obstack.h"

/* Size of a page in virtual memory */
#ifndef VIRTUAL_PAGE_SIZE
#define VIRTUAL_PAGE_SIZE 4096
#endif

/* Size of the overhead information required by the storage allocator */
#ifndef ALLOCATOR_OVERHEAD
#define ALLOCATOR_OVERHEAD 4
#endif

/* Determine default alignment.  */
struct fooalign {char x; double d;};
#define DEFAULT_ALIGNMENT ((char *)&((struct fooalign *) 0)->d - (char *)0)
/* If malloc were really smart, it would round addresses to DEFAULT_ALIGNMENT.
   But in fact it might be less smart and round addresses to as much as
   DEFAULT_ROUNDING.  So we prepare for it to do that.  */
union fooround {long x; double d;};
#define DEFAULT_ROUNDING (sizeof (union fooround))

/* The non-GNU-C macros copy the obstack address into this global variable
   to avoid multiple evaluation.  */

void *_obstack_object_base;

/* Initialize an obstack H for use.  Specify chunk size SIZE (0 means default).
   Objects start on multiples of ALIGNMENT (0 means use default).
   CHUNKFUN is the function to use to allocate chunks,
   and FREEFUN the function to free them.  */

#if PROTO_OK
void
_obstack_begin(
  ObstackP h, size_t size, int alignment,
    POINTER (*chunkfun) (size_t length),
    POINTER (*expandfun) (struct _obstack_chunk *chunk, size_t length),
    void (*freefun) (POINTER obj))
#else
void
_obstack_begin(h, size, alignment, chunkfun, expandfun, freefun)
ObstackP h; size_t size; int alignment;
  POINTER (*chunkfun)(); POINTER (*expandfun)(); void (*freefun)();
#endif
{
  register struct _obstack_chunk* chunk; /* points to new chunk */

  if (alignment == 0) alignment = DEFAULT_ALIGNMENT;
  if (size == 0) {
    int extra = ALLOCATOR_OVERHEAD;
    if (extra < DEFAULT_ROUNDING) extra = DEFAULT_ROUNDING;
    size = VIRTUAL_PAGE_SIZE - extra;
  }

  h->chunkfun = (CHUNKFUNTYPE)chunkfun;
  h->expandfun = (EXPANDFUNTYPE)expandfun;
  h->freefun = (FREEFUNTYPE)freefun;
  h->chunk_size = size;
  h->alignment_mask = alignment - 1;

  chunk	= h->chunk = (*h->chunkfun) (h->chunk_size);
  h->next_free = h->object_base = chunk->contents;
  h->chunk_limit = chunk->limit = (char *) chunk + h->chunk_size;
  chunk->prev = 0;

  /* Guarantee alignment */
  (void)obstack_alloc(h, 0);
}

/* Allocate a new current chunk for the obstack *H
   on the assumption that LENGTH bytes need to be added
   to the current object, or a new object of length LENGTH allocated.
   Copies any partial object from the end of the old chunk
   to the beginning of the new one.  */

#if PROTO_OK
void *
_obstack_malloc (size_t length)
#else
void *
_obstack_malloc (length)
size_t length;
#endif
{
  void *temp = malloc(length);

  if (temp) return temp;

  (void)perror("_obstack_malloc"); exit(1);
  return (void *)0;	/* To keep lint happy */
}

#if PROTO_OK
void *
_obstack_realloc(struct _obstack_chunk *chunk, size_t length)
#else
void *
_obstack_realloc (chunk, length)
struct _obstack_chunk *chunk; size_t length;
#endif
{
  void *temp = realloc((void *)chunk, length);

  if (temp) return temp;

  (void)perror("_obstack_realloc"); exit(1);
  return (void *)0;	/* To keep lint happy */
}

#if PROTO_OK
int
_obstack_newchunk(ObstackP h, size_t length)
#else
int
_obstack_newchunk (h, length)
     ObstackP h;
     size_t length;
#endif
{
  register struct _obstack_chunk*	old_chunk = h->chunk;
  register struct _obstack_chunk*	new_chunk;
  size_t new_size;
  char *obj_loc = h->object_base;
  size_t obj_size = h->next_free - h->object_base;

  /* Reset the default chunk size if necessary */
  if (h->chunk_size == 0) {
    int extra = ALLOCATOR_OVERHEAD;
    if (extra < DEFAULT_ROUNDING) extra = DEFAULT_ROUNDING;
    h->chunk_size = VIRTUAL_PAGE_SIZE - extra;
  }

  /* Compute size for new chunk.  */
  new_size = (obj_size + length) << 1;
  if (new_size < h->chunk_size)
    new_size = h->chunk_size;

  /* Determine the allocation strategy for the new chunk:
   *   Strategy 0: Reallocate the old chunk with the new size
   *   Strategy 1: Allocate a new chunk, move the immature object,
   *     set the previous pointer of the new chunk to the old chunk
   */

  if (obj_loc == old_chunk->contents && old_chunk->prev) {
    new_chunk = h->chunk = (*h->expandfun) (old_chunk, new_size);
    h->object_base = new_chunk->contents;
    h->next_free = new_chunk->contents + obj_size;
    h->chunk_limit = new_chunk->limit = (char *) new_chunk + new_size;
  } else {
    new_chunk = h->chunk = (*h->chunkfun) (new_size);
    h->next_free = h->object_base = new_chunk->contents;
    h->chunk_limit = new_chunk->limit = (char *) new_chunk + new_size;
  
    /* Guarantee alignment */
    { size_t save = h->t_size; (void)obstack_alloc(h, 0); h->t_size = save; }
  
    /* Move the existing object to the new chunk. */
    (void)memcpy(h->next_free, obj_loc, obj_size);
    h->next_free += obj_size;

    /* Link the old chunk */
    new_chunk->prev = old_chunk;
  }
  return 0;
}

/* Return nonzero if object OBJ has been allocated from obstack H.
   This is here for debugging.
   If you use it in a program, you are probably losing.  */

#if PROTO_OK
int
_obstack_allocated_p(ObstackP h, POINTER obj)
#else
int
_obstack_allocated_p (h, obj)
     ObstackP h;
     POINTER obj;
#endif
{
  register struct _obstack_chunk*  lp;	/* below addr of any objects in this chunk */
  register struct _obstack_chunk*  plp;	/* point to previous chunk if any */

  lp = (h)->chunk;
  while (lp != 0 && (lp > (struct _obstack_chunk*)obj ||
                     lp->limit < (char *)obj))
    {
      plp = lp -> prev;
      lp = plp;
    }
  return lp != 0;
}

/* Free objects in obstack H, including OBJ and everything allocate
   more recently than OBJ.  If OBJ is zero, free everything in H.  */

#if PROTO_OK
char *
_obstack_free (ObstackP h, POINTER obj)
#else
char *
_obstack_free (h, obj)
     ObstackP h;
     POINTER obj;
#endif
{
  register struct _obstack_chunk*  lp;	/* below addr of any objects in this chunk */
  register struct _obstack_chunk*  plp;	/* point to previous chunk if any */

  lp = (h)->chunk;
  while (lp != 0 && (lp > (struct _obstack_chunk*)obj ||
                     lp->limit < (char *)obj))
    {
      plp = lp -> prev;
      (*h->freefun) (lp);
      lp = plp;
    }
  if (lp)
    {
      (h)->object_base = (h)->next_free = (char *)(obj);
      (h)->chunk_limit = lp->limit;
      (h)->chunk = lp;
    }
  else if (obj != 0)
    /* obj is not in any of the chunks! */
    abort ();
  return (char *)(obj);
}

/* copy the contents of a string into an obstack */

#if PROTO_OK
void
obstack_strgrow(ObstackP obstk, char *data)
#else
void
obstack_strgrow(obstk, data)
ObstackP obstk; char *data;
#endif
{
  register char c, *p = data;

  if (p) while ((c = *p++)) obstack_1grow(obstk, c);
}
