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
PTGNode PTGOutFile (const char *fn, PTGNode r)
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

#endif

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

struct _SPTG0   _PTGNULL = { (_PTGProc) _PrPTGNULL };

/* -------------------------------------------------------- */
/*          Node-Construction and Print-functions           */
/* -------------------------------------------------------- */

/* ============================ */

/* Implementation of Pattern GramRule */

typedef struct _SPTGGramRule{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGGramRule;

#ifdef PROTO_OK
static void _PrPTGGramRule(_PPTGGramRule n)
#else
static void _PrPTGGramRule(n)
	_PPTGGramRule n;
#endif
{
	PTG_OUTPUT_STRING(f, "RULE ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\t");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " END;\n");
}

#ifdef PROTO_OK
PTGNode PTGGramRule(CONST char* p1, PTGNode p2)
#else
PTGNode PTGGramRule(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGGramRule n;
	n = (_PPTGGramRule)MALLOC(sizeof(struct _SPTGGramRule));
	n->_print = (_PTGProc)_PrPTGGramRule;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern GramProd */

typedef struct _SPTGGramProd{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGGramProd;

#ifdef PROTO_OK
static void _PrPTGGramProd(_PPTGGramProd n)
#else
static void _PrPTGGramProd(n)
	_PPTGGramProd n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " ::= ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGGramProd(CONST char* p1, PTGNode p2)
#else
PTGNode PTGGramProd(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGGramProd n;
	n = (_PPTGGramProd)MALLOC(sizeof(struct _SPTGGramProd));
	n->_print = (_PTGProc)_PrPTGGramProd;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern GramListof */

typedef struct _SPTGGramListof{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGGramListof;

#ifdef PROTO_OK
static void _PrPTGGramListof(_PPTGGramListof n)
#else
static void _PrPTGGramListof(n)
	_PPTGGramListof n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " LISTOF ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGGramListof(CONST char* p1, PTGNode p2)
#else
PTGNode PTGGramListof(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGGramListof n;
	n = (_PPTGGramListof)MALLOC(sizeof(struct _SPTGGramListof));
	n->_print = (_PTGProc)_PrPTGGramListof;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern GramLiteral */

typedef struct _SPTGGramLiteral{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGGramLiteral;

#ifdef PROTO_OK
static void _PrPTGGramLiteral(_PPTGGramLiteral n)
#else
static void _PrPTGGramLiteral(n)
	_PPTGGramLiteral n;
#endif
{
	PTG_OUTPUT_STRING(f, "'");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "'");
}

#ifdef PROTO_OK
PTGNode PTGGramLiteral(CONST char* p1)
#else
PTGNode PTGGramLiteral(p1)

CONST char* p1;
#endif
{
	_PPTGGramLiteral n;
	n = (_PPTGGramLiteral)MALLOC(sizeof(struct _SPTGGramLiteral));
	n->_print = (_PTGProc)_PrPTGGramLiteral;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern GramSymbol */

typedef struct _SPTGGramSymbol{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGGramSymbol;

#ifdef PROTO_OK
static void _PrPTGGramSymbol(_PPTGGramSymbol n)
#else
static void _PrPTGGramSymbol(n)
	_PPTGGramSymbol n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGGramSymbol(CONST char* p1)
#else
PTGNode PTGGramSymbol(p1)

CONST char* p1;
#endif
{
	_PPTGGramSymbol n;
	n = (_PPTGGramSymbol)MALLOC(sizeof(struct _SPTGGramSymbol));
	n->_print = (_PTGProc)_PrPTGGramSymbol;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern GramGenSymbol */

typedef struct _SPTGGramGenSymbol{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGGramGenSymbol;

#ifdef PROTO_OK
static void _PrPTGGramGenSymbol(_PPTGGramGenSymbol n)
#else
static void _PrPTGGramGenSymbol(n)
	_PPTGGramGenSymbol n;
#endif
{
	PTG_OUTPUT_STRING(f, "$");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGGramGenSymbol(CONST char* p1)
#else
PTGNode PTGGramGenSymbol(p1)

CONST char* p1;
#endif
{
	_PPTGGramGenSymbol n;
	n = (_PPTGGramGenSymbol)MALLOC(sizeof(struct _SPTGGramGenSymbol));
	n->_print = (_PTGProc)_PrPTGGramGenSymbol;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern GramSeq */

typedef struct _SPTGGramSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGGramSeq;

#ifdef PROTO_OK
static void _PrPTGGramSeq(_PPTGGramSeq n)
#else
static void _PrPTGGramSeq(n)
	_PPTGGramSeq n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, " ");
	}
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGGramSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGGramSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGGramSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGGramSeq)MALLOC(sizeof(struct _SPTGGramSeq));
	n->_print = (_PTGProc)_PrPTGGramSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern GramAltSeq */

typedef struct _SPTGGramAltSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGGramAltSeq;

#ifdef PROTO_OK
static void _PrPTGGramAltSeq(_PPTGGramAltSeq n)
#else
static void _PrPTGGramAltSeq(n)
	_PPTGGramAltSeq n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, " | ");
	}
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGGramAltSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGGramAltSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGGramAltSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGGramAltSeq)MALLOC(sizeof(struct _SPTGGramAltSeq));
	n->_print = (_PTGProc)_PrPTGGramAltSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Seq */

typedef struct _SPTGSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSeq;

#ifdef PROTO_OK
static void _PrPTGSeq(_PPTGSeq n)
#else
static void _PrPTGSeq(n)
	_PPTGSeq n;
#endif
{
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGSeq)MALLOC(sizeof(struct _SPTGSeq));
	n->_print = (_PTGProc)_PrPTGSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}

/* ============================ */

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

