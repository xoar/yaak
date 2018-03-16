/*
** $Id: lalr1tst.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: lalr1tst.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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
/* File: lalr1tst.c	First Edit: 16.03.89	  Last Edit: 21.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 31.03.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#include <stdio.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"
#include "bitset.h"
#include "name.h"	/* Definitions for modifications */

#include "parserlib.h"
#include "lalr1tst.h"

SID	compute_sid(str,tag)
String	str;
short	tag;
{
  symb_entry	symb;

  if ( tag == Kp_string )
    symb.Vp_string = cmrlib_strtopstring(CMR->symbols,str);
  else if ( tag == Kp_name )
    symb.Vp_name = cmrlib_strtopname(CMR->symbols,str);
  else
    INT_TAG_ERR("compute_sid()",tag);

  if ( symb.IDLclassCommon == NULL )
    return(UNDEF);
  else
    return(symb.IDLclassCommon->sid);
}  /* end of compute_sid() */


void	createCONFLICTSTATES()
{
  if ( (CONFLICTSTATES = (ARRSEQconflicttype)calloc( MAXSTATE+1,
						     sizeof(SEQconflicttype)
						   ))
	== (ARRSEQconflicttype)NULL )
    {
      INT_ALLOC_ERR("createCONFLICTSTATES()");
      exit(1);
    }
  return;
}  /* end of createCONFLICTSTATES() */

BitSet	ComputeShiftSet(shiftlist)
SEQshifttype	shiftlist;
{
  BitSet	result;

  result = MakeEmptySet(MAXTERM);
  for ( ; !emptySEQshift(shiftlist); shiftlist = tlSEQshift(shiftlist) )
    if ( typeof( DEFTBL[hdSEQshift(shiftlist).symbol] )  ==  Kp_term )
      (void)AddElemToSet(INDEX[hdSEQshift(shiftlist).symbol], result);

  return(result);

}  /* end of ComputeShiftSet() */


SEQmodiftype	LookAtReduceInstr(rule, reduce , noreduce)
DID	rule;
SID	reduce, noreduce;
{
  SEQmodiftype	result = initSEQmodif();
  modiftype	*elem;
  SEQunit	u_travel;
  unit		un;
  SEQprop_entry	p_travel;
  prop_entry	prop;

#ifdef DEBUG_LALR
  if ( typeof(DEFTBL[rule]) != Kp_prod )
    INT_TAG_ERR("LookAtReduceInstr()",typeof(DEFTBL[rule]));
#endif
  foreachinSEQunit( DEFTBL[rule].Vp_prod->rhs, u_travel, un )
    {
#ifdef DEBUG_LALR
      if ( typeof(un) != Kp_elunit )
        INT_TAG_ERR("LookAtReduceInstr()",typeof(un));
#endif
      if ( typeof(DEFTBL[un.Vp_elunit->did])  ==  Kp_other )
	foreachinSEQprop_entry(DEFTBL[un.Vp_elunit->did].Vp_other->prop,
				p_travel, prop)
	  if (typeof(prop)  ==  Kp_prop_val    &&
	      (prop.Vp_prop_val->sid == reduce  ||
	       prop.Vp_prop_val->sid == noreduce)
	     )
	    {
	      elem = mkmodif( prop.Vp_prop_val->sid == reduce,
			      (DID)prop.Vp_prop_val->val.Vp_dval->did,
			      rule, UNDEF
			    );

	      result = insSEQmodif(result, elem);
	    }  /* end of if */
    }  /* end of for */

  return(result);
}  /* end of LookAtReduceInstr() */


BitSet	Evaluate(modiflist,conflset,redset,noredset,autom,q,info)
SEQmodiftype	modiflist;
BitSet		conflset,	/* conflict-set */
		redset,		/* if reduce then SubFromSet(i,redset) */
		noredset;	/* if noreduce then SubFromSet(i,noredset) */
ARRstatetype	autom;
unsigned short	q;
Boolean		info;
{
  modiftype	*modifelem;
  Indextype	ind;

  while ( !emptySEQmodif(modiflist) )
  {
    ind = INDEX[hdSEQmodif(modiflist).term];
    if ( IsElemInSet(ind, conflset) )
      {
        (void)SubElemFromSet(ind, conflset);
	if ( hdSEQmodif(modiflist).tag )
	  if ( redset == (BitSet)NULL )
	    autom[q].Goto =
		deltermSEQshift(autom[q].Goto, hdSEQmodif(modiflist).term);
	  else
            (void)SubElemFromSet(ind, redset);
	else
          (void)SubElemFromSet(ind, noredset);
        hdSEQmodif(modiflist).stateno = q;
        modifelem = (modiftype *)modiflist;
        modiflist = tlSEQmodif(modiflist);
        if ( info )
	  MODIFICATIONS = insSEQmodif(MODIFICATIONS, modifelem);
	else
	  modiflist = delfirstSEQmodif(modifelem);
      }  /* end of if */
    else
      modiflist = delfirstSEQmodif(modiflist);
  }  /* end of while */

  return(conflset);
}  /* end of Evaluate() */


