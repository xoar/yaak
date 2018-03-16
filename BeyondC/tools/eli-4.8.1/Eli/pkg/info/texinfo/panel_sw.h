/* $Id: panel_sw.h,v 1.3 1994/06/22 06:22:38 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void ControlInit(Frame frame);
/* Create a subwindow to display the controls
 *    On entry-
 *       frame is the parent of the control display
 ***/

extern void ControlButton(int nodetop);
/* Set up the controls that are valid for the current node
 *    On entry-
 *       info_file[nodetop] is the first character of the node's mode line
 ***/

extern void print_error(char *buf);
/* Inform the user of an error via the message area
 *    On entry-
 *       buf=message to be displayed
 ***/
#else
extern void ControlInit();
extern void ControlButton();
extern void print_error();
#endif

extern void EchoClear();
/* Clear the control panel's message area
 ***/

extern void ding();
/* Provide an audible signal to the user
 ***/
