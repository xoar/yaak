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

#include <stdio.h>
#include <stdlib.h>

#include "ptg_gen.h"
#include "obstack.h"

/* -------------------------------------------------------- */
/*                      Memory Management                   */
/* -------------------------------------------------------- */

static Obstack _PTGObstack;
static void *_PTGFirstObj = NULL;

static void _PTGInit()
{
	if (_PTGFirstObj)
		return;
	obstack_init(&_PTGObstack);
	_PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}

void PTGFree()
{
	obstack_free(&_PTGObstack, _PTGFirstObj);
	_PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}


#if defined(__STDC__) || defined(__cplusplus)
static void *MALLOC(int size)
#else
static void *MALLOC(size) int size;
#endif
{
	if (! _PTGFirstObj)
		_PTGInit();
	return (obstack_alloc(&_PTGObstack, size));
}

/* -------------------------------------------------------- */
/*                       Output-functions                   */
/* -------------------------------------------------------- */

static PTG_OUTPUT_FILE f;
static char buffer[40];

#if PTG_OUTPUT_DEFAULT
#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOut (PTGNode r)
#else
PTGNode PTGOut (r)
	PTGNode r;
#endif
{
	f = stdout;
	if (r) {
		(* (r->_print)) (r);
	}
	return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFile (char *fn, PTGNode r)
#else
PTGNode PTGOutFile (fn, r)
	char * fn; PTGNode r;
#endif
{
	if ((f = fopen(fn, "w"))  == (FILE *)NULL)
	{
		fprintf(stderr, "ERROR: PTGOutFile: output file '%s' can't be opened.\n",fn);
		exit(1);
	}
	if (r)
		(* (r->_print)) (r);
	fclose(f);
	return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFPtr(FILE *fptr, PTGNode r)
#else
PTGNode PTGOutFPtr(fptr, r)
	FILE *fptr; PTGNode r;
#endif
{
	if ((f = fptr) == (FILE *)NULL)
	{
		fprintf(stderr, "ERROR: PTGOutFPtr: output file not open.\n");
		exit(1);
	}
	if (r)
		(* (r->_print)) (r);
	return (r);
}

#else /* PTG_OUTPUT_FILE defined by User */
#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGProcess(PTG_OUTPUT_FILE file, PTGNode r)
#else
PTGNode PTGProcess(file, r)
	PTG_OUTPUT_FILE file; PTGNode r;
#endif
{
	f = file;
	if (r)
		(* (r->_print)) (r);
	return (r);
}
#endif
/* -------------------------------------------------------- */
/*                            PTGNULL                       */
/* -------------------------------------------------------- */

/* Define PTGNULL as a PTGNode that prints nothing. */

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGNULL(_PPTG0 n)
#else
static void _PrPTGNULL(n)
_PPTG0 n;
#endif
{(void)n; /* function printing nothing */}

struct _SPTG0   _PTGNULL = { _PrPTGNULL };

/* -------------------------------------------------------- */
/*          Node-Construction and Print-functions           */
/* -------------------------------------------------------- */


/* Implementation of Pattern TOPT_RDS */

typedef struct _SPTGTOPT_RDS{
	_PTGProc _print;
} * _PPTGTOPT_RDS;

#ifdef PROTO_OK
static void _PrPTGTOPT_RDS(_PPTGTOPT_RDS n)
#else
static void _PrPTGTOPT_RDS(n)
	_PPTGTOPT_RDS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Row Displacement Scheme is performed for the terminal-table */\n\
\n\
#define SIGMAP(row , col) (sigmap[row][col >> 3] >> (col & 0x0007)) & 0x01\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
\t{\\\n\
\t  register    U_SHORT j;\\\n\
\t  j = conv[ term ]; \\\n\
\t  if( SIGMAP( sigrowind[RorS], sigcolind[j] ) )  { \\\n\
\t    j = ttab[ trowptr[RorS] + j ]; \\\n\
\t    Act  = j & ACTIONMASK; \\\n\
\t    RorS = j & OPERANDMASK; \\\n\
\t  }\\\n\
\t  else \\\n\
\t    Act  = 0; \\\n\
\t}\n\n");
}

static struct _SPTGTOPT_RDS _sptgTOPT_RDS = { _PrPTGTOPT_RDS };

#ifdef PROTO_OK
PTGNode PTGTOPT_RDS(void)
#else
PTGNode PTGTOPT_RDS()
#endif
{
	return (PTGNode)(&_sptgTOPT_RDS);
}

/* Implementation of Pattern NOPT_RDS */

typedef struct _SPTGNOPT_RDS{
	_PTGProc _print;
} * _PPTGNOPT_RDS;

#ifdef PROTO_OK
static void _PrPTGNOPT_RDS(_PPTGNOPT_RDS n)
#else
static void _PrPTGNOPT_RDS(n)
	_PPTGNOPT_RDS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Row Displacement Scheme is performed for the nonterminal-table */\n\
\n\
#define GET_NTABENTRY(RorS, Act, State, lhsnt) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  j = ntab[ nrowptr[State] + lhsnt ]; \\\n\
\t  Act = j & ACTIONMASK; \\\n\
\t  RorS = j & OPERANDMASK; \\\n\
\t}\n\n");
}

