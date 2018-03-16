
#ifndef ELEMENT_H
#define ELEMENT_H

#include "ptg_gen.h"


typedef struct NameElt {
  int selector;
  PTGNode name;
  PTGNode TypeName;
  int value;
} *Element;


#endif
