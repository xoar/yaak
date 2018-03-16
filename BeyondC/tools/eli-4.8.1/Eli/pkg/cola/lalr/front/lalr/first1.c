/*
** $Id: first1.c,v 1.7 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: first1.c,v 1.7 1997/08/29 08:38:08 mjung Exp $";

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
/* File: first1.c	First Edit: 27.02.89	  Last Edit: 31.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 24.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "comar.h"
#include "comarMacros.h"
#include "cmrlib.h"
#include "comar_func.h"
#include "cmrio.h"	/* defintion of CMR_OPNERR */
#include "name.h"

#include "format.h"             /* Declaration of print_prod() */

#include "privatlib.h"
#include "bitset.h"
#include "digraph.h"
#include "grammarcomp.h"
#include "first1.h"

#define	MAXLINE	65

/* declarations of local functions */
static  void    initFIRSTSETS();
static  ERR     putFIRSTSETS();
static  ERR     initnullable();
static	void	reinitCounter();
static  ERR     nullable();
static	ERR	defaultrules();
static	void	FreeArrays();
static  void    relation();
static  void    AddEmpty();
static  ERR	AddEpsilon();
static	ERR	first();

/************************************************************************/
/* Implementation of EXPORTED variables and functions			*/
/************************************************************************/

ARRBitSet	FIRSTSETS = (ARRBitSet)NULL;
p_prod		*DEFAULT = (p_prod *)NULL;

ERR	cmrtl_first(c, filename, version)
p_comar	c;
String	filename;
int	version;
{
  p_comar	sav;
  short		stat;
  FILE		*f;
  String	complname;

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  /* Computation of an empty terminal in global not exported variable 'EPS' */
  if ( (stat=AddEpsilon(c))  !=  CMR_SUCCESS )
    return(stat);

  /* Computation of the global variables included from "cmrlib" */
  cmrlib_arrangedefs();
  cmrlib_compute_globarrs();

 /* Initialization of Positionlist and Counter: associate with each
  * nonterminal a list of positions,
  * Determine NW1 = {A | A->. is a rule of G}
  * Determine DW1 = {A | A->x is a rule of G where x is in T*}
  */
  if ( (stat = initnullable(PROD_SEQ)) != CMR_SUCCESS )
    return( stat );

  switch ( version )
  {
    case FIR_AND_DEF:	if ( (stat = defaultrules(c))  !=  CMR_SUCCESS )
			  return(stat);
			reinitCounter();
    case ONLY_FIR:	if ( (stat = first(c))  !=  CMR_SUCCESS )
			  return(stat);
			break;
    case ONLY_DEF:	if ( (stat = defaultrules(c))  !=  CMR_SUCCESS )
			  return(stat);
			break;
    default:		return(FIR_VERSION);
  }  /* of switch */

  /* Frees storage of Positionlist, Counter and NULLABLE */
  FreeArrays();

  if ( *filename != '\0' )
  {
    switch ( version )
    {
      case FIR_AND_DEF:	complname = priv_genfilename(filename, ".default");
			if ( (f = fopen(complname, "w")) == (FILE *)NULL )
			return(CMR_OPNERR);
			if ( (stat = cmrtl_print_default(f,c)) != CMR_SUCCESS )
			  return(stat);
			fclose(f);
      case ONLY_FIR:	complname = priv_genfilename(filename, ".first");
                        if ( (f = fopen(complname, "w")) == (FILE *)NULL )
                        return(CMR_OPNERR);
			if ( (stat = cmrtl_print_first(f,c)) != CMR_SUCCESS )
			  return(stat);
			fclose(f);
			break;
      case ONLY_DEF:	complname = priv_genfilename(filename, ".default");
                        if ( (f = fopen(complname, "w")) == (FILE *)NULL )
                        return(CMR_OPNERR);
			if ( (stat = cmrtl_print_default(f,c)) != CMR_SUCCESS )
			  return(stat);
			fclose(f);
			break;
    }  /* of switch */
  }  /* end of if */

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */

  return(stat);
}  /* end of cmrtl_first() */


