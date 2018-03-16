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
/* $Id: ProdDep.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdDep.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================* 
 *									*
 *	FILE:		Prod/ProdDep.c					*
 *									*
 *	CONTENTS:	Dependency drawing in production graphs		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file contains the functions used for dependency drawing in
 * production dependency graphs. There are two entry points into this
 * file:	ProdDrawDep	- draw the dependencies
 *		ProdDepSelected - test for dependency selection
 */

#include "Misc.h"
#include "Symb.h"
#include "Main.h"
#include "Prod.h"


/************************************************************************
 *                               DoDepRow 				*
 ************************************************************************/

/* Loops over a column of a dependency matrix and performs the desired
 * action (drawing or selection test).
 */

PRIVATE Boolean DoDepRow (prod, x2, y2, symb2, ae2, no2, start_row2, dep_mask)
	PRODENTRY	*prod;
	Position	x2, y2;
	SYMBENTRY	*symb2;
	ATTRENTRY	*ae2;
	int		no2, start_row2;
	DEPENDENCY	dep_mask;
{
	SLNODE		*nd;
	ATTRENTRY	*ae;
	DEPENDENCY	*dep;
	DEP_VECTOR	row_dep = prod->dp[start_row2 + ae2->pos];
	Position	x1, y1;
	int		no1, height1, height2;

      /* Set coordinates of the first (lhs) symbol */
	x1      = prod->par->lhs_x;
	height2 = (ae2->state & A_CRITICAL) ? CrAttrHeight : AttrHeight;

      /* Loop over the productions symbols (incl. lhs) */
	for (nd = prod->hdright; nd != NULL; nd = nd->right)
	{
		SYMBENTRY *symb	= & SE(nd->sid);

	      /* Compute y-coordinate for first attribute */
		y1 = nd->y + 1 + 2*Res.text_pad +
		     Res.bold_font->ascent + Res.bold_font->descent;
		no1 = 0;

	      /* Loop over the symbol's attributes */
		for (ae=symb->first_attr; ae!=NULL; ae=ae->next)
		{
			if (ae->state & A_HIDDEN) continue;

			height1 = ae->state & A_CRITICAL ? 
				CrAttrHeight : AttrHeight;
			dep = & row_dep[nd->start_row+ae->pos];

			if (   !(ae->state & A_HIDDEN)
			    && (*dep & dep_mask) && !(*dep & T_TRAN)
			    && ((*dep != (T_PART|T_IND)) ||
				(Res.show_part_deps) ||
				(prod->dp_detail[start_row2 + ae2->pos]
					[nd->start_row+ae->pos].induced.from))
			    && DoDep (& row_dep[nd->start_row+ae->pos],
				x1, y1+height1/2, no1, symb->width,
				ae->attr_def->class==0,
				x2, y2+height2/2, no2, symb2->width,
				ae2->attr_def->class==0, 
				ae->down_space, ae->up_space,
				symb->length, nd == prod->hdright))
			{
				ProdSelection.type = ProdDep;
				ProdSelection.detail.dep.node1 = nd;
				ProdSelection.detail.dep.ae1   = ae;
				ProdSelection.detail.dep.dep   = dep;
				ProdSelection.detail.dep.det   = 
					&prod->dp_detail[start_row2 + ae2->pos]
						        [nd->start_row+ae->pos];
				return (True);
			}

		      /* Compute y-coordinate of next attribute */
			y1 += height1;
			no1 ++;
		}

	      /* Compute the coordinates of the next symbol occurence */
		if (nd == prod->hdright) x1 = prod->par->rhs_x;
	}
	return (False);
}


/************************************************************************
 *                              ProdDoDep				*
 ************************************************************************/

/* Loops over a row of a dependency matrix and performs the desired
 * action (drawing or selection test).
 */

PRIVATE Boolean ProdDoDep (prod, dep_mask)
	PRODENTRY	*prod;
	DEPENDENCY	dep_mask;
{
	SLNODE		*nd;
	ATTRENTRY	*ae;
	Position	x2, y2;
	int		no2;

      /* Set coordinates of the first (lhs) symbol */
	x2 = prod->par->lhs_x;

      /* Loop over the productions symbols (incl. lhs) */
	for (nd = prod->hdright; nd != NULL; nd = nd->right)
	{
		SYMBENTRY *symb	= & SE(nd->sid);

	      /* Compute y-coordinate for first attribute */
		y2 = nd->y + 1 + 2*Res.text_pad +
		     Res.bold_font->ascent + Res.bold_font->descent;
		no2 = 0;

	      /* Loop over the symbol's attributes */
		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
		{
			if (ae->state & A_HIDDEN) continue;

		      /* Draw the dependencies of this row */
			if (DoDepRow (prod, x2, y2, symb, ae, no2,
				      nd->start_row, dep_mask))
			{
				ProdSelection.detail.dep.node2 = nd;
				ProdSelection.detail.dep.ae2   = ae;
				return (True);
			}

		      /* Compute y-coordinate of next attribute */
			if (ae->state & A_CRITICAL)	y2 += CrAttrHeight;
			else				y2 += AttrHeight;
			no2 ++;
		}

	      /* Compute the coordinates of the next symbol occurence */
		if (nd == prod->hdright) x2 = prod->par->rhs_x;
	}
	return (False);
}


/************************************************************************
 *                             ProdDrawDep				*
 ************************************************************************/

/* Draws all dependencies of a given production. 
 */

PUBLIC void ProdDrawDep (win, reg, prod)
	Window		win;
	Region		reg;
	PRODENTRY	*prod;
{
	DepInitiate (win, reg, 0, 0, False);
	(void) ProdDoDep (prod, T_MASK);
}


/************************************************************************
 *			     ProdDepSelected				*
 ************************************************************************/

/* Tests the given point (<x>,<y>) against all dependencies of the
 * given production <prod>. If a match is found, the public structure
 * ProdSelection contains a description of the dependency.
 */

PUBLIC Boolean ProdDepSelected (prod, x, y, only_marked)
	PRODENTRY	*prod;
	Position	x, y;
	Boolean		only_marked;
{
	DepInitiate ((Window) NULL, (Region) NULL, x, y, False);
	return (ProdDoDep (prod, only_marked?(T_FOLLOWED|T_MARK):T_MASK));
}
