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
/* $Id: PathFind.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: PathFind.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Pathfind.c					*
 *									*
 *	DESCRIPTION:	Routines for finding the origin of a dependency	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* The functions in this file operate on the dependency graphs of symbols
 * and productions. They are used to recursively find and mark the origin
 * of a given dependency (which was selected by the user). The only entry
 * points into this file are ProdFindPath() and SymbFindPath(), which both
 * find and mark the origin of the given dependency.
 *
 * These functions will create the windows containing the marked origin
 * on the fly by calling ProdCreateNew() or SymbCreateNew().
 */

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"


/************************************************************************
 *			    ProdFindTransitive				*
 ************************************************************************/

/* Finds the origin of a transitive dependency. This is done by calling
 * ProdFindPath for the two parts of this dependency.
 */

PRIVATE void ProdFindTransitive (dep, det, prod, node1,node2,
				 ae1,ae2,follow_induced)
	DEPENDENCY	*dep;
	DETAIL		*det;
	PRODENTRY	*prod;
	SLNODE		*node1, *node2;
	ATTRENTRY	*ae1, *ae2;
	int		follow_induced;
{
	SLNODE		*os;
	SEQAttrdef	sad;
	Attrdef		ad;
	int		atno = det->transitive.over_atno;

      /* Locate the symbol instance in the middle of the path */
	for (os = prod->hdright; os != NULL; os = os->right)
		if (os->start_row <= atno &&
		    (os->right == NULL || atno < os->right->start_row))
			break;

      /* Locate attribute instance in the middle of the path */
	foreachinSEQAttrdef (SE(os->sid).symb_def->attrs, sad, ad)
	{
		if (atno == os->start_row) break;
		atno --;
	}

      /* Call ProdFindPath for the two parts */
	ProdFindPath (prod, node1, os, ae1, & AE(ad->did), follow_induced);
	ProdFindPath (prod, os, node2, & AE(ad->did), ae2, follow_induced);
}


/************************************************************************
 *			     ProdFindInduced				*
 ************************************************************************/

/* Finds the origin of a induced dependency. This is done by calling
 * ProdFindPath in the origin production context.
 */

PRIVATE void ProdFindInduced (dep,det, node1, ae1, ae2, follow_induced)
	DEPENDENCY	*dep;
	DETAIL		*det;
	SLNODE		*node1;
	ATTRENTRY	*ae1, *ae2;
	int		follow_induced;
{
      /* Locate symbol instance from which this dependency was induced */
	SLNODE *inf = det->induced.from;

      /* Context switching while following induced dependencies is limited
       * by the value of <follow_induced>. Check this before performing
       * the context switch.
       */
	if (follow_induced == 0)
	{
		*dep |= T_MARK;
		return;
	}
	*dep &= T_MASK;
	*dep |= T_FOLLOWED;

      /* If this dependency was induced from the symbol graph, the pointer
       * to the symbol instance will be NULL. Check this.
       */
	if (inf == NULL)	/* Induced from the symbol graph */
		SymbFindPath (& SE(node1->sid), ae1, ae2, follow_induced - 1);
	else			/* Induced from a production graph */
		ProdFindPath (& PE(inf->pid),inf,inf,ae1,ae2,follow_induced-1);
}


/************************************************************************
 *                             ProdFindPath				*
 ************************************************************************/

/* Finds recursively the origin of the given dependency. Induced depen-	
 * cies are searched only up to the given limit <follow_induced>, which
 * represents the depth of the search, spoken in contexts.
 * The corresponding windows are automatically created, and the path is 
 * marked with wide lines.
 */

