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
/* $Id: MainList.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: MainList.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/MainList.c					*
 *									*
 *	DESCRIPTION:	Visual lists of productions and symbols		*
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
#include "Popup.h"
#include "Main.h"

#include <X11/StringDefs.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/List.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Toggle.h>


/************************************************************************
 *			     Global Variables				*
 ************************************************************************/

/* State of the lists */
PRIVATE int	ProdMask, SymbMask;
PRIVATE Widget	ProdListView, SymbolListView, ProdListWidget, SymbolListWidget;
PRIVATE Widget	ProdCyclic, ProdArranged, ProdChanged, ProdVisitSeq;
PRIVATE Widget	SymbCyclic, SymbArranged, SymbChanged, SymbPartitioned;

/* The lists */
PRIVATE String	*ProdList, 	*SymbolList;
PRIVATE int	ProdListSize,	SymbolListSize;


/************************************************************************
 *				strcompare				*
 ************************************************************************/

/* This is the function used to compare two strings while sorting
 * the lists of productions and symbols.
 */

PRIVATE int strcompare (s1, s2)
	char **s1, **s2;
{
	return (strcmp (*s1, *s2));
}

#if defined(__cplusplus) || defined(__STDC__)
typedef int (*comparefunc)(const void *, const void *);
#endif

/************************************************************************
 *			       ProdFillList				*
 ************************************************************************/

/* Fills the list of productions with all productions matching the
 * condition (prod->state & ProdMask) == True.
 */

PRIVATE void ProdFillList()
{
	int i;

      /* Fill the list with the dname entries of the productions */
	ProdListSize = 0;
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD && (PE(i).state & ProdMask))
			ProdList[ProdListSize++] = PE(i).prod_def->dname;

      /* Sort the list and check for empty list */
	if (ProdListSize == 0)
	{
		ProdList[0] = Res.str_empty;
		ProdListSize = 1;
	}
	else if (Res.sort_prod_list)
#if defined(__cplusplus) || defined(__STDC__)
		qsort ((char *) &ProdList[0], ProdListSize,
			sizeof(String), (comparefunc)strcompare);
#else
		qsort ((char *) &ProdList[0], ProdListSize,
			sizeof(String), strcompare);
#endif
}


/************************************************************************
 *			       SymbFillList				*
 ************************************************************************/

/* Fills the list of symbols with all symbols matching the
 * condition (symb->state & SymbMask) == True.
 */

PRIVATE void SymbFillList()
{
	int i;

      /* Fill the list with the dname entries of the symbols */
	SymbolListSize = 0;
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == SYMB && (SE(i).state & SymbMask))
			SymbolList[SymbolListSize++] = SE(i).symb_def->dname;

      /* Sort the list and check for empty list */
	if (SymbolListSize == 0)
	{
		SymbolList[0] = Res.str_empty;
		SymbolListSize = 1;
	}
	else if (Res.sort_symb_list)
#if defined(__cplusplus) || defined(__STDC__)
 		qsort ((char *) &SymbolList[0], SymbolListSize, 
			sizeof (String), (comparefunc)strcompare);
#else
 		qsort ((char *) &SymbolList[0], SymbolListSize, 
			sizeof (String), strcompare);
#endif
}


/************************************************************************
 *			     ProdSelectItemCB				*
 ************************************************************************/

/* This is the Callback used for item selection in the production list.
 * It opens a new production window displaying the selected production.
 * If the selected production is cyclic, the cycle is marked.
 */

/*ARGSUSED*/
PRIVATE void ProdSelectItemCB (w, client_data, call_data)
        Widget  w;
        XtPointer client_data;
        XtPointer call_data;
{
	XawListReturnStruct	*item = (XawListReturnStruct *) call_data;
	PRODENTRY		*prod;
	int			pid;

      /* Check for selection during recomputation */
	if ((int)(state) <= (int)(ReftabAdditions)) return;

      /* Check for selection in an empty list */
	if (strcmp (item->string, Res.str_empty) == 0)
	{
		XawListUnhighlight (ProdListWidget);
		return;
	}

      /* Lookup the production entry in ref_tab */
	pid  = lookupProdByName (item->string) -> did;
	prod = & PE(pid);

      /* If cyclic production, mark the cycle */	
	if (prod->state & S_CYCLIC)
	{
		SLNODE		*nd;
		ATTRENTRY	*ae;

		if (ProdSearchCycle (prod, &nd, &ae))
			ProdFindPath (prod, nd, nd, ae, ae, 0);
		else
			Message (0, "No cycle found, internal inconsistency");
	}

      /* Create the new window */
	ProdCreateNew (pid);
	XawListUnhighlight (ProdListWidget);
}


