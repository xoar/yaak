
#include "cmpPatIndex.h"
#include "pdl_gen.h"

int cmpPatIndex (DefTableKey k1, DefTableKey k2)
{ int i1, i2;
  if (k1 == k2) return 0;
  i1 = GetIndex (k1, 0);
  i2 = GetIndex (k2, 0);
  if (i1 > i2) return 1;
  if (i1 < i2) return -1;
  return 0;
}
