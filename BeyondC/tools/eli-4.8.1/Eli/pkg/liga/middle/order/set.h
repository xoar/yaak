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
/* $Id: set.h,v 4.2 1997/08/29 09:16:01 peter Exp $ */

#ifndef SET_H
#define SET_H

/* only imported by visit.c (and Types.h for type BITVECTOR) */

/********************************************************
*       file: set.h                                     *
*       contains macros, typedefinitions, and external  *
*	functions declarations for set operations 	*
********************************************************/

#include "bool.h"

typedef unsigned int *BITVECTOR;

extern bool isemptyset();
extern bool issubset();
extern bool ismemberset();
extern void addtoset();
extern void delfromset();
extern void copyset();
extern void unionset();
extern void diffset();
extern BITVECTOR mkemptyset();

#ifdef GORTO
extern bool dep_is_subset();
extern void copy_dep_to_set();
extern void dep_unionset();
#endif

#endif
