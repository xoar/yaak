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
/* $Id: ProdSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdSelect.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdSelect.c				*
 *									*
 *	CONTENTS:	Processing of ButtonPress events in 		*
 *			production windows				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file implements the select() callback procedure of the graph
 * widgets containing production dependency graphs.
 */

#include "Misc.h"
#include "Symb.h"
#include "Graph.h"
#include "Main.h"
#include "Popup.h"
#include "Prod.h"


/************************************************************************
 *			     Public Variables				*
 ************************************************************************/

/* The selected item, used only for the processing of selections */
tProdSelection ProdSelection;

/* The currently marked attribute */
tProdAttrSelection ProdMarkedAttr = {NULL, NULL};


/************************************************************************
 *			     ProdSymbSelected				*
 ************************************************************************/

/* Tests all symbol names of the given production <prod> against
 * the selected point (<x>,<y>). If a match is found, a description is
 * filles in the public variable ProdSelection.
 */

PRIVATE Boolean ProdSymbSelected (prod, x, y)
	PRODENTRY	*prod;
	Position	x, y;
{
	SLNODE		*nd;
	SYMBENTRY	*symb;
	Position current_x = prod->par->lhs_x;

      /* loop over the symbol instances */
	for (nd=prod->hdright; nd!=NULL; nd=nd->right)
	{
		symb = & SE(nd->sid);

		if (x < current_x || x > (Position)(current_x + symb->width) ||
		    y < nd->y || y > nd->y + 2*Res.text_pad +
					     Res.bold_font->ascent +
					     Res.bold_font->descent)
		{
			current_x = prod->par->rhs_x;
			continue;
		}
		ProdSelection.type             = ProdSymb;
		ProdSelection.detail.symb.node = nd;
		return (True);
	}

      /* No match found */
	return (False);
}


/************************************************************************
 *			     ProdAttrSelected				*
 ************************************************************************/

/* Tests all attribute instances of the given production <prod> against
 * the selected point (<x>,<y>). If a match is found, the parameters
 * selected_node and selected_ae contain the description.
 */

PRIVATE Boolean ProdAttrSelected (prod, x, y)
	PRODENTRY	*prod;
	Position	x,y;
{
	SLNODE		*nd;
	ATTRENTRY	*ae;
	Position	current_y, current_x;
	Boolean		found;

	current_x = prod->par->lhs_x;
	for (nd=prod->hdright; nd!=NULL;nd=nd->right,current_x=prod->par->rhs_x)
	{
		SYMBENTRY	*symb = & SE(nd->sid);

	      /* Check the symbols enclosing rectangle */
		if (x < current_x || x > (Position)(current_x+symb->width) ||
		    y < nd->y     || y > (Position)(nd->y    +symb->height))
			continue;

		current_y = nd->y + 2*Res.text_pad +
				Res.bold_font->ascent + Res.bold_font->descent;
		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
		{
			if (ae->state & A_HIDDEN) continue;

		      /* Check x coordinate */
			if (symb->state & S_PARTITIONED)
			{
				if (ae->attr_def->class == 0)
					found = x >= current_x+Res.synt_indent;
				else
					found = x <= (Position)(current_x+symb->width-
							  Res.synt_indent);
			}

		      /* Check y coordinate */
			if (y < current_y ||
			    y >= current_y + (ae->state&A_CRITICAL ?
						CrAttrHeight:AttrHeight))
				found = False;

		      /* found the selected attribute */
			if (found)
			{
				ProdSelection.type = ProdAttr;
				ProdSelection.detail.attr.node = nd;
				ProdSelection.detail.attr.ae   = ae;
				ProdSelection.detail.attr.y    = current_y;
				return (True);	
			}

			current_y += ae->state & A_CRITICAL ? 
					CrAttrHeight:AttrHeight;
		}
	}
	return (False);
}


/************************************************************************
 *			        ProdFollow				*
 ************************************************************************/

/* Finds and shows the origin of a selected dependency.
 */

