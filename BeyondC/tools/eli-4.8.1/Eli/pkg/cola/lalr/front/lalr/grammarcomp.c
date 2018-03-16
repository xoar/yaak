/*
** $Id: grammarcomp.c,v 1.10 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: grammarcomp.c,v 1.10 1997/08/29 08:38:08 mjung Exp $";

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

/***************************************************************************/
/* File: grammarcomp.c	First Edit: 18.11.88	  Last Edit: 17.02.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	01.09.89 	From: Kalle				   */
/* 		16.02.90	From: Kalle				   */
/***************************************************************************/

/* TABLE OF CONTENTS:
 *
 *	SECTION 1: Implementation of 'cmrtl_compute_startprod()' and its
 *		   auxliary-functions
 *	SECTION 2: Implementation of 'cmrtl_reachibility()' and its
 *		   auxliary-functions
 *	SECTION 3: Implementation of 'cmrtl_partitial_ruleorder()' and its
 *		   auxliary-functions
 * 	SECTION 4: Implementation of 'cmrtl_grammar_comp()'
 */

#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "comarMacros.h"
#include "comar_func.h"
#include "cmrlib.h"
#include "name.h"
#include "privatlib.h"
#include "first1.h"
#include "format.h"			/* for print_prod() */
#include "grammarcomp.h"

p_prod	STARTPROD = NULL;

#ifndef EINS
#define EINS 1
#endif


/* SECTION 1: Implementation of 'cmrtl_compute_startprod()' and its
 *	      auxliary-functions
 */

Boolean	isinrhs(u_seq, el)
SEQunit	u_seq;
DID	el;
{
  SEQunit	travel;
  unit		un;

  foreachinSEQunit(u_seq, travel, un)
    switch ( typeof(un) )
      {
	case Kp_elunit	:
		if ( un.Vp_elunit->did == el )
		  return(TRUE);
		break;
	case Kp_alt	:
		if (isinrhs(un.Vp_alt->rhs1,el) || isinrhs(un.Vp_alt->rhs2,el))
		  return(TRUE);
		break;
	case Kp_opt	:
		if ( isinrhs(un.Vp_opt->rhs, el) )
		  return(TRUE);
		break;
	case Kp_plus	:
		if ( isinrhs(un.Vp_plus->rhs, el) )
		  return(TRUE);
		break;
	case Kp_star	:
		if ( isinrhs(un.Vp_star->rhs, el) )
		  return(TRUE);
		break;
	case Kp_delrep	:
		if ( isinrhs(un.Vp_delrep->rhs, el)
					|| isinrhs(un.Vp_delrep->sep, el) )
		  return(TRUE);
		break;
#ifdef DEBUG_GRC
	default: INT_TAG_ERR("isinrhs()", typeof(un));
#endif
	}		/* end of switch and foreach */
  return(FALSE);
}		/* end of isinrhs() */



ERR	check_startprod(startprod)
p_prod	* startprod;
{
  SEQdef_entry	travel1, travel2;
  def_entry	nt, prod;
  SEQdef_entry	startsymbols = NULL;
  int		lhsnumb;
  Boolean	isstart, oneprod = FALSE;

  foreachinSEQdef_entry(NTERM_SEQ, travel1, nt)
    {
      lhsnumb = 0;
      isstart = TRUE;

#ifdef DEBUG_GRC
      if ( typeof(nt) != Kp_nterm )
	INT_TAG_ERR("check_startprod_1()", typeof(nt));
#endif

      foreachinSEQdef_entry(PROD_SEQ, travel2, prod)
	{
	  if (prod.Vp_prod->lhsdid == nt.Vp_nterm->did)
	    lhsnumb++;
	  isstart = ! isinrhs(prod.Vp_prod->rhs, (DID)nt.Vp_nterm->did);
	  if ( !isstart )
	    break;
	}		/* end of foreachinSEQdef_entry(PROD_SEQ,...) */

      if ( isstart && lhsnumb )
	{
	  appendfrontSEQdef_entry(startsymbols, nt);
	  if ( lhsnumb == 1 )
	    oneprod = TRUE;
	}
    }		/* end of foreachinSEQdef_entry(NTERM_SEQ,...) */

  if ( lengthSEQdef_entry(startsymbols) == 1 )
    {
      retrievefirstSEQdef_entry(startsymbols, nt);
      removefirstSEQdef_entry(startsymbols);

      if ( oneprod )
      {
	retrievefirstSEQdef_entry(PRODWITHLHS[INDEX[nt.Vp_nterm->did]], prod);
	*startprod = prod.Vp_prod;
	if ( !cmrlib_isbnfprod(*startprod) )
	  return(ST_NOTBNFSTPROD);
      }
      else
      {
	foreachinSEQdef_entry(PRODWITHLHS[INDEX[nt.Vp_nterm->did]],
			      travel1, prod)
	{
	  print_prod(CMR, prod.Vp_prod->did, stderr);
	}
	return(ST_AMBSTPROD);
      }
      return(CMR_SUCCESS);
    }
  else if ( emptySEQdef_entry(startsymbols) )
    return(ST_NOSTSYM);
  else
    {
      fprintf(stderr, "Several possible startsymbols are found:\n\t");
      priv_printdefseq(startsymbols);
      fprintf(stderr, ".\n\n");

      return(ST_AMBSTSYM);
    }

}		/* end of check_startprod() */

