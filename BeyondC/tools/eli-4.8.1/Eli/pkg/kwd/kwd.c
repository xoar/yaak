static char RCSid[] = "$Id: kwd.c,v 1.7 2013/11/12 15:49:03 pfahler Exp $";
/* Keyword recognizer */
/* Copyright 1992, The Regents of the University of Colorado */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <stdio.h>
#include <stdlib.h>

#if defined(__STDC__) || defined(__cplusplus)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#endif

#include "source.h"
#include "match.h"

void
#if defined(__STDC__) || defined(__cplusplus)
ParseCommandLine(int argc, char *argv[])
#else
ParseCommandLine(argc,argv)
int argc; char *argv[];
#endif
{
   if (argc == 1) initBuf("stdin", 0);
   else if (argc > 2) {
      (void)fprintf(stderr, "Usage: %s [file]\n", argv[0]);
      exit(1);
   } else {
      int infile = open(argv[1], 0);
      if (infile != -1) initBuf(argv[1], infile);
      else {
         (void)fprintf(stderr, "%s: cannot open %s for reading\n", argv[0], argv[1]);
         exit(2);
      }
   }
}



#if defined(__STDC__) || defined(__cplusplus)
int main(int argc, char *argv[])
#else
int main(argc,argv) int argc; char *argv[];
#endif
{
  char Keyword[BUFSIZ];
  FILE *delit, *str;

  if ((delit = fopen("kwd_gen.delit", "w")) == NULL) {
    (void)fprintf(stderr, "%s: cannot open kwd_gen.delit for writing\n", argv[0]);
    exit(2);
    }

  if ((str = fopen("kwd_gen.str", "w")) == NULL) {
    (void)fprintf(stderr, "%s: cannot open kwd_gen.str for writing\n", argv[0]);
    exit(2);
    }

  ParseCommandLine(argc, argv);

  while (*TEXTSTART) {
    if (*TEXTSTART != '$') while (*TEXTSTART++ != '\n') ;
    else {
      register char *p = TEXTSTART + 1;
      register char *q = Keyword;

      while ((*q = *p++) > ' ') if (*q == '\\') *q++ = *p++; else q++;
      p++; *q = '\0';
      if (match(Keyword)) {
        while (*TEXTSTART > ' ') (void)putc(*TEXTSTART++, delit);
        (void)putc('\n', delit);
        while (*p != '\n') (void)putc(*p++, str);
        p++;
        (void)fprintf(str, " %lu %s\n", (unsigned long)strlen(Keyword), Keyword);
      } else while (*p++ != '\n') ;
      TEXTSTART = p;
    }
    if (*TEXTSTART == '\0') refillBuf(TEXTSTART);
  }

  return(0);
}
