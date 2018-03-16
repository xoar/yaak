
#include "Compute.h"
#include "pdl_gen.h"
#include "GrammarRules.h"
#include "Grammar.h"
#include "csm.h"
#include "Attribute.h"
#include "MakeName.h"
#include "Strings.h"
#include "PreDefId.h"
#include "Inherit.h"
#include "SymbolOcc.h"

#if defined(__cplusplus) || defined(__STDC__)
Binding AddCoordToBinding (Binding b, CoordPtr c)
#else
Binding AddCoordToBinding (b, c) Binding b; CoordPtr c;
#endif
{ ResetCoord (KeyOf (b), c);
  return b;
}

#if defined(__cplusplus) || defined(__STDC__)
Binding AddAttrToBinding (Binding b, DefTableKey a)
#else
Binding AddAttrToBinding (b, a) Binding b; DefTableKey a;
#endif
{ ResetAttribute (KeyOf (b), a);
  return b;
}

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
Binding BindNewPlainComp 
   (Environment compScope, Environment attrScope, CoordPtr c)
#else
Binding BindNewPlainComp (compScope, attrScope, c)
   Environment compScope, attrScope; CoordPtr c;
#endif
{ int sym = GenerateName ("plain$");
  Binding comp = BindIdn (compScope, sym);
  Binding attr = BindIdn (attrScope, sym);
#ifdef TEST
  printf ("BindNewPlainComp %s\n", StringTable(sym));
#endif
  ResetAttribute (KeyOf (comp), KeyOf (attr));
  ResetCoord (KeyOf (comp), c);
  ResetAttrClass (KeyOf (attr), SYNTClass);
  ResetAttrType (KeyOf (attr), VOIDkey);
  ResetNameSym (KeyOf (attr), sym);
  ResetCoord (KeyOf (attr), c);
  ResetIsDefined (KeyOf (attr), 1);
  ResetIsPlain (KeyOf (attr), 1);
  ResetIsPlain (KeyOf (comp), 1);
  return comp;
}/* BindNewPlainComp */

#ifdef TEST
void PrintCompute (Binding b)
{ int sym; Binding inh;
  if (b == NoBinding) return;
  sym = GetNameSym (KeyOfEnv (EnvOf (b)), 0);
  inh = GetInheritedFrom (KeyOf (b), NoBinding);
  if (inh == NoBinding)
    printf ("  %s.%s is rule comp in line %d\n", 
            StringTable (sym), StringTable (IdnOf (b)),
            LineOf (*GetCoord (KeyOf (b), NoPosition)));
  else
    printf ("  %s.%s inherited from %s in line %d\n",
            (EnvOf(inh) == GetHEADScope (KeyOfEnv (EnvOf (inh)), NoEnv))?
               "HEAD" : StringTable (sym), 
            StringTable (IdnOf (b)),
            StringTable (GetNameSym (KeyOfEnv (EnvOf (inh)), 0)),
            LineOf (*GetCoord (KeyOf (inh), NoPosition)));
}

#endif

#if defined(__cplusplus) || defined(__STDC__)
PTGNode InhCompOutput (DefTableKey comp)
#else
PTGNode InhCompOutput (comp) DefTableKey comp;
#endif
{ DefTableKeyList rulecomps = GetInheritedBy (comp, NULLDefTableKeyList);
  PTGNode res = PTGNULL;
  while (rulecomps != NULLDefTableKeyList)
  { DefTableKey rulecomp = HeadDefTableKeyList (rulecomps);
    res = PTGCommaSeq (res, 
       PTGNumb (LineOf (*GetCoord (GetContext (rulecomp, NoKey), NoPosition))));
    rulecomps = TailDefTableKeyList (rulecomps);
  }
  return PTGInhComp 
    (PTGNumb (LineOf (*GetCoord (comp, NoPosition))), res);
}/* InhCompOutput */


void InheritAComputation 
#if defined(__cplusplus) || defined(__STDC__)
   (Binding srcComp, Binding attr, Environment tgtEnv, DefTableKey rule,
    DefTableKey emptyHEADattr)
#else
   (srcComp, attr, tgtEnv, rule)
   Binding srcComp, attr; Environment tgtEnv; DefTableKey rule;
   DefTableKey emptyHEADattr;
