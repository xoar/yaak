
#ifndef KNOWNKEY_H
#define KNOWNKEY_H

#include <stdio.h>
#include "ptg_gen.h"
#include "ElementList.h"

#if defined(__cplusplus) || defined(__STDC__)
extern void StripText(FILE *f, int val);
extern Element CreateElement(int selector, PTGNode name,
                             PTGNode TypeName, int value);
extern int CmpElements(Element x, Element y);
extern PTGNode GenElements(ElementList list);
#else
extern void StripText();
extern Element CreateElement();
extern int CmpElements();
extern PTGNode GenElements();
#endif

#endif
