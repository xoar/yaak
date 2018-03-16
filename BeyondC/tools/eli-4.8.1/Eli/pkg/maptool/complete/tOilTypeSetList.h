
#ifndef _tOilTypeSetLIST_H
#define _tOilTypeSetLIST_H

/* include header file defining tOilTypeSet if oiladt2 is set: */
#define EMPTYoiladt2HDR
#ifndef EMPTYHDR
#include "oiladt2.h"
#endif
#undef EMPTYoiladt2HDR

#include "VoidPtrList.h"

typedef VoidPtrList     tOilTypeSetList;
typedef VoidPtrList    *tOilTypeSetListPtr;
typedef VoidPtrCmpFctType     tOilTypeSetCmpFctType;

#define NULLtOilTypeSetList             ((tOilTypeSetList)0)
#define NulltOilTypeSetList()   ((tOilTypeSetList)0)
#define SingletOilTypeSetList(e)        (ConstOilTypeSetList((e),NULLtOilTypeSetList))

#define FinltOilTypeSetList             FinlVoidPtrList

#define ConstOilTypeSetList(e,l)        ConsVoidPtrList ((VoidPtr)(e),(l))

#define HeadtOilTypeSetList(l)  ((tOilTypeSet)(HeadVoidPtrList (l)))

#define TailtOilTypeSetList(l)  TailVoidPtrList (l)

#define LengthtOilTypeSetList(l)        LengthVoidPtrList (l)

#define IthElemtOilTypeSetList(l,i)     ((tOilTypeSet)(IthElemVoidPtrList (l, i)))

#define CopytOilTypeSetList(l,cp)       CopyVoidPtrList (l, cp)

#define ApptOilTypeSetList(l1,l2)       AppVoidPtrList (l1, l2)

#define AppEltOilTypeSetList(l,e)       AppElVoidPtrList (l, (VoidPtr)e)

#define InsertAftertOilTypeSetList(l,e) \
        InsertAfterVoidPtrList (l, (VoidPtr)e)

#define OrderedInserttOilTypeSetList(l,e,fcmp) \
        OrderedInsertVoidPtrList (l, (VoidPtr)e, (VoidPtrCmpFctType)fcmp)

#define RefEndConstOilTypeSetList(addr,e) \
        RefEndConsVoidPtrList (addr, (VoidPtr)e)

#define RefEndApptOilTypeSetList(addr,l) \
        RefEndAppVoidPtrList (addr, l)

#define ElemIntOilTypeSetList(e,l,cmpfct) \
        ElemInVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define AddToSettOilTypeSetList(e,l,cmpfct) \
        AddToSetVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define AddToOrderedSettOilTypeSetList(e,l,cmpfct) \
        AddToOrderedSetVoidPtrList ((VoidPtr)e, l, (VoidPtrCmpFctType)cmpfct)

#define MaptOilTypeSetList(l,f) \
        MapVoidPtrList (l,(VoidPtrMapFct)f)

#define ComptOilTypeSetList(l1,l2,f) \
        CompVoidPtrList (l1, l2, (VoidPtrCmpFctType)f)

#define SumtOilTypeSetList(l,f,a) \
        SumVoidPtrList (l, (VoidPtrSumFct)f, (VoidPtr)a)

#ifdef MONITOR
#define DAPTO_RESULTtOilTypeSetList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGtOilTypeSetList(l)    DAPTO_ARG_PTR (l, tOilTypeSetList)
#endif

#endif
