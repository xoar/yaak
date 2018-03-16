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
/* $Id: ProdSymbol.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: ProdSymbol.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Prod/ProdSymbol.c				*
 *									*
 *	CONTENTS:	Routines dealing with symbols contained in	*
 *			production windows				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Graph.h"
#include "Symb.h"
#include "Prod.h"


/************************************************************************
 *                          ProdSortAttributes				*
 ************************************************************************/

/* Sorts the attributes of the given symbol. The order of the attributes
 * is stored in a linked list starting with symb->first_attr.
 */

PUBLIC void ProdSortAttributes (symb)
	SYMBENTRY *symb;
{
	SEQAttrdef	sad;
	Attrdef		ad;

	ATTRENTRY	*new, *ae;

      /* Initialize the attribute list */
	symb->first_attr = NULL;
	symb->last_attr  = NULL;
	symb->length = 0;

      /* Sort the symbols attributes */
	foreachinSEQAttrdef (symb->symb_def->attrs, sad, ad)
	{
		new = & AE(ad->did);

		if (! (new->state & A_HIDDEN)) symb->length ++;

	      /* Find a place for the new attribute */
		ae = symb->first_attr;
		while (ae != NULL && AttrAfter (ae, new)) ae = ae->next;

	      /* Insert the new attribute */
		if (ae != NULL)
		{
			if (ae->last)	ae->last->next = new;
			else		symb->first_attr = new;
			new->last = ae->last;
			new->next = ae;
			ae->last = new;
		}
		else
		{
			if (symb->last_attr)	symb->last_attr->next = new;
			else			symb->first_attr = new;
			new->last = symb->last_attr;
			new->next = NULL;
			symb->last_attr = new;
		}
	}
}


/************************************************************************
 *			    ComputeUpDownSpace				*
 ************************************************************************/

/* Computes recursive the up_space and down_space entries of a given
 * symbol's attributes in ref_tab.
 */

PRIVATE void ComputeUpDownSpace (ae, up_l, up_r, down_l_return, down_r_return)
	ATTRENTRY	*ae;
	int		up_l, up_r;
	int		*down_l_return, *down_r_return;
{
	int down_l, down_r, height2, nheight2;

	if (ae == NULL) 
	{
		down_l = 0;
		down_r = ALL_SPACE;
	}
	else 
	{
		height2 = ae->state&A_CRITICAL ? CrAttrHeight/2 : AttrHeight/2;
		nheight2= ae->next == NULL ? 0
					   : ae->next->state & A_CRITICAL ?
					      CrAttrHeight/2 : AttrHeight/2;

		if (ae->attr_def->class == 0)
		{
			ae->up_space = up_l;
			ComputeUpDownSpace (ae->next, up_l+height2+nheight2, 
				nheight2, & ae->down_space, (int *) NULL);
			if (ae->next == NULL)
				ae->down_space = height2 + Res.symb_v_pad;
			down_l = ae->down_space+height2+nheight2;
			down_r = nheight2;
		}
		else
		{
			ae->up_space = up_r;
			ComputeUpDownSpace (ae->next,
					nheight2, up_r+height2+nheight2, 
					(int *) NULL, &ae->down_space);
			down_l = nheight2;
			down_r = ae->down_space+height2+nheight2;
		}
	}

	if (down_l_return != NULL) *down_l_return = down_l;
	if (down_r_return != NULL) *down_r_return = down_r;
}


/************************************************************************
 *			  ProdComputeAttrSpaces				*
 ************************************************************************/

/* Computes the up_space and down_space entries of a given symbol's
 * attributes in ref_tab. They are used for the drawing of dependencies.
 */

PUBLIC void ProdComputeAttrSpaces (symb)
	SYMBENTRY *symb;
{
	int height = symb->first_attr == NULL ? 0 :
		(symb->first_attr->state&A_CRITICAL ? CrAttrHeight:AttrHeight);

	ComputeUpDownSpace (symb->first_attr, height/2, height/2,
				(int *) NULL, (int *) NULL);
}


/************************************************************************
 *			   ProdComputeAttrSizes				*
 ************************************************************************/

PUBLIC void ProdComputeAttrSizes (symb)
	SYMBENTRY *symb;
{
	ATTRENTRY *ae;

	for (ae = symb->first_attr; ae != NULL; ae = ae->next)
		ae->width = XTextWidth (ae->state & A_CRITICAL ?
				Res.critical_font : Res.font,
				ae->attr_def->name, strlen(ae->attr_def->name));
}


/************************************************************************
 *			  ProdComputeSymbolSize				*
 ************************************************************************/

/* Computes the width and height entries for the Symbol symb in ref_tab .
 */

PUBLIC void ProdComputeSymbolSize (symb)
	SYMBENTRY *symb;
{
	SEQAttrdef	sad;    /* used for loop over the */
	Attrdef		attr;   /* symbol's attributes    */

      /* Initialize width and height */
	symb->width  = XTextWidth (Res.bold_font, symb->symb_def->dname,
				   strlen (symb->symb_def->dname));
	symb->height = 1 + 2*Res.text_pad + Res.bold_font->ascent +
				            Res.bold_font->descent;

      /* Now loop over the Symbol's Attributes */
	foreachinSEQAttrdef (symb->symb_def->attrs, sad, attr)
	{
		Dimension	w;
		ATTRENTRY	*ae = & AE(attr->did);

	      /* Don't look at hidden attributes */
		if (ae->state & A_HIDDEN) continue;

	      /* Compute the maximum width */
		w = ae->width + Res.synt_indent;
		if (w > symb->width) symb->width = w;

	      /* Compute the sum of attribute heights */
		symb->height += ae->state&A_CRITICAL ? CrAttrHeight:AttrHeight;
	}

      /* Add the space needed for padding */
	symb->width +=  2 + 2*Res.text_pad;
}


