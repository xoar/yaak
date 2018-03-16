
#include "CheckRuleComps.h"
#include "CompRepr.h"
#include "GrammarRules.h"
#include "Grammar.h"
#include "pdl_gen.h"
#include "csm.h"
#include "Strings.h"
#include "DefTableKeyList.h"
#include "Predefined.h"
#include "PreDefId.h"
#include "Remote.h"
#include "Inherit.h"
#include "SymbolOcc.h"

extern Environment RootEnv; /* exported by AlgScope.h */

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

static RuleProd currRule;
static ProdSymbol currSymbOcc;
static DefTableKey currCompKey;
static PExprList loopAttributes;

#if defined(__cplusplus) || defined(__STDC__)
PExprList ExpandExprList (PExprList left, PExprList right);
#else
PExprList ExpandExprList ();
#endif

#if defined(__cplusplus) || defined(__STDC__)
PExprList ConsRHSAttrList
  (ProdSymbolList rhs, int attrIdn, CoordPtr coord)
#else
PExprList ConsRHSAttrList (rhs, attrIdn, coord) 
  ProdSymbolList rhs; int attrIdn; CoordPtr coord;
#endif
/* recursive construction of a list of attribute accesses
   X.attrIdn, one for each nonterminal of rhs
*/
{ PExprList res;
  ProdSymbol sy;
  if (rhs == NULLProdSymbolList) 
     return NULLPExprList;
  res = ConsRHSAttrList (TailProdSymbolList (rhs), attrIdn, coord);
  sy = HeadProdSymbolList (rhs);
  if (sy->kind != IsProdLiteral && !GetIsTerm (sy->u.s.symbolkey, 0))
  { Environment attrenv = GetAttrScope (sy->u.s.symbolkey, NoEnv);
    Binding attrBind = BindingInScope (attrenv, attrIdn);
    if (attrBind == NoBinding)
    { message (ERROR, CatStrInd 
                 ("RHS attribute is missing for ", 
                  GetNameSym (sy->u.s.symbolkey, 0)),
               0, coord);
      return res;
    }
    return
      ConsPExprList 
        (newAttrAccRule (sy, KeyOf(attrBind), 0, coord), res);
   }
  return res;
}/* ConsRHSAttrList */

#if defined(__cplusplus) || defined(__STDC__)
void ExpandRHSAttr (PExpr ex)
#else
void ExpandRHSAttr (ex) PExpr ex;
#endif
/* if RHS.a is allowed in the enclosing rule context, 
   ex is substituted by an expression list, 
   that will be embedded later
*/
{ ProdSymbolList rhs;
  ProdSymbol sy; 
  PExprList res;
  if (currRule->islistof)
  { message (ERROR, "RHS not allowed in LISTOF rule",
             0, ex->coord);
    ex->exprKind = wrongExprKind;
    return;
  }
  res =
    ConsRHSAttrList 
       (TailProdSymbolList (currRule->prod),
        ex->u.attrIdn,
        ex->coord);
  ex->exprKind = ExprListKind;
  ex->u.subList = res;
}/* ExpandRHSAttr */

#if defined(__cplusplus) || defined(__STDC__)
int getPrefix (PExpr ex, PExprList params)
#else
int getPrefix (ex, params) PExpr ex; PExprList params;
#endif
{ PExpr first; 
  if (params == NULLPExprList)
  { message (ERROR, "Arguments of function call missing", 
             0, ex->coord);
    ex->exprKind = wrongExprKind;
    return 0;
  }
  first = HeadPExprList (params);
  if (first->exprKind != StrValueKind)
  { message (ERROR, 
             "First argument of function call must be a string", 
             0, ex->coord);
    ex->exprKind = wrongExprKind;
    return 0;
  }
  return first->u.strValue;
}/* getPrefix */

#if defined(__cplusplus) || defined(__STDC__)
PExprList ConsTermCallList 
   (int prefix, ProdSymbolList rhs, int symbNo, 
    PExprList params, CoordPtr coord)
#else
PExprList ConsTermCallList (prefix, rhs, symbNo, params, coord)
   int prefix; ProdSymbolList rhs; int symbNo; 
   PExprList params; CoordPtr coord;
#endif
{ ProdSymbol sy;
  if (rhs == NULLProdSymbolList) return NULLPExprList;
  sy = HeadProdSymbolList (rhs);
  if (sy->kind != IsProdLiteral && GetIsTerm (sy->u.s.symbolkey, 0))
    return
      ConsPExprList
       (newCall 
           (IndCatStrStr
              (StringTable (prefix),
               StringTable (GetNameSym (sy->u.s.symbolkey, 0))),
            ConsPExprList
              (newRuleTermAcc (symbNo, sy->u.s.symbolkey, coord),
               params),
            coord),
        ConsTermCallList
          (prefix,
           TailProdSymbolList (rhs), 
           symbNo+1,
           params,
           coord));
   else
     return 
        ConsTermCallList
          (prefix, 
           TailProdSymbolList (rhs),
           symbNo,
           params,
           coord);
}/* ConsTermCallList */

