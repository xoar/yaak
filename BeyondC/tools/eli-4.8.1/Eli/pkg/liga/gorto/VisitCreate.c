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
/* $Id: VisitCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: VisitCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitCreate.c				*
 *									*
 *	CONTENTS:	Create and destroy of visit-sequence windows	*
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
#include "Graph.h"
#include "Main.h"
#include "Visit.h"

#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Viewport.h>

#define TOPLEVEL(w) XtParent(XtParent(w))


/************************************************************************
 *			      VisitCreateNew				*
 ************************************************************************/

/* Create a new toplevel window containing the visit-sequence of the
 * given producion.
 */

PUBLIC void VisitCreateNew (pid)
	int pid;
{
	PRODENTRY	*prod = & PE(pid);
	Arg		args[10];
	int		n;
	Dimension	width, height;
	Widget		newtop, form, view, win;
	char		title[80];

      /* Avoid two windows containing the same visit-sequence */
	if (prod->vs->vsar != (VSAR *) NULL)
	{
		RedisplayWidget (prod->vs->vsar->widget);
		XRaiseWindow (dpy, XtWindow (TOPLEVEL(prod->vs->vsar->widget)));
		return;
	}

      /* Allocate and initialize the new visit-sequence activation record */
	prod->vs->vsar = XtNew (VSAR);
	prod->vs->vsar->x = 0;

      /* Determine the title of the new window */
	(void) sprintf (title, "%s %s", Res.str_vs, prod->prod_def->dname);

      /* Create the new toplevel widget */
	n = 0;
	if (prod->vs->geometry)
	{
		XtSetArg (args[n], XtNgeometry, prod->vs->geometry); n++;
	}
	XtSetArg (args[n], XtNtitle, title); n++;
	XtSetArg (args[n], XtNiconName, title); n++;
	newtop = XtCreatePopupShell ("visitSeq", topLevelShellWidgetClass,
				Toplevel, args, n);

	if (Res.make_titles)
	{
		n = 0; form = CreateForm ("visitSeqForm", newtop);
		n = 0; (void) CreateLabel (title, form);
	}

      /* Create the viewport widget */
	VisitComputeWindowSize (prod, &width, &height);
	n = 0;
	view = CreateView ("visitSeqView", Res.make_titles ? form : newtop);

      /* Create the graph widget */
	n = 0;
	XtSetArg (args[n], XtNdid, pid); n++;
	XtSetArg (args[n], XtNwidth, width); n++;
	XtSetArg (args[n], XtNheight, height); n++;
	CreateGraph (win, "visitSeqGraph", view,
			VisitRedrawCB, VisitResizeCB, VisitSelectCB, prod);

      /* Realize the new window */
	prod->vs->vsar->widget = win;
	XtPopup (newtop, XtGrabNone);
}


/************************************************************************
 *			       VisitCloseCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitCloseCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	PRODENTRY	*prod = & PE(DidOfGraphMenu);
	Widget		top;

	char	geom[80];
	int	x, y;
	Window	child;

	if (prod->vs->vsar == (VSAR *) NULL) return;

      /* Determine the x and y positions of the window and store them in
	 the corresponding production entry in ref_tab. The Coordinates
	 are determined by using a raw Xlib Call, since this gives the
	 correct result in all cases, especially when using a re-parenting
	 window manager. */
	top = TOPLEVEL (prod->vs->vsar->widget);
	XTranslateCoordinates (dpy, XtWindow (top),
				RootWindowOfScreen (XtScreen (top)),
				0, 0, &x, &y, &child);
	XtFree (prod->vs->geometry);
	(void) sprintf (geom, "+%d+%d", x, y - Res.wm_push_down);
	prod->vs->geometry = XtNewString (geom);

      /* Destroy the window */
	XtUnmapWidget (top);
	XtDestroyWidget (top);

      /* Unmark marks in this visit-sequence */
	if (prod == VisitMarkedElem.prod)
	{
		VisitMarkedElem.prod = NULL;
		VisitMarkedElem.elem = NULL;
	}

      /* Free the visit-sequence activation record */
	XtFree ((char *) prod->vs->vsar);
	prod->vs->vsar = (VSAR *) NULL;
}


/************************************************************************
 *			     VisitCloseAllCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitCloseAllCB (w, client_data, call_data)
	Widget	w;
	caddr_t client_data;
	caddr_t call_data;
{
	int i;
	PRODENTRY *prod = (PRODENTRY *) client_data;

	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD &&
		    PE(i).vs != (VSINFO *) NULL &&
		    PE(i).vs->vsar != (VSAR *) NULL)
		{
			if (prod == & PE(i)) continue;
			DidOfGraphMenu = i;
			VisitCloseCB ((Widget) NULL, (caddr_t) NULL,
				      (caddr_t) NULL);
		}
}
