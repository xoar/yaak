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
/* $Id: Visit.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Visit/Visit.h					*
 *									*
 *	CONTENTS:	Shared Header-File of the directory Visit	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


typedef struct {
	PRODENTRY	*prod;
	VSPTR		elem, last;
	int		no;
} tVisitElemSelection;


#define IS_LEAVE(elem)	((elem)->vscls == VSVISIT && \
			 (elem)->vsinfo.visit.vssno == 0)
#define IS_VISIT(elem)	((elem)->vscls == VSVISIT && \
			 (elem)->vsinfo.visit.vssno != 0)


/************************************************************************
 *			      VisitCreate.c				*
 ************************************************************************/

EXTERN void VisitCreateNew();
	/* int	pid;	*/

EXTERN void VisitCloseCB();
	/* Callback	*/

EXTERN void VisitCloseAllCB();
	/* Callback	*/


/************************************************************************
 *			       VisitDraw.c				*
 ************************************************************************/

EXTERN void VisitComputeSize();
	/* PRODENTRY	*prod;		*/

EXTERN void VisitComputeWindowSize();
	/* PRODENTRY	*prod;		*/
	/* Dimension	*width_return;	*/
	/* Dimension	*height_return;	*/

EXTERN void VisitResizeCB();
	/* Callback			*/

EXTERN void VisitRedrawCB();
	/* Callback			*/


/************************************************************************
 *			       VisitLife.c				*
 ************************************************************************/

EXTERN void VisitUpdateProdLifes();
	/* PRODENTRY	*prod;		*/

EXTERN void VisitComputeLifetimes();

EXTERN void VisitUnmarkLifetimeCB();
	/* Callback			*/

EXTERN void VisitMarkLifetime();
	/* SYMBENTRY	*symb;		*/
	/* ATTRENTRY	*ae;		*/

EXTERN void VisitDrawLifes();
	/* Window	win;		*/
	/* Region	reg;		*/
	/* PRODENTRY	*prod;		*/


/************************************************************************
 *			       VisitMenu.c				*
 ************************************************************************/

EXTERN void VisitCreateMenu();
	/* Widget	father;		*/


/************************************************************************
 *			      VisitSelect.c				*
 ************************************************************************/

EXTERN tVisitElemSelection VisitSelection, VisitMarkedElem;
EXTERN VSPTR MoveRangeStartElem, MoveRangeEndElem;

EXTERN void VisitSelectCB();
	/* Callback	*/


/************************************************************************
 *			       VisitUtil.c				*
 ************************************************************************/

EXTERN SLNODE *SymbnoToNode();
	/* PRODENTRY	*prod;		*/
	/* int		symb_no;	*/

EXTERN String VisitElemString();
	/* VSPTR	vselem;		*/

EXTERN Boolean ElemDepends();
	/* PRODENTRY	*prod;		*/
	/* VSPTR	elem1, elem2;	*/

EXTERN Boolean ElemCritical();
	/* VSPTR	elem, last;	*/

EXTERN void VisitArrange();
	/* PRODENTRY	*prod;		*/
	/* VSPTR	elem, after;	*/