#if defined(__cplusplus) || defined(__STDC__)
void ExpandTermFct (PExpr ex)
#else
void ExpandTermFct (ex) PExpr ex;
#endif
/*         ex is a TermFct call of the form
           TermFct ("Pre", a1,...,an)
           Let  X ::= ... Ta ... Tb ... 
           be the rule containing that call, 
           where Ta and Tb are the only terminals.
           Then the result is an argument sequence
           PreTa (Ta, a1,...,an), PreTb (Tb, a1,...,an)
           where a1,...,an are recursively substituted.
*/
{ PExprList params = 
     ExpandExprList (ex->u.call.params, NULLPExprList);
  int prefix = getPrefix (ex, params);
  if (prefix == 0) return;

  ex->u.subList =
    ConsTermCallList 
      (prefix, 
       TailProdSymbolList (currRule->prod), 1,
       TailPExprList (params),
       ex->coord);
  ex->exprKind = ExprListKind;
}/* ExpandTermFct */

#if defined(__cplusplus) || defined(__STDC__)
PExprList ExpandExprList (PExprList left, PExprList right)
#else
PExprList ExpandExprList (left, right) PExprList left, right;
#endif
/* on entry
     left and right are expression lists in rule context
          evaluated for currSymOcc
     right is expanded and is to be appended to the expansion
     left
   on exit
     the expanded list is returned;
     any occurrence of RHS and TermFct in exl are expanded;
     the result list flattened
     other transformations or checks are not yet performed
*/
{ PExpr thisEx;
  if (left == NULLPExprList)
     return right;

  thisEx = HeadPExprList (left);
  if (thisEx->exprKind == RHSKind)
       ExpandRHSAttr (thisEx);
  else if ((thisEx->exprKind == CallKind) &&
           (thisEx->u.call.idn == TermFctsym))
       ExpandTermFct (thisEx);

  if (thisEx->exprKind == ExprListKind)
       return 
         ExpandExprList 
           (thisEx->u.subList,
            ExpandExprList (TailPExprList (left), right));

  else {
    left->tail =
        ExpandExprList (TailPExprList (left), right);
    return left;
  }         
}/* ExpandExprList */

#if defined(__cplusplus) || defined(__STDC__)
void CheckTrafoExpr (PExpr ex, int isVoid);
#else
void CheckTrafoExpr ();
#endif

#if defined(__cplusplus) || defined(__STDC__)
void CheckTrafoExprList (PExprList exl, int isVoid)
#else
void CheckTrafoExprList (exl, isVoid) 
   PExprList exl; int isVoid;
#endif
/* on entry
     exl is an expression list in rule context, evaluated for 
     currSymOcc in VOID context if isVoid indicates so.
     RHS and TermFct are already expanded in exl
   on exit
     the elements of exl are checked and transformed
*/
{ while (exl != NULLPExprList)
  { CheckTrafoExpr (HeadPExprList (exl), isVoid);
    exl = TailPExprList (exl);
  }
}/* CheckTrafoExprList */


#if defined(__cplusplus) || defined(__STDC__)
DefTableKey AttrAccType (PExpr ex)
#else
DefTableKey AttrAccType (ex) PExpr ex;
#endif
{ DefTableKey tp;
  if (ex == wrongExpr) return intkey;
  switch (ex->exprKind)
  { case AttrAccRuleKind:
      tp = GetAttrType (ex->u.attrAccRule.attrKey, VOIDkey);
      break;
    case RuleAttrAccKind:
      tp = GetAttrType (ex->u.ruleAttrAcc.attrKey, VOIDkey);
      break;
    case wrongExprKind:
      return intkey;
    default:
      tp = VOIDkey;
  }
  return tp;
}/* AttrAccType */

#if defined(__cplusplus) || defined(__STDC__)
void MsgEmptyRemoteSet (DefTableKey remkey, CoordPtr coord)
#else
void MsgEmptyRemoteSet (remkey, coord) 
  DefTableKey remkey; CoordPtr coord;
#endif
{ 
if (GetRemoteSet (remkey, NULLSymbAttrList) == NULLSymbAttrList) 
  {
    DefTableKey inhcontext = 
      GetContext (KeyOf (GetInheritedFrom (currCompKey, NoBinding)), NoKey);
    DefTableKey context = GetContext (currCompKey, NoKey);

    if (GetRemoteEpxrIsErr (remkey, 0)) return;
      /* the remote construct is reported to be erroneous */

    if (inhcontext != NoKey && !GetIsTreeSym (inhcontext, 0)) {
      message (ERROR, 
               "This empty set of remote attributes is inherited by some RULE",
               0, coord);
      message (ERROR, "Symbol inherits a computation with an empty remote set",
               0, currSymbOcc->u.s.coord);
    } else
      message (ERROR, "Set of remote attributes is empty", 0, coord);
  }  
}/* MsgEmptyRemoteSet */

