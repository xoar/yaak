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
/* $Id: Drawing.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Drawing.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Drawing.c					*
 *									*
 *	CONTENTS:	Utilities used for drawing with raw X calls	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* The functions contained in this file are used to set the elements of
 * the global graphics context <gc>. 
 *
 * Only one graphics context is used for all raw X calls of the program, 
 * since a lot of changes to the graphics context must be made, and a set
 * of more than one graphics contexts wouldn't do that reasonably faster.
 *
 * The current elements of <gc> are remembered by all functions, and only 
 * the X calls necessary to change them are emitted. This should reduce the
 * total number of raw X calls for gc changing.
 */

#include "Misc.h"


/************************************************************************
 *			     Global Variables				*
 ************************************************************************/

/* Startup values for the foreground color, line width and dash style */
#define INIT_FOREGROUND		Res.at_pixel
#define INIT_LINE_WIDTH		0
#define INIT_DASH_VALUE		Dash
#define INIT_DASH_PATTERN	dash

/* Current elements of graphics context. Before changing an element of 
 * the global graphics context, the desired value is compared against
 * the current value. This reduces the number of raw X Calls.
 */
PRIVATE Pixel	   CurrentForeground;
PRIVATE int        CurrentLineWidth = INIT_LINE_WIDTH;
PRIVATE DASH_STYLE CurrentLineStyle = Solid;
PRIVATE DASH_STYLE CurrentDashes    = INIT_DASH_VALUE;

/* Dash patterns */
static char dot[]	= {2, 2};
static char dash[]	= {6, 2};

/* Display and graphics context */
PUBLIC Display	*dpy;
PUBLIC GC	gc;

/* Public buffer for line segments */
PUBLIC XSegment *LineSegments, *CurrentSegment;


/************************************************************************
 *			       InitDrawing				*
 ************************************************************************/

/* Initializes the public variables in this file.
 * <max_segments> is the maximum number of line segments that will be used
 * in one call to XDrawSegments. It is used to allocate the public buffer
 * <LineSegments>. 
 */

PUBLIC void InitDrawing (max_segments)
	int max_segments;
{
      /* Get the default graphics context */
	gc = DefaultGC (dpy, DefaultScreen (dpy));

      /* Initialize those elements which are described by 
       * global variables in this file
       */
	XSetForeground     (dpy, gc, CurrentForeground = INIT_FOREGROUND);
	XSetLineAttributes (dpy, gc, INIT_LINE_WIDTH, LineSolid,
				     CapButt, JoinMiter);
	XSetDashes         (dpy, gc, 0, INIT_DASH_PATTERN, 
				     XtNumber(INIT_DASH_PATTERN));

      /* Allocate the public buffer for line segment drawing */
	LineSegments = (XSegment *) XtMalloc (sizeof(XSegment) * max_segments);
}


/************************************************************************
 *			       SetLineAttrs				*
 ************************************************************************/

/* Updates line width, line style and dashes in the global graphics context
 * to reflect the given values of <line_width> and <line_style>. X Calls
 * are ommitted only for necessary changes.
 */

PUBLIC void SetLineAttrs (line_width, line_style)
	unsigned	line_width;
	DASH_STYLE	line_style;
{
      /* Do we need some change at all? */
	if (line_width != CurrentLineWidth || line_style != CurrentLineStyle)
	{
	      /* Update the current line width and style */
		CurrentLineWidth = line_width;
		CurrentLineStyle = line_style;
		XSetLineAttributes (dpy, gc, line_width, 
			line_style == Solid ? LineSolid : LineOnOffDash, 
					 CapButt, JoinMiter);

	      /* Do the current dashes need a change? */
		if (line_style != Solid && CurrentDashes != line_style)
		{
		      /* Update the current dashes */
			CurrentDashes = line_style;
			switch (CurrentDashes)
			{
			case Dot:
			XSetDashes (dpy, gc, 0, dot, XtNumber (dot)); break;

			case Dash:
			XSetDashes (dpy, gc, 0, dash, XtNumber (dash)); break;

			case Solid:
			break;
			}
		}
	}
}


/************************************************************************
 *			      SetForeground				*
 ************************************************************************/

/* Updates the foreground pixel in the global graphics context to reflect
 * the given value of <col>. X Calls are ommitted only for necessary changes.
 */

PUBLIC void SetForeground (col)
	Pixel col;
{
      /* Do we need some change? */
	if (CurrentForeground != col)
	{
	      /* Update current foreground */
		XSetForeground (dpy, gc, CurrentForeground = col);
	}
}


/************************************************************************
 *			      SetAttrGCElems				*
 ************************************************************************/

/* Sets the elements of the global graphics context to the correct values
 * for the following attribute name drawing.
 */

PUBLIC void SetAttrGCElems (ae)
	ATTRENTRY *ae;
{
      /* Set the font */
	XSetFont (dpy, gc, (ae->state&A_CRITICAL) ? 
			   Res.critical_font->fid : Res.font->fid);

      /* Set the foreground pixel */
	switch (ae->attr_def->gen)
	{
	case 0:	 SetForeground (Res.at_pixel);		break;
	case 1:	 SetForeground (Res.at_i_pixel);	break;
	case 2:	 SetForeground (Res.at_co_pixel);	break;
	case 3:	 SetForeground (Res.at_ch_pixel);	break;
	default: SetForeground (Res.at_pixel);		break;
	}
}


/************************************************************************
 *			      SetDepGCElems				*
 ************************************************************************/

/* Sets the elements of the global graphics context to the correct values
 * for the following dependency drawing.
 */

PUBLIC void SetDepGCElems (type)
	short type;
{
	unsigned int width = (type & T_MARK) ? 3 : 0;

      /* Set the line attributes */
	if (type & T_FOLLOWED)		SetLineAttrs (3, Dash);
	else if (type & T_ARR)		SetLineAttrs (width, Dash);
	else if (type & T_PART)		SetLineAttrs (width, Dot);
	else				SetLineAttrs (width, Solid);

      /* Set the foreground pixel */
	switch (type & T_MASK)
	{
	case T_DIR:			SetForeground (Res.d_pixel);	break;
	case T_IND:			SetForeground (Res.i_pixel);	break;
	case T_ARR:			SetForeground (Res.a_pixel);	break;
	case T_IND | T_ARR:		SetForeground (Res.ai_pixel);	break;
	case T_PART:			SetForeground (Res.p_pixel);	break;
	case T_IND | T_PART:		SetForeground (Res.ip_pixel);	break;
	default:	printf ("SetDepGCAttrs: Unexpexted type: %X\n", type);
			SetForeground (Res.at_pixel);
			break;
	}
}
