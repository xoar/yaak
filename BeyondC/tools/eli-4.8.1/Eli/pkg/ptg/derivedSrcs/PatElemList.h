
#ifndef _PatElemLIST_H
#define _PatElemLIST_H

/* include header file defining PatElem if PatElem is set: */
#define EMPTYPatElemHDR
#ifndef EMPTYHDR
#include "PatElem.h"
#endif
#undef EMPTYPatElemHDR

#include "PatElemFunctionTypes.h"

typedef struct _PatElemLE *PatElemList;
typedef PatElemList    *PatElemListPtr;

struct _PatElemLE {
PatElem         head;
PatElemList     tail;
};

#define NULLPatElemList         ((PatElemList)0)
#define NullPatElemList()       ((PatElemList)0)
#define SinglePatElemList(e)    (ConsPatElemList((e),NULLPatElemList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlPatElemList(void);
   /* Deallocates all PatElemLists. */
   /* Dynamic storage is allocated on first need */

extern PatElemList ConsPatElemList (PatElem e, PatElemList l);
   /* Constructs a PatElemList of an element e and a given tail l.
    * e is the first element of the list. */

extern PatElem HeadPatElemList (PatElemList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern PatElemList TailPatElemList (PatElemList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthPatElemList (PatElemList l);
   /* Returns the number of elements in the list l. */

extern PatElem IthElemPatElemList (PatElemList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern PatElemList CopyPatElemList (PatElemList l, PatElemMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern PatElemList AppPatElemList (PatElemList l1, PatElemList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern PatElemList AppElPatElemList (PatElemList l, PatElem e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterPatElemList (PatElemList l, PatElem e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern PatElemList OrderedInsertPatElemList (PatElemList l, PatElem e, PatElemCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern PatElemListPtr RefEndConsPatElemList (PatElemListPtr addr, PatElem e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern PatElemListPtr RefEndAppPatElemList (PatElemListPtr addr, PatElemList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInPatElemList (PatElem e, PatElemList l, PatElemCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern PatElemList AddToSetPatElemList (PatElem e, PatElemList l, PatElemCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern PatElemList AddToOrderedSetPatElemList 
       (PatElem e, PatElemList l, PatElemCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern PatElemList MapPatElemList (PatElemList l, PatElemMapFct f);
   /* Returns a new PatElemList obtained by applying f to each element of l. */

extern int CompPatElemList (PatElemList l1, PatElemList l2, PatElemCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern PatElem SumPatElemList (PatElemList l, PatElemSumFct f, PatElem a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlPatElemList ();
extern PatElemList ConsPatElemList ();
extern PatElem HeadPatElemList ();
extern PatElemList TailPatElemList ();
extern int LengthPatElemList ();
extern PatElem IthElemPatElemList ();
extern PatElemList CopyPatElemList ();
extern PatElemList AppPatElemList ();
extern PatElemList AppElPatElemList ();
extern void InsertAfterPatElemList ();
extern PatElemList OrderedInsertPatElemList ();
extern PatElemListPtr RefEndConsPatElemList ();
extern PatElemListPtr RefEndAppPatElemList ();
extern int ElemInPatElemList ();
extern PatElemList AddToSetPatElemList ();
extern PatElemList MapPatElemList ();
extern int CompPatElemList ();
extern PatElem SumPatElemList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTPatElemList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGPatElemList(l)    DAPTO_ARG_PTR (l, PatElemList)
#endif

#endif
