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
/* $Id: expchain.c,v 4.5 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: expchain.c,v 4.5 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expchain.c					*
*	File:		expchain.c					*
*	Contents:	functions to expand CHAIN constructs		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	26 Feb 1991					*
*	Last change:	22 Nov 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "LIGAMacros.h"

#include "middle_mem.h"
/* Includes for option handling */
#include "option_enums.h"
#include "option_types.h"

#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "exp_io.h"
#include "expref.h"
#include "expidl.h"
#include "expand.h"
#include "exptrav.h"
#include "expchain.h"
#include "exp_prot.h"

/* **** EXPANSION OF CHAIN CONSTRUCTS *
 * 
 * To expand the CHAIN construct this pass first calls the function *
 * find_chains(). It searches for all CHAIN accesses by calling the recursive *
 * function chain_in_call(). For all different chains there is a list
 * containing * all accesses to and starts of the chain. *  In the next step
 * expand_chains() is called to expand all chains. In the main * loop for
 * each chain first the defining assignments for the chain starts are *
 * searched by the function find_startaccs(). Then the chain is checked for *
 * various error conditions in the function check_chain(). In the function *
 * mark_chain() marking the chain symbols and productions is started at the *
 * accesses to the chain. This marking is done by the recursive function *
 * mark_chain_trans(). The function also generated the necessary chain *
 * attributes. Then all start constructs of the chain are checked for errors *
 * by calling the function check_chainstarts(). *  After that the function
 * gen_chain_links() is called to generate new * assignments to link the
 * chain through every production involved in the chain. * This is done by
 * calling either lhs_chain_assign() or gen_start_links() or *
 * gen_trans_links() depending upon the type of the mark of the production. *
 * The function gen_start_links() calls the function r2r_chain_assign() to *
 * create a new assignment and the function repl_chainstart() to replace the *
 * chain start acces. The function gen_trans_links() calls the * functions
 * lhs_chain_assign(), l2r_chain_assign(), r2r_chain_assign() and *
 * r2l_chain_assign() to generate the appropriate assignments. *  When the
 * chain is linked through all productions all accesses to the chain * are
 * replaced by accesses to the appropriate chain attribute by calling the *
 * function repl_chaccs(). *  After all chains are expanded, the definitions
 * and starts of the chains are * deleted by calling del_chaindefs() and
 * del_chainstarts(). *
 * 
***
 * 
 */


/* * GLOBAL VARIABLES */

ChainNode chains;	/* CHAIN definitions, starts and accesses	 */

/* * LOCAL VARIABLES */

static int chaincount;	/* number if CHAIN constructs			 */
static int newassigns;	/* total number of new assignments		 */

/* * LOCAL FUNCTIONS */

#ifdef __STDC__
static char* msg_compose_2(char *s1, char *s2)
#else
static char* msg_compose_2(s1, s2)
char *s1, *s2;
#endif
{ char *tmp=middle_tempMalloc(__FILE__, __LINE__,
			      strlen(s1)+strlen(s2)+1);
  sprintf(tmp, "%s%s",s1,s2);
  return tmp;
}

#ifdef __STDC__
static char* msg_compose_4(char *s1, char *s2, char *s3, char*s4)
#else
static char* msg_compose_4(s1, s2, s3, s4)
char *s1, *s2, *s3, *s4;
#endif
{ char *tmp=middle_tempMalloc(__FILE__, __LINE__,
			      strlen(s1)+strlen(s2)+
			      strlen(s3)+strlen(s4)+1);
  sprintf(tmp, "%s%s%s%s",s1,s2,s3,s4);
  return tmp;
}

static
#ifdef __STDC__
void
ins_new_chain(Chain chain)
#else
void
ins_new_chain(chain)
   Chain chain;
#endif
/* make new chain node and append it to the list			 */
{
   ChainNode newcn;

   chaincount++;
   newcn = (ChainNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct ChainNode));
   if (!newcn)
      deadly("expand: out of memory\n");
   newcn->did = didOfChain(chain);
   newcn->cancelled = FALSE;
   newcn->chain = chain;
   newcn->starts = (ChStNode) NULL;
   newcn->accesses = (ChAccNode) NULL;
   newcn->next = chains;
   chains = newcn;
}/* ins_new_chain() */

static
#ifdef __STDC__
void
ins_chainstart(ChainStart cs, int pid)
#else
void
ins_chainstart(cs, pid)
   ChainStart cs;
   int pid;
#endif
/* search chain node, enter node for chain start and create attr. names	 */
{
   ChainNode cn;
   ChStNode csn, cs_list;

   /* search for chain node */
   for (cn = chains; cn && cn->did != chainidOfChainStart(cs); cn = cn->next);

   /* entry must have been found */
   if (!cn)
   {
      print_err(rowOfChainStart(cs), colOfChainStart(cs),
		"Internal error #1 in expchain.c", NO_ERRID);
      return;
   }	/* if */
   /* create new node */
   csn = (ChStNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct ChStNode));
   if (!csn)
      deadly("expand: out of memory\n");
   csn->start = cs;
   csn->prodid = pid;
   csn->startacc = NULL;

   /* only one CHAINSTART in each production allowed */
   for (cs_list = cn->starts; cs_list; cs_list = cs_list->next)
   {
      if (cs_list->prodid == pid)
      {
	 print_err(rowOfChainStart(cs), colOfChainStart(cs),
		   msg_compose_2("Multiple start rules for CHAIN ",
				 dnameOfChain(cn->chain)),
		   CHST_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
			"multiple start rules for CHAIN %s",
			dnameOfChain(cn->chain));
	 (void) fprintf(ProtocolFile,
			" in production %s, line %d, col %d\n\n",
			dnameOfProd(prodref(pid)),
			rowOfProd(prodref(pid)),
			colOfProd(prodref(pid)));
      }	/* if */
   }	/* for */
   csn->next = cn->starts;
   cn->starts = csn;

   pregenattrOfChainStart(cs) = (char *) middle_Malloc(__FILE__, __LINE__, 
					     strlen(dnameOfChain(cn->chain))
					      + strlen(CHAIN_PRE_ATTR) + 8);
   postgenattrOfChainStart(cs) = (char *) middle_Malloc(__FILE__, __LINE__, 
					     strlen(dnameOfChain(cn->chain))
					     + strlen(CHAIN_POST_ATTR) + 8);
   if (!pregenattrOfChainStart(cs) && !postgenattrOfChainStart(cs))
      deadly("expand: out of memory\n");
   (void) sprintf(pregenattrOfChainStart(cs), "%s%s",
		  dnameOfChain(cn->chain), CHAIN_PRE_ATTR);
   (void) sprintf(postgenattrOfChainStart(cs), "%s%s",
		  dnameOfChain(cn->chain), CHAIN_POST_ATTR);
}/* ins_chainstart() */

