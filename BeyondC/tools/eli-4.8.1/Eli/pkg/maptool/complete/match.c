

#include "deftbl.h"
#include "err.h"
#include "csm.h"
#include "oiladt2.h"
#include "Strings.h"
#include "match.h"
#include "map.h"
#include "rules.h"
#include "pdl_gen.h"
#include "symbol.h"
#include "eliproto.h"

/* On Entry:
 *   conkey - the concrete symbol to start with
 *   root - the root of the LISTOF (this may be a symbolic equivalent)
 *   absprod - the abstract LISTOF production
 *   traversal - how many traversals from the root
 *   coord - coordinates of the LISTOF for error reporting
 * On Exit:
 *   This function will recursively descend the rules of the concrete
 *   grammar beginning with conkey (which is equivalent to root for the
 *   first invocation).  The recursive descent stops when one of the
 *   rhs symbols of the LISTOF is found (or a symbol that can be coerced
 *   into a rhs symbol) or the root symbol of this traversal is found.
 *   For each traversal, rules that are found are marked with the traversal
 *   number, so that it is possible to determine whether a rule has been
 *   seen on this traversal or not.  This function also sets the Recursive
 *   property for root symbols that are recursively defined (the symbol
 *   appears on the rhs later in the traversal).
 */
#ifdef PROTO_OK
void
ListofRecurse (DefTableKey conkey, DefTableKey root, DefTableKey absprod,
                int traversal, POSITION *coord)
#else
void
ListofRecurse (conkey, root, absprod, traversal, coord)
DefTableKey conkey, root, absprod;
int traversal;
POSITION *coord;
#endif
{
  DefTableKeyList conrules;
  SymbolPList conrhs, rhslist;
  DefTableKey conmapkey, conelt, conrhskey;
  SymbolP conrhselt;

  conmapkey = GetMap(conkey, conkey);

  /* Make sure to establish an OIL type for conmapkey, so that the      */
  /* following coercion test functions properly.                        */
  if (GetOilType(conmapkey, OilErrorType()) == OilErrorType())
    ResetOilType(conmapkey, OilNewType(conmapkey));

  /* Does the concrete key match any of the RHS elements of the LISTOF? */
  /* Or is it coercible to any of the RHS elements?                     */
  /* We don't want to do this test if we are at the root symbol, since  */
  /* the root symbol might be coercible to one of the RHS elements and  */
  /* cause the matching to stop prematurely.                            */
  if (conmapkey != root) {
    rhslist = GetRHS(absprod, NULLSymbolPList);
    while (rhslist != NULLSymbolPList &&
           !OilIsValidCS(OilCoerce(GetOilType(conmapkey, OilErrorType()),
                         GetOilType(SymbolKeyGet(HeadSymbolPList(rhslist)),
                                OilErrorType()))))
      rhslist = TailSymbolPList(rhslist);
  }

  /* If it doesn't, then continue to recursively descend the grammar */
  if (conmapkey == root || rhslist == NULLSymbolPList) {

    /* Get each of the concrete rules that have this lhs symbol */
    conrules = GetConRules(conkey, NULLDefTableKeyList);

    /* If we've reached a terminal symbol that isn't supposed to be on  */
    /* the rhs, then we have to issue an error message.                 */
    if (conrules == NULLDefTableKeyList && conkey != root) {
      obstack_strgrow(Csm_obstk, "Terminal symbol, \"");
      obstack_strgrow(Csm_obstk, StrStr(conkey));
      message(FATAL,
              obstack_strcpy(Csm_obstk,
                        "\", reached unexpectedly while matching LISTOF"),
              0, coord);
    }

    while (conrules != NULLDefTableKeyList) {
      conelt = HeadDefTableKeyList(conrules);
      if (GetTraversal(conelt, 0) < traversal) {
        ResetTraversal(conelt, traversal);

        if (GetMatch(conelt, NoKey) == NoKey) {

          /* Mark the production as being matched */
          ResetMatch(conelt, absprod);
          ResetAbsMatch(absprod, AppElDefTableKeyList(GetAbsMatch(absprod,
                                        NULLDefTableKeyList), conelt));
        }

        /* Recursively descend into each RHS symbol */
        conrhs = GetRHS(conelt, NULLSymbolPList);
        while (conrhs != NULLSymbolPList) {
          conrhselt = HeadSymbolPList(conrhs);
          if (SymbolClassGet(conrhselt) == IDENTIFIER) {
            conrhskey = SymbolKeyGet(conrhselt);

            /* Issue a fatal error message if a symbolic equivalent of the */
            /* root is found along a traversal path from one of the other  */
            /* symbolic equivalents.                                       */
            if (conrhskey != root &&
                !GetBadRootError(conrhskey, 0) &&
                GetMap(conrhskey, conrhskey) == GetLHS(absprod, NoKey)) {
              obstack_1grow(Csm_obstk, '"');
              obstack_strgrow(Csm_obstk, StrStr(conrhskey));
              message(FATAL,
                obstack_strcpy(Csm_obstk,
                  "\" is the root of a LISTOF and is a descendant of a \
symbolically equivalent symbol"),
                  0, coord);

              /* Only issue the message once per symbol */
              ResetBadRootError(conrhskey, 1);
            }

            /* If the rhs symbol is equivalent to the root of this      */
            /* traversal, then we have to mark the root as recursively  */
            /* defined.  This is needed so that we can insert an extra  */
            /* chain rule at the root of the LISTOF.                    */
            if (conrhskey == root)
              ResetRecursive(root, 1);
            else
              ListofRecurse(SymbolKeyGet(conrhselt), root, absprod, traversal,
                                coord);
          }
          conrhs = TailSymbolPList(conrhs);
        }
      }
      conrules = TailDefTableKeyList(conrules);
    }
  }
}

