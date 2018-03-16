#ifndef OILADT2_H
#define OILADT2_H
/* $Id: oiladt2.h,v 1.47 2007/07/09 10:24:22 profw Exp $
 * Copyright, 1997, The Regents of the University of Colorado */

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

#include "eliproto.h"
#include "VoidPtrList.h"

#define WithIDs 1

/* 'WithIDs' indicates that an extract 'sID' component is maintained in 
	the data structures.  This, sID, field is a unique number 
	associated with each object for use in inter-object references 
	when 'dumping' the objects out to a file in form suitible for 
	compilation.
	  The field sStat is used to mark those fields which have been
	visited while dumping and need not be dumped again.  This field
	is also used to emit 'extern' stmts as necessary;
	*/
#ifdef WithIDs
#define OilDefID int sID, sStat;
#else
#define OilDefID
#endif

#define KeyID 1
#ifdef KeyID
#include "deftbl.h"
#define oilName DefTableKey
#define NoName NoKey
#define NewName NewKey()
extern char *RepName ELI_ARG((char *,DefTableKey));
#else
#define oilName int
#define NoName -1
#define NewName OilMaxName++
#define RepName(b,n) (sprintf(b,"%d",(n)), b)
#endif

#ifdef __cplusplus

/* provide forward declarations for C++ classes */
struct ScoercionSeq;
struct Ssig;
struct StypeSet;
struct Sop;
struct SopIdent;
struct SclassOpId;

#endif

typedef struct Stype {
	OilDefID
	oilName sName;		/* type denotation */
	struct ScoercionSeq
		*sCoercionCosts;/* Coercions from this type to others */
	struct Ssig *sSigs;	/* signatures whose 'top' type is this */
	struct StypeSet
		*sResultSets;	/* Sets whose last element is this */
	struct Sop *sCoercions;	/* Coercions that result in this type */
	} *tOilType;

#define OilInvalidType ((tOilType)0)

typedef struct Ssig {
	OilDefID
	struct Ssig *sNext;	/* next argument type in signature */
	tOilType sArg;		/* a specific type */
	struct Ssig *sSameType;	/* other sigs which end in this type */
	} *tOilArgSig;

#define OilEmptyArgSig ((tOilArgSig)0)

typedef struct Sop {
	OilDefID
	oilName sName;	/* operator denotation */
	int sCost;	/* its cost */
	tOilArgSig sArgs;	/* type signature of arguments */
	struct Sop *sInArcs;	/* other coercions into this type node */
	struct SopIdent *sIndOps; /* the identifiable ops */
	} *tOilOp;

#define OilInvalidOp ((tOilOp)0)

typedef struct ScoercionSeq {
	OilDefID
	tOilType sResultType;	/* type of result of coercion sequence */
	struct ScoercionSeq
		*sNextCost;/* next coercion which can be applied to this type */
	tOilOp sCoercionOp;	/* the coercion operator used here */
	struct ScoercionSeq
		*sCoercionSeq;	/* rest of coercion sequence */
	int sCost;		/* total cost of coercion sequence */
	} *tOilCoercionSeq;

typedef struct StypeSet {
	OilDefID
	tOilType sBaseType;	/* 'A' type which can be directly referenced */
	struct StypeSet
		*sNext;	/* the other types which can be directly referenced */
	int sCost;		/* the cost to get to this type */
	struct StypeSet
		*sSameBase;	/* other sets with this base type */
	} *tOilTypeSet;

#define OilEmptyTypeSet ((tOilTypeSet)0)

typedef struct _VoidPtrLE *tOilSetSig;

#define OilEmptySetSig ((tOilSetSig)0)

typedef struct SopIdent {
	OilDefID
	struct SopIdent *sNext;	/* next in list */
	tOilOp sOp;		/* which op to identify */
	} *tOilOpIdentification;

typedef tOilOpIdentification tOilOpSet;

typedef enum{
	eClassRef,	/* refers to the created type */
	eElementRef,	/* refers to the element used to derive type */
	eSpecTypeRef	/* refers to a specific type */
	} tOilClassSigArgDesc;

typedef struct SclassArgSig {
	OilDefID
	struct SclassArgSig *sAnother;	/* tail sharing ptr */
	struct SclassArgSig *sNext;	/* next in list */
	tOilClassSigArgDesc sDescPattern;
	tOilType sRefdType;		/* possibly refers to a specific type */
	int sParamIndex;		/* or a specific parameter */
	} *tOilClassArgSig;

typedef struct SclassOp {
	OilDefID
	struct SclassOp *sNext;
	oilName sName;		/* operator denotation */
	tOilClassArgSig sArgDesc;	/*  list of argument descriptions */
	int sCost;		/* cost of operator */
	int isCoercion;	/* defs a coercion */
	struct SclassOpId *sIdents;	/* indications */
	} *tOilClassOp;

typedef struct SclassOpId { 
	OilDefID
	struct SclassOpId *sNext;/* next in list */
	tOilOp sOpInd;		/* which operator indication is enhanced */
	} *tOilClassOpId;