#if defined(__cplusplus) || defined(__STDC__)
void CheckAllAttrsValue (DefTableKey remKey, int isIncl, CoordPtr coord)
#else
void CheckAllAttrsValue (remKey, isIncl, coord) 
  DefTableKey remkey; int isIncl; CoordPtr coord;
#endif
/* check whether all remote attrs are non-VOID */
{
  SymbAttrList sal = 
      GetRemoteSet (remKey, NULLSymbAttrList);

  if (GetRemoteEpxrIsErr (remKey, 0)) return;
    /* the remote construct is reported to be erroneous */

  while (sal != NULLSymbAttrList) {
    Environment syAttrs = 
      GetAttrScope (KeyOf(SymbolBindOf(HeadSymbAttrList (sal))),
                    NoEnv);
    Binding atb = 
      BindingInEnv (syAttrs, AttrOf(HeadSymbAttrList (sal)));
    if (atb != NoBinding && 
        GetAttrType (KeyOf(atb), VOIDkey) == VOIDkey) {
      if (isIncl)
        message (ERROR, "VOID INCLUDING in value context",
                 0, coord);
      else
        message (ERROR, "VOID CONSTITUENT(S) in value context",
                 0, coord);
      break;
    }
    sal = TailSymbAttrList (sal);
  }
}/* CheckAllAttrsValue */

#if defined(__cplusplus) || defined(__STDC__)
void CheckTrafoExpr (PExpr ex, int isVoid)
#else
void CheckTrafoExpr (ex, isVoid) 
   PExpr ex; int isVoid;