static
#ifdef __STDC__
void
show_chain(ChainNode chptr)
#else
void
show_chain(chptr)
   ChainNode chptr;
#endif
/* show this CHAIN construct						 */
{
   ChStNode csn;
   ChAccNode can;

   fprintf(ProtocolFile, "\nCHAIN construct:\n");
   fprintf(ProtocolFile,
	   "   CHAIN %s;\n   in ",
	   dnameOfChain(chptr->chain));
   prot_position(ProtocolFile, 
		 rowOfChain(chptr->chain), 
		 colOfChain(chptr->chain));
   if (chptr->cancelled)
   {
      (void) fprintf(ProtocolFile,
	      "   expansion cancelled due to previous error or warning\n");
      return;
   }	/* if */
   /* show start rules */
   (void) fprintf(ProtocolFile, "CHAINSTART(s):\n");
   for (csn = chptr->starts; csn; csn = csn->next)
   {
      if (!csn->start)
	 continue;
      fprintf(ProtocolFile,"   RULE ");
      prot_rule(ProtocolFile, csn->prodid);

      fprintf(ProtocolFile,"      ");
      prot_position(ProtocolFile, 
		    rowOfChainStart(csn->start), 
		    colOfChainStart(csn->start));

      if (!csn->startacc)
	 continue;
/*      (void) fprintf(ProtocolFile,
		     "\t\t\tstart access in line %d, col %d\n",
		     rowOfChainacc(csn->startacc),
		     colOfChainacc(csn->startacc));
*/
   }	/* for */

   /* show chain accesses */
   (void) fprintf(ProtocolFile, "CHAIN accesses:\n");
   for (can = chptr->accesses; can; can = can->next)
   {
      if (!can->acc)
	 continue;
      if (can->isdef)
	{ (void) fprintf(ProtocolFile,
			 "   definition in RULE ");
	}
      else { (void) fprintf(ProtocolFile,
			    "   usage in RULE ");
	   }
      prot_rule(ProtocolFile, can->prodid);
      fprintf(ProtocolFile,"      ");
      prot_position(ProtocolFile, 
		    rowOfChainacc(can->acc),
		    colOfChainacc(can->acc));
   }	/* for */
}/* show_chain() */

static
#ifdef __STDC__
void
find_startaccs(ChainNode chptr)
#else
void
find_startaccs(chptr)
   ChainNode chptr;
#endif
/* find chain accesses for all start rules				 */
{
   ChStNode csn;
   ChAccNode can, startcan;
   int minsno;
   int haslhsacc;
   int sid;

   if (!chptr->starts || !chptr->accesses)
      return;

   for (csn = chptr->starts; csn; csn = csn->next)
   {
      minsno = 1000;
      haslhsacc = FALSE;
      startcan = NULL;
      /* search for leftmost defining chain access */
      for (can = chptr->accesses; can; can = can->next)
      {
	 /* access must define attribute in the	 */
	 /* same production and must be the	 */
	 /* leftmost of the rhs symbols		 */
	 if (can->isdef
	     && csn->prodid == can->prodid
	     && symbnoOfChainacc(can->acc)
	     && symbnoOfChainacc(can->acc) < minsno)
	 {
	    minsno = symbnoOfChainacc(can->acc);
	    startcan = can;
	 }	/* if */
	 /* set flag to signal access to lhs symbol */
	 if (can->isdef
	     && csn->prodid == can->prodid
	     && !symbnoOfChainacc(can->acc))
	    haslhsacc = TRUE;
      }	/* for */

      /* access must be found */
      if (!startcan)
      {
	 if (haslhsacc)
	 {
	    print_err(
		      rowOfChainStart(csn->start),
		      colOfChainStart(csn->start),
		      msg_compose_4("CHAIN ",
			  	    dnameOfChain(chptr->chain),
				    " must not start on lhs symbol",
				    ""),
		      CHST_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "CHAIN %s must not start on lhs symbol",
			   dnameOfChain(chptr->chain));
	    (void) fprintf(ProtocolFile,
			   " in line %d, col %d\n\n",
			   rowOfChainStart(csn->start),
			   colOfChainStart(csn->start));
	    chptr->cancelled = TRUE;
	    continue;
	 }
	 /* if */
	 else
	 {
	    print_err(
		      rowOfChainStart(csn->start),
		      colOfChainStart(csn->start),
		      msg_compose_2("No access to started CHAIN ",
				    dnameOfChain(chptr->chain)),
		      CHST_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "no corresponding access to CHAINSTART");
	    (void) fprintf(ProtocolFile,
			   " in line %d, col %d\n\n",
			   rowOfChainStart(csn->start),
			   colOfChainStart(csn->start));
	    chptr->cancelled = TRUE;
	    continue;
	 }	/* else */
      }	/* if */
      /* enter chain access into chain start node */
      csn->startacc = startcan->acc;
      csn->accall = startcan->accall;
      sid = startcan->symbdid;
      csn->symbdid = sid;	/* sid is again used below */

      /* remove chain access node of chain start access */
      if (chptr->accesses == startcan)
      {
	 chptr->accesses = startcan->next;
      }
      /* if */
      else
      {
	 for (can = chptr->accesses; can; can = can->next)
	 {
	    if (can->next == startcan)
	    {
	       can->next = startcan->next;
	       break;
	    }	/* if */
	 }	/* for */
      }	/* else */

      /* mark start production */
      prodflag(csn->prodid) = start_prod;
      markedprods++;
      /* mark start symbol */
      if (symbflag(sid) == no_sflag)
      {
	 symbflag(sid) = chainstart_symb;
	 markedsymbs++;
	 /* generate attributes for start symbol */
	 gen_chain_attr(
			sid,
			pregenattrOfChainStart(csn->start),
			postgenattrOfChainStart(csn->start),
			typeidOfChain(chptr->chain));
	 newattrs += 2;
      }	/* if */
   }	/* for */
}/* find_startaccs() */

static
#ifdef __STDC__
int
check_chain(ChainNode chptr)
#else
int
check_chain(chptr)
   ChainNode chptr;
