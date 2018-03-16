static char rcsid[] = "$Id: oiladt2b.c,v 1.22 2009/08/05 22:06:06 profw Exp $";
/* Oil database dump module
   Copyright, 1989, The Regents of the University of Colorado */

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
#include "oiladt2.h"

#define ForDebugging 1

/* 'ForDebugging' is used by 'oiladt2b.c' to select the output of the
        compiler which contains the 'sID' component.  Originally designed to be
	removed for a 'release' to save space but never seen as worthwhile.
	*/

#ifndef WithIDs
	'WithIds' must be turned on !!!
	for both oiladt2b and oiladt2a
#endif


/******************************************************
  DumpFile - the file to dump the rep on
  */
  FILE * DumpFile;


/******************************************************
  Dump - increment state
  */
#define Dump t->sStat+=1; fprintf( DumpFile,


/******************************************************
  pRef - reference to a ptr
  */
#define pRef(str,dmp,comp) if(t->comp) dmp(t->comp)


/******************************************************
  First - check the status and emit 'extern' if necessary
  */
#define First(str) if (t->sStat>0) {\
    if (t->sStat==1) RecRef(t->sID,str); t->sStat+=1; return;} else \
    t->sStat+=1;


/******************************************************
  tRef - is the ptr a nil reference ??
  */
#define tRef(str,comp) (t->comp) ? FmtRef(t->comp->sID,str) : NilFmt


/******************************************************
  NilFmt - used for representing 'nil' ptr
  */
CONST char *NilFmt="0";


/******************************************************
  FmtBufs - set of circular buffers us for constructing ptr names
      (see FmtRef)
  */
static char Buf1[18];
static char Buf2[18];
static char Buf3[18];
static char Buf4[18];
char *FmtBufs[]={ Buf1, Buf2, Buf3, Buf4 };


/******************************************************
  FmtName - buffer use to rep name string
  */
char FmtName[41];



/******************************************************
  vOilBufIndex - index into FmtBufs
  */
int vOilBufIndex=0;



/******************************************************
  FmtRef - fmt a reference to a ptr
  */
char *
#if defined(__cplusplus) || defined(__STDC__)
FmtRef(int v, const char *s)
#else
FmtRef( v, s ) int v; char *s;
#endif
{
	char *rs;
    rs=FmtBufs[vOilBufIndex= (vOilBufIndex+1)%4];
    sprintf( rs, "&%s%d", s, v );
    return( rs );
  }


/******************************************************
  RecRef - a recursive reference requires an 'extern' declaration
  */
void
#if defined(__cplusplus) || defined(__STDC__)
RecRef(int v, const char *s)
#else
RecRef( v, s ) int v; char *s;
#endif
{
    fprintf(DumpFile, "\n  extern struct %s%d;\n", s, v );
  }


/******************************************************
  Object name prefixes
  */
CONST char
	*Ct="Oil_t",
	*Cs="Oil_s",
	*Ccc="Oil_cc",
	*Co="Oil_o",
	*Crs="Oil_rs",
	*Coid="Oil_oid",
	*Css="Oil_ss",
	*Ccoid="Oil_coid",
	*Cco="Oil_co",
	*Ctd="Oil_td",
	*Cc="Oil_c";


/******************************************************
  Declaration prefixes ( which type of object )
  */
CONST char
        *Et="Stype Oil_t",
        *Es="Ssig Oil_s",
        *Ecc="ScoercionSeq Oil_cc",
        *Eo="Sop Oil_o",
        *Ers="StypeSet Oil_rs",
        *Eoid="SopIdent Oil_oid",
        *Ecoid="SclassOpId Oil_coid",
        *Eco="SclassOp Oil_co",
        *Etd="SclassArgSig Oil_td",
	*Ec="Sclass Oil_c";


/******************************************************
  Declaration formats
  */

#ifdef ForDebugging

#define Dt "struct %s%d={ %d, 0, %s,\
 (tOilCoercionSeq)%s,\
 (tOilArgSig)%s,\
 (tOilTypeSet)%s,\
 (tOilOp)%s };\n",\
 Et,t->sID,
#define Ds "struct %s%d={ %d, 0,\
 (tOilArgSig)%s,\
 (tOilType)%s,\
 (tOilArgSig)%s };\n",\
 Es,t->sID,
#define Do "struct %s%d={ %d, 0, %s, %d,\
 (tOilArgSig)%s,\
 (tOilOp)%s,\
 (tOilOpIdentification)%s };\n",\
 Eo,t->sID,
#define Dcc "struct %s%d={ %d, 0,\
 (tOilType)%s,\
 (tOilCoercionSeq)%s,\
 (tOilOp)%s,\
 (tOilCoercionSeq)%s, %d };\n",\
 Ecc,t->sID,
