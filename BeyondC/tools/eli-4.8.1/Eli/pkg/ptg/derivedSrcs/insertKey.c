
#include "transInsert.h"
#include "pdl_gen.h"
#include "cmpPatIndex.h"
DefTableKeyList FillInsertKeyList (DefTableKeyList orig)
{ DefTableKeyList missing = NULLDefTableKeyList, l = orig;
  int index = 1;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    int elemindex = GetIndex (insKey, index);
    while (index < elemindex)
    { DefTableKey newk = NewKey ();
      ResetType (newk, nodeType); 
      ResetIndex (newk, index++);
      ResetUsed (newk, 0);
      missing = ConsDefTableKeyList (newk, missing);
    }
    index++;
    l = TailDefTableKeyList (l);
  }
  while (missing != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (missing);
    orig = AddToOrderedSetDefTableKeyList
             (insKey, orig, cmpPatIndex);
    missing = TailDefTableKeyList (missing);
  }
  return orig;
}

PTGNode MkTypedParams (DefTableKeyList l)
{ PTGNode res = PTGNULL; int index = 1;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    res = PTGCommaSeq (res,
      PTGFormalParam 
        (GetTargetType 
           (GetType (insKey, NoKey), PTGNULL),
         index++));
    l = TailDefTableKeyList (l);
  }
  return res;
}

