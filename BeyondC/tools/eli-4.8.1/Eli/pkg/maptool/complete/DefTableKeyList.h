
#ifndef _DefTableKeyLIST_H
#define _DefTableKeyLIST_H

/* include header file defining DefTableKey if deftbl is set: */
#define EMPTYdeftblHDR
#ifndef EMPTYHDR
#include "deftbl.h"
#endif
#undef EMPTYdeftblHDR

#include "DefTableKeyFunctionTypes.h"

typedef struct _DefTableKeyLE *DefTableKeyList;
typedef DefTableKeyList    *DefTableKeyListPtr;

struct _DefTableKeyLE {
DefTableKey             head;
DefTableKeyList tail;
};

#define NULLDefTableKeyList             ((DefTableKeyList)0)
#define NullDefTableKeyList()   ((DefTableKeyList)0)
#define SingleDefTableKeyList(e)        (ConsDefTableKeyList((e),NULLDefTableKeyList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlDefTableKeyList(void);
   /* Deallocates all DefTableKeyLists. */
   /* Dynamic storage is allocated on first need */

extern DefTableKeyList ConsDefTableKeyList (DefTableKey e, DefTableKeyList l);
   /* Constructs a DefTableKeyList of an element e and a given tail l.
    * e is the first element of the list. */

extern DefTableKey HeadDefTableKeyList (DefTableKeyList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern DefTableKeyList TailDefTableKeyList (DefTableKeyList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthDefTableKeyList (DefTableKeyList l);
   /* Returns the number of elements in the list l. */

extern DefTableKey IthElemDefTableKeyList (DefTableKeyList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern DefTableKeyList CopyDefTableKeyList (DefTableKeyList l, DefTableKeyMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern DefTableKeyList AppDefTableKeyList (DefTableKeyList l1, DefTableKeyList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern DefTableKeyList AppElDefTableKeyList (DefTableKeyList l, DefTableKey e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterDefTableKeyList (DefTableKeyList l, DefTableKey e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern DefTableKeyList OrderedInsertDefTableKeyList (DefTableKeyList l, DefTableKey e, DefTableKeyCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern DefTableKeyListPtr RefEndConsDefTableKeyList (DefTableKeyListPtr addr, DefTableKey e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern DefTableKeyListPtr RefEndAppDefTableKeyList (DefTableKeyListPtr addr, DefTableKeyList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInDefTableKeyList (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern DefTableKeyList AddToSetDefTableKeyList (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern DefTableKeyList AddToOrderedSetDefTableKeyList 
       (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern DefTableKeyList MapDefTableKeyList (DefTableKeyList l, DefTableKeyMapFct f);
   /* Returns a new DefTableKeyList obtained by applying f to each element of l. */

extern int CompDefTableKeyList (DefTableKeyList l1, DefTableKeyList l2, DefTableKeyCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern DefTableKey SumDefTableKeyList (DefTableKeyList l, DefTableKeySumFct f, DefTableKey a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlDefTableKeyList ();
extern DefTableKeyList ConsDefTableKeyList ();
extern DefTableKey HeadDefTableKeyList ();
extern DefTableKeyList TailDefTableKeyList ();
extern int LengthDefTableKeyList ();
extern DefTableKey IthElemDefTableKeyList ();
extern DefTableKeyList CopyDefTableKeyList ();
extern DefTableKeyList AppDefTableKeyList ();
extern DefTableKeyList AppElDefTableKeyList ();
extern void InsertAfterDefTableKeyList ();
extern DefTableKeyList OrderedInsertDefTableKeyList ();
extern DefTableKeyListPtr RefEndConsDefTableKeyList ();
extern DefTableKeyListPtr RefEndAppDefTableKeyList ();
extern int ElemInDefTableKeyList ();
extern DefTableKeyList AddToSetDefTableKeyList ();
extern DefTableKeyList MapDefTableKeyList ();
extern int CompDefTableKeyList ();
extern DefTableKey SumDefTableKeyList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTDefTableKeyList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGDefTableKeyList(l)    DAPTO_ARG_PTR (l, DefTableKeyList)
#endif

#endif
