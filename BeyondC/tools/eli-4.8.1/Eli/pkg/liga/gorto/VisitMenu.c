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
/* $Id: VisitMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: VisitMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitMenu.c				*
 *									*
 *	CONTENTS:	Implementation of visit-sequence menu		*
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
#include "Prod.h"
#include "Main.h"
#include "Graph.h"
#include "Visit.h"

#include <X11/StringDefs.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>


/************************************************************************
 *		    Widgets of the visit-sequence menu			*
 ************************************************************************/

PRIVATE Widget	VisitSeqMenu,		/* Surrounding simple menu widget */
		ItemClose,		/* Close item */
		ItemCloseAll,		/* Close all item */
		ItemNoLife,		/* Don't show lifetimes item */
		ItemFixElem,		/* Fix element position */
		ItemFreeVS;		/* Remove visit-sequence constaints */

PRIVATE PRODENTRY *prod;


/************************************************************************
 *			     VisitMenuPopupCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void VisitMenuPopupCB (w, client_data, call_data)
	Widget  w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	if (DidOfGraphMenu < 0 || DidOfGraphMenu > max_entry ||
	    ref_tab[DidOfGraphMenu].etag != PROD)
	{
		XtSetSensitive (ItemClose,   False);
		XtSetSensitive (ItemNoLife,  False);
		XtSetSensitive (ItemFixElem, False);
		XtSetSensitive (ItemFreeVS,  False);
	}
	else
	{
		prod = & PE(DidOfGraphMenu);

		XtSetSensitive (ItemClose,   True);
		XtSetSensitive (ItemNoLife,  prod->vs->marked_elem != NULL);
		XtSetSensitive (ItemFixElem, VisitMarkedElem.prod == prod);
		XtSetSensitive (ItemFreeVS,  prod->state & S_ARRANGED);
	}
}


/************************************************************************
 *			      VisitFixElemCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void VisitFixElemCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	PRIVATE char comment[100];

      /* Specify the arrange comment */
	sprintf (comment, "Fix %s in visit-sequence for rule %s",
			  VisitElemString (VisitMarkedElem.elem),
			  prod->prod_def->dname);
	ArrangeComment (comment);

      /* Introduce arrange options to fix the elements position */
	if (VisitMarkedElem.last)
		VisitArrange (prod, VisitMarkedElem.elem, 
				    VisitMarkedElem.last);
	if (VisitMarkedElem.elem->next)
		VisitArrange (prod, VisitMarkedElem.elem->next,
				    VisitMarkedElem.elem);

      /* Unmark the marked element */
	VisitMarkedElem.prod = NULL;
	VisitMarkedElem.elem = MoveRangeStartElem = MoveRangeEndElem = NULL;

      /* Redisplay the windows */
	UpdateVisitSequence (prod);
	RedisplayWidget (prod->vs->vsar->widget);
}


/************************************************************************
 *			      VisitFreeVSCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void VisitFreeVSCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	DEPENDENCY	*dep;
	DEP_VECTOR	*dep_row;
	DETAIL		*det;
	DET_VECTOR	*det_row;

      /* Remove all arrange options for this rule */
	dep_row = & prod->dp[prod->check_row];
	det_row = & prod->dp_detail[prod->check_row];
	for (; dep_row >= & prod->dp[0]; dep_row--, det_row--)
	{
		dep = & (*dep_row)[prod->check_row];
		det = & (*det_row)[prod->check_row];
		for (; dep >= & (*dep_row)[0]; dep --, det --)
		{
			if ((*dep & T_MASK) == T_ARR)
			{
				RemoveArrangeNode (det->arrange.node);
				DepRemoved = True;
				*dep = 0;
			}
		}
	}
	
      /* Update the production state */
	prod->state &= ~S_ARRANGED;
	ProdUpdateState (prod);

      /* Redisplay the windows */
	UpdateVisitSequence (prod);
	RedisplayWidget (prod->vs->vsar->widget);
	if (prod->par) RedisplayWidget (prod->par->widget);
}


/************************************************************************
 *			     VisitCreateMenu				*
 ************************************************************************/

PUBLIC void VisitCreateMenu (father)
	Widget father;
{
	int	n = 0;
	Arg	args[1];
	Widget	line;

	VisitSeqMenu = CreateMenu ("visitSeqMenu", father);
	XtAddCallback (VisitSeqMenu, XtNpopupCallback,
			VisitMenuPopupCB, (XtPointer) NULL);

	CreateMItem (ItemClose,   "close",   VisitSeqMenu,VisitCloseCB,   NULL);
	CreateMItem (ItemCloseAll,"closeAll",VisitSeqMenu,VisitCloseAllCB,NULL);
	CreateMLine (line,        "line",    VisitSeqMenu);
	CreateMItem (ItemNoLife, "noLifetimes", VisitSeqMenu,
			VisitUnmarkLifetimeCB, NULL);
	CreateMLine (line,        "line",    VisitSeqMenu);
	CreateMItem (ItemFixElem, "fixElem", VisitSeqMenu,VisitFixElemCB, NULL);
	CreateMItem (ItemFreeVS,  "freeVisitSeq", VisitSeqMenu,
			VisitFreeVSCB, NULL);
}
