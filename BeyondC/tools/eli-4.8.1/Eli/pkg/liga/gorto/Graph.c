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
/* $Id: Graph.c,v 4.2 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Graph.c,v 4.2 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Graph/Graph.c					*
 *									*
 *	CONTENTS:	Implementation of the Graph-Widget.		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* The graph widget implemented in this file is used as a drawing area
 * for dependency graphs and visit-sequences. There is no private header
 * file GraphP.h, since the graph widget is not intended to be subclassed.
 * The contents of GraphP.h are merged into this file.
 *
 * The graph widget supplies callbacks for exposure, resize and 
 * key or button press events. The action procedure for key or button press
 * events accepts parameters, which in turn are passed to the callback
 * procedures registered with XtNselect (via the call_data pointer).
 * There is also a special menu-popup action procedure provided.
 *
 * After creation time and processing of XtSetValues calls, the graph widget
 * remembers the current width and height to be the preferred width and 
 * height. This allows a reasonable response to QueryGeometry calls from
 * the parent.
 *
 * A special resource XtNdid is provided by the graph widget to allow
 * the registration of a single int value with each graph widget instance.
 * The utility value DidOfGraphMenu is updated by each call to menu-popup,
 * so the application has a way to determine which instance of the graph
 * widget has popped up the last menu.
 *
 * There is also a special utility function GraphBackground, which can be
 * used by the application to determine the current background pixel of
 * a graph widget instance.
 */

#include <stdio.h>

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include "Graph.h"		/* Graph public header file */
#include <X11/CoreP.h>		/* superclass private header file */


/************************************************************************
 *			     Type definitions				*
 ************************************************************************/

typedef struct {
	int empty;
} GraphClassPart;

typedef struct _GraphClassRec {
	CoreClassPart	core_class;
	GraphClassPart	graph_class;
} GraphClassRec;

typedef struct {
      /* resources */
	XtCallbackList	expose_callback;
	XtCallbackList	resize_callback;
	XtCallbackList	select_callback;
	int		did;

      /* private state */
	Position	preferred_width;
	Position	preferred_height;
} GraphPart;

typedef struct _GraphRec {
	CorePart	core;
	GraphPart	graph;
} GraphRec;


/************************************************************************
 *			   Resource definitions				*
 ************************************************************************/

static XtResource graph_resources[] = {
#define offset(field) XtOffset(GraphWidget, graph.field)
	{ XtNexpose, XtCCallback, XtRCallback, sizeof(XtCallbackList),
	  offset(expose_callback), XtRCallback, NULL },
	{ XtNresize, XtCCallback, XtRCallback, sizeof(XtCallbackList),
	  offset(resize_callback), XtRCallback, NULL },
	{ XtNselect, XtCCallback, XtRCallback, sizeof(XtCallbackList),
	  offset(select_callback), XtRCallback, NULL },
	{ XtNdid, XtCDid, XtRInt, sizeof(int),
	  offset(did), XtRImmediate, 0 },
#undef offset
};


/************************************************************************
 *			   Function definitions				*
 ************************************************************************/

static void Initialize(), Realize(), Resize(), Redisplay();
static Boolean SetValues();
static XtGeometryResult QueryGeometry();

static void SelectAction();


/************************************************************************
 *			       Translations				*
 ************************************************************************/

static XtActionsRec actions[] =
{
	{"select",	SelectAction},
};

static char translations[] =
"<Btn3Down>:	menu-popup(mainMenu) \n\
<BtnDown>:	select(FOLLOW) \n\
";

/* accepted parameters of the select action */
typedef struct { String name; unsigned int type; } Action;
static Action ActionNames[] = {
	{"FOLLOW",		DEP_ACTION},
	{"FOLLOW-AND-CLOSE",	DEP_ACTION},
	{"FOLLOW-MARKED",	DEP_ACTION},
	{"REMOVE",		REMOVE_ACTION},
	{"HIDE",		ATTR_ACTION},
	{"UNHIDE",		ATTR_ACTION},
	{"MOVE",		ATTR_ACTION},
	{"SPLIT-PARTITION",	ATTR_ACTION},
	{"APPEND-PARTITION",	ATTR_ACTION},
};


