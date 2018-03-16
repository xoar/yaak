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
/* $Id: ordout.c,v 4.5 2010/04/08 10:27:10 peter Exp $ */
static char rcs_id[] = "$Id: ordout.c,v 4.5 2010/04/08 10:27:10 peter Exp $";

/****************************************************************
*                                                               *
*       Module  : output.c                                      *
*       Version : 1.0                                           *
*       Author  : Jiyang Liu                                    *
*       Contains routines to produce readable output.		*
****************************************************************/

#include "ligaconsts.h"
#include "printerr.h"
#include "option.h"
#include "do_order.h"
#include "reftab.h"

#include "ordout.h"

/****************************************
*       bool member()			*
****************************************/
static
bool member (pos, word) int pos; unsigned word;
{
   int bit;
   bit = pos % WORD_LENGTH;
   if (word & 0x1 << bit)
      return (TRUE);
   else
      return (FALSE);
}/* member() */


/****************************************
*	void print_stateText()		*
****************************************/
static
void print_stateText (graph_state) int graph_state;
{
   switch (graph_state)
   {
   case DIRECT:
      (void) fprintf(ProtocolFile, "DIRECT ");
      break;

   case TRANSITIVE:
      (void) fprintf(ProtocolFile, "TRANS. CLOSED ");
      break;

   case INDUCED:
      (void) fprintf(ProtocolFile, "INDUCED ");
      break;

   case PARTITIONED:
      (void) fprintf(ProtocolFile, "PARTITIONED ");
      break;
   }
   fflush(ProtocolFile);
}/* print_stateText() */


/****************************************
*       void print_headerForGraphs()    *
****************************************/

void print_headerForGraphs (graph_state) int graph_state;
{
   switch (graph_state)
   {
   case DIRECT:
      (void) fprintf(ProtocolFile, "GRAPHS FOR DIRECT DEPENDENCIES\n");
      (void) fprintf(ProtocolFile, "==============================\n\n");
      break;

   case TRANSITIVE:
      fprintf(ProtocolFile, "TRANSITIVE CLOSURE OF GRAPHS FOR DIRECT DEPENDENCIES\n ");
      fprintf(ProtocolFile, "====================================================\n\n");
      break;

   case INDUCED:
      fprintf(ProtocolFile, "TRANSITIVE CLOSURE OF GRAPHS FOR INDUCED DEPENDENCIES\n");
      fprintf(ProtocolFile, "=====================================================\n\n");
      break;

   case PARTITIONED:
      fprintf(ProtocolFile, "TRANSITIVE CLOSURE OF GRAPHS FOR PARTITION DEPENDENCIES\n");
      fprintf(ProtocolFile, "=======================================================\n\n");
      break;
   }	/* switch */

   fflush(ProtocolFile);
}/* print_headerForGraphs() */


/********************************************************
* 	void print_symb_graph()				*
*       print the attribute dependency graph of 	*
*	the given symbol.				*
********************************************************/
static
void print_symb_graph(sid) int sid;
{
   Symb symbdef;
   SEQAttrdef x;
   Attrdef attr;
   int atno = 0;
   int depatno;

   symbdef = ref_tab[sid].entry.symb.symb_def;

   print_stateText(graphstate);
   fprintf(ProtocolFile, "GRAPH FOR SYMBOL %s #%d AT ROW %d; COL %d\n",
	   symbdef->dname,
	   symbdef->did,
	   symbdef->row,
	   symbdef->col);

   fprintf(ProtocolFile, "  ATNO  CLASS  PART              SYMB.ATTR                DEPENDS ON\n");
   if (ref_tab[sid].entry.symb.attr_num == 0)
      fprintf(ProtocolFile, " NO ATTR\n");
   else
      /* print_dep_list */
      foreachinSEQAttrdef(symbdef->attrs, x, attr)
   {
      fprintf(ProtocolFile, "%5d", atno);
      switch (attr->class)
      {
      case ATCLSYNT:
	 fprintf(ProtocolFile, "    SYNT ");
	 break;
      case ATCLINH:
	 fprintf(ProtocolFile, "    INH  ");
	 break;
      default:
	 fprintf(ProtocolFile, "    ???? ");
	 break;
      }
      fprintf(ProtocolFile, " %3d    %15s.%-15s", attr->part, symbdef->dname, attr->name);
      if (member(atno, ref_tab[sid].entry.symb.ds[atno][atno / WORD_LENGTH]))
	 fprintf(ProtocolFile, " CYCLIC [");
      else
	 fprintf(ProtocolFile, "        [ ");

      for (depatno = 0; depatno < ref_tab[sid].entry.symb.attr_num; depatno++)
	 if (member(depatno, ref_tab[sid].entry.symb.ds[atno][depatno / WORD_LENGTH]))
	    fprintf(ProtocolFile, "%d ", depatno);
      fprintf(ProtocolFile, "]\n");
      atno += 1;
   }	/* foreach */

   fprintf(ProtocolFile, "\n");
   fflush(ProtocolFile);
}/* print_symb_graph() */

