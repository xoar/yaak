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
/* $Id: Bitmaps.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Bitmaps.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Bitmaps.c					*
 *									*
 *	CONTENTS:	Initialization of the used bitmaps		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Main.h"

#include "CheckMark.bm"
#include "Cascade.bm"
#include "Icon.bm"


/************************************************************************
 *		     	    Global Definitions				*
 ************************************************************************/

PUBLIC Pixmap	CheckMarkBitmap = None;		/* Menu item checkmark */
PUBLIC Pixmap	CascadeBitmap = None;		/* Menu cascade indicator */
PUBLIC Pixmap	IconBitmap = None;		/* Main window icon */


/************************************************************************
 *        		       LoadBitmaps				*
 ************************************************************************/

/* Initializes the three public bitmaps exported from this file.
 */

PUBLIC void LoadBitmaps()
{
      /* Build CheckMarkBitmap */
	CheckMarkBitmap = XCreateBitmapFromData (dpy, 
		RootWindowOfScreen (XtScreen (Toplevel)),
		(const char *) CheckMark_bits, CheckMark_width, CheckMark_height);

      /* Build CascadeBitmap */
	CascadeBitmap = XCreateBitmapFromData (dpy,
		RootWindowOfScreen (XtScreen (Toplevel)),
		(const char *) Cascade_bits, Cascade_width, Cascade_height);

      /* Build IconBitmap */
	IconBitmap = XCreateBitmapFromData (dpy,
		RootWindowOfScreen (XtScreen (Toplevel)),
		(const char *) Icon_bits, Icon_width, Icon_height);
}
