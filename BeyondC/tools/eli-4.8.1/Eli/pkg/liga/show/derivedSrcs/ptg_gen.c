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

/* Implementation of Pattern AttrListHead */

typedef struct _SPTGAttrListHead{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAttrListHead;

#ifdef PROTO_OK
static void _PrPTGAttrListHead(_PPTGAttrListHead n)
#else
static void _PrPTGAttrListHead(n)
	_PPTGAttrListHead n;
#endif
{
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ":");
}

#ifdef PROTO_OK
PTGNode PTGAttrListHead(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAttrListHead(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAttrListHead n;
	n = (_PPTGAttrListHead)MALLOC(sizeof(struct _SPTGAttrListHead));
	n->_print = (_PTGProc)_PrPTGAttrListHead;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrDecl */

typedef struct _SPTGAttrDecl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGAttrDecl;

#ifdef PROTO_OK
static void _PrPTGAttrDecl(_PPTGAttrDecl n)
#else
static void _PrPTGAttrDecl(n)
	_PPTGAttrDecl n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n	");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ");
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
}

#ifdef PROTO_OK
PTGNode PTGAttrDecl(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGAttrDecl(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGAttrDecl n;
	n = (_PPTGAttrDecl)MALLOC(sizeof(struct _SPTGAttrDecl));
	n->_print = (_PTGProc)_PrPTGAttrDecl;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrInfo */

typedef struct _SPTGAttrInfo{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGAttrInfo;

#ifdef PROTO_OK
static void _PrPTGAttrInfo(_PPTGAttrInfo n)
#else
static void _PrPTGAttrInfo(n)
	_PPTGAttrInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "/*  visit: ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " store: ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " origin: ");
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, " */");
}

