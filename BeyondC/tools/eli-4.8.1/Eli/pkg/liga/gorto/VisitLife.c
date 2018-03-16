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
/* $Id: VisitLife.c,v 4.2 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: VisitLife.c,v 4.2 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitLife.c				*
 *									*
 *	CONTENTS:	Computation of attribute lifetimes		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Visit.h"

#include <stdio.h>

PRIVATE SYMBENTRY *MarkedLifeSymb = (SYMBENTRY *) NULL;
PRIVATE ATTRENTRY *MarkedLifeAE   = (ATTRENTRY *) NULL;

#define DEFINING_OCC(lhs,synt) (((lhs) && (synt)) || (!(lhs) && !(synt)))

/************************************************************************
 *			      InitLifetimes				*
 ************************************************************************/

/* Initializes the lifetime information for the given production.
 */

PRIVATE void InitLifetimes (prod)
	PRODENTRY *prod;
{
	int		i;
	LIFETIME	*life = & prod->vs->lifetimes[0];

	for (i=0; i < prod->check_row; i++)
	{
		life->last_local  = (VSPTR) NULL;
		life->last_global = (VSPTR) NULL;
		life ++;
	}
}


/************************************************************************
 *			     UpdateLastLocal				*
 ************************************************************************/

/* Updates the last_local entries of all attribute instances of the
 * given production, which are used for the computation of the attribute
 * instance represented by the given visit-sequence element.
 */
 
PRIVATE void UpdateLastLocal (prod, vsord, elem, dep_row)
	PRODENTRY	*prod;
	int		vsord[];
	VSPTR		elem;
	DEP_VECTOR	dep_row;
{
	SLNODE		*nd;
	SEQAttrdef	sad;
	Attrdef		ad;
	int		index, sno;

	sno = 0;
	for (nd = prod->hdright; nd != NULL; nd = nd->right, sno++)
	{
		index = nd->start_row;
		foreachinSEQAttrdef (SE(nd->sid).symb_def->attrs, sad, ad)
		{
			if (dep_row[index] & T_DIR)
			{
				prod->vs->lifetimes[index].last_local = elem;
				if (!DEFINING_OCC(sno == 0, ad->class == 0) &&
				    vsord[sno] > AE(ad->did).life_vsno)
				{
					AE(ad->did).life_vsno = vsord[sno];
					AE(ad->did).life_node = nd;
				}
			}
			index ++;
		}
	}
}


/************************************************************************
 *			  ComputeLocalLifetimes				*
 ************************************************************************/

/* Computes the local lifetime information for all attribute instances
 * of the given production. The resulting last use of the attribute
 * instances is maximized in the corresponding attribute entry.
 */

PRIVATE void ComputeLocalLifetimes (prod)
	PRODENTRY *prod;
{
	VSPTR		elem;
	LIFETIME	*life;
	SLNODE		*nd;
	int		i;
	int		*vsord = (int *)NULL;/* now dynamic allocated array */

      vsord = (int *)XtMalloc( (MaxRhsLen+1)*sizeof(int) );

      /* Initialize vsord[] */
	for (i = 0; i < MaxRhsLen; i++)
		vsord[i] = i < prod->check_row ? 1 : -1;
	
      /* Loop over the elements of the visit-sequence */
	for (elem = prod->visitseq; elem != NULL; elem = elem->next)
	{
		if (elem->vscls == VSASSIG)
		{
		      /* Locate corresponding symbol instance and lifetime */
			nd   = SymbnoToNode (prod, elem->vsinfo.assig.sno);
			life = & prod->vs->lifetimes[nd->start_row +
						 elem->vsinfo.assig.apos];

		      /* Update the last_local entries */
			UpdateLastLocal (prod, vsord, elem, prod->dp
				[nd->start_row+elem->vsinfo.assig.apos]);
		}
		else if (elem->vscls == VSVISIT)
		{
			vsord[elem->vsinfo.visit.vssno] = 
				elem->vsinfo.visit.vsord;
			if (elem->vsinfo.visit.vssno == 0) vsord[0] ++;
		}
	}
}