static struct _SPTGNOPT_RDS _sptgNOPT_RDS = { _PrPTGNOPT_RDS };

#ifdef PROTO_OK
PTGNode PTGNOPT_RDS(void)
#else
PTGNode PTGNOPT_RDS()
#endif
{
	return (PTGNode)(&_sptgNOPT_RDS);
}

/* Implementation of Pattern TOPT_RCSA */

typedef struct _SPTGTOPT_RCSA{
	_PTGProc _print;
} * _PPTGTOPT_RCSA;

#ifdef PROTO_OK
static void _PrPTGTOPT_RCSA(_PPTGTOPT_RCSA n)
#else
static void _PrPTGTOPT_RCSA(n)
	_PPTGTOPT_RCSA n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* The simple Row Column Scheme is performed for the terminal-table */\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
\t{ \\\n\
\t  register unsigned int\ti,j,k; \\\n\
\t  Act  = 0; \\\n\
\t  k = tbase[(RorS) + 1];\\\n\
\t  for( i = tbase[RorS]; i < k; i++ ) { \\\n\
\t       if((ttab[i] & 0x0000FFFF) == term )  { \\\n\
\t           j = ttab[i] >> 16; \\\n\
\t           Act  = j & ACTIONMASK; \\\n\
\t           RorS = j & OPERANDMASK; \\\n\
\t           break; \\\n\
\t       } \\\n\
\t  }\\\n\
\t}\n\n");
}

static struct _SPTGTOPT_RCSA _sptgTOPT_RCSA = { _PrPTGTOPT_RCSA };

#ifdef PROTO_OK
PTGNode PTGTOPT_RCSA(void)
#else
PTGNode PTGTOPT_RCSA()
#endif
{
	return (PTGNode)(&_sptgTOPT_RCSA);
}

/* Implementation of Pattern NOPT_RCSA */

typedef struct _SPTGNOPT_RCSA{
	_PTGProc _print;
} * _PPTGNOPT_RCSA;

#ifdef PROTO_OK
static void _PrPTGNOPT_RCSA(_PPTGNOPT_RCSA n)
#else
static void _PrPTGNOPT_RCSA(n)
	_PPTGNOPT_RCSA n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the simple Row Column Scheme is performed for the nonterminal-table */\n\
\n\
#define GET_NTABENTRY( RorS, Act, State, lhsnt ) \\\n\
\t{ \\\n\
\t  register unsigned int i,j,k; \\\n\
\t  k = nbase[State + 1];\\\n\
\t  for( i = nbase[State]; i < k; i++ ) {\\\n\
\t      if((ntab[i] & 0x0000FFFF) == lhsnt )  { \\\n\
\t          j = ntab[i] >> 16; \\\n\
\t          Act  = j & ACTIONMASK; \\\n\
\t          RorS = j & OPERANDMASK; \\\n\
\t          break; \\\n\
\t      } \\\n\
\t  } \\\n\
\t}\n\n");
}

static struct _SPTGNOPT_RCSA _sptgNOPT_RCSA = { _PrPTGNOPT_RCSA };

