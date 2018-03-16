
#ifndef PROD_H
#define PROD_H

#include "args.h"
#include "deftbl.h"
#include "envmod.h"
#include "err.h"

#define IsProdLiteral   0
#define IsProdSymbol    1
#define IsProdGenSymbol 2

typedef struct
{ int    kind;                /* one of the above kinds */
  union 
   { struct
     { DefTableKey symbolkey; /* nonterm or non-literal term */
       int symbolpos;         
         /* i-th nonterm in production counted from 0, or
            i-th terminal in production counted from 1 
         */
       Environment scope;     /* the scope of the symbol occurrence */
       CoordPtr coord;
     } s;
     int         literal;     /* StringTable index of literal */
   } u;
} _PElem, *ProdSymbol;

#define NoProdSymbol ((ProdSymbol)0)
#define PosOfProdSymbol(sy) ((sy) == NoProdSymbol ? 0 : (sy)->u.s.symbolpos)
#define GetSymbolOccScope(sy) ((sy) == NoProdSymbol ? NoEnv : (sy)->u.s.scope)

extern void *ProdSpace;

extern ProdSymbol MakeProdSymbol 
  FEARGS ((DefTableKey key, int isgen, CoordPtr coord));
extern ProdSymbol MakeProdLiteral FEARGS ((int lit));

#endif
