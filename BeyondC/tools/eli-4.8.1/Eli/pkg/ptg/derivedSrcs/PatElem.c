
#include "PatElem.h"
#include "DynSpace.h"
#include "csm.h"
#include "pdl_gen.h"

static void *dynspace = (void *)0;

static PatElem create ()
{ if (!dynspace) dynspace = InitDynSpace();
  return (PatElem) DynAlloc (dynspace, 
                             sizeof (PatElemStruct));
}

PatElem newPatElem (PatKind kd, DefTableKey k, int i)
{ PatElem p;
  if (!dynspace) dynspace = InitDynSpace();
  p = (PatElem) DynAlloc (dynspace, 
                          sizeof (PatElemStruct));
  p->kind = kd; 
  switch (p->kind)
  { case INSERT: case CALL:
      p->data.key = k;  break;
    case CSTRING: case OPTION:
      p->data.index = i; break;
    default: ;
  }
  return p;
}

int cmpPatElem (PatElem p1, PatElem p2)
{ 
  if (p1 == p2) return 0;
  if (!p1 || !p2) return 1;
  if (p1->kind != p2->kind) return 1;
  switch (p1->kind)
  { case INSERT:
      if (GetIndex (p1->data.key, 0) !=
          GetIndex (p2->data.key, 0))
         return 1;
      if (GetType (p1->data.key, multipleType) !=
          GetType (p2->data.key, multipleType))
         return 1;
      return 0;
    case CSTRING:
      return strcmp
         (StringTable(p1->data.index),
          StringTable(p2->data.index));
    case OPTION:
      return (p1->data.index == p2->data.index ? 0 : 1);
    case CALL:
      return (p1->data.key == p2->data.key ? 0 : 1);
    default:     return 1;
  }
}