ERR	check_eofsymb(startprod)
p_prod	startprod;
{
  unit		un;
  SEQunit	u_travel;
  SEQunit	*unptr;
  p_term	eofterm	= (p_term)NULL;
  SEQdef_entry	eofseq;
  SEQdef_entry	travel;
  def_entry	prod, term;
  symb_entry	symb;

  symb.Vp_string = cmrlib_newstring(STOP);

  foreachinSEQdef_entry(TERM_SEQ, travel, term)
    if ( cmrlib_sidtoprop(term.Vp_term->prop, symb.IDLclassCommon->sid) )
      {
	eofterm = term.Vp_term;
	break;
      }

  if ( eofterm )  /* eof-symbol is defined */
    {
      manipulSEQunit(startprod->rhs, unptr, un)
	if ( un.Vp_elunit->did == eofterm->did )
	  break;

      if ( emptySEQunit(*unptr) )
	{
	  un.Vp_elunit = Mkp_elunit(eofterm->did);
	  appendfrontSEQunit(*unptr, un);
	}
      else
        foreachinSEQunit(tailSEQunit((*unptr)), u_travel, un)
          switch ( typeof(DEFTBL[un.Vp_elunit->did]) )
	    {
	    case Kp_term  : return(ST_EOFERR);
	    case Kp_nterm : return(ST_EOFNOTERM);
	    case Kp_other : break;
#ifdef DEBUG_GRC
	    default	: INT_TAG_ERR("check_eofsymb",
				      typeof(DEFTBL[un.Vp_elunit->did]));
#endif
	    }
    }  /* end of if then */
  else  /* taking last symbol of production as eof-symbol */
    foreachinSEQunit(startprod->rhs, u_travel, un)
      {
#ifdef DEBUG_GRC
        if ( typeof(un) != Kp_elunit )
          INT_TAG_ERR("check_eofsymb", typeof(un));
#endif
        switch ( typeof(DEFTBL[un.Vp_elunit->did]) )
	  {
	    case Kp_term  : eofterm = DEFTBL[un.Vp_elunit->did].Vp_term;
			    break;
	    case Kp_nterm : eofterm = (p_term)NULL;
	    case Kp_other : break;
#ifdef DEBUG_GRC
	    default	: INT_TAG_ERR("check_eofsymb",
				      typeof(DEFTBL[un.Vp_elunit->did]));
#endif
	  }
      }  /* end of for and else */

  term.Vp_term = eofterm;
  if ( eofterm	== (p_term)NULL)
    return(ST_EOFNOTERM);
  else
    (void)cmrlib_newprop(term, symb.IDLclassCommon->sid);

  /* Checking the eof-symbol */
  eofseq = cmrlib_sidtoterms(TERM_SEQ, eofterm->sid);
  if ( lengthSEQdef_entry(eofseq) != EINS )
    {
      return(ST_AMBEOF);
    }

  foreachinSEQdef_entry(PROD_SEQ, travel, prod)
    {
#ifdef DEBUG_GRC
          if ( typeof(prod) != Kp_prod )
	    INT_TAG_ERR("check_eofsymb()", typeof(prod));
#endif
      if ( isinrhs(prod.Vp_prod->rhs, eofterm->did)
	   && prod.Vp_prod != startprod )
	return(ST_EOFERR);
    }

    return(CMR_SUCCESS);
}		/* end of check_eofsymb() */


