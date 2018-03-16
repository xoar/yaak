

#include <stdio.h>
#include "deftbl.h"
#include "ptg_gen.h"
#include "pdl_gen.h"
#include "ActionStack.h"
#include "intList.h"
#include "DefTableKeyList.h"
#include "SymbolPList.h"
#include "MakeName.h"
#include "rules.h"
#include "match.h"
#include "map.h"
#include "output.h"
#include "symbol.h"
#include "eliproto.h"

/* forward definition of the function */
PTGNode GenCanonicalLISTOF ELI_ARG((DefTableKey listofkey, DefTableKey root,
                                int pgram));

#ifdef PROTO_OK
PTGNode
GenChain (DefTableKey key, int pgram)
#else
PTGNode
GenChain (key, pgram)
DefTableKey key;
int pgram;
#endif
/* Create chain rules
 * On Entry:
 *   key - a chain rule key, i.e., only one symbol on the rhs
 *   pgram - 1 if we are generating this for the parsing grammar,
 *              0 if we are generating it for the concrete syntax
 * On Exit:
 *   GenChain returns this chain rule and concatenates any other abstract
 *   chain rules which may need to be included as a result.
 *   For the parsing grammar, terminal symbols must have special nested
 *   actions.
 ***/
{
  DefTableKey lhs, absrule;
  SymbolP rhs;
  SymbolPList rhslist;
  DefTableKeyList absrules;
  PTGNode result, action;
  int ChainDone;

  lhs = GetLHS(key, NoKey);

  if (pgram)
    ChainDone = GetPChainDone(key, 0);
  else
    ChainDone = GetChainDone(key, 0);

  /* The left hand side must already be a symbol in the concrete        */
  /* syntax or the left hand side must the start symbol.                */
  if (!ChainDone &&
        GetAbsMatch(key, NULLDefTableKeyList) == NULLDefTableKeyList &&
        (GetConSym(lhs, 0) ||
        (GetAbsMap(lhs, NULLDefTableKeyList) == NULLDefTableKeyList &&
         GetStart(lhs, 0)))) {

    if (pgram)
      ResetPChainDone(key, 1);
    else
      ResetChainDone(key, 1);

    /* Get the rhs symbol */
    rhslist = GetRHS(key, NULLSymbolPList);

    if (pgram) {
      action = PTGNULL;
      while (SymbolClassGet(HeadSymbolPList(rhslist)) == GEN_IDENT) {
        action = PTGCommaSeq(action, PTGNullNode());
        rhslist = TailSymbolPList(rhslist);
      }

      rhs = HeadSymbolPList(rhslist);
      if (SymbolClassGet(rhs) == IDENTIFIER) {
        if (GetNonTerm(SymbolKeyGet(rhs), 0))
          action = PTGCommaSeq(action, PTGActionArg(PTGPos(1)));
        else
          action = PTGCommaSeq(action,
                PTGTermAction(PTGAsIs(StrStr(SymbolKeyGet(rhs))), PTGPos(1)));
      }

      rhslist = TailSymbolPList(rhslist);
      while (rhslist != NULLSymbolPList &&
                SymbolClassGet(HeadSymbolPList(rhslist)) == GEN_IDENT) {
        action = PTGCommaSeq(action, PTGNullNode());
        rhslist = TailSymbolPList(rhslist);
      }

      action = PTGCommaSeq(PTGCurPos(), action);

      if ((SymbolClassGet(rhs) == IDENTIFIER) &&
          (GetNonTerm(SymbolKeyGet(rhs), 0)))
        action = PTGAction(PTGNULL,
                   PTGNestActionArg(PTGAsIs(StrStr(key)), action));
      else
        action = PTGAction(PTGIncStackPtr(),
                   PTGNestActionArg(PTGAsIs(StrStr(key)),
                     action));

      result = PTGConRule(PTGAsIs(StrStr(lhs)),
                        PTGSpcSeq(PTGAsIs(StrStr(SymbolKeyGet(rhs))), action));
    } else {
      rhs = NextSymbol(&rhslist);
      result = PTGConRule(PTGAsIs(StrStr(lhs)),
                        PTGAsIs(StrStr(SymbolKeyGet(rhs))));
    }

    /* If the rhs is a symbol in the concrete syntax or if it is TEXT,  */
    /* we have nothing further to do.                                   */
    if (GetConSym(SymbolKeyGet(rhs), 0) || (SymbolClassGet(rhs) == TEXT))
      return result;

    /* If the rhs is not yet a symbol in the concrete grammar, we have  */
    /* to mark that it now is by the introduction of this chain rule    */
    /* and see if there are any other abstract chain rules that must be */
    /* introduced as a result.  Introduction of all abstract rules      */
    /* which can contribute to the concrete syntax is done to ensure    */
    /* the connectivity of the concrete grammar.                        */
    /* We also want to check if the new rhs symbol introduced is the lhs*/
    /* of a LISTOF, in which case we may need to generate a canonical   */
    /* version of the LISTOF.                                           */
    else {
      ResetConSym(SymbolKeyGet(rhs), 1);
      absrules = GetAbsRules(SymbolKeyGet(rhs), NULLDefTableKeyList);
      while (absrules != NULLDefTableKeyList) {
        absrule = HeadDefTableKeyList(absrules);
        if (GetType(absrule, T_NONLISTOF) == T_LISTOF)
          result = PTGSeq(result, GenCanonicalLISTOF(absrule,
                                                SymbolKeyGet(rhs), pgram));
        else if (GetArgCount(HeadDefTableKeyList(absrules), 0) == 1)
          result = PTGSeq(result, GenChain(HeadDefTableKeyList(absrules),
                                                pgram));
        absrules = TailDefTableKeyList(absrules);
      }
      return result;
    }
  } else
    return PTGNULL;
}


