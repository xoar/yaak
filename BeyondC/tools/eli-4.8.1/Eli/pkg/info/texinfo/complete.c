static char rcsid[] = "$Id: complete.c,v 1.15 2010/01/09 22:42:10 profw Exp $";

/* complete.c

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

/* **************************************************************** */
/*								    */
/*			Completing Things			    */
/*								    */
/* **************************************************************** */

#include "../../../config.h"
#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif

#include "info.h"
#include "strbuild.h"
#include "typeout.h"
#include "system.h"
#include "util.h"
#include "list.h"
#include "complete.h"

/* The echo area */
extern WINDOW *echo_area;
extern int maxcol;

/* The vector of COMP_ENTRY pointers that COMPLETE returns. */
COMP_ENTRY **completions = NULL;

/* The number of elements in the above vector. */
int completion_count;

/* Initial size of COMPLETIONS array. */
#define INITIAL_COMPLETIONS_CORE_SIZE 200

/* Current size of the completion array in core. */
int completions_core_size = 0;

/* Ease the typing task.  Another name for the I'th IDENTIFIER of COMPLETIONS. */
#define completion_id(i) ((completions[(i)])->identifier)
#define completion_data(i) ((completions[(i)])->data)

/* The number of completions that can be present before the help
   function starts asking you about whether it should print them
   all or not. */
int completion_query_threshold = 100;

int help_print_data;

void
#ifdef PROTO_OK
init_completer(void)
#else
init_completer()
#endif
{
  /* Initialize whatever the completer is using. */

  if (completions_core_size != INITIAL_COMPLETIONS_CORE_SIZE)
    {
      if (completions) free ((char *)completions);
      completions = (COMP_ENTRY **)xmalloc((unsigned)((sizeof (COMP_ENTRY *)) *
		   (completions_core_size = INITIAL_COMPLETIONS_CORE_SIZE)));
    }
  completion_count = 0;
}

void
#ifdef PROTO_OK
remember_completion(COMP_ENTRY *pointer)
#else
remember_completion(pointer) COMP_ENTRY *pointer;
#endif
{
  if (completion_count == completions_core_size) {
    COMP_ENTRY **temp = (COMP_ENTRY **)xrealloc((char *)completions,
	(size_t)((sizeof (COMP_ENTRY *)) *
	 (completions_core_size += INITIAL_COMPLETIONS_CORE_SIZE)));
    if (temp) completions = temp;
    else {
      char errbuf[BUFSIZ];
	(void)sprintf(errbuf, "Too many completions (%d)!Out of core!",
			     completion_count);
	display_error(errbuf);
	return;
    }
  }
  completions[completion_count++] = pointer;
}

boolean
#ifdef PROTO_OK
complete(char *text, COMP_ENTRY *list)
#else
complete(text, list) char *text; COMP_ENTRY *list;
#endif
{
  /* Complete TEXT from identifiers in LIST.  Place the resultant
     completions in COMPLETIONS, and the number of completions in
     COMPLETION_COUNT. Modify TEXT to contain the least common
     denominator of all the completions found. */

  int low_match, i, ndx;
  size_t string_length = strlen (text);

  init_completer ();
  low_match = 1000; /* some large number. */

  while (list)
    {
      if (strnicmp (text, list->identifier, string_length) == 0)
	remember_completion (list);
      list = list->next;
    }

  if (completion_count == 0)
    return (false);

  if (completion_count == 1)
    {				/* One completion */
      (void)strcpy (text, completion_id (0));
      return (true);
    }

  /* Else find the least common denominator */

  for (ndx = 1; ndx < completion_count; ndx++) {
      int c1, c2;

      for (i = 0;
	   (c1 = to_lower (completion_id (ndx - 1)[i])) &&
	   (c2 = to_lower (completion_id (ndx)[i]));
	   i++)
	if (c1 != c2) break;

      if (low_match > i) low_match = i;
  }

  (void)strncpy (text, completion_id (0), low_match);
  text[low_match] = '\0';
  return (true);
}

/* Complete TEXT from the completion structures in COMPLETION_LIST. */
boolean
#ifdef PROTO_OK
try_complete(char *text)
#else
try_complete(text) char *text;
#endif
{
  return (complete (text, completion_list));
}

