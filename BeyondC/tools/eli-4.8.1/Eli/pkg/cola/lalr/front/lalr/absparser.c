/*
** $Id: absparser.c,v 1.8 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: absparser.c,v 1.8 1997/08/29 08:38:08 mjung Exp $";

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
/* File: absparser.c	First Edit: 28.03.89	  Last Edit: 31.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 02.05.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "name.h"
#include "privatlib.h"

#include "grammarcomp.h"	/* definition of ORDER and START */

#include "prsiface.h"
#include "mkiface.h"
#include "lr0.h"
#include "lalr.h"
#include "lalr1tst.h"
#include "printtbl.h"
#include "printst2ter.h"
#include "absparser.h"
#include "purdom.h"
#include "parserlib.h"		/* definition of type 'ARRstatetype' */

/* Global variables */
ARRstatetype	AUTOM;
absparsertype	ABSPRS;


#define	ERROPNMAIL(str)	\
	(void)fprintf(stderr, "Cannot open file for writing %s.\n", str)

ERR	cmrtl_compute_absparser(c, cmrfile, opt, exe_purdom)
p_comar	c;
String	cmrfile;
short	opt;
Boolean	exe_purdom;
{
  p_comar	sav;
  SEQdef_entry	epslist;
  def_entry	eps;
  p_prod	startprod;
  short		exe,	/* execute-options */
		prt;	/* print-options */
  ERR		stat;	/* variable for errorcodes */

  /* What should be executed? */
  Boolean	exe_all  = FALSE, exe_lr0  = FALSE,
		exe_lalr = FALSE, exe_ltst = FALSE,
		prt_lr0  = FALSE, prt_lalr = FALSE,
		prt_ltst = FALSE, prt_abs = FALSE;

  FILE		*f;	/* File for output of statetables */

  exe = opt % 8;
  prt = opt / 8;

  if ( exe == 0 )
    exe_all = TRUE;
  else if ( exe >= 4 )
    exe_lr0 = exe_lalr = exe_ltst = TRUE;
  else if ( exe >= 2 )
    exe_lr0 = exe_lalr = TRUE;
  else
    exe_lr0 = TRUE;

  if ( prt >= 8 )
    {
      prt_abs = TRUE;
      prt -= 8;
    }
  if ( prt >= 4 )
    {
      prt_ltst = TRUE;
      prt -= 4;
    }
  if ( prt >= 2 )
    {
      prt_lalr = TRUE;
      prt -= 2;
    }
  if ( prt >= 1 )
    prt_lr0 = TRUE;

  /* Initializing of imported global variables */
  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */
  if ( exe_all || exe_lalr || exe_purdom )
    {
      /* Computation of an empty terminal */
      epslist = cmrlib_sidtoterms(c->definitions,S_EMPTY);
      switch ( lengthSEQdef_entry(epslist) )
        {
          case 0	: eps.Vp_term = cmrlib_newterm(S_EMPTY);
		  	  break;
          case 1	: eps = headSEQdef_entry(epslist);
		  	  removefirstSEQdef_entry(epslist);
		  	  break;
          default	: return(LALR_AMBEPS);
        }  /* end of switch */

      /* Computation of the global variables included from "cmrlib" */
      cmrlib_arrangedefs();
    }  /* end of if */
  cmrlib_compute_globarrs();


  if ( exe_all || exe_lr0 || exe_purdom )
    {
#ifdef DEBUG_ABS
      (void)printf("\ta) Computing the LR(0)-automaton.\n");
#endif
      if ( (stat=cmrtl_compute_LR0automat(CMR,START,ORDER,&AUTOM,&startprod))
	   != CMR_SUCCESS )
	return(stat);

      if ( prt_lr0 )
	{
#ifdef DEBUG_ABS
	  (void)printf("\t   Output of the LR0-Statetables.\n");
#endif
	  if ( (f = fopen(priv_genfilename(cmrfile, ".lr0"), "w"))
		== (FILE *)NULL )
	    {
	      ERROPNMAIL("LR0-Statetables");
	      exit(1);
	    }
	  printARRstate(AUTOM, f, AFTERLR0);
	  fclose(f);
	}  /* end of if */
    }  /* end of if */

  if ( exe_all || exe_lalr )
    {
#ifdef DEBUG_ABS
      (void)printf("\tb) Computing the LALR(1)-lookaheads.\n");
#endif
      if ( (stat = cmrtl_compute_LALR1(CMR, AUTOM)) != CMR_SUCCESS )
	return(stat);

      if ( prt_lalr )
	{
#ifdef DEBUG_ABS
	  (void)printf("\t   Output of the LALR(1)-Statetables.\n");
#endif
	  if ( (f = fopen(priv_genfilename(cmrfile, ".lalr"), "w"))
		== (FILE *)NULL )
	    {
	      ERROPNMAIL("LALR(1)-Statetables");
	      exit(1);
	    }
	  printARRstate(AUTOM, f, AFTERLALR);
	  fclose(f);
	}  /* end of if */
    }  /* end of if */

  if ( exe_all || exe_ltst || exe_purdom )
    {
#ifdef DEBUG_ABS
      (void)printf("\tc) Performing the LALR(1)-Analyze.\n");
#endif
      stat = cmrtl_lalr1tst(CMR, AUTOM, TRUE);
      if (stat != CMR_SUCCESS ){
	if ( stat != ISNOTLALR1 )
	  return(stat);	/* error: can't continue */
	else if ( !prt_ltst )	/* Grammar is not LALR(1) */
	{
#ifdef DEBUG_ABS
	  (void)printf("\t   Output of the conflict states");
	  (void)printf(" found when executing the LALR(1)-Test.\n");
#endif
	  if ( (f = fopen(priv_genfilename(cmrfile, ".info"), "w"))
		== (FILE *)NULL )
	    {
	      ERROPNMAIL("the conflict states.");
	      exit(1);
	    }
	  printARRstate(AUTOM, f, ONLY_CONFLICTS);
	  fclose(f);
	}  /* end of if */
	}
      if ( prt_ltst )
	{
#ifdef DEBUG_ABS
	  (void)printf("\t   Output of the LALR(1)-Statetables");
	  (void)printf(" after performing the LALR(1)-Test.\n");
#endif
	  if ( (f = fopen(priv_genfilename(cmrfile, ".info"), "w"))
		== (FILE *)NULL )
	    {
	      ERROPNMAIL("LALR(1)-Statetables after the LALR(1)-Analyze");
	      exit(1);
	    }
	  printARRstate(AUTOM, f, AFTERLTST);
	  fclose(f);
	}  /* end of if */
    }  /* end of if */

  if ( exe_all )
    {
#ifdef DEBUG_ABS
      (void)printf("\td) Construction of the parser-interface.\n");
#endif
      cmrtl_compute_interface(CMR, AUTOM, (DID)startprod->did, &ABSPRS);

      if ( prt_abs )
	{
#ifdef DEBUG_ABS
	  (void)printf("\t   Output of the abstract-parser-interface.\n");
#endif
	  printstate2terms(ABSPRS, CMR);
	  if ( (f = fopen(priv_genfilename(cmrfile, ".abs2"), "w"))
		== (FILE *)NULL )
	    {
	      ERROPNMAIL("the abstract-parser-interface");
	      exit(1);
	    }
	  WriteAbsparser(f, ABSPRS);
	  fclose(f);
	}  /* end of if */
    }  /* end of if */

  if ( stat != CMR_SUCCESS )
    return(stat);
  /* Algorithm of Purdom and Brown will be executed only,
   * if grammar is LALR(1). */
  if ( exe_purdom )
    {
#ifdef DEBUG_ABS
      (void)printf("\te) Execution of Purdom and Brown's algorithm.\n");
#endif
      if ( (stat = cmrtl_purdom(CMR, AUTOM)) != CMR_SUCCESS )
	return(stat);
    }  /* end of if */

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */
  return(CMR_SUCCESS);
}  /* end of cmrtl_compute_absprs() */
