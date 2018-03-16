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
/* $Id: reftab.h,v 4.2 1997/08/29 09:16:01 peter Exp $ */

#ifndef REFTAB_H
#define REFTAB_H

#include "Types.h"

/* exported to do_order.c: */
extern int ord_max_did; /* the largest did ever used
                           may be incremented beyond max_entry */

/* exported to ordout.c: */
extern int ord_DefSymbNum; /* number of symbols */
extern int ord_DefRuleNum; /* number of rules */
extern int DefAttrNum;     /* total number of attributes */
extern int MaxRhsLen;      /* maximal number of rhs symbols */
extern int MaxRuleAttrs;   /* maximal number of attrs in a rule */
extern int MaxSymbAttrNum; /* maximal number of attributes per symbol */

extern int graphstate;	/* the state of graphs */

/* exported to do_order.c; sets above variables: */
extern void find_max_did (/* AttrEval IS; */);

/* exported to do_order.c: */
extern void order_init_ref_tab(/* AttrEval IS; */);
extern void order_finl_ref_tab();

/* ref_tab access functions and macros: */
extern ALLENTRIES *ref_tab;	/* the reference table of symbols,
				 * symbols, productions, and attributes
				   indexed by did
				*/

extern int min_entry, max_entry; /* the index range of ref_tab */

extern int lookup_attr (/* int sid, atno */); /* yields did of attr */

#define IsChainProd(pid) \
        (ref_tab[pid].entry.prod.hdright->right != NULL && \
	 ref_tab[pid].entry.prod.hdright->right->right == NULL)

#define LhsDidOfProd(pid) \
	(ref_tab[pid].entry.prod.hdright->sid)

#endif
