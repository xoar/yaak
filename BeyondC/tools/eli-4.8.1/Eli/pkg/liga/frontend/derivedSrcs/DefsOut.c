
#include "DefsOut.h"
#include "GrammarRules.h"
#include "Grammar.h"
#include "Attribute.h"
#include "pdl_gen.h"
#include "csm.h"
#include "MakeName.h"

/* is set to the global scope by the call of MarkGrammarUses: */
static Environment globalEnv = NoEnv;
static int nextDid = 8;

#if defined(__cplusplus) || defined(__STDC__)
int SetDidIfNew (DefTableKey def)
#else
int SetDidIfNew (def) DefTableKey def;
#endif
/* on exit:
     def has a unique did;
     it is returned as result
*/
{ 
  int res = GetDid (def, 0);
  if (!res)
  { res = nextDid++; ResetDid (def, res);}
  return res;
}

static
#if defined(__cplusplus) || defined(__STDC__)
void CopyAttrToSymbol (DefTableKey attr, DefTableKey symb)
#else
void CopyAttrToSymbol (attr, symb) DefTableKey attr; DefTableKey symb;
#endif
{ Environment symEnv = GetAttrScope (symb, NoEnv);
  /* Attaches _RuleAttr_ruledid to the attribute name, as order requires: */
  int atId =
     IdnNumb 
       (PreIdnPost ("", GetNameSym (attr, 0), "_RuleAttr_"), 
                    GetDid (GetRuleOfAttr (attr, NoKey), 0));
  Binding atb = BindIdn (symEnv, atId);
  DefTableKey symatk = KeyOf(atb);
  ResetNameSym (symatk, atId);
  ResetAttrType (symatk, GetAttrType (attr, NoKey));
  ResetAttrClass (symatk, SYNTClass);
  ResetCoord (symatk, GetCoord (attr, NoPosition));
  ResetRuleOfAttr (symatk, GetRuleOfAttr (attr, NoKey));
  ResetDid (symatk, GetDid (attr, 0));
}/*CopyAttrToSymbol*/

static int minPredefTypeDid = 0;
static int maxPredefTypeDid = 0;
static 
#if defined(__cplusplus) || defined(__STDC__)
int IsPredefType (int did)
#else
int IsPredefType (did) int did;
#endif
{ return did >= minPredefTypeDid && did <= maxPredefTypeDid; 
}

#if defined(__cplusplus) || defined(__STDC__)
void SetAllDids (Environment globEnv, Environment chainEnv)
#else
void SetAllDids (globEnv, chainEnv) 
   Environment globEnv; Environment chainEnv;
