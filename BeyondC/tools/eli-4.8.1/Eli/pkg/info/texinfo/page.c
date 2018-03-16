static char rcsid[] = "$Id: page.c,v 1.17 2010/01/09 22:42:13 profw Exp $";

#include "../../../config.h" 
#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif
#include "info.h"
#include "util.h"
#include "node.h"
#include "page.h"

/* The windows */
extern WINDOW *terminal_window, *modeline_window, *echo_area;
extern int maxcol;

void
#ifdef PROTO_OK
make_modeline(size_t pagebot)
#else
make_modeline(pagebot) size_t pagebot;
#endif
{
  /* Create and display the modeline. */

  char modeline1[256], modeline2[256];
  size_t i, first_line, displayed_lines;
  char unodename[NODENAME_LEN];
  char nnodename[NODENAME_LEN];
  char pnodename[NODENAME_LEN];
  char egstring[NODENAME_LEN];

  (void)sprintf (modeline1, "Info: (%s)%s, ",
		 current_info_file, current_info_node );

  /* Discover first line number and the number of lines displayed */
  for (i = nodetop, first_line = 1; i != pagetop; i++)
    if (info_file[i] == '\n') first_line++;
  for (i = pagetop, displayed_lines = 0; i != pagebot; i++)
    if (info_file[i] == '\n') displayed_lines++;
  if (pagebot == nodebot) displayed_lines--;
  
  /* Decide how to display the current position */
  (void)sprintf (&modeline1[strlen (modeline1)], "lines %lu-%lu of %d",
		 (unsigned long)first_line,
		 (unsigned long)(first_line + displayed_lines), nodelines);

  /* ams: This just takes up space on the modeline and doesn't help the user
     at all. */
#ifdef NOTDEF
  if (strnicmp
      (pathname (current_info_file), last_loaded_info_file,
       strlen (last_loaded_info_file)) != 0)
    {
      (void)sprintf (&modeline1[strlen (modeline1)], ", Subfile: %s", 
		     last_loaded_info_file);
    }
#endif

  /* Build the second line of the modeline with the node info. */
  modeline2[0] = '\0';
  if (extract_field ("Eg:", egstring, datatop)) {
    (void) strcat( modeline2, egstring );
    (void) strcat( modeline2, " " );
  }
  if (extract_field ("Up:", unodename, datatop)) {
    (void) strcat( modeline2, "U:" );
    (void) strcat( modeline2, unodename );
    (void) strcat( modeline2, " " );
  }
  if (extract_field ("Next:", nnodename, datatop)) {
    (void) strcat( modeline2, "N:" );
    (void) strcat( modeline2, nnodename );
    (void) strcat( modeline2, " " );
  }
  if (extract_field ("Prev:", pnodename, datatop)) {
    (void) strcat( modeline2, "P:" );
    (void) strcat( modeline2, pnodename );
    (void) strcat( modeline2, " " );
  }

#if defined(__cplusplus) || defined(__STDC__)
  if (strlen (modeline1) < (size_t)maxcol)
#else
  if (strlen (modeline1) < maxcol)
#endif
    {
      size_t index = strlen (modeline1);
      while (index != maxcol)
	modeline1[index++] = '-';
      modeline1[index] = '\0';
    }
#if defined(__cplusplus) || defined(__STDC__)
  if (strlen (modeline2) < (size_t)maxcol)
#else
  if (strlen (modeline2) < maxcol)
#endif
    {
      size_t index = strlen (modeline2);
      while (index != maxcol)
	modeline2[index++] = '-';
      modeline2[index] = '\0';
    }

#if defined(__cplusplus) || defined(__STDC__)
  if (strlen (modeline1) > (size_t)maxcol)
#else
  if (strlen (modeline1) > maxcol)
#endif
    modeline1[maxcol] = '\0';
#if defined(__cplusplus) || defined(__STDC__)
  if (strlen (modeline2) > (size_t)maxcol)
#else
  if (strlen (modeline2) > maxcol)
#endif
    modeline2[maxcol] = '\0';

  werase(modeline_window); wmove(modeline_window, 0, 0);
  wstandout(modeline_window);
  waddstr(modeline_window, modeline1);
  waddstr(modeline_window, modeline2);
  wstandend(modeline_window);
  wrefresh(modeline_window);
}

void
#ifdef PROTO_OK
display_page(size_t start)
#else
display_page(start) size_t start;
#endif
/* Display the current node in the terminal window
 *    On entry-
 *       start=index of the first character to be displayed
 *       nodebot=offset of the first character beyond the node
 *    On exit-
 *       The text has been displayed
 *       pagetop=offset of the first character of the page
 *       pagebot=offset of the first character beyond the page
 ***/
{
	size_t i;

	if (start < nodetop) pagetop = nodetop;
	else pagetop = start;
	set_search_constraints(info_file, nodebot);

	pagebot = forward_lines(LINES-3, pagetop);
	if (pagebot == nodebot) {
		pagetop = back_lines(LINES-3, pagebot);
		if (pagetop < nodetop) pagetop = nodetop;
	}

	werase(terminal_window); wmove(terminal_window, 0, 0);
	for (i = pagetop; i < pagebot; i++)
		waddch(terminal_window, info_file[i]);
	wrefresh(terminal_window);

	make_modeline(i);
}
