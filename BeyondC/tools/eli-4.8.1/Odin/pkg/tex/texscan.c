
#include <stdio.h>
#include <stdlib.h>

#if defined(__cplusplus) || defined(__STDC__) || defined(__ANSI__) || \
    defined(__GNUC__) || defined(__STRICT_ANSI__)
#define T(t) t
#define D(t,n)
#else
#define T(t)
#define D(t,n) t n;
#endif

void
PassChr(T(char *) argument) D(char *, argument)
{ 
  int c, t = getchar();
  
  while ((c = getchar()) != t)
    if (c == EOF || c == '\n' || c == '\r') exit(0);
   }

void
PassStr(T(char *) argument) D(char *, argument)
{ 
  char *p = argument;
  int c;
  
  while (*p) {
    if ((c = getchar()) != *p) p = argument;
    if (c == EOF) exit(0);
    if (c == *p) p++;
  }
   }

void
OutNames(T(char *) argument) D(char *, argument)
{ 
  for (;;) {
    char *p = argument;
    int n = 0, c = getchar();
    while (c != '}' && c != ',') {
      if (c == EOF) exit(0);
      if (c == *p) p++; else p = argument;
      putchar(c); c = getchar(); n++;
    }
    if (n && *p != '\0') puts(argument);
    if (c == '}') return;
  }
   }


struct {
  char *repr;
  int common;
  void (*routine)(T(char *));
  char *argument;
} Commands[] = {
  { "begin{verbatim*}",   0,  PassStr,  "\\end{verbatim*}" },
  { "begin{verbatim}",    14, PassStr,  "\\end{verbatim}" },
  { "bibliographystyle{", 1,  OutNames, ".bst" },
  { "bibliography{",      12, OutNames, ".bib" },
  { "documentclass{",     0,  OutNames, ".cls" },
  { "include{",           0,  OutNames, ".tex" },
  { "input{",             2,  OutNames, ".tex" },
  { "usepackage{",        0,  OutNames, ".sty" },
  { "verb*",              0,  PassChr,  "" },
  { "verb",               4,  PassChr,  "" },
  { 0,                    0,  0,        0 }
};


int
main(T(void))
{ 
  for (;;) {
    int c = getchar();
  
    if (c == '\\') {
      
      int i, n = 0;
      c = getchar();
      for (i = 0; Commands[i].repr; i++) {
        char *p;
        if (n > Commands[i].common) break;
        if (n < Commands[i].common) continue;
        for (p = Commands[i].repr + n; *p; p++) {
          if (*p == '{') {    /* Stuff allowed between command and argument */
            while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
              c = getchar();
            if (c == '[') {
              while (c != ']') c = getchar();
              c = getchar();
            }
          }
          if (*p != c) break;
          c = getchar(); n++;
        }
        if (*p == '\0') {
          (void)ungetc(c, stdin); Commands[i].routine(Commands[i].argument);
          break;
        }
      }
      
    } else if (c == '%') {
      while ((c = getchar()) != '\n' && c != '\r') if (c == EOF) return 0;
      if (c == '\r') { if ((c = getchar()) != '\n') ungetc(c, stdin); }
    } else if (c == EOF) return 0;
  }
   }
