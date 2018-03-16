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

/* Implementation of Pattern Flex */

typedef struct _SPTGFlex{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGFlex;

#ifdef PROTO_OK
static void _PrPTGFlex(_PPTGFlex n)
#else
static void _PrPTGFlex(n)
	_PPTGFlex n;
#endif
{
	PTG_OUTPUT_STRING(f, "%%\n\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n\n");
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGFlex(PTGNode p1, PTGNode p2)
#else
PTGNode PTGFlex(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGFlex n;
	n = (_PPTGFlex)MALLOC(sizeof(struct _SPTGFlex));
	n->_print = (_PTGProc)_PrPTGFlex;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern FlexEntry */

typedef struct _SPTGFlexEntry{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGFlexEntry;

#ifdef PROTO_OK
static void _PrPTGFlexEntry(_PPTGFlexEntry n)
#else
static void _PrPTGFlexEntry(n)
	_PPTGFlexEntry n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\t");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "; /* ext=");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " sourceLine=");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, " */\n");
}

#ifdef PROTO_OK
PTGNode PTGFlexEntry(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGFlexEntry(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGFlexEntry n;
	n = (_PPTGFlexEntry)MALLOC(sizeof(struct _SPTGFlexEntry));
	n->_print = (_PTGProc)_PrPTGFlexEntry;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern Backend */

typedef struct _SPTGBackend{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGBackend;

#ifdef PROTO_OK
static void _PrPTGBackend(_PPTGBackend n)
#else
static void _PrPTGBackend(n)
	_PPTGBackend n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	n->p4->_print(n->p4);
}

#ifdef PROTO_OK
PTGNode PTGBackend(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGBackend(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGBackend n;
	n = (_PPTGBackend)MALLOC(sizeof(struct _SPTGBackend));
	n->_print = (_PTGProc)_PrPTGBackend;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern BEEntry */

typedef struct _SPTGBEEntry{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
} * _PPTGBEEntry;

#ifdef PROTO_OK
static void _PrPTGBEEntry(_PPTGBEEntry n)
#else
static void _PrPTGBEEntry(n)
	_PPTGBEEntry n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGBEEntry(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5)
#else
PTGNode PTGBEEntry(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
#endif
{
	_PPTGBEEntry n;
	n = (_PPTGBEEntry)MALLOC(sizeof(struct _SPTGBEEntry));
	n->_print = (_PTGProc)_PrPTGBEEntry;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern Quoted */

typedef struct _SPTGQuoted{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGQuoted;

#ifdef PROTO_OK
static void _PrPTGQuoted(_PPTGQuoted n)
#else
static void _PrPTGQuoted(n)
	_PPTGQuoted n;
#endif
{
	PTG_OUTPUT_STRING(f, "\"");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\"");
}

#ifdef PROTO_OK
PTGNode PTGQuoted(PTGNode p1)
#else
PTGNode PTGQuoted(p1)

PTGNode p1;
#endif
{
	_PPTGQuoted n;
	n = (_PPTGQuoted)MALLOC(sizeof(struct _SPTGQuoted));
	n->_print = (_PTGProc)_PrPTGQuoted;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Str */

typedef struct _SPTGStr{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGStr;

#ifdef PROTO_OK
static void _PrPTGStr(_PPTGStr n)
#else
static void _PrPTGStr(n)
	_PPTGStr n;
#endif
{
	PrString(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGStr(CONST char* p1)
#else
PTGNode PTGStr(p1)

CONST char* p1;
#endif
{
	_PPTGStr n;
	n = (_PPTGStr)MALLOC(sizeof(struct _SPTGStr));
	n->_print = (_PTGProc)_PrPTGStr;
	n->p1 = p1;
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

