
#include "Remote.h"
#include "pdl_gen.h"
#include "csm.h"

DefTableKeyList IncludingKeys = NULLDefTableKeyList;
DefTableKeyList ConstituentKeys = NULLDefTableKeyList;
DefTableKeyList ConstituentsKeys = NULLDefTableKeyList;

static 
#if defined(__cplusplus) || defined(__STDC__)
int equalDefTableKeyLists (DefTableKeyList l1, DefTableKeyList l2)
#else
int equalDefTableKeyLists (l1, l2) DefTableKeyList l1; DefTableKeyList l2;
#endif
/* comparison is done elementwise, because the lists are ordered
   (opposite order of the symbols in RootEnv)
*/
{ 
  while (l1 != NULLDefTableKeyList && l2 != NULLDefTableKeyList)
  { DefTableKey sa1 = HeadDefTableKeyList (l1);
    DefTableKey sa2 = HeadDefTableKeyList (l2);
    if (sa1 != sa2)
       return 0;
    l1 = TailDefTableKeyList (l1);
    l2 = TailDefTableKeyList (l2);
  }
  return l1 == NULLDefTableKeyList && l2 == NULLDefTableKeyList;
}/* equalDefTableKeyLists */


static 
#if defined(__cplusplus) || defined(__STDC__)
int equalSymbAttrLists (SymbAttrList l1, SymbAttrList l2)
#else
int equalSymbAttrLists (l1, l2) SymbAttrList l1; SymbAttrList l2;
#endif
/* comparison is done elementwise, because the lists are ordered
   (opposite order of the symbols in RootEnv)
*/
{ 
  while (l1 != NULLSymbAttrList && l2 != NULLSymbAttrList)
  { SymbAttr sa1 = HeadSymbAttrList (l1);
    SymbAttr sa2 = HeadSymbAttrList (l2);
    if (SymbolBindOf(sa1) != SymbolBindOf(sa2) ||
        AttrOf(sa1) != AttrOf(sa2))
       return 0;
    l1 = TailSymbAttrList (l1);
    l2 = TailSymbAttrList (l2);
  }
  return l1 == NULLSymbAttrList && l2 == NULLSymbAttrList;
}/* equalSymbAttrLists */

#ifdef TEST
#define TEST
#include <stdio.h>
#endif

#if defined(__cplusplus) || defined(__STDC__)
DefTableKey EnterIncluding (SymbAttrList remset, DefTableKey comp, CoordPtr coord)
#else
DefTableKey EnterIncluding (remset, comp, coord) 
   SymbAttrList remset; DefTableKey comp; CoordPtr coord;
#endif
/* A new including construct is entered in the list with the
   properties as given by the parameters, if such a construct
   does not yet exist.
*/
{ DefTableKeyList l = IncludingKeys;
  DefTableKey res;
  while (l != NULLDefTableKeyList)
  { DefTableKey c = HeadDefTableKeyList (l);
    SymbAttrList rset = GetRemoteSet (c, NULLSymbAttrList);
    if (equalSymbAttrLists (rset, remset))
    {
#ifdef TEST
      printf ("INCLUDING in line %d is the same as in line %d\n",
         LineOf (*coord), LineOf (*(GetCoord (c, NoPosition))));
#endif
      ResetInComputations 
         (c, ConsDefTableKeyList 
                 (comp, GetInComputations (c, NULLDefTableKeyList)));
      return c;
    }
    l = TailDefTableKeyList (l);
  }
  res = NewKey();
  ResetIsIncluding (res, 1);
  ResetRemoteSet (res, remset);
  ResetCoord (res, coord);
  ResetInComputations (res, ConsDefTableKeyList (comp, NULLDefTableKeyList));
  IncludingKeys = ConsDefTableKeyList (res, IncludingKeys);
#ifdef TEST
      printf ("new INCLUDING in line %d\n", LineOf (*coord));
#endif
  return res;
}/* EnterIncluding */


#if defined(__cplusplus) || defined(__STDC__)
DefTableKey EnterSglConstit
    (SymbAttrList remset, DefTableKeyList shieldset, 
     DefTableKey comp, CoordPtr coord)
#else
DefTableKey EnterSglConstit 
    (remset, shieldset, comp, coord)
  SymbAttrList remset; DefTableKeyList shieldset;
  DefTableKey comp; CoordPtr coord;
