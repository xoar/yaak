
#include "Accumulate.h"
#include "pdl_gen.h"
#include "Strings.h"
#include "Attribute.h"
#include "RuleProdList.h"
#include "CompRepr.h"
#include "PreDefId.h"

#ifdef ACCUTEST
#define ACCUTEST
#include <stdio.h>
#endif

#define ZeroCoord (&NoCoord)

extern RuleProdList GrammarRules;

extern void instantiateExpr(); 

void AccumulateExpr (DefTableKey compKey, PExpr expr) {
/* on entry:
     compKey is the key of an accumulating computation,
     expr is the internal representation of that assignment,
       or part of it.
   on exit:
     expr is recursively decomposed into its lhs attribute, 
     its executable part, and its dependences. 
     The 3 components are added to the properties of compKey
*/
#ifdef ACCUTEST
  printf ("AccumulateExpr \n");
#endif
  if (expr == NULLPExpr) return;

#ifdef ACCUTEST
  printf ("  kind %d line %d\n", expr->exprKind, LineOf (*(expr->coord)));
#endif

  switch (expr->exprKind)
  {  
  case CallKind: /* may be executable */
  case NameKind:
    ResetAccuExecList (compKey,
      ConsPExprList (expr, GetAccuExecList (compKey, NULLPExprList)));
    return;
  case IntValueKind: /* not executable, no dependence */
  case StrValueKind:
  case ChrValueKind:
  case FltValueKind:
  case SymbTermAccKind:
  case RuleTermAccKind:
  case RHSKind:
    return;
  case AttrAccRuleKind: /* dependence only */
  case RuleAttrAccKind:
  case AttrAccSymbKind:
  case IncludingKind:
  case ConstituentKind:
  case ConstituentsKind:
  case HeadAccKind:
  case TailAccKind:
    ResetAccuDepList (compKey,
      ConsPExprList (expr, GetAccuDepList (compKey, NULLPExprList)));
    return;
  case DependKind:
    ResetAccuDepList (compKey,
      AppPExprList (expr->u.depend.deps, 
        GetAccuDepList (compKey, NULLPExprList)));
    AccumulateExpr (compKey, expr->u.depend.ex);
    return;
  case AssignKind:
    ResetAccuLhs (compKey, expr->u.assign.left);
    AccumulateExpr (compKey, expr->u.assign.right);
    return;
  case LoopKind:
  case ExprListKind:
  case wrongExprKind: /* illegal expression */
    message (FATAL, "System: illegal expression", 0, expr->coord);
    return;
  default: ; /* does not occur */
  }/* switch exprKind */
}/* AccumulateExpr */

PExpr ex42;

Binding MakeAnAccuBinding 
   (Environment sc, Binding attr, DefTableKey context, CoordPtr co) {

  Binding res = BindIdn (sc, IdnOf(attr));
#ifdef ACCUTEST
  printf ("MakeAnAccuBinding line %d\n", LineOf (*co));
#endif
  ResetAttribute (KeyOf (res), KeyOf (attr));
  ResetContext (KeyOf (res), context);
  ResetCoord (KeyOf (res), co);
  ResetIsAccu (KeyOf (res), 1);
  return res;
}/* MakeAnAccuBinding */

PExpr MakeAccuAssign (DefTableKey compKey) {
/* on entry:
     compKey is a computation key; its AccuLhs property must be set
   on exit:
     an expression of type AssignKind is returned, constructed from the 
     three accu properties of compKey
*/
  PExpr lhs      = GetAccuLhs (compKey, NULLPExpr);
  PExprList exec = GetAccuExecList (compKey, NULLPExprList);
  PExprList deps = GetAccuDepList (compKey, NULLPExprList);
  PExpr res; 
  CoordPtr coord;

#ifdef ACCUTEST
  printf ("MakeAccuAssign begin lhs ok %d\n", lhs != NULLPExpr);
#endif
  if (lhs == NULLPExpr) return wrongExpr;

  coord = lhs->coord;

#ifdef ACCUTEST
  printf ("  line %d\n", LineOf (*coord));
#endif

  if (exec == NULLPExprList) 
     res = ex42;
  else if (TailPExprList (exec) == NULLPExprList)
     res = HeadPExprList (exec);
  else 
     res = newCall (ORDERsym, exec, coord);

  if (deps == NULLPExprList)
     res = newAssign (lhs, res, coord);
  else 
     res = newAssign (lhs, newDepend (res, deps, coord), coord);
#ifdef ACCUTEST
  printf ("MakeAccuAssign end\n");
#endif
  return res;
}/* MakeAccuAssign */


