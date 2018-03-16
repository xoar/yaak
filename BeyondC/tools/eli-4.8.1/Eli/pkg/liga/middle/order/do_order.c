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
/* $Id: do_order.c,v 4.10 1997/08/29 09:16:01 peter Exp $ */
static char rcs_id[] = "$Id: do_order.c,v 4.10 1997/08/29 09:16:01 peter Exp $";
/*********************************************
*                                            *
*       Module  : do_order.c                 *
*                                            *
*       Version : 1.0                        *
*                                            *
*       Contains the main-routine of order   *
*					     *
*	Author  : Jiyang Liu		     *
*                                            *
**********************************************/
#ifndef GORTO
/* gorto doesn't use me */

#include "err.h"
#include "option_enums.h"
#include "option.h"
#include "option_types.h"
#include "opt_input.h"

#include "reftab.h"
#include "bottomup.h"
#include "visit.h"
#include "ordout.h"
#include "part.h"
#include "induce.h"
#include "initdp.h"

#include "expand.h" 
    /* expand provides 
       FILE *InputFile;
       FILE *OutputFile;
       FILE *ProtocolFile;
       FILE *ExpOptFile;
       FILE *OptOutFile;
    */


/********************************************
* 	global variables		    *
********************************************/

AttrEval ISexp;
FILE *OrdOptFile;
FILE *BuProdFile;


/* functions */

#ifdef __STDC__
static void 
order_deadly(char *msg)
#else
static void 
order_deadly
(msg)
   char *msg;
#endif
/* print deadly error message and terminate program                      */
{
   curpos.line = 0;
   curpos.col = 0;
   message(DEADLY, msg, 0, &curpos);
}/* order_deadly() */


#ifdef __STDC__
void 
do_order(AttrEval idlstruct, FILE *ctlfile)
#else
void 
do_order(idlstruct, ctlfile)
     AttrEval idlstruct;
     FILE *ctlfile;
#endif
{
   fprintf(ProtocolFile, "============================\n");
   fprintf(ProtocolFile, "Protocol of liga phase order\n");
   fprintf(ProtocolFile, "============================\n\n");

   ISexp = idlstruct;	/* get LIGA structure */
   OrdOptFile  = ctlfile;

   find_max_did (ISexp);

   /* read in options for order, set switches only: */
   read_orderOption();

   /* printf("order: initialize ref_tab\n"); */
   order_init_ref_tab(ISexp);

   /* printf("order: construct direct graphs\n"); */
   graphstate = DIRECT;
   cons_init_dp(ISexp);
   fprintf(ProtocolFile, "\n");

   if (TREE_BOTTOM_UP && TREE_COMPLETE)
      order_deadly
	("BOTTOMUP computations contradict TREE_COMPLETE option\n");

   cons_init_ds();

   if ((PRINT_SYMBOL_DIRECT) || (PRINT_RULE_DIRECT))
      print_headerForGraphs(DIRECT);

   if (PRINT_SYMBOL_DIRECT)
   {
      read_printOption(direct_symb);
      print_SymbGraphs();
   }
   if (PRINT_RULE_DIRECT)
   {
      read_printOption(direct_rule);
      print_RuleGraphs();
   }
   check_cycle();

   graphstate = TRANSITIVE;

   transitiveclosure();

   if ((PRINT_SYMBOL_TRANSITIV) || (PRINT_RULE_TRANSITIV))
      print_headerForGraphs(TRANSITIVE);

   if (PRINT_SYMBOL_TRANSITIV)
   {
      read_printOption(trans_symb);
      print_SymbGraphs();
   }
   if (PRINT_RULE_TRANSITIV)
   {
      read_printOption(trans_rule);
      print_RuleGraphs();
   }
   check_cycle();


   if (ARRANGE)
   {
      fprintf(ProtocolFile, "ARRANGE OPTIONS OF THE AG:\n");
      fprintf(ProtocolFile, "==========================\n\n");
      set_arrangeOption();
      fprintf(ProtocolFile, "\n\n");
   }

   graphstate = INDUCED;
   distributealldeps();
   transitiveclosure();

   /* set dependencies for generated trees: */
   GenTreeDeps (ISexp);
   distributealldeps();
   transitiveclosure();

   if ((PRINT_SYMBOL_INDUCED) || (PRINT_RULE_INDUCED))
      print_headerForGraphs(INDUCED);

   if (PRINT_SYMBOL_INDUCED)
   {  read_printOption(ind_symb);
      print_SymbGraphs();
   }
   if (PRINT_RULE_INDUCED)
   {  read_printOption(ind_rule);
      print_RuleGraphs();
   }
   check_cycle();

   if (TREE_BOTTOM_UP)
   {
     InduceBUAttrs ();
     distributealldeps();
     transitiveclosure();
     BUPartition ();
     InduceBUAttrs ();
     distributealldeps();
     transitiveclosure();

     if ((PRINT_SYMBOL_INDUCED) || (PRINT_RULE_INDUCED))
        print_headerForGraphs(INDUCED);
     if (PRINT_SYMBOL_INDUCED)
        print_SymbGraphs();
     if (PRINT_RULE_INDUCED)
        print_RuleGraphs();
     check_cycle();
   }

   graphstate = PARTITIONED;
   partit();

   distributealldeps(); /* added; check whether needed for ARRANGE FAST*/
   transitiveclosure();

   if ((PRINT_PARTITION) || (PRINT_RULE_PARTITIONED))
      print_headerForGraphs(PARTITIONED);

   if (PRINT_PARTITION)
   {
      read_printOption(partition);
      print_SymbGraphs();
   }
   if (PRINT_RULE_PARTITIONED)
   {
      read_printOption(part_rule);
      print_RuleGraphs();
   }
   check_cycle();

   visitsequence();

   if (TREE_BOTTOM_UP)
   { fprintf
       (ProtocolFile, 
        "\nFor the following rules nodes may not be created from above.\n");
     fprintf
       (ProtocolFile,
        "They have code or subtree visits in the construction phase.\n");
     fprintf
       (ProtocolFile,
        "For further analysis consult the visit-sequences.\n\n");

     BUChkProds ();
     fprintf(ProtocolFile, "\n");

     ChkBUInGenTrees ();
   }
   
   if (PRINT_VISITSEQUENCE)
   {
      if (TREE_BOTTOM_UP)
      {
         fprintf
          (ProtocolFile,
	   "\nAll visit-sequences are constructed for bottom-up processing:\n");
         fprintf
          (ProtocolFile,
           "The first visits to subtrees occur in left-to right order.\n");
         fprintf
          (ProtocolFile,
	   "They are not executed; they model what has happened before\n");
         fprintf
          (ProtocolFile,
	   "this node is constructed.\n");
         fprintf
          (ProtocolFile,
	   "Computations in that phase reflect dependencies without code.\n");
         fprintf
          (ProtocolFile,
	   "Then upto the first LEAVE there may be computations and visits\n");
         fprintf
          (ProtocolFile,
	   "which are executed when the node is created.\n");
         fprintf
          (ProtocolFile,
	   "The rest of the visit-sequence is reached by visits from above.\n\n");
      }
      read_printOption(visit_seq);
      print_VisitSequences();
   }
   /* print the statistics info of the input AG */

   print_statistics();

   write_dataStruct();

   order_finl_ref_tab();
}

#endif