#endif
/* on entry
     ex is an expression in rule context, evaluated for currSymOcc
     in VOID context if isVoid indicates so.
   on exit
     ex is recursively checked and transformed
*/
{
  if (ex == wrongExpr) return;
#ifdef TEST
  printf ("CheckTrafo ExprKind %d \n", ex->exprKind);
#endif
  switch (ex->exprKind)
  {
    case CallKind:
#ifdef TEST
  printf ("CheckTrafo call %s %d predef %d\n", 
          StringTable(ex->u.call.idn), ex->u.call.idn,
          IsPredefSym(ex->u.call.idn));
#endif
      ex->u.call.params = 
        ExpandExprList (ex->u.call.params, NULLPExprList);

      if (IsPredefSym (ex->u.call.idn))
      { PExprList params = ex->u.call.params;
        /*                    -----*/
        if (ex->u.call.idn == IFsym)
        { if (params == NULLPExprList)
          { message (ERROR, "Arguments of IF missing", 
                     0, ex->coord);
            break;
          }
          CheckTrafoExpr (HeadPExprList (params), 0);
          params = TailPExprList (params);
          if (params == NULLPExprList)
          { message (ERROR, "Arguments of IF missing", 
                     0, ex->coord);
            break;
          }
          CheckTrafoExpr (HeadPExprList (params), isVoid);
          params = TailPExprList (params);
          if (params == NULLPExprList)
          { if (!isVoid)
              message (ERROR, "IF needs else part in value context", 
                       0, ex->coord);
            break;
          }
          CheckTrafoExpr (HeadPExprList (params), isVoid);
          params = TailPExprList (params);
          if (params != NULLPExprList)
                message (ERROR, "IF has more than 3 arguments",
                         0, ex->coord);
        } else
        /*                    --------*/
        if (ex->u.call.idn == ORDERsym)
        { 
          if (params == NULLPExprList)
          { message (ERROR, "Arguments of ORDER missing", 
                     0, ex->coord);
            break;
          }
          while (TailPExprList (params) != NULLPExprList)
          {
            CheckTrafoExpr (HeadPExprList (params), 1);
            params = TailPExprList (params);
          }
          CheckTrafoExpr (HeadPExprList (params), isVoid);
        } else
        /*                    ----------*/
        if (ex->u.call.idn == RuleFctsym)
        { int prefix = getPrefix (ex, params);
          int ruleName = 
            GetNameSym (RuleKeyOfRuleProd (currRule), 0);
#ifdef TEST
  printf ("RuleFct begin\n"); 
#endif
          CheckTrafoExprList (params, 0);
          if (prefix == 0)
             break;
          /* create new call identifier: */
          ex->u.call.idn = 
            IndCatStrStr 
              (StringTable (prefix),
               StringTable (ruleName));
          ex->u.call.params = TailPExprList(params);
#ifdef TEST
  printf ("RuleFct end\n"); 
#endif
        } else
        /*                    ---------*/
        if (ex->u.call.idn == RhsFctsym)
        { int prefix = getPrefix (ex, params);
          int nonterms = 0, terms = 0;
          char buffer [64];
          ProdSymbolList rhs = 
             TailProdSymbolList (currRule->prod);
#ifdef TEST
  printf ("RhsFct begin\n"); 
#endif
          CheckTrafoExprList (params, 0);
          if (prefix == 0)
             break;
          while (rhs != NULLProdSymbolList)
          { ProdSymbol sy = HeadProdSymbolList (rhs);
            if (sy->kind != IsProdLiteral) {
              if (GetIsTerm (sy->u.s.symbolkey, 0))
                   terms++;
              else nonterms++;
            }
            rhs = TailProdSymbolList (rhs);
          }
          /* create new call identifier: */
          sprintf (buffer, "Rhs_%d_%d", nonterms, terms);
          ex->u.call.idn = 
            IndCatStrStr 
              (StringTable (prefix),
               buffer);
          ex->u.call.params = TailPExprList(params);
#ifdef TEST
  printf ("RhsFct end\n"); 
#endif
        } else
        /*                    ---------*/
        if (ex->u.call.idn == TermFctsym)
        { ExpandTermFct (ex);
          CheckTrafoExpr (ex, isVoid);
        } else

        { message (ERROR, CatStrInd
                   ("Unknown predefined function: ",
                    ex->u.call.idn),
                   0, ex->coord);
          ex->exprKind = wrongExprKind;
          break;
        }
      } else
         CheckTrafoExprList (ex->u.call.params, 0);
      break;
    case ExprListKind:
    /* only a singleton list can be accepted as an expression: */
      if (LengthPExprList (ex->u.subList) == 1)
      { int kd = (HeadPExprList (ex->u.subList))->exprKind;
        ex->u = (HeadPExprList (ex->u.subList))->u;
        ex->exprKind = kd;
        CheckTrafoExpr (ex, isVoid);
      } else 
      { 
        DefTableKey inhcontext = 
          GetContext 
            (KeyOf (GetInheritedFrom (currCompKey, NoBinding)), NoKey);

        if (inhcontext != NoKey && !GetIsTreeSym (inhcontext, 0)) {
           message 
             (ERROR, 
              "Resulting sequence of expressions is illegal in some context",
              0, ex->coord);
           message 
             (ERROR, 
              "Symbol inherits an illegal application of RHS or TermFct",
              0, currSymbOcc->u.s.coord);
        } else
           message 
             (ERROR, 
              "Resulting sequence of expressions is illegal",
              0, ex->coord);

        ex->exprKind = wrongExprKind;
      }
      break;
    case DependKind:
      CheckTrafoExpr (ex->u.depend.ex, isVoid);
      ex->u.depend.deps = 
        ExpandExprList (ex->u.depend.deps, NULLPExprList);
      CheckTrafoExprList (ex->u.depend.deps, 1);
      break;
    case NameKind:
      if (IsPredefSym (ex->u.name))
      { if (ex->u.name == RULENAMEsym)
        { 
          ex->exprKind = StrValueKind;
          ex->u.strValue =
            GetNameSym (RuleKeyOfRuleProd (currRule), 0);
        }
        /* unchanged predefined names:
           LINEsym COLsym COORDREFsym
        */
      }
      break;
    case IntValueKind:
    case StrValueKind:
    case ChrValueKind:
    case FltValueKind:
      /* nothing to be done */
      break;
    case AttrAccRuleKind:
    case RuleAttrAccKind:
      { DefTableKey ak = 
           ex->exprKind == AttrAccRuleKind ?
             ex->u.attrAccRule.attrKey : ex->u.ruleAttrAcc.attrKey;
        int idn = GetNameSym (ak, 0);
        if (idn == GENTREEsym)
             message (ERROR, "GENTREE attribute may only be defined",
                      0, ex->coord);
        if (!isVoid && (AttrAccType (ex) == VOIDkey))
        {
          if (GetAttrTypeDefault (ak, 0))
             message (ERROR, CatStrInd
                      ("attribute with default type VOID in value context: ",
                       idn),
                      0, ex->coord);
          else
             message (ERROR, CatStrInd
                      ("VOID attribute in value context: ", idn),
                      0, ex->coord);
        }
      }
      break;
    case ConstituentsKind:
      if (!isVoid && GetType (ex->u.remote.remKey, NoKey) == NoKey)
        message (ERROR, "WITH clause is missing in value context",
                 0, ex->coord);

      if (isVoid && GetType (ex->u.remote.remKey, NoKey) != NoKey)
        message (WARNING, "WITH clause is not needed in VOID context",
                 0, ex->coord);
      if (!GetIsRuleComputation (currCompKey, 0) &&
          currSymbOcc->u.s.symbolpos > 0) {
        /* transformation in symbol computations: */
        /* CONSTITUENTS in upper context restricted to subtree */
        ex->u.remote.subtree = currSymbOcc->u.s.symbolpos;
      }

      if (GetRemoteSet (ex->u.remote.remKey, NULLSymbAttrList) == 
          NULLSymbAttrList) {
         if (isVoid) {
            /* the empty CONSTITUENTS is replaced by a dummy value: */
           ex->exprKind = IntValueKind;
           ex->u.intValue = 0;
         } else {
             /* An anomaly is encountred. But no message is issued
                to be consistent with previous Liga versions.
             */
             if (GetType (ex->u.remote.remKey, NoKey) == NoKey){
                /* WITH construct is missing */
                 ex->exprKind = IntValueKind;
                 ex->u.intValue = 0;
             } else {
                /* The CONSTITUENTS is replaced by a call of the
                   constant function given in the WITH construct: 
                */
                 ex->exprKind = CallKind;
                 ex->u.call.idn =
                    GetFunct0 (ex->u.remote.remKey, NoStrIndex);
                 ex->u.call.params = NULLPExprList;
             }
         }
         break;
      }

      /* shield clauses are not transformed */

      if (isVoid) ResetInVoidContext (ex->u.remote.remKey, 1);
         else     ResetInValueContext (ex->u.remote.remKey, 1);

      if (!isVoid) 
        CheckAllAttrsValue 
          (ex->u.remote.remKey, 0 /* not IncludingKind */, ex->coord);
      break;

    case ConstituentKind:
      if (!GetIsRuleComputation (currCompKey, 0) &&
          currSymbOcc->u.s.symbolpos > 0) {
        /* transformation in symbol computations: */
        /* CONSTITUENT in upper context restricted to subtree */
        ex->u.remote.subtree = currSymbOcc->u.s.symbolpos;
      }

      if (GetRemoteSet (ex->u.remote.remKey, NULLSymbAttrList) == 
          NULLSymbAttrList) 
        MsgEmptyRemoteSet (ex->u.remote.remKey, ex->coord);

      /* shield clauses are not transformed */

      if (isVoid) ResetInVoidContext (ex->u.remote.remKey, 1);
         else     ResetInValueContext (ex->u.remote.remKey, 1);

      if (!isVoid) 
        CheckAllAttrsValue 
          (ex->u.remote.remKey, 0 /* not IncludingKind */, ex->coord);
      break;

    case IncludingKind: 
      if (GetRemoteSet (ex->u.remote.remKey, NULLSymbAttrList) == 
          NULLSymbAttrList) 
        MsgEmptyRemoteSet (ex->u.remote.remKey, ex->coord);

      if (isVoid) ResetInVoidContext (ex->u.remote.remKey, 1);
         else     ResetInValueContext (ex->u.remote.remKey, 1);

      if (!isVoid) 
        CheckAllAttrsValue 
          (ex->u.remote.remKey, 1/* IncludingKind */, ex->coord);

      /* check Including inherited from upper symbol computation: */
      if (!GetIsRuleComputation (currCompKey, 0) &&
          currSymbOcc->u.s.symbolpos > 0) {
        ProdSymbol lhsOcc = HeadProdSymbolList (currRule->prod);
        DefTableKey lhsKey = lhsOcc->u.s.symbolkey;
        SymbAttrList sal = 
           GetRemoteSet (ex->u.remote.remKey, NULLSymbAttrList);
        while (sal != NULLSymbAttrList) {
        /* search the RemoteSet: */
          SymbAttr sa = HeadSymbAttrList (sal);
          if (lhsKey == KeyOf(SymbolBindOf(sa))) {
            /* the lhs symbol of the current rule is found,
               substitute this Including by an attribute access: */
            Environment symEnv = GetAttrScope (lhsKey, NoEnv);
            ex->exprKind = AttrAccRuleKind;
            ex->u.attrAccRule.prodSymb = lhsOcc;
            ex->u.attrAccRule.attrKey = 
                KeyOf(BindingInEnv (symEnv, AttrOf(sa)));
            ex->u.attrAccRule.isChain = 0;
            return;
          }
          sal = TailSymbAttrList (sal);
        }
      }
      break;
    case RHSKind: 
    { ExpandRHSAttr (ex);
      if (ex->exprKind != RHSKind)
         CheckTrafoExpr (ex, isVoid);
      break;
    }
    case TailAccKind:      
      { ProdSymbol symb = FindTAILSymbolOcc (currRule);
        DefTableKey chnKey = ex->u.chnKey;
        /* in rule contexts non empty rhs is checked earlier */
        if (symb == NoProdSymbol)
          { /* TAIL.c in empty rule. Search for a HEAD.c computation: */
#ifdef TEST
  printf ("CheckTrafo TAIL in empty rule line %d\n",
           LineOf(*(ex->coord)));
#endif
            DefTableKeyList eHEADs = 
              GetEmptyHEADCompsOfRule 
                 (RuleKeyOfRuleProd (currRule), NULLDefTableKeyList);
            while (eHEADs != NULLDefTableKeyList) {
              DefTableKey eHEADcomp = HeadDefTableKeyList (eHEADs);
              if (chnKey == GetEmptyHEADChain (eHEADcomp, NoKey)) {
                /* There is a HEAD computations; 
                   acess its result from its rule attribute: */
                ex->exprKind = RuleAttrAccKind;
                ex->u.ruleAttrAcc.attrKey = 
                   GetEmptyHEADAttr (eHEADcomp, NoKey);
#ifdef TEST
  printf ("CheckTrafo TAIL line %d: found an attr with HEAD result; chain %s\n",
           LineOf(*(ex->coord)), StringTable (GetNameSym (chnKey, 0)));
#endif
                return;
              }
              eHEADs = TailDefTableKeyList (eHEADs);
            }
            /* There is no HEAD computation in this context;
               substitute chainacc of lhs symbol: */
            ex->exprKind = AttrAccRuleKind;
            ex->u.attrAccRule.prodSymb = 
              HeadProdSymbolList (currRule->prod);
            ex->u.attrAccRule.attrKey = chnKey;
            ex->u.attrAccRule.isChain = 1;
            return;
          }
        /* There is a rhs symb to access the chain TAIL from: */
        ex->exprKind = AttrAccRuleKind;
        ex->u.attrAccRule.prodSymb = symb;
        ex->u.attrAccRule.attrKey = chnKey;
        ex->u.attrAccRule.isChain = 1;
        break;
      }
    case LoopKind:
    { /* loop computation within assign (until cond do attr = iter): */
      /* add to list of loop attributes of this rule: */
      loopAttributes =
        ConsPExprList (ex->u.loop.attr, loopAttributes);
#ifdef TEST
  printf ("expr loop:  store ITER attr line %d\n",
          LineOf(*(ex->u.loop.attr->coord)));
#endif
     CheckTrafoExpr 
        (ex->u.loop.iter, 
         AttrAccType (ex->u.loop.attr) == VOIDkey);
      CheckTrafoExpr (ex->u.loop.cond, 0);
      break;
    }
    case AssignKind:
    case AttrAccSymbKind:
    case SymbTermAccKind:
    case wrongExprKind:
    case HeadAccKind:
      /* should not occur */
#ifdef TEST
  printf ("CheckTrafo wrong kind: %d\n", ex->exprKind);
#endif
    case RuleTermAccKind:
    default:;
      /* no check or transformation required */
  }
}/* CheckTrafoExpr */

