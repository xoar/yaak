/* $Id: oiladt2a.c,v 1.40 2009/09/04 01:59:41 profw Exp $ */
/* Copyright, 1993, The Regents of the University of Colorado */

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

#include <stdio.h>
#include <stdlib.h>

#include "oiladt2.h"
#include "tOilTypeSetList.h"

#ifdef KeyID
#include "pdl_gen.h"
#endif

#ifdef MONITOR
#include "oil_dapto.h"
#endif

#undef BOOL
#undef FALSE
#undef TRUE
#define BOOL int
#define FALSE 0
#define TRUE 1

/**********************************************
  OilNewID - allocates a object and assigns the ptr
      may define the object's ID if the compilation switch 'WithIDs' is
      set.
  */
#ifdef WithIDs
#define OilNewID(ptr,type,str) \
     ptr=OilNew(type,str); ptr->sID= OilMasterID++; ptr->sStat= 0;
  int OilMasterID=1;	/* counter for debugging  and output formatting */
#else
#define OilNewID(ptr,type,str) ptr=OilNew(type,str); 
#endif


/**********************************************
  These state variables are used in the minimum cost coercion sequence
      algorithm for the balancing of 2 types.
  */
tOilCoercionSeq vOilCoercionSeq;/* which is the coercion seq selected */
tOilTypeSet vOilCoercionElement;/* which is the set element selected */
tOilType vOilCoercionType;	 /* what type is the result of balancing */
int vOilCost;	    		 /* cost of identifying a type */

/**********************************************
  OilAddArgSig - adds a new argument type to the front of the signature
  */
tOilArgSig
#ifdef PROTO_OK
OilAddArgSig(tOilType arg, tOilArgSig sig )
#else
OilAddArgSig( arg, sig )
tOilType arg; tOilArgSig sig;
#endif
{ tOilArgSig ps;

  if (!arg) {
    OilNewID(ps, tOilArgSig, Ssig);
    ps->sNext = sig;
    ps->sArg = arg;
    ps->sSameType = OilEmptyArgSig;
    return ps;
  }

  /* search for like signature */
  for (ps=arg->sSigs; ps; ps= ps->sSameType)
    if (ps->sNext == sig) return ps;

  /* otherwise construct a new one */
  OilNewID(ps, tOilArgSig, Ssig);
  ps->sNext = sig;
  ps->sArg = arg;
  ps->sSameType = arg->sSigs;

  arg->sSigs = ps;

  return ps;
}


/********************************
  OilNewOp - define a new operator 'id' with signature 'sig' and cost 'cost'
  */
tOilOp
#ifdef PROTO_OK
OilNewOp(oilName id, tOilArgSig sig, int cost)
#else
OilNewOp(id, sig, cost)
oilName id; tOilArgSig sig; int cost;
#endif
{
    tOilOp op;
    OilNewID(op,tOilOp,Sop);
    op->sName= id;	/* name of operator */
#ifdef KeyID
    SetOilOp(id, op, (tOilOp)0);
#endif
    op->sCost= cost;
    op->sArgs= sig;
    op->sInArcs = (tOilOp)0;
    op->sIndOps= (tOilOpIdentification)0;
    return( op );
    }

/********************************
  OilAddIdentification - add the possible identification of 'op' by indication
          'id'
  */
tOilOp
#ifdef PROTO_OK
OilAddIdentification(tOilOp id, tOilOp op)
#else
OilAddIdentification( id, op )
tOilOp op; tOilOp id;
#endif
{
    tOilOpIdentification pid;
    OilNewID(pid,tOilOpIdentification,SopIdent);  /* create new identification */
    pid->sNext= id->sIndOps;	/* link in new identification */
    pid->sOp= op;
    id->sIndOps= pid;
    return(op);
    }
 
/********************************
  OilcErrorCoercion -  This constant is used to denote an invalid coercion
      sequence
  */
struct ScoercionSeq OilcErrorCoercion= {
  0, 0,
  (tOilType)0,
  (tOilCoercionSeq)0,
  (tOilOp)0,
  (tOilCoercionSeq)0,
  0 };

/********************************
  OilAddCoercionCost - define a coercion from 'srctype' to 'destype' by 
      operator 'cop', followed by coercion sequence 'cs'
  */
