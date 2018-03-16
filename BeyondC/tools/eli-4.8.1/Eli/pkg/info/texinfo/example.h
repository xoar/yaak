/* $Id */

extern boolean get_eg_file_list();

#if defined(__cplusplus) || defined(__STDC__)
extern boolean set_up_run(boolean *, char *, char **);
extern void set_up_edit(boolean *, char *, char *);
#else
extern boolean set_up_run();
extern void set_up_edit();
#endif
