/* $Id: list.h,v 1.1 1994/06/22 06:07:34 waite Exp $ */

extern COMP_ENTRY *completion_list;

#if defined(__cplusplus) || defined(__STDC__)
extern void add_completion(char *identifier, char *data);
extern COMP_ENTRY *reverse_list(COMP_ENTRY *list);
extern boolean scan_list(char *string, char *nodename);
#else
extern void add_completion();
extern COMP_ENTRY *reverse_list();
extern boolean scan_list();
#endif

extern void free_completion_list();