ERR	cmrtl_print_first(f,cmr)
FILE	*f;
p_comar	cmr;
{
  p_string	firstname;
  SEQdef_entry	deflist;
  def_entry	def, term;
  symb_entry	symb;
  p_prop_val	firstprop;
  SEQvalue	vallist;
  value		val;
  int		cnt;

  if ( (firstname = cmrlib_strtopstring(cmr->symbols, FIRST1))
		== (p_string)NULL )
	return(FIR_UNK);

  cmrlib_compute_globarrs();

  foreachinSEQdef_entry(definitionsOfp_comar(cmr), deflist, def)
    if ( typeof(def)  ==  Kp_nterm )
    {
	cnt = 0;
	symb = cmrlib_getsymb(symbolsOfp_comar(cmr), sidOfdef_entry(def));
	fprintf(f, "%s:\n\t", strOfsymb_entry(symb));
	if ((firstprop = cmrlib_sidtopropval(propOfdef_entry(def),
                                             (SID)firstname->sid))
            == (p_prop_val)NULL )
        return(FIR_INCOMPL);
	foreachinSEQvalue(listOfp_lval(valueTop_lval(valOfp_prop_val(firstprop))),
			vallist, val)
        {
	  term = DEFTBL[didOfp_dval(valueTop_dval(val))];

#ifdef	DEBUG_FIR
	   /* print only terminals: used in combination with an old
	    * first set computation
	    */
	  if ( typeof(term) == Kp_term )
	  {
#endif
	    symb = cmrlib_getsymb(symbolsOfp_comar(cmr), sidOfdef_entry(term));
	    if ( typeof(symb) == Kp_string )
		cnt += fprintf(f, " '%s'", strOfsymb_entry(symb));
	    else
		cnt += fprintf(f, " %s", strOfsymb_entry(symb));
	    if ( cnt > MAXLINE )
	    {
		cnt = 0;
		fprintf(f, "\n\t");
	    }  /* of if */
#ifdef  DEBUG_FIR
	  }  /* of if */
#endif
	}  /* of for */
	fprintf(f, "\n");
    }  /* of if */

  return(CMR_SUCCESS);
} /* of cmrtl_print_first() */


ERR	cmrtl_print_default(f,cmr)
FILE    *f;
p_comar cmr;
{
  p_string	ordername;
  p_prop_val	prop;
  SEQdef_entry	deflist;
  def_entry	def;

  if ( (ordername=cmrlib_strtopstring(cmr->symbols, TERMINALIZE)) == (p_string)NULL
       || (ordername=cmrlib_strtopstring(cmr->symbols, ORDER)) == (p_string)NULL
     )
        return(GR_NODEFAULT);

  foreachinSEQdef_entry(definitionsOfp_comar(cmr), deflist, def)
    if ( typeof(def)  ==  Kp_prod )
    {
      prop = cmrlib_sidtopropval(propOfdef_entry(def),sidOfp_string(ordername));
      if ( prop != (p_prop_val)NULL  &&
           valOfp_nval(valueTop_nval(valOfp_prop_val(prop))) == 1 )
		print_prod(cmr, didOfdef_entry(def), f);
    }  /* of if */

  return(CMR_SUCCESS);
}  /* of cmrtl_print_default() */


ERR	readFIRSTSETS(c)
p_comar	c;
{
  p_comar	sav;
  p_string	firstname;
  SEQdef_entry	d_travel;
  def_entry	nt;
  p_prop_val	firstprop;
  SEQvalue	v_travel;
  value		val;

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  /* Computation of the global variables included from "cmrlib" */
  cmrlib_arrangedefs();
  cmrlib_compute_globarrs();

  if ( (firstname = cmrlib_strtopstring(c->symbols, FIRST1))
	== (p_string)NULL )
    return(FIR_UNK);

  foreachinSEQdef_entry(NTERM_SEQ, d_travel, nt)
    {
#ifdef DEBUG_FIR
      if ( typeof(nt) != Kp_nterm )
	INT_TAG_ERR("readFIRSTSETS(1)",typeof(nt));
#endif
      if ((firstprop = cmrlib_sidtopropval(nt.Vp_nterm->prop,
					   (SID)firstname->sid))
	    == (p_prop_val)NULL )
	return(FIR_INCOMPL);
      foreachinSEQvalue(firstprop->val.Vp_lval->list, v_travel, val)
	{
#ifdef DEBUG_FIR
          if ( typeof(val) != Kp_dval )
	    INT_TAG_ERR("readFIRSTSETS(2)",typeof(val));
	  if ( typeof( DEFTBL[val.Vp_dval->did]) != Kp_term )
#endif
	    (void)AddElemToSet(INDEX[val.Vp_dval->did],
			       FIRSTSETS[INDEX[nt.Vp_nterm->did]]);
	}  /* end of for */
    }  /* end of for */

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return(CMR_SUCCESS);

}  /* end of readFIRSTSETS() */


