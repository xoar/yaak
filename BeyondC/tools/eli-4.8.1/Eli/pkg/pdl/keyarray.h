#ifndef KEYARRAY_H
#define KEYARRAY_H 
/* $Id: keyarray.h,v 1.4 1997/09/04 18:21:30 waite Exp $ */
/* Copyright 1992, The Regents of the University of Colorado */

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

#include "deftbl.h"

typedef struct KeyArrayStart {
  int size;
  DefTableKey Key[1];
} *KeyArray;

#define NoKeyArray (KeyArray)0
#define KeyArraySize(b) (b?b->size:0)

#if defined(__STDC__) || defined(__cplusplus)
extern KeyArray NewKeyArray(int n);
/* Create a array of definition table keys
 *    On entry-
 *       n=number of keys in the array
 *    On exit-
 *       NewKeyArray is an array of n "NoKey" values,
 *          indexed by the integers 0 through n-1 inclusive
 ***/

extern void StoreKeyInArray(KeyArray b, int i, DefTableKey k);
/* Store a definition table key into an array of keys
 *    On entry-
 *       b is the array into which the key is to be stored
 *       k is the key to be stored
 *    If i is a valid index for b then on exit-
 *       element i of b contains k
 *    Else on exit-
 *       b is unchanged
 ***/

extern DefTableKey FetchKeyFromArray(KeyArray b, int i);
/* Fetch a definition table key from an array of keys
 *    On entry-
 *       b is the array from which the key is to be fetched
 *       i is the index of the element to be fetched
 *    If i is a valid index for b then on exit-
 *       FetchKeyFromArray=key i of array b
 *    Else on exit-
 *       FetchKeyFromArray=NoKey
 ***/
#else
extern KeyArray NewKeyArray();
extern void StoreKeyInArray();
extern DefTableKey FetchKeyFromArray();
#endif
#endif
