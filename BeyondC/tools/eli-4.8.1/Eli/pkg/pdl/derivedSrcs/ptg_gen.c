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

/* Implementation of Pattern CGen */

typedef struct _SPTGCGen{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGCGen;

#ifdef PROTO_OK
static void _PrPTGCGen(_PPTGCGen n)
#else
static void _PrPTGCGen(n)
	_PPTGCGen n;
#endif
{
	PTG_OUTPUT_STRING(f, "#include \"pdl_gen.h\"\n\n");
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "#include \"pdl_dapto.h\"\n");
	PTG_OUTPUT_STRING(f, "#endif\n\n");
	PTG_OUTPUT_STRING(f, "#define PRESENT find(key, _property, (Entry *)&_Item, 0)\n");
	PTG_OUTPUT_STRING(f, "#define VALUE (_Item->PropVal)\n\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
	n->p5->_print(n->p5);
}

#ifdef PROTO_OK
PTGNode PTGCGen(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGCGen(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGCGen n;
	n = (_PPTGCGen)MALLOC(sizeof(struct _SPTGCGen));
	n->_print = (_PTGProc)_PrPTGCGen;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern OperationSpec */

typedef struct _SPTGOperationSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
} * _PPTGOperationSpec;

#ifdef PROTO_OK
static void _PrPTGOperationSpec(_PPTGOperationSpec n)
#else
static void _PrPTGOperationSpec(n)
	_PPTGOperationSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " (int _property, ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ")\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " (_property, ");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, ")\n");
	PTG_OUTPUT_STRING(f, "int _property;\n");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{  ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "Property _Item;\n");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, "\n}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGOperationSpec(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7)
