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
/* $Id: DepLayout.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: DepLayout.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/DepLayout.c				*
 *									*
 *	CONTENTS:	Layout of drawn dependencies			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file implements the layout of drawn dependencies. It supports two
 * basic types of a dependency:
 *
 *                 --->                   --->
 * horizontal    /          and vertical |	  dependencies.
 *            --                          -----
 *
 * Note that horizontal dependencies are used only in production graphs.
 *
 * The vertical parts of the vertical dependencies are arranged in columns,
 * and three different algorithms are used to calculate the total number of
 * columns and the column for a given dependency:
 *   a - induced dependencies
 *   b - direct, arranged and partitioned dependencies
 *   c - visit-sequence lifetimes.
 */

#include "Misc.h"
#include <math.h>
#include <float.h>


/************************************************************************
 *		 	     Global Variables				*
 ************************************************************************/

/* The points that constitute the drawn dependency */
PRIVATE XPoint		points[10];
PRIVATE int		npoints;

/* Some global parameters, which are passed down via DepInitiate() */
PRIVATE Window		win;
PRIVATE Region		reg;
PRIVATE Position	select_x, select_y;
PRIVATE Boolean		visit_seq;
PRIVATE Position	dep_x, dep_y;
PRIVATE Dimension	dep_width, dep_height;


/************************************************************************
 *			       PointInLines				*
 ************************************************************************/

/* Decides membership of the point (x, y) in the lines described by the 
 * global array points[]. The line width used for this test is 
 * Res.select_width.
 */

PRIVATE Boolean PointInLines (x, y)
	Position x, y;
{
	int i;

      /* Loop over all line segments */
	for (i=0; i<npoints-1; i++)
	{
	      /* Calculate tangens, sine and cosine */
		int	xdiff = points[i+1].x - points[i].x;
		double	tn    = (xdiff == 0 ) ?
			        DBL_MAX :
				((double) points[i+1].y - points[i].y) / xdiff;
		double	l     = sqrt (1 + tn * tn);
		int	wsn2, wcs2;
		XPoint	p[4];

		if (xdiff > 0)
		{
			wsn2 = Res.select_width * tn / l / 2;
			wcs2 = Res.select_width * 1 / l / 2;
		}
		else
		{
			wsn2 = - Res.select_width * tn / l;
			wcs2 = - Res.select_width * 1 / l / 2;
		}



	      /* Construct the corresponding rectangle for this line segment */
		p[0].x = points[i  ].x - wsn2;	p[0].y = points[i  ].y + wcs2;
		p[1].x = points[i  ].x + wsn2;	p[1].y = points[i  ].y - wcs2;
		p[2].x = points[i+1].x - wsn2;	p[2].y = points[i+1].y + wcs2;
		p[3].x = points[i+1].x + wsn2;	p[3].y = points[i+1].y - wcs2;

		  
		/* Test membership of the given point in the rectangle */
		if (XPointInRegion (XPolygonRegion (p, 4, EvenOddRule), x, y)){
		  return (True);
		}
  	}

      /* None of the segments was containing the point */
	return (False);
}


/************************************************************************
 *			 	NumColumns				*
 ************************************************************************/

/* Calculates the number of dependency columns needed for a symbol S 
 * which has <length> visible (not hidden) attributes.
 * This is used for induced dependencies only.
 */

PRIVATE int NumColumns (length)
	int length;
{
	int h = length / 2;

	return ((length <= 0) ? 0
			      : (h * h + ((length & 1) ? h : 0)));
}


/************************************************************************
 *			       StartColumn				*
 ************************************************************************/

/* Calculates the starting column for all vertical dependencies with a 
 * vertical length <diff>. The corresponding symbol is assumed to have 
 * <length> visible (not hidden) attributes.
 * This is used for induced dependencies only.
 */

PRIVATE int StartColumn (diff, length)
	int diff;
	int length;
{
	return (  NumColumns (diff + 1)
		+ NumColumns (diff - 2)
		- NumColumns (diff + diff - 1 - length));
}


/************************************************************************
 *	 	     NormalDepWidth & InducedDepWidth			*
 ************************************************************************/

/* Compute the width in pixels needed for the vertical dependencies of a
 * symbol with <length> visible (not hidden) attributes. Since for induced
 * dependencies a different layout policy is used, an extra function is given.
 */

