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
/* $Id: SymbSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: SymbSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbSelect.c				*
 *									*
 *	CONTENTS:	Processing of ButtonPress events in 		*
 *			symbol windows					*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Main.h"
#include "Graph.h"
#include "Popup.h"
#include "Symb.h"


/************************************************************************
 *                           Global Variables                           *
 ************************************************************************/

PUBLIC tSymbSelection		SymbSelection;
PUBLIC tSymbAttrSelection	SymbMarkedAttr;
PUBLIC Boolean			SplitPending = False;
PUBLIC ATTRENTRY		*SplitAfter  = NULL;


/************************************************************************
 *			     SymbAttrSelected				*
 ************************************************************************/

/* Tests all attribute instances of the given symbol <symb> against
 * the selected point (<x>,<y>). If a match is found, the parameter
 * selected_no contains the description.
 */

PRIVATE Boolean SymbAttrSelected (symb, x, y)
	SYMBENTRY	*symb;
	Position	x, y;
{
	Position	current_y;
	ATTRENTRY	*ae;

      /* Check the enclosing rectangle first */
	if (x < symb->sar->x || x > (Position)(symb->sar->x + symb->sar->width) ||
	    y < symb->sar->y || y > (Position)(symb->sar->y + symb->sar->height))
		return (False);

      /* Loop over all attribute instances */
	current_y = symb->sar->y + 2*Res.text_pad +
			Res.bold_font->ascent + Res.bold_font->descent;
	for (ae = symb->first_attr; ae != NULL;
		current_y += ae->state & A_CRITICAL ? CrAttrHeight : AttrHeight,
		ae = ae->next)
	{
	      /* Check x-coordinate */
		if (CLASS(ae) == 0)
		{
			if (x < symb->sar->x + Res.synt_indent) continue;
		}
		else
		{
			if (x > (Position)(symb->sar->x+symb->sar->width-Res.synt_indent))
				continue;
		}

	      /* Check y-coordinate */
		if (y < current_y || 
		    y >= current_y + (ae->state & A_CRITICAL ?
				       CrAttrHeight : AttrHeight))
			continue;

	      /* Found the selected attribute instance */
		SymbSelection.type = SymbAttr;
		SymbSelection.detail.attr.symb = symb;
		SymbSelection.detail.attr.ae   = ae;
		SymbSelection.detail.attr.y    = current_y;
		return (True);
	}

      /* No match found */
	return (False);
}


/************************************************************************
 *			       SymbMoveAttr				*
 ************************************************************************/

PRIVATE void SymbMoveAttr (symb)
	SYMBENTRY	*symb;
{
      /* Allow only moves of non-critical attributes */
	if (SymbMarkedAttr.ae->state & A_CRITICAL) return;

      /* Allow only moves into partitions of the correct class */
	if (CLASS(SymbSelection.detail.attr.ae) != CLASS (SymbMarkedAttr.ae))
		return;

      /* Now move the attribute */
	MoveAttr (symb, SymbMarkedAttr.ae, SymbSelection.detail.attr.ae);
	SymbMarkedAttr.symb = NULL;
	SymbMarkedAttr.ae   = NULL;

      /* Perform partial recomputation and window updates */
	SymbRecomputePartition (symb);
}


/************************************************************************
 *			   SymbAppendPartition				*
 ************************************************************************/

PRIVATE void SymbAppendPartition (symb)
	SYMBENTRY *symb;
{
	Boolean front = (SymbSelection.detail.attr.ae->part ==
			 symb->first_attr->part);

      /* Check for correct input */
	if (front)
	{
		if (CLASS(SymbMarkedAttr.ae) == CLASS(symb->first_attr)) return;
	}
	else
	{
		if (SymbSelection.detail.attr.ae->part != symb->last_attr->part)
			return;

		if (CLASS(SymbMarkedAttr.ae) == CLASS(symb->last_attr)) return;
	}

      /* Perform the partition append */
	if (front)    AppendFrontPartition (symb, SymbMarkedAttr.ae, 
						  SymbSelection.detail.attr.ae);
	else	      AppendRearPartition  (symb, SymbMarkedAttr.ae,
						  SymbSelection.detail.attr.ae);
	SymbMarkedAttr.symb = NULL;
	SymbMarkedAttr.ae   = NULL;

      /* Perform partial recomputation and window updates */
	SymbRecomputePartition (symb);
}


/************************************************************************
 *			    SymbSplitPartition				*
 ************************************************************************/

PRIVATE void SymbSplitPartition (symb)
	SYMBENTRY *symb;
{
	ATTRENTRY *with  = SymbMarkedAttr.ae;
	ATTRENTRY *after = SymbSelection.detail.attr.ae;

      /* Allow only split of partitions of the correct class */
	if (CLASS(after) == CLASS(with)) return;

      /* Allow only split of partitions with >= 2 attributes */
	if ((after->last == NULL || CLASS(after) != CLASS(after->last)) &&
	    (after->next == NULL || CLASS(after) != CLASS(after->next)))
		return;

      /* Now split the partition */
	SplitPartition (symb, with, after);
	if (! SplitPending)
	{
	      /* Unmark the marked attribute */
		SymbMarkedAttr.symb = NULL;
		SymbMarkedAttr.ae   = NULL;

	      /* Perform partial recomputation and window updates */
		SymbRecomputePartition (symb);
	}
	else
	{
		SymbUpdateState (symb);
		RedisplayGraphOfDid (symb->symb_def->did);
	}
}


/************************************************************************
 *			    SymbCompleteSplit				*
 ************************************************************************/