/* On Entry:
 *   listof - the DefTableKey representing the LISTOF rule
 *   coord - the coordinates to use in error reporting
 * On Exit:
 *   VerifyListof checks the rhs symbols of each rule that matches the
 *   LISTOF.  If it is not one of the symbols on the rhs of the LISTOF (or
 *   coercible to one) and it is not the root symbol, then we must verify
 *   that the symbol cannot be derived from a concrete rule that is not
 *   matched to the LISTOF.  This guarantees that all intermediate symbols
 *   used in determining the structure of the LISTOF do not appear elsewhere
 *   in the grammar.  A fatal error message is issued if this is found to be
 *   the case.
 */
#ifdef PROTO_OK
void
VerifyListof (DefTableKey listof, POSITION *coord)
#else
void
VerifyListof (listof, coord)
DefTableKey listof;
POSITION *coord;
#endif
{
  DefTableKeyList conrules, rhsconrules;
  SymbolPList conrhs, listofrhs;
  DefTableKey conmapkey;
  SymbolP conrhselt;

  /* For each concrete rule that matches the LISTOF */
  conrules = GetAbsMatch(listof, NULLDefTableKeyList);
  while (conrules != NULLDefTableKeyList) {

    /* For each rhs symbol of that rule */
    conrhs = GetRHS(HeadDefTableKeyList(conrules), NULLSymbolPList);
    while (conrhs != NULLSymbolPList) {
      conrhselt = HeadSymbolPList(conrhs);
      if (SymbolClassGet(conrhselt) == IDENTIFIER) {
        conmapkey = GetMap(SymbolKeyGet(conrhselt), SymbolKeyGet(conrhselt));

        /* Does the concrete key match any RHS elements of the LISTOF? */
        /* Or is it coercible to any of the RHS elements?              */
        listofrhs = GetRHS(listof, NULLSymbolPList);
        while (listofrhs != NULLSymbolPList &&
               !OilIsValidCS(OilCoerce(GetOilType(conmapkey, OilErrorType()),
                        GetOilType(SymbolKeyGet(HeadSymbolPList(listofrhs)),
                                OilErrorType()))))
          listofrhs = TailSymbolPList(listofrhs);

        /* If it didn't match any of the RHS elements and it isn't the  */
        /* root symbol of the LISTOF.                                   */
        if (listofrhs == NULLSymbolPList &&
                conmapkey != GetLHS(listof, NoKey)) {

          /* Check each of the rules that have this symbol on their rhs */
          /* and make sure that all of them only match the LISTOF rule. */
          rhsconrules = GetRHSConRules(SymbolKeyGet(conrhselt),
                                        NULLDefTableKeyList);
          while (rhsconrules != NULLDefTableKeyList) {

            /* If not, issue a fatal error message */
            if (GetMatch(HeadDefTableKeyList(rhsconrules), NoKey) != listof) {
              obstack_strgrow(Csm_obstk, "Symbol, \"");
              obstack_strgrow(Csm_obstk, StrStr(SymbolKeyGet(conrhselt)));
              message(FATAL,
                obstack_strcpy(Csm_obstk,
                        "\", may not be used in defining the structure of a \
LISTOF rule and be used elsewhere in the grammar."),
                        0, coord);
              rhsconrules = TailDefTableKeyList(rhsconrules);
            }
            rhsconrules = TailDefTableKeyList(rhsconrules);
          }
        }
      }
      conrhs = TailSymbolPList(conrhs);
    }
    conrules = TailDefTableKeyList(conrules);
  }
}

