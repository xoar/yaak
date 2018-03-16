
#include "Prod.h"
#include "DynSpace.h"

void *ProdSpace = (void*)0;

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol MakeProdSymbol (DefTableKey key, int isgen, CoordPtr coord)
#else
ProdSymbol MakeProdSymbol (key, isgen, coord) 
   DefTableKey key; int isgen; CoordPtr coord;
#endif
{ ProdSymbol res;
  if (!ProdSpace) ProdSpace = InitDynSpace ();
  res = (ProdSymbol) DynAlloc (ProdSpace, sizeof (_PElem));
  res->kind = isgen ? IsProdGenSymbol : IsProdSymbol;
  res->u.s.symbolkey = key;
  res->u.s.coord = coord;
  return res;
}

#if defined(__cplusplus) || defined(__STDC__)
ProdSymbol MakeProdLiteral (int lit)
#else
ProdSymbol MakeProdLiteral (lit) int lit;
#endif
{ ProdSymbol res;
  if (!ProdSpace) ProdSpace = InitDynSpace ();
  res = (ProdSymbol) DynAlloc (ProdSpace, sizeof (_PElem));
  res->kind = IsProdLiteral;
  res->u.literal = lit;
  return res;
}
