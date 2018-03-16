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

/* Implementation of Pattern ConRule */

typedef struct _SPTGConRule{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGConRule;

#ifdef PROTO_OK
static void _PrPTGConRule(_PPTGConRule n)
#else
static void _PrPTGConRule(n)
	_PPTGConRule n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " .\n\n");
}

#ifdef PROTO_OK
PTGNode PTGConRule(PTGNode p1, PTGNode p2)
#else
PTGNode PTGConRule(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGConRule n;
	n = (_PPTGConRule)MALLOC(sizeof(struct _SPTGConRule));
	n->_print = (_PTGProc)_PrPTGConRule;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern AltSeq */

typedef struct _SPTGAltSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAltSeq;

#ifdef PROTO_OK
static void _PrPTGAltSeq(_PPTGAltSeq n)
#else
static void _PrPTGAltSeq(n)
	_PPTGAltSeq n;
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
PTGNode PTGAltSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAltSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAltSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGAltSeq)MALLOC(sizeof(struct _SPTGAltSeq));
	n->_print = (_PTGProc)_PrPTGAltSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern AbsRule */

typedef struct _SPTGAbsRule{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGAbsRule;

#ifdef PROTO_OK
static void _PrPTGAbsRule(_PPTGAbsRule n)
#else
static void _PrPTGAbsRule(n)
	_PPTGAbsRule n;
#endif
{
	PTG_OUTPUT_STRING(f, "RULE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ::= ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "END;\n\n");
}

#ifdef PROTO_OK
PTGNode PTGAbsRule(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGAbsRule(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGAbsRule n;
	n = (_PPTGAbsRule)MALLOC(sizeof(struct _SPTGAbsRule));
	n->_print = (_PTGProc)_PrPTGAbsRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Start */

typedef struct _SPTGStart{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGStart;

#ifdef PROTO_OK
static void _PrPTGStart(_PPTGStart n)
#else
static void _PrPTGStart(n)
	_PPTGStart n;
#endif
{
	PTG_OUTPUT_STRING(f, "<$START_SYMBOL>: ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " .\n");
}

#ifdef PROTO_OK
PTGNode PTGStart(PTGNode p1)
#else
PTGNode PTGStart(p1)

PTGNode p1;
#endif
{
	_PPTGStart n;
	n = (_PPTGStart)MALLOC(sizeof(struct _SPTGStart));
	n->_print = (_PTGProc)_PrPTGStart;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SpcSeq */

typedef struct _SPTGSpcSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSpcSeq;

#ifdef PROTO_OK
static void _PrPTGSpcSeq(_PPTGSpcSeq n)
#else
static void _PrPTGSpcSeq(n)
	_PPTGSpcSeq n;
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
PTGNode PTGSpcSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSpcSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSpcSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGSpcSeq)MALLOC(sizeof(struct _SPTGSpcSeq));
	n->_print = (_PTGProc)_PrPTGSpcSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern GenIdent */

typedef struct _SPTGGenIdent{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGGenIdent;

#ifdef PROTO_OK
static void _PrPTGGenIdent(_PPTGGenIdent n)
#else
static void _PrPTGGenIdent(n)
	_PPTGGenIdent n;
#endif
{
	PTG_OUTPUT_STRING(f, " $ ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGGenIdent(PTGNode p1)
#else
PTGNode PTGGenIdent(p1)

PTGNode p1;
#endif
{
	_PPTGGenIdent n;
	n = (_PPTGGenIdent)MALLOC(sizeof(struct _SPTGGenIdent));
	n->_print = (_PTGProc)_PrPTGGenIdent;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Connection */

typedef struct _SPTGConnection{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGConnection;

#ifdef PROTO_OK
static void _PrPTGConnection(_PPTGConnection n)
#else
static void _PrPTGConnection(n)
	_PPTGConnection n;
#endif
{
	PTG_OUTPUT_STRING(f, "&");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGConnection(PTGNode p1)
#else
PTGNode PTGConnection(p1)

PTGNode p1;
#endif
{
	_PPTGConnection n;
	n = (_PPTGConnection)MALLOC(sizeof(struct _SPTGConnection));
	n->_print = (_PTGProc)_PrPTGConnection;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AtMod */

typedef struct _SPTGAtMod{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAtMod;

#ifdef PROTO_OK
static void _PrPTGAtMod(_PPTGAtMod n)
#else
static void _PrPTGAtMod(n)
	_PPTGAtMod n;
#endif
{
	PTG_OUTPUT_STRING(f, "@");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGAtMod(PTGNode p1)
#else
PTGNode PTGAtMod(p1)

PTGNode p1;
#endif
{
	_PPTGAtMod n;
	n = (_PPTGAtMod)MALLOC(sizeof(struct _SPTGAtMod));
	n->_print = (_PTGProc)_PrPTGAtMod;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern DollarMod */

typedef struct _SPTGDollarMod{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGDollarMod;

#ifdef PROTO_OK
static void _PrPTGDollarMod(_PPTGDollarMod n)
#else
static void _PrPTGDollarMod(n)
	_PPTGDollarMod n;
#endif
{
	PTG_OUTPUT_STRING(f, "$");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGDollarMod(PTGNode p1)
#else
PTGNode PTGDollarMod(p1)

PTGNode p1;
#endif
{
	_PPTGDollarMod n;
	n = (_PPTGDollarMod)MALLOC(sizeof(struct _SPTGDollarMod));
	n->_print = (_PTGProc)_PrPTGDollarMod;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AbsList */

typedef struct _SPTGAbsList{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGAbsList;

#ifdef PROTO_OK
static void _PrPTGAbsList(_PPTGAbsList n)
#else
static void _PrPTGAbsList(n)
	_PPTGAbsList n;
#endif
{
	PTG_OUTPUT_STRING(f, "RULE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " LISTOF ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "END;\n\n");
}

#ifdef PROTO_OK
PTGNode PTGAbsList(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGAbsList(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGAbsList n;
	n = (_PPTGAbsList)MALLOC(sizeof(struct _SPTGAbsList));
	n->_print = (_PTGProc)_PrPTGAbsList;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern PgramList */

typedef struct _SPTGPgramList{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGPgramList;

#ifdef PROTO_OK
static void _PrPTGPgramList(_PPTGPgramList n)
#else
static void _PrPTGPgramList(n)
	_PPTGPgramList n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " &'_nst[_nsp]=Mk");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "(&curpos, _nst[_nsp]);' .\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": &'_incrnodestack(); _nst[_nsp]=Mk0");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "(&curpos);' .\n");
}

#ifdef PROTO_OK
PTGNode PTGPgramList(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGPgramList(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGPgramList n;
	n = (_PPTGPgramList)MALLOC(sizeof(struct _SPTGPgramList));
	n->_print = (_PTGProc)_PrPTGPgramList;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern PgramRecList */

typedef struct _SPTGPgramRecList{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGPgramRecList;

#ifdef PROTO_OK
static void _PrPTGPgramRecList(_PPTGPgramRecList n)
#else
static void _PrPTGPgramRecList(n)
	_PPTGPgramRecList n;
#endif
{
	PTG_OUTPUT_STRING(f, "LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " &'_nsp -=1; _nst[_nsp]=Mk2");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "(&curpos, _nst[_nsp], ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ");' .\n");
}

#ifdef PROTO_OK
PTGNode PTGPgramRecList(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGPgramRecList(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGPgramRecList n;
	n = (_PPTGPgramRecList)MALLOC(sizeof(struct _SPTGPgramRecList));
	n->_print = (_PTGProc)_PrPTGPgramRecList;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern ConList */

typedef struct _SPTGConList{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGConList;

#ifdef PROTO_OK
static void _PrPTGConList(_PPTGConList n)
#else
static void _PrPTGConList(n)
	_PPTGConList n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " .\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": .\n");
}

#ifdef PROTO_OK
PTGNode PTGConList(PTGNode p1, PTGNode p2)
#else
PTGNode PTGConList(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGConList n;
	n = (_PPTGConList)MALLOC(sizeof(struct _SPTGConList));
	n->_print = (_PTGProc)_PrPTGConList;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ConRecList */

typedef struct _SPTGConRecList{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGConRecList;

#ifdef PROTO_OK
static void _PrPTGConRecList(_PPTGConRecList n)
#else
static void _PrPTGConRecList(n)
	_PPTGConRecList n;
#endif
{
	PTG_OUTPUT_STRING(f, "LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": LST_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " .\n");
}

#ifdef PROTO_OK
PTGNode PTGConRecList(PTGNode p1, PTGNode p2)
#else
PTGNode PTGConRecList(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGConRecList n;
	n = (_PPTGConRecList)MALLOC(sizeof(struct _SPTGConRecList));
	n->_print = (_PTGProc)_PrPTGConRecList;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Mk0Name */

typedef struct _SPTGMk0Name{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMk0Name;

#ifdef PROTO_OK
static void _PrPTGMk0Name(_PPTGMk0Name n)
#else
static void _PrPTGMk0Name(n)
	_PPTGMk0Name n;
#endif
{
	PTG_OUTPUT_STRING(f, "0");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGMk0Name(PTGNode p1)
#else
PTGNode PTGMk0Name(p1)

PTGNode p1;
#endif
{
	_PPTGMk0Name n;
	n = (_PPTGMk0Name)MALLOC(sizeof(struct _SPTGMk0Name));
	n->_print = (_PTGProc)_PrPTGMk0Name;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkName */

typedef struct _SPTGMkName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkName;

#ifdef PROTO_OK
static void _PrPTGMkName(_PPTGMkName n)
#else
static void _PrPTGMkName(n)
	_PPTGMkName n;
#endif
{
	PTG_OUTPUT_STRING(f, "Mk");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGMkName(PTGNode p1)
#else
PTGNode PTGMkName(p1)

PTGNode p1;
#endif
{
	_PPTGMkName n;
	n = (_PPTGMkName)MALLOC(sizeof(struct _SPTGMkName));
	n->_print = (_PTGProc)_PrPTGMkName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ListGenSym */

typedef struct _SPTGListGenSym{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGListGenSym;

#ifdef PROTO_OK
static void _PrPTGListGenSym(_PPTGListGenSym n)
#else
static void _PrPTGListGenSym(n)
	_PPTGListGenSym n;
#endif
{
	PTG_OUTPUT_STRING(f, "LST_");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGListGenSym(PTGNode p1)
#else
PTGNode PTGListGenSym(p1)

PTGNode p1;
#endif
{
	_PPTGListGenSym n;
	n = (_PPTGListGenSym)MALLOC(sizeof(struct _SPTGListGenSym));
	n->_print = (_PTGProc)_PrPTGListGenSym;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CombineListArgs */

typedef struct _SPTGCombineListArgs{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGCombineListArgs;

#ifdef PROTO_OK
static void _PrPTGCombineListArgs(_PPTGCombineListArgs n)
#else
static void _PrPTGCombineListArgs(n)
	_PPTGCombineListArgs n;
#endif
{
	if (n->p2 != PTGNULL && n->p3 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, "Mk2");
		n->p1->_print(n->p1);
		PTG_OUTPUT_STRING(f, "(&curpos, ");
	}
	n->p2->_print(n->p2);
	if (n->p2 != PTGNULL && n->p3 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ", ");
	}
	n->p3->_print(n->p3);
	if (n->p2 != PTGNULL && n->p3 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ")");
	}
}

#ifdef PROTO_OK
PTGNode PTGCombineListArgs(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGCombineListArgs(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGCombineListArgs n;
	if(p2 == PTGNULL && p3 == PTGNULL)
		return PTGNULL;
	n = (_PPTGCombineListArgs)MALLOC(sizeof(struct _SPTGCombineListArgs));
	n->_print = (_PTGProc)_PrPTGCombineListArgs;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern NullNode */

typedef struct _SPTGNullNode{
	_PTGProc _print;
} * _PPTGNullNode;

#ifdef PROTO_OK
static void _PrPTGNullNode(_PPTGNullNode n)
#else
static void _PrPTGNullNode(n)
	_PPTGNullNode n;
#endif
{
	PTG_OUTPUT_STRING(f, "NULLNODEPTR");
}

static struct _SPTGNullNode _sptgNullNode = { (_PTGProc) _PrPTGNullNode };

#ifdef PROTO_OK
PTGNode PTGNullNode(void)
#else
PTGNode PTGNullNode()
#endif
{
	return (PTGNode)(&_sptgNullNode);
}


/* Implementation of Pattern ActionArg */

typedef struct _SPTGActionArg{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGActionArg;

#ifdef PROTO_OK
static void _PrPTGActionArg(_PPTGActionArg n)
#else
static void _PrPTGActionArg(n)
	_PPTGActionArg n;
#endif
{
	PTG_OUTPUT_STRING(f, "_nst[_nsp+");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGActionArg(PTGNode p1)
#else
PTGNode PTGActionArg(p1)

PTGNode p1;
#endif
{
	_PPTGActionArg n;
	n = (_PPTGActionArg)MALLOC(sizeof(struct _SPTGActionArg));
	n->_print = (_PTGProc)_PrPTGActionArg;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NestActionArg */

typedef struct _SPTGNestActionArg{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGNestActionArg;

#ifdef PROTO_OK
static void _PrPTGNestActionArg(_PPTGNestActionArg n)
#else
static void _PrPTGNestActionArg(n)
	_PPTGNestActionArg n;
#endif
{
	PTG_OUTPUT_STRING(f, "Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGNestActionArg(PTGNode p1, PTGNode p2)
#else
PTGNode PTGNestActionArg(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGNestActionArg n;
	n = (_PPTGNestActionArg)MALLOC(sizeof(struct _SPTGNestActionArg));
	n->_print = (_PTGProc)_PrPTGNestActionArg;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IncStackPtr */

typedef struct _SPTGIncStackPtr{
	_PTGProc _print;
} * _PPTGIncStackPtr;

#ifdef PROTO_OK
static void _PrPTGIncStackPtr(_PPTGIncStackPtr n)
#else
static void _PrPTGIncStackPtr(n)
	_PPTGIncStackPtr n;
#endif
{
	PTG_OUTPUT_STRING(f, "_incrnodestack();");
}

static struct _SPTGIncStackPtr _sptgIncStackPtr = { (_PTGProc) _PrPTGIncStackPtr };

#ifdef PROTO_OK
PTGNode PTGIncStackPtr(void)
#else
PTGNode PTGIncStackPtr()
#endif
{
	return (PTGNode)(&_sptgIncStackPtr);
}


/* Implementation of Pattern DecStackPtr */

typedef struct _SPTGDecStackPtr{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGDecStackPtr;

#ifdef PROTO_OK
static void _PrPTGDecStackPtr(_PPTGDecStackPtr n)
#else
static void _PrPTGDecStackPtr(n)
	_PPTGDecStackPtr n;
#endif
{
	PTG_OUTPUT_STRING(f, "_nsp -= ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGDecStackPtr(PTGNode p1)
#else
PTGNode PTGDecStackPtr(p1)

PTGNode p1;
#endif
{
	_PPTGDecStackPtr n;
	n = (_PPTGDecStackPtr)MALLOC(sizeof(struct _SPTGDecStackPtr));
	n->_print = (_PTGProc)_PrPTGDecStackPtr;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Action */

typedef struct _SPTGAction{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAction;

#ifdef PROTO_OK
static void _PrPTGAction(_PPTGAction n)
#else
static void _PrPTGAction(n)
	_PPTGAction n;
#endif
{
	PTG_OUTPUT_STRING(f, "&'");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "_nst[_nsp]=");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";'");
}

#ifdef PROTO_OK
PTGNode PTGAction(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAction(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAction n;
	n = (_PPTGAction)MALLOC(sizeof(struct _SPTGAction));
	n->_print = (_PTGProc)_PrPTGAction;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Pos */

typedef struct _SPTGPos{
	_PTGProc _print;
	int p1;
} * _PPTGPos;

#ifdef PROTO_OK
static void _PrPTGPos(_PPTGPos n)
#else
static void _PrPTGPos(n)
	_PPTGPos n;
#endif
{
	PrDecInt(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGPos(int p1)
#else
PTGNode PTGPos(p1)

int p1;
#endif
{
	_PPTGPos n;
	n = (_PPTGPos)MALLOC(sizeof(struct _SPTGPos));
	n->_print = (_PTGProc)_PrPTGPos;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TermAction */

typedef struct _SPTGTermAction{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGTermAction;

#ifdef PROTO_OK
static void _PrPTGTermAction(_PPTGTermAction n)
#else
static void _PrPTGTermAction(n)
	_PPTGTermAction n;
#endif
{
	PTG_OUTPUT_STRING(f, "Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(&(T_POS(TokenStack(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "))), ");
	PTG_OUTPUT_STRING(f, "T_ATTR(TokenStack(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")))");
}

#ifdef PROTO_OK
PTGNode PTGTermAction(PTGNode p1, PTGNode p2)
#else
PTGNode PTGTermAction(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGTermAction n;
	n = (_PPTGTermAction)MALLOC(sizeof(struct _SPTGTermAction));
	n->_print = (_PTGProc)_PrPTGTermAction;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern CoordStack */

typedef struct _SPTGCoordStack{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGCoordStack;

#ifdef PROTO_OK
static void _PrPTGCoordStack(_PPTGCoordStack n)
#else
static void _PrPTGCoordStack(n)
	_PPTGCoordStack n;
#endif
{
	PTG_OUTPUT_STRING(f, "&(T_POS(TokenStack(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")))");
}

#ifdef PROTO_OK
PTGNode PTGCoordStack(PTGNode p1)
#else
PTGNode PTGCoordStack(p1)

PTGNode p1;
#endif
{
	_PPTGCoordStack n;
	n = (_PPTGCoordStack)MALLOC(sizeof(struct _SPTGCoordStack));
	n->_print = (_PTGProc)_PrPTGCoordStack;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NoPosition */

typedef struct _SPTGNoPosition{
	_PTGProc _print;
} * _PPTGNoPosition;

#ifdef PROTO_OK
static void _PrPTGNoPosition(_PPTGNoPosition n)
#else
static void _PrPTGNoPosition(n)
	_PPTGNoPosition n;
#endif
{
	PTG_OUTPUT_STRING(f, "NoPosition");
}

static struct _SPTGNoPosition _sptgNoPosition = { (_PTGProc) _PrPTGNoPosition };

#ifdef PROTO_OK
PTGNode PTGNoPosition(void)
#else
PTGNode PTGNoPosition()
#endif
{
	return (PTGNode)(&_sptgNoPosition);
}


/* Implementation of Pattern CurPos */

typedef struct _SPTGCurPos{
	_PTGProc _print;
} * _PPTGCurPos;

#ifdef PROTO_OK
static void _PrPTGCurPos(_PPTGCurPos n)
#else
static void _PrPTGCurPos(n)
	_PPTGCurPos n;
#endif
{
	PTG_OUTPUT_STRING(f, "&curpos");
}

static struct _SPTGCurPos _sptgCurPos = { (_PTGProc) _PrPTGCurPos };

#ifdef PROTO_OK
PTGNode PTGCurPos(void)
#else
PTGNode PTGCurPos()
#endif
{
	return (PTGNode)(&_sptgCurPos);
}


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

