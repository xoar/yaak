
#include "transInsert.h"
#include "pdl_gen.h"
#include "cmpPatIndex.h"

PTGNode MkParamSpecs (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  int index = 1;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    res = PTGSeq (res,
      PTGSemicolon 
        (PTGFormalParam 
           (GetTargetType 
              (GetType (insKey, NoKey), PTGNULL),
            index++)));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkTypeList (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    res = 
      PTGCommaSeq 
        (res,
         GetTargetType (insKey, PTGNULL));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkStructFields (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    if (GetUsed (insKey, 1))
      res = 
        PTGSeq 
          (res,
           PTGSemicolon (PTGFormalParam 
             (GetTargetType 
                (GetType (insKey, NoKey), PTGNULL),
              GetIndex (insKey,0))));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkParamNames (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  int index = 1;
  while (l != NULLDefTableKeyList)
  { res = PTGCommaSeq (res, PTGIndexedName (index++));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkParamAssigns (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    if (GetUsed (insKey, 1))
       res = PTGSeq (res, 
         PTGParamAssign (GetIndex (insKey, 0)));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkOptionCondition (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    if (GethasFreeOccurrence (insKey, 0) &&
        nodeType == GetType (insKey, nodeType))
       res = PTGAnd (res, 
         PTGOptionCondition (GetIndex (insKey, 0)));
    l = TailDefTableKeyList (l);
  }
  return res;
}

PTGNode MkEmptyResultCode (DefTableKeyList l)
{ PTGNode res = PTGNULL;
  while (l != NULLDefTableKeyList)
  { DefTableKey insKey = HeadDefTableKeyList (l);
    if (GethasFreeOccurrence (insKey, 0) &&
        nodeType == GetType (insKey, nodeType))
       res = PTGAnd (res, 
         PTGIsNull (GetIndex (insKey, 0)));
    l = TailDefTableKeyList (l);
  }
  return res;
}


