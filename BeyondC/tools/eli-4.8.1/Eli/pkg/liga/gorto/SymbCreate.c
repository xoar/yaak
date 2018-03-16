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
/* $Id: SymbCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: SymbCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbCreate.c				*
 *									*
 *	DESCRIPTION:	Create and destroy of symbol windows		*
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
#include "Main.h"
#include "Graph.h"
#include "Symb.h"

#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Viewport.h>

#define TOPLEVEL(w)	XtParent(XtParent(XtParent(w)))

/************************************************************************
 *				 Actions				*
 ************************************************************************/

PRIVATE XtActionsRec symb_actions[] = {
{"close",	ActionCloseWindow},
};
static Atom wm_delete_window;


/************************************************************************
 *			       SymbCloseCB				*
 ************************************************************************/

/* Callback of the <close> button of a symbol window.
 */

/*ARGSUSED*/
PUBLIC void SymbCloseCB (w, client_data, call_data)
        Widget  w;
        caddr_t client_data;
        caddr_t call_data;
{
	SYMBENTRY	*symb = & SE (DidOfGraphMenu);
	Widget		top;

	char	geom[80];
	int	x, y;
	Window	child;

	if (symb->sar == (SAR *) NULL) return;

      /* Determine the x and y positions of the window and store them in
         the corresponding production entry in ref_tab. The Coordinates
         are determined by using a raw Xlib Call, since this gives the
         correct result in all cases, especially when using a re-parenting
         window manager. */
	top = TOPLEVEL (symb->sar->widget);
        XTranslateCoordinates (dpy, XtWindow (top),
                                RootWindowOfScreen (XtScreen (top)),
                                0, 0, &x, &y, &child);
        XtFree (symb->geometry);
        (void) sprintf (geom, "+%d+%d", x, y - Res.wm_push_down);
        symb->geometry = XtNewString (geom);

      /* Destroy the window */
        XtUnmapWidget (top);
        XtDestroyWidget (top);

      /* Unmark all dependencies */
	SymbMaskDependencies (symb, T_MASK);

      /* Free the symbol activation record */
	if (symb == SymbMarkedAttr.symb)
	{
		SymbMarkedAttr.symb = NULL;
		SymbMarkedAttr.ae   = NULL;
	}
        XtFree ((char *) symb->sar);
        symb->sar = (SAR *) NULL;
}


/************************************************************************
 *			      SymbCloseAllCB				*
 ************************************************************************/

/* Closes all symbol windows.
 */

/*ARGSUSED*/
PUBLIC void SymbCloseAllCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	int i;
	SYMBENTRY *symb = (SYMBENTRY *) client_data;

	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == SYMB && SE(i).sar != (SAR *) NULL)
		{
			if (symb == & SE(i)) continue;
			DidOfGraphMenu = i;
			SymbCloseCB ((Widget) NULL, (caddr_t) NULL,
				     (caddr_t) NULL);
		}
	
	if (symb != NULL) SymbMaskDependencies (symb, T_MASK);
}


/************************************************************************
 *			      SymbCreateNew				*
 ************************************************************************/

/* Creates a new toplevel window containing the dependency graph of the	
 * given symbol.
 */

PUBLIC void SymbCreateNew (sid)
	int sid;
{
	SYMBENTRY	*symb = & SE(sid);
	Arg		args[10];
	int		n;
	Dimension	width, height;
	Widget		newtop, vpaned, view, win, label;
	char		title[80];

      /* Avoid two windows containing the same symbol */
	if (symb->sar)
	{
		RedisplayGraphOfDid (symb->symb_def->did);
		XRaiseWindow (dpy, XtWindow (TOPLEVEL (symb->sar->widget)));
		return;
	}

      /* Allocate and initialize the new symbol activation record */
	symb->sar = XtNew (SAR);
	InitSAR (symb);

      /* Determine the title of the new window */
	(void) sprintf (title, "%s %s", Res.str_symbol, symb->symb_def->dname);

      /* Create the new toplevel widget */
	n = 0;
	if (symb->geometry)
	{
		XtSetArg (args[n], XtNgeometry, symb->geometry); n++;
	}
	XtSetArg (args[n], XtNtitle, title); n++;
	XtSetArg (args[n], XtNiconName, title); n++;
	newtop = XtCreatePopupShell ("symbol", topLevelShellWidgetClass, 
			Toplevel, args, n);

      /* Create the vertical paned widget */
	n = 0;
	vpaned = CreatePaned ("vpaned", newtop);

      /* Create the state label */
	n = 0;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	XtSetArg (args[n], XtNlabel, SymbStateLabel (symb)); n++;
	label = CreateLabel ("state", vpaned);

      /* Create the viewport widget */
	SymbComputeWindowSize (symb, &width, &height);
	n = 0;
	view = CreateView ("symbolView", vpaned);

      /* Create the window widget */
	XtSetArg (args[n], XtNdid, sid); n++;
        XtSetArg (args[n], XtNwidth, width); n++;
        XtSetArg (args[n], XtNheight, height); n++;
	CreateGraph (win, "symbolGraph", view, 
			SymbRedrawCB, SymbResizeCB, SymbSelectCB, symb);

      /* Realize the new window */
        symb->sar->widget = win;
	symb->sar->state  = label;
        XtPopup (newtop, XtGrabNone);
	/*
       * This is a hack so that wm_delete_window will close the rule graph window.
       */
       
        /* Register Actions */
       XtAppAddActions (XtWidgetToApplicationContext(newtop), symb_actions, XtNumber(symb_actions));

       XtOverrideTranslations(newtop, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: close()"));
       
       wm_delete_window = XInternAtom (XtDisplay(newtop), "WM_DELETE_WINDOW", False);
       
       XSetWMProtocols (XtDisplay(newtop), XtWindow(newtop),
			    &wm_delete_window, 1);
}


/************************************************************************
 *			     SymbUpdateState				*
 ************************************************************************/

/* Updates the state label of the given symbol.
 */

PUBLIC void SymbUpdateState (symb)
	SYMBENTRY *symb;
{
	Arg args[1];

	if (symb->sar)
	{
		XtSetArg (args[0], XtNlabel, SymbStateLabel (symb));
		XtSetValues (symb->sar->state, args, 1);
		SymbUpdateList ();
	}
}