PRIVATE void ProdFollow (prod, close)
	PRODENTRY	*prod;
	Boolean		close;
{
	Boolean		CloseLido = False;
	String		msg;
	DEPENDENCY	*dep = ProdSelection.detail.dep.dep;

	if (close && !(*dep & (T_MARK | T_FOLLOWED)))
	{
		ProdCloseAllCB ((Widget) NULL, (caddr_t) prod, (caddr_t) NULL);
		SymbCloseAllCB ((Widget) NULL, (caddr_t) NULL, (caddr_t) NULL);
		CloseLido = LidoTop != NULL;
	}

	if (*dep & T_DIR)
	{
		*dep |= T_FOLLOWED;
		RedisplayWidget (prod->par->widget);

		if (ProdSelection.detail.dep.det->direct.row == 0)
		{
			switch (ProdSelection.detail.dep.ae1->attr_def->gen)
			{
				case 0:  msg = Res.str_transfer; break;
				case 1:  msg = Res.str_including; break;
				case 2:  msg = Res.str_constituent; break;
				case 3:  msg = Res.str_chain; break;
				default: msg = Res.str_unknown_dep; break;
			}
			Message (prod->prod_def->did, msg);
		}
		else
		{
			ShowLidoPosition (ProdSelection.detail.dep.det->
					  direct.row);
			CloseLido = False;
		}
	}
	else if (*dep & T_IND)
		ProdFindPath (prod, ProdSelection.detail.dep.node1,
			  	    ProdSelection.detail.dep.node2,
			  	    ProdSelection.detail.dep.ae1,
			  	    ProdSelection.detail.dep.ae2, 1);
	if (CloseLido) LidoCB ((Widget) NULL, (caddr_t) NULL, (caddr_t) NULL);
}


/************************************************************************
 *			      ProdRemoveDep				*
 ************************************************************************/

/* Removed a selected arranged dependency.
 */

PRIVATE void ProdRemoveDep (prod)
	PRODENTRY *prod;
{
	if ((*ProdSelection.detail.dep.dep & T_MASK) == T_ARR)
	{
		RemoveArrangeNode (ProdSelection.detail.dep.det->arrange.node);
		*ProdSelection.detail.dep.dep = 0;
		DepRemoved = True;
		RedisplayGraphOfDid (prod->prod_def->did);
	}
}


/************************************************************************
 *			       ProdSelectCB				*
 ************************************************************************/

/* This is the callback used for selection events on a production window.
 */

/*ARGSUSED*/
PUBLIC void ProdSelectCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	PRODENTRY		*prod = (PRODENTRY *) client_data;
	GraphReturnStruct	*call = (GraphReturnStruct *) call_data;


	ProdSelection.type = ProdNothing;

      /* Process symbol selection */
	if (ProdSymbSelected (prod, call->x, call->y))
		SymbCreateNew (ProdSelection.detail.symb.node->sid);

      /* Process attribute selection */
	else if (ProdAttrSelected (prod, call->x, call->y))
	{
	      /* Check for pending attribute (un)hide */
		if (state == HideAttribute || state == UnHideAttribute)
			HideName (ProdSelection.detail.attr.ae->attr_def->name,
				  state == HideAttribute);

	      /* Check for hide action */
		else if (call->action[ATTR_ACTION] == DO_HIDE)
			HideName (ProdSelection.detail.attr.ae->attr_def->name,
				  True);

	      /* Check for attribute marking */
		else if (ProdMarkedAttr.node == NULL ||
			 ProdMarkedAttr.node->pid !=
			 ProdSelection.detail.attr.node->pid ||
			 ProdMarkedAttr.node!=ProdSelection.detail.attr.node ||
			 ProdMarkedAttr.ae != ProdSelection.detail.attr.ae)
		{
			tProdAttrSelection OldMark;

			OldMark = ProdMarkedAttr;
			ProdMarkedAttr = ProdSelection.detail.attr;
			if (OldMark.node != NULL) ProdRedrawAttr (OldMark);
			ProdRedrawAttr (ProdMarkedAttr);
		}

	      /* Check for attribute unmarking */
		else if (ProdMarkedAttr.node==ProdSelection.detail.attr.node &&
			 ProdMarkedAttr.ae  ==ProdSelection.detail.attr.ae)
		{
			ProdMarkedAttr.node = NULL;
			ProdMarkedAttr.ae   = NULL;
			ProdRedrawAttr (ProdSelection.detail.attr);
		}
	}

      /* Process dependency selection */
	else
	{
	      /* Process selection of a marked dependency */
		if (call->action[DEP_ACTION] == DO_FOLLOW_MARKED &&
		    ProdDepSelected (prod, call->x, call->y, True))
			ProdFollow (prod, False);

	      /* Process selection of a unmarked dependency */
		if ((call->action[DEP_ACTION] == DO_FOLLOW ||
		     call->action[DEP_ACTION] == DO_FOLLOW_AND_CLOSE ||
		     call->action[REMOVE_ACTION] == DO_REMOVE) &&
		    ProdDepSelected (prod, call->x, call->y, False))
		{
			if (call->action[DEP_ACTION] == DO_FOLLOW)
				ProdFollow (prod, False);

			else if (call->action[DEP_ACTION]==DO_FOLLOW_AND_CLOSE)
				ProdFollow (prod, True);

			if (call->action[REMOVE_ACTION] == DO_REMOVE)
				ProdRemoveDep (prod);
		}
	}
}
