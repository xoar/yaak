/* $Id: obstack.h,v 1.1.1.1 2001/04/26 20:01:49 waite Exp $ */
/* obstack.h - object stack macros
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


/* Summary:

All the apparent functions defined here are macros. The idea
is that you would use these pre-tested macros to solve a
very specific set of problems, and they would run fast.
Caution: no side-effects in arguments please!! They may be
evaluated MANY times!!

These macros operate a stack of objects.  Each object starts life
small, and may grow to maturity.  (Consider building a word syllable
by syllable.)  An object can move while it is growing.  Once it has
been "finished" it never changes address again.  So the "top of the
stack" is typically an immature growing object, while the rest of the
stack is of mature, fixed size and fixed address objects.

These routines grab large chunks of memory, using a function you
supply, called `obstack_chunk_alloc'.  On occasion, they free chunks,
by calling `obstack_chunk_free' or re-size chunks by calling
`obstack_chunk_realloc'.  You may supply your own chunk management
functions by providing #define directives for these three symbols before
including this file, or by defining them on the cc command line.
*/

#include "config.h"

#define POINTER void *

#ifndef obstack_chunk_alloc
#define obstack_chunk_alloc _obstack_malloc
#endif
#ifndef obstack_chunk_realloc
#define obstack_chunk_realloc _obstack_realloc
#endif
#ifndef obstack_chunk_free
#define obstack_chunk_free free
#endif

#if PROTO_OK
#define CHUNKFUNTYPE struct _obstack_chunk *(*)(size_t length)
#define EXPANDFUNTYPE \
  struct _obstack_chunk *(*)(struct _obstack_chunk *chunk, size_t length)
#define FREEFUNTYPE void (*) (POINTER obj)
#else
#define CHUNKFUNTYPE struct _obstack_chunk *(*)()
#define EXPANDFUNTYPE struct _obstack_chunk *(*)()
#define FREEFUNTYPE void (*) ()
#endif

/*
Each independent stack is represented by an `Obstack'.
Each of the obstack macros expects a pointer to such a structure
as the first argument.

One motivation for this package is the problem of growing char strings
in symbol tables.  Unless you are "facist pig with a read-only mind"
[Gosper's immortal quote from HAKMEM item 154, out of context] you
would not like to put any arbitrary upper limit on the length of your
symbols.

In practice this often means you will build many short symbols and a
few long symbols.  At the time you are reading a symbol you don't know
how long it is.  One traditional method is to read a symbol into a
buffer, realloc()ating the buffer every time you try to read a symbol
that is longer than the buffer.  This is beaut, but you still will
want to copy the symbol from the buffer to a more permanent
symbol-table entry say about half the time.

With obstacks, you can work differently.  Use one obstack for all symbol
names.  As you read a symbol, grow the name in the obstack gradually.
When the name is complete, finalize it.  Then, if the symbol exists already,
free the newly read name.

The way we do this is to take a large chunk, allocating memory from
low addresses.  When you want to build a aymbol in the chunk you just
add chars above the current "high water mark" in the chunk.  When you
have finished adding chars, because you got to the end of the symbol,
you know how long the chars are, and you can create a new object.
Mostly the chars will not burst over the highest address of the chunk,
because you would typically expect a chunk to be (say) 100 times as
long as an average object.

In case that isn't clear, when we have enough chars to make up
the object, THEY ARE ALREADY CONTIGUOUS IN THE CHUNK (guaranteed)
so we just point to it where it lies.  No moving of chars is
needed and this is the second win: potentially long strings need
never be explicitly shuffled. Once an object is formed, it does not
change its address during its lifetime.

When the chars burst over a chunk boundary, we allocate a larger
chunk, and then copy the partly formed object from the end of the old
chunk to the beggining of the new larger chunk.  We then carry on
accreting characters to the end of the object as we normaly would.

A special macro is provided to add a single char at a time to a
growing object.  This allows the use of register variables, which
break the ordinary 'growth' macro.

Summary:
	We allocate large chunks.
	We carve out one object at a time from the current chunk.
	Once carved, an object never moves.
	We are free to append data of any size to the currently
	  growing object.
	Exactly one object is growing in an obstack at any one time.
	You can run one obstack per control block.
	You may have as many control blocks as you dare.
	Because of the way we do it, you can `unwind' a obstack
	  back to a previous state. (You may remove objects much
	  as you would with a stack.)
*/


/* Don't do the contents of this file more than once.  */

