#ifndef _PTGGEN_H
#define _PTGGEN_H

#include <stdio.h>
#include "eliproto.h"

/* Include-files specified in .ptg.phi-files */

#include "ptg.h"
/* Definition of Output-Macros */

#if !defined(PTG_OUTPUT_FILE)
#    define PTG_OUTPUT_FILE FILE *
#    define PTG_OUTPUT_DEFAULT 1
#else
#    define PTG_OUTPUT_DEFAULT 0
#endif
#if !defined(PTG_OUTPUT_STRING)
#    define PTG_OUTPUT_STRING(file,param) fputs(param, file)
#    if !defined(PTG_OUTPUT_INT)
#            define PTG_OUTPUT_INT(file,param)    fprintf(file,"%d",param)
#    endif
#    if !defined(PTG_OUTPUT_LONG)
#            define PTG_OUTPUT_LONG(file,param)   fprintf(file,"%ld",param)
#    endif
#    if !defined(PTG_OUTPUT_SHORT)
#            define PTG_OUTPUT_SHORT(file,param)  fprintf(file,"%d",(int) param)
#    endif
#    if !defined(PTG_OUTPUT_CHAR)
#            define PTG_OUTPUT_CHAR(file,param)   fputc(param, file)
#    endif
#    if !defined(PTG_OUTPUT_FLOAT)
#            define PTG_OUTPUT_FLOAT(file,param)  fprintf(file,"%g",(double)param)
#    endif
#    if !defined(PTG_OUTPUT_DOUBLE)
#            define PTG_OUTPUT_DOUBLE(file,param) fprintf(file,"%g",param)
#    endif

#else
     /* PTG_OUTPUT_STRING defined */
     extern void _PTGPrintInt ELI_ARG((PTG_OUTPUT_FILE,int));
     extern void _PTGPrintLong ELI_ARG((PTG_OUTPUT_FILE,long));
     extern void _PTGPrintChar ELI_ARG((PTG_OUTPUT_FILE,char));
     extern void _PTGPrintDouble ELI_ARG((PTG_OUTPUT_FILE,double));
#    if !defined(PTG_OUTPUT_INT)
#            define PTG_OUTPUT_INT(file,param)    _PTGPrintInt(file,param)
#    endif
#    if !defined(PTG_OUTPUT_LONG)
#            define PTG_OUTPUT_LONG(file,param)   _PTGPrintLong(file,param)
#    endif
#    if !defined(PTG_OUTPUT_SHORT)
#            define PTG_OUTPUT_SHORT(file,param)  _PTGPrintInt(file,(int)param)
#    endif
#    if !defined(PTG_OUTPUT_CHAR)
#            define PTG_OUTPUT_CHAR(file,param)   _PTGPrintChar(file,param)
#    endif
#    if !defined(PTG_OUTPUT_FLOAT)
#            define PTG_OUTPUT_FLOAT(file,param)  _PTGPrintDouble(file,(double)param)
#    endif
#    if !defined(PTG_OUTPUT_DOUBLE)
#            define PTG_OUTPUT_DOUBLE(file,param) _PTGPrintDouble(file,param)
#    endif
#endif

/* Define PTGNode Type */
#if defined(__cplusplus)
struct _SPTG0;
typedef void (* _PTGProc)(struct _SPTG0 *);
#else
typedef void (* _PTGProc)();
#endif

typedef struct _SPTG0
{
  _PTGProc _print;
} * _PPTG0;
typedef _PPTG0 PTGNode;                      /* the only exported type */

/* predefined static PTGNULL-Node */

extern struct _SPTG0 _PTGNULL;
#define PTGNULL (& _PTGNULL)
#define PTGNull() (& _PTGNULL)

/* output functions */

#if PTG_OUTPUT_DEFAULT
extern PTGNode PTGOut ELI_ARG((PTGNode root));
extern PTGNode PTGOutFile ELI_ARG((const char *filename, PTGNode root));
extern PTGNode PTGOutFPtr ELI_ARG((FILE *output, PTGNode root));
#endif
extern PTGNode PTGProcess ELI_ARG((PTG_OUTPUT_FILE file, PTGNode root));

/* Memory Management functions. */

extern void PTGFree ELI_ARG((void));

