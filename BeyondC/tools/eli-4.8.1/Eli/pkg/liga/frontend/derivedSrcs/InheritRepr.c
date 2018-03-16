
#include "InheritRepr.h"
#include "Inherit.h"
#include "CompRepr.h"
#include "GrammarRules.h"
#include "Prod.h"
#include "Grammar.h"
#include "Attribute.h"
#include "pdl_gen.h"
#include "csm.h"
#include "Strings.h"
#include "MakeName.h"

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
DefTableKey CreateBUAssignAttr
  (DefTableKey context, DefTableKey attr, CoordPtr coord)
#else
DefTableKey CreateBUAssignAttr (context, coord) 
  DefTableKey context, attr; CoordPtr coord;
#endif
/* An attribute is created for the lhs of a plain BU computation
   the lhs attr is a new rule-attr if context is a rule,
   it is the computation attr if context is a symbol;
   in either case IsPlain is NOT set, to keep the attr in the output
*/
{ 
  Environment attrScope = GetAttrScope (context, NoEnv);
  if (GetIsRule (context, 0))
  { 
    int sym = GenerateName ("_BUPlain");
    attr = KeyOf (BindIdn (attrScope, sym));
    ResetNameSym (attr, sym);
    ResetRuleOfAttr (attr, context);
    ResetCoord (attr, coord);
  }
  ResetIsPlain (attr, 0);
  ResetAttrClass (attr, SYNTClass);
  ResetAttrType (attr, VOIDkey);
  ResetIsDefined (attr, 1);
#ifdef TEST
  printf ("CreateBUAssignAttr attr %s of %s\n",
          StringTable (GetNameSym (attr, 0)), 
          StringTable (GetNameSym (context, 0)));
#endif
  return attr;
}/* CreateBUAssignAttr */

#if defined(__cplusplus) || defined(__STDC__)
PExpr TurnPlainBUIntoAssign
  (DefTableKey context, DefTableKey attr, PExpr plain, CoordPtr coord)
#else
PExpr TurnPlainBUIntoAssign (context, attr, plain, coord) 
  DefTableKey context; DefTableKey attr; PExpr plain; CoordPtr coord;
#endif
/* The plain computation is turned into an assignment;
   the lhs attr is a rule-attr if context is a rule,
   it is a symbol-attr if context is a symbol;
*/
{
  PExpr lhs = 
    GetIsRule (context, 0) ?
      newRuleAttrAcc (attr, coord) :
      newAttrAccSymb (context, attr, 0, coord);
  return newAssign (lhs, plain, coord);
}/* TurnPlainBUIntoAssign */

#if defined(__cplusplus) || defined(__STDC__)
void instantiateExpr (PExpr ex, RuleProd rule, ProdSymbol symocc)
#else
void instantiateExpr (ex, rule, symocc) 
  PExpr ex; RuleProd rule; ProdSymbol symocc;
#endif
/* the result is a deep copy of ex */
{ PExprList exl;
#ifdef TEST
  printf ("instantiateExpr kind %d\n", ex->exprKind);
#endif
  switch (ex->exprKind)
  {
    case AttrAccSymbKind:
      { int isChain = ex->u.attrAccSymb.isChain;
        DefTableKey attrKey;
        if (isChain)
           attrKey = ex->u.attrAccSymb.attrKey;
        else
           attrKey = 
             KeyInEnv 
               (GetAttrScope (symocc->u.s.symbolkey, NoEnv),
                GetNameSym (ex->u.attrAccSymb.attrKey, 0));

       ex->exprKind = AttrAccRuleKind;
       ex->u.attrAccRule.prodSymb = symocc;
       ex->u.attrAccRule.attrKey = attrKey;
       ex->u.attrAccRule.isChain = isChain;
       return;
      }
    case SymbTermAccKind:
      { int symbNo = 0, index;
        ProdSymbol s;
        ProdSymbolList rhs = TailProdSymbolList (rule->prod);

        if (symocc->u.s.symbolpos > 0)
        { ex->exprKind = wrongExprKind;
          return;
        }

        index = ex->u.symbTerm; 
        if (index == 0) index = 1;
        if (rule->islistof) rhs = NULLProdSymbolList;

        while (rhs != NULLProdSymbolList)
        { s = HeadProdSymbolList (rhs);
          symbNo++;
          if (s->kind == IsProdSymbol && GetIsTerm (s->u.s.symbolkey, 0))
          { 
#ifdef TEST
  printf ("TERM[%d] symbolpos: %d\n", index, s->u.s.symbolpos);
#endif
            if (s->u.s.symbolpos == index) break; 
          }
          rhs = TailProdSymbolList (rhs);
        }
        if (rhs == NULLProdSymbolList)
        { message (ERROR, CatStrInd
                     ("Too few terminals in rule ",
                      GetNameSym (RuleKeyOfRuleProd (rule), 0)),
                   0, ex->coord);
          ex->exprKind = wrongExprKind;
          return;          
        }
        ex->exprKind = RuleTermAccKind;
        ex->u.ruleTerm.symbNo = index;
        ex->u.ruleTerm.symbKey = s->u.s.symbolkey;
        return;
      }
    case CallKind:
      exl = ex->u.call.params;
      while (exl != NULLPExprList)
      { instantiateExpr (HeadPExprList (exl), rule, symocc);
        exl = TailPExprList (exl);
      }
      break;
    case LoopKind:
      instantiateExpr (ex->u.loop.cond, rule, symocc);
      instantiateExpr (ex->u.loop.attr, rule, symocc);
      instantiateExpr (ex->u.loop.iter, rule, symocc);
      break;
    case DependKind:
      instantiateExpr (ex->u.depend.ex, rule, symocc);
      exl = ex->u.depend.deps;
      while (exl != NULLPExprList)
      { instantiateExpr (HeadPExprList (exl), rule, symocc);
        exl = TailPExprList (exl);
      }
      break;
    case AssignKind:
      instantiateExpr (ex->u.assign.left, rule, symocc);
      instantiateExpr (ex->u.assign.right, rule, symocc);
      break;
    case ExprListKind:
      exl = ex->u.subList;
      while (exl != NULLPExprList)
      { instantiateExpr (HeadPExprList (exl), rule, symocc);
        exl = TailPExprList (exl);
      }
      break;
    default:;
      /* no sub-expression to be instantiated */
  }
  return;
}/* instantiateExpr */

