
#include "CompOut.h"
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

static DefTableKey currRuleKey;
static DefTableKey currentComp;
static int isBottomUp;
static DefTableKey isChainstart;
static PTGNode outcoord = PTGNULL;

static PTGNode IdlUnknown ()
{ return 
    PTGIdlCall 
      (PTGNULL, "$UNKNOWN", 
       outcoord == PTGNULL ? 
         PTGIdlCompCoord (0, 0) : outcoord);
}

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode TranslateCoord (CoordPtr coord)
#else
PTGNode TranslateCoord (coord) CoordPtr coord;
#endif
{ return 
    (coord == NoPosition ?
       PTGIdlCompCoord (0, 0) :
       PTGIdlCompCoord 
         (ColOf(*coord), LineOf(*coord)));
}

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlSymbAttrsOutput (SymbAttrList sal)
#else
PTGNode IdlSymbAttrsOutput (sal) SymbAttrList sal;
#endif
{ PTGNode res = PTGNULL;
  while ( sal != NULLSymbAttrList)
  { SymbAttr sa = HeadSymbAttrList (sal);
    DefTableKey SymbKey = KeyOf(SymbolBindOf (sa));
    Environment SymbAttrEnv = GetAttrScope (SymbKey, NoEnv);
    Binding attrBind = BindingInEnv (SymbAttrEnv, AttrOf(sa));
    DefTableKey attrKey = attrBind == NoBinding ? NoKey : KeyOf (attrBind);
    res = PTGSeq (res,
       PTGIdlSymbAttr (GetDid (attrKey, 0), GetDid (SymbKey, 0)));
    sal = TailSymbAttrList (sal);
  }
  return res;
}/* SymbAttrsOutput */

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlShieldSetOutput (DefTableKeyList dkl, PTGNode con)
#else
PTGNode IdlShieldSetOutput (dkl) DefTableKeyList dkl; PTGNode con;
#endif
{ PTGNode res = PTGNULL;
  if (dkl == NULLDefTableKeyList) return con;

  while (dkl != NULLDefTableKeyList)
  { DefTableKey hd = HeadDefTableKeyList (dkl);
#ifdef TEST
  if (hd == NoKey)
    printf ("shield elem NoKey\n");
  else
    printf ("shield elem\n");
#endif
    if (hd != NoKey) /* sentinel in the shield list */
      res = PTGSeq (res, 
          PTGIdlShieldSym (GetDid (hd, 0), outcoord));
    dkl = TailDefTableKeyList (dkl);
  }
  return PTGIdlShield (con, res, outcoord);
}/* IdlShieldSetOutput */

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlWithOutput (DefTableKey k, PTGNode con)
#else
PTGNode IdlWithOutput (k, con) DefTableKey k; PTGNode con;
#endif
{ DefTableKey tp = GetType (k, NoKey);
  if (tp == NoKey) return con;

  return PTGIdlWith
    (con,
     StringTable (GetNameSym (tp, 0)), 
     StringTable (GetFunct2 (k, 0)),
     StringTable (GetFunct1 (k, 0)),
     StringTable (GetFunct0 (k, 0)), outcoord);
}/* IdlWithOutput */

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlConstituent (DefTableKey k, int subtree, int isSingle)
#else
PTGNode IdlConstituent (k, subtree, isSingle) 
DefTableKey k; int subtree; int isSingle;
#endif
{  PTGNode c =
     IdlWithOutput
       (k,
        IdlShieldSetOutput
          (GetShieldSet (k, NULLDefTableKeyList),
           PTGIdlConstituent 
             (IdlSymbAttrsOutput (GetRemoteSet (k, NULLSymbAttrList)),
              subtree,
              isSingle,
              outcoord)));
     if (GetInVoidContext (k, 0) && (!GetInValueContext (k, 0)))
        c = PTGIdlVoiden (c, outcoord);
     return c;
}/* IdlConstituent */

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlIncluding (DefTableKey remkey)
#else
PTGNode IdlIncluding (remkey) DefTableKey remkey;
#endif
{ PTGNode c = 
    PTGIdlIncluding
      (IdlSymbAttrsOutput 
         (GetRemoteSet (remkey, NULLSymbAttrList)),
       outcoord);  
     if (GetInVoidContext (remkey, 0) && 
         (!GetInValueContext (remkey, 0)))
        c = PTGIdlVoiden (c, outcoord);
  return c;
}/* InclOutput */

