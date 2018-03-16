
#ifndef GLAFE_H
#define GLAFE_H

#include "eliproto.h"
#include "ptg_gen.h"

#define NORETURN        15001

extern void PrString ELI_ARG((PTG_OUTPUT_FILE f, CONST char *str));
extern int NoDups ELI_ARG((int x, int y));

#endif