/************************************************************************
 *		        Graph Widget Class Record			*
 ************************************************************************/

GraphClassRec graphClassRec = {
  { /* core fields */
    /* superclass		*/	(WidgetClass) &widgetClassRec,
    /* class_name		*/	"Graph",
    /* widget_size		*/	sizeof(GraphRec),
    /* class_initialize		*/	NULL,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	actions,
    /* num_actions		*/	XtNumber(actions),
    /* resources		*/	graph_resources,
    /* num_resources		*/	XtNumber(graph_resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	NULL,
    /* resize			*/	Resize,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	translations,
    /* query_geometry		*/	QueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
  },
  { /* graph fields */
    /* empty			*/	0
  }
};

/* definition of graphWidgetClass */
WidgetClass graphWidgetClass = (WidgetClass) & graphClassRec;

/* definition of did utility value */
int DidOfGraphMenu = 0;


/************************************************************************
 *			 	Initialize				*
 ************************************************************************/

/* Initialization of a graph widget instance. The current width and height
 * are remembered to be the preferred width and height.
 */

/*ARGSUSED*/
static void Initialize (request, new)
	Widget	request, new;
{
	GraphWidget gw = (GraphWidget) new;

      /* Remember the preferred width and height */
	gw->graph.preferred_width  = request->core.width;
	gw->graph.preferred_height = request->core.height;
}


/************************************************************************
 *			 	 Realize				*
 ************************************************************************/

/* Realization of a graph widget instance. We have to register a grab
 * with our window in order to make the action menu-popup useful.
 */

/*ARGSUSED*/
static void Realize (w, mask, attrs)
	Widget			w;
	Mask			*mask;
	XSetWindowAttributes	*attrs;
{
      /* Call superclass realize proc */
	(*((WidgetClass) &widgetClassRec)->core_class.realize) (w, mask, attrs);

      /* Register a grab for menu-popup */
	XGrabButton (XtDisplay (w), AnyButton, AnyModifier, XtWindow (w),
			TRUE, ButtonPressMask|ButtonReleaseMask,
			GrabModeAsync, GrabModeAsync, None, None);
}


/************************************************************************
 *				  Resize				*
 ************************************************************************/

/* Resize of a graph widget instance. Simply call the callbacks registered
 * with XtNresize.
 */

/*ARGSUSED*/
static void Resize (w)
	Widget w;
{
	XtCallCallbacks (w, XtNresize, (caddr_t) NULL);
}


/************************************************************************
 *				Redisplay				*
 ************************************************************************/

/* Redisplay of a graph widget instance. Simply call the callbacks registered
 * with XtNexpose.
 */

/*ARGSUSED*/
static void Redisplay (w, event, region)
	Widget	w;
	XEvent	*event;
	Region	region;
{
	XtCallCallbacks (w, XtNexpose, (caddr_t) region);
}


/************************************************************************
 *				SetValues				*
 ************************************************************************/

/* XtSetValues to a graph widget instance. Remember the new width and height
 * to be the preferred width and height.
 */

/*ARGSUSED*/
static Boolean SetValues (current, request, new)
	Widget current, request, new;
{
	GraphWidget new_gw = (GraphWidget) new;

      /* Remember new preferred width and height */
	new_gw->graph.preferred_width  = new->core.width;
	new_gw->graph.preferred_height = new->core.height;

      /* Return False, no redisplay is necessary from our point of view */
	return (False);
}


/************************************************************************
 *			      QueryGeometry				*
 ************************************************************************/

/* QueryGeometry call from the parent. Request our preferred 
 * width and height.
 */

/*ARGSUSED*/
static XtGeometryResult QueryGeometry (w, intended, preferred)
	Widget			w;
	XtWidgetGeometry	*intended, *preferred;
{
	GraphWidget gw = (GraphWidget) w;

	preferred->request_mode = CWWidth | CWHeight;
	preferred->width	= gw->graph.preferred_width;
	preferred->height	= gw->graph.preferred_height;

	if (((intended->request_mode & (CWWidth | CWHeight)) 
				    == (CWWidth | CWHeight)) &&
	    intended->width  == preferred->width &&
	    intended->height == preferred->height)
		return (XtGeometryYes);
	else if (preferred->width  == w->core.width &&
		 preferred->height == w->core.height)
		return (XtGeometryNo);
	else
		return (XtGeometryAlmost);
}


/************************************************************************
 *			       SelectAction				*
 ************************************************************************/

/* Call of the action procedure select. Build the call_data of type
 * GraphReturnStruct and call the callbacks registered with XtNselect.
 * This also performs a strict parameter checking.
 */

/*ARGSUSED*/
static void SelectAction (w, event, params, num_params)
	Widget		w;
	XEvent		*event;
	String		*params;
	Cardinal	*num_params;
{
static char event_warn[]  = "GraphWidget: wrong event type in select()";
static char double_warn[] = "GraphWidget: parameter '%s' ignored in select()";
static char unknown_warn[]= "GraphWidget: unknown parameter '%s' in select()";

	int			i, j;
	GraphReturnStruct 	call;
	char			warn[100];

      /* Initialize the <call> return structure */
	call.x = 0;
	call.y = 0;
	for (i=0; i<NUM_ACTION_TYPES; i++) call.action[i] = -1;

      /* Try to determine the x and y position in the given event structure */
	switch (event->type)
	{
		case KeyPress:		/* Key press and release events */
		case KeyRelease:
			call.x = (Position) ((XKeyEvent *) event) -> x;
			call.y = (Position) ((XKeyEvent *) event) -> y;
			break;

		case ButtonPress:	/* Button press and release events */
		case ButtonRelease:
			call.x = (Position) ((XButtonEvent *) event) -> x;
			call.y = (Position) ((XButtonEvent *) event) -> y;
			break;

		case MotionNotify:	/* Pointer motion notify events */
			call.x = (Position) ((XMotionEvent *) event) -> x;
			call.y = (Position) ((XMotionEvent *) event) -> y;
			break;

		case EnterNotify:	/* Window enter and leave events */
		case LeaveNotify:
			call.x = (Position) ((XCrossingEvent *) event) -> x;
			call.y = (Position) ((XCrossingEvent *) event) -> y;
			break;

		default:		/* Event has no position */
			call.x = (Position) 0;
			call.y = (Position) 0;
			XtWarning (event_warn);
	}

      /* Fill the action array of <call> from the params */
	for (i=0; i<*num_params; i++)
	{
		j = 0;
		while (j < XtNumber(ActionNames))
		{
			if (strcmp (params[i], ActionNames[j].name) == 0)
			{
				if (call.action[ActionNames[j].type] != -1)
				{
					sprintf (warn, double_warn, params[i]);
					XtWarning (warn);
				}
				else
					call.action[ActionNames[j].type] = j;
				break;
			}
			j ++;
		}
		if (j >= XtNumber (ActionNames))
		{
			(void) sprintf (warn, unknown_warn, params[i]);
			XtWarning (warn);
		}
	}

      /* Call the callbacks */
	XtCallCallbacks (w, XtNselect, (caddr_t) &call);
}


/************************************************************************
 *			     GraphBackground				*
 ************************************************************************/

/* Utility function used to determine the current background pixel of a
 * graph widget instance. Returns the requested pixel value.
 */

Pixel GraphBackground (w)
	Widget w;
{
	return (w->core.background_pixel);
}
