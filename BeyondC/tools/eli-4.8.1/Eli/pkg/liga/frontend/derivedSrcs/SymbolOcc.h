
#ifndef SYMBOLOCC_H
#define SYMBOLOCC_H

#include "args.h"
#include "GrammarRules.h"
#include "err.h"

extern ProdSymbol FindHEADSymbolOcc
   FEARGS ((RuleProd rule));

extern ProdSymbol FindTAILSymbolOcc
   FEARGS ((RuleProd rule));

extern ProdSymbol FindSymbolOcc
   FEARGS ((RuleProd rule, DefTableKey symbol, int index, CoordPtr coord));
extern ProdSymbol FindSymbolRef
   FEARGS ((RuleProd rule, DefTableKey symbol, int index));
extern int CountSymbolRef
   FEARGS ((RuleProd rule, DefTableKey symbol));

#endif