/************************************************************************
 *			      ProdRedrawAttr				*
 ************************************************************************/

/* Redraws the given attribute <attr> of a production context.
 */

PUBLIC void ProdRedrawAttr (attr)
	tProdAttrSelection attr;
{
	PRODENTRY	*prod  = & PE(attr.node->pid);
	SYMBENTRY	*symb  = & SE(attr.node->sid);
	Window		win    = XtWindow (prod->par->widget);
	XFontStruct	*font  = attr.ae->state & A_CRITICAL ?
					Res.critical_font : Res.font;
	Position	x      = prod->hdright == attr.node ? 
					prod->par->lhs_x : prod->par->rhs_x;
	Dimension	height = attr.ae->state & A_CRITICAL ?
					CrAttrHeight-1 : AttrHeight-1;
	Dimension	width;

	if (attr.ae->attr_def->class == 0) x += Res.synt_indent;

	width = symb->width - 2 - Res.synt_indent;

	SetAttrGCElems (attr.ae);
	if (attr.node == ProdMarkedAttr.node &&
	    attr.ae   == ProdMarkedAttr.ae)
	{
		XFillRectangle (dpy, win, gc, 
				x+1, attr.y+1, width, height);
		SetForeground (GraphBackground (prod->par->widget));
	}
	else	
		XClearArea (dpy, win, x+1, attr.y+1, width, height, False);

	XDrawString (dpy, win, gc,
		x + (Dimension)(symb->width - Res.synt_indent - attr.ae->width) / (Dimension)2,
		attr.y + Res.text_pad + 1 + font->ascent,
		attr.ae->attr_def->name, strlen (attr.ae->attr_def->name));
}


/************************************************************************
 *			      ProdDrawSymbol 				*
 ************************************************************************/

/* Draws the symbol sid at the specified coordinates in Window win.
 */

PUBLIC void ProdDrawSymbol (win, reg, nd)
	Window		win;
	Region		reg;
	SLNODE		*nd;
{
	SYMBENTRY	*symb	= & SE(nd->sid);
	PRODENTRY	*prod	= & PE(nd->pid);
	char		*sname  = symb->symb_def->dname;

	Position x	= prod->hdright == nd ? prod->par->lhs_x : 
						prod->par->rhs_x;
	Position y	= nd->y;
	Position x2	= x + symb->width -1;
	Position old_xl	= x + Res.synt_indent;
	Position old_xr	= x2- Res.synt_indent;
	ATTRENTRY *ae;

      /* Test the enclosing rectangle against the clipping region */
	if (XRectInRegion (reg,x,y,symb->width,symb->height) == RectangleOut)
		return;

      /* Draw the centered symbol name */
	XSetFont (dpy, gc, Res.bold_font->fid);
	SetForeground (Res.symb_pixel);
	XDrawString (dpy, win, gc, 
		     (int) (x + (Dimension)(symb->width -
			      XTextWidth(Res.bold_font,sname,strlen(sname)))/(Dimension)2),
		     y + Res.text_pad + Res.bold_font->ascent,
		     sname, strlen (sname));

      /* Now loop over the symbol's attributes */
	CurrentSegment = & LineSegments[0];
	y += 2*Res.text_pad + Res.bold_font->ascent + Res.bold_font->descent;
	for (ae = symb->first_attr; ae!=NULL; ae=ae->next)
	{
		bool		synt	= ae->attr_def->class == 0;
		Position	old_y	= y;
		Position	xl, xr;
		XFontStruct	*font	= ae->state & A_CRITICAL ?
						Res.critical_font : Res.font;

		if (ae->state & A_HIDDEN) continue;

	      /* Compute the x-coordinates of the enclosing lines */
		xl = synt ? (x + Res.synt_indent)  : x;
		xr = synt ? x2                     : (x2 - Res.synt_indent);
			
	      /* Remember the separating line */
		NewSegment (MIN(xl,old_xl), y, MAX(xr,old_xr), y);

	      /* Draw the attribute's name */
		SetAttrGCElems (ae);
		if (nd == ProdMarkedAttr.node && ae == ProdMarkedAttr.ae)
		{
			XFillRectangle (dpy, win, gc,
					xl, y+1, 
					(Dimension) xr - xl, 
					ae->state&A_CRITICAL ?  CrAttrHeight-1:
								AttrHeight-1);
			SetForeground (GraphBackground (prod->par->widget));
		}
		y += Res.text_pad + 1 + font->ascent;
		XDrawString (dpy, win, gc, xl + 
			    (Dimension)(symb->width - Res.synt_indent - ae->width) / (Dimension)2, y,
			     ae->attr_def->name, strlen (ae->attr_def->name));
		y += Res.text_pad + font->descent;

	      /* Remember the left and right lines */
		NewSegment (xl, old_y, xl, y);
		NewSegment (xr, old_y, xr, y);

	      /* Remember the old values */
		old_xl = xl;
		old_xr = xr;
	}

      /* Remember the last closing line */
	if (symb->length > 0)
		NewSegment (old_xl, y, old_xr, y);

      /* Perform the actual line drawing */
	if (CurrentSegment - & LineSegments[0] > 0)
	{
		SetForeground (Res.line_pixel);
		SetLineAttrs (0, Solid);
		XDrawSegments (dpy, win, gc, LineSegments, 
					     CurrentSegment - &LineSegments[0]);
	}
}
