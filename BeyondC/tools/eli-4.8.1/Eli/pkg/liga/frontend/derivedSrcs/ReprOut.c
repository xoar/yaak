
#include "ReprOut.h"
#include "pdl_gen.h"
#include "ptg_gen.h"
#include "envmod.h"
#include "csm.h"
#include "CompRepr.h"
#include "RuleProdList.h"
#include "RemoteOut.h"

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

extern RuleProdList GrammarRules;

#if defined(__cplusplus) || defined(__STDC__)
PTGNode ExprOut (PExpr ex)
#else
PTGNode ExprOut (ex) PExpr ex;
#endif
{ PTGNode outcoord = PTGNULL;
  if (ex == wrongExpr || ex->exprKind == wrongExprKind) 
    return PTGIndentNL (PTGAsIs ("wrongExpr"));

#ifdef TEST
  if (ex->coord)
    printf ("ExprOut kind %d line %d\n",
      ex->exprKind, LineOf(*(ex->coord)));
  else
    printf ("ExprOut kind %d no line\n", ex->exprKind);
#endif

  outcoord = 
    PTGOutCoord (LineOf(*(ex->coord)), ColOf(*(ex->coord)));
  switch (ex->exprKind)
  {
    case DependKind:
         { PTGNode p = PTGNULL;
           PExprList l = ex->u.depend.deps;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, ExprOut (e));
             l = TailPExprList (l);
           }
           return PTGDepend
             (ExprOut (ex->u.depend.ex), p, outcoord);
         }
    case AssignKind:
        return PTGAssign
           (ExprOut (ex->u.assign.left),
            ExprOut (ex->u.assign.right),
            outcoord);
    case LoopKind:
        return PTGLoop
           (ExprOut (ex->u.loop.cond),
            ExprOut (ex->u.loop.attr),
            ExprOut (ex->u.loop.iter),
            outcoord);
    case CallKind:
         { PTGNode name = PTGNULL;
           PTGNode p = PTGNULL;
           PExprList l = ex->u.call.params;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, ExprOut (e));
             l = TailPExprList (l);
           }
           return PTGCallExpr 
              (PTGAsIs (StringTable (ex->u.call.idn)), p , outcoord);
         }
    case ExprListKind:
         { PTGNode p = PTGNULL;
           PExprList l = ex->u.subList;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, ExprOut (e));
             l = TailPExprList (l);
           }
           return p;
          }
    case NameKind:
        return PTGName (StringTable (ex->u.name));
    case IntValueKind:
        return PTGIntValue (ex->u.intValue);
    case StrValueKind:
        return PTGStrValue (StringTable (ex->u.strValue));
    case ChrValueKind:
        return PTGChrValue (ex->u.chrValue);
    case FltValueKind:
        return PTGFltValue (StringTable (ex->u.fltValue));
    case AttrAccRuleKind:
        { ProdSymbol ps = ex->u.attrAccRule.prodSymb;
          int spos = (ps == NoProdSymbol ? 0 : ps->u.s.symbolpos);
          DefTableKey sKey = 
                (ps == NoProdSymbol ? NoKey : ps->u.s.symbolkey);
          return PTGAttrAccRule
            (ex->u.attrAccRule.isChain ? PTGIsChain() : PTGIsAttr(),
             StringTable 
               (GetNameSym (sKey, 0)),
             spos,
             StringTable (GetNameSym (ex->u.attrAccRule.attrKey, 0)));
        }
    case RuleAttrAccKind:
        return PTGRuleAttrAcc 
          (StringTable (GetNameSym (ex->u.ruleAttrAcc.attrKey, 0)));
    case AttrAccSymbKind:
        return PTGAttrAccSymb
          (ex->u.attrAccSymb.isChain ? PTGIsChain() : PTGIsAttr(),
           StringTable (GetNameSym (ex->u.attrAccSymb.symbKey, 0)),
           StringTable (GetNameSym (ex->u.attrAccSymb.attrKey, 0)));
    case IncludingKind:
        return PTGIndentNL (InclOutput (ex->u.remote.remKey));
    case ConstituentKind:
        return PTGIndentNL (ConstitOutput (ex->u.remote.remKey));
    case ConstituentsKind:
        return PTGIndentNL (ConstitsOutput (ex->u.remote.remKey));
    case SymbTermAccKind:
        return PTGSymbTermAcc (ex->u.symbTerm);
    case RuleTermAccKind:
        return PTGRuleTermAcc 
           (StringTable (GetNameSym (ex->u.ruleTerm.symbKey, 0)),
            ex->u.ruleTerm.symbNo);
    case RHSKind:
        return PTGRHS (StringTable (ex->u.attrIdn));
    case HeadAccKind:
        return PTGHeadAcc 
          (StringTable (GetNameSym (ex->u.chnKey, 0)));
    case TailAccKind:
        return PTGTailAcc 
          (StringTable (GetNameSym (ex->u.chnKey, 0)));
    default:
         return PTGUnknownExpr (outcoord);
  }
}/* ExprOut */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode CompReprOut (Binding comp)
#else
PTGNode CompReprOut (comp) Binding comp;
#endif
{ DefTableKey k = KeyOf (comp);
  DefTableKey c = GetContext (k, NoKey);
  PExpr repr = GetCompRepr (k, wrongExpr);
  PTGNode context = PTGNULL, plain = PTGNULL, 
          start = PTGNULL, bottomup = PTGNULL;
#ifdef TEST
  printf ("CompReprOut\n");
#endif
  if (repr == wrongExpr) return PTGNULL;

  context = 
    PTGSeq
       ( GetIsRule (c, 0) ? PTGAsIs ("RULE ") :
         (GetIsSymbol (c, 0) ? PTGAsIs ("SYMBOL "):
                                PTGAsIs ("NoContext ")),
         PTGAsIs (StringTable (GetNameSym (c, 0))));

  return PTGComputation
    (context, 
     GetIsChainStart (k, NoKey) != NoKey ? 
                PTGAsIs (" CHAINSTART ") : PTGNULL,
     GetAttribute (k, NoKey) == NoKey ? 
                PTGAsIs (" PLAIN ") : PTGAsIs (" ATTR "),
     GetIsBottomUp (k, 0) ? 
                PTGAsIs ("BOTTOMUP ") : PTGNULL,
     ExprOut (repr));
}/* CompReprOut */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode SymbolCompsOut (Binding sym)
#else
PTGNode SymbolCompsOut (sym) Binding sym;
#endif
/* output all upper and lower computations of sym */
{ PTGNode ures = PTGNULL, lres = PTGNULL;
  Environment sc;
  Binding cmp;
#ifdef TEST
  printf ("SymbolCompsOut\n");
#endif

  sc = GetLowerScope (KeyOf(sym), NoEnv);
  cmp = DefinitionsOf (sc);
  while (cmp != NoBinding)
  { lres = PTGSeq (lres, CompReprOut (cmp));
    cmp = NextDefinition (cmp);
  }

  sc = GetUpperScope (KeyOf(sym), NoEnv);
  cmp = DefinitionsOf (sc);
  while (cmp != NoBinding)
  { ures = PTGSeq (ures, CompReprOut (cmp));
    cmp = NextDefinition (cmp);
  }

  return PTGSymbolComputations
    (StringTable(IdnOf(sym)), ures, lres);
}/* SymbolCompsOut */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode RuleCompsOut (RuleProd rule)
#else
PTGNode RuleCompsOut (rule) RuleProd rule;
#endif
/* output all computations of rule */
{ 
    PTGNode res = PTGNULL;
    ProdSymbolList prod = rule->prod;

    DefTableKey ruleKey = RuleKeyOfRuleProd (rule);
    Environment rulescope = GetLowerScope (ruleKey, NoEnv);
    Binding b = DefinitionsOf (rulescope);
#ifdef TEST
  printf ("RuleCompsOut\n");
#endif
    while (b != NoBinding)
    {
      res = PTGSeq (res, CompReprOut (b));
      b = NextDefinition (b);
    }

    while (prod != NULLProdSymbolList)
    { ProdSymbol sy = HeadProdSymbolList (prod);
      if (sy->kind != IsProdLiteral && !GetIsTerm (sy->u.s.symbolkey, 0))
      { Environment syenv = sy->u.s.scope;
        Binding b = DefinitionsOf (syenv);
        while (b != NoBinding)
        { 
          res = PTGSeq (res, CompReprOut (b));
          b = NextDefinition (b);
        }
      }
      if (rule->islistof) break;
      prod = TailProdSymbolList (prod);
    }
  return PTGRuleComputations 
    (StringTable (GetNameSym (ruleKey, 0)), res);
}/* RuleCompsOut */


extern Environment RootEnv; /* exported by AlgScope.h */

PTGNode ReprOut ()
/* on entry:
     computation representations set to the computation keys
   on exit:
     a textual representation is output
*/
{ Binding b;
  RuleProdList rules;
  PTGNode res = PTGNULL;
#ifdef TEST
  printf ("ReprOut\n");
#endif

  /* step through all nonterminal occurrences of productions: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  {  
    res = PTGSeq (res, RuleCompsOut (HeadRuleProdList (rules)));
    rules = TailRuleProdList (rules);
  }

#ifdef DONTDOIT
  b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b); Environment sc;
    if (GetIsSymbol (k, 0) && !GetIsTerm (k, 0) && 
        (sc = GetLowerScope (k, NoEnv)) != NoEnv &&
         DefinitionsOf (sc) != NoBinding)
    res = PTGSeq (res, SymbolCompsOut (b));
    b = NextDefinition (b);
  }
#endif

  return PTGSeq (res, PTGAsIs ("\n"));
} /* ReprOut */


