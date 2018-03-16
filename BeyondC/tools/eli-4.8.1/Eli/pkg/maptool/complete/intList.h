
#ifndef _intLIST_H
#define _intLIST_H

/* include header file defining int if  is set: */
#define EMPTYHDR
#ifndef EMPTYHDR
#include ".h"
#endif
#undef EMPTYHDR

#include "intFunctionTypes.h"

typedef struct _intLE *intList;
typedef intList    *intListPtr;

struct _intLE {
int             head;
intList tail;
};

#define NULLintList             ((intList)0)
#define NullintList()   ((intList)0)
#define SingleintList(e)        (ConsintList((e),NULLintList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlintList(void);
   /* Deallocates all intLists. */
   /* Dynamic storage is allocated on first need */

extern intList ConsintList (int e, intList l);
   /* Constructs a intList of an element e and a given tail l.
    * e is the first element of the list. */

extern int HeadintList (intList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern intList TailintList (intList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthintList (intList l);
   /* Returns the number of elements in the list l. */

extern int IthElemintList (intList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern intList CopyintList (intList l, intMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern intList AppintList (intList l1, intList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern intList AppElintList (intList l, int e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterintList (intList l, int e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern intList OrderedInsertintList (intList l, int e, intCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern intListPtr RefEndConsintList (intListPtr addr, int e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern intListPtr RefEndAppintList (intListPtr addr, intList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInintList (int e, intList l, intCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern intList AddToSetintList (int e, intList l, intCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern intList AddToOrderedSetintList 
       (int e, intList l, intCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern intList MapintList (intList l, intMapFct f);
   /* Returns a new intList obtained by applying f to each element of l. */

extern int CompintList (intList l1, intList l2, intCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern int SumintList (intList l, intSumFct f, int a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlintList ();
extern intList ConsintList ();
extern int HeadintList ();
extern intList TailintList ();
extern int LengthintList ();
extern int IthElemintList ();
extern intList CopyintList ();
extern intList AppintList ();
extern intList AppElintList ();
extern void InsertAfterintList ();
extern intList OrderedInsertintList ();
extern intListPtr RefEndConsintList ();
extern intListPtr RefEndAppintList ();
extern int ElemInintList ();
extern intList AddToSetintList ();
extern intList MapintList ();
extern int CompintList ();
extern int SumintList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTintList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGintList(l)    DAPTO_ARG_PTR (l, intList)
#endif

#endif