/* symbol occurrences that have a GENTREE assignment are collected.
   They are checked against the insertion symbols.
*/
static ProdSymbolList gentreeAssigned;

#if defined(__cplusplus) || defined(__STDC__)
void CheckGentreeComplete (ProdSymbolList prod, ProdSymbolList assigned)
#else
void CheckGentreeComplete (prod, assigned)
  ProdSymbolList prod, assigned;
#endif
{ 
  while (prod != NULLProdSymbolList)
  { ProdSymbol sy = HeadProdSymbolList (prod);
    if (sy->kind == IsProdGenSymbol)
      { ProdSymbolList asg = assigned; 
        int found = 0;
        while (!found && asg != NULLProdSymbolList)
        { ProdSymbol s = HeadProdSymbolList (asg);
          if (s == sy) found = 1;
          asg = TailProdSymbolList (asg);
        }
        if (!found)
          message (ERROR, "GENTREE computation missing",
                   0, sy->u.s.coord);
      }
    prod = TailProdSymbolList (prod);
  }
}/* CheckGentreeComplete */

#if defined(__cplusplus) || defined(__STDC__)
void CheckLhsAttr (PExpr ex)
#else
void CheckLhsAttr (ex) PExpr ex;
#endif
{ DefTableKey ak; int idn;
  if (ex == wrongExpr || ex->exprKind == wrongExprKind) 
    return;

  if (ex->exprKind == HeadAccKind)
      { ProdSymbol symb = FindHEADSymbolOcc (currRule);
        DefTableKey chnKey = ex->u.chnKey;
        DefTableKey genRuleAttr = 
          GetEmptyHEADAttr (currCompKey, NoKey);
        if (genRuleAttr != NoKey)
        /* HEAD access substituted by generated rule attribute: */
          { ex->exprKind = RuleAttrAccKind;
            ex->u.ruleAttrAcc.attrKey = genRuleAttr;
            return;
          }
        /* HEAD access substituted by rhs chain access: */
        ex->exprKind = AttrAccRuleKind;
        ex->u.attrAccRule.prodSymb = symb;
        ex->u.attrAccRule.attrKey = chnKey;
        ex->u.attrAccRule.isChain = 1;
        return;
      }
  
  if (ex->exprKind != AttrAccRuleKind && 
      ex->exprKind != RuleAttrAccKind)
    return;

  ak = ex->exprKind == AttrAccRuleKind ?
    ex->u.attrAccRule.attrKey : ex->u.ruleAttrAcc.attrKey;

  idn = GetNameSym (ak, 0);
  if (idn != GENTREEsym)
    return;

  if (ex->exprKind == RuleAttrAccKind)
  { message (ERROR, "GENTREE may not be a RULE attribute",
             0, ex->coord);
    return;
  }

  if (currSymbOcc->kind != IsProdGenSymbol)
  { message
        (ERROR, 
         "This symbol occurrence must not have a GENTREE computation",
         0, currSymbOcc->u.s.coord);
 
    message 
        (ERROR, 
         "GENTREE may only be used at a tree insertion",
         0, ex->coord);
    return;
  }
#ifdef TEST
  printf ("GENTREE found for symbol %s:\n", 
     StringTable (GetNameSym (currSymbOcc->u.s.symbolkey, 0)));
#endif
  gentreeAssigned = ConsProdSymbolList (currSymbOcc, gentreeAssigned);
}/* CheckLhsAttr */

