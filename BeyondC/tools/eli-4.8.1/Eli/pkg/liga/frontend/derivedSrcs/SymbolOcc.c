
#include "SymbolOcc.h"
#include "pdl_gen.h"
#include "csm.h"

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol FindHEADSymbolOcc (RuleProd rule)
#else
ProdSymbol FindHEADSymbolOcc (rule)
  RuleProd rule;
#endif
{ ProdSymbolList rhs;
  if (rule == NoRuleProd) return NoProdSymbol;

  rhs = TailProdSymbolList (rule->prod);
  while (rhs != NULLProdSymbolList)
  { ProdSymbol s = HeadProdSymbolList (rhs);
    if (s->kind != IsProdLiteral && 
        GetIsNonterm (s->u.s.symbolkey, 0))
       return s;
    rhs = TailProdSymbolList (rhs);
  }
  return NoProdSymbol;
}/* FindHEADSymbolOcc */

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol FindTAILSymbolOcc (RuleProd rule)
#else
ProdSymbol FindTAILSymbolOcc (rule)
  RuleProd rule;
#endif
{ ProdSymbolList rhs; 
  ProdSymbol lastnonterm = NoProdSymbol;
  if (rule == NoRuleProd) return NoProdSymbol;

  rhs = TailProdSymbolList (rule->prod);
  while (rhs != NULLProdSymbolList)
  { ProdSymbol s = HeadProdSymbolList (rhs);
    if (s->kind != IsProdLiteral &&
        GetIsNonterm (s->u.s.symbolkey, 0))
       lastnonterm = s;
    rhs = TailProdSymbolList (rhs);
  }
  return lastnonterm;
}/* FindTAILSymbolOcc */

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol FindSymbolOcc 
  (RuleProd rule, DefTableKey symbol, int index, CoordPtr coord)
#else
ProdSymbol FindSymbolOcc (rule, symbol, index, coord)
  RuleProd rule; DefTableKey symbol; int index; CoordPtr coord;
#endif
/* on entry:
     rule is the representative production of a rule
     symbol[index] is a symbol occurrence to be found
       index == 0 represents no index
   on exit:
     the pointer to the symbol occurrence record is returned
     messages are reported if
        the symbol occurrence is not in the production,
        the index should be present
        the index should not be present
     NoProdSymbol is returned in erroneous cases
*/
{ ProdSymbolList symblist;
  ProdSymbol result = NoProdSymbol;
  int count = (index > 0 ? index : 1);
#ifdef TEST
printf ("FindSymbolOcc %s count %d in line %d\n",
    StringTable(GetNameSym (symbol, 0)), count, LineOf(*coord));
#endif
  if (rule == NoRuleProd) return NoProdSymbol;

  symblist = rule->prod;
  while (symblist != NULLProdSymbolList && count > 0)
  { ProdSymbol s = HeadProdSymbolList (symblist);
    if (s->kind != IsProdLiteral && s->u.s.symbolkey == symbol)
    { count--;
      result = s;
    }
    symblist = TailProdSymbolList (symblist);
  }

  if (count > 0) /* not enough occs of symbol in the prod */
  { if (rule->islistof)
      message (ERROR,
               "Only left-hand side of a LISTOF may be accessed",
               0, coord);
    else
      message (ERROR,
               "Symbol is not in production",
               0, coord);
    return NoProdSymbol;
  }

  /* count == 0 implies 
       result is the i-th occurrence of symbol
  */
  if (index > 1) /* explicit index>1 is correct */
     return result;

  /* index==1 or no index was given, 
     first occ has been found */
  /* check whether there is another occurrence of symbol: */
  while (symblist != NULLProdSymbolList)
  { ProdSymbol s = HeadProdSymbolList (symblist);
    if (s->kind != IsProdLiteral && s->u.s.symbolkey == symbol)
    { /* found another occ after the first one */
      if (index == 0) /* is not indexed */
         message (ERROR,
                  "Symbol index is missing",
                  0, coord);
      return result;
    }
    symblist = TailProdSymbolList (symblist);
  }

  /* result is the only occ of symbol */
  if (index > 1) /* is indexed */
     message (ERROR,
              "Symbol must not be indexed",
              0, coord);
  return result;
}/* FindSymbolOcc */

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol FindSymbolRef 
  (RuleProd rule, DefTableKey symbol, int index)
#else
ProdSymbol FindSymbolRef (rule, symbol, index)
  RuleProd rule; DefTableKey symbol; int index;
#endif
/*same as FindSymbolOcc but without messages;
  to be used to find a terminal occurrence
  on entry:
     rule is the representative production of a rule
     symbol[index] is a symbol occurrence to be found
       index == 1 is set for an optional index
   on exit:
     the pointer to the symbol occurrence record is returned
     NoProdSymbol is returned if the symbol is not found
*/
{ ProdSymbolList symblist;
  ProdSymbol result = NoProdSymbol;
  int count = (index > 0 ? index : 1);

  if (rule == NoRuleProd) return NoProdSymbol;

  symblist = rule->prod;
  while (symblist != NULLProdSymbolList && count > 0)
  { ProdSymbol s = HeadProdSymbolList (symblist);
    if (s->kind != IsProdLiteral && s->u.s.symbolkey == symbol)
    { count--;
      result = s;
    }
    symblist = TailProdSymbolList (symblist);
  }

  if (count > 0) /* not enough occs of symbol in the prod */
    return NoProdSymbol;

  if (rule->islistof && result != HeadProdSymbolList (rule->prod))
    return NoProdSymbol;

  return result;
}/* FindSymbolRef */


#if defined(__cplusplus) || defined(__STDC__)
int CountSymbolRef 
  (RuleProd rule, DefTableKey symbol)
#else
int CountSymbolRef (rule, symbol, index)
  RuleProd rule; DefTableKey symbol; int index;
#endif
/*same as FindSymbolRef, but counting the occurrences;
  on entry:
     rule is the representative production of a rule
     symbol is the key of a name; its occurrences are counted
   on exit:
     the number of occurrences of symbol in the rule is returned
*/
{ ProdSymbolList symblist;
  int count = 0;

  if (rule == NoRuleProd) return 0;
  if (rule->islistof) return 0; /* nor terminals are in LISTOF rules */

  symblist = rule->prod;
  while (symblist != NULLProdSymbolList)
  { ProdSymbol s = HeadProdSymbolList (symblist);
    if (s->kind != IsProdLiteral && s->u.s.symbolkey == symbol)
    { count++;
    }
    symblist = TailProdSymbolList (symblist);
  }
  return count;
}/* CountSymbolRef */
