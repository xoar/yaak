static char rcsid[]="$Id: rel_err.c,v 1.9 2007/02/21 15:10:00 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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
#include <string.h>

FILE *fopen();

static FILE *out;
static char OutFileName[100];
static int OutLineCount;

void
OutputReport(msg)
char *msg;
{
   if (OutLineCount == 0) {
      (void)fprintf(out, "In file %s:\n", OutFileName);
   }
   (void)fprintf(out, "	%s", msg);
   OutLineCount++;
}

void
SetOutFile(flag)
int flag;
{
}

static FILE *e;
static char ErrorMessage[BUFSIZ];

int
NextErrorLine()
{
   char ErrorLine[BUFSIZ], *p;
   int lno;

   do { if (fgets(ErrorLine, BUFSIZ, e) == NULL) return(-1); }
   while (ErrorLine[0] == '\n' || ErrorLine[0] == '\r');
   (void)sscanf(ErrorLine, "%d", &lno);
   p = (char *)strchr(ErrorLine, 'C'); (void)strcpy(ErrorMessage, p);
   return(lno);
}

int
ErrorReport(inputline,outputline)
int inputline,outputline;
{
   int lno;
   char ErrorLine[BUFSIZ];

   do {
      (void)sprintf(ErrorLine, "LINE %d %s", outputline, ErrorMessage);
      OutputReport(ErrorLine);
      lno = NextErrorLine();
   } while (inputline == lno);
   return(lno);
}

int
main(argc,argv)
int argc; char *argv[];
{
   char FileLine[BUFSIZ];
   int FileLineNumber, ErrorLineNumber, OutLineNumber, IncludeFlag;
   FILE *f;

   if (argc != 4) {
      (void)fprintf(stderr, "Usage %s errors file output\n", argv[0]);
      return 1;
   }

   if ((e = fopen(argv[1], "r")) == NULL) {
           (void)fprintf(stderr, "Could not open error file %s\n", argv[1]);
           return 1;
        }

   ErrorLineNumber = NextErrorLine();

   if ((f = fopen(argv[2], "r")) == NULL) {
           (void)fprintf(stderr, "Could not open input file %s\n", argv[2]);
           return 1;
        }

   if ((out = fopen(argv[3], "w")) == NULL) {
           (void)fprintf(stderr, "Could not open output file %s\n", argv[3]);
           return 1;
        }

   OutFileName[0] = '\0';
   OutLineCount = 0;

   FileLineNumber = 1;
   while (fgets(FileLine, BUFSIZ, f) != NULL) {
      if (FileLine[0] == '#') {
         IncludeFlag = 0;
         (void)sscanf(FileLine, "# %d \"%[^\"]\" %d",
            &OutLineNumber, OutFileName, &IncludeFlag);
         if (OutLineCount != 0) (void)fputc('\n', out);
         if (IncludeFlag != 0) {
            (void)fprintf(stderr, "# flag = %d\n", IncludeFlag);
            return 1;
         }
         OutLineCount = 0;
      } else {
         if (FileLineNumber == ErrorLineNumber) {
            ErrorLineNumber = ErrorReport(FileLineNumber, OutLineNumber);
            if (ErrorLineNumber == -1) break;
         }
         OutLineNumber++;
      }
      FileLineNumber++;
   }
}
