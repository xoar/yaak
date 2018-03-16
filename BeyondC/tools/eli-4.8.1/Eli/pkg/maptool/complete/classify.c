

#include "pdl_gen.h"
#include "DefTableKeyList.h"
#include "classify.h"
#include "symbol.h"

/* On Entry:
 *   key - a key representing a grammar symbol
 *   type - 0 if key is in the concrete grammar and
 *              1 if it is in the abstract grammar
 * On Exit:
 *   If the symbol is determined to be a root, then the Start
 *   property will be set for all symbols in its equivalence
 *   class and CheckAxiom will return 1, otherwise CheckAxiom
 *   returns 0.  CheckAxiom will also return 0 if this root has
 *   previously been detected.
 */
#ifdef PROTO_OK
int
CheckAxiom (DefTableKey key, int type)
#else
int
CheckAxiom (key, type)
DefTableKey key;
int type;
#endif
{
  DefTableKeyList list;

  /* If the symbol appears on the rhs of a production, then it  */
  /* is not a root.  If we have previously detected this symbol */
  /* to be a root, also return 0.                               */
  if ((GetIsRHS(key, 0)) || (GetStart(key, 0)))
    return 0;
  if (!type) {
    if (GetIsRHS(GetMap(key, key), 0))
      return 0;
  } else {
    list = GetAbsMap(key, NULLDefTableKeyList);
    while (list != NULLDefTableKeyList) {
      if (GetIsRHS(HeadDefTableKeyList(list), 0))
        return 0;
      list = TailDefTableKeyList(list);
    }
  }

  /* If it is a concrete symbol, then set the Start property    */
  /* for the key itself and its mapping in the abstract         */
  /* grammar.  Otherwise, mark this symbol and all concrete     */
  /* symbols in its equivalence class.                          */
  if (!type) {
    ResetStart(key, 1);
    ResetStart(GetMap(key, key), 1);
  } else {
    ResetStart(key, 1);
    list = GetAbsMap(key, NULLDefTableKeyList);
    while (list != NULLDefTableKeyList) {
      ResetStart(HeadDefTableKeyList(list), 1);
      list = TailDefTableKeyList(list);
    }
  }
  return 1;
}

/* On Entry:
 *   key - a root symbol
 * On Exit:
 *   The Reach property will be set for all contexts which
 *   appear as subtrees of the symbol represented by key.
 *   The Reach property is not set for contexts which are
 *   only reachable through $ symbols, i.e., computed subtrees.
 */
#ifdef PROTO_OK
void
ComputeReach (DefTableKey key)
#else
void
ComputeReach (key)
DefTableKey key;
#endif
{
  DefTableKeyList Rules, ConKeys;
  SymbolPList RHS;
  DefTableKey Rule;

  /* Get all concrete and abstract rules which have this key as their   */
  /* lhs.  To get the abstract rules, the key is first mapped.  If it   */
  /* is already an abstract key, the mapping won't matter.              */
  Rules = AppDefTableKeyList(GetAbsRules(GetMap(key, key),
                                        NULLDefTableKeyList),
                        GetConRules(key, NULLDefTableKeyList));

  /* Get all of the concrete keys in the equivalence class.  If key is  */
  /* a concrete key, then a null list will be returned.  Append the     */
  /* associated rules to the set of rules which must be traversed.      */
  ConKeys = GetAbsMap(key, NULLDefTableKeyList);
  while (ConKeys != NULLDefTableKeyList) {
    Rules = AppDefTableKeyList(GetConRules(HeadDefTableKeyList(ConKeys),
                                        NULLDefTableKeyList),
                                Rules);
    ConKeys = TailDefTableKeyList(ConKeys);
  }    

  /* Loop through each of these rules and if the rule has not yet been  */
  /* marked, then mark it and recursively check each of the rhs symbols */
  while (Rules != NULLDefTableKeyList) {
    Rule = HeadDefTableKeyList(Rules);
    if (!GetReach(Rule, 0)) {
      ResetReach(Rule, 1);

      RHS = GetRHS(Rule, NULLSymbolPList);
      while (RHS != NULLSymbolPList) {
        if (SymbolClassGet(HeadSymbolPList(RHS)) == IDENTIFIER)
          ComputeReach(SymbolKeyGet(HeadSymbolPList(RHS)));
        RHS = TailSymbolPList(RHS);
      }
    }
    Rules = TailDefTableKeyList(Rules);
  }
}

/* On Entry:
 *   key - key representing an abstract rule
 * On Exit:
 *   The symbols of the rule represented by key will be marked
 *   as concrete symbols, if the rule is to be included in the
 *   concrete grammar.
 */
#ifdef PROTO_OK
void
MarkConSym (DefTableKey key)
#else
void
MarkConSym (key)
DefTableKey key;
#endif
{
  SymbolPList prod;

  /* If there is no corresponding concrete rule, the abstract   */
  /* rule is reachable, and it is not a chain production, then  */
  /* it needs to be included as a concrete production.          */
  if ((GetAbsMatch(key, NULLDefTableKeyList) == NULLDefTableKeyList) &&
        (GetReach(key, 0)) &&
        (GetArgCount(key, 0) != 1)) {
    ResetConSym(GetLHS(key, NoKey), 1);
    prod = GetRHS(key, NULLSymbolPList);
    while (prod != NULLSymbolPList) {
      if (SymbolClassGet(HeadSymbolPList(prod)) != GEN_IDENT)
        ResetConSym(SymbolKeyGet(HeadSymbolPList(prod)), 1);
      prod = TailSymbolPList(prod);
    }
  }
}