/* On Entry:
 *   key - an abstract LISTOF rule key
 *   coord - coordinates of the LISTOF
 * On Exit:
 *   ListofMatch recursively descends into the rules of the concrete grammar
 *   beginning with the lhs of the LISTOF rule and stopping at points where
 *   the lhs is found again or any of the elements of the rhs of the LISTOF
 *   are found.  All rules traversed are matched to the LISTOF.  In the
 *   future, this function must also guarantee that all intermediate symbols
 *   found along any of these paths is not reachable from other symbols in
 *   the grammar.
 */
#ifdef PROTO_OK
void
ListofMatch (DefTableKey key, POSITION *coord)
#else
void
ListofMatch (key, coord)
DefTableKey key;
POSITION *coord;
#endif
{
  DefTableKey lhskey, rhskey;
  DefTableKeyList lhsequivs;
  SymbolPList rhs;
  int traversal;

  /* First make sure that OIL types are established for all right hand  */
  /* side symbols of the LISTOF so that we can determine if there are   */
  /* coercions between the symbols we encounter in the recursive        */
  /* matching process and the right hand side symbols of the LISTOF.    */
  rhs = GetRHS(key, NULLSymbolPList);
  while (rhs != NULLSymbolPList) {
    rhskey = SymbolKeyGet(HeadSymbolPList(rhs));
    if (GetOilType(rhskey, OilErrorType()) == OilErrorType())
      ResetOilType(rhskey, OilNewType(rhskey));
    rhs = TailSymbolPList(rhs);
  }

  /* Recursively descend beginning at the lhs of the LISTOF and all     */
  /* symbols in the same equivalence class with the lhs symbol.         */
  lhskey = GetLHS(key, NoKey);
  traversal = 1;
  ListofRecurse(lhskey, lhskey, key, traversal, coord);
  lhsequivs = GetAbsMap(lhskey, NULLDefTableKeyList);
  while (lhsequivs != NULLDefTableKeyList) {
    lhskey = HeadDefTableKeyList(lhsequivs);
    ++traversal;
    ListofRecurse(lhskey, lhskey, key, traversal, coord);
    lhsequivs = TailDefTableKeyList(lhsequivs);
  }

  /* Make sure that symbols used in defining the structure of the LISTOF */
  /* don't appear elsewhere in the grammar.                              */
  VerifyListof(key, coord);
}

/* On Entry:
 *   listptr - a pointer to a list representing the rhs of a rule
 * On Exit:
 *   NextSymbol will return the next symbol which represents an
 *   identifier or literal and is not a parser modification or action or
 *   an abstract symbol preceded by a '$'.
 *   A NULL pointer is returned if no such key exists.  On exit, the list
 *   pointed to by listptr will be set to the list following the symbol
 *   returned.
 */
#ifdef PROTO_OK
SymbolP
NextSymbol (SymbolPList *listptr)
#else
SymbolP
NextSymbol (listptr)
SymbolPList *listptr;
#endif
{
  int cls;
  SymbolP result;

  while (*listptr != NULLSymbolPList) {
    cls = SymbolClassGet(HeadSymbolPList(*listptr));
    if (cls == IDENTIFIER || cls == TEXT)
      break;
    *listptr = TailSymbolPList(*listptr);
  }

  if (*listptr == NULLSymbolPList)
    return (SymbolP)0;
  else {
    result = HeadSymbolPList(*listptr);
    *listptr = TailSymbolPList(*listptr);
    return result;
  }
}