#ifdef PROTO_OK
PTGNode PTGNOPT_RCSA(void)
#else
PTGNode PTGNOPT_RCSA()
#endif
{
	return (PTGNode)(&_sptgNOPT_RCSA);
}

/* Implementation of Pattern TOPT_GCS */

typedef struct _SPTGTOPT_GCS{
	_PTGProc _print;
} * _PPTGTOPT_GCS;

#ifdef PROTO_OK
static void _PrPTGTOPT_GCS(_PPTGTOPT_GCS n)
#else
static void _PrPTGTOPT_GCS(n)
	_PPTGTOPT_GCS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Graph Colouring Scheme is performed for the terminal-table */\n\
\n\
#define SIGMAP(row, col) (sigmap[row][col >> 3] >> (col & 0x0007)) & 0x01\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
        {\\\n\
          register      U_SHORT j;\\\n\
          j = conv[ term ]; \\\n\
          if( SIGMAP( sigrowind[RorS], sigcolind[ j ] ) )  { \\\n\
              j = ttab[ trowptr[ RorS ] ][ tcolptr[ j ] ]; \\\n\
              Act  = j & ACTIONMASK; \\\n\
              RorS = j & OPERANDMASK; \\\n\
          } \\\n\
          else \\\n\
              Act  = 0; \\\n\
        }\n\n");
}

static struct _SPTGTOPT_GCS _sptgTOPT_GCS = { _PrPTGTOPT_GCS };

#ifdef PROTO_OK
PTGNode PTGTOPT_GCS(void)
#else
PTGNode PTGTOPT_GCS()
#endif
{
	return (PTGNode)(&_sptgTOPT_GCS);
}

/* Implementation of Pattern NOPT_GCS */

typedef struct _SPTGNOPT_GCS{
	_PTGProc _print;
} * _PPTGNOPT_GCS;

#ifdef PROTO_OK
static void _PrPTGNOPT_GCS(_PPTGNOPT_GCS n)
#else
static void _PrPTGNOPT_GCS(n)
	_PPTGNOPT_GCS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Graph Colouring Scheme is performed for the nonterminal-table */\n\
\n\
#define GET_NTABENTRY( RorS, Act, State, lhsnt) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  j = ntab[ nrowptr[State] ][ ncolptr[lhsnt] ]; \\\n\
\t  Act  = j & ACTIONMASK; \\\n\
\t  RorS = j & OPERANDMASK; \\\n\
\t}\n\n");
}

static struct _SPTGNOPT_GCS _sptgNOPT_GCS = { _PrPTGNOPT_GCS };

#ifdef PROTO_OK
PTGNode PTGNOPT_GCS(void)
#else
PTGNode PTGNOPT_GCS()
#endif
{
	return (PTGNode)(&_sptgNOPT_GCS);
}

/* Implementation of Pattern TOPT_LES */

typedef struct _SPTGTOPT_LES{
	_PTGProc _print;
} * _PPTGTOPT_LES;

#ifdef PROTO_OK
static void _PrPTGTOPT_LES(_PPTGTOPT_LES n)
#else
static void _PrPTGTOPT_LES(n)
	_PPTGTOPT_LES n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Line Elimination Scheme is performed for the terminal-table */\n\
\n\
#define SIGMAP(row , col) (sigmap[row][col >> 3] >> (col & 0x0007)) & 0x01\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  j = conv[term]; \\\n\
\t  if( SIGMAP( sigrowind[RorS], sigcolind[j] ) )  { \\\n\
\t       if( tdecrow[RorS] < tdeccol[j] ) \\\n\
\t           j = trowval[RorS]; \\\n\
\t       else if( tdecrow[RorS] > tdeccol[j] ) \\\n\
\t           j = tcolval[j]; \\\n\
\t       else \\\n\
\t           j = ttab[ trowval[RorS] ][ tcolval[j] ]; \\\n\
\t       Act  = j & ACTIONMASK; \\\n\
\t       RorS = j & OPERANDMASK; \\\n\
\t  } \\\n\
\t  else \\\n\
\t       Act  = 0; \\\n\
\t}\n\n");
}

static struct _SPTGTOPT_LES _sptgTOPT_LES = { _PrPTGTOPT_LES };

