static char rcsid[] = "$Id: text_sw.c,v 1.12 1998/02/11 16:43:33 waite Exp $";

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/textsw.h>
#include <xview/font.h>
#include <xview/defaults.h>
#else
#include <suntool/sunview.h>
#include <suntool/textsw.h>
#endif

#include "info.h"
#include "panel_sw.h"

extern int nodetop, nodebot;
extern char *info_file;
extern void clean_up();

static Textsw node = (Textsw) NULL;

/**/
static void
GetLine(win, buf, hit)
Textsw win; char *buf; int *hit;
/* Get the selected text line, the one before, and the one after
 *    On entry-
 *       win=window from which to extract the information
 *       buf points to the area that will receive the text
 *    On exit-
 *       buf contains the text
 *       buf[hit] is the character actually selected
 **/
{
	Textsw_index picked, limit, low, high, ignore;

	picked = (Textsw_index)window_get(win, TEXTSW_INSERTION_POINT);
	limit = (Textsw_index)window_get(win, TEXTSW_LENGTH);

	ignore = picked;
	if (textsw_find_bytes(win, &ignore, &low, "\n", 1, 1) == -1
			|| ignore > picked)
		low = 0;
	else {
		ignore--;
		if (textsw_find_bytes(win, &ignore, &low, "\n", 1, 1) == -1
				|| ignore > picked)
			low = 0;
	}

	high = picked;
	if (textsw_find_bytes(win, &high, &ignore, "\n", 1, 0) == -1
			|| ignore < picked)
		high = limit;
	else {
		high++;
		if (textsw_find_bytes(win, &high, &ignore, "\n", 1, 0) == -1
				|| ignore < picked)
			high = limit;
	}

	if (low == high) *hit = 0;
	else {
		(void)window_get(win, TEXTSW_CONTENTS, low, buf, high-low);
		*hit = picked-low-1;
	}
	buf[high-low] = '\0';
}

/**/
static Notify_value
click_interposer(win, event, arg, type)
Textsw win; Event *event; Notify_arg arg; Notify_event_type type;
/* Recognize a selection
 *    On entry-
 *       win=window in which the event occurred
 *       event=event that occurred
 *       arg=
 *       type=
 **/
{
	char buf[BUFSIZ];
	int picked;
	Notify_value value;

#ifdef XVIEW
	/* Something goes wrong inside XView with the menu handling, so
	   we'll just ignore the right button for now to prevent coredump. */
	if (event_id(event) == MS_RIGHT)
		return NOTIFY_DONE;
#endif

#ifdef XVIEW
	value = notify_next_event_func(win, (Notify_event) event, arg, type);
#else
	value = notify_next_event_func(win, event, arg, type);
#endif

	if (event_id(event) == MS_LEFT && event_is_up(event)) {
		GetLine(win, buf, &picked);
		if (NodeNote(buf, picked)) return value;
		if (NodeMenu(buf, picked)) return value;
	}
	if (event_is_ascii(event)) {
		if (event_is_up(event)) {
			return value;
		} else {
			switch (event->ie_code) {
			case 'b': BackButton(); return value;
			case 'd': DirButton();  return value;
			case 'n': NextButton(); return value;
			case 'p': PrevButton(); return value;
			case 'q': FrameFinl();  return value;
			case 'u': UpButton();   return value;
			default:
#ifdef XVIEW
				xv_set(win, WIN_ALARM);
#endif
				return value;
			}
		}
	}
	return value;
}

/***/
void
NodeInit(frame)
Frame frame;
/* Create a subwindow to display the text
 *    On entry-
 *       frame=parent of the text display
 ***/
{
#ifdef XVIEW
	/* Get the font from the resource database */
	char *name;
	Xv_Font font;

	name = defaults_get_string("textsw.font","Textsw.Font", "fixed"),
	font = xv_find(frame, FONT,
		       FONT_NAME,      name,
		       NULL);
#endif

	node = window_create(frame, TEXTSW,
			     WIN_X, 0,
			     WIN_ROWS, 40,
			     TEXTSW_MEMORY_MAXIMUM, 90000,
			     TEXTSW_MENU, NULL,
			     TEXTSW_INSERT_MAKES_VISIBLE, TEXTSW_NEVER,
			     TEXTSW_AUTO_SCROLL_BY, 0,
			     TEXTSW_LOWER_CONTEXT, -1,
#ifdef XVIEW
			     XV_FONT, font,
#endif
			     0);

#ifdef XVIEW
	(void)notify_interpose_event_func(xv_get (node, OPENWIN_NTH_VIEW, 0),
					  click_interposer, NOTIFY_SAFE);
#else
	(void)notify_interpose_event_func(node, click_interposer, NOTIFY_SAFE);
#endif
}

