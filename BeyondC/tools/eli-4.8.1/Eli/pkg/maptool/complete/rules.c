

#include "err.h"
#include "csm.h"
#include "idn.h"
#include "pdl_gen.h"
#include "oiladt2.h"
#include "obstack.h"
#include "deftbl.h"
#include "MakeName.h"
#include "map.h"
#include "symbol.h"
#include "rules.h"

/* On Entry:
 *   env - the global environment
 *   key - is a key for a rule
 * On Exit:
 *   The Str property of key has a value
 */
void
#ifdef PROTO_OK
GenRuleName (DefTableKey key)
#else
GenRuleName (key) DefTableKey key;
#endif
{ if (GetStr(key, NoStrIndex) == NoStrIndex) {
    ResetStr(key, GenerateName("rule_"));
  }
}

/* On Entry:
 *   key - a rule key
 * On Exit:
 *   QChain returns non-zero if key represents a QChain
 *   production and zero otherwise.
 *   A QChain production is defined as a rules in which the right hand
 *   side has a single nonterminal (with any number of literal symbols) and
 *   that nonterminal is symbolically equivalent to the left hand side symbol.
 */
#ifdef PROTO_OK
int
QChain (DefTableKey key)
#else
int
QChain (key)
DefTableKey key;
#endif
{
  DefTableKey lhs;
  SymbolP rhs;

  lhs = GetLHS(key, NoKey);
  rhs = GetNthNT(GetRHS(key, NULLSymbolPList), 1);
  if (GetNTCount(key, 0) == 1 &&
        GetMap(lhs, lhs) == GetMap(SymbolKeyGet(rhs), SymbolKeyGet(rhs)))
    return 1;
  else
    return 0;
}

/* On Entry:
 *   key - a rule key
 * On Exit:
 *   Trivial returns non-zero if key represents a trivial chain production
 *   and zero otherwise.
 *   A trivial chain production is defined as a rules in which the right hand
 *   side has a single nonterminal and that nonterminal is symbolically
 *   equivalent to the left hand side symbol.
 */
#ifdef PROTO_OK
int
Trivial (DefTableKey key)
#else
int
Trivial (key)
DefTableKey key;
#endif
{
  DefTableKey lhs;
  SymbolP rhs;

  lhs = GetLHS(key, NoKey);
  rhs = GetNthNT(GetRHS(key, NULLSymbolPList), 1);
  if (GetArgCount(key, 0) == 1 && GetNTCount(key, 0) == 1 &&
        GetMap(lhs, lhs) == GetMap(SymbolKeyGet(rhs), SymbolKeyGet(rhs)))
    return 1;
  else
    return 0;
}

/* A special type index representing an empty right hand side of a */
/* production and the corresponding OIL type                       */
tOilType EmptyType;

/* A special argument signature used in attribution to detect   */
/* LISTOF constructs, for which signatures are not built        */
tOilArgSig NullArgSig=((tOilArgSig)0);

/* On Exit:
 *   EmptyTypeIndex and EmptyType are initialized
 *   The global environment is returned
 */
#ifdef PROTO_OK
Environment
Initialize (void)
#else
Environment
Initialize ()
#endif
{
  DefTableKey key;
  key = NewKey();
  ResetStr(key, stostr("", 0));
  EmptyType = OilNewType(key);
  return NewEnv();
}

/* On Entry:
 *   sig - the signature built up so far (the result of OilNewArgSig
 *              represents an empty signature
 *   key - the key representing the symbol to be added to the
 *              signature
 * On Exit:
 *   The new signature is returned after appending the symbol
 *   represented by key to the signature, sig.  If an
 *   OIL type has not yet been created for the symbol to be
 *   added then such an OIL type is created.
 */
#ifdef PROTO_OK
tOilArgSig
SigAppend (tOilArgSig sig, DefTableKey key)
#else
tOilArgSig
SigAppend (sig, key)
  tOilArgSig sig;
  DefTableKey key;
#endif
{
  tOilType type;

  type = GetOilType(key, OilErrorType());
  if (type == OilErrorType()) {
    type = OilNewType(key);
    ResetOilType(key, type);
  }
  return OilAddArgSig(type, sig);
}

/* On Entry:
 *   argcount - the number of symbols on the rhs of the rule
 *   key - the key representing the rule
 *   opsig - the OIL signature of the rule
 * On Exit:
 *   The rule is entered into the OIL database.  Rules with
 *   one rhs symbol are entered as coercions and all others
 *   are entered as normal operations.  The name of the
 *   operation is the rule name and the indication is given
 *   by the lhs of the rule.
 */
#ifdef PROTO_OK
void
CreateOper (int argcount, DefTableKey prodkey, tOilArgSig opsig)
#else
void
CreateOper (argcount, prodkey, opsig)
int argcount;
DefTableKey prodkey;
tOilArgSig opsig;
#endif
{
  DefTableKey indkey;
  tOilOp op, indication;

  indkey = GetLHS(prodkey, NoKey);

  /* Create the new operation, using the name of the rule */
  op = OilNewOp(prodkey, opsig, 1);

  /* If it is a chain production, add it as a coercion */
  if (argcount == 1) OilAddCoercion(op);

  /* Get the OIL indication for this lhs */
  indication = GetOilOp(indkey, OilErrorOp());

  /* If it hasn't been created yet, create it */
  if (!OilIsValidOp(indication)) {
    indication = OilNewOp(indkey, (tOilArgSig)0, 0);
    ResetOilOp(indkey, indication);
  }
  OilAddIdentification(indication, op);
}

