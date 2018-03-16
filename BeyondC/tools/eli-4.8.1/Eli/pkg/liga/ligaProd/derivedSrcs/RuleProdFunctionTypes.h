
#ifndef RuleProdFUNCTIONTYPES_H
#define RuleProdFUNCTIONTYPES_H

#include "eliproto.h"

/* include header file defining RuleProd if RuleProd is set: */
#define EMPTYRuleProdHDR
#ifndef EMPTYHDR
#include "RuleProd.h"
#endif
#undef EMPTYRuleProdHDR

typedef int (*RuleProdCmpFctType) ELI_ARG((RuleProd, RuleProd));
/* Functions that compare two RuleProd values
 *   If the left argument is less than the right then on exit-
 *     RuleProdCmpFctType = -1
 *   Else if the arguments are equal then on exit-
 *     RuleProdCmpFctType = 0
 *   Else on exit-
 *     RuleProdCmpFctType = 1
 ***/

typedef RuleProd (*RuleProdMapFct) ELI_ARG((RuleProd));
/* Functions that map one RuleProd value into another
 *   On exit-
 *     RuleProdMapFct = image of the argument under the map
 ***/

typedef RuleProd (*RuleProdSumFct) ELI_ARG((RuleProd, RuleProd));
/* Functions that combine two RuleProd values
 *   On exit-
 *     RuleProdSumFct = combination of the two arguments
 ***/

#endif