/************************************************************************
 *			     SymbSelectItemCB				*
 ************************************************************************/

/* This is the Callback used for item selection in the production list.
 * It opens a new production window displaying the selected production.
 * If the selected production is cyclic, the cycle is marked.
 */

/*ARGSUSED*/
PRIVATE void SymbSelectItemCB (w, client_data, call_data)
        Widget  w;
        XtPointer client_data;
        XtPointer call_data;
{
	XawListReturnStruct	*item = (XawListReturnStruct *) call_data;

	int		sid;
	SYMBENTRY	*symb;
	
      /* Check for selection during recomputation */
	if ((int)(state) <= (int)(ReftabAdditions)) return;

      /* Check for selection in an empty list */
	if (strcmp (item->string, Res.str_empty) == 0)
	{
		XawListUnhighlight (SymbolListWidget);
		return;
	}

      /* Lookup the symbol entry in ref_tab */
	sid  = lookupSymbByName (item->string) -> did;
	symb = & SE(sid);

      /* If cyclic symbol, mark the cycle */	
	if (symb->state & S_CYCLIC)
	{
		ATTRENTRY	*ae;

		if (SymbSearchCycle (symb, &ae))
			SymbFindPath (symb, ae, ae, 0);
		else
			Message (0, "No cycle found, internal inconsistency");
	}

      /* Create the new window */
	SymbCreateNew (symb->symb_def->did);
	XawListUnhighlight (SymbolListWidget);
}


/************************************************************************
 *			      ProdUpdateList				*
 ************************************************************************/

/* Updates the displayed list of productions. This is called in two cases:
 * 	1. The state of a production changes.
 *	2. The production selection mask is changed.
 */

PUBLIC void ProdUpdateList ()
{
	ProdFillList ();
	XawListChange (ProdListWidget, ProdList, ProdListSize, 0, True);
}


/************************************************************************
 *			      SymbUpdateList				*
 ************************************************************************/

/* Updates the displayed list of symbols. This is called in two cases:
 * 	1. The state of a symbol changes.
 *	2. The symbol selection mask is changed.
 */

PUBLIC void SymbUpdateList ()
{
	SymbFillList ();
	XawListChange (SymbolListWidget, SymbolList, SymbolListSize, 0, True);
}


/************************************************************************
 *			       ProdSwitchCB				*
 ************************************************************************/

/* This is the callback used for changes in the production selection
 * mask. It is invoced from a toggle widget.
 */

/*ARGSUSED*/
PRIVATE void ProdSwitchCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer call_data;
{
	int mask    = (unsigned long) client_data;	/* The bit to switch */
	int set = (unsigned long) call_data;	/* The desired state */

	if (set)	ProdMask |= mask;
	else 		ProdMask &= ~mask;
	ProdUpdateList ();
}


/************************************************************************
 *			       SymbSwitchCB				*
 ************************************************************************/

/* This is the callback used for changes in the symbol selection
 * mask. It is invoced from a toggle widget.
 */

/*ARGSUSED*/
PRIVATE void SymbSwitchCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer call_data;
{
	int mask    = (unsigned long) client_data;	/* The bit to switch */
	int set = (unsigned long) call_data;	/* The desired state */

	if (set)	SymbMask |= mask;
	else 		SymbMask &= ~mask;
	SymbUpdateList ();
}


/************************************************************************
 *			      ProdCreateList				*
 ************************************************************************/

/* Allocates and fills the production list, creates the corresponding
 * list widget.
 */

PUBLIC void ProdCreateList (hpaned, father)
	Widget hpaned, father;
{
	int	i;
	Arg	args[5];
	int	n;
	Widget	form, label;

      /* Create surrounding form widget */
	n = 0; form = CreateForm ("rules", hpaned);

      /* Create description label */
	n = 0; label = CreateLabel ("rules", form);

      /* Create toggles */
	n = 0;
	XtSetArg (args[n], XtNstate, True); n++;
	XtSetArg (args[n], XtNfromHoriz, label); n++;
	CreateToggle (ProdCyclic,   "cyclic",   form, ProdSwitchCB, S_CYCLIC);

	XtSetArg (args[n-1], XtNfromHoriz, ProdCyclic);
	CreateToggle (ProdArranged, "arranged", form, ProdSwitchCB, S_ARRANGED);

	XtSetArg (args[n-1], XtNfromHoriz, ProdArranged);
	CreateToggle (ProdChanged,  "changed",  form, ProdSwitchCB, S_CHANGED);

	XtSetArg (args[n-1], XtNfromHoriz, ProdChanged);
	CreateToggle (ProdVisitSeq, "visitSeq", form, ProdSwitchCB,S_VISIT_SEQ);

      /* Count the productions and allocate space */
	ProdListSize = 0;
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD) ProdListSize ++;
	ProdList = (String *) XtMalloc (sizeof (String) * (1+ProdListSize));
	ProdMask = S_CYCLIC | S_ARRANGED | S_CHANGED | S_VISIT_SEQ;

      /* Fill the list */
	ProdFillList();

      /* Create the surrounding viewport widget */
	n = 0;
	ProdListView = CreateView ("prodListView", father);

      /* Create the corresponding list widget for the production list */
	n = 0;
	XtSetArg (args[n], XtNlist, ProdList); n++;
	XtSetArg (args[n], XtNnumberStrings, ProdListSize); n++;
	ProdListWidget = CreateList ("prodList", ProdListView);
	XtAddCallback (ProdListWidget, XtNcallback,
			ProdSelectItemCB, (XtPointer) NULL);
}


