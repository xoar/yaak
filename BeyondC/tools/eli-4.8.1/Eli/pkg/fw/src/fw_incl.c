static char RCSid[] = "$Id: fw_incl.c,v 1.10 2013/11/08 21:46:14 profw Exp $";
/* Copyright, 1992-1997, The Regents of the University of Colorado */

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

#define	FALSE 0
#define	TRUE 1

#define STRLEN 500

typedef struct {
	char *whole;	/* Complete name */
	char *key;	/* Selector */
} NAMESPEC;

static NAMESPEC *p, name[STRLEN];
static char *me;

static char *
#if defined(__cplusplus) || defined(__STDC__) || defined(__ANSI__) || \
    defined(__GNUC__) || defined(__STRICT_ANSI__)
fgetl(char *s, int size, FILE *stream)
#else
fgetl(s, size, stream) char *s; int size; FILE *stream;
#endif
{ int i;

  for (i = 0; i < size-1; ) {
    int c = fgetc(stream);

    if (c == EOF) {
      if (i == 0) { s[i] = '\0'; return NULL; }
      break;
    }
    s[i++] = c;
    if (c == '\n') break;
    if (c == '\r') {
      s[i-1] = '\n';
      if ((c = fgetc(stream)) != '\n') ungetc(c, stream);
      break;
    }
  }
  s[i] = '\0';

  return s;
}


static char *Path[20];

/**/
void
InitPath(FileName)
char *FileName;
/* Initialize the directory names on the search path
 *    On entry-
 *       FileName defines a file containing n directory names, 1 per line
 *    On exit-
 *       Path[0..n-1] point to the directory names
 *       Path[n]=0
 **/
{
	char line[STRLEN];
	int n;
	FILE *names;

	if ((names = fopen(FileName, "r")) == NULL) {
		(void)fprintf(stderr, "%s: Could not open %s\n", me, FileName);
		exit(1);
	}

	n = 0;
	while (fgetl(line,STRLEN,names) != NULL) {
		int l = strlen(line);

		Path[n] = (char *)malloc((unsigned)(l));
		(void)strncpy(Path[n],line,l-1);
		(Path[n++])[l-1] = '\0';
	}
	Path[n] = NULL;
}

int	num_IgnoreS = 0;
char	IgnoreS [10] [200];

void
InitIgnore(FileName)
   char *FileName;
{
   FILE *stream;
   char *Line, LineBuf[200];

   stream = fopen(FileName, "r");
   if (stream == NULL) {
      return; }/*if*/;
   Line = fgetl(LineBuf, sizeof(LineBuf), stream);
   while (Line != NULL) {
      Line[strlen(Line)-1] = 0;
      (void)strcpy(IgnoreS[num_IgnoreS], Line);
      num_IgnoreS += 1;
      Line = fgetl(LineBuf, sizeof(LineBuf), stream); }/*while*/;
   (void) fclose(stream);
}/*InitIgnore*/

int
IsIgnore(FileName)
   char *FileName;
{
   int i;

   for (i=0; i<num_IgnoreS; i++) {
      if (strncmp(FileName, IgnoreS[i], strlen(IgnoreS[i])) == 0) {
	 return TRUE; }/*if*/; }/*for*/;
   return FALSE;
}/*IsIgnore*/

void
ExpandFileName(NewStr, OldStr)
   char *NewStr, *OldStr;
{
   int iNew, iOld, iSeg;
   char SegStr[200];

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
	       iSeg += 1; iOld += 1; }/*while*/;
	    SegStr[iSeg] = 0;
	    /*select*/{
	       if (strcmp(SegStr, "..") == 0) {
		  if (NewStr[iNew-1] != '/' || iNew <= 1) {
		     (void)fprintf(stderr, "%s: Bad filename : \"%s\"\n", me, OldStr);
		     }/*if*/;
		  iNew -= 2;
		  while (NewStr[iNew] != '/') iNew -= 1;
	       }else if (strcmp(SegStr, ".") == 0) {
		  iNew -= 1;
		  if (NewStr[iNew] != '/') {
		     (void)fprintf(stderr, "%s: Bad filename : \"%s\"\n", me, OldStr);
		     }/*if*/;
	       }else{
		  (void)strcpy(&NewStr[iNew], SegStr);
		  iNew += strlen(SegStr);
		  };}/*select*/; };}/*select*/; }/*while*/;
   NewStr[iNew] = 0;
}/*ExpandFileName*/

