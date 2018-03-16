
#include "CompRepr.h"
#include "pdl_gen.h"
#include "DynSpace.h"
#include "csm.h"

#ifdef TEST
#define TEST
PExpr TESTEXPR =(PExpr)0;

void TESTIT(char *s)
{ printf ("TESTIT %s\n",s);
  if (!TESTEXPR) 
  { printf ("NULL\n"); return;}
  printf ("  kind %d line %d\n",
           TESTEXPR->exprKind, LineOf(*(TESTEXPR->coord)));
  if (TESTEXPR->exprKind == AttrAccRuleKind)
  { 
    printf ("  isChain    : %d\n", TESTEXPR->u.attrAccRule.isChain);
    printf ("  attrName   : %s\n", 
      StringTable (GetNameSym (TESTEXPR->u.attrAccRule.attrKey, 1)));
    printf ("  prodSymb no: %d\n", 
      TESTEXPR->u.attrAccRule.prodSymb->u.s.symbolpos);
  }
}
#endif

PExpr wrongExpr;

void *ExprSpace = (void*)0;

#if defined(__cplusplus) || defined(__STDC__)
PExpr allocExpr (CoordPtr coord)
#else
PExpr allocExpr (coord) CoordPtr coord;
#endif
{ PExpr res;
  if (!ExprSpace)
  { /* initialize: */
    ExprSpace = InitDynSpace ();
    wrongExpr = (PExpr) DynAlloc (ExprSpace, sizeof (_SExpr));
    wrongExpr->coord = NoPosition;
    wrongExpr->exprKind = wrongExprKind;
  }
  res = (PExpr) DynAlloc (ExprSpace, sizeof (_SExpr));
  res->coord = coord;
  return res;
}/* allocExpr */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newCall (int name, PExprList params, CoordPtr coord)
#else
PExpr newCall (name, params, coord) int name; PExprList params; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = CallKind;
  res->u.call.idn = name;
  res->u.call.params = params;
  return res;
}/* newCall */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newExprList (PExprList subList, CoordPtr coord)
#else
PExpr newExprList (subList, coord) PExprList subList; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = ExprListKind;
  res->u.subList = subList;
  return res;
}/* newExprList */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newDepend (PExpr ex, PExprList deps, CoordPtr coord)
#else
PExpr newDepend (ex, deps, coord) PExpr ex; PExprList deps; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = DependKind;
  res->u.depend.ex = ex;
  res->u.depend.deps = deps;
  return res;
}/* newDepend */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newAssign (PExpr left, PExpr right, CoordPtr coord)
#else
PExpr newAssign (left, right, coord) PExpr left; PExpr right; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = AssignKind;
  res->u.assign.left = left;
  res->u.assign.right = right;
  return res;
}/* newAssign */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newLoop (PExpr cond, PExpr attr, PExpr iter, CoordPtr coord)
#else
PExpr newLoop (cond, attr, iter, coord)
   PExpr cond; PExpr attr; PExpr iter; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = LoopKind;
  res->u.loop.cond = cond;
  res->u.loop.attr = attr;
  res->u.loop.iter = iter;
  return res;
}/* newLoop */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newName (int name, CoordPtr coord)
#else
PExpr newName (name, coord) int name; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = NameKind;
  res->u.name = name;
  return res;
}/* newName */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newIntValue (int val, CoordPtr coord)
#else
PExpr newIntValue (val, coord) int val; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = IntValueKind;
  res->u.intValue = val;
  return res;
}/* newIntValue */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newStrValue (int val, CoordPtr coord)
#else
PExpr newStrValue (val, coord) int val; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = StrValueKind;
  res->u.strValue = val;
  return res;
}/* newStrValue */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newChrValue (int val, CoordPtr coord)
#else
PExpr newChrValue (val, coord) int val; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = ChrValueKind;
  res->u.chrValue = val;
  return res;
}/* newChrValue */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newFltValue (int val, CoordPtr coord)
#else
PExpr newFltValue (val, coord) int val; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = FltValueKind;
  res->u.fltValue = val;
  return res;
}/* newFltValue */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newAttrAccRule 
  (ProdSymbol prodSymb, DefTableKey attrKey, int isChain, CoordPtr coord)
#else
PExpr newAttrAccRule (prodSymb, attrKey, isChain, coord)
  ProdSymbol prodSymb; DefTableKey attrKey; int isChain; CoordPtr coord;
#endif
{ PExpr res;
  if (prodSymb == NoProdSymbol) return wrongExpr;
  res = allocExpr (coord);
  res->exprKind = AttrAccRuleKind;
  res->u.attrAccRule.prodSymb = prodSymb;
  res->u.attrAccRule.attrKey = attrKey;
  res->u.attrAccRule.isChain = isChain;
  return res;
}/* newAttrAccRule */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newRuleAttrAcc (DefTableKey attrKey, CoordPtr coord)
#else
PExpr newRuleAttrAcc (attrKey, coord) DefTableKey attrKey; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = RuleAttrAccKind;
  res->u.ruleAttrAcc.attrKey = attrKey;
  return res;
}/* newRuleAttrAcc */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newAttrAccSymb
  (DefTableKey symbKey, DefTableKey attrKey, int isChain, CoordPtr coord)
