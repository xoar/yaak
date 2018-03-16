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
/* $Id: MainWindow.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: MainWindow.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/MainWindow.c				*
 *									*
 *	DESCRIPTION:	Routines dealing with the main window of GORTO	*
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
#include "Symb.h"
#include "Visit.h"
#include "Popup.h"
#include "Main.h"

#include <X11/StringDefs.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>

/* Dont't use cascading menues
#include "SmeMenu.h"
*/

PUBLIC Widget StateLabel;
PUBLIC Widget LidoMenuItem;


/************************************************************************
 *			      CreateMainMenu				*
 ************************************************************************/

/* Creates the widgets of the main menu.
 */

PRIVATE void CreateMainMenu (father)
	Widget father;
{
	Widget	menu, item;
	Arg	args[5];
	int	n;

      /* Menu Shell */
	n = 0;
	menu = CreateMenu ("mainMenu", father);

      /* Menu Items */
	n = 0;
	XtSetArg (args[n], XtNsensitive, Res.lido_name != NULL); n++;
	CreateMItem (LidoMenuItem, "lido", menu, LidoCB, NULL);

	n = 0;
	CreateMItem (item, "close",         menu, ProdCloseAllCB, NULL);
	XtAddCallback (item, XtNcallback, SymbCloseAllCB,  (caddr_t) NULL);
	XtAddCallback (item, XtNcallback, VisitCloseAllCB, (caddr_t) NULL);

	CreateMItem (item, "recompute",     menu, RecomputeCB,    NULL);
	CreateMLine (item, "line", menu);
	CreateMItem (item, "hide",          menu, HideCB,         True);
	CreateMItem (item, "unhide",        menu, HideCB,         False);

	XtSetArg (args[n], XtNleftBitmap, 
		  Res.show_part_deps ? CheckMarkBitmap : None); n++;
	CreateMItem (item, "partDeps",	    menu, PartDepsCB,	  NULL);

	n = 0;
	CreateMLine (item, "line", menu);

/* Dont't use cascading menues
	n = 0;
	XtSetArg (args[n], XtNrightBitmap, CascadeBitmap); n++;
	XtSetArg (args[n], XtNmenu, "topologicalMenu"); n++;
	item = XtCreateManagedWidget ("topological", smeMenuObjectClass,
						menu, args, n);
	n = 0;
	XtSetArg (args[n], XtNrightBitmap, CascadeBitmap); n++;
	XtSetArg (args[n], XtNmenu, "partitionMenu"); n++;
	item = XtCreateManagedWidget ("partition", smeMenuObjectClass,
						menu, args, n);
	n = 0;
	CreateMLine (item, "line", menu);
*/

	n = 0;
	CreateMItem (item, "ctlquit", menu, CtlQuitCB, NULL);
	n = 0;
	CreateMItem (item, "quit", menu, QuitCB, NULL);
}


/************************************************************************
 *			    CreateProdWidgets				*
 ************************************************************************/

/* Create the widgets of the main window that are dealing with prod's.
 */

PRIVATE void CreateProdWidgets (father)
	Widget father;
{
	Widget	hpaned;
	Arg	args[5];
	int	n;

      /* Topological strategy */
	CreateTopoMenu (Toplevel);

      /* Surrounding paned widget */
	n = 0;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	XtSetArg (args[n], XtNskipAdjust, True); n++;
	XtSetArg (args[n], XtNorientation, XtorientHorizontal); n++;
	hpaned = CreatePaned ("rules", father);

      /* Menu Button */
	n = 0;
	XtSetArg (args[n], XtNmenuName, "topologicalMenu"); n++;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	(void) CreateMButton ("topologicalMenuButton", hpaned);

      /* Production list */
	ProdCreateList (hpaned, father);
}


/************************************************************************
 *			    CreateSymbWidgets				*
 ************************************************************************/

/* Create the widgets of the main window that are dealing with symbols.
 */

PRIVATE void CreateSymbWidgets (father)
	Widget father;
{
	Widget	hpaned; 
	Arg	args[5];
	int	n;

      /* Partition strategy */
	CreatePartMenu (Toplevel);
	
      /* Surrounding paned widget */
	n = 0;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	XtSetArg (args[n], XtNskipAdjust, True); n++;
	XtSetArg (args[n], XtNorientation, XtorientHorizontal); n++;
	hpaned = CreatePaned ("symbols", father);

      /* Menu Button */
	n = 0;
	XtSetArg (args[n], XtNmenuName, "partitionMenu"); n++;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	(void) CreateMButton ("partitionMenuButton", hpaned);

      /* Symbol list */
	SymbCreateList (hpaned, father);
}


/************************************************************************
 *                            CreateWidgets				*
 ************************************************************************/

/* Creates the widgets for the main window.
 */

PUBLIC void CreateWidgets ()
{
	Widget	paned, hpaned; 
        Arg args[10];
        int n;

      /* Main Paned Widget */
	n = 0;
	paned = CreatePaned ("paned", Toplevel);

      /* Main Menu and state label */
	n = 0;
	XtSetArg (args[n], XtNorientation, XtorientHorizontal); n++;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	hpaned = CreatePaned ("hPaned", paned);

	n = 0;
	XtSetArg (args[n], XtNshowGrip, False); n++;
	XtSetArg (args[n], XtNmenuName, "mainMenu"); n++;
	(void) CreateMButton ("mainMenuButton", hpaned);
	CreateMainMenu (Toplevel);

	n = 0;
	XtSetArg (args[n], XtNlabel, " "); n++;
	StateLabel = CreateLabel ("state", hpaned);

      /* Topological strategy and production list with filter */
	CreateProdWidgets (paned);

      /* Partition strategy and symbol list with filter */
	CreateSymbWidgets (paned);

      /* Symbol Menu */
	ProdCreateMenu  (Toplevel);
	SymbCreateMenu  (Toplevel);
	VisitCreateMenu (Toplevel);
}
