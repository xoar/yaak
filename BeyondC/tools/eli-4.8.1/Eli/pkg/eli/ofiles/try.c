#include <stdio.h>
#include <stdlib.h>
#include "rdsymb.h"

static int retcode = 8;

int
main()
{ read_symbols("data.o");
  exit(retcode);
  return 0;
}

void
SymbolInfo(char *s, int ext)
{ char *p = s;

  printf("%s: %s\n", s, ext ? "external" : "entry");
  if (*p == '_') p++;
  if ((*p == 'p' || *p == 'x') &&  ext) retcode--;
  if ((*p == 'q' || *p == 'n') && !ext) retcode--;
  return;
}
