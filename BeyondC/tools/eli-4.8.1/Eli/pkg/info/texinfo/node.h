/* $Id: node.h,v 1.3 1998/02/11 16:43:20 waite Exp $ */

extern boolean indirect;	/* If true, the tag table is indirect. */

/* the filename of the currently loaded info file. */
extern char current_info_file[];

/* the nodename of the node the user is looking at. */
extern char current_info_node[];

/* the last file actually loaded.  Not the same as current info file. */
extern char last_loaded_info_file[];

/* offsets in info_file of top and bottom of current_info_node. */
extern size_t nodetop, nodebot;

/* offsets in info_file of the data line of current_info_node. */
/* if no data line is there, datatop == nodetop */
extern size_t datatop;

extern int nodelines;		/* number of lines in this node. */
extern char current_info_dir[];	/* directory of current_info_file */

extern char *info_file;		/* buffer for the info file. */
extern size_t info_buffer_len;	/* length of the above buffer. */

extern size_t pagetop;	/* offset in the buffer of the current pagetop. */
extern size_t pagebot;	/* offset of the character beyond the current page. */


#if defined(__cplusplus) || defined(__STDC__)
extern boolean get_node(char *nodename, char *filename, boolean popping);
/* Make a specific node current
 *    On entry-
 *       nodename=name of the desired node
 *       filename=file containing the text of the desired node
 *       popping=TRUE if the request is due to popping the node stack
 *    If the text of the node is available then on exit-
 *       get_node=TRUE
 *       current_info_node=nodename
 *    Else on exit-
 *       get_node=FALSE
 *       current_info_node is unchanged
 ***/
#else
extern boolean get_node();
#endif

extern boolean last_node();
/* Move to the node from which the current node was reached
 ***/


extern boolean print_current_node();
/* Print the current node
 *    If the print was successful then on exit-
 *       print_current_node=true
 *    Else on exit-
 *       print_current_node=false
 ***/
