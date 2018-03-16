
#ifndef intFUNCTIONTYPES_H
#define intFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining int if  is set: */
#define EMPTYHDR
#ifndef EMPTYHDR
#include ".h"
#endif
#undef EMPTYHDR

typedef int (*intCmpFctType) ELI_ARG((int, int));
/* Functions that compare two int values
 *   If the left argument is less than the right then on exit-
 *     intCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     intCmpFctType = 0
 *   Else on exit-
 *     intCmpFctType = 1
 ***/

typedef int (*intMapFct) ELI_ARG((int));
/* Functions that map one int value into another
 *   On exit-
 *     intMapFct = image of the argument under the map
 ***/

typedef int (*intSumFct) ELI_ARG((int, int));
/* Functions that combine two int values
 *   On exit-
 *     intSumFct = combination of the two arguments
 ***/

#endif