void
#ifdef PROTO_OK
OilAddCoercionCost
  (tOilType srctype, tOilType destype, tOilOp cop, tOilCoercionSeq cs)
#else
OilAddCoercionCost( srctype, destype, cop, cs )
    tOilType srctype, destype;
    tOilOp cop;
    tOilCoercionSeq cs;
#endif
{ tOilCoercionSeq pc, destcc;
  int cost;

  destcc = OilCoerce(srctype, destype);
  if (!destcc) return;	/* if no coercion is required */
  
  cost = cop->sCost;
  if (cs) cost += cs->sCost;

  if (destcc != &OilcErrorCoercion) {	/* a path already exists */
    if (cost >= destcc->sCost) return;	/* if existing path is cheaper */
    pc = destcc;			/* otherwise replace existing one */
  } else {			/* no path exists, so create a new one */
    OilNewID(pc,tOilCoercionSeq,ScoercionSeq);
    pc->sNextCost = srctype->sCoercionCosts;
    srctype->sCoercionCosts = pc;
  }
  pc->sResultType = destype;
  pc->sCoercionOp = cop;
  pc->sCoercionSeq = cs;
  pc->sCost= cost;

  /* Possibly change coercion sequences for types that can reach here */
  for (cop = srctype->sCoercions; cop; cop = cop->sInArcs )
    OilAddCoercionCost(cop->sArgs->sNext->sArg, destype, cop, pc);
}


/********************************
  OilAddCoercion - add a coercion operator 'cop' to the coercion lattice
  */
void
#ifdef PROTO_OK
OilAddCoercion(tOilOp cop)
#else
OilAddCoercion( cop )
        tOilOp cop;
#endif
{ tOilType srctype = cop->sArgs->sNext->sArg;
  tOilType destype = cop->sArgs->sArg;
  tOilCoercionSeq destcc;

  if (srctype == OilInvalidType ||
      destype == OilInvalidType ||
      srctype == destype) return;
 
  /* Add coercion for the new arc */
  OilAddCoercionCost(srctype, destype, cop, (tOilCoercionSeq)0);

  /* Add coercion sequences to types reachable from destination */
  for (destcc = destype->sCoercionCosts; destcc; destcc = destcc->sNextCost ) 
    OilAddCoercionCost(srctype, destcc->sResultType, cop, destcc);

  cop->sInArcs = destype->sCoercions;
  destype->sCoercions = cop;
}
 

/********************************
  OilNewType - define a new type with name 'id'
  */

tOilType
#ifdef PROTO_OK
OilNewType(oilName id)
#else
OilNewType( id )
        oilName id;
#endif
{
    tOilType nt;
    OilNewID(nt,tOilType,Stype);
    nt->sName= id;              /* name for type */
#ifdef KeyID
    SetOilType(id, nt, (tOilType)0);
#endif
    nt->sCoercionCosts= (tOilCoercionSeq)0;	/* no coercions to start */
    nt->sSigs= (tOilArgSig)0;			/* no signatures */
    nt->sResultSets= (tOilTypeSet)0;		/* no result sets */
    nt->sCoercions= (tOilOp)0;			/* no coercions can pt here */
    return(nt);
    }	/* end of Oil New Type */

/********************************
  OilIsCoercibleTo - test if type 't1' can be coerced to type 't2'
  */
BOOL
#ifdef PROTO_OK
OilIsCoercibleTo(tOilType t1, tOilType t2)
#else
OilIsCoercibleTo( t1, t2 )
        tOilType t1, t2;
#endif
    {
    tOilCoercionSeq pcc;

    if (t1==t2 || !t2 || !t1) return(TRUE);
    for (pcc=t1->sCoercionCosts; pcc; pcc=pcc->sNextCost )
    	if (pcc->sResultType==t2) return(TRUE);
    return( FALSE );
    }


/********************************
  OilSetIncludes - test if type set 's1' includes type 't2'
  */
BOOL
#ifdef PROTO_OK
OilSetIncludes(tOilTypeSet s1, tOilType t2)
#else
OilSetIncludes( s1, t2 )
        tOilTypeSet s1;
        tOilType t2;