#else
PExpr newAttrAccSymb (symbKey, attrKey, isChain, coord)
  DefTableKey symbKey; DefTableKey attrKey; int isChain; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = AttrAccSymbKind;
  res->u.attrAccSymb.symbKey = symbKey;
  res->u.attrAccSymb.attrKey = attrKey;
  res->u.attrAccSymb.isChain = isChain;
  return res;
}/* newAttrAccSymb */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newIncluding (DefTableKey inclKey, CoordPtr coord)
#else
PExpr newIncluding (inclKey, coord) DefTableKey inclKey; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = IncludingKind;
  res->u.remote.remKey = inclKey;
  res->u.remote.subtree = 0; /* irrelevant */
  return res;
}/* newIncluding */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newConstituent (DefTableKey constKey, int subtree, CoordPtr coord)
#else
PExpr newConstituent (constKey, subtree, coord) 
DefTableKey constKey; int subtree; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = ConstituentKind;
  res->u.remote.remKey = constKey;
  res->u.remote.subtree = subtree;
  return res;
}/* newConstituent */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newConstituents (DefTableKey constKey, int subtree, CoordPtr coord)
#else
PExpr newConstituents (constKey, subtree, coord) 
DefTableKey constKey; int subtree; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = ConstituentsKind;
  res->u.remote.remKey = constKey;
  res->u.remote.subtree = subtree;
  return res;
}/* newConstituents */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newSymbTermAcc (int index, CoordPtr coord)
#else
PExpr newSymbTermAcc (index, coord) int index; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = SymbTermAccKind;
  res->u.symbTerm = index;
  return res;
}/* newSymbTermAcc */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newRuleTermAcc (int symbNo, DefTableKey termKey, CoordPtr coord)
#else
PExpr newRuleTermAcc (symbNo, termKey, coord) 
  int symbNo; DefTableKey termKey; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = RuleTermAccKind;
  res->u.ruleTerm.symbNo = symbNo;
  res->u.ruleTerm.symbKey = termKey;
  return res;
}/* newRuleTermAcc */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newRHS (int attrIdn, CoordPtr coord)
#else
PExpr newRHS (attrIdn, coord) int attrIdn; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = RHSKind;
  res->u.attrIdn = attrIdn;
  return res;
}/* newRHS */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newHeadAcc (DefTableKey chnKey, CoordPtr coord)
#else
PExpr newHeadAcc (chnKey, coord) DefTableKey chnKey; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
#ifdef TEST
  printf ("newHEADAcc line %d\n", LineOf (*coord));
#endif
  res->exprKind = HeadAccKind;
  res->u.chnKey = chnKey;
  return res;
}/* newHeadAcc */

#if defined(__cplusplus) || defined(__STDC__)
PExpr newTailAcc (DefTableKey chnKey, CoordPtr coord)
#else
PExpr newTailAcc (chnKey, coord) DefTableKey chnKey; CoordPtr coord;
#endif
{ PExpr res = allocExpr (coord);
  res->exprKind = TailAccKind;
  res->u.chnKey = chnKey;
  return res;
}/* newTailAcc */

#if defined(__cplusplus) || defined(__STDC__)
PExpr copyExpr (PExpr ex)
#else
PExpr copyExpr (ex) PExpr ex;
#endif
/* the result is a deep copy of ex */
{ /* first a flat copy: */
  PExpr res = allocExpr (ex->coord);
  res->exprKind = ex->exprKind;
  res->u = ex->u;

  /* extend the flat copy recursively to a deep copy: */
  switch (ex->exprKind)
  {
    case CallKind:
      res->u.call.params = CopyPExprList (ex->u.call.params, copyExpr);
      break;
    case ExprListKind:
      res->u.subList = CopyPExprList (ex->u.subList, copyExpr);
      break;
    case LoopKind:
      res->u.loop.cond = copyExpr (ex->u.loop.cond);
      res->u.loop.attr = copyExpr (ex->u.loop.attr);
      res->u.loop.iter = copyExpr (ex->u.loop.iter);
      break;
    case DependKind:
      res->u.depend.ex = copyExpr (ex->u.depend.ex);
      res->u.depend.deps = CopyPExprList (ex->u.depend.deps, copyExpr);
      break;
    case AssignKind:
      res->u.assign.left = copyExpr (ex->u.assign.left);
      res->u.assign.right = copyExpr (ex->u.assign.right);
      break;
    default:;
      /* no sub-expression to be copied */
  }
  return res;
}/* copyExpr */
