/* $Id: menunote.h,v 1.1 1994/08/08 03:04:53 waite Exp $ */

/* Number of items that the current menu has. */
extern int the_menu_size;

/* Build a completion list of menuname/nodename for each
   line in this node that is a menu item. */
extern boolean build_menu();

/* Build a completion list of notename/nodename for each
   line in this node that is a cross-reference item. */
extern boolean build_notes();

#if defined(__cplusplus) || defined(__STDC__)
extern boolean get_menu(int);
extern boolean find_menu_node(char *, char *);
extern boolean find_note_node(char *, char *);
#else
extern boolean get_menu();
extern boolean find_menu_node();
extern boolean find_note_node();
#endif