#endif
/* check this CHAIN construct for errors				 */
{
   ChStNode csn;
   ChAccNode can;
   int defcount, usecount, startdefcount;

/* for messages: the name of the CHAIN */
   char *chainname = dnameOfChain(chptr->chain);

   if (!chptr->starts && !chptr->accesses)
   {
      (void) fprintf(ProtocolFile, "\n*** WARNING  ");
      (void) fprintf(ProtocolFile,
		     "CHAIN %s defined but never used, line %d, col %d\n",
		     chainname,
		     rowOfChain(chptr->chain),
		     colOfChain(chptr->chain));
      chptr->cancelled = TRUE;
      return (FALSE);
   }	/* if */
   if (!chptr->starts)
   {  
      print_err(rowOfChain(chptr->chain),
		colOfChain(chptr->chain),
		msg_compose_2("CHAIN without start rule: ",chainname), 
		CHST_ERRID);
      (void) fprintf(ProtocolFile, "\n*** ERROR  ");
      (void) fprintf(ProtocolFile,
		     "CHAIN %s without start rule, line %d, col %d\n\n",
		     chainname,
		     rowOfChain(chptr->chain),
		     colOfChain(chptr->chain));
      chptr->cancelled = TRUE;
      return (FALSE);
   }	/* if */
   /* count number of chain start */
   /* and search for chain starts at terminal symbols */
   startdefcount = 0;
   for (csn = chptr->starts; csn; csn = csn->next)
   {
      if (csn->startacc)
	 startdefcount++;
      else
	 break;
      /* chain must not start at terminal symbol */
      if (torntOfSymb(symbref(csn->symbdid)) == SYMBTERM)
      {
	 print_err(rowOfChainStart(csn->start),
		   colOfChainStart(csn->start),
		   msg_compose_4("CHAIN start at terminal symbol: ",
				 dnameOfSymb(symbref(csn->symbdid)),
				 ".",
				 chainname),
		   CHTS_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
			"chain start at terminal symbol %s, ",
			dnameOfSymb(symbref(csn->symbdid)));
	 (void) fprintf(ProtocolFile,
			"line %d, col %d in production %s\n\n",
			rowOfChainStart(csn->start),
			colOfChainStart(csn->start),
			dnameOfProd(prodref(csn->prodid)));
	 chptr->cancelled = TRUE;
      }	/* if */
   }	/* for */
   /* check number of chain accesses */
   if (!chptr->accesses && !startdefcount)
   {
      print_err(
		rowOfChain(chptr->chain),
		colOfChain(chptr->chain),
		msg_compose_2("No accesses to CHAIN ",chainname), 
		CHACC_ERRID);
      (void) fprintf(ProtocolFile, "\n*** ERROR  ");
      (void) fprintf(ProtocolFile,
		     "no accesses to CHAIN %s, line %d, col %d\n\n",
		     chainname,
		     rowOfChain(chptr->chain),
		     colOfChain(chptr->chain));
      chptr->cancelled = TRUE;
      return (FALSE);
   }	/* if */
   /* count uses and defs of chain attributes */
   /* and search for accesses at terminal symbols */
   defcount = 0;
   usecount = 0;
   for (can = chptr->accesses; can; can = can->next)
   {
      if (can->isdef)
	 defcount++;
      else
	 usecount++;
      /* chain must not lead through terminal symbol */
      if (torntOfSymb(symbref(can->symbdid)) == SYMBTERM)
      {
	 print_err(
		   rowOfChainacc(can->acc),
		   colOfChainacc(can->acc),
		   msg_compose_4("CHAIN access at terminal symbol: ",
				 dnameOfSymb(symbref(can->symbdid)),
				 ".",
				 chainname),
		   CHTS_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
			"chain access at terminal symbol %s, ",
			dnameOfSymb(symbref(can->symbdid)));
	 (void) fprintf(ProtocolFile,
			"line %d, col %d in production %s\n\n",
			rowOfChainacc(can->acc),
			colOfChainacc(can->acc),
			dnameOfProd(prodref(can->prodid)));
	 chptr->cancelled = TRUE;
      }	/* if */
   }	/* for */

   /* check number of definitions */
   if (!(defcount + startdefcount))
   {
      print_err(
		rowOfChain(chptr->chain),
		colOfChain(chptr->chain),
		msg_compose_2("No definitions of CHAIN: ", chainname),
		CHDEF_ERRID);
      (void) fprintf(ProtocolFile, "\n*** ERROR  ");
      (void) fprintf(ProtocolFile,
		     "no definition of CHAIN %s, line %d, col %d\n\n",
		     chainname,
		     rowOfChain(chptr->chain),
		     colOfChain(chptr->chain));
      chptr->cancelled = TRUE;
   }	/* if */
   /* check number of usages */
   if (!usecount)
   {
      (void) fprintf(ProtocolFile, "\n*** WARNING  ");
      (void) fprintf(ProtocolFile,
		     "CHAIN %s started but not used, line %d, col %d\n",
		     chainname,
		     rowOfChain(chptr->chain),
		     colOfChain(chptr->chain));
   }	/* if */
   /* search for using accesses to the left of chain start accesses */
   for (csn = chptr->starts; csn; csn = csn->next)
   {
      if (!csn->startacc)
	 continue;
      for (can = chptr->accesses; can; can = can->next)
      {
	 if (!can->acc)
	    continue;
	 if (csn->prodid == can->prodid
	     && symbnoOfChainacc(can->acc)
	     && symbnoOfChainacc(can->acc)
	     < symbnoOfChainacc(csn->startacc))
	 {
	    print_err(
		      rowOfChainStart(csn->start),
		      colOfChainStart(csn->start),
		      msg_compose_2("Use of chain on the left of CHAINSTART symbol. CHAIN ",
				    chainname),
		      CHST_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "Use of chain on the left of CHAINSTART symbol");
	    (void) fprintf(ProtocolFile,
			   " in line %d, col %d, CHAIN %s\n\n",
			   rowOfChainacc(can->acc),
			   colOfChainacc(can->acc),
			   chainname);
	    chptr->cancelled = TRUE;
	 }	/* if */
      }	/* for */
   }	/* for */
   return (!chptr->cancelled);
}/* check_chain() */

static
#ifdef __STDC__
void
mark_chain(ChainNode chptr)
#else
void
mark_chain(chptr)
   ChainNode chptr;
