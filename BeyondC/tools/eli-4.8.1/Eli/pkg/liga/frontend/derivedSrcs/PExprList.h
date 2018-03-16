
#ifndef _PExprLIST_H
#define _PExprLIST_H

/* include header file defining PExpr if ExprRepr is set: */
#define EMPTYExprReprHDR
#ifndef EMPTYHDR
#include "ExprRepr.h"
#endif
#undef EMPTYExprReprHDR

#include "PExprFunctionTypes.h"

typedef struct _PExprLE *PExprList;
typedef PExprList    *PExprListPtr;

struct _PExprLE {
PExpr           head;
PExprList       tail;
};

#define NULLPExprList           ((PExprList)0)
#define NullPExprList() ((PExprList)0)
#define SinglePExprList(e)      (ConsPExprList((e),NULLPExprList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlPExprList(void);
   /* Deallocates all PExprLists. */
   /* Dynamic storage is allocated on first need */

extern PExprList ConsPExprList (PExpr e, PExprList l);
   /* Constructs a PExprList of an element e and a given tail l.
    * e is the first element of the list. */

extern PExpr HeadPExprList (PExprList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern PExprList TailPExprList (PExprList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthPExprList (PExprList l);
   /* Returns the number of elements in the list l. */

extern PExpr IthElemPExprList (PExprList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern PExprList CopyPExprList (PExprList l, PExprMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern PExprList AppPExprList (PExprList l1, PExprList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern PExprList AppElPExprList (PExprList l, PExpr e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterPExprList (PExprList l, PExpr e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern PExprList OrderedInsertPExprList (PExprList l, PExpr e, PExprCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern PExprListPtr RefEndConsPExprList (PExprListPtr addr, PExpr e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern PExprListPtr RefEndAppPExprList (PExprListPtr addr, PExprList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInPExprList (PExpr e, PExprList l, PExprCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern PExprList AddToSetPExprList (PExpr e, PExprList l, PExprCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern PExprList AddToOrderedSetPExprList 
       (PExpr e, PExprList l, PExprCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern PExprList MapPExprList (PExprList l, PExprMapFct f);
   /* Returns a new PExprList obtained by applying f to each element of l. */

extern int CompPExprList (PExprList l1, PExprList l2, PExprCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern PExpr SumPExprList (PExprList l, PExprSumFct f, PExpr a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlPExprList ();
extern PExprList ConsPExprList ();
extern PExpr HeadPExprList ();
extern PExprList TailPExprList ();
extern int LengthPExprList ();
extern PExpr IthElemPExprList ();
extern PExprList CopyPExprList ();
extern PExprList AppPExprList ();
extern PExprList AppElPExprList ();
extern void InsertAfterPExprList ();
extern PExprList OrderedInsertPExprList ();
extern PExprListPtr RefEndConsPExprList ();
extern PExprListPtr RefEndAppPExprList ();
extern int ElemInPExprList ();
extern PExprList AddToSetPExprList ();
extern PExprList MapPExprList ();
extern int CompPExprList ();
extern PExpr SumPExprList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTPExprList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGPExprList(l)    DAPTO_ARG_PTR (l, PExprList)
#endif

#endif
