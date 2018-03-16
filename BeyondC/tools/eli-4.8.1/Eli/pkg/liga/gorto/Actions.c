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
/* $Id: Actions.c,v 4.2 1998/04/28 14:07:14 ludi Exp $ */
static char rcs_id[]= "$Id: Actions.c,v 4.2 1998/04/28 14:07:14 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/Actions.c					*
 *									*
 *	CONTENTS:	Implementation of the GORTO actions		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"
#include "Visit.h"
#include "Main.h"
#include "Graph.h"
#include "Popup.h"

#include <stdio.h>
#include <X11/Xaw/AsciiText.h>


/************************************************************************
 *			     ActionMenuPopup				*
 ************************************************************************/

/* Call of the action procedure menu-popup. Update the utility value
 * DidOfGraphMenu and popup the requested menu.
 */

/*ARGSUSED*/
PUBLIC void ActionMenuPopup (w, event, params, num_params)
	Widget		w;
	XEvent		*event;
	String		*params;
	Cardinal	*num_params;
{
	static int did;
	static Arg args[] = {{XtNdid, (XtArgVal) &did}};

      /* Set utility value for graph widgets */
	if (XtClass (w) == graphWidgetClass)
	{
		XtGetValues (w, args, XtNumber(args));
		DidOfGraphMenu = did;
	}

      /* Popup the requested menu by calling the corresponding actions */
	XtCallActionProc (w, "XawPositionSimpleMenu", event, params, 1);
	XtCallActionProc (w, "MenuPopup", event, params, 1);
}


/************************************************************************
 *			    ActionCloseWindow				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void ActionCloseWindow (w, event, params, num_params)
	Widget		w;
	XEvent		*event;
	String		*params;
	Cardinal	*num_params;
{
	static int did;
	static Arg args[] = {{XtNdid, (XtArgVal) &did}};

      /* Try to identify the class of <w> */
	if (XtClass (w) == graphWidgetClass)
	{
	      /* Retrieve did of this graph widget */
		XtGetValues (w, args, XtNumber(args));

	      /* Determine window contents */
		DidOfGraphMenu = did;
		if (ref_tab[did].etag == PROD)
		{
			if (PE(did).vs && PE(did).vs->vsar &&
			    PE(did).vs->vsar->widget == w)
				VisitCloseCB (w, (caddr_t)NULL, (caddr_t)NULL);
			else
				ProdCloseCB (w, (caddr_t) NULL, (caddr_t) NULL);
		}
		else if (ref_tab[did].etag == SYMB)
			SymbCloseCB (w, (caddr_t) NULL, (caddr_t) NULL);
	}
	else if (XtClass (w) == asciiTextWidgetClass)
		LidoCB (w, (caddr_t) NULL, (caddr_t) NULL);
}
