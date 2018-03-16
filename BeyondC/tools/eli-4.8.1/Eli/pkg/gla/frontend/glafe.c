
#include <stdio.h>
#include <string.h>
#include "ptg_gen.h"
#include "err.h"
#include "glafe.h"

void
#if PROTO_OK
PrString (PTG_OUTPUT_FILE f, CONST char *str)
#else
PrString (f, str) PTG_OUTPUT_FILE f; char *str;
#endif
{
  if (str == (char *)0)
    fprintf(f, "(null)");
  else if (strncmp(str, "%%", 2) == 0)
    fprintf(f, "\"%%%%\"%s", &str[2]);
  else
    fprintf(f, "%s", str);
}

int
#if defined(__cplusplus) || defined(__STDC__)
NoDups (int x, int y)
#else
NoDups (x, y)
int x, y;
#endif
{
  if (x == NORETURN)
    return y;
  else if (y == NORETURN)
    return x;
  else {
    message(ERROR, "More than one Eof encoding supplied", 0, NoPosition);
    return x;
  }
}
