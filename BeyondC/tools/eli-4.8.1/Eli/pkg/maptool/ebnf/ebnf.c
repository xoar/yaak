
#include "ebnf.h"
#include "ptg_gen.h"

PTGNodeList
#ifdef PROTO_OK
Concatenate(PTGNodeList left, PTGNodeList right)
#else
Concatenate(left, right) PTGNodeList left, right;
#endif

/* Create the ordered pairs of elements from two lists
 *   On entry-
 *     left=[l1, l2, ..., lm]
 *     right=[r1, r2, ..., rn]
 *   On exit-
 *     Concatenate=[l1 r1, l1 r2, ..., l2 r1, ..., lm rn]
 ***/
{ PTGNodeList l, r, result = NULLPTGNodeList;

  for (l = left; l != NULLPTGNodeList; l = TailPTGNodeList(l))
    for (r = right; r != NULLPTGNodeList; r = TailPTGNodeList(r))
      result=
        ConsPTGNodeList(PTGSpSeq(HeadPTGNodeList(l),HeadPTGNodeList(r)),result);

  return result;
}


PTGNode
#ifdef PROTO_OK
Combine(PTGNode out, PTGNode lhs, PTGNodeList rhs)
#else
Combine(out, lhs, rhs) PTGNode out, lhs; PTGNodeList rhs;
#endif

/* Build a collection of rules
 *   On entry-
 *     out=rules previously constructed
 *     lhs=common left hand side for the collection
 *     rhs=non-empty collection of right-hand sides
 *   On exit-
 *     Combine=all rules constructed so far
 ***/
{ do {
    out = PTGRule(out, lhs, HeadPTGNodeList(rhs));
    rhs = TailPTGNodeList(rhs);
  } while (rhs != NULLPTGNodeList);

  return out;
}