/* On Entry:
 *   key - a concrete rule key which doesn't have a match in
 *              the abstract grammar
 * On Exit:
 *   A new key is created which represents all of the rules which
 *   are equivalent to key after symbolic mapping is performed.
 *   Each rule which belongs to this equivalence group has its
 *   Duplicate property set to the newly created key and the
 *   newly created key is returned.
 *   This is done to ensure that only one abstract rule is generated
 *   for each of these equivalence groupings.
 */
#ifdef PROTO_OK
DefTableKey
Duplicates (DefTableKey key)
#else
DefTableKey
Duplicates (key)
DefTableKey key;
#endif
{
  DefTableKeyList rules, lhslist;
  DefTableKey DupKey, lhs, lhsmap;

  /* Create the new key */
  DupKey = NewKey();

  /* Assemble a list of all concrete rules which have lhs' in   */
  /* same symbolic equivalence class.                           */
  lhs = GetLHS(key, NoKey);
  lhsmap = GetMap(lhs, lhs);
  rules = GetConRules(lhsmap, NULLDefTableKeyList);
  lhslist = GetAbsMap(lhsmap, NULLDefTableKeyList);
  while (lhslist != NULLDefTableKeyList) {
    rules = AppDefTableKeyList(rules,
                GetConRules(HeadDefTableKeyList(lhslist),
                        NULLDefTableKeyList));
    lhslist = TailDefTableKeyList(lhslist);
  }

  /* Check each rule in the list to see if it is equivalent to  */
  /* key.  If it is, set its Duplicate property to the newly    */
  /* created key.                                               */
  while (rules != NULLDefTableKeyList) {
    if (RuleCmp(HeadDefTableKeyList(rules), key, 1))
      ResetDuplicate(HeadDefTableKeyList(rules), DupKey);
    rules = TailDefTableKeyList(rules);
  }

  /* Return the newly created key */
  return DupKey;
}

static void
#ifdef PROTO_OK
IdentifyOp(DefTableKey abs, DefTableKey con, tOilSetSig sig,
           DefTableKey rule, CoordPtr coord)
#else
IdentifyOp(abs, con, sig, rule, coord)
DefTableKey abs, con, rule; tOilSetSig sig; CoordPtr coord;
#endif
/* Identify an abstract production
 *   On entry-
 *     abs=key of abstract LHS symbol
 *     con=key of concrete LHS symbol
 *     sig=signature of the desired production
 *     rule=key of abstract rule
 *     coord=points to source text coordinates for error reporting
 ***/
{ tOilOp ind;

  /* If there is no indication for the lhs, then there is no match */
  ind = GetOilOp(abs, OilErrorOp());
  if (OilIsValidOp(ind)) {
    tOilOpSet opset;

    /* Using the indication (the abstract lhs) and the signature of     */
    /* the concrete rule, find a set of abstract rules which could      */
    /* match it.                                                        */
    opset = OilIdOpSet(ind, sig, 0);

    if (!OilEmptyOS(opset) && !OilEmptyOS(OilTailOS(opset)) && rule == NoKey) {
      obstack_strgrow(Csm_obstk, "Multiple possible matches for this rule: ");
      obstack_strgrow(Csm_obstk, StrStr(OilOpName(OilHeadOS(opset))));
      opset = OilTailOS(opset);
      while (!OilEmptyOS(opset)) {
        obstack_strgrow(Csm_obstk, ", ");
        obstack_strgrow(Csm_obstk, StrStr(OilOpName(OilHeadOS(opset))));
        opset = OilTailOS(opset);
      }
      obstack_1grow(Csm_obstk, '\0');
      message(ERROR, obstack_finish(Csm_obstk), 0, coord);
    } else {
      while (!OilEmptyOS(opset)) {
        DefTableKey absrule = OilOpName(OilHeadOS(opset));
        if (rule == NoKey || rule == absrule) {
          ResetMatch(con, absrule);
          ResetAbsMatch(
            absrule,
            AppElDefTableKeyList(
              GetAbsMatch(absrule, NULLDefTableKeyList),
              con));
          break;
        }
        opset = OilTailOS(opset);
      }
    }
  }
}