/**/
int
Exists(included)
char *included;
/* Check the existence of an included file
 *    On entry-
 *       included=relative file name to be checked
 *    If the file is either available or explicitly ignored then on exit-
 *       Exists=TRUE
 *       If the file was not explicitly ignored then its full path name
 *         has been written to standard output
 *    Else on exit-
 *       Exists=FALSE
 **/
{
	char FileName[STRLEN], NewFileName[STRLEN];
	int i;
	struct stat buf;

	if (*included == '/') {
		if (IsIgnore(included)) return(TRUE);
		if (stat(included,&buf) == 0) {
			puts(included);
			return(TRUE);
		}
	}

	for (i = 0; Path[i] != NULL; i++) {
		(void)strcpy(FileName,Path[i]);
		(void)strcat(FileName,"/");
		(void)strcat(FileName,included);
		ExpandFileName(NewFileName,FileName);
		if (IsIgnore(NewFileName)) return(TRUE);
		if (stat(NewFileName,&buf) == 0) {
			puts(NewFileName);
			return(TRUE);
		}
	}
	return(FALSE);
}




int	num_DefineS = 0;
char	DefineS [20] [200];


void
InitDefine(FileName)
   char *FileName;
{
   FILE *stream;
   char *Line, LineBuf[200];

   stream = fopen(FileName, "r");
   if (stream == NULL) {
      return; }/*if*/;
   Line = fgetl(LineBuf, sizeof(LineBuf), stream);
   while (Line != NULL) {
      Line[strlen(Line)-1] = 0;
      (void)strcpy(DefineS[num_DefineS], Line);
      num_DefineS += 1;
      Line = fgetl(LineBuf, sizeof(LineBuf), stream); }/*while*/;
   (void) fclose(stream);
   }/*InitDefine*/


/**/
void
InitDerived(Filename)
char *Filename;
/* Initialize the list of derived include files
 *    On entry-
 *       Filename=name of the file containing the derived include files
 *    On exit-
 *       name points to the first derived include file name
 *       p points beyond the last derived include file name
 **/
{
	char line[STRLEN];
	FILE *names;

	if ((names = fopen(Filename, "r")) == NULL) {
		(void)fprintf(stderr, "%s: Could not open %s\n", me, Filename);
		exit(1);
	}

	p = name;
	while (fgetl(line,STRLEN,names) != NULL) {
		char *q = line + strlen(line);

		do q--; while (*q <= ' ');
		*(q+1) = '\0';
		p->whole = (char *)malloc((unsigned)(q-line+2));
		(void)strcpy(p->whole,line);
		q = (p->whole) + (q-line);
		while (*q > ' ' && *q != '@') q--;
		*q = '\0'; (p++)->key = q + 1;
	}
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
	char candidate[STRLEN];
	NAMESPEC *t;

	(void)strcpy(candidate,q);
	t = name;
	while (t != p) {
		if (strcmp(candidate,t->key) == 0) break;
		t++;
	}
	if (t != p) puts(t->whole);
	return(t != p);
}

int
main(argc, argv)
   int argc;
   char **argv;
{
   char StrBuf[STRLEN], FileName[STRLEN], NewFileName[STRLEN];
   char *Str, *nl;
   char Special = '@';
   int len;

   me = argv[0];

   if (argc < 2) {
      (void)fprintf(stderr, "%s: Search path required\n", me);
      return 0;
   }

   InitPath(argv[1]);

   if (argc > 2) {
      InitDefine(argv[2]); }/*if*/;

   if (argc > 3) {
      InitIgnore(argv[3]); }/*if*/;

   if (argc > 4) {
      if (argc > 5)
         (void)fprintf(stderr, "%s: Only four arguments expected\n", me);
      InitDerived(argv[4]);
   } else {p = name; }/*if*/;

   Str = fgetl (StrBuf, STRLEN, stdin);
   while (Str != 0) {
      nl = Str + strlen (Str) - 1;
      if (feof(stdin));
      else if (*nl == '\n')
	 *nl = '\0';
      else {
	 (void) fprintf (stderr, "%s: buffer overflow, line length > %d\n",
			 me, STRLEN);
	 exit (1);
      }
      len = strlen(Str);
      if (len >= 2 && Str[0] == Special && Str[1] == 'i') {
	 if (len <= 3)
	   (void)fprintf(stderr, "%s: No include file given\n", me);
         else if (Str[2] == ' ' &&
		  (Str[3] == '/' || !IsDerived(&Str[3])) && !Exists(&Str[3])) {
	   (void)fprintf(stderr, "%s: Bad include : \"%s\"\n", me, Str);
         }
      } else {
         while ((Str = strchr(Str, Special))) {
#if defined(__cplusplus) || defined(__STDC__)
            if (strlen(Str) > 2U && Str[1] == '=') { Special = Str[2]; Str++; }
#else
            if (strlen(Str) > 2 && Str[1] == '=') { Special = Str[2]; Str++; }
#endif
            Str += 2;
         }
      }
      Str = fgetl (StrBuf, STRLEN, stdin);
   }

   return 0;
}
