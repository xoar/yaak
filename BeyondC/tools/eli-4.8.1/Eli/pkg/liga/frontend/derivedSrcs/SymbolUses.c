
#include "SymbolUses.h"
#include "GrammarRules.h"
#include "pdl_gen.h"

/* is set to the global scope by the call of MarkGrammarUses: */
static Environment globalEnv = NoEnv;

void UnmarkSymbols ()
/* on exit: IsMarked is set to 0 for all symbols */
{
  Binding b = DefinitionsOf (globalEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0)) 
      ResetIsMarked (k, 0); 
    b = NextDefinition (b);
  }
}/*UnmarkSymbols */

#if defined(__cplusplus) || defined(__STDC__)
void MarkInheritUses (DefTableKey sym)
#else
void MarkInheritUses (sym) DefTableKey sym;
#endif
/* on exit:
     IsUsed flag is set for all symbols 
     which this sym inherits from 
*/
{ 
  Environment symEnv = GetUpperScope (sym, NoEnv);

  Binding b = DefinitionsOf (globalEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0)) 
    { Environment fromEnv = GetUpperScope (k, NoEnv);
      if (Inheritsfrom (symEnv, fromEnv))
         ResetIsUsed (k, 1);
    }
    b = NextDefinition (b);
  }
}

#if defined(__cplusplus) || defined(__STDC__)
void MarkGrammarUses (Environment globenv)
#else
void MarkGrammarUses (globenv) Environment globenv;
#endif
/* on entry
     no IsUsed flags are set
   on exit
     IsUsed is set 
        for every symbol that occurs in a production and
        for every symbol that a used symbol inherits from
*/
{ RuleProdList rules;

  /* keep the global environment: */
  globalEnv = globenv;
  /* init IsMarked flags: */
  UnmarkSymbols ();

  /* set all symbols in productions IsUsed and call
     MarkInheritUses for each of them:
  */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList prod = rule->prod;
    while (prod != NULLProdSymbolList)
    { ProdSymbol s = HeadProdSymbolList (prod);
      if (s->kind != IsProdLiteral)
      { ResetIsUsed (s->u.s.symbolkey, 1);
        if (!GetIsMarked (s->u.s.symbolkey, 0))
        { MarkInheritUses (s->u.s.symbolkey);
          ResetIsMarked (s->u.s.symbolkey, 1);
        }
      }
      prod = TailProdSymbolList (prod);
    }
    rules = TailRuleProdList (rules);
  }
}/* MarkGrammarUses */
