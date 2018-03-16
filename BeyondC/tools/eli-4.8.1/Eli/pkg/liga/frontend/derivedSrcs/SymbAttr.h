
#ifndef SYMBATTR_H
#define SYMBATTR_H

#include "envmod.h"
#include "args.h"

typedef struct
{ Binding symbolbind;
  int     attr;
} _SAElem, *SymbAttr;

#define NoSymbAttr ((SymbAttr)0)
#define SymbolBindOf(sa) ((sa)->symbolbind)
#define AttrOf(sa) ((sa)->attr)

extern SymbAttr MakeSymbAttr FEARGS ((Binding sym, int attr));
#endif