#ifndef __OBSTACKS__
#define __OBSTACKS__

#include <stdlib.h>
#include <memory.h>

struct _obstack_chunk		/* Lives at front of each chunk. */
{
  char  *limit;			/* 1 past end of this chunk */
  struct _obstack_chunk *prev;	/* address of prior chunk or NULL */
  char	contents[4];		/* objects begin here */
};

#if PROTO_OK
typedef struct obstack		/* control current object in current chunk */
{
  size_t chunk_size;		/* preferred size to allocate chunks in */
  struct _obstack_chunk* chunk;	/* address of current struct obstack_chunk */
  char	*object_base;		/* address of object we are building */
  char	*next_free;		/* where to add next char to current object */
  char	*chunk_limit;		/* address of char after current chunk */
  size_t t_size;		/* Temporary for some macros  */
  size_t alignment_mask;	/* Mask of alignment for each object. */
				/* User's fcn to allocate a chunk.  */
  struct _obstack_chunk *(*chunkfun) (size_t length);
  struct _obstack_chunk *	/* User's fcn to re-size a chunk.  */
    (*expandfun) (struct _obstack_chunk *chunk, size_t length);
  void (*freefun) (POINTER obj);/* User's function to free a chunk.  */
} Obstack, *ObstackP;

typedef struct _obstack		/* Access to void *object_base */
{
  size_t chunk_size;		/* preferred size to allocate chunks in */
  struct _obstack_chunk* chunk;	/* address of current struct obstack_chunk */
  void	*object_base;		/* address of object we are building */
  char	*next_free;		/* where to add next char to current object */
  char	*chunk_limit;		/* address of char after current chunk */
  size_t t_size;		/* Temporary for some macros  */
  size_t alignment_mask;	/* Mask of alignment for each object. */
				/* User's fcn to allocate a chunk.  */
  struct _obstack_chunk *(*chunkfun) (size_t length);
  struct _obstack_chunk *	/* User's fcn to re-size a chunk.  */
    (*expandfun) (struct _obstack_chunk *chunk, size_t length);
  void (*freefun) (POINTER obj);/* User's function to free a chunk.  */
} *_ObstackP;

/* Do the function-declarations after the structs
   but before defining the macros.  */

extern void obstack_strgrow (ObstackP obstk, char *data);

extern void _obstack_begin(ObstackP h, size_t size, int alignment,
      POINTER (*chunkfun)(size_t length),
      POINTER (*expandfun)(struct _obstack_chunk *chunk, size_t length),
      void (*freefun)(POINTER obj));

extern int _obstack_newchunk(ObstackP h, size_t length);

extern char *_obstack_free (ObstackP obstack, void *block);

extern void *_obstack_malloc(size_t length);
extern void *_obstack_realloc(struct _obstack_chunk *chunk, size_t length);

#else /* __cplusplus || __STDC__ */
typedef struct obstack		/* control current object in current chunk */
{
  size_t chunk_size;		/* preferred size to allocate chunks in */
  struct _obstack_chunk* chunk;	/* address of current struct obstack_chunk */
  char	*object_base;		/* address of object we are building */
  char	*next_free;		/* where to add next char to current object */
  char	*chunk_limit;		/* address of char after current chunk */
  size_t t_size;		/* Temporary for some macros  */
  size_t alignment_mask;	/* Mask of alignment for each object. */
				/* User's fcn to allocate a chunk.  */
  struct _obstack_chunk *(*chunkfun) ();
				/* User's fcn to re-size a chunk.  */
  struct _obstack_chunk * (*expandfun) ();
  void (*freefun) ();		/* User's function to free a chunk.  */
} Obstack, *ObstackP;

typedef struct _obstack		/* Access to void *object_base */
{
  size_t chunk_size;		/* preferred size to allocate chunks in */
  struct _obstack_chunk* chunk;	/* address of current struct obstack_chunk */
  void	*object_base;		/* address of object we are building */
  char	*next_free;		/* where to add next char to current object */
  char	*chunk_limit;		/* address of char after current chunk */
  size_t t_size;		/* Temporary for some macros  */
  size_t alignment_mask;	/* Mask of alignment for each object. */
				/* User's fcn to allocate a chunk.  */
  struct _obstack_chunk *(*chunkfun) ();
				/* User's fcn to re-size a chunk.  */
  struct _obstack_chunk * (*expandfun) ();
  void (*freefun) ();		/* User's function to free a chunk.  */
} *_ObstackP;


