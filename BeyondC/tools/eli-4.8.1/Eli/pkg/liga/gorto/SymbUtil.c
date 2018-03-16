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
/* $Id: SymbUtil.c,v 4.2 1997/08/29 08:06:05 peter Exp $ */

static char rcs_id[]= "$Id: SymbUtil.c,v 4.2 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbUtil.c					*
 *									*
 *	CONTENTS:	Utilities dealing with symbols			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Symb.h"


/************************************************************************
 *				 InitSAR				*
 ************************************************************************/

/* Computes the entries of the symbol activation record.
 */

PUBLIC void InitSAR (symb)
	SYMBENTRY *symb;
{
	SEQAttrdef	sad;
	Attrdef		ad;

      /* Initialize the x and y positions */
	symb->sar->x = 0;
	symb->sar->y = 0;

      /* Initialize width and height */
	symb->sar->width = XTextWidth (Res.bold_font, symb->symb_def->dname,
						strlen (symb->symb_def->dname));
	symb->sar->height = 1 + 2*Res.text_pad + 
			    Res.bold_font->ascent+Res.bold_font->descent;

      /* Loop over the symbol's attributes */
	foreachinSEQAttrdef (symb->symb_def->attrs, sad, ad)
	{
		ATTRENTRY	*ae = & AE(ad->did);
		Dimension	w;

	      /* Compute the maximum width */
		w = XTextWidth (ae->state & A_CRITICAL ?
				  Res.critical_font : Res.font,
				ad->name, strlen (ad->name)) + Res.synt_indent;
		if (w > symb->sar->width) symb->sar->width = w;

	      /* Compute the sum of attribute heights */
		symb->sar->height += ae->state & A_CRITICAL ?
					CrAttrHeight : AttrHeight;
	}

      /* Add the space needed for padding */
	symb->sar->width += 2 + 2*Res.text_pad;
}


/************************************************************************
 *			      SymbStateLabel				*
 ************************************************************************/

PUBLIC String SymbStateLabel (symb)
	SYMBENTRY *symb;
{
	static char ret[255];

	strcpy (ret, "");
	if (symb->state & S_CYCLIC)
		{ strcat (ret, " "); strcat (ret, Res.str_cyclic); }
	if (symb->state & S_ARRANGED)
		{ strcat (ret, " "); strcat (ret, Res.str_arranged); }
	if (symb->state & S_CHANGED)
		{ strcat (ret, " "); strcat (ret, Res.str_changed); }
	if (symb->state & S_PARTITIONED)
		{ strcat (ret, " "); strcat (ret, Res.str_part); }
	if (symb->state & S_FORCED)
		{ strcat (ret, " "); strcat (ret, Res.str_forced); }

	if (ret[0] != '\0')	return (& ret[1]);
	else			return ("");
}


/************************************************************************
 *			     SymbSearchCycle				*
 ************************************************************************/

PUBLIC Boolean SymbSearchCycle (symb, ae)
	SYMBENTRY	*symb;
	ATTRENTRY	**ae;
{
	ATTRENTRY *i;

	for (i = symb->first_attr; i != NULL; i = i->next)
	{
		if (symb->ds[i->pos][i->pos])
		{
			*ae = i;
			return (True);
		}
	}
	*ae = NULL;
	return (False);
}


/************************************************************************
 *			      RemoveProdDeps				*
 ************************************************************************/

PRIVATE void RemoveProdDeps (prod, symb)
	PRODENTRY	*prod;
	SYMBENTRY	*symb;
{
	SLNODE		*nd1, *nd2;
	ATTRENTRY	*ae1, *ae2;
	DEPENDENCY	*dep;
	DETAIL		*det;

	for (nd1 = prod->hdright; nd1 != NULL; nd1 = nd1->right)
	{
		ae1 = SE(nd1->sid).first_attr;
		for (; ae1 != NULL; ae1 = ae1->next)
			for (nd2 = prod->hdright; nd2 != NULL; nd2 = nd2->right)
			{
				ae2 = SE(nd2->sid).first_attr;
				for (; ae2 != NULL; ae2 = ae2->next)
				{
					dep = & prod->dp[nd2->start_row+ae2->pos]
						      [nd1->start_row+ae1->pos];
					det = & prod->dp_detail
						      [nd2->start_row+ae2->pos]
						      [nd1->start_row+ae1->pos];
					switch (*dep & T_MASK)
					{
					case T_ARR:
					case T_TRAN|T_ARR:
					case T_TRAN|T_PART:
					 *dep = 0;
					 break;

					case T_IND | T_ARR:
					case T_IND | T_PART:
					 if (det->induced.from == NULL &&
					     symb == & SE(nd1->sid))
						*dep = 0;
					 break;
					}
				}
					
			}
	}
}      


/************************************************************************
 *			    PartialTransitive				*
 ************************************************************************/

PRIVATE void PartialTransitive (symb)
	SYMBENTRY *symb;
{
	bool changed;
	SLNODE *nd;
	int	last_pid;

	do {
		changed = FALSE;
		last_pid = 0;
		for (nd=symb->hddown; nd!=NULL; last_pid=nd->pid, nd=nd->down)
			if (last_pid != nd->pid) ruletransitive (nd->pid);

		if ((symb->state & S_CHANGED) && !(symb->state & S_CYCLIC))
		{
			symb->state &= ~S_CHANGED;
			distributedeps (symb->symb_def->did, &changed);
		}
	} while (changed);
}


/************************************************************************
 *			     UpdatePartition				*
 ************************************************************************/

PUBLIC void UpdatePartition (symb)
	SYMBENTRY *symb;
{
	SLNODE *nd;

      /* Remove arranged and partition dependencies */
	SymbRemoveDependencies (symb, T_PART|T_ARR);
	for (nd=symb->hddown; nd != NULL; nd = nd->down)
		RemoveProdDeps (& PE(nd->pid), symb);
	symb->state &= S_CHANGED | S_FORCED;

      /* Re-Introduce (all) arranged dependencies */
	IntroduceArrangeList();

      /* Construct transitive closure of influenced graphs */
	graphstate_hint=T_ARR; PartialTransitive (symb);
	if (symb->state & S_CYCLIC) return;

      /* Recompute partition of this symbol and distribute partitioned deps */
	symbpartition (symb->symb_def->did);
	graphstate_hint=T_PART; PartialTransitive (symb);
}
