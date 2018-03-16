/* $Id: complain_sw.h,v 1.2 1994/06/22 06:13:14 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void ComplainButton(Panel_item item, Event *event);
/* Popup a complaint window and allow the user to send a message.
 *    On entry-
 *       item is the Panel_item which was clicked on
 *       event is the click
 */
#else
extern void ComplainButton();
#endif

extern void ComplainFinl();
/* Destroy the complain popup if there is one. */