/****************************************
*	void print_SymbGraphs()		*
****************************************/

void print_SymbGraphs()
{  SEQint iseq;
   int did, printdid;

   if (emptySEQint (PrintList))
      return;
   retrievefirstSEQint (PrintList, printdid);
   if (printdid == PRINT_ALL)
      for (did = min_entry; did <= max_entry; did++)
      {
	 if (ref_tab[did].etag == SYMB)
	    print_symb_graph(did);
      }
   else
      foreachinSEQint (PrintList, iseq, did)
	 print_symb_graph(did);
}/* print_SymbGraphs() */


/********************************************************
*       void print_syntax()                             *
*       print the sytactic rule of a given rule         *
********************************************************/
void print_syntax (pid) int pid;
{
   SLNODE *slnptr;
   int sno = 0;

   for (slnptr = ref_tab[pid].entry.prod.hdright; slnptr != NULL; slnptr = slnptr->right)
   {
      fprintf(ProtocolFile, "  %s", ref_tab[slnptr->sid].entry.symb.symb_def->dname);
      if (sno == 0)
	 fprintf(ProtocolFile, " ::= ");
      sno++;
   }
   fprintf(ProtocolFile, "\n");
   fflush(ProtocolFile);
}/* print_syntax() */

/********************************************************
*       void print_rule_graph()                         *
*       print the attribute dependency graph of 	*
*	a given rule					*
********************************************************/
static
void print_rule_graph (pid) int pid;
{
   SLNODE *r_slnptr, *c_slnptr;
   SEQAttrdef x;
   Attrdef attr;
   int atno, pos, symbpos=0;

   print_stateText(graphstate);
   fprintf(ProtocolFile, "GRAPH FOR RULE %s #%d AT ROW %d; COL %d\n",
	   ref_tab[pid].entry.prod.prod_def->dname, pid,
	   ref_tab[pid].entry.prod.prod_def->row,
	   ref_tab[pid].entry.prod.prod_def->col);
   print_syntax(pid);
   fprintf(ProtocolFile, "  ATNO  CLASS  PART SPOS        SYMB.ATTR                DEPENDS ON\n");

   /* loop on the row */
   for (r_slnptr = ref_tab[pid].entry.prod.hdright; r_slnptr != NULL; r_slnptr = r_slnptr->right) {
      if (ref_tab[r_slnptr->sid].entry.symb.attr_num == 0)
	 fprintf(ProtocolFile, " NO ATTR\n");
      else
      {
	 atno = r_slnptr->start_row;
	 foreachinSEQAttrdef(ref_tab[r_slnptr->sid].entry.symb.symb_def->attrs, x, attr)
	 {
	    fprintf(ProtocolFile, "%3d", atno);
	    switch (attr->class)
	    {
	    case ATCLSYNT:
	       fprintf(ProtocolFile, "    SYNT ");
	       break;
	    case ATCLINH:
	       fprintf(ProtocolFile, "    INH  ");
	       break;
	    default:
	       fprintf(ProtocolFile, "    ???? ");
	       break;
	    }
	    fprintf(ProtocolFile, " %5d  %3d  %15s.%-15s", attr->part, symbpos, ref_tab[r_slnptr->sid].entry.symb.symb_def->dname, attr->name);
	    if (member(atno - r_slnptr->start_row, ref_tab[pid].entry.prod.dp[atno][r_slnptr->start_col + (atno - r_slnptr->start_row) / WORD_LENGTH]))
	       fprintf(ProtocolFile, " CYCLIC [");
	    else
	       fprintf(ProtocolFile, "        [ ");

	    /* loop on the column */
	    for (c_slnptr = ref_tab[pid].entry.prod.hdright; c_slnptr != NULL; c_slnptr = c_slnptr->right)
	       if (ref_tab[c_slnptr->sid].entry.symb.attr_num > 0)
		  for (pos = 0; pos < ref_tab[c_slnptr->sid].entry.symb.attr_num; pos++)
		     if (member(pos, ref_tab[pid].entry.prod.dp[atno][c_slnptr->start_col + pos / WORD_LENGTH]))
			fprintf(ProtocolFile, "%d ", pos + c_slnptr->start_row);


	    fprintf(ProtocolFile, "]\n");
	    atno++;
	 }	/* foreach */
      }
      symbpos++;
      }
   fprintf(ProtocolFile, "END RULE\n\n");
   fflush(ProtocolFile);
}/* print_rule_graph()  */

