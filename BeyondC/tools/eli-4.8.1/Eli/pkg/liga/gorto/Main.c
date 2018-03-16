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
/* $Id: Main.c,v 4.7 1999/07/26 08:38:09 mjung Exp $ */
static char rcs_id[]= "$Id: Main.c,v 4.7 1999/07/26 08:38:09 mjung Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/Main.c					*
 *									*
 *	DESCRIPTION:	Main Module of GORTO (Graphical Order Tool)	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Main.h"
#include "../middle/order/reftab.h"
#include "../middle/order/option.h"
#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>

/************************************************************************
 *			   Command line options				*
 ************************************************************************/

/* These are the additions to the standard X Toolkit command line options */
PRIVATE XrmOptionDescRec gorto_options[] = {
{"-input",	"inputName",	XrmoptionSepArg, (XtPointer) NULL},
{"-output",	"outputName",	XrmoptionSepArg, (XtPointer) NULL},
{"-lido",	"lidoName",	XrmoptionSepArg, (XtPointer) NULL},
{"-ctrl",	"controlName",	XrmoptionSepArg, (XtPointer) NULL},
{"-lcl",	"lclName",	XrmoptionSepArg, (XtPointer) NULL},
};

PRIVATE String known_options =
"Gorto accepts all standard X Toolkit options and the following:\n\
\n\
-input <filename>       Name of the IDL input file.\n\
-output <filename>      Name of the IDL output file.\n\
-lido <filename>        Name of the LIDO source file.\n\
-ctrl <filename>	Name of the order_option file.\n\
-lcl <filename>         Name of the LCL output file.\n\
\n";

/***********************************************************************\
*			Global variable definitions			*
\***********************************************************************/

Widget		Toplevel;
String		ProgName;
XtAppContext	app_context;

/************************************************************************
 *				 Actions				*
 ************************************************************************/

PRIVATE XtActionsRec gorto_actions[] = {
{"menu-popup",		ActionMenuPopup},
{"close-window",	ActionCloseWindow},
{"quit2010",		QuitCB},
};

/************************************************************************
 *				  Usage					*
 ************************************************************************/

/* Prints out the command line usage. The given arguments represent
 * unknown options, that were not accepted by the X Toolkit.
 */

PRIVATE void Usage (argc, argv)
	int	argc;
	char	*argv[];
{
	int i;

	fprintf (stderr, "%s: Unknown option:", ProgName);
	for (i=1; i<argc; i++)
		fprintf (stderr, " %s", argv[i]);
	fprintf (stderr, "\n");
	fprintf (stderr, "%s", known_options);
	exit(1);
}


/************************************************************************
 *				  EFopen				*
 ************************************************************************/

/* Opens a file <name> in the given <mode>. Exits if fopen() fails.
 */

PRIVATE FILE *EFopen (file, mode) 
	char *file, *mode;
{
	FILE *fp, *fopen();

      /* Try to open the file */
	if ((fp = fopen (file, mode)) != NULL)
		return (fp);

      /* Open failed, print a message and die */
	fprintf (stderr, "%s: can't open file %s mode %s\n",
			 ProgName, file, mode);
	exit(1);
}

	
/************************************************************************
 *				  OpenIO				*
 ************************************************************************/

/* Opens the input and output files. 
 */

PRIVATE void OpenIO()
{
	if (Res.input_name != NULL)
		In= EFopen (Res.input_name, "r");
	if (Res.output_name != NULL)
		Out= EFopen (Res.output_name, "w");
	if (Res.lcl_name != NULL)
		LCL= EFopen (Res.lcl_name, "w");
}


/************************************************************************
 *				   main					*
 ************************************************************************/
static Atom wm_delete_window;

PUBLIC int main (argc, argv)
	int argc;
	char *argv[];
{
	Arg args[1];

      /* Assign File Pointers */ 
	In = stdin;
	ProtocolFile = stderr;
	LCL = stdout;
	BuProdFile = stdout;

      /* Remember name of program */
	ProgName = *argv;

      /* Initialize the X Toolkit */
	Toplevel = XtAppInitialize (&app_context, "Gorto",
			gorto_options, XtNumber (gorto_options),
			&argc, argv, NULL, NULL, 0);
	if (argc != 1) Usage (argc, argv);

      /* Initializations */
	dpy = XtDisplay (Toplevel);	/* Remember display */
	ReadResources();		/* Load ressources */
	LoadBitmaps();			/* Construct bitmaps */

      /* Register Actions */
	XtAppAddActions (app_context, gorto_actions, XtNumber(gorto_actions));


      /* Set the icon bitmap */
	XtSetArg (args[0], XtNiconPixmap, IconBitmap);
	XtSetValues (Toplevel, args, 1);

      /* Perform steps necessary to realize main window */
	OpenIO();			/* Open I/O files */
	ISexp = ligain (In);		/* Read IDL structure */
	find_max_did (ISexp);

      /* read in options for order, set switches only: */
	if (Res.control_name != NULL)	/* read file with order options */
	   read_orderOption(Res.control_name);
	
	order_init_ref_tab (ISexp);		/* Initialize ref_tab */

	CreateWidgets ();		/* Instantiate widgets of main window */
	CallOrder();			/* Initiate further order computation */
	XtRealizeWidget (Toplevel);	/* Realize main window */

	/*
       * This is a hack so that wm_delete_window (clicking on the windows X mark)
         will lead to quitting gorto smoothly
       */
     
       XtOverrideTranslations(Toplevel, 
		    XtParseTranslationTable ("<Message>WM_PROTOCOLS: quit2010()"));
       wm_delete_window = XInternAtom (XtDisplay(Toplevel), "WM_DELETE_WINDOW",
				    False);
       XSetWMProtocols (XtDisplay(Toplevel), XtWindow(Toplevel),
			    &wm_delete_window, 1);
				    		    
      /* Perform the further computation and process X input */
	XtAppMainLoop (app_context);
	
	return (0);
}
