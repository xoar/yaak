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
/* $Id: ProdSectList.h,v 1.2 1997/08/29 07:54:24 peter Exp $ */
/* Copyright, 1995, AG-Kastens, University Of Paderborn  */

#ifndef _PRODLIST_H
#define _PRODLIST_H

#include "VoidPtrList.h"

/* adaption of pointer lists to VoidPtrList implementation: */
typedef VoidPtrList ProdSectPtrList;
#define NULLProdSectPtrList NULLVoidPtrList
#define HeadProdSectPtrList(l) ((ProdSectPtr)(HeadVoidPtrList(l)))
#define TailProdSectPtrList(l) TailVoidPtrList(l)
#define ConsProdSectPtrList(e,l) ConsVoidPtrList((VoidPtr)e, l)

/* the number of sections for each production context (visits to it): */
typedef struct {
	Prod	proddef;
	int	sectno;
} ProdSect, *ProdSectPtr;

extern ProdSectPtrList	prodsectlist;

#endif