/* On Entry:
 *   listofkey - a LISTOF rule key
 *   root - a symbolic equivalent to the lhs of the LISTOF
 *   pgram - 1 if we are generating this for the parsing grammar,
 *              0 if we are generating it for the concrete syntax
 * On Exit:
 *   GenCanonicalLISTOF will generate a canonical representation of
 *   the LISTOF rule key given by listofkey rooted by the symbolic
 *   equivalent of the lhs of the LISTOF given by root.  It will not
 *   be generated if lhs already has defining productions in the concrete
 *   syntax.
 */
#ifdef PROTO_OK
PTGNode
GenCanonicalLISTOF (DefTableKey listofkey, DefTableKey root, int pgram)
#else
PTGNode
GenCanonicalLISTOF (listofkey, root, pgram)
DefTableKey listofkey;
DefTableKey root;
int pgram;
#endif
{
  PTGNode lhs, rhs, result;
  SymbolPList rhslist;
  DefTableKey elt, absrule;
  DefTableKeyList absrules;
  int LISTOFDone;

  if (pgram)
    LISTOFDone = GetPLISTOFDone(listofkey, 0);
  else
    LISTOFDone = GetLISTOFDone(listofkey, 0);

  if (GetConRules(root, NULLDefTableKeyList) != NULLDefTableKeyList ||
      LISTOFDone)
    return PTGNULL;

  if (pgram)
    ResetPLISTOFDone(listofkey, 1);
  else
    ResetLISTOFDone(listofkey, 1);

  rhslist = GetRHS(listofkey, NULLSymbolPList);
  rhs = PTGNULL;
  lhs = PTGAsIs(StrStr(root));

  while (rhslist != NULLSymbolPList) {
    elt = SymbolKeyGet(HeadSymbolPList(rhslist));

    if (pgram) {
      /* If the rhs element is a terminal, the tree construction must   */
      /* be done differently.                                           */
      if (!GetNonTerm(elt, 0))
        rhs = PTGSeq(rhs, PTGPgramRecList(lhs,
                                PTGAsIs(StrStr(elt)),
                                PTGAsIs(StrStr(listofkey)),
                                PTGTermAction(PTGAsIs(StrStr(elt)),PTGPos(2))));
      else
        rhs = PTGSeq(rhs, PTGPgramRecList(lhs, PTGAsIs(StrStr(elt)),
                                        PTGAsIs(StrStr(listofkey)),
                                        PTGActionArg(PTGPos(2))));
    } else
      rhs = PTGSeq(rhs, PTGConRecList(lhs, PTGAsIs(StrStr(elt))));

    rhslist = TailSymbolPList(rhslist);
  }

  if (pgram)
    result = PTGPgramList(lhs, PTGAsIs(StrStr(listofkey)), rhs);
  else
    result = PTGConList(lhs, rhs);

  /* Check to see if there are any abstract chain productions that must */
  /* be added now because of the rhs symbols of the LISTOF being added. */
  rhslist = GetRHS(listofkey, NULLSymbolPList);
  while (rhslist != NULLSymbolPList) {
    elt = SymbolKeyGet(HeadSymbolPList(rhslist));
    if (!GetConSym(elt, 0)) {
      ResetConSym(elt, 1);
      absrules = GetAbsRules(elt, NULLDefTableKeyList);
      while (absrules != NULLDefTableKeyList) {
        absrule = HeadDefTableKeyList(absrules);
        if (GetArgCount(absrule, 0) == 1)
          result = PTGSeq(result, GenChain(absrule, pgram));
        absrules = TailDefTableKeyList(absrules);
      }
    }
    rhslist = TailSymbolPList(rhslist);
  }

  return result;
}

#ifdef PROTO_OK
PTGNode
GenLISTOF (DefTableKey key, int pgram)
#else
PTGNode
GenLISTOF (key, pgram)
DefTableKey key;
int pgram;
#endif
/* Generate concrete rules for a LISTOF if necessary
 * On Entry:
 *   key - a LISTOF rule key
 *   pgram - 1 if we are generating this for the parsing grammar,
 *              0 if we are generating it for the concrete syntax
 * On Exit:
 *   GenLISTOF checks each of the symbolic equivalents to the LHS of the
 *   LISTOF and generates canonical representations for the LISTOF
 *   with the symbolic equivalents at the root if the symbol doesn't
 *   have defining productions in the concrete syntax already.
 ***/
{
  DefTableKey lhs;
  DefTableKeyList lhsequivs;
  PTGNode result;

  result = PTGNULL;

  lhs = GetLHS(key, NoKey);
  if (GetConSym(lhs, 0))
    result = GenCanonicalLISTOF(key, lhs, pgram);

  lhsequivs = GetAbsMap(lhs, NULLDefTableKeyList);
  while (lhsequivs != NULLDefTableKeyList) {
    result = PTGSeq(result, GenCanonicalLISTOF(key,
                                HeadDefTableKeyList(lhsequivs), pgram));
    lhsequivs = TailDefTableKeyList(lhsequivs);
  }

  return result;
}


/* On Entry:
 *   seq - an Oil coercion sequence
 *
 * On Exit:
 *   BottomUpConstraint checks each coercion operator along the sequence
 *   to see if there is a bottomup constraint on the construction of the
 *   chain sequence represented by seq.  It returns 1 if there is a constraint
 *   and 0 if there isn't.
 */
