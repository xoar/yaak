
#include "GrammarRules.h"
#include "MakeName.h"
#include "pdl_gen.h"
#include "Strings.h"
#include "DynSpace.h"

#ifdef TEST
#define TEST
#include <stdio.h>
static void TestRule (char *s, DefTableKey key, CoordPtr coord)
{ int id = GetNameSym (key, 0);
  char *name = id == 0 ? "unnamed" : StringTable(id);
  printf ("%s rule %s in line %d\n", s, name, LineOf(*coord));
}
#endif

static
#if defined(__cplusplus) || defined(__STDC__)
int CmpProdElem (ProdSymbol s1, ProdSymbol s2)
#else
int CmpProdElem (s1, s2) ProdSymbol s1, s2;
#endif
/* compares 2 ProdSymbols */
{
    if (s1->kind != s2->kind) return 1;
    if (s1->kind == IsProdLiteral)
    {  if (strcmp (StringTable (s1->u.literal),
                   StringTable (s2->u.literal)) != 0) 
          return 1;
    } else
    if (s1->u.s.symbolkey != s2->u.s.symbolkey) return 1;
    else return 0;
    return 0; /* never reached */
}

static
#if defined(__cplusplus) || defined(__STDC__)
int CmpProd (ProdSymbolList prod1, ProdSymbolList prod2)
#else
int CmpProd (prod1, prod2) ProdSymbolList prod1, prod2;
#endif
/* compares 2 non-listof productions */
{
  while (prod1 != NULLProdSymbolList && prod2 != NULLProdSymbolList)
  { ProdSymbol s1 = HeadProdSymbolList (prod1);
    ProdSymbol s2 = HeadProdSymbolList (prod2);
    if (CmpProdElem (s1, s2)) return 1;
    prod1 = TailProdSymbolList (prod1);
    prod2 = TailProdSymbolList (prod2);
  }
  if (prod1 != NULLProdSymbolList || prod2 != NULLProdSymbolList)
       return 1;
  else return 0;
}

static
#if defined(__cplusplus) || defined(__STDC__)
int CmpListofProd (ProdSymbolList prod1, ProdSymbolList prod2)
#else
int CmpListofProd (prod1, prod2) ProdSymbolList prod1, prod2;
#endif
/* compares 2 listof productions */
{ ProdSymbolList aux1 = prod1;
  while (aux1 != NULLProdSymbolList)
  { ProdSymbol s1 = HeadProdSymbolList (aux1);
    if (!ElemInProdSymbolList (s1, prod2, CmpProdElem))
       return 1;
    aux1 = TailProdSymbolList (aux1);
  }
  while (prod2 != NULLProdSymbolList)
  { ProdSymbol s2 = HeadProdSymbolList (prod2);
    if (!ElemInProdSymbolList (s2, prod1, CmpProdElem))
       return 1;
    prod2 = TailProdSymbolList (prod2);
  }
  return 0;
}

static
#if defined(__cplusplus) || defined(__STDC__)
int CmpRule (RuleProd rule1, RuleProd rule2)
#else
int CmpRule (rule1, rule2) RuleProd rule1, rule2;
#endif
/* compares 2 rules */
{
  if (rule1->rulekey != rule2->rulekey) return 1;
  if (rule1->islistof != rule2->islistof) return 1;
  if (rule1->islistof)
       return CmpListofProd (rule1->prod, rule2->prod);
  else return CmpProd (rule1->prod, rule2->prod);
}

/* all explicitly named rules, one for all instances,
   the productions are checked for equality:
*/
static RuleProdList namedrules = NULLRuleProdList;

/* all rules without a name that differ in the production:
*/
static RuleProdList unnamedrules = NULLRuleProdList;

/* all rules, no duplicate instances, each named,
   names generated for unnamed rules that are not matched to
   a named rule:
*/
RuleProdList GrammarRules = NULLRuleProdList;

