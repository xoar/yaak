/* (C) Copyright 1997 University of Paderborn */

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

static char rcsid[]="$Id: string.c,v 1.7 2007/02/23 10:39:02 peter Exp $";

#include <stdio.h>
#include "global.h"
#include <ctype.h>
#include <string.h>

/* string table size */
#define STABSIZ 250

typedef struct IDLtag1{
        struct IDLtag1 *next;
        String value;
} CString, *LString;

# define SEQString LString
# define appendfrontSEQString(Stringseq,Stringvalue) Stringseq=\
		(SEQString)IDLListAddFront((pGenList)Stringseq,(someptr)Stringvalue)
# define foreachinSEQString(Stringseq,Stringptr,Stringvalue) for\
(Stringptr = Stringseq; \
 		Stringptr!=NULL&&((Stringvalue=Stringptr->value)||1); \
Stringptr=Stringptr->next)
# define emptySEQString(Stringseq) ((Stringseq)==NULL)


/* string table (static variables are initialized to NULL)*/
static SEQString StringTable[STABSIZ]; 

/* hash a string for the string table */
int StringHash(S)
register char *S;
{	register int i;
	for (i=0 ; *S ; i += (*S) , S++);
	return(i % (STABSIZ-1));
}

/* add a string to the String Table and return pointer */
String NewString(str)
String str;
{
	int index;
	SEQString SStr;
	String AStr;

	index = StringHash(str);
	foreachinSEQString(StringTable[index], SStr, AStr) {
	    if (!strcmp(AStr, str)) {  /* string is already in table */
		return(AStr);
	    }
	}

	/* if this point is reached, string was not found so 
	   allocate new storage and add to sequence of appropriate 
	   index in String Table */
	AStr = (String)GetHeap(strlen(str) + 1);
	strcpy(AStr, str);
	appendfrontSEQString(StringTable[index], AStr);
	return(AStr);
}

void InitStringTable()
{
	int i;

	for (i=0; i<STABSIZ; i++) {
	    StringTable[i] = NULL;
	}
}

/* for debugging */
void PrintStringTable()
{
	int i;
	SEQString SStr;
	String AStr;

	fprintf(stderr, "String Table\n");
	for (i=0; i<STABSIZ; i++) {
	    if (!emptySEQString(StringTable[i])) {
		fprintf(stderr, "%3d: ", i);
		foreachinSEQString(StringTable[i], SStr, AStr)
		    fprintf(stderr, "%s ", AStr);
		fprintf(stderr, "\n");
	    }
	}
}

/* reader string table (static variables are initialized to NULL)*/
static SEQString ReaderStringTable[STABSIZ]; 

void InitReaderStringTable()
{
	int i;

	for (i=0; i<STABSIZ; i++) {
	    ReaderStringTable[i] = NULL;
	}
}

void PrintReaderStringTable()
{
	int i;
	SEQString SStr;
	String AStr;

	fprintf(stderr, "Reader String Table\n");
	for (i=0; i<STABSIZ; i++) {
	    if (!emptySEQString(ReaderStringTable[i])) {
		fprintf(stderr, "%3d: ", i);
		foreachinSEQString(ReaderStringTable[i], SStr, AStr)
		    fprintf(stderr, "%s ", AStr);
		fprintf(stderr, "\n");
	    }
	}
}

/* add a string to the String Table and return pointer */
String NewReaderString(str)
String str;
{
	int index;
	SEQString SStr;
	String AStr;

	index = StringHash(str);
	foreachinSEQString(ReaderStringTable[index], SStr, AStr)
	    if (!strcmp(AStr, str)) {  /* string is already in table */
		return(AStr);
	    }

	/* if this point is reached, string was not found so 
	   allocate new storage and add to sequence of appropriate 
	   index in Reader String Table */
	AStr = (String)GetHeap(strlen(str) + 1);
	strcpy(AStr, str);
	appendfrontSEQString(ReaderStringTable[index], AStr);
	return(AStr);
}
/* retrieve a string in the String Table, if found
   return pointer else return NULL */
String RetrieveReaderString(str)
String str;
{
	int index;
	SEQString SStr;
	String AStr;

	index = StringHash(str);
	foreachinSEQString(ReaderStringTable[index], SStr, AStr)
	    if (!strcmp(AStr, str)) {  /* string is in table */
		return(AStr);
	    }

	/* if this point is reached, string was not found so 
	   return NULL						*/
	return(NULL);
}

/* convert an IDL string to a C array of characters */
char *StringToChar(str)
String str;
{
	char *AStr;

	AStr = (char *)GetHeap(strlen(str) + 1);
	strcpy(AStr, str);
	return(AStr);
}


/* compare two IDL strings.  (works the same as strcmp)
 * return -1 if str1 < str2.
 * return +1 if str1 > str2.
 * return  0 if str1 == str2
*/
int StringCmp(str1, str2)
String str1, str2;
{
    if (str1 == str2) return(0);
    else return(strcmp(str1, str2));
}


/***********************************************************************
 *
 * Function NCStringMatch
 *
 * Purpose: Check if two strings are equal regardless of case
 *
 * Return Value: TRUE if equal else FALSE
 *
 * Algorithm: 
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
Boolean NCStringMatch(s1, s2)
String s1, s2;
{
    int len1, len2;   /* length of strings */
    int i;
    char c1, c2;
    Boolean match = TRUE;

    if (!s1) {
	if (!s2) return(TRUE);
	else return(FALSE);
    }
	
    len1 = strlen(s1);
    len2 = strlen(s2);
    if (len1 == len2) {
	for (i=0; i<len1; i++) {
	    c1 = s1[i];
	    c2 = s2[i];
	    if (isupper(c1)) c1 = tolower(c1);
	    if (isupper(c2)) c2 = tolower(c2);
	    if (c1 != c2) {
		match = FALSE;
		break;
	    }
	}
    }
    else match = FALSE;

    return(match);
}
