static char rcsid[] = "$Id: list.c,v 1.4 1998/02/11 16:43:15 waite Exp $";

/* list.c

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

#include "info.h"
#include "util.h"
#include "system.h"

/* The linked list of COMP_ENTRY structures that you create. */
COMP_ENTRY *completion_list = (COMP_ENTRY *) NULL;

void
free_completion_list()
{
  COMP_ENTRY *temp;
  while (completion_list)
    {
      temp = completion_list;
      if (completion_list->identifier)
	free (completion_list->identifier);
      if (completion_list->data)
	free (completion_list->data);
      completion_list = completion_list->next;
      free ((char *)temp);
    }
}

/* Add a single completion to COMPLETION_LIST.
   IDENTIFIER is the string that the user should type.
   DATA should just be a pointer to some random data that you wish to
   have associated with the identifier, but I'm too stupid for that, so
   it must be a string as well.  This allocates the space for the strings
   so you don't necessarily have to. */
void
#if defined(__cplusplus) || defined(__STDC__)
add_completion(char *identifier, char *data)
#else
add_completion(identifier, data)
char *identifier, *data;
#endif
{
  COMP_ENTRY *temp = (COMP_ENTRY *) xmalloc (sizeof (COMP_ENTRY));

  temp->identifier = (char *)xmalloc((size_t)(strlen(identifier) + 1));
  (void)strcpy (temp->identifier, identifier);
  temp->data = (char *)xmalloc((size_t)(strlen(data) + 1));
  (void)strcpy (temp->data, data);
  temp->next = completion_list;
  completion_list = temp;
}

/* Reverse the completion list passed in LIST, and
   return a pointer to the new head. */
COMP_ENTRY *
#if defined(__cplusplus) || defined(__STDC__)
reverse_list(COMP_ENTRY *list)
#else
reverse_list (list)
COMP_ENTRY *list;
#endif
{
  COMP_ENTRY *next;
  COMP_ENTRY *prev = (COMP_ENTRY *) NULL;

  while (list)
    {
      next = list->next;
      list->next = prev;
      prev = list;
      list = next;
    }
  return (prev);
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
scan_list(char *string, char *nodename)
#else
scan_list(string, nodename)
char *string, *nodename;
#endif
{
  /* The work part of find_menu_node and find_note_node. */

  COMP_ENTRY *temp = completion_list;

  while (temp)
    {
      if (strnicmp (string, temp->identifier, strlen (string)) == 0)
	{
	  (void)strcpy (nodename, temp->data);
	  return (true);
	}
      temp = temp->next;
    }
  return (false);
}
