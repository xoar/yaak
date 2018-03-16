static char *rscid = "$Id: Storage.c,v 3.4 1997/11/03 09:16:31 mjung Exp $";
/* Copyright 1989, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include <stdlib.h>
#include "Storage.h"

/***/
StorageRequired
#if defined(__STDC__) || defined(__cplusplus)
NewStorage(int size, int align, int top)
#else
NewStorage(size, align, top) int size, align, top;
#endif
/* Create a new storage object
 *    On entry-
 *       size=size of the new object
 *       align=required divisor of the object's address
 *       top=FALSE if the lowest address must be aligned
 *           TRUE if the last+1 address must be aligned
 ***/
{ StorageRequired s;

   s = (StorageRequired)malloc(sizeof(struct StorageRec));
   s->size = size; s->align = align; s->top = top;
   return s;
}

/***/
StorageRequired
#if defined(__STDC__) || defined(__cplusplus)
CopyStorage(StorageRequired a)
#else
CopyStorage(a) StorageRequired a;
#endif
/* Create a new storage object equal to an existing storage object
 *    On entry-
 *       a=storage object to be copied
 ***/
{ StorageRequired s;

   if (a == NoStorage) return NoStorage;

   s = (StorageRequired)malloc(sizeof(struct StorageRec));
   *s = *a;
   return s;
}

/***/
StorageRequired
#if defined(__STDC__) || defined(__cplusplus)
ArrayStorage(int n, StorageRequired a)
#else
ArrayStorage(n,a) int n; StorageRequired a;
#endif
/* Create a new storage object for an array of existing storage objects
 *    On entry-
 *       n=number of array elements
 *       a=element storage object
 ***/
{ StorageRequired s;
   struct StorageRec t;

   if (a == NoStorage) return NoStorage;

   s = (StorageRequired)malloc(sizeof(struct StorageRec));
   *s = t = *a;
   t.size = 0;
   (void)Concatenate(s, &t);
   s->size *= n;
   return s;
}

/***/
int
#if defined(__STDC__) || defined(__cplusplus)
StorageSize(StorageRequired a)
#else
StorageSize(a) StorageRequired a;
#endif
/* Obtain the size of a storage object
 *    On exit-
 *       StorageSize=size of the storage object a
 ***/
{ if (a != NoStorage) return a->size;
   return 0;
}

/***/
int
#if defined(__STDC__) || defined(__cplusplus)
StorageAlignment(StorageRequired a)
#else
StorageAlignment(a) StorageRequired a;
#endif
/* Obtain the alignment of a storage object
 *    On exit-
 *       StorageAlignment=alignment of the storage object a
 ***/
{ if (a != NoStorage) return a->align;
   return 1;
}

/***/
int
#if defined(__STDC__) || defined(__cplusplus)
Concatenate(StorageRequired a, StorageRequired b)
#else
Concatenate(a, b) StorageRequired a, b;
#endif
/* Extend the storage requirement for an object by concatenating another object
 *    On entry-
 *       a describes the object to be extended
 *       b describes the object to be concatenated to a
 *    On exit-
 *       a describes the storage required by the extended object
 *       Concatenate=offset of the address of b from the address of a
 ***/
{ int offset;

   if (a == NoStorage || b == NoStorage) return 0;

   if (a->top == b->top) {
      offset = ((a->size+(b->align-1)) / b->align)*b->align;
      a->size = offset+b->size;
   } else {
      offset = ((a->size+b->size+(b->align-1)) / b->align)*b->align;
      a->size = offset;
   }
   if (a->align < b->align) a->align = b->align;
   if (a->top) return -offset; else return offset;
}

/***/
int
#if defined(__STDC__) || defined(__cplusplus)
Overlay(StorageRequired a, StorageRequired b)
#else
Overlay(a, b) StorageRequired a, b;
#endif
/* Extend the storage requirement for an object by overlaying another object
 *    On entry-
 *       a describes the object to be extended
 *       b describes the object to be overlaid on a
 *    On exit-
 *       a describes the storage required by the extended object
 *       Overlay=offset of the address of b from the address of a
 ***/
{ int offset;
   StorageRequired tmp;

   if (a == NoStorage || b == NoStorage) return 0;

   if (a->top == b->top) offset = 0;
   else { tmp = a; tmp->size = 0; offset = Concatenate(tmp,b); b = tmp; }
   if (a->size < b->size) a->size = b->size;
   if (a->align < b->align) a->align = b->align;
   return offset;
}
