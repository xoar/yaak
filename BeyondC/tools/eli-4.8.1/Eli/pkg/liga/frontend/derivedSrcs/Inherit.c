
#include "Inherit.h"
#include "GrammarRules.h"
#include "Grammar.h"
#include "pdl_gen.h"

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
Environment AddKeyToEnv (Environment env, DefTableKey k)
#else
Environment AddKeyToEnv (env, k) Environment env; DefTableKey k;
#endif
{
  SetKeyOfEnv (env, k);
  return env;
}

static POSITION NoPos = {0,1};

#if defined(__cplusplus) || defined(__STDC__)
void MakeSymbOccScopes (Environment env)
#else
void MakeSymbOccScopes (env) Environment env;
#endif
/* on entry
        the GrammarRules are completed,
        the Scope property is set to each symbol
   on exit
        a scope is created for each symbol occurrence,
        the scope of the symbol is inherited to it
*/
{ RuleProdList rules;

#ifdef TEST
  printf ("MakeSymbOccScopes begin\n");
#endif

  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbol lhs = HeadProdSymbolList (rule->prod);
    ProdSymbolList rhs = TailProdSymbolList (rule->prod);

    lhs->u.s.scope = AddKeyToEnv (NewScope (env), lhs->u.s.symbolkey);
    (void)InheritClass
       (lhs->u.s.scope, GetLowerScope (lhs->u.s.symbolkey, NoEnv));

    if (lhs->u.s.symbolkey == GrammarRoot)
    (void)InheritClass /* inherit the INH computations, too */
       (lhs->u.s.scope, GetUpperScope (lhs->u.s.symbolkey, NoEnv));

    while (rhs != NULLProdSymbolList)
    { ProdSymbol sy = HeadProdSymbolList (rhs);
      if (sy->kind != IsProdLiteral)
      { sy->u.s.scope = AddKeyToEnv (NewScope (env), sy->u.s.symbolkey);
        (void)InheritClass 
          (sy->u.s.scope, GetUpperScope (sy->u.s.symbolkey, NoEnv));
      }
      rhs = TailProdSymbolList (rhs);
    }
    rules = TailRuleProdList (rules);
  }

  if (GrammarRoot != NoKey)
  {  if (!InheritClass (GetUpperScope (GrammarRoot, NoEnv),
                        GetUpperScope (ROOTCLASSkey, NoEnv)))
    message (ERROR, "Cyclic inheritance for ROOTCLASS", 0,
             GetCoord (GrammarRoot, &NoPos));
#ifdef TEST
  printf ("connect ROOTCLASS\n");
#endif
  (void) InheritClass (GetLowerScope (GrammarRoot, NoEnv),
                       GetLowerScope (ROOTCLASSkey, NoEnv));
  (void) InheritClass (GetHEADScope (GrammarRoot, NoEnv),
                       GetHEADScope (ROOTCLASSkey, NoEnv));
  (void) InheritClass (GetAttrScope (GrammarRoot, NoEnv),
                       GetAttrScope (ROOTCLASSkey, NoEnv));
  }
#ifdef TEST
  printf ("MakeSymbOccScopes end\n");
#endif
}/* MakeSymbOccScopes */
