static char rcsid[] = "$Id: infoReader.c,v 1.28 2013/11/14 04:02:11 profw Exp $";

/* infoReader.c -- a stand-alone Info program which does what Info in GNU Emacs does.

   Copyright (C) 1987 Free Software Foundation, Inc.

   This file is part of GNU Info.

   GNU Info is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.  No author or distributor accepts
   responsibility to anyone for the consequences of using it or for
   whether it serves any particular purpose or works at all, unless he
   says so in writing.  Refer to the GNU Emacs General Public License
   for full details.

   Everyone is granted permission to copy, modify and redistribute
   GNU Info, but only under the conditions described in the GNU Emacs
   General Public License.   A copy of this license is supposed to
   have been given to you along with GNU Emacs so you can know your
   rights and responsibilities.  It should be in a file named COPYING.
   Among other things, the copyright notice and this notice must be
   preserved on all copies.
*/
#include "../../../config.h" 
#include <unistd.h>

#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif
#include "info.h"
#include "driver.h"
#include "strbuild.h"
#include "file.h"
#include "node.h"
#include "menunote.h"
#include "option.h"
#include "system.h"
#include "signals.h"
#include "list.h"
#include "util.h"
#include "example.h"
#include "help.h"
#include "typeout.h"
#include "complete.h"
#include "page.h"

WINDOW *terminal_window, *modeline_window, *echo_area;
int maxcol;

/***/
void
#ifdef PROTO_OK
opsys_abort(char *message, int code)
#else
opsys_abort(message, code) char *message; int code;
#endif
/* Abort the session on a fatal error
 *    On entry-
 *       message=error report to be delivered
 *       code=exit code to be used
 ***/
{
  endwin();
  (void)fputs(message, stderr); putc('\n', stderr);
  exit(code);
}

extern boolean totally_inhibit_errors;

/***/
void
#ifdef PROTO_OK
display_error(char *report)
#else
display_error(report) char *report;
#endif
/* Report an error to the user
 *    On entry-
 *       report describes the error
 *       report terminates with '\n'
 ***/
{
  if (totally_inhibit_errors) return;

  werase(echo_area); wmove(echo_area, 0, 0);
  (void)waddstr(echo_area, report); (void)waddstr(echo_area, "\n");
  wrefresh(echo_area);
  putchar(CTRL('G'));
  return;
}

/***/
boolean
#ifdef PROTO_OK
confirm(char *s)
#else
confirm(s) char *s;
#endif
/* Request confirmation from the user
 *    On entry-
 *       s=Kernel of the query, which does NOT end with '\n'
 *    If the user answered "Y" then on exit-
 *       confirm=TRUE
 *    If the user answered "N" then on exit-
 *       confirm=FALSE
 ***/
{
	int character, y, x;

	werase(echo_area); wmove(echo_area, 0, 0);
	(void)waddstr(echo_area, s);
	(void)waddstr(echo_area, " (Y or N)? ");
	putchar(CTRL('G'));
	getyx(echo_area, y, x);
	wrefresh(echo_area);

	for (;;) {
		character = getch();
		mvwaddch(echo_area, y, x, character);
		wrefresh(echo_area);

		switch (character) {
		case 'y': case 'Y': return(true);
		case 'n': case 'N': return(false);
		default: putchar(CTRL('G'));
		}
	}
}

/**/
static void
#ifdef PROTO_OK
set_options(void)
#else
set_options()
#endif
/* Allow the user to change option values
 **/
{
  OPTION *op;
  char opt[STRING_SIZE], val[STRING_SIZE];

  /* put up the screen of current values and descriptions */
  /* also build completion list for later prompting */
  textstr("The options which can be set are:\n\n");
  init_completer();
  for (op = options; op->name != NULL; op++) {
    /* problem with NULL op->value??? */
    (void)sprintf(fmtarea,
      "%-*s%s\n    %s\n", INDENT, op->name, op->value, op->desc);
    textstr(fmtarea);
    add_completion( op->name, "" );
  }
  typeout(textptr, 1);
  textfree();

  /* read options and values and change them */
  for (;;) {
    /* get the option name */
    opt[0] = '\0';
    if (!readline( "Set which option (^G to finish): ", opt, STRING_SIZE,
		  true ))
      break;

    /* find its entry */
    for (op = options; (op->name != NULL); op++)
      if (strcmp(op->name,opt) == 0) break;
    if (op->name == NULL) continue;

    /* get the value, change it in the entry and on screen */
    val[0] = '\0';
    if (readline(strcat(opt, " = "), val, STRING_SIZE, false )) {
      if (op->value) free(op->value);
      op->value = strcpy((char *)xmalloc((size_t)(1+strlen(val))),val);
      mvwaddstr(terminal_window, 2*(op-options+1), INDENT, val);
      wclrtoeol(terminal_window);
      wrefresh(terminal_window);
    }
  }
}

