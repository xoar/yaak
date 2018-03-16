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
/* $Id: Lido.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: Lido.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Popup/Lido.c					*
 *									*
 *	CONTENTS:	Routines dealing with the lido source window	*
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
#include "Main.h"
#include "Popup.h"

#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/AsciiText.h>
#include <X11/Xaw/SmeBSB.h>

#define AsciiTextSinkName "*textSink"


/************************************************************************
 *		      	     Global Variables				*
 ************************************************************************/

PUBLIC  Widget LidoTop  = (Widget)NULL; /* Toplevel of lido window */
PRIVATE Widget LidoText = (Widget)NULL; /* Text widget containing the lido
					   source */

PRIVATE char LidoGeometry[80] = "";
PRIVATE XawTextPosition	*LinePosition = NULL;

PRIVATE XtActionsRec lido_actions[] = {
{"close",	ActionCloseWindow},
};
static Atom wm_delete_window;

/************************************************************************
 *				CreateLido				*
 ************************************************************************/

/* Creates the lido window.
 */

PRIVATE void CreateLido ()
{
	Widget	sink;
	Arg	args[10];
	int	n;

      /* Create a new toplevel Shell */
	n = 0;
	if (LidoGeometry[0] != '\0')
	{
		XtSetArg (args[n], XtNgeometry, LidoGeometry); n++;
	}
	XtSetArg (args[n], XtNtitle, Res.lido_name); n++;
	LidoTop = XtCreatePopupShell ("lido", topLevelShellWidgetClass,
						Toplevel, args, n);

      /* Create the Text Widget */
	n = 0;
	XtSetArg (args[n], XtNtype, XawAsciiFile); n++;
	XtSetArg (args[n], XtNstring, Res.lido_name); n++;
	LidoText = XtCreateManagedWidget ("lidoText", asciiTextWidgetClass,
						LidoTop, args, n);

      /* Realize the new top level Widget */
	XtPopup (LidoTop, XtGrabNone);

      /*
       * This is a hack so that wm_delete_window will close the rule graph window.
       */
       
        /* Register Actions */
       XtAppAddActions (XtWidgetToApplicationContext(LidoTop), lido_actions, XtNumber(lido_actions));

       XtOverrideTranslations(LidoTop, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: close()"));
       
       wm_delete_window = XInternAtom (XtDisplay(LidoTop), "WM_DELETE_WINDOW", False);
       
       XSetWMProtocols (XtDisplay(LidoTop), XtWindow(LidoTop),
			    &wm_delete_window, 1);


      /* Try to find text sink */
	sink = XtNameToWidget (LidoTop, AsciiTextSinkName);
	if (sink == NULL)
	{
/* Don't give warnings... XtNameToWidget has never worked!
		fprintf (stderr,"%s: Couldn't find window of LIDO text.\n",
				ProgName);
		fprintf (stderr, "Menu will not work in LIDO window.\n");
*/
		return;
	}
	
      /* Register a passive grab for menu-popup */
	XGrabButton (XtDisplay (sink), AnyButton, AnyModifier, 
		XtWindow (sink), TRUE, ButtonPressMask|ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync, None, None);
}


/************************************************************************
 *			       DestroyLido				*
 ************************************************************************/

/* Destroys the lido window and remembers its current geometry.
 */

PRIVATE void DestroyLido ()
{
	int		root_x, root_y;
	int		x, y;
	unsigned int	width, height, bw, depth;
	Window		dummy;

      /* Remember the window's position */
	XTranslateCoordinates (dpy, XtWindow (LidoTop),
				RootWindowOfScreen (XtScreen (LidoTop)),
				0, 0, &root_x, &root_y, &dummy);
	XGetGeometry (dpy, XtWindow (LidoTop), &dummy,
				&x, &y, &width, &height, &bw, &depth);
	(void) sprintf (LidoGeometry, "%ux%u+%d+%d", 
			width, height, root_x, root_y - Res.wm_push_down);

      /* Destroy the window */
	XtUnmapWidget (LidoTop);
	XtDestroyWidget (LidoTop);
	LidoTop = (Widget) NULL;
}


/************************************************************************
 *				  LidoCB				*
 ************************************************************************/

/* Callback of the lido menu item.
 */

/*ARGSUSED*/
PUBLIC void LidoCB (w, client_data, call_data)
        Widget  w;
        caddr_t client_data;
        caddr_t call_data;
{
	Arg args[2];

      /* Check the lido file name */
	if (Res.lido_name == NULL) return;

      /* Check for already existing window */
	if (LidoTop != (Widget) NULL)
	{
		XtSetArg (args[0], XtNleftBitmap, None);
		DestroyLido();
	}
	else	
	{
		XtSetArg (args[0], XtNleftBitmap, CheckMarkBitmap);
		CreateLido();
	}
	XtSetValues (LidoMenuItem, args, 1);
}


/************************************************************************
 *			    LookupLinePosition				*
 ************************************************************************/

/* Fills the array LinePosition up to the given row.
 */

PRIVATE void LookupLinePosition (row)
	int row;
{
	static int LastLinePosition = -1;

	XawTextPosition	current_pos;
	int		c;
	FILE		*source;

	if (row <= LastLinePosition) return;

      /* Increase the size of the position buffer */
	LinePosition = (XawTextPosition *) 
		XtRealloc ((char *)LinePosition, sizeof (XawTextPosition) * (row+1));

      /* Open the source text */
	if ((source = fopen (Res.lido_name, "r")) == NULL)
	{
		XtWarning ("LIDO Source file could not be read");
		return;
	}

      /* Seek to the last stored text position */
	if (LastLinePosition >= 0 &&
	    fseek (source, (long) LinePosition[LastLinePosition]+1, 0))
	{
		XtWarning ("LIDO Source file could not be seeked");
		return;
	}

      /* Initialize the current line position */
	if (LastLinePosition < 0)
		LinePosition[LastLinePosition = 0] = (XawTextPosition) 0;
	current_pos = LinePosition[LastLinePosition] + 1;

      /* Lookup the line positions up to the requested row */
	while ((c = getc (source)) != EOF && LastLinePosition < row)
	{
		if (c == '\n')
			LinePosition[++ LastLinePosition] = current_pos;
		current_pos ++;
	}

      /* Close the source text */
	fclose (source);
}


/************************************************************************
 *			     ShowLidoPosition				*
 ************************************************************************/

/* Highlights the given source position in the lido window.
 */

PUBLIC void ShowLidoPosition (row)
	int row;
{
      /* Assure existing lido text */
	if (Res.lido_name == NULL) return;

      /* Assure existing lido window */
	if (LidoTop == (Widget) NULL)
		LidoCB ((Widget) NULL, (caddr_t) NULL, (caddr_t) NULL);

      /* Assure the requested position is already buffered */
	LookupLinePosition (row);

      /* Set the text selection and insertion point */
	XawTextSetSelection (LidoText, LinePosition[row-1], LinePosition[row]);
	XawTextSetInsertionPoint (LidoText, LinePosition[row-1]+1);
}
