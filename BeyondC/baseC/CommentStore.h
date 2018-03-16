#ifndef COMMENTSTORE_H
#define COMMENTSTORE_H

#include "csm.h" /*ERROR: when you add spaces here it crash????*/

extern int commentVar;

extern void storeComment
      (const char *start, int length, int *syncode, int *intrinsic);

extern int getComment ();

#endif