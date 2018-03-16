/* $Id: text_sw.h,v 1.4 1994/06/22 06:22:38 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void NodeInit(Frame frame);
/* Create a subwindow to display the text
 *    On entry-
 *       frame=parent of the text display
 ***/


extern void NodeDisplay(char *buf, int len);
/* Display text for the current node
 *    On entry-
 *       buf[0..len-1]=text to be displayed
 ***/

extern boolean NodeNote(char *str, int picked);
/* Follow a possible cross-reference selected from the current node
 *    On entry-
 *       str=a text segment guaranteed to contain the entire reference
 *          (if one is present)
 *       str[picked]=character actually marked by the selection
 *    If a reference is present, and the node is accessible, then on exit-
 *       NodeNote=true
 *       The referenced node has been displayed
 *    Else if a reference is present then on exit-
 *       NodeNote=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeNote=false
 ***/

extern boolean NodeMenu(char *str, int picked);
/* Follow a possible menu item selected from the current node
 *    On entry-
 *       str=a text segment guaranteed to contain the entire menu item
 *          (if one is present)
 *       str[picked]=character actually marked by the selection
 *    If a menu item is present, and the node is accessible, then on exit-
 *       NodeMenu=true
 *       The referenced node has been displayed
 *    Else if a menu item is present then on exit-
 *       NodeMenu=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeMenu=false
 ***/

extern void SearchNode(char *str);
/* Search for a string in the current node
 *    On entry-
 *       str=a string to be searched for
 *    If the string is present in the node starting at the position of the
 * 	 carat, then on exit-
 *          The line with the string is at the top of the page.
 *	    The carat points to the end of the string.
 */
#else
extern void NodeInit();
extern void NodeDisplay();
extern boolean NodeNote();
extern boolean NodeMenu();
extern void SearchNode();
#endif

extern void NodeClear();
/* Delete the current node's text
 ***/

extern void display_page();
/* Display a node with the appropriate buttons
 *    On entry-
 *       info_file[datatop..nodetop-1]=mode information
 *       info_file[nodetop..nodebot-1]=text
 ***/
