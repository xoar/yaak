
static char rcsid[] =
  "$Id: KnownKey.fw,v 1.7 2007/01/29 16:46:42 profw Exp $";


#include <stdio.h>
#include "csm.h"

void
#if defined(__cplusplus) || defined(__STDC__)
StripText(FILE *f, int val)
#else
StripText(f, val) FILE *f; int val;
#endif
{ register char *p = StringTable(val) + 1;
  register char c = *p++;

  while (*p) { putc(c, f); c = *p++; }
}


#include "ptg_gen.h"
#include "KnownKey.h"

Element
#if defined(__cplusplus) || defined(__STDC__)
CreateElement (int selector, PTGNode name, PTGNode TypeName, int value)
#else
CreateElement (selector, name, TypeName, value)
int selector;
PTGNode name;
PTGNode TypeName;
int value;
#endif
{
  Element result;
  result = (Element)malloc(sizeof(struct NameElt));
  result->selector = selector;
  result->name = name;
  result->TypeName = TypeName;
  result->value = value;
  return result;
}


#include "KnownKey.h"

int
#if defined(__cplusplus) || defined(__STDC__)
CmpElements (Element x, Element y)
#else
CmpElements (x, y)
Element x, y;
#endif
{
  if (x->selector < y->selector)
    return 1;
  else if (x->selector > y->selector)
    return -1;
  else
    return 0;
}


#include "ptg_gen.h"
#include "ElementList.h"

PTGNode
#if defined(__cplusplus) || defined(__STDC__)
GenElements (ElementList list)
#else
GenElements (list)
ElementList list;
#endif
{
  Element elt;

  if (list == NULLElementList)
    return PTGNULL;
  else {
    elt = HeadElementList(list);
    return PTGSeq(
             GenElements(
               TailElementList(list)),
             PTGElement(
               elt->TypeName,
               elt->name,
               (TailElementList(list)==NULLElementList ?
                  PTGEndList() :
                  HeadElementList(TailElementList(list))->name),
               PTGNum(elt->selector),
               PTGValue(elt->value)));
  }
}

