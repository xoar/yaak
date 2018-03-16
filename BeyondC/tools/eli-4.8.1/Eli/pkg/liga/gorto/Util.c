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
/* $Id: Util.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: Util.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Util.c					*
 *									*
 *	DESCRIPTION:	Several Utilities				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file contains a collection of some useful utilities:
 *  - InitUtil(), which loads the CheckMark and Cascase  Bitmaps
 *  - *MaskDependencies(), which mask the type bits of a dependency graph
 *  - *RemoveDependencies(), which remove existing dependencies
 *  - RedisplayGraphOfDid(), which redisplays a graph widget
 */

#include "Misc.h"
#include "Main.h"
#include <X11/Xaw/SmeBSB.h>

/************************************************************************
 *		     	   ProdMaskDependencies				*
 ************************************************************************/

/* Performs a bitwise AND with the given <bitmask> for all type fields
 * of the dependency graph belonging to the given production.
 */

PUBLIC void ProdMaskDependencies (prod, bitmask)
	PRODENTRY	*prod;
	short		bitmask;
{
	int i,j;
	DEPENDENCY *dep;

	for (i=0; i<=prod->check_row; i++)
	{
		dep = & prod->dp[i][0];
		for (j=0; j<=prod->check_row; j++)
		{
			*dep++ &= bitmask;
		}
	}
}      


/************************************************************************
 *		     	   SymbMaskDependencies				*
 ************************************************************************/

/* Performs a bitwise AND with the given <bitmask> for all type fields
 * of the dependency graph belonging to the given symbol.
 */

PUBLIC void SymbMaskDependencies (symb, bitmask)
	SYMBENTRY	*symb;
	short		bitmask;
{
	int i,j;
	DEPENDENCY *dep;

	for (i=0; i<symb->attr_num; i++)
	{
		dep = & symb->ds[i][0];
		for (j=0; j<symb->attr_num; j++)
		{
			*dep++ &= bitmask;
		}
	}
}


/************************************************************************
 *		     	  ProdRemoveDependencies			*
 ************************************************************************/

/* Removes all dependencies of the given production for which the
 * bitwise AND of the given <bitmask> width the type field yields True.
 */

PUBLIC void ProdRemoveDependencies (prod, bitmask)
	PRODENTRY	*prod;
	short		bitmask;
{
	int i,j;
	DEPENDENCY *dep;

	for (i=0; i<=prod->check_row; i++)
	{
		dep = & prod->dp[i][0];
		for (j=0; j<=prod->check_row; j++)
		{
			if (*dep & bitmask) *dep = 0;
			dep ++;
		}
	}
}      


/************************************************************************
 *		     	  SymbRemoveDependencies			*
 ************************************************************************/

/* Removes all dependencies of the given symbol for which the
 * bitwise AND of the given <bitmask> width the type field yields True.
 */

PUBLIC void SymbRemoveDependencies (symb, bitmask)
	SYMBENTRY	*symb;
	short		bitmask;
{
	int i,j;
	DEPENDENCY *dep;

	for (i=0; i<symb->attr_num; i++)
	{
		dep = & symb->ds[i][0];
		for (j=0; j<symb->attr_num; j++)
		{
			if (*dep & bitmask) *dep = 0;
			dep ++;
		}
	}
}


/************************************************************************
 *		     	   RedisplayGraphOfDid				*
 ************************************************************************/

/* Initiates the redisplay of the corresponding graph widget for
 * the given <did>.
 */

PUBLIC void RedisplayGraphOfDid (did)
	int did;
{
      /* <did> corresponds to a production */
	if (ref_tab[did].etag == PROD)
	{
		PRODENTRY *prod = & PE (did);
		if (! (prod->state & S_REDISPLAYED) && prod->par != NULL)
			RedisplayWidget (prod->par->widget);
		prod->state |= S_REDISPLAYED;
	}

      /* <did> corresponds to a symbol */
	else if (ref_tab[did].etag == SYMB)
	{
		SYMBENTRY *symb = & SE (did);
		if (! (symb->state & S_REDISPLAYED) && symb->sar != NULL)
			RedisplayWidget (symb->sar->widget);
		symb->state |= S_REDISPLAYED;
	}
}


/************************************************************************
 *		     	        PartDepsCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void PartDepsCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	Arg args[2];
	int i;
	PRODENTRY *prod;
	SYMBENTRY *symb;

      /* Toggle the flag */
	Res.show_part_deps = ! Res.show_part_deps;

      /* Set the menu check mark */
	XtSetArg (args[0], XtNleftBitmap,
		  Res.show_part_deps ? CheckMarkBitmap : None);
	XtSetValues (w, args, 1);

      /* Redisplay all open productions */
	for (i=min_entry; i<=max_entry; i++)
		if (ref_tab[i].etag == PROD)
		{
			prod = & PE(i);
			if (prod->par) RedisplayWidget (prod->par->widget);
		}
		else if (ref_tab[i].etag == SYMB)
		{
			symb = & SE(i);
			if (symb->sar) RedisplayWidget (symb->sar->widget);
		}
}