int
#ifdef PROTO_OK
BottomUpConstraint (tOilCoercionSeq seq)
#else
BottomUpConstraint (seq)
tOilCoercionSeq seq;
#endif
{
  for ( ; !OilEmptyCS(seq); seq = OilTailCS(seq))
    if (GetBottomUp(OilOpName(OilHeadCS(seq)), 0))
      return 1;

  return 0;
}

/* On Entry:
 *   symbol - the right hand side symbol to generate
 *   rule - the key for the rule that symbol is on the rhs of
 *   pgram - flag to indicate if generating for the parsing grammar
 *
 * On Exit:
 *   GenRHSSymbol generates and returns the PTGNode representation of
 *   symbol.  This includes possible modifiers (dollar and at) embedded
 *   actions.  It also checks to see if the symbol matches a root of a
 *   recursively defined LISTOF.  In this case, it prefixes the name
 *   of the symbol with LST_ so that a chain rule can be introduced at
 *   the root to finalize the LISTOF.
 */
PTGNode
#ifdef PROTO_OK
GenRHSSymbol (SymbolP symbol, DefTableKey rule, int pgram)
#else
GenRHSSymbol (symbol, rule, pgram)
SymbolP symbol;
DefTableKey rule;
int pgram;
#endif
{
  PTGNode result = PTGNULL;
  DefTableKey key;
  int cls;

  key = SymbolKeyGet(symbol);
  cls = SymbolClassGet(symbol);

  switch (cls) {

  case IDENTIFIER:
  case ATMODIDN:
  case DOLLARMODIDN:
    if (pgram) {
      if (GetRecursive(key, 0) &&
          GetType(GetMatch(rule, NoKey), T_NONLISTOF) == T_LISTOF)
        result = PTGListGenSym(PTGAsIs(StrStr(key)));
      else
        result = PTGAsIs(StrStr(key));
    } else
      result = PTGAsIs(StrStr(key));
    break;

  case TEXT:
  case ATMODTXT:
  case DOLLARMODTXT:
    result = PTGAsIs(StrStr(key));
    break;

  case ACTION:
    result = PTGConnection(PTGAsIs(StrStr(key)));
    break;
  }

  /* Add any appropriate modifiers */
  switch (cls) {

  case IDENTIFIER:
  case GEN_IDENT:
  case TEXT:
  case ACTION:
    break;

  case ATMODIDN:
  case ATMODTXT:
    result = PTGAtMod(result);
    break;

  case DOLLARMODIDN:
  case DOLLARMODTXT:
    result = PTGDollarMod(result);
    break;
  }

  return result;
}

#ifdef PROTO_OK
PTGNode
GenLISTOFRHS (DefTableKey key, PTGNode RuleName, DefTableKey absrulekey,
              int pgram, PTGNode *added)
