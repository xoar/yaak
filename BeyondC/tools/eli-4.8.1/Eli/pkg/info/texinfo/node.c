static char rcsid[] = "$Id: node.c,v 1.21 2009/09/18 12:01:43 asloane Exp $";

/* node.c

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
/*			Getting Nodes				    */
/*								    */
/* **************************************************************** */

#include "info.h"
#include "file.h"
#include "node.h"
#include "util.h"
#include "system.h"

INDIRECT_INFO indirect_list[MAX_INDIRECT_FILES];

boolean indirect = false;	/* If true, the tag table is indirect. */
size_t indirect_top;

char *tag_table = NULL;		/* Pointer to the start of a tag table */
                                /* NULL to show none. */
size_t tag_buffer_len;		/* length of the above buffer. */

NODEINFO *Info_History = NULL;	/* the info history list. */

/* the filename of the currently loaded info file. */
char current_info_file[FILENAME_LEN];

/* the nodename of the node the user is looking at. */
char current_info_node[NODENAME_LEN];

/* the last file actually loaded.  Not the same as current info file. */
char last_loaded_info_file[FILENAME_LEN];

/* offsets in info_file of top and bottom of current_info_node. */
size_t nodetop, nodebot;

/* offsets in info_file of the data line of current_info_node. */
/* if no data line is there, datatop == nodetop */
size_t datatop;

int nodelines;				/* number of lines in this node. */
char current_info_dir[FILENAME_LEN];	/* directory of current_info_file */

char *info_file = NULL;			/* buffer for the info file. */
size_t info_buffer_len;			/* length of the above buffer. */

size_t pagetop;		/* offset in the buffer of the current pagetop. */
size_t pagebot;		/* offset of the character beyond the current page. */

/* Get the bounds for this node.  NODETOP points to the start of the
   node. Scan forward looking for info_separator_char, and remember
   that in NODEBOT. */
static void
get_node_extent()
{
  size_t ndx = nodetop;
  int character;

  boolean do_it_till_end = (strcmp (current_info_node, "*") == 0);

  nodelines = 0;

again:
  while ((ndx < info_buffer_len) &&
	 ((character = info_file[ndx]) != info_separator_char))
    {
      if (character == '\n')
	nodelines++;
      ndx++;
    }
  if (do_it_till_end && ndx != info_buffer_len)
    {
      ndx++;
      goto again;
    }
  nodebot = ndx;
}

static int
#if defined(__cplusplus) || defined(__STDC__)
find_node_start(size_t *start)
#else
find_node_start(start) size_t *start;
#endif
/* Locate the next node in the current search_buffer
 *   On entry-
 *     *start is the starting index for the search
 *   If a node is found then on exit-
 *     find_node_start=1
 *     *start indexes the beginning of the next node
 *   Else on exit-
 *     find_node_start=0
 *     *start is unchanged
 ***/
{
  return (search_forward(start_of_node_string, start));
}

static int
#if defined(__cplusplus) || defined(__STDC__)
find_node_in_tag_table(char *nodename, size_t *offset)
#else
find_node_in_tag_table(nodename, offset) char *nodename; size_t *offset;
#endif
/* Locate a node in the tag table
 *   On entry-
 *     nodename is the node to be found
 *     *offset is the starting index for the search
 *   If a node is found then on exit-
 *     find_node_in_tag_table=1
 *     *offset indexes the beginning of the next node
 *   Else on exit-
 *     find_node_in_tag_table=0
 *     *offset is undefined
 ***/
{ set_search_constraints (tag_table, tag_buffer_len);

  for (;;) {
    if (!search_forward(NODE_ID, offset)) return 0;
    *offset = skip_whitespace(*offset + strlen(NODE_ID));
    if (strnicmp (tag_table + *offset, nodename, strlen (nodename)) == 0 &&
	*(tag_table + *offset + strlen (nodename)) == '\177')
      return 1;
    }
}

