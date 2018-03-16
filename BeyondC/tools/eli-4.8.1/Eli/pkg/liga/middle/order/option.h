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
/* $Id: option.h,v 1.3 1997/08/29 09:16:01 peter Exp $ */
#ifndef OPTION_H
#define OPTION_H

#include "bool.h"
/* switches for processing: */
extern bool
  AUTOMATICALLY, PARSE_TIME, ARRANGE,
  PART_EARLY, PART_LATE, 
  TREE_COMPLETE, TREE_TOP_DOWN, TREE_BOTTOM_UP;

#ifndef GORTO
/* switches for info output: */
extern bool
  PRINT_SYMBOL_DIRECT, PRINT_SYMBOL_TRANSITIV, PRINT_SYMBOL_INDUCED,
  PRINT_RULE_DIRECT, PRINT_RULE_TRANSITIV, PRINT_RULE_INDUCED,
  PRINT_RULE_PARTITIONED, PRINT_PARTITION, PRINT_VISITSEQUENCE;
#endif 

/* The PrintList is filled with the did of the graphs in each state
   to be printed.
   PrintList is exported to ordout.
*/

#include "Types.h"
extern SEQint PrintList;
#define PRINT_ALL       -100

extern void read_orderOption(); /* for do_order.c, gorto/Main.c */
extern void set_arrangeOption();/* for do_order.c, gorto/Order.c */
extern void read_printOption(); /* for do_order.c */

/* interface between option.c and predefdp.c
   an inconvenient way to enter symbol dependencies ...:
*/
typedef struct RArrangeHelp
{
   int toAttrId;
   int fromAttrId;
   int toOrd;
   int toSymbId;
   int fromOrd;
   int fromSymbId;
   int prodId;
} *ArrangeHelp;
extern ArrangeHelp getIdArrangeSymbol(); /* for predefdp.c only */
extern void enter_depSymbol(); /* for predefdp.c only */


#ifdef GORTO
#include "Types.h"
extern Symb lookupSymbByName();
extern Prod lookupProdByName();
#endif


#endif