#else
PTGNode
GenLISTOFRHS (key, RuleName, absrulekey, pgram, added)
DefTableKey key;
PTGNode RuleName;
DefTableKey absrulekey;
int pgram;
PTGNode *added;
#endif
/* On Entry:
 *   key - a rule key whose abstract counterpart is a LISTOF
 *   RuleName - a PTGNode with the abstract rule name for use in creating the
 *              tree construction function names
 *   absrulekey - the rule key for the LISTOF
 *   pgram - is this for the parsing grammar
 * On Exit:
 *   Generate the PTG output for the right hand side of a concrete rule
 *   that matches a LISTOF (including the action).
 *
 * If this concrete rule is matched to an abstract LISTOF, then
 * the parsing action depends on the number of nonterminals.  If
 * there are 0, we use the Mk0 tree construction function.  If
 * there is 1, we do nothing unless it is the root of the LISTOF.
 * If there is more than 1, we successively nest Mk2 tree
 * construction functions for each of the nonterminals.  If the
 * lhs of the concrete rule is the root of the LISTOF, we must
 * always place the simple Mk function at the outermost level.
 ***/
{
  int argcount, ntcount, termcount, cls;
  PTGNode rhs, action, stackstmt, tmp;
  DefTableKey lhskey, rhskey, mappedkey;
  SymbolPList rhslist, listofrhs;
  tOilCoercionSeq seq;
  SymbolP symbol;

  /* These are the two pieces of output that we are generating. */
  rhs = PTGNULL;
  action = PTGNULL;

  /* argcount keeps track of the total number of right hand side symbols    */
  /*   that appear on the token stack (doesn't count symbols w/ modifiers)  */
  /* ntcount counts the number of nonterminals on the rhs whose tree nodes  */
  /*   are gotten from the stack                                            */
  /* termcount counts the number of terminals that are coerced to rhs's of  */
  /*   the LISTOF and have actions associated with them                     */
  argcount = 0;
  ntcount = 0;
  termcount = 0;

  rhslist = GetRHS(key, NULLSymbolPList);
  while (rhslist != NULLSymbolPList) {

    symbol = HeadSymbolPList(rhslist);
    rhskey = SymbolKeyGet(symbol);
    cls = SymbolClassGet(symbol);

    /* If we're not generating for the parsing grammar or we found a symbol */
    /* that is a modified symbol or an action, then just add the symbol to  */
    /* the rule and continue in the loop.                                   */
    if (!pgram || (cls != TEXT && cls != IDENTIFIER)) {
      rhs = PTGSpcSeq(rhs, GenRHSSymbol(symbol, key, pgram));
      rhslist = TailSymbolPList(rhslist);
      continue;
    }

    mappedkey = GetMap(rhskey, rhskey);
    ++argcount;

    /* Here we loop to see if the current symbol can be coerced to one of   */
    /* the rhs's of the LISTOF.                                             */
    listofrhs = GetRHS(absrulekey, NULLSymbolPList);
    while (listofrhs != NULLSymbolPList &&
           !OilIsValidCS(
             seq = OilCoerce(GetOilType(mappedkey, OilErrorType()),
                             GetOilType(
                               SymbolKeyGet(HeadSymbolPList(listofrhs)),
                               OilErrorType()))))
      listofrhs = TailSymbolPList(listofrhs);

    /* If it is coercible to one of the rhs's of the LISTOF and the       */
    /* coercion sequence is non-empty...                                  */
    if (listofrhs != NULLSymbolPList && !OilEmptyCS(seq)) {

      /* If the sequence has bottomup constraints, then we have to insert */
      /* a chain rule into the parsing grammar to make sure the leaf is   */
      /* built immediately.                                               */
      if (BottomUpConstraint(seq)) {

        /* Keep track of whether or not we have to increment the node stack */
        /* for a terminal symbol being coerced to a rhs of the LISTOF.      */
        int AddToStack = 0;

        /* The new generated name for the chain rule being introduced. */
        PTGNode BottomUpName;

        ++ntcount;
        BottomUpName = PTGAsIs(StringTable(GenerateName("BU")));
        rhs = PTGSpcSeq(rhs, BottomUpName);

        /* The piece of the action for the current symbol will be to just  */
        /* get an element from the stack, since the added rule will place  */
        /* the appropriate node on the stack.                              */
        action = PTGCombineListArgs(RuleName, action,
                   PTGActionArg(PTGPos(ntcount)));

        /* Here we deal with the first coercion for the action of the newly */
        /* added chain rule.  (We have to do different things for terminals)*/
        if (cls == TEXT) {
          tmp = PTGNestActionArg(
                  PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                  PTGCoordStack(PTGPos(1)));
          seq = OilTailCS(seq);
          AddToStack = 1;
        } else {
          if (GetNonTerm(rhskey, 0)) {
            tmp = PTGActionArg(PTGPos(1));
          } else {
            tmp = PTGNestActionArg(
                    PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                    PTGCommaSeq(
                      PTGCoordStack(PTGPos(1)),
                      PTGTermAction(
                        PTGAsIs(StrStr(mappedkey)),
                        PTGPos(1))));
              seq = OilTailCS(seq);
              AddToStack = 1;
          }
        }

        /* Loop through and apply each of the coercions. */
        while (!OilEmptyCS(seq)) {
          tmp = PTGNestActionArg(
                  PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                  PTGCommaSeq(
                    PTGCoordStack(PTGPos(1)),
                    tmp));
          seq = OilTailCS(seq);
        }

        /* Finish creating the action for the new chain rule. */
        if (AddToStack)
          tmp = PTGAction(PTGIncStackPtr(), tmp);
        else
          tmp = PTGAction(PTGNULL, tmp);

        /* Add the new chain rule to the added output parameter. */
        tmp = PTGSpcSeq(PTGAsIs(StrStr(rhskey)), tmp);
        *added = PTGSeq(*added, PTGConRule(BottomUpName, tmp));

      /* The coercion sequence doesn't have any bottomup constraints.     */
      /* This means we don't have to worry about adding any chain rules,  */
      /* but we do have to add calls if the symbol is a terminal.         */
      } else {
        rhs = PTGSpcSeq(rhs, GenRHSSymbol(symbol, key, pgram));

        if (cls == TEXT) {
          ++termcount;
          action = PTGCombineListArgs(RuleName,
                     action,
                     PTGNestActionArg(
                       PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                       PTGCoordStack(PTGPos(argcount))));
        } else {
          if (GetNonTerm(rhskey, 0)) {
            ++ntcount;
            action = PTGCombineListArgs(RuleName,
                       action,
                       PTGActionArg(PTGPos(ntcount)));
          } else {
            ++termcount;
            action = PTGCombineListArgs(RuleName,
                       action,
                       PTGNestActionArg(
                         PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                         PTGCommaSeq(
                           PTGCoordStack(PTGPos(argcount)),
                           PTGTermAction(PTGAsIs(StrStr(mappedkey)),
                             PTGPos(argcount)))));
          }
        }
      }

    /* Either we have a literal that doesn't get coerced to any rhs of the  */
    /* LISTOF or an identifier that has an empty coercion sequence (it is   */
    /* equivalent to a rhs of the LISTOF).                                  */
    } else {
      rhs = PTGSpcSeq(rhs, GenRHSSymbol(symbol, key, pgram));
      if (cls == IDENTIFIER) {
        ++ntcount;
        action = PTGCombineListArgs(RuleName,
                   action,
                   PTGActionArg(PTGPos(ntcount)));
      }
    }

    rhslist = TailSymbolPList(rhslist);
  }

  if (!pgram)
    return rhs;

  /* Depending on the count of nonterminals being used from the node stack */
  /* in this action, we may have to increment or decrement the stack       */
  /* pointer.                                                              */
  if (ntcount == 0)
    stackstmt = PTGIncStackPtr();
  else if (ntcount == 1)
    stackstmt = PTGNULL;
  else
    stackstmt = PTGDecStackPtr(PTGPos(ntcount));

  lhskey = GetLHS(key, NoKey);

  /* If the lhs of this rule is the lhs of the LISTOF, then we have to      */
  /* insert the call to finalize the list, unless it is a recursively       */
  /* defined LISTOF.  In that case, the finalization gets done when the     */
  /* generated chain rule at the root is created.                           */
  if (!GetRecursive(lhskey, 0) &&
      GetMap(lhskey, lhskey) == GetLHS(absrulekey, NoKey)) {
    if (termcount == 0 && ntcount == 0)
      action = PTGAction(stackstmt,
                 PTGNestActionArg(RuleName,
                   PTGCommaSeq(
                     PTGCurPos(),
                     PTGNestActionArg(
                       PTGMk0Name(RuleName),
                       PTGNoPosition()))));
    else
      action = PTGAction(stackstmt,
                 PTGNestActionArg(RuleName, PTGCommaSeq(PTGCurPos(), action)));
  } else if (termcount == 0 && ntcount == 0)
    action = PTGAction(stackstmt,
             PTGNestActionArg(PTGMk0Name(RuleName), PTGNoPosition()));
  else if (termcount == 0 && ntcount == 1)
    action = PTGNULL;
  else
    action = PTGAction(stackstmt, action);

  return PTGSpcSeq(rhs, action);
}