typedef struct Sclass {
	OilDefID
	oilName sName;			/* class denotation */
	int sNumArg;			/* number of args to class */
	tOilClassOp sClassOps;	/* description of operator */
	} *tOilClass;

#define OilInvalidClass ((tOilClass)0)

#define OilNew(ptr,str) (ptr)calloc(1, sizeof(struct str))

#define OilMaxCost 32000

#define OilSelectTypeFromTS(ts) OilBalance(ts,ts)

#define OilNewArgSig() OilEmptyArgSig
extern tOilArgSig OilAddArgSig ELI_ARG((tOilType arg, tOilArgSig sig));

#define OilNewSetSig() OilEmptySetSig
#define OilAddSetSig(arg,sig) ConstOilTypeSetList(arg,sig)

extern tOilOp OilNewOp ELI_ARG((oilName id, tOilArgSig sig, int cost));

#define OilErrorOp() OilInvalidOp

extern tOilOp OilAddIdentification ELI_ARG((tOilOp id, tOilOp op));

extern void OilAddCoercionCost
  ELI_ARG((tOilType srctype, tOilType destype, tOilOp cop, tOilCoercionSeq cs));

extern tOilType OilNewType ELI_ARG((oilName id));

#define OilErrorType() OilInvalidType

/* define a new type of class 'c' with signature 'as' */
extern void OilDefClassOps ELI_ARG((tOilClass c, tOilArgSig as));

/* validate type t1 is coercible to t2 */
extern int OilIsCoercibleTo ELI_ARG((tOilType t1, tOilType t2));

/* validate that type 't2' is in the type set 's1'	*/
extern int OilSetIncludes ELI_ARG((tOilTypeSet s1, tOilType t2));

/* add a new type to the set of possible result types */
extern tOilTypeSet OilAddResultType ELI_ARG((tOilType t, tOilTypeSet set, int cost));

/* find the union of two possible type sets */
extern tOilTypeSet OilUnionTypeSets ELI_ARG((tOilTypeSet t1, tOilTypeSet t2));

/* OilEmptyTS, OilHeadTS & OilTailTS - access root elements of type sets */
#define OilEmptyTS(set) (!(set))
#define OilHeadTS(set)  ((set)->sBaseType)
#define OilTailTS(set)  ((set)->sNext)

/* Check the sets of possible actual argument types to see if they might
	be coerced to the corresponding formal type */
extern int OilCanIdSigs ELI_ARG((tOilSetSig src, tOilArgSig dest));

/* check for valid coercion*/
extern struct ScoercionSeq OilcErrorCoercion;
#define OilIsValidCS(ccs) ((ccs)!=&OilcErrorCoercion)

/* check for valid operator*/
#define OilIsValidOp(op) ((op)!=OilInvalidOp)

/* return coercion sequence for coercing 't1' to 't2'*/
extern tOilCoercionSeq OilCoerce ELI_ARG((tOilType t1, tOilType t2));

#define OilEmptyCS(cs) (!(cs))
#define OilHeadCS(cs)  ((cs)->sCoercionOp)
#define OilTailCS(cs)  ((cs)->sCoercionSeq)
#define OilErrorCS()   (&OilcErrorCoercion)

extern void OilAddCoercion ELI_ARG((tOilOp cop));

/* find all possible result types which might be indicated by 'ind'
	with arguments 'setsig' */
extern tOilTypeSet OilIdResultSet ELI_ARG((tOilOp ind, tOilSetSig setsig));

/* find the minimum-cost operator which might be indicated by 'ind'
	with arguments 'setsig' and result type 'rt' */
extern tOilOp OilIdOpTSn ELI_ARG((tOilOp ind, tOilSetSig setsig, tOilType rt));

/* if 'opr' is invalid, and 'ind' can only indicate a single operator,
	then return that operator.  ('opr' is the result of OilIdOpTSn) */
extern tOilOp OilNoOverload ELI_ARG((tOilOp ind, tOilOp opr));

#define OilTypeToSet(t) OilAddResultType((t),OilEmptyTypeSet,0)

extern tOilType OilBalance ELI_ARG((tOilTypeSet ts1, tOilTypeSet ts2));

extern int OilMinimumCoercionSeq ELI_ARG((tOilTypeSet ts1, tOilTypeSet ts2, int cost));

extern int OilMinimumCoercionCost ELI_ARG((tOilTypeSet ts, tOilType t, int cost));

extern tOilClass OilNewClass ELI_ARG((oilName id, int argNum));

#define OilErrorClass() OilInvalidClass

extern tOilClassArgSig OilNewClassSigArg ELI_ARG((void)); /* returns empty signature */

extern tOilClassArgSig OilAddClassSigArg
  ELI_ARG((tOilClassSigArgDesc td, tOilType st, int pi, tOilClassArgSig cs));

extern tOilClassOp OilAddClassOp
  ELI_ARG((oilName id, tOilClassArgSig sig, int cost, tOilClass c));

extern int OilAddClassOpId ELI_ARG((tOilOp ind, tOilClassOp op));

extern int OilAddClassCoercion ELI_ARG((tOilClassOp op));

extern tOilType OilArgRef ELI_ARG((int index, tOilArgSig argSig));