PUBLIC Dimension NormalDepWidth (length)
	int length;
{
	return ((Dimension) (Res.arrow_length + Res.dep_fase + 
			     length * Res.dep_width));
}


PUBLIC Dimension InducedDepWidth (length)
	int length;
{
	return ((Dimension) (Res.arrow_length + Res.dep_fase +
			     NumColumns (length) * Res.dep_width));
}


/************************************************************************
 *                              DrawArrow				*
 ************************************************************************/

/* Draws a horizontal arrow head, pointing at the pixel (<x>,<y>).
 * The direction is determined by the Boolean flag <right2>.
 */

PRIVATE void DrawArrow (x, y, right2)
	Position	x, y;
	Boolean		right2;
{
	XPoint	points[3];

      /* Compute the three polygon points */
	points[0].y = y - Res.arrow_width;
	points[0].x = (right2) ? (x-Res.arrow_height) : (x+Res.arrow_height);

	points[1].x = x;
	points[1].y = y;

	points[2].x = points[0].x;
	points[2].y = y + Res.arrow_width;

      /* Fill the polygon */
	XFillPolygon (dpy, win, gc, points, 3, Convex, CoordModeOrigin);
}


/************************************************************************
 * 				DoVertDep				*
 ************************************************************************/

/* Calculates the points of a vertical dependency.
 */

PRIVATE void DoVertDep (x1, y1, y2, right1, length1, no1, no2, dep)
	Position	x1, y1, y2;
	Boolean		right1;
	int		length1, no1, no2;
	DEPENDENCY	*dep;
{
	int	u, diff;
	int	v_vert	= (y2 > y1) ? Res.dep_fase : -Res.dep_fase;
        int	v_hor	= right1 ? Res.dep_fase : -Res.dep_fase;

	if (no2 > no1) 	diff = no2 - no1;
	else		diff = no1 - no2;
	if (diff == 0) diff = 1;

	if (visit_seq)
		u = Res.arrow_length + diff * Res.dep_width + Res.synt_indent;
	else if ((*dep & T_IND) && !(*dep & T_DIR))
		u = Res.arrow_length + 
		      Res.dep_width * (StartColumn(diff,length1)+no1%diff-1);
	else
		u = Res.arrow_length + no2 * Res.dep_width;

	if (!right1) u = -u;

	points[npoints  ].x = x1 + u;
	points[npoints++].y = y1;

	points[npoints  ].x = x1 + u + v_hor;
	points[npoints++].y = y1 + v_vert;

	points[npoints  ].x = x1 + u + v_hor;
	points[npoints++].y = y2 - v_vert;

	points[npoints  ].x = x1 + u;
	points[npoints++].y = y2;

	dep_width = (right1 ? (u+v_hor) : (-u-v_hor)) + 1 + Res.synt_indent;
}


/************************************************************************
 * 				 DoHorDep				*
 ************************************************************************/

/* Calculates the points of a horizontal dependency.
 */

PRIVATE void DoHorDep (x1, y1, synt1, down1, up1, x2, y2, right2)
	Position	x1, y1, x2, y2;
	Boolean		synt1, right2;
	int		down1, up1;
{
	double	xi1, xi2, xid;

	if (right2)
	{
		xi1 = x1 + Res.synt_indent;
		xi2 = x2 - Res.arrow_length;
		xid = xi2 - x1;
	}
	else
	{
		xi1 = x1 - Res.synt_indent;
		xi2 = x2 + Res.arrow_length;
		xid = x1 - xi2;
	}

	if (((!synt1 && right2) || (synt1 && !right2)) &&
	    ((y2>y1) ?
	     (((double) down1-AttrHeight/4) / Res.synt_indent <= (y2-y1) / xid):
	     (((double) up1  -AttrHeight/4) / Res.synt_indent <= (y1-y2) / xid))
	   )
	{
		points[npoints  ].x = xi1;
		points[npoints++].y = y1;
	}

	points[npoints  ].x = xi2;
	points[npoints++].y = y2;

	dep_width = (x2 > x1) ? (x2 - x1 + 1) : (x1 - x2 + 1);
}


/************************************************************************
 *			       DepInitiate				*
 ************************************************************************/

