
#ifndef _SymbolPLIST_H
#define _SymbolPLIST_H

/* include header file defining SymbolP if symbol is set: */
#define EMPTYsymbolHDR
#ifndef EMPTYHDR
#include "symbol.h"
#endif
#undef EMPTYsymbolHDR

#include "SymbolPFunctionTypes.h"

typedef struct _SymbolPLE *SymbolPList;
typedef SymbolPList    *SymbolPListPtr;

struct _SymbolPLE {
SymbolP         head;
SymbolPList     tail;
};

#define NULLSymbolPList         ((SymbolPList)0)
#define NullSymbolPList()       ((SymbolPList)0)
#define SingleSymbolPList(e)    (ConsSymbolPList((e),NULLSymbolPList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlSymbolPList(void);
   /* Deallocates all SymbolPLists. */
   /* Dynamic storage is allocated on first need */

extern SymbolPList ConsSymbolPList (SymbolP e, SymbolPList l);
   /* Constructs a SymbolPList of an element e and a given tail l.
    * e is the first element of the list. */

extern SymbolP HeadSymbolPList (SymbolPList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern SymbolPList TailSymbolPList (SymbolPList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthSymbolPList (SymbolPList l);
   /* Returns the number of elements in the list l. */

extern SymbolP IthElemSymbolPList (SymbolPList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern SymbolPList CopySymbolPList (SymbolPList l, SymbolPMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern SymbolPList AppSymbolPList (SymbolPList l1, SymbolPList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern SymbolPList AppElSymbolPList (SymbolPList l, SymbolP e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterSymbolPList (SymbolPList l, SymbolP e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern SymbolPList OrderedInsertSymbolPList (SymbolPList l, SymbolP e, SymbolPCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern SymbolPListPtr RefEndConsSymbolPList (SymbolPListPtr addr, SymbolP e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern SymbolPListPtr RefEndAppSymbolPList (SymbolPListPtr addr, SymbolPList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInSymbolPList (SymbolP e, SymbolPList l, SymbolPCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern SymbolPList AddToSetSymbolPList (SymbolP e, SymbolPList l, SymbolPCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern SymbolPList AddToOrderedSetSymbolPList 
       (SymbolP e, SymbolPList l, SymbolPCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern SymbolPList MapSymbolPList (SymbolPList l, SymbolPMapFct f);
   /* Returns a new SymbolPList obtained by applying f to each element of l. */

extern int CompSymbolPList (SymbolPList l1, SymbolPList l2, SymbolPCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern SymbolP SumSymbolPList (SymbolPList l, SymbolPSumFct f, SymbolP a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlSymbolPList ();
extern SymbolPList ConsSymbolPList ();
extern SymbolP HeadSymbolPList ();
extern SymbolPList TailSymbolPList ();
extern int LengthSymbolPList ();
extern SymbolP IthElemSymbolPList ();
extern SymbolPList CopySymbolPList ();
extern SymbolPList AppSymbolPList ();
extern SymbolPList AppElSymbolPList ();
extern void InsertAfterSymbolPList ();
extern SymbolPList OrderedInsertSymbolPList ();
extern SymbolPListPtr RefEndConsSymbolPList ();
extern SymbolPListPtr RefEndAppSymbolPList ();
extern int ElemInSymbolPList ();
extern SymbolPList AddToSetSymbolPList ();
extern SymbolPList MapSymbolPList ();
extern int CompSymbolPList ();
extern SymbolP SumSymbolPList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTSymbolPList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGSymbolPList(l)    DAPTO_ARG_PTR (l, SymbolPList)
#endif

#endif
