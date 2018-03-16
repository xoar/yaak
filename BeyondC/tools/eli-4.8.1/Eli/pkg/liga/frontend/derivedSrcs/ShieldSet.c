
#include "ShieldSet.h"
#include "pdl_gen.h"

extern Environment RootEnv; /* exported by AlgScope.h */

#if defined(__cplusplus) || defined(__STDC__)
void MarkInheritingTreeSymbs (Binding sym)
#else
void MarkInheritingTreeSymbs (sym) Binding sym;
#endif
/* on entry:
    inheritance relations are set between symbol scopes
   on exit:
    all tree symbols that inherit from sym are marked
*/
{ Environment symenv;
  Binding b;

  if (sym == NoBinding) return;

  symenv = GetUpperScope (KeyOf (sym), NoEnv);

  b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0) && GetIsTreeSym (k, 0))
    { Environment toEnv = GetUpperScope (k, NoEnv);
      if (Inheritsfrom (toEnv, symenv))
         ResetIsMarked (k, 1);
    }
    b = NextDefinition (b);
  }
}/* MarkInheritingTreeSymbs */

DefTableKeyList MakeShieldSet ()
/* a list of symbol keys is build; 
   it contains every symbol that is marked;
   the marks are unset.
   The list always contains a NoKey element;
   it distinguishes an empty shield list from an omitted one.
*/
{ DefTableKeyList res = 
    ConsDefTableKeyList (NoKey, NULLDefTableKeyList);
  Binding b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0) && GetIsMarked (k, 0))
    { ResetIsMarked (k, 0);
      res = ConsDefTableKeyList (k, res);
    }
    b = NextDefinition (b);
  }
  return res;
}/* MakeShieldSet */
