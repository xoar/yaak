
#ifndef _SymbAttrLIST_H
#define _SymbAttrLIST_H

/* include header file defining SymbAttr if SymbAttr is set: */
#define EMPTYSymbAttrHDR
#ifndef EMPTYHDR
#include "SymbAttr.h"
#endif
#undef EMPTYSymbAttrHDR

#include "SymbAttrFunctionTypes.h"

typedef struct _SymbAttrLE *SymbAttrList;
typedef SymbAttrList    *SymbAttrListPtr;

struct _SymbAttrLE {
SymbAttr                head;
SymbAttrList    tail;
};

#define NULLSymbAttrList                ((SymbAttrList)0)
#define NullSymbAttrList()      ((SymbAttrList)0)
#define SingleSymbAttrList(e)   (ConsSymbAttrList((e),NULLSymbAttrList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlSymbAttrList(void);
   /* Deallocates all SymbAttrLists. */
   /* Dynamic storage is allocated on first need */

extern SymbAttrList ConsSymbAttrList (SymbAttr e, SymbAttrList l);
   /* Constructs a SymbAttrList of an element e and a given tail l.
    * e is the first element of the list. */

extern SymbAttr HeadSymbAttrList (SymbAttrList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern SymbAttrList TailSymbAttrList (SymbAttrList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthSymbAttrList (SymbAttrList l);
   /* Returns the number of elements in the list l. */

extern SymbAttr IthElemSymbAttrList (SymbAttrList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern SymbAttrList CopySymbAttrList (SymbAttrList l, SymbAttrMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern SymbAttrList AppSymbAttrList (SymbAttrList l1, SymbAttrList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern SymbAttrList AppElSymbAttrList (SymbAttrList l, SymbAttr e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterSymbAttrList (SymbAttrList l, SymbAttr e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern SymbAttrList OrderedInsertSymbAttrList (SymbAttrList l, SymbAttr e, SymbAttrCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern SymbAttrListPtr RefEndConsSymbAttrList (SymbAttrListPtr addr, SymbAttr e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern SymbAttrListPtr RefEndAppSymbAttrList (SymbAttrListPtr addr, SymbAttrList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInSymbAttrList (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern SymbAttrList AddToSetSymbAttrList (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern SymbAttrList AddToOrderedSetSymbAttrList 
       (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern SymbAttrList MapSymbAttrList (SymbAttrList l, SymbAttrMapFct f);
   /* Returns a new SymbAttrList obtained by applying f to each element of l. */

extern int CompSymbAttrList (SymbAttrList l1, SymbAttrList l2, SymbAttrCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern SymbAttr SumSymbAttrList (SymbAttrList l, SymbAttrSumFct f, SymbAttr a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlSymbAttrList ();
extern SymbAttrList ConsSymbAttrList ();
extern SymbAttr HeadSymbAttrList ();
extern SymbAttrList TailSymbAttrList ();
extern int LengthSymbAttrList ();
extern SymbAttr IthElemSymbAttrList ();
extern SymbAttrList CopySymbAttrList ();
extern SymbAttrList AppSymbAttrList ();
extern SymbAttrList AppElSymbAttrList ();
extern void InsertAfterSymbAttrList ();
extern SymbAttrList OrderedInsertSymbAttrList ();
extern SymbAttrListPtr RefEndConsSymbAttrList ();
extern SymbAttrListPtr RefEndAppSymbAttrList ();
extern int ElemInSymbAttrList ();
extern SymbAttrList AddToSetSymbAttrList ();
extern SymbAttrList MapSymbAttrList ();
extern int CompSymbAttrList ();
extern SymbAttr SumSymbAttrList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTSymbAttrList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGSymbAttrList(l)    DAPTO_ARG_PTR (l, SymbAttrList)
#endif

#endif