/***/
void
NodeClear()
/* Delete the current node's text
 ***/
{
	textsw_reset(node, 0, 0);
	window_set(node, TEXTSW_INSERTION_POINT, 0, 0);
}

/***/
void
NodeDisplay(buf, len)
char *buf; int len;
/* Display text for the current node
 *    On entry-
 *       buf[0..len-1]=text to be displayed
 ***/
{
	NodeClear();
	textsw_insert(node, buf, len);
	window_set(node, TEXTSW_INSERTION_POINT, 0, 0);
	textsw_possibly_normalize(node, 0);
}

/***/
void
display_page()
/* Display a node with the appropriate buttons
 *    On entry-
 *       info_file[datatop..nodetop-1]=mode information
 *       info_file[nodetop..nodebot-1]=text
 ***/
{
	extern char *info_file;
	extern int nodebot, nodetop, datatop;

	ControlButton(datatop);
	EchoClear();
	NodeDisplay(&info_file[nodetop], nodebot-nodetop);
}

/***/
boolean
NodeNote(str, picked)
char *str; int picked;
/* Follow a possible cross-reference selected from the current node
 *    On entry-
 *       str=a text segment guaranteed to contain the entire reference
 *          (if one is present)
 *       str[picked]=character actually marked by the selection
 *    If a reference is present, and the node is accessible, then on exit-
 *       NodeNote=true
 *       The referenced node has been displayed
 *    Else if a reference is present then on exit-
 *       NodeNote=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeNote=false
 ***/
{
	char buf[BUFSIZ], *p, *q;

	p = str + picked;
	while (*p != '*' && *p != '.' && p > str) p--;
	if (strnicmp(p, "*note", 5) != 0) return(false);

	p += 5;
	p += strspn(p, " \t\n");
	if ((q = strpbrk(p, ":")) == NULL) return(false);

	(void)strncpy(buf, p, q-p);
	buf[q-p] = '\0';
	if (q[1] == ':') p = buf;
	else p = q + strspn(q, ": \t\n");

	if (!get_node((char *)NULL, p, 0)) return(false);

	display_node();
	return(true);
}

/***/
boolean
NodeMenu(str, picked)
char *str; int picked;
/* Follow a possible menu item selected from the current node
 *    On entry-
 *       str=a text segment guaranteed to contain the entire menu item
 *          (if one is present)
 *       str[picked]=character actually marked by the selection
 *    If a menu item is present, and the node is accessible, then on exit-
 *       NodeMenu=true
 *       The referenced node has been displayed
 *    Else if a menu item is present then on exit-
 *       NodeMenu=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeMenu=false
 ***/
{
	char buf[BUFSIZ], *p, *q;

	p = str + picked;
	while (*p != '\n' && p > str) p--;
	p += strspn(p, " \t\n");
	if (*p++ != '*') return(false);

	p += strspn(p, " \t");
	if ((q = strpbrk(p, ":")) == NULL) return(false);

	(void)strncpy(buf, p, q-p);
	buf[q-p] = '\0';
	if (q[1] == ':') p = buf;
	else p = q + strspn(q, ": ");

	if (!get_node((char *)NULL, p, 0)) return(false);

	display_node();
	return(true);
}

/* Search for a string in the current node
 *    On entry-
 *       str=a string to be searched for
 *    If the string is present in the node starting at the position of the
 * 	 carat, then on exit-
 *          The line with the string is at the top of the page.
 *	    The carat points to the end of the string.
 */

void
SearchNode (str)
char *str;
{
	size_t pos = 0;
	int start = nodetop + (int) window_get (node, TEXTSW_INSERTION_POINT);

	set_search_constraints (info_file + start, nodebot - start + 1);
	if (!search_forward(str,&pos)) {
		char buf [BUFSIZ];

		sprintf (buf, "String '%s' not found.", str);
		display_error (buf);
	} else {
		size_t tpos = start + pos - nodetop;

		textsw_possibly_normalize (node, tpos);
		window_set (node, TEXTSW_INSERTION_POINT, tpos + strlen(str),
			    0);
		textsw_set_selection (node, tpos, tpos + strlen (str), 1);
	}
}


