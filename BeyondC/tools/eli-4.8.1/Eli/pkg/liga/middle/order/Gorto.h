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
/* $Id: Gorto.h,v 4.3 1997/08/29 09:16:01 peter Exp $ */

#ifndef GORTO_H
#define GORTO_H

/* ===================================================================
 * 		order/Gorto.h
 * entities defined in order modules, exported to Gorto
 * included only by Gorto
 * ===================================================================
*/
#include "Types.h"

/************************************************************************
 *			  Variable declarations				*
 ************************************************************************/

extern ALLENTRIES *ref_tab;	/* the reference table of symbols,
				 * productios, and attributes indexed by did */
extern int max_entry;	/* the maximum did used	 */
extern int min_entry;	/* the minimum did used */
extern int MaxRhsLen;   /* the maximum length of rule right hand sides */
extern int graphstate;	/* the state of graphs	 */

extern AttrEval ISexp;

extern bool TREE_BOTTOM_UP, TREE_COMPLETE;

/************************************************************************
 *				  Macros				*
 ************************************************************************/

extern void cons_init_dp(); /* from initdp.c */
extern void check_cycle();  /* from initdp.c */
extern void GenTreeDeps (); /* from bottomup.c */

extern void cons_init_ds(); /* from induce.c */
extern void transitiveclosure(); /* from induce.c */
extern void ruletransitive(); /* from induce.c */
extern void distributedeps(); /* from induce.c */
extern void InduceBUAttrs (); /* from bottomup.c */

extern void partit(); /* from part.c */
extern void symbpartition(); /* from part.c */
extern void BUPartition(); /* from part.c */
extern void BUChkProds (); /* from bottomup.c */
extern void ChkBUInGenTrees (); /* from bottomup.c */

extern void rulevisitsequence (); /* from visit.c */
extern void visitsequence (); /* from visit.c */
extern void write_dataStruct (); /* from visit.c */

extern Symb lookupSymbByName(); /* from option.c */
extern Prod lookupProdByName(); /* from option.c */

#endif
