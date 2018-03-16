

#ifndef CLASSIFY_H
#define CLASSIFY_H

#include "deftbl.h"
#include "eliproto.h"

extern int CheckAxiom ELI_ARG((DefTableKey key, int type));
extern void ComputeReach ELI_ARG((DefTableKey key));
extern void MarkConSym ELI_ARG((DefTableKey key));

#endif


#define CombineSiblings(x,y)    ((y) != NoKey) ? \
                                (ResetSibling((x), 1), (y)) : (x)
#define ZeroKey()       NoKey