void	MarkAsStart(prod)
p_prod	prod;
{
  p_string	symbol;
  def_entry	def;

  symbol = cmrlib_newstring(START);
  def.Vp_prod = prod;
  (void)cmrlib_newprop(def,symbol->sid);

  return;
}  /* end of MarkAsStart() */


ERR	cmrtl_compute_startprod(c, startprod)
p_comar c;
p_prod	* startprod;
{
  p_comar	sav;
  ERR		stat;

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  *startprod = NULL;
  stat = check_startprod(startprod);

  if ( stat == CMR_SUCCESS )
    stat = check_eofsymb(*startprod);

  if ( stat == CMR_SUCCESS )
    MarkAsStart(*startprod);

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return(stat);

}		/* end of compute_startprod() */



/* SECTION 2: Implementation of 'cmrtl_reachibility()' and its
 *	      auxliary-functions
 */

/* definition of global used variables and their types */
typedef Boolean	*Boolarrtype;
Boolarrtype	reached;


SEQunit	flatten(u_seq, firstcall)
SEQunit	u_seq;
int firstcall;
{
  static  SEQunit  res;
  SEQunit	travel;
  unit		un;

  if ( firstcall )
    initializeSEQunit(res);
  foreachinSEQunit(u_seq, travel, un)
    switch ( typeof(un) )
      {
	case Kp_elunit	: appendfrontSEQunit(res, un);
			  break;
	case Kp_alt	: (void)flatten(un.Vp_alt->rhs1, FALSE);
			  (void)flatten(un.Vp_alt->rhs2, FALSE);
			  break;
	case Kp_opt	: (void)flatten(un.Vp_opt->rhs, FALSE);
			  break;
	case Kp_plus	: (void)flatten(un.Vp_plus->rhs, FALSE);
			  break;
	case Kp_star	: (void)flatten(un.Vp_star->rhs, FALSE);
			  break;
	case Kp_delrep	: (void)flatten(un.Vp_delrep->rhs, FALSE);
			  (void)flatten(un.Vp_delrep->sep, FALSE);
			  break;
#ifdef DEBUG_GRC
	default: INT_TAG_ERR("flatten()", typeof(un));
#endif
      }

  return(res);
}		/* end of flatten() */


void	compute_reached(maxind, startdid)
Indextype	maxind;
DID		startdid;
{
  Indextype	ntind;
  shstacktype	stack;
  SEQdef_entry	d_travel;
  def_entry	prod;
  SEQunit	u_travel;
  unit		un;

  if ( (reached = (Boolarrtype)calloc(maxind, sizeof(Boolean))) == NULL )
    {
      INT_ALLOC_ERR("compute_reached()");
      exit(1);
    }

  ntind = INDEX[startdid];
  reached[ntind] = TRUE;
  stack = shcreate();
  stack = shpush(stack, (sheltype)ntind);

  while ( ! shempty(stack) )
    {
      ntind = (Indextype)shtop(stack);
      stack = shpop(stack);
      foreachinSEQdef_entry(PRODWITHLHS[ntind], d_travel, prod)
	{
#ifdef DEBUG_GRC
          if ( typeof(prod) != Kp_prod )
	    INT_TAG_ERR("compute_reached()", typeof(prod));
#endif
	  foreachinSEQunit(flatten(prod.Vp_prod->rhs, TRUE), u_travel, un)
	    {
	      if ( typeof(DEFTBL[un.Vp_elunit->did]) == Kp_nterm )
		if ( ! reached[(ntind = INDEX[un.Vp_elunit->did])] )
		  {
		    reached[ntind] = TRUE;
		    stack = shpush(stack, (sheltype)ntind);
		  }
	     }	/* end of foreachinSEQunit() */
	}	/* end of foreachinSEQdef_entry() */
    }	/* end of while */
}		/* end of compute_reached() */

SEQdef_entry	compute_notreached()
{
  SEQdef_entry	travel, result = NULL;
  def_entry	nt;

  foreachinSEQdef_entry(NTERM_SEQ, travel, nt)
    if ( ! reached[INDEX[nt.Vp_nterm->did]] )
      appendfrontSEQdef_entry(result, nt);

  return(result);
}		/* end of compute_notreached() */


