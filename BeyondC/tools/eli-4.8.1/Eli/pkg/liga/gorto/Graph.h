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
/* $Id: Graph.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Graph/Graph.h					*
 *									*
 *	CONTENTS:	Public header file of graph widget		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* See the file Graph/Graph.c for a description of the functionality
 * provided by the graph widget.
 */

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 height		     Height		Dimension	0
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 sensitive	     Sensitive		Boolean		True
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0
 expose              Callback		Callback     	NULL
 resize        	     Callback		Callback     	NULL
 select        	     Callback		Callback     	NULL
 did		     Did		Integer		0

*/


/* special resource names */
#define XtNexpose	"expose"
#ifndef XtNresize
#define XtNresize	"resize"
#endif
#define XtNselect	"select"
#define XtNdid		"did"

/* special recources classes */
#define XtCDid		"Did"

/* specific GraphWidget class and instance datatypes */
typedef struct _GraphClassRec*	GraphWidgetClass;
typedef struct _GraphRec*	GraphWidget;


/* the class constant */
extern WidgetClass graphWidgetClass;


/* did resource value of graph widget that popped up the last menu */
extern int DidOfGraphMenu;

/* parameters of the select action */
#define DO_FOLLOW		0
#define DO_FOLLOW_AND_CLOSE	1
#define DO_FOLLOW_MARKED	2
#define DO_REMOVE		3
#define DO_HIDE			4
#define DO_UNHIDE		5
#define DO_MOVE			6
#define DO_SPLIT_PARTITION	7
#define DO_APPEND_PARTITION	8

/* possible action types */
#define DEP_ACTION		0
#define REMOVE_ACTION		1
#define ATTR_ACTION		2
#define NUM_ACTION_TYPES	3

/* type of call_data for XtNselect callback */
typedef struct {
	Position	x, y;
	short		action[NUM_ACTION_TYPES];
} GraphReturnStruct;

/* convenience functions */
extern Pixel GraphBackground( /* Widget w */ );