/* ============================ */
/* functions for making PTG nodes */
PTGNode PTGId ELI_ARG((int p1));
PTGNode PTGAsIs ELI_ARG((CONST char* p1));
PTGNode PTGNumb ELI_ARG((int p1));
PTGNode PTGCString ELI_ARG((CONST char* p1));
PTGNode PTGCChar ELI_ARG((int p1));
PTGNode PTGPString ELI_ARG((CONST char* p1));
PTGNode PTGSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGCommaSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGEol ELI_ARG((PTGNode p1));
PTGNode PTGGramRule ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGGramProd ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGGramListof ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGGramLiteral ELI_ARG((CONST char* p1));
PTGNode PTGGramSymbol ELI_ARG((CONST char* p1));
PTGNode PTGGramGenSymbol ELI_ARG((CONST char* p1));
PTGNode PTGGramSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGGramAltSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGUsedSymbols ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGSymbol ELI_ARG((CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5));
PTGNode PTGRule ELI_ARG((CONST char* p1, PTGNode p2, PTGNode p3));
PTGNode PTGCoord ELI_ARG((int p1, int p2));
PTGNode PTGAttribute ELI_ARG((CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5));
PTGNode PTGDefaultType ELI_ARG((void));
PTGNode PTGInhComputations ELI_ARG((PTGNode p1));
PTGNode PTGInhComp ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGRemoteInfo ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGWithOccurrences ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIncludingInfo ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGConstitInfo ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGConstitsInfo ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGShieldInfo ELI_ARG((PTGNode p1));
PTGNode PTGWithInfo ELI_ARG((CONST char* p1, CONST char* p2, CONST char* p3, CONST char* p4));
PTGNode PTGSymbAttr ELI_ARG((CONST char* p1, CONST char* p2));
PTGNode PTGSymbolComputations ELI_ARG((CONST char* p1, PTGNode p2, PTGNode p3));
PTGNode PTGRuleComputations ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGUnknownExpr ELI_ARG((PTGNode p1));
PTGNode PTGComputation ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5));
PTGNode PTGOutCoord ELI_ARG((int p1, int p2));
PTGNode PTGDepend ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGAssign ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGLoop ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGCallExpr ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGName ELI_ARG((CONST char* p1));
PTGNode PTGIntValue ELI_ARG((int p1));
PTGNode PTGStrValue ELI_ARG((CONST char* p1));
PTGNode PTGChrValue ELI_ARG((int p1));
PTGNode PTGFltValue ELI_ARG((CONST char* p1));
PTGNode PTGAttrAccRule ELI_ARG((PTGNode p1, CONST char* p2, int p3, CONST char* p4));
PTGNode PTGIsChain ELI_ARG((void));
PTGNode PTGIsAttr ELI_ARG((void));
PTGNode PTGRuleAttrAcc ELI_ARG((CONST char* p1));
PTGNode PTGAttrAccSymb ELI_ARG((PTGNode p1, CONST char* p2, CONST char* p3));
PTGNode PTGSymbTermAcc ELI_ARG((int p1));
PTGNode PTGRuleTermAcc ELI_ARG((CONST char* p1, int p2));
PTGNode PTGRHS ELI_ARG((CONST char* p1));
PTGNode PTGHeadAcc ELI_ARG((CONST char* p1));
PTGNode PTGTailAcc ELI_ARG((CONST char* p1));
PTGNode PTGIndentNL ELI_ARG((PTGNode p1));
PTGNode PTGIdlTypedef ELI_ARG((int p1, CONST char* p2, PTGNode p3));
PTGNode PTGIdlTermdef ELI_ARG((int p1, CONST char* p2, PTGNode p3));
PTGNode PTGIdlSymb ELI_ARG((int p1, CONST char* p2, PTGNode p3, PTGNode p4));
PTGNode PTGIdlAttrdef ELI_ARG((int p1, int p2, int p3, PTGNode p4, CONST char* p5, int p6));
PTGNode PTGIdlProd ELI_ARG((int p1, CONST char* p2, PTGNode p3, PTGNode p4, int p5));
PTGNode PTGIdlChain ELI_ARG((int p1, CONST char* p2, PTGNode p3, int p4));
PTGNode PTGIdlSymbol ELI_ARG((PTGNode p1, int p2));
PTGNode PTGIdlLiteral ELI_ARG((PTGNode p1, CONST char* p2));
PTGNode PTGIdlNonLitTerm ELI_ARG((PTGNode p1, CONST char* p2, CONST char* p3));
PTGNode PTGIdlGenSymbol ELI_ARG((PTGNode p1, int p2));
PTGNode PTGIdlrowCol ELI_ARG((int p1, int p2));
PTGNode PTGIdlcolRow ELI_ARG((int p1, int p2));
PTGNode PTGIdlAttrEval ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlRuleComputations ELI_ARG((PTGNode p1, int p2));
PTGNode PTGIdlCompCoord ELI_ARG((int p1, int p2));
PTGNode PTGIdlDepend ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGIdlBottomup ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlIdentity ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlAssign ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGIdlGenTreeDummy ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlDummyComp ELI_ARG((int p1));
PTGNode PTGIdlChainstart ELI_ARG((int p1, PTGNode p2, PTGNode p3));
PTGNode PTGIdlLoopInit ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlLoop ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGIdlCall ELI_ARG((PTGNode p1, CONST char* p2, PTGNode p3));
PTGNode PTGIdlName ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGIdlIntValue ELI_ARG((int p1, PTGNode p2));
PTGNode PTGIdlStrValue ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGIdlChrValue ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGIdlFltValue ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGIdlAttrAcc ELI_ARG((int p1, int p2, PTGNode p3));
PTGNode PTGIdlChainAcc ELI_ARG((int p1, int p2, PTGNode p3));
PTGNode PTGIdlTermAcc ELI_ARG((int p1, PTGNode p2));
PTGNode PTGIdlConstituent ELI_ARG((PTGNode p1, int p2, int p3, PTGNode p4));
PTGNode PTGIdlWith ELI_ARG((PTGNode p1, CONST char* p2, CONST char* p3, CONST char* p4, CONST char* p5, PTGNode p6));
PTGNode PTGIdlShield ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGIdlVoiden ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlShieldSym ELI_ARG((int p1, PTGNode p2));
PTGNode PTGIdlIncluding ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIdlSymbAttr ELI_ARG((int p1, int p2));

/* prototypes for used function call insertions */

void PtgOutId ELI_ARG((PTG_OUTPUT_FILE, int));
void CPtgOutstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void CPtgOutchar ELI_ARG((PTG_OUTPUT_FILE, int));
void PPtgOutstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void IndentIncr ELI_ARG((PTG_OUTPUT_FILE));
void IndentDecr ELI_ARG((PTG_OUTPUT_FILE));
void IndentNewLine ELI_ARG((PTG_OUTPUT_FILE));
void IdlStringTrafo ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
/* ============================ */

#ifdef MONITOR
/* Monitoring support for structured values */
#define DAPTO_RESULTPTGNode(n) DAPTO_RESULT_PTR(n)
#define DAPTO_ARGPTGNode(n) DAPTO_ARG_PTR(n, PTGNode)
#endif

#endif