extern tOilArgSig OilBuildClassSigInst
  ELI_ARG((tOilArgSig argSig, tOilClassArgSig tdl));

extern void OilDefClassOpId ELI_ARG((tOilClassOpId opid, tOilOp op));

extern tOilOp OilDefClassOp ELI_ARG((tOilClassOp co, tOilArgSig argSig));


/* Get type of argument #n of operator 'op' */
extern tOilType OilGetArgType ELI_ARG((tOilOp op, int n));
#define OilSignatureOf(x) ((x)?(x)->sArgs:OilEmptyArgSig)
#define OilResultTypeOf(x) (((x)&&(x)->sArgs)?(x)->sArgs->sArg:OilInvalidType)
#define OilArgTypesOf(x) (((x)&&(x)->sArgs)?(x)->sArgs->sNext:OilEmptyArgSig)
#define OilArgType(x) ((x)?(x)->sArg:OilInvalidType)
#define OilNextArg(x) ((x)?(x)->sNext:OilEmptyArgSig)

extern tOilTypeSet OilIdResultTS1 ELI_ARG((tOilOp id, tOilTypeSet as1));
extern tOilTypeSet OilIdResultTS2
  ELI_ARG((tOilOp id, tOilTypeSet as1, tOilTypeSet as2));
extern tOilTypeSet OilIdResultTS3
  ELI_ARG((tOilOp id, tOilTypeSet as1, tOilTypeSet as2, tOilTypeSet as3));

extern tOilOp OilIdOpTS1 ELI_ARG((tOilType rt, tOilOp id, tOilTypeSet as1));
extern tOilOp OilIdOpTS2
  ELI_ARG((tOilType rt, tOilOp id, tOilTypeSet as1, tOilTypeSet as2));
extern tOilOp OilIdOpTS3
  ELI_ARG((tOilType rt, tOilOp id, tOilTypeSet as1, tOilTypeSet as2, tOilTypeSet as3));

extern tOilOp OilIdOp1 ELI_ARG((tOilOp id, tOilType at1));
extern tOilOp OilIdOp2 ELI_ARG((tOilOp id, tOilType at1, tOilType at2));
extern tOilOp OilIdOp3 ELI_ARG((tOilOp id, tOilType at1, tOilType at2, tOilType at3));

extern oilName OilTypeName ELI_ARG((tOilType t));
extern oilName OilOpName ELI_ARG((tOilOp op));
extern oilName OilClassName ELI_ARG((tOilClass cl));

extern tOilType OilClassInst0 ELI_ARG((tOilClass c, oilName id));
extern tOilType OilClassInst1 ELI_ARG((tOilClass c, oilName id, tOilType at1));
extern tOilType OilClassInst2
  ELI_ARG((tOilClass c, oilName id, tOilType at1, tOilType at2));

extern oilName OilNextName ELI_ARG((void));

extern tOilType	OilTypeIndex ELI_ARG((int index));
extern tOilOp OilOpIndex ELI_ARG((int index));
extern tOilClass OilClassIndex ELI_ARG((int index));

extern tOilOpSet OilIdOpSet ELI_ARG((tOilOp ind, tOilSetSig setsig, tOilType rt));
extern tOilOpSet OilAddOpSet ELI_ARG((tOilOpSet set, tOilOp op));
extern void OilFreeOpSet ELI_ARG((tOilOpSet set));

extern tOilOp OilHeadOS ELI_ARG((tOilOpSet set));
extern tOilOpSet OilTailOS ELI_ARG((tOilOpSet set));
extern int OilEmptyOS ELI_ARG((tOilOpSet set));

#ifdef MONITOR
/* Monitoring support for Oil values */

#define DAPTO_RESULTtOilType(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilType(e)    DAPTO_ARG_PTR(e, tOilType)

#define DAPTO_RESULTtOilOp(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilOp(e)    DAPTO_ARG_PTR(e, tOilOp)

#define DAPTO_RESULTtOilTypeSet(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilTypeSet(e)    DAPTO_ARG_PTR(e, tOilTypeSet)

#define DAPTO_RESULTtOilSetSig(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilSetSig(e)    DAPTO_ARG_PTR(e, tOilSetSig)

#define DAPTO_RESULTtOilArgSig(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilArgSig(e)    DAPTO_ARG_PTR(e, tOilArgSig)

#define DAPTO_RESULTtOilCoercionSeq(e) DAPTO_RESULT_PTR(e)
#define DAPTO_ARGtOilCoercionSeq(e)    DAPTO_ARG_PTR(e, tOilCoercionSeq)

#define DAPTO_RESULTtOilOpIdentification(e) DAPTO_RESULT_PTR(e)
#define DAPTO_RESULTtOilClassArgSig(e)      DAPTO_RESULT_PTR(e)
#define DAPTO_RESULTtOilClassOp(e)          DAPTO_RESULT_PTR(e)
#define DAPTO_RESULTtOilClassOpId(e)        DAPTO_RESULT_PTR(e)
#define DAPTO_RESULTtOilClass(e)            DAPTO_RESULT_PTR(e)

#endif

#endif