#ifdef PROTO_OK
PTGNode PTGTOPT_LES(void)
#else
PTGNode PTGTOPT_LES()
#endif
{
	return (PTGNode)(&_sptgTOPT_LES);
}

/* Implementation of Pattern NOPT_LES */

typedef struct _SPTGNOPT_LES{
	_PTGProc _print;
} * _PPTGNOPT_LES;

#ifdef PROTO_OK
static void _PrPTGNOPT_LES(_PPTGNOPT_LES n)
#else
static void _PrPTGNOPT_LES(n)
	_PPTGNOPT_LES n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Line Elimination Scheme is performed for the nonterminal-table */\n\
\n\
#define GET_NTABENTRY( RorS, Act, State, lhsnt) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  if( ndecrow[State] < ndeccol[lhsnt] ) \\\n\
\t      j = nrowval[State]; \\\n\
\t  else if( ndecrow[State] > ndeccol[lhsnt] ) \\\n\
\t      j = ncolval[lhsnt]; \\\n\
\t  else \\\n\
\t      j = ntab[ nrowval[State] ][ ncolval[lhsnt] ]; \\\n\
\t  Act  = j & ACTIONMASK; \\\n\
\t  RorS = j & OPERANDMASK;\\\n\
\t}\n\n");
}

static struct _SPTGNOPT_LES _sptgNOPT_LES = { _PrPTGNOPT_LES };

#ifdef PROTO_OK
PTGNode PTGNOPT_LES(void)
#else
PTGNode PTGNOPT_LES()
#endif
{
	return (PTGNode)(&_sptgNOPT_LES);
}

/* Implementation of Pattern TOPT_SDS */

typedef struct _SPTGTOPT_SDS{
	_PTGProc _print;
} * _PPTGTOPT_SDS;

#ifdef PROTO_OK
static void _PrPTGTOPT_SDS(_PPTGTOPT_SDS n)
#else
static void _PrPTGTOPT_SDS(n)
	_PPTGTOPT_SDS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Significant Distance Scheme is performed for the terminal-table */\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  j = conv[ term ]; \\\n\
\t  if( j < tfirstptr[RorS]  ||  j > tlastptr[RorS] ) \\\n\
\t    Act  = 0; \\\n\
\t  else { \\\n\
\t    j = ttab[ trowptr[RorS] + j ]; \\\n\
\t    Act  = j & ACTIONMASK; \\\n\
\t    RorS = j & OPERANDMASK; \\\n\
\t  }\\\n\
\t}\n\n");
}

static struct _SPTGTOPT_SDS _sptgTOPT_SDS = { _PrPTGTOPT_SDS };

#ifdef PROTO_OK
PTGNode PTGTOPT_SDS(void)
#else
PTGNode PTGTOPT_SDS()
#endif
{
	return (PTGNode)(&_sptgTOPT_SDS);
}

/* Implementation of Pattern NOPT_SDS */

typedef struct _SPTGNOPT_SDS{
	_PTGProc _print;
} * _PPTGNOPT_SDS;

#ifdef PROTO_OK
static void _PrPTGNOPT_SDS(_PPTGNOPT_SDS n)
#else
static void _PrPTGNOPT_SDS(n)
	_PPTGNOPT_SDS n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Significant Distance Scheme is performed for the nonterminal-table */\n\
\n\
#define GET_NTABENTRY( RorS, Act, State, lhsnt) \\\n\
\t{\\\n\
\t  register      U_SHORT j;\\\n\
\t  j = ntab[ nrowptr[State] + lhsnt ]; \\\n\
\t  Act  =  j & ACTIONMASK; \\\n\
\t  RorS =  j & OPERANDMASK; \\\n\
\t}\n\n");
}

static struct _SPTGNOPT_SDS _sptgNOPT_SDS = { _PrPTGNOPT_SDS };

#ifdef PROTO_OK
PTGNode PTGNOPT_SDS(void)
#else
PTGNode PTGNOPT_SDS()
#endif
{
	return (PTGNode)(&_sptgNOPT_SDS);
}

/* Implementation of Pattern TOPT_RCSB */

typedef struct _SPTGTOPT_RCSB{
	_PTGProc _print;
} * _PPTGTOPT_RCSB;

