
#ifndef SymbolPFUNCTIONTYPES_H
#define SymbolPFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining SymbolP if symbol is set: */
#define EMPTYsymbolHDR
#ifndef EMPTYHDR
#include "symbol.h"
#endif
#undef EMPTYsymbolHDR

typedef int (*SymbolPCmpFctType) ELI_ARG((SymbolP, SymbolP));
/* Functions that compare two SymbolP values
 *   If the left argument is less than the right then on exit-
 *     SymbolPCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     SymbolPCmpFctType = 0
 *   Else on exit-
 *     SymbolPCmpFctType = 1
 ***/

typedef SymbolP (*SymbolPMapFct) ELI_ARG((SymbolP));
/* Functions that map one SymbolP value into another
 *   On exit-
 *     SymbolPMapFct = image of the argument under the map
 ***/

typedef SymbolP (*SymbolPSumFct) ELI_ARG((SymbolP, SymbolP));
/* Functions that combine two SymbolP values
 *   On exit-
 *     SymbolPSumFct = combination of the two arguments
 ***/

#endif
