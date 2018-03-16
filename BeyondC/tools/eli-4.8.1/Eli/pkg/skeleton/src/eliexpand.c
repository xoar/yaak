static char rcsid[] = "$Id: eliexpand.c,v 1.4 2004/08/01 01:44:26 profw Exp $";
/* Convert tabs into spaces
   Copyright 1994, The Regents of the University of Colorado */

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

#if defined(__STDC__) || defined(__cplusplus)
void expand_tabs(FILE *infile, FILE *outfile)
#else
void expand_tabs(infile, outfile)
FILE *infile;
FILE *outfile;
#endif
{ int c;
  int column = 0;
  
  while ((c = getc(infile)) != EOF) {
    if (c == '\t') {
      do {putc(' ', outfile); column++; } while (column % 8 != 0);
    }  else   {  
      putc(c, outfile);
      if (c != '\n' && c != '\r') column++;
      else {
        column = 0;
        if (c == '\r') {
          if ((c = getc(infile)) != '\n') ungetc(c, infile);
        }
      }
    }
  }
}

  
  

#if defined(__STDC__) || defined(__cplusplus)
int main(int argc, char **argv)
#else
int main(argc, argv)
int argc;
char **argv;
#endif
{ if (argc <= 1) expand_tabs (stdin, stdout);
  else {
    FILE *infile;
  
    if (!(infile = fopen(argv[1], "r"))) {
      fprintf (stderr, "%s: cannot open %s\n", argv[0], argv[1]);
      return 1;
    } else {
      expand_tabs (infile, stdout);
      fclose (infile);
    }
  }

  return 0;
}
