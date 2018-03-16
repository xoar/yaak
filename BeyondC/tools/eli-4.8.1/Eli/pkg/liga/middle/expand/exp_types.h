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
/* $Id: exp_types.h,v 4.1 1997/08/29 09:09:06 peter Exp $ */

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		no specific (global)				*
*	File:		exp_types.h					*
*	Contents:	type declarations for expand pass		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	12 Dec 1990					*
*	Last change:	24 Sep 1991					*
*									*
\***********************************************************************/

#ifndef	_EXP_TYPES_H_INCL
#define	_EXP_TYPES_H_INCL

/* * ENUMERATORS */

/* tags for types of entries in the reference table */
typedef enum
{
   empty_entry, symbol_entry, prod_entry
} ref_tag;

/* * STRUCTURE DECLARATIONS */

/* node structure for global list of INCLUDING constructs */
typedef struct IncNode
{
   int prodid;	/* did of the production */
   int typeid;	/* id of the type */
   Including incl;	/* reference to INCLUDING construct */
   int dep;	/* only for attribute dependecies */
   struct IncNode *next;	/* link pointer */
   struct IncNode *same;	/* link to identical INCLUDING construct */
} *IncNode;

/* node structure for the list of symbol occurrences in a production */
typedef struct SNode
{
   int symbdid;	/* did of the symbol */
   int prodid;	/* did of the production */
   struct SNode *right;	/* link pointer */
   struct SNode *down;	/* link to next symbol with same did */
} *SNode;

/* node structure for the list of transfer rules in a production */
typedef struct TfNode
{
   int row, col;	/* position of original statement */
   int symbdid;	/* did of rhs symbol */
   int symb_no;	/* index in list of rhs symbols */
   Attrdef lhs_attr;	/* definition of the attribute of lhs symbol */
   Attrdef rhs_attr;	/* definition of the attribute of rhs symbol */
   int cancelled;	/* cancellation flag */
   struct TfNode *next;	/* link pointer */
} *TfNode;

/* structure of a symbol entry in the reference table */
typedef struct SymbEntry
{
   Symb symb_def;	/* reference to the liga definition from IDL */
   SNode ldown;	/* list of this symbol on left hand sides */
   SNode rdown;	/* list of this symbol on right hand sides */
   int flag;	/* various flags */
   int visited;	/* tmp mark for recursive search */
   int completechk;	/* reachability check is complete */
   int prodvisited;	/* mark for recursive production search */
} *SymbEntry;

/* structure of a production entry in the reference table */
typedef struct ProdEntry
{
   Prod prod_def;	/* reference to the definition */
   Attribution attrib;	/* reference to the attribution */
   SNode right;	/* list of symbols */
   TfNode trns;	/* list of transfer rules */
   int flag;	/* various flags */
} *ProdEntry;

/* one element of the reference table */
typedef struct RefEntry
{
   ref_tag entry_tag;	/* type of entry */
   union
   {
      struct SymbEntry symb;
      struct ProdEntry prod;
   } entry;	/* the entry itself */
} *RefEntry;

/* node for a list of CHAINSTARTs */
typedef struct ChStNode
{
   ChainStart start;	/* reference to chain start */
   Chainacc startacc;	/* access starting the chain */
   int prodid;	/* did of the production */
   int symbdid;	/* did of the access symbol */
   Call accall;	/* call containing the start access */
   struct ChStNode *next;	/* link pointer */
} *ChStNode;

/* node for a list of accesses to CHAIN attributes */
typedef struct ChAccNode
{
   Chainacc acc;	/* reference to access */
   int prodid;	/* did of the production */
   int symbdid;	/* did of the access symbol */
   Call accall;	/* call containing the access */
   int isdef;	/* flag for appearance on lhs of assignment */
   struct ChAccNode *next;	/* link pointer */
} *ChAccNode;

/* node for the list of all CHAIN constructs */
typedef struct ChainNode
{
   int did;	/* did of CHAIN construct */
   int cancelled;	/* cancellation flag */
   Chain chain;	/* reference to CHAIN definition */
   ChStNode starts;	/* start rules of this chain */
   ChAccNode accesses;	/* list of accesses */
   struct ChainNode *next;	/* link pointer */
} *ChainNode;

/* node for list of CONSTITUENT(S) source attributes */
typedef struct SyAttrNode
{
   Attrdef ad;	/* definition of the source attribute */
   struct SyAttrNode *next;	/* link pointer */
} *SyAttrNode;

/* node for list of CONSTITUENT(S) symbols */
typedef struct CoSyNode
{
   int symbdid;	/* did of the symbol */
   SyAttrNode attrs;	/* list of source attributes */
   struct CoSyNode *next;	/* link pointer */
} *CoSyNode;

/* node structure for global list of CONSTITUENT(S) constructs */
typedef struct ConstNode
{
   int prodid;	/* did of the production */
   int subdid;	/* did of the subtree symbol */
   int typeid;	/* did of the type */
   int list_tid;	/* did of the list type */
   char *list_name;	/* name of the list type */
   char *concat_name;	/* name of concatenation function */
   char *creat_name;	/* name of function for single elements */
   char *empty_name;	/* name of function for empty lists */
   CoSyNode src;	/* list of source symbols and attributes */
   Constit constit;	/* reference to the construct */
   Call constcall;	/* call containing the construct */
   int parmno;	/* parameter in that call being the construct */
   SEQExpr shield_symbs;	/* list of shielding symbols */
   int dep;	/* only for attribute dependecies */
   int cancelled;	/* cancellation flag */
   struct ConstNode *next;	/* link pointer */
   struct ConstNode *same;	/* link to identical construct */
} *ConstNode;

#endif

/***********************\
* end of exp_types.h	*
\***********************/

/* HaDeS */
