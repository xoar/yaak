static char rcsid[] = {"$Id: options.c,v 1.3 2005/08/20 22:36:25 profw Exp $"};

#include "p2c.h"
#include <stdio.h>
#include "options.h"

long Options[9];

void
InitOptions()
{ FILE *f;

  Options[0] = 0;
  if ((f = fopen("Optionen", "r")) == NULL) return;
  while (!P_eoln(f)) {
    P_addset(Options, (unsigned)P_peek(f));
    getc(f);
  }
  if (!P_inset('S', Options))
    return;
  P_addset(Options, (unsigned)'A');
  P_addset(Options, (unsigned)'O');
  P_addset(Options, (unsigned)'Z');
}
