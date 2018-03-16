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
/* $Id: depmod.h,v 1.2 1997/08/29 09:16:01 peter Exp $*/

#ifndef DEPMOD_H
#define DEPMOD_H

#define GetSymAttrPos(aid) ref_tab[aid].entry.attr.pos

#include "Types.h"

extern SLNODE *GetSymbOfProd (/* int pid, sno */);

extern int DPAttrIsDefined (/* int prodid; SLNODE *symptr; int attrid;*/);

extern void DPAttrSetDefined (/* int prodid; SLNODE *symptr; int attrid;*/);

extern void DPSetDepend ();
/*
	int prodid;
	SLNODE *tosymptr; int tosymatno;
	SLNODE *fromsymptr; fromsymatno;
	int kind;  dependency kind for non-gorto: 1 == direct
	int line;  source line
*/

extern int DPDependson (/*
	int pid;
	SLNODE *tosymptr; int tosymatno;
	SLNODE *fromsymptr; int fromsymatno;
*/);

extern int DSDependson (/* int sid, tosymatno, fromsymatno */);
extern void DSSetDepend (/* int sid, tosymatno, fromsymatno */);

#endif
