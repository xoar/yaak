
#ifndef SYMBOL_H
#define SYMBOL_H

#include "obstack.h"
#include "deftbl.h"
#include "eliproto.h"

extern Obstack mapobstack;

#define MapObstack      (&mapobstack)

typedef struct Symbol {
        int Class;
        DefTableKey Key;
} *SymbolP;

#define SymbolKeySet(s,k)       (((SymbolP)(s))->Key = (k))
#define SymbolKeyGet(s)         (((SymbolP)(s))->Key)
#define SymbolClassSet(s,c)     (((SymbolP)(s))->Class = (c))
#define SymbolClassGet(s)       (((SymbolP)(s))->Class)
#define DAPTO_RESULTSymbolP(e)  DAPTO_RESULT_PTR(e)
#define DAPTO_ARGSymbolP(e)     DAPTO_ARG_PTR(e, SymbolP)

extern SymbolP CreateSymbol ELI_ARG((void));

#endif