#endif
/* mark symbols and productions for expansion of CHAIN			 */
{
   ChAccNode chaccptr;
   
   
   if (chptr->cancelled)
      return;

   /* mark chain symbols and productions beginning at the chain accesses */
   for (chaccptr = chptr->accesses; chaccptr; chaccptr = chaccptr->next)
   {
      if (symbnoOfChainacc(chaccptr->acc))
      {
	 /* access symbol is on the rhs */
	 prodflag(chaccptr->prodid) |= target_prod;

	 /* this function will do the rest for us */
	 mark_chain_trans(
			  chaccptr->symbdid,
			  chptr, chaccptr,
			  chaccptr->prodid, TRUE);
      }
      /* if */
      else
      {
	 /* access symbol is on the lhs */
	 /* chain access to lhs symbol in start production */
	 if (prodflag(chaccptr->prodid) & start_prod)
	 {
	    prodflag(chaccptr->prodid) |= target_prod;

	    /* mark symbol if not already marked */
	    if (symbflag(chaccptr->symbdid) == no_sflag)
	    {
	       symbflag(chaccptr->symbdid) = chain_symb;
	       markedsymbs++;
	       gen_chain_attr(
			      chaccptr->symbdid,
			      pregenattrOfChainStart(
						     chptr->starts->start),
			      postgenattrOfChainStart(
						      chptr->starts->start),
			      typeidOfChain(chptr->chain));
	       newattrs += 2;
	    }	/* if */
	 }
	 /* if */
	 /* else start next iteration if production is already marked */
	 else if (prodflag(chaccptr->prodid) != no_pflag)
	 {
	    prodflag(chaccptr->prodid) |= target_prod;
	    continue;
	 }
	 /* else if */
	 /* else mark as access production */
	 else
	 {
	    prodflag(chaccptr->prodid) = trans_prod | target_prod;
	    markedprods++;
	 }	/* else */

	 /* mark symbols and productions for transport */
	 mark_chain_trans(
			  chaccptr->symbdid,
			  chptr, chaccptr,
			  chaccptr->prodid, TRUE);
      }	/* else */
   }	/* for */

/*   protout(ProtocolFile,
	   "\tchain contains %d symbols in %d productions\n",
	   markedsymbs, markedprods);
*/

}/* mark_chain() */

static
#ifdef __STDC__
void
check_chainstarts(ChainNode chptr)
#else
void
check_chainstarts(chptr)
   ChainNode chptr;
#endif
/* search for chain start symbols outside chain paths			 */
{
   ChStNode csn1;
   SNode sn;
   int sno;
   ChAccNode tempacc;

   /* for messages: the name of the CHAIN */
   char *chainname = dnameOfChain(chptr->chain);
   if (chptr->cancelled)
      return;

   /* examine all chain starts */
   for (csn1 = chptr->starts; csn1; csn1 = csn1->next)
   {
      /* search all productions with the start symbol on the rhs */
      for (sn = symbrdown(csn1->symbdid); sn; sn = sn->down)
      {
	 /* production must not be this start production */
	 if (sn->prodid == csn1->prodid)
	    continue;

	 if (prodflag(sn->prodid) == no_pflag)
	 {
	    if (symbflag(prodright(sn->prodid)->symbdid) == no_sflag)
	    {
	       /* no chain path reaches this production */
	       /* so try to mark a path to a chain start production */
	       tempacc = (ChAccNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct ChAccNode));
	       tempacc->acc = csn1->startacc;
	       tempacc->prodid = csn1->prodid;
	       tempacc->symbdid = csn1->symbdid;
	       tempacc->accall = csn1->accall;
	       tempacc->isdef = TRUE;
	       tempacc->next = NULL;
	       mark_chain_trans(
				csn1->symbdid,
				chptr, tempacc,
				sn->prodid, TRUE);
	    }
	    /* if */
	    else
	    {
	       /* chain already runs through lhs of production */
	       /* therefore mark production so that */
	       /* transport rules will be generated */
	       prodflag(sn->prodid) = trans_prod;
	    }	/* else */
	 }	/* if */
      }	/* for */

      /* no marked rhs symbol must occur to the left of the chain start */
      sno = 1;
      for (sn = prodright(csn1->prodid)->right;
	   sn && sno < symbnoOfChainacc(csn1->startacc);
	   sn = sn->right)
      {
	 sno++;
	 if (symbflag(sn->symbdid) != no_sflag)
	 {
	    print_err(
		      rowOfChainStart(csn1->start),
		      colOfChainStart(csn1->start),
		      msg_compose_2("Use of chain on the left of CHAINSTART symbol. CHAIN ",
				    chainname),
		      CHST_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "chain symbol %s to the left of CHAINSTART ",
			   dnameOfSymb(symbref(sn->symbdid)));
	    (void) fprintf(ProtocolFile,
			   "in production %s, line %d, row %d\n\n",
			   dnameOfProd(prodref(csn1->prodid)),
			   rowOfChainStart(csn1->start),
			   colOfChainStart(csn1->start));
	    chptr->cancelled = TRUE;
	    continue;
	 }	/* if */
      }	/* for */

      /* chain start node must be found */
      if (!sn)
      {
	 print_err(0, 0, "expchain.c: internal error #2", NO_ERRID);
	 chptr->cancelled = TRUE;
	 return;
      }	/* if */
   }	/* for */
}/* check_chainstarts */

static
#ifdef __STDC__
void
repl_chainstart(ChStNode csn, int sid, int sno)
#else
void
repl_chainstart(csn, sid, sno)
   ChStNode csn;
   int sid;
   int sno;
#endif
/* replace chain start access by access to inherited chain attribute	 */
/* of the start symbol							 */
{
   Attracc na;
   Attrdef ad;
   Expr expr;

   /* inherited chain attribute of the symbol must be second attribute */
   retrievefirstSEQAttrdef(tailSEQAttrdef(attrsOfSymb(symbref(sid))), ad);
   if (classOfAttrdef(ad) != ATCLINH)
   {
      print_err(0, 0, "expchain.c: internal error #3", NO_ERRID);
      return;
   }	/* if */
   /* build new attribute access */
   na = NAttracc;
   symbnoOfAttracc(na) = sno;
   attridOfAttracc(na) = didOfAttrdef(ad);
   rowOfAttracc(na) = rowOfChainacc(csn->startacc);
   colOfAttracc(na) = colOfChainacc(csn->startacc);
   ExprToAttracc(IDLtempExpr) = na;

   /* chain access must be the first expression of the assignment */
   retrievefirstSEQExpr(paramsOfCall(csn->accall), expr);
   if (typeof(expr) != KChainacc && ExprToChainacc(expr) != csn->startacc)
   {
      print_err(0, 0, "expchain.c: internal error #4", NO_ERRID);
      return;
   }	/* if */
   /* replace access */
   removefirstSEQExpr(paramsOfCall(csn->accall));
   appendfrontSEQExpr(paramsOfCall(csn->accall), IDLtempExpr);
}/* repl_chainstart() */