#endif
/* on Entry:
     srcComp is a binding of a computation of attr in some symbol
     scope, in the context of rule.
   on exit:
     A new binding is created for a computation of attr in tgtEnv.
     Its properties are set and it is linked to the 
     inherited computation (srcComp, InheritedFrom).
*/
{
  Binding newcomp = BindIdn (tgtEnv, IdnOf (attr));
  DefTableKey defattr = GetAttribute (KeyOf (srcComp), NoKey);

  ResetCoord 
    (KeyOf (newcomp), 
     GetCoord (KeyOf (srcComp), NoPosition));
  ResetContext (KeyOf (newcomp), rule);
  ResetInheritedFrom (KeyOf (newcomp), srcComp);
  ResetInheritedBy 
    (KeyOf (srcComp), 
     ConsDefTableKeyList 
       (KeyOf (newcomp),
        GetInheritedBy 
          (KeyOf (srcComp), NULLDefTableKeyList)));
  ResetIsPlain (KeyOf (newcomp), GetIsPlain (KeyOf (srcComp), 0));
#ifdef TEST
  PrintCompute (newcomp);
#endif
  /* set the attribute of the new computation: */
  if (defattr == NoKey) ;/* plain */
  else if (GetIsChain (defattr, 0))
    ResetAttribute (KeyOf (newcomp), defattr);
  else
    ResetAttribute (KeyOf(newcomp), KeyOf (attr));
  if (emptyHEADattr != NoKey) {
    /* lhs of this computation is to be substituted by emptyHEADattr */
     ResetEmptyHEADChain (KeyOf(newcomp), defattr); /*chain*/
     ResetEmptyHEADAttr (KeyOf(newcomp), emptyHEADattr);
     ResetIsChainStart (KeyOf(newcomp), NoKey);
     ResetEmptyHEADCompsOfRule (rule,
       ConsDefTableKeyList (KeyOf(newcomp), 
         GetEmptyHEADCompsOfRule (rule, NULLDefTableKeyList)));
#ifdef TEST
  printf ("empty HEAD comp for chain %s\n",
          StringTable (GetNameSym (defattr, 0)));
#endif
  }
}/* InheritAComputation */


#if defined(__cplusplus) || defined(__STDC__)
void SymbOccChainInherits (DefTableKey symKey, Environment syenv,
        RuleProd rule, DefTableKey ruleKey, Environment chainScope, CoordPtr coord)
#else
void SymbOccChainInherits (symKey, syenv, ruleKey, chainScope, coord) 
DefTableKey symKey; Environment syenv; RuleProd rule;
DefTableKey ruleKey; Environment chainScope; CoordPtr coord;
#endif
{
          Environment headScope = GetHEADScope (symKey, NoEnv);
          Binding b;
#ifdef TEST
  printf("  try chains\n");
#endif
          /* try all chains: */
          Binding chn =  DefinitionsOf (chainScope);
          while (chn != NoBinding)
          {
            b = BindingInEnv (syenv, IdnOf (chn));
            if (b != NoBinding)
            { if (EnvOf (b) != syenv)
                 InheritAComputation (b, chn, syenv, ruleKey, NoKey);
              else
              {
#ifdef TEST
  printf("  already in rule:\n");
  PrintCompute (b);
#endif
              }
            }

#ifdef TEST
  printf("  check HEAD.c =\n");
#endif
            /* inherit HEAD.c = expr by first rhs symbol: */
            b = BindingInEnv (headScope, IdnOf (chn));
            if (b != NoBinding)
            { ProdSymbol rhsSymb = FindHEADSymbolOcc (rule);
              if (rhsSymb != NoProdSymbol)
              { if (NoBinding == 
                      BindingInEnv (rhsSymb->u.s.scope, IdnOf (chn)))
                /* HEAD.c is not overridden */
                /* The inherited HEAD.c is bound in the rule's
                   computation scope. 
                   In the computation occurrences of THIS
                   are substituted by the lhs symbol, and 
                   HEAD.c does not collide with an <lhs>.c
                */
                InheritAComputation 
                   (b, chn, GetLowerScope (ruleKey, NoEnv), ruleKey, NoKey);
              } else {
                /* The HEAD computation is inherited by an empty rule.
                   A rule attribute is generated to become the lhs
                   of the computation.
                   The computation is marked to be transformed later.
                */
#ifdef TEST
  printf("empty HEAD\n");
#endif
                int sym = GenerateName ("HEAD$");
                Binding atb = 
                        BindIdn (GetAttrScope (ruleKey, NoEnv), sym);
                DefTableKey atk = KeyOf(atb);
                ResetNameSym (atk, sym);
                ResetAttrClass (atk, SYNTClass);
                ResetAttrType (atk, GetAttrType (KeyOf(chn), NoKey));
                ResetCoord (atk, GetCoord (KeyOf(atb), NoPosition));
                InheritAComputation 
                  (b, chn, GetLowerScope (ruleKey, NoEnv), ruleKey, KeyOf(atb));
              }
            }
            chn = NextDefinition (chn);
          }
}/*SymbOccChainInherits*/


#if defined(__cplusplus) || defined(__STDC__)
void SymbOccInherits (DefTableKey symKey, int symOccIndex, Environment syenv,
                        DefTableKey ruleKey, CoordPtr coord)
