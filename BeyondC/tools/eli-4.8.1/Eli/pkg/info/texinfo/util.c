static char rcsid[] = "$Id: util.c,v 1.12 2010/01/09 22:42:14 profw Exp $";

/* util.c

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
/*			Utility Functions			    */
/*								    */
/* **************************************************************** */

#include <string.h>
#include "info.h"
#include "option.h"
#include "util.h"

char *search_buffer;		/* area in ram to scan through. */
size_t buffer_bottom;		/* Length of this area. */

void
#if defined(__cplusplus) || defined(__STDC__)
set_search_constraints(char *buffer, size_t extent)
#else
set_search_constraints(buffer, extent) char *buffer; size_t extent;
#endif
{
  /* Set the global variables that all of these routines use. */

  search_buffer = buffer;
  buffer_bottom = extent;
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
to_beg_line(size_t from)
#else
to_beg_line(from) size_t from;
#endif
{
  extern int maxcol;
  int i;

  i = 0;
  /* Move back to the start of this line. */
  while (from && search_buffer[from - 1] != '\n') {
      from--;
      i++;
  }
  while (i > maxcol) {
    from += maxcol;
    i -= maxcol;
  }
  return (from);
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
to_end_line(size_t from)
#else
to_end_line(from) size_t from;
#endif
{
  extern int maxcol;
  int i;

  /* Move forward to the end of this line. */
  i = 0;
  while (from < buffer_bottom && search_buffer[from] != '\n' && i < maxcol) {
    from++;
    i++;
  }
  return (from);
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
to_end_file_line(size_t from)
#else
to_end_file_line(from) size_t from;
#endif
{
  /* Move forward to the end of this line. */
  while (from < buffer_bottom && search_buffer[from] != '\n')
    from++;
  return (from);
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
back_lines(size_t count, size_t starting_pos)
#else
back_lines(count, starting_pos) size_t count, starting_pos;
#endif
{
  /* Move back count lines in search_buffer starting at starting_pos.
     Returns the start of that line. */
  starting_pos = to_beg_line (starting_pos);
  while (starting_pos && count)
    {
      starting_pos = to_beg_line (starting_pos - 1);
      count--;
    }
  return (starting_pos);
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
forward_lines(size_t count, size_t starting_pos)
#else
forward_lines (count, starting_pos) size_t count, starting_pos;
#endif
{
  /* Move forward count lines starting at starting_pos.
     Returns the start of that line. */
  starting_pos = to_end_line (starting_pos);
  while (starting_pos < buffer_bottom && count)
    {
      starting_pos = to_end_line (starting_pos + 1);
      count--;
    }
  return (to_beg_line (starting_pos));
}

int
#if defined(__cplusplus) || defined(__STDC__)
search_forward(char *string, size_t *starting_pos)
#else
search_forward (string, starting_pos) char *string; size_t *starting_pos;
#endif
/* Search forward in the search_buffer
 * On entry-
 *   string is the string sought
 *   *starting_pos is the location to start the search
 * If the string is found then on exit-
 *   search_forward=1
 *   *starting_pos is the location of the string found
 * Else on exit-
 *   search_forward=0
 *   *starting_pos is unchanged
 ***/
{ size_t pos = *starting_pos, len = strlen(string);

  int insensitive = strnicmp(options[SEARCHINSENSITIVE].value,"yes",3) == 0;
#if defined(__cplusplus) || defined(__STDC__)
  int (*func)(const char *, const char *, size_t);
#else
  int (*func)();
#endif

  func = (insensitive ? strnicmp : strncmp);
  while ((pos + len) <= buffer_bottom) {
    if (func(search_buffer + pos, string, len) != 0) pos++;
    else {*starting_pos = pos; return 1; }
  }
  return 0;
}

int
#if defined(__cplusplus) || defined(__STDC__)
search_backward(char *string, size_t *starting_pos)
#else
search_backward (string, starting_pos) char *string; size_t *starting_pos;
#endif
/* Search backward in the search_buffer
 * On entry-
 *   string is the string sought
 *   *starting_pos is the location to start the search
 * If the string is found then on exit-
 *   search_backward=1
 *   *starting_pos is the index of the string found
 * Else on exit-
 *   search_backward=0
 *   *starting_pos is unchanged
 ***/
{ size_t pos = *starting_pos, len = strlen(string);

  int insensitive = strnicmp(options[SEARCHINSENSITIVE].value,"yes",3) == 0;
#if defined(__cplusplus) || defined(__STDC__)
  int (*func)(const char *, const char *, size_t);
#else
  int (*func)();
#endif

  func = (insensitive ? strnicmp : strncmp);
  while (pos >= len) {
    if (func(search_buffer + (pos - len), string, len) != 0) pos--;
    else {*starting_pos = pos - len; return 1; }
  }
  return 0;
}

int
#if defined(__cplusplus) || defined(__STDC__)
string_in_line(char *string, size_t *starting_pos)
#else
string_in_line(string, starting_pos) char *string; size_t *starting_pos;
#endif
/* Search forward in the current line
 * On entry-
 *   string is the string sought
 *   *starting_pos is the location to start the search
 * If the string is found then on exit-
 *   string_in_line=1
 *   *starting_pos is the location of the string found
 * Else on exit-
 *   string_in_line=0
 *   *starting_pos is unchanged
 ***/
{ size_t old_buffer_bottom = buffer_bottom;
  int result;

  set_search_constraints(search_buffer, to_end_file_line(*starting_pos));
  result = search_forward(string, starting_pos);
  buffer_bottom = old_buffer_bottom;
  return result;
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
skip_whitespace(size_t offset)
#else
skip_whitespace(offset) size_t offset;
#endif
/* Skip space and tab characters
 * On entry-
 *   offset is the index to start skipping
 * On exit-
 *   skip_whitespace=index of the first character other than space or tab
 *                   or the end of the buffer
 ***/
{ int character;

  while (offset < buffer_bottom) {
    character = search_buffer[offset];
    if (character == ' ' || character == '\t') offset++;
    else return offset;
  }
  return offset;
}

size_t
#if defined(__cplusplus) || defined(__STDC__)
skip_whitespace_and_cr(size_t offset)
#else
skip_whitespace_and_cr(offset) size_t offset;
#endif
/* Skip whitespace characters
 * On entry-
 *   offset is the index to start skipping
 * On exit-
 *   skip_whitespace_and_cr=index of the first non-whitespace character
 *                   or the end of the buffer
 ***/
{ int character;

  while (offset < buffer_bottom) {
    character = search_buffer[offset];
    if (character == ' ' || character == '\t' || character == '\n') offset++;
    else return offset;
  }
  return offset;
}

/* Extract the node name part of the of the text after the FIELD.
   Place the node name into NODENAME.  Assume the line starts at
   OFFSET in SEARCH_BUFFER. */
boolean
#if defined(__cplusplus) || defined(__STDC__)
extract_field(char *field_name, char *nodename, size_t offset)
#else
extract_field(field_name, nodename, offset)
char *field_name, *nodename; size_t offset;
#endif
{ int character;

  if (!string_in_line(field_name, &offset)) return (false);

  offset = skip_whitespace(offset + strlen(field_name));

  /* Okay, place the following text into NODENAME. */

  while ((character = search_buffer[offset]) != ','
	 && character != '\n'
	 && character != '\t')
    {
      *nodename = character;
      nodename++;
      offset++;
    }
  *nodename = '\0';
  return (true);
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
looking_at(char *string, size_t pointer)
#else
looking_at (string, pointer) char *string; size_t pointer;
#endif
{
  /* Return true if pointer is exactly at string, else false. */

  if (strnicmp (search_buffer + pointer, string, strlen (string)) == 0)
    return (true);
  else
    return (false);
}

/* Whoops, Unix doesn't have strnicmp. */

int
#if defined(__cplusplus) || defined(__STDC__)
strnicmp(const char *string1, const char *string2, size_t count)
#else
strnicmp (string1, string2, count)
char *string1, *string2; size_t count;
#endif
{
  /* Compare at most COUNT characters from string1 to string2.  Case
     doesn't matter. */
  char ch1, ch2;

  while (count)
    {
      ch1 = *string1++;
      ch2 = *string2++;
      if (to_upper (ch1) == to_upper (ch2))
	count--;
      else
	return ch1 < ch2 ? -1 : 1;
    }
  return 0;
}

void
#if defined(__cplusplus) || defined(__STDC__)
clean_up(char *string)
#else
clean_up (string)
char *string;
#endif
{
  /* Remove <CR> and whitespace from string, replacing them with
     only one space.  Exception:  <CR> at end of string disappears. */

  char *to = string;
  char last_char = 0;
  boolean result;

  while ((*to = *string++))
    {
      if (*to == '\n')
	{
	  *to = SPACE;
	  if (!(*(to + 1)))
	    {
	      *to = '\0';
	      return;
	    }
	}
      result = (last_char == SPACE);
      last_char = *to;
      if (last_char != SPACE)
	to++;
      else if (!result)
	to++;
    }
}