#ifdef PROTO_OK
static void _PrPTGTOPT_RCSB(_PPTGTOPT_RCSB n)
#else
static void _PrPTGTOPT_RCSB(n)
	_PPTGTOPT_RCSB n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Row Column Scheme is performed for the terminal-table */\n\
/* with merging of equal rows                                */\n\
\n\
#define GET_TTABENTRY( RorS, Act, term ) \\\n\
\t{\\\n\
\t  register unsigned int i,j,k; \\\n\
\t  Act  = 0; \\\n\
\t  k = tbase[trpt[RorS] + 1]; \\\n\
\t  for( i = tbase[trpt[RorS]]; i < k; i++ ) { \\\n\
\t      if((ttab[i] & 0x0000FFFF) == term )  { \\\n\
\t          j = ttab[i] >> 16; \\\n\
\t          Act  = j & ACTIONMASK; \\\n\
\t          RorS = j & OPERANDMASK; \\\n\
\t          break; \\\n\
\t      } \\\n\
\t  }\\\n\
\t}\n\n");
}

static struct _SPTGTOPT_RCSB _sptgTOPT_RCSB = { _PrPTGTOPT_RCSB };

#ifdef PROTO_OK
PTGNode PTGTOPT_RCSB(void)
#else
PTGNode PTGTOPT_RCSB()
#endif
{
	return (PTGNode)(&_sptgTOPT_RCSB);
}

/* Implementation of Pattern NOPT_RCSB */

typedef struct _SPTGNOPT_RCSB{
	_PTGProc _print;
} * _PPTGNOPT_RCSB;

#ifdef PROTO_OK
static void _PrPTGNOPT_RCSB(_PPTGNOPT_RCSB n)
#else
static void _PrPTGNOPT_RCSB(n)
	_PPTGNOPT_RCSB n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* the Row Column Scheme is performed for the nonterminal-table */\n\
/* with merging of equal rows                                   */\n\
\n\
#define GET_NTABENTRY( RorS, Act, State, lhsnt ) \\\n\
\t{ \\\n\
\t  register unsigned int i,j,k; \\\n\
\t  k = nbase[nrpt[State] + 1]; \\\n\
\t  for( i = nbase[nrpt[State]]; i < k; i++ ) { \\\n\
\t      if((ntab[i] & 0x0000FFFF) == lhsnt )  { \\\n\
\t          j = ntab[i] >> 16; \\\n\
\t          Act  = j & ACTIONMASK; \\\n\
\t          RorS = j & OPERANDMASK; \\\n\
\t          break; \\\n\
\t      } \\\n\
\t  } \\\n\
\t}\n\n");
}

static struct _SPTGNOPT_RCSB _sptgNOPT_RCSB = { _PrPTGNOPT_RCSB };

#ifdef PROTO_OK
PTGNode PTGNOPT_RCSB(void)
#else
PTGNode PTGNOPT_RCSB()
#endif
{
	return (PTGNode)(&_sptgNOPT_RCSB);
}


/* -------------------------------------------------------- */
/*                  Default Output Functions                */
/* -------------------------------------------------------- */


#ifdef PROTO_OK
void _PTGPrintInt(PTG_OUTPUT_FILE file, int param)
#else
void _PTGPrintInt(file, param)
	PTG_OUTPUT_FILE file; int param;
#endif
{    /* used for short and int */
	sprintf(buffer,"%d",param);
	PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintLong(PTG_OUTPUT_FILE file, long param)
#else
void _PTGPrintLong(file, param)
	PTG_OUTPUT_FILE file; long param;
#endif
{
	sprintf(buffer,"%ld",param);
	PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintDouble(PTG_OUTPUT_FILE file, double param)
#else
void _PTGPrintDouble(file, param)
	PTG_OUTPUT_FILE file; double param;
#endif
{    /* used for float and double */
	sprintf(buffer,"%g",param);
	PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintChar(PTG_OUTPUT_FILE file, char param)
#else
void _PTGPrintChar(file, param)
	PTG_OUTPUT_FILE file; char param;
#endif
{
	buffer[0] = param;
	buffer[1] = 0;
	PTG_OUTPUT_STRING(file,buffer);
}

