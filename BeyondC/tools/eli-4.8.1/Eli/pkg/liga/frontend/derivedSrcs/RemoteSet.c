
#include "RemoteSet.h"
#include "pdl_gen.h"
#include "csm.h"

extern Environment RootEnv; /* exported by AlgScope.h */

void UnsetRemoteAttr ()
/* on exit: RemoteAttr is set to NoBinding for all symbols */
{
  Binding b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0)) 
      ResetRemoteAttr (k, NoStrIndex); 
    b = NextDefinition (b);
  }
}/* UnsetRemoteAttr */

#if defined(__cplusplus) || defined(__STDC__)
int MarkInhTreeSymbAttrs (Binding sym, int attr)
#else
int MarkInhTreeSymbAttrs (sym, attr) Binding sym; int attr;
#endif
/* on entry:
    inheritance relations are set between symbol scopes
   on exit:
    all tree symbols that inherit from sym are marked with the
    RemoteAttr attr.
    0 is returned if another attribute is to be associated
    to the same symbol.
*/
{ Environment symenv;
  Binding b;
  int res = 1;
  if (sym == NoBinding) return res;

  symenv = GetUpperScope (KeyOf (sym), NoEnv);

  b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b);
    if (GetIsSymbol (k, 0) && GetIsTreeSym (k, 0))
    { Environment toEnv = GetUpperScope (k, NoEnv);
      if (Inheritsfrom (toEnv, symenv))
      {  int a = GetRemoteAttr (k, NoStrIndex);
         if (k != KeyOf(sym) && GetIsTerm (k, 0))
            return -1; /* a terminal inherits from sym */
         if (a != 0 && a != attr) 
            res = 0;   /* a different remote attr has been set for this symbol */
         ResetRemoteAttr (k, attr);
      }
    }
    b = NextDefinition (b);
  }
  return res;
}/* MarkInhTreeSymbAttrs */

SymbAttrList MakeRemoteSet ()
/* a list of pairs (symbol binding, attr binding) is build; 
   it contains every symbol that is marked;
*/
{ SymbAttrList res = NULLSymbAttrList;
  Binding b = DefinitionsOf (RootEnv);
  while (b != NoBinding)
  { DefTableKey k = KeyOf (b); int ra;
    if (GetIsSymbol (k, 0) && GetIsTreeSym (k, 0) &&
        (ra = GetRemoteAttr (k, NoStrIndex)) != NoStrIndex)
    { ResetRemoteAttr (k, NoStrIndex);
      res = ConsSymbAttrList (MakeSymbAttr (b, ra), res);
    }
    b = NextDefinition (b);
  }
  return res;
}/* MakeRemoteSet */