/************************************************************************
 *			       EnterLastUse				*
 ************************************************************************/

PRIVATE void EnterLastUse (prod, elem)
	PRODENTRY	*prod;
	VSPTR		elem;
{
	SLNODE		*nd;
	SEQAttrdef	sad;
	Attrdef		ad;
	int		index;

	for (nd = prod->hdright; nd != NULL; nd = nd->right)
	{
		index = nd->start_row - 1;
		foreachinSEQAttrdef (SE(nd->sid).symb_def->attrs, sad, ad)
		{
			index ++;
			if (!DEFINING_OCC (nd==prod->hdright, ad->class==0))
				continue;

			if (elem == prod->vs->lifetimes[index].last_local)
				prod->vs->lifetimes[index].last_global = elem;

			if (elem->vscls == VSVISIT &&
			    elem->vsinfo.visit.vssid == nd->sid &&
			    AE(ad->did).life_vsno == elem->vsinfo.visit.vsord)
				prod->vs->lifetimes[index].last_global = elem;
		}
	}
}


/************************************************************************
 *			  VisitComputeLifetimes				*
 ************************************************************************/

/* Computes the lifetimes of all attribute instances for all productions.
 */

PUBLIC void VisitComputeLifetimes()
{
	int		i;
	PRODENTRY	*prod;
	VSPTR		elem;

      /* Initialize global life_vsno entries for all attributes */
	for (i = min_entry; i <= max_entry; i++)
		if (ref_tab[i].etag == ATTR) AE(i).life_vsno = -1;

      /* Compute the local attribute lifetimes */
	for (i = min_entry; i <= max_entry; i++)
		if (ref_tab[i].etag == PROD)
		{
			prod = & PE (i);
			if (prod->vs == (VSINFO *) NULL)
			{
				prod->vs = XtNew (VSINFO);
				prod->vs->vsar		= (VSAR *) NULL;
				prod->vs->geometry	= (String) NULL;
				prod->vs->width		= (Dimension) 0;
				prod->vs->height 	= (Dimension) 0;
				prod->vs->length	= 0;
				prod->vs->lifetimes	= (LIFETIME *)
				    XtMalloc (sizeof(LIFETIME)*(prod->check_row+1));
				prod->vs->marked_elem	= (VSPTR) NULL;
			}
			InitLifetimes (prod);
			ComputeLocalLifetimes (prod);
		}

      /* Distribute the life_vsno entries to compute global lifetimes */
	for (i = min_entry; i <= max_entry; i++)
		if (ref_tab[i].etag == PROD)
		{
			prod = & PE (i);
			elem = prod->visitseq;
			for (; elem != NULL; elem = elem->next)
				EnterLastUse (prod, elem);
		}
}


/************************************************************************
 *			   VisitUpdateProdLifes
 ************************************************************************/

PUBLIC void VisitUpdateProdLifes (prod)
	PRODENTRY *prod;
{
	VSPTR elem = prod->visitseq;

	InitLifetimes (prod);
	ComputeLocalLifetimes (prod);
	for (; elem != NULL; elem = elem->next)
		EnterLastUse (prod, elem);
}


/************************************************************************
 *			   VisitUnmarkLifetime				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitUnmarkLifetimeCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	SLNODE *nd;
	VSINFO *vs;

	if (MarkedLifeSymb != (SYMBENTRY *) NULL)
	{
		for (nd = MarkedLifeSymb->hddown; nd != NULL; nd = nd->down)
			if ((vs = PE(nd->pid).vs) != NULL)
			{
				vs->marked_elem = (VSPTR) NULL;
				if (vs->vsar != NULL)
					RedisplayWidget (vs->vsar->widget);
			}

		MarkedLifeSymb = (SYMBENTRY *) NULL;
		MarkedLifeAE   = (ATTRENTRY *) NULL;
	}
}


/************************************************************************
 *			    VisitMarkLifetime				*
 ************************************************************************/

