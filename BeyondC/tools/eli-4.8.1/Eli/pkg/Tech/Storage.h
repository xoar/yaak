#ifndef STORAGE_H
#define STORAGE_H

/* $Id: Storage.h,v 3.4 1997/11/03 09:16:31 mjung Exp $ */
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

typedef struct StorageRec{
   int size;	/* Number of bytes */
   int align;	/* Number that must divide the address */
   int top;	/* True if addressed by the last+1 location */
} *StorageRequired;

#define NoStorage ((StorageRequired)0)

#if defined(__STDC__) || defined(__cplusplus)
extern StorageRequired NewStorage(int size, int align, int top);
/* Create a new storage object
 *    On entry-
 *       size=size of the new object
 *       align=required divisor of the object's address
 *       top=FALSE if the lowest address must be aligned
 *           TRUE if the last+1 address must be aligned
 ***/

extern StorageRequired CopyStorage(StorageRequired a);
/* Create a new storage object equal to an existing storage object
 *    On entry-
 *       a=storage object to be copied
 ***/

extern StorageRequired ArrayStorage(int n, StorageRequired a);
/* Create a new storage object for an array of existing storage objects
 *    On entry-
 *       n=number of array elements
 *       a=element storage object
 ***/

extern int StorageSize(StorageRequired a);
/* Obtain the size of a storage object
 *    On exit-
 *       StorageSize=size of the storage object a
 ***/

extern int StorageAlignment(StorageRequired a);
/* Obtain the alignment of a storage object
 *    On exit-
 *       StorageAlignment=alignment of the storage object a
 ***/

extern int Concatenate(StorageRequired a, StorageRequired b);
/* Extend the storage requirement for an object by concatenating another object
 *    On entry-
 *       a describes the object to be extended
 *       b describes the object to be concatenated to a
 *    On exit-
 *       a describes the storage required by the extended object
 *       Concatenate=offset of the address of b from the address of a
 ***/

extern int Overlay(StorageRequired a, StorageRequired b);
/* Extend the storage requirement for an object by overlaying another object
 *    On entry-
 *       a describes the object to be extended
 *       b describes the object to be overlaid on a
 *    On exit-
 *       a describes the storage required by the extended object
 *       Overlay=offset of the address of b from the address of a
 ***/
#else
extern StorageRequired NewStorage();
extern StorageRequired CopyStorage();
extern StorageRequired ArrayStorage();
extern int StorageSize();
extern int StorageAlignment();
extern int Concatenate();
extern int Overlay();
#endif

#endif