void
#ifdef PROTO_OK
AdvancePosition (int *pos, intList *order)
#else
AdvancePosition (pos, order)
int *pos;
intList *order;
#endif
{
  if (*order == NULLintList)
    ++(*pos);
  else {
    *pos = HeadintList(*order);
    *order = TailintList(*order);
  }
}

/* On Entry:
 *   rhslist - right-hand side of a concrete rule
 * On Exit:
 *   ActionStack[i - 1] - PTGNode for the action associated with the
 *     ith non-literal symbol of the right-hand side
 */
#ifdef PROTO_OK
void
Actions(SymbolPList rhs)
#else
void
Actions(rhs)
SymbolPList rhs;
#endif
{ int argcount, ntcount;

  while (!ActionStackEmpty) ActionStackPop;

  for (argcount = ntcount = 1;
       rhs != NULLSymbolPList;
       argcount++, rhs = TailSymbolPList(rhs)) {
    SymbolP sym = HeadSymbolPList(rhs);
    DefTableKey key;

    if (SymbolClassGet(sym) != IDENTIFIER) continue;

    key = SymbolKeyGet(sym);
    if (GetNonTerm(key, 0)) {
      ActionStackPush(PTGActionArg(PTGPos(ntcount)));
      ntcount++;
    } else {
      ActionStackPush(
        PTGTermAction(PTGAsIs(StrStr(GetMap(key, key))),PTGPos(argcount)));
    }
  }
}

#ifdef PROTO_OK
PTGNode
GenConRHS (DefTableKey key, int pgram, int isabs, DefTableKey absrulekey,
           PTGNode RuleName, PTGNode *added)
