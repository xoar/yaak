static char RCSid[] = "$Id: get_incl.c,v 1.26 2013/11/11 03:09:41 profw Exp $";
/* Copyright, 1992, The Regents of the University of Colorado */

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

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "source.h"
#include "obstack.h"

#ifdef PATH_MAX
#define NAMESZ     PATH_MAX
#else
#define NAMESZ     1024
#endif

Obstack Storage;

typedef struct namespec {
  char *whole;	/* Complete name */
  char *key;	/* Selector */
  struct namespec *next;
} NAMESPEC;

static NAMESPEC *Derived;

typedef struct strspec {
  char *str;
  struct strspec *next;
} STRSPEC;

static STRSPEC *Paths;
static STRSPEC *Ignores;
static STRSPEC *Defines;

static int LineNumber = 1;


/**/
void
InitList(List, FileName, Error)
STRSPEC **List;
char *FileName;
int Error;
/* Initialize the directory names on the search path
 *    On entry-
 *       FileName defines a file containing n directory names, 1 per line
 *    On exit-
 *       Paths points to a linked list of the directory names
 **/
{
  int fd;
  char *line;
  STRSPEC **listptr;
  char ch;

  fd = open(FileName, 0);
  if (fd == -1) {
    if (Error) {
      (void)fprintf(stderr, ". 0 0 Could not open %s\n", FileName);
      exit(1);
    } else
      return;
  }

  initBuf(FileName, fd);
  line = TEXTSTART;

  listptr = List;

  while (*line) {
    *listptr = (STRSPEC *)obstack_alloc(&Storage, sizeof(STRSPEC));

    while ((ch = *line++) != '\n' && ch != '\r') obstack_1grow(&Storage, ch);
    if (ch == '\r' && *line == '\n') line++;

    if (!*line) {
      refillBuf(line);
      line = TEXTSTART;
    }

    obstack_1grow(&Storage, '\0');
    (*listptr)->str = (char *)obstack_finish(&Storage);
    listptr = &((*listptr)->next);
  }

  *listptr = (STRSPEC *)0;
  finlBuf();
}

void
ExpandFileName(NewStr, OldStr)
   char *NewStr, *OldStr;
{
   int iNew, iOld, iSeg;
   char SegStr[NAMESZ];

   iNew = 0; iOld = 0;
   while (OldStr[iOld] != 0) {
      /*select*/{
	 if (OldStr[iOld] == '/') {
	    NewStr[iNew] = '/';
	    iOld += 1; iNew += 1;
	 }else{
	    iSeg = 0;
	    while (OldStr[iOld] != '/' && OldStr[iOld] != 0) {
	       SegStr[iSeg] = OldStr[iOld];
	       iSeg += 1; iOld += 1; }/*while*/
	    SegStr[iSeg] = 0;
	    /*select*/{
	       if (strcmp(SegStr, "..") == 0) {
		  if (NewStr[iNew-1] != '/' || iNew <= 1) {
		     (void)fprintf(stderr, ". 0 0 Bad filename : \"%s\"\n", OldStr);
		     }/*if*/
		  iNew -= 2;
		  while (NewStr[iNew] != '/') iNew -= 1;
	       }else if (strcmp(SegStr, ".") == 0) {
		  iNew -= 1;
		  if (NewStr[iNew] != '/') {
		     (void)fprintf(stderr, ". 0 0 Bad filename : \"%s\"\n", OldStr);
		     }/*if*/
	       }else{
		  (void)strcpy(&NewStr[iNew], SegStr);
		  iNew += strlen(SegStr);
		  };}/*select*/ }}/*select*/ }/*while*/
   NewStr[iNew] = 0;
}/*ExpandFileName*/

int
IsIgnore(FileName)
   char *FileName;
{
   STRSPEC *temp;

   for (temp = Ignores; temp != (STRSPEC *)0; temp = temp->next) {
      if (strncmp(FileName, temp->str, strlen(temp->str)) == 0) {
	 return 1; }/*if*/ }/*for*/
   return 0;
}/*IsIgnore*/

