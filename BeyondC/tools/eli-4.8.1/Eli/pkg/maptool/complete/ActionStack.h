
#ifndef ActionSTACK_H
#define ActionSTACK_H
#include "obstack.h"

extern Obstack ActionStack;

#define ActionStackEmpty \
  (obstack_next_free(&ActionStack) == obstack_base(&ActionStack))

#define ActionStackSize \
  ((PTGNode *)obstack_next_free(&ActionStack)-(PTGNode *)obstack_base(&ActionStack))

#define ActionStackTop \
  (((PTGNode *)obstack_next_free(&ActionStack))[-1])

#define ActionStackPush(v) {\
  PTGNode ActionStackTemp; ActionStackTemp = v; \
  obstack_grow(&ActionStack, &ActionStackTemp, sizeof(PTGNode)); \
}

#define ActionStackPop \
  (*((PTGNode *)(obstack_next_free(&ActionStack) -= sizeof(PTGNode))))

#define ForEachActionStackElementUp(i) \
  for ((i) = (PTGNode *)obstack_base(&ActionStack); \
       (i) < (PTGNode *)obstack_next_free(&ActionStack); \
       (i)++)

#define ForEachActionStackElementDown(i) \
  for ((i) = ((PTGNode *)obstack_next_free(&ActionStack)) - 1; \
       (i) >= (PTGNode *)obstack_base(&ActionStack); \
       (i)--)

#define ActionStackArray(i) \
  (((PTGNode *)obstack_base(&ActionStack))[i])

#define ActionStackElement(i) \
  (((PTGNode *)obstack_next_free(&ActionStack))[-1-(i)])
#endif