/* On Entry:
 *   key - a concrete rule key
 *   sig - the OIL signature of this concrete rule
 *   rule - an abstract rule key
 *   coord - source text coordinates for issuing error messages
 */
void
#ifdef PROTO_OK
ConMatch (DefTableKey key, tOilSetSig sig, DefTableKey rule, CoordPtr coord)
#else
ConMatch (key, sig, rule, coord)
DefTableKey key;
tOilSetSig sig;
DefTableKey rule;
CoordPtr coord;
#endif
{ DefTableKey conlhs, abslhs;

  /* If this concrete rule already has a match, then don't bother       */
  /* finding another one.  If the Duplicate property is set for this    */
  /* key, then we know that the rule doesn't have a match in the        */
  /* abstract grammar and we've already generated a name for the rule.  */
  if ((GetMatch(key, NoKey) != NoKey) || (GetDuplicate(key, NoKey) != NoKey))
    return;

  conlhs = GetLHS(key, NoKey);
  abslhs = GetMap(conlhs, conlhs);

  /* If this rule is a chain rule, then we have to try to match it      */
  /* against a coercion.                                                */
  if (GetArgCount(key, 0) == 1) {
    SymbolPList conrhs;
    DefTableKey conkey;
    tOilCoercionSeq sequence;

    if ((conrhs = GetMappedRHS(key, NULLSymbolPList)) == NULLSymbolPList)
      conrhs = GetRHS(key, NULLSymbolPList);
    conkey = SymbolKeyGet(NextSymbol(&conrhs));
    sequence = OilCoerce(GetOilType(GetMap(conkey, conkey), OilErrorType()),
                        GetOilType(GetMap(conlhs, conlhs), OilErrorType()));
    if (OilEmptyCS(sequence)) {
      IdentifyOp(abslhs, key, sig, rule, coord);
    } else if (OilIsValidCS(sequence)) {
      DefTableKey absrule;

      while (!OilEmptyCS(OilTailCS(sequence))) {
        absrule = OilOpName(OilHeadCS(sequence));
        ResetAbsMatch(absrule, AppElDefTableKeyList(GetAbsMatch(absrule,
                                                NULLDefTableKeyList),
                                                key));
        sequence = OilTailCS(sequence);
      }
      absrule = OilOpName(OilHeadCS(sequence));
      ResetMatch(key, absrule);
      ResetAbsMatch(absrule, AppElDefTableKeyList(GetAbsMatch(absrule,
                                                NULLDefTableKeyList),
                                                key));
    }
  } else {
    IdentifyOp(abslhs, key, sig, rule, coord);
  }
 
  /* If we didn't find a match, then find all the symbolically  */
  /* equivalent concrete rules and generate an abstract rule    */
  /* name for these rules.  Note that QChains from the concrete */
  /* grammar are not included in the abstract grammar.          */
  if (GetMatch(key, NoKey) == NoKey &&
      ((MapQChains && !Trivial(key)) || !QChain(key)))
    GenRuleName(Duplicates(key));
    
  return;
}

/* On Entry:
 *   key - a symbol key
 * On Exit:
 *   If an OIL type has not yet been created for the abstract equivalent of
 *   the symbol represented by key, such an OIL type is created.  An OIL
 *   TypeSet with that OIL type as its only element is returned.
 */
#ifdef PROTO_OK
tOilTypeSet
CreateTS (DefTableKey key)
#else
tOilTypeSet
CreateTS (key)
DefTableKey key;
#endif
{
  tOilType type;

  key = GetMap(key, key);

  /* If the OIL type doesn't exist, create it */
  type = GetOilType(key, OilErrorType());
  if (type == OilErrorType()) {
    type = OilNewType(key);
    ResetOilType(key, type);
  }

  /* Return the OIL typeset with type as its only element */
  return OilTypeToSet(type);
}

