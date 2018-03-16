
#include "RemoteOut.h"
#include "SymbolOutput.h"
#include "Remote.h"
#include "pdl_gen.h"
#include "csm.h"

#if defined(__cplusplus) || defined(__STDC__)
PTGNode SymbAttrsOutput (SymbAttrList sal)
#else
PTGNode SymbAttrsOutput (sal) SymbAttrList sal;
#endif
{ PTGNode res = PTGNULL;
  while ( sal != NULLSymbAttrList)
  { SymbAttr sa = HeadSymbAttrList (sal);
    res = PTGCommaSeq 
            (res,
             PTGSymbAttr 
               (StringTable (IdnOf (SymbolBindOf (sa))),
                StringTable (AttrOf (sa))));
    sal = TailSymbAttrList (sal);
  }
  return res;
}/* SymbAttrsOutput */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode LinesOutput (DefTableKeyList dkl)
#else
PTGNode LinesOutput (dkl) DefTableKeyList dkl;
#endif
{ PTGNode res = PTGNULL;
  while (dkl != NULLDefTableKeyList)
  { 
    res = PTGCommaSeq 
           (res, 
            OutCoord (HeadDefTableKeyList (dkl)));
    dkl = TailDefTableKeyList (dkl);
  }
  return res;
}/* LinesOutput */


#if defined(__cplusplus) || defined(__STDC__)
PTGNode InclOutput (DefTableKey k)
#else
PTGNode InclOutput (k) DefTableKey k;
#endif
{  PTGNode valvoid = 
      GetInValueContext (k, 0) ? PTGAsIs ("value ") : PTGNULL;
   if (GetInVoidContext (k, 0)) 
      valvoid = PTGSeq (valvoid, PTGAsIs ("void"));
   return PTGIncludingInfo 
     (SymbAttrsOutput (GetRemoteSet (k, NULLSymbAttrList)),
      valvoid);
}/* InclOutput */


#if defined(__cplusplus) || defined(__STDC__)
PTGNode ShieldSetOutput (DefTableKeyList dkl)
#else
PTGNode ShieldSetOutput (dkl) DefTableKeyList dkl;
#endif
{ PTGNode res = PTGNULL;
  if (dkl == NULLDefTableKeyList)
    return PTGNULL;

  while (dkl != NULLDefTableKeyList)
  { DefTableKey hd = HeadDefTableKeyList (dkl);
    if (hd != NoKey)
     res = PTGCommaSeq
      (res, 
       PTGAsIs 
         (StringTable (GetNameSym (HeadDefTableKeyList (dkl), 0))));
    dkl = TailDefTableKeyList (dkl);
  }
  return PTGShieldInfo (res);
}/* ShieldSetOutput */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode ConstitOutput (DefTableKey k)
#else
PTGNode ConstitOutput (k) DefTableKey k;
#endif
{  PTGNode valvoid = 
      GetInValueContext (k, 0) ? PTGAsIs ("value ") : PTGNULL;

   if (GetInVoidContext (k, 0)) 
      valvoid = PTGSeq (valvoid, PTGAsIs ("void"));
   return PTGConstitInfo 
     (SymbAttrsOutput (GetRemoteSet (k, NULLSymbAttrList)),
      ShieldSetOutput (GetShieldSet (k, NULLDefTableKeyList)),
      valvoid);
}/* ConstitOutput */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode WithOutput (DefTableKey k)
#else
PTGNode WithOutput (k) DefTableKey k;
#endif
{ DefTableKey tp = GetType (k, NoKey);
  if (tp == NoKey) return PTGNULL;

  return PTGWithInfo
    (StringTable (GetNameSym (tp, 0)), 
     StringTable (GetFunct2 (k, 0)),
     StringTable (GetFunct1 (k, 0)),
     StringTable (GetFunct0 (k, 0)));
}/* WithOutput */

#if defined(__cplusplus) || defined(__STDC__)
PTGNode ConstitsOutput (DefTableKey k)
#else
PTGNode ConstitsOutput (k) DefTableKey k;
#endif
{  PTGNode valvoid = 
      GetInValueContext (k, 0) ? PTGAsIs ("value ") : PTGNULL;

   if (GetInVoidContext (k, 0)) 
      valvoid = PTGSeq (valvoid, PTGAsIs ("void"));

   return PTGConstitsInfo 
     (SymbAttrsOutput (GetRemoteSet (k, NULLSymbAttrList)),
      ShieldSetOutput (GetShieldSet (k, NULLDefTableKeyList)),
      WithOutput (k),
      valvoid);
}/* ConstitsOutput */


PTGNode RemoteOutput ()
{ DefTableKeyList reml; DefTableKey k;
  PTGNode incls = PTGNULL, constitss = PTGNULL, constits = PTGNULL;

  reml = IncludingKeys;
  while (reml != NULLDefTableKeyList)
  { k = HeadDefTableKeyList (reml);
    incls = PTGSeq (incls, 
      PTGWithOccurrences
        (InclOutput (k),
         LinesOutput (GetInComputations (k, NULLDefTableKeyList))));
    reml = TailDefTableKeyList (reml);
  }

  reml = ConstituentKeys;
  while (reml != NULLDefTableKeyList)
  { k = HeadDefTableKeyList (reml);
    constits = PTGSeq (constits, 
      PTGWithOccurrences
        (ConstitOutput (k),
         LinesOutput (GetInComputations (k, NULLDefTableKeyList))));
    reml = TailDefTableKeyList (reml);
  }

  reml = ConstituentsKeys;
  while (reml != NULLDefTableKeyList)
  { k = HeadDefTableKeyList (reml);
    constitss = PTGSeq (constitss, 
      PTGWithOccurrences
        (ConstitsOutput (k),
         LinesOutput (GetInComputations (k, NULLDefTableKeyList))));
    reml = TailDefTableKeyList (reml);
  }

  return PTGRemoteInfo (incls, constits, constitss);
}/* RemoteOutput */
