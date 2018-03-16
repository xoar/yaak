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
/* $Id: bottomup.c,v 4.1 1997/08/29 07:55:18 peter Exp peter $ */

#include <string.h>
#include "global.h"
#include "LIGA.h"
#include "LIGAMacros.h"
#include "ligaconsts.h"

#include "bottomup.h"

int BottomUpVisits;

void DecideBottomUp (AE)
	AttrEval	AE;
/*
Bottom up visit-procedures are to be generated iff first Def is a
Typedef named TNBUMARK generated by order
BottomUpVisits is set
*/
{	Def	def;

BottomUpVisits = FALSE;
if (emptySEQDef (defseqOfAttrEval(AE))) return;
retrievefirstSEQDef (defseqOfAttrEval(AE), def);
if (typeof(def) != KTypedef) return;
if (strcmp (dnameOfDef (def), TNBUMARK) == 0)
	BottomUpVisits = TRUE;
}/* DecideBottomUp */