#define Drs "struct %s%d={ %d, 0,\
 (tOilType)%s,\
 (tOilTypeSet)%s, %d };\n",\
 Ers,t->sID,
#define Doid "struct %s%d={ %d, 0,\
 (tOilOpIdentification)%s,\
 (tOilOp)%s };\n",\
 Eoid,t->sID,
#define Dtd "struct %s%d={ %d, 0,\
 (tOilClassArgSig)%s,\
 (tOilClassArgSig)%s, %s,\
 (tOilType)%s, %d };\n",\
 Etd,t->sID,
#define Dcoid "struct %s%d={ %d, 0,\
 (tOilClassOpId)%s,\
 (tOilOp)%s };\n",\
 Ecoid,t->sID,
#define Dco "struct %s%d={ %d, 0,\
 (tOilClassOp)%s, %s,\
 (tOilClassArgSig)%s, %d, %d,\
 (tOilClassOpId)%s };\n",\
 Eco,t->sID,
#define Dc "struct %s%d={ %d, 0, %s, %d,\
 (tOilClassOp)%s };\n",\
 Ec,t->sID,

#else

#define Dt "struct %s%d={ %s,\
 (tOilCoercionSeq)%s,\
 (tOilArgSig)%s,\
 (tOilTypeSet)%s,\
 (tOilOp)%s };\n",\
 Et,
#define Ds "struct %s%d={\
 (tOilArgSig)%s,\
 (tOilType)%s,\
 (tOilArgSig)%s };\n",\
 Es,
#define Do "struct %s%d={ %s, %d,\
 (tOilArgSig)%s,\
 (tOilOp)%s,\
 (tOilOpIdentification)%s };\n",\
 Eo,
#define Dcc "struct %s%d={\
 (tOilType)%s,\
 (tOilCoercionSeq)%s,\
 (tOilOp)%s,\
 (tOilCoercionSeq)%s, %d };\n",\
 Ecc,
#define Drs "struct %s%d={\
 (tOilType)%s,\
 (tOilTypeSet)%s, %d };\n",\
 Ers,
#define Doid "struct %s%d={\
 (tOilOpIdentification)%s,\
 (tOilOp)%s };\n",\
 Eoid,
#define Dtd "struct %s%d={\
 (tOilClassArgSig)%s,\
 (tOilClassArgSig)%s, %s,\
 (tOilType)%s, %d };\n",\
 Etd,
#define Dcoid "struct %s%d={\
 (tOilClassOpId)%s,\
 (tOilOp)%s };\n",\
 Ecoid,
#define Dco "struct %s%d={\
 (tOilClassOp)%s, %s,\
 (tOilClassArgSig)%s, %d, %d,\
 (tOilClassOpId)%s };\n",\
 Eco,
#define Dc "struct %s%d={ %s, %d,\
 (tOilClassOp)%s };\n",\
 Ec,

#endif

/******************************************************
  Some forward refs
  */