ERR	cmrtl_reachibility(c, startdid)
p_comar	c;
DID	startdid;
{
  p_comar	sav;
  SEQdef_entry	notreached;

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  if ( typeof(DEFTBL[startdid]) != Kp_nterm )
    return(CMR_UNKERR);
  compute_reached(MAXNTERM, startdid);
  notreached = compute_notreached();

  if ( ! emptySEQdef_entry(notreached) )
    {
      fprintf(stderr, "The following nonterminals are not reachable");
      fprintf(stderr, " from the startsymbol:\n\t");
      priv_printdefseq(notreached);
      fprintf(stderr, ".\n\n");

      return(GR_NOTREACH);
    }

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  free(reached);
  reached = (Boolarrtype)NULL;

  return(CMR_SUCCESS);
}		/* end of cmrtl_reachibility() */


/* SECTION 3: Implementation of 'cmrtl_partitial_ruleorder()' and its
 *	      auxliary-functions
 */


/* return == TRUE	: 'prod' is the default-production
 *	  == FALSE	: 'prod' is not the default-production
 *	  == GR_NOTBNF	: 'prod' is not in BNF
 *	  == GR_NODEFAULT: there exists no DEFAULT-OTHER-object in the
 *			   DEFTABLE or no DEFAULT-SYMBTABLE-entry
 */
int	isdefaultprod(prod)
p_prod	prod;
{
static	p_string	ordername = (p_string)NULL;
  p_prop_val	prop;

  if ( ordername == (p_string)NULL   &&
       (ordername=cmrlib_strtopstring(CMR->symbols, ORDER)) == (p_string)NULL )
    return(GR_NODEFAULT);

  prop = cmrlib_sidtopropval(propOfp_prod(prod), sidOfp_string(ordername));
  return( prop != (p_prop_val)NULL  &&
	  valOfp_nval(valueTop_nval(valOfp_prop_val(prop))) == 1
	);
}		/* end of isdefaultprod() */

/* copy default production to the first position */
ERR	compute_default_prodseq(orig, copy)
SEQdef_entry	orig;
SEQdef_entry	*copy;
{
  SEQdef_entry	travel, *formanipul;
  def_entry	prod, def;


  initializeSEQdef_entry(*copy);
  if ( emptySEQdef_entry(orig) )
    return(GR_NTHASNOPROD);
  foreachinSEQdef_entry(orig, travel, prod)
  {
    def = Cpdef_entry(prod);
    appendfrontSEQdef_entry(*copy, def);
  }

  manipulSEQdef_entry(*copy, formanipul, prod)
    {
      switch ( isdefaultprod(prod.Vp_prod) )
	{
          case TRUE	   : removefirstSEQdef_entry(*formanipul);
			     appendfrontSEQdef_entry(*copy, prod);
			     return(CMR_SUCCESS);
          case FALSE	   : break;
          case GR_NODEFAULT: return(GR_NODEFAULT);
	}
    }
  return(GR_NODEFAULT);
}		/* end of compute_default_prodseq() */


ERR	changedids(d_seq, old , new)
SEQdef_entry	d_seq;
DID		old;
int		new;
{
  SEQdef_entry	d_travel;
  def_entry	prod;
  SEQunit	u_travel;
  unit		un;

  foreachinSEQdef_entry(d_seq, d_travel, prod)
    {
#ifdef DEBUG_GRC
      if ( typeof(prod) != Kp_prod )
        INT_TAG_ERR("changedids()", typeof(prod));
#endif
      foreachinSEQunit(prod.Vp_prod->rhs, u_travel, un)
	{
	  if ( typeof(un) != Kp_elunit )
	    return(GR_NOTBNF);
	  if ( un.Vp_elunit->did == old )
	    un.Vp_elunit->did = new;
	}
    }
  return(CMR_SUCCESS);
}		/* end of changedids() */


ERR	compute_newdids(d_seq)
SEQdef_entry	d_seq;
{
  def_entry	hd;
  int		lrhs, stat;
  SEQunit	travel;
  unit		un;

  hd = headSEQdef_entry(d_seq);
#ifdef DEBUG_GRC
  if ( typeof(hd) != Kp_prod )
    INT_TAG_ERR("compute_newdids()", typeof(hd));
#endif
  lrhs = -lengthSEQunit(hd.Vp_prod->rhs);
  foreachinSEQunit(hd.Vp_prod->rhs, travel, un)
    {
      if ( typeof(un) != Kp_elunit )
	return(GR_NOTBNF);
      if ( un.Vp_elunit->did > 0  &&
	   typeof(DEFTBL[un.Vp_elunit->did]) == Kp_nterm
	 )
	{
	  if ( (stat = changedids(d_seq, (DID)un.Vp_elunit->did, lrhs))
		!= CMR_SUCCESS )
	    return(stat);
	  un.Vp_elunit->did = lrhs++;
	}
    }
  return(CMR_SUCCESS);
}		/* end of compute_newdids() */


