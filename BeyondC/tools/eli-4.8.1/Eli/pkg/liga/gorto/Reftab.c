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
/* $Id: Reftab.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: Reftab.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/Reftab.c					*
 *									*
 *	CONTENTS:	Computation of the additions to ref_tab		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"
#include "Visit.h"
#include "Main.h"


/************************************************************************
 *			     ComputeSymbolOrd				*
 ************************************************************************/

/* Computes the <ord> entries of all symbol instances of the symbol <symb>.
 */

PRIVATE void ComputeSymbolOrd (symb)
	SYMBENTRY *symb;
{
	SLNODE *nd, *last;

	last = NULL;
	for (nd = symb->hddown; nd != NULL; last = nd, nd = nd->down)
	{
		if (last != NULL && last->pid == nd->pid)
		{
			if (last->ord == 0) last->ord = 1;
			nd->ord = last->ord + 1;
		}
		else
			nd->ord = 0;
	}
}


/************************************************************************
 *			  ComputeRefTabAdditions			*
 ************************************************************************/

/* Initializes additional fields in ref_tab that have been added to 
 * the original order implementation.
 */

PUBLIC void ComputeRefTabAdditions ()
{
	static Boolean first_time = True;
	int max_segments = 0;
	int i, segments;

      /* Compute Attribute Additions */
	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == ATTR)
		{
			ATTRENTRY *ae = & AE(i);

			if (first_time) ae->state = 0;
		}

      /* Compute Symbol Additions */
	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == SYMB)
		{
			SYMBENTRY *symb = & SE(i);

			if (first_time)
				ComputeSymbolOrd (symb);
			else
			{
				symb->state &= ~S_CHANGED;
				SymbUpdateState (symb);
			}
			ProdSortAttributes (symb);
			ProdComputeAttrSpaces (symb);
			SymbMarkCriticalPath (symb);
			ProdComputeAttrSizes (symb);
			ProdComputeSymbolSize (symb);
			segments = symb->attr_num * 3 + 1;
			if (segments > max_segments)
				max_segments = segments;
		}

      /* Compute Production Additions */
	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD)
		{
			PRODENTRY *prod = & PE(i);

			ProdComputeSize (prod);
			if (prod->state & S_VISIT_SEQ) VisitComputeSize (prod);
			if (first_time)
			{
				prod->par      = NULL;
				prod->geometry = NULL;
			}
		}

	if (first_time)
		InitDrawing (max_segments);
	else			
	{
		ProdUpdateList ();
		SymbUpdateList ();
	}
	first_time = False;
}
