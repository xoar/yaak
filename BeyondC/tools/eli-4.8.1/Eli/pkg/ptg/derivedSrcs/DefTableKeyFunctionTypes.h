
#ifndef DefTableKeyFUNCTIONTYPES_H
#define DefTableKeyFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining DefTableKey if deftbl is set: */
#define EMPTYdeftblHDR
#ifndef EMPTYHDR
#include "deftbl.h"
#endif
#undef EMPTYdeftblHDR

typedef int (*DefTableKeyCmpFctType) ELI_ARG((DefTableKey, DefTableKey));
/* Functions that compare two DefTableKey values
 *   If the left argument is less than the right then on exit-
 *     DefTableKeyCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     DefTableKeyCmpFctType = 0
 *   Else on exit-
 *     DefTableKeyCmpFctType = 1
 ***/

typedef DefTableKey (*DefTableKeyMapFct) ELI_ARG((DefTableKey));
/* Functions that map one DefTableKey value into another
 *   On exit-
 *     DefTableKeyMapFct = image of the argument under the map
 ***/

typedef DefTableKey (*DefTableKeySumFct) ELI_ARG((DefTableKey, DefTableKey));
/* Functions that combine two DefTableKey values
 *   On exit-
 *     DefTableKeySumFct = combination of the two arguments
 ***/

#endif