#if defined(__cplusplus) || defined(__STDC__)
RuleProd MakeRuleProd 
  (DefTableKey rulekey, ProdSymbolList prod, 
   int islistof, CoordPtr coord)
#else
RuleProd MakeRuleProd (rulekey, prod, islistof, coord) 
  DefTableKey rulekey; ProdSymbolList prod; 
  int islistof; CoordPtr coord;
#endif
/* on exit
     one of the lists unnamedrules or GrammarRules
     contains an entry for this rule instance
*/
{ RuleProd res;
#ifdef TEST
  TestRule("MakeRuleProd", rulekey, coord);
#endif
  /* check whether there is already an instance of this rule: */
  if (rulekey == NoKey)
  { RuleProdList search = unnamedrules;
    while (search != NULLRuleProdList)
    { RuleProd unnamedrule = HeadRuleProdList (search);
      int equal = unnamedrule->islistof == islistof;
      if (equal && islistof &&
          0 == CmpListofProd (unnamedrule->prod, prod))
         return unnamedrule;
      if (equal && !islistof &&
          0 == CmpProd (unnamedrule->prod, prod))
         return unnamedrule;
      search = TailRuleProdList (search);
    }
  } else
  { RuleProdList search = GrammarRules;
    while (search != NULLRuleProdList)
    { RuleProd namedrule = HeadRuleProdList (search);
      if (namedrule->rulekey == rulekey)
      { int equal = namedrule->islistof == islistof;
        if (equal && islistof)
           equal = (0 == CmpListofProd (namedrule->prod, prod));
        if (equal && !islistof)
           equal = (0 == CmpProd (namedrule->prod, prod));
        if (!equal)
        { message 
             (ERROR,
              "Different productions for the same RULE name",
              0, namedrule->coord);
          message 
             (ERROR,
              "Different productions for the same RULE name",
              0, coord);
        }
        return namedrule;
      }
      search = TailRuleProdList (search);
    }
  }
  /* a new rule is found: */
  res = (RuleProd) DynAlloc (ProdSpace, sizeof (_RElem));
  res->rulekey = rulekey;
  res->prod = prod;
  res->islistof = islistof;
  res->coord = coord;

  { ProdSymbol lhs = HeadProdSymbolList (prod);
    if (islistof) {
         ResetHasListof (lhs->u.s.symbolkey, 1);
         if (rulekey != NoKey) /* named rule */
           ResetListofRuleOfLhs (lhs->u.s.symbolkey, rulekey);
    }
    else ResetHasNonListof (lhs->u.s.symbolkey, 1);
  }

  if (rulekey == NoKey)
       unnamedrules = ConsRuleProdList (res, unnamedrules);
  else GrammarRules = ConsRuleProdList (res, GrammarRules);
  return res;
}/* MakeRuleProd */