#if defined(__cplusplus) || defined(__STDC__)
void CheckTrafo (Binding compBind)
#else
void CheckTrafo (compBind) Binding compBind;
#endif
/* on entry
     compBind is the binding of a rule computation.
     3 global variables are set:
     currCompKey is set to the key of the current computation;
     currRule is set to the current rule;
     currSymbOcc is set to the symbol occurrence of the current computation.
     For computations of rule attributes and for 
     plain computations in rule context currSymbOcc is the
     left-hand side symbol occurrence.
   on exit
     The following  checks and transformations are made for 
     rule computations:
     - illegal use of void attributes
     - with clause in value CONSTITUENTS
     - value or void propagation for INCLUDING and CONSTITUENTS
     - distinction of a CONSTITUENTS if it is inherited to
       rules such that they differ in the SHIELD symbol
     - expansion of the RHS construct
     - check for the existence of the RHS attributes
     - substitution of abbreviations for rule names and functions
     - check of inherited terminal access
     - symbol positions for HEAD and TAIL
     - handle rule attributes
*/
{ DefTableKey compKey = KeyOf (compBind);
  PExpr compute = GetCompRepr (compKey, wrongExpr);
  if (compute == wrongExpr) return;

  currCompKey = compKey;

  switch (compute->exprKind)
  { case AssignKind: 
      /* attribute assign: */
      CheckLhsAttr (compute->u.assign.left);
      CheckTrafoExpr 
        (compute->u.assign.right, 
         AttrAccType (compute->u.assign.left) == VOIDkey);
      break;
    case LoopKind:
      /* loop computation (until cond do attr = iter): */
      /* add to list of loop attributes of this rule: */
      loopAttributes =
        ConsPExprList (compute->u.loop.attr, loopAttributes);
#ifdef TEST
  printf ("plain loop:  store ITER attr line %d\n",
          LineOf(*(compute->u.loop.attr->coord)));
#endif
     CheckTrafoExpr 
        (compute->u.loop.iter, 
         AttrAccType (compute->u.loop.attr) == VOIDkey);
      CheckTrafoExpr (compute->u.loop.cond, 0);
      break;
    case wrongExprKind:
      break;
    default:
      /* plain computation: */
#ifdef TEST
      printf ("CheckTrafo plain\n");
#endif
      CheckTrafoExpr (compute, 1);
  }
}/* CheckTrafo */


