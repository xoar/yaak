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
/* $Id: Symb.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Symb/Symb.h					*
 *									*
 *	CONTENTS:	Shared Header-File of the directory Symb	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


#define CLASS(ae) ((ae)->attr_def->class)

typedef struct {
	ATTRENTRY	*ae1, *ae2;
	DEPENDENCY	*dep;
	DETAIL		*det;
} tSymbDepSelection;

typedef struct {
	ATTRENTRY	*ae;
	SYMBENTRY	*symb;
	Position	y;
} tSymbAttrSelection;

typedef struct {
	enum {
		SymbNothing, SymbDep, SymbAttr
	} type;

	union {
		tSymbDepSelection	dep;
		tSymbAttrSelection	attr;
	} detail;
} tSymbSelection;

	
	
/************************************************************************
 *			       SymbAttrs.c				*
 ************************************************************************/

EXTERN Boolean AttrAfter();
	/* ATTRENTRY	*a1, *a2;		*/

EXTERN void SymbRecomputePartition();
	/* SYMBENTRY	*symb;			*/

EXTERN void MoveAttr();
	/* SYMBENTRY	*symb;			*/
	/* ATTRENTRY	*from, *to;		*/

EXTERN void AppendFrontPartition();
	/* SYMBENTRY	*symb;			*/
	/* ATTRENTRY	*content, *before;	*/

EXTERN void AppendRearPartition();
	/* SYMBENTRY	*symb;			*/
	/* ATTRENTRY	*content, *after;	*/

EXTERN void PerformSplit();
	/* SYMBENTRY	*symb;			*/
	/* ATTRENTRY	*with, *after;		*/
	/* ATTRENTRY	*before;		*/

EXTERN void SplitPartition();
	/* SYMBENTRY	*symb;			*/
	/* ATTRENTRY	*with, *after;		*/

EXTERN void ArrangeForced();
	/* SYMBENTRY	*symb;			*/

EXTERN void SymbMarkCriticalPath();
	/* SYMBENTRY	*symb;			*/


/************************************************************************
 *			       SymbCreate.c				*
 ************************************************************************/

EXTERN void SymbCloseCB();
	/* Callback		*/

EXTERN void SymbCloseAllCB();
	/* Callback		*/

EXTERN void SymbCreateNew();
	/* int	sid;		*/

EXTERN void SymbUpdateState();
	/* SYMBENTRY 	*symb;	*/


/************************************************************************
 *				SymbDep.c				*
 ************************************************************************/

EXTERN void SymbDrawDep();
	/* Window	win;		*/
	/* Region	reg;		*/
	/* SYMBENTRY	*symb;		*/

EXTERN Boolean SymbDepSelected();
	/* SYMBENTRY	*symb;		*/
	/* Position	x, y;		*/
	/* Boolean	only_marked;	*/


/************************************************************************
 *				SymbDraw.c				*
 ************************************************************************/

EXTERN void SymbComputeWindowSize();
	/* SYMBENTRY	*symb;		*/
	/* Dimension	*width_return;	*/
	/* Dimension	*height_return;	*/

EXTERN void SymbResizeCB();
	/* Callback			*/

EXTERN void SymbRedrawAttr();
	/* tSymbAttrSelection	attr;	*/

EXTERN void SymbRedrawCB();
	/* Callback                     */


/************************************************************************
 *				SymbMenu.c				*
 ************************************************************************/

EXTERN void SymbCreateMenu();
	/* Widget	father;		*/


/************************************************************************
 *			       SymbSelect.c				*
 ************************************************************************/

EXTERN tSymbSelection SymbSelection;
EXTERN tSymbAttrSelection SymbMarkedAttr;
EXTERN Boolean SplitPending;
EXTERN ATTRENTRY *SplitAfter;

EXTERN void SymbSelectCB();
	/* Callback	*/


/************************************************************************
 *				SymbUtil.c				*
 ************************************************************************/

EXTERN void InitSAR();
	/* SYMBENTRY	*symb;	*/

EXTERN String SymbStateLabel();
	/* SYMBENTRY	*symb;	*/

EXTERN Boolean SymbSearchCycle();
	/* SYMBENTRY	*symb;	*/
	/* ATTRENTRY	**ae;	*/


/************************************************************************
 *				SymbProd.c				*
 ************************************************************************/

EXTERN void SymbProdCB();
	/* Callback	*/
