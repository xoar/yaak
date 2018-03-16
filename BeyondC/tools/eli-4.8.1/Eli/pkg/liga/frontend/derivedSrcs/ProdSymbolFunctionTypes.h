
#ifndef ProdSymbolFUNCTIONTYPES_H
#define ProdSymbolFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining ProdSymbol if Prod is set: */
#define EMPTYProdHDR
#ifndef EMPTYHDR
#include "Prod.h"
#endif
#undef EMPTYProdHDR

typedef int (*ProdSymbolCmpFctType) ELI_ARG((ProdSymbol, ProdSymbol));
/* Functions that compare two ProdSymbol values
 *   If the left argument is less than the right then on exit-
 *     ProdSymbolCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     ProdSymbolCmpFctType = 0
 *   Else on exit-
 *     ProdSymbolCmpFctType = 1
 ***/

typedef ProdSymbol (*ProdSymbolMapFct) ELI_ARG((ProdSymbol));
/* Functions that map one ProdSymbol value into another
 *   On exit-
 *     ProdSymbolMapFct = image of the argument under the map
 ***/

typedef ProdSymbol (*ProdSymbolSumFct) ELI_ARG((ProdSymbol, ProdSymbol));
/* Functions that combine two ProdSymbol values
 *   On exit-
 *     ProdSymbolSumFct = combination of the two arguments
 ***/

#endif
