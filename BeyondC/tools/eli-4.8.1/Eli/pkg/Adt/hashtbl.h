#ifndef HASHTBL_H
#define HASHTBL_H 

/* $Id: hashtbl.h,v 1.1 2008/06/16 19:00:51 profw Exp $ */
/* Hash list module interface
   Copyright 2008, The Regents of the University of Colorado */

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

#include <stdlib.h>	/* To get size_t */
#include "hash.h"
#include "deftbl.h"
#include "eliproto.h"

typedef struct HashElt {	/* Properties of a hash list entry */
  struct HashElt *next;		  /* The next hash table entry */
  ub4 selector;			  /* Which hash code */
  void *keylist;		  /* The list of collisions */
} *HashList;

extern int hashFind ELI_ARG((ub4 c, HashList l, HashList *r));
/* Obtain an element for a specific hash code
 *   On entry-
 *     c=Code sought
 *     l points to the header of the list in which c is sought
 *   If the code does not have an associated value then on exit-
 *     find=false
 *     *r points to the element that would precede c
 *   Else on exit-
 *     find=true
 *     *r points to the element containing c
 ***/

#endif