#else
PTGNode
GenConRHS (key, pgram, isabs, absrulekey, RuleName, added)
DefTableKey key, absrulekey;
int pgram, isabs;
PTGNode RuleName;
PTGNode *added;
#endif
/* Generate the right hand side of a concrete rule
 * On Entry:
 *   key - a rule key
 *   pgram - flag to indicate if it is being generated for the parsing grammar
 *   isabs - flag to indicate if key is an abstract production
 *   absrulekey - if key is a concrete rule, then this is it's abstract match
 *   RuleName - PTGNode representing the abstract rule name which is the
 *              basis of the tree construction function name
 *   added - output parameter for rules to be added for proper bottomup
 *           construction
 * On Exit:
 *   Generate the PTG output for the right hand side of a concrete rule.
 *   This includes any semantic actions needed in the parsing grammar.
 *   "added" will have chain rules as required for proper bottomup
 *   construction.
 */
{
  SymbolPList rhslist, mappedrhslist, absrhslist;
  intList order;
  int conclass, absclass, argcount, ntcount, pos;
  SymbolP consym, abssym;
  DefTableKey conkey, abskey, tmpkey;
  tOilCoercionSeq seq;
  PTGNode rhs, action, tmp;

  /* RuleMapped is a flag to indicate if the rule has been mapped or not. */
  int RuleMapped = 0;

  /* This will contain the list of chain rules we may have added due to */
  /* bottomup constraints.                                              */
  *added = PTGNULL;

  if (GetType(absrulekey, T_NONLISTOF) == T_LISTOF)
    return GenLISTOFRHS(key, RuleName, absrulekey, pgram, added);
  

  /* These are the two pieces of output we want to construct. */
  rhs = PTGNULL;
  action = PTGNULL;

  rhslist = GetRHS(key, NULLSymbolPList);

  /* The following conditional determines when an action is attached    */
  /* to a chain rule.  The following criteria must hold:                */
  /*   If it is a trivial chain rule, it must never have an action.     */
  /*   If it is a concrete QChain, it must only have an action if the   */
  /*     rule exists in the abstract syntax.                            */
  /*   Otherwise, we want an action.                                    */
  /* If no action is needed, we simply loop through the rhs elements    */
  /* and then return the result.                                        */
  if (!pgram || Trivial(key) ||
      (!isabs && !MapQChains && QChain(key) && absrulekey == NoKey)) {
    while (rhslist != NULLSymbolPList) {
      rhs = PTGSpcSeq(rhs, GenRHSSymbol(HeadSymbolPList(rhslist), key, pgram));
      rhslist = TailSymbolPList(rhslist);
    }
    return rhs;
  }

  /* Define the actions corresponding to RHS non-literals */
  Actions(rhslist);

  /* Get the mapped version of the rhs is there is a rule mapping. */
  if (isabs) {
    mappedrhslist = NULLSymbolPList;
    absrhslist = rhslist;
  } else {
    mappedrhslist = GetMappedRHS(key, rhslist);
    absrhslist = GetRHS(absrulekey, NULLSymbolPList);
  }

  /* If the rule is mapped, we want to go ahead and generate the right   */
  /* hand side, since we have no reason to insert additional actions     */
  /* (for bottomup) into the right hand side.                            */
  if (!isabs && mappedrhslist != rhslist) {
    while (rhslist != NULLSymbolPList) {
      rhs = PTGSpcSeq(rhs, GenRHSSymbol(HeadSymbolPList(rhslist), key, pgram));
      rhslist = TailSymbolPList(rhslist);
    }

    /* This prevents us from trying to generate rhs elements in the rest */
    /* of this function.                                                 */
    RuleMapped = 1;
  }

  /* Get the symbol reordering list.  If there isn't one, then the      */
  /* order is just sequential, otherwise it is dictated by the order    */
  /* list.                                                              */
  order = GetOrder(key, NULLintList);
  pos = 0;
  AdvancePosition(&pos, &order);

  /* argcount keeps track of the total number of right hand side symbols    */
  /*   that appear on the token stack (doesn't count symbols w/ modifiers)  */
  /* ntcount counts the number of nonterminals on the rhs whose tree nodes  */
  /*   are gotten from the stack                                            */
  ntcount = 0;
  argcount = 0;

  consym = (SymbolP)0;
  abssym = (SymbolP)0;

  /* Loop through each right hand side symbol */
  while (mappedrhslist != NULLSymbolPList ||
         absrhslist != NULLSymbolPList) {

    /* If we need to get another concrete symbol (consym==0) and we     */
    /* haven't yet exhausted the list, get another one.                 */
    if (!consym && mappedrhslist != NULLSymbolPList) {
      consym = HeadSymbolPList(mappedrhslist);
      conclass = SymbolClassGet(consym);

      /* If the concrete symbol is not an IDENTIFIER or TEXT, then it   */
      /* has a modifier attached to it.  In this case, we simply want   */
      /* to add it to the rhs and continue.  We set consym to 0 to      */
      /* indicate that we need to get the next symbol.                  */
      if (conclass != IDENTIFIER && conclass != TEXT) {
        if (!RuleMapped)
          rhs = PTGSpcSeq(rhs, GenRHSSymbol(consym, key, pgram));
        mappedrhslist = TailSymbolPList(mappedrhslist);
        consym = (SymbolP)0;
        continue;
      }
      conkey = SymbolKeyGet(consym);
    }

    /* We do the same for the abstract symbols */
    if (!abssym && absrhslist != NULLSymbolPList) {
      abssym = HeadSymbolPList(absrhslist);
      absclass = SymbolClassGet(abssym);

      /* If the abstract symbol is preceded by a '$', we just want to   */
      /* insert a NULL node, because this part of the tree will be      */
      /* computed in the attribute grammar specification.  After        */
      /* inserting the NULL node, we must proceed to the next symbol.   */
      if (absclass == GEN_IDENT) {
        action = PTGCommaSeq(action, PTGNullNode());
        absrhslist = TailSymbolPList(absrhslist);
        abssym = (SymbolP)0;
        continue;
      }
      abskey = SymbolKeyGet(abssym);
    }

    ++argcount;

    /* If we are generating an action for an abstract rule that is      */
    /* being included in the concrete syntax or we don't have a matching*/
    /* abstract rule, the arguments for the tree construction function  */
    /* just come from the stack.                                        */
    if (isabs || !abssym) {

      if (!RuleMapped) {
        if (isabs)
          rhs = PTGSpcSeq(rhs, GenRHSSymbol(abssym, key, pgram));
        else
          rhs = PTGSpcSeq(rhs, GenRHSSymbol(consym, key, pgram));
      }

      /* We want to ignore TEXT symbols */
      if ((isabs && absclass == IDENTIFIER) ||
          (!isabs && conclass == IDENTIFIER)) {
        if (isabs)
          tmpkey = abskey;
        else
          tmpkey = conkey;
        if (GetNonTerm(tmpkey, 0)) ++ntcount;
        action = PTGCommaSeq(action, ActionStackArray(pos - 1));
        AdvancePosition(&pos, &order);
      }

    /* In this case, we do have a matching abstract rule, but we want   */
    /* to ignore literal symbols.                                       */
    } else if (absclass != TEXT) {

      /* If the concrete and abstract identifiers are identical */
      if (GetMap(conkey, conkey) == abskey) {

        if (!RuleMapped)
          rhs = PTGSpcSeq(rhs, GenRHSSymbol(consym, key, pgram));

        if (GetNonTerm(conkey, 0)) ++ntcount;
        action = PTGCommaSeq(action, ActionStackArray(pos - 1));
        AdvancePosition(&pos, &order);

      /* Otherwise, a coercion must be defined between the two symbols */
      } else {

        seq = OilCoerce(GetOilType(conkey, OilErrorType()),
                        GetOilType(abskey, OilErrorType()));

        if (GetSibling(abskey, 0) && BottomUpConstraint(seq) && !RuleMapped) {

          int AddToStack = 0;
          PTGNode BottomUpName;

          ++ntcount;
          BottomUpName = PTGAsIs(StringTable(GenerateName("BU")));
          rhs = PTGSpcSeq(rhs, BottomUpName);

          /* The part of the action for the current rule is simple - just  */
          /* get an element from the stack.  This is because the chain     */
          /* rule that is about to be created will put the correct node on */
          /* the stack.                                                    */
          action = PTGCommaSeq(action, ActionStackArray(pos - 1));

          /* We have to advance the position and treat it as a nonterminal */
          /* so that subsequent action arguments will pull the right       */
          /* elements from the node stack.                                 */
          ++pos;

          /* Construct the part of the action for the new chain rule to   */
          /* handle the first coercion.                                   */
          if (conclass == TEXT) {
            tmp = PTGNestActionArg(
                    PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                    PTGCoordStack(PTGPos(1)));
            seq = OilTailCS(seq);
            AddToStack = 1;
          } else {
            if (GetNonTerm(conkey, 0)) {
              tmp = PTGActionArg(PTGPos(1));
            } else {
              tmp = PTGNestActionArg(
                      PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                      PTGCommaSeq(
                        PTGCoordStack(PTGPos(1)),
                        PTGTermAction(
                          PTGAsIs(StrStr(GetMap(conkey, conkey))),
                          PTGPos(1))));
              seq = OilTailCS(seq);
              AddToStack = 1;
            }
          }

          /* Loop through and apply the remaining coercions. */
          while (!OilEmptyCS(seq)) {
            tmp = PTGNestActionArg(
                    PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                    PTGCommaSeq(
                      PTGCoordStack(PTGPos(1)),
                      tmp));
            seq = OilTailCS(seq);
          }

          if (AddToStack)
            tmp = PTGAction(PTGIncStackPtr(), tmp);
          else
            tmp = PTGAction(PTGNULL, tmp);

          /* Add the chain rule to the output parameter added */
          tmp = PTGSpcSeq(PTGAsIs(StrStr(conkey)), tmp);
          *added = PTGSeq(*added, PTGConRule(BottomUpName, tmp));

        /* The coercion sequence had no bottomup constraints. */
        } else {

          if (!RuleMapped)
            rhs = PTGSpcSeq(rhs, PTGAsIs(StrStr(conkey)));

          /* If the concrete symbol is a literal symbol, we have to     */
          /* insert a node construction, because we have nothing to get */
          /* from the stack for a literal symbol.                       */
          if (conclass == TEXT) {
            tmp = PTGNestActionArg(
                    PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                    PTGCoordStack(PTGPos(argcount)));

          /* Otherwise, the argument can come from the stack and the     */
          /* sequence of chain productions can be constructed implicitly */
          /* by the tree construction function for the parent node.      */
          } else {
            if (GetNonTerm(conkey, 0)) {
              ++ntcount;
              tmp = ActionStackArray(pos - 1);
            } else {
              /* For terminals, we must insert the bottom-most coercion */
              /* production, because we can't build implicitly from     */
              /* terminals.                                             */
              tmp = PTGNestActionArg(
                      PTGAsIs(StrStr(OilOpName(OilHeadCS(seq)))),
                      PTGCommaSeq(
                        PTGCoordStack(PTGPos(argcount)),
                        ActionStackArray(pos - 1)));
            }
            AdvancePosition(&pos, &order);
          }
          action = PTGCommaSeq(action, tmp);
        }
      }  
    } else {
      if (!RuleMapped)
        rhs = PTGSpcSeq(rhs, PTGAsIs(StrStr(conkey)));
    }

    /* Advance the concrete and abstract symbol lists and reset consym  */
    /* and abssym to 0 so that a new symbol will be fetched on the next */
    /* iteration.                                                       */
    if (mappedrhslist != NULLSymbolPList) {
      mappedrhslist = TailSymbolPList(mappedrhslist);
      consym = (SymbolP)0;
    }
    if (absrhslist != NULLSymbolPList) {
      absrhslist = TailSymbolPList(absrhslist);
      abssym = (SymbolP)0;
    }
  }

  action = PTGCommaSeq(PTGCurPos(), action);

  /* If there was no rhs nonterminal, then the node stack must be       */
  /* incremented before the new node is built.                          */
  if (ntcount == 0)
    action = PTGAction(PTGIncStackPtr(), PTGNestActionArg(RuleName, action));
  else if (ntcount == 1)
    action = PTGAction(PTGNULL, PTGNestActionArg(RuleName, action));

  /* If there was more than one rhs nonterminal, then the node stack    */
  /* index must be decremented before the new node is built.            */
  else
    action = PTGAction(PTGDecStackPtr(PTGPos(ntcount)),
               PTGNestActionArg(RuleName, action));

  return PTGSpcSeq(rhs, action);
}


