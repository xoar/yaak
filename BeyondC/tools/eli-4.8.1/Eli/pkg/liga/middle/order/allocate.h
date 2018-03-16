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
/* $Id: allocate.h,v 1.2 1997/08/29 09:16:01 peter Exp $ */

#ifndef ALLOCATE_H
#define ALLOCATE_H

/* redefinition of Malloc: */
#ifndef GORTO
#include "middle_mem.h"
#define Allocate(file,line,size) middle_tempMalloc (file,line,size)
#else
#include <X11/Intrinsic.h>
#define Allocate(file,line,size) XtMalloc(size)
#endif

#endif
