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
/* $Id: Debug.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Debug.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Debug.c					*
 *									*
 *	CONTENTS:	Functions useful for debugging.			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* The functions contained in this file are not called from any other file,
 * they are only intended for interactive source-level debugging.
 */

#include "Misc.h"
#include "Visit.h"
#include <string.h>
#include <stdio.h>


/************************************************************************
 *				DepString				*
 ************************************************************************/

/* Yields a human readable representation of a dependency.
 */

PUBLIC String DepString (dep)
	DEPENDENCY *dep;
{
	static char ret[80];

	if (dep == (DEPENDENCY *) NULL) return ("<NULL>");

	strcpy (ret, "<");
	if (*dep & T_DIR)	strcat (ret, "D");
	if (*dep & T_TRAN)	strcat (ret, "T");
	if (*dep & T_IND)	strcat (ret, "I");
	if (*dep & T_ARR)	strcat (ret, "A");
	if (*dep & T_PART)	strcat (ret, "P");
	if (*dep & T_MARK)	strcat (ret, "M");
	if (*dep & T_FOLLOWED)	strcat (ret, "F");
	strcat (ret, ">");

	return (ret);
}


/************************************************************************
 *			      PrintBITVECTOR				*
 ************************************************************************/

/* Prints the contents of the given set <deps>.
 */

PUBLIC void PrintBITVECTOR (prod, deps)
	PRODENTRY	*prod;
	BITVECTOR	deps;
{
	SLNODE	*nd;
	SYMBENTRY	*symb;
	ATTRENTRY	*ae;

	for (nd = prod->hdright; nd != NULL; nd = nd->right)
	{
		symb = & SE (nd->sid);

		for (ae = symb->first_attr; ae != NULL; ae = ae->next)
		{
			if (deps[nd->start_col + ae->pos/WORD_LENGTH]
			       & 1 << ae->pos%WORD_LENGTH)
			{
				if (nd->ord)
					printf ("%s[%d].%s\n",
					  symb->symb_def->dname, nd->ord,
					  ae->attr_def->name);
				else
					printf ("%s.%s\n",
					  symb->symb_def->dname,
					  ae->attr_def->name);
			}
		}
	}
}


/************************************************************************
 *			    WriteProdLifetimes				*
 ************************************************************************/

/* Writes the computed lifetimes of all attribute instances of the given
 * production <prod> to the file LifeProt.
 */

#define VERBOSE(elem)	((elem) ? VisitElemString(elem) : "_")

PRIVATE FILE *LifeProt;

PUBLIC void WriteProdLifetimes (prod)
	PRODENTRY *prod;
{
	SLNODE		*nd;
	SEQAttrdef	sad;
	Attrdef		ad;
	int		index;

	fprintf (LifeProt, "*****************************************\n");
	fprintf (LifeProt, "Lifetimes for rule %s (%d)\n",
			   prod->prod_def->dname, prod->prod_def->did);

	for (nd = prod->hdright; nd != NULL; nd = nd->right)
	{
		fprintf (LifeProt, "\n\n======== Symbol %s\n\n",
			SE(nd->sid).symb_def->dname);
		index = nd->start_row;
		foreachinSEQAttrdef (SE(nd->sid).symb_def->attrs, sad, ad)
		{
			fprintf (LifeProt, "%-11s: -> %-24s/ ", ad->name,
			  VERBOSE (prod->vs->lifetimes[index].last_local));
			fprintf (LifeProt, "%s (%d)\n", 
			  VERBOSE (prod->vs->lifetimes[index].last_global),
			  AE(ad->did).life_vsno);
			index ++;
		}
	}

	fprintf (LifeProt, "\n\n\n");
}


/************************************************************************
 *			      WriteLifetimes				*
 ************************************************************************/

/* Writes all computed lifetimes to a file.
 */

PUBLIC void WriteLifetimes()
{
	int i;

	LifeProt = fopen ("lifetimes", "w");
	for (i = min_entry; i <= max_entry; i++)
		if (ref_tab[i].etag == PROD) WriteProdLifetimes (& PE(i));
	fclose (LifeProt);
}