#ifdef PROTO_OK
PTGNode
GenConProd (DefTableKey key, int isabs, int pgram)
#else
PTGNode
GenConProd (key, isabs, pgram)
DefTableKey key;
int isabs;
int pgram;
#endif
/* Generate a concrete grammar rule
 * On Entry:
 *   key - a rule key
 *   isabs - If 0, then key is a concrete rule key, otherwise it is an
 *              abstract rule key
 *   pgram - 1 if we are generating this for the parsing grammar,
 *              0 if we are generating it for the concrete syntax
 * On Exit:
 *   If key is a concrete rule, a rule is generated for the concrete syntax.
 *   If key is an abstract rule:
 *     It has a corresponding concrete rule or is not reachable from the
 *     root without passing through $ symbols
 *       nothing is done
 *     It is an unmatched LISTOF
 *       a series of left recursive concrete rules are generated to match it
 *     Otherwise
 *       it is placed in the concrete syntax
 *   If pgram is set, then the rule is being generated for the parsing grammar
 *   and an appropriate semantic action must be generated as well.
 ***/
{
  int IsRHS;
  DefTableKey absrulekey, lhskey;
  PTGNode RuleName, result, lhs;
  DefTableKeyList conrules;
  PTGNode BottomUpChains;

  if (GetType(key, T_NONLISTOF) == T_LISTOF && GetReach(key,0))
    return GenLISTOF(key, pgram);
  
  if (isabs && GetArgCount(key, 0) == 1)
    return GenChain(key, pgram);
  

  /* If it is an abstract rule which has a concrete counterpart or is   */
  /* not reachable from the root without passing through $ symbols,     */
  /* then don't add it to the concrete syntax.                          */
  if (isabs &&
        ((GetAbsMatch(key, NULLDefTableKeyList) != NULLDefTableKeyList) ||
         (!GetReach(key, 0))))
    return PTGNULL;

  /* Otherwise, it is a rule to be placed in the concrete syntax */
  
  /* We will need to compare the corresponding abstract rule to this    */
  /* concrete rule to get the parsing actions right.  If this is an     */
  /* abstract rule to be included, then treat it like a concrete        */
  /* rule except that the RuleName has to be obtained differently.      */
  /* The RuleName contributes to the name of the tree building          */
  /* action.                                                            */
  if (isabs) {
    absrulekey = NoKey;
    RuleName = PTGAsIs(StrStr(key));
  } else {
    absrulekey = GetMatch(key, NoKey);
    if (absrulekey == NoKey)
      RuleName = PTGAsIs(StrStr(GetDuplicate(key, NoKey)));
    else
      RuleName = PTGAsIs(StrStr(absrulekey));
  }

  result = GenConRHS(key, pgram, isabs, absrulekey, RuleName, &BottomUpChains);
  

  /* Prefix the lhs if necessary */
  lhskey = GetLHS(key, NoKey);
  lhs = PTGAsIs(StrStr(lhskey));

  if (pgram && GetRecursive(lhskey, 0)) {
    result = PTGConRule(PTGListGenSym(lhs), result);

    /* If this was a recursively defined LISTOF, then construct the     */
    /* chain rule at the root of the LISTOF.  Note that this is only    */
    /* done for the parsing grammar.                                    */
    if (!GetListChainDone(lhskey, 0)) {
      result = PTGSeq(
                 result,
                 PTGConRule(
                   lhs,
                   PTGSpcSeq(
                     PTGListGenSym(lhs),
                     PTGAction(
                       PTGNULL,
                       PTGNestActionArg(
                         RuleName,
                         PTGCommaSeq(
                           PTGCurPos(),          
                           PTGActionArg(PTGPos(1))))))));
      ResetListChainDone(lhskey, 1);
    }
  } else
    result = PTGConRule(lhs, result);

  /* Add the chain rules required for correct bottomup processing */
  return PTGSeq(result, BottomUpChains);
}


