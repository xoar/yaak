
#ifndef _PTGNodeLIST_H
#define _PTGNodeLIST_H

/* include header file defining PTGNode if ptg_gen is set: */
#define EMPTYptg_genHDR
#ifndef EMPTYHDR
#include "ptg_gen.h"
#endif
#undef EMPTYptg_genHDR

#include "VoidPtrList.h"

typedef VoidPtrList     PTGNodeList;
typedef VoidPtrList    *PTGNodeListPtr;
typedef VoidPtrCmpFctType     PTGNodeCmpFctType;

#define NULLPTGNodeList         ((PTGNodeList)0)
#define NullPTGNodeList()       ((PTGNodeList)0)
#define SinglePTGNodeList(e)    (ConsPTGNodeList((e),NULLPTGNodeList))

#define FinlPTGNodeList         FinlVoidPtrList

#define ConsPTGNodeList(e,l)    ConsVoidPtrList ((VoidPtr)(e),(l))

#define HeadPTGNodeList(l)      ((PTGNode)(HeadVoidPtrList (l)))

#define TailPTGNodeList(l)      TailVoidPtrList (l)

#define LengthPTGNodeList(l)    LengthVoidPtrList (l)

#define IthElemPTGNodeList(l,i) ((PTGNode)(IthElemVoidPtrList (l, i)))

#define CopyPTGNodeList(l,cp)   CopyVoidPtrList (l, cp)

#define AppPTGNodeList(l1,l2)   AppVoidPtrList (l1, l2)

#define AppElPTGNodeList(l,e)   AppElVoidPtrList (l, (VoidPtr)e)

#define InsertAfterPTGNodeList(l,e) \
        InsertAfterVoidPtrList (l, (VoidPtr)e)

#define OrderedInsertPTGNodeList(l,e,fcmp) \
        OrderedInsertVoidPtrList (l, (VoidPtr)e, (VoidPtrCmpFctType)fcmp)

#define RefEndConsPTGNodeList(addr,e) \
        RefEndConsVoidPtrList (addr, (VoidPtr)e)

#define RefEndAppPTGNodeList(addr,l) \
        RefEndAppVoidPtrList (addr, l)

#define ElemInPTGNodeList(e,l,cmpfct) \
        ElemInVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define AddToSetPTGNodeList(e,l,cmpfct) \
        AddToSetVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define AddToOrderedSetPTGNodeList(e,l,cmpfct) \
        AddToOrderedSetVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define MapPTGNodeList(l,f) \
        MapVoidPtrList (l,(VoidPtrMapFct)f)

#define CompPTGNodeList(l1,l2,f) \
        CompVoidPtrList (l1, l2, (VoidPtrCmpFctType)f)

#define SumPTGNodeList(l,f,a) \
        SumVoidPtrList (l, (VoidPtrSumFct)f, (VoidPtr)a)

#ifdef MONITOR
#define DAPTO_RESULTPTGNodeList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGPTGNodeList(l)    DAPTO_ARG_PTR (l, PTGNodeList)
#endif

#endif
