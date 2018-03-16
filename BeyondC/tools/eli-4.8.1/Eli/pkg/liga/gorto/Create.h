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
/* $Id: Create.h,v 4.1 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Misc/Create.h					*
 *									*
 *	CONTENTS:	Makros useful for Widget Creation		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#define CreateBox(name,father) \
	XtCreateManagedWidget(name,boxWidgetClass,father,args,n)

#define CreateCommand(command,name,father,callback,closure) \
	{ \
		command = XtCreateManagedWidget (name, commandWidgetClass, \
					father, args, n); \
		XtAddCallback (command,XtNcallback,callback,(caddr_t)closure); \
	}

#define CreateDialog(name,father) \
	XtCreateManagedWidget(name,dialogWidgetClass,father,args,n)

#define CreateForm(name,father) \
	XtCreateManagedWidget(name,formWidgetClass,father,args,n)

#define CreateToggle(toggle,name,father,callback,closure) \
	{ \
		toggle = XtCreateManagedWidget (name, toggleWidgetClass, \
					father, args, n); \
		XtAddCallback (toggle,XtNcallback,callback,(caddr_t)closure); \
	}

#define CreateMItem(item,name,father,callback,closure) \
	{ \
		item = XtCreateManagedWidget(name,smeBSBObjectClass, \
						father,args,n); \
		XtAddCallback (item,XtNcallback,callback,(caddr_t) closure); \
	}

#define CreateMLine(line,name,father) \
	line = XtCreateManagedWidget(name,smeLineObjectClass,father,args,n)

#define CreateView(name,father) \
	XtCreateManagedWidget(name,viewportWidgetClass,father,args,n)

#define CreateList(name,father) \
	XtCreateManagedWidget(name,listWidgetClass,father,args,n)

#define CreateMButton(name,father) \
	XtCreateManagedWidget(name,menuButtonWidgetClass,father,args,n)

#define CreateMenu(name,father) \
	XtCreatePopupShell(name,simpleMenuWidgetClass,father,args,n)

#define CreateLabel(name,father) \
	XtCreateManagedWidget(name,labelWidgetClass,father,args,n)

#define CreatePaned(name,father) \
	XtCreateManagedWidget(name,panedWidgetClass,father,args,n)

#define CreateGraph(graph,name,father,expose,resize,select,closure) \
	{ \
		graph = XtCreateManagedWidget (name, graphWidgetClass, \
					father, args, n); \
		XtAddCallback (graph, XtNexpose, expose, (caddr_t) closure); \
		XtAddCallback (graph, XtNresize, resize, (caddr_t) closure); \
		XtAddCallback (graph, XtNselect, select, (caddr_t) closure); \
	}