void
#ifdef PROTO_OK
help_possible_completions(char *text)
#else
help_possible_completions(text) char *text;
#endif
{
  /* The function that prints out the possible completions. */

  char temp_string[2000];

  (void)strcpy (temp_string, text);
  (void)try_complete (temp_string);

  if (completion_count == 0) {
    typeout("There are no possible completions.\n", 1);
    wrefresh(echo_area);
    return;
  }

  if (completion_count == 1) {
    textstr("The only possible completion of what you have typed is:\n\n");
    if (help_print_data)
	(void)sprintf(fmtarea,"%s%s\n",completion_id(0),completion_data(0));
      else
	(void)sprintf(fmtarea,"%s\n",completion_id(0));
    textstr(fmtarea);
    typeout(textptr, 1);
    textfree();
    wrefresh(echo_area);
    return;
  }

  if (completion_count >= completion_query_threshold) {
      (void)sprintf(fmtarea,
	"There are %d completions.  Do you really want to see them all",
	completion_count);
      if (!confirm (fmtarea)) return;
  }

  (void)sprintf(fmtarea,
    "The %d completions of what you have typed are:\n\n", completion_count);
  textstr(fmtarea);

  if (help_print_data) {
    int ndx;
    for (ndx = 0; ndx < completion_count; ndx++) {
      (void)sprintf(fmtarea,
	"%s%s\n",completion_id(ndx),completion_data(ndx));
      textstr(fmtarea);
      }
  } else {
    int ndx;
    int next = 0;
    int column = 0;

    for (ndx = 0; ndx < completion_count; ndx++) {
      char *p; size_t length = strlen(completion_id(ndx));

      if (column+length > maxcol) {
	fmtarea[next] = '\n'; fmtarea[next+1] = '\0'; textstr(fmtarea);
	next = column = 0;
      }

      while (next < column) fmtarea[next++] = ' ';
      for (p = completion_id(ndx); *p; p++) fmtarea[next++] = *p;

      do column += 30; while (next+4 > column);
    }
    fmtarea[next] = '\n'; fmtarea[next+1] = '\0'; textstr(fmtarea);
  }
  typeout(textptr, 1); textfree();
}

/* Function for reading a line.  Supports completion on COMPLETION_LIST
   if you pass COMPLETING as true.  Prompt is either a prompt or NULL,
   LINE is the place to store the characters that are read.  LINE may start
   out already containing some characters; if so, they are printed.  MAXCHARS
   tells how many characters can fit in the buffer at LINE.  READLINE returns
   FALSE if the user types the abort character.  LINE is returned with a '\0'
   at the end, not a '\n'.  */

boolean
#ifdef PROTO_OK
readline(char *prompt, char *line, int maxchars, boolean completing)
#else
readline (prompt, line, maxchars, completing)
     char *prompt, *line;
     int maxchars;
     boolean completing;
#endif
{
  int character, y, x;

  size_t current_len = strlen (line);
  int meta_flag = 0;

  werase(echo_area); wmove(echo_area, 0, 0);
  if (prompt) waddstr(echo_area, prompt);
  getyx(echo_area, y, x);
  waddstr(echo_area, line);

  while (true)
    {

      line[current_len] = '\0';
      wrefresh(echo_area);

      character = getch();
      if (meta_flag)
	{
	  character = META (character);
	  meta_flag = 0;
	}

      if (META_P (character))
	character = META (to_upper (UNMETA (character)));

      switch (character)
	{

	case EOF:
	  character = '\n';

	case ESC:
	  meta_flag++;
	  break;

	case META (DELETE):
	case CTRL ('W'):
	  while (current_len && line[current_len] == SPACE) {
	    current_len--; waddch(echo_area, '\b');
	  }
	  while (current_len && line[current_len] != SPACE) {
	    current_len--; waddch(echo_area, '\b');
	  }
	  break;

	case CTRL ('U'):
	  current_len = 0;
	  wmove(echo_area, y, x);
	  break;

	case '\b':
	case 0x07f:
	  if (current_len) { current_len--; waddch(echo_area, '\b'); }
	  else putchar(CTRL('G'));
	  break;

	case '\n':
	case '\r':
	  if (completing) {
	      (void)try_complete (line);
	      if (completion_count >= 1) {
		  (void)strcpy(line, completion_id(0));
		  mvwaddstr(echo_area, y, x, completion_id(0));
		  wclrtoeol(echo_area);
		  wrefresh(echo_area);
		  return (true);
	      } else {
		  current_len = strlen (line);
		  putchar(CTRL('G'));
		  break;
	      }
	  } else {
	      wrefresh(echo_area);
	      return (true);
	  }

	case ABORT_CHAR:
	  if (current_len) current_len = 0;
	  else return (false);
	  break;

	case '?':
	  if (completing) help_possible_completions (line);
	  break;

	case ' ':
	case '\t':
	  if (completing) {
	    char temp_line[NODENAME_LEN];
	    (void)strcpy (temp_line, line);
	    (void)try_complete (line);
	    if (completion_count != 1 && character == SPACE) {
		if (strcmp (temp_line, line) == 0) {
		  line[current_len] = SPACE;
		  line[current_len + 1] = '\0';
		  (void)strcpy (temp_line, line);
		  (void)try_complete (line);
		  if (completion_count == 0) {
		    line[current_len] = '\0';
		    putchar(CTRL('G'));
		  }
		}
	    }
	    current_len = strlen (line);
	    mvwaddstr(echo_area, y, x, line);
	    if (completion_count == 0) putchar(CTRL('G'));
	    break;
	  }
	default:
	  if (!CTRL_P (character) && !META_P (character) &&
	      current_len < maxchars) {
	    line[current_len++] = character;
	    waddch(echo_area, character);
	  } else putchar(CTRL('G'));
	}
    }
}
