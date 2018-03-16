#ifndef MATCH_H
#define MATCH_H

/* $Id: match.h,v 1.5 1999/11/29 08:16:47 tony Exp $ */
/* Keyword matching module interface */
/* Copyright 1992, The Regents of the University of Colorado */

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

#include "eliproto.h"

extern char match ELI_ARG((char *v));
/* Check whether a string is in a given set of tokens
 *    On entry-
 *       v addresses the string to be matched
 *    If the string matched a token completely then on exit-
 *       match=1
 *    Else on exit-
 *       match=0
 ***/

#endif