Boolean	compare_lexical(gr,sm)
p_prod	gr, sm; /* type changed from def_entry to p_prod to be compatible */
		/* with function IDLListSort from the IDL-library */
{
  SEQunit	gr_unitseq, sm_unitseq;
  int		gr_unit, sm_unit;
  static int    lhs = 0;
  Boolean	busy = TRUE;
  unit 		un;

  gr_unitseq = gr->rhs;
  sm_unitseq = sm->rhs;
  if ( emptySEQunit(gr_unitseq) || emptySEQunit(sm_unitseq) )
    busy = FALSE;
  while ( busy )
    {
      un = headSEQunit(gr_unitseq);
#ifdef DEBUG_GRC
      if ( typeof(un) != Kp_elunit )
        INT_TAG_ERR("compare_lexical_gr()", typeof(un));
#endif
      gr_unit = un.Vp_elunit->did;
      un = headSEQunit(sm_unitseq);
#ifdef DEBUG_GRC
      if ( typeof(un) != Kp_elunit )
        INT_TAG_ERR("compare_lexical_sm()", typeof(un));
#endif
      sm_unit = un.Vp_elunit->did;

      if ( gr_unit < sm_unit )
	return(FALSE);
      else if ( gr_unit > sm_unit )
	return(TRUE);
      gr_unitseq = tailSEQunit(gr_unitseq);
      sm_unitseq = tailSEQunit(sm_unitseq);
      if ( emptySEQunit(gr_unitseq) || emptySEQunit(sm_unitseq) )
        busy = FALSE;
    }	/* end of while */
  if ( !emptySEQunit(gr_unitseq) )
    return(TRUE);
  if ( !emptySEQunit(sm_unitseq) )
    return(FALSE);

  /* gr and sm must be identical productions */
  if ( lhs != gr->lhsdid )
  {
    priv_generrstr(GR_IDENTRULES, (String)(unsigned long)gr->did);
    lhs = gr->lhsdid;
  }
  return(gr->did >= sm->did);
}		/* end of compare_lexical() */


/* missing declaration( needed for the following sortSEQdef_entry() call*/
pGenList IDLListSort();

void	arrange_lexical(d_seq)
SEQdef_entry	*d_seq;
{
  def_entry	defaultprod;

  if ( emptySEQdef_entry(*d_seq) )
    return;

  defaultprod = headSEQdef_entry(*d_seq);
  removefirstSEQdef_entry(*d_seq);
  sortSEQdef_entry(*d_seq, compare_lexical);
  appendfrontSEQdef_entry(*d_seq, defaultprod);
}		/* end of arrange_lexical() */


ERR	compute_ruleorder(origseq, copyseq)
SEQdef_entry	origseq, copyseq;
{
  int	numb = 1;
  SEQdef_entry	travel;
  def_entry	copyprod, origprod;
  p_prop_val	propval;

static	  SID	orderedsid = 0;

  if ( ! orderedsid )
    orderedsid = (cmrlib_newstring(ORDER))->sid;
  foreachinSEQdef_entry(copyseq, travel, copyprod)
    {
      origprod = cmrlib_getdef(origseq, copyprod.Vp_prod->did);
#ifdef DEBUG_GRC
      if ( origprod.Vp_prod == NULL )
	fprintf(stderr,"Internal Error in compute_ruleorder().\n");
#endif
      propval = cmrlib_sidtopropval(origprod.Vp_prod->prop, orderedsid);
      if ( propval == NULL )
	{
	  value		val;
	  val.Vp_nval = Mkp_nval(numb);
	  propval = cmrlib_newpropval(origprod, orderedsid, val);
	}
      else
	{
	  if ( typeof(propval->val) != Kp_nval )
	    return(GR_ORDER_EXIST);
	  propval->val.Vp_nval->val = numb;
	}
      numb++;
    }	/* end of foreachin... */
  return(CMR_SUCCESS);
}		/* end of compute_ruleorder() */


