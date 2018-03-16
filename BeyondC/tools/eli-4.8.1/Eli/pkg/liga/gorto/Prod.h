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
/* $Id: Prod.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Prod/Prod.h					*
 *									*
 *	CONTENTS:	Shared Header-File of the directory Prod	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


typedef struct {
	SLNODE		*node1, *node2;
	ATTRENTRY	*ae1, *ae2;
	DEPENDENCY	*dep;
	DETAIL		*det;
} tProdDepSelection;

typedef struct {
	SLNODE		*node;
	ATTRENTRY	*ae;
	Position	y;
} tProdAttrSelection;

typedef struct {
	SLNODE		*node;
} tProdSymbSelection;

typedef struct {
	enum {
		ProdNothing, 
		ProdDep, ProdAttr, ProdSymb
	} type;

	union {
		tProdDepSelection	dep;
		tProdAttrSelection	attr;
		tProdSymbSelection	symb;
	} detail;
} tProdSelection;


/************************************************************************
 *			       ProdCreate.c				*
 ************************************************************************/

EXTERN void ProdCreateNew();
	/* int	pid;		*/

EXTERN void ProdUpdateState();
	/* PRODENTRY	*prod;	*/

EXTERN void ProdCloseCB();
	/* Callback		*/

EXTERN void ProdCloseAllCB();
	/* Callback		*/


/************************************************************************
 *				ProdDep.c				*
 ************************************************************************/

EXTERN Boolean DepRemoved;

EXTERN void ProdDrawDep();
	/* Window	win;		*/
	/* Region	reg;		*/
	/* PRODENTRY	*prod;		*/

EXTERN Boolean ProdDepSelected();
	/* PRODENTRY	*prod;		*/
	/* Position	x,y;		*/
	/* Boolean	only_marked;	*/


/************************************************************************
 *				ProdDraw.c				*
 ************************************************************************/

EXTERN void ProdComputeSize();
	/* PRODENTRY	*prod;		*/

EXTERN void ProdComputeWindowSize();
	/* PRODENTRY	*prod;		*/
	/* Dimension	*width_return;	*/
	/* Dimension	*height_return;	*/

EXTERN void ProdResizeCB();
	/* Callback			*/

EXTERN void ProdRedrawCB();
	/* Callback			*/


/************************************************************************
 *				ProdMenu.c				*
 ************************************************************************/

EXTERN void ProdCreateMenu();
	/* Widget	father;		*/


/************************************************************************
 *			       ProdSelect.c				*
 ************************************************************************/

EXTERN tProdSelection ProdSelection;
EXTERN tProdAttrSelection ProdMarkedAttr;

EXTERN void ProdSelectCB();
	/* Callback		*/


/************************************************************************
 *			       ProdSymbol.c				*
 ************************************************************************/

#define ALL_SPACE	10000

EXTERN void ProdSortAttributes();
	/* SYMBENTRY		*symb;	*/

EXTERN void ProdComputeAttrSpaces();
	/* SYMBENTRY		*symb;	*/

EXTERN void ProdComputeAttrSizes();
	/* SYMBENTRY		*symb;	*/

EXTERN void ProdComputeSymbolSize();
	/* SYMBENTRY		*symb;	*/

EXTERN void ProdRedrawAttr();
	/* tProdAttrSelection	attr;	*/

EXTERN void ProdDrawSymbol();
	/* Window		win;	*/
	/* Region		reg;	*/
	/* SLNODE		*nd;	*/


/************************************************************************
 *				ProdUtil.c				*
 ************************************************************************/

EXTERN String ProdStateLabel();
	/* PRODENTRY	*prod;	*/

EXTERN Boolean ProdSearchCycle();
	/* PRODENTRY	*prod;	*/
	/* SLNODE	**node;	*/
	/* ATTRENTRY	**ae;	*/

EXTERN void ProdResizeWindow();
	/* PRODENTRY	*prod;	*/
