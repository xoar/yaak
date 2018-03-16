#ifndef SHOWEX_H
#define SHOWEX_H
/* $Id: showEx.h,v 1.2 2005/05/23 14:03:42 profw Exp $ */
/* Copyright 2005, The Regents of the University of Colorado
 *
 * This file is part of the Eli translator construction system.
 *
 * Eli is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 *
 * Eli is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Eli; see the file COPYING.  If not, write to the Free Software
 * Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "eliproto.h"

extern void InitExamples ELI_ARG((void));
/* Initialize the relations needed to output examples
 *   On entry-
 *     LALR(1) analysis is complete
 *     Reductions by chain productions have not been eliminated
 *     Shift-reduce optimizations have not been introduced
 *   On exit-
 *     PrintExample may be invoked
 ***/

extern void PrintExample ELI_ARG((int S, long T, long *C));
/* Print derivations leading to a conflict
 *   On entry-
 *     InitExamples has been executed
 *     S is the state in which the conflict occurs
 *     T=1 for a reduce-reduce conflict
 *       2 for a shift-reduce conflict
 *     C is the conflict set
 ***/

#endif