/* Find NODENAME in INFO_FILE. */
static int
#if defined(__cplusplus) || defined(__STDC__)
find_node_in_file(char *nodename, size_t *offset)
#else
find_node_in_file(nodename, offset) char *nodename; size_t *offset;
#endif
/* Locate a node in the info file
 *   On entry-
 *     nodename is the node to be found
 *     *offset is the starting index for the search
 *   If a node is found then on exit-
 *     find_node_in_file=1
 *     *offset indexes the beginning of the next node
 *   Else on exit-
 *     find_node_in_file=0
 *     *offset is undefined
 ***/
{ size_t temp;

  set_search_constraints (info_file, info_buffer_len);

  for (;;) {
    if (!find_node_start(offset)) return 0;
    temp = forward_lines (1, *offset);
    if (temp == *offset) return 0;	/* At last line now, just a node start. */
    *offset = temp;
    if (string_in_line(NODE_ID, offset)) {
      temp = skip_whitespace(*offset + strlen(NODE_ID));
      if (strnicmp (info_file + temp, nodename, strlen (nodename)) == 0) {
	int check_exact = *(info_file + temp + strlen (nodename));
	if (check_exact == '\t'
	    || check_exact == ','
	    || check_exact == '.'
	    || check_exact == '\n') {
          *offset = temp;
          return 1;
        }
      }
    }
  }
}

/* A node name looks like:
   Node: nodename with spaces but not a comma,
or Node: (filename-containing-node)node-within-file
or Node: (filename)

   The latter case implies a nodename of "Top".  All files are
   supposed to have one.

   Lastly, the nodename specified could be "*", which specifies the
   entire file. */

static boolean
#if defined(__cplusplus) || defined(__STDC__)
get_info_file(char *filename, boolean remember_name)
#else
get_info_file(filename, remember_name)
char *filename; boolean remember_name;
#endif
{
  /* Load FILENAME.  If REMEMBER_NAME is true, then remember the loaded filename
     in CURRENT_INFO_FILE.  In either case, remember the name of this
     file in LAST_LOADED_INFO_FILE. */

  FILE *input_stream;
  struct stat file_info;
  size_t pointer;
  int result;
  char tempname[FILENAME_LEN];
  char *cp;

  /* Get real filename. */
  (void)strcpy (tempname, pathname (filename));

  /* See if the file exists. */
  if ((result = stat (tempname, &file_info)) != 0)
    {
      /* Try again, this time with the name in lower-case. */
      char temp_tempname[FILENAME_LEN];
      int i;

      for (i = 0; (temp_tempname[i] = to_lower (tempname[i])); i++);
      /* Get real filename again. AMS */
      (void)strcpy (temp_tempname, pathname (temp_tempname));

      result = stat (temp_tempname, &file_info);
      if (!result)
	(void)strcpy (tempname, temp_tempname);
    }

  /* See if this file is the last loaded one. */
  if (!result && (strcmp (last_loaded_info_file, tempname) == 0))
    {
      return (true);		/* Okay, the file is loaded. */
    }

  /* Now try to open the file. */
  if (result || (input_stream = fopen (tempname, "r")) == NULL)
    return (false);

  /* If we already have a file loaded, then free it first. */
  if (info_file)
    {
      free (info_file);

      if (!indirect)
	{
	  /* Then the tag table is also no longer valid. */
	  tag_table = (char *) NULL;
	}
    }

  /* Read the contents of the file into a new buffer. */

  info_file = (char *)xmalloc((size_t)(file_info.st_size + 1));
  info_buffer_len = file_info.st_size;
  (void)fread (info_file, 1, info_buffer_len, input_stream);
  info_file[info_buffer_len] = '\0';
  (void)fclose (input_stream);
  (void)strcpy (last_loaded_info_file, tempname);
  (void)strcpy( current_info_dir, tempname );
  cp = strrchr( current_info_dir, '/' );
  if (cp == NULL)
    cp = current_info_dir;
  else
    cp++;
  *cp = '\0';

if (remember_name)
    {
      (void)strcpy (current_info_file, tempname);
      if (indirect)
	{
	  int ndx;
	  indirect = false;
	  free (tag_table);
	  for (ndx = 0; ndx < MAX_INDIRECT_FILES &&
	       indirect_list[ndx].filename != (char *) NULL;
	       ndx++)
	    {
	      free (indirect_list[ndx].filename);
	      indirect_list[ndx].filename = (char *) NULL;
	    }
	}
    }
  else
    return (true);

  /* The file has been read, and we don't know anything about it.
     Find out if it contains a tag table. */

  tag_table = NULL;		/* assume none. */
  indirect = false;
  tag_buffer_len = 0;

  set_search_constraints (info_file, info_buffer_len);

  /* Go to the last few lines in the file. */
  pointer = back_lines (8, info_buffer_len);
  if (search_forward (TAG_TABLE_END_STRING, &pointer)) {
    /* Then there is a tag table.  Find the start of it, and remember that. */
    if (!search_backward(TAG_TABLE_BEG_STRING, &pointer))

    /* Handle error for malformed info file. */
	display_error ("Start of tag table not found!");
    else
	{
	/* No problem.  If this file is an indirect file, then the contents
	   of the tag table must remain in RAM the entire time.  Otherwise,
	   we can flush the tag table with the file when the file is flushed.
	   So, if indirect, remember that, and copy the table to another place.*/

	size_t indirect_check = forward_lines(2, pointer);

	tag_table = info_file + pointer;
	tag_buffer_len = info_buffer_len - pointer;

	/* Shorten the search constraints. */
	info_buffer_len = pointer;

	if (looking_at ("(Indirect)\n", indirect_check))
	  {

	    /* We have to find the start of the indirect files information. */
	    tag_table = (char *) xmalloc((size_t)tag_buffer_len);

	    memcpy(tag_table, &info_file[indirect_check], tag_buffer_len);

	    /* Find the list of filenames. */
            indirect_top = indirect_check;
	    if (!search_backward("Indirect:\n", &indirect_top))
		{
		free (tag_table);
		tag_table = (char *) NULL;
		display_error ("Start of INDIRECT tag table not found!");
		return (false);
		}

	    /* Remember the filenames, and their byte offsets. */
	    {
		/* Index into the filename/offsets array. */
		int ndx = 0;
		char temp_filename[FILENAME_LEN];
		int temp_first_byte;

		info_buffer_len = indirect_top;

		/* For each line, scan the info into globals.Then save
	         the information in the INDIRECT_INFO structure. */

		while (info_file[indirect_top] != info_separator_char &&
		     ndx < MAX_INDIRECT_FILES)
		{
		  indirect_top = forward_lines (1, indirect_top);
		  if (info_file[indirect_top] == info_separator_char)
		    break;

		  /* Ignore blank lines. */
		  if (info_file[indirect_top] == '\n')
		    continue;

		  (void)sscanf (&info_file[indirect_top], "%s%d",
				temp_filename, &temp_first_byte);

		  if (strlen (temp_filename))
		    {
			temp_filename[strlen (temp_filename) - 1] = '\0';
			indirect_list[ndx].filename =
			(char *)xmalloc((size_t)(strlen(temp_filename)+1));
			(void)strcpy (indirect_list[ndx].filename,
				    temp_filename);
			indirect_list[ndx].first_byte = temp_first_byte;
			ndx++;
		    }
		}
		/* Terminate the table. */
		if (ndx == MAX_INDIRECT_FILES)
		{
		  display_error ("Sorry, the INDIRECT file array isn't large enough.");
		  ndx--;
		}
		indirect_list[ndx].filename = (char *) NULL;
	    }
	    indirect = true;
	  }
	}
    }
  return (true);
}