#endif
{
    tOilCoercionSeq pcc;
    tOilType pt;

    if (!s1) {	/* error set includes all */
      vOilCoercionElement=(tOilTypeSet)0;
      vOilCoercionSeq=(tOilCoercionSeq)0;
      return(TRUE);
    }
    /* validate that type 't2' is in the type set 's1'*/
    for( ;s1; s1= s1->sNext ) {
      pt= s1->sBaseType;
      vOilCoercionElement= s1;
      vOilCoercionSeq= (tOilCoercionSeq)0;
      if (pt==t2 || !t2) return(TRUE);
      for (pcc=pt->sCoercionCosts; pcc; pcc=pcc->sNextCost ){
    	if (pcc->sResultType==t2) { vOilCoercionSeq= pcc; return(TRUE);}
    	}}
    return( FALSE );
    }


/********************************
  OilAddResultType -  add a new type to the set of possible result types
  */
tOilTypeSet
#ifdef PROTO_OK
OilAddResultType(tOilType t, tOilTypeSet set, int cost)
#else
OilAddResultType(t, set, cost) tOilType t; tOilTypeSet set; int cost;
#endif
{ tOilTypeSet prs;

  if (!t) return (tOilTypeSet)0;	/* error type => error set */

  for(prs = t->sResultSets; prs; prs = prs->sSameBase)
    if ((prs->sNext == set) && (prs->sCost == cost)) return prs;

  OilNewID(prs, tOilTypeSet, StypeSet);
  prs->sBaseType = t;
  prs->sNext = set;
  prs->sCost = cost;

  prs->sSameBase = t->sResultSets;	/* link in new result set */
  t->sResultSets = prs;

  return prs;
}

/********************************
  OilUnionTypeSets -  Compute the union of two possible result type sets
  */
tOilTypeSet
#ifdef PROTO_OK
OilUnionTypeSets(tOilTypeSet t1, tOilTypeSet t2)
#else
OilUnionTypeSets(t1, t2) tOilTypeSet t1, t2;
#endif
{ tOilTypeSet prs;

  if (!t2) return t1;	/* Union identity */

  while(t1) {
    t2 = OilAddResultType(t1->sBaseType, t2, t1->sCost);
    t1 = t1->sNext;
  }

  return t2;
}

/********************************
  OilCanIdSigs -  Check the sets of possible actual argument types to see
      if they might be coerced to the corresponding formal type
  */
BOOL
#ifdef PROTO_OK
OilCanIdSigs(tOilSetSig src, tOilArgSig dest )
#else
OilCanIdSigs( src, dest )
	tOilSetSig src;
	tOilArgSig dest;
#endif
{
    vOilCost= 0;
    if (dest) {
	for (dest=dest->sNext; dest; dest= dest->sNext){
	    if (!src) return(FALSE);
	    if (OilSetIncludes( (tOilTypeSet)(src->head), dest->sArg)){
		src=src->tail;
		if (vOilCoercionSeq) vOilCost+= vOilCoercionSeq->sCost;
		}
	    else return(FALSE);
	    }
	}
    return !src;  /* match only if sigs same length */
    }



/*****************************************************
  OilCoerce - return coercion sequence for coercing 't1' to 't2'
  */
tOilCoercionSeq
#ifdef PROTO_OK
OilCoerce(tOilType t1, tOilType t2)
#else
OilCoerce( t1, t2 )
	tOilType t1, t2;
#endif
  {
  tOilCoercionSeq cc;
  if (t1==t2 || !t1 || !t2) return (tOilCoercionSeq)0;
  for (cc=t1->sCoercionCosts; cc; cc=cc->sNextCost)
  	if (cc->sResultType == t2) return(cc);
  return(&OilcErrorCoercion);
  }

/********************************
  OilIdResultSet - find all possible result types which might be indicated
      by 'ind' with arguments 'setsig'. (PS only the minimum coercion costs
      for each possible result is used )
  */
tOilTypeSet
#ifdef PROTO_OK
OilIdResultSet(tOilOp ind, tOilSetSig setsig)
#else
OilIdResultSet( ind, setsig )
	tOilOp ind;
	tOilSetSig setsig;
#endif
{
    tOilOpIdentification pid;
    tOilTypeSet rts=(tOilTypeSet)0;
    if (ind) {
	for( pid= ind->sIndOps; pid; pid=pid->sNext ){
	    if (OilCanIdSigs( setsig, pid->sOp->sArgs))
		rts= OilAddResultType( pid->sOp->sArgs->sArg, rts, vOilCost );
	    }
	}
    return( rts );
    }


