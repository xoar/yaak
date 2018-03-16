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
PTGNode PTGThisNode ELI_ARG((void));
PTGNode PTGDescNode ELI_ARG((int p1));
PTGNode PTGDescName ELI_ARG((PTGNode p1));
PTGNode PTGVisitProcName ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGInclGlobName ELI_ARG((PTGNode p1));
PTGNode PTGInclLocName ELI_ARG((PTGNode p1));
PTGNode PTGSymbStructName ELI_ARG((PTGNode p1));
PTGNode PTGSymbPtrTypeName ELI_ARG((PTGNode p1));
PTGNode PTGProdStructName ELI_ARG((PTGNode p1));
PTGNode PTGProdPtrTypeName ELI_ARG((PTGNode p1));
PTGNode PTGMkProcName ELI_ARG((PTGNode p1));
PTGNode PTGNullNodePtr ELI_ARG((void));
PTGNode PTGMkParmName ELI_ARG((PTGNode p1));
PTGNode PTGTermGetName ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGLhsStackAttrName ELI_ARG((PTGNode p1));
PTGNode PTGRhsStackAttrName ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGVarAttrName ELI_ARG((PTGNode p1));
PTGNode PTGTreeAttrName ELI_ARG((PTGNode p1));
PTGNode PTGRuleAttrName ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGStmt ELI_ARG((PTGNode p1));
PTGNode PTGCall ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGProcExpr ELI_ARG((PTGNode p1));
PTGNode PTGAssign ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIfStmt ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGIfExpr ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGParen ELI_ARG((PTGNode p1));
PTGNode PTGPtrTo ELI_ARG((PTGNode p1));
PTGNode PTGSelectPtr ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGContent ELI_ARG((PTGNode p1));
PTGNode PTGAddr ELI_ARG((PTGNode p1));
PTGNode PTGNoVal ELI_ARG((void));
PTGNode PTGToNoVal ELI_ARG((PTGNode p1));
PTGNode PTGDecl ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGProto ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGExternDecl ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGComElem ELI_ARG((PTGNode p1));
PTGNode PTGComSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGSeqCom ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGSep ELI_ARG((PTGNode p1));
PTGNode PTGFile ELI_ARG((PTGNode p1));
PTGNode PTGNumb ELI_ARG((int p1));
PTGNode PTGAsIs ELI_ARG((CONST char* p1));
PTGNode PTGC_Str ELI_ARG((CONST char* p1));
PTGNode PTGP_Str ELI_ARG((CONST char* p1));
PTGNode PTGSpecLineInfo ELI_ARG((int p1));
PTGNode PTGVisitProcFileHead ELI_ARG((void));
PTGNode PTGRootProc ELI_ARG((PTGNode p1));
PTGNode PTGRootVisit ELI_ARG((void));
PTGNode PTGPredefVSProc ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGPredefVSHeader ELI_ARG((PTGNode p1));
PTGNode PTGVisitHeader ELI_ARG((PTGNode p1));
PTGNode PTGVisitProcHeader ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGDefineVS ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGVisitProcHead ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8));
PTGNode PTGDescVisit ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGGenAssign ELI_ARG((PTGNode p1, CONST char* p2, PTGNode p3));
PTGNode PTGTreeActHead ELI_ARG((CONST char* p1));
PTGNode PTGDefineLine ELI_ARG((PTGNode p1));
PTGNode PTGNonLitTermAcc ELI_ARG((int p1));
PTGNode PTGLineSelect ELI_ARG((PTGNode p1));
PTGNode PTGColSelect ELI_ARG((PTGNode p1));
PTGNode PTGLineAccess ELI_ARG((void));
PTGNode PTGColAccess ELI_ARG((void));
PTGNode PTGCoordAccess ELI_ARG((void));
PTGNode PTGLabel ELI_ARG((PTGNode p1));
PTGNode PTGLabName ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGLoop ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGInclPre ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGInclPost ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGNodeTypeFile ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGProdTypeDef ELI_ARG((CONST char* p1));
PTGNode PTGSymbTypeDef ELI_ARG((CONST char* p1));
PTGNode PTGProdStructDecl ELI_ARG((CONST char* p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGListDescs ELI_ARG((void));
PTGNode PTGSymbStructDecl ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGSubTreeComp ELI_ARG((CONST char* p1, int p2));
PTGNode PTGAttrComp ELI_ARG((CONST char* p1, CONST char* p2));
PTGNode PTGNodePtrHeader ELI_ARG((void));
PTGNode PTGEncodeFile ELI_ARG((PTGNode p1));
PTGNode PTGDefine ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGRuleCode ELI_ARG((PTGNode p1));
PTGNode PTGSymbCode ELI_ARG((PTGNode p1));
PTGNode PTGVisitMapHead ELI_ARG((PTGNode p1));
PTGNode PTGVisitMapExtern ELI_ARG((PTGNode p1));
PTGNode PTGVisitMapFile ELI_ARG((PTGNode p1));
PTGNode PTGVisitArray ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGVisitCast ELI_ARG((PTGNode p1));
PTGNode PTGLhsArray ELI_ARG((PTGNode p1));
PTGNode PTGTreeConFileHead ELI_ARG((void));
PTGNode PTGMkSymbFctHead ELI_ARG((PTGNode p1));
PTGNode PTGMkSymbFctChk ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGMkSymbFctTail ELI_ARG((PTGNode p1));
PTGNode PTGMkTermFct ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGParmSpec ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGProtoSpec ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGAttrAssign ELI_ARG((PTGNode p1));
PTGNode PTGMkProdFct ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7));
PTGNode PTGNonLitTermAct ELI_ARG((PTGNode p1));
PTGNode PTGNonLitTermDefine ELI_ARG((CONST char* p1));
PTGNode PTGOldTermDefine ELI_ARG((CONST char* p1));
PTGNode PTGNonLitTermProto ELI_ARG((CONST char* p1, int p2));
PTGNode PTGNonLitTermName ELI_ARG((int p1));
PTGNode PTGNonLitTermSpec ELI_ARG((CONST char* p1, int p2));
PTGNode PTGTreeConVisit ELI_ARG((void));
PTGNode PTGMkTreeParmSpec ELI_ARG((PTGNode p1));
PTGNode PTGMkProtoSpec ELI_ARG((PTGNode p1));
PTGNode PTGTreeAssign ELI_ARG((PTGNode p1, CONST char* p2, CONST char* p3, int p4));
PTGNode PTGGenTreeAssign ELI_ARG((PTGNode p1, CONST char* p2));
PTGNode PTGTreeConHeader ELI_ARG((PTGNode p1));
PTGNode PTGMkSymbHeader ELI_ARG((PTGNode p1));
PTGNode PTGMkProcHeader ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGMkTermProcHeader ELI_ARG((PTGNode p1));
PTGNode PTGComma ELI_ARG((void));
PTGNode PTGNewLine ELI_ARG((void));
PTGNode PTGListStruct ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGListFunctsHdr ELI_ARG((PTGNode p1));
PTGNode PTGListElemFct ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGListElemChk ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGListFuncts ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5));
PTGNode PTGListTermact ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGMonAprods ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGAbsProds ELI_ARG((PTGNode p1));
PTGNode PTGProds ELI_ARG((CONST char* p1, CONST char* p2, PTGNode p3));
PTGNode PTGAbsNchild ELI_ARG((PTGNode p1));
PTGNode PTGNchild ELI_ARG((int p1));
PTGNode PTGAbsChild ELI_ARG((PTGNode p1));
PTGNode PTGChild ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGDesc ELI_ARG((int p1));
PTGNode PTGSseq ELI_ARG((PTGNode p1, CONST char* p2));
PTGNode PTGLseq ELI_ARG((PTGNode p1, CONST char* p2));
PTGNode PTGMonAttrFile ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3));
PTGNode PTGMonGetSymbAttrs ELI_ARG((PTGNode p1));
PTGNode PTGMonGetRuleAttrs ELI_ARG((PTGNode p1));
PTGNode PTGMonGetAttrSymbCase ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGMonGetAttrRuleCase ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGMonGetTerms ELI_ARG((PTGNode p1));
PTGNode PTGMonGetTermCase ELI_ARG((CONST char* p1, PTGNode p2));
PTGNode PTGMonTermDescr ELI_ARG((CONST char* p1, PTGNode p2, CONST char* p3));
PTGNode PTGMonIndex ELI_ARG((int p1));
PTGNode PTGMonAttrDescr ELI_ARG((CONST char* p1, CONST char* p2));
PTGNode PTGMonAttrComp ELI_ARG((CONST char* p1));
PTGNode PTGMonPlainComp ELI_ARG((void));
PTGNode PTGMonTermEvent ELI_ARG((CONST char* p1));
PTGNode PTGMonAttrCompCall ELI_ARG((CONST char* p1, PTGNode p2, int p3, CONST char* p4, PTGNode p5, int p6, int p7));
PTGNode PTGMonTermCall ELI_ARG((CONST char* p1, CONST char* p2, PTGNode p3, int p4));
PTGNode PTGMonPlainCompCall ELI_ARG((int p1, int p2));
PTGNode PTGMonVoidAssign ELI_ARG((PTGNode p1, CONST char* p2, int p3, int p4));
PTGNode PTGMonTreeInsertion ELI_ARG((PTGNode p1, int p2));

/* prototypes for used function call insertions */

void new_line ELI_ARG((PTG_OUTPUT_FILE));
void C_outstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void P_outstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void cpp_new_line ELI_ARG((PTG_OUTPUT_FILE));
void ord_new_line ELI_ARG((PTG_OUTPUT_FILE));
void C_outstr_noquotes ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
/* ============================ */

#ifdef MONITOR
/* Monitoring support for structured values */
#define DAPTO_RESULTPTGNode(n) DAPTO_RESULT_PTR(n)
#define DAPTO_ARGPTGNode(n) DAPTO_ARG_PTR(n, PTGNode)
#endif

#endif