#ifdef PROTO_OK
PTGNode
GenAbsProd (DefTableKey key, int iscon)
#else
PTGNode
GenAbsProd (key, iscon)
DefTableKey key;
int iscon;
#endif
/* Generate an abstract grammar rule
 * On Entry:
 *   key - a rule key
 *   iscon - 0 if key is a concrete rule key; 1 if key is an abstract rule key
 * On Exit:
 *   If key is an abstract rule, then return a PTGNODE representing the rule.
 *   If key is a concrete rule that has no match in the abstract grammar and
 *   isn't a trivial chain production, then return a PTGNODE representing the
 *   rule.  Otherwise return PTGNULL.
 ***/
{
  SymbolPList rhslist;
  DefTableKey dupkey, lhs, elt;
  PTGNode rhs;

  if (iscon) {
    /* We need to get the key which represents all of the symbolically  */
    /* equivalent concrete rules.  If there is no such key, then this   */
    /* rule does not belong in the abstract grammar.                    */
    dupkey = GetDuplicate(key, NoKey);
    if (dupkey == NoKey || GetAbsDone(dupkey, 0) == 1)
      return PTGNULL;
    ResetAbsDone(dupkey, 1);
  }

  rhslist = GetRHS(key, NULLSymbolPList);

  /* If it's a LISTOF production then put it in the abstract grammar */
  if (GetType(key, T_NONLISTOF) == T_LISTOF) {
    elt = SymbolKeyGet(HeadSymbolPList(rhslist));
    rhs = PTGAsIs(StrStr(elt));
    rhslist = TailSymbolPList(rhslist);
    while (rhslist != NULLSymbolPList) {
      elt = SymbolKeyGet(HeadSymbolPList(rhslist));
      rhs = PTGAltSeq(rhs, PTGAsIs(StrStr(elt)));
      rhslist = TailSymbolPList(rhslist);
    }

  /* Otherwise, treat it as a normal rule and put it in the grammar */
  } else {
    rhs = PTGNULL;
    while (rhslist != NULLSymbolPList) {
      elt = SymbolKeyGet(HeadSymbolPList(rhslist));
      switch (SymbolClassGet(HeadSymbolPList(rhslist))) {
        case GEN_IDENT:
          rhs = PTGSpcSeq(rhs, PTGGenIdent(PTGAsIs(StrStr(elt))));
          break;
        case IDENTIFIER:
          rhs = PTGSpcSeq(rhs,
                        PTGAsIs(StrStr((iscon ? GetMap(elt, elt) : elt))));
          break;
        case TEXT:
          rhs = PTGSpcSeq(rhs, PTGAsIs(StrStr(elt)));
      }
      rhslist = TailSymbolPList(rhslist);
    }
  }

  if (GetType(key, T_NONLISTOF) == T_LISTOF)
    return PTGAbsList(PTGAsIs(StrStr(key)),
                        PTGAsIs(StrStr(GetLHS(key, NoKey))), rhs);
  else if (iscon) {
    lhs = GetLHS(key, NoKey);
    return PTGAbsRule(PTGAsIs(StrStr(dupkey)),
                        PTGAsIs(StrStr(GetMap(lhs, lhs))), rhs);
  } else
    return PTGAbsRule(PTGAsIs(StrStr(key)),
                        PTGAsIs(StrStr(GetLHS(key, NoKey))), rhs);
}


/* On Entry:
 *   f - a valid file pointer
 *   i - a number
 * On Exit:
 *   The value of (i-1) will be printed on f.
 */
#ifdef PROTO_OK
void
PrDecInt (FILE *f, int i)
#else
void
PrDecInt (f, i)
FILE *f;
int i;
#endif
{
  fprintf(f, "%d", i-1);
  return;
}