/********************************
  OilIdOpTSn - find the minimum operator cost which might be indicated
      by 'ind' with arguments 'setsig' and result type 'rt'
  */
tOilOp
#ifdef PROTO_OK
OilIdOpTSn(tOilOp ind, tOilSetSig setsig, tOilType rt)
#else
OilIdOpTSn( ind, setsig, rt )
	tOilType rt;
	tOilOp ind;
	tOilSetSig setsig;
#endif
{
    tOilOpIdentification pid;
    int cost=OilMaxCost;
    tOilOp op=(tOilOp)0;
    if (ind) {
      for( pid= ind->sIndOps; pid; pid=pid->sNext ){
      	int tcost;
      	tOilCoercionSeq cs = OilCoerce(pid->sOp->sArgs->sArg, rt);
      	if (OilIsValidCS(cs)) {
      	  tcost= pid->sOp->sCost;
      	  if (cs) tcost+= cs->sCost;
  	  if (OilCanIdSigs( setsig, pid->sOp->sArgs))
  	    if( cost> (tcost+= vOilCost)) {
  		cost= tcost;
  		op= pid->sOp;
  		}
  	  }  /* if 'OilIsValidCS */
  	}  /* for 'pid */
      }  /* if 'ind */
    return( op );
    }  /* end of Id Op Type Set */


/********************************
  OilNoOverload - if a non-overloaded operator can't be identified,
      return it anyway
  */
tOilOp
#ifdef PROTO_OK
OilNoOverload(tOilOp ind, tOilOp opr)
#else
OilNoOverload( ind, opr )
        tOilOp ind, opr;
#endif
{
    if (!opr) {
      if (ind && ind->sIndOps && !ind->sIndOps->sNext)
	return ind->sIndOps->sOp;
      }
    return opr;
    }


/********************************
  OilBalance - select the minimum cost coercion sequence common to the two
      type sets
  */
tOilType
#ifdef PROTO_OK
OilBalance(tOilTypeSet ts1, tOilTypeSet ts2)
#else
OilBalance( ts1, ts2 )
        tOilTypeSet ts1, ts2;
#endif
{
    tOilType rt;
    int cost;

    if (!ts1 && !ts2) return OilInvalidType;
    if (!ts1) return OilBalance(ts2,ts2);
    if (!ts2) return OilBalance(ts1,ts1);

    cost= OilMinimumCoercionSeq( ts1, ts2, OilMaxCost );
    rt= vOilCoercionType;
    if(cost>OilMinimumCoercionSeq( ts2, ts1, cost )){
      rt=vOilCoercionType;
      }
    return( rt );
    }  /* end of OilBalance */


/********************************
  OilMinimumCoercionSeq - calculate the minimum coercion cost sequence between
      ts1 and ts2
  */
int
#ifdef PROTO_OK
OilMinimumCoercionSeq(tOilTypeSet ts1, tOilTypeSet ts2, int cost)
#else
OilMinimumCoercionSeq( ts1, ts2, cost )
	tOilTypeSet ts1, ts2;
	int cost;
#endif
  {
    tOilType rt=(tOilType)0;
    tOilCoercionSeq seq=(tOilCoercionSeq)0, cc;
    tOilTypeSet rs;

    for (rs=ts1; rs; rs=rs->sNext){ int tcost;
      tcost= OilMinimumCoercionCost(ts2,rs->sBaseType,cost);
      if (cost>tcost){
              seq= vOilCoercionSeq;
              rt= vOilCoercionType;
              cost= tcost;
          }
        else if (cost > rs->sCost)	/* quick rejection */
          for (cc=rs->sBaseType->sCoercionCosts; cc; cc=cc->sNextCost){
            int basecost= rs->sCost;
            int tmpcost;
	    tmpcost= OilMinimumCoercionCost(ts2,
            				cc->sResultType,
            				cost-basecost);
            if(cost> (basecost+=tmpcost)){
              seq= vOilCoercionSeq;
              rt= vOilCoercionType;
              cost= basecost;
              }  /* end of if'cost */
            }  /* end of for'cc */
      } /* end of for'rs */
    vOilCoercionSeq= seq;
    vOilCoercionType= rt;
    return( cost );
    }  /* end of Minimum Coercion Seq */


