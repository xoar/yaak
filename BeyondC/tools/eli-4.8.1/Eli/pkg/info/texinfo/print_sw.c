static char rcsid[] = "$Id: print_sw.c,v 1.4 1991/07/04 17:18:32 waite Exp $";

#include <stdio.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/notice.h>
#else
#include <suntool/sunview.h>
#include <suntool/panel.h>
#endif

#include "info.h"
#include "file.h"
#include "node.h"
#include "option.h"

#ifdef XVIEW

int
confirm (message)
char *message;
{
	extern Panel control_panel;

	int answer;
	answer = notice_prompt (control_panel, NULL,
			       NOTICE_MESSAGE_STRINGS, message, NULL,
			       NOTICE_BUTTON_YES, "Ok",
			       NOTICE_BUTTON_NO, "Cancel",
			       NULL);
	return (answer == NOTICE_YES ? 1 : 0);
}

#else

static void
OkConfirm(item, event)
Panel_item item; Event *event;
{
	window_return (1);
}

static void
CancelConfirm(item, event)
Panel_item item; Event *event;
{
	window_return (0);
}

int
confirm (message)
char *message;
{
	int answer;
	Frame popup;
	Panel panel;
	Rect *r;
	int left, top, width, height;

	popup = window_create (0, FRAME, FRAME_SHOW_LABEL, FALSE, 0);
	panel = window_create (popup, PANEL, 0);
	(void) panel_create_item (panel, PANEL_MESSAGE,
				  PANEL_LABEL_STRING, message,
				  0);
	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_IMAGE,
				  panel_button_image (panel, "Ok", 4, 0),
				  PANEL_NOTIFY_PROC, OkConfirm,
				  0);
	(void) panel_create_item (panel, PANEL_BUTTON,
				  PANEL_LABEL_IMAGE,
				  panel_button_image (panel, "Cancel", 8, 0),
				  PANEL_NOTIFY_PROC, CancelConfirm,
				  0);
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

	answer = (int) window_loop (popup);
	window_set (popup, FRAME_NO_CONFIRM, TRUE, 0);
	window_destroy (popup);
	return answer;
}

#endif

void
PrintNodeButton(item, event)
Panel_item item; Event *event;
{
	if (confirm("Really print current node ?") && print_current_node()) {
		char errbuf[BUFSIZ];
		(void)sprintf(errbuf,
			"The current node has been sent to \"%s\".\n", 
			options[PRINTER].value);
		display_error(errbuf);
	}
}

void
PrintManualButton(item, event)
Panel_item item; Event *event;
{
	char buf[STRING_SIZE];
	extern char manualname[];
	extern struct stat manualinfo;

	(void)sprintf(buf, "Really print the current manual (%dk) ?",
			manualinfo.st_size / 1024);
	if (confirm(buf) && printfile(manualname)) {
		char errbuf[BUFSIZ];
		(void)sprintf(errbuf,
			"The manual has been sent to \"%s\".\n",
			options[PRINTER].value);
		display_error(errbuf);
	}
}
