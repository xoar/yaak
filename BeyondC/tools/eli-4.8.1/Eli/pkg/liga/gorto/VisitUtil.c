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
/* $Id: VisitUtil.c,v 4.2 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: VisitUtil.c,v 4.2 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitUtil.c				*
 *									*
 *	CONTENTS:	Utilities dealing with visit-sequences		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Visit.h"
#include <stdio.h>


/************************************************************************
 *			       SymbnoToNode				*
 ************************************************************************/

PUBLIC SLNODE *SymbnoToNode (prod, symb_no)
	PRODENTRY	*prod;
	int		symb_no;
{
	SLNODE *nd = prod->hdright;

	while (symb_no--) nd = nd->right;
	return (nd);
}


/************************************************************************
 *			     VisitElemString				*
 ************************************************************************/

PUBLIC String VisitElemString (vselem)
	VSPTR vselem;
{
	static char ret[255];

	switch (vselem->vscls)
	{
	case VSASSIG:	(void) sprintf (ret, "%s[%d].%s",
				SE(vselem->vsinfo.assig.sid).symb_def->dname,
				vselem->vsinfo.assig.sno,
				AE(vselem->vsinfo.assig.aid).attr_def->name);
			break;

	case VSCOND:	(void) sprintf (ret, "Check Condition %s",
				vselem->vsinfo.cond.idldef->name);
			break;

	case VSVISIT:	if (vselem->vsinfo.visit.vssno == 0)
				(void) sprintf (ret, "%d.Leave",
					vselem->vsinfo.visit.vsord);
			else
				(void) sprintf (ret, "%d.Visit %s[%d]",
					vselem->vsinfo.visit.vsord,
					SE(vselem->vsinfo.visit.vssid)
						.symb_def->dname,
					vselem->vsinfo.visit.vssno);
			break;
	}
	return(ret);
}


/************************************************************************
 *				cut_empty				*
 ************************************************************************/

PRIVATE Boolean cut_empty (set1, set2, prod)
	BITVECTOR	set1, set2;
	PRODENTRY	*prod;
{
	int word;

	for (word = 0; word <= prod->check_col; word++)
		if (set1[word] & set2[word]) return (False);

	return (True);
}


/************************************************************************
 *			       ElemDepends				*
 ************************************************************************/

PUBLIC Boolean ElemDepends (prod, elem1, elem2)
	PRODENTRY	*prod;
	VSPTR		elem1, elem2;
{
	SLNODE	*node1, *node2;
	int	apos1, word1, bit1, index1, index2;

	if (elem1->vscls == VSASSIG)
	{
		node1  = SymbnoToNode (prod, elem1->vsinfo.assig.sno);
		apos1  = elem1->vsinfo.assig.apos;
		index1 = node1->start_row + apos1;
		word1  = node1->start_col + apos1/WORD_LENGTH;
		bit1   = 1 << apos1 % WORD_LENGTH;

		if (elem2->vscls == VSASSIG)
		{
			node2  = SymbnoToNode (prod, elem2->vsinfo.assig.sno);
			index2 = node2->start_row + elem2->vsinfo.assig.apos;
			return (prod->dp[index2][index1]);
		}
		else if (elem2->vscls == VSVISIT)
			return (elem2->deps[word1] & bit1);

		else if (elem2->vscls == VSCOND)
			return (elem2->deps[word1] & bit1);
	}
	else if (elem1->vscls == VSVISIT)
	{
		return ((elem2->vscls == VSASSIG || elem2->vscls == VSCOND) &&
		    ! cut_empty (elem1->vsinfo.visit.evalset,elem2->deps,prod));
	}
	return (False);
}


/************************************************************************
 *			       ElemCritical				*
 ************************************************************************/

PUBLIC Boolean ElemCritical (prod, elem, last)
	PRODENTRY	*prod;
	VSPTR		elem, last;
{
	if (IS_LEAVE (elem) || elem->vscls == VSCOND) return (True);

	return ((last == NULL         || ElemDepends (prod, last, elem)) &&
		(IS_LEAVE(elem->next) || ElemDepends (prod, elem, elem->next)));
}


/************************************************************************
 *			       VisitArrange				*
 ************************************************************************/

/* Arranges for the visit-sequence element <elem> to depend on <after>.
 */

PUBLIC void VisitArrange (prod, elem, after)
	PRODENTRY	*prod;
	VSPTR		elem, after;
{
	SLNODE		*fromNode, *toNode;
	int		fromAid, toAid;
	SYMBENTRY	*symb;
	ATTRENTRY	*ae;

      /* Compute <fromNode> and <fromAid> */
	fromAid = 0;
	if (after->vscls == VSASSIG)
	{
		fromNode = SymbnoToNode (prod, after->vsinfo.assig.sno);
		fromAid  = after->vsinfo.assig.aid;
	}
	else if (after->vscls == VSVISIT)
	{
		symb     = & SE (after->vsinfo.visit.vssid);
		fromNode = SymbnoToNode (prod, after->vsinfo.visit.vssno);
		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
			if (after->vsinfo.visit.evalset
				[fromNode->start_col + ae->pos/WORD_LENGTH]
				& 1 << ae->pos%WORD_LENGTH)
			{
				fromAid = ae->attr_def->did;
				break;
			}
	}
	if (fromAid == 0) return;

      /* Compute <toNode> and <toAid> */
	toAid = 0;
	if (elem->vscls == VSASSIG)
	{
		toNode = SymbnoToNode (prod, elem->vsinfo.assig.sno);
		toAid  = elem->vsinfo.assig.aid;
	}
	else if (elem->vscls == VSVISIT)
	{
		symb   = & SE (elem->vsinfo.visit.vssid);
		toNode = SymbnoToNode (prod, elem->vsinfo.visit.vssno);
		toAid  = 0;
		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
			if (elem->vsinfo.visit.evalset
			     [toNode->start_col + ae->pos/WORD_LENGTH] 
			     & 1 << ae->pos%WORD_LENGTH)
			{
				toAid = ae->attr_def->did;
				break;
			}
	}
	if (toAid == 0) return;

      /* Construct and introduce the arrange option */
	MakeArrangeNode (prod->prod_def->did, fromNode, toNode,
				fromAid, toAid, True);
	ProdUpdateState (prod);
}