#if defined(__cplusplus) || defined(__STDC__)
int sameAttrAcc (PExpr lex, PExpr rex)
#else
int sameAttrAcc (lex, rex) PExpr lex, rex;
#endif
{ if (lex == wrongExpr || rex == wrongExpr) return 0;
  if (lex->exprKind != rex->exprKind) return 0;

  if (lex->exprKind == AttrAccRuleKind) {
#ifdef TEST
  printf ("  sameAttrAcc lines %d and %d\n",
          LineOf(*(lex->coord)), LineOf(*(rex->coord)));
#endif

    return (lex->u.attrAccRule.prodSymb == rex->u.attrAccRule.prodSymb &&
            lex->u.attrAccRule.attrKey == rex->u.attrAccRule.attrKey &&
            lex->u.attrAccRule.isChain == rex->u.attrAccRule.isChain);
  } else
  if (lex->exprKind == RuleAttrAccKind) {
    return (lex->u.ruleAttrAcc.attrKey == rex->u.ruleAttrAcc.attrKey);
  } else 
    return 0; /* chain attr or symbol context are not allowed here */
}/*sameAttrAcc  */


#if defined(__cplusplus) || defined(__STDC__)
void CheckLoopInit (DefTableKeyList allRuleComps, 
                    PExprList loopAttributes)
#else
void CheckLoopInit (allRuleComps, loopAttributes)
        DefTableKeyList allRuleComps;
        PExprList loopAttributes;
