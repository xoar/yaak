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
/* $Id: VisitDraw.c,v 4.2 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: VisitDraw.c,v 4.2 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Visit/VisitDraw.c				*
 *									*
 *	CONTENTS:	Drawing of visit-sequences			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Graph.h"
#include "Visit.h"
#include <X11/StringDefs.h>


/************************************************************************
 *			      SetElemGCAttrs				*
 ************************************************************************/

PRIVATE void SetElemGCAttrs (elem)
	VSPTR elem;
{
	switch (elem->vscls)
	{
	case VSASSIG:	switch (AE(elem->vsinfo.assig.aid).attr_def->gen)
			{
			case 0:	SetForeground (Res.at_pixel);	break;
			case 1: SetForeground (Res.at_i_pixel);	break;
			case 2: SetForeground (Res.at_co_pixel);break;
			case 3: SetForeground (Res.at_ch_pixel);break;
			default:SetForeground (Res.at_pixel);	break;
			}
			break;
	case VSCOND:	SetForeground (Res.cond_pixel);		break;
	case VSVISIT:	SetForeground (Res.visit_pixel);	break;
	}
}


/************************************************************************
 *			     VisitComputeSize				*
 ************************************************************************/

PUBLIC void VisitComputeSize (prod)
	PRODENTRY *prod;
{
	VSPTR		elem;
	Dimension	w;

	prod->vs->width  = 0;
	prod->vs->height = 0;
	prod->vs->length = 0;

      /* Loop over the visit-sequence elements */
	for (elem=prod->visitseq; elem!=NULL; elem=elem->next)
	{
		String t = VisitElemString (elem);

	      /* Compute the maximum width */
		w = XTextWidth (Res.font, t, strlen(t));
		if (w > prod->vs->width) prod->vs->width = w;
		w = XTextWidth (Res.critical_font, t, strlen(t));
		if (w > prod->vs->width) prod->vs->width = w;

	      /* Count the number of elements */
		prod->vs->length ++;

	      /* Compute the sum of heights */
		if (IS_LEAVE (elem) && elem->next != NULL)
			prod->vs->height += Res.symb_v_pad;
	}

      /* Add the space needed for padding */
	prod->vs->width += 2 + 2*Res.text_pad;

      /* Compute the height */
	prod->vs->height += prod->vs->length * MAX (CrAttrHeight, AttrHeight);
}


/************************************************************************
 *			  VisitComputeWindowSize			*
 ************************************************************************/

PUBLIC void VisitComputeWindowSize (prod, width_return, height_return)
	PRODENTRY	*prod;
	Dimension	*width_return, *height_return;
{
	*width_return  = Res.symb_h_pad + prod->vs->width + 2*Res.synt_indent +
			 NormalDepWidth (prod->vs->length) + Res.symb_h_pad;
	*height_return = Res.symb_v_pad + prod->vs->height + Res.symb_v_pad;
}


/************************************************************************
 *			      VisitResizeCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitResizeCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	static Dimension width, height;
	static Arg args[] = {
		{ XtNwidth, (XtArgVal) &width },
		{ XtNheight, (XtArgVal) &height },
	};

	PRODENTRY *prod = (PRODENTRY *) client_data;

      /* Get the Window's width and height */
	XtGetValues (w, args, XtNumber (args));

      /* Center the visit-sequence */
	prod->vs->vsar->x = (Dimension)(width  - prod->vs->width - 
			    NormalDepWidth (prod->vs->length)) / (Dimension)2
				- Res.synt_indent;
	prod->vs->vsar->y = (Dimension)(height - prod->vs->height) / (Dimension)2;
}


/************************************************************************
 *			      VisitRedrawCB				*
 ************************************************************************/