#ifdef PROTO_OK
PTGNode PTGAttrInfo(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGAttrInfo(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGAttrInfo n;
	n = (_PPTGAttrInfo)MALLOC(sizeof(struct _SPTGAttrInfo));
	n->_print = (_PTGProc)_PrPTGAttrInfo;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeStore */

typedef struct _SPTGTreeStore{
	_PTGProc _print;
} * _PPTGTreeStore;

#ifdef PROTO_OK
static void _PrPTGTreeStore(_PPTGTreeStore n)
#else
static void _PrPTGTreeStore(n)
	_PPTGTreeStore n;
#endif
{
	PTG_OUTPUT_STRING(f, " TREE ");
}

static struct _SPTGTreeStore _sptgTreeStore = { (_PTGProc) _PrPTGTreeStore };

#ifdef PROTO_OK
PTGNode PTGTreeStore(void)
#else
PTGNode PTGTreeStore()
#endif
{
	return (PTGNode)(&_sptgTreeStore);
}


/* Implementation of Pattern StackStore */

typedef struct _SPTGStackStore{
	_PTGProc _print;
} * _PPTGStackStore;

#ifdef PROTO_OK
static void _PrPTGStackStore(_PPTGStackStore n)
#else
static void _PrPTGStackStore(n)
	_PPTGStackStore n;
#endif
{
	PTG_OUTPUT_STRING(f, " STACK ");
}

static struct _SPTGStackStore _sptgStackStore = { (_PTGProc) _PrPTGStackStore };

#ifdef PROTO_OK
PTGNode PTGStackStore(void)
#else
PTGNode PTGStackStore()
#endif
{
	return (PTGNode)(&_sptgStackStore);
}


/* Implementation of Pattern VarStore */

typedef struct _SPTGVarStore{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVarStore;

#ifdef PROTO_OK
static void _PrPTGVarStore(_PPTGVarStore n)
#else
static void _PrPTGVarStore(n)
	_PPTGVarStore n;
#endif
{
	PTG_OUTPUT_STRING(f, " VARIABLE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
}

#ifdef PROTO_OK
PTGNode PTGVarStore(PTGNode p1)
#else
PTGNode PTGVarStore(p1)

PTGNode p1;
#endif
{
	_PPTGVarStore n;
	n = (_PPTGVarStore)MALLOC(sizeof(struct _SPTGVarStore));
	n->_print = (_PTGProc)_PrPTGVarStore;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern OrigChain */

typedef struct _SPTGOrigChain{
	_PTGProc _print;
} * _PPTGOrigChain;

#ifdef PROTO_OK
static void _PrPTGOrigChain(_PPTGOrigChain n)
#else
static void _PrPTGOrigChain(n)
	_PPTGOrigChain n;
#endif
{
	PTG_OUTPUT_STRING(f, " CHAIN ");
}

static struct _SPTGOrigChain _sptgOrigChain = { (_PTGProc) _PrPTGOrigChain };

#ifdef PROTO_OK
PTGNode PTGOrigChain(void)
#else
PTGNode PTGOrigChain()
#endif
{
	return (PTGNode)(&_sptgOrigChain);
}


/* Implementation of Pattern OrigRule */

typedef struct _SPTGOrigRule{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGOrigRule;

#ifdef PROTO_OK
static void _PrPTGOrigRule(_PPTGOrigRule n)
#else
static void _PrPTGOrigRule(n)
	_PPTGOrigRule n;
#endif
{
	PTG_OUTPUT_STRING(f, " RULE ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGOrigRule(PTGNode p1)
#else
PTGNode PTGOrigRule(p1)

PTGNode p1;
#endif
{
	_PPTGOrigRule n;
	n = (_PPTGOrigRule)MALLOC(sizeof(struct _SPTGOrigRule));
	n->_print = (_PTGProc)_PrPTGOrigRule;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern OrigConst */

typedef struct _SPTGOrigConst{
	_PTGProc _print;
} * _PPTGOrigConst;

#ifdef PROTO_OK
static void _PrPTGOrigConst(_PPTGOrigConst n)
#else
static void _PrPTGOrigConst(n)
	_PPTGOrigConst n;
#endif
{
	PTG_OUTPUT_STRING(f, " CONSTITUENT(S) ");
}

static struct _SPTGOrigConst _sptgOrigConst = { (_PTGProc) _PrPTGOrigConst };

#ifdef PROTO_OK
PTGNode PTGOrigConst(void)
#else
PTGNode PTGOrigConst()
#endif
{
	return (PTGNode)(&_sptgOrigConst);
}


/* Implementation of Pattern OrigIncl */

typedef struct _SPTGOrigIncl{
	_PTGProc _print;
} * _PPTGOrigIncl;

#ifdef PROTO_OK
static void _PrPTGOrigIncl(_PPTGOrigIncl n)
#else
static void _PrPTGOrigIncl(n)
	_PPTGOrigIncl n;
#endif
{
	PTG_OUTPUT_STRING(f, " INCLUDING ");
}

static struct _SPTGOrigIncl _sptgOrigIncl = { (_PTGProc) _PrPTGOrigIncl };

#ifdef PROTO_OK
PTGNode PTGOrigIncl(void)
#else
PTGNode PTGOrigIncl()
#endif
{
	return (PTGNode)(&_sptgOrigIncl);
}


/* Implementation of Pattern Unknown */

typedef struct _SPTGUnknown{
	_PTGProc _print;
} * _PPTGUnknown;

#ifdef PROTO_OK
static void _PrPTGUnknown(_PPTGUnknown n)
#else
static void _PrPTGUnknown(n)
	_PPTGUnknown n;
#endif
{
	PTG_OUTPUT_STRING(f, " UNKNOWN ");
}

static struct _SPTGUnknown _sptgUnknown = { (_PTGProc) _PrPTGUnknown };

#ifdef PROTO_OK
PTGNode PTGUnknown(void)
#else
PTGNode PTGUnknown()
#endif
{
	return (PTGNode)(&_sptgUnknown);
}


/* Implementation of Pattern NONTERM */

typedef struct _SPTGNONTERM{
	_PTGProc _print;
} * _PPTGNONTERM;

#ifdef PROTO_OK
static void _PrPTGNONTERM(_PPTGNONTERM n)
#else
static void _PrPTGNONTERM(n)
	_PPTGNONTERM n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nNONTERM ");
}

static struct _SPTGNONTERM _sptgNONTERM = { (_PTGProc) _PrPTGNONTERM };

#ifdef PROTO_OK
PTGNode PTGNONTERM(void)
#else
PTGNode PTGNONTERM()
#endif
{
	return (PTGNode)(&_sptgNONTERM);
}


/* Implementation of Pattern TerminalDef */

typedef struct _SPTGTerminalDef{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
} * _PPTGTerminalDef;

#ifdef PROTO_OK
static void _PrPTGTerminalDef(_PPTGTerminalDef n)
#else
static void _PrPTGTerminalDef(n)
	_PPTGTerminalDef n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nTERM ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ": ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGTerminalDef(CONST char* p1, CONST char* p2)
#else
PTGNode PTGTerminalDef(p1, p2)

CONST char* p1;
CONST char* p2;
#endif
{
	_PPTGTerminalDef n;
	n = (_PPTGTerminalDef)MALLOC(sizeof(struct _SPTGTerminalDef));
	n->_print = (_PTGProc)_PrPTGTerminalDef;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern INH */

typedef struct _SPTGINH{
	_PTGProc _print;
} * _PPTGINH;

#ifdef PROTO_OK
static void _PrPTGINH(_PPTGINH n)
#else
static void _PrPTGINH(n)
	_PPTGINH n;
#endif
{
	PTG_OUTPUT_STRING(f, "INH  ");
}

static struct _SPTGINH _sptgINH = { (_PTGProc) _PrPTGINH };

#ifdef PROTO_OK
PTGNode PTGINH(void)
#else
PTGNode PTGINH()
#endif
{
	return (PTGNode)(&_sptgINH);
}


/* Implementation of Pattern SYNT */

typedef struct _SPTGSYNT{
	_PTGProc _print;
} * _PPTGSYNT;

#ifdef PROTO_OK
static void _PrPTGSYNT(_PPTGSYNT n)
#else
static void _PrPTGSYNT(n)
	_PPTGSYNT n;
#endif
{
	PTG_OUTPUT_STRING(f, "SYNT ");
}

static struct _SPTGSYNT _sptgSYNT = { (_PTGProc) _PrPTGSYNT };

#ifdef PROTO_OK
PTGNode PTGSYNT(void)
#else
PTGNode PTGSYNT()
#endif
{
	return (PTGNode)(&_sptgSYNT);
}


/* Implementation of Pattern Line */

typedef struct _SPTGLine{
	_PTGProc _print;
} * _PPTGLine;

#ifdef PROTO_OK
static void _PrPTGLine(_PPTGLine n)
#else
static void _PrPTGLine(n)
	_PPTGLine n;
#endif
{
	PTG_OUTPUT_STRING(f, "LINE ");
}

static struct _SPTGLine _sptgLine = { (_PTGProc) _PrPTGLine };

#ifdef PROTO_OK
PTGNode PTGLine(void)
#else
PTGNode PTGLine()
#endif
{
	return (PTGNode)(&_sptgLine);
}


/* Implementation of Pattern Col */

typedef struct _SPTGCol{
	_PTGProc _print;
} * _PPTGCol;

#ifdef PROTO_OK
static void _PrPTGCol(_PPTGCol n)
#else
static void _PrPTGCol(n)
	_PPTGCol n;
#endif
{
	PTG_OUTPUT_STRING(f, "COL ");
}

static struct _SPTGCol _sptgCol = { (_PTGProc) _PrPTGCol };

#ifdef PROTO_OK
PTGNode PTGCol(void)
#else
PTGNode PTGCol()
#endif
{
	return (PTGNode)(&_sptgCol);
}


/* Implementation of Pattern Addr */

typedef struct _SPTGAddr{
	_PTGProc _print;
} * _PPTGAddr;

#ifdef PROTO_OK
static void _PrPTGAddr(_PPTGAddr n)
#else
static void _PrPTGAddr(n)
	_PPTGAddr n;
#endif
{
	PTG_OUTPUT_STRING(f, "ADDR (...) ");
}

static struct _SPTGAddr _sptgAddr = { (_PTGProc) _PrPTGAddr };

#ifdef PROTO_OK
PTGNode PTGAddr(void)
#else
PTGNode PTGAddr()
#endif
{
	return (PTGNode)(&_sptgAddr);
}


/* Implementation of Pattern Order */

typedef struct _SPTGOrder{
	_PTGProc _print;
} * _PPTGOrder;

#ifdef PROTO_OK
static void _PrPTGOrder(_PPTGOrder n)
#else
static void _PrPTGOrder(n)
	_PPTGOrder n;
#endif
{
	PTG_OUTPUT_STRING(f, "ORDER (...) ");
}

static struct _SPTGOrder _sptgOrder = { (_PTGProc) _PrPTGOrder };

#ifdef PROTO_OK
PTGNode PTGOrder(void)
#else
PTGNode PTGOrder()
#endif
{
	return (PTGNode)(&_sptgOrder);
}


/* Implementation of Pattern Pragma */

typedef struct _SPTGPragma{
	_PTGProc _print;
} * _PPTGPragma;

#ifdef PROTO_OK
static void _PrPTGPragma(_PPTGPragma n)
#else
static void _PrPTGPragma(n)
	_PPTGPragma n;
#endif
{
	PTG_OUTPUT_STRING(f, "LIGAPragma (...) ");
}

static struct _SPTGPragma _sptgPragma = { (_PTGProc) _PrPTGPragma };

#ifdef PROTO_OK
PTGNode PTGPragma(void)
#else
PTGNode PTGPragma()
#endif
{
	return (PTGNode)(&_sptgPragma);
}


/* Implementation of Pattern If */

typedef struct _SPTGIf{
	_PTGProc _print;
} * _PPTGIf;

#ifdef PROTO_OK
static void _PrPTGIf(_PPTGIf n)
#else
static void _PrPTGIf(n)
	_PPTGIf n;
#endif
{
	PTG_OUTPUT_STRING(f, "IF (...) ");
}

static struct _SPTGIf _sptgIf = { (_PTGProc) _PrPTGIf };

#ifdef PROTO_OK
PTGNode PTGIf(void)
#else
PTGNode PTGIf()
#endif
{
	return (PTGNode)(&_sptgIf);
}


/* Implementation of Pattern Iterate */

typedef struct _SPTGIterate{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGIterate;

#ifdef PROTO_OK
static void _PrPTGIterate(_PPTGIterate n)
#else
static void _PrPTGIterate(n)
	_PPTGIterate n;
#endif
{
	PTG_OUTPUT_STRING(f, "ITERATE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = ... ");
}

#ifdef PROTO_OK
PTGNode PTGIterate(PTGNode p1)
#else
PTGNode PTGIterate(p1)

PTGNode p1;
#endif
{
	_PPTGIterate n;
	n = (_PPTGIterate)MALLOC(sizeof(struct _SPTGIterate));
	n->_print = (_PTGProc)_PrPTGIterate;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Call */

typedef struct _SPTGCall{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGCall;

#ifdef PROTO_OK
static void _PrPTGCall(_PPTGCall n)
#else
static void _PrPTGCall(n)
	_PPTGCall n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (...) ");
}

#ifdef PROTO_OK
PTGNode PTGCall(PTGNode p1)
#else
PTGNode PTGCall(p1)

PTGNode p1;
#endif
{
	_PPTGCall n;
	n = (_PPTGCall)MALLOC(sizeof(struct _SPTGCall));
	n->_print = (_PTGProc)_PrPTGCall;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Assign */

typedef struct _SPTGAssign{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAssign;

#ifdef PROTO_OK
static void _PrPTGAssign(_PPTGAssign n)
#else
static void _PrPTGAssign(n)
	_PPTGAssign n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGAssign(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAssign(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAssign n;
	n = (_PPTGAssign)MALLOC(sizeof(struct _SPTGAssign));
	n->_print = (_PTGProc)_PrPTGAssign;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermAcc */

typedef struct _SPTGNonLitTermAcc{
	_PTGProc _print;
	int p1;
} * _PPTGNonLitTermAcc;

#ifdef PROTO_OK
static void _PrPTGNonLitTermAcc(_PPTGNonLitTermAcc n)
#else
static void _PrPTGNonLitTermAcc(n)
	_PPTGNonLitTermAcc n;
#endif
{
	PTG_OUTPUT_STRING(f, "TERM[");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "] ");
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermAcc(int p1)
#else
PTGNode PTGNonLitTermAcc(p1)

int p1;
#endif
{
	_PPTGNonLitTermAcc n;
	n = (_PPTGNonLitTermAcc)MALLOC(sizeof(struct _SPTGNonLitTermAcc));
	n->_print = (_PTGProc)_PrPTGNonLitTermAcc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Constituents */

typedef struct _SPTGConstituents{
	_PTGProc _print;
} * _PPTGConstituents;

#ifdef PROTO_OK
static void _PrPTGConstituents(_PPTGConstituents n)
#else
static void _PrPTGConstituents(n)
	_PPTGConstituents n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONSTITUENTS ... ");
}

static struct _SPTGConstituents _sptgConstituents = { (_PTGProc) _PrPTGConstituents };

#ifdef PROTO_OK
PTGNode PTGConstituents(void)
#else
PTGNode PTGConstituents()
#endif
{
	return (PTGNode)(&_sptgConstituents);
}


/* Implementation of Pattern Constituent */

typedef struct _SPTGConstituent{
	_PTGProc _print;
} * _PPTGConstituent;

#ifdef PROTO_OK
static void _PrPTGConstituent(_PPTGConstituent n)
#else
static void _PrPTGConstituent(n)
	_PPTGConstituent n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONSTITUENT ... ");
}

static struct _SPTGConstituent _sptgConstituent = { (_PTGProc) _PrPTGConstituent };

#ifdef PROTO_OK
PTGNode PTGConstituent(void)
#else
PTGNode PTGConstituent()
#endif
{
	return (PTGNode)(&_sptgConstituent);
}


/* Implementation of Pattern Constituent_s */

typedef struct _SPTGConstituent_s{
	_PTGProc _print;
} * _PPTGConstituent_s;

#ifdef PROTO_OK
static void _PrPTGConstituent_s(_PPTGConstituent_s n)
#else
static void _PrPTGConstituent_s(n)
	_PPTGConstituent_s n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONSTITUENT(S) ... ");
}

static struct _SPTGConstituent_s _sptgConstituent_s = { (_PTGProc) _PrPTGConstituent_s };

#ifdef PROTO_OK
PTGNode PTGConstituent_s(void)
#else
PTGNode PTGConstituent_s()
#endif
{
	return (PTGNode)(&_sptgConstituent_s);
}


/* Implementation of Pattern Including */

typedef struct _SPTGIncluding{
	_PTGProc _print;
} * _PPTGIncluding;

#ifdef PROTO_OK
static void _PrPTGIncluding(_PPTGIncluding n)
#else
static void _PrPTGIncluding(n)
	_PPTGIncluding n;
#endif
{
	PTG_OUTPUT_STRING(f, "INCLUDING ... ");
}

static struct _SPTGIncluding _sptgIncluding = { (_PTGProc) _PrPTGIncluding };

#ifdef PROTO_OK
PTGNode PTGIncluding(void)
#else
PTGNode PTGIncluding()
#endif
{
	return (PTGNode)(&_sptgIncluding);
}


/* Implementation of Pattern VisitRule */

typedef struct _SPTGVisitRule{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGVisitRule;

#ifdef PROTO_OK
static void _PrPTGVisitRule(_PPTGVisitRule n)
#else
static void _PrPTGVisitRule(n)
	_PPTGVisitRule n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nRULE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ::= ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGVisitRule(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGVisitRule(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGVisitRule n;
	n = (_PPTGVisitRule)MALLOC(sizeof(struct _SPTGVisitRule));
	n->_print = (_PTGProc)_PrPTGVisitRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbolIndex */

typedef struct _SPTGSymbolIndex{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSymbolIndex;

#ifdef PROTO_OK
static void _PrPTGSymbolIndex(_PPTGSymbolIndex n)
#else
static void _PrPTGSymbolIndex(n)
	_PPTGSymbolIndex n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGSymbolIndex(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSymbolIndex(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSymbolIndex n;
	n = (_PPTGSymbolIndex)MALLOC(sizeof(struct _SPTGSymbolIndex));
	n->_print = (_PTGProc)_PrPTGSymbolIndex;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Symbol */

typedef struct _SPTGSymbol{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSymbol;

#ifdef PROTO_OK
static void _PrPTGSymbol(_PPTGSymbol n)
#else
static void _PrPTGSymbol(n)
	_PPTGSymbol n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
}

#ifdef PROTO_OK
PTGNode PTGSymbol(PTGNode p1)
#else
PTGNode PTGSymbol(p1)

PTGNode p1;
#endif
{
	_PPTGSymbol n;
	n = (_PPTGSymbol)MALLOC(sizeof(struct _SPTGSymbol));
	n->_print = (_PTGProc)_PrPTGSymbol;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern GenSymbol */

typedef struct _SPTGGenSymbol{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGGenSymbol;

#ifdef PROTO_OK
static void _PrPTGGenSymbol(_PPTGGenSymbol n)
#else
static void _PrPTGGenSymbol(n)
	_PPTGGenSymbol n;
#endif
{
	PTG_OUTPUT_STRING(f, "$ ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGGenSymbol(PTGNode p1)
#else
PTGNode PTGGenSymbol(p1)

PTGNode p1;
#endif
{
	_PPTGGenSymbol n;
	n = (_PPTGGenSymbol)MALLOC(sizeof(struct _SPTGGenSymbol));
	n->_print = (_PTGProc)_PrPTGGenSymbol;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Literal */

typedef struct _SPTGLiteral{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLiteral;

#ifdef PROTO_OK
static void _PrPTGLiteral(_PPTGLiteral n)
#else
static void _PrPTGLiteral(n)
	_PPTGLiteral n;
#endif
{
	PTG_OUTPUT_STRING(f, "'");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "' ");
}

#ifdef PROTO_OK
PTGNode PTGLiteral(PTGNode p1)
#else
PTGNode PTGLiteral(p1)

PTGNode p1;
#endif
{
	_PPTGLiteral n;
	n = (_PPTGLiteral)MALLOC(sizeof(struct _SPTGLiteral));
	n->_print = (_PTGProc)_PrPTGLiteral;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Visit */

typedef struct _SPTGVisit{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGVisit;

#ifdef PROTO_OK
static void _PrPTGVisit(_PPTGVisit n)
#else
static void _PrPTGVisit(n)
	_PPTGVisit n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n	visit no. ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " to ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGVisit(PTGNode p1, PTGNode p2)
#else
PTGNode PTGVisit(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGVisit n;
	n = (_PPTGVisit)MALLOC(sizeof(struct _SPTGVisit));
	n->_print = (_PTGProc)_PrPTGVisit;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Leave */

typedef struct _SPTGLeave{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLeave;

#ifdef PROTO_OK
static void _PrPTGLeave(_PPTGLeave n)
#else
static void _PrPTGLeave(n)
	_PPTGLeave n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n	leave no. ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGLeave(PTGNode p1)
#else
PTGNode PTGLeave(p1)

PTGNode p1;
#endif
{
	_PPTGLeave n;
	n = (_PPTGLeave)MALLOC(sizeof(struct _SPTGLeave));
	n->_print = (_PTGProc)_PrPTGLeave;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Computation */

typedef struct _SPTGComputation{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGComputation;

#ifdef PROTO_OK
static void _PrPTGComputation(_PPTGComputation n)
#else
static void _PrPTGComputation(n)
	_PPTGComputation n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n     ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "; in ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGComputation(PTGNode p1, PTGNode p2)
#else
PTGNode PTGComputation(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGComputation n;
	n = (_PPTGComputation)MALLOC(sizeof(struct _SPTGComputation));
	n->_print = (_PTGProc)_PrPTGComputation;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Label */

typedef struct _SPTGLabel{
	_PTGProc _print;
} * _PPTGLabel;

#ifdef PROTO_OK
static void _PrPTGLabel(_PPTGLabel n)
#else
static void _PrPTGLabel(n)
	_PPTGLabel n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n     ITERATE on preceeding attribute");
}

static struct _SPTGLabel _sptgLabel = { (_PTGProc) _PrPTGLabel };

#ifdef PROTO_OK
PTGNode PTGLabel(void)
#else
PTGNode PTGLabel()
#endif
{
	return (PTGNode)(&_sptgLabel);
}


/* Implementation of Pattern ChainStart */

typedef struct _SPTGChainStart{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGChainStart;

#ifdef PROTO_OK
static void _PrPTGChainStart(_PPTGChainStart n)
#else
static void _PrPTGChainStart(n)
	_PPTGChainStart n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n	CHAINSTART ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGChainStart(PTGNode p1)
#else
PTGNode PTGChainStart(p1)

PTGNode p1;
#endif
{
	_PPTGChainStart n;
	n = (_PPTGChainStart)MALLOC(sizeof(struct _SPTGChainStart));
	n->_print = (_PTGProc)_PrPTGChainStart;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrAcc */

typedef struct _SPTGAttrAcc{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAttrAcc;

#ifdef PROTO_OK
static void _PrPTGAttrAcc(_PPTGAttrAcc n)
#else
static void _PrPTGAttrAcc(n)
	_PPTGAttrAcc n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ".");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGAttrAcc(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAttrAcc(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAttrAcc n;
	n = (_PPTGAttrAcc)MALLOC(sizeof(struct _SPTGAttrAcc));
	n->_print = (_PTGProc)_PrPTGAttrAcc;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern FileList */

typedef struct _SPTGFileList{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGFileList;

#ifdef PROTO_OK
static void _PrPTGFileList(_PPTGFileList n)
#else
static void _PrPTGFileList(n)
	_PPTGFileList n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* Coordinates are denoted (Fi:line:col) with");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n*/\n");
}

#ifdef PROTO_OK
PTGNode PTGFileList(PTGNode p1)
#else
PTGNode PTGFileList(p1)

PTGNode p1;
#endif
{
	_PPTGFileList n;
	n = (_PPTGFileList)MALLOC(sizeof(struct _SPTGFileList));
	n->_print = (_PTGProc)_PrPTGFileList;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern FileAssoc */

typedef struct _SPTGFileAssoc{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGFileAssoc;

#ifdef PROTO_OK
static void _PrPTGFileAssoc(_PPTGFileAssoc n)
#else
static void _PrPTGFileAssoc(n)
	_PPTGFileAssoc n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n	");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":  ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGFileAssoc(PTGNode p1, PTGNode p2)
#else
PTGNode PTGFileAssoc(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGFileAssoc n;
	n = (_PPTGFileAssoc)MALLOC(sizeof(struct _SPTGFileAssoc));
	n->_print = (_PTGProc)_PrPTGFileAssoc;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Coord */

typedef struct _SPTGCoord{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGCoord;

#ifdef PROTO_OK
static void _PrPTGCoord(_PPTGCoord n)
#else
static void _PrPTGCoord(n)
	_PPTGCoord n;
#endif
{
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ":");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGCoord(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGCoord(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGCoord n;
	n = (_PPTGCoord)MALLOC(sizeof(struct _SPTGCoord));
	n->_print = (_PTGProc)_PrPTGCoord;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern FileRef */

typedef struct _SPTGFileRef{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGFileRef;

#ifdef PROTO_OK
static void _PrPTGFileRef(_PPTGFileRef n)
#else
static void _PrPTGFileRef(n)
	_PPTGFileRef n;
#endif
{
	PTG_OUTPUT_STRING(f, "F");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGFileRef(PTGNode p1)
#else
PTGNode PTGFileRef(p1)

PTGNode p1;
#endif
{
	_PPTGFileRef n;
	n = (_PPTGFileRef)MALLOC(sizeof(struct _SPTGFileRef));
	n->_print = (_PTGProc)_PrPTGFileRef;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Comma */

typedef struct _SPTGComma{
	_PTGProc _print;
} * _PPTGComma;

#ifdef PROTO_OK
static void _PrPTGComma(_PPTGComma n)
#else
static void _PrPTGComma(n)
	_PPTGComma n;
#endif
{
	PTG_OUTPUT_STRING(f, ", ");
}

static struct _SPTGComma _sptgComma = { (_PTGProc) _PrPTGComma };

#ifdef PROTO_OK
PTGNode PTGComma(void)
#else
PTGNode PTGComma()
#endif
{
	return (PTGNode)(&_sptgComma);
}


/* Implementation of Pattern Semicol */

typedef struct _SPTGSemicol{
	_PTGProc _print;
} * _PPTGSemicol;

#ifdef PROTO_OK
static void _PrPTGSemicol(_PPTGSemicol n)
#else
static void _PrPTGSemicol(n)
	_PPTGSemicol n;
#endif
{
	PTG_OUTPUT_STRING(f, "; ");
}

static struct _SPTGSemicol _sptgSemicol = { (_PTGProc) _PrPTGSemicol };

#ifdef PROTO_OK
PTGNode PTGSemicol(void)
#else
PTGNode PTGSemicol()
#endif
{
	return (PTGNode)(&_sptgSemicol);
}


/* Implementation of Pattern ColSemi */

typedef struct _SPTGColSemi{
	_PTGProc _print;
} * _PPTGColSemi;

#ifdef PROTO_OK
static void _PrPTGColSemi(_PPTGColSemi n)
#else
static void _PrPTGColSemi(n)
	_PPTGColSemi n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n: ;\n");
}

static struct _SPTGColSemi _sptgColSemi = { (_PTGProc) _PrPTGColSemi };

#ifdef PROTO_OK
PTGNode PTGColSemi(void)
#else
PTGNode PTGColSemi()
#endif
{
	return (PTGNode)(&_sptgColSemi);
}


/* Implementation of Pattern NewLine */

typedef struct _SPTGNewLine{
	_PTGProc _print;
} * _PPTGNewLine;

#ifdef PROTO_OK
static void _PrPTGNewLine(_PPTGNewLine n)
#else
static void _PrPTGNewLine(n)
	_PPTGNewLine n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
}

static struct _SPTGNewLine _sptgNewLine = { (_PTGProc) _PrPTGNewLine };

#ifdef PROTO_OK
PTGNode PTGNewLine(void)
#else
PTGNode PTGNewLine()
#endif
{
	return (PTGNode)(&_sptgNewLine);
}


/* Implementation of Pattern Space2 */

typedef struct _SPTGSpace2{
	_PTGProc _print;
} * _PPTGSpace2;

#ifdef PROTO_OK
static void _PrPTGSpace2(_PPTGSpace2 n)
#else
static void _PrPTGSpace2(n)
	_PPTGSpace2 n;
#endif
{
	PTG_OUTPUT_STRING(f, "  ");
}

static struct _SPTGSpace2 _sptgSpace2 = { (_PTGProc) _PrPTGSpace2 };

#ifdef PROTO_OK
PTGNode PTGSpace2(void)
#else
PTGNode PTGSpace2()
#endif
{
	return (PTGNode)(&_sptgSpace2);
}


/* Implementation of Pattern CChar */

typedef struct _SPTGCChar{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGCChar;

#ifdef PROTO_OK
static void _PrPTGCChar(_PPTGCChar n)
#else
static void _PrPTGCChar(n)
	_PPTGCChar n;
#endif
{
	PTG_OUTPUT_STRING(f, "'");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "'");
}

#ifdef PROTO_OK
PTGNode PTGCChar(CONST char* p1)
#else
PTGNode PTGCChar(p1)

CONST char* p1;
#endif
{
	_PPTGCChar n;
	n = (_PPTGCChar)MALLOC(sizeof(struct _SPTGCChar));
	n->_print = (_PTGProc)_PrPTGCChar;
	n->p1 = p1;
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