void AccumulateAnInhComp (Binding symComp, Binding inhComp) {
/* on entry:
     symComp is an accumulating computation in a TREE symbol context.
     It inherits accumulated computations from inhComp.
   on exit:
     The accumulated computations from inhComp are accumulated.
     The xref properties of ruleComp and inhComp are set.
     It is checked that inhComp is accumulating and 
     has the type VOID.
*/ 
   DefTableKey symKey = KeyOf (symComp);
   DefTableKey inhAttr = GetAttribute (KeyOf (inhComp), NoKey);
   PExprList elst = GetAccuExecList (KeyOf (inhComp), NULLPExprList);

#ifdef ACCUTEST
  printf ("AccumulateAnInhComp line %d inherits from %d\n",
          LineOf (*(GetCoord(KeyOf(symComp), ZeroCoord))),
          LineOf (*(GetCoord(KeyOf(inhComp), ZeroCoord))));
#endif

   while (elst != NULLPExprList) {
     ResetAccuExecList 
       (symKey,
        ConsPExprList 
          (HeadPExprList (elst), GetAccuExecList (symKey, NULLPExprList)));
     elst = TailPExprList (elst);
   }

   elst = GetAccuDepList (KeyOf (inhComp), NULLPExprList);
   while (elst != NULLPExprList) {
     ResetAccuDepList 
       (symKey,
        ConsPExprList 
          (HeadPExprList (elst), GetAccuDepList (symKey, NULLPExprList)));
     elst = TailPExprList (elst);
   }

   ResetAccuLhs (symKey, GetAccuLhs (KeyOf (inhComp), NULLPExpr));

   /* The property yields an xref list of those computation which 
      are affected by the inherited computation: */
   ResetInheritedBy (KeyOf (inhComp),
     ConsDefTableKeyList (KeyOf (symComp), 
                          GetInheritedBy (KeyOf (inhComp), 
                                          NULLDefTableKeyList)));

   if (!(GetIsAccu (KeyOf (inhComp), 0))) {
      message (ERROR, CatStrInd ("Is inherited by an accumulating computation: ",
                                 GetNameSym (inhAttr, 0)),
               0, GetCoord (KeyOf (inhComp), ZeroCoord));
      message (ERROR, CatStrInd ("Inherits a non-accumulating computation: ",
                                 GetNameSym (inhAttr, 0)),
               0, GetCoord (KeyOf (symComp), ZeroCoord));
   }
#ifdef ACCUTEST
  printf ("AccumulateAnInhComp end\n");
#endif
}/* AccumulateAnInhComp */

extern Environment RootEnv; /* exported by AlgScope.h */

int InheritAttrAccu (Binding attr)
/* on entry:
     attr is a binding of an attribute in an attribute
     scope of a symbol
   on exit:
     The HasAccuAsgn property is propagated along the
     inheritance chain down to the TREE symbol.
     The property ist returned as result.
*/
{ DefTableKey attrkey; 
  int accu, triedInh = 0;
  Environment atenv;
  Binding over;

  if (attr == NoBinding) return 0;

  attrkey = KeyOf (attr);
  accu = GetHasAccuAsgn (attrkey, 0);

  /* avoid multiple analysis in case of 
     multiple inheritance:
  */
  if (GetHasAccuAsgnDone (attrkey, 0)) return accu;
  ResetHasAccuAsgnDone (attrkey, 1);

  /* a deep search through overridden bindings
     establishes all class properties there 
  */
  atenv = EnvOf (attr);
  over = OverridesBinding (attr);
  while (over != NoBinding)
  {
    int inhaccu = InheritAttrAccu (over);
    accu = (inhaccu || accu);
    over = NextInhBinding (atenv, over);
  }

  ResetHasAccuAsgn (attrkey, accu);
  return accu;
}/* InheritAttrAccu */

