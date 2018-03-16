
#ifndef ElementFUNCTIONTYPES_H
#define ElementFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining Element if Element is set: */
#define EMPTYElementHDR
#ifndef EMPTYHDR
#include "Element.h"
#endif
#undef EMPTYElementHDR

typedef int (*ElementCmpFctType) ELI_ARG((Element, Element));
/* Functions that compare two Element values
 *   If the left argument is less than the right then on exit-
 *     ElementCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     ElementCmpFctType = 0
 *   Else on exit-
 *     ElementCmpFctType = 1
 ***/

typedef Element (*ElementMapFct) ELI_ARG((Element));
/* Functions that map one Element value into another
 *   On exit-
 *     ElementMapFct = image of the argument under the map
 ***/

typedef Element (*ElementSumFct) ELI_ARG((Element, Element));
/* Functions that combine two Element values
 *   On exit-
 *     ElementSumFct = combination of the two arguments
 ***/

#endif
