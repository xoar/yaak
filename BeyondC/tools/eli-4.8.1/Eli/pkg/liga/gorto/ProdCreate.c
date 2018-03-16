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
/* $Id: ProdCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdCreate.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdCreate.c				*
 *									*
 *	CONTENTS:	Create and destroy of production windows	*
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

/* This file contains the functions to create and destroy the popup shells 
 * containing production dependency graphs.
 */

#include <stdio.h>
#include "Misc.h"
#include "Create.h"
#include "Graph.h"
#include "Main.h"
#include "Prod.h"

#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Viewport.h>

#define TOPLEVEL(w) XtParent(XtParent(XtParent(w)))
/************************************************************************
 *				 Actions				*
 ************************************************************************/

PRIVATE XtActionsRec prod_actions[] = {
{"close",	ActionCloseWindow},
};

/************************************************************************
 *			      ProdCreateNew				*
 ************************************************************************/

/* Creates a new toplevel window containing the dependency graph of the 
 * given production. A reference to the created graph widget is stored in
 * the ref_tab entry of this production.
 * If the window is already existing, it is raised instead.
 */
static Atom wm_delete_window;

PUBLIC void ProdCreateNew (pid)
	int pid;
{
	PRODENTRY	*prod = & PE(pid);
	Arg		args[10];
	int		n;
	Dimension	width, height;
	Widget		newtop, paned, view;
	char		title[80];

      /* If the window is already existing, only raise it */
	if (prod->par)
	{
		RedisplayGraphOfDid (prod->prod_def->did);
		XRaiseWindow (dpy, XtWindow (TOPLEVEL (prod->par->widget)));
		return;
	}

      /* Allocate and initialize the new production activation record */
	prod->par = XtNew (PAR);
	prod->par->lhs_x = 0;

      /* Create the new toplevel widget */
	(void) sprintf (title, "%s %s", Res.str_rule, prod->prod_def->dname);
	n = 0;
	if (prod->geometry)
		{ XtSetArg (args[n], XtNgeometry, prod->geometry); n++; }

	XtSetArg (args[n], XtNtitle, title); n++;
	XtSetArg (args[n], XtNiconName, title); n++;
	newtop = XtCreatePopupShell ("rule", topLevelShellWidgetClass, 
				Toplevel, args, n);

      /* Create the paned widget */
	n = 0;
	paned = CreatePaned ("rulePaned", newtop);

      /* State Label */
	n = 0;
	XtSetArg (args[n], XtNlabel, ProdStateLabel (prod)); n++;
	prod->par->state = CreateLabel ("state", paned);

      /* Create the scrolled window widget */
	n = 0;
	view = CreateView ("ruleView", paned);

      /* Create the workspace widget */
	ProdComputeWindowSize (prod, &width, &height);
	n = 0;
	XtSetArg (args[n], XtNdid, pid); n++;
	XtSetArg (args[n], XtNwidth, width); n++;
	XtSetArg (args[n], XtNheight, height); n++;
	CreateGraph (prod->par->widget, "ruleGraph", view,
			ProdRedrawCB, ProdResizeCB, ProdSelectCB, prod);



      /* Realize the new window */
	XtPopup (newtop, XtGrabNone);
      
      /*
       * This is a hack so that wm_delete_window will close the rule graph window.
       */
       
        /* Register Actions */
       XtAppAddActions (XtWidgetToApplicationContext(newtop), prod_actions, XtNumber(prod_actions));

       XtOverrideTranslations(newtop, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: close()"));
       
       wm_delete_window = XInternAtom (XtDisplay(newtop), "WM_DELETE_WINDOW", False);
       
       XSetWMProtocols (XtDisplay(newtop), XtWindow(newtop),
			    &wm_delete_window, 1);


}


/************************************************************************
 *			     ProdUpdateState				*
 ************************************************************************/

/* Updates the state label of the given production <prod>.
 */

PUBLIC void ProdUpdateState (prod)
	PRODENTRY *prod;
{
	if (prod->par)
	{
		Arg args[1];

		XtSetArg (args[0], XtNlabel, ProdStateLabel (prod));
		XtSetValues (prod->par->state, args, 1);
	}
}


/************************************************************************
 *			       ProdCloseCB				*
 ************************************************************************/

/* Callback of the <close> button of a production window.
 * Closes the toplevel window containing a production. Frees the
 * corresponding production layout.
 */

/*ARGSUSED*/
PUBLIC void ProdCloseCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	PRODENTRY	*prod = & PE(DidOfGraphMenu);
	Widget		top;

	char	geom[80];
	int	x,y;
	Window	child;

	if (prod->par == (PAR *) NULL) return;

      /* Determine the x and y positions of the window and store them in
	 the corresponding production entry in ref_tab. The Coordinates
	 are determined by using a raw Xlib Call, since this gives the 
	 correct result in all cases, especially when using a re-parenting
	 window manager. */
	top = TOPLEVEL (prod->par->widget);
	XTranslateCoordinates (dpy, XtWindow (top), 
				RootWindowOfScreen (XtScreen (top)),
				0, 0, &x, &y, &child);
	XtFree (prod->geometry);
	(void) sprintf (geom, "+%d+%d", x, y - Res.wm_push_down);
	prod->geometry = XtNewString (geom);

      /* Destroy the window */
	XtUnmapWidget (top);
	XtDestroyWidget (top);

      /* Unmark all dependencies */
	ProdMaskDependencies (prod, T_MASK);

      /* Free the production activation record */
	if (ProdMarkedAttr.node != NULL && 
	    ProdMarkedAttr.node->pid == prod->prod_def->did)
	{
		ProdMarkedAttr.node = NULL;
		ProdMarkedAttr.ae   = NULL;
	}
	XtFree ((char *) prod->par);
	prod->par = NULL;
}


/************************************************************************
 *			      ProdCloseAllCB				*
 ************************************************************************/

/* Closes all production windows. If a PRODENTRY * is passed as
 * client_data, the corresponding production is not closed.
 */

/*ARGSUSED*/
PUBLIC void ProdCloseAllCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	int i;
	PRODENTRY *prod = (PRODENTRY *) client_data;

      /* Search all productions and close them */
	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD && PE(i).par != (PAR *) NULL)
		{
			if (prod == & PE(i)) continue;
			DidOfGraphMenu = i;
			ProdCloseCB ((Widget) NULL, (caddr_t) NULL,
				     (caddr_t) NULL);
		}

      /* If a production was passed as client_data, mask the dependencies */
	if (prod) ProdMaskDependencies (prod, T_MASK);
}