void	freeFIRSTSETS()
{
  unsigned short	i;

extern	unsigned short	SIZEFIRSTSETS;	/* defined below */

  for (i=0; i<SIZEFIRSTSETS; i++)
    FreeSet(FIRSTSETS[i]);

  free( (char *)FIRSTSETS );
  FIRSTSETS = (ARRBitSet)NULL;

  return;
}  /* end of freeFIRSTSETS() */

/************************************************************************/
/* Implementation of NOT EXPORTED variables and functions 			*/
/************************************************************************/

unsigned short	SIZEFIRSTSETS = 0;

static	def_entry	EPS; /* already used in cmrtl_first() */

static	void	initFIRSTSETS()
{
  int	i;

  /* creating an array of empty BitSets indexed by nonterminals */
  if ( FIRSTSETS != (ARRBitSet)NULL )
    freeFIRSTSETS();

  SIZEFIRSTSETS = MAXNTERM;
  if ( (FIRSTSETS = (ARRBitSet)malloc(MAXNTERM*sizeof(BitSet)))
        == (ARRBitSet)NULL )
    {
      INT_ALLOC_ERR("initFIRSTSETS()");
      exit(1);
    }
  for (i=0; (Indextype) i<MAXNTERM; i++)
    FIRSTSETS[i] = MakeEmptySet(MAXTERM);

  return;
}


static	ERR	putFIRSTSETS(nterms, first)
SEQdef_entry	nterms;
p_string	first;
{
  SEQdef_entry	deflist;
  def_entry	def;
  SEQvalue	dvalues;
  unsigned short i, no;
  value		val;
  prop_entry	prop;

  /* TermIndexInvers[i] == did <==> INDEX[did] == i */
  DID	*TermIndexInvers; /* TermIndexInvers[0...MAXTERM-1] */

  short	*Terms;		/* Terms[[0...MAXTERM-1] */

  if ( (Terms = (short *)malloc(MAXTERM * sizeof(short)))  ==  (short *)NULL )
  {
    INT_ALLOC_ERR("putFIRSTSETS()");
    exit(1);
  }

  TermIndexInvers = cmrlib_INDEX_Invers(Kp_term);

  foreachinSEQdef_entry(nterms, deflist, def)
  {
    initializeSEQvalue(dvalues);
    no = EvalBitSet(Terms, FIRSTSETS[INDEX[didOfdef_entry(def)]]);
    for (i=0; i<no; i++)
    {
      val.Vp_dval = Mkp_dval(TermIndexInvers[Terms[i]]);
      appendfrontSEQvalue(dvalues, val);
    } /* of for */

    val.Vp_lval = Mkp_lval(dvalues);
    prop.Vp_prop_val = Mkp_prop_val(val);
    prop = Mkprop_entry(didOfdef_entry(def), sidOfp_string(first), prop);
    appendfrontSEQprop_entry(propOfdef_entry(def), prop);
  } /* of for */

  (void)free(Terms);
  (void)free(TermIndexInvers);
  return(CMR_SUCCESS);
}  /* of putFIRSTSETS() */


/* computation of nullable symbols analogous to theorem 4.14 in
 * "Parsing Theory", Vol.1 of Sippu and Soisalon-Soininen, Springer-Verlag
 */

typedef struct
{
  Indextype	lhs_ind;	/* Index of lhs nonterminal: 0...MAXNTERM-1 */
  short		counter;	/* number of marked symbols of assoc. rule */
  short		length;		/* total number of symbols of assoc. rule */
  short		ntno;		/* total number of nonterminals of ass. rule */
}	InfoType;

static	InfoType	*Counter;	/* Counter[0...MAXPROD-1] */
static	shstacktype	*Positionlist;	/* Positionlist[0...MAXNTERM-1] */

/* marked (nullable/terminalizable) nonterminals for which all instances of the
 * associated position lists have not been marked.
 */
static	shstacktype	NWk;
static	shqueuetype	DWk;

/* ISNULLABLE[nt_ind] <==> there is a derivation nt_ind =>* . */
static ARRBoolean ISNULLABLE = (ARRBoolean)NULL;/* ISNULLABLE[0...MAXNTERM-1] */

