/* $Id: print_sw.h,v 1.2 1994/06/22 06:22:38 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void PrintNodeButton(Panel_item item, Event *event);
/* Send the current node to a printer with confirmation from the user.
 *    On entry-
 *       item is the Panel_item which was clicked on
 *       event is the click
 */

extern void PrintManualButton(Panel_item item, Event *event);
/* Send the current manual to a printer with confirmation from the user.
 *    On entry-
 *       item is the Panel_item which was clicked on
 *       event is the click
 */
#else
extern void PrintNodeButton();
extern void PrintManualButton();
#endif