#if defined(__cplusplus) || defined(__STDC__)
extern void OilDumpCoercionCost(tOilCoercionSeq t);
extern void OilDumpOp(tOilOp t);
extern void OilDumpSig(tOilArgSig t);
extern void OilDumpTypeSet(tOilTypeSet t);
extern void OilDumpOpId(tOilOpIdentification t);
#else
extern void OilDumpCoercionCost(); /* ( t ) tOilCoercionSeq t; */
extern void OilDumpOp();
extern void OilDumpSig();
extern void OilDumpTypeSet();
extern void OilDumpOpId();
#endif

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpType(tOilType t)
#else
OilDumpType( t ) tOilType t;
#endif
{
  First(Et)
     pRef(Ccc,OilDumpCoercionCost,sCoercionCosts);
     pRef(Cs,OilDumpSig,sSigs);
     pRef(Crs,OilDumpTypeSet,sResultSets);
     pRef(Co,OilDumpOp,sCoercions);
 Dump
    Dt
    t->sID,
    RepName(FmtName,t->sName),
    tRef(Ccc,sCoercionCosts),
    tRef(Cs,sSigs),
    tRef(Crs,sResultSets),
    tRef(Co,sCoercions)
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpSig(tOilArgSig t)
#else
OilDumpSig( t ) tOilArgSig t;
#endif
{
  First(Es)
    pRef(Cs,OilDumpSig,sNext);
    pRef(Ct,OilDumpType,sArg);
    pRef(Cs,OilDumpSig,sSameType);
  Dump
    Ds
    t->sID,
    tRef(Cs,sNext),
    tRef(Ct,sArg),
    tRef(Cs,sSameType)
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpOp(tOilOp t)
#else
OilDumpOp( t ) tOilOp t;
#endif
{
  First(Eo)
    pRef(Cs,OilDumpSig,sArgs);
    pRef(Co,OilDumpOp,sInArcs);
    pRef(Coid,OilDumpOpId,sIndOps);
  Dump
    Do
    t->sID,
    RepName(FmtName,t->sName),
    t->sCost,
    tRef(Cs,sArgs),
    tRef(Co,sInArcs),
    tRef(Coid,sIndOps)
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpCoercionCost(tOilCoercionSeq t)
#else
OilDumpCoercionCost( t ) tOilCoercionSeq t;
#endif
{
  First(Ecc)
    pRef(Ct,OilDumpType,sResultType);
    pRef(Ccc,OilDumpCoercionCost,sNextCost);
    pRef(Co,OilDumpOp,sCoercionOp);
    pRef(Ccc,OilDumpCoercionCost,sCoercionSeq);
  Dump
    Dcc
    t->sID,
    tRef(Ct,sResultType),
    tRef(Ccc,sNextCost),
    tRef(Co,sCoercionOp),
    tRef(Ccc,sCoercionSeq),
    t->sCost
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpTypeSet(tOilTypeSet t)
#else
OilDumpTypeSet( t ) tOilTypeSet t;
#endif
{
  First(Ers)
    pRef(Ct,OilDumpType,sBaseType);
    pRef(Crs,OilDumpTypeSet,sNext);
  Dump
    Drs
    t->sID,
    tRef(Ct,sBaseType),
    tRef(Crs,sNext),
    t->sCost
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpOpId(tOilOpIdentification t)
#else
OilDumpOpId( t ) tOilOpIdentification t;
#endif
{
  First(Eoid)
    pRef(Coid,OilDumpOpId,sNext);
    pRef(Co,OilDumpOp,sOp);
 Dump
    Doid
    t->sID,
    tRef(Coid,sNext),
    tRef(Co,sOp)
    );
  }


CONST char * OilDumpArgDescInd[]= {
	"eClassRef",
	"eElementRef",
	"eSpecTypeRef"
  };

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpArgDesc(tOilClassArgSig t)
#else
OilDumpArgDesc( t ) tOilClassArgSig t;
#endif
{
  First(Etd)
    pRef(Ctd,OilDumpArgDesc,sAnother);
    pRef(Ctd,OilDumpArgDesc,sNext);
    pRef(Ct,OilDumpType,sRefdType);
  Dump
    Dtd
    t->sID,
    tRef(Ctd,sAnother),
    tRef(Ctd,sNext),
    OilDumpArgDescInd[((int)(t->sDescPattern))],
    tRef(Ct,sRefdType),
    t->sParamIndex
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpClassOpId(tOilClassOpId t)
#else
OilDumpClassOpId( t ) tOilClassOpId t;
#endif
{
  First(Ecoid)
    pRef(Ccoid,OilDumpClassOpId,sNext);
    pRef(Co,OilDumpOp,sOpInd);
  Dump
    Dcoid
    t->sID,
    tRef(Ccoid,sNext),
    tRef(Co,sOpInd)
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpClassOp(tOilClassOp t)
#else
OilDumpClassOp( t ) tOilClassOp t;
#endif
{
  First(Eco)
    pRef(Cco,OilDumpClassOp,sNext);
    pRef(Ctd,OilDumpArgDesc,sArgDesc);
    pRef(Ccoid,OilDumpClassOpId,sIdents);
  Dump
    Dco
    t->sID,
    tRef(Cco,sNext),
    RepName(FmtName,t->sName),
    tRef(Ctd,sArgDesc),
    t->sCost,
    t->isCoercion,
    tRef(Ccoid,sIdents)
    );
  }

void
#if defined(__cplusplus) || defined(__STDC__)
OilDumpClass(tOilClass t)
#else
OilDumpClass( t ) tOilClass t;
#endif
{
  First(Ec)
    pRef(Cco,OilDumpClassOp,sClassOps);
  Dump
    Dc
    t->sID,
    RepName(FmtName,t->sName),
    t->sNumArg,
    tRef(Cco,sClassOps)
    );
  }

FILE *
#if defined(__cplusplus) || defined(__STDC__)
OilDumpInit(char *fname)
#else
OilDumpInit(fname)
    char *fname;
#endif
{
  DumpFile= fopen(fname,"w");
#ifdef KeyID
  fprintf(DumpFile, "#include \"pdl_gen.h\"\n");
#endif
  fprintf(DumpFile, "#include \"oiladt2.h\"\n\n");
  return(DumpFile);
  }
