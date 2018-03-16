static char rcsid[] = "$Id: panel_sw.c,v 1.9 1992/05/03 16:24:26 tony Exp $";

#include <stdio.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/panel.h>
#else
#include <suntool/sunview.h>
#include <suntool/panel.h>
#endif

#ifdef XVIEW
#define MY_PANEL_LABEL(x,y) PANEL_LABEL_STRING, (x)
#else
#define MY_PANEL_LABEL(x,y) PANEL_LABEL_IMAGE, panel_button_image(control_panel, (x), (y), 0)
#endif

#ifdef XVIEW
#define ACTIVATE_ITEM(i) panel_set (i, PANEL_INACTIVE, FALSE, 0)
#else
#define ACTIVATE_ITEM(i) panel_set (i, PANEL_SHOW_ITEM, TRUE, 0)
#endif

#ifdef XVIEW
#define DEACTIVATE_ITEM(i) panel_set (i, PANEL_INACTIVE, TRUE, 0)
#else
#define DEACTIVATE_ITEM(i) panel_set (i, PANEL_SHOW_ITEM, FALSE, 0)
#endif

#include "info.h"
#include "node.h"
#include "complain_sw.h"
#include "option_sw.h"
#include "print_sw.h"

Panel control_panel;
static Panel_item echo, next, prev, goup, input, edit, exec, undo, pman;
static Menu eg_files;
static char next_node_name[NODENAME_LEN];
static char prev_node_name[NODENAME_LEN];
static char up_node_name[NODENAME_LEN];

char manualname[FILENAME_LEN];
struct stat manualinfo;

extern void FrameFinl(), SearchNode ();
extern void set_up_edit(), background(), display_page(), ComplainButton();
extern COMP_ENTRY *completion_list;

void
display_node()
{
	char buf[STRING_SIZE];
	extern Frame frame;
	extern char *program_name;
	extern char current_info_file[], current_info_node[];

	display_page ();
	sprintf (buf, "%s: (%s)%s", program_name, current_info_file,
		 current_info_node );
	window_set (frame, FRAME_LABEL, buf, 0);
}

void
DirButton(item, event)
Panel_item item; Event *event;
{
	if (get_node((char *)NULL, "(dir)Top", 0)) display_node();
}

void
NextButton(item, event)
Panel_item item; Event *event;
{
	if (get_node((char *)NULL, next_node_name, 0)) display_node();
}

void
PrevButton(item, event)
Panel_item item; Event *event;
{
	if (get_node((char *)NULL, prev_node_name, 0)) display_node();
}

void
UpButton(item, event)
Panel_item item; Event *event;
{
	if (get_node((char *)NULL, up_node_name, 0)) display_node();
}

void
BackButton(item, event)
Panel_item item; Event *event;
{
	if (last_node()) display_node();
}

void
GotoButton(item, event)
Panel_item item; Event *event;
{
	char *node = (char *)panel_get (input, PANEL_VALUE);

	if (get_node ((char *)NULL, node, 0)) display_node ();
}

void
SearchButton(item, event)
Panel_item item; Event *event;
{
	char *str = (char *)panel_get (input, PANEL_VALUE);

	SearchNode (str);
}

static void
StartEdit(file)
char *file;
{
	boolean bg;
	char buf[BUFSIZ], buf1[BUFSIZ], *bp;

	set_up_edit(&bg, buf, file);
	if (!bg) {
#ifdef XVIEW
		sprintf(buf1, "xterm -e %s", buf);
#else
		sprintf(buf1, "shelltool %s", buf);
#endif
		bp = buf1;
	} else bp = buf;
	background(bp, (char *)NULL);
}

#ifdef XVIEW
static void
EditFile(menu, item)
Menu menu;
Menu_item item;
{
	StartEdit (xv_get (item, MENU_STRING));
}
#endif

static void
EditMenu(item, event)
Panel_item item; Event *event;
{
	char *file;

	if (event_id(event) == MS_RIGHT && event_is_down(event)) {
#ifdef XVIEW
		menu_show (eg_files,control_panel,event,0);
#else
		if ((file = (char *)menu_show(eg_files,control_panel,event,0)))
			StartEdit(file);
#endif
	} else panel_default_handle_event(item, event);
}

static COMP_ENTRY *edit_pointer;

static void
EditButton(item, event)
Panel_item item; Event *event;
{
	if (!edit_pointer) edit_pointer = completion_list;
	StartEdit(edit_pointer->data);
	edit_pointer = edit_pointer->next;
}

static void
ExecButton(item, event)
Panel_item item; Event *event;
{
	boolean bg;
	char buf[BUFSIZ], *file;

	if (set_up_run(&bg, buf, &file))
		background(buf, file);
}

