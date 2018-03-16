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
/* $Id: VisitSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: VisitSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitSelect.c				*
 *									*
 *	CONTENTS:	Processing of ButtonPress events in		*
 *			visit-sequence windows				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Graph.h"
#include "Prod.h"
#include "Main.h"
#include "Popup.h"
#include "Visit.h"


/************************************************************************
 *			     Public Variables				*
 ************************************************************************/

/* The selected item, used only for the processing of selections */
PUBLIC tVisitElemSelection VisitSelection;

/* The currently marked element */
PUBLIC tVisitElemSelection VisitMarkedElem = {NULL, NULL};
PUBLIC VSPTR MoveRangeStartElem, MoveRangeEndElem;
PRIVATE int MoveRangeStartNo, MoveRangeEndNo;


/************************************************************************
 *			    VisitElemSelected				*
 ************************************************************************/

PRIVATE Boolean VisitElemSelected (prod, x, y)
	PRODENTRY	*prod;
	Position	x, y;
{
	Position	xl, current_y;
	VSPTR		vselem, last;
	int		no, height;

	if (x < prod->vs->vsar->x ||
	    x > (Position)(prod->vs->vsar->x + prod->vs->width + 2*Res.synt_indent))
		return (False);

	current_y = prod->vs->vsar->y;
	no = 0;
	last = NULL;
	vselem = prod->visitseq;
	for (; vselem != NULL && vselem->next != NULL; vselem = vselem->next)
	{
		height = ElemCritical (prod, vselem, last) ? 
				CrAttrHeight : AttrHeight;
		if (y >= current_y && y < current_y + height)
		{
			if (IS_LEAVE (vselem))
				xl = prod->vs->vsar->x;
			else if (IS_VISIT (vselem))
				xl = prod->vs->vsar->x + 2*Res.synt_indent;
			else
				xl = prod->vs->vsar->x + Res.synt_indent;
			if (xl <= x && x < (Position)(xl + prod->vs->width))
			{
				VisitSelection.prod = prod;
				VisitSelection.elem = vselem;
				VisitSelection.last = last;
				VisitSelection.no   = no;
				return (True);
			}
		}
		if (IS_LEAVE (vselem)) current_y += Res.symb_v_pad;
		current_y += height;

		if (vselem->vscls != VSCOND) last = vselem;
		no++;
	}
	return (False);
}


/************************************************************************
 *			    VisitMarkMoveRange				*
 ************************************************************************/

PRIVATE void VisitMarkMoveRange ()
{
	PRODENTRY	*prod = VisitMarkedElem.prod;
	VSPTR		elem, last;
	int		no;

	MoveRangeStartElem = NULL;
	MoveRangeStartNo   = 0;

	last = NULL;
	no = 0;
	elem = prod->visitseq;
	for (; elem!=NULL && elem->next!=NULL; last=elem, elem=elem->next, no++)
	{
		if (ElemDepends (prod, elem, VisitMarkedElem.elem)) 
		{
			MoveRangeStartElem = elem->next;
			MoveRangeStartNo   = no + 1;
		}

		if (ElemDepends (prod, VisitMarkedElem.elem, elem))
		{
			MoveRangeEndElem = last;
			MoveRangeEndNo   = no - 1;
			return;
		}
	}
	MoveRangeEndElem = last;
	MoveRangeEndNo   = no - 1;
}


/************************************************************************
 *			      VisitMoveElem				*
 ************************************************************************/

PRIVATE void VisitMoveElem ()
{
	PRIVATE char	comment[100];
	PRODENTRY	*prod = VisitMarkedElem.prod;

      /* Allow only moves in the computes move range */
      /* and dont't allow move after a condition */
	if (VisitSelection.no > MoveRangeEndNo ||
	    VisitSelection.no < MoveRangeStartNo ||
	    VisitSelection.elem->vscls == VSCOND)
		return;

      /* Specify the arrange comment */
	sprintf (comment, "Move %s in visit-sequence for rule %s",
			  VisitElemString (VisitMarkedElem.elem), 
			  prod->prod_def->dname);
	ArrangeComment (comment);

      /* Move the element */
	if (VisitSelection.no > VisitMarkedElem.no)
		VisitArrange (prod, VisitMarkedElem.elem, VisitSelection.elem);
	else
		VisitArrange (prod, VisitSelection.elem, VisitMarkedElem.elem);

      /* Unmark the marked element */
	VisitMarkedElem.prod = NULL;
	VisitMarkedElem.elem = MoveRangeStartElem = MoveRangeEndElem = NULL;

      /* Redisplay the windows */
	UpdateVisitSequence (prod);
	RedisplayWidget (prod->vs->vsar->widget);
}


/************************************************************************
 *			      VisitSelectCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitSelectCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	PRODENTRY		*prod = (PRODENTRY *) client_data;
	GraphReturnStruct	*call = (GraphReturnStruct *) call_data;

      /* Process element selection */
	if (VisitElemSelected (prod, call->x, call->y))
	{
	      /* Check for pending attribute (un)hide */
		if ((state == HideAttribute || state == UnHideAttribute) &&
		    VisitSelection.elem->vscls == VSASSIG)
		{
			ATTRENTRY *ae = & AE(VisitSelection.elem->
						  vsinfo.assig.aid);
			HideName (ae->attr_def->name, state == UnHideAttribute);
		}

	      /* Check for hide or unhide action */
		else if ((call->action[ATTR_ACTION] == DO_HIDE ||
			  call->action[ATTR_ACTION] == DO_UNHIDE) &&
			 VisitSelection.elem->vscls == VSASSIG)
		{
			ATTRENTRY *ae = & AE(VisitSelection.elem->
						vsinfo.assig.aid);

			HideName (ae->attr_def->name, 
				  call->action[ATTR_ACTION] == DO_UNHIDE);
		}

	      /* Check for element marking */
		else if ((VisitMarkedElem.prod != prod ||
			  (VisitMarkedElem.elem != VisitSelection.elem &&
			   call->action[ATTR_ACTION] == -1)) &&
			  VisitSelection.elem->vscls != VSCOND)
		{
			tVisitElemSelection OldMark;

			OldMark = VisitMarkedElem;
			VisitMarkedElem = VisitSelection;
			VisitMarkMoveRange();
			if (OldMark.elem != NULL) 
			       RedisplayWidget(OldMark.prod->vs->vsar->widget);
			RedisplayWidget (prod->vs->vsar->widget);
		}

	      /* Check for element unmarking */
		else if (VisitMarkedElem.elem == VisitSelection.elem)
		{
			VisitMarkedElem.prod = NULL;
			VisitMarkedElem.elem = NULL;
			MoveRangeStartElem   = NULL;
			MoveRangeEndElem     = NULL;
			RedisplayWidget (prod->vs->vsar->widget);
		}

	      /* Check for move action */
		else if (call->action[ATTR_ACTION] == DO_MOVE)
			VisitMoveElem ();
	}
}