/****************************************
*       void print_RuleGraphs()         *
****************************************/

void print_RuleGraphs()
{  SEQint iseq;
   int did, printdid;

   if (emptySEQint (PrintList))
      return;
   retrievefirstSEQint (PrintList, printdid);
   if (printdid == PRINT_ALL)
      for (did = min_entry; did <= max_entry; did++)
      {
	 if (ref_tab[did].etag == PROD)
	    print_rule_graph(did);
      }
   else
      foreachinSEQint (PrintList, iseq, did)
	 print_rule_graph(did);
}/* print_RuleGraphs() */

/********************************************************
*       void print_visit_sequence()                     *
*       print the visit sequences for one rule          *
*       in readable form.				*
********************************************************/
static
void print_visit_sequence (pid) int pid;
{
   PRODENTRY *prod;
   VSPTR vselmptr;
   int vselmno;

   prod = &ref_tab[pid].entry.prod;

   fprintf(ProtocolFile, "VISIT-SEQUENCE FOR RULE %s #%d AT ROW %d; COL %d\n",
      prod->prod_def->dname, pid, prod->prod_def->row, prod->prod_def->col);

   print_syntax(pid);
   fprintf(ProtocolFile, " NO KIND  SYMBNO VISITNO  SYMBOL         ATTRIBUTE or FCT\n");

   vselmno = 1;
   for (vselmptr = prod->visitseq; vselmptr != NULL; vselmptr = vselmptr->next)
   {

      fprintf(ProtocolFile, "%3d ", vselmno++);

      switch (vselmptr->vscls)
      {

      case VSASSIG:
	 fprintf(ProtocolFile, "EVAL  %6d          %-15.14s%-15.14s",
		 vselmptr->vsinfo.assig.sno,
	     ref_tab[vselmptr->vsinfo.assig.sid].entry.symb.symb_def->dname,
	     ref_tab[vselmptr->vsinfo.assig.aid].entry.attr.attr_def->name);
	 break;

      case VSCOND:
         fprintf(ProtocolFile, "COMPUTE                              FCT: %s",
		 vselmptr->vsinfo.cond.idldef->name);

	 break;

      case VSVISIT:
	 if (vselmptr->vsinfo.visit.vssno == 0)
	    fprintf(ProtocolFile, "LEAVE      0 %7d  TO ANCESTOR",
		    vselmptr->vsinfo.visit.vsord);
	 else
	    fprintf(ProtocolFile, "VISIT %6d %7d  %-15.14s%-15.14s",
		    vselmptr->vsinfo.visit.vssno,
		    vselmptr->vsinfo.visit.vsord,
	    ref_tab[vselmptr->vsinfo.visit.vssid].entry.symb.symb_def->dname,
		    " ");
	 break;

      default:
	 fprintf(ProtocolFile, "*** ERROR *** in VISIT-SEQUENCE of RULE %s #%d AT ROW %d; COL %d\n",
		 prod->prod_def->dname, pid, prod->prod_def->row, prod->prod_def->col);
	 err_setpos(prod->prod_def->row, prod->prod_def->col);
	 err_print_error("in Visit Sequence of Rule.");
	 break;

      }	/* end of switch */

      fprintf(ProtocolFile, "\n");

   }	/* for */

   fprintf(ProtocolFile, "\n");
   fflush(ProtocolFile);
}/* print_visit_sequence() */