/********************************
  OilMinimumCoercionCost - 
  */ 
int
#ifdef PROTO_OK
OilMinimumCoercionCost(tOilTypeSet ts, tOilType t, int cost)
#else
OilMinimumCoercionCost( ts, t, cost )
	tOilTypeSet ts;
	tOilType t;
	int cost;
#endif
{
    tOilType rt=(tOilType)0;
    tOilCoercionSeq seq=(tOilCoercionSeq)0;

      if (OilSetIncludes(ts,t))
          { int tcost;
            seq= vOilCoercionSeq;
            tcost= vOilCoercionElement->sCost;
            if (!vOilCoercionSeq){
                if (tcost<cost) {rt= vOilCoercionElement->sBaseType; cost= tcost;}}
              else { tcost+= vOilCoercionSeq->sCost;
                if(tcost<cost) { rt= vOilCoercionSeq->sResultType;
                  cost= tcost; }
              	}
            }
    vOilCoercionSeq= seq;
    vOilCoercionType= rt;
    return( cost );
    }  /* end of Minimum Coercion Cost */


/********************************
  OilNewClass - define a new class with 'numarg' parameters
  */
tOilClass
#ifdef PROTO_OK
OilNewClass(oilName id, int numArg )
#else
OilNewClass( id, numArg )
        oilName id;
        int numArg;
#endif
{
  tOilClass nc;
  OilNewID(nc,tOilClass,Sclass);
  nc->sName= id;
#ifdef KeyID
  SetOilClass(id, nc, (tOilClass)0);
#endif
  nc->sNumArg= numArg;
  nc->sClassOps= (tOilClassOp)0;
  return( nc );
  }


/********************************
  OilNewClassSigArg - return and empty class signature
  */
tOilClassArgSig
OilNewClassSigArg()
{ return (tOilClassArgSig)0; }



/********************************
  This variable holds the list of existing class argument signatures
  */

tOilClassArgSig vOilClassArgSig=(tOilClassArgSig)0;


/********************************
  OilAddClassSigArg - add an argument to a class signature
      td - is arg a class ref/ specific type ref / arg ref
      st - the specific type referenced
      pi - the parameter index ref'd
      cs - the root class argument signature
  */
tOilClassArgSig
#ifdef PROTO_OK
OilAddClassSigArg(tOilClassSigArgDesc td, tOilType st, int pi, tOilClassArgSig cs)
#else
OilAddClassSigArg( td, st, pi, cs )
	tOilClassSigArgDesc td;
	tOilType st;
        int pi;
	tOilClassArgSig cs;
#endif
{
    tOilClassArgSig  next;
    tOilClassArgSig  ntd=(tOilClassArgSig)0;

    for(next= vOilClassArgSig; next && !ntd; next= next->sAnother)
	    if ((next->sDescPattern==td)&&
		(next->sNext==cs) &&
		 ((td==eSpecTypeRef)
		       ?(next->sRefdType==st)
		       :(next->sParamIndex==pi)))
		    ntd= next;
    if (!ntd) {
	OilNewID(ntd,tOilClassArgSig,SclassArgSig);
	ntd->sAnother= vOilClassArgSig;
	ntd->sNext= cs;
	ntd->sDescPattern= td;
	ntd->sRefdType= (td==eSpecTypeRef)?st:(tOilType)0;
	ntd->sParamIndex= pi;
	vOilClassArgSig= ntd;
    }
    return( ntd );
  }


/********************************
  OilAddClassOpId - add an identification to class operator 'op'
      ind - the indication
      op - the class operator
  */
BOOL
#ifdef PROTO_OK
OilAddClassOpId(tOilOp ind, tOilClassOp op )
#else
OilAddClassOpId( ind, op )
	tOilOp ind;
        tOilClassOp op;
#endif
{
    tOilClassOpId opid;
    OilNewID(opid,tOilClassOpId,SclassOpId);
    opid->sNext= op->sIdents;
    op->sIdents= opid;

    opid->sOpInd= ind;
    return(TRUE);
  }
/********************************
  OilAddClassOp - adda new operator to class 'c'
      id - name of operator
      sig - the argument signature
      cost - the cost of operator
  */
tOilClassOp
#ifdef PROTO_OK
OilAddClassOp(oilName id, tOilClassArgSig sig, int cost, tOilClass c)
#else
OilAddClassOp( id, sig, cost, c )
        oilName id;
	tOilClassArgSig sig;
	int cost;
        tOilClass c;
