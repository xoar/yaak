static char rcsid[] = "$Id: infotool.c,v 1.13 2010/01/09 22:42:13 profw Exp $";

/* mpr_static needs identifier concatenation. But the definition in 
 * /usr/include/pixrect/memvar.h results in errors while compiling under
 * Ansi C. 
 */

#if defined(__STDC__) || defined(__cplusplus)
#define CAT(a,b)	a##b
#endif

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#ifdef XVIEW
#include <xview/xview.h>
#include <xview/textsw.h>
#include <xview/panel.h>
#else
#include <suntool/sunview.h>
#include <suntool/textsw.h>
#include <suntool/panel.h>
#endif

#include "info.h"
#include "option.h"
#include "panel_sw.h"
#include "text_sw.h"
#include "complain_sw.h"
#include "option_sw.h"

extern void info();

#ifdef XVIEW
char *program_name = "XInfotool";
#else
char *program_name = "Infotool";
#endif

static char *message;
static int aborted = 0;
Frame frame;
int maxcol;

static unsigned short icon_image[] = {
#include "infotool.icon"
};
mpr_static(icon_pixrect, 64, 64, 1, icon_image);

#ifndef DEFAULT_WINRUNNER
#ifdef XVIEW
#define DEFAULT_WINRUNNER	"xterm -e"
#else
#define DEFAULT_WINRUNNER	"shelltool"
#endif
#endif

static INIT_OPTION infotool_options[] = {
	{ WINEDITOR, NULL }, /* value filled in below */
	{ WINRUNNER, DEFAULT_WINRUNNER },
	{ -1, NULL }
};

void
main(argc, argv)
int argc; char **argv;
{
	char buf[STRING_SIZE];
	char *cp;

#ifdef XVIEW
#define NO_PARENT (Xv_Window) NULL

	xv_init (XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);
#else
#define NO_PARENT NULL
#endif

	frame = window_create(NO_PARENT, FRAME,
		FRAME_ARGC_PTR_ARGV, &argc, argv,
		FRAME_ICON, icon_create(ICON_IMAGE, &icon_pixrect, 0),
		FRAME_LABEL, program_name,
		FRAME_NO_CONFIRM, TRUE,
		WIN_ERROR_MSG, "Cannot create frame",
#ifdef XVIEW
		XV_NAME, "XInfotool",
#endif
		0);

	maxcol = (int) window_get(frame, WIN_COLUMNS);

	ControlInit(frame);
	NodeInit(frame);

#ifdef XVIEW
	window_fit (frame);
#else
	window_fit_height (frame);
#endif

	/* Initialise options. */
	if ((cp = getenv("EDITOR")) == (char *)NULL)
		sprintf (buf, "%s %s", DEFAULT_WINRUNNER, DEFAULT_EDITOR);
	else
		sprintf (buf, "%s %s", DEFAULT_WINRUNNER, cp);
	infotool_options[0].value = buf;
	init_options( infotool_options );

	info(argc, argv);
	display_node();

	(void)signal(SIGINT, SIG_IGN);

	window_main_loop(frame);

	if (aborted) {
		(void)fputs(message, stderr); putc('\n', stderr);
	}

	exit(aborted);
}


void
FrameFinl()
{
	NodeClear();
	ComplainFinl();
	OptionFinl();
	window_destroy(frame);
}

void
opsys_abort(s, i)
char *s; int i;
{
	message = s;
	aborted = i;
	FrameFinl();
}
