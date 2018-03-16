static char rcsid[] = "$Id: complain_sw.c,v 1.9 1993/12/07 19:48:02 kadhim Exp $";

#include <stdio.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/textsw.h>
#else
#include <suntool/sunview.h>
#include <suntool/panel.h>
#include <suntool/textsw.h>
#endif

#ifdef XVIEW
#define MY_PANEL_LABEL(x,y) PANEL_LABEL_STRING, (x)
#else
#define MY_PANEL_LABEL(x,y) PANEL_LABEL_IMAGE, panel_button_image(panel, (x), (y), 0)
#endif

#include "info.h"
#include "file.h"

static Frame popup = (Frame) NULL;
static Panel panel;
static Textsw text;

static char *instructions[] = {
" Type your complaint into the text window below. When done, click \"Send\"",
" to send the message or \"Cancel\" to return to browsing without sending."
};

static void
AbortComplaint(item, event)
Panel_item item; Event *event;
{
	textsw_reset (text, 0, 0);
	window_set (popup, WIN_SHOW, FALSE, 0);
}

static void
SendComplaint(item, event)
Panel_item item; Event *event;
{
	char cmdbuf[STRING_SIZE], errbuf[BUFSIZ];
	char *filename;
	
	filename = make_temp_filename ("complaint");
	if (textsw_store_file (text, filename, 0, 0)) {
		display_error("Can't store complaint, sorry.\n");
		return;
	}
	(void) sprintf (cmdbuf, "%s %s <%s", MAIL, MAINTAINER, filename);
	if (system (cmdbuf) != 0) {
		(void)sprintf(errbuf, "Error running \"%s\".\n", cmdbuf);
		display_error(errbuf);
	} else
	  (void)deletefile(filename);
	textsw_reset (text, 0, 0);
	window_set (popup, WIN_SHOW, FALSE, 0);
}

static void
MakeComplainPopup(item, event)
Panel_item item; Event *event;
{
	Rect *r;
	int left, top, width, height;

	/* create the new frame and contents */
	popup = window_create (0, FRAME,
			       FRAME_LABEL, "Complainer",
			       0);

	panel = window_create (popup, PANEL, 0);

	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_X, ATTR_COL(17),
				  MY_PANEL_LABEL("Send", 6),
				  PANEL_NOTIFY_PROC, SendComplaint,
				  0);
	
	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_X, ATTR_COL(48),
				  MY_PANEL_LABEL("Cancel", 8),
				  PANEL_NOTIFY_PROC, AbortComplaint,
				  0);
	
	(void) panel_create_item (panel, PANEL_MESSAGE,
				  PANEL_LABEL_X, ATTR_COL(0),
				  PANEL_LABEL_Y, ATTR_ROW(1),
				  PANEL_LABEL_STRING, instructions[0],
				  0);

	(void) panel_create_item (panel, PANEL_MESSAGE,
				  PANEL_LABEL_X, ATTR_COL(0),
				  PANEL_LABEL_Y, ATTR_ROW(2),
				  PANEL_LABEL_STRING, instructions[1],
				  0);
	
	window_fit_height (panel);

	text = window_create (popup, TEXTSW,
			      WIN_X, 0,
			      WIN_ROWS, 10,
			      TEXTSW_STORE_CHANGES_FILE, FALSE,
			      0);
	window_set (text, TEXTSW_INSERTION_POINT, TEXTSW_INFINITY, 0);

#ifdef XVIEW
	window_fit (popup);
#else
	window_fit_height (popup);
#endif

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
ComplainButton(item, event)
Panel_item item; Event *event;
{
	/* build it if we haven't done so already */
	if (popup == (Frame) NULL)
		MakeComplainPopup (item, event);

	/* go for it */
	window_set (popup, WIN_SHOW, TRUE, 0);
}

void
ComplainFinl()
{
	if (popup != (Frame) NULL) {
		window_set (popup, FRAME_NO_CONFIRM, TRUE, 0);
		window_destroy (popup);
	}
}
