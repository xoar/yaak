/* $Id: option_sw.h,v 1.2 1994/06/22 06:22:38 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void OptionButton(Panel_item item, Event *event);
/* Popup an option window and allow the user to set the options.
 *    On entry-
 *       item is the Panel_item which was clicked on
 *       event is the click
 */
#else
extern void OptionButton();
#endif

extern void OptionFinl();
/* Destroy the option popup if there is one. */