#endif
/* on entry

   on exit
*/
{ Binding b;

  /* Set Did of predefined types: */
  minPredefTypeDid = 1;
  ResetDid (VOIDkey, 1);
  ResetDid (VOID_LISTkey, 2);
  ResetDid (intkey, 3);
  ResetDid (BOOLkey, 4);
  ResetDid (SYMBkey, 5);
  ResetDid (POSITIONkey, 6);
  ResetDid (NODEPTRkey, 7);
  maxPredefTypeDid = 7;

  /* Set Did of user types: */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsType (k, 0)) SetDidIfNew (k);
    b = NextDefinition (b);
  }

  /* Set Did of Chains: */
  b = DefinitionsOf (chainEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsChain (k, 0)) SetDidIfNew (k);
    b = NextDefinition (b);
  }

  /* Set Did of nonterminals: */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsNonterm (k, 0) && GetIsTreeSym (k, 0)) SetDidIfNew (k);
    b = NextDefinition (b);
  }

  /* Set Did of non-literal terminals: */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsTerm (k, 0) && GetIsTreeSym (k, 0)) 
    { if (GetType (k, NoKey) == NoKey) ResetType (k, intkey);
      SetDidIfNew (k);
    }
    b = NextDefinition (b);
  }

  /* Set Did of rules: */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsRule (k, 0)) SetDidIfNew (k);
    b = NextDefinition (b);
  }

  /* Set Did of attributes of nonterminals: */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsNonterm (k, 0) && GetIsTreeSym (k, 0)) {
      Environment symEnv = GetAttrScope (k, NoEnv);
      Binding at = DefinitionsOf (symEnv);
      while (at != NoBinding)
      { DefTableKey atk = KeyOf (at);
        if (!GetIsPlain (atk, 0))
           SetDidIfNew (atk);
        at = NextDefinition (at);
      }
    }
    b = NextDefinition (b);
  }

  /* Set Did of attributes of rules;
     copy each rule attribute to the lhs symbol:
  */
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey ruleKey = KeyOf (b);
    if (GetIsRule (ruleKey, 0)) {
      Environment ruleEnv = GetAttrScope (ruleKey, NoEnv);
      Binding at = DefinitionsOf (ruleEnv);
      while (at != NoBinding)
      { DefTableKey atk = KeyOf (at);
        if (!GetIsPlain (atk, 0)) {
           SetDidIfNew (atk);
           ResetRuleOfAttr (atk, ruleKey);
           CopyAttrToSymbol (atk, GetLhsOfRule (ruleKey, NoKey));
        }
        at = NextDefinition (at);
      }
    }
    b = NextDefinition (b);
  }
}/* SetAllDids */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode RowCol (DefTableKey k)
#else
PTGNode RowCol (k) DefTableKey k;
#endif
{ CoordPtr c = GetCoord (k, NoPosition);
  if (c == NoPosition)
    return PTGIdlrowCol (0, 0);
  else
    return PTGIdlrowCol (LineOf(*c),ColOf(*c));
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode ColRow (DefTableKey k)
#else
PTGNode ColRow (k) DefTableKey k;
#endif
{ CoordPtr c = GetCoord (k, NoPosition);
  if (c == NoPosition)
    return PTGIdlcolRow (0, 0);
  else
    return PTGIdlcolRow (LineOf(*c),ColOf(*c));
}

#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutAttrDefs (DefTableKey sym, Environment globEnv)
#else
PTGNode OutAttrDefs (sym) DefTableKey sym; Environment globEnv;
#endif
/* outputs the list of attributes of sym */
{
  PTGNode res = PTGNULL;
  Environment symEnv = GetAttrScope (sym, NoEnv);
  Binding b = DefinitionsOf (symEnv), rb;

  /* output the attributes of sym itself: */
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    int atcl;
    if (sym == GrammarRoot)
    /* turn INH to SYNT: */
        atcl = 0;
    else
        atcl = GetAttrClass (k, NoClass)==SYNTClass? 0 : 1;

    if (!GetIsPlain (k, 0))
       res = PTGSeq (res,
          PTGIdlAttrdef (
                 GetDid (GetRuleOfAttr (k, NoKey), 0),
                 atcl,
                 GetDid (GetAttrType (k, NoKey), 0),
                 ColRow (k),
                 StringTable (IdnOf (b)),
                 GetDid (k, 0)));
    b = NextDefinition (b);
  }
  return res;
}/*OutAttrDefs*/


#if defined(__cplusplus) || defined(__STDC__)
PTGNode OutputDefs (Environment globEnv, Environment chainEnv)
#else
PTGNode OutputDefs (globEnv, chainEnv) 
   Environment globEnv; Environment chainEnv;