void AccuInheritAtTreeSymbs (Environment globEnv) {
/* on entry:
       The internal representations of all single accumulating computations
       have been associated to the properties AccuLhs, AccuExecList, 
       AccuDepList of the computation key.
       The other Accu-properties are set.
       The inheritance relations in the computation scopes are established.
       The attribute types are determined.
   on exit:
       Each TREE symbol X has collected the accumulated computations from
       any CLASS Symbol it inherits from, stored in its properties AccuLhs, 
       AccuExecList, AccuDepList of X's computation key.
*/
  Binding symBind = DefinitionsOf (globEnv);

#ifdef ACCUTEST
  printf ("AccuInheritAtTreeSymbs begin\n");
#endif

  while (symBind != NoBinding) {
    DefTableKey symKey = KeyOf (symBind);
    if (GetIsNonterm (symKey, 0) && GetIsTreeSym (symKey, 0)) {
       Environment attrenv = GetAttrScope (symKey, NoEnv);
       Binding attr;
       Environment symLowScope = GetLowerScope (symKey, NoEnv);
       Environment symUpScope = GetUpperScope (symKey, NoEnv);
 
      /* search all attributes of this symbol for accumulating ones: */
         attr = DefinitionsOf (attrenv);
         while (attr != NoBinding) {
          if (InheritAttrAccu (attr)) {
             int attrId = IdnOf (attr);
             int attrCl = GetAttrClass (KeyOf (attr), NoClass);
             Environment symScope = 
                (attrCl == SYNTClass ? symLowScope : symUpScope);
             Binding inhComp, classSym;
             Binding symComp = BindingInEnv (symScope, attrId);
#ifdef ACCUTEST
  printf ("    accu attribute %s.%s\n",
     StringTable (GetNameSym (symKey, 0)),
     StringTable (attrId));
#endif
             if (symComp == NoBinding) {
                /* no symbol computation, no inherited computation 
                   create a symbol computation */
                symComp = 
                   MakeAnAccuBinding (symScope, attr, symKey, 
                                      GetCoord (symKey, ZeroCoord));
                ResetAccuLhs (KeyOf (symComp), 
                              newAttrAccSymb (symKey, KeyOf (attr), 0, 
                                              GetCoord (symKey, ZeroCoord)));
                break; /* no further action for this attr */
             } else if (EnvOf (symComp) == symScope) {
                inhComp = OverridesBinding (symComp);
                if (inhComp == NoBinding) 
                    /* a symbol computation, no inherited computation */
                    break; /* no action for this attr */
                /* else a symbol computation, an inherited computation */
             } else {
                /* no symbol computation, only inherited computations */
                /* create a symbol computation: */
                inhComp = symComp;
                symComp = 
                   MakeAnAccuBinding (symScope, attr, symKey, 
                                      GetCoord (symKey, ZeroCoord));
                ResetInheritedFrom (KeyOf (symComp), inhComp);
                ResetAccuLhs (KeyOf (symComp), 
                              newAttrAccSymb (symKey, KeyOf (attr), 0, 
                                              GetCoord (symKey, ZeroCoord)));
             }
             /* There are inherited computations to be accumulated on symComp: 
                We step through all symbols and search in their 
                computation scopes inhCompScope which 
                     Inheritsfrom (symScope, inhCompScope), 
                whether it has a computation to be accumulated on symComp.
             */
#ifdef ACCUTEST
  printf ("    there are inherited computations for %s.%s\n",
     StringTable (GetNameSym (symKey, 0)),
     StringTable (attrId));
#endif
             classSym = DefinitionsOf (globEnv);
             while (classSym != NoBinding) {
               DefTableKey k = KeyOf (classSym);
               if (k != symKey && GetIsSymbol (k, 0)) {
                  Environment inhCompScope =
                    (attrCl == SYNTClass ? 
                     GetLowerScope (k, NoEnv) : GetUpperScope (k, NoEnv));
                  if (Inheritsfrom (symScope, inhCompScope)) {
                     /* inheritance relation holds */
#ifdef ACCUTEST
  printf ("    inherits from class %s\n", StringTable (GetNameSym (k, 0)));
#endif
                     Binding attrComp = DefinitionsOf (inhCompScope);
                     while (attrComp != NoBinding) {
                       if (IdnOf (attrComp) == attrId) {
                           if (!GetIsAccu (KeyOf (attrComp), 0)) {
                             message (ERROR, 
                               CatStrInd ("Is inherited by an accumulating computation: ",
                                          attrId), 0, 
                               GetCoord (KeyOf(attrComp), ZeroCoord));
                               break;
                          } else if (GetIsTreeSym (k, 0)) {
                             message (ERROR, 
                               CatStrInd ("Can not inherit from a TREE symbol: ",
                                 attrId), 0, GetCoord (KeyOf(attrComp), ZeroCoord));
                             break;
                         } /* IsClass */
                         /* this computation is to be accumulated to symComp */

                         AccumulateAnInhComp (symComp, attrComp);

                         /* there is only one such computation in a scope: */
                         break;
                       }/* attr comps of this class symb */
                       attrComp = NextDefinition (attrComp);
                     }/* end search for a computation in a super scope */
                  }/* a super scope */
               }/* a symbol */
               classSym = NextDefinition (classSym);
             }/* a global definition */
          } /* accu attr */
          attr = NextDefinition (attr);
       }/* attributes */
    }/* IsTreeSym */
    symBind = NextDefinition (symBind);
  }/* definitions */
#ifdef ACCUTEST
  printf ("AccuInheritAtTreeSymbs end\n");
#endif
}/* AccuInheritAtTreeSymbs */

