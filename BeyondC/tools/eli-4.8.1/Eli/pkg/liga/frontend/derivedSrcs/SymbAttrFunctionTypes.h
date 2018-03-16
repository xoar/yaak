
#ifndef SymbAttrFUNCTIONTYPES_H
#define SymbAttrFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining SymbAttr if SymbAttr is set: */
#define EMPTYSymbAttrHDR
#ifndef EMPTYHDR
#include "SymbAttr.h"
#endif
#undef EMPTYSymbAttrHDR

typedef int (*SymbAttrCmpFctType) ELI_ARG((SymbAttr, SymbAttr));
/* Functions that compare two SymbAttr values
 *   If the left argument is less than the right then on exit-
 *     SymbAttrCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     SymbAttrCmpFctType = 0
 *   Else on exit-
 *     SymbAttrCmpFctType = 1
 ***/

typedef SymbAttr (*SymbAttrMapFct) ELI_ARG((SymbAttr));
/* Functions that map one SymbAttr value into another
 *   On exit-
 *     SymbAttrMapFct = image of the argument under the map
 ***/

typedef SymbAttr (*SymbAttrSumFct) ELI_ARG((SymbAttr, SymbAttr));
/* Functions that combine two SymbAttr values
 *   On exit-
 *     SymbAttrSumFct = combination of the two arguments
 ***/

#endif
