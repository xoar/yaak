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
/* $Id: bottomup.h,v 4.5 1997/08/29 09:16:01 peter Exp $ */

#ifndef BOTTOMUP_H
#define BOTTOMUP_H

#include "bool.h"
#include "eliproto.h"

extern void ChkBUComp (/* Call ca */ );
/*
on entry:	ca is an attr ASSIGN
on exit:	if ca is marked BOTTOMUP the attr property is set
		and TREE_BOTTOM_UP is set
*/

extern int lidoposition(/* int rulepos, pid */);
#define NONE (-1)

extern void InduceBUAttrs ();

extern int NeedsCode ELI_ARG((Call));

extern void BUChkProds ();

extern void GenTreeDeps (/*AttrEval ae */);

extern void ChkBUInGenTrees ();

#endif