/* Initializes Counter and Positionlist and computes an initial set of
 * nullable symbols in NWk and an initial set of symbols that can be
 * terminalized in DWk
 */
static	ERR	initnullable(rules)
SEQdef_entry	rules;
{
  SEQdef_entry	deflist;
  def_entry	def, symbol;
  p_prod	prod;
  SEQunit	unlist;
  unit		un;
  short		cnt;	/* counting all symbols in a rule */
  short		ntcnt;	/* counting all nonterminals in a rule */
  shstacktype	*ptr;
  InfoType	*info;

  if ( (Positionlist = (shstacktype *)calloc(MAXNTERM, sizeof(shstacktype)))
	== (shstacktype *)NULL )
  {
    INT_ALLOC_ERR("initnullable()");
    exit(1);
  }

  if ( (Counter = (InfoType *)calloc(MAXPROD, sizeof(InfoType)))
	== (InfoType *)NULL )
  {
    INT_ALLOC_ERR("initnullable()");
    exit(1);
  }

  NWk = shcreate();
  DWk = shqcreate();

  foreachinSEQdef_entry(rules, deflist, def)
  {
#ifdef DEBUG_FIR
    if ( typeof(def) != Kp_prod )
	INT_TAG_ERR("initnullable()", typeof(def));
#endif
    ntcnt = cnt = 0;
    prod = def_entryTop_prod(def);
    foreachinSEQunit(rhsOfp_prod(prod), unlist, un)
    {
      if ( typeof(un) != Kp_elunit )
	return(GR_NOTBNF);

      symbol = DEFTBL[didOfp_elunit(un.Vp_elunit)];
      switch ( typeof(symbol) )
      {
	case Kp_nterm:	/* associate nonterminal symbol with rule prod */
		ptr = &( Positionlist[INDEX[didOfdef_entry(symbol)]] );
		*ptr = shpush(*ptr, (sheltype)INDEX[didOfp_prod(prod)]);
		ntcnt++;
	case Kp_term:	cnt++;	/* count terminals and nonterminals */
	case Kp_other:  break;
	default:	UL_TAG_ERR("initnullable()", typeof(symbol));
      } /* of switch */

    } /* of for */
    info = &( Counter[INDEX[didOfp_prod(prod)]] );
    info->lhs_ind = INDEX[lhsdidOfp_prod(prod)];
    info->counter = 0;
    info->length = cnt;
    info->ntno = ntcnt;

    if ( cnt == 0 )		/* nullable nonterminals */
	NWk = shpush(NWk, (sheltype)INDEX[lhsdidOfp_prod(prod)]);

    if ( ntcnt == 0 )		/* nonterminals that can be terminalized */
	DWk = shenq(DWk, (sheltype)didOfp_prod(prod));
  } /* of for */

  return(CMR_SUCCESS);
} /* of initnullable() */


static	void	reinitCounter()
{
  Indextype	i;

  for (i=0; i<MAXPROD; i++)
    Counter[i].counter = 0;

  return;
}  /* of reinitCounter() */


static	ERR	nullable(rules)
SEQdef_entry	rules;
{
  Indextype	nt_ind;
  InfoType	*info;
  shstacktype	list;

  /* allocation of ISNULLABLE and initialization with FALSE */
  if ( (ISNULLABLE = calloc(MAXNTERM, sizeof(Boolean)))  == (Boolean *)NULL )
  {
    INT_ALLOC_ERR("nullable()");
    exit(1);
  }

  while ( !shempty(NWk) )
  {
    nt_ind = (Indextype)shtop(NWk);
    NWk = shpop(NWk);

    /* Mark all instances of symbol nt_ind in the associated position lists
     * if and only if that has not been done already for nt_ind indicated
     * with ISNULLABLE[nt_ind]
     */
    if ( !ISNULLABLE[nt_ind] )
    {
	ISNULLABLE[nt_ind] = TRUE;
	for ( list = Positionlist[nt_ind]; !shempty(list); list = shtail(list) )
	{
	    info = &Counter[(Indextype)shtop(list)];

	    /* all instances of production top(list) have been marked
	     * but corresponding lhs nonterminal info->lhs_ind has not
	     */
	    if ( (++(info->counter) == info->length)  &&
		 !ISNULLABLE[info->lhs_ind] )
		NWk = shpush(NWk, (sheltype)info->lhs_ind);
	} /* of for */
    } /* of if */
  }  /* of while */

  return(CMR_SUCCESS);

}  /* end of nullable() */


