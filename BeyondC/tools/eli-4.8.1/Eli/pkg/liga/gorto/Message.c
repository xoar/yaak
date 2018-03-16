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
/* $Id: Message.c,v 4.2 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: Message.c,v 4.2 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Popup/Message.c					*
 *									*
 *	CONTENTS:	Implementation of messages to the user		*
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
#include "Popup.h"

#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Dialog.h>
#include <X11/Xaw/Command.h>


/************************************************************************
 *			Private widget definitions			*
 ************************************************************************/

PRIVATE Widget Popup, Dialog, Confirm;
PRIVATE void ConfirmMessageCB();
PRIVATE XtActionsRec mess_actions[] = {
{"close",	ConfirmMessageCB},
};

/************************************************************************
 *			     ConfirmMessageCB				*
 ************************************************************************/

/* Callback used for confirming the message.
 */

/*ARGSUSED*/
PRIVATE void ConfirmMessageCB (w, client_data, call_data)
        Widget  w;
        XtPointer client_data;
        XtPointer call_data;
{
	XtPopdown	(Popup);
	XtDestroyWidget	(Popup);
}


/************************************************************************
 *				 Message				*
 ************************************************************************/

/* Gives the message <message> to the user and prompts for a confirm.
 * The popup window is placed over the window of the specified production
 * or symbol with did <did>.
 */
static Atom wm_delete_window;

PUBLIC void Message (did, message)
	int	did;
	String	message;
{
	Arg		args[10];
	int		n;
	Position	x,y;

      /* Popup shell */
	GetPopupPositions (did, &x, &y);
        n = 0;
        XtSetArg (args[n], XtNx, x); n++;
        XtSetArg (args[n], XtNy, y); n++;
        Popup = XtCreatePopupShell ("Message", transientShellWidgetClass,
                                                Toplevel, args, n);

      /* Dialog */
	n = 0;
	XtSetArg (args[n], XtNlabel, message); n++;
	Dialog = CreateDialog ("msg", Popup);

      /* Confirm */
	n = 0;
	CreateCommand (Confirm, "Ok", Dialog, ConfirmMessageCB, NULL);

      /* Popup the message */
	XtPopup (Popup, XtGrabExclusive);
	
	      
        /* Register Actions */
       XtAppAddActions (XtWidgetToApplicationContext(Popup), mess_actions, XtNumber(mess_actions));

       XtOverrideTranslations(Popup, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: close()"));
       
       wm_delete_window = XInternAtom (XtDisplay(Popup), "WM_DELETE_WINDOW", False);
       
       XSetWMProtocols (XtDisplay(Popup), XtWindow(Popup),
			    &wm_delete_window, 1);
	
}