/* Save the current filename, nodename, and position on the history list.
   We prepend. */
static boolean
#if defined(__cplusplus) || defined(__STDC__)
push_node(char *filename, char *nodename,
          size_t page_position, size_t node_position, size_t data_position)
#else
push_node (filename, nodename, page_position, node_position, data_position)
char *filename, *nodename; size_t page_position, node_position, data_position;
#endif
{
  NODEINFO *newnode = (NODEINFO *) xmalloc (sizeof (NODEINFO));

  newnode->next = Info_History;

  newnode->filename = (char *)xmalloc((size_t)(strlen(filename) + 1));
  (void)strcpy (newnode->filename, filename);

  newnode->nodename = (char *)xmalloc((size_t)(strlen(nodename) + 1));
  (void)strcpy (newnode->nodename, nodename);

  newnode->pagetop = page_position;
  newnode->nodetop = node_position;
  newnode->datatop = data_position;

  Info_History = newnode;
  return (true);
}

static boolean
#if defined(__cplusplus) || defined(__STDC__)
pop_node(char *filename, char *nodename,
  size_t *ntop, size_t *ptop, size_t *dtop)
#else
pop_node (filename, nodename, ntop, ptop, dtop)
char *filename, *nodename; size_t *ntop, *ptop, *dtop;
#endif
{
  /* Pop one node from the node list, leaving the values in
     passed variables. */

  if (Info_History->next == (NODEINFO *) NULL) {
      display_error ("At beginning of history now!");
      return (false);
  } else {
      NODEINFO *releaser = Info_History;

      if (strcmp (Info_History->filename, last_loaded_info_file) != 0)
	last_loaded_info_file[0] = '\0';	/* Force the reloading of the file. */
      (void)strcpy (filename, Info_History->filename);
      (void)strcpy (nodename, Info_History->nodename);
      *ptop = Info_History->pagetop;
      *ntop = Info_History->nodetop;
      *dtop = Info_History->datatop;
      free (Info_History->nodename);
      free (Info_History->filename);
      Info_History = Info_History->next;
      free ((char *)releaser);
      return (true);
    }
}