#endif
/* on entry
   on exit
*/
{ PTGNode outPredefTypes = PTGNULL, outUserTypes = PTGNULL,
          outTerms = PTGNULL, outSymbs = PTGNULL, 
          outProds = PTGNULL, outChains = PTGNULL;
  Binding b;
  RuleProdList rules;

  /* set all Did properties: */
  SetAllDids (globEnv, chainEnv);

  /* output all defs but chains:*/
  b = DefinitionsOf (globEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsType (k, 0)) {
        PTGNode t = 
          PTGIdlTypedef (
                GetDid (k, 0),
                StringTable (GetNameSym (k, 0)),
                RowCol (k));
       if (IsPredefType (GetDid (k, 0)))
                outPredefTypes = PTGSeq (outPredefTypes, t);
       else     outUserTypes = PTGSeq (outUserTypes, t);
    } else
    if (GetIsTerm (k, 0) && GetIsTreeSym (k, 0)) {
        outTerms = PTGSeq (outTerms,
          PTGIdlTermdef (
                GetDid (k, 0),
                StringTable (GetNameSym (k, 0)),
                RowCol (k)));
    } else
    if (GetIsNonterm (k, 0) && GetIsTreeSym (k, 0)) {
        outSymbs = PTGSeq (outSymbs,
          PTGIdlSymb (
                GetDid (k, 0),
                StringTable (GetNameSym (k, 0)),
                RowCol (k),
                OutAttrDefs(k, globEnv)));
    } else
    if (GetIsRule (k, 0)) {
      /* is output separately */
    } else {}

    b = NextDefinition (b);
  }

  /* output all chains:*/
  b = DefinitionsOf (chainEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsChain (k, 0)) {
        outChains = PTGSeq (outChains,
          PTGIdlChain (
                GetDid (k, 0),
                StringTable (GetNameSym (k, 0)),
                RowCol (k),
                GetDid (GetAttrType (k, NoKey), 0)));
    }
    b = NextDefinition (b);
  }

  /* output all rules with their rhs: */
  rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbolList rhs = TailProdSymbolList (rule->prod);
    int lhsDid = 
       GetDid ((HeadProdSymbolList (rule->prod))->u.s.symbolkey, 0);
    PTGNode coordOut = RowCol (rule->rulekey);

    /* transform right-hand side: */
    PTGNode rhsout = PTGNULL;
    while (rhs != NULLProdSymbolList)
    { ProdSymbol symbol = HeadProdSymbolList (rhs);
      PTGNode symout = PTGNULL;
      CoordPtr c;
      switch (symbol->kind)
      { case IsProdLiteral:
          symout = 
                PTGIdlLiteral 
                 (coordOut, 
                  StringTable (symbol->u.literal));
          break;
        case IsProdSymbol:
          c = symbol->u.s.coord;
          if (GetIsNonterm (symbol->u.s.symbolkey, 0))
             symout =
                PTGIdlSymbol
                  (PTGIdlrowCol (LineOf(*c),ColOf(*c)),
                   GetDid (symbol->u.s.symbolkey, 0));
          else
             symout =
                PTGIdlNonLitTerm
                  (PTGIdlrowCol (LineOf(*c),ColOf(*c)),
                   StringTable (GetNameSym (symbol->u.s.symbolkey, 0)),
                   StringTable 
                    (GetNameSym (GetType (symbol->u.s.symbolkey, NoKey), 0)));
          break;
        case IsProdGenSymbol:
          c = symbol->u.s.coord;
          symout =
                PTGIdlGenSymbol
                  (PTGIdlrowCol (LineOf(*c),ColOf(*c)),
                   GetDid (symbol->u.s.symbolkey, 0));
           break;
      }
      rhsout = PTGSeq (rhsout, symout);
      rhs = TailProdSymbolList (rhs);
    }

    outProds = PTGSeq (outProds,
      PTGIdlProd (
        GetDid (rule->rulekey, 0),
        StringTable (GetNameSym (rule->rulekey, 0)),
        coordOut,
        rhsout,
        lhsDid));
    rules = TailRuleProdList (rules);
  }

  return PTGSeq (outPredefTypes, 
         PTGSeq (outUserTypes, 
         PTGSeq (outTerms, 
         PTGSeq (outSymbs,
         PTGSeq (outProds, 
                 outChains)))));
}/* OutputDefs */