/**/
int
Exists(included)
char *included;
/* Check the existence of an included file
 *    On entry-
 *       included=relative file name to be checked
 *    If the file is either available or explicitly ignored then on exit-
 *       Exists=1
 *       If the file was not explicitly ignored then its full path name
 *         has been written to standard output
 *    Else on exit-
 *       Exists=0
 **/
{
	char FileName[NAMESZ], NewFileName[NAMESZ];
	STRSPEC *temp;
	struct stat buf;

	if (*included == '/') {
		if (IsIgnore(included)) return(1);
		if (stat(included,&buf) == 0) {
			puts(included);
			return(1);
		}
	}

	for (temp = Paths; temp != (STRSPEC *)0; temp = temp->next) {
		(void)strcpy(FileName,temp->str);
		(void)strcat(FileName,"/");
		(void)strcat(FileName,included);
		ExpandFileName(NewFileName,FileName);
		if (IsIgnore(NewFileName)) return(1);
		if (stat(NewFileName,&buf) == 0) {
			puts(NewFileName);
			return(1);
		}
	}
	return(0);
}



int
IsDefine(Macro)
   char *Macro;
{
   STRSPEC *temp;

   for (temp = Defines; temp != (STRSPEC *)0; temp = temp->next) {
      if (strncmp(Macro, Defines->str, strlen(Defines->str)) == 0) {
	 return 1; }/*if*/ }/*for*/
   return 0;
   }/*IsDefine*/


void
SkipToEndIf(BufPtr)
char **BufPtr;
{
   char *Str;
   int done = 0;

   Str = *BufPtr;

   while (*Str != '\n' && *Str != '\r') Str++;
   if (*Str++ == '\r' && *Str == '\n') Str++;
   ++LineNumber;
   if (!*Str) {
     refillBuf(Str);
     Str = TEXTSTART;
   }

   while (*Str && !done) {
     if (*Str == '#') {
       ++Str;
       while (*Str == ' ') ++Str;
       if (strncmp(Str, "endif", 5) == 0)
         done = 1;
       else if (strncmp(Str, "if", 2) == 0) {
         *BufPtr = Str + 2;
	 SkipToEndIf(BufPtr);
       }
     }

     while (*Str != '\n' && *Str != '\r') Str++;
     if (*Str++ == '\r' && *Str == '\n') Str++;
     ++LineNumber;
     if (!*Str) {
       refillBuf(Str);
       Str = TEXTSTART;
     }
   }

   *BufPtr = Str;

}/*SkipToEndIf*/


/**/
void
InitDerived(Filename)
char *Filename;
/* Initialize the list of derived include files
 *    On entry-
 *       Filename=name of the file containing the derived include files
 *    On exit-
 *       Derived points to the first derived include file name
 **/
{
  int fd;
  char *line, *q, *eol;
  NAMESPEC **listptr, *p;

  fd = open(Filename, 0);
  if (fd == -1) {
      (void)fprintf(stderr, ". 0 0 Could not open %s\n", Filename);
      exit(1);
  }

  initBuf(Filename, fd);
  line = TEXTSTART;

  listptr = &Derived;

  while (*line) {
    p = *listptr = (NAMESPEC *)obstack_alloc(&Storage, sizeof(NAMESPEC));

    eol = line;
    while (*eol != '\n' && *eol != '\r') eol++;
    q = eol;
    do q--; while (*q <= ' ');

    p->whole = obstack_alloc(&Storage, (unsigned)(q-line+2));
    (void)memcpy(p->whole,line,q-line+1);
    q = (p->whole) + (q-line) + 1;
    *q = '\0'; q--;
    while (*q > ' ' && *q != '@') q--;
    *q = '\0'; p->key = q + 1;

    if (*eol++ == '\r' && *eol == '\n') eol++;
    line = eol;
    if (!*line) {
      refillBuf(line);
      line = TEXTSTART;
    }

    listptr = &(p->next);
  }

  *listptr = (NAMESPEC *)0;
  finlBuf();
}