void AccumulateInherit (Environment globEnv) {
/* on entry:
       The internal representations of all single accumulating computations
       have been associated to the properties AccuLhs, AccuExecListe, 
       AccuDepList of the computation key.
       The other Accu-properties are set.
       The inheritance relation in the computation scopes are established.
       The attribute types are determined.
   on exit:
       AccuInheritAtTreeSymbs collects for every TREE symbol the inherited
         accumulated computations.
       for every rule 
          the rule the accumulating rule computations are collected, and 
          for every symbol occurrence symocc
            the accumulating computations are instantiated from the corresponding
            TREE symbols.
*/
  RuleProdList rules;
#ifdef ACCUTEST
  printf("AccumulateInherit begin\n");
#endif
  ex42 = newIntValue (42, ZeroCoord);

  AccuInheritAtTreeSymbs (globEnv);
  /* for each accu. attr. of each TREE symbol all computations inherited 
     from CLASS symbols are combined in the 3 accu properties of the TREE symbol
     now
     instantiate the computations from TREE symbols to symbol occurrences:
  */

  /* step through all productions: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList prod = rule->prod;
    DefTableKey ruleKey = RuleKeyOfRuleProd (rule);
    Binding rulecomp;
    Environment ruleScope = GetLowerScope (ruleKey, NoEnv);
    int symbolIndex = -1;
#ifdef ACCUTEST
  printf ("RULE %s:\n", 
     StringTable (GetNameSym (ruleKey, 0)));
#endif
    /* search the rule attributes for accumulating computations: */
    rulecomp = DefinitionsOf(ruleScope);
    while (rulecomp != NoBinding)
    { if (GetIsAccu (KeyOf (rulecomp), 0)) {
         /* The computations for this attribute have been accumulated
            in three properties; combine them into one assign: */
         ResetCompRepr 
            (KeyOf (rulecomp), MakeAccuAssign (KeyOf (rulecomp)));
      }
      rulecomp = NextDefinition(rulecomp);
    }

    /* step through all nonterminal occurrences of this production: */
    while (prod != NULLProdSymbolList) { 
      ProdSymbol sy = HeadProdSymbolList (prod);
      DefTableKey symKey = sy->u.s.symbolkey;
      if (sy->kind != IsProdLiteral && !GetIsTerm (symKey, 0)) { 
        Environment syCompScope = sy->u.s.scope;
        Environment attrenv = GetAttrScope (symKey, NoEnv);
        Binding attr = DefinitionsOf (attrenv);
        symbolIndex++;

#ifdef ACCUTEST
  printf ("   symbol no. %d %s\n", symbolIndex, 
     StringTable (GetNameSym (symKey, 0)));
#endif
        /* search all attributes of this symbol for accumulating ones: */
        while (attr != NoBinding) {
          if (GetHasAccuAsgn (KeyOf (attr), 0) &&
              ((symbolIndex > 0 && 
                GetAttrClass (KeyOf (attr), NoClass) == INHClass) ||
               (symbolIndex == 0 && 
                GetAttrClass (KeyOf (attr), NoClass) == SYNTClass))) {
             int attrId = IdnOf (attr);
             /* symbol symKey has an accumulating attribute named attrId */
             Binding symOccAttrComp = BindingInEnv (syCompScope, attrId);
             Binding symAttrComp;
             PExpr assign;

#ifdef ACCUTEST
  printf ("    attribute %s.%s\n",
     StringTable (GetNameSym (symKey, 0)),
     StringTable (GetNameSym (KeyOf (attr), 0)));
#endif
             if (symOccAttrComp == NoBinding) {
                /* no computation exists for this attr at all, create one: */
                symOccAttrComp =
                   MakeAnAccuBinding (syCompScope, attr, ruleKey, ZeroCoord);
                ResetCompRepr (KeyOf (symOccAttrComp),
                     newAssign (newAttrAccRule (sy, KeyOf (attr), 0, ZeroCoord),
                                ex42, ZeroCoord));
             } else if (EnvOf (symOccAttrComp) != syCompScope) {
               /* there are computations to be inherited */
               /* there is no computation in the symbol occurrence,
                  we create one: */
               symAttrComp = symOccAttrComp;
               symOccAttrComp = 
                 MakeAnAccuBinding (syCompScope, attr, ruleKey, 
                     GetCoord (KeyOf (symAttrComp), ZeroCoord));
               ResetInheritedFrom (KeyOf (symOccAttrComp), symAttrComp);

               assign =
                  copyExpr (MakeAccuAssign (KeyOf (symAttrComp)));
               instantiateExpr (assign, rule, sy);
               ResetCompRepr (KeyOf (symOccAttrComp), assign);
               ResetIsBottomUp (KeyOf(symOccAttrComp), 
                 GetIsBottomUp (KeyOf(symAttrComp), 0));
             } else {
                  symAttrComp = OverridesBinding (symOccAttrComp);
                  if (symAttrComp == NoBinding) {
                     /* there are no symbol computations,
                        combine the 3 properties in rule context:
                     */
                     ResetCompRepr (KeyOf (symOccAttrComp), 
                                    MakeAccuAssign (KeyOf (symOccAttrComp)));
                  } else {
                       /*  There are properties in symbol context (symAttrComp)
                           and 3 properties in the symbol occurrence (symOccAttrComp).
                           Instantiate the symbol computation:
                       */
                     assign = copyExpr (MakeAccuAssign (KeyOf(symAttrComp)));
                     instantiateExpr (assign, rule, sy);
                     /* decompose assign onto symOccAttrComp: */
                     AccumulateExpr (KeyOf (symOccAttrComp), assign);
                     /* compose the 3 properties into an assign: */
                     assign = MakeAccuAssign (KeyOf (symOccAttrComp));
                     ResetCompRepr (KeyOf (symOccAttrComp), assign);
                  }
             }
          }/* an accumulating attribute of the symbol occurrence */
          attr = NextDefinition (attr);
        }/* the attributes of the symbol occurrence */
      }/* is a non-terminal occurrence in the rule */
      if (rule->islistof) break; /* lhs only */
      prod = TailProdSymbolList (prod);
    }/* all rule elements */
    rules = TailRuleProdList (rules);
  }/* all rules */
#ifdef ACCUTEST
  printf("AccumulateInherit end\n");
#endif
}/* AccumulateInherit */
