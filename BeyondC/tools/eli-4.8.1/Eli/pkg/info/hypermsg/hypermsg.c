static char RCSid[] = "$Id: hypermsg.c,v 1.12 1998/10/22 17:30:20 waite Exp $";
/* Copyright (c) 1991, The Regents of the University of Colorado */

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

static FILE *fd;		/* File containing errors */
static char FileName[BUFSIZ];	/* Name of the file */
static int Present;		/* Current line in the file */
static int AtEOF;		/* End-of-input flag */

void
#if defined(__cplusplus) || defined(__STDC__)
InitFile(char *name)
#else
InitFile(name) char *name;
#endif
{
   if (name == NULL || *name == '\0') {
      (void)fprintf(stderr, "hypermsg: Null error file name\n");
      exit(1);
   }
   if ((fd = fopen(name,"r")) == NULL) {
      (void)fprintf(stderr, "hypermsg: Cannot open file %s\n", name);
      exit(1);
   }
   Present = 0;
   AtEOF = 0;
}

void
#if defined(__cplusplus) || defined(__STDC__)
GetLine(int line)
#else
GetLine(line) int line;
#endif
{
   while (Present < line) {
      int c;

      if (AtEOF) {
         (void)puts("Error report beyond end-of-file");
         return;
      }
      Present++;
      if ((c = getc(fd)) == EOF) {
         if (ferror(fd)) {
            (void)perror(FileName);
            return;
         }
         AtEOF = 1;
      }
      if (Present != line) while (c != '\n' && c != EOF) c = getc(fd);
      else { 
         (void)printf("%6d |", Present);
         if (AtEOF) (void)puts("(end-of-file)");
         else
            for (;;) {
	       if (c == '@' || c == '{' || c == '}') putchar('@');
	       putchar(c);
               if (c == '\n') break;
               if ((c = getc(fd)) == EOF) { putchar('\n'); break; }
            }
      }
   }
}

void
#if defined(__cplusplus) || defined(__STDC__)
MarkColumn(int column)
#else
MarkColumn(column) int column;
#endif
{
   int s = column+7;

   if (column < 0) {
     printf("Bad column number: %d\n", column);
     return;
   }
   if (column == 0) return;
   while (s--) (void)putchar(' ');
   (void)puts("^");
}

typedef struct filenode {	/* File node description */
   char *name;			   /* name of the file */
   int node;			   /* node linkage (0 => top) */
   struct filenode *next;	   /* next node description */
} FileNode;

static FileNode *FileList	/* List of file nodes */
	= (FileNode *)NULL;

void
#if defined(__cplusplus) || defined(__STDC__)
InitNodes(char *name)
#else
InitNodes(name) char *name;
#endif
/* Set up the node descriptions for files containing reports
 *    On entry-
 *       name=name of the report file
 **/
{
   char FileName[BUFSIZ];
   int NodeNumber = 0;
   FileNode *p, *q;
   FILE *fd;

   if ((fd = fopen(name,"r")) == NULL) {
      (void)fprintf(stderr, "hypermsg: Cannot open file %s\n", name);
      exit(1);
   }

   p = FileList;
   while (fscanf(fd, "%s%*[^\n]", FileName) != EOF) {
      if (p && strcmp(FileName, p->name) == 0) continue;

      q = (FileNode *)malloc(sizeof(FileNode));
      if (p) p->next = q; else FileList = q;

      q->name = (char *)malloc((unsigned)(strlen(FileName)+1));
      (void)strcpy(q->name, FileName);
      q->node = ++NodeNumber; q->next = (FileNode *)NULL;

      p = q;
      }

   (void)fclose(fd);

   (void)puts("@menu");
   for (p = FileList; p; p = p->next) {
      (void)printf("* F%d:: ", p->node);
      if (strcmp(p->name, ".")) (void)printf("Messages for %s\n", p->name);
      else (void)printf("General messages\n");
   }
   (void)puts("@end menu");
}

void
#if defined(__cplusplus) || defined(__STDC__)
PrintNode(char *name)
#else
PrintNode(name) char *name;
#endif
/* Output a texinfo node description if necessary
 *    On entry-
 *       name=name of the file corresponding to the new node
 **/
{
   FileNode *p;

   for (p = FileList; p; p = p->next) {
      if (strcmp(name, p->name)) continue;
      (void)printf("@node F%d, ", p->node);
      if (p->next) (void)printf("F%d, ", p->node + 1);
      else (void)printf(", ");
      if (p->node == 1) (void)printf("top, top");
      else (void)printf("F%d, top", p->node - 1);

      if (strcmp(name, "."))
         (void)printf(", Edit\nMessages for %s:\n@menu\n", p->name);
      else if (FileList->next)
         (void)printf(", Edit\nGeneral messages:\n@menu\n");
      else
         (void)printf("\nGeneral messages:\n@menu\n");
   }
}

void
#if defined(__cplusplus) || defined(__STDC__)
EndNode(char *name)
#else
EndNode(name) char *name;
#endif
/* Terminate the current node
 *    On entry-
 *       name=name of the file corresponding to the current node
 **/
{
   FileNode *p;

   if (*name) {
      (void)puts("@end menu");
      if (strcmp(name,"."))
         (void)printf("@egfiles .\n%s\n@end egfiles\n", name);
      else if (FileList->next) {
         (void)printf("@egfiles .\n");
         for (p = FileList->next; p; p = p->next)
            (void)printf("%s\n", p->name);
         (void)printf("@end egfiles\n");
      }
   }
}

int
#if defined(__cplusplus) || defined(__STDC__)
main(int argc, char **argv)
#else
main(argc, argv) int argc; char **argv;
#endif
{
   char NewFile[BUFSIZ];
   int ErrorNumber, line, column;
   FILE *fd;

   if (argc != 2) {
      (void)fprintf(stderr, "Usage: %s ReportFile\n", argv[0]);
      exit(1);
   }

   InitNodes(argv[1]);

   if ((fd = fopen(argv[1],"r")) == NULL) {
      (void)fprintf(stderr, "hypermsg: Cannot open file %s\n", argv[1]);
      exit(1);
   }

   FileName[0] = '\0';

   while (fscanf(fd, "%s%d%d", NewFile, &line, &column) != EOF) {
      int c, spaces = 0;

      if (strcmp(FileName,NewFile)) {

         EndNode(FileName);

         (void)strcpy(FileName,NewFile);
         ErrorNumber = 1;

         PrintNode(FileName);
         if (strcmp(FileName,".")) InitFile(FileName);
      }

      if (strcmp(FileName,".")) {GetLine(line); MarkColumn(column);}

      while ((c = getc(fd)) == ' ') spaces++;
      if (c == ':') (void)printf("* %d", ErrorNumber++);
      else while (spaces--) putchar(' ');
      for (;;) {
	 if (c == '@' || c == '{' || c == '}') putchar('@');
	 putchar(c);
         if (c == '\n') break;
         if ((c = getc(fd)) == EOF) { putchar('\n'); break; }
      }

   }

   EndNode(FileName);
   return 0;
}