static  ERR     defaultrules(cmr)
p_comar	cmr;
{
  p_string	ordername;
  Indextype	nt_ind;
  shstacktype	list;
  InfoType	*info;
  SEQdef_entry	deflist;
  def_entry	nterm;
  p_prod	prod;
  value		val;
  prop_entry	prop;
  DID		*index2did;	/* index2did[0...MAXPROD-1] */

  if ( (ordername = cmrlib_strtopstring(cmr->symbols, TERMINALIZE))
	!= (p_string)NULL )
    return(CMR_SUCCESS);
  if ( (ordername = cmrlib_strtopstring(cmr->symbols, ORDER))
        != (p_string)NULL )
    return(GR_ORDER_EXIST);

  if ( DEFAULT != (p_prod *)NULL )
    free(DEFAULT);

  if ( (DEFAULT=(p_prod *)calloc(MAXNTERM, sizeof(p_prod))) == (p_prod *)NULL )
  {
    INT_ALLOC_ERR("defaultrules()");
    exit(1);
  }

  index2did = cmrlib_INDEX_Invers(Kp_prod);

  /* computing DW1 */
  DWk = shenq(DWk, (sheltype)(MAXDID+1)); 		/* insert token */
  while ( (DID)shfront(DWk) != (MAXDID+1) )
  {
    nt_ind = Counter[INDEX[(DID)shfront(DWk)]].lhs_ind;
    if ( DEFAULT[nt_ind] == (p_prod)NULL )
    {
	DWk = shenq(DWk, (sheltype)nt_ind);
	DEFAULT[nt_ind] = def_entryTop_prod(DEFTBL[(DID)shfront(DWk)]);
    }  /* of if */
    DWk = shdeq(DWk);
  }  /* of while */
  DWk = shdeq(DWk);				/* delete token */

  /* computing the continuation grammar with the nearly the same
   * algorithm as in nullable()
   */
  while ( !shqempty(DWk) )
  {
    nt_ind = (Indextype)shfront(DWk);
    DWk = shdeq(DWk);
    /* Mark all instances of symbol nt_ind in the associated position lists
     * if and only if that has not been done already for nt_ind
     */
    for ( list = Positionlist[nt_ind]; !shempty(list); list = shtail(list) )
    {
      info = &Counter[(Indextype)shtop(list)];

      /* all instances of production top(list) have been marked
       * but corresponding lhs nonterminal info->lhs_ind has not
       */
      if ( (++(info->counter) == info->ntno)  &&
	   DEFAULT[info->lhs_ind] == (p_prod)NULL )
      {
        DWk = shenq(DWk, (sheltype)info->lhs_ind);
	/* mark nonterminal 'info->lhs_ind' and store default production */
	DEFAULT[info->lhs_ind] =
		def_entryTop_prod(DEFTBL[index2did[(Indextype)shtop(list)]]);
      }  /* of if */
    } /* of for */
  }  /* of while */

  (void)free(index2did);
  ordername = cmrlib_newstring(ORDER);

  /* Storing the results in the COMAR data structure */
  foreachinSEQdef_entry (NTERM_SEQ, deflist, nterm)
  {
    if ( (prod = DEFAULT[INDEX[didOfdef_entry(nterm)]]) == (p_prod)NULL )
	return(FIR_NOTERMIN);
    val.Vp_nval = Mkp_nval(1);
    prop.Vp_prop_val = Mkp_prop_val(val);
    prop = Mkprop_entry(didOfp_prod(prod), sidOfp_string(ordername), prop);
    appendfrontSEQprop_entry(propOfp_prod(prod), prop);
  }  /* of for */

  (void)cmrlib_newstring(TERMINALIZE);
  return(CMR_SUCCESS);
}  /* of defaultrules() */


static	void	FreeArrays()
{
  shstacktype	*tmp;

  (void)free(Counter);
  Counter = (InfoType *)NULL;

  for (tmp=Positionlist; tmp < (Positionlist+MAXNTERM); tmp++)
    while ( !shempty(*tmp) )
	*tmp = shpop(*tmp);

  (void)free(Positionlist);
  Positionlist = (shstacktype *)NULL;

  (void)free(ISNULLABLE);
  ISNULLABLE = (ARRBoolean)NULL;

  return;
}  /* of FreeArrays() */


