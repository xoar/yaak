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
/* $Id: Hide.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Hide.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Popup/Hide.c					*
 *									*
 *	CONTENTS:	Routines used for hiding attributes		*
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
#include "Popup.h"
#include "Compile.h"

#include <string.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/AsciiText.h>


/************************************************************************
 *			     Global variables				*
 ************************************************************************/

#define MAX_NAME_LENGTH 20	/* Maximum length of an attribute name */

PUBLIC  Widget	HidePopup = (Widget) NULL;	/* Popup - Shell */
PRIVATE char	HideString[MAX_NAME_LENGTH];	/* Attribute name */
PRIVATE STATE	OldState;


/************************************************************************
 *				 Actions				*
 ************************************************************************/
PRIVATE void CancelCB();

PRIVATE XtActionsRec hide_actions[] = {
{"close",	CancelCB},
};


/************************************************************************
 *	   Stuff used to access the regular expression routines		*
 *		  see regexp(3) for further information			*
 ************************************************************************/

PUBLIC void regerr (val)
	int val;
{
	XtPopdown	(HidePopup);
	XtDestroyWidget	(HidePopup);
	SetState (OldState);
}


#define ESIZE		255	/* max. size of compiled expression */

/************************************************************************
 *			     UpdateAfterHide				*
 ************************************************************************/

PRIVATE void UpdateAfterHide(close)
	Boolean close;
{
	int i;

      /* Recompute the additions to ref_tab */
	ComputeRefTabAdditions();

      /* Perform a re-display of all production windows */
	for (i=min_entry; i<=max_entry; i++)
	{
		if (ref_tab[i].etag == PROD && PE(i).par != NULL)
			ProdResizeWindow (& PE(i));
	}

      /* Popdown and destroy the hide popup */
	if (close && HidePopup != (Widget) NULL)
	{
		XtPopdown	(HidePopup);
		XtDestroyWidget	(HidePopup);
		HidePopup = (Widget) NULL;
		SetState (OldState);
	}
}


/************************************************************************
 *				 HideNonCyclic				*
 ************************************************************************/
 
PUBLIC void HideNonCyclic (hide)
	Boolean	hide;
{
	int i;
	ATTRENTRY *ae;

      /* Set the hidden flags */
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == ATTR)
		{
			ae = & AE(i);
			if (!ae->cyclic)
			{
			    if (hide)
			    {
				ae->state |= A_HIDDEN;
			    }
			    else
			    {
				ae->state &= ~A_HIDDEN;
			    }
			}
		}
      /* Perform the necessary updates */
	UpdateAfterHide(False);
}

/************************************************************************
 *				 HideGen				*
 ************************************************************************/

PRIVATE void HideGen (gen, hide)
	int	gen;
	Boolean	hide;
{
	int i;
	ATTRENTRY *ae;

      /* Set the hidden flags */
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == ATTR)
		{
			ae = & AE(i);
			if (ae->attr_def->gen == gen)
			{
			    if (hide)
			    {
				ae->state |= A_HIDDEN;
			    }
			    else
			    {
				ae->state &= ~A_HIDDEN;
			    }
			}
		}
      /* Perform the necessary updates */
	UpdateAfterHide(False);
}


/************************************************************************
 *				 HideName				*
 ************************************************************************/

PUBLIC void HideName (name, hide)
	String	name;
	Boolean	hide;
{
	int i;
	ATTRENTRY *ae;

      /* Set the hidden flags */
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == ATTR)
		{
		    ae = & AE(i);
		    if (strcmp (ae->attr_def->name, name) == 0)
		    {
			if (hide)
			{
			    ae->state |= A_HIDDEN;
			}
			else
			{
			    ae->state &= ~A_HIDDEN;
			}
		    }
		}

      /* Perform the necessary updates */
	UpdateAfterHide(False);
}


/************************************************************************
 *				 HideExpr				*
 ************************************************************************/

PRIVATE void HideExpr (expr, hide)
	String	expr;
	Boolean	hide;
{
	int i;
	ATTRENTRY *ae;
	PRIVATE char expbuf[ESIZE];

      /* Compile the regular expression */
	
      /* Set the hidden flags */
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == ATTR)
		{
			ae = & AE(i);
			if (advance (ae->attr_def->name, expbuf) && *loc2 == '\0')
			{
			    if (hide)
			    {
				ae->state |= A_HIDDEN;
			    }
			    else
			    {
				ae->state &= ~A_HIDDEN;
			    }
			}
		}

      /* Perform the necessary updates */
	UpdateAfterHide(False);
}


/************************************************************************
 *				 CancelCB				*
 ************************************************************************/

/* This is the callback attached to the cancel command. It simply
 * pops down the hide popup.
 */

/*ARGSUSED*/
PRIVATE void CancelCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	XtPopdown       (HidePopup);
	XtDestroyWidget (HidePopup);
	SetState (OldState);
}


/************************************************************************
 *			      ConfirmHideCB				*
 ************************************************************************/

/* This is the callback attached to the confirm command.
 */

/*ARGSUSED*/
PRIVATE void ConfirmHideCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	HideExpr (HideString, state == HideAttribute);
}


