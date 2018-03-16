#ifndef OPTIONS_H
#define OPTIONS_H
/* $Id: options.h,v 1.2 2005/05/13 19:59:49 profw Exp $ */

#include "eliproto.h"

extern long Options[];

extern void InitOptions ELI_ARG((void));
/* Load options from a file
 *   On exit-
 *     Options is a (possibly empty) set containing the option characters
 ***/

#endif