static	void	relation(rules)
SEQdef_entry	rules;
{
  SEQdef_entry  deflist;
  def_entry     def, symbol;
  p_prod        prod;
  SEQunit       unlist;
  unit          un;
  Boolean	ready;

  foreachinSEQdef_entry(rules, deflist, def)
  {
#ifdef DEBUG_FIR
    if ( typeof(def) != Kp_prod )
        INT_TAG_ERR("relation()", typeof(def));
#endif
    prod = def_entryTop_prod(def);
    ready = FALSE;
    unlist = rhsOfp_prod(prod);
    while ( !ready && !emptySEQunit(unlist) )
    {
      retrievefirstSEQunit(unlist, un);

#ifdef DEBUG_FIR
      if ( typeof(un) != Kp_elunit )
        INT_TAG_ERR("relation()", typeof(def));
#endif

      symbol = DEFTBL[didOfp_elunit(un.Vp_elunit)];
      switch ( typeof(symbol) )
      {
        case Kp_nterm:
		AddToRelation(INDEX[lhsdidOfp_prod(prod)],
			      INDEX[didOfdef_entry(symbol)]);
		ready = !ISNULLABLE[INDEX[didOfdef_entry(symbol)]];
		break;
        case Kp_term:
		AddElemToSet(INDEX[didOfdef_entry(symbol)],
			     FIRSTSETS[INDEX[lhsdidOfp_prod(prod)]]);
		ready = TRUE;
		break;
        case Kp_other:  break;
#ifdef DEBUG_FIR
        default:        INT_TAG_ERR("relation()", typeof(symbol));
#endif
      } /* of switch */

      unlist = tailSEQunit(unlist);
    } /* of while */
  } /* of for */

  return;

}  /* of relation() */


static	void	AddEmpty(nterms, epsdid)
SEQdef_entry    nterms;
DID		epsdid;
{
  SEQdef_entry	deflist;
  def_entry	def;

  foreachinSEQdef_entry(nterms, deflist, def)
  {
    if ( ISNULLABLE[INDEX[didOfdef_entry(def)]] )
	(void)AddElemToSet(INDEX[epsdid], FIRSTSETS[INDEX[didOfdef_entry(def)]]);
  }  /* of for */

} /* of AddEmpty() */


/* Insertion of an empty terminal in 'cmr' */
static	ERR	AddEpsilon(cmr)
p_comar cmr;
{
  SEQdef_entry  epslist;

  epslist = cmrlib_sidtoterms(cmr->definitions,S_EMPTY);
  switch ( lengthSEQdef_entry(epslist) )
  {
          case 0        : EPS.Vp_term = cmrlib_newterm(S_EMPTY);
                          break;
          case 1        : EPS = headSEQdef_entry(epslist);
                          removefirstSEQdef_entry(epslist);
                          break;
          default       : return(LALR_AMBEPS);
  }  /* end of switch */

  return(CMR_SUCCESS);
}  /* of AddEpsilon() */


static	ERR	first(cmr)
p_comar	cmr;
{
  p_string      firstname;
  ERR		stat;

  if ( (firstname = cmrlib_strtopstring(cmr->symbols, FIRST1))
        != (p_string)NULL )
    return(FIR_PRESENT);

  initFIRSTSETS();

  /* Computing nullable symbols */
  if ( (stat = nullable(PROD_SEQ))  !=  CMR_SUCCESS )
    return(stat);

  /* computing relation R: (A,B) in R <==> there is a rule A->uBv where u=>* .
   * computing F0
   *  /initializing FIRSTSETS: t is in FIRSTSETS[A] <==> there is a rule A->tv
   */
  InitRelation(MAXNTERM);
  relation(PROD_SEQ);

  /* Chapter 5.5 in "Parsing Theory", Vol.1 of Sippu and Soisalon-Soininen */
  DiGraph(MAXNTERM, FIRSTSETS);

  /* Adds the empty symbol to FIRSTSET[A] <==> A->* . */
  AddEmpty(NTERM_SEQ, (DID)didOfdef_entry(EPS));

  firstname = cmrlib_newstring(FIRST1);

  stat = putFIRSTSETS(NTERM_SEQ, firstname);

  FreeRelation();
  return(stat);
}  /* end of first() */

