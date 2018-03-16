static char rcsid[] = "$Id: menunote.c,v 1.12 2005/07/29 21:47:28 profw Exp $";

/* menunote.c

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
#if USE_NCURSES
#include "ncurses.h"
#else
#include "curses.h"
#endif
#include "info.h"
#include "node.h"
#include "list.h"
#include "util.h"

char *visible_footnote = 0;	/* The default prompt string for the Follow Reference command. ams: not any more! */

/* Number of items that the current menu has. */
int the_menu_size = 0;

/* The node that last made a menus completion list. */
char menus_nodename[NODENAME_LEN];
char menus_filename[NODENAME_LEN];

/* Build a completion list of menuname/nodename for each
   line in this node that is a menu item. */
boolean
build_menu ()
{
  size_t pointer = nodetop;
  char menuname[NODENAME_LEN];
  char nodename[NODENAME_LEN];

  if (strcmp (menus_nodename, current_info_node) == 0 &&
      strcmp (menus_filename, current_info_file) == 0)
    return (the_menu_size != 0);

  (void)strcpy (menus_nodename, current_info_node);
  (void)strcpy (menus_filename, current_info_file);
  free_completion_list ();

  set_search_constraints (info_file, nodebot);
  the_menu_size = 0;
  if (!search_forward(MENU_HEADER, &pointer)) return (false);

  /* There is a menu here.  Look for members of it. */
  pointer += strlen (MENU_HEADER);

   for (;;) {
      int ndx, infilename;

      if (!search_forward(MENU_ID, &pointer))
        break;			/* no more menus in this node. */
      pointer = skip_whitespace(pointer + strlen(MENU_ID));
      ndx = 0;
      /* skip over the leading character, ie. ignore leadings ':'s */
      menuname[ndx++] = info_file[pointer++];
      while ((menuname[ndx] = info_file[pointer]) && menuname[ndx] != ':')
	{
	  ndx++, pointer++;
	}
      menuname[ndx] = '\0';
      pointer++;
      if (info_file[pointer] == ':')
	{
	  (void)strcpy (nodename, menuname);
	}
      else
	{
	  pointer = skip_whitespace(pointer);
	  ndx = 0;
	  infilename = 0;
	  while ((nodename[ndx] = info_file[pointer]) &&
		 nodename[ndx] != '\t' &&
		 (infilename || (nodename[ndx] != '.' &&
				 nodename[ndx] != ',')))
	    {
	      /* assumes we don't have multiple sets of () */
	      if (nodename[ndx] == '(') infilename++;
	      else if (nodename[ndx] == ')') infilename--;
	      ndx++, pointer++;
	    }
	  nodename[ndx] = '\0';
	}
      add_completion (menuname, nodename);
      the_menu_size++;
    }
  if (the_menu_size)
    completion_list = reverse_list (completion_list);
  return (the_menu_size != 0);
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
get_menu(int item)
#else
get_menu (item)
     int item;
#endif
{
  /* Select ITEMth item from the list built by build_menu. */

  if (!build_menu ()) return (false);
  if (item > the_menu_size) return (false);
  else {
    COMP_ENTRY *temp;
    for (temp = completion_list; --item; temp = temp->next) ;
    return (get_node((char *)0, temp->data, false));
  }
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
find_menu_node(char *string, char *nodename)
#else
find_menu_node (string, nodename)
     char *string, *nodename;
#endif
{
  /* Scan through the ?already? built menu list looking
     for STRING.  If you find it, put the corresponding nodes
     name in NODENAME. */

  return (scan_list (string, nodename));
}

static int
#if defined(__cplusplus) || defined(__STDC__)
find_footnote_ref(size_t *from)
#else
find_footnote_ref(from) size_t *from;
#endif
/* Find a footnote reference
 *   On entry-
 *     *from=index of the current position
 *   If there is a footnote beyond the current position then on exit-
 *     find_footnote_ref=1
 *     *from=index of the footnote
 *   Else on exit-
 *     find_footnote_ref=01
 *     *from is unchanged
 ***/
{ for (;;) {
      if (!search_forward (FOOTNOTE_HEADER, from)) return 0;
      else
	*from += strlen(FOOTNOTE_HEADER);
      if (info_file[*from] == ' ' ||
	  info_file[*from] == '\n' ||
	  info_file[*from] == '\t')
	return 1;
    }
}

boolean
#ifdef PROTO_OK
build_notes(void)
#else
build_notes()
#endif
{
  /* Build an array of (footnote.nodename) for each footnote in this node. */

  size_t pointer;
  char notename[NODENAME_LEN];
  char nodename[NODENAME_LEN];

  set_search_constraints (info_file, nodebot);

  pointer = nodetop;
  if (!find_footnote_ref(&pointer)) return (false);

  menus_filename[0] = menus_nodename[0] = '\0';
  visible_footnote = "";
  free_completion_list ();

  for(pointer = nodetop;;)
    {
      int ndx;

      if (!find_footnote_ref(&pointer))
	break;			/* no more footnotes in this node. */

      pointer = skip_whitespace_and_cr (pointer);
      ndx = 0;
      while ((notename[ndx] = info_file[pointer]) && notename[ndx] != ':')
	{
	  ndx++, pointer++;
	}
      notename[ndx] = '\0';
      clean_up (notename);
      pointer++;
      if (info_file[pointer] == ':')
	{
	  (void)strcpy (nodename, notename);
	}
      else
	{
	  pointer = skip_whitespace_and_cr (pointer);
	  ndx = 0;
	  while ((nodename[ndx] = info_file[pointer]) &&
		 nodename[ndx] != '\t' &&
		 nodename[ndx] != '.' &&
		 nodename[ndx] != ',')
	    {
	      ndx++, pointer++;
	    }
	  nodename[ndx] = '\0';
          clean_up (nodename);
	}
      /* Add the notename/nodename to the list. */
      add_completion (notename, nodename);
      the_menu_size++;

      /* Remember this identifier as the default if it is the first one in the
         page. */
      if (!(*visible_footnote) &&
	  pointer > pagetop &&
      pointer < forward_lines (LINES-3, pointer))
	visible_footnote = completion_list->identifier;
    }
  if (the_menu_size)
    completion_list = reverse_list (completion_list);
  return (the_menu_size != 0);
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
find_note_node(char *string, char *nodename)
#else
find_note_node (string, nodename)
     char *string, *nodename;
#endif
{
  /* Scan through the ?already? built footnote list looking
     for STRING.  If found, place the corresponding node name
     in NODENAME. */

  return (scan_list (string, nodename));
}