/********************************************************
*       void print_VisitSequences()                     *
*       print the visit sequences for all rules         *
*       in readable form.                               *
********************************************************/

void print_VisitSequences()
{  SEQint iseq;
   int did, printdid;

   if (emptySEQint (PrintList))
      return;
   retrievefirstSEQint (PrintList, printdid);
   fprintf(ProtocolFile, "VISIT-SEQUENCES\n");
   fprintf(ProtocolFile, "===============\n");

   if (printdid == PRINT_ALL)
      for (did = min_entry; did <= max_entry; did++)
      {
	 if (ref_tab[did].etag == PROD)
	    print_visit_sequence(did);
      }

   else
      foreachinSEQint (PrintList, iseq, did)
	 print_visit_sequence(did);
}/* print_VisitSequences() */

/*********************************************
* eval_maxVisitNo                            *
**********************************************/
static
int eval_maxVisitNo()
{
   int maxVisitNo;
   int did;
   VSPTR vselmptr;

   maxVisitNo = 0;

   for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == PROD)
      {
	 vselmptr = ref_tab[did].entry.prod.visitseq;
	 while (vselmptr != NULL)
	 {
	    if (vselmptr->vscls == VSVISIT)
	       /* if (vselmptr->vsinfo.visit.vssno > 0) */
	       if (maxVisitNo < vselmptr->vsinfo.visit.vsord)
		  maxVisitNo = vselmptr->vsinfo.visit.vsord;
	    vselmptr = vselmptr->next;
	 }
      }
   return (maxVisitNo);
}/* eval_maxVisitNo() */


/*********************************************
* eval_maxSymbNoInRule                       *
**********************************************/
static
int eval_maxSymbNoInRule()
{
   int did;
   int MaxSymbNum, symbnum;
   SLNODE *slnptr;

   MaxSymbNum = 0;

   for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == PROD)
      {
	 symbnum = 0;

	 for (slnptr = ref_tab[did].entry.prod.hdright;
	      slnptr != NULL; slnptr = slnptr->right)
	    symbnum++;

	 if (MaxSymbNum < symbnum)
	    MaxSymbNum = symbnum;
      }
   return (MaxSymbNum);

}/* eval_maxSymbNoInRule() */


/*********************************************
* eval_maxAttrNoInRule                       *
**********************************************/
static
int eval_maxAttrNoInRule()
{
   int did;
   int MaxRuleAttrNum;

   MaxRuleAttrNum = 0;

   for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == PROD)
      {

	 if (MaxRuleAttrNum < ref_tab[did].entry.prod.check_row)
	    MaxRuleAttrNum = ref_tab[did].entry.prod.check_row;

      }
   return (MaxRuleAttrNum);

}/* eval_maxAttrNoInRule() */


/*********************************************
* eval_maxAttrNoInSymb                       *
**********************************************/
static
int eval_maxAttrNoInSymb()
{
   int did;
   int MaxSymbAttrNum;

   MaxSymbAttrNum = 0;

   for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == SYMB)
      {

	 if (MaxSymbAttrNum < ref_tab[did].entry.symb.attr_num)
	    MaxSymbAttrNum = ref_tab[did].entry.symb.attr_num;

      }
   return (MaxSymbAttrNum);
}/* eval_maxAttrNoInSymb() */


