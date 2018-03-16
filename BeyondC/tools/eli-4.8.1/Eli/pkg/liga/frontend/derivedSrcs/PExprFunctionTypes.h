
#ifndef PExprFUNCTIONTYPES_H
#define PExprFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining PExpr if ExprRepr is set: */
#define EMPTYExprReprHDR
#ifndef EMPTYHDR
#include "ExprRepr.h"
#endif
#undef EMPTYExprReprHDR

typedef int (*PExprCmpFctType) ELI_ARG((PExpr, PExpr));
/* Functions that compare two PExpr values
 *   If the left argument is less than the right then on exit-
 *     PExprCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     PExprCmpFctType = 0
 *   Else on exit-
 *     PExprCmpFctType = 1
 ***/

typedef PExpr (*PExprMapFct) ELI_ARG((PExpr));
/* Functions that map one PExpr value into another
 *   On exit-
 *     PExprMapFct = image of the argument under the map
 ***/

typedef PExpr (*PExprSumFct) ELI_ARG((PExpr, PExpr));
/* Functions that combine two PExpr values
 *   On exit-
 *     PExprSumFct = combination of the two arguments
 ***/

#endif