static
#ifdef __STDC__
void
lhs_chain_assign(ChainNode chptr, Attribution attrib)
#else
void
lhs_chain_assign(chptr, attrib)
   ChainNode chptr;
   Attribution attrib;
#endif
/* generate assignment from inherited chain attribute of the lhs symbol	 */
/* to the synthesized chain attribute of the lhs symbol			 */
{
   int pid;
   int lhsid;
   ChAccNode can;
   Attrdef ad1, ad2;

   pid = prodidOfAttribution(attrib);
   lhsid = prodright(pid)->symbdid;

   /* get definition of synthesized chain attribute */
   retrievefirstSEQAttrdef(
			   attrsOfSymb(symbref(lhsid)), ad1);
   /* get definition of inherited chain attribute */
   retrievefirstSEQAttrdef(tailSEQAttrdef(
					  attrsOfSymb(symbref(lhsid))), ad2);

   /* check if explicit assignment to chain overrides transport */
   if (prodflag(pid) & target_prod)
   {
      /* look for defining chain accesses */
      for (can = chptr->accesses; can; can = can->next)
	 /* check if the access defines the value of the	 */
	 /* chain attribute at the rhs symbol		 */
	 if (can->isdef
	     && can->prodid == pid
	     && symbnoOfChainacc(can->acc) == 0)
	 {
	    protout(ProtocolFile,
		    "      explicit assignment to %s<1>.%s\n",
		    dnameOfSymb(symbref(lhsid)),
		    nameOfAttrdef(ad1));
	    return;
	 }
   }	/* if */
   /* generate assignment for transport */
   protout(ProtocolFile,
	   "      %s<1>.%s = %s<1>.%s\n",
	   dnameOfSymb(symbref(lhsid)),
	   nameOfAttrdef(ad1),
	   dnameOfSymb(symbref(lhsid)),
	   nameOfAttrdef(ad2));
   newassigns++;
   gen_assign(attrib, 0, 0,
	      0, didOfAttrdef(ad1),
	      0, didOfAttrdef(ad2),
	      (typeidOfChain(chptr->chain) == DIDVOID));
}/* lhs_chain_assign() */

static
#ifdef __STDC__
void
l2r_chain_assign(ChainNode chptr, Attribution attrib, int sno, int sid)
#else
void
l2r_chain_assign(chptr, attrib, sno, sid)
   ChainNode chptr;
   Attribution attrib;
   int sno, sid;
#endif
/* generate assignment from inherited chain attribute of the lhs symbol	 */
/* to the inherited chain attribute of a rhs symbol			 */
{
   int pid;
   int lhsid;
   ChAccNode can;
   Attrdef ad1, ad2;

   pid = prodidOfAttribution(attrib);
   lhsid = prodright(pid)->symbdid;

   /* get definition of inherited chain attribute of rhs symbol */
   retrievefirstSEQAttrdef(tailSEQAttrdef(
					  attrsOfSymb(symbref(sid))), ad1);
   /* get definition of inherited chain attribute of lhs symbol */
   retrievefirstSEQAttrdef(tailSEQAttrdef(
					  attrsOfSymb(symbref(lhsid))), ad2);

   /* check if explicit assignment to chain overrides transport */
   if (prodflag(pid) & target_prod)
   {
      /* look for defining chain accesses */
      for (can = chptr->accesses; can; can = can->next)
	 /* check if the access defines the value of the	 */
	 /* chain attribute at the rhs symbol		 */
	 if (can->isdef
	     && can->prodid == pid
	     && symbnoOfChainacc(can->acc) == sno)
	 {
	    protout(ProtocolFile,
		    "      explicit assignment to %s<%d>.%s\n",
		    dnameOfSymb(symbref(sid)),
		    sno + 1,
		    nameOfAttrdef(ad1));
	    return;
	 }	/* if */
   }	/* if */
   /* generate assignment for transport */
   protout(ProtocolFile,
	   "      %s<%d>.%s = %s<1>.%s\n",
	   dnameOfSymb(symbref(sid)),
	   sno + 1,
	   nameOfAttrdef(ad1),
	   dnameOfSymb(symbref(lhsid)),
	   nameOfAttrdef(ad2));
   newassigns++;
   gen_assign(attrib, 0, 0,
	      sno, didOfAttrdef(ad1),
	      0, didOfAttrdef(ad2),
	      (typeidOfChain(chptr->chain) == DIDVOID));
}/* l2r_chain_assign() */

static
#ifdef __STDC__
void
r2r_chain_assign(ChainNode chptr, Attribution attrib,
		 int sno1, int sid1,
		 int sno2, int sid2)
#else
void
r2r_chain_assign(chptr, attrib, sno1, sid1, sno2, sid2)
   ChainNode chptr;
   Attribution attrib;
   int sno1, sid1, sno2, sid2;
#endif
/* generate assignment from synthesized chain attribute of a rhs symbol	 */
/* to the inherited chain attribute of the next rhs symbol		 */
{
   int pid;
   ChAccNode can;
   Attrdef ad1, ad2;

   pid = prodidOfAttribution(attrib);

   /* get definition of synthesized chain attribute */
   retrievefirstSEQAttrdef(
			   attrsOfSymb(symbref(sid1)), ad1);
   /* get definition of inherited chain attribute */
   retrievefirstSEQAttrdef(tailSEQAttrdef(
					  attrsOfSymb(symbref(sid2))), ad2);

   /* check if explicit assignment to chain overrides transport */
   if (prodflag(pid) & target_prod)
   {
      /* look for defining chain accesses */
      for (can = chptr->accesses; can; can = can->next)
	 /* check if the access defines the value of the	 */
	 /* chain attribute at the rhs symbol		 */
	 if (can->isdef
	     && can->prodid == pid
	     && symbnoOfChainacc(can->acc) == sno2)
	 {
	    protout(ProtocolFile,
		    "      explicit assignment to %s<%d>.%s\n",
		    dnameOfSymb(symbref(sid2)),
		    sno2 + 1,
		    nameOfAttrdef(ad2));
	    return;
	 }	/* if */
   }	/* if */
   /* generate assignment for transport */
   protout(ProtocolFile,
	   "      %s<%d>.%s = %s<%d>.%s\n",
	   dnameOfSymb(symbref(sid2)),
	   sno2 + 1,
	   nameOfAttrdef(ad2),
	   dnameOfSymb(symbref(sid1)),
	   sno1 + 1,
	   nameOfAttrdef(ad1));
   newassigns++;
   gen_assign(attrib, 0, 0,
	      sno2, didOfAttrdef(ad2),
	      sno1, didOfAttrdef(ad1),
	      (typeidOfChain(chptr->chain) == DIDVOID));
}/* r2r_chain_assign() */