#endif
{
    tOilClassOp op;
    OilNewID(op,tOilClassOp,SclassOp);
    op->sNext= c->sClassOps;
    c->sClassOps= op;

    op->sName= id;
    op->sArgDesc= sig;
    op->sCost= cost;
    op->isCoercion= FALSE;
    op->sIdents= (tOilClassOpId)0;
    return(op);
  }


/********************************
  OilAddClassCoercion - define coercion for the class 'c'
  */
BOOL
#ifdef PROTO_OK
OilAddClassCoercion(tOilClassOp op)
#else
OilAddClassCoercion( op )
        tOilClassOp op;
#endif
{
    op->isCoercion= TRUE;
    return(TRUE);
  }


/********************************
  OilArgRef - get the ref'd argument
  */
tOilType
#ifdef PROTO_OK
OilArgRef(int index, tOilArgSig argSig)
#else
OilArgRef( index, argSig )
        int index;
        tOilArgSig argSig ;
#endif
{
  if (!argSig) return (tOilType)0;
  if (index==0) return( argSig->sArg );
  return( OilArgRef(index-1,argSig->sNext) );
  }


/********************************
  OilBuildClassSigInst - build the argument signature from the class signature
  */
tOilArgSig
#ifdef PROTO_OK
OilBuildClassSigInst(tOilArgSig argSig, tOilClassArgSig tdl)
#else
OilBuildClassSigInst( argSig, tdl )
        tOilArgSig argSig;
	tOilClassArgSig tdl;
#endif
{
    if (!tdl) return (tOilArgSig)0;
      else {
	tOilType t;
	switch (tdl->sDescPattern) {
	  case eClassRef: t= argSig->sArg; break;
	  case eElementRef: t= OilArgRef(tdl->sParamIndex, argSig); break;
	  case eSpecTypeRef: t= tdl->sRefdType; break;
	  }
	return( OilAddArgSig( t,
			OilBuildClassSigInst( argSig, tdl->sNext )
			));
      }
    } /* end of OilBuildClassSigInst */


/********************************
  OilDefClassOpId - add the defined class operator to the possible
  identification.
  */
void
#ifdef PROTO_OK
OilDefClassOpId(tOilClassOpId opid, tOilOp op)
#else
OilDefClassOpId( opid, op )
	tOilClassOpId opid;
	tOilOp op ;
#endif
{
  if (!opid) return;
  OilDefClassOpId( opid->sNext, op );
  (void)OilAddIdentification( opid->sOpInd, op );
  } /* end of OilDefClassOpId */


/********************************
  OilDefClassOp - build an instance of the class operator 'co' using the 
      class type signature
  */
tOilOp
#ifdef PROTO_OK
OilDefClassOp(tOilClassOp co, tOilArgSig argSig)
#else
OilDefClassOp( co, argSig )
	tOilClassOp co;
        tOilArgSig argSig ;
#endif
{ 
  tOilOp  op;
  op= OilNewOp( co->sName,
	OilBuildClassSigInst( argSig, co->sArgDesc ),
	co->sCost
	);
  if (co->isCoercion==TRUE) OilAddCoercion(op);
  OilDefClassOpId(co->sIdents,op);
  return( op );
  } /* end of Build Class Op */

    
/********************************
  OilDefClassOps - define the operators of class 'c' with signature 'as'
  */
void
#ifdef PROTO_OK
OilDefClassOps(tOilClass c, tOilArgSig as)
#else
OilDefClassOps(c, as) tOilClass c; tOilArgSig as;
#endif
{ tOilClassOp pco;

  for (pco=c->sClassOps; pco; pco=pco->sNext) OilDefClassOp(pco, as);
}



/********************************
  OilGetArgType - Get type of argument #n of operator 'op'
  */
tOilType
#ifdef PROTO_OK
OilGetArgType(tOilOp op, int n )
#else
OilGetArgType( op, n )
	tOilOp op; int n;
#endif
  {
  tOilArgSig s;
  for (s= op ? op->sArgs : (tOilArgSig)0; n>0&&s; n--) s=s->sNext;
  return s ? s->sArg : (tOilType)0;
   
  }

	/* the end of oiladt2a.c */