/* Initializes the private variables in this file.
 */

PUBLIC void DepInitiate (w, r, x, y, vs)
	Window		w;
	Region		r;
	Position	x, y;
	Boolean		vs;
{
	win	  = w;
	reg	  = r;
	select_x  = x;
	select_y  = y;
	visit_seq = vs;
}


/************************************************************************
 * 				  DoDep					*
 ************************************************************************/

/* Calculates the points of the given dependency and performs the desi-	
 * red action. This can be testing of point membership or dependency
 * drawing.
 */

PUBLIC Boolean DoDep (dep, x1, y1, no1, width1, synt1, 
			   x2, y2, no2, width2, synt2,
			   down1, up1, length1, lhs)
	DEPENDENCY	*dep;
	Position	x1, y1, x2, y2;
	Dimension	width1, width2;
	int		no1, no2, down1, up1, length1, synt1, synt2;
	Boolean		lhs;
{
	Position	start_x, target_x;
	Boolean		right1, right2;
	Boolean		induced = (*dep & T_IND) && !(*dep & T_DIR);

      /* Initialize the number of points */
	npoints = 0;

      /* Compute right1 and start_x */
	if (visit_seq)
	{
		right1 = True;
		start_x = x1 + width1 + synt1 * Res.synt_indent;
	}
	else
	{
		right1 = x2 > x1 || (x1 == x2 &&  induced && !lhs) ||
				    (x1 == x2 && !induced &&  lhs);
		if (right1)
		{
		    if (synt1)
		    {
			start_x = x1 + width1;
		    }
		    else
		    {
			start_x = x1 + width1 - Res.synt_indent;
		    }
		}
		else
		{
		    if (synt1) {
			start_x = x1 +Res.synt_indent-1;
		    }
		    else {
			start_x = x1;
		    }
		}
	}

      /* Compute right2 and target_x */
	if (visit_seq)
	{
		right2 = False;
		target_x = x1 + width1 + synt2 * Res.synt_indent;
	}
	else
	{
		right2 = (x2 > x1 || (x1 == x2 &&  induced &&  lhs) ||
				     (x1 == x2 && !induced && !lhs));
		if (right2)
		{	
		    if (synt2)
		    {
			target_x = x2+Res.synt_indent-1;
		    }
		    else
		    {
			target_x = x2;
		    }
		}
		else
		{
		    if (synt2)
		    {
			target_x = x2+width2;
		    }
		    else
		    {
			target_x = x2+width2 - Res.synt_indent;
		    }
		}
	}

      /* Add the first point */
	y1 = (y2 >= (y1+AttrHeight/4)) ? (y1+AttrHeight/4) : (y1-AttrHeight/4);
	points[npoints  ].x = start_x;
	points[npoints++].y = y1;

      /* Add the intermediate lines */
	if (x1 == x2)
	{
		DoVertDep (right1 ? ((int) (x1+width1)) : x1,
			   y1, y2, right1, length1, no1, no2, dep);
	}
	else
	{
		DoHorDep  (start_x, y1, synt1, down1,up1, target_x, y2, right2);
	}

      /* Add the last point */
	points[npoints  ].x = right2 ? (target_x - Res.arrow_height) : 
				       (target_x + Res.arrow_height);
	points[npoints++].y = y2;

      /* Determine surrounding rectangle of dependency */
	dep_x = MIN (start_x, target_x);
	if (x1 == x2 && !right1) dep_x -= dep_width;
	dep_y = MIN (points[0].y, points[npoints-1].y);
	dep_height = (y1 < y2) ? (y2 - y1 + 1) : (y1 - y2 + 1);

      /* Perform the desired action */
	if (select_x != 0)
		return (dep_x <= select_x && select_x <= (Position)(dep_x + dep_width) &&
			dep_y <= select_y && select_y <= (Position)(dep_y + dep_height) &&
			PointInLines (select_x, select_y));
	else
	{
		SetDepGCElems (*dep);
		if (XRectInRegion (reg, dep_x, dep_y, dep_width, dep_height) !=
					RectangleOut)
			XDrawLines (dpy, win, gc, points, npoints, 
							CoordModeOrigin);
		DrawArrow (target_x, y2, right2);
		return (False);
	}
}
