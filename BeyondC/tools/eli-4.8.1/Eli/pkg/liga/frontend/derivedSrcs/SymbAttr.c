
#include "SymbAttr.h"
#include "DynSpace.h"

void *SymbAttrSpace = (void*)0;

#if defined(__cplusplus) || defined(__STDC__)
SymbAttr MakeSymbAttr (Binding sym, int attr)
#else
SymbAttr MakeSymbAttr (sym, attr) Binding sym; int attr;
#endif
{ SymbAttr res;
  if (!SymbAttrSpace) SymbAttrSpace = InitDynSpace ();
  res = (SymbAttr) DynAlloc (SymbAttrSpace, sizeof (_SAElem));
  res->symbolbind = sym;
  res->attr = attr;
  return res;
}/* MakeSymbAttr */
