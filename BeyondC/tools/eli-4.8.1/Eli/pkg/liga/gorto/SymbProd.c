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
/* $Id: SymbProd.c,v 4.2 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: SymbProd.c,v 4.2 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbProd.c					*
 *									*
 *	CONTENTS:	Creation of production windows from a symbol	*
 *			window						*
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
#include "Popup.h"
#include "Symb.h"

#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/List.h>


/************************************************************************
 *			      Global Widgets				*
 ************************************************************************/

PRIVATE Widget	SymbProdPopup = NULL;
PRIVATE String	*SymbProdList;
PRIVATE int	SymbProdListSize;


/************************************************************************
 *			         CancelCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void CancelCB (w, client_data, call_data)
	Widget	w;
	XtPointer client_data;
	XtPointer call_data;
{
	XtPopdown	(SymbProdPopup);
	XtDestroyWidget	(SymbProdPopup);
	XtFree ((char *)SymbProdList);
	SymbProdPopup = NULL;
}


/************************************************************************
 *			       SelectProdCB				*
 ************************************************************************/

/*ARGSUSED*/
PRIVATE void SelectProdCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	XawListReturnStruct	*item = (XawListReturnStruct *) call_data;
	int			pid   = lookupProdByName (item->string) -> did;

      /* Create the new production */
	ProdCreateNew (pid);
}


/************************************************************************
 *			        strcompare				*
 ************************************************************************/

PRIVATE int strcompare (s1, s2)
	char **s1, **s2;
{
	return (strcmp (*s1, *s2));
}

#if defined(__cplusplus) || defined(__STDC__)
typedef int (*comparefunc)(const void *, const void *);
#endif

/************************************************************************
 *			    SymbBuildProdList 				*
 ************************************************************************/

PRIVATE void SymbBuildProdList (symb)
	SYMBENTRY *symb;
{
	SLNODE *nd;
	String	name;

      /* Count the productions */
	SymbProdListSize = 0;
	for (nd = symb->hddown; nd != NULL; nd = nd->down) SymbProdListSize ++;

      /* Allocate space for the list */
	SymbProdList = (String *) XtMalloc (sizeof(String) * (1+SymbProdListSize));

      /* Fill the list with the dname entries of the productions */
	SymbProdListSize = 0;
	for (nd = symb->hddown; nd != NULL; nd = nd->down)
	{
		name = PE(nd->pid).prod_def->dname;

		if (SymbProdListSize == 0 ||
		    strcmp (SymbProdList[SymbProdListSize-1], name))
			SymbProdList[SymbProdListSize++] = name;
	}

      /* Sort the production list */
	if (Res.sort_prod_list)
#if defined(__cplusplus) || defined(__STDC__)
		qsort ((char *) SymbProdList, SymbProdListSize,
			sizeof (String), (comparefunc)strcompare);
#else
		qsort ((char *) SymbProdList, SymbProdListSize,
			sizeof (String), strcompare);
#endif
}


/************************************************************************
 *			        SymbProdCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void SymbProdCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	SYMBENTRY	*symb = & SE (DidOfGraphMenu);

	Position	x, y;
	Arg		args[10];
	int		n;
	Widget		paned, cancel, list;

      /* Close old popup */
	if (SymbProdPopup)
		CancelCB ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);

      /* Popup shell */
	GetPopupPositions (symb->symb_def->did, &x, &y);
	n = 0;
	XtSetArg (args[n], XtNx, x); n++;
	XtSetArg (args[n], XtNy, y); n++;
	SymbProdPopup = XtCreatePopupShell ("symbolRules",
		transientShellWidgetClass, Toplevel, args, n);

      /* paned widget */
	n = 0; paned = CreatePaned ("paned", SymbProdPopup);

      /* label */
	n = 0; (void) CreateLabel ("label", paned);

      /* cancel command */
	n = 0; CreateCommand (cancel, "cancel", paned, CancelCB, NULL);

      /* production list */
	SymbBuildProdList (symb);
	n = 0;
	XtSetArg (args[n], XtNlist, SymbProdList); n++;
	XtSetArg (args[n], XtNnumberStrings, SymbProdListSize); n++;
	list = CreateList ("rules", paned);
	XtAddCallback (list, XtNcallback, SelectProdCB, (XtPointer) NULL);
	
      /* Popup the window */
	XtPopup (SymbProdPopup, XtGrabNone);
}
