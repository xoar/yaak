static char rcsid[] = "$Id: option_sw.c,v 1.7 1994/06/22 06:22:38 waite Exp $";

#include <stdio.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/panel.h>
#else
#include <suntool/sunview.h>
#include <suntool/panel.h>
#endif

#include "info.h"
#include "option.h"
#include "system.h"

#define ITEMNAMEWIDTH 20

static Frame popup = (Frame) NULL;
static Panel panel;
static Panel_item description;

static char *instructions[] = {
" Set the options and click \"Done\" when finished.",
"Click on an option name to see a description of the option."
};

static char *null_message = "                                              ";

static void
Done(item, event)
Panel_item item; Event *event;
{
	int i;
	Panel_item it;

	for (i = 0,
	     it = (Panel_item) panel_get (description, PANEL_NEXT_ITEM),
	     it = (Panel_item) panel_get (it, PANEL_NEXT_ITEM);
	     i != SEARCHINSENSITIVE;
	     i++,
	     it = (Panel_item) panel_get (it, PANEL_NEXT_ITEM),
	     it = (Panel_item) panel_get (it, PANEL_NEXT_ITEM))
		options[i].value = (char *) panel_get_value (it);
	options[SEARCHINSENSITIVE].value =
		(((int) panel_get_value (it) == 0) ? "yes" : "no");
	window_set (popup, WIN_SHOW, FALSE, 0);
}

static void
Describe(item, event)
Panel_item item; Event *event;
{
	char buf[STRING_SIZE];

	int index = (int) panel_get (item, PANEL_CLIENT_DATA);

	sprintf (buf, "%s: %s", options[index].name, options[index].desc); 
	panel_set (description, PANEL_LABEL_STRING, buf, 0);
}

static void
MakeOptionPopup(item, event)
Panel_item item; Event *event;
{
	int i;
	Rect *r;
	int left, top, width, height;
	char *cp, *name;

	/* create the new frame and contents */
	popup = window_create (0, FRAME,
			       FRAME_LABEL, "Options",
			       0);

	panel = window_create (popup, PANEL, 0);

	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_X, ATTR_COL(0),
				  PANEL_LABEL_Y, ATTR_ROW(0),
#ifdef XVIEW
				  PANEL_LABEL_STRING, "Done",
#else
				  PANEL_LABEL_IMAGE,
				  panel_button_image (panel, "Done", 6, 0),
#endif
				  PANEL_NOTIFY_PROC, Done,
				  0);
	
	(void) panel_create_item (panel, PANEL_MESSAGE,
				  PANEL_LABEL_STRING, instructions[0],
				  0);
	
	(void) panel_create_item (panel, PANEL_MESSAGE,
				  PANEL_LABEL_X, ATTR_COL(0),
				  PANEL_LABEL_Y, ATTR_ROW(1),
				  PANEL_LABEL_STRING, instructions[1],
				  0);
	
	description = panel_create_item (panel, PANEL_MESSAGE,
					 PANEL_LABEL_X, ATTR_COL(0),
					 PANEL_LABEL_Y, ATTR_ROW(2),
					 PANEL_LABEL_STRING, null_message,
					 0);
	
	/* build the option text items */
	for (i = 0, name = options[i].name; i != SEARCHINSENSITIVE;
	     i++, name = options[i].name) {
		(void) panel_create_item (panel, PANEL_BUTTON,
					  PANEL_LABEL_X, ATTR_COL(0),
					  PANEL_LABEL_Y, ATTR_ROW(3+i),
					  PANEL_LABEL_STRING, name,
					  PANEL_NOTIFY_PROC, Describe,
					  PANEL_CLIENT_DATA, (caddr_t) i,
					  0);
		(void) panel_create_item (panel, PANEL_TEXT,
					  PANEL_LABEL_X, ATTR_COL(ITEMNAMEWIDTH),
					  PANEL_LABEL_STRING, "",
					  PANEL_VALUE_DISPLAY_LENGTH, 40,
					  PANEL_VALUE, options[i].value,
					  0);
	}

	/* SEARCHINSENSITIVE */
	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_X, ATTR_COL(0),
				  PANEL_LABEL_Y, ATTR_ROW(3+i),
				  PANEL_LABEL_STRING, name,
				  PANEL_NOTIFY_PROC, Describe,
				  PANEL_CLIENT_DATA, (caddr_t) i,
				  0);
#ifdef XVIEW
	(void) panel_create_item (panel, PANEL_TOGGLE,
				  PANEL_LABEL_X, ATTR_COL(ITEMNAMEWIDTH),
				  PANEL_CHOOSE_ONE, TRUE,
				  PANEL_LABEL_STRING, "",
				  PANEL_CHOICE_STRINGS, "Yes", "No", 0,
				  PANEL_VALUE,
				  (strcmp (options[SEARCHINSENSITIVE].value,
					   "yes")
				   ? 1 : 0),
				  0);
#else
	(void) panel_create_item (panel, PANEL_CYCLE,
				  PANEL_LABEL_X, ATTR_COL(ITEMNAMEWIDTH),
				  PANEL_LABEL_STRING, "",
				  PANEL_CHOICE_STRINGS, "Yes", "No", 0,
				  PANEL_VALUE,
				  (strcmp (options[SEARCHINSENSITIVE].value,
					   "yes")
				   ? 1 : 0),
				  0);
#endif
		
	/* make everything fit nicely */
	window_fit (panel);
	window_fit (popup);

	/* center the window on the screen, p.33 Programmer's Guide */
	r = (Rect *) window_get (popup, WIN_SCREEN_RECT);
	width = (int) window_get (popup, WIN_WIDTH);
	height = (int) window_get (popup, WIN_HEIGHT);
	left = (r->r_width - width) / 2;
	top = (r->r_height - height) / 2;
	if (left < 0) left = 0;
	if (top < 0) top = 0;
	window_set (popup, WIN_X, left, WIN_Y, top, 0);
}

void
OptionButton(item, event)
Panel_item item; Event *event;
{
	/* build it if we haven't done so already */
	if (popup == (Frame) NULL)
		MakeOptionPopup (item, event);

	/* go for it */
	window_set (popup, WIN_SHOW, TRUE, 0);
}

void
OptionFinl()
{
	if (popup != (Frame) NULL) {
		window_set (popup, FRAME_NO_CONFIRM, TRUE, 0);
		window_destroy (popup);
	}
}

