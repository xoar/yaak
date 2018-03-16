
#include "Grammar.h"
#include "GrammarRules.h"
#include "pdl_gen.h"
#include "MakeName.h"
#include "err.h"
#include "Strings.h"
#include <stdio.h>

DefTableKey GrammarRoot = NoKey;
int MultipleRoots = 0;

#if defined(__cplusplus) || defined(__STDC__)
void TransformListofRules (Environment env)
#else
void TransformListofRules (env) Environment env;
#endif
/* on entry
        the GrammarRules are completed,
        LISTOF rules are checked
   on exit
        LISTOF rules are substituted,
        generated rules are added
*/
{ RuleProdList rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    if (rule->islistof) {
        Binding newRuleBind;
        DefTableKey newRuleKey;
        RuleProd newRule;
        ProdSymbolList symbollist, alts;
        CoordPtr listRuleCoord = GetCoord (rule->rulekey, NoPosition);

        /* let the rule be RULE rr: Lhs LISTOF Xa | Xb END */
        /* create a new nonterminal named LST_Lhs: */
        DefTableKey oldlhskey = 
          (HeadProdSymbolList (rule->prod))->u.s.symbolkey;
        Binding listSymBind = 
          BindIdn 
            (env, PreIdnPost ("LST_", GetNameSym (oldlhskey, 0), ""));

        DefTableKey listSymKey = KeyOf (listSymBind);
        ResetIsNonterm (listSymKey, 1);
        ResetIsSymbol (listSymKey, 1);
        ResetIsTreeSym (listSymKey, 1);
        ResetNameSym (listSymKey, IdnOf (listSymBind));
        ResetCoord (listSymKey, listRuleCoord);

        /* create an empty rule RULE LST_0rr: LST_Lhs ::= END */
        newRuleBind =
          BindIdn
            (env, PreIdnPost ("LST_0", GetNameSym (rule->rulekey, 0), ""));
        newRuleKey = KeyOf (newRuleBind);
        ResetIsRule (newRuleKey, 1);
        ResetNameSym (newRuleKey, IdnOf (newRuleBind));
        ResetCoord (newRuleKey, listRuleCoord);
        symbollist =
          ConsProdSymbolList
            (MakeProdSymbol (listSymKey, 0, listRuleCoord),
             NULLProdSymbolList);
        newRule = MakeRuleProd (newRuleKey, symbollist, 0, listRuleCoord);
        ResetRule (newRuleKey, newRule);

        /* create a rule for each alternative: 
                RULE LST_Xarr: LST_Lhs ::= Xa LST_Lhs END */
        alts = TailProdSymbolList (rule->prod);
        while (alts != NULLProdSymbolList) {
          DefTableKey altkey = 
            (HeadProdSymbolList (alts))->u.s.symbolkey;
          
          newRuleBind =
            BindIdn
              (env, PreIdnPost ("LST_", 
                                GetNameSym (altkey, 0),
                                StringTable (GetNameSym (rule->rulekey, 0))));
          newRuleKey = KeyOf (newRuleBind);
          ResetIsRule (newRuleKey, 1);
          ResetNameSym (newRuleKey, IdnOf (newRuleBind));
          ResetCoord (newRuleKey, listRuleCoord);
          symbollist =
            ConsProdSymbolList
              (MakeProdSymbol (listSymKey, 0, listRuleCoord),
               ConsProdSymbolList
                 (MakeProdSymbol (altkey, 0, listRuleCoord),
                  ConsProdSymbolList
                    (MakeProdSymbol (listSymKey, 0, listRuleCoord),
                     NULLProdSymbolList)));
          newRule = MakeRuleProd (newRuleKey, symbollist, 0, listRuleCoord);
          ResetRule (newRuleKey, newRule);

          alts = TailProdSymbolList (alts);
        }

        /* replace the right-hand side of rr by LST_Lhs */
        rule->islistof = 0;
        rule->prod->tail =
          ConsProdSymbolList
                (MakeProdSymbol (listSymKey, 0, listRuleCoord),
                 NULLProdSymbolList);
    }
    rules = TailRuleProdList (rules);
  }
}/* TransformListofRules */


void ClassifySymbols ()
/* on entry
        the GrammarRules are completed
   on exit
        the properties IsNonterm, IsTerm, IsRoot 
        are set and checked
*/
{ RuleProdList rules;
  int rootfound = 0;

  /* set IsNonterm IsTree and symbolpos=0 for left-hand side symbols: 
  */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbol lhs = HeadProdSymbolList (rule->prod);
    ResetIsNonterm (lhs->u.s.symbolkey, 1);
    /* IsTreeSym has been set earlier. */
    lhs->u.s.symbolpos = 0;
    rules = TailRuleProdList (rules);
  }

  /* set !IsRoot for all right-hand side symbols,
     set IsTerm for right-hand side symbols if !IsNonterm,
     set symbolpos for right-hand side symbols: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList rhs = TailProdSymbolList (rule->prod);
    int nontermpos = 1, termpos = 1;

    while (rhs != NULLProdSymbolList)
    { ProdSymbol s = HeadProdSymbolList (rhs);
      if (s->kind != IsProdLiteral)
      { ResetIsRoot (s->u.s.symbolkey, 0);
        if (!(GetIsNonterm (s->u.s.symbolkey, 0)))
        {    s->u.s.symbolpos = termpos++;
             ResetIsTerm (s->u.s.symbolkey, 1);
        }
        else s->u.s.symbolpos = nontermpos++;
      }
      rhs = TailProdSymbolList (rhs);
    }
    rules = TailRuleProdList (rules);
  }

  /* find roots: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbol lhs = HeadProdSymbolList (rule->prod);

    /* IsRoot is not set to 0 if symbol does not occur on rhs */
    if (GetIsRoot (lhs->u.s.symbolkey, 1))
    { ResetIsRoot (lhs->u.s.symbolkey, 1);
      rootfound = 1;
      if (GrammarRoot == NoKey) GrammarRoot = lhs->u.s.symbolkey;
      else if (GrammarRoot != lhs->u.s.symbolkey)
         MultipleRoots = 1; /* to be reported in RULE context */
    }
    rules = TailRuleProdList (rules);
  }

  if (!rootfound)
     message (ERROR, 
              "No tree grammar root found",
              0, NoPosition);
}/* ClassifySymbols */
