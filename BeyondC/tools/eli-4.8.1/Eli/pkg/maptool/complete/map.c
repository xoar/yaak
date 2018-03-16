

#include "deftbl.h"
#include "err.h"
#include "obstack.h"
#include "pdl_gen.h"
#include "SymbolPList.h"
#include "DefTableKeyList.h"
#include "intList.h"
#include "map.h"
#include "match.h"
#include "symbol.h"
#include "tOilTypeSetList.h"

int MapQChains = 0;

/* On Entry:
 *   a - a definition table key
 *   b - another definition table key
 * On Exit:
 *   DefTableKeyCmp returns 1 if a and b are the same definition table keys,
 *   otherwise it returns 0.
 */
#ifdef PROTO_OK
int
DefTableKeyCmp (DefTableKey a, DefTableKey b)
#else
int
DefTableKeyCmp (a, b)
DefTableKey a;
DefTableKey b;
#endif
{
  if (a == b) return 0;
  else return 1;
}

/* On Entry:
 *   a - an integer
 *   b - another integer
 * On Exit:
 *   intCmp returns 1 if a and b are the same and 0 otherwise.
 */
#ifdef PROTO_OK
int
intCmp (int a, int b)
#else
int
intCmp (a, b)
int a;
int b;
#endif
{
  if (a == b) return 0;
  else return 1;
}

/* On Entry:
 *   list - a list representing the rhs of a rule
 *   pos - integer representing which rhs nonterminal to return
 * On Exit:
 *   GetNthNT returns a definition table key representing the nth nonterminal
 *   in list.  It skips over TEXT and GEN_IDENT keys and returns NoKey if no
 *   such nonterminal exists.
 */
#ifdef PROTO_OK
SymbolP
GetNthNT (SymbolPList list, int n)
#else
SymbolP
GetNthNT (list, n)
SymbolPList list;
int n;
#endif
{
  if (n == 0)
    return (SymbolP) 0;

  while (1) {
    /* Find the next IDENTIFIER symbol */
    while (list != NULLSymbolPList &&
           SymbolClassGet(HeadSymbolPList(list)) != IDENTIFIER)
      list = TailSymbolPList(list);
    if (list == NULLSymbolPList)
      return (SymbolP)0;
    else if (!(--n))
      return HeadSymbolPList(list);
    else
      list = TailSymbolPList(list);
  }
}

/* On Entry:
 *   rhs - a reordered right hand side symbol list
 * On Exit:
 *   CreateSignature returns an OIL signature for the reordered right hand
 *   side for use by ConMatch to try to find an appropriate match.
 */
tOilSetSig
#ifdef PROTO_OK
CreateSignature (SymbolPList rhs)
#else
CreateSignature (rhs) SymbolPList rhs;
#endif
{
  tOilSetSig result;

  result = OilNewSetSig();

  if (rhs == NULLSymbolPList) {
    result = OilAddSetSig(OilTypeToSet(EmptyType),result);
  } else {
    while (rhs != NULLSymbolPList) {
      result = OilAddSetSig(CreateTS(SymbolKeyGet(HeadSymbolPList(rhs))),
                            result);
      rhs = TailSymbolPList(rhs);
    }
  }

  return result;
}

/* On Entry:
 *   rule1, rule2 - rule keys to be compared
 *   map - non-zero if RuleCmp should symbolically map symbols before
 *              comparing, zero if it should not map
 * On Exit:
 *   RuleCmp returns 1 if the rules match, 0 if they don't.
 *   Matching is done by checking each symbol of the rules with the
 *   corresponding symbol in the other.
 */
#ifdef PROTO_OK
int
RuleCmp (DefTableKey rule1, DefTableKey rule2, int map)
#else
int
RuleCmp (rule1, rule2, map)
DefTableKey rule1, rule2;
int map;
#endif
{
  DefTableKey key1, key2;
  SymbolPList rhs1, rhs2;
  SymbolP symbol1, symbol2;

  /* Compare the lhs' */
  key1 = GetLHS(rule1, NoKey);
  key2 = GetLHS(rule2, NoKey);
  if (map) {
    if (GetMap(key1, key1) != GetMap(key2, key2))
      return 0;
  } else if (key1 != key2)
    return 0;

  rhs1 = GetRHS(rule1, NULLSymbolPList);
  rhs2 = GetRHS(rule2, NULLSymbolPList);

  symbol1 = NextSymbol(&rhs1);
  symbol2 = NextSymbol(&rhs2);

  /* Compare each symbol of the rhs' */
  while (symbol1 && symbol2) {
    if (map) {
      if (GetMap(SymbolKeyGet(symbol1), SymbolKeyGet(symbol1)) !=
                GetMap(SymbolKeyGet(symbol2), SymbolKeyGet(symbol2)))
        return 0;
    } else if (SymbolKeyGet(symbol1) != SymbolKeyGet(symbol2))
      return 0;
    symbol1 = NextSymbol(&rhs1);
    symbol2 = NextSymbol(&rhs2);
  }

  if (symbol1 || symbol2)
    return 0;
  else
    return 1;
}

/* On Entry:
 *   lhs - symbol key representing the lhs of a rule
 *   rhs - list of symbol keys representing the rhs of a rule
 * On Exit:
 *   If a concrete rule is found which matches the descriptions of the
 *   arguments, then the key for the concrete rule found is returned,
 *   otherwise FindConRule returns NoKey.
 */
#ifdef PROTO_OK
DefTableKey
FindConRule (DefTableKey lhs, SymbolPList rhs)
#else
DefTableKey
FindConRule (lhs, rhs)
DefTableKey lhs;
SymbolPList rhs;
#endif
{
  DefTableKey key;
  DefTableKeyList conrules;

  /* Create a dummy rule key with the lhs and rhs given by the arguments */
  key = NewKey();
  ResetLHS(key, lhs);
  ResetRHS(key, rhs);

  /* Get a list of the concrete rules with the specified lhs and use    */
  /* RuleCmp to compare them to the dummy rule just created.            */
  conrules = GetConRules(lhs, NULLDefTableKeyList);
  while (conrules != NULLDefTableKeyList &&
         !RuleCmp(HeadDefTableKeyList(conrules), key, 0))
    conrules = TailDefTableKeyList(conrules);

  if (conrules != NULLDefTableKeyList)
    return HeadDefTableKeyList(conrules);
  else
    return NoKey;
}

