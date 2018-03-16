static char rcsid[] = "$Id: ligaErr.c,v 1.3 2007/02/23 13:50:50 peter Exp $";
/* Copyright 1997, The Regents of the University of Colorado */
/* Map visitproc errors to Liga input file */
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
#include <string.h>
#include "eliproto.h"

static char curfile[BUFSIZ] = {'\0'};
static int  curline;
static FILE *visitp = NULL;

static int  newline;

void
#ifdef PROTO_OK
AdvFile(void)
#else
AdvFile()
#endif
/* Advance to the next SPC comment
 *   On entry-
 *     visitp is the stream being used
 *     curline = index of the line last read
 *   If there is another SPC comment then on exit-
 *     curline=number of the line containing the SPC comment
 *     newline=number contained in the SPC comment
 *   Else on exit-
 *     visitprocs file has been closed
 *     visitp = NULL
 *     curline=0
 *     newline=0
 ***/
{ char visitline[BUFSIZ];

  if (visitp == NULL) {
    curline = 0;
    newline = 0;
    return;
  } 

  while (fgets(visitline, BUFSIZ, visitp) != NULL) {
    curline++;
    if (strncmp(visitline, "/*SPC(", 6) == 0) {
      (void)sscanf(visitline + 6, "%d", &newline);
      return;
    }
  }

  (void)fclose(visitp);
  curline = 0;
  newline = 0;
  return;
}

void
#ifdef PROTO_OK
NewFile(char *filename)
#else
NewFile(filename) char *filename;
#endif 
/* Start a new visitprocs file
 *   On entry-
 *     filename=name of the file to be opened
 *   On exit-
 *     curfile=filename
 *   If the file is present and contains an SPC comment then on exit-
 *     curline=number of the line containing the SPC comment
 *     newline=number contained in the SPC comment
 *   Else on exit-
 *     curline=0
 *     newline=0
 ***/
{ if (visitp != NULL) (void)fclose(visitp);
  (void)strcpy(curfile, filename);
  visitp = fopen(curfile, "r");
  curline = 0;
  AdvFile();
}

int
#ifdef PROTO_OK
main(int argc, char *argv[])
#else
main(argc, argv) int argc; char *argv[];
#endif
/* Map visitproc errors to LIDO files
 *   On entry-
 *     raw error reports are on stdin
 *     argv[1]=name of the LIDO file
 *   On exit-
 *     mapped error reports have been written to stdout
 *     unmapped error reports have been written to file argv[2]
 ***/
{ char c, repfile[BUFSIZ];
  int  repline, result;
  FILE *unmapped;

  if ((unmapped = fopen(argv[2], "w")) == NULL) {
    perror("Opening unmapped output");
    exit(1);
  }

  result = scanf("%s %d", repfile, &repline);
  while (result != EOF) {
    FILE *outfile;

    if (strcmp(curfile,repfile) != 0) NewFile(repfile);
    while (curline && curline < repline) AdvFile();

    if (curline) {
      (void)printf("%s %d", argv[1], newline);
      outfile = stdout;
    } else {
      (void)fprintf(unmapped, "%s %d", repfile, repline);
      outfile = unmapped;
    }
    do { c = getchar(); putc(c, outfile); } while (c != '\n');

    result = scanf("%s %d", repfile, &repline);
  }

  return 0;
}