ERR	cmrtl_partitial_ruleorder(c)
p_comar	c;
{
  p_comar	sav;
  SEQdef_entry	travel, origseq, copyseq;
  def_entry	nt;
  ERR		stat;

#ifdef DEBUG_GRC
  FILE		*test;
  if ( (test = fopen("aus.grc", "w")) == NULL )
    {
      fprintf(stderr, "Datei 'aus.grc' kann nicht eroeffnet werden.\n");
      exit(1);
    }
  fprintf(test, "cmrtl_partitial_ruleorder() startet:\n\n");
#endif

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  foreachinSEQdef_entry(NTERM_SEQ, travel, nt)
    {

#ifdef DEBUG_GRC
      fprintf(test, "Nichtterminal: %d <==> %s\n",
	      nt.Vp_nterm->did, priv_deftostr(nt)
	     );
#endif

      origseq = PRODWITHLHS[INDEX[nt.Vp_nterm->did]];
#ifdef DEBUG_GRC
      fprintf(test, "\tDie Produktionen dieses NT's:\n");
      priv_print_rhsdid(origseq, test);
#endif

      if ((stat = compute_default_prodseq(origseq, &copyseq)) != CMR_SUCCESS)
	return(stat);
#ifdef DEBUG_GRC
      fprintf(test, "\tKopie dieser Produktionen:\n");
      priv_print_rhsdid(copyseq, test);
#endif

      if ( (stat = compute_newdids(copyseq)) != CMR_SUCCESS )
	return(stat);
#ifdef DEBUG_GRC
      fprintf(test, "\tDie Kopie-Produktionen mit neuen dids:\n");
      priv_print_rhsdid(copyseq, test);
#endif

      arrange_lexical(&copyseq);
#ifdef DEBUG_GRC
      fprintf(test, "\tDie Kopie-Produktionen sortiert:\n");
      priv_print_rhsdid(copyseq, test);
      fprintf(test, "\tDie Orig-Produktionen wiederholt:\n");
      priv_print_rhsdid(origseq, test);
#endif

      if ( (stat = compute_ruleorder(origseq, copyseq)) != CMR_SUCCESS )
	return(stat);
#ifdef DEBUG_GRC
      fprintf(test, "\tNochmal die Orig-Produktionen wiederholt:\n");
      priv_print_rhsdid(origseq, test);
#endif

     if ( (stat = cmrlib_rekdelSEQdef_entry(copyseq)) != CMR_SUCCESS )
	return(stat);
    }

#ifdef DEBUG_GRC
      fclose(test);
#endif

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */

  return(CMR_SUCCESS);
}		/* end of cmrtl_partitial_ruleorder() */



/* SECTION 4: Implementation of 'cmrtl_grammar_comp()'  */

ERR cmrtl_grammar_comp(c, start, reach, order)
p_comar	c;
Boolean	start, reach, order;
{
  ERR		stat = CMR_SUCCESS;
  p_comar	sav;

  /* Initializing of imported global variables */
  if ( start || reach || order )
    {
      sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */
      cmrlib_compute_globarrs();
      cmrlib_arrangedefs();
      (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
    }  /* end of if */

  /* executing of the task: computing and checking the startproduction */
  if ( start || reach )
    {
#ifdef DEBUG_GRC
      printf("grcomp: Computing and checking the startproduction.\n");
#endif
      if ((stat = cmrtl_compute_startprod(c, &STARTPROD)) != CMR_SUCCESS)
	return(stat);
    }


  /* executing of the task: checking of being a reduced grammar */
  if ( reach )
    {
#ifdef DEBUG_GRC
      printf("grcomp: Checking the reachibility of every nonterminal.\n");
#endif
      if ( (stat = cmrtl_reachibility(c,STARTPROD->lhsdid)) != CMR_SUCCESS )
	return(stat);
    }
  if ( reach || order )
    {
#ifdef DEBUG_GRC
      printf("grcomp: Checking the terminaliziation of every nonterminal.\n");
#endif
      if ( (stat = cmrtl_first(c,"", ONLY_DEF)) != CMR_SUCCESS )
	return(stat);

      if ( reach )
 	  (void)cmrlib_newstring(REDUCED);	/* Mark grammar as reduced */
    }

  /* executing of the task: computing a partitial order on the productions */
  if ( order )
    {
#ifdef DEBUG_GRC
      printf("grcomp: Computing a partitial order on the productions.\n");
#endif
      if ( (stat = cmrtl_partitial_ruleorder(c)) !=  CMR_SUCCESS )
	return(stat);
    }

  return(CMR_SUCCESS);
}		/*end of cmrtl_grammar_comp() */