/**/
static void
setup()
/* Set up the screen
 **/
{ if ((!isatty (0)) || (!isatty (1))) {
    fprintf (stderr, "infoReader: must be run with tty input and output.\n");
    exit (1);
  }
  initscr();
  maxcol = COLS;
  terminal_window = subwin(stdscr, LINES-3, 0, 0, 0);
  modeline_window = subwin(stdscr, 2, 0, LINES-3, 0);
  echo_area = subwin(stdscr, 1, 0, LINES-1, 0);

  /* Only the node subwindow can be scrolled */
  scrollok(modeline_window,FALSE);
  scrollok(echo_area, FALSE);

  /* Terminal should not echo, and we need each character */
  noecho(); crmode();
}

/**/
static void
#ifdef PROTO_OK
foreground(char *cmd, char *file)
#else
foreground(cmd, file) char *cmd, *file;
#endif
/* Run a command in the foreground
 *    On entry-
 *       cmd=command to be run
 *    If file != NULL then on exit-
 *       file has been deleted
 **/
{
  endwin();
  (void)system(cmd);
  if ( file ) (void)deletefile(file);
  setup();
  display_page(pagetop);
}

static void
complain()
{
  char cmdbuf[STRING_SIZE];

  endwin();
  (void)sprintf( cmdbuf, "%s %s", MAIL, MAINTAINER );
  (void)printf( "\nType your complaint in a mail message now.\n" );
  (void)printf( "Usually you should hit C-d to end, or C-c to abort.\n" );
  (void)printf( "%s\n", cmdbuf );
  if (system( cmdbuf ) != 0) {
    setup();
    (void)sprintf(fmtarea, "Error running \"%s\".", cmdbuf);
    display_error(fmtarea);
  } else setup();
}

