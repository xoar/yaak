/* $Id: option_types.h,v 4.1 1997/08/29 09:19:06 peter Exp $ */
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

/***********************************************************************\
*	option_types.h							*
*	types for the LIGA option handler				*
*									*
*	Written 06/20/90 - 11/14/90	by HaDeS			*
\***********************************************************************/

#ifndef _OPT_TYPES_H_INCL
#define _OPT_TYPES_H_INCL

typedef struct _idlist {
	char		*ident;
	struct _idlist	*next;
} *IdList;

typedef	struct _anameslist {
	char		*symbname;
	IdList		names;
	struct _anameslist *next;
} *ANamesList;

typedef	struct _expoption {
	expoptflag	flag;
	char		*attrname;
} *ExpOption;

typedef struct _orderoption {
	ordoptflag	flag;
	int		namecount;
	char		**names;
	int		symbindex1,
			symbindex2;
} *OrdOption;

typedef	struct _optimoption {
	optoptflag	flag;
	ANamesList	attrs;
} *OptOption;

typedef struct _backendoption {
	beoptflag	flag;
	int		value;
} *BEOption;

typedef struct _explist {
	ExpOption	entry;
	struct _explist	*next;
} *ExpList;

typedef struct _ordlist {
	OrdOption	entry;
	struct _ordlist	*next;
} *OrdList;

typedef struct _optlist {
	OptOption	entry;
	struct _optlist	*next;
} *OptList;

typedef struct _belist {
	BEOption	entry;
	struct _belist	*next;
} *BEList;

typedef struct _optcollect {
	ExpList		exp_opts;
	OrdList		ord_opts;
	OptList		opt_opts;
	BEList		be_opts;
} *OptCollect;

typedef union {
	ExpList		entry1;
	OrdList		entry2;
	OptList		entry3;
	BEList		entry4;
} OptLists;

typedef struct _optcombin {
	listtype	type;
	OptLists	entry;
} *OptCombin;

#endif

