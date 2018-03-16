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
/* $Id: ProdUtil.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdUtil.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdUtil.c					*
 *									*
 *	CONTENTS:	Utilities dealing with productions		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"

#include <X11/StringDefs.h>


/************************************************************************
 *			      ProdStateLabel				*
 ************************************************************************/

/* Returns the label indicating the current state of this production.
 */

PUBLIC String ProdStateLabel (prod)
	PRODENTRY *prod;
{
	static char ret[255];

	strcpy (ret, "");
	if (prod->state & S_CYCLIC)
		{ strcat (ret, " "); strcat (ret, Res.str_cyclic); }
	if (prod->state & S_ARRANGED)
		{ strcat (ret, " "); strcat (ret, Res.str_arranged); }
	if (prod->state & S_CHANGED)
		{ strcat (ret, " "); strcat (ret, Res.str_changed); }
	if (prod->state & S_PARTITIONED)
		{ strcat (ret, " "); strcat (ret, Res.str_part); }
	if (prod->state & S_VISIT_SEQ)
		{ strcat (ret, " "); strcat (ret, Res.str_vs); }

	if (ret[0] != '\0')     return (& ret[1]);
	else                    return ("");
}


/************************************************************************
 *			     ProdSearchCycle				*
 ************************************************************************/

/* Searches a cycle in the given production <prod>.
 */

PUBLIC Boolean ProdSearchCycle (prod, nd, ae)
	PRODENTRY	*prod;
	SLNODE		**nd;
	ATTRENTRY	**ae;
{
	SEQAttrdef	sad;
	Attrdef		ad;

	for (*nd=prod->hdright; *nd!=NULL; *nd=(*nd)->right)
	{
		SYMBENTRY *symb = & SE((*nd)->sid);

		foreachinSEQAttrdef (symb->symb_def->attrs, sad, ad)
		{
			*ae = & AE(ad->did);
			if (prod->dp[(*nd)->start_row+(*ae)->pos]
				    [(*nd)->start_row+(*ae)->pos])
				return (True);
		}
	}
	*nd = (SLNODE *) NULL;
	*ae = (ATTRENTRY *) NULL;
	return (False);
}


/************************************************************************
 *			     ProdResizeWindow				*
 ************************************************************************/

PUBLIC void ProdResizeWindow (prod)
	PRODENTRY *prod;
{
	Dimension	width, height;
	Arg		args[2];

      /* Don't try the following for non-existent windows */
	if (! prod->par) return;

      /* Force later redisplay */
	RedisplayGraphOfDid (prod->prod_def->did);

      /* Compute desired width and height and store them in <args> */
	ProdComputeWindowSize (prod, &width, &height);
	XtSetArg (args[0], XtNwidth, width);
	XtSetArg (args[1], XtNheight, height);

      /* Try to resize the windows */
	XtSetValues (prod->par->state, args, 1);
	XtSetValues (XtParent (prod->par->widget), args, 2);
	XtSetValues (prod->par->widget, args, 2);
}
