static char rcsid[] = "$Id: oiladt2f.c,v 1.4 2009/10/15 17:11:35 profw Exp $";
/* Copyright, 1995, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include "oiladt2.h"

/**********************************************
  OilNewID - allocates a object and assigns the ptr
      may define the object's ID if the compilation switch 'WithIDs' is
      set.
  */
#ifdef WithIDs
#define OilNewID(ptr,type,str) \
     ptr=OilNew(type,str); ptr->sID= OilMasterID++; ptr->sStat= 0;
  extern int OilMasterID;    /* counter for debugging  and output formatting */
#else
#define OilNewID(ptr,type,str) ptr=OilNew(type,str); 
#endif

extern int vOilCost;

tOilOpSet
#if defined(__cplusplus) || defined(__STDC__)
OilIdOpSet(tOilOp ind, tOilSetSig setsig, tOilType rt)
#else
OilIdOpSet( ind, setsig, rt )
     tOilType rt;
     tOilOp ind;
     tOilSetSig setsig;
#endif
{
    tOilOpIdentification pid;
    int cost=OilMaxCost;
    tOilOpSet set=(tOilOpSet)0;
    for( pid= ind->sIndOps; pid; pid=pid->sNext ){
    	int tcost;
    	tOilCoercionSeq cs;
    	if (OilIsValidCS( cs=OilCoerce( pid->sOp->sArgs->sArg, rt))) {
    	  tcost= pid->sOp->sCost;
    	  if (cs) tcost+= cs->sCost;
	  if (OilCanIdSigs( setsig, pid->sOp->sArgs))
	    if( cost> (tcost+= vOilCost))
              cost= tcost;
	}  /* if 'OilIsValidCS */
    }  /* for 'pid */
 
    for( pid= ind->sIndOps; pid; pid=pid->sNext ){
    	int tcost;
    	tOilCoercionSeq cs;
    	if (OilIsValidCS( cs=OilCoerce( pid->sOp->sArgs->sArg, rt))) {
    	  tcost= pid->sOp->sCost;
    	  if (cs) tcost+= cs->sCost;
	  if (OilCanIdSigs( setsig, pid->sOp->sArgs))
	    if( cost == (tcost+= vOilCost))
              set = OilAddOpSet(set, pid->sOp);
	  }  /* if 'OilIsValidCS */
    } /* for 'pid */
    return( set );
}  /* end of Id Op Type Set */

tOilOpSet
#if defined(__cplusplus) || defined(__STDC__)
OilAddOpSet (tOilOpSet set, tOilOp op)
#else
OilAddOpSet (set, op)
  tOilOpSet set;
  tOilOp op;
#endif
{
  tOilOpSet pid;
  OilNewID(pid, tOilOpSet, SopIdent);

  pid->sNext = set;
  pid->sOp = op;
  return pid;
}

void
#if defined(__cplusplus) || defined(__STDC__)
OilFreeOpSet (tOilOpSet set)
#else
OilFreeOpSet (set)
  tOilOpSet set;
#endif
{
  tOilOpSet next;
  while (set) {
    next = set->sNext;
    free(set);
    set = next;
  }
}

tOilOp
#if defined(__cplusplus) || defined(__STDC__)
OilHeadOS (tOilOpSet set)
#else
OilHeadOS (set)
  tOilOpSet set;
#endif
{
  return ( set ? set->sOp : OilInvalidOp);
}

tOilOpSet
#if defined(__cplusplus) || defined(__STDC__)
OilTailOS (tOilOpSet set)
#else
OilTailOS (set)
  tOilOpSet set;
#endif
{
  return (set ? set->sNext : (tOilOpSet)0);
}

int
#if defined(__cplusplus) || defined(__STDC__)
OilEmptyOS (tOilOpSet set)
#else
OilEmptyOS (set)
  tOilOpSet set;
#endif
{
  return (set ? 0 : 1);
}
