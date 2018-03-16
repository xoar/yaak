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
/* $Id: SymbDraw.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: SymbDraw.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbDraw.c					*
 *									*
 *	CONTENTS:	Drawing of symbol graphs			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Graph.h"
#include "Symb.h"
#include <X11/StringDefs.h>


/************************************************************************
 *			  SymbComputeWindowSize				*
 ************************************************************************/

/* Computes the best size for a window containing this symbol.
 * Stores the results in width_return and height_return.
 */

PUBLIC void SymbComputeWindowSize (symb, width_return, height_return)
	SYMBENTRY	*symb;
        Dimension       *width_return, *height_return;
{
	Dimension nw = NormalDepWidth  (symb->attr_num);
	Dimension iw = InducedDepWidth (symb->attr_num);

	*width_return  = Res.symb_h_pad + nw + symb->sar->width +
			 iw + Res.symb_h_pad;
	*height_return = Res.symb_v_pad + symb->sar->height + Res.symb_v_pad;
}


/************************************************************************
 *			       SymbResizeCB				*
 ************************************************************************/

/* This is the callback used for resize events on a symbol window.
 */

/*ARGSUSED*/
PUBLIC void SymbResizeCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	static Dimension width, height;
	static Arg args[] = {
		{ XtNwidth, (XtArgVal) &width },
		{ XtNheight, (XtArgVal) &height },
	};

	SYMBENTRY *symb = (SYMBENTRY *) client_data;

	Dimension nw = NormalDepWidth  (symb->attr_num);
	Dimension iw = InducedDepWidth (symb->attr_num);

      /* Get the Window's width and height */
	XtGetValues (w, args, XtNumber (args));

      /* Center the symbol */
	symb->sar->x = (Position)(width  - symb->sar->width - nw - iw)  / (Position)2 + 
		       (Res.left_symbol ? iw : nw);
	symb->sar->y = (Position)(height - symb->sar->height) / (Position)2;
}


/************************************************************************
 *                            SymbRedrawAttr				*
 ************************************************************************/

PUBLIC void SymbRedrawAttr (attr)
	tSymbAttrSelection attr;
{
	Window		win = XtWindow (attr.symb->sar->widget);
	Position	x = attr.symb->sar->x;
	XFontStruct	*font  = attr.ae->state & A_CRITICAL ?
					Res.critical_font : Res.font;
	Dimension	height = attr.ae->state & A_CRITICAL ?
					CrAttrHeight-1 : AttrHeight-1;
	Dimension	width;

	if (attr.ae->attr_def->class == 0) x += Res.synt_indent;

	width = attr.symb->sar->width - 2 - Res.synt_indent;

	SetAttrGCElems (attr.ae);
	if (SymbMarkedAttr.ae == attr.ae)
	{
		XFillRectangle (dpy, win, gc, x+1, attr.y+1, width, height);
		SetForeground (GraphBackground (attr.symb->sar->widget));
	}
	else
		XClearArea (dpy, win, x+1, attr.y+1, width, height, False);

	XDrawString (dpy, win, gc, 
			x + (Position)(attr.symb->width-Res.synt_indent-attr.ae->width)/(Position)2,
			attr.y + Res.text_pad + 1 + font->ascent,
			attr.ae->attr_def->name,
			strlen (attr.ae->attr_def->name));
}


/************************************************************************
 *			       SymbRedrawCB				*
 ************************************************************************/

/* This is the callback used for exposure events on a symbol window.
 */

/*ARGSUSED*/
PUBLIC void SymbRedrawCB (w, client_data, call_data)
	Widget	w;
	caddr_t	client_data;
	caddr_t	call_data;
{
	ATTRENTRY *ae;

	Window		win   = XtWindow (w);
	SYMBENTRY	*symb = (SYMBENTRY *) client_data;
	Region		reg   = (Region) call_data;

	char		*sname= symb->symb_def->dname;

	Position x, y, x2, old_xl, old_xr;

      /* Switch the S_REDISPLAYED flag */
	symb->state &= ~S_REDISPLAYED;

      /* If this is the first invocation for the symbol, the
	 layout of this symbol needs to be calculated.	     */
	if (symb->sar->x == 0) SymbResizeCB (w, client_data, call_data);

      /* Initialize values */
	x       = symb->sar->x;
	y       = symb->sar->y;
	x2	= x + symb->sar->width - 1;
	old_xl	= x + Res.synt_indent;
	old_xr  = x2 - Res.synt_indent;

      /* Draw the centered symbol name */
	CurrentSegment = & LineSegments[0];
	XSetFont (dpy, gc, Res.bold_font->fid);
	SetForeground (Res.symb_pixel);
	XDrawString (dpy, win, gc, 
		     (int) (x + (Position)(symb->sar->width -
			     XTextWidth(Res.bold_font,sname,strlen(sname)))/(Position)2),
		     y + Res.text_pad + Res.bold_font->ascent,
		     sname, strlen (sname));

      /* Now loop over the symbol's attributes */
	y += 2*Res.text_pad + Res.bold_font->ascent + Res.bold_font->descent;
	for (ae = symb->first_attr; ae != NULL; ae = ae->next)
	{
		Position	old_y = y;
		Position	xl, xr;
		XFontStruct	*font = ae->state & A_CRITICAL ?
						Res.critical_font : Res.font;

	      /* Compute the x-coordinates of the enclosing lines */
		xl = CLASS(ae)==0 ? (x+Res.synt_indent) : x;
		xr = CLASS(ae)==0 ? x2		        : (x2-Res.synt_indent);

	      /* Remember the separating line */
		NewSegment (MIN(xl,old_xl), y, MAX(xr,old_xr), y);

	      /* Draw the attribute's name */
		SetAttrGCElems (ae);
		if (SymbMarkedAttr.ae == ae)
		{
			XFillRectangle (dpy, win, gc,
					xl, y+1, 
					(Dimension) xr - xl, 
					ae->state & A_CRITICAL ?
					 CrAttrHeight-1 : AttrHeight-1);
			SetForeground (GraphBackground (symb->sar->widget));
		}
		y += Res.text_pad + 1 + font->ascent;
		XDrawString (dpy, win, gc,
			xl + (Position)(symb->width - Res.synt_indent - ae->width) / (Position)2, y,
			ae->attr_def->name, strlen(ae->attr_def->name));
		y += Res.text_pad + font->descent;

	      /* Remember the left and right lines */
		NewSegment (xl, old_y, xl, y);
		NewSegment (xr, old_y, xr, y);

	      /* Remember the old values */
		old_xl = xl;
		old_xr = xr;
	}

      /* Remember the last closing line */
	if (symb->attr_num > 0)
	{
		NewSegment (old_xl, y, old_xr, y);
		SymbDrawDep (win, reg, symb);
	}

      /* Perform the actual line drawing */
	if (CurrentSegment - & LineSegments[0] > 0)
	{
		SetLineAttrs (0, Solid);
		SetForeground (Res.line_pixel);
		XDrawSegments (dpy, win, gc, LineSegments,
					     CurrentSegment - &LineSegments[0]);
	}
}
