

#ifndef MATCH_H
#define MATCH_H

#include "envmod.h"
#include "deftbl.h"
#include "oiladt2.h"
#include "symbol.h"
#include "SymbolPList.h"
#include "err.h"
#include "eliproto.h"

#define obstack_strgrow(obs, dat) obstack_grow(obs, dat, strlen(dat))
#define obstack_strcpy(obs, dat) obstack_copy0(obs, dat, strlen(dat))

extern void ListofMatch ELI_ARG((DefTableKey key, POSITION *coord));
extern SymbolP NextSymbol ELI_ARG((SymbolPList *listptr));
extern void ConMatch ELI_ARG((DefTableKey, tOilSetSig, DefTableKey, CoordPtr));
extern tOilTypeSet CreateTS ELI_ARG((DefTableKey key));
extern DefTableKey Duplicates ELI_ARG((DefTableKey key));

#endif