PUBLIC void ProdFindPath (prod, node1, node2, ae1, ae2, follow_induced)
	PRODENTRY	*prod;
	SLNODE		*node1, *node2;
	ATTRENTRY	*ae1, *ae2;
	int		follow_induced;
{
	DEPENDENCY *dep = & prod->dp[node2->start_row + ae2->pos]
				    [node1->start_row + ae1->pos];
	DETAIL	   *det = & prod->dp_detail[node2->start_row + ae2->pos]
					   [node1->start_row + ae1->pos];

/*
	printf ("ProdFindPath: %s: %s.%s -> %s.%s (%d), Type %o\n",
		prod->prod_def->dname,
		SE(node1->sid).symb_def->dname,
		ae1->attr_def->name,
		SE(node2->sid).symb_def->dname,
		ae2->attr_def->name, follow_induced, *dep);
*/

	ProdCreateNew (prod->prod_def->did);
	switch (*dep & T_MASK)
	{
	      /* Direct, arranged and partitioned dependencies: Set the mark */
		case T_DIR:
		case T_ARR:
		case T_PART:	
			*dep |= T_MARK; break;

	      /* Transitive dependencies: Recursive call for the two parts */
		case T_TRAN:
		case T_TRAN | T_IND:
		case T_TRAN | T_ARR:
		case T_TRAN | T_PART:
			ProdFindTransitive (dep, det, prod, node1, node2, 
						ae1, ae2, follow_induced);
			break;

	      /* Induced dependencies: Switch context */
		case T_IND:
		case T_IND | T_ARR:
		case T_IND | T_PART:
			ProdFindInduced (dep,det,node1,ae1,ae2,follow_induced);
			break;

	      /* Unexpected dependencies: Give a warning */
		default:
			fprintf (stderr, "ProdFindPath: unexpected type: %o\n",
					*dep);
			break;
	}
}


/************************************************************************
 *                           SymbFindInduced				*
 ************************************************************************/

/* Finds the origin of a induced dependency. This is done by calling
 * ProdFindPath in the origin production context.
 */

PRIVATE void SymbFindInduced (dep, det, ae1, ae2, follow_induced)
	DEPENDENCY	*dep;
	DETAIL		*det;
	ATTRENTRY	*ae1, *ae2;
	int		follow_induced;
{
	SLNODE *inf = det->induced.from;

	if (follow_induced > 0)
	{
		*dep |= T_FOLLOWED;
		ProdFindPath (& PE(inf->pid), inf, inf, ae1, ae2, 
			      follow_induced - 1);
	}
	else
		*dep |= T_MARK;
}


/************************************************************************
 *                             SymbFindPath				*
 ************************************************************************/

/* Finds recursively the origin of the given dependency. Induced depen-	
 * cies are searched only up to the given limit <follow_induced>, which
 * represents the depth of the search, spoken in contexts.
 * The corresponding windows are automatically created, and the path is 
 * marked with wide lines.
 */

PUBLIC void SymbFindPath (symb, ae1, ae2, follow_induced)
	SYMBENTRY	*symb;
	ATTRENTRY	*ae1, *ae2;
	int		follow_induced;
{
	DEPENDENCY	*dep = & symb->ds[ae2->pos][ae1->pos];
	DETAIL		*det = & symb->ds_detail[ae2->pos][ae1->pos];

/*
	printf ("SymbFindPath: %s: %s -> %s (%d), Type %o\n",
		symb->symb_def->dname, ae1->attr_def->name, ae2->attr_def->name,
		follow_induced, *dep);
*/

	SymbCreateNew (symb->symb_def->did);
	switch (*dep & T_MASK)
	{
	      /* Direct, arranged and partitioned dependencies: Set the mark */
		case T_ARR:
		case T_PART:
			*dep |= T_MARK; break;

	      /* Induced dependencies: Switch context */
		case T_DIR:
		case T_IND:
		case T_IND | T_ARR:
		case T_IND | T_PART:
			SymbFindInduced (dep, det, ae1, ae2, follow_induced);
			break;

	      /* Unexpected dependencies: Give a warning */
		default:
			fprintf (stderr, "SymbFindPath: unexpected type: %o\n",
					*dep);
			break;
	}
}
