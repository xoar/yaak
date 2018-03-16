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
/* $Id: OrdStrategy.c,v 4.5 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: OrdStrategy.c,v 4.5 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/OrderStrategy.c				*
 *									*
 *	CONTENTS:	Routines dealing with the different computation	*
 *			strategies provided by order			*
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

#include <X11/StringDefs.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>


/************************************************************************
 *			     Public Variables				*
 ************************************************************************/

/* Variables used to influence order 
PUBLIC bool 
    AUTOMATICALLY = FALSE,
    ARRANGE = FALSE,
    PARSE_TIME = FALSE,
    TREE_BOTTOM_UP = FALSE,
    TREE_TOP_DOWN = FALSE,
    TREE_COMPLETE = FALSE,
    DEFAULT_TREE_COMPLETE = TRUE;
    */

/* Variables indicating the active partition and topological strategies */
PRIVATE Widget ActivePartItem, ActiveTopoItem;
PRIVATE int    PartCurrent,    TopoCurrent;


/************************************************************************
 *	     Description of the possible partition strategies		*
 ************************************************************************/

/* Names of possible partition strategies.
 * For each given strategy name a corresponding menu item in the
 * partition strategy menu is created.
 */
PRIVATE String PartStrategies[] = {
	"branchAndBound",	/* Partition strategy number 0 */
	"early",		/* Partition strategy number 1 */
	"late",			/* Partition strategy number 2 */
};

/* Public variables influencing the computation of partitions.
 * The given initializers represent the default partition strategy, the 
 * actual values can be changed by the user by inserting order options in
 * the control file, or by menu selection at runtime of this tool.
 */
/*
  PUBLIC bool PART_EARLY = FALSE,  PART_LATE = TRUE,
*/

/* Initialization of the partition strategy number.
 * The public variables described above could have been changed during the
 * processing of order options in the IDL interface, so we have to look at
 * the actual values.
 */
PRIVATE void InitializePartitionStrategy()
{
	if (PART_EARLY)		PartCurrent = 1;
	else 				PartCurrent = 2;
}

/* Update of the public variables after the partition strategy number
 * was changed by the user.
 */
PRIVATE void UpdatePartitionStrategy()
{
	PART_EARLY		= (PartCurrent == 1);
	PART_LATE		= (PartCurrent == 2);
}


/************************************************************************
 *	    Description of the possible topological strategies		*
 ************************************************************************/

/* Names of possible topological strategies.
 * For each given strategy name a corresponding menu item in the
 * topological strategy menu is created.
 */
PRIVATE String TopoStrategies[] = {
	"early",			/* Topological strategy number 0 */
};

/* Public variables influencing the computation of visit-sequences.
 * The given initializers represent the default topolocigal strategy, the
 * actual values can be changed by the user by inserting order options in
 * the control file, or by menu selection at runtime of this tool.
 */
/* PUBLIC bool example = TRUE; */

/* Initialization of the topological strategy number.
 * The public variables described above could have been changed during the
 * processing of order options in the IDL interface, so we have to look at
 * the actual values.
 */
PRIVATE void InitializeTopologicalStrategy()
{
	/* if (example) */		 TopoCurrent = 0;
}

/* Update of the public variables after the topological strategy number
 * was changed by the user.
 */
PRIVATE void UpdateTopologicalStrategy()
{
	/* example		= (TopoCurrent == 0); */
}


/************************************************************************
 *			      PartStrategyCB				*
 ************************************************************************/

/* This is the callback attached to the partition strategy menu items.
 */

/*ARGSUSED*/
PRIVATE void PartStrategyCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	Arg args[2];

      /* Set the new strategy */
	PartCurrent = (unsigned long) client_data;

      /* Remove old checkmark */
	XtSetArg (args[0], XtNleftBitmap, None);
	XtSetValues (ActivePartItem, args, 1);

      /* Set new checkmark */
	XtSetArg (args[0], XtNleftBitmap, CheckMarkBitmap);
	XtSetValues (ActivePartItem = w, args, 1);

      /* Set the new parameters and start computation */
	UpdatePartitionStrategy();
	RecomputeCB ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);
}


/************************************************************************
 *			     AutomaticallyCB				*
 ************************************************************************/

/* This is the callback attached to the automatically menu item.
 */

/*ARGSUSED*/
PRIVATE void AutomaticallyCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	Arg args[2];

      /* Toggle the automatically flag */
	AUTOMATICALLY = ! AUTOMATICALLY;

      /* Toggle the checkmark of the automatically menu item */
	XtSetArg (args[0], XtNleftBitmap, AUTOMATICALLY ? CheckMarkBitmap:None);
	XtSetValues (w, args, 1);

      /* Start new computation */
	RecomputeCB ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);
}


/************************************************************************
 *			      CreatePartMenu				*
 ************************************************************************/

/* Creates a menu to allow the selection of a partition strategy.
 */

PUBLIC void CreatePartMenu (father)
	Widget father;
{
	Widget	menu, item;
	Arg	args[2];
	int	n = 0, i;

      /* Initialize the description of the current strategy */
	InitializePartitionStrategy();

      /* Create surrounding simple menu */
	n = 0;
	menu = CreateMenu ("partitionMenu", father);

      /* Create a menu item for each partition strategy */
	n = 1;
	for (i = 0; i < XtNumber (PartStrategies); i++)
	{
		XtSetArg (args[0], XtNleftBitmap,
			  i == PartCurrent ? CheckMarkBitmap : None);
		CreateMItem (item, PartStrategies[i], menu, PartStrategyCB, (unsigned long)i);
		if (i == PartCurrent) ActivePartItem = item;
	}

      /* Create the arrange automatically item */
	n = 0;
	CreateMLine (item, "line", menu);

	n = 1;
	XtSetArg (args[0], XtNleftBitmap, AUTOMATICALLY ? CheckMarkBitmap:None);
	CreateMItem (item, "automatically", menu, AutomaticallyCB, NULL);
}


/************************************************************************
 *			      TopoStrategyCB				*
 ************************************************************************/

/* This is the callback attached to the topological strategy menu items.
 */

/*ARGSUSED*/
PRIVATE void TopoStrategyCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
	Arg args[2];

      /* Set the new strategy */
	TopoCurrent = (unsigned long) client_data;

      /* Remove old checkmark */
	XtSetArg (args[0], XtNleftBitmap, None);
	XtSetValues (ActiveTopoItem, args, 1);

      /* Set new checkmark */
	XtSetArg (args[0], XtNleftBitmap, CheckMarkBitmap);
	XtSetValues (ActiveTopoItem = w, args, 1);

      /* Set the new parameters and start computation */
	UpdateTopologicalStrategy();
	RecomputeCB ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);
}


/************************************************************************
 *			      CreateTopoMenu				*
 ************************************************************************/

/* Creates a menu to allow the selection of the topological strategy.
 */

PUBLIC void CreateTopoMenu (father)
	Widget father;
{
	Widget	menu, item;
	Arg	args[2];
	int	n = 0, i;

      /* Initialize the description of the current strategy */
	InitializeTopologicalStrategy();

      /* Create surrounding simple menu */
	n = 0;
	menu = CreateMenu ("topologicalMenu", father);

      /* Create a menu item for each topological strategy */
	n = 1;
	for (i = 0; i < XtNumber (TopoStrategies); i++)
	{
		XtSetArg (args[0], XtNleftBitmap,
			  i == TopoCurrent ? CheckMarkBitmap : None);
		CreateMItem (item, TopoStrategies[i], menu, TopoStrategyCB, (unsigned long)i);
		if (i == TopoCurrent) ActiveTopoItem = item;
	}
}