extern void obstack_strgrow ();

extern void _obstack_begin();

extern int _obstack_newchunk();

extern char * _obstack_free();

extern void *_obstack_malloc();
extern void *_obstack_realloc();

#endif /* __cplusplus || __STDC__ */

/* Non-ANSI C cannot really support alternative functions for these macros,
   so we do not declare them.  */

/* Pointer to beginning of object being allocated or to be allocated next.
   Note that this might not be the final address of the object
   because a new chunk might be needed to hold the final size.  */

#define obstack_base(h) (((_ObstackP)(h))->object_base)

/* Size for allocating ordinary chunks.  */

#define obstack_chunk_size(h) ((unsigned)((h)->chunk_size))

/* Pointer to next byte not yet allocated in current chunk.  */

#define obstack_next_free(h)	((h)->next_free)

/* Mask specifying low bits that should be clear in address of an object.  */

#define obstack_alignment_mask(h) ((h)->alignment_mask)

#define obstack_init(h) \
  _obstack_begin ((h), 0, 0, \
    obstack_chunk_alloc, obstack_chunk_realloc, obstack_chunk_free)

#define obstack_begin(h, size, alignment) \
  _obstack_begin ((h), (size), (alignment), \
    obstack_chunk_alloc, obstack_chunk_realloc, obstack_chunk_free)

#define obstack_1grow_fast(h,achar) (*((h)->next_free)++ = achar)

#define obstack_blank_fast(h,n) ((h)->next_free += (n))


#define obstack_object_size(h) \
 (unsigned) ((h)->next_free - (h)->object_base)

#define obstack_room(h)		\
 (unsigned) ((h)->chunk_limit - (h)->next_free)

#define obstack_grow(h,where,length)					\
( (h)->t_size = (length),						\
  (((h)->next_free + (h)->t_size > (h)->chunk_limit)			\
   ? _obstack_newchunk ((h), (h)->t_size) : 0),				\
  (void)memcpy ((h)->next_free, where, (h)->t_size),			\
  (h)->next_free += (h)->t_size)

#define obstack_grow0(h,where,length)					\
( (h)->t_size = (length),						\
  (((h)->next_free + (h)->t_size + 1 > (h)->chunk_limit)		\
   ? _obstack_newchunk ((h), (h)->t_size + 1) : 0),			\
  (void)memcpy ((h)->next_free, where, (h)->t_size),			\
  (h)->next_free += (h)->t_size,					\
  *((h)->next_free)++ = 0)

#define obstack_1grow(h,datum)						\
( (((h)->next_free + 1 > (h)->chunk_limit)				\
   ? _obstack_newchunk ((h), 1) : 0),					\
  *((h)->next_free)++ = (datum))

#define obstack_blank(h,length)						\
( (h)->t_size = (length),						\
  (((h)->next_free + (h)->t_size > (h)->chunk_limit)			\
   ? _obstack_newchunk ((h), (h)->t_size) : 0),				\
  (h)->next_free += (h)->t_size)

#define obstack_alloc(h,length)						\
 (obstack_blank ((h), (length)), obstack_finish ((h)))

#define obstack_copy(h,where,length)					\
 (obstack_grow ((h), (where), (length)), obstack_finish ((h)))

#define obstack_copy0(h,where,length)					\
 (obstack_grow0 ((h), (where), (length)), obstack_finish ((h)))

#define obstack_strcpy(h,where)						\
 (obstack_strgrow ((h), (where)), obstack_1grow(h,'\0'), obstack_finish ((h)))

#define obstack_finish(h)  						\
(_obstack_object_base = ((_ObstackP)(h))->object_base,			\
  (h)->next_free =							\
    (((((h)->next_free - (char *)(h)->chunk) + (h)->alignment_mask)	\
    & ~ (h)->alignment_mask) + (char *)(h)->chunk),			\
  ((h)->next_free > (h)->chunk_limit 					\
    ? ((h)->next_free = (h)->chunk_limit) : 0),				\
  (h)->object_base = (h)->next_free,					\
  _obstack_object_base)

#define obstack_free(h,obj)						\
( (h)->object_base = (char *)(obj),					\
  (((h)->object_base >= (char *)(h)->chunk &&				\
    (h)->object_base < (h)->chunk_limit)				\
   ? ((h)->next_free = (h)->object_base)				\
   : _obstack_free((h), (h)->object_base)))

extern void *_obstack_object_base;

#endif /* not __OBSTACKS__ */
