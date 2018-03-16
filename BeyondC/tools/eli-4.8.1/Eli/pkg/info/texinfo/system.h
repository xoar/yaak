/* $Id: system.h,v 1.2 1998/02/11 16:43:30 waite Exp $ */

#if defined(__cplusplus) || defined(__STDC__)
extern void *xmalloc(size_t bytes);
extern void *xrealloc(char *pointer, size_t bytes);
extern void background(char *cmd, char *file);
#else
extern void *xmalloc();
extern void *xrealloc();
extern void background();
#endif
