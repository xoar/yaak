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

/* Implementation of Pattern FormalParam */

typedef struct _SPTGFormalParam{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGFormalParam;

#ifdef PROTO_OK
static void _PrPTGFormalParam(_PPTGFormalParam n)
#else
static void _PrPTGFormalParam(n)
	_PPTGFormalParam n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " p");
	PTG_OUTPUT_INT(f, n->p2);
}

#ifdef PROTO_OK
PTGNode PTGFormalParam(PTGNode p1, int p2)
#else
PTGNode PTGFormalParam(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGFormalParam n;
	n = (_PPTGFormalParam)MALLOC(sizeof(struct _SPTGFormalParam));
	n->_print = (_PTGProc)_PrPTGFormalParam;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern NoTypedParams */

typedef struct _SPTGNoTypedParams{
	_PTGProc _print;
} * _PPTGNoTypedParams;

#ifdef PROTO_OK
static void _PrPTGNoTypedParams(_PPTGNoTypedParams n)
#else
static void _PrPTGNoTypedParams(n)
	_PPTGNoTypedParams n;
#endif
{
	PTG_OUTPUT_STRING(f, "void");
}

static struct _SPTGNoTypedParams _sptgNoTypedParams = { (_PTGProc) _PrPTGNoTypedParams };

#ifdef PROTO_OK
PTGNode PTGNoTypedParams(void)
#else
PTGNode PTGNoTypedParams()
#endif
{
	return (PTGNode)(&_sptgNoTypedParams);
}


/* Implementation of Pattern HeaderFile */

typedef struct _SPTGHeaderFile{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGHeaderFile;

#ifdef PROTO_OK
static void _PrPTGHeaderFile(_PPTGHeaderFile n)
#else
static void _PrPTGHeaderFile(n)
	_PPTGHeaderFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifndef _PTGGEN_H\n");
	PTG_OUTPUT_STRING(f, "#define _PTGGEN_H\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#include <stdio.h>\n");
	PTG_OUTPUT_STRING(f, "#include \"eliproto.h\"\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* Include-files specified in .ptg.phi-files */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#include \"ptg.h\"\n");
	PTG_OUTPUT_STRING(f, "/* Definition of Output-Macros */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if !defined(PTG_OUTPUT_FILE)\n");
	PTG_OUTPUT_STRING(f, "#    define PTG_OUTPUT_FILE FILE *\n");
	PTG_OUTPUT_STRING(f, "#    define PTG_OUTPUT_DEFAULT 1\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "#    define PTG_OUTPUT_DEFAULT 0\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "#if !defined(PTG_OUTPUT_STRING)\n");
	PTG_OUTPUT_STRING(f, "#    define PTG_OUTPUT_STRING(file,param) fputs(param, file)\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_INT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_INT(file,param)    fprintf(file,\"%d\",param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_LONG)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_LONG(file,param)   fprintf(file,\"%ld\",param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_SHORT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_SHORT(file,param)  fprintf(file,\"%d\",(int) param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_CHAR)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_CHAR(file,param)   fputc(param, file)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_FLOAT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_FLOAT(file,param)  fprintf(file,\"%g\",(double)param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_DOUBLE)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_DOUBLE(file,param) fprintf(file,\"%g\",param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "     /* PTG_OUTPUT_STRING defined */\n");
	PTG_OUTPUT_STRING(f, "     extern void _PTGPrintInt ELI_ARG((PTG_OUTPUT_FILE,int));\n");
	PTG_OUTPUT_STRING(f, "     extern void _PTGPrintLong ELI_ARG((PTG_OUTPUT_FILE,long));\n");
	PTG_OUTPUT_STRING(f, "     extern void _PTGPrintChar ELI_ARG((PTG_OUTPUT_FILE,char));\n");
	PTG_OUTPUT_STRING(f, "     extern void _PTGPrintDouble ELI_ARG((PTG_OUTPUT_FILE,double));\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_INT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_INT(file,param)    _PTGPrintInt(file,param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_LONG)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_LONG(file,param)   _PTGPrintLong(file,param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_SHORT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_SHORT(file,param)  _PTGPrintInt(file,(int)param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_CHAR)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_CHAR(file,param)   _PTGPrintChar(file,param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_FLOAT)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_FLOAT(file,param)  _PTGPrintDouble(file,(double)param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#    if !defined(PTG_OUTPUT_DOUBLE)\n");
	PTG_OUTPUT_STRING(f, "#            define PTG_OUTPUT_DOUBLE(file,param) _PTGPrintDouble(file,param)\n");
	PTG_OUTPUT_STRING(f, "#    endif\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* Define PTGNode Type */\n");
	PTG_OUTPUT_STRING(f, "#if defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "struct _SPTG0;\n");
	PTG_OUTPUT_STRING(f, "typedef void (* _PTGProc)(struct _SPTG0 *);\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "typedef void (* _PTGProc)();\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "typedef struct _SPTG0\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "  _PTGProc _print;\n");
	PTG_OUTPUT_STRING(f, "} * _PPTG0;\n");
	PTG_OUTPUT_STRING(f, "typedef _PPTG0 PTGNode;                      /* the only exported type */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* predefined static PTGNULL-Node */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "extern struct _SPTG0 _PTGNULL;\n");
	PTG_OUTPUT_STRING(f, "#define PTGNULL (& _PTGNULL)\n");
	PTG_OUTPUT_STRING(f, "#define PTGNull() (& _PTGNULL)\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* output functions */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if PTG_OUTPUT_DEFAULT\n");
	PTG_OUTPUT_STRING(f, "extern PTGNode PTGOut ELI_ARG((PTGNode root));\n");
	PTG_OUTPUT_STRING(f, "extern PTGNode PTGOutFile ELI_ARG((const char *filename, PTGNode root));\n");
	PTG_OUTPUT_STRING(f, "extern PTGNode PTGOutFPtr ELI_ARG((FILE *output, PTGNode root));\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "extern PTGNode PTGProcess ELI_ARG((PTG_OUTPUT_FILE file, PTGNode root));\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* Memory Management functions. */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "extern void PTGFree ELI_ARG((void));\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* ============================ */\n");
	PTG_OUTPUT_STRING(f, "/* functions for making PTG nodes */\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* prototypes for used function call insertions */\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* ============================ */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#ifdef MONITOR\n");
	PTG_OUTPUT_STRING(f, "/* Monitoring support for structured values */\n");
	PTG_OUTPUT_STRING(f, "#define DAPTO_RESULTPTGNode(n) DAPTO_RESULT_PTR(n)\n");
	PTG_OUTPUT_STRING(f, "#define DAPTO_ARGPTGNode(n) DAPTO_ARG_PTR(n, PTGNode)\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
}

#ifdef PROTO_OK
PTGNode PTGHeaderFile(PTGNode p1, PTGNode p2)
#else
PTGNode PTGHeaderFile(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGHeaderFile n;
	n = (_PPTGHeaderFile)MALLOC(sizeof(struct _SPTGHeaderFile));
	n->_print = (_PTGProc)_PrPTGHeaderFile;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern PatternFile */

typedef struct _SPTGPatternFile{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGPatternFile;

#ifdef PROTO_OK
static void _PrPTGPatternFile(_PPTGPatternFile n)
#else
static void _PrPTGPatternFile(n)
	_PPTGPatternFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "#include <stdio.h>\n");
	PTG_OUTPUT_STRING(f, "#include <stdlib.h>\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#include \"ptg_gen.h\"\n");
	PTG_OUTPUT_STRING(f, "#include \"obstack.h\"\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "/*                      Memory Management                   */\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "static Obstack _PTGObstack;\n");
	PTG_OUTPUT_STRING(f, "static void *_PTGFirstObj = NULL;\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "static void _PTGInit()\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       if (_PTGFirstObj)\n");
	PTG_OUTPUT_STRING(f, "               return;\n");
	PTG_OUTPUT_STRING(f, "       obstack_init(&_PTGObstack);\n");
	PTG_OUTPUT_STRING(f, "       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "void PTGFree()\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       obstack_free(&_PTGObstack, _PTGFirstObj);\n");
	PTG_OUTPUT_STRING(f, "       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "static void *MALLOC(int size)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "static void *MALLOC(size) int size;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       if (! _PTGFirstObj)\n");
	PTG_OUTPUT_STRING(f, "               _PTGInit();\n");
	PTG_OUTPUT_STRING(f, "       return (obstack_alloc(&_PTGObstack, size));\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "/*                       Output-functions                   */\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "static PTG_OUTPUT_FILE f;\n");
	PTG_OUTPUT_STRING(f, "static char buffer[40];\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if PTG_OUTPUT_DEFAULT\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOut (PTGNode r)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOut (r)\n");
	PTG_OUTPUT_STRING(f, "       PTGNode r;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       f = stdout;\n");
	PTG_OUTPUT_STRING(f, "       if (r) {\n");
	PTG_OUTPUT_STRING(f, "               (* (r->_print)) (r);\n");
	PTG_OUTPUT_STRING(f, "       }\n");
	PTG_OUTPUT_STRING(f, "       return (r);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOutFile (const char *fn, PTGNode r)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOutFile (fn, r)\n");
	PTG_OUTPUT_STRING(f, "       char * fn; PTGNode r;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       if ((f = fopen(fn, \"w\"))  == (FILE *)NULL)\n");
	PTG_OUTPUT_STRING(f, "       {\n");
	PTG_OUTPUT_STRING(f, "               fprintf(stderr, \"ERROR: PTGOutFile: output file '%s' can't be opened.\\n\",fn);\n");
	PTG_OUTPUT_STRING(f, "               exit(1);\n");
	PTG_OUTPUT_STRING(f, "       }\n");
	PTG_OUTPUT_STRING(f, "       if (r)\n");
	PTG_OUTPUT_STRING(f, "               (* (r->_print)) (r);\n");
	PTG_OUTPUT_STRING(f, "       fclose(f);\n");
	PTG_OUTPUT_STRING(f, "       return (r);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOutFPtr(FILE *fptr, PTGNode r)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGOutFPtr(fptr, r)\n");
	PTG_OUTPUT_STRING(f, "       FILE *fptr; PTGNode r;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       if ((f = fptr) == (FILE *)NULL)\n");
	PTG_OUTPUT_STRING(f, "       {\n");
	PTG_OUTPUT_STRING(f, "               fprintf(stderr, \"ERROR: PTGOutFPtr: output file not open.\\n\");\n");
	PTG_OUTPUT_STRING(f, "               exit(1);\n");
	PTG_OUTPUT_STRING(f, "       }\n");
	PTG_OUTPUT_STRING(f, "       if (r)\n");
	PTG_OUTPUT_STRING(f, "               (* (r->_print)) (r);\n");
	PTG_OUTPUT_STRING(f, "       return (r);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGProcess(PTG_OUTPUT_FILE file, PTGNode r)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTGProcess(file, r)\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_FILE file; PTGNode r;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       f = file;\n");
	PTG_OUTPUT_STRING(f, "       if (r)\n");
	PTG_OUTPUT_STRING(f, "               (* (r->_print)) (r);\n");
	PTG_OUTPUT_STRING(f, "       return (r);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "/*                            PTGNULL                       */\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* Define PTGNULL as a PTGNode that prints nothing. */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#if defined(__STDC__) || defined(__cplusplus)\n");
	PTG_OUTPUT_STRING(f, "static void _PrPTGNULL(_PPTG0 n)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "static void _PrPTGNULL(n)\n");
	PTG_OUTPUT_STRING(f, "_PPTG0 n;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{(void)n; /* function printing nothing */}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "struct _SPTG0   _PTGNULL = { (_PTGProc) _PrPTGNULL };\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "/*          Node-Construction and Print-functions           */\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* ============================ */\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "/* ============================ */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "/*                  Default Output Functions                */\n");
	PTG_OUTPUT_STRING(f, "/* -------------------------------------------------------- */\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintInt(PTG_OUTPUT_FILE file, int param)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintInt(file, param)\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_FILE file; int param;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{    /* used for short and int */\n");
	PTG_OUTPUT_STRING(f, "       sprintf(buffer,\"%d\",param);\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_STRING(file,buffer);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintLong(PTG_OUTPUT_FILE file, long param)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintLong(file, param)\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_FILE file; long param;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       sprintf(buffer,\"%ld\",param);\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_STRING(file,buffer);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintDouble(PTG_OUTPUT_FILE file, double param)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintDouble(file, param)\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_FILE file; double param;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{    /* used for float and double */\n");
	PTG_OUTPUT_STRING(f, "       sprintf(buffer,\"%g\",param);\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_STRING(file,buffer);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintChar(PTG_OUTPUT_FILE file, char param)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "void _PTGPrintChar(file, param)\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_FILE file; char param;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{\n");
	PTG_OUTPUT_STRING(f, "       buffer[0] = param;\n");
	PTG_OUTPUT_STRING(f, "       buffer[1] = 0;\n");
	PTG_OUTPUT_STRING(f, "       PTG_OUTPUT_STRING(file,buffer);\n");
	PTG_OUTPUT_STRING(f, "}\n");
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGPatternFile(PTGNode p1)
#else
PTGNode PTGPatternFile(p1)

PTGNode p1;
#endif
{
	_PPTGPatternFile n;
	n = (_PPTGPatternFile)MALLOC(sizeof(struct _SPTGPatternFile));
	n->_print = (_PTGProc)_PrPTGPatternFile;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PatternImpl */

typedef struct _SPTGPatternImpl{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGPatternImpl;

#ifdef PROTO_OK
static void _PrPTGPatternImpl(_PPTGPatternImpl n)
#else
static void _PrPTGPatternImpl(n)
	_PPTGPatternImpl n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n/* Implementation of Pattern ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " */\n\n");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
}

#ifdef PROTO_OK
PTGNode PTGPatternImpl(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGPatternImpl(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGPatternImpl n;
	n = (_PPTGPatternImpl)MALLOC(sizeof(struct _SPTGPatternImpl));
	n->_print = (_PTGProc)_PrPTGPatternImpl;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern FunctHdr */

typedef struct _SPTGFunctHdr{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGFunctHdr;

#ifdef PROTO_OK
static void _PrPTGFunctHdr(_PPTGFunctHdr n)
#else
static void _PrPTGFunctHdr(n)
	_PPTGFunctHdr n;
#endif
{
	PTG_OUTPUT_STRING(f, "PTGNode PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "));\n");
}

#ifdef PROTO_OK
PTGNode PTGFunctHdr(PTGNode p1, PTGNode p2)
#else
PTGNode PTGFunctHdr(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGFunctHdr n;
	n = (_PPTGFunctHdr)MALLOC(sizeof(struct _SPTGFunctHdr));
	n->_print = (_PTGProc)_PrPTGFunctHdr;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern EmptyPattern */

typedef struct _SPTGEmptyPattern{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGEmptyPattern;

#ifdef PROTO_OK
static void _PrPTGEmptyPattern(_PPTGEmptyPattern n)
#else
static void _PrPTGEmptyPattern(n)
	_PPTGEmptyPattern n;
#endif
{
	PTG_OUTPUT_STRING(f, "#define PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " PTGNull\n");
}

#ifdef PROTO_OK
PTGNode PTGEmptyPattern(PTGNode p1)
#else
PTGNode PTGEmptyPattern(p1)

PTGNode p1;
#endif
{
	_PPTGEmptyPattern n;
	n = (_PPTGEmptyPattern)MALLOC(sizeof(struct _SPTGEmptyPattern));
	n->_print = (_PTGProc)_PrPTGEmptyPattern;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CalledFunction */

typedef struct _SPTGCalledFunction{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGCalledFunction;

#ifdef PROTO_OK
static void _PrPTGCalledFunction(_PPTGCalledFunction n)
#else
static void _PrPTGCalledFunction(n)
	_PPTGCalledFunction n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nvoid ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ELI_ARG((PTG_OUTPUT_FILE");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "));");
}

#ifdef PROTO_OK
PTGNode PTGCalledFunction(PTGNode p1, PTGNode p2)
#else
PTGNode PTGCalledFunction(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGCalledFunction n;
	n = (_PPTGCalledFunction)MALLOC(sizeof(struct _SPTGCalledFunction));
	n->_print = (_PTGProc)_PrPTGCalledFunction;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern CommaOpt */

typedef struct _SPTGCommaOpt{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGCommaOpt;

#ifdef PROTO_OK
static void _PrPTGCommaOpt(_PPTGCommaOpt n)
#else
static void _PrPTGCommaOpt(n)
	_PPTGCommaOpt n;
#endif
{
	if (n->p1 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ", ");
	}
	n->p1->_print(n->p1);
}

#ifdef PROTO_OK
PTGNode PTGCommaOpt(PTGNode p1)
#else
PTGNode PTGCommaOpt(p1)

PTGNode p1;
#endif
{
	_PPTGCommaOpt n;
	if(p1 == PTGNULL)
		return PTGNULL;
	n = (_PPTGCommaOpt)MALLOC(sizeof(struct _SPTGCommaOpt));
	n->_print = (_PTGProc)_PrPTGCommaOpt;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Structure */

typedef struct _SPTGStructure{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGStructure;

#ifdef PROTO_OK
static void _PrPTGStructure(_PPTGStructure n)
#else
static void _PrPTGStructure(n)
	_PPTGStructure n;
#endif
{
	PTG_OUTPUT_STRING(f, "typedef struct _SPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "{");
	PP_Indent(f);
	PTG_OUTPUT_STRING(f, "\n_PTGProc _print;");
	n->p2->_print(n->p2);
	PP_Exdent(f);
	PTG_OUTPUT_STRING(f, "\n} * _PPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";\n\n");
}

#ifdef PROTO_OK
PTGNode PTGStructure(PTGNode p1, PTGNode p2)
#else
PTGNode PTGStructure(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGStructure n;
	n = (_PPTGStructure)MALLOC(sizeof(struct _SPTGStructure));
	n->_print = (_PTGProc)_PrPTGStructure;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Semicolon */

typedef struct _SPTGSemicolon{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSemicolon;

#ifdef PROTO_OK
static void _PrPTGSemicolon(_PPTGSemicolon n)
#else
static void _PrPTGSemicolon(n)
	_PPTGSemicolon n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGSemicolon(PTGNode p1)
#else
PTGNode PTGSemicolon(p1)

PTGNode p1;
#endif
{
	_PPTGSemicolon n;
	n = (_PPTGSemicolon)MALLOC(sizeof(struct _SPTGSemicolon));
	n->_print = (_PTGProc)_PrPTGSemicolon;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ConstructorFunction */

typedef struct _SPTGConstructorFunction{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
} * _PPTGConstructorFunction;

#ifdef PROTO_OK
static void _PrPTGConstructorFunction(_PPTGConstructorFunction n)
#else
static void _PrPTGConstructorFunction(n)
	_PPTGConstructorFunction n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ")\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ")\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n#endif\n");
	PTG_OUTPUT_STRING(f, "{");
	PP_Indent(f);
	PTG_OUTPUT_STRING(f, "\n_PPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " n;");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "\nn = (_PPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")MALLOC(sizeof(struct _SPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "));");
	PTG_OUTPUT_STRING(f, "\nn->_print = (_PTGProc)_PrPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ";");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, "\nreturn (PTGNode)n;");
	PP_Exdent(f);
	PTG_OUTPUT_STRING(f, "\n}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGConstructorFunction(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6)
#else
PTGNode PTGConstructorFunction(p1, p2, p3, p4, p5, p6)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
#endif
{
	_PPTGConstructorFunction n;
	n = (_PPTGConstructorFunction)MALLOC(sizeof(struct _SPTGConstructorFunction));
	n->_print = (_PTGProc)_PrPTGConstructorFunction;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	return (PTGNode)n;
}


/* Implementation of Pattern IndexedName */

typedef struct _SPTGIndexedName{
	_PTGProc _print;
	int p1;
} * _PPTGIndexedName;

#ifdef PROTO_OK
static void _PrPTGIndexedName(_PPTGIndexedName n)
#else
static void _PrPTGIndexedName(n)
	_PPTGIndexedName n;
#endif
{
	PTG_OUTPUT_STRING(f, "p");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGIndexedName(int p1)
#else
PTGNode PTGIndexedName(p1)

int p1;
#endif
{
	_PPTGIndexedName n;
	n = (_PPTGIndexedName)MALLOC(sizeof(struct _SPTGIndexedName));
	n->_print = (_PTGProc)_PrPTGIndexedName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ParamAssign */

typedef struct _SPTGParamAssign{
	_PTGProc _print;
	int p1;
} * _PPTGParamAssign;

#ifdef PROTO_OK
static void _PrPTGParamAssign(_PPTGParamAssign n)
#else
static void _PrPTGParamAssign(n)
	_PPTGParamAssign n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nn->p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " = p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ";");
}

#ifdef PROTO_OK
PTGNode PTGParamAssign(int p1)
#else
PTGNode PTGParamAssign(p1)

int p1;
#endif
{
	_PPTGParamAssign n;
	n = (_PPTGParamAssign)MALLOC(sizeof(struct _SPTGParamAssign));
	n->_print = (_PTGProc)_PrPTGParamAssign;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ConstantConstructor */

typedef struct _SPTGConstantConstructor{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGConstantConstructor;

#ifdef PROTO_OK
static void _PrPTGConstantConstructor(_PPTGConstantConstructor n)
#else
static void _PrPTGConstantConstructor(n)
	_PPTGConstantConstructor n;
#endif
{
	PTG_OUTPUT_STRING(f, "static struct _SPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " _sptg");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " = { (_PTGProc) _PrPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " };\n\n");
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(void)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "PTGNode PTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "()\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{");
	PP_Indent(f);
	PTG_OUTPUT_STRING(f, "\nreturn (PTGNode)(&_sptg");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ");");
	PP_Exdent(f);
	PTG_OUTPUT_STRING(f, "\n}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGConstantConstructor(PTGNode p1)
#else
PTGNode PTGConstantConstructor(p1)

PTGNode p1;
#endif
{
	_PPTGConstantConstructor n;
	n = (_PPTGConstantConstructor)MALLOC(sizeof(struct _SPTGConstantConstructor));
	n->_print = (_PTGProc)_PrPTGConstantConstructor;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PrintFunction */

typedef struct _SPTGPrintFunction{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGPrintFunction;

#ifdef PROTO_OK
static void _PrPTGPrintFunction(_PPTGPrintFunction n)
#else
static void _PrPTGPrintFunction(n)
	_PPTGPrintFunction n;
#endif
{
	PTG_OUTPUT_STRING(f, "#ifdef PROTO_OK\n");
	PTG_OUTPUT_STRING(f, "static void _PrPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(_PPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " n)\n");
	PTG_OUTPUT_STRING(f, "#else\n");
	PTG_OUTPUT_STRING(f, "static void _PrPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(n)\n");
	PTG_OUTPUT_STRING(f, "\t_PPTG");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " n;\n");
	PTG_OUTPUT_STRING(f, "#endif\n");
	PTG_OUTPUT_STRING(f, "{");
	PP_Indent(f);
	n->p2->_print(n->p2);
	PP_Exdent(f);
	PTG_OUTPUT_STRING(f, "\n}\n\n");
}

#ifdef PROTO_OK
PTGNode PTGPrintFunction(PTGNode p1, PTGNode p2)
#else
PTGNode PTGPrintFunction(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGPrintFunction n;
	n = (_PPTGPrintFunction)MALLOC(sizeof(struct _SPTGPrintFunction));
	n->_print = (_PTGProc)_PrPTGPrintFunction;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern OutputCall */

typedef struct _SPTGOutputCall{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
} * _PPTGOutputCall;

#ifdef PROTO_OK
static void _PrPTGOutputCall(_PPTGOutputCall n)
#else
static void _PrPTGOutputCall(n)
	_PPTGOutputCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nPTG_OUTPUT_");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "(f, ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ");");
}

#ifdef PROTO_OK
PTGNode PTGOutputCall(CONST char* p1, PTGNode p2)
#else
PTGNode PTGOutputCall(p1, p2)

CONST char* p1;
PTGNode p2;
#endif
{
	_PPTGOutputCall n;
	n = (_PPTGOutputCall)MALLOC(sizeof(struct _SPTGOutputCall));
	n->_print = (_PTGProc)_PrPTGOutputCall;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern PrintFctCall */

typedef struct _SPTGPrintFctCall{
	_PTGProc _print;
	int p1;
} * _PPTGPrintFctCall;

#ifdef PROTO_OK
static void _PrPTGPrintFctCall(_PPTGPrintFctCall n)
#else
static void _PrPTGPrintFctCall(n)
	_PPTGPrintFctCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nn->p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, "->_print(n->p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ");");
}

#ifdef PROTO_OK
PTGNode PTGPrintFctCall(int p1)
#else
PTGNode PTGPrintFctCall(p1)

int p1;
#endif
{
	_PPTGPrintFctCall n;
	n = (_PPTGPrintFctCall)MALLOC(sizeof(struct _SPTGPrintFctCall));
	n->_print = (_PTGProc)_PrPTGPrintFctCall;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Field */

typedef struct _SPTGField{
	_PTGProc _print;
	int p1;
} * _PPTGField;

#ifdef PROTO_OK
static void _PrPTGField(_PPTGField n)
#else
static void _PrPTGField(n)
	_PPTGField n;
#endif
{
	PTG_OUTPUT_STRING(f, "n->p");
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGField(int p1)
#else
PTGNode PTGField(p1)

int p1;
#endif
{
	_PPTGField n;
	n = (_PPTGField)MALLOC(sizeof(struct _SPTGField));
	n->_print = (_PTGProc)_PrPTGField;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern FunctionCall */

typedef struct _SPTGFunctionCall{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGFunctionCall;

#ifdef PROTO_OK
static void _PrPTGFunctionCall(_PPTGFunctionCall n)
#else
static void _PrPTGFunctionCall(n)
	_PPTGFunctionCall n;
#endif
{
	PTG_OUTPUT_STRING(f, "\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "(f");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ");");
}

#ifdef PROTO_OK
PTGNode PTGFunctionCall(PTGNode p1, PTGNode p2)
#else
PTGNode PTGFunctionCall(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGFunctionCall n;
	n = (_PPTGFunctionCall)MALLOC(sizeof(struct _SPTGFunctionCall));
	n->_print = (_PTGProc)_PrPTGFunctionCall;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern IfStatement */

typedef struct _SPTGIfStatement{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGIfStatement;

#ifdef PROTO_OK
static void _PrPTGIfStatement(_PPTGIfStatement n)
#else
static void _PrPTGIfStatement(n)
	_PPTGIfStatement n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nif (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")\n");
	PTG_OUTPUT_STRING(f, "{");
	PP_Indent(f);
	n->p2->_print(n->p2);
	PP_Exdent(f);
	PTG_OUTPUT_STRING(f, "\n}");
}

#ifdef PROTO_OK
PTGNode PTGIfStatement(PTGNode p1, PTGNode p2)
#else
PTGNode PTGIfStatement(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGIfStatement n;
	n = (_PPTGIfStatement)MALLOC(sizeof(struct _SPTGIfStatement));
	n->_print = (_PTGProc)_PrPTGIfStatement;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern And */

typedef struct _SPTGAnd{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGAnd;

#ifdef PROTO_OK
static void _PrPTGAnd(_PPTGAnd n)
#else
static void _PrPTGAnd(n)
	_PPTGAnd n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, " && ");
	}
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGAnd(PTGNode p1, PTGNode p2)
#else
PTGNode PTGAnd(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGAnd n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGAnd)MALLOC(sizeof(struct _SPTGAnd));
	n->_print = (_PTGProc)_PrPTGAnd;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern OptionCondition */

typedef struct _SPTGOptionCondition{
	_PTGProc _print;
	int p1;
} * _PPTGOptionCondition;

#ifdef PROTO_OK
static void _PrPTGOptionCondition(_PPTGOptionCondition n)
#else
static void _PrPTGOptionCondition(n)
	_PPTGOptionCondition n;
#endif
{
	PTG_OUTPUT_STRING(f, "n->p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " != PTGNULL");
}

#ifdef PROTO_OK
PTGNode PTGOptionCondition(int p1)
#else
PTGNode PTGOptionCondition(p1)

int p1;
#endif
{
	_PPTGOptionCondition n;
	n = (_PPTGOptionCondition)MALLOC(sizeof(struct _SPTGOptionCondition));
	n->_print = (_PTGProc)_PrPTGOptionCondition;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ConditionalReturn */

typedef struct _SPTGConditionalReturn{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGConditionalReturn;

#ifdef PROTO_OK
static void _PrPTGConditionalReturn(_PPTGConditionalReturn n)
#else
static void _PrPTGConditionalReturn(n)
	_PPTGConditionalReturn n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nif(");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
	PP_Indent(f);
	PTG_OUTPUT_STRING(f, "\nreturn PTGNULL;");
	PP_Exdent(f);
}

#ifdef PROTO_OK
PTGNode PTGConditionalReturn(PTGNode p1)
#else
PTGNode PTGConditionalReturn(p1)

PTGNode p1;
#endif
{
	_PPTGConditionalReturn n;
	n = (_PPTGConditionalReturn)MALLOC(sizeof(struct _SPTGConditionalReturn));
	n->_print = (_PTGProc)_PrPTGConditionalReturn;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern IsNull */

typedef struct _SPTGIsNull{
	_PTGProc _print;
	int p1;
} * _PPTGIsNull;

#ifdef PROTO_OK
static void _PrPTGIsNull(_PPTGIsNull n)
#else
static void _PrPTGIsNull(n)
	_PPTGIsNull n;
#endif
{
	PTG_OUTPUT_STRING(f, "p");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " == PTGNULL");
}

#ifdef PROTO_OK
PTGNode PTGIsNull(int p1)
#else
PTGNode PTGIsNull(p1)

int p1;
#endif
{
	_PPTGIsNull n;
	n = (_PPTGIsNull)MALLOC(sizeof(struct _SPTGIsNull));
	n->_print = (_PTGProc)_PrPTGIsNull;
	n->p1 = p1;
	return (PTGNode)n;
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

