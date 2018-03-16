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
/* $Id: ProdMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: ProdMenu.c,v 4.2 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdMenu.c					*
 *									*
 *	CONTENTS:	Implementation of the rule menu			*
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

/* This file implements the creation of the rule menu and some of the
 * callbacks attached to menu items of the rule menu.
 */

#include "Misc.h"
#include "Create.h"
#include "Visit.h"
#include "Graph.h"
#include "Prod.h"

#include <X11/StringDefs.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>


/************************************************************************
 *		       The Widgets of the rule menu			*
 ************************************************************************/

PRIVATE Widget	RuleMenu,	/* Surrounding simple menu widget */
		ItemClose,	/* Close item */
		ItemCloseAll,	/* Close all item */
		ItemFollow,	/* Follow marked dependencies item */
		ItemVisitSeq;	/* Show visit-sequence item */

PRIVATE PRODENTRY *prod;


/************************************************************************
 *	 		     ProdMenuPopupCB				*
 ************************************************************************/

/* This callback is called immediately before the production menu is
 * popped up. It determines the surrounding production context and
 * sets the sensitive state of the menu items.
 */

/*ARGSUSED*/
PRIVATE void ProdMenuPopupCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	if (DidOfGraphMenu < 0 || DidOfGraphMenu > max_entry ||
	    ref_tab[DidOfGraphMenu].etag != PROD)
	{
		XtSetSensitive (ItemClose,    False);
		XtSetSensitive (ItemFollow,   False);
		XtSetSensitive (ItemVisitSeq, False);
	}
	else
	{
		prod = & PE(DidOfGraphMenu);

		XtSetSensitive (ItemClose,    True);
		XtSetSensitive (ItemFollow,   True);
		XtSetSensitive (ItemVisitSeq, prod->state & S_VISIT_SEQ);
	}
}


/************************************************************************
 *			       ProdFollowCB				*
 ************************************************************************/

/* This is the callback attached to the followInduced menu item. It marks
 * the origins of all marked induced dependencies in this context.
 */

/*ARGSUSED*/
PRIVATE void ProdFollowCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	SLNODE		*nd1, *nd2;
	ATTRENTRY	*ae1, *ae2;
	DEPENDENCY	*dep;

	for (nd1 = prod->hdright; nd1 != NULL; nd1 = nd1->right)
		for (ae1=SE(nd1->sid).first_attr; ae1!=NULL; ae1=ae1->next)
			for (nd2 = prod->hdright; nd2 != NULL; nd2 = nd2->right)
				for (ae2=SE(nd2->sid).first_attr; ae2!=NULL;
				     ae2=ae2->next)
				{
					dep = & prod->dp
						[nd2->start_row + ae2->pos]
						[nd1->start_row + ae1->pos];
					if (*dep & (T_MARK|T_FOLLOWED))
						ProdFindPath (prod, nd1,nd2,
								    ae1,ae2,1);
				}
}


/************************************************************************
 *			      ProdVisitSeqCB				*
 ************************************************************************/

/* This is the callback attached to the visitSeq menu item. It creates
 * the corresponding visit-sequence window.
 */

/*ARGSUSED*/
PRIVATE void ProdVisitSeqCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	VisitCreateNew (prod->prod_def->did);
}


/************************************************************************
 *			      ProdCreateMenu				*
 ************************************************************************/

/* Creates the production menu.
 */

PUBLIC void ProdCreateMenu (father)
	Widget father;
{
	int	n = 0;
	Arg	args[1];
	Widget	line;

	RuleMenu = CreateMenu ("ruleMenu", father);
	XtAddCallback (RuleMenu, XtNpopupCallback,
			ProdMenuPopupCB, (XtPointer) NULL);

	CreateMItem (ItemClose,   "close",    RuleMenu, ProdCloseCB,    NULL);
	CreateMItem (ItemCloseAll,"closeAll", RuleMenu, ProdCloseAllCB, NULL);
	CreateMLine (line,        "line",     RuleMenu);
	CreateMItem (ItemFollow,  "followInduced", RuleMenu,ProdFollowCB, NULL);
	CreateMLine (line,        "line",     RuleMenu);
	CreateMItem (ItemVisitSeq,"visitSeq", RuleMenu, ProdVisitSeqCB, NULL);
}
