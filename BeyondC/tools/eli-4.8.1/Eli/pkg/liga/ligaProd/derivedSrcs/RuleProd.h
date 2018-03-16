
#ifndef RULEPROD_H
#define RULEPROD_H

#include "args.h"
#include "deftbl.h"
#include "err.h"
#include "ProdSymbolList.h"

typedef struct
{ DefTableKey    rulekey;
  ProdSymbolList prod;
  int            islistof;
  CoordPtr       coord;
} _RElem, *RuleProd;

#define NoRuleProd ((RuleProd)0)
#define RuleKeyOfRuleProd(r) ((r)->rulekey)

#endif
