
#ifndef PatElemFUNCTIONTYPES_H
#define PatElemFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining PatElem if PatElem is set: */
#define EMPTYPatElemHDR
#ifndef EMPTYHDR
#include "PatElem.h"
#endif
#undef EMPTYPatElemHDR

typedef int (*PatElemCmpFctType) ELI_ARG((PatElem, PatElem));
/* Functions that compare two PatElem values
 *   If the left argument is less than the right then on exit-
 *     PatElemCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     PatElemCmpFctType = 0
 *   Else on exit-
 *     PatElemCmpFctType = 1
 ***/

typedef PatElem (*PatElemMapFct) ELI_ARG((PatElem));
/* Functions that map one PatElem value into another
 *   On exit-
 *     PatElemMapFct = image of the argument under the map
 ***/

typedef PatElem (*PatElemSumFct) ELI_ARG((PatElem, PatElem));
/* Functions that combine two PatElem values
 *   On exit-
 *     PatElemSumFct = combination of the two arguments
 ***/

#endif