/* 'Lalr1Analyze()' computes 'ISLALR1' and if 'info' it computes also
 * 'CONFLICTSTATES'.
 */
void	Lalr1Analyze(autom,info)
ARRstatetype	autom;
Boolean		info;
{
  BitSet	intersect, shiftset;
  unsigned short q;
  SEQitemtype	itemlist1, itemlist2;
  SID		reduce = UNDEF, noreduce = UNDEF;
  Boolean	known;
  SEQmodiftype	modiflist;

  reduce = compute_sid(REDUCE, REDUCETYPE);
  noreduce = compute_sid(NOREDUCE, NOREDUCETYPE);
  known = ( reduce != UNDEF  ||  noreduce != UNDEF );

  ISLALR1 = TRUE;
  intersect = MakeEmptySet(MAXTERM);
  for ( q=1; q<=MAXSTATE; q++)
    {
      shiftset = ComputeShiftSet(autom[q].Goto);
      for ( itemlist1 = autom[q].Kernel;
	    !emptySEQitem(itemlist1);
	    itemlist1 = tlSEQitem(itemlist1)
	  )
	if ( tagofitem(hdSEQitem(itemlist1))  ==  Kred )
	  {
	    /* Searching shift-reduce conflicts. */
	    (void)InitSetToSet(shiftset,intersect);
	    (void)IntersectSet(hdSEQitem(itemlist1).red.erc, intersect);
	    if ( !IsEmptySet(intersect) && known)
	      {
		modiflist =
			LookAtReduceInstr(rulenoofitem(hdSEQitem(itemlist1)),
					  reduce, noreduce);
		intersect = Evaluate(modiflist, intersect, (BitSet)NULL,
				     hdSEQitem(itemlist1).red.erc,
				     autom, q, info);
		  	/* MODIFICATIONS will be manipulated.*/
	      }  /* end of if */
	    if ( !IsEmptySet(intersect) )
	      {
		if ( ISLALR1  &&  info )
		  createCONFLICTSTATES();
		ISLALR1 = FALSE;
		if ( info )
		  CONFLICTSTATES[q] = insSEQconflict( CONFLICTSTATES[q],
			mkconflict( FALSE, MakeSetCopy(intersect),
				    rulenoofitem(hdSEQitem(itemlist1)),UNDEF
				  )
						    );
	      }  /* end of if */

	    /* Searching reduce-reduce conflicts. */
	    for ( itemlist2 = tlSEQitem(itemlist1);
		  !emptySEQitem(itemlist2);
		  itemlist2 = tlSEQitem(itemlist2)
		)
	      if ( tagofitem(hdSEQitem(itemlist2))  ==  Kred )
		{
		  (void)InitSetToSet(hdSEQitem(itemlist1).red.erc,intersect);
		  (void)IntersectSet(hdSEQitem(itemlist2).red.erc,intersect);		  if ( !IsEmptySet(intersect) && known)
		    {
		      modiflist =
			LookAtReduceInstr(rulenoofitem(hdSEQitem(itemlist1)),
					  reduce, noreduce);
		      intersect = Evaluate(modiflist, intersect,
					   hdSEQitem(itemlist2).red.erc,
					   hdSEQitem(itemlist1).red.erc,
					   autom, q, info);
		  	/* MODIFICATIONS will be manipulated.*/
		      modiflist =
			LookAtReduceInstr(rulenoofitem(hdSEQitem(itemlist2)),
					  reduce, noreduce);
		      intersect = Evaluate(modiflist, intersect,
					   hdSEQitem(itemlist1).red.erc,
					   hdSEQitem(itemlist2).red.erc,
					   autom, q, info);
		  	/* MODIFICATIONS will be manipulated.*/
		    }  /* end of if */
		  if ( !IsEmptySet(intersect) )
		    {
		      if ( ISLALR1  &&  info )
		        createCONFLICTSTATES();
		      ISLALR1 = FALSE;
		      if ( info )
	CONFLICTSTATES[q] = insSEQconflict(
				CONFLICTSTATES[q],
				mkconflict( TRUE, MakeSetCopy(intersect),
				    rulenoofitem(hdSEQitem(itemlist1)),
				    rulenoofitem(hdSEQitem(itemlist2))
				  	  ));
		    }  /* end of if */
		}  /* end of if */
	}  /* end of if */

      /* end of for */
      FreeSet(shiftset);

    }  /* end of for */

  FreeSet(intersect);
  return;

}  /* end of Lalr1Analyze() */


ERR	cmrtl_lalr1tst(c,autom,info)
p_comar		c;
ARRstatetype	autom;
Boolean		info;
{
  p_comar	sav;

  sav = cmrlib_changeglobalcmrvar(c);	/* initializing of CMR */

  Lalr1Analyze(autom,info);

  (void)cmrlib_changeglobalcmrvar(sav);/* reinit. of CMR to old value */

  if ( ISLALR1 )
    return(CMR_SUCCESS);
  else
    return( ISNOTLALR1 );

}  /* end of cmrtl_lalr1tst() */
