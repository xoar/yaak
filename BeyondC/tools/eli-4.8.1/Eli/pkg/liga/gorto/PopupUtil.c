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
/* $Id: PopupUtil.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: PopupUtil.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Popup/PopupUtil.c				*
 *									*
 *	DESCRIPTION:	Utilities for Popup windows			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Main.h"
#include "Popup.h"
#include <X11/StringDefs.h>


/************************************************************************
 *                          GetPopupPositions				*
 ************************************************************************/

/* Computes the x and y positions of a popup window.
 */

PUBLIC void GetPopupPositions (did, x_return, y_return)
	int		did;
	Position	*x_return;
	Position	*y_return;
{
	Widget	w;
	int	x, y;
	Window	child;

      /* Determine the x and y positions of the window and store them in
         the corresponding production entry in ref_tab. The Coordinates
         are determined by using a raw Xlib Call, since this gives the
         correct result in all cases, especially when using a re-parenting
         window manager. */
	if (did == 0)				w = Toplevel;
	else if (ref_tab[did].etag == PROD)	w = PE(did).par->widget;
	else					w = SE(did).sar->widget;

	XTranslateCoordinates (dpy, XtWindow (w),
				RootWindowOfScreen (XtScreen (w)),
				0, 0, &x, &y, &child);

      /* Set the return values */
	*x_return = x + 20;
	*y_return = y + 10;
}
