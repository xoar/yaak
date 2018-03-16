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
/* $Id: SymbMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: SymbMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbMenu.c					*
 *									*
 *	CONTENTS:	Implementation of the symbol menu		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

       /************************ WARNING ************************ 
	*							*
 	*	This file depends on the Athena Widget Set	*
 	*	of X Version 11, Release 4			*
	*							*
	*********************************************************/

#include "Misc.h"
#include "Create.h"
#include "Visit.h"
#include "Graph.h"
#include "Popup.h"
#include "Symb.h"

#include <X11/StringDefs.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>


/************************************************************************
 *			Widgets of the symbol menu			*
 ************************************************************************/

PRIVATE Widget	SymbMenu, 		/* Surrounding simple menu widget */
		ItemClose,		/* Close item */
		ItemCloseAll,		/* Close all item */
		ItemFreeAttr,		/* Free attribute partition item */
		ItemForcePart,		/* Force partition item */
		ItemProductions,	/* Select production item */
		ItemLifetime;		/* Show attribute lifetime item	*/

PRIVATE SYMBENTRY *symb;

		
/************************************************************************
 *		  	     SymbMenuPopupCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void	SymbMenuPopupCB (w, client_data, call_data)
	Widget  w;
	XtPointer client_data;
	XtPointer call_data;
{
	Arg args[1];

	XtSetArg (args[0], XtNleftBitmap, None);

	if (DidOfGraphMenu < 0 || DidOfGraphMenu > max_entry ||
	    ref_tab[DidOfGraphMenu].etag != SYMB)
	{
		XtSetSensitive (ItemClose,       False);
		XtSetSensitive (ItemFreeAttr,    False);
		XtSetSensitive (ItemForcePart,   False);
		XtSetSensitive (ItemProductions, False);
		XtSetSensitive (ItemLifetime,    False);
	}
	else
	{
		symb = & SE(DidOfGraphMenu);

		XtSetSensitive (ItemClose,       True);
		XtSetSensitive (ItemFreeAttr,    SymbMarkedAttr.symb == symb);
		XtSetSensitive (ItemForcePart,   True);
		XtSetSensitive (ItemProductions, True);
		XtSetSensitive (ItemLifetime,    SymbMarkedAttr.symb == symb);

		if (symb->state & S_FORCED)
			XtSetArg (args[0], XtNleftBitmap, CheckMarkBitmap);
	}
	XtSetValues (ItemForcePart, args, 1);
}


/************************************************************************
 *				FreeAttrCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void FreeAttrCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	UnarrangeAttr (SymbMarkedAttr.ae);
	SymbMarkedAttr.symb = NULL;
	SymbMarkedAttr.ae   = NULL;
	SymbRecomputePartition (symb);
}


/************************************************************************
 *			       SymbForceCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void SymbForceCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	if (symb->state & S_FORCED)
	{
		ATTRENTRY *ae;

		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
			UnarrangeAttr (ae);
		symb->state &= ~(S_ARRANGED|S_FORCED);
	}
	else
	{
		ArrangeForced (symb);
		symb->state |= S_FORCED;
	}
	SymbRecomputePartition (symb);
}


/************************************************************************
 *				LifetimeCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void LifetimeCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
      /* Mark the last use of this attribute in all productions */
	VisitMarkLifetime (symb, SymbMarkedAttr.ae);

      /* Try to show the last BmNF use */
	if (SymbMarkedAttr.ae->life_node == NULL)
		Message (DidOfGraphMenu, Res.no_bmnf_msg);
	else
		VisitCreateNew (SymbMarkedAttr.ae->life_node->pid);
}


/************************************************************************
 *			      SymbCreateMenu				*
 ************************************************************************/

PUBLIC void SymbCreateMenu (father)
	Widget father;
{
	int	n = 0;
	Arg	args[1];
	Widget	line;

	SymbMenu = CreateMenu ("symbolMenu", father);
	XtAddCallback (SymbMenu, XtNpopupCallback,
			SymbMenuPopupCB, (XtPointer) NULL);

	CreateMItem (ItemClose,    "close",    SymbMenu, SymbCloseCB,    NULL);
	CreateMItem (ItemCloseAll, "closeAll", SymbMenu, SymbCloseAllCB, NULL);
	CreateMLine (line,         "line",     SymbMenu);

	CreateMItem (ItemFreeAttr,  "freeAttr", SymbMenu, FreeAttrCB,  NULL);
	CreateMItem (ItemForcePart, "force",    SymbMenu, SymbForceCB, NULL);
	CreateMLine (line,          "line",     SymbMenu);

	CreateMItem (ItemProductions, "productions",SymbMenu, SymbProdCB, NULL);
	CreateMItem (ItemLifetime,    "lifetime",   SymbMenu, LifetimeCB, NULL);
}