static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode IdlExpr (PExpr ex)
#else
PTGNode IdlExpr (ex) PExpr ex;
#endif
{ 
  if (ex == wrongExpr || ex->exprKind == wrongExprKind) 
    return IdlUnknown ();

#ifdef TEST
  if (ex->coord)
    printf ("IdlExpr kind %d line %d\n",
      ex->exprKind, LineOf(*(ex->coord)));
  else
    printf ("IdlExpr kind %d no line\n", ex->exprKind);
#endif

  outcoord = TranslateCoord (ex->coord);

  switch (ex->exprKind)
  {
    case DependKind:
         { PTGNode p = PTGNULL;
           PExprList l = ex->u.depend.deps;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, IdlExpr (e));
             l = TailPExprList (l);
           }
           return PTGIdlDepend
             (IdlExpr (ex->u.depend.ex), p, outcoord);
         }
    case AssignKind:
         { PTGNode rhs = IdlExpr (ex->u.assign.right);
           PTGNode lhs = IdlExpr (ex->u.assign.left);
           PTGNode assig;
           DefTableKey lhsAttr;

           /* bottomup mark is attached to rhs: */
           if (isBottomUp)
             rhs = PTGIdlBottomup (rhs, outcoord);

           /* loop init mark is attached to rhs: */
           if (GetIsLoopInit (currentComp, 0))
             rhs = PTGIdlLoopInit (rhs, outcoord);

           assig = PTGIdlAssign (lhs, rhs, outcoord);

           /* chainstart mark is attached to assignment: */
           if (isChainstart != NoKey) 
                return PTGIdlChainstart 
                  (GetDid (isChainstart, 0), assig, outcoord);

           return assig;
         }
    case LoopKind:
        return PTGIdlLoop
           (IdlExpr (ex->u.loop.cond),
            IdlExpr (ex->u.loop.attr),
            IdlExpr (ex->u.loop.iter),
            outcoord);
    case CallKind:
         { PTGNode p = PTGNULL;
           PExprList l = ex->u.call.params;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, IdlExpr (e));
             l = TailPExprList (l);
           }
           return 
             PTGIdlCall (p, StringTable (ex->u.call.idn), outcoord);
         }
    case ExprListKind:
         { PTGNode p = PTGNULL;
           PExprList l = ex->u.subList;
           while (l != NULLPExprList)
           { PExpr e = HeadPExprList (l);
             p = PTGSeq (p, IdlExpr (e));
             l = TailPExprList (l);
           }
           return p;
          }
    case NameKind:
        return PTGIdlName (StringTable (ex->u.name), outcoord);
    case IntValueKind:
        return PTGIdlIntValue (ex->u.intValue, outcoord);
    case StrValueKind:
        return PTGIdlStrValue 
           (StringTable (ex->u.strValue), outcoord);
    case ChrValueKind:
        return PTGIdlChrValue 
           (StringTable (ex->u.chrValue), outcoord);
    case FltValueKind:
        return PTGIdlFltValue (StringTable (ex->u.fltValue), outcoord);
    case AttrAccRuleKind:
        { ProdSymbol ps = ex->u.attrAccRule.prodSymb;
          int spos = (ps == NoProdSymbol ? 0 : ps->u.s.symbolpos);
#ifdef TEST
  printf ("AttrAccRule symbol pos %d isChain %d\n", spos,
           ex->u.attrAccRule.isChain);
#endif
          if (ex->u.attrAccRule.isChain)
             return PTGIdlChainAcc
               (GetDid (ex->u.attrAccRule.attrKey, 999),
                spos,
                outcoord);
          else
             return PTGIdlAttrAcc
               (GetDid (ex->u.attrAccRule.attrKey, 999),
                spos,
                outcoord);
        }
    case RuleAttrAccKind:
           return PTGIdlAttrAcc
             (GetDid (ex->u.ruleAttrAcc.attrKey, 999),
              0,
              outcoord);
    case AttrAccSymbKind:
        return IdlUnknown ();
    case IncludingKind:
        return IdlIncluding (ex->u.remote.remKey);
    case ConstituentKind:
        return IdlConstituent 
                 (ex->u.remote.remKey, ex->u.remote.subtree, 1);
    case ConstituentsKind:
        return IdlConstituent 
                 (ex->u.remote.remKey, ex->u.remote.subtree, 0);
    case SymbTermAccKind:
        return IdlUnknown ();
    case RuleTermAccKind:
        return PTGIdlTermAcc (ex->u.ruleTerm.symbNo, outcoord);
    case RHSKind:
    case HeadAccKind:
    case TailAccKind:
    default:
         return IdlUnknown (); /*should not occur*/
  }
}/* IdlExpr */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode ComputationOut (DefTableKey comp)
#else
PTGNode ComputationOut (comp) DefTableKey comp;
#endif
{ PExpr repr = GetCompRepr (comp, wrongExpr);
  PTGNode res;
  if (repr == wrongExpr) return IdlUnknown ();

  if (GetIsGenTreeDummy (comp, 0)) {
    if (repr->exprKind != AttrAccRuleKind) return IdlUnknown ();
    return
      PTGIdlGenTreeDummy 
        (IdlExpr (repr), 
         TranslateCoord (repr->coord));
  }

  isChainstart = GetIsChainStart (comp, NoKey);
  isBottomUp = GetIsBottomUp (comp, 0);
  currentComp = comp;

  res = IdlExpr (repr);

  if (isBottomUp && repr->exprKind != AssignKind)
    res = PTGIdlBottomup (res, outcoord);
  isChainstart = 0;
  isBottomUp = 0;

  switch (repr->exprKind)
  {
    case DependKind:
    case AssignKind:
    case LoopKind:
    case CallKind:
        return res;
    default:
        return PTGIdlIdentity (res, outcoord);
  }  
}/* ComputationOut */


