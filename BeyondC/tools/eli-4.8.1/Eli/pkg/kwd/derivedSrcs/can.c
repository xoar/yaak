static char RCSid[] = "$Id: can.c,v 1.11 2009/04/19 20:59:31 profw Exp $";
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

/* Canned description module */

#include <string.h>
#include "can.h"

static CannedDescr nulldescr = { (char *)0, (char *)0, (char *)0, (char *)0 };

CannedDescrPtr NullDescr = &nulldescr;

static CannedDescr lib[] = {
/*  later, read this data from a file - I don't feel like parsing it now! */
{ "SPACES",	"\\040+",	(char *)0,	(char *)0},
{ "TAB",	"\\t",	"auxTab",	(char *)0},
{ "NEW_LINE",	"[\\r\\n]",	"auxNewLine",	(char *)0},
{ "C_IDENTIFIER",	"[a-zA-Z_][a-zA-Z_0-9]*",
					(char *)0, "mkidn" },
{ "C_IDENTIFIER_ISO",
  "[a-zA-Z_\\0300-\\0326\\0330-\\0366\\0370-\\0377][a-zA-Z_\\0300-\\0326\\0330-\\0366\\0370-\\03770-9]*",
					(char *)0, "mkidn" },
{ "C_INTEGER",		"([0-9]+|0[xX][0-9a-fA-F]*)",
					(char *)0, "c_mkint"},
{ "C_INT_DENOTATION", "([1-9][0-9]*|0[0-7]*|0[xX][0-9a-fA-F]+)([uU][lL]?|[lL][uU]?)?",
					(char *)0, "mkstr"},
{ "C_FLOAT",
"(((([0-9]+\\.[0-9]*)|(\\.[0-9]+))((e|E)(\\+|\\-)?[0-9]+)?)|([0-9]+(e|E)(\\+|\\-)?[0-9]+))[fFlL]?",
					(char *)0, "mkstr"},
{ "C_STRING_LIT",	"\\\"",
					"auxCString", "mkstr"},
{ "C_CHAR_CONSTANT",	"'",
					"auxCChar", "c_mkchar"},
{ "C_COMMENT",		"\"/*\"",
					"auxCComment", (char *)0 },
{ "MODULA2_COMMENT", 	"\"(*\"",
	                                "auxM3Comment", (char *)0 },
{ "MODULA3_COMMENT", 	"\"(*\"",
	                                "auxM3Comment", (char *)0 },
{ "MODULA2_CHARINT",	"[0-9][0-9A-Fa-f]*C",
	                                (char *)0, "modula_mkint" },
{ "MODULA2_INTEGER",	"[0-9][0-9A-Fa-f]*[BH]?",
	                                (char *)0, "modula_mkint" },
{ "MODULA2_LITERALDQ",  "\\\"",
                                        "auxM2String", "mkstr" },
{ "MODULA2_LITERALSQ",	"'",
                                        "auxM2String", "mkstr" },
{ "PASCAL_COMMENT",	"\"{\"|\"(*\"",
					"auxPascalComment", (char *)0 },
{ "PASCAL_IDENTIFIER",	"[a-zA-Z][a-zA-Z0-9]*",
					(char *)0, "mkidn" },
{ "PASCAL_REAL",
"(([0-9]+\\.[0-9]+)((e|E)(\\+|\\-)?[0-9]+)?)|([0-9]+(e|E)(\\+|\\-)?[0-9]+)",
					(char *)0, "mkstr"},
{ "PASCAL_INTEGER",	"[0-9]+",
					(char *)0, "mkint"},
{ "PASCAL_STRING",	"'",
					"auxPascalString", "mkstr"},
{ "MODULA_INTEGER",	"[0-9][0-9A-Fa-f]*[BCH]?",
					(char *)0, "modula_mkint"},
{ "ADA_COMMENT",	"--",
					"auxEOL", (char *)0 },
{ "ADA_IDENTIFIER",	"[a-zA-Z](_?[a-zA-Z0-9])*",
					(char *)0, "mkidn" },
{ "AWK_COMMENT",	"#",
					"auxEOL", (char *)0 },
};


/***/
CannedDescrPtr
#if defined(__STDC__) || defined(__cplusplus)
libLookup (char *s)
#else
libLookup (s)
char *s;
#endif
/* Obtain an index to a canned description
 *    On entry-
 *       s names the canned description desired
 *    If s names a valid canned description then on exit-
 *       libLookup is the address of the canned description
 *    Otherwise on exit-
 *       libLookup is NullDescr
 ***/
{
	size_t i;

	for(i = 0; i < (sizeof lib)/(sizeof lib[0]); i++) 
		if (!strcmp(s, lib[i].Lname)) break;

	return (i < (sizeof lib)/(sizeof lib[0]) ? &lib[i] : NullDescr);
}