static
#ifdef __STDC__
void
r2l_chain_assign(ChainNode chptr, Attribution attrib, int sno, int sid)
#else
void
r2l_chain_assign(chptr, attrib, sno, sid)
   ChainNode chptr;
   Attribution attrib;
   int sno, sid;
#endif
/* generate assignment from synthesized chain attribute of the last rhs	 */
/* symbol to the synthesized chain attribute of the lhs symbol		 */
{
   int pid;
   int lhsid;
   ChAccNode can;
   Attrdef ad1, ad2;

   pid = prodidOfAttribution(attrib);
   lhsid = prodright(pid)->symbdid;

   /* get definition of synthesized chain attribute of the rhs symbol */
   retrievefirstSEQAttrdef(attrsOfSymb(symbref(sid)), ad1);
   /* get definition of synthesized chain attribute of the lhs symbol */
   retrievefirstSEQAttrdef(attrsOfSymb(symbref(lhsid)), ad2);

   /* check if explicit assignment to chain overrides transport */
   if (prodflag(pid) & target_prod)
   {
      /* look for defining chain accesses */
      for (can = chptr->accesses; can; can = can->next)
	 /* check if the access defines the value of the	 */
	 /* chain attribute at the rhs symbol		 */
	 if (can->isdef
	     && can->prodid == pid
	     && symbnoOfChainacc(can->acc) == 0)
	 {
	    protout(ProtocolFile,
		    "      explicit assignment to %s<1>.%s\n",
		    dnameOfSymb(symbref(lhsid)),
		    nameOfAttrdef(ad2));
	    return;
	 }	/* if */
   }	/* if */
   /* generate assignment for transport */
   protout(ProtocolFile,
	   "      %s<1>.%s = %s<%d>.%s\n",
	   dnameOfSymb(symbref(lhsid)),
	   nameOfAttrdef(ad2),
	   dnameOfSymb(symbref(sid)),
	   sno + 1,
	   nameOfAttrdef(ad1));
   newassigns++;
   gen_assign(attrib, 0, 0,
	      0, didOfAttrdef(ad2),
	      sno, didOfAttrdef(ad1),
	      (typeidOfChain(chptr->chain) == DIDVOID));
}/* r2l_chain_assign() */

static
#ifdef __STDC__
void
gen_start_links(ChainNode chptr, Attribution attrib)
#else
void
gen_start_links(chptr, attrib)
   ChainNode chptr;
   Attribution attrib;
#endif
/* generate link assignments for productions with CHAINSTART rule	 */
{
   int pid;
   ChStNode csn;
   SNode sn1, sn2;
   int sno1, sno2;
   int first;

   pid = prodidOfAttribution(attrib);
   if (EXP_PROT)
     { protout(ProtocolFile, "   RULE ");
       prot_rule(ProtocolFile, pid);
     }

   /* search for chain start node */
   for (csn = chptr->starts; csn; csn = csn->next)
   {
      if (csn->prodid == pid)
	 break;
   }	/* for */
   if (!csn)
   {
      /* this case should never occur */
      print_err(0, 0, "expchain.c: internal error #5", NO_ERRID);
      prodflag(pid) = no_pflag;
   }	/* if */
   protout(ProtocolFile,
	   "      CHAINSTART at symbol %s\n",
	   dnameOfSymb(symbref(csn->symbdid)));

   /* replace chain start access */
   sno2 = symbnoOfChainacc(csn->startacc);
   repl_chainstart(csn, csn->symbdid, sno2);

   /* search for start symbol node */
   sno2 = 1;
   for (sn2 = prodright(pid)->right;
	sno2 < symbnoOfChainacc(csn->startacc);
	sn2 = sn2->right)
   {
      sno2++;
   }	/* for */

   /* link chain from above */
   if (symbflag(prodright(pid)->symbdid) != no_sflag)
   {
      protout(ProtocolFile,
	      "      shielded chain through lhs symbol %s\n",
	      dnameOfSymb(symbref(prodright(pid)->symbdid)));
      lhs_chain_assign(chptr, attrib);
   }	/* if */
   /* generate transport assignments for all marked rhs symbols */
   first = TRUE;
   do
   {
      sn1 = sn2;
      sno1 = sno2;
      /* search next marked symbol */
      do
      {
	 sn2 = sn2->right;
	 sno2++;
      } while (sn2 && symbflag(sn2->symbdid) == no_sflag);

      /* link chain from last marked symbol */
      if (sn2)
      {
	 if (first)
	 {
	    first = FALSE;
/*	    protout(ProtocolFile, "\t\tchain symbols:\n");
*/
	 }	/* if */
/*	 protout(ProtocolFile, "\t\t\t%s<%d>\n",
		 dnameOfSymb(symbref(sn1->symbdid)),
		 sno1 + 1);
*/
	 r2r_chain_assign(
			  chptr, attrib,
			  sno1, sn1->symbdid,
			  sno2, sn2->symbdid);
      }	/* if */
   } while (sn2);
/*   if (!first)
      protout(ProtocolFile, "\t\t\t%s<%d>\n",
	      dnameOfSymb(symbref(sn1->symbdid)),
	      sno1 + 1);
*/
}/* gen_start_links() */

static
#ifdef __STDC__
void
gen_trans_links(ChainNode chptr, Attribution attrib)
#else
void
gen_trans_links(chptr, attrib)
   ChainNode chptr;
   Attribution attrib;