#else
PTGNode PTGOperationSpec(p1, p2, p3, p4, p5, p6, p7)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
#endif
{
	_PPTGOperationSpec n;
	n = (_PPTGOperationSpec)MALLOC(sizeof(struct _SPTGOperationSpec));
	n->_print = (_PTGProc)_PrPTGOperationSpec;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
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
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
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


/* Implementation of Pattern Identifier */

typedef struct _SPTGIdentifier{
	_PTGProc _print;
	int p1;
} * _PPTGIdentifier;

#ifdef PROTO_OK
static void _PrPTGIdentifier(_PPTGIdentifier n)
#else
static void _PrPTGIdentifier(n)
	_PPTGIdentifier n;
#endif
{
	PrIdent(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGIdentifier(int p1)
#else
PTGNode PTGIdentifier(p1)

int p1;
#endif
{
	_PPTGIdentifier n;
	n = (_PPTGIdentifier)MALLOC(sizeof(struct _SPTGIdentifier));
	n->_print = (_PTGProc)_PrPTGIdentifier;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern String */

typedef struct _SPTGString{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGString;

#ifdef PROTO_OK
static void _PrPTGString(_PPTGString n)
#else
static void _PrPTGString(n)
	_PPTGString n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGString(CONST char* p1)
#else
PTGNode PTGString(p1)

CONST char* p1;
#endif
{
	_PPTGString n;
	n = (_PPTGString)MALLOC(sizeof(struct _SPTGString));
	n->_print = (_PTGProc)_PrPTGString;
	n->p1 = p1;
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
	PTG_OUTPUT_STRING(f, ", ");
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
	n = (_PPTGCommaSeq)MALLOC(sizeof(struct _SPTGCommaSeq));
	n->_print = (_PTGProc)_PrPTGCommaSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ParamDecl */

typedef struct _SPTGParamDecl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGParamDecl;

#ifdef PROTO_OK
static void _PrPTGParamDecl(_PPTGParamDecl n)
#else
static void _PrPTGParamDecl(n)
	_PPTGParamDecl n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ";\n");
}

#ifdef PROTO_OK
PTGNode PTGParamDecl(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGParamDecl(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGParamDecl n;
	n = (_PPTGParamDecl)MALLOC(sizeof(struct _SPTGParamDecl));
	n->_print = (_PTGProc)_PrPTGParamDecl;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern SModifier */

typedef struct _SPTGSModifier{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSModifier;

#ifdef PROTO_OK
static void _PrPTGSModifier(_PPTGSModifier n)
#else
static void _PrPTGSModifier(n)
	_PPTGSModifier n;
#endif
{
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGSModifier(PTGNode p1)
#else
PTGNode PTGSModifier(p1)

PTGNode p1;
#endif
{
	_PPTGSModifier n;
	n = (_PPTGSModifier)MALLOC(sizeof(struct _SPTGSModifier));
	n->_print = (_PTGProc)_PrPTGSModifier;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern EModifier */

typedef struct _SPTGEModifier{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGEModifier;

#ifdef PROTO_OK
static void _PrPTGEModifier(_PPTGEModifier n)
#else
static void _PrPTGEModifier(n)
	_PPTGEModifier n;
#endif
{
	PTG_OUTPUT_STRING(f, "(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ", ... )");
}

#ifdef PROTO_OK
PTGNode PTGEModifier(PTGNode p1)
#else
PTGNode PTGEModifier(p1)

PTGNode p1;
#endif
{
	_PPTGEModifier n;
	n = (_PPTGEModifier)MALLOC(sizeof(struct _SPTGEModifier));
	n->_print = (_PTGProc)_PrPTGEModifier;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PTypeSpec */

typedef struct _SPTGPTypeSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGPTypeSpec;

#ifdef PROTO_OK
static void _PrPTGPTypeSpec(_PPTGPTypeSpec n)
#else
static void _PrPTGPTypeSpec(n)
	_PPTGPTypeSpec n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGPTypeSpec(PTGNode p1, PTGNode p2)
#else
PTGNode PTGPTypeSpec(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGPTypeSpec n;
	n = (_PPTGPTypeSpec)MALLOC(sizeof(struct _SPTGPTypeSpec));
	n->_print = (_PTGProc)_PrPTGPTypeSpec;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IPTypeSpec */

typedef struct _SPTGIPTypeSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGIPTypeSpec;

#ifdef PROTO_OK
static void _PrPTGIPTypeSpec(_PPTGIPTypeSpec n)
#else
static void _PrPTGIPTypeSpec(n)
	_PPTGIPTypeSpec n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ");
	n->p3->_print(n->p3);
}

#ifdef PROTO_OK
PTGNode PTGIPTypeSpec(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGIPTypeSpec(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGIPTypeSpec n;
	n = (_PPTGIPTypeSpec)MALLOC(sizeof(struct _SPTGIPTypeSpec));
	n->_print = (_PTGProc)_PrPTGIPTypeSpec;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern FuncName */

typedef struct _SPTGFuncName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGFuncName;

#ifdef PROTO_OK
static void _PrPTGFuncName(_PPTGFuncName n)
#else
static void _PrPTGFuncName(n)
	_PPTGFuncName n;
#endif
{
	PTG_OUTPUT_STRING(f, "(*");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
}

#ifdef PROTO_OK
PTGNode PTGFuncName(PTGNode p1)
#else
PTGNode PTGFuncName(p1)

PTGNode p1;
#endif
{
	_PPTGFuncName n;
	n = (_PPTGFuncName)MALLOC(sizeof(struct _SPTGFuncName));
	n->_print = (_PTGProc)_PrPTGFuncName;
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


/* Implementation of Pattern TypeDef */

typedef struct _SPTGTypeDef{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGTypeDef;

#ifdef PROTO_OK
static void _PrPTGTypeDef(_PPTGTypeDef n)
#else
static void _PrPTGTypeDef(n)
	_PPTGTypeDef n;
#endif
{
	PTG_OUTPUT_STRING(f, "typedef struct ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "Elt {\n");
	PTG_OUTPUT_STRING(f, "\tEntry next;\n");
	PTG_OUTPUT_STRING(f, "\tint selector;\n");
	PTG_OUTPUT_STRING(f, "\tTYPE PropVal;\n");
	PTG_OUTPUT_STRING(f, "} *");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "Property;\n\n");
}

#ifdef PROTO_OK
PTGNode PTGTypeDef(PTGNode p1)
#else
PTGNode PTGTypeDef(p1)

PTGNode p1;
#endif
{
	_PPTGTypeDef n;
	n = (_PPTGTypeDef)MALLOC(sizeof(struct _SPTGTypeDef));
	n->_print = (_PTGProc)_PrPTGTypeDef;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Functions */

typedef struct _SPTGFunctions{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGFunctions;

#ifdef PROTO_OK
static void _PrPTGFunctions(_PPTGFunctions n)
#else
static void _PrPTGFunctions(n)
	_PPTGFunctions n;
#endif
{
	PTG_OUTPUT_STRING(f, "#define TYPE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n\n");
	PTG_OUTPUT_STRING(f, "#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "Elt))\n\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "#undef ACCESS\n");
	PTG_OUTPUT_STRING(f, "#undef TYPE\n");
}

#ifdef PROTO_OK
PTGNode PTGFunctions(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGFunctions(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGFunctions n;
	n = (_PPTGFunctions)MALLOC(sizeof(struct _SPTGFunctions));
	n->_print = (_PTGProc)_PrPTGFunctions;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Mon */

typedef struct _SPTGMon{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGMon;

#ifdef PROTO_OK
static void _PrPTGMon(_PPTGMon n)
#else
static void _PrPTGMon(n)
	_PPTGMon n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "static CONST char *pdl_names[] = {\n");
	PTG_OUTPUT_STRING(f, "    (char *)0,\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "};\n");
	PTG_OUTPUT_STRING(f, "static CONST char *pdl_types[] = {\n");
	PTG_OUTPUT_STRING(f, "    (char *)0,\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "};\n\n");
	PTG_OUTPUT_STRING(f, "void\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "pdl_mon_properties(DefTableKey k)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "pdl_mon_properties(k) DefTableKey k;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "    Entry e;\n");
	PTG_OUTPUT_STRING(f, "    if (k == NoKey) return;\n");
	PTG_OUTPUT_STRING(f, "    for (e = k->List; (e != (Entry)0) && (e->selector != 0);\n");
	PTG_OUTPUT_STRING(f, "         e = e->next) {\n");
	PTG_OUTPUT_STRING(f, "        DAPTO_RESULT_STR (pdl_names[e->selector]);\n");
	PTG_OUTPUT_STRING(f, "        DAPTO_RESULT_STR (pdl_types[e->selector]);\n");
	PTG_OUTPUT_STRING(f, "        switch (e->selector) {\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "            default: DAPTO_RESULT_STR (\"unknown property\");\n");
	PTG_OUTPUT_STRING(f, "        }\n");
	PTG_OUTPUT_STRING(f, "    }\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGMon(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGMon(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGMon n;
	n = (_PPTGMon)MALLOC(sizeof(struct _SPTGMon));
	n->_print = (_PTGProc)_PrPTGMon;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern ArrayEntry */

typedef struct _SPTGArrayEntry{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGArrayEntry;

#ifdef PROTO_OK
static void _PrPTGArrayEntry(_PPTGArrayEntry n)
#else
static void _PrPTGArrayEntry(n)
	_PPTGArrayEntry n;
#endif
{
	PTG_OUTPUT_STRING(f, "    \"");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\",\n");
}

#ifdef PROTO_OK
PTGNode PTGArrayEntry(PTGNode p1)
#else
PTGNode PTGArrayEntry(p1)

PTGNode p1;
#endif
{
	_PPTGArrayEntry n;
	n = (_PPTGArrayEntry)MALLOC(sizeof(struct _SPTGArrayEntry));
	n->_print = (_PTGProc)_PrPTGArrayEntry;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SwitchEntry */

typedef struct _SPTGSwitchEntry{
	_PTGProc _print;
	int p1;
	PTGNode p2;
} * _PPTGSwitchEntry;

#ifdef PROTO_OK
static void _PrPTGSwitchEntry(_PPTGSwitchEntry n)
#else
static void _PrPTGSwitchEntry(n)
	_PPTGSwitchEntry n;
#endif
{
	PTG_OUTPUT_STRING(f, "            case ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	PTG_OUTPUT_STRING(f, "#ifdef DAPTO_RESULT");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "                DAPTO_RESULT");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " (((");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "Property)e)->PropVal);\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "                DAPTO_RESULT_OTHER (((");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "Property)e)->PropVal);\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "                break;\n");
}

#ifdef PROTO_OK
PTGNode PTGSwitchEntry(int p1, PTGNode p2)
#else
PTGNode PTGSwitchEntry(p1, p2)

int p1;
PTGNode p2;
#endif
{
	_PPTGSwitchEntry n;
	n = (_PPTGSwitchEntry)MALLOC(sizeof(struct _SPTGSwitchEntry));
	n->_print = (_PTGProc)_PrPTGSwitchEntry;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern HGen */

typedef struct _SPTGHGen{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGHGen;

#ifdef PROTO_OK
static void _PrPTGHGen(_PPTGHGen n)
#else
static void _PrPTGHGen(n)
	_PPTGHGen n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifndef PDL_GEN_H\n");
	PTG_OUTPUT_STRING(f, "#define PDL_GEN_H\n\n");
	PTG_OUTPUT_STRING(f, "#include \"deftbl.h\"\n\n");
	PTG_OUTPUT_STRING(f, "#ifdef ELI_ARG\n");
	PTG_OUTPUT_STRING(f, "#undef ELI_ARG\n");
	PTG_OUTPUT_STRING(f, "#endif\n\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "#define ELI_ARG(proto)    proto\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "#define ELI_ARG(proto)    ()\n");
	PTG_OUTPUT_STRING(f, "#endif\n\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "extern DefTableKey CloneKey ELI_ARG((DefTableKey key));\n");
	PTG_OUTPUT_STRING(f, "/* Clone a definition\n");
	PTG_OUTPUT_STRING(f, " *    On entry-\n");
	PTG_OUTPUT_STRING(f, " *       key=a valid definition\n");
	PTG_OUTPUT_STRING(f, " *    On exit-\n");
	PTG_OUTPUT_STRING(f, " *       CloneKey=Unique definition with the same properties\n");
	PTG_OUTPUT_STRING(f, " *                and property values as key\n");
	PTG_OUTPUT_STRING(f, " ***/\n\n");
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "extern void pdl_mon_properties ELI_ARG((DefTableKey));\n");
	PTG_OUTPUT_STRING(f, "#endif\n\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGHGen(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGHGen(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGHGen n;
	n = (_PPTGHGen)MALLOC(sizeof(struct _SPTGHGen));
	n->_print = (_PTGProc)_PrPTGHGen;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern Include */

typedef struct _SPTGInclude{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGInclude;

#ifdef PROTO_OK
static void _PrPTGInclude(_PPTGInclude n)
#else
static void _PrPTGInclude(n)
	_PPTGInclude n;
#endif
{
	PTG_OUTPUT_STRING(f, "#include ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGInclude(PTGNode p1)
#else
PTGNode PTGInclude(p1)

PTGNode p1;
#endif
{
	_PPTGInclude n;
	n = (_PPTGInclude)MALLOC(sizeof(struct _SPTGInclude));
	n->_print = (_PTGProc)_PrPTGInclude;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ExternSpec */

typedef struct _SPTGExternSpec{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGExternSpec;

#ifdef PROTO_OK
static void _PrPTGExternSpec(_PPTGExternSpec n)
#else
static void _PrPTGExternSpec(n)
	_PPTGExternSpec n;
#endif
{
	PTG_OUTPUT_STRING(f, "extern ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " ELI_ARG((int _Property, ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "));\n");
}

#ifdef PROTO_OK
PTGNode PTGExternSpec(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGExternSpec(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGExternSpec n;
	n = (_PPTGExternSpec)MALLOC(sizeof(struct _SPTGExternSpec));
	n->_print = (_PTGProc)_PrPTGExternSpec;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern ExtParamDecl */

typedef struct _SPTGExtParamDecl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGExtParamDecl;

#ifdef PROTO_OK
static void _PrPTGExtParamDecl(_PPTGExtParamDecl n)
#else
static void _PrPTGExtParamDecl(n)
	_PPTGExtParamDecl n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
}

#ifdef PROTO_OK
PTGNode PTGExtParamDecl(PTGNode p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGExtParamDecl(p1, p2, p3)

PTGNode p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGExtParamDecl n;
	n = (_PPTGExtParamDecl)MALLOC(sizeof(struct _SPTGExtParamDecl));
	n->_print = (_PTGProc)_PrPTGExtParamDecl;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Externs */

typedef struct _SPTGExterns{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGExterns;

#ifdef PROTO_OK
static void _PrPTGExterns(_PPTGExterns n)
#else
static void _PrPTGExterns(n)
	_PPTGExterns n;
#endif
{
	PTG_OUTPUT_STRING(f, "#define TYPE ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "#undef TYPE\n");
}

#ifdef PROTO_OK
PTGNode PTGExterns(PTGNode p1, PTGNode p2)
#else
PTGNode PTGExterns(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGExterns n;
	n = (_PPTGExterns)MALLOC(sizeof(struct _SPTGExterns));
	n->_print = (_PTGProc)_PrPTGExterns;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Macro */

typedef struct _SPTGMacro{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
} * _PPTGMacro;

#ifdef PROTO_OK
static void _PrPTGMacro(_PPTGMacro n)
#else
static void _PrPTGMacro(n)
	_PPTGMacro n;
#endif
{
	PTG_OUTPUT_STRING(f, "#define ");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "   \\\n");
	PTG_OUTPUT_STRING(f, "\t\t");
	n->p4->_print(n->p4);
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "(");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, ", ");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, ")\n");
}

#ifdef PROTO_OK
PTGNode PTGMacro(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7)
#else
PTGNode PTGMacro(p1, p2, p3, p4, p5, p6, p7)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
#endif
{
	_PPTGMacro n;
	n = (_PPTGMacro)MALLOC(sizeof(struct _SPTGMacro));
	n->_print = (_PTGProc)_PrPTGMacro;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	return (PTGNode)n;
}


/* Implementation of Pattern Num */

typedef struct _SPTGNum{
	_PTGProc _print;
	int p1;
} * _PPTGNum;

#ifdef PROTO_OK
static void _PrPTGNum(_PPTGNum n)
#else
static void _PrPTGNum(n)
	_PPTGNum n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGNum(int p1)
#else
PTGNode PTGNum(p1)

int p1;
#endif
{
	_PPTGNum n;
	n = (_PPTGNum)MALLOC(sizeof(struct _SPTGNum));
	n->_print = (_PTGProc)_PrPTGNum;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Elements */

typedef struct _SPTGElements{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGElements;

#ifdef PROTO_OK
static void _PrPTGElements(_PPTGElements n)
#else
static void _PrPTGElements(n)
	_PPTGElements n;
#endif
{
	PTG_OUTPUT_STRING(f, "static struct PropElt PDLe0 = {(Entry)0, 0};\n");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGElements(PTGNode p1)
#else
PTGNode PTGElements(p1)

PTGNode p1;
#endif
{
	_PPTGElements n;
	n = (_PPTGElements)MALLOC(sizeof(struct _SPTGElements));
	n->_print = (_PTGProc)_PrPTGElements;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Element */

typedef struct _SPTGElement{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGElement;

#ifdef PROTO_OK
static void _PrPTGElement(_PPTGElement n)
#else
static void _PrPTGElement(n)
	_PPTGElement n;
#endif
{
	PTG_OUTPUT_STRING(f, "static struct ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "Elt ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " = {(Entry)&");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ", ");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "};\n");
}

#ifdef PROTO_OK
PTGNode PTGElement(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGElement(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGElement n;
	n = (_PPTGElement)MALLOC(sizeof(struct _SPTGElement));
	n->_print = (_PTGProc)_PrPTGElement;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern ElementName */

typedef struct _SPTGElementName{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGElementName;

#ifdef PROTO_OK
static void _PrPTGElementName(_PPTGElementName n)
#else
static void _PrPTGElementName(n)
	_PPTGElementName n;
#endif
{
	PTG_OUTPUT_STRING(f, "PDLe");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGElementName(PTGNode p1)
#else
PTGNode PTGElementName(p1)

PTGNode p1;
#endif
{
	_PPTGElementName n;
	n = (_PPTGElementName)MALLOC(sizeof(struct _SPTGElementName));
	n->_print = (_PTGProc)_PrPTGElementName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Value */

typedef struct _SPTGValue{
	_PTGProc _print;
	int p1;
} * _PPTGValue;

#ifdef PROTO_OK
static void _PrPTGValue(_PPTGValue n)
#else
static void _PrPTGValue(n)
	_PPTGValue n;
#endif
{
	StripText(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGValue(int p1)
#else
PTGNode PTGValue(p1)

int p1;
#endif
{
	_PPTGValue n;
	n = (_PPTGValue)MALLOC(sizeof(struct _SPTGValue));
	n->_print = (_PTGProc)_PrPTGValue;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Array */

typedef struct _SPTGArray{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGArray;

#ifdef PROTO_OK
static void _PrPTGArray(_PPTGArray n)
#else
static void _PrPTGArray(n)
	_PPTGArray n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nstruct PropList PDLk[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "};\n");
}

#ifdef PROTO_OK
PTGNode PTGArray(PTGNode p1)
#else
PTGNode PTGArray(p1)

PTGNode p1;
#endif
{
	_PPTGArray n;
	n = (_PPTGArray)MALLOC(sizeof(struct _SPTGArray));
	n->_print = (_PTGProc)_PrPTGArray;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ArrayElt */

typedef struct _SPTGArrayElt{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGArrayElt;

#ifdef PROTO_OK
static void _PrPTGArrayElt(_PPTGArrayElt n)
#else
static void _PrPTGArrayElt(n)
	_PPTGArrayElt n;
#endif
{
	PTG_OUTPUT_STRING(f, "  {(Entry)&");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "}");
}

#ifdef PROTO_OK
PTGNode PTGArrayElt(PTGNode p1)
#else
PTGNode PTGArrayElt(p1)

PTGNode p1;
#endif
{
	_PPTGArrayElt n;
	n = (_PPTGArrayElt)MALLOC(sizeof(struct _SPTGArrayElt));
	n->_print = (_PTGProc)_PrPTGArrayElt;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern EndList */

typedef struct _SPTGEndList{
	_PTGProc _print;
} * _PPTGEndList;

#ifdef PROTO_OK
static void _PrPTGEndList(_PPTGEndList n)
#else
static void _PrPTGEndList(n)
	_PPTGEndList n;
#endif
{
	PTG_OUTPUT_STRING(f, "PDLe0");
}

static struct _SPTGEndList _sptgEndList = { (_PTGProc) _PrPTGEndList };

#ifdef PROTO_OK
PTGNode PTGEndList(void)
#else
PTGNode PTGEndList()
#endif
{
	return (PTGNode)(&_sptgEndList);
}


/* Implementation of Pattern ArraySeq */

typedef struct _SPTGArraySeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGArraySeq;

#ifdef PROTO_OK
static void _PrPTGArraySeq(_PPTGArraySeq n)
#else
static void _PrPTGArraySeq(n)
	_PPTGArraySeq n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ",\n");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGArraySeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGArraySeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGArraySeq n;
	n = (_PPTGArraySeq)MALLOC(sizeof(struct _SPTGArraySeq));
	n->_print = (_PTGProc)_PrPTGArraySeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Defines */

typedef struct _SPTGDefines{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGDefines;

#ifdef PROTO_OK
static void _PrPTGDefines(_PPTGDefines n)
#else
static void _PrPTGDefines(n)
	_PPTGDefines n;
#endif
{
	PTG_OUTPUT_STRING(f, "extern struct PropList PDLk[];\n\n");
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGDefines(PTGNode p1)
#else
PTGNode PTGDefines(p1)

PTGNode p1;
#endif
{
	_PPTGDefines n;
	n = (_PPTGDefines)MALLOC(sizeof(struct _SPTGDefines));
	n->_print = (_PTGProc)_PrPTGDefines;
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
	PTG_OUTPUT_STRING(f, "#define ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " (&PDLk[");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "])\n");
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


/* Implementation of Pattern CloneKey */

typedef struct _SPTGCloneKey{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGCloneKey;

#ifdef PROTO_OK
static void _PrPTGCloneKey(_PPTGCloneKey n)
#else
static void _PrPTGCloneKey(n)
	_PPTGCloneKey n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nDefTableKey\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "CloneKey (DefTableKey key)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "CloneKey (key)\n");
	PTG_OUTPUT_STRING(f, "    DefTableKey key;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "  DefTableKey k;\n");
	PTG_OUTPUT_STRING(f, "  Entry e;\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  if (key == NoKey) return NoKey;\n");
	PTG_OUTPUT_STRING(f, "  k = NewKey ();\n");
	PTG_OUTPUT_STRING(f, "  for (e = key->List; (e != (Entry)0) && (e->selector != 0);\n");
	PTG_OUTPUT_STRING(f, "       e = e->next) {\n");
	PTG_OUTPUT_STRING(f, "    switch (e->selector) {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "      }\n");
	PTG_OUTPUT_STRING(f, "  }\n");
	PTG_OUTPUT_STRING(f, "  return k;\n");
	PTG_OUTPUT_STRING(f, "}\n");
}

#ifdef PROTO_OK
PTGNode PTGCloneKey(PTGNode p1)
#else
PTGNode PTGCloneKey(p1)

PTGNode p1;
#endif
{
	_PPTGCloneKey n;
	n = (_PPTGCloneKey)MALLOC(sizeof(struct _SPTGCloneKey));
	n->_print = (_PTGProc)_PrPTGCloneKey;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CloneCase */

typedef struct _SPTGCloneCase{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	PTGNode p3;
} * _PPTGCloneCase;

#ifdef PROTO_OK
static void _PrPTGCloneCase(_PPTGCloneCase n)
#else
static void _PrPTGCloneCase(n)
	_PPTGCloneCase n;
#endif
{
	PTG_OUTPUT_STRING(f, "      case ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ":\n");
	PTG_OUTPUT_STRING(f, "         Reset");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " (k, ((");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "Property)e)->PropVal);\n");
	PTG_OUTPUT_STRING(f, "         break;\n");
}

#ifdef PROTO_OK
PTGNode PTGCloneCase(int p1, PTGNode p2, PTGNode p3)
#else
PTGNode PTGCloneCase(p1, p2, p3)

int p1;
PTGNode p2;
PTGNode p3;
#endif
{
	_PPTGCloneCase n;
	n = (_PPTGCloneCase)MALLOC(sizeof(struct _SPTGCloneCase));
	n->_print = (_PTGProc)_PrPTGCloneCase;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
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

