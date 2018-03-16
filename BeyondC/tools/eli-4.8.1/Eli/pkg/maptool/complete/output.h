

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include "ptg_gen.h"
#include "deftbl.h"

extern PTGNode GenConProd ELI_ARG((DefTableKey key, int isabs, int pgram));
extern PTGNode GenAbsProd ELI_ARG((DefTableKey key, int iscon));
extern void PrDecInt ELI_ARG((FILE *f, int i));

#endif