/*ARGSUSED*/
PUBLIC void VisitRedrawCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	Window		win   = XtWindow (w);
	PRODENTRY	*prod = (PRODENTRY *) client_data;
	Region		reg   = (Region) call_data;

	Position	x0, x1, x2, y, old_xl, old_xr;
	VSPTR		elem, last;
	Boolean		visit_start = True;

      /* If this is the first invocation for the production, the */
      /* layout of the visit-sequence needs to be calculated.    */
      /* This is done with the standard resize callback. 	 */
	if (prod->vs->vsar->x == 0) VisitResizeCB (w, client_data, call_data);

      /* Initialize values */
	x0 = prod->vs->vsar->x;
	x1 = prod->vs->vsar->x + Res.synt_indent;
	x2 = x1 + Res.synt_indent;
	y  = prod->vs->vsar->y;

      /* Beginning of move range */
	if (prod == VisitMarkedElem.prod && MoveRangeStartElem == NULL)
	{
		SetForeground (Res.line_pixel);
		SetLineAttrs (3, Solid);
		XDrawLine (dpy, win, gc, x0, y, x2+prod->vs->width, y);
	}

      /* Loop over the visit-sequence elements */
	last = NULL;
	for (elem=prod->visitseq; elem!=NULL; elem=elem->next)
	{
		String 	 t     = VisitElemString (elem);
		Position old_y = y;
		Position xl, xr;
		Dimension w;

		Boolean		critical = ElemCritical (prod, elem, last);
		XFontStruct	*font = critical ? Res.critical_font : Res.font;

	      /* Test for beginning of a visit-sequence part */
		if (visit_start)
		{
			visit_start    = False;
			old_xl         = x2;
			old_xr         = x0 + prod->vs->width - 1;
		}

	      /* Compute the x-coordinates of the enclosing lines */
		if (IS_LEAVE (elem))		xl = x0;
		else if (IS_VISIT (elem))	xl = x2;
		else				xl = x1;
		xr = xl + prod->vs->width - 1;

	      /* Separating line or beginning of move range */
		CurrentSegment = & LineSegments[0];
		if (elem == MoveRangeStartElem)
		{
			SetForeground (Res.line_pixel);
			SetLineAttrs (3, Solid);
			XDrawLine (dpy, win, gc, x0, y, x2+prod->vs->width, y);
		}
		else
			NewSegment (MIN(xl,old_xl), y, MAX(xr,old_xr), y);

	      /* Draw the element string */
		SetElemGCAttrs (elem);
		if (elem == VisitMarkedElem.elem ||
		    (prod != VisitMarkedElem.prod &&
		     elem == prod->vs->marked_elem))
		{
			XFillRectangle (dpy, win, gc, xl, y+1, (Dimension)xr-xl,
					critical ? CrAttrHeight-1:AttrHeight-1);
			SetForeground (GraphBackground(prod->vs->vsar->widget));
		}
		y += Res.text_pad + 1 + font->ascent;
		XSetFont (dpy, gc, font->fid);
		w = XTextWidth (font, t, strlen(t));
		XDrawString (dpy, win, gc, xl + (Dimension)(prod->vs->width - w) / (Dimension)2, y,
				t, strlen (t));
		y += font->descent + Res.text_pad;

	      /* Left and right lines */
		NewSegment (xl, old_y, xl, y);
		NewSegment (xr, old_y, xr, y);

	      /* End of move range */
		if (elem == MoveRangeEndElem)
		{
			SetForeground (Res.line_pixel);
			SetLineAttrs (3, Solid);
			XDrawLine (dpy, win, gc, x0, y, x2+prod->vs->width, y);
		}

	      /* Remember the old values */
		old_xl = xl;
		old_xr = xr;

	      /* Test for ending of a visit-sequence part */
		if (IS_LEAVE (elem))
		{
		      /* Last closing line */
			NewSegment (old_xl, y, old_xr, y);

		      /* Initiate new visit-sequence part */
			visit_start = True;
			y += Res.symb_v_pad;
		}

	      /* Draw the accumulated lines */
		if (XRectInRegion (reg, x0, LineSegments[0].y1,
				prod->vs->width + 2*Res.synt_indent,
				y-LineSegments[0].y1+1)
			!= RectangleOut)
		{
			SetLineAttrs (0, Solid);
			SetForeground (Res.line_pixel);
			XDrawSegments (dpy, win, gc, LineSegments,
				       CurrentSegment-&LineSegments[0]);
		}

	      /* Update <last> pointer */
		if (elem->vscls != VSCOND) last = elem;
	}
	VisitDrawLifes (win, reg, prod);
}
