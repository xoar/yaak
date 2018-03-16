
#ifndef CLASSIFY_H
#define CLASSIFY_H

#include "deftbl.h"             /* for DefTableKey */

#define FAULT           (-1)
#define UNDEF           0
#define TERMINAL        1
#define NONTERMINAL     2

#define MESSAGE1 "Terminal expected: symbol has been used as nonterminal too"
#define MESSAGE2 "Nonterminal expected: symbol has been used as terminal too"

extern  void
#if defined(__STDC__) || defined(__cplusplus)
        Classify(DefTableKey key, int class);
#else
        Classify();
#endif


#endif