int
#ifdef PROTO_OK
main(int argc, char *argv[])
#else
main(argc, argv) int argc; char **argv;
#endif
{
  boolean done = false;
  int command;
  char nodename[NODENAME_LEN];
  char searchstring[STRING_SIZE];
  size_t search_start;			/* place to start searching from */
  char search_node[NODENAME_LEN];	/* last node searched in */

  setup();

  textinit();
  init_options( (INIT_OPTION *)NULL );

  info(argc, argv);

  /* Install handlers for restoring/breaking the screen. */
  install_signals ();

  /* Display the initial screen */
  display_page(nodetop);
  waddstr(echo_area, "Welcome to Info!  Type \"?\" for help. ");
  wrefresh(echo_area);

  searchstring[0] = '\0';
  search_node[0] = '\0';

  while (!done) {
      nodename[0] = '\0';	/* Don't display old text in input line. */

      command = getch();
      werase(echo_area); wmove(echo_area, 0, 0);
      wrefresh(echo_area);

      switch (command = to_upper(command)) {

	case 'D':
	  (void)get_node ((char *)NULL, "(dir)Top", false);
	  display_page(nodetop);
	  break;

	case 'H':
	  if (LINES < 21)
	    (void)get_node ((char *)NULL, "(info)Help-Small-Screen", false);
	  else
	    (void)get_node ((char *)NULL, "(info)Help", false);
          display_page(nodetop);
	  break;

	case 'N':
	  if (!extract_field ("Next:", nodename, datatop)) {
	      display_error ("No NEXT for this node!");
	      break;
	  }
	  if (get_node ((char *)NULL, nodename, false))
	      display_page(nodetop);
	  break;

	case 'P':
	  if (!extract_field ("Prev:", nodename, datatop)) {
	      display_error ("No PREV for this node!");
	      break;
	  }
	  if (get_node ((char *)NULL, nodename, false))
	      display_page(nodetop);
	  break;

	case 'U':
	  if (!extract_field ("Up:", nodename, datatop)) {
	      display_error ("No UP for this node!");
	      break;
	  }
	  if (get_node ((char *)NULL, nodename, false))
	      display_page(nodetop);
	  break;

	case 'M':
	  if (!build_menu ()) {
	      display_error ("No menu in this node!");
	      break;
	  }

	  if (!readline ("Menu item: ", nodename, NODENAME_LEN, true))
	      break;

	  if (!find_menu_node (nodename, nodename)) {
	      (void)sprintf(fmtarea, "\"%s\" is not a menu item!", nodename);
	      display_error(fmtarea);
	      break;
	  }

	  if (get_node ((char *)NULL, nodename, false))
            display_page(nodetop);
	  break;


	case 'F':
	  {
	    char footnote[NODENAME_LEN];
	    if (!build_notes ()) {
		display_error ("No cross-references in this node!");
		break;
	    }
	    footnote[0] = '\0';
	    if (!readline ("Follow reference: ", footnote, NODENAME_LEN, true))
	      break;

	    if (!find_note_node (footnote, nodename)) {
		(void)sprintf(fmtarea,
		  "\"%s\" is not a cross-reference in this node!",
		  footnote);
		display_error(fmtarea);
		break;
	    }

	  if (get_node ((char *)NULL, nodename, false))
            display_page(nodetop);
	  break;
	  }

	case 'L':
	  if (last_node()) display_page(pagetop);
	  break;


	case CTRL('D'):
	  if (pagebot == nodebot) {
	      display_error ("At last page of this node now!");
	      break;
	  }
	  set_search_constraints(info_file, nodebot);
	  display_page(forward_lines((LINES-3)/2, pagetop));
	  break;

	case SPACE:
	  if (pagebot == nodebot) {
	      display_error ("At last page of this node now!");
	      break;
	  }
	  set_search_constraints(info_file, nodebot);
	  display_page(back_lines(1, pagebot));
	  break;

	case CTRL('U'):
	  if (pagetop == nodetop) {
	      display_error ("At first page of this node now!");
	      break;
	  }
	  set_search_constraints(info_file, nodebot);
          display_page(back_lines((LINES-3)/2, pagetop));
	  break;

	case DELETE:
	  if (pagetop == nodetop) {
	      display_error ("At first page of this node now!");
	      break;
	  }
	  set_search_constraints(info_file, nodebot);
          display_page(back_lines(LINES-4, pagetop));
	  break;

	case 'B':
	  if (pagetop == nodetop) {
	      display_error ("Already at beginning of this node!");
	      break;
	  }
	  display_page(nodetop);
	  break;

	  /* I don't want to do this this way, but the documentation clearly states
	     that '6' doesn't work.  It states this for a reason, and ours is not to
	     wonder why... */

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	  {
	    int item = command - '0';
	    if (!build_menu ()) {
		display_error ("No menu in this node!");
		break;
	    }
	    if (item > the_menu_size) {
		(void)sprintf(fmtarea,
		  "There are only %d items in the menu!",
		  the_menu_size);
		display_error(fmtarea);
		break;
	    }

	    if (get_menu (item)) display_page(nodetop);
	    break;
	  }

	case 'G':
	  if (readline ("Goto node: ", nodename, NODENAME_LEN, false)
	      && get_node ((char *)NULL, nodename, false))
            display_page(nodetop);
	  break;

	case 'S':
	  {
	    /* Search from the starting position forward for a string.
	       Of course, this should really wrap the search around, but
	       it doesn't do that yet.  Select the node containing the
	       desired string.  Put the top of the page screen_lines/2
	       lines behind it, but not before nodetop. */

	    size_t pointer;

	    if (strcmp( current_info_node, search_node) != 0)
	      search_start = pagetop;

	    if (!readline ("Search for string: ", searchstring, STRING_SIZE,
			   false))
		break;

	    if (indirect) {
		/* Put the indirect search right here. */
		display_error ("This is an indirect file, and I can't search these yet!");
		break;
	    } else {
		set_search_constraints (info_file, info_buffer_len);
		if(!search_forward (searchstring, &search_start)) {
		    (void)sprintf(fmtarea,
		      "\"%s\" not found.", searchstring);
		    display_error(fmtarea);
		    break;
		}
		/* save the position for next time */
		search_start += strlen(searchstring);
	    }
	    if (!search_backward(start_of_node_string, &pointer)) {
		(void)sprintf(fmtarea,
		  "\"%s\" not within a node.", searchstring);
		display_error(fmtarea);
		break;
	    }

	    pointer = forward_lines (1, pointer);
	    if (!extract_field ("Node:", nodename, pointer)) {
		display_error ("There doesn't appear to be a nodename for this node.");
		if (get_node ((char *)NULL, "*", false)) display_page(pointer);
		break;
	    }

	    (void)strcpy( search_node, nodename );

	    if (get_node ((char *)NULL, nodename, false)) {
	      werase(echo_area); wmove(echo_area, 0, 0);
	      display_page(back_lines((LINES-3)/2, search_start));
	    }
	    break;
	  }

	case CTRL ('H'):
	case '?':
	  help_use_info ();
          display_page(pagetop);
	  break;

	case 'Q':
	  if (confirm("Really quit Info")) { done = true; break; }
	  werase(echo_area); wmove(echo_area, 0, 0);
	  break;

	case CTRL ('L'):	/* Control-l is redisplay */
          display_page(pagetop);
	  break;

	case '(':		/* You *must* be trying to type a complete nodename. */
	  (void)strcpy (nodename, "(");
	  if (!readline ("Goto node: ", nodename, NODENAME_LEN, false))
	      break;

	  if (get_node ((char *)NULL, nodename, false)) {
	    werase(echo_area); wmove(echo_area, 0, 0);
	    display_page(nodetop);
	  }
	  break;

	case CTRL('T'):
	  if (!confirm("Really print current node")) {
	    werase(echo_area); wmove(echo_area, 0, 0);
	    break;
	  }

	  if (print_current_node()) {
	    (void)sprintf(fmtarea,
	      "The current node has been sent to \"%s\".",
	      options[PRINTER].value);
	    display_error(fmtarea);
	  }
	  break;

	case CTRL('P'):
	  {
	    char printfilename[STRING_SIZE];

	    if (!confirm("Really print current manual in full")) {
	      werase(echo_area); wmove(echo_area, 0, 0);
	      break;
	    }

	    if (strcmp(current_info_file,"dir") == 0) {
	      display_error("No manual associated with the directory node.");
	    } else {
	      (void)sprintf( printfilename, "%s%s%s", current_info_dir,
			    current_info_file, PRINTEXTENSION );
	      if (printfile(printfilename)) {
		(void)sprintf(fmtarea,
		  "The manual has been sent to \"%s\".",
		  options[PRINTER].value);
		display_error(fmtarea);
	      }
	    }
	  }
	  break;

	case 'O':
	  set_options();
	  display_page(pagetop);
	  break;

	case 'R':
        {
          boolean bg;
          char cmdbuf[BUFSIZ], *cmdfilename;

          /* check for runnable commands in this node */
          if (!extract_field ("Run", nodename, datatop)) {
            display_error ("No commands to run in this node!");
            break;
          }

          if (!set_up_run(&bg, cmdbuf, &cmdfilename)) break;

          if (bg) background(cmdbuf, cmdfilename);
          else foreground(cmdbuf, cmdfilename);
	  break;
        }

	case 'V':
	  if (FILE_EXISTS(SCRIPTOUTPUT)
	      && get_node( SCRIPTOUTPUT, "*", false ))
	    display_page(nodetop);
	  else {
	    display_error( "No run output to display, see 'r' command." );
	  }
	  break;

	case 'E':
        {
          boolean bg;
          char file[FILENAME_LEN], cmdbuf[BUFSIZ];

          /* make sure that there are editable things in this node */
          if (!extract_field ("Edit", nodename, datatop) ||
              !get_eg_file_list()) {
            display_error ("No files in this node are accessible!");
            break;
          }

          /* read the name of the file to be edited with completion */
          file[0] = '\0';
          if (!readline("File to edit: ",file,FILENAME_LEN,true)) {
            break;
          }
	  (void)scan_list(file, file);

          set_up_edit(&bg, cmdbuf, file);

          if (bg) background(cmdbuf, (char *)NULL);
          else foreground(cmdbuf, (char *)NULL);
	  break;
        }

	case 'C':
	  complain();
	  display_page(pagetop);
	  break;

	default:
	  display_error ("Unknown command! Type \"?\" for help.");

	}
    wmove(echo_area, 0, 0); wrefresh(echo_area);
  }

  endwin();
  putchar('\n');

  return 0;
}