#else
void SymbOccInherits (symKey, symOccIndex, syenv, ruleKey, chainScope, coord) 
DefTableKey symKey; int symOccIndex; Environment syenv;
DefTableKey ruleKey; CoordPtr coord;
#endif
/* on entry:
     symKey is the key of a TREE symbol, it occurs at position symOccIndex
     in the rule ruleKey.
     syenv is the scope of where the computations of that symbol occurrence
     are bound (lower if symOccIndex == 0, or upper).
  on exit:
     for each attribute of symKey (either INH or SYNT) it is checked 
     whether there is a computation in syenv or one can be
     inherited from a symbol. 
     In the latter case InheritAComputation creates a new binding 
     for that attribute in syenv, sets its properties and links it
     to the inherited computation (InheritedFrom).
*/
{
        Environment attrenv = GetAttrScope (symKey, NoEnv);
        Binding attr = DefinitionsOf (attrenv);
        Binding b;
#ifdef TEST
  printf ("symbol %s:\n", 
     StringTable (GetNameSym (symKey, 0)));
#endif
        /* try all attributes of this symbol,
           including those for plain computations: 
        */
        while (attr != NoBinding)
        { int cl = GetAttrClass (KeyOf (attr), NoClass);
          if (((symOccIndex == 0 && cl == SYNTClass) ||
              (symOccIndex > 0  && cl ==  INHClass)) && 
            !(GetHasAccuAsgn (KeyOf (attr), 0)))
          /* inheritance of accumulating attrs is in AccumulateInherit */
          {

            /* find a computation for attr in the computation scope: */
            b = BindingInEnv (syenv, IdnOf (attr));
            if (b == NoBinding)
            { if (IdnOf (attr) != GENTREEsym)
                  message (ERROR, 
                       CatStrInd (
                       CatStrStr (
                       CatStrInd (
                       CatStrStr (
                       CatStrInd ("Computation of ", 
                         GetNameSym (symKey, 0)),
                         "."),
                         IdnOf (attr)),
                         " missing in RULE "),
                         GetNameSym (ruleKey, 0)),
                       0, GetCoord (ruleKey, NoPosition));
            } else
            { /* there is a computation for IdnOf (attr): */
              if (EnvOf (b) != syenv)
              { /* it is not in rule context; inherit this computation: */
                InheritAComputation (b, attr, syenv, ruleKey, NoKey);
              } else
              { /* there is a rule computation for this identifier */
                Binding inhComp = OverridesBinding (b);
                if (inhComp != NoBinding &&
                    GetIsAccu (KeyOf (inhComp), 0)) {
                  message (ERROR, 
                    CatStrInd ("Is inherited by a non-accumulating computation: ",
                               IdnOf (attr)),
                    0, GetCoord (KeyOf (inhComp), NoPosition));
                  message (ERROR, 
                    CatStrInd ("Inherits an accumulating computation: ",
                               IdnOf (attr)),
                    0, GetCoord (KeyOf (b), NoPosition));
                }
#ifdef TEST
  PrintCompute (b);
#endif
              }
            }
          }

          attr = NextDefinition (attr);
        }/* for all attrs */
}/*SymbOccInherits*/


#if defined(__cplusplus) || defined(__STDC__)
void InheritCompute (Environment chainScope)
#else
void InheritCompute (chainScope) Environment chainScope;
#endif
/* on entry:
     The explicit computations are bound in their computation scopes.
   on exit:
     All inherited computations are bound in the computation scopes 
     of the symbol occurrences.
*/
{ RuleProdList rules;
#ifdef TEST
  printf("InheritCompute started\n");
#endif

  /* step through all nonterminal occurrences of productions: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList prod = rule->prod;
    DefTableKey ruleKey = RuleKeyOfRuleProd (rule);
    int symbolIndex = -1;
#ifdef TEST
  printf ("RULE %s:\n", 
     StringTable (GetNameSym (ruleKey, 0)));
#endif
    while (prod != NULLProdSymbolList)
    { ProdSymbol sy = HeadProdSymbolList (prod);
      if (sy->kind != IsProdLiteral && !GetIsTerm (sy->u.s.symbolkey, 0))
      { 
        symbolIndex++;

        SymbOccInherits (sy->u.s.symbolkey, symbolIndex, sy->u.s.scope,
                ruleKey, sy->u.s.coord);

        if (symbolIndex == 0) 
        /* left-hand side symbol; inherit chain computations: */
        { 
          SymbOccChainInherits (sy->u.s.symbolkey, sy->u.s.scope,
                rule, ruleKey, chainScope, sy->u.s.coord);
        }
      }
      if (rule->islistof) break; /* lhs only */
      prod = TailProdSymbolList (prod);
    }
    rules = TailRuleProdList (rules);
  }
#ifdef TEST
  printf("InheritCompute completed\n");
#endif
}/* InheritCompute */