static
#if defined(__cplusplus) || defined(__STDC__)
PTGNode MakeDummyRuleComps (DefTableKey rulekey)
#else
PTGNode MakeDummyRuleComps (rulekey) DefTableKey rulekey;
#endif
/* create dummy computations for rule attributes not computed in rulekey*/
{ DefTableKey lhsKey = GetLhsOfRule (rulekey, NoKey);
  Environment symEnv = GetAttrScope (lhsKey, NoEnv);
  PTGNode res = PTGNULL;
  Binding at = DefinitionsOf (symEnv);
  while (at != NoBinding)
  { DefTableKey atk = KeyOf (at);
    DefTableKey ruleOfAttr = GetRuleOfAttr (atk, NoKey);
    if (ruleOfAttr != NoKey && ruleOfAttr != rulekey)
       res = PTGSeq (res, PTGIdlDummyComp (GetDid (atk, 0)));
    at = NextDefinition (at);
  }
  return res;
}/*MakeDummyRuleComps*/

#if defined(__cplusplus) || defined(__STDC__)
PTGNode RuleComputationsOut (DefTableKey rulekey)
#else
PTGNode RuleComputationsOut (rulekey) DefTableKey rulekey;
#endif
/* output all computations of rule */
{ 
    PTGNode res = PTGNULL;
    DefTableKeyList complist = 
        GetAllRuleComps (rulekey, NULLDefTableKeyList);
    currRuleKey = rulekey;

    while (complist != NULLDefTableKeyList)
    { DefTableKey comp = HeadDefTableKeyList (complist);
      res = PTGSeq (res, ComputationOut (comp));
      complist = TailDefTableKeyList (complist);
    }
    res = PTGSeq (res, MakeDummyRuleComps (rulekey));
    return PTGIdlRuleComputations (res, GetDid (rulekey, 999));
}/* RuleComputationsOut */

PTGNode CompOut ()
/* on entry:
     computation representations set to the computation keys
   on exit:
     a textual representation is output
*/
{ Binding b;
  RuleProdList rules;
  PTGNode res = PTGNULL;

  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    res = PTGSeq (res, RuleComputationsOut (RuleKeyOfRuleProd (rule)));
    rules = TailRuleProdList (rules);
  }

  return res;
} /* CompOut */
