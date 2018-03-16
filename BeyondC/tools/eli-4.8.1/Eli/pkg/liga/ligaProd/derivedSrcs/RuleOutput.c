
#include "RuleOutput.h"
#include "GrammarRules.h"
#include "csm.h"
#include "pdl_gen.h"

const char *adaptLiterals(const char* str)
{ if (strcmp(str, "'")) {
     return str;
  }
  else return "''";
}

PTGNode OutputRules ()
{ PTGNode res = PTGNULL;

  RuleProdList rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbol lhs = HeadProdSymbolList (rule->prod);
    ProdSymbolList rhs = TailProdSymbolList (rule->prod);
    PTGNode rhsout = PTGNULL;

    while (rhs != NULLProdSymbolList)
    { ProdSymbol symbol = HeadProdSymbolList (rhs);
      switch (symbol->kind)
      { case IsProdLiteral:
          rhsout = 
             PTGGramSeq 
               (rhsout,
                PTGGramLiteral 
                  (adaptLiterals(StringTable (symbol->u.literal))));
          break;
        case IsProdSymbol:
          if (rule->islistof)
            rhsout = 
              PTGGramAltSeq
               (rhsout,
                PTGGramSymbol 
                  (StringTable (GetNameSym (symbol->u.s.symbolkey, 0))));
          else
            rhsout = 
              PTGGramSeq
               (rhsout,
                PTGGramSymbol 
                  (StringTable (GetNameSym (symbol->u.s.symbolkey, 0))));
          break;
        case IsProdGenSymbol:
          rhsout = 
             PTGGramSeq
               (rhsout,
                PTGGramGenSymbol 
                  (StringTable (GetNameSym (symbol->u.s.symbolkey, 0))));
          break;
      }
      rhs = TailProdSymbolList (rhs);
    }
    res = 
      PTGSeq 
        (res, 
           PTGGramRule 
             (StringTable (GetNameSym (rule->rulekey, 0)),
              rule->islistof ?
                PTGGramListof 
                  (StringTable (GetNameSym (lhs->u.s.symbolkey, 0)),
                   rhsout) :
                PTGGramProd 
                  (StringTable (GetNameSym (lhs->u.s.symbolkey, 0)),
                   rhsout)));
    rules = TailRuleProdList (rules);
  }
  return res;
}/* OutputRules */