PRIVATE void SymbCompleteSplit (symb)
	SYMBENTRY *symb;
{
      /* Allow only splitting before attributes of the correct class */
	if (CLASS(SplitAfter) != CLASS(SymbSelection.detail.attr.ae)) return;

      /* Perform the actual split */
	PerformSplit (symb, SymbMarkedAttr.ae, SplitAfter, 
			    SymbSelection.detail.attr.ae);

      /* Unmark the marked attribute */
	SymbMarkedAttr.symb = NULL;
	SymbMarkedAttr.ae   = NULL;

      /* Perform partial recomputation and window updates */
	SymbRecomputePartition (symb);
}


/************************************************************************
 *				SymbFollow				*
 ************************************************************************/

PRIVATE void SymbFollow (symb, close)
	SYMBENTRY	*symb;
	Boolean		close;
{
	tSymbDepSelection *detail = & SymbSelection.detail.dep;

	if (*detail->dep & (T_DIR | T_IND))
	{
		if (close)
		{
			SymbCloseAllCB ((Widget) NULL, (caddr_t) symb,
					(caddr_t) NULL);
			ProdCloseAllCB ((Widget) NULL, (caddr_t) NULL,
					(caddr_t) NULL);
		}
		SymbFindPath (symb, detail->ae1, detail->ae2, 1);
	}
}


/************************************************************************
 *			      SymbRemoveDep				*
 ************************************************************************/

PRIVATE void SymbRemoveDep (symb)
	SYMBENTRY *symb;
{
	if ((*SymbSelection.detail.dep.dep & T_MASK) == T_ARR)
	{
		RemoveArrangeNode (SymbSelection.detail.dep.det->arrange.node);
		*SymbSelection.detail.dep.dep = 0;
		DepRemoved = True;

	      /* Perform partial recomputation and window updates */
		SymbRecomputePartition (symb);
	}
}


/************************************************************************
 *			       SymbSelectCB				*
 ************************************************************************/

/* This is the callback used for selections on a symbol window.
 */

/*ARGSUSED*/
PUBLIC void SymbSelectCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	SYMBENTRY		*symb = (SYMBENTRY *) client_data;
	GraphReturnStruct	*call = (GraphReturnStruct *) call_data;

	SymbSelection.type = SymbNothing;

      /* Process attribute selection */
	if (SymbAttrSelected (symb, call->x, call->y))
	{
	      /* Check for pending partition split */
		if (SplitPending && SymbMarkedAttr.symb == symb)
		{
			SymbCompleteSplit (symb);
			return;
		}
		SplitPending = False;

	      /* Check for pending attribute (un)hide */
		if (state == HideAttribute || state == UnHideAttribute)
			HideName (SymbSelection.detail.attr.ae->attr_def->name,
				  state == HideAttribute);

	      /* Check for hide action */
		else if (call->action[ATTR_ACTION] == DO_HIDE)
			HideName (SymbSelection.detail.attr.ae->attr_def->name,
				  True);

	      /* Check for unhide action */
		else if (call->action[ATTR_ACTION] == DO_UNHIDE)
			HideName (SymbSelection.detail.attr.ae->attr_def->name,
				  False);

	      /* Check for attribute marking */
		else if (SymbMarkedAttr.symb != SymbSelection.detail.attr.symb||
			 (SymbMarkedAttr.ae != SymbSelection.detail.attr.ae &&
			  call->action[ATTR_ACTION] == -1))
		{
			tSymbAttrSelection OldMark;

			OldMark = SymbMarkedAttr;
			SymbMarkedAttr = SymbSelection.detail.attr;
			if (OldMark.symb != NULL) SymbRedrawAttr (OldMark);
			SymbRedrawAttr (SymbMarkedAttr);
		}

	      /* Check for move action */
		else if (call->action[ATTR_ACTION] == DO_MOVE)
			SymbMoveAttr (symb);

	      /* Check for partition append */
		else if (call->action[ATTR_ACTION] == DO_APPEND_PARTITION)
			SymbAppendPartition (symb);

	      /* Check for partition split */
		else if (call->action[ATTR_ACTION] == DO_SPLIT_PARTITION)
			SymbSplitPartition (symb);

	      /* Check for attribute unmarking */
		else if (SymbMarkedAttr.ae == SymbSelection.detail.attr.ae)
		{
			SymbMarkedAttr.symb = NULL;
			SymbMarkedAttr.ae   = NULL;
			SymbRedrawAttr (SymbSelection.detail.attr);
		}
	}

      /* Process dependency selection */
	else 
	{
	      /* Process selection of a marked dependency */
		if (call->action[DEP_ACTION] == DO_FOLLOW_MARKED &&
		    SymbDepSelected (symb, call->x, call->y, True))
			SymbFollow (symb, False);

	      /* Process selection of a unmarked dependency */
		if ((call->action[DEP_ACTION] == DO_FOLLOW ||
		     call->action[DEP_ACTION] == DO_FOLLOW_AND_CLOSE ||
		     call->action[REMOVE_ACTION] == DO_REMOVE) &&
		    SymbDepSelected (symb, call->x, call->y, False))
		{
			if (call->action[DEP_ACTION] == DO_FOLLOW)
				SymbFollow (symb, False);

			else if (call->action[DEP_ACTION]==DO_FOLLOW_AND_CLOSE)
				SymbFollow (symb, True);

			if (call->action[REMOVE_ACTION] == DO_REMOVE)
				SymbRemoveDep (symb);
		}
	}
}
