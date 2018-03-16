static char rcsid[] = "$Id: typeout.c,v 1.10 2010/01/09 22:42:14 profw Exp $";

#include "../../../config.h"
#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif
#include "info.h"
#include "util.h"
#include "typeout.h"

/* Windows */
extern WINDOW *terminal_window, *echo_area;
extern int maxcol;

static char *message;
static size_t length, texttop, textbot;

/**/
static void
#ifdef PROTO_OK
type(size_t offset)
#else
type(offset) size_t offset;
#endif
/* Type a portion of the text
 *    On entry-
 *       s=string containing the typeout area
 *       offset indexes the first character of the text to be typed
 *    On exit-
 *       texttop indexes the first character of the text actually typed
 *       textbot indexes the first character beyond the text actually typed
 **/
{
	size_t i;

	textbot = forward_lines(LINES-4, offset);
	texttop = back_lines(LINES-4, textbot);

	wmove(terminal_window, 0, 0);
	for (i = texttop; i < textbot; i++)
		waddch(terminal_window, message[i]);

	if (texttop == 0 && textbot == length) {
		int i;
		for (i = 0; i < maxcol; i++) (void)waddch(terminal_window, '-');
	} else {
		if (textbot == length) waddstr(terminal_window, "[Done]");
		else waddstr(terminal_window, "[More]");
		wclrtoeol(terminal_window);
	}
	wrefresh(terminal_window);
}

/***/
void
#ifdef PROTO_OK
typeout(char *s, int ret)
#else
typeout(s, ret) char *s; int ret;
#endif
/* Type out a string to the terminal window
 *    On entry-
 *       s=string to be typed out (must end with \n)
 *       ret=1 if typeout should return if whole string fits on one page
 *	     0 otherwise.
 ***/
{
	int character;
	WINDOW *help;

	message = s; length = strlen(s);
	set_search_constraints(s, length);

	type(0);
	if (ret && (textbot == length)) return;

	help = newwin(1, maxcol, LINES-1, 0);
	waddstr(help, "SPACE=advance, DEL=back up, Q=end display\n");
	wrefresh(help);

	for (;;) {
		character = getch();
		switch (to_upper(character)) {
		case SPACE:
			if (textbot == length) { putchar(CTRL('G')); break; }
			type(back_lines(2, textbot));
			break;
		case DELETE:
			if (texttop == 0) { putchar(CTRL('G')); break; }
			type(back_lines(LINES-6, texttop));
			break;
		case 'Q':
			delwin(help);
			touchwin(echo_area);
			return;
		default:
			putchar(CTRL('G'));
			wrefresh(help);
			touchwin(echo_area);
		}
	}
}