#endif
/* generate transport assignments for all marked CHAIN symbols		 */
{
   int pid;
   SNode sn1, sn2;
   int sno1, sno2;

   pid = prodidOfAttribution(attrib);
   if (EXP_PROT)
     { protout(ProtocolFile, "   RULE ");
       if (EXP_PROT)prot_rule(ProtocolFile, pid);
     }

   /* generate transport assignments for all marked symbols */
   sno2 = 0;

   sn1 = prodright(pid);
   /* search first marked symbol on the right hand side */
   for (sn2 = sn1->right; sn2; sn2 = sn2->right)
   {
      sno2++;
      if (symbflag(sn2->symbdid) != no_sflag)
	 break;
   }	/* for */
   if (!sn2)
   {
      /* no marked symbols on the rhs */
/*      protout(ProtocolFile, "\t\tchain through lhs symbol %s\n",
	      dnameOfSymb(symbref(prodright(pid)->symbdid)));
*/
      lhs_chain_assign(chptr, attrib);
      return;
   }	/* if */
   /* generate transport from lhs symbol to first marked rhs symbol */
/*   protout(ProtocolFile, "\t\tchain symbols:\n");
     protout(ProtocolFile, "\t\t\t%s<%d>\n",
	   dnameOfSymb(symbref(sn2->symbdid)),
	   sno2 + 1);
*/
   l2r_chain_assign(chptr, attrib, sno2, sn2->symbdid);

   /* generate transport assignments for all marked rhs symbols */
   do
   {
      sn1 = sn2;
      sno1 = sno2;
      /* search next marked symbol */
      do
      {
	 sn2 = sn2->right;
	 sno2++;
      } while (sn2 && symbflag(sn2->symbdid) == no_sflag);

      /* link chain from last marked symbol */
      if (sn2)
      {
/*	 protout(ProtocolFile, "\t\t\t%s<%d>\n",
		 dnameOfSymb(symbref(sn2->symbdid)),
		 sno2 + 1);
*/
	 r2r_chain_assign(
			  chptr, attrib,
			  sno1, sn1->symbdid,
			  sno2, sn2->symbdid);
      }	/* if */
   } while (sn2);

   /* generate transport from last marked rhs symbol to lhs symbol */
   r2l_chain_assign(chptr, attrib, sno1, sn1->symbdid);
}/* gen_trans_links() */


static
#ifdef __STDC__
void
gen_chain_links(ChainNode chptr)
#else
void
gen_chain_links(chptr)
   ChainNode chptr;
#endif
/* generate assignments to link the chain through marked productions	 */
{
   SEQAttribution tmp;
   Attribution attrib;
   int pid;

   if (chptr->cancelled)
      return;

   newassigns = 0;
   /* walk through all attributions */
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp, attrib)
   {
      pid = prodidOfAttribution(attrib);
      if (prodflag(pid) == no_pflag)
      {
	 /* link chain from above */
	 if (symbflag(prodright(pid)->symbdid) != no_sflag)
	 {
	   
	   if (EXP_PROT)
	     { protout(ProtocolFile, "   RULE ");
	       prot_rule(ProtocolFile, pid);
	     }
	   lhs_chain_assign(chptr, attrib);
	 }	/* if */
       }
      /* if */
      else if (prodflag(pid) & start_prod)
      {
	 gen_start_links(chptr, attrib);
	 if (chptr->cancelled)
	    return;
      }
      /* if */
      else if (prodflag(pid) & trans_prod)
      {
	 gen_trans_links(chptr, attrib);
      }	/* if */
      prodflag(pid) = no_pflag;
   }	/* foreachinSEQAttribution */
/*   protout(ProtocolFile, "\tnew assignments for CHAIN expansion: %d\n",
	   newassigns);
*/
}/* gen_chain_links() */

static
#ifdef __STDC__
void
repl_chaccs(ChainNode chptr)
#else
void
repl_chaccs(chptr)
   ChainNode chptr;
#endif
/* expand all CHAIN accesses for this chain				 */
{
   ChAccNode can;
   Attracc na;
   Attrdef ad;
   SEQExpr se;
   Expr expr, nextexpr;

   if (chptr->cancelled)
      return;

   /* protout(ProtocolFile, "Replacing accesses to CHAIN %s:\n",
	   dnameOfChain(chptr->chain)); */

   /* walk through all accesses */
   for (can = chptr->accesses; can; can = can->next)
   {
      /* get the did of the appropriate chain attribute */
      if ((symbnoOfChainacc(can->acc) && can->isdef)
	  || (!symbnoOfChainacc(can->acc) && !can->isdef))
      {
	 /* assignment to chain on rhs symbol	 */
	 /* or use of chain on lhs symbol	 */
	 /* so use inherited chain attribute	 */
	 retrievefirstSEQAttrdef(tailSEQAttrdef(
				   attrsOfSymb(symbref(can->symbdid))), ad);
      }
      /* if */
      else
      {
	 /* assignment to chain on lhs symbol	 */
	 /* or use of chain on rhs symbol	 */
	 /* so use synthesized chain attribute	 */
	 retrievefirstSEQAttrdef(
				 attrsOfSymb(symbref(can->symbdid)), ad);
      }	/* else */

      /* build new attribute access */
      na = NAttracc;
      symbnoOfAttracc(na) = symbnoOfChainacc(can->acc);
      attridOfAttracc(na) = didOfAttrdef(ad);
      rowOfAttracc(na) = rowOfChainacc(can->acc);
      colOfAttracc(na) = colOfChainacc(can->acc);
      ExprToAttracc(IDLtempExpr) = na;

/*      protout(ProtocolFile,"   RULE ");
      if (EXP_PROT)
	prot_rule(ProtocolFile, can->prodid);
      protout(ProtocolFile,"      ");
      if (EXP_PROT)
	prot_position(ProtocolFile, 
		    rowOfChainacc(can->acc),
		    colOfChainacc(can->acc));
      protout(ProtocolFile,
	      "         access to attribute %s<%d>.%s\n",
	      dnameOfSymb(symbref(can->symbdid)),
	      symbnoOfChainacc(can->acc) + 1,
	      nameOfAttrdef(ad));

*/
      /* replace access */
      retrievefirstSEQExpr(paramsOfCall(can->accall), expr);
      if (typeof(expr) == KChainacc
	  && ExprToChainacc(expr) == can->acc)
      {
	 removefirstSEQExpr(paramsOfCall(can->accall));
	 appendfrontSEQExpr(
			    paramsOfCall(can->accall),
			    IDLtempExpr);
      }
      /* if */
      else
      {
	 /* search previous expression */
	 foreachinSEQExpr(paramsOfCall(can->accall), se, expr)
	 {
	    if (emptySEQExpr(tailSEQExpr(se)))
	    {
	       print_err(0, 0,
			 "expchain.c: internal error #6",
			 NO_ERRID);
	       return;
	    }	/* if */
	    retrievefirstSEQExpr(tailSEQExpr(se), nextexpr);
	    if (typeof(nextexpr) == KChainacc
		&& ExprToChainacc(nextexpr) == can->acc)
	    {
	       break;
	    }	/* if */
	 }	/* foreachinSEQExpr */
	 removefirstSEQExpr(se->next);
	 appendfrontSEQExpr(se->next, IDLtempExpr);
      }	/* else */
   }	/* for */
}/* repl_chaccs() */

