
#ifndef _ProdSymbolLIST_H
#define _ProdSymbolLIST_H

/* include header file defining ProdSymbol if Prod is set: */
#define EMPTYProdHDR
#ifndef EMPTYHDR
#include "Prod.h"
#endif
#undef EMPTYProdHDR

#include "ProdSymbolFunctionTypes.h"

typedef struct _ProdSymbolLE *ProdSymbolList;
typedef ProdSymbolList    *ProdSymbolListPtr;

struct _ProdSymbolLE {
ProdSymbol              head;
ProdSymbolList  tail;
};

#define NULLProdSymbolList              ((ProdSymbolList)0)
#define NullProdSymbolList()    ((ProdSymbolList)0)
#define SingleProdSymbolList(e) (ConsProdSymbolList((e),NULLProdSymbolList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlProdSymbolList(void);
   /* Deallocates all ProdSymbolLists. */
   /* Dynamic storage is allocated on first need */

extern ProdSymbolList ConsProdSymbolList (ProdSymbol e, ProdSymbolList l);
   /* Constructs a ProdSymbolList of an element e and a given tail l.
    * e is the first element of the list. */

extern ProdSymbol HeadProdSymbolList (ProdSymbolList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern ProdSymbolList TailProdSymbolList (ProdSymbolList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthProdSymbolList (ProdSymbolList l);
   /* Returns the number of elements in the list l. */

extern ProdSymbol IthElemProdSymbolList (ProdSymbolList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern ProdSymbolList CopyProdSymbolList (ProdSymbolList l, ProdSymbolMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern ProdSymbolList AppProdSymbolList (ProdSymbolList l1, ProdSymbolList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern ProdSymbolList AppElProdSymbolList (ProdSymbolList l, ProdSymbol e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterProdSymbolList (ProdSymbolList l, ProdSymbol e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern ProdSymbolList OrderedInsertProdSymbolList (ProdSymbolList l, ProdSymbol e, ProdSymbolCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern ProdSymbolListPtr RefEndConsProdSymbolList (ProdSymbolListPtr addr, ProdSymbol e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern ProdSymbolListPtr RefEndAppProdSymbolList (ProdSymbolListPtr addr, ProdSymbolList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInProdSymbolList (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern ProdSymbolList AddToSetProdSymbolList (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern ProdSymbolList AddToOrderedSetProdSymbolList 
       (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern ProdSymbolList MapProdSymbolList (ProdSymbolList l, ProdSymbolMapFct f);
   /* Returns a new ProdSymbolList obtained by applying f to each element of l. */

extern int CompProdSymbolList (ProdSymbolList l1, ProdSymbolList l2, ProdSymbolCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern ProdSymbol SumProdSymbolList (ProdSymbolList l, ProdSymbolSumFct f, ProdSymbol a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlProdSymbolList ();
extern ProdSymbolList ConsProdSymbolList ();
extern ProdSymbol HeadProdSymbolList ();
extern ProdSymbolList TailProdSymbolList ();
extern int LengthProdSymbolList ();
extern ProdSymbol IthElemProdSymbolList ();
extern ProdSymbolList CopyProdSymbolList ();
extern ProdSymbolList AppProdSymbolList ();
extern ProdSymbolList AppElProdSymbolList ();
extern void InsertAfterProdSymbolList ();
extern ProdSymbolList OrderedInsertProdSymbolList ();
extern ProdSymbolListPtr RefEndConsProdSymbolList ();
extern ProdSymbolListPtr RefEndAppProdSymbolList ();
extern int ElemInProdSymbolList ();
extern ProdSymbolList AddToSetProdSymbolList ();
extern ProdSymbolList MapProdSymbolList ();
extern int CompProdSymbolList ();
extern ProdSymbol SumProdSymbolList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTProdSymbolList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGProdSymbolList(l)    DAPTO_ARG_PTR (l, ProdSymbolList)
#endif

#endif