/**/
int
IsDerived(q)
char *q;
/* Check whether an include file is derived
 *    On entry-
 *       q points to the name of the include file
 *    If the name is on the derived include file list then on exit-
 *       IsDerived=1
 *    Else on exit-
 *       IsDerived=0
 **/
{
  NAMESPEC *t;

  t = Derived;
  while (t != (NAMESPEC *)0) {
    if (strcmp(q, t->key) == 0) {
      if (!IsIgnore(t->whole)) puts(t->whole);
      return 1;
    }
    t = t->next;
  }
  return 0;
}

#if defined(__cplusplus) || defined(__STDC__)
int
main(int argc, char **argv)
#else
int
main(argc, argv)
   int argc;
   char **argv;
#endif
{
   char FileName[NAMESZ], NewFileName[NAMESZ];
   char *Str, *EndStr;
   int i, len;

   if (argc < 2) {
      (void)fprintf(stderr, ". 0 0 Search path required\n");
      return 1; }/*if*/

   obstack_init(&Storage);

   InitList(&Paths, argv[1], 1);

   if (argc > 2) {
      InitList(&Defines, argv[2], 0); }/*if*/

   if (argc > 3) {
      InitList(&Ignores, argv[3], 0); }/*if*/

   if (argc > 4) {
      if (argc > 5)
         (void)fprintf(stderr, ". 0 0 Only four arguments expected\n");
      InitDerived(argv[4]);
   }

   initBuf("stdin", 0);
   Str = TEXTSTART;
   while (*Str) {
     i = 0;
     if (Str[0] == '#') {
       ++i;
       while (Str[i] == ' ') ++i;
       if (strncmp(&Str[i], "include", 7) == 0) {
         i += 7;
	 while (Str[i] != '<' &&
                Str[i] != '"' &&
                Str[i] != '\n' &&
                Str[i] != '\r')
           ++i;
         if (Str[i] == '<') {
           ++i;
           EndStr = strchr(&Str[i], '>');
	   if (EndStr == 0) {
	     (void)fprintf(stderr, ". %d %d Bad include\n", LineNumber, i);
	   } else {
             len = EndStr - Str - i;
	     if (len == 0)
	       (void)fprintf(stderr, ". %d %d Bad include\n", LineNumber, i);
             else {
               if (Str[i] == '/') FileName[0] = '\0';
	       else (void)strcpy(FileName, "/usr/include/");
               (void)strncat(FileName, &Str[i], len);
               ExpandFileName(NewFileName, FileName);
               if (!IsIgnore(NewFileName)) puts(NewFileName);
             }
           }
         } else if (Str[i] == '"') {
           ++i;
           EndStr = strchr(&Str[i], '"');
           if (EndStr == 0) {
             (void)fprintf(stderr, ". %d %d Bad include\n", LineNumber, i);
           } else {
             len = EndStr - Str - i;
	     if (len == 0)
	       (void)fprintf(stderr, ". %d %d Bad include\n", LineNumber, i);
             else {
               (void)strncpy(NewFileName, &Str[i], len);
               NewFileName[len] = '\0';
               if ((*NewFileName == '/' || !IsDerived(NewFileName)) &&
                   !Exists(NewFileName)) {
                 /* Assume it's a system file as per cpp */
                 if (Str[i] == '/') FileName[0] = '\0';
                 else (void)strcpy(FileName, "/usr/include/");
                 (void)strcat(FileName, NewFileName);
                 ExpandFileName(NewFileName, FileName);
                 if (!IsIgnore(NewFileName)) puts(NewFileName);
               }
             }
           }
         } else {
           (void)fprintf(stderr, ". %d %d Bad include\n", LineNumber, i);
         }
         Str = Str + i;
       } else if (strncmp(&Str[i], "ifndef", 6) == 0) {
         i += 6;
         while (Str[i] == ' ') ++i;
	 Str = Str + i;
         if (IsDefine(Str)) SkipToEndIf(&Str);
       }
     }

     while (*Str != '\n' && *Str != '\r') Str++;
     if (*Str++ == '\r' && *Str == '\n') Str++;
     ++LineNumber;
     if (!*Str) {
       refillBuf(Str);
       Str = TEXTSTART;
     }
   }

   finlBuf();

   return 0;
}/*main*/