static
#ifdef __STDC__
void
del_chaindefs(void)
#else
void
del_chaindefs()
#endif
/* delete all chain definitions						 */
{
   Def def;
   SEQDef temp, last;
   int found;

   last = defseqOfAttrEval(IdlStruct);

   do
   {
      found = FALSE;
      /* search next chain definition */
      foreachinSEQDef(last, temp, def)
      {
	 if (typeof(def) == KChain)
	 {
	    found = TRUE;
	    break;
	 }	/* if */
	 last = temp;
      }	/* foreachinSEQDef */
      if (found)
      {
	 if (last == defseqOfAttrEval(IdlStruct))
	 {
	    removefirstSEQDef(defseqOfAttrEval(IdlStruct));
	    last = defseqOfAttrEval(IdlStruct);
	 }
	 /* if */
	 else
	 {
	    removeSEQDef(last, def);
	 }	/* else */
      }	/* if */
   } while (found);
}/* del_chaindefs() */

static
#ifdef __STDC__
void
del_chainstarts(void)
#else
void
del_chainstarts()
#endif
/* delete all chain start rules						 */
{
   SEQAttribution tmp1;
   Attribution attrib;
   SEQAttrrule tmp2;
   Attrrule rule;
   int found;

   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp1, attrib)
   {
      do
      {
	 found = FALSE;
	 /* search next chain start rule */
	 foreachinSEQAttrrule(
			      attrrulesOfAttribution(attrib), tmp2, rule)
	 {
	    if (typeof(rule) == KChainStart)
	    {
	       found = TRUE;
	       break;
	    }	/* if */
	 }	/* foreachinSEQAttrrule */
	 if (found)
	 {
	    removeSEQAttrrule(attrrulesOfAttribution(attrib), rule);
	 }	/* if */
      } while (found);
   }	/* foreachinSEQAttribution */
}/* del_chainstarts() */

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
void
find_chains(void)
#else
void
find_chains()
#endif
/* find all CHAIN definitions, CHAINSTART constructs and CHAIN accesses	 */
{
   SEQDef tmp1;
   Def def;
   SEQAttribution tmp2;
   Attribution attrib;
   SEQAttrrule tmp3;
   Attrrule rule;

   /* search all CHAIN definitions */
   chains = (ChainNode) NULL;
   chaincount = 0;
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp1, def)
   {
      if (typeof(def) == KChain)
      {
	 ins_new_chain(DefToChain(def));
      }	/* if */
   }	/* foreachinSEQDef */

   /* search for CHAINSTART constructs and CHAIN accesses */
   foreachinSEQAttribution(attrrulesOfAttrEval(IdlStruct), tmp2, attrib)
   {
      foreachinSEQAttrrule(attrrulesOfAttribution(attrib), tmp3, rule)
      {
	 switch (typeof(rule))
	 {
	 case KChainStart:
	    ins_chainstart(
			   AttrruleToChainStart(rule),
			   prodidOfAttribution(attrib));
	    break;
	 case KCall:
	    chain_in_call(
			  AttrruleToCall(rule),
			  prodidOfAttribution(attrib));
	    break;
	 }	/* switch */
      }	/* foreachinSEQAttrrule */
   }	/* foreachinSEQAttribution */

/*
   switch (chaincount)
   {
   case 0:
      (void) fprintf(ProtocolFile, "\nNo CHAINs found\n");
      break;
   case 1:
      (void) fprintf(ProtocolFile, "\nOne CHAIN found\n");
      break;
   default:
      (void) fprintf(ProtocolFile,
		     "\n%d CHAINs found\n", chaincount);
   }
*/

}/* find_chains() */

#ifdef __STDC__
void
expand_chains(void)
#else
void
expand_chains()
#endif
/* expand all CHAIN constructs						 */
{
   ChainNode chptr1;
   OptList asl;
   int allassigns;

   if (!chaincount)
      return;

   newattrs = 0;
   allassigns = 0;
   protout(ProtocolFile, "\nExpanding CHAINs\n");
   protout(ProtocolFile, "-----------------\n");
   /* examine all chain constructs in the list */
   for (chptr1 = chains; chptr1; chptr1 = chptr1->next)
   {
      /* prepare entry for optim option */
      attrspez = (OptOption) middle_Malloc(__FILE__, __LINE__, sizeof(struct _optimoption));
      if (!attrspez)
	 deadly("expand: out of memory\n");
      attrspez->flag = attr_group_var;
      attrspez->attrs = NULL;

      clear_psflags();
      markedsymbs = 0;
      markedprods = 0;

      find_startaccs(chptr1);

      if (EXP_PROT)
	 show_chain(chptr1);

      if (!check_chain(chptr1))
	 continue;

      mark_chain(chptr1);
      check_chainstarts(chptr1);
      protout(ProtocolFile,"CHAIN transports:\n");

      gen_chain_links(chptr1);
      allassigns += newassigns;
      repl_chaccs(chptr1);

     if (!(typeidOfChain(chptr1->chain) == DIDVOID ||
	   typeidOfChain(chptr1->chain) == DIDVOLI))
     {/* append grouping-option for optim */
      asl = (OptList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _optlist));
      if (!asl)
	 deadly("expand: out of memory\n");
      asl->next = optim_opts->opt_opts;
      asl->entry = attrspez;
      optim_opts->opt_opts = asl;
     }
   }	/* for */

   /* remove definitions of the chains */
   del_chaindefs();
   /* remove start rules of the chains */
   del_chainstarts();
   
   fprintf(ProtocolFile, "\nCHAIN Expansion Summary\n");
   fprintf(ProtocolFile, "========================\n");
   fprintf(ProtocolFile, "   Number of expanded CHAINs:  %d\n",
	   chaincount);
   fprintf(ProtocolFile, "   Number of new attributes:   %d\n",
	   newattrs);
   fprintf(ProtocolFile, "   Number of new computations: %d\n",
	   allassigns);
}/* expand_chains() */

/***********************\
* end of expchain.c	*
\***********************/

/* HaDeS */