/************************************************************************
 *			      SymbCreateList				*
 ************************************************************************/

/* Allocates and fills the symbols list, creates the corresponding
 * list widget.
 */

PUBLIC void SymbCreateList (hpaned, father)
	Widget hpaned, father;
{
	int	i;
	Arg	args[5];
	int	n;
	Widget	form, label;

      /* Create surrounding form widget */
	n = 0; form = CreateForm ("symbols", hpaned);

      /* Create description label */
	n = 0; label = CreateLabel ("symbols", form);

      /* Create toggles */
	n = 0;
	XtSetArg (args[n], XtNstate, True); n++;
	XtSetArg (args[n], XtNfromHoriz, label); n++;
	CreateToggle (SymbCyclic,   "cyclic",   form, SymbSwitchCB, S_CYCLIC);

	XtSetArg (args[n-1], XtNfromHoriz, SymbCyclic);
	CreateToggle (SymbArranged, "arranged", form, SymbSwitchCB, S_ARRANGED);

	XtSetArg (args[n-1], XtNfromHoriz, SymbArranged);
	CreateToggle (SymbChanged,  "changed",  form, SymbSwitchCB, S_CHANGED);

	XtSetArg (args[n-1], XtNfromHoriz, SymbChanged);
	CreateToggle (SymbPartitioned, "partitioned", form,
			SymbSwitchCB, S_PARTITIONED);

      /* Count the symbols and allocate space */
	SymbolListSize = 0;
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == SYMB) SymbolListSize ++;
	SymbolList = (String *) XtMalloc (sizeof (String) * (1+SymbolListSize));
	SymbMask = S_CYCLIC | S_ARRANGED | S_CHANGED | S_PARTITIONED;

      /* Fill the list */
	SymbFillList();

      /* Create the surrounding viewport widget */
	n = 0;
	SymbolListView = CreateView ("symbolListView", father);

      /* Create the corresponding list widget for the list of symbols */
	n = 0;
	XtSetArg (args[n], XtNlist, SymbolList); n++;
	XtSetArg (args[n], XtNnumberStrings, SymbolListSize); n++;
	SymbolListWidget = CreateList ("symbolList", SymbolListView);
	XtAddCallback (SymbolListWidget, XtNcallback, 
			SymbSelectItemCB, (XtPointer) NULL);
}


/************************************************************************
 *			       SetListMasks				*
 ************************************************************************/

/* Sets the symbol and production masks to a reasonable value. This is
 * called after every complete order computation. 
 */

PUBLIC void SetListMasks ()
{
	static Arg on[]  = {{XtNstate, (XtArgVal) True}};
	static Arg off[] = {{XtNstate, (XtArgVal) False}};

	XtSetValues (ProdArranged, off, 1);
	XtSetValues (ProdChanged,  off, 1);
	XtSetValues (SymbArranged, off, 1);
	XtSetValues (SymbChanged,  off, 1);

	if (Cyclic)
	{
		ProdMask = S_CYCLIC;
		SymbMask = S_CYCLIC;
		XtSetValues (ProdCyclic,      on,  1);
		XtSetValues (ProdVisitSeq,    off, 1);
		XtSetValues (SymbCyclic,      on,  1);
		XtSetValues (SymbPartitioned, off, 1);
	}
	else
	{
		ProdMask = S_VISIT_SEQ;
		SymbMask = S_PARTITIONED;
		XtSetValues (ProdCyclic,      off, 1);
		XtSetValues (ProdVisitSeq,    on,  1);
		XtSetValues (SymbCyclic,      off, 1);
		XtSetValues (SymbPartitioned, on,  1);
	}

	ProdUpdateList ();
	SymbUpdateList ();
}