void instantiateComputation
#if defined(__cplusplus) || defined(__STDC__)
      (Binding rulecomp, Binding orig, RuleProd rule, ProdSymbol symb)
#else
      (rulecomp, orig, rule, symb)
      Binding rulecomp, orig; RuleProd rule; ProdSymbol symb;
#endif
/* on entry:
   rulecomp is a computation binding in the context of the rule rule or 
     of the symbol occurrence symb of rule
   orig is a computation binding which is to be inherited
     if rulecomp has no code associated by CompRepr
   on exit:
   if rulecomp has code associated by CompRepr it is left unchanged,
     otherwise the inherited computation is instantiated for that
     rule context
*/
{ 
  PExpr sourceEx = GetCompRepr (KeyOf(orig), NULLPExpr);
  PExpr targetEx = GetCompRepr (KeyOf(rulecomp), NULLPExpr);
  DefTableKey sourceIsChainStart = GetIsChainStart(KeyOf(orig), NoKey);

  if (targetEx ==  NULLPExpr)
  {
#ifdef TEST
  printf ("inherited repr from line %d\n", LineOf(*(sourceEx->coord)));
#endif
    /* the source expression is copied, then modified by recursive
       calls of instantiateExpr: 
    */
    targetEx = copyExpr (sourceEx);
    instantiateExpr (targetEx, rule, symb);

    ResetCompRepr (KeyOf(rulecomp), targetEx);
    ResetIsBottomUp (KeyOf(rulecomp), 
         GetIsBottomUp (KeyOf(orig), 0));

    if ((sourceIsChainStart != NoKey) &&
        (GetEmptyHEADAttr (KeyOf(rulecomp), NoKey) == NoKey))
         ResetIsChainStart (KeyOf(rulecomp), sourceIsChainStart);
    else ResetIsChainStart (KeyOf(rulecomp), NoKey);
  }
}/* instantiateComputation */

void InheritRepr ()
/* on entry:
     All inherited computations are bound in the computation scopes 
     of the symbol occurrences.
     Each such key of an inherited computation is related to
     the original symbol computation by the property InheritedFrom.
     All original computations have representations.
   on exit:
     All inherited computations have a representation which is
     instantiated from the original symbol computation
*/
{ RuleProdList rules;
  Binding rulecomp;
#ifdef TEST
  printf ("InheritRepr started\n"); 
#endif

  /* step through all nonterminal occurrences of productions: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList prod = rule->prod;
    DefTableKey ruleKey = RuleKeyOfRuleProd (rule);
    ProdSymbol symb = HeadProdSymbolList (prod);
    int inRootRule = 0;
#ifdef TEST
    int i = 0;
   printf ("RULE %s:\n", 
      StringTable (GetNameSym (ruleKey, 0)));
#endif
    rulecomp = DefinitionsOf(GetLowerScope(ruleKey, NoEnv));
    while (rulecomp != NoBinding)
    { Binding orig = GetInheritedFrom (KeyOf(rulecomp), NoBinding);
      if (orig != NoBinding)
        instantiateComputation (rulecomp, orig, rule, symb);
      rulecomp = NextDefinition(rulecomp);
    }
 #ifdef TEST
  printf ("computations at symb occs:\n"); 
#endif 
    while (prod != NULLProdSymbolList)
    { 
 #ifdef TEST
  printf ("symb occ %d:\n", i++); 
#endif 
      symb = HeadProdSymbolList (prod);
      if (symb->kind != IsProdLiteral && 
          !GetIsTerm (symb->u.s.symbolkey, 0))
      { Environment syenv = symb->u.s.scope;
#ifdef TEST
  printf ("symbol %s:\n", 
     StringTable (GetNameSym (symb->u.s.symbolkey, 0)));
#endif
        rulecomp = DefinitionsOf(syenv);
        while (rulecomp != NoBinding)
        { Binding orig = GetInheritedFrom (KeyOf(rulecomp), NoBinding);
          if (orig != NoBinding)
            instantiateComputation (rulecomp, orig, rule, symb);
          rulecomp = NextDefinition(rulecomp);
        }
      }
      if (rule->islistof) break;
      prod = TailProdSymbolList (prod);
    }
    rules = TailRuleProdList (rules);
  }
#ifdef TEST
  printf ("InheritRepr completed\n"); 
#endif
}/* InheritRepr */