static
void MapUnnamedRules (Environment globenv)
/* on entry:
        The lists namedrules and GrammarRules 
        contain one entry for each RULE
   on exit:
        The list GrammarRules contains one named entry
        for each RULE
*/
{ RuleProdList orignamedrules = GrammarRules;
        /* the rules that have non-generated names */

  while (unnamedrules != NULLRuleProdList)
  { RuleProdList mapto = orignamedrules;
    RuleProd unnamedrule = HeadRuleProdList (unnamedrules);
    RuleProd namedrule;

    /* search first named rule with same production: */
    while (mapto != NULLRuleProdList)
    { namedrule = HeadRuleProdList (mapto);
      if (namedrule->islistof == unnamedrule->islistof &&
          0 == CmpProd (namedrule->prod, unnamedrule->prod))
         break;
       mapto = TailRuleProdList (mapto);
    }
    if (mapto != NULLRuleProdList)
    {  /* found one: */
       int reported = 0;
       RuleProd firstfound = namedrule;
       /* use named key: */
       unnamedrule->rulekey = namedrule->rulekey;
#ifdef TEST
  TestRule("orig coord", namedrule->rulekey, namedrule->coord);
#endif
       /* use coord of unnamed, because more likely to be
          manually written: */
       namedrule->coord = unnamedrule->coord;
       ResetCoord (namedrule->rulekey, unnamedrule->coord);
#ifdef TEST
  TestRule("new coord", namedrule->rulekey, namedrule->coord);
#endif

       /* search for another one: */
       mapto = TailRuleProdList (mapto);
       while (mapto != NULLRuleProdList)
       { namedrule = HeadRuleProdList (mapto);
         if (namedrule->islistof == unnamedrule->islistof &&
             0 == CmpProd (namedrule->prod, unnamedrule->prod))
         { if (!reported)
           { message (ERROR,
                      CatStrInd (
                         "Unnamed RULE matches several named rules: ",
                         GetNameSym (firstfound->rulekey, 0)),
                      0, unnamedrule->coord);
             reported = 1;
           }
           message (ERROR, 
                    CatStrInd (
                       "Unnamed RULE matches several named rules: ",
                       GetNameSym (namedrule->rulekey, 0)),
                    0, unnamedrule->coord);
         }
         mapto = TailRuleProdList (mapto);
       }
    } else /* create rule name, add unnamedrule to grammar: */
    { int newname = GenerateName ("rule_");
      unnamedrule->rulekey = DefineIdn (globenv, newname);
      ResetNameSym (unnamedrule->rulekey, newname);
      ResetIsRule (unnamedrule->rulekey, 1);
      ResetCoord (unnamedrule->rulekey, unnamedrule->coord);
      GrammarRules = ConsRuleProdList (unnamedrule, GrammarRules);
    }
    unnamedrules = TailRuleProdList (unnamedrules);
  }
}/* MapUnnamedRules */

static
void SetRuleProperty ()
/* on entry
        the GrammarRules are completed
   on exit
        the properties Rule and LhsOfRule are set for each rule key
*/
{ RuleProdList rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    ProdSymbol lhs = HeadProdSymbolList (rule->prod);
    ResetRule (rule->rulekey, rule);
    ResetLhsOfRule (rule->rulekey, lhs->u.s.symbolkey);
    rules = TailRuleProdList (rules);
  }
}/* SetRuleProperty */

static
void ChkListofRules ()
/* on entry
        the GrammarRules are completed
   on exit
        reports are given for any lhs symbol that has both
        a LISTOF and a non-LISTOF or a different production
*/
{ RuleProdList rules = GrammarRules;
  while (rules != NULLRuleProdList)
  { RuleProd rule = HeadRuleProdList (rules);
    DefTableKey lhs = (HeadProdSymbolList (rule->prod))->u.s.symbolkey;
    DefTableKey otherListRule = GetListofRuleOfLhs (lhs, NoKey);

    if (rule->islistof && 
        otherListRule != NoKey && otherListRule != rule->rulekey)
          message (ERROR,
                   CatStrInd (
           "The same left-hand side occurs in a different production: ",
                     GetNameSym (otherListRule, 0)),
                   0, rule->coord);

    if (GetHasListof (lhs, 0) && GetHasNonListof (lhs, 0))
    {  if (rule->islistof)
          message (ERROR,
                   CatStrInd (
         "The same left-hand side occurs in a non-LISTOF production: ",
                     GetNameSym (rule->rulekey, 0)),
                   0, rule->coord);
       else
          message (ERROR,
                   CatStrInd (
         "The same left-hand side occurs in a LISTOF production: ",
                     GetNameSym (rule->rulekey, 0)),
                   0, rule->coord);
    }
    rules = TailRuleProdList (rules);
  }
}/* ChkListofRules */

#if defined(__cplusplus) || defined(__STDC__)
void MakeGrammar (Environment env)
#else
void MakeGrammar (env) Environment env;
#endif
{
  MapUnnamedRules (env);
  SetRuleProperty ();
  ChkListofRules ();
}/* MakeGrammar */
