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
/*$Id: exp_prot.h,v 4.1 1997/08/29 09:09:06 peter Exp $*/

#ifndef EXP_PROTOCOL_H
#define EXP_PROTOCOL_H
#include <stdio.h>
#include "exp_types.h"

#if defined (__cplusplus) || defined(__STDC__)
extern void prot_position(FILE *prot, int line, int col);
#else
extern void prot_position();
#endif

#if defined (__cplusplus) || defined(__STDC__)
extern void prot_rule(FILE *prot, int pid);
#else
extern void prot_rule();
#endif

#endif
