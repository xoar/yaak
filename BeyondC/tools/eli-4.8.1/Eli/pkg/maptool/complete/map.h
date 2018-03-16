

#ifndef MAP_H
#define MAP_H

#include "symbol.h"
#include "SymbolPList.h"
#include "intList.h"
#include "deftbl.h"
#include "err.h"
#include "oiladt2.h"
#include "eliproto.h"

/* Do not change these values.  It is important that they stay this way. */
#define T_TERM          0
#define T_NONTERM       1
#define T_ERROR         2       /* used if nonterms and terms are mixed */
                                /* in an equivalence class: cannot be   */
                                /* 0 or 1                               */

#define ASSIGN(x,y)     ((x)=(y))

#define SymbolPValid(s) ((s) != NULL)

extern int MapQChains;

extern int DefTableKeyCmp ELI_ARG((DefTableKey a, DefTableKey b));
extern int intCmp ELI_ARG((int a, int b));
extern SymbolP GetNthNT ELI_ARG((SymbolPList list, int n));
extern tOilSetSig CreateSignature ELI_ARG((SymbolPList rhs));
extern DefTableKey FindConRule ELI_ARG((DefTableKey lhs, SymbolPList rhs));
extern int RuleCmp ELI_ARG((DefTableKey rule1, DefTableKey rule2, int map));

#endif