/************************************************************************
 *			       IncludingsCB				*
 ************************************************************************/

/* This is the callback attached to the including command. (Un)Hides all
 * attributes that were generated by expansion of INCLUDING.
 */

/*ARGSUSED*/
PRIVATE void IncludingsCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	HideGen (1, state == HideAttribute);
}


/************************************************************************
 *			      ConstituentsCB				*
 ************************************************************************/

/* This is the callback attached to the constituents command. (Un)Hides all
 * attributes that were generated by expansion of CONSTITUENT(S).
 */

/*ARGSUSED*/
PRIVATE void ConstituentsCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	HideGen (2, state == HideAttribute);
}


/************************************************************************
 *			         ChainsCB				*
 ************************************************************************/

/* This is the callback attached to the chain command. (Un)Hides all
 * attributes that were generated by expansion of CHAIN.
 */

/*ARGSUSED*/
PRIVATE void ChainsCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	HideGen (3, state == HideAttribute);
}

/************************************************************************
 *			         NonCyclicCB				*
 ************************************************************************/

/* This is the callback attached to the NonCyclic command. (Un)Hides all
 * non-cyclic attributes.
 */

/*ARGSUSED*/
PRIVATE void NonCyclicCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	HideNonCyclic (state == HideAttribute);
}

/************************************************************************
 *				  HideCB				*
 ************************************************************************/

/* This is the callback of the hide and unhide menu items. It creates
 * the hide popup.
 */
static Atom wm_delete_window;

/*ARGSUSED*/
PUBLIC void HideCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	int		hide = (unsigned long) client_data;
	Arg		args[10];
	int		n;
	Position	x, y;
	Widget		paned, form;
	Widget		name, confirm, cancel;
	Widget		includings, constituent, chains, noncyclic;

	char *shell = hide ? "hide" : "unhide";

      /* Popup shell */
	GetPopupPositions (0, &x, &y);
	n = 0;
	XtSetArg (args[n], XtNx, x); n++;
	XtSetArg (args[n], XtNy, y); n++;
	HidePopup = XtCreatePopupShell (shell, transientShellWidgetClass,
						Toplevel, args, n);

      /* Vertical paned and label */
	n=0; paned = CreatePaned ("paned", HidePopup);
	n=0; (void) CreateLabel ("label", paned);

      /* Box to select attribute name */
	n=0;
	form = XtCreateManagedWidget ("selectBox", formWidgetClass,
						paned, args, n);
	n=0;
	strcpy (HideString, "");
	XtSetArg (args[n], XtNstring, HideString); n++;
	XtSetArg (args[n], XtNlength, MAX_NAME_LENGTH); n++;
	XtSetArg (args[n], XtNuseStringInPlace, True); n++;
	XtSetArg (args[n], XtNeditType, XawtextEdit); n++;
	name = XtCreateManagedWidget("name",asciiTextWidgetClass,form,args,n);
	XtSetKeyboardFocus (paned, name);
	
	n=0;
	XtSetArg (args[n], XtNfromHoriz, name); n++;
	CreateCommand (confirm, "confirm", form, ConfirmHideCB, NULL);
	n=0;
	XtSetArg (args[n], XtNfromHoriz, confirm); n++;
	/* CreateCommand (cancel, "cancel", form, CancelCB, NULL);*/

      /* Box to select attribute generation */
	n=0;
	form = XtCreateManagedWidget ("genBox", formWidgetClass, paned, args, n);
	
	n=0;
	CreateCommand (includings, "including", form, IncludingsCB, NULL);
	
	n=0;
	XtSetArg (args[n], XtNfromHoriz, includings); n++;
	CreateCommand (constituent, "constituent", form, ConstituentsCB, NULL);

	n=0;
	XtSetArg (args[n], XtNfromHoriz, constituent); n++;
	CreateCommand (chains, "chain", form, ChainsCB, NULL);

	n=0;
	XtSetArg (args[n], XtNfromHoriz, chains); n++;
	CreateCommand (noncyclic, "Non-cyclic", form, NonCyclicCB, NULL);

	n=0;
	XtSetArg (args[n], XtNfromHoriz, noncyclic); n++;


       /* Box for OK command */
	n=0;
	form = XtCreateManagedWidget ("okBox", formWidgetClass, paned, args, n);
	
	n=0;
	CreateCommand (cancel, "OK", form, CancelCB, NULL);
	
      /* Ready, now popup the dialog */
	XtPopup (HidePopup, XtGrabNone);
	
	/*
       * This is a hack so that wm_delete_window will close 
         the hide menu
       */
       
        /* Register Actions */
       XtAppAddActions (XtWidgetToApplicationContext(HidePopup), hide_actions, XtNumber(hide_actions));

       XtOverrideTranslations(HidePopup, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: close()"));
       
       wm_delete_window = XInternAtom (XtDisplay(HidePopup), "WM_DELETE_WINDOW", False);
       
       XSetWMProtocols (XtDisplay(HidePopup), XtWindow(HidePopup),
			    &wm_delete_window, 1);
      /* Set the state */
	OldState = state;
	SetState (hide ? HideAttribute : UnHideAttribute);
}
