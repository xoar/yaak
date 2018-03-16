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
/* $Id: ProdDraw.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdDraw.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdDraw.c					*
 *									*
 *	CONTENTS:	Drawing of production graphs			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file contains functions dealing with the graphical representation
 * of production dependency graphs. 
 * There are functions to compute the size of a drawn production,
 * deal with resize events and redraw a production dependency graph.
 */

#include "Misc.h"
#include "Prod.h"
#include <X11/StringDefs.h>


/************************************************************************
 *			     ProdComputeSize  	                        *
 ************************************************************************/

/* Computes the width and height of this production and stores them
 * in the corresponding ref_tab entries.
 */

PUBLIC void ProdComputeSize (prod)
	PRODENTRY *prod;
{
	SLNODE		*nd;
	Dimension	rhs_length = 0;

      /* Initialize values */
	prod->dep_width  = 0;
	prod->rhs_width  = 0;
	prod->rhs_height = 0;

      /* Loop over the productions symbols */
	for (nd = prod->hdright->right; nd != NULL; nd = nd->right)
	{
	      /* Refer to the symbol`s entry in ref_tab */
		SYMBENTRY *symb = & SE(nd->sid);
		Dimension nw	= NormalDepWidth  (symb->length);
		Dimension iw	= InducedDepWidth (symb->length);

	      /* Maximize the dep width */
		if (nw > prod->dep_width) prod->dep_width = nw;

	      /* Maximize the widht of rhs */
		if ((Dimension)(symb->width + iw)  > prod->rhs_width)
			prod->rhs_width = symb->width + iw;

	      /* Add the symbol`s height */
		prod->rhs_height += symb->height + Res.symb_v_pad;
		rhs_length ++;
	}

      /* Substract the vertical padding after the last rhs symbol */
	if (rhs_length > 0)
		prod->rhs_height -= Res.symb_v_pad;
}


/************************************************************************
 *			  ProdComputeWindowSize				*
 ************************************************************************/

/* Computes the best size for a window containing this production.
 * Stores the results in width_return and height_return.
 */

PUBLIC void ProdComputeWindowSize (prod, width_return, height_return)
	PRODENTRY	*prod;
	Dimension	*width_return, *height_return;
{
	SYMBENTRY	*lhs  = & SE(prod->hdright->sid);
	Dimension	nw    = NormalDepWidth  (lhs->length);
	Dimension	iw    = InducedDepWidth (lhs->length);

      /* Width of lhs */
	*width_return = iw + lhs->width + nw;

      /* Width of rhs */
	if (prod->rhs_width != 0)
		*width_return += prod->dep_width + prod->rhs_width + 
				 Res.symb_h_pad;

      /* Construct return values */
	*width_return += 2 * Res.symb_h_pad;
	*height_return = MAX (lhs->height, prod->rhs_height) + 2*Res.symb_v_pad;
}


/************************************************************************
 *			       ProdResizeCB				*
 ************************************************************************/

/* This is the callback used for resize events on a production window.
 * We need only to perform layout calculation, since an expose event
 * will come next.
 */

/*ARGSUSED*/
PUBLIC void ProdResizeCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	static Dimension width, height;
	static Arg args[] = {{XtNwidth,  (XtArgVal) &width},
			     {XtNheight, (XtArgVal) &height}};

	PRODENTRY *prod = (PRODENTRY *) client_data;
	SYMBENTRY *lhs	= & SE(prod->hdright->sid);
	Dimension nw	= NormalDepWidth  (lhs->length);
	Dimension iw	= InducedDepWidth (lhs->length);

	SLNODE		*nd;
	Position	current_y;

      /* Get the new Window's width and height */
	XtGetValues (w, args, XtNumber (args));

      /* Compute the x coordinates */
	prod->par->lhs_x = (prod->rhs_width == 0) ?
		     ((Dimension)(width - iw - lhs->width - nw) / (Dimension)2 + iw) :
		     ((Dimension)(width - iw - lhs->width - nw -Res.symb_h_pad -
		       prod->rhs_width - prod->dep_width) / (Dimension)2 + iw);
	prod->par->rhs_x = prod->par->lhs_x + lhs->width + nw + 
			Res.symb_h_pad + prod->dep_width;

       /* Compute the y coordinates of the lhs */
	nd    = prod->hdright;
	nd->y = (Dimension)(height - lhs->height) / (Dimension)2;

       /* Compute the y coordinates of the rhs */
	current_y = (Dimension)(height - prod->rhs_height) / (Dimension)2;
	for (nd = nd->right; nd != NULL; nd = nd->right)
	{
		nd->y = current_y;
		current_y += SE(nd->sid).height + Res.symb_v_pad;
	}
}


/************************************************************************
 *			       ProdRedrawCB				*
 ************************************************************************/

/* This is the callback used for exposure events on a production window.
 * Simply calls ProdDrawSymbol for every symbol instance of this production.
 */

/*ARGSUSED*/
PUBLIC void ProdRedrawCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	Window		win   = XtWindow (w);
	PRODENTRY	*prod = (PRODENTRY *) client_data;
	Region		reg   = (Region) call_data;

	SLNODE	*nd;

      /* Switch the S_REDISPLAYED flag */
	prod->state &= ~S_REDISPLAYED;

      /* If this is the first invocation for the production, the */
      /* layout of the production needs to be calculated.        */
      /* This is done with the standard resize callback.         */
	if (prod->par->lhs_x == 0) ProdResizeCB (w, client_data, call_data);

      /* Draw every symbol instance of this production */
	SetLineAttrs (0, Solid);
	for (nd = prod->hdright; nd != NULL; nd = nd->right)
		ProdDrawSymbol (win, reg, nd);

      /* Draw the dependencies of this production */
	ProdDrawDep (win, reg, prod);
}