/***/
void
ControlInit(frame)
Frame frame;
/* Create a subwindow to display the controls
 *    On entry-
 *       frame is the parent of the control display
 ***/
{
	control_panel = window_create(frame, PANEL, 0);

	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Quit", 6),
				 PANEL_NOTIFY_PROC, FrameFinl,
				 0);

	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Dir", 6),
				 PANEL_NOTIFY_PROC, DirButton,
				 0);
	
	prev = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("<=", 6),
				 PANEL_NOTIFY_PROC, PrevButton,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);

	next = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("=>", 6),
				 PANEL_NOTIFY_PROC, NextButton,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);
	
	goup = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Up", 6),
				 PANEL_NOTIFY_PROC, UpButton,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);
	
	undo = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Back", 6),
				 PANEL_NOTIFY_PROC, BackButton,
				 0);
	
	edit = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Edit", 6),
				 PANEL_NOTIFY_PROC, EditButton,
				 PANEL_EVENT_PROC, EditMenu,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);
	
	exec = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Run", 6),
				 PANEL_NOTIFY_PROC, ExecButton,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);
	
	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Goto Node", 11),
				 PANEL_LABEL_X, ATTR_COL(0),
				 PANEL_LABEL_Y, ATTR_ROW(1),
				 PANEL_NOTIFY_PROC, GotoButton,
				 0);
	
	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Search", 8),
				 PANEL_NOTIFY_PROC, SearchButton,
				 0);

	input = panel_create_item(control_panel, PANEL_TEXT,
				  PANEL_LABEL_STRING, "Node/String:",
				  PANEL_VALUE_DISPLAY_LENGTH, 30,
				  PANEL_VALUE, "",
				  0);

	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Complain...", 10),
				 PANEL_LABEL_X, ATTR_COL(0),
				 PANEL_LABEL_Y, ATTR_ROW(2),
				 PANEL_NOTIFY_PROC, ComplainButton,
				 0);
	
	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Options...", 9),
				 PANEL_NOTIFY_PROC, OptionButton,
				 0);
	
	(void) panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Print Node", 12),
				 PANEL_NOTIFY_PROC, PrintNodeButton,
				 0);
	
	pman = panel_create_item(control_panel, PANEL_BUTTON,
				 MY_PANEL_LABEL("Print Manual", 14),
				 PANEL_NOTIFY_PROC, PrintManualButton,
#ifdef XVIEW
				 PANEL_INACTIVE, TRUE,
#else
				 PANEL_SHOW_ITEM, FALSE,
#endif
				 0);
	
	echo = panel_create_item(control_panel, PANEL_MESSAGE,
				 PANEL_LABEL_X, ATTR_COL(0),
				 PANEL_LABEL_Y, ATTR_ROW(3),
				 PANEL_LABEL_STRING, 
				 "Move to a menu item or note by clicking on the text",
				 0);

	window_fit_height (control_panel);
}

/***/
void
ControlButton(nodetop)
int nodetop;
/* Set up the controls that are valid for the current node
 *    On entry-
 *       info_file[nodetop] is the first character of the node's mode line
 ***/
{
	char buf[BUFSIZ];
	extern char current_info_dir[], current_info_file[];

	if (extract_field ("Next:", next_node_name, nodetop))
		ACTIVATE_ITEM (next);
	else
		DEACTIVATE_ITEM (next);

	if (extract_field ("Prev:", prev_node_name, nodetop))
		ACTIVATE_ITEM (prev);
	else
		DEACTIVATE_ITEM (prev);

	if (extract_field ("Up:", up_node_name, nodetop))
		ACTIVATE_ITEM (goup);
	else
		DEACTIVATE_ITEM (goup);

	if (extract_field ("Edit", buf, nodetop) && get_eg_file_list()) {
		COMP_ENTRY *temp;

		eg_files = menu_create (0);
		for (temp = completion_list;
		     temp != (COMP_ENTRY *)NULL;
		     temp = temp->next)
			(void)menu_set(eg_files,
				MENU_APPEND_ITEM, menu_create_item (
					MENU_STRING_ITEM, temp->identifier, temp->data,
#ifdef XVIEW
					MENU_NOTIFY_PROC, EditFile,
#endif
					0),
				0);
		edit_pointer = completion_list;
		ACTIVATE_ITEM (edit);
	} else {
		if (eg_files) {
			menu_destroy(eg_files);
			eg_files = (Menu) NULL;
		}
		edit_pointer = (COMP_ENTRY *)NULL;
		DEACTIVATE_ITEM (edit);
	}

	if (extract_field ("Run", buf, nodetop))
		ACTIVATE_ITEM (exec);
	else
		DEACTIVATE_ITEM (exec);

	(void) sprintf (manualname, "%s%s%s", current_info_dir,
			current_info_file, PRINTEXTENSION);
	if (stat (manualname, &manualinfo) == 0)
		ACTIVATE_ITEM (pman);
	else
		DEACTIVATE_ITEM (pman);
}

/***/
void
EchoClear()
/* Clear the control panel's message area
 ***/
{
	panel_set(echo,
		PANEL_LABEL_STRING,
			"Move to a menu item or note by clicking on the text",
		0);
}

/***/
void
display_error(buf)
char *buf;
/* Inform the user of an error via the message area
 *    On entry-
 *       buf=message to be displayed
 ***/
{
	window_bell(control_panel);
	panel_set(echo, PANEL_LABEL_STRING, buf, 0);
}

/***/
void
ding()
/* Provide an audible signal to the user
 ***/
{
        window_bell(control_panel);
}
