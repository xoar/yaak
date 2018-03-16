
#include <string.h>
#include "ptg_gen.h"
        
static col = 0;

void InitCol(void)
{
   col = 0;
}

void OutputLine(FILE *f, char *s)
{
   int l;
   char *nl;

   if (!s) return;

   l = strlen(s);
   nl = strrchr(s, '\n');

   if (!nl)
      col += l;
   else
      col = (l - 1 - (nl - s)); 
   fputs(s, f);
}

void CondNl(FILE *f)
{
   if (col > 65)
      OutputLine(f, "\n");
}
