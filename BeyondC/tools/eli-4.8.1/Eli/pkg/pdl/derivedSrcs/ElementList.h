
#ifndef _ElementLIST_H
#define _ElementLIST_H

/* include header file defining Element if Element is set: */
#define EMPTYElementHDR
#ifndef EMPTYHDR
#include "Element.h"
#endif
#undef EMPTYElementHDR

#include "ElementFunctionTypes.h"

typedef struct _ElementLE *ElementList;
typedef ElementList    *ElementListPtr;

struct _ElementLE {
Element         head;
ElementList     tail;
};

#define NULLElementList         ((ElementList)0)
#define NullElementList()       ((ElementList)0)
#define SingleElementList(e)    (ConsElementList((e),NULLElementList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlElementList(void);
   /* Deallocates all ElementLists. */
   /* Dynamic storage is allocated on first need */

extern ElementList ConsElementList (Element e, ElementList l);
   /* Constructs a ElementList of an element e and a given tail l.
    * e is the first element of the list. */

extern Element HeadElementList (ElementList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern ElementList TailElementList (ElementList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthElementList (ElementList l);
   /* Returns the number of elements in the list l. */

extern Element IthElemElementList (ElementList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern ElementList CopyElementList (ElementList l, ElementMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern ElementList AppElementList (ElementList l1, ElementList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern ElementList AppElElementList (ElementList l, Element e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterElementList (ElementList l, Element e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern ElementList OrderedInsertElementList (ElementList l, Element e, ElementCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern ElementListPtr RefEndConsElementList (ElementListPtr addr, Element e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern ElementListPtr RefEndAppElementList (ElementListPtr addr, ElementList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInElementList (Element e, ElementList l, ElementCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern ElementList AddToSetElementList (Element e, ElementList l, ElementCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern ElementList AddToOrderedSetElementList 
       (Element e, ElementList l, ElementCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern ElementList MapElementList (ElementList l, ElementMapFct f);
   /* Returns a new ElementList obtained by applying f to each element of l. */

extern int CompElementList (ElementList l1, ElementList l2, ElementCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern Element SumElementList (ElementList l, ElementSumFct f, Element a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlElementList ();
extern ElementList ConsElementList ();
extern Element HeadElementList ();
extern ElementList TailElementList ();
extern int LengthElementList ();
extern Element IthElemElementList ();
extern ElementList CopyElementList ();
extern ElementList AppElementList ();
extern ElementList AppElElementList ();
extern void InsertAfterElementList ();
extern ElementList OrderedInsertElementList ();
extern ElementListPtr RefEndConsElementList ();
extern ElementListPtr RefEndAppElementList ();
extern int ElemInElementList ();
extern ElementList AddToSetElementList ();
extern ElementList MapElementList ();
extern int CompElementList ();
extern Element SumElementList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTElementList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGElementList(l)    DAPTO_ARG_PTR (l, ElementList)
#endif

#endif
