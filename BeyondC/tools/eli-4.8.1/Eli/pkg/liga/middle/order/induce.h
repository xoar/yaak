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
/* $Id: induce.h,v 1.4 1997/08/29 09:16:01 peter Exp $ */
#include "eliproto.h"

extern void ruletransitive ELI_ARG((int));    /* two versions: 1 for order, 1 for gorto */
extern void distributedeps ELI_ARG((int,int*)); /* two versions: 1 for order, 1 for gorto */
extern void transitiveclosure ELI_ARG((void)); /* two versions: 1 for order, 1 for gorto */
extern void cons_init_ds ELI_ARG((void));      /* one version for both */
#ifndef GORTO
extern void distributealldeps ELI_ARG((void)); /* only for order */
#endif

