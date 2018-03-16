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

/* Implementation of Pattern Id */

typedef struct _SPTGId{
	_PTGProc _print;
	int p1;
} * _PPTGId;

#ifdef PROTO_OK
static void _PrPTGId(_PPTGId n)
#else
static void _PrPTGId(n)
	_PPTGId n;
#endif
{
	PtgOutId(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGId(int p1)
#else
PTGNode PTGId(p1)

int p1;
#endif
{
	_PPTGId n;
	n = (_PPTGId)MALLOC(sizeof(struct _SPTGId));
	n->_print = (_PTGProc)_PrPTGId;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AsIs */

typedef struct _SPTGAsIs{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGAsIs;

#ifdef PROTO_OK
static void _PrPTGAsIs(_PPTGAsIs n)
#else
static void _PrPTGAsIs(n)
	_PPTGAsIs n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGAsIs(CONST char* p1)
#else
PTGNode PTGAsIs(p1)

CONST char* p1;
#endif
{
	_PPTGAsIs n;
	n = (_PPTGAsIs)MALLOC(sizeof(struct _SPTGAsIs));
	n->_print = (_PTGProc)_PrPTGAsIs;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Numb */

typedef struct _SPTGNumb{
	_PTGProc _print;
	int p1;
} * _PPTGNumb;

#ifdef PROTO_OK
static void _PrPTGNumb(_PPTGNumb n)
#else
static void _PrPTGNumb(n)
	_PPTGNumb n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGNumb(int p1)
#else
PTGNode PTGNumb(p1)

int p1;
#endif
{
	_PPTGNumb n;
	n = (_PPTGNumb)MALLOC(sizeof(struct _SPTGNumb));
	n->_print = (_PTGProc)_PrPTGNumb;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CString */

typedef struct _SPTGCString{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGCString;

#ifdef PROTO_OK
static void _PrPTGCString(_PPTGCString n)
#else
static void _PrPTGCString(n)
	_PPTGCString n;
#endif
{
	CPtgOutstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGCString(CONST char* p1)
#else
PTGNode PTGCString(p1)

CONST char* p1;
#endif
{
	_PPTGCString n;
	n = (_PPTGCString)MALLOC(sizeof(struct _SPTGCString));
	n->_print = (_PTGProc)_PrPTGCString;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CChar */

typedef struct _SPTGCChar{
	_PTGProc _print;
	int p1;
} * _PPTGCChar;

#ifdef PROTO_OK
static void _PrPTGCChar(_PPTGCChar n)
#else
static void _PrPTGCChar(n)
	_PPTGCChar n;
#endif
{
	CPtgOutchar(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGCChar(int p1)
#else
PTGNode PTGCChar(p1)

int p1;
#endif
{
	_PPTGCChar n;
	n = (_PPTGCChar)MALLOC(sizeof(struct _SPTGCChar));
	n->_print = (_PTGProc)_PrPTGCChar;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PString */

typedef struct _SPTGPString{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGPString;

#ifdef PROTO_OK
static void _PrPTGPString(_PPTGPString n)
#else
static void _PrPTGPString(n)
	_PPTGPString n;
#endif
{
	PPtgOutstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGPString(CONST char* p1)
#else
PTGNode PTGPString(p1)

CONST char* p1;
#endif
{
	_PPTGPString n;
	n = (_PPTGPString)MALLOC(sizeof(struct _SPTGPString));
	n->_print = (_PTGProc)_PrPTGPString;
	n->p1 = p1;
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


/* Implementation of Pattern CommaSeq */

typedef struct _SPTGCommaSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGCommaSeq;

#ifdef PROTO_OK
static void _PrPTGCommaSeq(_PPTGCommaSeq n)
#else
static void _PrPTGCommaSeq(n)
	_PPTGCommaSeq n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ", ");
	}
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGCommaSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGCommaSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGCommaSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGCommaSeq)MALLOC(sizeof(struct _SPTGCommaSeq));
	n->_print = (_PTGProc)_PrPTGCommaSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Eol */

typedef struct _SPTGEol{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGEol;

#ifdef PROTO_OK
static void _PrPTGEol(_PPTGEol n)
#else
static void _PrPTGEol(n)
	_PPTGEol n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGEol(PTGNode p1)
#else
PTGNode PTGEol(p1)

PTGNode p1;
#endif
{
	_PPTGEol n;
	n = (_PPTGEol)MALLOC(sizeof(struct _SPTGEol));
	n->_print = (_PTGProc)_PrPTGEol;
	n->p1 = p1;
	return (PTGNode)n;
}


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


/* Implementation of Pattern UsedSymbols */

typedef struct _SPTGUsedSymbols{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGUsedSymbols;

#ifdef PROTO_OK
static void _PrPTGUsedSymbols(_PPTGUsedSymbols n)
#else
static void _PrPTGUsedSymbols(n)
	_PPTGUsedSymbols n;
#endif
{
	PTG_OUTPUT_STRING(f, "USED TREE SYMBOLS:");
	IndentIncr(f);
	n->p1->_print(n->p1);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "USED CLASS SYMBOLS:");
	IndentIncr(f);
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "RULES:");
	IndentIncr(f);
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
}

#ifdef PROTO_OK
PTGNode PTGUsedSymbols(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGUsedSymbols(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGUsedSymbols n;
	n = (_PPTGUsedSymbols)MALLOC(sizeof(struct _SPTGUsedSymbols));
	n->_print = (_PTGProc)_PrPTGUsedSymbols;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Symbol */

typedef struct _SPTGSymbol{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGSymbol;

#ifdef PROTO_OK
static void _PrPTGSymbol(_PPTGSymbol n)
#else
static void _PrPTGSymbol(n)
	_PPTGSymbol n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, n->p1);
	n->p2->_print(n->p2);
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "direct INHERITS ");
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "   all INHERITS ");
	n->p4->_print(n->p4);
	IndentDecr(f);
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "ATTRIBUTES");
	n->p5->_print(n->p5);
	IndentDecr(f);
	IndentNewLine(f);
}

#ifdef PROTO_OK
PTGNode PTGSymbol(CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGSymbol(p1, p2, p3, p4, p5)

CONST char* p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGSymbol n;
	n = (_PPTGSymbol)MALLOC(sizeof(struct _SPTGSymbol));
	n->_print = (_PTGProc)_PrPTGSymbol;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern Rule */

typedef struct _SPTGRule{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGRule;

#ifdef PROTO_OK
static void _PrPTGRule(_PPTGRule n)
#else
static void _PrPTGRule(n)
	_PPTGRule n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, n->p1);
	n->p2->_print(n->p2);
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "ATTRIBUTES");
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
}

#ifdef PROTO_OK
PTGNode PTGRule(CONST char* p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGRule(p1, p2, p3)

CONST char* p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGRule n;
	n = (_PPTGRule)MALLOC(sizeof(struct _SPTGRule));
	n->_print = (_PTGProc)_PrPTGRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Coord */

typedef struct _SPTGCoord{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGCoord;

#ifdef PROTO_OK
static void _PrPTGCoord(_PPTGCoord n)
#else
static void _PrPTGCoord(n)
	_PPTGCoord n;
#endif
{
	PTG_OUTPUT_STRING(f, " (");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGCoord(int p1, int p2)
#else
PTGNode PTGCoord(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGCoord n;
	n = (_PPTGCoord)MALLOC(sizeof(struct _SPTGCoord));
	n->_print = (_PTGProc)_PrPTGCoord;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Attribute */

typedef struct _SPTGAttribute{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGAttribute;

#ifdef PROTO_OK
static void _PrPTGAttribute(_PPTGAttribute n)
#else
static void _PrPTGAttribute(n)
	_PPTGAttribute n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ": ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	n->p4->_print(n->p4);
	n->p5->_print(n->p5);
}

#ifdef PROTO_OK
PTGNode PTGAttribute(CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGAttribute(p1, p2, p3, p4, p5)

CONST char* p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGAttribute n;
	n = (_PPTGAttribute)MALLOC(sizeof(struct _SPTGAttribute));
	n->_print = (_PTGProc)_PrPTGAttribute;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern DefaultType */

typedef struct _SPTGDefaultType{
	_PTGProc _print;
} * _PPTGDefaultType;

#ifdef PROTO_OK
static void _PrPTGDefaultType(_PPTGDefaultType n)
#else
static void _PrPTGDefaultType(n)
	_PPTGDefaultType n;
#endif
{
	PTG_OUTPUT_STRING(f, " (by default)");
}

static struct _SPTGDefaultType _sptgDefaultType = { (_PTGProc) _PrPTGDefaultType };

#ifdef PROTO_OK
PTGNode PTGDefaultType(void)
#else
PTGNode PTGDefaultType()
#endif
{
	return (PTGNode)(&_sptgDefaultType);
}


/* Implementation of Pattern InhComputations */

typedef struct _SPTGInhComputations{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGInhComputations;

#ifdef PROTO_OK
static void _PrPTGInhComputations(_PPTGInhComputations n)
#else
static void _PrPTGInhComputations(n)
	_PPTGInhComputations n;
#endif
{
	PTG_OUTPUT_STRING(f, "SYMBOL computation is inherited by RULEs:\n\n");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGInhComputations(PTGNode p1)
#else
PTGNode PTGInhComputations(p1)

PTGNode p1;
#endif
{
	_PPTGInhComputations n;
	n = (_PPTGInhComputations)MALLOC(sizeof(struct _SPTGInhComputations));
	n->_print = (_PTGProc)_PrPTGInhComputations;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern InhComp */

typedef struct _SPTGInhComp{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGInhComp;

#ifdef PROTO_OK
static void _PrPTGInhComp(_PPTGInhComp n)
#else
static void _PrPTGInhComp(n)
	_PPTGInhComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "line ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " inherited by lines ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGInhComp(PTGNode p1, PTGNode p2)
#else
PTGNode PTGInhComp(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGInhComp n;
	n = (_PPTGInhComp)MALLOC(sizeof(struct _SPTGInhComp));
	n->_print = (_PTGProc)_PrPTGInhComp;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern RemoteInfo */

typedef struct _SPTGRemoteInfo{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGRemoteInfo;

#ifdef PROTO_OK
static void _PrPTGRemoteInfo(_PPTGRemoteInfo n)
#else
static void _PrPTGRemoteInfo(n)
	_PPTGRemoteInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "INCLUDING Constructs:");
	IndentIncr(f);
	IndentNewLine(f);
	IndentNewLine(f);
	n->p1->_print(n->p1);
	IndentDecr(f);
	IndentNewLine(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "CONSTITUENT Constructs:");
	IndentIncr(f);
	IndentNewLine(f);
	IndentNewLine(f);
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "CONSTITUENTS Constructs:");
	IndentIncr(f);
	IndentNewLine(f);
	IndentNewLine(f);
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	IndentNewLine(f);
}

#ifdef PROTO_OK
PTGNode PTGRemoteInfo(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGRemoteInfo(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGRemoteInfo n;
	n = (_PPTGRemoteInfo)MALLOC(sizeof(struct _SPTGRemoteInfo));
	n->_print = (_PTGProc)_PrPTGRemoteInfo;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern WithOccurrences */

typedef struct _SPTGWithOccurrences{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGWithOccurrences;

#ifdef PROTO_OK
static void _PrPTGWithOccurrences(_PPTGWithOccurrences n)
#else
static void _PrPTGWithOccurrences(n)
	_PPTGWithOccurrences n;
#endif
{
	n->p1->_print(n->p1);
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "occurs in ");
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
}

#ifdef PROTO_OK
PTGNode PTGWithOccurrences(PTGNode p1, PTGNode p2)
#else
PTGNode PTGWithOccurrences(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGWithOccurrences n;
	n = (_PPTGWithOccurrences)MALLOC(sizeof(struct _SPTGWithOccurrences));
	n->_print = (_PTGProc)_PrPTGWithOccurrences;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IncludingInfo */

typedef struct _SPTGIncludingInfo{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIncludingInfo;

#ifdef PROTO_OK
static void _PrPTGIncludingInfo(_PPTGIncludingInfo n)
#else
static void _PrPTGIncludingInfo(n)
	_PPTGIncludingInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "INCLUDING (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, " propagate ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGIncludingInfo(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIncludingInfo(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIncludingInfo n;
	n = (_PPTGIncludingInfo)MALLOC(sizeof(struct _SPTGIncludingInfo));
	n->_print = (_PTGProc)_PrPTGIncludingInfo;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ConstitInfo */

typedef struct _SPTGConstitInfo{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGConstitInfo;

#ifdef PROTO_OK
static void _PrPTGConstitInfo(_PPTGConstitInfo n)
#else
static void _PrPTGConstitInfo(n)
	_PPTGConstitInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONSTITUENT (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " propagate ");
	n->p3->_print(n->p3);
}

#ifdef PROTO_OK
PTGNode PTGConstitInfo(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGConstitInfo(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGConstitInfo n;
	n = (_PPTGConstitInfo)MALLOC(sizeof(struct _SPTGConstitInfo));
	n->_print = (_PTGProc)_PrPTGConstitInfo;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern ConstitsInfo */

typedef struct _SPTGConstitsInfo{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGConstitsInfo;

#ifdef PROTO_OK
static void _PrPTGConstitsInfo(_PPTGConstitsInfo n)
#else
static void _PrPTGConstitsInfo(n)
	_PPTGConstitsInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONSTITUENTS (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " propagate ");
	n->p4->_print(n->p4);
}

#ifdef PROTO_OK
PTGNode PTGConstitsInfo(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGConstitsInfo(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGConstitsInfo n;
	n = (_PPTGConstitsInfo)MALLOC(sizeof(struct _SPTGConstitsInfo));
	n->_print = (_PTGProc)_PrPTGConstitsInfo;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern ShieldInfo */

typedef struct _SPTGShieldInfo{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGShieldInfo;

#ifdef PROTO_OK
static void _PrPTGShieldInfo(_PPTGShieldInfo n)
#else
static void _PrPTGShieldInfo(n)
	_PPTGShieldInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, " SHIELD (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGShieldInfo(PTGNode p1)
#else
PTGNode PTGShieldInfo(p1)

PTGNode p1;
#endif
{
	_PPTGShieldInfo n;
	n = (_PPTGShieldInfo)MALLOC(sizeof(struct _SPTGShieldInfo));
	n->_print = (_PTGProc)_PrPTGShieldInfo;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern WithInfo */

typedef struct _SPTGWithInfo{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
	CONST char* p3;
	CONST char* p4;
} * _PPTGWithInfo;

#ifdef PROTO_OK
static void _PrPTGWithInfo(_PPTGWithInfo n)
#else
static void _PrPTGWithInfo(n)
	_PPTGWithInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, " WITH (");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGWithInfo(CONST char* p1, CONST char* p2, CONST char* p3, CONST char* p4)
#else
PTGNode PTGWithInfo(p1, p2, p3, p4)

CONST char* p1;
CONST char* p2;
CONST char* p3;
CONST char* p4;
#endif
{
	_PPTGWithInfo n;
	n = (_PPTGWithInfo)MALLOC(sizeof(struct _SPTGWithInfo));
	n->_print = (_PTGProc)_PrPTGWithInfo;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbAttr */

typedef struct _SPTGSymbAttr{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
} * _PPTGSymbAttr;

#ifdef PROTO_OK
static void _PrPTGSymbAttr(_PPTGSymbAttr n)
#else
static void _PrPTGSymbAttr(n)
	_PPTGSymbAttr n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ".");
	PTG_OUTPUT_STRING(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGSymbAttr(CONST char* p1, CONST char* p2)
#else
PTGNode PTGSymbAttr(p1, p2)

CONST char* p1;
CONST char* p2;
#endif
{
	_PPTGSymbAttr n;
	n = (_PPTGSymbAttr)MALLOC(sizeof(struct _SPTGSymbAttr));
	n->_print = (_PTGProc)_PrPTGSymbAttr;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbolComputations */

typedef struct _SPTGSymbolComputations{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGSymbolComputations;

#ifdef PROTO_OK
static void _PrPTGSymbolComputations(_PPTGSymbolComputations n)
#else
static void _PrPTGSymbolComputations(n)
	_PPTGSymbolComputations n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Upper computations for Symbol ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " <");
	IndentIncr(f);
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, ">");
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Lower computations for Symbol ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " <");
	IndentIncr(f);
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, ">");
}

#ifdef PROTO_OK
PTGNode PTGSymbolComputations(CONST char* p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGSymbolComputations(p1, p2, p3)

CONST char* p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGSymbolComputations n;
	n = (_PPTGSymbolComputations)MALLOC(sizeof(struct _SPTGSymbolComputations));
	n->_print = (_PTGProc)_PrPTGSymbolComputations;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern RuleComputations */

typedef struct _SPTGRuleComputations{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGRuleComputations;

#ifdef PROTO_OK
static void _PrPTGRuleComputations(_PPTGRuleComputations n)
#else
static void _PrPTGRuleComputations(n)
	_PPTGRuleComputations n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Computations for Rule ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " <");
	n->p2->_print(n->p2);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, ">");
}

#ifdef PROTO_OK
PTGNode PTGRuleComputations(CONST char* p1, PTGNode p2)
#else
PTGNode PTGRuleComputations(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGRuleComputations n;
	n = (_PPTGRuleComputations)MALLOC(sizeof(struct _SPTGRuleComputations));
	n->_print = (_PTGProc)_PrPTGRuleComputations;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern UnknownExpr */

typedef struct _SPTGUnknownExpr{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGUnknownExpr;

#ifdef PROTO_OK
static void _PrPTGUnknownExpr(_PPTGUnknownExpr n)
#else
static void _PrPTGUnknownExpr(n)
	_PPTGUnknownExpr n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Unknown Expr at ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGUnknownExpr(PTGNode p1)
#else
PTGNode PTGUnknownExpr(p1)

PTGNode p1;
#endif
{
	_PPTGUnknownExpr n;
	n = (_PPTGUnknownExpr)MALLOC(sizeof(struct _SPTGUnknownExpr));
	n->_print = (_PTGProc)_PrPTGUnknownExpr;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Computation */

typedef struct _SPTGComputation{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGComputation;

#ifdef PROTO_OK
static void _PrPTGComputation(_PPTGComputation n)
#else
static void _PrPTGComputation(n)
	_PPTGComputation n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Computation in ");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
	n->p5->_print(n->p5);
}

#ifdef PROTO_OK
PTGNode PTGComputation(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGComputation(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGComputation n;
	n = (_PPTGComputation)MALLOC(sizeof(struct _SPTGComputation));
	n->_print = (_PTGProc)_PrPTGComputation;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern OutCoord */

typedef struct _SPTGOutCoord{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGOutCoord;

#ifdef PROTO_OK
static void _PrPTGOutCoord(_PPTGOutCoord n)
#else
static void _PrPTGOutCoord(n)
	_PPTGOutCoord n;
#endif
{
	PTG_OUTPUT_STRING(f, "line ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ", col ");
	PTG_OUTPUT_INT(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGOutCoord(int p1, int p2)
#else
PTGNode PTGOutCoord(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGOutCoord n;
	n = (_PPTGOutCoord)MALLOC(sizeof(struct _SPTGOutCoord));
	n->_print = (_PTGProc)_PrPTGOutCoord;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Depend */

typedef struct _SPTGDepend{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGDepend;

#ifdef PROTO_OK
static void _PrPTGDepend(_PPTGDepend n)
#else
static void _PrPTGDepend(n)
	_PPTGDepend n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Depend [");
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "expr: ");
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "deps: < ");
	IndentIncr(f);
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, ">");
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "coord: ");
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGDepend(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGDepend(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGDepend n;
	n = (_PPTGDepend)MALLOC(sizeof(struct _SPTGDepend));
	n->_print = (_PTGProc)_PrPTGDepend;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Assign */

typedef struct _SPTGAssign{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGAssign;

#ifdef PROTO_OK
static void _PrPTGAssign(_PPTGAssign n)
#else
static void _PrPTGAssign(n)
	_PPTGAssign n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Assign [");
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "left: ");
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "right: ");
	n->p2->_print(n->p2);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "coord: ");
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGAssign(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGAssign(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGAssign n;
	n = (_PPTGAssign)MALLOC(sizeof(struct _SPTGAssign));
	n->_print = (_PTGProc)_PrPTGAssign;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Loop */

typedef struct _SPTGLoop{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGLoop;

#ifdef PROTO_OK
static void _PrPTGLoop(_PPTGLoop n)
#else
static void _PrPTGLoop(n)
	_PPTGLoop n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Loop [");
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "expr: ");
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "attr:  ");
	n->p2->_print(n->p2);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "iter:  ");
	n->p3->_print(n->p3);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "coord: ");
	n->p4->_print(n->p4);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGLoop(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGLoop(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGLoop n;
	n = (_PPTGLoop)MALLOC(sizeof(struct _SPTGLoop));
	n->_print = (_PTGProc)_PrPTGLoop;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern CallExpr */

typedef struct _SPTGCallExpr{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGCallExpr;

#ifdef PROTO_OK
static void _PrPTGCallExpr(_PPTGCallExpr n)
#else
static void _PrPTGCallExpr(n)
	_PPTGCallExpr n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Call [");
	IndentIncr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "name: ");
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "params: <");
	IndentIncr(f);
	n->p2->_print(n->p2);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, ">");
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "coord: ");
	n->p3->_print(n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGCallExpr(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGCallExpr(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGCallExpr n;
	n = (_PPTGCallExpr)MALLOC(sizeof(struct _SPTGCallExpr));
	n->_print = (_PTGProc)_PrPTGCallExpr;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Name */

typedef struct _SPTGName{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGName;

#ifdef PROTO_OK
static void _PrPTGName(_PPTGName n)
#else
static void _PrPTGName(n)
	_PPTGName n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "Name: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGName(CONST char* p1)
#else
PTGNode PTGName(p1)

CONST char* p1;
#endif
{
	_PPTGName n;
	n = (_PPTGName)MALLOC(sizeof(struct _SPTGName));
	n->_print = (_PTGProc)_PrPTGName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern IntValue */

typedef struct _SPTGIntValue{
	_PTGProc _print;
	int p1;
} * _PPTGIntValue;

#ifdef PROTO_OK
static void _PrPTGIntValue(_PPTGIntValue n)
#else
static void _PrPTGIntValue(n)
	_PPTGIntValue n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "IntValue: ");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGIntValue(int p1)
#else
PTGNode PTGIntValue(p1)

int p1;
#endif
{
	_PPTGIntValue n;
	n = (_PPTGIntValue)MALLOC(sizeof(struct _SPTGIntValue));
	n->_print = (_PTGProc)_PrPTGIntValue;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern StrValue */

typedef struct _SPTGStrValue{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGStrValue;

#ifdef PROTO_OK
static void _PrPTGStrValue(_PPTGStrValue n)
#else
static void _PrPTGStrValue(n)
	_PPTGStrValue n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "StrValue: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGStrValue(CONST char* p1)
#else
PTGNode PTGStrValue(p1)

CONST char* p1;
#endif
{
	_PPTGStrValue n;
	n = (_PPTGStrValue)MALLOC(sizeof(struct _SPTGStrValue));
	n->_print = (_PTGProc)_PrPTGStrValue;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ChrValue */

typedef struct _SPTGChrValue{
	_PTGProc _print;
	int p1;
} * _PPTGChrValue;

#ifdef PROTO_OK
static void _PrPTGChrValue(_PPTGChrValue n)
#else
static void _PrPTGChrValue(n)
	_PPTGChrValue n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "ChrValue: ");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGChrValue(int p1)
#else
PTGNode PTGChrValue(p1)

int p1;
#endif
{
	_PPTGChrValue n;
	n = (_PPTGChrValue)MALLOC(sizeof(struct _SPTGChrValue));
	n->_print = (_PTGProc)_PrPTGChrValue;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern FltValue */

typedef struct _SPTGFltValue{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGFltValue;

#ifdef PROTO_OK
static void _PrPTGFltValue(_PPTGFltValue n)
#else
static void _PrPTGFltValue(n)
	_PPTGFltValue n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "FltValue: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGFltValue(CONST char* p1)
#else
PTGNode PTGFltValue(p1)

CONST char* p1;
#endif
{
	_PPTGFltValue n;
	n = (_PPTGFltValue)MALLOC(sizeof(struct _SPTGFltValue));
	n->_print = (_PTGProc)_PrPTGFltValue;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrAccRule */

typedef struct _SPTGAttrAccRule{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	int p3;
	CONST char* p4;
} * _PPTGAttrAccRule;

#ifdef PROTO_OK
static void _PrPTGAttrAccRule(_PPTGAttrAccRule n)
#else
static void _PrPTGAttrAccRule(n)
	_PPTGAttrAccRule n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "AttrAccRule [ ");
	IndentIncr(f);
	IndentNewLine(f);
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "[");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, "].");
	PTG_OUTPUT_STRING(f, n->p4);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGAttrAccRule(PTGNode p1, CONST char* p2, int p3, CONST char* p4)
#else
PTGNode PTGAttrAccRule(p1, p2, p3, p4)

PTGNode p1;
CONST char* p2;
int p3;
CONST char* p4;
#endif
{
	_PPTGAttrAccRule n;
	n = (_PPTGAttrAccRule)MALLOC(sizeof(struct _SPTGAttrAccRule));
	n->_print = (_PTGProc)_PrPTGAttrAccRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern IsChain */

typedef struct _SPTGIsChain{
	_PTGProc _print;
} * _PPTGIsChain;

#ifdef PROTO_OK
static void _PrPTGIsChain(_PPTGIsChain n)
#else
static void _PrPTGIsChain(n)
	_PPTGIsChain n;
#endif
{
	PTG_OUTPUT_STRING(f, "IsChain");
}

static struct _SPTGIsChain _sptgIsChain = { (_PTGProc) _PrPTGIsChain };

#ifdef PROTO_OK
PTGNode PTGIsChain(void)
#else
PTGNode PTGIsChain()
#endif
{
	return (PTGNode)(&_sptgIsChain);
}


/* Implementation of Pattern IsAttr */

typedef struct _SPTGIsAttr{
	_PTGProc _print;
} * _PPTGIsAttr;

#ifdef PROTO_OK
static void _PrPTGIsAttr(_PPTGIsAttr n)
#else
static void _PrPTGIsAttr(n)
	_PPTGIsAttr n;
#endif
{
	PTG_OUTPUT_STRING(f, "IsAttr");
}

static struct _SPTGIsAttr _sptgIsAttr = { (_PTGProc) _PrPTGIsAttr };

#ifdef PROTO_OK
PTGNode PTGIsAttr(void)
#else
PTGNode PTGIsAttr()
#endif
{
	return (PTGNode)(&_sptgIsAttr);
}


/* Implementation of Pattern RuleAttrAcc */

typedef struct _SPTGRuleAttrAcc{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGRuleAttrAcc;

#ifdef PROTO_OK
static void _PrPTGRuleAttrAcc(_PPTGRuleAttrAcc n)
#else
static void _PrPTGRuleAttrAcc(n)
	_PPTGRuleAttrAcc n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "RuleAttrAcc: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGRuleAttrAcc(CONST char* p1)
#else
PTGNode PTGRuleAttrAcc(p1)

CONST char* p1;
#endif
{
	_PPTGRuleAttrAcc n;
	n = (_PPTGRuleAttrAcc)MALLOC(sizeof(struct _SPTGRuleAttrAcc));
	n->_print = (_PTGProc)_PrPTGRuleAttrAcc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrAccSymb */

typedef struct _SPTGAttrAccSymb{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	CONST char* p3;
} * _PPTGAttrAccSymb;

#ifdef PROTO_OK
static void _PrPTGAttrAccSymb(_PPTGAttrAccSymb n)
#else
static void _PrPTGAttrAccSymb(n)
	_PPTGAttrAccSymb n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "AttrAccSymb [ ");
	IndentIncr(f);
	IndentNewLine(f);
	n->p1->_print(n->p1);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ".");
	PTG_OUTPUT_STRING(f, n->p3);
	IndentDecr(f);
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGAttrAccSymb(PTGNode p1, CONST char* p2, CONST char* p3)
#else
PTGNode PTGAttrAccSymb(p1, p2, p3)

PTGNode p1;
CONST char* p2;
CONST char* p3;
#endif
{
	_PPTGAttrAccSymb n;
	n = (_PPTGAttrAccSymb)MALLOC(sizeof(struct _SPTGAttrAccSymb));
	n->_print = (_PTGProc)_PrPTGAttrAccSymb;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbTermAcc */

typedef struct _SPTGSymbTermAcc{
	_PTGProc _print;
	int p1;
} * _PPTGSymbTermAcc;

#ifdef PROTO_OK
static void _PrPTGSymbTermAcc(_PPTGSymbTermAcc n)
#else
static void _PrPTGSymbTermAcc(n)
	_PPTGSymbTermAcc n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "SymbTermAcc: ");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGSymbTermAcc(int p1)
#else
PTGNode PTGSymbTermAcc(p1)

int p1;
#endif
{
	_PPTGSymbTermAcc n;
	n = (_PPTGSymbTermAcc)MALLOC(sizeof(struct _SPTGSymbTermAcc));
	n->_print = (_PTGProc)_PrPTGSymbTermAcc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern RuleTermAcc */

typedef struct _SPTGRuleTermAcc{
	_PTGProc _print;
	CONST char* p1;
	int p2;
} * _PPTGRuleTermAcc;

#ifdef PROTO_OK
static void _PrPTGRuleTermAcc(_PPTGRuleTermAcc n)
#else
static void _PrPTGRuleTermAcc(n)
	_PPTGRuleTermAcc n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "RuleTermAcc: ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "[");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGRuleTermAcc(CONST char* p1, int p2)
#else
PTGNode PTGRuleTermAcc(p1, p2)

CONST char* p1;
int p2;
#endif
{
	_PPTGRuleTermAcc n;
	n = (_PPTGRuleTermAcc)MALLOC(sizeof(struct _SPTGRuleTermAcc));
	n->_print = (_PTGProc)_PrPTGRuleTermAcc;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern RHS */

typedef struct _SPTGRHS{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGRHS;

#ifdef PROTO_OK
static void _PrPTGRHS(_PPTGRHS n)
#else
static void _PrPTGRHS(n)
	_PPTGRHS n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "RHS.");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGRHS(CONST char* p1)
#else
PTGNode PTGRHS(p1)

CONST char* p1;
#endif
{
	_PPTGRHS n;
	n = (_PPTGRHS)MALLOC(sizeof(struct _SPTGRHS));
	n->_print = (_PTGProc)_PrPTGRHS;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern HeadAcc */

typedef struct _SPTGHeadAcc{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGHeadAcc;

#ifdef PROTO_OK
static void _PrPTGHeadAcc(_PPTGHeadAcc n)
#else
static void _PrPTGHeadAcc(n)
	_PPTGHeadAcc n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "HeadAcc: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGHeadAcc(CONST char* p1)
#else
PTGNode PTGHeadAcc(p1)

CONST char* p1;
#endif
{
	_PPTGHeadAcc n;
	n = (_PPTGHeadAcc)MALLOC(sizeof(struct _SPTGHeadAcc));
	n->_print = (_PTGProc)_PrPTGHeadAcc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TailAcc */

typedef struct _SPTGTailAcc{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGTailAcc;

#ifdef PROTO_OK
static void _PrPTGTailAcc(_PPTGTailAcc n)
#else
static void _PrPTGTailAcc(n)
	_PPTGTailAcc n;
#endif
{
	IndentNewLine(f);
	PTG_OUTPUT_STRING(f, "TailAcc: ");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGTailAcc(CONST char* p1)
#else
PTGNode PTGTailAcc(p1)

CONST char* p1;
#endif
{
	_PPTGTailAcc n;
	n = (_PPTGTailAcc)MALLOC(sizeof(struct _SPTGTailAcc));
	n->_print = (_PTGProc)_PrPTGTailAcc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern IndentNL */

typedef struct _SPTGIndentNL{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGIndentNL;

#ifdef PROTO_OK
static void _PrPTGIndentNL(_PPTGIndentNL n)
#else
static void _PrPTGIndentNL(n)
	_PPTGIndentNL n;
#endif
{
	IndentNewLine(f);
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGIndentNL(PTGNode p1)
#else
PTGNode PTGIndentNL(p1)

PTGNode p1;
#endif
{
	_PPTGIndentNL n;
	n = (_PPTGIndentNL)MALLOC(sizeof(struct _SPTGIndentNL));
	n->_print = (_PTGProc)_PrPTGIndentNL;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlTypedef */

typedef struct _SPTGIdlTypedef{
	_PTGProc _print;
	int p1;
	CONST char* p2;
	PTGNode p3;
} * _PPTGIdlTypedef;

#ifdef PROTO_OK
static void _PrPTGIdlTypedef(_PPTGIdlTypedef n)
#else
static void _PrPTGIdlTypedef(n)
	_PPTGIdlTypedef n;
#endif
{
	PTG_OUTPUT_STRING(f, "Typedef[did\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ndname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\";\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "listedto\t0;\nextname\t\"\"]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlTypedef(int p1, CONST char* p2, PTGNode p3)
#else
PTGNode PTGIdlTypedef(p1, p2, p3)

int p1;
CONST char* p2;
PTGNode p3;
#endif
{
	_PPTGIdlTypedef n;
	n = (_PPTGIdlTypedef)MALLOC(sizeof(struct _SPTGIdlTypedef));
	n->_print = (_PTGProc)_PrPTGIdlTypedef;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlTermdef */

typedef struct _SPTGIdlTermdef{
	_PTGProc _print;
	int p1;
	CONST char* p2;
	PTGNode p3;
} * _PPTGIdlTermdef;

#ifdef PROTO_OK
static void _PrPTGIdlTermdef(_PPTGIdlTermdef n)
#else
static void _PrPTGIdlTermdef(n)
	_PPTGIdlTermdef n;
#endif
{
	PTG_OUTPUT_STRING(f, "Typedef[did\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ndname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\";\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "listedto\t0;\nextname\t\"$TERM\"]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlTermdef(int p1, CONST char* p2, PTGNode p3)
#else
PTGNode PTGIdlTermdef(p1, p2, p3)

int p1;
CONST char* p2;
PTGNode p3;
#endif
{
	_PPTGIdlTermdef n;
	n = (_PPTGIdlTermdef)MALLOC(sizeof(struct _SPTGIdlTermdef));
	n->_print = (_PTGProc)_PrPTGIdlTermdef;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlSymb */

typedef struct _SPTGIdlSymb{
	_PTGProc _print;
	int p1;
	CONST char* p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGIdlSymb;

#ifdef PROTO_OK
static void _PrPTGIdlSymb(_PPTGIdlSymb n)
#else
static void _PrPTGIdlSymb(n)
	_PPTGIdlSymb n;
#endif
{
	PTG_OUTPUT_STRING(f, "Symb[did\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ndname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\";\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "attrs\t<");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ">;\n");
	PTG_OUTPUT_STRING(f, "tornt\t0]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlSymb(int p1, CONST char* p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGIdlSymb(p1, p2, p3, p4)

int p1;
CONST char* p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGIdlSymb n;
	n = (_PPTGIdlSymb)MALLOC(sizeof(struct _SPTGIdlSymb));
	n->_print = (_PTGProc)_PrPTGIdlSymb;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlAttrdef */

typedef struct _SPTGIdlAttrdef{
	_PTGProc _print;
	int p1;
	int p2;
	int p3;
	PTGNode p4;
	CONST char* p5;
	int p6;
} * _PPTGIdlAttrdef;

#ifdef PROTO_OK
static void _PrPTGIdlAttrdef(_PPTGIdlAttrdef n)
#else
static void _PrPTGIdlAttrdef(n)
	_PPTGIdlAttrdef n;
#endif
{
	PTG_OUTPUT_STRING(f, "Attrdef[globname\t\"\";\npart\t0;\ngen\t0;\nstore\t3;\nprodid\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "class\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ";\ntypeid\t");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "name\t\"");
	PTG_OUTPUT_STRING(f, n->p5);
	PTG_OUTPUT_STRING(f, "\";\ndid\t");
	PTG_OUTPUT_INT(f, n->p6);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlAttrdef(int p1, int p2, int p3, PTGNode p4, CONST char* p5, int p6)
#else
PTGNode PTGIdlAttrdef(p1, p2, p3, p4, p5, p6)

int p1;
int p2;
int p3;
PTGNode p4;
CONST char* p5;
int p6;
#endif
{
	_PPTGIdlAttrdef n;
	n = (_PPTGIdlAttrdef)MALLOC(sizeof(struct _SPTGIdlAttrdef));
	n->_print = (_PTGProc)_PrPTGIdlAttrdef;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlProd */

typedef struct _SPTGIdlProd{
	_PTGProc _print;
	int p1;
	CONST char* p2;
	PTGNode p3;
	PTGNode p4;
	int p5;
} * _PPTGIdlProd;

#ifdef PROTO_OK
static void _PrPTGIdlProd(_PPTGIdlProd n)
#else
static void _PrPTGIdlProd(n)
	_PPTGIdlProd n;
#endif
{
	PTG_OUTPUT_STRING(f, "Prod[did\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ndname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\";\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "rhs\t<");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ">;\n");
	PTG_OUTPUT_STRING(f, "lhs\t");
	PTG_OUTPUT_INT(f, n->p5);
	PTG_OUTPUT_STRING(f, "]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlProd(int p1, CONST char* p2, PTGNode p3, PTGNode p4, int p5)
#else
PTGNode PTGIdlProd(p1, p2, p3, p4, p5)

int p1;
CONST char* p2;
PTGNode p3;
PTGNode p4;
int p5;
#endif
{
	_PPTGIdlProd n;
	n = (_PPTGIdlProd)MALLOC(sizeof(struct _SPTGIdlProd));
	n->_print = (_PTGProc)_PrPTGIdlProd;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlChain */

typedef struct _SPTGIdlChain{
	_PTGProc _print;
	int p1;
	CONST char* p2;
	PTGNode p3;
	int p4;
} * _PPTGIdlChain;

#ifdef PROTO_OK
static void _PrPTGIdlChain(_PPTGIdlChain n)
#else
static void _PrPTGIdlChain(n)
	_PPTGIdlChain n;
#endif
{
	PTG_OUTPUT_STRING(f, "Chain[did\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ndname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\";\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
	PTG_OUTPUT_STRING(f, "typeid\t");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, "]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlChain(int p1, CONST char* p2, PTGNode p3, int p4)
#else
PTGNode PTGIdlChain(p1, p2, p3, p4)

int p1;
CONST char* p2;
PTGNode p3;
int p4;
#endif
{
	_PPTGIdlChain n;
	n = (_PPTGIdlChain)MALLOC(sizeof(struct _SPTGIdlChain));
	n->_print = (_PTGProc)_PrPTGIdlChain;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlSymbol */

typedef struct _SPTGIdlSymbol{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGIdlSymbol;

#ifdef PROTO_OK
static void _PrPTGIdlSymbol(_PPTGIdlSymbol n)
#else
static void _PrPTGIdlSymbol(n)
	_PPTGIdlSymbol n;
#endif
{
	PTG_OUTPUT_STRING(f, "Symbol[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\ndid\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlSymbol(PTGNode p1, int p2)
#else
PTGNode PTGIdlSymbol(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGIdlSymbol n;
	n = (_PPTGIdlSymbol)MALLOC(sizeof(struct _SPTGIdlSymbol));
	n->_print = (_PTGProc)_PrPTGIdlSymbol;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlLiteral */

typedef struct _SPTGIdlLiteral{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
} * _PPTGIdlLiteral;

#ifdef PROTO_OK
static void _PrPTGIdlLiteral(_PPTGIdlLiteral n)
#else
static void _PrPTGIdlLiteral(n)
	_PPTGIdlLiteral n;
#endif
{
	PTG_OUTPUT_STRING(f, "Literal[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\nstr\t\"");
	IdlStringTrafo(f, n->p2);
	PTG_OUTPUT_STRING(f, "\"]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlLiteral(PTGNode p1, CONST char* p2)
#else
PTGNode PTGIdlLiteral(p1, p2)

PTGNode p1;
CONST char* p2;
#endif
{
	_PPTGIdlLiteral n;
	n = (_PPTGIdlLiteral)MALLOC(sizeof(struct _SPTGIdlLiteral));
	n->_print = (_PTGProc)_PrPTGIdlLiteral;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlNonLitTerm */

typedef struct _SPTGIdlNonLitTerm{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	CONST char* p3;
} * _PPTGIdlNonLitTerm;

#ifdef PROTO_OK
static void _PrPTGIdlNonLitTerm(_PPTGIdlNonLitTerm n)
#else
static void _PrPTGIdlNonLitTerm(n)
	_PPTGIdlNonLitTerm n;
#endif
{
	PTG_OUTPUT_STRING(f, "Literal[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\nstr\t\"\"]\n ");
	PTG_OUTPUT_STRING(f, "Literal[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\nstr\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\"]\n ");
	PTG_OUTPUT_STRING(f, "Literal[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\nstr\t\"");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "\"]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlNonLitTerm(PTGNode p1, CONST char* p2, CONST char* p3)
#else
PTGNode PTGIdlNonLitTerm(p1, p2, p3)

PTGNode p1;
CONST char* p2;
CONST char* p3;
#endif
{
	_PPTGIdlNonLitTerm n;
	n = (_PPTGIdlNonLitTerm)MALLOC(sizeof(struct _SPTGIdlNonLitTerm));
	n->_print = (_PTGProc)_PrPTGIdlNonLitTerm;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlGenSymbol */

typedef struct _SPTGIdlGenSymbol{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGIdlGenSymbol;

#ifdef PROTO_OK
static void _PrPTGIdlGenSymbol(_PPTGIdlGenSymbol n)
#else
static void _PrPTGIdlGenSymbol(n)
	_PPTGIdlGenSymbol n;
#endif
{
	PTG_OUTPUT_STRING(f, "Literal[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\nstr\t\"\"]\n ");
	PTG_OUTPUT_STRING(f, "Symbol[");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\ndid\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n ");
}

#ifdef PROTO_OK
PTGNode PTGIdlGenSymbol(PTGNode p1, int p2)
#else
PTGNode PTGIdlGenSymbol(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGIdlGenSymbol n;
	n = (_PPTGIdlGenSymbol)MALLOC(sizeof(struct _SPTGIdlGenSymbol));
	n->_print = (_PTGProc)_PrPTGIdlGenSymbol;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlrowCol */

typedef struct _SPTGIdlrowCol{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGIdlrowCol;

#ifdef PROTO_OK
static void _PrPTGIdlrowCol(_PPTGIdlrowCol n)
#else
static void _PrPTGIdlrowCol(n)
	_PPTGIdlrowCol n;
#endif
{
	PTG_OUTPUT_STRING(f, "row\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\ncol\t");
	PTG_OUTPUT_INT(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGIdlrowCol(int p1, int p2)
#else
PTGNode PTGIdlrowCol(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGIdlrowCol n;
	n = (_PPTGIdlrowCol)MALLOC(sizeof(struct _SPTGIdlrowCol));
	n->_print = (_PTGProc)_PrPTGIdlrowCol;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlcolRow */

typedef struct _SPTGIdlcolRow{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGIdlcolRow;

#ifdef PROTO_OK
static void _PrPTGIdlcolRow(_PPTGIdlcolRow n)
#else
static void _PrPTGIdlcolRow(n)
	_PPTGIdlcolRow n;
#endif
{
	PTG_OUTPUT_STRING(f, "col\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nrow\t");
	PTG_OUTPUT_INT(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGIdlcolRow(int p1, int p2)
#else
PTGNode PTGIdlcolRow(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGIdlcolRow n;
	n = (_PPTGIdlcolRow)MALLOC(sizeof(struct _SPTGIdlcolRow));
	n->_print = (_PTGProc)_PrPTGIdlcolRow;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlAttrEval */

typedef struct _SPTGIdlAttrEval{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlAttrEval;

#ifdef PROTO_OK
static void _PrPTGIdlAttrEval(_PPTGIdlAttrEval n)
#else
static void _PrPTGIdlAttrEval(n)
	_PPTGIdlAttrEval n;
#endif
{
	PTG_OUTPUT_STRING(f, "-- structure LIGA\nAttrEval[");
	PTG_OUTPUT_STRING(f, "attrrules\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;\n");
	PTG_OUTPUT_STRING(f, "defseq\t<");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ">]\n#\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlAttrEval(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlAttrEval(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlAttrEval n;
	n = (_PPTGIdlAttrEval)MALLOC(sizeof(struct _SPTGIdlAttrEval));
	n->_print = (_PTGProc)_PrPTGIdlAttrEval;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlRuleComputations */

typedef struct _SPTGIdlRuleComputations{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGIdlRuleComputations;

#ifdef PROTO_OK
static void _PrPTGIdlRuleComputations(_PPTGIdlRuleComputations n)
#else
static void _PrPTGIdlRuleComputations(n)
	_PPTGIdlRuleComputations n;
#endif
{
	PTG_OUTPUT_STRING(f, "Attribution[attrrules\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;\nprodid\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlRuleComputations(PTGNode p1, int p2)
#else
PTGNode PTGIdlRuleComputations(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGIdlRuleComputations n;
	n = (_PPTGIdlRuleComputations)MALLOC(sizeof(struct _SPTGIdlRuleComputations));
	n->_print = (_PTGProc)_PrPTGIdlRuleComputations;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlCompCoord */

typedef struct _SPTGIdlCompCoord{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGIdlCompCoord;

#ifdef PROTO_OK
static void _PrPTGIdlCompCoord(_PPTGIdlCompCoord n)
#else
static void _PrPTGIdlCompCoord(n)
	_PPTGIdlCompCoord n;
#endif
{
	PTG_OUTPUT_STRING(f, "col\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nrow\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ";\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlCompCoord(int p1, int p2)
#else
PTGNode PTGIdlCompCoord(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGIdlCompCoord n;
	n = (_PPTGIdlCompCoord)MALLOC(sizeof(struct _SPTGIdlCompCoord));
	n->_print = (_PTGProc)_PrPTGIdlCompCoord;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlDepend */

typedef struct _SPTGIdlDepend{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIdlDepend;

#ifdef PROTO_OK
static void _PrPTGIdlDepend(_PPTGIdlDepend n)
#else
static void _PrPTGIdlDepend(n)
	_PPTGIdlDepend n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ">;");
	PTG_OUTPUT_STRING(f, "\nname\t\"$DEP\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlDepend(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIdlDepend(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIdlDepend n;
	n = (_PPTGIdlDepend)MALLOC(sizeof(struct _SPTGIdlDepend));
	n->_print = (_PTGProc)_PrPTGIdlDepend;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlBottomup */

typedef struct _SPTGIdlBottomup{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlBottomup;

#ifdef PROTO_OK
static void _PrPTGIdlBottomup(_PPTGIdlBottomup n)
#else
static void _PrPTGIdlBottomup(n)
	_PPTGIdlBottomup n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;");
	PTG_OUTPUT_STRING(f, "\nname\t\"$BU\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlBottomup(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlBottomup(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlBottomup n;
	n = (_PPTGIdlBottomup)MALLOC(sizeof(struct _SPTGIdlBottomup));
	n->_print = (_PTGProc)_PrPTGIdlBottomup;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlIdentity */

typedef struct _SPTGIdlIdentity{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlIdentity;

#ifdef PROTO_OK
static void _PrPTGIdlIdentity(_PPTGIdlIdentity n)
#else
static void _PrPTGIdlIdentity(n)
	_PPTGIdlIdentity n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;");
	PTG_OUTPUT_STRING(f, "\nname\t\"$ID\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlIdentity(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlIdentity(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlIdentity n;
	n = (_PPTGIdlIdentity)MALLOC(sizeof(struct _SPTGIdlIdentity));
	n->_print = (_PTGProc)_PrPTGIdlIdentity;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlAssign */

typedef struct _SPTGIdlAssign{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIdlAssign;

#ifdef PROTO_OK
static void _PrPTGIdlAssign(_PPTGIdlAssign n)
#else
static void _PrPTGIdlAssign(n)
	_PPTGIdlAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$ASSIGN\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlAssign(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIdlAssign(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIdlAssign n;
	n = (_PPTGIdlAssign)MALLOC(sizeof(struct _SPTGIdlAssign));
	n->_print = (_PTGProc)_PrPTGIdlAssign;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlGenTreeDummy */

typedef struct _SPTGIdlGenTreeDummy{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlGenTreeDummy;

#ifdef PROTO_OK
static void _PrPTGIdlGenTreeDummy(_PPTGIdlGenTreeDummy n)
#else
static void _PrPTGIdlGenTreeDummy(n)
	_PPTGIdlGenTreeDummy n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "Val[col\t0;\nrow\t0;\nv\t0]\n");
	PTG_OUTPUT_STRING(f, "Name[col\t0;\nrow\t0;\nn\t\"VOID\"]\n");
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$ASSIGN\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlGenTreeDummy(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlGenTreeDummy(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlGenTreeDummy n;
	n = (_PPTGIdlGenTreeDummy)MALLOC(sizeof(struct _SPTGIdlGenTreeDummy));
	n->_print = (_PTGProc)_PrPTGIdlGenTreeDummy;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlDummyComp */

typedef struct _SPTGIdlDummyComp{
	_PTGProc _print;
	int p1;
} * _PPTGIdlDummyComp;

#ifdef PROTO_OK
static void _PrPTGIdlDummyComp(_PPTGIdlDummyComp n)
#else
static void _PrPTGIdlDummyComp(n)
	_PPTGIdlDummyComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[col\t0;\nrow\t0;\nparams<");
	PTG_OUTPUT_STRING(f, "Attracc[col\t0;\nrow\t0;\nattrid\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nsymbno\t0]\n");
	PTG_OUTPUT_STRING(f, "Val[col\t0;\nrow\t0;\nv\t0]\n");
	PTG_OUTPUT_STRING(f, "Name[col\t0;\nrow\t0;\nn\t\"VOID\"]\n");
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$ASSIGN\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlDummyComp(int p1)
#else
PTGNode PTGIdlDummyComp(p1)

int p1;
#endif
{
	_PPTGIdlDummyComp n;
	n = (_PPTGIdlDummyComp)MALLOC(sizeof(struct _SPTGIdlDummyComp));
	n->_print = (_PTGProc)_PrPTGIdlDummyComp;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlChainstart */

typedef struct _SPTGIdlChainstart{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIdlChainstart;

#ifdef PROTO_OK
static void _PrPTGIdlChainstart(_PPTGIdlChainstart n)
#else
static void _PrPTGIdlChainstart(n)
	_PPTGIdlChainstart n;
#endif
{
	PTG_OUTPUT_STRING(f, "ChainStart[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "postgenattr\t\"\";\npostgenattr\t\"\";\nchainid\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "]\n");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGIdlChainstart(int p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIdlChainstart(p1, p2, p3)

int p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIdlChainstart n;
	n = (_PPTGIdlChainstart)MALLOC(sizeof(struct _SPTGIdlChainstart));
	n->_print = (_PTGProc)_PrPTGIdlChainstart;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlLoopInit */

typedef struct _SPTGIdlLoopInit{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlLoopInit;

#ifdef PROTO_OK
static void _PrPTGIdlLoopInit(_PPTGIdlLoopInit n)
#else
static void _PrPTGIdlLoopInit(n)
	_PPTGIdlLoopInit n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;");
	PTG_OUTPUT_STRING(f, "\nname\t\"$INITCYCLE\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlLoopInit(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlLoopInit(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlLoopInit n;
	n = (_PPTGIdlLoopInit)MALLOC(sizeof(struct _SPTGIdlLoopInit));
	n->_print = (_PTGProc)_PrPTGIdlLoopInit;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlLoop */

typedef struct _SPTGIdlLoop{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGIdlLoop;

#ifdef PROTO_OK
static void _PrPTGIdlLoop(_PPTGIdlLoop n)
#else
static void _PrPTGIdlLoop(n)
	_PPTGIdlLoop n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$LOOP\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlLoop(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGIdlLoop(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGIdlLoop n;
	n = (_PPTGIdlLoop)MALLOC(sizeof(struct _SPTGIdlLoop));
	n->_print = (_PTGProc)_PrPTGIdlLoop;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlCall */

typedef struct _SPTGIdlCall{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	PTGNode p3;
} * _PPTGIdlCall;

#ifdef PROTO_OK
static void _PrPTGIdlCall(_PPTGIdlCall n)
#else
static void _PrPTGIdlCall(n)
	_PPTGIdlCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;");
	PTG_OUTPUT_STRING(f, "\nname\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlCall(PTGNode p1, CONST char* p2, PTGNode p3)
#else
PTGNode PTGIdlCall(p1, p2, p3)

PTGNode p1;
CONST char* p2;
PTGNode p3;
#endif
{
	_PPTGIdlCall n;
	n = (_PPTGIdlCall)MALLOC(sizeof(struct _SPTGIdlCall));
	n->_print = (_PTGProc)_PrPTGIdlCall;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlName */

typedef struct _SPTGIdlName{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGIdlName;

#ifdef PROTO_OK
static void _PrPTGIdlName(_PPTGIdlName n)
#else
static void _PrPTGIdlName(n)
	_PPTGIdlName n;
#endif
{
	PTG_OUTPUT_STRING(f, "Name[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "n\t\"");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlName(CONST char* p1, PTGNode p2)
#else
PTGNode PTGIdlName(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGIdlName n;
	n = (_PPTGIdlName)MALLOC(sizeof(struct _SPTGIdlName));
	n->_print = (_PTGProc)_PrPTGIdlName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlIntValue */

typedef struct _SPTGIdlIntValue{
	_PTGProc _print;
	int p1;
	PTGNode p2;
} * _PPTGIdlIntValue;

#ifdef PROTO_OK
static void _PrPTGIdlIntValue(_PPTGIdlIntValue n)
#else
static void _PrPTGIdlIntValue(n)
	_PPTGIdlIntValue n;
#endif
{
	PTG_OUTPUT_STRING(f, "Val[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "v\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlIntValue(int p1, PTGNode p2)
#else
PTGNode PTGIdlIntValue(p1, p2)

int p1;
PTGNode p2;
#endif
{
	_PPTGIdlIntValue n;
	n = (_PPTGIdlIntValue)MALLOC(sizeof(struct _SPTGIdlIntValue));
	n->_print = (_PTGProc)_PrPTGIdlIntValue;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlStrValue */

typedef struct _SPTGIdlStrValue{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGIdlStrValue;

#ifdef PROTO_OK
static void _PrPTGIdlStrValue(_PPTGIdlStrValue n)
#else
static void _PrPTGIdlStrValue(n)
	_PPTGIdlStrValue n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<Literal[row\t0;\ncol\t0;\n");
	PTG_OUTPUT_STRING(f, "str\t\"");
	IdlStringTrafo(f, n->p1);
	PTG_OUTPUT_STRING(f, "\"]\n>;\nname\t\"$STRING\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlStrValue(CONST char* p1, PTGNode p2)
#else
PTGNode PTGIdlStrValue(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGIdlStrValue n;
	n = (_PPTGIdlStrValue)MALLOC(sizeof(struct _SPTGIdlStrValue));
	n->_print = (_PTGProc)_PrPTGIdlStrValue;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlChrValue */

typedef struct _SPTGIdlChrValue{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGIdlChrValue;

#ifdef PROTO_OK
static void _PrPTGIdlChrValue(_PPTGIdlChrValue n)
#else
static void _PrPTGIdlChrValue(n)
	_PPTGIdlChrValue n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<Literal[row\t0;\ncol\t0;\n");
	PTG_OUTPUT_STRING(f, "str\t\"");
	IdlStringTrafo(f, n->p1);
	PTG_OUTPUT_STRING(f, "\"]\n>;\nname\t\"$CHAR\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlChrValue(CONST char* p1, PTGNode p2)
#else
PTGNode PTGIdlChrValue(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGIdlChrValue n;
	n = (_PPTGIdlChrValue)MALLOC(sizeof(struct _SPTGIdlChrValue));
	n->_print = (_PTGProc)_PrPTGIdlChrValue;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlFltValue */

typedef struct _SPTGIdlFltValue{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGIdlFltValue;

#ifdef PROTO_OK
static void _PrPTGIdlFltValue(_PPTGIdlFltValue n)
#else
static void _PrPTGIdlFltValue(n)
	_PPTGIdlFltValue n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<Literal[row\t0;\ncol\t0;\n");
	PTG_OUTPUT_STRING(f, "str\t\"");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\"]\n>;\nname\t\"$FLOAT\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlFltValue(CONST char* p1, PTGNode p2)
#else
PTGNode PTGIdlFltValue(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGIdlFltValue n;
	n = (_PPTGIdlFltValue)MALLOC(sizeof(struct _SPTGIdlFltValue));
	n->_print = (_PTGProc)_PrPTGIdlFltValue;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlAttrAcc */

typedef struct _SPTGIdlAttrAcc{
	_PTGProc _print;
	int p1;
	int p2;
	PTGNode p3;
} * _PPTGIdlAttrAcc;

#ifdef PROTO_OK
static void _PrPTGIdlAttrAcc(_PPTGIdlAttrAcc n)
#else
static void _PrPTGIdlAttrAcc(n)
	_PPTGIdlAttrAcc n;
#endif
{
	PTG_OUTPUT_STRING(f, "Attracc[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "attrid\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nsymbno\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlAttrAcc(int p1, int p2, PTGNode p3)
#else
PTGNode PTGIdlAttrAcc(p1, p2, p3)

int p1;
int p2;
PTGNode p3;
#endif
{
	_PPTGIdlAttrAcc n;
	n = (_PPTGIdlAttrAcc)MALLOC(sizeof(struct _SPTGIdlAttrAcc));
	n->_print = (_PTGProc)_PrPTGIdlAttrAcc;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlChainAcc */

typedef struct _SPTGIdlChainAcc{
	_PTGProc _print;
	int p1;
	int p2;
	PTGNode p3;
} * _PPTGIdlChainAcc;

#ifdef PROTO_OK
static void _PrPTGIdlChainAcc(_PPTGIdlChainAcc n)
#else
static void _PrPTGIdlChainAcc(n)
	_PPTGIdlChainAcc n;
#endif
{
	PTG_OUTPUT_STRING(f, "Chainacc[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "chainid\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nsymbno\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlChainAcc(int p1, int p2, PTGNode p3)
#else
PTGNode PTGIdlChainAcc(p1, p2, p3)

int p1;
int p2;
PTGNode p3;
#endif
{
	_PPTGIdlChainAcc n;
	n = (_PPTGIdlChainAcc)MALLOC(sizeof(struct _SPTGIdlChainAcc));
	n->_print = (_PTGProc)_PrPTGIdlChainAcc;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlTermAcc */

typedef struct _SPTGIdlTermAcc{
	_PTGProc _print;
	int p1;
	PTGNode p2;
} * _PPTGIdlTermAcc;

#ifdef PROTO_OK
static void _PrPTGIdlTermAcc(_PPTGIdlTermAcc n)
#else
static void _PrPTGIdlTermAcc(n)
	_PPTGIdlTermAcc n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<Val[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "v\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "]\n>;\nname\t\"$TERM\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlTermAcc(int p1, PTGNode p2)
#else
PTGNode PTGIdlTermAcc(p1, p2)

int p1;
PTGNode p2;
#endif
{
	_PPTGIdlTermAcc n;
	n = (_PPTGIdlTermAcc)MALLOC(sizeof(struct _SPTGIdlTermAcc));
	n->_print = (_PTGProc)_PrPTGIdlTermAcc;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlConstituent */

typedef struct _SPTGIdlConstituent{
	_PTGProc _print;
	PTGNode p1;
	int p2;
	int p3;
	PTGNode p4;
} * _PPTGIdlConstituent;

#ifdef PROTO_OK
static void _PrPTGIdlConstituent(_PPTGIdlConstituent n)
#else
static void _PrPTGIdlConstituent(n)
	_PPTGIdlConstituent n;
#endif
{
	PTG_OUTPUT_STRING(f, "Constit[");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "constattrs\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;\nsubtree\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ";\nsingle\t");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ";\ngenattr\t\"\"]");
}

#ifdef PROTO_OK
PTGNode PTGIdlConstituent(PTGNode p1, int p2, int p3, PTGNode p4)
#else
PTGNode PTGIdlConstituent(p1, p2, p3, p4)

PTGNode p1;
int p2;
int p3;
PTGNode p4;
#endif
{
	_PPTGIdlConstituent n;
	n = (_PPTGIdlConstituent)MALLOC(sizeof(struct _SPTGIdlConstituent));
	n->_print = (_PTGProc)_PrPTGIdlConstituent;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlWith */

typedef struct _SPTGIdlWith{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	CONST char* p3;
	CONST char* p4;
	CONST char* p5;
	PTGNode p6;
} * _PPTGIdlWith;

#ifdef PROTO_OK
static void _PrPTGIdlWith(_PPTGIdlWith n)
#else
static void _PrPTGIdlWith(n)
	_PPTGIdlWith n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\nName[");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "n\t\"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\"]\nName[");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "n\t\"");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "\"]\nName[");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "n\t\"");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "\"]\nName[");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "n\t\"");
	PTG_OUTPUT_STRING(f, n->p5);
	PTG_OUTPUT_STRING(f, "\"]\n>;\nname\t\"$WITH\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlWith(PTGNode p1, CONST char* p2, CONST char* p3, CONST char* p4, CONST char* p5, PTGNode p6)
#else
PTGNode PTGIdlWith(p1, p2, p3, p4, p5, p6)

PTGNode p1;
CONST char* p2;
CONST char* p3;
CONST char* p4;
CONST char* p5;
PTGNode p6;
#endif
{
	_PPTGIdlWith n;
	n = (_PPTGIdlWith)MALLOC(sizeof(struct _SPTGIdlWith));
	n->_print = (_PTGProc)_PrPTGIdlWith;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlShield */

typedef struct _SPTGIdlShield{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIdlShield;

#ifdef PROTO_OK
static void _PrPTGIdlShield(_PPTGIdlShield n)
#else
static void _PrPTGIdlShield(n)
	_PPTGIdlShield n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$SHIELD\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlShield(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIdlShield(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIdlShield n;
	n = (_PPTGIdlShield)MALLOC(sizeof(struct _SPTGIdlShield));
	n->_print = (_PTGProc)_PrPTGIdlShield;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlVoiden */

typedef struct _SPTGIdlVoiden{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlVoiden;

#ifdef PROTO_OK
static void _PrPTGIdlVoiden(_PPTGIdlVoiden n)
#else
static void _PrPTGIdlVoiden(n)
	_PPTGIdlVoiden n;
#endif
{
	PTG_OUTPUT_STRING(f, "Call[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "params\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;\nname\t\"$VOID\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlVoiden(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlVoiden(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlVoiden n;
	n = (_PPTGIdlVoiden)MALLOC(sizeof(struct _SPTGIdlVoiden));
	n->_print = (_PTGProc)_PrPTGIdlVoiden;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlShieldSym */

typedef struct _SPTGIdlShieldSym{
	_PTGProc _print;
	int p1;
	PTGNode p2;
} * _PPTGIdlShieldSym;

#ifdef PROTO_OK
static void _PrPTGIdlShieldSym(_PPTGIdlShieldSym n)
#else
static void _PrPTGIdlShieldSym(n)
	_PPTGIdlShieldSym n;
#endif
{
	PTG_OUTPUT_STRING(f, "Val[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "v\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlShieldSym(int p1, PTGNode p2)
#else
PTGNode PTGIdlShieldSym(p1, p2)

int p1;
PTGNode p2;
#endif
{
	_PPTGIdlShieldSym n;
	n = (_PPTGIdlShieldSym)MALLOC(sizeof(struct _SPTGIdlShieldSym));
	n->_print = (_PTGProc)_PrPTGIdlShieldSym;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlIncluding */

typedef struct _SPTGIdlIncluding{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIdlIncluding;

#ifdef PROTO_OK
static void _PrPTGIdlIncluding(_PPTGIdlIncluding n)
#else
static void _PrPTGIdlIncluding(n)
	_PPTGIdlIncluding n;
#endif
{
	PTG_OUTPUT_STRING(f, "Including[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "inclattrs\t<");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ">;\ngenattrid\t0;\ngenattr\t\"\"]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlIncluding(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIdlIncluding(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIdlIncluding n;
	n = (_PPTGIdlIncluding)MALLOC(sizeof(struct _SPTGIdlIncluding));
	n->_print = (_PTGProc)_PrPTGIdlIncluding;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IdlSymbAttr */

typedef struct _SPTGIdlSymbAttr{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGIdlSymbAttr;

#ifdef PROTO_OK
static void _PrPTGIdlSymbAttr(_PPTGIdlSymbAttr n)
#else
static void _PrPTGIdlSymbAttr(n)
	_PPTGIdlSymbAttr n;
#endif
{
	PTG_OUTPUT_STRING(f, "Symbattr[attrdef\t");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";\nsymbdef\t");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "]\n");
}

#ifdef PROTO_OK
PTGNode PTGIdlSymbAttr(int p1, int p2)
#else
PTGNode PTGIdlSymbAttr(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGIdlSymbAttr n;
	n = (_PPTGIdlSymbAttr)MALLOC(sizeof(struct _SPTGIdlSymbAttr));
	n->_print = (_PTGProc)_PrPTGIdlSymbAttr;
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