/**/
static void
backout()
/* Back out of a failed attempt to get a node
 *    On exit-
 *       The node from which failed attempt was made is current
 **/
{
  char internal_filename[FILENAME_LEN];
  char internal_nodename[NODENAME_LEN];

  current_info_file[0] = '\0';
  current_info_node[0] = '\0';
  last_loaded_info_file[0] = '\0';
  (void)pop_node (internal_filename, internal_nodename,
                    &nodetop, &pagetop, &datatop);
  (void)get_node (internal_filename, internal_nodename, true);
}

/**/
static void
#if defined(__cplusplus) || defined(__STDC__)
node_not_in_file(char *nodename, char *filename)
#else
node_not_in_file(nodename, filename)
char *nodename, *filename;
#endif
/* Report that a node is not in a file
 *    On entry-
 *       nodename=name of the node sought
 *       filename=name of the file being searched
 *    On exit-
 *       An error has been reported
 *       The node from which failed attempt was made is current
 **/
{
  char errbuf[BUFSIZ];

  (void)sprintf(errbuf,
    "Sorry, unable to find the node \"%s\" in the file \"%s\".",
    nodename, filename);
  display_error(errbuf);
  backout();
}

/***/
boolean
#if defined(__cplusplus) || defined(__STDC__)
get_node(char *filename, char *nodename, boolean popping)
#else
get_node(filename, nodename, popping)
char *filename, *nodename; boolean popping;
#endif
/* Make a specific node current
 *    On entry-
 *       filename=file containing the text of the desired node
 *       nodename=name of the desired node
 *       popping=TRUE if the request is due to popping the node stack
 *    If the text of the node is available then on exit-
 *       get_node=TRUE
 *       current_info_node=nodename
 *    Else on exit-
 *       get_node=FALSE
 *       current_info_node is unchanged
 *       An error report has been issued
 ***/
{
  size_t pointer;
  char internal_filename[FILENAME_LEN];
  char internal_nodename[NODENAME_LEN];

  if (nodename && *nodename) {
    /* Clean up a node name supplied by the client */
    char ch, *p;

    if (*nodename == '(') {
      /* Nodename looks like: (filename)nodename, or worse: (filename). */

      filename = p = internal_filename;
      for (nodename++; (ch = *nodename) && ch != ')'; nodename++) *p++ = ch;
      *p = '\0';
      if (ch == ')') nodename++;
      while (((ch = *nodename) && ch == ' ') || ch == '\n') nodename++;
    }
    for (p = internal_nodename;
	(ch = *nodename) && ch != '.' && ch != ',' && ch != '\t';
        nodename++) {
      if (ch != '\n' && ch != ' ') *p++ = ch;
      else {
        *p++ = ' ';
        while (nodename[1] == ' ') nodename++;
      }
    }
    *p = '\0';
    nodename = internal_nodename;
  }

  if (!popping)
    (void)push_node (current_info_file, current_info_node, pagetop, nodetop,
		     datatop);

  if (!nodename || !*nodename) {
    nodename = internal_nodename;
    (void)strcpy (nodename, "Top");
  }

  if (!filename || !*filename) {
    filename = internal_filename;
    (void)strcpy (filename, current_info_file);
  }

  if (!*filename) (void)strcpy (filename, "dir");

  if (!get_info_file (filename, true)) {
    char errbuf[BUFSIZ];
    if (popping) return (false);
    (void)sprintf(errbuf, "Sorry, unable to find file \"%s\".", filename);
    display_error(errbuf);
    backout();
    return(false);
  }

  if (strcmp (nodename, "*") == 0) {
    /* The "node" that we want is the entire file. */
    pointer = 0;
    goto found_node;
  }

  /* If we are using a tag table, see if we can find the nodename in it. */
  if (tag_table) {
    pointer = 0;
    if (!find_node_in_tag_table(nodename, &pointer)) {
      if (popping) return (false);	/* second time through. */
      node_not_in_file(nodename, filename);
      return (false);
    }

    while (tag_table[pointer] != '\177') pointer++;
    (void)sscanf (&tag_table[pointer + 1], "%lu", (unsigned long *)(&pointer));

      /* Okay, we have a position pointer.  If this is an indirect file,
         then we should look through the indirect_list for the first
         element.first_byte which is larger than this.  Then we can load
         the specified file, and win. */
    if (indirect) {
      /* Find the filename for this node. */
      int ndx;
      for (ndx = 0;
	  ndx < MAX_INDIRECT_FILES
	    && indirect_list[ndx].filename != (char *) NULL;
	  ndx++) {
	if (indirect_list[ndx].first_byte > pointer) break;
      }
      if (!get_info_file (indirect_list[ndx - 1].filename, true)) {
	node_not_in_file(nodename, filename);
	return(false);
      }

      pointer -= indirect_list[ndx - 1].first_byte;
      /* Here is code to compensate for the header of an indirect file. */
      { size_t tt = 0; if (find_node_start(&tt)) pointer += tt; }

    } else {
	  /* This tag table is *not* indirect.  The filename of the file
	     containing this node is the same as the current file.  The
	     line probably looks like:
	     File: info,  Node: Checking25796 */
    }
  } else {
      /* We don't have a tag table.  The node can only be found by
         searching this file in its entirety.  */
      (void)get_info_file (filename, true);
      pointer = 0;
  }

  /* Search this file, using pointer as a good guess where to start. */
  /* This is the same number that RMS used.  It might be right or wrong. */
  if (pointer > 1000) pointer -= 1000; else pointer = 0;

  if (!find_node_in_file(nodename, &pointer)) {
    node_not_in_file(nodename, filename);
    return(false);
  }

  /* We found the node in it's file.  Remember exciting information. */

found_node:
  pointer = back_lines(0, pointer);
  nodetop = pagetop = datatop = pointer;

  /* ams: we ignore the first line of the node if it starts with 'File:'
     This is because this info is displayed in the modeline now, so that it
     can be visible all of the time. (I suppose the second line of the node
     is always blank -- wmw.) */
  if (strncmp( &(info_file[nodetop]), "File:", 5) == 0) {
    while (info_file[nodetop++] != '\n') ;
    while (info_file[nodetop++] != '\n') ;
    pagetop = nodetop;
  }

  (void)strcpy (current_info_node, nodename);
  (void)strcpy (current_info_file, filename);
  get_node_extent ();
  return (true);
}