#endif
/* on entry
     allRuleComps is a list of keys of all computations of this rule.
     loopAttributes is a list of attribute accesses that occur as
     iteration attribute in a loop construct in any computation of
     this rule.
on exit:
     For every attribute in loopAttributes it is checked whether there
     is an assignment in allRuleComps. The key of that computation is 
     marked IsLoopInit
*/
{ 
#ifdef TEST
  printf ("CheckLoopInit begin\n");
#endif
  while (loopAttributes != NULLPExprList) {
    PExpr attrexpr = HeadPExprList (loopAttributes);
    DefTableKeyList comps = allRuleComps;
#ifdef TEST
  printf ("  find an assign to ITER attr line %d\n",
          LineOf(*(attrexpr->coord)));
#endif
    while (comps != NULLDefTableKeyList) {
      DefTableKey comp = HeadDefTableKeyList (comps);
      PExpr repr = GetCompRepr (comp, wrongExpr);
      if (repr != wrongExpr && repr->exprKind == AssignKind &&
          sameAttrAcc (repr->u.assign.left, attrexpr)) {
         ResetIsLoopInit (comp, 1);
#ifdef TEST
  printf ("  found an assign to ITER attr line %d\n",
          LineOf(*(repr->coord)));
#endif
         break;
      }
      comps = TailDefTableKeyList (comps);
    }
    if (comps == NULLDefTableKeyList) {
      message (ERROR, "Missing initialisation of ITER attribute",
               0, attrexpr->coord);
    }
    loopAttributes = TailPExprList (loopAttributes);
  }
#ifdef TEST
  printf ("CheckLoopInit end\n");
#endif
}/* CheckLoopInit */

void CheckRuleComps ()
/* on entry:
     All inherited computations have a representation which is
     instantiated from the original symbol computation
   on exit:
     checks and transformations are made for each rule computation
     as described by CheckTrafo;
     a list of keys is formed with the key of each computation 
     of a rule; it is associated by the property AllRuleComps
*/{
 RuleProdList rules;
  Binding rulecomp;
  /* step through all rules: */
#ifdef TEST
  printf ("CheckRuleComps started\n"); 
#endif
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { ProdSymbolList prod;
    DefTableKey ruleKey;
    DefTableKeyList allRuleComps;
    Environment ruleScope;
    int inRootRule = 0;

    currRule = HeadRuleProdList (rules);
    ruleKey = RuleKeyOfRuleProd (currRule);
    allRuleComps = NULLDefTableKeyList;
    ruleScope = GetLowerScope (ruleKey, NoEnv);
    gentreeAssigned = NULLProdSymbolList;
    loopAttributes = NULLPExprList;
#ifdef TEST
  printf ("RULE %s:\n", 
     StringTable (GetNameSym (ruleKey, 0)));
#endif
    /* step through all computations associated to the ruleKey */
    currSymbOcc = HeadProdSymbolList (currRule->prod);
    rulecomp = DefinitionsOf(ruleScope);
    while (rulecomp != NoBinding)
    {
#ifdef TEST
  printf ("rule attr comp\n"); 
#endif
      CheckTrafo (rulecomp);
      allRuleComps = ConsDefTableKeyList (KeyOf(rulecomp), allRuleComps);
      rulecomp = NextDefinition(rulecomp);
    }
    /* step through all nonterminal occurrences of production: */
    prod = currRule->prod;
    while (prod != NULLProdSymbolList)
    { currSymbOcc = HeadProdSymbolList (prod);
      if (currSymbOcc->kind != IsProdLiteral && 
          !GetIsTerm (currSymbOcc->u.s.symbolkey, 0))
      { Environment syenv = currSymbOcc->u.s.scope;
        Environment attrenv = 
            GetAttrScope (currSymbOcc->u.s.symbolkey, NoEnv);
        Binding genattr = BindingInEnv (attrenv, GENTREEsym);
#ifdef TEST
  printf ("symbol %s:\n", 
     StringTable (GetNameSym (currSymbOcc->u.s.symbolkey, 0)));
#endif
        if (currSymbOcc->u.s.symbolkey == GrammarRoot)
                inRootRule = 1;
        /* step through all computations of this symbol occurrence */
        rulecomp = DefinitionsOf(syenv);
        while (rulecomp != NoBinding)
        { 
          CheckTrafo (rulecomp);
          allRuleComps = 
            ConsDefTableKeyList (KeyOf(rulecomp), allRuleComps);
          rulecomp = NextDefinition(rulecomp);
        }
        if (currSymbOcc->u.s.symbolpos > 0 &&
            currSymbOcc->kind != IsProdGenSymbol &&
            genattr != NoBinding) {
            /* a dummy computation for currSymbOcc.GENATTR is generated: */
            DefTableKey genCompKey = NewKey ();
            ResetIsGenTreeDummy (genCompKey, 1);
            ResetCompRepr
              (genCompKey,
               newAttrAccRule 
                  (currSymbOcc, 
                   KeyOf (genattr), 0, currSymbOcc->u.s.coord));

            allRuleComps = 
              ConsDefTableKeyList (genCompKey, allRuleComps);

        }
      }
      if (currRule->islistof) break;
      prod = TailProdSymbolList (prod);
    }
    CheckGentreeComplete (currRule->prod, gentreeAssigned);
    CheckLoopInit (allRuleComps, loopAttributes);
    ResetAllRuleComps (ruleKey, allRuleComps);
    rules = TailRuleProdList (rules);
  }
#ifdef TEST
  printf ("CheckRuleComps completed\n"); 
#endif
}/* CheckRuleComps */
