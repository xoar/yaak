/* $Id: option.h,v 1.2 1994/06/22 06:22:38 waite Exp $ */

extern OPTION options[];

#if defined(__cplusplus) || defined(__STDC__)
extern void init_options(INIT_OPTION *opts);
/* Initialize the option data structure
 ***/
#else
extern void init_options();
#endif