/*********************************************
* print_stat                                 *
*********************************************/

void print_statistics()
{
   (void) fprintf(ProtocolFile, "OPTIONS OF THE AG:\n");
   (void) fprintf(ProtocolFile, "==================\n\n");

   (void) fprintf(ProtocolFile, "PARTITION-STRATEGY:   ");
   if (PART_EARLY)
      (void) fprintf(ProtocolFile, "AS EARLY AS POSSIBLE\n\n");
   else if (PART_LATE)
      (void) fprintf(ProtocolFile, "AS LATE AS POSSIBLE\n\n");
   /* else */

   /* (void)fprintf(ProtocolFile,"TOPOLOGICAL-STRATEGY: "); if (TOPO_MINCUT)
    * (void)fprintf(ProtocolFile,"WITH MIN_CUT\n\n"); else if (TOPO_EARLY)
    * (void)fprintf(ProtocolFile,"SO EARLY AS POSSIBLE (GREEDY)\n\n"); else if
    * (TOPO_LATE) (void)fprintf(ProtocolFile,"SO LATE AS POSSIBLE (LAZY)\n\n"); else
    * (void)fprintf(ProtocolFile,"WITHOUT MIN_CUT\n\n"); */
   /* else */

   (void) fprintf(ProtocolFile, "TREE_BOTTOM_UP:       ");
   if (TREE_BOTTOM_UP)
      (void) fprintf(ProtocolFile, "TRUE\n\n");
   else
      (void) fprintf(ProtocolFile, "FALSE\n\n");
   (void) fprintf(ProtocolFile, "TREE_COMPLETE:        ");
   if (TREE_COMPLETE)
      (void) fprintf(ProtocolFile, "TRUE\n\n");
   else
      (void) fprintf(ProtocolFile, "FALSE\n\n");
   /* else */

   (void) fprintf(ProtocolFile, "AUTOMATICALLY:         ");
   if (AUTOMATICALLY)
      (void) fprintf(ProtocolFile, "TRUE\n\n");
   else
      (void) fprintf(ProtocolFile, "FALSE\n\n");
   /* else */

   (void) fprintf(ProtocolFile, "\n\nCHARACTERISTICS OF THE AG:\n");
   (void) fprintf(ProtocolFile, "==========================\n\n");

   (void) fprintf(ProtocolFile, "THE AG IS  ");
   if (!AUTOMATICALLY)
      (void) fprintf(ProtocolFile, "*** ORDERED ***\n\n");
   else
      (void) fprintf(ProtocolFile, "*** ARRANGED ORDERED ***\n\n");

   (void) fprintf(ProtocolFile, "MAX. NUMBER OF SYMBOL VISIT:  %10d\n\n",
		  eval_maxVisitNo());
   (void) fprintf(ProtocolFile, "MAX. NUMBER OF SYMBOLS IN RULE: %8d\n\n",
		  eval_maxSymbNoInRule());
   (void) fprintf(ProtocolFile, "MAX. NUMBER OF ATTRIBUTES IN RULE: %5d\n\n",
		  eval_maxAttrNoInRule());
   (void) fprintf(ProtocolFile, "MAX. NUMBER OF ATTRIBUTES IN SYMBOL: %3d\n\n",
		  eval_maxAttrNoInSymb());

   (void) fprintf(ProtocolFile, "NUMBER OF DEFINED SYMBOLS:    %10d\n\n",
		  ord_DefSymbNum);
   (void) fprintf(ProtocolFile, "NUMBER OF CONTEXT-FREE RULES: %10d\n\n",
		  ord_DefRuleNum);

   (void) fprintf(ProtocolFile, "NUMBER OF ALL ATTRIBUTES: %14d\n\n",
		  DefAttrNum);
}/* print_statistics */