#endif
/* A new constituent construct is entered in the list with the
   properties as given by the parameters, if such a construct
   does not yet exist.
*/
{ DefTableKeyList l = ConstituentKeys;
  DefTableKey res;
#ifdef TEST
      printf ("enter CONSTITUENT in line %d\n",LineOf (*coord));
#endif
  while (l != NULLDefTableKeyList)
  { DefTableKey c = HeadDefTableKeyList (l);
    SymbAttrList rset = GetRemoteSet (c, NULLSymbAttrList);
    DefTableKeyList sset = GetShieldSet (c, NULLDefTableKeyList);
    if (equalSymbAttrLists (rset, remset) && 
        equalDefTableKeyLists (sset, shieldset))
    {
#ifdef TEST
      printf ("CONSTITUENT in line %d is the same as in line %d\n",
         LineOf (*coord), LineOf (*(GetCoord (c, NoPosition))));
#endif
      ResetInComputations 
         (c, ConsDefTableKeyList 
                 (comp, GetInComputations (c, NULLDefTableKeyList)));
      return c;
    }
    l = TailDefTableKeyList (l);
  }
  res = NewKey();
  ResetIsConstituent (res, 1);
  ResetRemoteSet (res, remset);
  ResetShieldSet (res, shieldset);
  ResetCoord (res, coord);
  ResetInComputations (res, ConsDefTableKeyList (comp, NULLDefTableKeyList));
  ConstituentKeys = ConsDefTableKeyList (res, ConstituentKeys);
#ifdef TEST
      printf ("entered CONSTITUENT in line %d\n", LineOf (*coord));
#endif
  return res;
}/* EnterSglConstit */


#if defined(__cplusplus) || defined(__STDC__)
DefTableKey EnterMulConstit
   (SymbAttrList remset, DefTableKeyList shieldset, 
    DefTableKey tp, int fct2, int fct1, int fct0,
    DefTableKey comp, CoordPtr coord)
#else
DefTableKey EnterMulConstit 
     (remset, shieldset, 
      tp, fct2, fct1, fct0, comp, coord)
   SymbAttrList remset; DefTableKeyList shieldset; 
   DefTableKey tp; int fct2, int fct1, int fct0;
   DefTableKey comp; CoordPtr coord;
#endif
{ DefTableKeyList l = ConstituentsKeys;
  DefTableKey res;
#ifdef TEST
      printf ("enter CONSTITUENTS in line %d\n", LineOf (*coord));
#endif
  while (l != NULLDefTableKeyList)
  { DefTableKey c = HeadDefTableKeyList (l);
    SymbAttrList rset = GetRemoteSet (c, NULLSymbAttrList);
    DefTableKeyList sset = GetShieldSet (c, NULLDefTableKeyList);
    DefTableKey t = GetType (c, NoKey);
    int f2 = GetFunct2 (c, NoStrIndex);
    int f1 = GetFunct1 (c, NoStrIndex);
    int f0 = GetFunct0 (c, NoStrIndex);
 
    if (equalSymbAttrLists (rset, remset) && 
        equalDefTableKeyLists (sset, shieldset) &&
        t == tp && f2 == fct2 && f1 == fct1 && f0 == fct0)
    {
#ifdef TEST
      printf ("CONSTITUENTS in line %d is the same as in line %d\n",
         LineOf (*coord), LineOf (*(GetCoord (c, NoPosition))));
#endif
      ResetInComputations 
         (c, ConsDefTableKeyList 
                 (comp, GetInComputations (c, NULLDefTableKeyList)));
      return c;
    }
    l = TailDefTableKeyList (l);
  }
  res = NewKey();
  ResetIsConstituents (res, 1);
  ResetRemoteSet (res, remset);
  ResetShieldSet (res, shieldset);
  ResetType (res, tp);
  ResetFunct2 (res, fct2);
  ResetFunct1 (res, fct1);
  ResetFunct0 (res, fct0);
  ResetCoord (res, coord);
  ResetInComputations (res, ConsDefTableKeyList (comp, NULLDefTableKeyList));
  ConstituentsKeys = ConsDefTableKeyList (res, ConstituentsKeys);
#ifdef TEST
      printf ("entered CONSTITUENTS in line %d\n", LineOf (*coord));
#endif
  return res;
}/* EnterMulConstit */