/***/
boolean
last_node()
/* Move to the node from which the current node was reached
 ***/
{
  /* Move to the last node in the history list */

  char filename[FILENAME_LEN], nodename[NODENAME_LEN];
  size_t ptop, ntop, dtop;

  if (pop_node (filename, nodename, &ntop, &ptop, &dtop) &&
        get_node (filename, nodename, true))
    {
      pagetop = ptop;
      return(true);
    }
  return(false);
}

/***/
boolean
print_current_node()
/* Print the current node
 *    If the print was successful then on exit-
 *       print_current_node=true
 *    Else on exit-
 *       print_current_node=false
 ***/
{
  boolean flag;
  char *tempname;
  size_t i;
  FILE *output_stream;

  tempname = make_temp_filename("infoprint");
  output_stream = fopen(tempname, "w");
  if (output_stream == (FILE *)NULL) {
    file_error(tempname);
    return(false);
  }

  for (i = nodetop; i < nodebot && i < info_buffer_len; i++) {
    int c = info_file[i];
    if (c < 0x020 && !(strchr("\n\t\f", c))) (void)putc('^', output_stream);
    (void)putc(info_file[i], output_stream);
  }

  (void)fclose (output_stream);

  flag = printfile(tempname);
  (void)deletefile(tempname);
  free(tempname);

  return(flag);
}
