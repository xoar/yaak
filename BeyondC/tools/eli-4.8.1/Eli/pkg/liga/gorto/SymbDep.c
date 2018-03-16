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
/* $Id: SymbDep.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: SymbDep.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbDep.c					*
 *									*
 *	CONTENTS:	Dependency drawing in symbol graphs		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"


/************************************************************************
 *				SymbDoDep				*
 ************************************************************************/

/* Performs the desired action for all dependencies of this symbol.
 */

PRIVATE Boolean SymbDoDep (symb, dep_mask)
	SYMBENTRY	*symb;
	DEPENDENCY	dep_mask;
{
	int		i,  j;
	Position	y1, y2;
	ATTRENTRY	*ae1, *ae2;
	DEPENDENCY	*dep;
	int		height1, height2;

	y2 = symb->sar->y + 1 + 2*Res.text_pad +
		Res.bold_font->ascent + Res.bold_font->descent;

	j = 0;
	for (ae2 = symb->first_attr; ae2 != NULL; j++, ae2 = ae2->next)
	{
		height2	= ae2->state & A_CRITICAL ? CrAttrHeight : AttrHeight;
		y1	= symb->sar->y + 1 + 2*Res.text_pad + 
				Res.bold_font->ascent + Res.bold_font->descent;

		i = 0;
		for (ae1 = symb->first_attr; ae1 != NULL; ae1 = ae1->next, i++)
		{
			height1 = ae1->state & A_CRITICAL ?
					CrAttrHeight : AttrHeight;
			dep	= & symb->ds[ae2->pos][ae1->pos];

			if ((*dep & dep_mask) && !(*dep & T_TRAN) &&
				DoDep (dep, 
					symb->sar->x, y1+height1/2,
					i, symb->sar->width,
					ae1->attr_def->class == 0,
					symb->sar->x, y2+height2/2,
					j, symb->sar->width,
					ae2->attr_def->class == 0,
					0, 0, symb->attr_num, Res.left_symbol))
			{
				SymbSelection.type = SymbDep;
				SymbSelection.detail.dep.ae1 = ae1;
				SymbSelection.detail.dep.ae2 = ae2;
				SymbSelection.detail.dep.dep = dep;
				SymbSelection.detail.dep.det =
				  & symb->ds_detail[ae2->pos][ae1->pos];
				return (True);
			}
			y1 += height1;
		}
		y2 += height2;
	}
	return (False);
}


/************************************************************************
 *			       SymbDrawDep				*
 ************************************************************************/

/* Draws all dependencies of a given symbol.
 */

PUBLIC void SymbDrawDep (win, reg, symb)
	Window		win;
	Region		reg;
	SYMBENTRY	*symb;
{
	DEPENDENCY mask = Res.show_part_deps ? T_MASK|T_MARK|T_FOLLOWED : 
					((T_MASK|T_MARK|T_FOLLOWED) & ~T_PART);

	DepInitiate (win, reg, 0, 0, False);
	(void) SymbDoDep (symb, mask);
}


/************************************************************************
 *			     SymbDepSelected				*
 ************************************************************************/

/* Tests the given point (<x>,<y>) against all dependencies of the given
 * symbol <symb>.
 */

PUBLIC Boolean SymbDepSelected (symb, x, y, only_marked)
	SYMBENTRY	*symb;
	Position	x, y;
	Boolean		only_marked;
{
	DEPENDENCY mask = Res.show_part_deps ? T_MASK|T_MARK|T_FOLLOWED : 
					((T_MASK|T_MARK|T_FOLLOWED) & ~T_PART);

	DepInitiate ((Window) NULL, (Region) NULL, x, y, False);
	return (SymbDoDep (symb, only_marked ? (T_DIR|T_MARK|T_FOLLOWED):mask));
}
