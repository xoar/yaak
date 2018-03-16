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

/* Implementation of Pattern ThisNode */

typedef struct _SPTGThisNode{
	_PTGProc _print;
} * _PPTGThisNode;

#ifdef PROTO_OK
static void _PrPTGThisNode(_PPTGThisNode n)
#else
static void _PrPTGThisNode(n)
	_PPTGThisNode n;
#endif
{
	PTG_OUTPUT_STRING(f, "_currn");
}

static struct _SPTGThisNode _sptgThisNode = { (_PTGProc) _PrPTGThisNode };

#ifdef PROTO_OK
PTGNode PTGThisNode(void)
#else
PTGNode PTGThisNode()
#endif
{
	return (PTGNode)(&_sptgThisNode);
}


/* Implementation of Pattern DescNode */

typedef struct _SPTGDescNode{
	_PTGProc _print;
	int p1;
} * _PPTGDescNode;

#ifdef PROTO_OK
static void _PrPTGDescNode(_PPTGDescNode n)
#else
static void _PrPTGDescNode(n)
	_PPTGDescNode n;
#endif
{
	PTG_OUTPUT_STRING(f, "_currn->_desc");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGDescNode(int p1)
#else
PTGNode PTGDescNode(p1)

int p1;
#endif
{
	_PPTGDescNode n;
	n = (_PPTGDescNode)MALLOC(sizeof(struct _SPTGDescNode));
	n->_print = (_PTGProc)_PrPTGDescNode;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern DescName */

typedef struct _SPTGDescName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGDescName;

#ifdef PROTO_OK
static void _PrPTGDescName(_PPTGDescName n)
#else
static void _PrPTGDescName(n)
	_PPTGDescName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_desc");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGDescName(PTGNode p1)
#else
PTGNode PTGDescName(p1)

PTGNode p1;
#endif
{
	_PPTGDescName n;
	n = (_PPTGDescName)MALLOC(sizeof(struct _SPTGDescName));
	n->_print = (_PTGProc)_PrPTGDescName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitProcName */

typedef struct _SPTGVisitProcName{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGVisitProcName;

#ifdef PROTO_OK
static void _PrPTGVisitProcName(_PPTGVisitProcName n)
#else
static void _PrPTGVisitProcName(n)
	_PPTGVisitProcName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_VS");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGVisitProcName(PTGNode p1, PTGNode p2)
#else
PTGNode PTGVisitProcName(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGVisitProcName n;
	n = (_PPTGVisitProcName)MALLOC(sizeof(struct _SPTGVisitProcName));
	n->_print = (_PTGProc)_PrPTGVisitProcName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern InclGlobName */

typedef struct _SPTGInclGlobName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGInclGlobName;

#ifdef PROTO_OK
static void _PrPTGInclGlobName(_PPTGInclGlobName n)
#else
static void _PrPTGInclGlobName(n)
	_PPTGInclGlobName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_IG");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGInclGlobName(PTGNode p1)
#else
PTGNode PTGInclGlobName(p1)

PTGNode p1;
#endif
{
	_PPTGInclGlobName n;
	n = (_PPTGInclGlobName)MALLOC(sizeof(struct _SPTGInclGlobName));
	n->_print = (_PTGProc)_PrPTGInclGlobName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern InclLocName */

typedef struct _SPTGInclLocName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGInclLocName;

#ifdef PROTO_OK
static void _PrPTGInclLocName(_PPTGInclLocName n)
#else
static void _PrPTGInclLocName(n)
	_PPTGInclLocName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_IL");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGInclLocName(PTGNode p1)
#else
PTGNode PTGInclLocName(p1)

PTGNode p1;
#endif
{
	_PPTGInclLocName n;
	n = (_PPTGInclLocName)MALLOC(sizeof(struct _SPTGInclLocName));
	n->_print = (_PTGProc)_PrPTGInclLocName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbStructName */

typedef struct _SPTGSymbStructName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSymbStructName;

#ifdef PROTO_OK
static void _PrPTGSymbStructName(_PPTGSymbStructName n)
#else
static void _PrPTGSymbStructName(n)
	_PPTGSymbStructName n;
#endif
{
	PTG_OUTPUT_STRING(f, "struct _TS");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGSymbStructName(PTGNode p1)
#else
PTGNode PTGSymbStructName(p1)

PTGNode p1;
#endif
{
	_PPTGSymbStructName n;
	n = (_PPTGSymbStructName)MALLOC(sizeof(struct _SPTGSymbStructName));
	n->_print = (_PTGProc)_PrPTGSymbStructName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbPtrTypeName */

typedef struct _SPTGSymbPtrTypeName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSymbPtrTypeName;

#ifdef PROTO_OK
static void _PrPTGSymbPtrTypeName(_PPTGSymbPtrTypeName n)
#else
static void _PrPTGSymbPtrTypeName(n)
	_PPTGSymbPtrTypeName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_TSP");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGSymbPtrTypeName(PTGNode p1)
#else
PTGNode PTGSymbPtrTypeName(p1)

PTGNode p1;
#endif
{
	_PPTGSymbPtrTypeName n;
	n = (_PPTGSymbPtrTypeName)MALLOC(sizeof(struct _SPTGSymbPtrTypeName));
	n->_print = (_PTGProc)_PrPTGSymbPtrTypeName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ProdStructName */

typedef struct _SPTGProdStructName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGProdStructName;

#ifdef PROTO_OK
static void _PrPTGProdStructName(_PPTGProdStructName n)
#else
static void _PrPTGProdStructName(n)
	_PPTGProdStructName n;
#endif
{
	PTG_OUTPUT_STRING(f, "struct _TP");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGProdStructName(PTGNode p1)
#else
PTGNode PTGProdStructName(p1)

PTGNode p1;
#endif
{
	_PPTGProdStructName n;
	n = (_PPTGProdStructName)MALLOC(sizeof(struct _SPTGProdStructName));
	n->_print = (_PTGProc)_PrPTGProdStructName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ProdPtrTypeName */

typedef struct _SPTGProdPtrTypeName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGProdPtrTypeName;

#ifdef PROTO_OK
static void _PrPTGProdPtrTypeName(_PPTGProdPtrTypeName n)
#else
static void _PrPTGProdPtrTypeName(n)
	_PPTGProdPtrTypeName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_TPP");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGProdPtrTypeName(PTGNode p1)
#else
PTGNode PTGProdPtrTypeName(p1)

PTGNode p1;
#endif
{
	_PPTGProdPtrTypeName n;
	n = (_PPTGProdPtrTypeName)MALLOC(sizeof(struct _SPTGProdPtrTypeName));
	n->_print = (_PTGProc)_PrPTGProdPtrTypeName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkProcName */

typedef struct _SPTGMkProcName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkProcName;

#ifdef PROTO_OK
static void _PrPTGMkProcName(_PPTGMkProcName n)
#else
static void _PrPTGMkProcName(n)
	_PPTGMkProcName n;
#endif
{
	PTG_OUTPUT_STRING(f, "Mk");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGMkProcName(PTGNode p1)
#else
PTGNode PTGMkProcName(p1)

PTGNode p1;
#endif
{
	_PPTGMkProcName n;
	n = (_PPTGMkProcName)MALLOC(sizeof(struct _SPTGMkProcName));
	n->_print = (_PTGProc)_PrPTGMkProcName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NullNodePtr */

typedef struct _SPTGNullNodePtr{
	_PTGProc _print;
} * _PPTGNullNodePtr;

#ifdef PROTO_OK
static void _PrPTGNullNodePtr(_PPTGNullNodePtr n)
#else
static void _PrPTGNullNodePtr(n)
	_PPTGNullNodePtr n;
#endif
{
	PTG_OUTPUT_STRING(f, "NULLNODEPTR ");
}

static struct _SPTGNullNodePtr _sptgNullNodePtr = { (_PTGProc) _PrPTGNullNodePtr };

#ifdef PROTO_OK
PTGNode PTGNullNodePtr(void)
#else
PTGNode PTGNullNodePtr()
#endif
{
	return (PTGNode)(&_sptgNullNodePtr);
}


/* Implementation of Pattern MkParmName */

typedef struct _SPTGMkParmName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkParmName;

#ifdef PROTO_OK
static void _PrPTGMkParmName(_PPTGMkParmName n)
#else
static void _PrPTGMkParmName(n)
	_PPTGMkParmName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_tr");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGMkParmName(PTGNode p1)
#else
PTGNode PTGMkParmName(p1)

PTGNode p1;
#endif
{
	_PPTGMkParmName n;
	n = (_PPTGMkParmName)MALLOC(sizeof(struct _SPTGMkParmName));
	n->_print = (_PTGProc)_PrPTGMkParmName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TermGetName */

typedef struct _SPTGTermGetName{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGTermGetName;

#ifdef PROTO_OK
static void _PrPTGTermGetName(_PPTGTermGetName n)
#else
static void _PrPTGTermGetName(n)
	_PPTGTermGetName n;
#endif
{
	PTG_OUTPUT_STRING(f, "GET");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGTermGetName(PTGNode p1, PTGNode p2)
#else
PTGNode PTGTermGetName(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGTermGetName n;
	n = (_PPTGTermGetName)MALLOC(sizeof(struct _SPTGTermGetName));
	n->_print = (_PTGProc)_PrPTGTermGetName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern LhsStackAttrName */

typedef struct _SPTGLhsStackAttrName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLhsStackAttrName;

#ifdef PROTO_OK
static void _PrPTGLhsStackAttrName(_PPTGLhsStackAttrName n)
#else
static void _PrPTGLhsStackAttrName(n)
	_PPTGLhsStackAttrName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_AS0");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGLhsStackAttrName(PTGNode p1)
#else
PTGNode PTGLhsStackAttrName(p1)

PTGNode p1;
#endif
{
	_PPTGLhsStackAttrName n;
	n = (_PPTGLhsStackAttrName)MALLOC(sizeof(struct _SPTGLhsStackAttrName));
	n->_print = (_PTGProc)_PrPTGLhsStackAttrName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern RhsStackAttrName */

typedef struct _SPTGRhsStackAttrName{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGRhsStackAttrName;

#ifdef PROTO_OK
static void _PrPTGRhsStackAttrName(_PPTGRhsStackAttrName n)
#else
static void _PrPTGRhsStackAttrName(n)
	_PPTGRhsStackAttrName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_AS");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGRhsStackAttrName(PTGNode p1, PTGNode p2)
#else
PTGNode PTGRhsStackAttrName(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGRhsStackAttrName n;
	n = (_PPTGRhsStackAttrName)MALLOC(sizeof(struct _SPTGRhsStackAttrName));
	n->_print = (_PTGProc)_PrPTGRhsStackAttrName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern VarAttrName */

typedef struct _SPTGVarAttrName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVarAttrName;

#ifdef PROTO_OK
static void _PrPTGVarAttrName(_PPTGVarAttrName n)
#else
static void _PrPTGVarAttrName(n)
	_PPTGVarAttrName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_AV");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGVarAttrName(PTGNode p1)
#else
PTGNode PTGVarAttrName(p1)

PTGNode p1;
#endif
{
	_PPTGVarAttrName n;
	n = (_PPTGVarAttrName)MALLOC(sizeof(struct _SPTGVarAttrName));
	n->_print = (_PTGProc)_PrPTGVarAttrName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeAttrName */

typedef struct _SPTGTreeAttrName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGTreeAttrName;

#ifdef PROTO_OK
static void _PrPTGTreeAttrName(_PPTGTreeAttrName n)
#else
static void _PrPTGTreeAttrName(n)
	_PPTGTreeAttrName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_AT");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGTreeAttrName(PTGNode p1)
#else
PTGNode PTGTreeAttrName(p1)

PTGNode p1;
#endif
{
	_PPTGTreeAttrName n;
	n = (_PPTGTreeAttrName)MALLOC(sizeof(struct _SPTGTreeAttrName));
	n->_print = (_PTGProc)_PrPTGTreeAttrName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern RuleAttrName */

typedef struct _SPTGRuleAttrName{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGRuleAttrName;

#ifdef PROTO_OK
static void _PrPTGRuleAttrName(_PPTGRuleAttrName n)
#else
static void _PrPTGRuleAttrName(n)
	_PPTGRuleAttrName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_AR");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGRuleAttrName(PTGNode p1, PTGNode p2)
#else
PTGNode PTGRuleAttrName(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGRuleAttrName n;
	n = (_PPTGRuleAttrName)MALLOC(sizeof(struct _SPTGRuleAttrName));
	n->_print = (_PTGProc)_PrPTGRuleAttrName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Stmt */

typedef struct _SPTGStmt{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGStmt;

#ifdef PROTO_OK
static void _PrPTGStmt(_PPTGStmt n)
#else
static void _PrPTGStmt(n)
	_PPTGStmt n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	new_line(f);
}

#ifdef PROTO_OK
PTGNode PTGStmt(PTGNode p1)
#else
PTGNode PTGStmt(p1)

PTGNode p1;
#endif
{
	_PPTGStmt n;
	n = (_PPTGStmt)MALLOC(sizeof(struct _SPTGStmt));
	n->_print = (_PTGProc)_PrPTGStmt;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Call */

typedef struct _SPTGCall{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGCall;

#ifdef PROTO_OK
static void _PrPTGCall(_PPTGCall n)
#else
static void _PrPTGCall(n)
	_PPTGCall n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGCall(PTGNode p1, PTGNode p2)
#else
PTGNode PTGCall(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGCall n;
	n = (_PPTGCall)MALLOC(sizeof(struct _SPTGCall));
	n->_print = (_PTGProc)_PrPTGCall;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ProcExpr */

typedef struct _SPTGProcExpr{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGProcExpr;

#ifdef PROTO_OK
static void _PrPTGProcExpr(_PPTGProcExpr n)
#else
static void _PrPTGProcExpr(n)
	_PPTGProcExpr n;
#endif
{
	PTG_OUTPUT_STRING(f, "(*(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) ");
}

#ifdef PROTO_OK
PTGNode PTGProcExpr(PTGNode p1)
#else
PTGNode PTGProcExpr(p1)

PTGNode p1;
#endif
{
	_PPTGProcExpr n;
	n = (_PPTGProcExpr)MALLOC(sizeof(struct _SPTGProcExpr));
	n->_print = (_PTGProc)_PrPTGProcExpr;
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
	PTG_OUTPUT_STRING(f, "=");
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


/* Implementation of Pattern IfStmt */

typedef struct _SPTGIfStmt{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIfStmt;

#ifdef PROTO_OK
static void _PrPTGIfStmt(_PPTGIfStmt n)
#else
static void _PrPTGIfStmt(n)
	_PPTGIfStmt n;
#endif
{
	new_line(f);
	PTG_OUTPUT_STRING(f, "if (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") {");
	new_line(f);
	n->p2->_print(n->p2);
	new_line(f);
	PTG_OUTPUT_STRING(f, "} else {");
	new_line(f);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "}");
	new_line(f);
}

#ifdef PROTO_OK
PTGNode PTGIfStmt(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIfStmt(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIfStmt n;
	n = (_PPTGIfStmt)MALLOC(sizeof(struct _SPTGIfStmt));
	n->_print = (_PTGProc)_PrPTGIfStmt;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern IfExpr */

typedef struct _SPTGIfExpr{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIfExpr;

#ifdef PROTO_OK
static void _PrPTGIfExpr(_PPTGIfExpr n)
#else
static void _PrPTGIfExpr(n)
	_PPTGIfExpr n;
#endif
{
	new_line(f);
	PTG_OUTPUT_STRING(f, "((");
	n->p1->_print(n->p1);
	new_line(f);
	PTG_OUTPUT_STRING(f, ") ? (");
	n->p2->_print(n->p2);
	new_line(f);
	PTG_OUTPUT_STRING(f, ") : (");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "))");
	new_line(f);
}

#ifdef PROTO_OK
PTGNode PTGIfExpr(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIfExpr(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIfExpr n;
	n = (_PPTGIfExpr)MALLOC(sizeof(struct _SPTGIfExpr));
	n->_print = (_PTGProc)_PrPTGIfExpr;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Paren */

typedef struct _SPTGParen{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGParen;

#ifdef PROTO_OK
static void _PrPTGParen(_PPTGParen n)
#else
static void _PrPTGParen(n)
	_PPTGParen n;
#endif
{
	new_line(f);
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
	new_line(f);
}

#ifdef PROTO_OK
PTGNode PTGParen(PTGNode p1)
#else
PTGNode PTGParen(p1)

PTGNode p1;
#endif
{
	_PPTGParen n;
	n = (_PPTGParen)MALLOC(sizeof(struct _SPTGParen));
	n->_print = (_PTGProc)_PrPTGParen;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PtrTo */

typedef struct _SPTGPtrTo{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGPtrTo;

#ifdef PROTO_OK
static void _PrPTGPtrTo(_PPTGPtrTo n)
#else
static void _PrPTGPtrTo(n)
	_PPTGPtrTo n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "*");
}

#ifdef PROTO_OK
PTGNode PTGPtrTo(PTGNode p1)
#else
PTGNode PTGPtrTo(p1)

PTGNode p1;
#endif
{
	_PPTGPtrTo n;
	n = (_PPTGPtrTo)MALLOC(sizeof(struct _SPTGPtrTo));
	n->_print = (_PTGProc)_PrPTGPtrTo;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SelectPtr */

typedef struct _SPTGSelectPtr{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSelectPtr;

#ifdef PROTO_OK
static void _PrPTGSelectPtr(_PPTGSelectPtr n)
#else
static void _PrPTGSelectPtr(n)
	_PPTGSelectPtr n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "->");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGSelectPtr(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSelectPtr(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSelectPtr n;
	n = (_PPTGSelectPtr)MALLOC(sizeof(struct _SPTGSelectPtr));
	n->_print = (_PTGProc)_PrPTGSelectPtr;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Content */

typedef struct _SPTGContent{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGContent;

#ifdef PROTO_OK
static void _PrPTGContent(_PPTGContent n)
#else
static void _PrPTGContent(n)
	_PPTGContent n;
#endif
{
	PTG_OUTPUT_STRING(f, "(* ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGContent(PTGNode p1)
#else
PTGNode PTGContent(p1)

PTGNode p1;
#endif
{
	_PPTGContent n;
	n = (_PPTGContent)MALLOC(sizeof(struct _SPTGContent));
	n->_print = (_PTGProc)_PrPTGContent;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Addr */

typedef struct _SPTGAddr{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAddr;

#ifdef PROTO_OK
static void _PrPTGAddr(_PPTGAddr n)
#else
static void _PrPTGAddr(n)
	_PPTGAddr n;
#endif
{
	PTG_OUTPUT_STRING(f, "(&( ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "))");
}

#ifdef PROTO_OK
PTGNode PTGAddr(PTGNode p1)
#else
PTGNode PTGAddr(p1)

PTGNode p1;
#endif
{
	_PPTGAddr n;
	n = (_PPTGAddr)MALLOC(sizeof(struct _SPTGAddr));
	n->_print = (_PTGProc)_PrPTGAddr;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NoVal */

typedef struct _SPTGNoVal{
	_PTGProc _print;
} * _PPTGNoVal;

#ifdef PROTO_OK
static void _PrPTGNoVal(_PPTGNoVal n)
#else
static void _PrPTGNoVal(n)
	_PPTGNoVal n;
#endif
{
	PTG_OUTPUT_STRING(f, "(0)");
}

static struct _SPTGNoVal _sptgNoVal = { (_PTGProc) _PrPTGNoVal };

#ifdef PROTO_OK
PTGNode PTGNoVal(void)
#else
PTGNode PTGNoVal()
#endif
{
	return (PTGNode)(&_sptgNoVal);
}


/* Implementation of Pattern ToNoVal */

typedef struct _SPTGToNoVal{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGToNoVal;

#ifdef PROTO_OK
static void _PrPTGToNoVal(_PPTGToNoVal n)
#else
static void _PrPTGToNoVal(n)
	_PPTGToNoVal n;
#endif
{
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ", 0)");
}

#ifdef PROTO_OK
PTGNode PTGToNoVal(PTGNode p1)
#else
PTGNode PTGToNoVal(p1)

PTGNode p1;
#endif
{
	_PPTGToNoVal n;
	n = (_PPTGToNoVal)MALLOC(sizeof(struct _SPTGToNoVal));
	n->_print = (_PTGProc)_PrPTGToNoVal;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Decl */

typedef struct _SPTGDecl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGDecl;

#ifdef PROTO_OK
static void _PrPTGDecl(_PPTGDecl n)
#else
static void _PrPTGDecl(n)
	_PPTGDecl n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";\n");
}

#ifdef PROTO_OK
PTGNode PTGDecl(PTGNode p1, PTGNode p2)
#else
PTGNode PTGDecl(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGDecl n;
	n = (_PPTGDecl)MALLOC(sizeof(struct _SPTGDecl));
	n->_print = (_PTGProc)_PrPTGDecl;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Proto */

typedef struct _SPTGProto{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGProto;

#ifdef PROTO_OK
static void _PrPTGProto(_PPTGProto n)
#else
static void _PrPTGProto(n)
	_PPTGProto n;
#endif
{
	PTG_OUTPUT_STRING(f, ",");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGProto(PTGNode p1, PTGNode p2)
#else
PTGNode PTGProto(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGProto n;
	n = (_PPTGProto)MALLOC(sizeof(struct _SPTGProto));
	n->_print = (_PTGProc)_PrPTGProto;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ExternDecl */

typedef struct _SPTGExternDecl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGExternDecl;

#ifdef PROTO_OK
static void _PrPTGExternDecl(_PPTGExternDecl n)
#else
static void _PrPTGExternDecl(n)
	_PPTGExternDecl n;
#endif
{
	PTG_OUTPUT_STRING(f, "extern ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";\n");
}

#ifdef PROTO_OK
PTGNode PTGExternDecl(PTGNode p1, PTGNode p2)
#else
PTGNode PTGExternDecl(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGExternDecl n;
	n = (_PPTGExternDecl)MALLOC(sizeof(struct _SPTGExternDecl));
	n->_print = (_PTGProc)_PrPTGExternDecl;
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


/* Implementation of Pattern ComElem */

typedef struct _SPTGComElem{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGComElem;

#ifdef PROTO_OK
static void _PrPTGComElem(_PPTGComElem n)
#else
static void _PrPTGComElem(n)
	_PPTGComElem n;
#endif
{
	PTG_OUTPUT_STRING(f, ",");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGComElem(PTGNode p1)
#else
PTGNode PTGComElem(p1)

PTGNode p1;
#endif
{
	_PPTGComElem n;
	n = (_PPTGComElem)MALLOC(sizeof(struct _SPTGComElem));
	n->_print = (_PTGProc)_PrPTGComElem;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ComSeq */

typedef struct _SPTGComSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGComSeq;

#ifdef PROTO_OK
static void _PrPTGComSeq(_PPTGComSeq n)
#else
static void _PrPTGComSeq(n)
	_PPTGComSeq n;
#endif
{
	PTG_OUTPUT_STRING(f, ",");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGComSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGComSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGComSeq n;
	n = (_PPTGComSeq)MALLOC(sizeof(struct _SPTGComSeq));
	n->_print = (_PTGProc)_PrPTGComSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern SeqCom */

typedef struct _SPTGSeqCom{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSeqCom;

#ifdef PROTO_OK
static void _PrPTGSeqCom(_PPTGSeqCom n)
#else
static void _PrPTGSeqCom(n)
	_PPTGSeqCom n;
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
PTGNode PTGSeqCom(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSeqCom(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSeqCom n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGSeqCom)MALLOC(sizeof(struct _SPTGSeqCom));
	n->_print = (_PTGProc)_PrPTGSeqCom;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Sep */

typedef struct _SPTGSep{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSep;

#ifdef PROTO_OK
static void _PrPTGSep(_PPTGSep n)
#else
static void _PrPTGSep(n)
	_PPTGSep n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
}

#ifdef PROTO_OK
PTGNode PTGSep(PTGNode p1)
#else
PTGNode PTGSep(p1)

PTGNode p1;
#endif
{
	_PPTGSep n;
	n = (_PPTGSep)MALLOC(sizeof(struct _SPTGSep));
	n->_print = (_PTGProc)_PrPTGSep;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern File */

typedef struct _SPTGFile{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGFile;

#ifdef PROTO_OK
static void _PrPTGFile(_PPTGFile n)
#else
static void _PrPTGFile(n)
	_PPTGFile n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGFile(PTGNode p1)
#else
PTGNode PTGFile(p1)

PTGNode p1;
#endif
{
	_PPTGFile n;
	n = (_PPTGFile)MALLOC(sizeof(struct _SPTGFile));
	n->_print = (_PTGProc)_PrPTGFile;
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


/* Implementation of Pattern C_Str */

typedef struct _SPTGC_Str{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGC_Str;

#ifdef PROTO_OK
static void _PrPTGC_Str(_PPTGC_Str n)
#else
static void _PrPTGC_Str(n)
	_PPTGC_Str n;
#endif
{
	C_outstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGC_Str(CONST char* p1)
#else
PTGNode PTGC_Str(p1)

CONST char* p1;
#endif
{
	_PPTGC_Str n;
	n = (_PPTGC_Str)MALLOC(sizeof(struct _SPTGC_Str));
	n->_print = (_PTGProc)_PrPTGC_Str;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern P_Str */

typedef struct _SPTGP_Str{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGP_Str;

#ifdef PROTO_OK
static void _PrPTGP_Str(_PPTGP_Str n)
#else
static void _PrPTGP_Str(n)
	_PPTGP_Str n;
#endif
{
	P_outstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGP_Str(CONST char* p1)
#else
PTGNode PTGP_Str(p1)

CONST char* p1;
#endif
{
	_PPTGP_Str n;
	n = (_PPTGP_Str)MALLOC(sizeof(struct _SPTGP_Str));
	n->_print = (_PTGProc)_PrPTGP_Str;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SpecLineInfo */

typedef struct _SPTGSpecLineInfo{
	_PTGProc _print;
	int p1;
} * _PPTGSpecLineInfo;

#ifdef PROTO_OK
static void _PrPTGSpecLineInfo(_PPTGSpecLineInfo n)
#else
static void _PrPTGSpecLineInfo(n)
	_PPTGSpecLineInfo n;
#endif
{
	PTG_OUTPUT_STRING(f, "/*SPC(");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ")*/\n");
}

#ifdef PROTO_OK
PTGNode PTGSpecLineInfo(int p1)
#else
PTGNode PTGSpecLineInfo(p1)

int p1;
#endif
{
	_PPTGSpecLineInfo n;
	n = (_PPTGSpecLineInfo)MALLOC(sizeof(struct _SPTGSpecLineInfo));
	n->_print = (_PTGProc)_PrPTGSpecLineInfo;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitProcFileHead */

typedef struct _SPTGVisitProcFileHead{
	_PTGProc _print;
} * _PPTGVisitProcFileHead;

#ifdef PROTO_OK
static void _PrPTGVisitProcFileHead(_PPTGVisitProcFileHead n)
#else
static void _PrPTGVisitProcFileHead(n)
	_PPTGVisitProcFileHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#include \"HEAD.h\"\n#include \"err.h\"\n#include \"node.h\"\n#include \"visitprocs.h\"\n#include \"attrpredef.h\"\n\n#include \"visitmap.h\"\n\n#ifdef MONITOR\n#include \"attr_mon_dapto.h\"\n#include \"liga_dapto.h\"\n#endif\n\n#ifndef _VisitVarDecl\n#define _VisitVarDecl()\n#endif\n\n#ifndef _VisitEntry\n#define _VisitEntry()\n#endif\n\n#ifndef _VisitExit\n#define _VisitExit()\n#endif\n\n");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\n#define _CALL_VS_(args) (void (*)args)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n#define _CALL_VS_(args) ");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n");
}

static struct _SPTGVisitProcFileHead _sptgVisitProcFileHead = { (_PTGProc) _PrPTGVisitProcFileHead };

#ifdef PROTO_OK
PTGNode PTGVisitProcFileHead(void)
#else
PTGNode PTGVisitProcFileHead()
#endif
{
	return (PTGNode)(&_sptgVisitProcFileHead);
}


/* Implementation of Pattern RootProc */

typedef struct _SPTGRootProc{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGRootProc;

#ifdef PROTO_OK
static void _PrPTGRootProc(_PPTGRootProc n)
#else
static void _PrPTGRootProc(n)
	_PPTGRootProc n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nvoid LIGA_ATTREVAL (NODEPTR _currn)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nvoid LIGA_ATTREVAL (_currn) NODEPTR _currn;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "}\n/*SPC(0)*/\n");
}

#ifdef PROTO_OK
PTGNode PTGRootProc(PTGNode p1)
#else
PTGNode PTGRootProc(p1)

PTGNode p1;
#endif
{
	_PPTGRootProc n;
	n = (_PPTGRootProc)MALLOC(sizeof(struct _SPTGRootProc));
	n->_print = (_PTGProc)_PrPTGRootProc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern RootVisit */

typedef struct _SPTGRootVisit{
	_PTGProc _print;
} * _PPTGRootVisit;

#ifdef PROTO_OK
static void _PrPTGRootVisit(_PPTGRootVisit n)
#else
static void _PrPTGRootVisit(n)
	_PPTGRootVisit n;
#endif
{
	PTG_OUTPUT_STRING(f, "(*(VS1MAP[_currn->_prod])) ((NODEPTR)_currn);");
}

static struct _SPTGRootVisit _sptgRootVisit = { (_PTGProc) _PrPTGRootVisit };

#ifdef PROTO_OK
PTGNode PTGRootVisit(void)
#else
PTGNode PTGRootVisit()
#endif
{
	return (PTGNode)(&_sptgRootVisit);
}


/* Implementation of Pattern PredefVSProc */

typedef struct _SPTGPredefVSProc{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGPredefVSProc;

#ifdef PROTO_OK
static void _PrPTGPredefVSProc(_PPTGPredefVSProc n)
#else
static void _PrPTGPredefVSProc(n)
	_PPTGPredefVSProc n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nvoid ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(NODEPTR _currn)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nvoid ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_currn) NODEPTR _currn;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{ _VisitVarDecl()\n_VisitEntry();\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n_VisitExit();\n}\n");
}

#ifdef PROTO_OK
PTGNode PTGPredefVSProc(PTGNode p1, PTGNode p2)
#else
PTGNode PTGPredefVSProc(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGPredefVSProc n;
	n = (_PPTGPredefVSProc)MALLOC(sizeof(struct _SPTGPredefVSProc));
	n->_print = (_PTGProc)_PrPTGPredefVSProc;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern PredefVSHeader */

typedef struct _SPTGPredefVSHeader{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGPredefVSHeader;

#ifdef PROTO_OK
static void _PrPTGPredefVSHeader(_PPTGPredefVSHeader n)
#else
static void _PrPTGPredefVSHeader(n)
	_PPTGPredefVSHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern void ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((NODEPTR _currn));");
}

#ifdef PROTO_OK
PTGNode PTGPredefVSHeader(PTGNode p1)
#else
PTGNode PTGPredefVSHeader(p1)

PTGNode p1;
#endif
{
	_PPTGPredefVSHeader n;
	n = (_PPTGPredefVSHeader)MALLOC(sizeof(struct _SPTGPredefVSHeader));
	n->_print = (_PTGProc)_PrPTGPredefVSHeader;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitHeader */

typedef struct _SPTGVisitHeader{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVisitHeader;

#ifdef PROTO_OK
static void _PrPTGVisitHeader(_PPTGVisitHeader n)
#else
static void _PrPTGVisitHeader(n)
	_PPTGVisitHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#ifndef _VISITPROCS_H\n#define _VISITPROCS_H\n");
	PTG_OUTPUT_STRING(f, "\n#include \"HEAD.h\"");
	PTG_OUTPUT_STRING(f, "\n#include \"node.h\"");
	PTG_OUTPUT_STRING(f, "\n#include \"treecon.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"eliproto.h\"\n");
	PTG_OUTPUT_STRING(f, "\n\nextern void LIGA_ATTREVAL ELI_ARG((NODEPTR));");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGVisitHeader(PTGNode p1)
#else
PTGNode PTGVisitHeader(p1)

PTGNode p1;
#endif
{
	_PPTGVisitHeader n;
	n = (_PPTGVisitHeader)MALLOC(sizeof(struct _SPTGVisitHeader));
	n->_print = (_PTGProc)_PrPTGVisitHeader;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitProcHeader */

typedef struct _SPTGVisitProcHeader{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGVisitProcHeader;

#ifdef PROTO_OK
static void _PrPTGVisitProcHeader(_PPTGVisitProcHeader n)
#else
static void _PrPTGVisitProcHeader(n)
	_PPTGVisitProcHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern void ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " _currn");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "));");
}

#ifdef PROTO_OK
PTGNode PTGVisitProcHeader(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGVisitProcHeader(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGVisitProcHeader n;
	n = (_PPTGVisitProcHeader)MALLOC(sizeof(struct _SPTGVisitProcHeader));
	n->_print = (_PTGProc)_PrPTGVisitProcHeader;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern DefineVS */

typedef struct _SPTGDefineVS{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGDefineVS;

#ifdef PROTO_OK
static void _PrPTGDefineVS(_PPTGDefineVS n)
#else
static void _PrPTGDefineVS(n)
	_PPTGDefineVS n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#define ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGDefineVS(PTGNode p1, PTGNode p2)
#else
PTGNode PTGDefineVS(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGDefineVS n;
	n = (_PPTGDefineVS)MALLOC(sizeof(struct _SPTGDefineVS));
	n->_print = (_PTGProc)_PrPTGDefineVS;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitProcHead */

typedef struct _SPTGVisitProcHead{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
	PTGNode p8;
} * _PPTGVisitProcHead;

#ifdef PROTO_OK
static void _PrPTGVisitProcHead(_PPTGVisitProcHead n)
#else
static void _PrPTGVisitProcHead(n)
	_PPTGVisitProcHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nvoid ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " _currn");
	n->p8->_print(n->p8);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nvoid ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_currn ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " _currn;\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{\n");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "\n_VisitVarDecl()\n_VisitEntry();\n");
	n->p6->_print(n->p6);
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, "\n_VisitExit();\n}\n");
}

#ifdef PROTO_OK
PTGNode PTGVisitProcHead(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8)
#else
PTGNode PTGVisitProcHead(p1, p2, p3, p4, p5, p6, p7, p8)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
PTGNode p8;
#endif
{
	_PPTGVisitProcHead n;
	n = (_PPTGVisitProcHead)MALLOC(sizeof(struct _SPTGVisitProcHead));
	n->_print = (_PTGProc)_PrPTGVisitProcHead;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	return (PTGNode)n;
}


/* Implementation of Pattern DescVisit */

typedef struct _SPTGDescVisit{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGDescVisit;

#ifdef PROTO_OK
static void _PrPTGDescVisit(_PPTGDescVisit n)
#else
static void _PrPTGDescVisit(n)
	_PPTGDescVisit n;
#endif
{
	PTG_OUTPUT_STRING(f, "(*(_CALL_VS_((NODEPTR ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ")) ");
	PTG_OUTPUT_STRING(f, "(VS");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "MAP[_currn->");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "->_prod])))((NODEPTR) _currn->");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ");\n");
}

#ifdef PROTO_OK
PTGNode PTGDescVisit(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGDescVisit(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGDescVisit n;
	n = (_PPTGDescVisit)MALLOC(sizeof(struct _SPTGDescVisit));
	n->_print = (_PTGProc)_PrPTGDescVisit;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern GenAssign */

typedef struct _SPTGGenAssign{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	PTGNode p3;
} * _PPTGGenAssign;

#ifdef PROTO_OK
static void _PrPTGGenAssign(_PPTGGenAssign n)
#else
static void _PrPTGGenAssign(n)
	_PPTGGenAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "{ ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = (_TSP");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ") ");
	PTG_OUTPUT_STRING(f, "Mk");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "(NoPosition, ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "  if ((NODEPTR)");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " == NULLNODEPTR)\n");
	PTG_OUTPUT_STRING(f, "    message (DEADLY, \"generated tree is not of type ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\", 0, NoPosition);\n}");
}

#ifdef PROTO_OK
PTGNode PTGGenAssign(PTGNode p1, CONST char* p2, PTGNode p3)
#else
PTGNode PTGGenAssign(p1, p2, p3)

PTGNode p1;
CONST char* p2;
PTGNode p3;
#endif
{
	_PPTGGenAssign n;
	n = (_PPTGGenAssign)MALLOC(sizeof(struct _SPTGGenAssign));
	n->_print = (_PTGProc)_PrPTGGenAssign;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeActHead */

typedef struct _SPTGTreeActHead{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGTreeActHead;

#ifdef PROTO_OK
static void _PrPTGTreeActHead(_PPTGTreeActHead n)
#else
static void _PrPTGTreeActHead(n)
	_PPTGTreeActHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n\n#define _TERMACT_");
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGTreeActHead(CONST char* p1)
#else
PTGNode PTGTreeActHead(p1)

CONST char* p1;
#endif
{
	_PPTGTreeActHead n;
	n = (_PPTGTreeActHead)MALLOC(sizeof(struct _SPTGTreeActHead));
	n->_print = (_PTGProc)_PrPTGTreeActHead;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern DefineLine */

typedef struct _SPTGDefineLine{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGDefineLine;

#ifdef PROTO_OK
static void _PrPTGDefineLine(_PPTGDefineLine n)
#else
static void _PrPTGDefineLine(n)
	_PPTGDefineLine n;
#endif
{
	PTG_OUTPUT_STRING(f, " \\\n\t");
	cpp_new_line(f);
	n->p1->_print(n->p1);
	ord_new_line(f);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGDefineLine(PTGNode p1)
#else
PTGNode PTGDefineLine(p1)

PTGNode p1;
#endif
{
	_PPTGDefineLine n;
	n = (_PPTGDefineLine)MALLOC(sizeof(struct _SPTGDefineLine));
	n->_print = (_PTGProc)_PrPTGDefineLine;
	n->p1 = p1;
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
	PTG_OUTPUT_STRING(f, "_TERM");
	PTG_OUTPUT_INT(f, n->p1);
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


/* Implementation of Pattern LineSelect */

typedef struct _SPTGLineSelect{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLineSelect;

#ifdef PROTO_OK
static void _PrPTGLineSelect(_PPTGLineSelect n)
#else
static void _PrPTGLineSelect(n)
	_PPTGLineSelect n;
#endif
{
	PTG_OUTPUT_STRING(f, "((");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ").line)");
}

#ifdef PROTO_OK
PTGNode PTGLineSelect(PTGNode p1)
#else
PTGNode PTGLineSelect(p1)

PTGNode p1;
#endif
{
	_PPTGLineSelect n;
	n = (_PPTGLineSelect)MALLOC(sizeof(struct _SPTGLineSelect));
	n->_print = (_PTGProc)_PrPTGLineSelect;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ColSelect */

typedef struct _SPTGColSelect{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGColSelect;

#ifdef PROTO_OK
static void _PrPTGColSelect(_PPTGColSelect n)
#else
static void _PrPTGColSelect(n)
	_PPTGColSelect n;
#endif
{
	PTG_OUTPUT_STRING(f, "((");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ").col)");
}

#ifdef PROTO_OK
PTGNode PTGColSelect(PTGNode p1)
#else
PTGNode PTGColSelect(p1)

PTGNode p1;
#endif
{
	_PPTGColSelect n;
	n = (_PPTGColSelect)MALLOC(sizeof(struct _SPTGColSelect));
	n->_print = (_PTGProc)_PrPTGColSelect;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern LineAccess */

typedef struct _SPTGLineAccess{
	_PTGProc _print;
} * _PPTGLineAccess;

#ifdef PROTO_OK
static void _PrPTGLineAccess(_PPTGLineAccess n)
#else
static void _PrPTGLineAccess(n)
	_PPTGLineAccess n;
#endif
{
	PTG_OUTPUT_STRING(f, "(_coordref ? _coordref->line : 0)");
}

static struct _SPTGLineAccess _sptgLineAccess = { (_PTGProc) _PrPTGLineAccess };

#ifdef PROTO_OK
PTGNode PTGLineAccess(void)
#else
PTGNode PTGLineAccess()
#endif
{
	return (PTGNode)(&_sptgLineAccess);
}


/* Implementation of Pattern ColAccess */

typedef struct _SPTGColAccess{
	_PTGProc _print;
} * _PPTGColAccess;

#ifdef PROTO_OK
static void _PrPTGColAccess(_PPTGColAccess n)
#else
static void _PrPTGColAccess(n)
	_PPTGColAccess n;
#endif
{
	PTG_OUTPUT_STRING(f, "(_coordref ? _coordref->col : 0)");
}

static struct _SPTGColAccess _sptgColAccess = { (_PTGProc) _PrPTGColAccess };

#ifdef PROTO_OK
PTGNode PTGColAccess(void)
#else
PTGNode PTGColAccess()
#endif
{
	return (PTGNode)(&_sptgColAccess);
}


/* Implementation of Pattern CoordAccess */

typedef struct _SPTGCoordAccess{
	_PTGProc _print;
} * _PPTGCoordAccess;

#ifdef PROTO_OK
static void _PrPTGCoordAccess(_PPTGCoordAccess n)
#else
static void _PrPTGCoordAccess(n)
	_PPTGCoordAccess n;
#endif
{
	PTG_OUTPUT_STRING(f, "(_coordref ? *_coordref : NoCoord)");
}

static struct _SPTGCoordAccess _sptgCoordAccess = { (_PTGProc) _PrPTGCoordAccess };

#ifdef PROTO_OK
PTGNode PTGCoordAccess(void)
#else
PTGNode PTGCoordAccess()
#endif
{
	return (PTGNode)(&_sptgCoordAccess);
}


/* Implementation of Pattern Label */

typedef struct _SPTGLabel{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLabel;

#ifdef PROTO_OK
static void _PrPTGLabel(_PPTGLabel n)
#else
static void _PrPTGLabel(n)
	_PPTGLabel n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ":;\n");
}

#ifdef PROTO_OK
PTGNode PTGLabel(PTGNode p1)
#else
PTGNode PTGLabel(p1)

PTGNode p1;
#endif
{
	_PPTGLabel n;
	n = (_PPTGLabel)MALLOC(sizeof(struct _SPTGLabel));
	n->_print = (_PTGProc)_PrPTGLabel;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern LabName */

typedef struct _SPTGLabName{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGLabName;

#ifdef PROTO_OK
static void _PrPTGLabName(_PPTGLabName n)
#else
static void _PrPTGLabName(n)
	_PPTGLabName n;
#endif
{
	PTG_OUTPUT_STRING(f, "_CYCLE");
	n->p2->_print(n->p2);
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGLabName(PTGNode p1, PTGNode p2)
#else
PTGNode PTGLabName(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGLabName n;
	n = (_PPTGLabName)MALLOC(sizeof(struct _SPTGLabName));
	n->_print = (_PTGProc)_PrPTGLabName;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Loop */

typedef struct _SPTGLoop{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGLoop;

#ifdef PROTO_OK
static void _PrPTGLoop(_PPTGLoop n)
#else
static void _PrPTGLoop(n)
	_PPTGLoop n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nif (!(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) {\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\ngoto ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n}\n");
}

#ifdef PROTO_OK
PTGNode PTGLoop(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGLoop(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGLoop n;
	n = (_PPTGLoop)MALLOC(sizeof(struct _SPTGLoop));
	n->_print = (_PTGProc)_PrPTGLoop;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern InclPre */

typedef struct _SPTGInclPre{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGInclPre;

#ifdef PROTO_OK
static void _PrPTGInclPre(_PPTGInclPre n)
#else
static void _PrPTGInclPre(n)
	_PPTGInclPre n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "=");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "= &(_currn->");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ");\n");
}

#ifdef PROTO_OK
PTGNode PTGInclPre(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGInclPre(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGInclPre n;
	n = (_PPTGInclPre)MALLOC(sizeof(struct _SPTGInclPre));
	n->_print = (_PTGProc)_PrPTGInclPre;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern InclPost */

typedef struct _SPTGInclPost{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGInclPost;

#ifdef PROTO_OK
static void _PrPTGInclPost(_PPTGInclPost n)
#else
static void _PrPTGInclPost(n)
	_PPTGInclPost n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "=");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";\n");
}

#ifdef PROTO_OK
PTGNode PTGInclPost(PTGNode p1, PTGNode p2)
#else
PTGNode PTGInclPost(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGInclPost n;
	n = (_PPTGInclPost)MALLOC(sizeof(struct _SPTGInclPost));
	n->_print = (_PTGProc)_PrPTGInclPost;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern NodeTypeFile */

typedef struct _SPTGNodeTypeFile{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGNodeTypeFile;

#ifdef PROTO_OK
static void _PrPTGNodeTypeFile(_PPTGNodeTypeFile n)
#else
static void _PrPTGNodeTypeFile(n)
	_PPTGNodeTypeFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* definition of tree node structure */\n");
	PTG_OUTPUT_STRING(f, "\n#ifndef NODE_H");
	PTG_OUTPUT_STRING(f, "\n#define NODE_H");
	PTG_OUTPUT_STRING(f, "\n#include \"err.h\"");
	PTG_OUTPUT_STRING(f, "\n#include \"nodeptr.h\" /* defines NODEPTR */");
	PTG_OUTPUT_STRING(f, "\n#include \"HEAD.h\"");
	PTG_OUTPUT_STRING(f, "\n\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\n#define _NODECOMMON int _prod; POSITION _coord; int _uid;");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n#define _NODECOMMON int _prod;");
	PTG_OUTPUT_STRING(f, "\n#endif\n");
	PTG_OUTPUT_STRING(f, "struct NODEPTR_struct {\n");
	PTG_OUTPUT_STRING(f, "        _NODECOMMON\n");
	PTG_OUTPUT_STRING(f, "#ifdef __cplusplus\n");
	PTG_OUTPUT_STRING(f, "        void* operator new(size_t size);\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "};\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n#undef _NODECOMMON");
	PTG_OUTPUT_STRING(f, "\n#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGNodeTypeFile(PTGNode p1, PTGNode p2)
#else
PTGNode PTGNodeTypeFile(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGNodeTypeFile n;
	n = (_PPTGNodeTypeFile)MALLOC(sizeof(struct _SPTGNodeTypeFile));
	n->_print = (_PTGProc)_PrPTGNodeTypeFile;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ProdTypeDef */

typedef struct _SPTGProdTypeDef{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGProdTypeDef;

#ifdef PROTO_OK
static void _PrPTGProdTypeDef(_PPTGProdTypeDef n)
#else
static void _PrPTGProdTypeDef(n)
	_PPTGProdTypeDef n;
#endif
{
	PTG_OUTPUT_STRING(f, "\ntypedef struct _TP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "* _TPP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGProdTypeDef(CONST char* p1)
#else
PTGNode PTGProdTypeDef(p1)

CONST char* p1;
#endif
{
	_PPTGProdTypeDef n;
	n = (_PPTGProdTypeDef)MALLOC(sizeof(struct _SPTGProdTypeDef));
	n->_print = (_PTGProc)_PrPTGProdTypeDef;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbTypeDef */

typedef struct _SPTGSymbTypeDef{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGSymbTypeDef;

#ifdef PROTO_OK
static void _PrPTGSymbTypeDef(_PPTGSymbTypeDef n)
#else
static void _PrPTGSymbTypeDef(n)
	_PPTGSymbTypeDef n;
#endif
{
	PTG_OUTPUT_STRING(f, "\ntypedef struct _TS");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "* _TSP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGSymbTypeDef(CONST char* p1)
#else
PTGNode PTGSymbTypeDef(p1)

CONST char* p1;
#endif
{
	_PPTGSymbTypeDef n;
	n = (_PPTGSymbTypeDef)MALLOC(sizeof(struct _SPTGSymbTypeDef));
	n->_print = (_PTGProc)_PrPTGSymbTypeDef;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ProdStructDecl */

typedef struct _SPTGProdStructDecl{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGProdStructDecl;

#ifdef PROTO_OK
static void _PrPTGProdStructDecl(_PPTGProdStructDecl n)
#else
static void _PrPTGProdStructDecl(n)
	_PPTGProdStructDecl n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nstruct _TP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\n\t: public NODEPTR_struct {");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n_NODECOMMON");
	PTG_OUTPUT_STRING(f, "\n#endif");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n};\n");
}

#ifdef PROTO_OK
PTGNode PTGProdStructDecl(CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGProdStructDecl(p1, p2, p3, p4)

CONST char* p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGProdStructDecl n;
	n = (_PPTGProdStructDecl)MALLOC(sizeof(struct _SPTGProdStructDecl));
	n->_print = (_PTGProc)_PrPTGProdStructDecl;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern ListDescs */

typedef struct _SPTGListDescs{
	_PTGProc _print;
} * _PPTGListDescs;

#ifdef PROTO_OK
static void _PrPTGListDescs(_PPTGListDescs n)
#else
static void _PrPTGListDescs(n)
	_PPTGListDescs n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nNODEPTR _desc1;\nNODEPTR _desc2;");
}

static struct _SPTGListDescs _sptgListDescs = { (_PTGProc) _PrPTGListDescs };

#ifdef PROTO_OK
PTGNode PTGListDescs(void)
#else
PTGNode PTGListDescs()
#endif
{
	return (PTGNode)(&_sptgListDescs);
}


/* Implementation of Pattern SymbStructDecl */

typedef struct _SPTGSymbStructDecl{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGSymbStructDecl;

#ifdef PROTO_OK
static void _PrPTGSymbStructDecl(_PPTGSymbStructDecl n)
#else
static void _PrPTGSymbStructDecl(n)
	_PPTGSymbStructDecl n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nstruct _TS");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\n\t: public NODEPTR_struct {");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n_NODECOMMON");
	PTG_OUTPUT_STRING(f, "\n#endif");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n};\n");
}

#ifdef PROTO_OK
PTGNode PTGSymbStructDecl(CONST char* p1, PTGNode p2)
#else
PTGNode PTGSymbStructDecl(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGSymbStructDecl n;
	n = (_PPTGSymbStructDecl)MALLOC(sizeof(struct _SPTGSymbStructDecl));
	n->_print = (_PTGProc)_PrPTGSymbStructDecl;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern SubTreeComp */

typedef struct _SPTGSubTreeComp{
	_PTGProc _print;
	CONST char* p1;
	int p2;
} * _PPTGSubTreeComp;

#ifdef PROTO_OK
static void _PrPTGSubTreeComp(_PPTGSubTreeComp n)
#else
static void _PrPTGSubTreeComp(n)
	_PPTGSubTreeComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n_TSP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " _desc");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGSubTreeComp(CONST char* p1, int p2)
#else
PTGNode PTGSubTreeComp(p1, p2)

CONST char* p1;
int p2;
#endif
{
	_PPTGSubTreeComp n;
	n = (_PPTGSubTreeComp)MALLOC(sizeof(struct _SPTGSubTreeComp));
	n->_print = (_PTGProc)_PrPTGSubTreeComp;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrComp */

typedef struct _SPTGAttrComp{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
} * _PPTGAttrComp;

#ifdef PROTO_OK
static void _PrPTGAttrComp(_PPTGAttrComp n)
#else
static void _PrPTGAttrComp(n)
	_PPTGAttrComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " _AT");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGAttrComp(CONST char* p1, CONST char* p2)
#else
PTGNode PTGAttrComp(p1, p2)

CONST char* p1;
CONST char* p2;
#endif
{
	_PPTGAttrComp n;
	n = (_PPTGAttrComp)MALLOC(sizeof(struct _SPTGAttrComp));
	n->_print = (_PTGProc)_PrPTGAttrComp;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern NodePtrHeader */

typedef struct _SPTGNodePtrHeader{
	_PTGProc _print;
} * _PPTGNodePtrHeader;

#ifdef PROTO_OK
static void _PrPTGNodePtrHeader(_PPTGNodePtrHeader n)
#else
static void _PrPTGNodePtrHeader(n)
	_PPTGNodePtrHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#ifndef NODEPTR_H\n");
	PTG_OUTPUT_STRING(f, "\n#define NODEPTR_H\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\ntypedef struct NODEPTR_struct *NODEPTR;\n");
	PTG_OUTPUT_STRING(f, "\n#define NULLNODEPTR ((NODEPTR) 0)\n");
	PTG_OUTPUT_STRING(f, "\n#endif\n");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "\n#define DAPTO_RESULTNODEPTR(n) DAPTO_RESULT_PTR(n)\n");
	PTG_OUTPUT_STRING(f, "\n#define DAPTO_ARGNODEPTR(n) DAPTO_ARG_PTR(n, NODEPTR)\n");
	PTG_OUTPUT_STRING(f, "\n#endif\n");
}

static struct _SPTGNodePtrHeader _sptgNodePtrHeader = { (_PTGProc) _PrPTGNodePtrHeader };

#ifdef PROTO_OK
PTGNode PTGNodePtrHeader(void)
#else
PTGNode PTGNodePtrHeader()
#endif
{
	return (PTGNode)(&_sptgNodePtrHeader);
}


/* Implementation of Pattern EncodeFile */

typedef struct _SPTGEncodeFile{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGEncodeFile;

#ifdef PROTO_OK
static void _PrPTGEncodeFile(_PPTGEncodeFile n)
#else
static void _PrPTGEncodeFile(n)
	_PPTGEncodeFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* encoding of tree node types and symbols */\n");
	PTG_OUTPUT_STRING(f, "\n#ifndef NODECODE_H");
	PTG_OUTPUT_STRING(f, "\n#define NODECODE_H\n");
	PTG_OUTPUT_STRING(f, "\nextern int LHSMAP[];\n");
	PTG_OUTPUT_STRING(f, "\n#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGEncodeFile(PTGNode p1)
#else
PTGNode PTGEncodeFile(p1)

PTGNode p1;
#endif
{
	_PPTGEncodeFile n;
	n = (_PPTGEncodeFile)MALLOC(sizeof(struct _SPTGEncodeFile));
	n->_print = (_PTGProc)_PrPTGEncodeFile;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Define */

typedef struct _SPTGDefine{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGDefine;

#ifdef PROTO_OK
static void _PrPTGDefine(_PPTGDefine n)
#else
static void _PrPTGDefine(n)
	_PPTGDefine n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#define ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGDefine(PTGNode p1, PTGNode p2)
#else
PTGNode PTGDefine(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGDefine n;
	n = (_PPTGDefine)MALLOC(sizeof(struct _SPTGDefine));
	n->_print = (_PTGProc)_PrPTGDefine;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern RuleCode */

typedef struct _SPTGRuleCode{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGRuleCode;

#ifdef PROTO_OK
static void _PrPTGRuleCode(_PPTGRuleCode n)
#else
static void _PrPTGRuleCode(n)
	_PPTGRuleCode n;
#endif
{
	PTG_OUTPUT_STRING(f, "RULE");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGRuleCode(PTGNode p1)
#else
PTGNode PTGRuleCode(p1)

PTGNode p1;
#endif
{
	_PPTGRuleCode n;
	n = (_PPTGRuleCode)MALLOC(sizeof(struct _SPTGRuleCode));
	n->_print = (_PTGProc)_PrPTGRuleCode;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SymbCode */

typedef struct _SPTGSymbCode{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSymbCode;

#ifdef PROTO_OK
static void _PrPTGSymbCode(_PPTGSymbCode n)
#else
static void _PrPTGSymbCode(n)
	_PPTGSymbCode n;
#endif
{
	PTG_OUTPUT_STRING(f, "SYMB");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGSymbCode(PTGNode p1)
#else
PTGNode PTGSymbCode(p1)

PTGNode p1;
#endif
{
	_PPTGSymbCode n;
	n = (_PPTGSymbCode)MALLOC(sizeof(struct _SPTGSymbCode));
	n->_print = (_PTGProc)_PrPTGSymbCode;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitMapHead */

typedef struct _SPTGVisitMapHead{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVisitMapHead;

#ifdef PROTO_OK
static void _PrPTGVisitMapHead(_PPTGVisitMapHead n)
#else
static void _PrPTGVisitMapHead(n)
	_PPTGVisitMapHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifndef VISITMAP_H\n");
	PTG_OUTPUT_STRING(f, "#define VISITMAP_H\n\n");
	PTG_OUTPUT_STRING(f, "#include \"nodeptr.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\ntypedef void (* _VPROCPTR) (NODEPTR);");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\ntypedef void (* _VPROCPTR) ();");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n\n#endif\n\n");
}

#ifdef PROTO_OK
PTGNode PTGVisitMapHead(PTGNode p1)
#else
PTGNode PTGVisitMapHead(p1)

PTGNode p1;
#endif
{
	_PPTGVisitMapHead n;
	n = (_PPTGVisitMapHead)MALLOC(sizeof(struct _SPTGVisitMapHead));
	n->_print = (_PTGProc)_PrPTGVisitMapHead;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitMapExtern */

typedef struct _SPTGVisitMapExtern{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVisitMapExtern;

#ifdef PROTO_OK
static void _PrPTGVisitMapExtern(_PPTGVisitMapExtern n)
#else
static void _PrPTGVisitMapExtern(n)
	_PPTGVisitMapExtern n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern _VPROCPTR VS");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "MAP[];");
}

#ifdef PROTO_OK
PTGNode PTGVisitMapExtern(PTGNode p1)
#else
PTGNode PTGVisitMapExtern(p1)

PTGNode p1;
#endif
{
	_PPTGVisitMapExtern n;
	n = (_PPTGVisitMapExtern)MALLOC(sizeof(struct _SPTGVisitMapExtern));
	n->_print = (_PTGProc)_PrPTGVisitMapExtern;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitMapFile */

typedef struct _SPTGVisitMapFile{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVisitMapFile;

#ifdef PROTO_OK
static void _PrPTGVisitMapFile(_PPTGVisitMapFile n)
#else
static void _PrPTGVisitMapFile(n)
	_PPTGVisitMapFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* mapping of RULEcodes to visit procedures */\n");
	PTG_OUTPUT_STRING(f, "\n#include \"visitprocs.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"visitmap.h\"\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGVisitMapFile(PTGNode p1)
#else
PTGNode PTGVisitMapFile(p1)

PTGNode p1;
#endif
{
	_PPTGVisitMapFile n;
	n = (_PPTGVisitMapFile)MALLOC(sizeof(struct _SPTGVisitMapFile));
	n->_print = (_PTGProc)_PrPTGVisitMapFile;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitArray */

typedef struct _SPTGVisitArray{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGVisitArray;

#ifdef PROTO_OK
static void _PrPTGVisitArray(_PPTGVisitArray n)
#else
static void _PrPTGVisitArray(n)
	_PPTGVisitArray n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n_VPROCPTR VS");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "MAP[] = {\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n};");
}

#ifdef PROTO_OK
PTGNode PTGVisitArray(PTGNode p1, PTGNode p2)
#else
PTGNode PTGVisitArray(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGVisitArray n;
	n = (_PPTGVisitArray)MALLOC(sizeof(struct _SPTGVisitArray));
	n->_print = (_PTGProc)_PrPTGVisitArray;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern VisitCast */

typedef struct _SPTGVisitCast{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGVisitCast;

#ifdef PROTO_OK
static void _PrPTGVisitCast(_PPTGVisitCast n)
#else
static void _PrPTGVisitCast(n)
	_PPTGVisitCast n;
#endif
{
	PTG_OUTPUT_STRING(f, "(_VPROCPTR)");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGVisitCast(PTGNode p1)
#else
PTGNode PTGVisitCast(p1)

PTGNode p1;
#endif
{
	_PPTGVisitCast n;
	n = (_PPTGVisitCast)MALLOC(sizeof(struct _SPTGVisitCast));
	n->_print = (_PTGProc)_PrPTGVisitCast;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern LhsArray */

typedef struct _SPTGLhsArray{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGLhsArray;

#ifdef PROTO_OK
static void _PrPTGLhsArray(_PPTGLhsArray n)
#else
static void _PrPTGLhsArray(n)
	_PPTGLhsArray n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* mapping of productions to lefthand side symbols */\n");
	PTG_OUTPUT_STRING(f, "\n#include \"nodecode.h\"\n");
	PTG_OUTPUT_STRING(f, "\nint LHSMAP[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n};\n");
}

#ifdef PROTO_OK
PTGNode PTGLhsArray(PTGNode p1)
#else
PTGNode PTGLhsArray(p1)

PTGNode p1;
#endif
{
	_PPTGLhsArray n;
	n = (_PPTGLhsArray)MALLOC(sizeof(struct _SPTGLhsArray));
	n->_print = (_PTGProc)_PrPTGLhsArray;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeConFileHead */

typedef struct _SPTGTreeConFileHead{
	_PTGProc _print;
} * _PPTGTreeConFileHead;

#ifdef PROTO_OK
static void _PrPTGTreeConFileHead(_PPTGTreeConFileHead n)
#else
static void _PrPTGTreeConFileHead(n)
	_PPTGTreeConFileHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* implementation of tree construction functions */\n");
	PTG_OUTPUT_STRING(f, "\n#include \"node.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"nodecode.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"attrpredef.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"visitmap.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"treeact.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "#include \"attr_mon_dapto.h\"\n");
	PTG_OUTPUT_STRING(f, "#include \"MONTblStack.h\"\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "\n#include <stdlib.h>\n");
	PTG_OUTPUT_STRING(f, "\n#define _USE_OBSTACK 1\n");
	PTG_OUTPUT_STRING(f, "\n/* use of obstack: */\n");
	PTG_OUTPUT_STRING(f, "\n#if _USE_OBSTACK\n");
	PTG_OUTPUT_STRING(f, "\n#include \"obstack.h\"");
	PTG_OUTPUT_STRING(f, "\nstatic struct obstack TreeSpace;");
	PTG_OUTPUT_STRING(f, "\nstatic void *_TreeBase;\n");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\nvoid* NODEPTR_struct::operator new(size_t size)");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n\treturn obstack_alloc(&TreeSpace, size);");
	PTG_OUTPUT_STRING(f, "\n}");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nchar* TreeNodeAlloc(int size)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nchar* TreeNodeAlloc(size) int size;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n	return (char *)(obstack_alloc(&TreeSpace, size));");
	PTG_OUTPUT_STRING(f, "\n}\n#endif\n");
	PTG_OUTPUT_STRING(f, "\nvoid InitTree()");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n	obstack_init(&TreeSpace);");
	PTG_OUTPUT_STRING(f, "\n	_TreeBase=obstack_alloc(&TreeSpace,0);");
	PTG_OUTPUT_STRING(f, "\n}\n");
	PTG_OUTPUT_STRING(f, "\nvoid FreeTree()");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n	obstack_free(&TreeSpace, _TreeBase);");
	PTG_OUTPUT_STRING(f, "\n	_TreeBase=obstack_alloc(&TreeSpace,0);");
	PTG_OUTPUT_STRING(f, "\n}\n");
	PTG_OUTPUT_STRING(f, "\n#else\n");
	PTG_OUTPUT_STRING(f, "\n#include <stdio.h>\n");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\nvoid* NODEPTR_struct::operator new(size_t size)");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n\tvoid *retval = malloc(size);");
	PTG_OUTPUT_STRING(f, "\n\tif (retval) return retval;");
	PTG_OUTPUT_STRING(f, "\n\tfprintf(stderr, \"*** DEADLY: No more memory.\\n\");");
	PTG_OUTPUT_STRING(f, "\n\texit(1);");
	PTG_OUTPUT_STRING(f, "\n}");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nchar* TreeNodeAlloc(int size)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nchar* TreeNodeAlloc(size) int size;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n	char *retval = (char *) malloc(size);");
	PTG_OUTPUT_STRING(f, "\n	if (retval) return retval;");
	PTG_OUTPUT_STRING(f, "\n	fprintf(stderr, \"*** DEADLY: No more memory.\\n\");");
	PTG_OUTPUT_STRING(f, "\n	exit(1);");
	PTG_OUTPUT_STRING(f, "\n}\n#endif\n");
	PTG_OUTPUT_STRING(f, "\nvoid InitTree() { }\n");
	PTG_OUTPUT_STRING(f, "\nvoid FreeTree() { }\n");
	PTG_OUTPUT_STRING(f, "\n#endif\n");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\n#define _SETCOORD(node) \\");
	PTG_OUTPUT_STRING(f, "\n        node->_coord = _coordref ? *_coordref : NoCoord;");
	PTG_OUTPUT_STRING(f, "\n#define _COPYCOORD(node) \\");
	PTG_OUTPUT_STRING(f, "\n        node->_coord = _currn->_desc1->_coord;");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n#define _SETCOORD(node)");
	PTG_OUTPUT_STRING(f, "\n#define _COPYCOORD(node)");
	PTG_OUTPUT_STRING(f, "\n#endif");
}

static struct _SPTGTreeConFileHead _sptgTreeConFileHead = { (_PTGProc) _PrPTGTreeConFileHead };

#ifdef PROTO_OK
PTGNode PTGTreeConFileHead(void)
#else
PTGNode PTGTreeConFileHead()
#endif
{
	return (PTGNode)(&_sptgTreeConFileHead);
}


/* Implementation of Pattern MkSymbFctHead */

typedef struct _SPTGMkSymbFctHead{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkSymbFctHead;

#ifdef PROTO_OK
static void _PrPTGMkSymbFctHead(_PPTGMkSymbFctHead n)
#else
static void _PrPTGMkSymbFctHead(n)
	_PPTGMkSymbFctHead n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref, NODEPTR _currn)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, _currn)");
	PTG_OUTPUT_STRING(f, "\n\tPOSITION *_coordref; NODEPTR _currn;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\nif (_currn == NULLNODEPTR) return NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\nif (IsSymb (_currn, SYMB");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) return (_currn);");
}

#ifdef PROTO_OK
PTGNode PTGMkSymbFctHead(PTGNode p1)
#else
PTGNode PTGMkSymbFctHead(p1)

PTGNode p1;
#endif
{
	_PPTGMkSymbFctHead n;
	n = (_PPTGMkSymbFctHead)MALLOC(sizeof(struct _SPTGMkSymbFctHead));
	n->_print = (_PTGProc)_PrPTGMkSymbFctHead;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkSymbFctChk */

typedef struct _SPTGMkSymbFctChk{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGMkSymbFctChk;

#ifdef PROTO_OK
static void _PrPTGMkSymbFctChk(_PPTGMkSymbFctChk n)
#else
static void _PrPTGMkSymbFctChk(n)
	_PPTGMkSymbFctChk n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nif (IsSymb (_currn, SYMB");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) return (Mk");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "(_coordref, _currn));");
}

#ifdef PROTO_OK
PTGNode PTGMkSymbFctChk(PTGNode p1, PTGNode p2)
#else
PTGNode PTGMkSymbFctChk(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGMkSymbFctChk n;
	n = (_PPTGMkSymbFctChk)MALLOC(sizeof(struct _SPTGMkSymbFctChk));
	n->_print = (_PTGProc)_PrPTGMkSymbFctChk;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MkSymbFctTail */

typedef struct _SPTGMkSymbFctTail{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkSymbFctTail;

#ifdef PROTO_OK
static void _PrPTGMkSymbFctTail(_PPTGMkSymbFctTail n)
#else
static void _PrPTGMkSymbFctTail(n)
	_PPTGMkSymbFctTail n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nreturn(NULLNODEPTR);");
	PTG_OUTPUT_STRING(f, "\n}/* Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " */\n");
}

#ifdef PROTO_OK
PTGNode PTGMkSymbFctTail(PTGNode p1)
#else
PTGNode PTGMkSymbFctTail(p1)

PTGNode p1;
#endif
{
	_PPTGMkSymbFctTail n;
	n = (_PPTGMkSymbFctTail)MALLOC(sizeof(struct _SPTGMkSymbFctTail));
	n->_print = (_PTGProc)_PrPTGMkSymbFctTail;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkTermFct */

typedef struct _SPTGMkTermFct{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGMkTermFct;

#ifdef PROTO_OK
static void _PrPTGMkTermFct(_PPTGMkTermFct n)
#else
static void _PrPTGMkTermFct(n)
	_PPTGMkTermFct n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR TMk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(NODEPTR _currn)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR TMk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_currn)");
	PTG_OUTPUT_STRING(f, "\n\tNODEPTR _currn;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\nif (IsSymb (_currn, SYMB");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) return (_currn);");
	PTG_OUTPUT_STRING(f, "\nreturn(NULLNODEPTR);");
	PTG_OUTPUT_STRING(f, "\n}/* TMk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " */\n");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(POSITION *_coordref, int attrval )");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_coordref, attrval)");
	PTG_OUTPUT_STRING(f, "\n\tPOSITION *_coordref;\n\tint attrval;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{\n");
	PTG_OUTPUT_STRING(f, "\t_TSP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " _currn;");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\n_currn = new _TS");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n_currn = (_TSP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") TreeNodeAlloc (sizeof (struct _TS");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n_currn->_prod = RULE");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\nreturn ((NODEPTR) _currn);\n}/* Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "*/\n");
}

#ifdef PROTO_OK
PTGNode PTGMkTermFct(PTGNode p1, PTGNode p2)
#else
PTGNode PTGMkTermFct(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGMkTermFct n;
	n = (_PPTGMkTermFct)MALLOC(sizeof(struct _SPTGMkTermFct));
	n->_print = (_PTGProc)_PrPTGMkTermFct;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ParmSpec */

typedef struct _SPTGParmSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGParmSpec;

#ifdef PROTO_OK
static void _PrPTGParmSpec(_PPTGParmSpec n)
#else
static void _PrPTGParmSpec(n)
	_PPTGParmSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGParmSpec(PTGNode p1, PTGNode p2)
#else
PTGNode PTGParmSpec(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGParmSpec n;
	n = (_PPTGParmSpec)MALLOC(sizeof(struct _SPTGParmSpec));
	n->_print = (_PTGProc)_PrPTGParmSpec;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ProtoSpec */

typedef struct _SPTGProtoSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGProtoSpec;

#ifdef PROTO_OK
static void _PrPTGProtoSpec(_PPTGProtoSpec n)
#else
static void _PrPTGProtoSpec(n)
	_PPTGProtoSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, ", ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGProtoSpec(PTGNode p1, PTGNode p2)
#else
PTGNode PTGProtoSpec(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGProtoSpec n;
	n = (_PPTGProtoSpec)MALLOC(sizeof(struct _SPTGProtoSpec));
	n->_print = (_PTGProc)_PrPTGProtoSpec;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern AttrAssign */

typedef struct _SPTGAttrAssign{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAttrAssign;

#ifdef PROTO_OK
static void _PrPTGAttrAssign(_PPTGAttrAssign n)
#else
static void _PrPTGAttrAssign(n)
	_PPTGAttrAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n_currn->_AT");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = attrval;");
}

#ifdef PROTO_OK
PTGNode PTGAttrAssign(PTGNode p1)
#else
PTGNode PTGAttrAssign(p1)

PTGNode p1;
#endif
{
	_PPTGAttrAssign n;
	n = (_PPTGAttrAssign)MALLOC(sizeof(struct _SPTGAttrAssign));
	n->_print = (_PTGProc)_PrPTGAttrAssign;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkProdFct */

typedef struct _SPTGMkProdFct{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
} * _PPTGMkProdFct;

#ifdef PROTO_OK
static void _PrPTGMkProdFct(_PPTGMkProdFct n)
#else
static void _PrPTGMkProdFct(n)
	_PPTGMkProdFct n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n\tPOSITION *_coordref;");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{\t_TPP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " _currn;");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\n_currn = new _TP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n_currn = (_TPP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") TreeNodeAlloc (sizeof (struct _TP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\n_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n_currn->_prod = RULE");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	n->p4->_print(n->p4);
	n->p7->_print(n->p7);
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "\nreturn ( (NODEPTR) _currn);\n}/* Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " */\n");
}

#ifdef PROTO_OK
PTGNode PTGMkProdFct(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7)
#else
PTGNode PTGMkProdFct(p1, p2, p3, p4, p5, p6, p7)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
#endif
{
	_PPTGMkProdFct n;
	n = (_PPTGMkProdFct)MALLOC(sizeof(struct _SPTGMkProdFct));
	n->_print = (_PTGProc)_PrPTGMkProdFct;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermAct */

typedef struct _SPTGNonLitTermAct{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGNonLitTermAct;

#ifdef PROTO_OK
static void _PrPTGNonLitTermAct(_PPTGNonLitTermAct n)
#else
static void _PrPTGNonLitTermAct(n)
	_PPTGNonLitTermAct n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n_TERMACT_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermAct(PTGNode p1)
#else
PTGNode PTGNonLitTermAct(p1)

PTGNode p1;
#endif
{
	_PPTGNonLitTermAct n;
	n = (_PPTGNonLitTermAct)MALLOC(sizeof(struct _SPTGNonLitTermAct));
	n->_print = (_PTGProc)_PrPTGNonLitTermAct;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermDefine */

typedef struct _SPTGNonLitTermDefine{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGNonLitTermDefine;

#ifdef PROTO_OK
static void _PrPTGNonLitTermDefine(_PPTGNonLitTermDefine n)
#else
static void _PrPTGNonLitTermDefine(n)
	_PPTGNonLitTermDefine n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#define Mk");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "(pos,val) (val)");
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermDefine(CONST char* p1)
#else
PTGNode PTGNonLitTermDefine(p1)

CONST char* p1;
#endif
{
	_PPTGNonLitTermDefine n;
	n = (_PPTGNonLitTermDefine)MALLOC(sizeof(struct _SPTGNonLitTermDefine));
	n->_print = (_PTGProc)_PrPTGNonLitTermDefine;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern OldTermDefine */

typedef struct _SPTGOldTermDefine{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGOldTermDefine;

#ifdef PROTO_OK
static void _PrPTGOldTermDefine(_PPTGOldTermDefine n)
#else
static void _PrPTGOldTermDefine(n)
	_PPTGOldTermDefine n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#define Mk");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "(pos,val) Mk_RNT_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "(pos,val)");
}

#ifdef PROTO_OK
PTGNode PTGOldTermDefine(CONST char* p1)
#else
PTGNode PTGOldTermDefine(p1)

CONST char* p1;
#endif
{
	_PPTGOldTermDefine n;
	n = (_PPTGOldTermDefine)MALLOC(sizeof(struct _SPTGOldTermDefine));
	n->_print = (_PTGProc)_PrPTGOldTermDefine;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermProto */

typedef struct _SPTGNonLitTermProto{
	_PTGProc _print;
	CONST char* p1;
	int p2;
} * _PPTGNonLitTermProto;

#ifdef PROTO_OK
static void _PrPTGNonLitTermProto(_PPTGNonLitTermProto n)
#else
static void _PrPTGNonLitTermProto(n)
	_PPTGNonLitTermProto n;
#endif
{
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " _TERM");
	PTG_OUTPUT_INT(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermProto(CONST char* p1, int p2)
#else
PTGNode PTGNonLitTermProto(p1, p2)

CONST char* p1;
int p2;
#endif
{
	_PPTGNonLitTermProto n;
	n = (_PPTGNonLitTermProto)MALLOC(sizeof(struct _SPTGNonLitTermProto));
	n->_print = (_PTGProc)_PrPTGNonLitTermProto;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermName */

typedef struct _SPTGNonLitTermName{
	_PTGProc _print;
	int p1;
} * _PPTGNonLitTermName;

#ifdef PROTO_OK
static void _PrPTGNonLitTermName(_PPTGNonLitTermName n)
#else
static void _PrPTGNonLitTermName(n)
	_PPTGNonLitTermName n;
#endif
{
	PTG_OUTPUT_STRING(f, ", _TERM");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermName(int p1)
#else
PTGNode PTGNonLitTermName(p1)

int p1;
#endif
{
	_PPTGNonLitTermName n;
	n = (_PPTGNonLitTermName)MALLOC(sizeof(struct _SPTGNonLitTermName));
	n->_print = (_PTGProc)_PrPTGNonLitTermName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern NonLitTermSpec */

typedef struct _SPTGNonLitTermSpec{
	_PTGProc _print;
	CONST char* p1;
	int p2;
} * _PPTGNonLitTermSpec;

#ifdef PROTO_OK
static void _PrPTGNonLitTermSpec(_PPTGNonLitTermSpec n)
#else
static void _PrPTGNonLitTermSpec(n)
	_PPTGNonLitTermSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n\t");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " _TERM");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGNonLitTermSpec(CONST char* p1, int p2)
#else
PTGNode PTGNonLitTermSpec(p1, p2)

CONST char* p1;
int p2;
#endif
{
	_PPTGNonLitTermSpec n;
	n = (_PPTGNonLitTermSpec)MALLOC(sizeof(struct _SPTGNonLitTermSpec));
	n->_print = (_PTGProc)_PrPTGNonLitTermSpec;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeConVisit */

typedef struct _SPTGTreeConVisit{
	_PTGProc _print;
} * _PPTGTreeConVisit;

#ifdef PROTO_OK
static void _PrPTGTreeConVisit(_PPTGTreeConVisit n)
#else
static void _PrPTGTreeConVisit(n)
	_PPTGTreeConVisit n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */");
}

static struct _SPTGTreeConVisit _sptgTreeConVisit = { (_PTGProc) _PrPTGTreeConVisit };

#ifdef PROTO_OK
PTGNode PTGTreeConVisit(void)
#else
PTGNode PTGTreeConVisit()
#endif
{
	return (PTGNode)(&_sptgTreeConVisit);
}


/* Implementation of Pattern MkTreeParmSpec */

typedef struct _SPTGMkTreeParmSpec{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkTreeParmSpec;

#ifdef PROTO_OK
static void _PrPTGMkTreeParmSpec(_PPTGMkTreeParmSpec n)
#else
static void _PrPTGMkTreeParmSpec(n)
	_PPTGMkTreeParmSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n\tNODEPTR ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGMkTreeParmSpec(PTGNode p1)
#else
PTGNode PTGMkTreeParmSpec(p1)

PTGNode p1;
#endif
{
	_PPTGMkTreeParmSpec n;
	n = (_PPTGMkTreeParmSpec)MALLOC(sizeof(struct _SPTGMkTreeParmSpec));
	n->_print = (_PTGProc)_PrPTGMkTreeParmSpec;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkProtoSpec */

typedef struct _SPTGMkProtoSpec{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkProtoSpec;

#ifdef PROTO_OK
static void _PrPTGMkProtoSpec(_PPTGMkProtoSpec n)
#else
static void _PrPTGMkProtoSpec(n)
	_PPTGMkProtoSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, ", NODEPTR ");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGMkProtoSpec(PTGNode p1)
#else
PTGNode PTGMkProtoSpec(p1)

PTGNode p1;
#endif
{
	_PPTGMkProtoSpec n;
	n = (_PPTGMkProtoSpec)MALLOC(sizeof(struct _SPTGMkProtoSpec));
	n->_print = (_PTGProc)_PrPTGMkProtoSpec;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeAssign */

typedef struct _SPTGTreeAssign{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	CONST char* p3;
	int p4;
} * _PPTGTreeAssign;

#ifdef PROTO_OK
static void _PrPTGTreeAssign(_PPTGTreeAssign n)
#else
static void _PrPTGTreeAssign(n)
	_PPTGTreeAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n_currn->");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = (_TSP");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ") Mk");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, " (_coordref, ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ");	\nif (((NODEPTR)_currn->");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") == NULLNODEPTR)	\n\tmessage (DEADLY, \"RULE ");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, ": root of subtree no. ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, " can not be made a ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, " node \", 0, _coordref);");
}

#ifdef PROTO_OK
PTGNode PTGTreeAssign(PTGNode p1, CONST char* p2, CONST char* p3, int p4)
#else
PTGNode PTGTreeAssign(p1, p2, p3, p4)

PTGNode p1;
CONST char* p2;
CONST char* p3;
int p4;
#endif
{
	_PPTGTreeAssign n;
	n = (_PPTGTreeAssign)MALLOC(sizeof(struct _SPTGTreeAssign));
	n->_print = (_PTGProc)_PrPTGTreeAssign;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern GenTreeAssign */

typedef struct _SPTGGenTreeAssign{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
} * _PPTGGenTreeAssign;

#ifdef PROTO_OK
static void _PrPTGGenTreeAssign(_PPTGGenTreeAssign n)
#else
static void _PrPTGGenTreeAssign(n)
	_PPTGGenTreeAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nif (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " == NULLNODEPTR)");
	PTG_OUTPUT_STRING(f, "\n\t_currn->");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = (_TSP");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ") NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\nelse\t_currn->");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = (_TSP");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, ") Mk");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, " (_coordref, ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ");");
}

#ifdef PROTO_OK
PTGNode PTGGenTreeAssign(PTGNode p1, CONST char* p2)
#else
PTGNode PTGGenTreeAssign(p1, p2)

PTGNode p1;
CONST char* p2;
#endif
{
	_PPTGGenTreeAssign n;
	n = (_PPTGGenTreeAssign)MALLOC(sizeof(struct _SPTGGenTreeAssign));
	n->_print = (_PTGProc)_PrPTGGenTreeAssign;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern TreeConHeader */

typedef struct _SPTGTreeConHeader{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGTreeConHeader;

#ifdef PROTO_OK
static void _PrPTGTreeConHeader(_PPTGTreeConHeader n)
#else
static void _PrPTGTreeConHeader(n)
	_PPTGTreeConHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* interface of tree construction functions */\n");
	PTG_OUTPUT_STRING(f, "\n#ifndef TREECON_H");
	PTG_OUTPUT_STRING(f, "\n#define TREECON_H");
	PTG_OUTPUT_STRING(f, "\n#include \"eliproto.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"err.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"nodeptr.h\"\n");
	PTG_OUTPUT_STRING(f, "\n#include \"HEAD.h\"\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\nextern void InitTree ELI_ARG((void));");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\nextern void FreeTree ELI_ARG((void));");
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGTreeConHeader(PTGNode p1)
#else
PTGNode PTGTreeConHeader(p1)

PTGNode p1;
#endif
{
	_PPTGTreeConHeader n;
	n = (_PPTGTreeConHeader)MALLOC(sizeof(struct _SPTGTreeConHeader));
	n->_print = (_PTGProc)_PrPTGTreeConHeader;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkSymbHeader */

typedef struct _SPTGMkSymbHeader{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkSymbHeader;

#ifdef PROTO_OK
static void _PrPTGMkSymbHeader(_PPTGMkSymbHeader n)
#else
static void _PrPTGMkSymbHeader(n)
	_PPTGMkSymbHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((POSITION *_coordref, NODEPTR _currn));");
}

#ifdef PROTO_OK
PTGNode PTGMkSymbHeader(PTGNode p1)
#else
PTGNode PTGMkSymbHeader(p1)

PTGNode p1;
#endif
{
	_PPTGMkSymbHeader n;
	n = (_PPTGMkSymbHeader)MALLOC(sizeof(struct _SPTGMkSymbHeader));
	n->_print = (_PTGProc)_PrPTGMkSymbHeader;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MkProcHeader */

typedef struct _SPTGMkProcHeader{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGMkProcHeader;

#ifdef PROTO_OK
static void _PrPTGMkProcHeader(_PPTGMkProcHeader n)
#else
static void _PrPTGMkProcHeader(n)
	_PPTGMkProcHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((POSITION *_coordref");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "));");
}

#ifdef PROTO_OK
PTGNode PTGMkProcHeader(PTGNode p1, PTGNode p2)
#else
PTGNode PTGMkProcHeader(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGMkProcHeader n;
	n = (_PPTGMkProcHeader)MALLOC(sizeof(struct _SPTGMkProcHeader));
	n->_print = (_PTGProc)_PrPTGMkProcHeader;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MkTermProcHeader */

typedef struct _SPTGMkTermProcHeader{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMkTermProcHeader;

#ifdef PROTO_OK
static void _PrPTGMkTermProcHeader(_PPTGMkTermProcHeader n)
#else
static void _PrPTGMkTermProcHeader(n)
	_PPTGMkTermProcHeader n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR TMk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((NODEPTR _currn));");
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((POSITION *_coordref, int attrval));");
}

#ifdef PROTO_OK
PTGNode PTGMkTermProcHeader(PTGNode p1)
#else
PTGNode PTGMkTermProcHeader(p1)

PTGNode p1;
#endif
{
	_PPTGMkTermProcHeader n;
	n = (_PPTGMkTermProcHeader)MALLOC(sizeof(struct _SPTGMkTermProcHeader));
	n->_print = (_PTGProc)_PrPTGMkTermProcHeader;
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


/* Implementation of Pattern ListStruct */

typedef struct _SPTGListStruct{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGListStruct;

#ifdef PROTO_OK
static void _PrPTGListStruct(_PPTGListStruct n)
#else
static void _PrPTGListStruct(n)
	_PPTGListStruct n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nstruct _TP0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " {\nint _prod;");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\nNODEPTR _desc1;\nNODEPTR _desc2;\n};\n");
}

#ifdef PROTO_OK
PTGNode PTGListStruct(PTGNode p1, PTGNode p2)
#else
PTGNode PTGListStruct(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGListStruct n;
	n = (_PPTGListStruct)MALLOC(sizeof(struct _SPTGListStruct));
	n->_print = (_PTGProc)_PrPTGListStruct;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ListFunctsHdr */

typedef struct _SPTGListFunctsHdr{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGListFunctsHdr;

#ifdef PROTO_OK
static void _PrPTGListFunctsHdr(_PPTGListFunctsHdr n)
#else
static void _PrPTGListFunctsHdr(n)
	_PPTGListFunctsHdr n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#define Mk0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_coordref) NULLNODEPTR");
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR Mk2");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((POSITION *_coordref, NODEPTR l, NODEPTR r));");
	PTG_OUTPUT_STRING(f, "\nextern NODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((POSITION *_coordref, NODEPTR t));");
}

#ifdef PROTO_OK
PTGNode PTGListFunctsHdr(PTGNode p1)
#else
PTGNode PTGListFunctsHdr(p1)

PTGNode p1;
#endif
{
	_PPTGListFunctsHdr n;
	n = (_PPTGListFunctsHdr)MALLOC(sizeof(struct _SPTGListFunctsHdr));
	n->_print = (_PTGProc)_PrPTGListFunctsHdr;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ListElemFct */

typedef struct _SPTGListElemFct{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGListElemFct;

#ifdef PROTO_OK
static void _PrPTGListElemFct(_PPTGListElemFct n)
#else
static void _PrPTGListElemFct(n)
	_PPTGListElemFct n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nstatic NODEPTR _Mk");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref, NODEPTR elem)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nstatic NODEPTR _Mk");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " (_coordref, elem)");
	PTG_OUTPUT_STRING(f, "\n\tPOSITION *_coordref; NODEPTR elem;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{");
	PTG_OUTPUT_STRING(f, "\n\t_TPPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " _new;");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\n\t_new = new _TPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\n\t_new = (_TPPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ") TreeNodeAlloc (sizeof (struct _TPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\n_new->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_new));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n\t_new->_prod = RULELST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n\t_new->_desc1 = (_TSP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")elem;");
	PTG_OUTPUT_STRING(f, "\n\t_new->_desc2 = (_TSPLST_");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ")_new;");
	PTG_OUTPUT_STRING(f, "\n\t{_TPPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " _currn = _new;");
	PTG_OUTPUT_STRING(f, "\n\t _SETCOORD(_currn)");
	PTG_OUTPUT_STRING(f, "\n\t _TERMACT_LST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n\t}");
	PTG_OUTPUT_STRING(f, "\n\treturn (NODEPTR)_new;");
	PTG_OUTPUT_STRING(f, "\n}\n");
}

#ifdef PROTO_OK
PTGNode PTGListElemFct(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGListElemFct(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGListElemFct n;
	n = (_PPTGListElemFct)MALLOC(sizeof(struct _SPTGListElemFct));
	n->_print = (_PTGProc)_PrPTGListElemFct;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern ListElemChk */

typedef struct _SPTGListElemChk{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGListElemChk;

#ifdef PROTO_OK
static void _PrPTGListElemChk(_PPTGListElemChk n)
#else
static void _PrPTGListElemChk(n)
	_PPTGListElemChk n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n\tif (IsSymb (t, SYMB");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")) ");
	PTG_OUTPUT_STRING(f, "\n\t\treturn _Mk");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " (_coordref, Mk");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " (_coordref, t));");
}

#ifdef PROTO_OK
PTGNode PTGListElemChk(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGListElemChk(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGListElemChk n;
	n = (_PPTGListElemChk)MALLOC(sizeof(struct _SPTGListElemChk));
	n->_print = (_PTGProc)_PrPTGListElemChk;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern ListFuncts */

typedef struct _SPTGListFuncts{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGListFuncts;

#ifdef PROTO_OK
static void _PrPTGListFuncts(_PPTGListFuncts n)
#else
static void _PrPTGListFuncts(n)
	_PPTGListFuncts n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nstatic NODEPTR _Elem");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref, NODEPTR t)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nstatic NODEPTR _Elem");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, t)");
	PTG_OUTPUT_STRING(f, "\n\tPOSITION *_coordref; NODEPTR t;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n/* coerces t to a list element and returns a single circular list */");
	PTG_OUTPUT_STRING(f, "\n{\tNODEPTR elem;");
	PTG_OUTPUT_STRING(f, "\n\t/* check first without then with coercion: */");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n\tmessage (DEADLY, \"a ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " list element node can not be generated \",");
	PTG_OUTPUT_STRING(f, "\n\t\t0, _coordref);");
	PTG_OUTPUT_STRING(f, "\n\treturn t; /* never reached */");
	PTG_OUTPUT_STRING(f, "\n}\n");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk2");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref, NODEPTR l, NODEPTR r)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk2");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, l, r) POSITION *_coordref; NODEPTR l, r;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n/* make a list of l and r, which may be null, elements, or lists */");
	PTG_OUTPUT_STRING(f, "\n{\tNODEPTR last;");
	PTG_OUTPUT_STRING(f, "\nif (l == NULLNODEPTR) return r;");
	PTG_OUTPUT_STRING(f, "\nif (r == NULLNODEPTR) return l;");
	PTG_OUTPUT_STRING(f, "\n/* ensure l and r to be lists: */");
	PTG_OUTPUT_STRING(f, "\nif (LHSMAP[l->_prod] != SYMBLST_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n\tl =_Elem");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, l);");
	PTG_OUTPUT_STRING(f, "\nif (LHSMAP[r->_prod] != SYMBLST_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n\tr = _Elem");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, r);");
	PTG_OUTPUT_STRING(f, "\n/* concatenate two lists: */");
	PTG_OUTPUT_STRING(f, "\nlast = ((NODEPTR)((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")r)->_desc2);");
	PTG_OUTPUT_STRING(f, "\n((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")r)->_desc2 = ((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")l)->_desc2;");
	PTG_OUTPUT_STRING(f, "\n((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")l)->_desc2 = last;");
	PTG_OUTPUT_STRING(f, "\nreturn l;");
	PTG_OUTPUT_STRING(f, "\n}\n");
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (POSITION *_coordref, NODEPTR t)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR Mk");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, t)");
	PTG_OUTPUT_STRING(f, " POSITION *_coordref; NODEPTR t;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{\tNODEPTR _currn; _TPP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " root;");
	PTG_OUTPUT_STRING(f, "\n\t_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " list, remain, p;");
	PTG_OUTPUT_STRING(f, "\n/* argument t may be empty, a list element, or a list: */");
	PTG_OUTPUT_STRING(f, "\nif (t == NULLNODEPTR)");
	PTG_OUTPUT_STRING(f, "\n\tremain = (_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\nelse {\tif (LHSMAP[t->_prod] != SYMBLST_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n\t\tt = _Elem");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (_coordref, t);");
	PTG_OUTPUT_STRING(f, "\n\tremain = (_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")(((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") t)->_desc2);");
	PTG_OUTPUT_STRING(f, "\n\t((_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") t)->_desc2 = NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\n}");
	PTG_OUTPUT_STRING(f, "\n/* remain is a possibly empty list in reverse order */");
	PTG_OUTPUT_STRING(f, "\n/* finalize the list by an empty context: */");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\nlist = new _TPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nlist = (_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") TreeNodeAlloc (sizeof (struct _TPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\nlist->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)list));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\nlist->_prod = RULELST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\nlist->_desc1 = NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\nlist->_desc2 = NULLNODEPTR;");
	PTG_OUTPUT_STRING(f, "\n_SETCOORD(list)");
	PTG_OUTPUT_STRING(f, "\n_currn = (NODEPTR)list;");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n/* reverse the list and visit its nodes: */");
	PTG_OUTPUT_STRING(f, "\nwhile (remain) {");
	PTG_OUTPUT_STRING(f, "\n\tp = (_TPPLST_0");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")(remain->_desc2);");
	PTG_OUTPUT_STRING(f, "\n\tremain->_desc2 = (NODEPTR)list;");
	PTG_OUTPUT_STRING(f, "\n\tlist = remain;");
	PTG_OUTPUT_STRING(f, "\n\tremain = p;");
	PTG_OUTPUT_STRING(f, "\n\t_currn = (NODEPTR)list;");
	n->p5->_print(n->p5);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n}");
	PTG_OUTPUT_STRING(f, "\n/* make root node and visit it: */");
	PTG_OUTPUT_STRING(f, "\n#ifdef __cplusplus");
	PTG_OUTPUT_STRING(f, "\nroot = new _TP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nroot = (_TPP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ") TreeNodeAlloc (sizeof (struct _TP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR");
	PTG_OUTPUT_STRING(f, "\nroot->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)root));");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\nroot->_prod = RULE");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\nroot->_desc1 = (_TSPLST_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")list;");
	PTG_OUTPUT_STRING(f, "\n{ _TPP");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " _currn = root;");
	PTG_OUTPUT_STRING(f, "\n  _SETCOORD(_currn)");
	PTG_OUTPUT_STRING(f, "\n  _TERMACT_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n}");
	PTG_OUTPUT_STRING(f, "\n_currn = (NODEPTR)root;");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\nreturn (NODEPTR)_currn;");
	PTG_OUTPUT_STRING(f, "\n}\n");
}

#ifdef PROTO_OK
PTGNode PTGListFuncts(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGListFuncts(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGListFuncts n;
	n = (_PPTGListFuncts)MALLOC(sizeof(struct _SPTGListFuncts));
	n->_print = (_PTGProc)_PrPTGListFuncts;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern ListTermact */

typedef struct _SPTGListTermact{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGListTermact;

#ifdef PROTO_OK
static void _PrPTGListTermact(_PPTGListTermact n)
#else
static void _PrPTGListTermact(n)
	_PPTGListTermact n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n\t/*if (_currn->_prod == RULELST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")");
	PTG_OUTPUT_STRING(f, "\n\t{_TPPLST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " _currn = _currn;");
	PTG_OUTPUT_STRING(f, "\n\t _TERMACT_LST_");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ";");
	PTG_OUTPUT_STRING(f, "\n\t} this code has been moved to _Elem");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "*/");
}

#ifdef PROTO_OK
PTGNode PTGListTermact(PTGNode p1, PTGNode p2)
#else
PTGNode PTGListTermact(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGListTermact n;
	n = (_PPTGListTermact)MALLOC(sizeof(struct _SPTGListTermact));
	n->_print = (_PTGProc)_PrPTGListTermact;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonAprods */

typedef struct _SPTGMonAprods{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGMonAprods;

#ifdef PROTO_OK
static void _PrPTGMonAprods(_PPTGMonAprods n)
#else
static void _PrPTGMonAprods(n)
	_PPTGMonAprods n;
#endif
{
	PTG_OUTPUT_STRING(f, "/* implementation of monitoring support for attribution */\n\n");
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n\n");
	PTG_OUTPUT_STRING(f, "#include \"node.h\"\n");
	PTG_OUTPUT_STRING(f, "#include \"treecon.h\"\n");
	PTG_OUTPUT_STRING(f, "#include\"nodecode.h\"\n");
	PTG_OUTPUT_STRING(f, "#include\"eliproto.h\"\n");
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "/* To avoid messages about empty files */\n");
	PTG_OUTPUT_STRING(f, "static int _dapto;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonAprods(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGMonAprods(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGMonAprods n;
	n = (_PPTGMonAprods)MALLOC(sizeof(struct _SPTGMonAprods));
	n->_print = (_PTGProc)_PrPTGMonAprods;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern AbsProds */

typedef struct _SPTGAbsProds{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAbsProds;

#ifdef PROTO_OK
static void _PrPTGAbsProds(_PPTGAbsProds n)
#else
static void _PrPTGAbsProds(n)
	_PPTGAbsProds n;
#endif
{
	PTG_OUTPUT_STRING(f, "CONST char *abs_prods[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "  (char *) 0\n");
	PTG_OUTPUT_STRING(f, "};\n\n");
}

#ifdef PROTO_OK
PTGNode PTGAbsProds(PTGNode p1)
#else
PTGNode PTGAbsProds(p1)

PTGNode p1;
#endif
{
	_PPTGAbsProds n;
	n = (_PPTGAbsProds)MALLOC(sizeof(struct _SPTGAbsProds));
	n->_print = (_PTGProc)_PrPTGAbsProds;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Prods */

typedef struct _SPTGProds{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
	PTGNode p3;
} * _PPTGProds;

#ifdef PROTO_OK
static void _PrPTGProds(_PPTGProds n)
#else
static void _PrPTGProds(n)
	_PPTGProds n;
#endif
{
	PTG_OUTPUT_STRING(f, "  \"{");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "} {");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "} {");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "}\",\n");
}

#ifdef PROTO_OK
PTGNode PTGProds(CONST char* p1, CONST char* p2, PTGNode p3)
#else
PTGNode PTGProds(p1, p2, p3)

CONST char* p1;
CONST char* p2;
PTGNode p3;
#endif
{
	_PPTGProds n;
	n = (_PPTGProds)MALLOC(sizeof(struct _SPTGProds));
	n->_print = (_PTGProc)_PrPTGProds;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern AbsNchild */

typedef struct _SPTGAbsNchild{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAbsNchild;

#ifdef PROTO_OK
static void _PrPTGAbsNchild(_PPTGAbsNchild n)
#else
static void _PrPTGAbsNchild(n)
	_PPTGAbsNchild n;
#endif
{
	PTG_OUTPUT_STRING(f, "int abs_nchild[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "};\n\n");
}

#ifdef PROTO_OK
PTGNode PTGAbsNchild(PTGNode p1)
#else
PTGNode PTGAbsNchild(p1)

PTGNode p1;
#endif
{
	_PPTGAbsNchild n;
	n = (_PPTGAbsNchild)MALLOC(sizeof(struct _SPTGAbsNchild));
	n->_print = (_PTGProc)_PrPTGAbsNchild;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Nchild */

typedef struct _SPTGNchild{
	_PTGProc _print;
	int p1;
} * _PPTGNchild;

#ifdef PROTO_OK
static void _PrPTGNchild(_PPTGNchild n)
#else
static void _PrPTGNchild(n)
	_PPTGNchild n;
#endif
{
	PTG_OUTPUT_STRING(f, "  ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ",\n");
}

#ifdef PROTO_OK
PTGNode PTGNchild(int p1)
#else
PTGNode PTGNchild(p1)

int p1;
#endif
{
	_PPTGNchild n;
	n = (_PPTGNchild)MALLOC(sizeof(struct _SPTGNchild));
	n->_print = (_PTGProc)_PrPTGNchild;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AbsChild */

typedef struct _SPTGAbsChild{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGAbsChild;

#ifdef PROTO_OK
static void _PrPTGAbsChild(_PPTGAbsChild n)
#else
static void _PrPTGAbsChild(n)
	_PPTGAbsChild n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#if defined(__STDC__) || defined(__cplusplus)");
	PTG_OUTPUT_STRING(f, "\nNODEPTR abs_child (NODEPTR n, int c)");
	PTG_OUTPUT_STRING(f, "\n#else");
	PTG_OUTPUT_STRING(f, "\nNODEPTR abs_child (n, c)\n");
	PTG_OUTPUT_STRING(f, "  NODEPTR n;\n");
	PTG_OUTPUT_STRING(f, "  int c;");
	PTG_OUTPUT_STRING(f, "\n#endif");
	PTG_OUTPUT_STRING(f, "\n{\n");
	PTG_OUTPUT_STRING(f, "  switch (n->_prod) {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "    default:\n");
	PTG_OUTPUT_STRING(f, "        return (NODEPTR) 0;\n");
	PTG_OUTPUT_STRING(f, "  }\n");
	PTG_OUTPUT_STRING(f, "}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGAbsChild(PTGNode p1)
#else
PTGNode PTGAbsChild(p1)

PTGNode p1;
#endif
{
	_PPTGAbsChild n;
	n = (_PPTGAbsChild)MALLOC(sizeof(struct _SPTGAbsChild));
	n->_print = (_PTGProc)_PrPTGAbsChild;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Child */

typedef struct _SPTGChild{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGChild;

#ifdef PROTO_OK
static void _PrPTGChild(_PPTGChild n)
#else
static void _PrPTGChild(n)
	_PPTGChild n;
#endif
{
	PTG_OUTPUT_STRING(f, "    case RULE");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ": {\n");
	PTG_OUTPUT_STRING(f, "      _TPP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " m = (_TPP");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ") n;\n");
	PTG_OUTPUT_STRING(f, "      switch (c) {\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "        default:\n");
	PTG_OUTPUT_STRING(f, "          return (NODEPTR) 0;\n");
	PTG_OUTPUT_STRING(f, "      }\n");
	PTG_OUTPUT_STRING(f, "      break;\n");
	PTG_OUTPUT_STRING(f, "    }\n");
}

#ifdef PROTO_OK
PTGNode PTGChild(CONST char* p1, PTGNode p2)
#else
PTGNode PTGChild(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGChild n;
	n = (_PPTGChild)MALLOC(sizeof(struct _SPTGChild));
	n->_print = (_PTGProc)_PrPTGChild;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Desc */

typedef struct _SPTGDesc{
	_PTGProc _print;
	int p1;
} * _PPTGDesc;

#ifdef PROTO_OK
static void _PrPTGDesc(_PPTGDesc n)
#else
static void _PrPTGDesc(n)
	_PPTGDesc n;
#endif
{
	PTG_OUTPUT_STRING(f, "        case ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ": return (NODEPTR) m->_desc");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "; break;\n");
}

#ifdef PROTO_OK
PTGNode PTGDesc(int p1)
#else
PTGNode PTGDesc(p1)

int p1;
#endif
{
	_PPTGDesc n;
	n = (_PPTGDesc)MALLOC(sizeof(struct _SPTGDesc));
	n->_print = (_PTGProc)_PrPTGDesc;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Sseq */

typedef struct _SPTGSseq{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
} * _PPTGSseq;

#ifdef PROTO_OK
static void _PrPTGSseq(_PPTGSseq n)
#else
static void _PrPTGSseq(n)
	_PPTGSseq n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_STRING(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGSseq(PTGNode p1, CONST char* p2)
#else
PTGNode PTGSseq(p1, p2)

PTGNode p1;
CONST char* p2;
#endif
{
	_PPTGSseq n;
	n = (_PPTGSseq)MALLOC(sizeof(struct _SPTGSseq));
	n->_print = (_PTGProc)_PrPTGSseq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Lseq */

typedef struct _SPTGLseq{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
} * _PPTGLseq;

#ifdef PROTO_OK
static void _PrPTGLseq(_PPTGLseq n)
#else
static void _PrPTGLseq(n)
	_PPTGLseq n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " '");
	C_outstr_noquotes(f, n->p2);
	PTG_OUTPUT_STRING(f, "'");
}

#ifdef PROTO_OK
PTGNode PTGLseq(PTGNode p1, CONST char* p2)
#else
PTGNode PTGLseq(p1, p2)

PTGNode p1;
CONST char* p2;
#endif
{
	_PPTGLseq n;
	n = (_PPTGLseq)MALLOC(sizeof(struct _SPTGLseq));
	n->_print = (_PTGProc)_PrPTGLseq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonAttrFile */

typedef struct _SPTGMonAttrFile{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGMonAttrFile;

#ifdef PROTO_OK
static void _PrPTGMonAttrFile(_PPTGMonAttrFile n)
#else
static void _PrPTGMonAttrFile(n)
	_PPTGMonAttrFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "aspect attribution;\n");
	PTG_OUTPUT_STRING(f, "/* implementation of attribute monitoring */\n\n");
	PTG_OUTPUT_STRING(f, "\"node.h\"\n\"nodecode.h\"\n\"eliproto.h\"\n\"MONTblStack.h\"\n\n");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\nend;\n");
}

#ifdef PROTO_OK
PTGNode PTGMonAttrFile(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGMonAttrFile(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGMonAttrFile n;
	n = (_PPTGMonAttrFile)MALLOC(sizeof(struct _SPTGMonAttrFile));
	n->_print = (_PTGProc)_PrPTGMonAttrFile;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetSymbAttrs */

typedef struct _SPTGMonGetSymbAttrs{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMonGetSymbAttrs;

#ifdef PROTO_OK
static void _PrPTGMonGetSymbAttrs(_PPTGMonGetSymbAttrs n)
#else
static void _PrPTGMonGetSymbAttrs(n)
	_PPTGMonGetSymbAttrs n;
#endif
{
	PTG_OUTPUT_STRING(f, "operation get_symb_attrs\n");
	PTG_OUTPUT_STRING(f, "\t\"Return the attribute names and types for a particular node\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the relevant node\") : str\n");
	PTG_OUTPUT_STRING(f, "{ switch (LHSMAP[(MONTblStackArray(root))->_prod]) {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\tdefault: DAPTO_RESULT_STR (\"unknown node type\");\n");
	PTG_OUTPUT_STRING(f, "}}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetSymbAttrs(PTGNode p1)
#else
PTGNode PTGMonGetSymbAttrs(p1)

PTGNode p1;
#endif
{
	_PPTGMonGetSymbAttrs n;
	n = (_PPTGMonGetSymbAttrs)MALLOC(sizeof(struct _SPTGMonGetSymbAttrs));
	n->_print = (_PTGProc)_PrPTGMonGetSymbAttrs;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetRuleAttrs */

typedef struct _SPTGMonGetRuleAttrs{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMonGetRuleAttrs;

#ifdef PROTO_OK
static void _PrPTGMonGetRuleAttrs(_PPTGMonGetRuleAttrs n)
#else
static void _PrPTGMonGetRuleAttrs(n)
	_PPTGMonGetRuleAttrs n;
#endif
{
	PTG_OUTPUT_STRING(f, "operation get_rule_attrs\n");
	PTG_OUTPUT_STRING(f, "\t\"Return the attribute names and types for a particular node\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the relevant node\") : str\n");
	PTG_OUTPUT_STRING(f, "{ switch ((MONTblStackArray(root))->_prod) {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\tdefault: DAPTO_RESULT_STR (\"unknown node type\");\n");
	PTG_OUTPUT_STRING(f, "}}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetRuleAttrs(PTGNode p1)
#else
PTGNode PTGMonGetRuleAttrs(p1)

PTGNode p1;
#endif
{
	_PPTGMonGetRuleAttrs n;
	n = (_PPTGMonGetRuleAttrs)MALLOC(sizeof(struct _SPTGMonGetRuleAttrs));
	n->_print = (_PTGProc)_PrPTGMonGetRuleAttrs;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetAttrSymbCase */

typedef struct _SPTGMonGetAttrSymbCase{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGMonGetAttrSymbCase;

#ifdef PROTO_OK
static void _PrPTGMonGetAttrSymbCase(_PPTGMonGetAttrSymbCase n)
#else
static void _PrPTGMonGetAttrSymbCase(n)
	_PPTGMonGetAttrSymbCase n;
#endif
{
	PTG_OUTPUT_STRING(f, "\tcase SYMB");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\t\tbreak;\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetAttrSymbCase(CONST char* p1, PTGNode p2)
#else
PTGNode PTGMonGetAttrSymbCase(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGMonGetAttrSymbCase n;
	n = (_PPTGMonGetAttrSymbCase)MALLOC(sizeof(struct _SPTGMonGetAttrSymbCase));
	n->_print = (_PTGProc)_PrPTGMonGetAttrSymbCase;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetAttrRuleCase */

typedef struct _SPTGMonGetAttrRuleCase{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGMonGetAttrRuleCase;

#ifdef PROTO_OK
static void _PrPTGMonGetAttrRuleCase(_PPTGMonGetAttrRuleCase n)
#else
static void _PrPTGMonGetAttrRuleCase(n)
	_PPTGMonGetAttrRuleCase n;
#endif
{
	PTG_OUTPUT_STRING(f, "\tcase RULE");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\t\tbreak;\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetAttrRuleCase(CONST char* p1, PTGNode p2)
#else
PTGNode PTGMonGetAttrRuleCase(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGMonGetAttrRuleCase n;
	n = (_PPTGMonGetAttrRuleCase)MALLOC(sizeof(struct _SPTGMonGetAttrRuleCase));
	n->_print = (_PTGProc)_PrPTGMonGetAttrRuleCase;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetTerms */

typedef struct _SPTGMonGetTerms{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMonGetTerms;

#ifdef PROTO_OK
static void _PrPTGMonGetTerms(_PPTGMonGetTerms n)
#else
static void _PrPTGMonGetTerms(n)
	_PPTGMonGetTerms n;
#endif
{
	PTG_OUTPUT_STRING(f, "operation get_rule_terms\n");
	PTG_OUTPUT_STRING(f, "\t\"Return terminal names and types for the rule applied at a node\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the relevant node\") : str\n");
	PTG_OUTPUT_STRING(f, "{ switch ((MONTblStackArray(root))->_prod) {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\tdefault: DAPTO_RESULT_STR (\"unknown node type\");\n");
	PTG_OUTPUT_STRING(f, "}}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetTerms(PTGNode p1)
#else
PTGNode PTGMonGetTerms(p1)

PTGNode p1;
#endif
{
	_PPTGMonGetTerms n;
	n = (_PPTGMonGetTerms)MALLOC(sizeof(struct _SPTGMonGetTerms));
	n->_print = (_PTGProc)_PrPTGMonGetTerms;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonGetTermCase */

typedef struct _SPTGMonGetTermCase{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGMonGetTermCase;

#ifdef PROTO_OK
static void _PrPTGMonGetTermCase(_PPTGMonGetTermCase n)
#else
static void _PrPTGMonGetTermCase(n)
	_PPTGMonGetTermCase n;
#endif
{
	PTG_OUTPUT_STRING(f, "\tcase RULE");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\t\tbreak;\n");
}

#ifdef PROTO_OK
PTGNode PTGMonGetTermCase(CONST char* p1, PTGNode p2)
#else
PTGNode PTGMonGetTermCase(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGMonGetTermCase n;
	n = (_PPTGMonGetTermCase)MALLOC(sizeof(struct _SPTGMonGetTermCase));
	n->_print = (_PTGProc)_PrPTGMonGetTermCase;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonTermDescr */

typedef struct _SPTGMonTermDescr{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	CONST char* p3;
} * _PPTGMonTermDescr;

#ifdef PROTO_OK
static void _PrPTGMonTermDescr(_PPTGMonTermDescr n)
#else
static void _PrPTGMonTermDescr(n)
	_PPTGMonTermDescr n;
#endif
{
	PTG_OUTPUT_STRING(f, "\t\tDAPTO_RESULT_STR (\"");
	PTG_OUTPUT_STRING(f, n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "\");\n");
}

#ifdef PROTO_OK
PTGNode PTGMonTermDescr(CONST char* p1, PTGNode p2, CONST char* p3)
#else
PTGNode PTGMonTermDescr(p1, p2, p3)

CONST char* p1;
PTGNode p2;
CONST char* p3;
#endif
{
	_PPTGMonTermDescr n;
	n = (_PPTGMonTermDescr)MALLOC(sizeof(struct _SPTGMonTermDescr));
	n->_print = (_PTGProc)_PrPTGMonTermDescr;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern MonIndex */

typedef struct _SPTGMonIndex{
	_PTGProc _print;
	int p1;
} * _PPTGMonIndex;

#ifdef PROTO_OK
static void _PrPTGMonIndex(_PPTGMonIndex n)
#else
static void _PrPTGMonIndex(n)
	_PPTGMonIndex n;
#endif
{
	PTG_OUTPUT_STRING(f, "[");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "]");
}

#ifdef PROTO_OK
PTGNode PTGMonIndex(int p1)
#else
PTGNode PTGMonIndex(p1)

int p1;
#endif
{
	_PPTGMonIndex n;
	n = (_PPTGMonIndex)MALLOC(sizeof(struct _SPTGMonIndex));
	n->_print = (_PTGProc)_PrPTGMonIndex;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonAttrDescr */

typedef struct _SPTGMonAttrDescr{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
} * _PPTGMonAttrDescr;

#ifdef PROTO_OK
static void _PrPTGMonAttrDescr(_PPTGMonAttrDescr n)
#else
static void _PrPTGMonAttrDescr(n)
	_PPTGMonAttrDescr n;
#endif
{
	PTG_OUTPUT_STRING(f, "\t\tDAPTO_RESULT_STR (\"");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\");\n");
}

#ifdef PROTO_OK
PTGNode PTGMonAttrDescr(CONST char* p1, CONST char* p2)
#else
PTGNode PTGMonAttrDescr(p1, p2)

CONST char* p1;
CONST char* p2;
#endif
{
	_PPTGMonAttrDescr n;
	n = (_PPTGMonAttrDescr)MALLOC(sizeof(struct _SPTGMonAttrDescr));
	n->_print = (_PTGProc)_PrPTGMonAttrDescr;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonAttrComp */

typedef struct _SPTGMonAttrComp{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGMonAttrComp;

#ifdef PROTO_OK
static void _PrPTGMonAttrComp(_PPTGMonAttrComp n)
#else
static void _PrPTGMonAttrComp(n)
	_PPTGMonAttrComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "event attr_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\t\"An attribute of type ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " has been evaluated\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the attribute's node\",\n");
	PTG_OUTPUT_STRING(f, "\t int is_symb \"Is a symbol attribute\",\n");
	PTG_OUTPUT_STRING(f, "\t str name \"Name of the attribute\",\n");
	PTG_OUTPUT_STRING(f, "\t ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " value \"Value of the attribute\",\n");
	PTG_OUTPUT_STRING(f, "\t int line \"The line number of the computation in the specification\",\n");
	PTG_OUTPUT_STRING(f, "\t int col \"The column of the computation in the specification\");\n\n");
}

#ifdef PROTO_OK
PTGNode PTGMonAttrComp(CONST char* p1)
#else
PTGNode PTGMonAttrComp(p1)

CONST char* p1;
#endif
{
	_PPTGMonAttrComp n;
	n = (_PPTGMonAttrComp)MALLOC(sizeof(struct _SPTGMonAttrComp));
	n->_print = (_PTGProc)_PrPTGMonAttrComp;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonPlainComp */

typedef struct _SPTGMonPlainComp{
	_PTGProc _print;
} * _PPTGMonPlainComp;

#ifdef PROTO_OK
static void _PrPTGMonPlainComp(_PPTGMonPlainComp n)
#else
static void _PrPTGMonPlainComp(n)
	_PPTGMonPlainComp n;
#endif
{
	PTG_OUTPUT_STRING(f, "event computation\n");
	PTG_OUTPUT_STRING(f, "\t\"A plain computation has been computed\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the node that is the computation's context\",\n");
	PTG_OUTPUT_STRING(f, "\t int line \"The line number of the computation in the specification\",\n");
	PTG_OUTPUT_STRING(f, "\t int col \"The column of the computation in the specification\");\n\n");
	PTG_OUTPUT_STRING(f, "event void_comp\n");
	PTG_OUTPUT_STRING(f, "\t\"A computation associated with a VOID attribute has been evaluated\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the attribute's node\",\n");
	PTG_OUTPUT_STRING(f, "\t str name \"Name of the attribute\",\n");
	PTG_OUTPUT_STRING(f, "\t int line \"The line number of the computation in the specification\",\n");
	PTG_OUTPUT_STRING(f, "\t int col \"The column of the computation in the specification\");\n\n");
}

static struct _SPTGMonPlainComp _sptgMonPlainComp = { (_PTGProc) _PrPTGMonPlainComp };

#ifdef PROTO_OK
PTGNode PTGMonPlainComp(void)
#else
PTGNode PTGMonPlainComp()
#endif
{
	return (PTGNode)(&_sptgMonPlainComp);
}


/* Implementation of Pattern MonTermEvent */

typedef struct _SPTGMonTermEvent{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGMonTermEvent;

#ifdef PROTO_OK
static void _PrPTGMonTermEvent(_PPTGMonTermEvent n)
#else
static void _PrPTGMonTermEvent(n)
	_PPTGMonTermEvent n;
#endif
{
	PTG_OUTPUT_STRING(f, "event term_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\t\"A terminal value of type ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " is available\"\n");
	PTG_OUTPUT_STRING(f, "\t(int root \"Pointer to the left-hand side node of the rule ");
	PTG_OUTPUT_STRING(f, "where the terminal appears\",\n");
	PTG_OUTPUT_STRING(f, "\t str name \"Name of the terminal\",\n");
	PTG_OUTPUT_STRING(f, "\t ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, " value \"Value of the terminal\");\n\n");
}

#ifdef PROTO_OK
PTGNode PTGMonTermEvent(CONST char* p1)
#else
PTGNode PTGMonTermEvent(p1)

CONST char* p1;
#endif
{
	_PPTGMonTermEvent n;
	n = (_PPTGMonTermEvent)MALLOC(sizeof(struct _SPTGMonTermEvent));
	n->_print = (_PTGProc)_PrPTGMonTermEvent;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern MonAttrCompCall */

typedef struct _SPTGMonAttrCompCall{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	int p3;
	CONST char* p4;
	PTGNode p5;
	int p6;
	int p7;
} * _PPTGMonAttrCompCall;

#ifdef PROTO_OK
static void _PrPTGMonAttrCompCall(_PPTGMonAttrCompCall n)
#else
static void _PrPTGMonAttrCompCall(n)
	_PPTGMonAttrCompCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "_dapto_attr_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "((");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "->_uid), ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", \"");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "\", ");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p6);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p7);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonAttrCompCall(CONST char* p1, PTGNode p2, int p3, CONST char* p4, PTGNode p5, int p6, int p7)
#else
PTGNode PTGMonAttrCompCall(p1, p2, p3, p4, p5, p6, p7)

CONST char* p1;
PTGNode p2;
int p3;
CONST char* p4;
PTGNode p5;
int p6;
int p7;
#endif
{
	_PPTGMonAttrCompCall n;
	n = (_PPTGMonAttrCompCall)MALLOC(sizeof(struct _SPTGMonAttrCompCall));
	n->_print = (_PTGProc)_PrPTGMonAttrCompCall;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	return (PTGNode)n;
}


/* Implementation of Pattern MonTermCall */

typedef struct _SPTGMonTermCall{
	_PTGProc _print;
	CONST char* p1;
	CONST char* p2;
	PTGNode p3;
	int p4;
} * _PPTGMonTermCall;

#ifdef PROTO_OK
static void _PrPTGMonTermCall(_PPTGMonTermCall n)
#else
static void _PrPTGMonTermCall(n)
	_PPTGMonTermCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));\n");
	PTG_OUTPUT_STRING(f, "_dapto_term_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "((_currn)->_uid, \"");
	PTG_OUTPUT_STRING(f, n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\", _TERM");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonTermCall(CONST char* p1, CONST char* p2, PTGNode p3, int p4)
#else
PTGNode PTGMonTermCall(p1, p2, p3, p4)

CONST char* p1;
CONST char* p2;
PTGNode p3;
int p4;
#endif
{
	_PPTGMonTermCall n;
	n = (_PPTGMonTermCall)MALLOC(sizeof(struct _SPTGMonTermCall));
	n->_print = (_PTGProc)_PrPTGMonTermCall;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern MonPlainCompCall */

typedef struct _SPTGMonPlainCompCall{
	_PTGProc _print;
	int p1;
	int p2;
} * _PPTGMonPlainCompCall;

#ifdef PROTO_OK
static void _PrPTGMonPlainCompCall(_PPTGMonPlainCompCall n)
#else
static void _PrPTGMonPlainCompCall(n)
	_PPTGMonPlainCompCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "_dapto_computation (_currn->_uid, ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonPlainCompCall(int p1, int p2)
#else
PTGNode PTGMonPlainCompCall(p1, p2)

int p1;
int p2;
#endif
{
	_PPTGMonPlainCompCall n;
	n = (_PPTGMonPlainCompCall)MALLOC(sizeof(struct _SPTGMonPlainCompCall));
	n->_print = (_PTGProc)_PrPTGMonPlainCompCall;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MonVoidAssign */

typedef struct _SPTGMonVoidAssign{
	_PTGProc _print;
	PTGNode p1;
	CONST char* p2;
	int p3;
	int p4;
} * _PPTGMonVoidAssign;

#ifdef PROTO_OK
static void _PrPTGMonVoidAssign(_PPTGMonVoidAssign n)
#else
static void _PrPTGMonVoidAssign(n)
	_PPTGMonVoidAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "_dapto_void_comp ((");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "->_uid), \"");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "\", ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonVoidAssign(PTGNode p1, CONST char* p2, int p3, int p4)
#else
PTGNode PTGMonVoidAssign(p1, p2, p3, p4)

PTGNode p1;
CONST char* p2;
int p3;
int p4;
#endif
{
	_PPTGMonVoidAssign n;
	n = (_PPTGMonVoidAssign)MALLOC(sizeof(struct _SPTGMonVoidAssign));
	n->_print = (_PTGProc)_PrPTGMonVoidAssign;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern MonTreeInsertion */

typedef struct _SPTGMonTreeInsertion{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGMonTreeInsertion;

#ifdef PROTO_OK
static void _PrPTGMonTreeInsertion(_PPTGMonTreeInsertion n)
#else
static void _PrPTGMonTreeInsertion(n)
	_PPTGMonTreeInsertion n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));\n");
	PTG_OUTPUT_STRING(f, "_dapto_tree ((");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "->_uid), _currn->_uid, ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMonTreeInsertion(PTGNode p1, int p2)
#else
PTGNode PTGMonTreeInsertion(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGMonTreeInsertion n;
	n = (_PPTGMonTreeInsertion)MALLOC(sizeof(struct _SPTGMonTreeInsertion));
	n->_print = (_PTGProc)_PrPTGMonTreeInsertion;
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