PUBLIC void VisitMarkLifetime (symb, ae)
	SYMBENTRY *symb;
	ATTRENTRY *ae;
{
	SLNODE *nd;
	VSPTR  elem;
	PRODENTRY	*prod;
	LIFETIME	*life;
	Boolean		seen;

	VisitUnmarkLifetimeCB ((Widget) NULL, (caddr_t) NULL, (caddr_t) NULL);

	for (nd = symb->hddown; nd != NULL; nd = nd->down)
	{
		prod = & PE(nd->pid);
		life = & prod->vs->lifetimes[nd->start_row + ae->pos];
		seen = prod->vs->marked_elem == NULL;

		if (prod->vs->vsar != NULL)
			RedisplayWidget (prod->vs->vsar->widget);

		if (life->last_global != NULL)
		{
			prod->vs->marked_elem = life->last_global;
			continue;
		}

		for (elem = prod->visitseq; elem != NULL; elem = elem->next)
		{
			if (elem == prod->vs->marked_elem) seen = True;

			if (elem == life->last_local && seen)
				prod->vs->marked_elem = elem;
		}

	}

	MarkedLifeSymb = symb;
	MarkedLifeAE   = ae;
}


/************************************************************************
 *			      VisitDrawLifes				*
 ************************************************************************/

PRIVATE DEPENDENCY life_dep = {T_DIR};

PUBLIC void VisitDrawLifes (win, reg, prod)
	Window		win;
	Region		reg;
	PRODENTRY	*prod;
{
	VSPTR		elem1, last1, elem2, last2;
	Position	y1, y2;
	int		no1, no2, synt1, synt2;
	LIFETIME	*life1;
	SLNODE		*node1;

	DepInitiate (win, reg, 0, 0, True);
	last1 = NULL;
	elem1 = prod->visitseq;
	y1    = prod->vs->vsar->y + 
	       (ElemCritical(prod,elem1,last1) ? CrAttrHeight/2 : AttrHeight/2);
	no1   = 0;

	for (; elem1 != NULL; elem1=elem1->next, no1++)
	{
		y2  = y1;
		no2 = no1;

		if (elem1->vscls == VSASSIG)
		{
			node1 = SymbnoToNode (prod, elem1->vsinfo.assig.sno);
			life1 = &prod->vs->lifetimes
				 [node1->start_row + elem1->vsinfo.assig.apos];
			elem2 = elem1;
		}
		else
			elem2 = NULL;
		last2 = last1;

		if (IS_VISIT (elem1))		synt1 = 2;
		else if (IS_LEAVE (elem1))	synt1 = 0;
		else				synt1 = 1;

		for (; elem2 != NULL; elem2=elem2->next, no2++)
		{
			if (IS_VISIT (elem2))		synt2 = 2;
			else if (IS_LEAVE (elem2))	synt2 = 0;
			else				synt2 = 1;

			if (life1->last_global == elem2)
				(void) DoDep (& life_dep, 
					prod->vs->vsar->x, y1, no1, 
					prod->vs->width, synt1,
					prod->vs->vsar->x, y2, no2,
					prod->vs->width, synt2,
					0, 0, prod->vs->length, False);

			if (IS_LEAVE (elem2)) y2 += Res.symb_v_pad;
			y2 += ElemCritical (prod, elem2, last2) ?
					CrAttrHeight : AttrHeight;
			if (elem2->vscls != VSCOND) last2 = elem2;
		}

		if (IS_LEAVE (elem1)) y1 += Res.symb_v_pad;
		y1 += ElemCritical (prod, elem1, last1) ?
				CrAttrHeight : AttrHeight;
		if (elem1->vscls != VSCOND) last1 = elem1;
	}
}
