
#ifndef _RuleProdLIST_H
#define _RuleProdLIST_H

/* include header file defining RuleProd if RuleProd is set: */
#define EMPTYRuleProdHDR
#ifndef EMPTYHDR
#include "RuleProd.h"
#endif
#undef EMPTYRuleProdHDR

#include "RuleProdFunctionTypes.h"

typedef struct _RuleProdLE *RuleProdList;
typedef RuleProdList    *RuleProdListPtr;

struct _RuleProdLE {
RuleProd                head;
RuleProdList    tail;
};

#define NULLRuleProdList                ((RuleProdList)0)
#define NullRuleProdList()      ((RuleProdList)0)
#define SingleRuleProdList(e)   (ConsRuleProdList((e),NULLRuleProdList))

#if defined(__STDC__) || defined(__cplusplus)

extern void FinlRuleProdList(void);
   /* Deallocates all RuleProdLists. */
   /* Dynamic storage is allocated on first need */

extern RuleProdList ConsRuleProdList (RuleProd e, RuleProdList l);
   /* Constructs a RuleProdList of an element e and a given tail l.
    * e is the first element of the list. */

extern RuleProd HeadRuleProdList (RuleProdList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern RuleProdList TailRuleProdList (RuleProdList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthRuleProdList (RuleProdList l);
   /* Returns the number of elements in the list l. */

extern RuleProd IthElemRuleProdList (RuleProdList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern RuleProdList CopyRuleProdList (RuleProdList l, RuleProdMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern RuleProdList AppRuleProdList (RuleProdList l1, RuleProdList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern RuleProdList AppElRuleProdList (RuleProdList l, RuleProd e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterRuleProdList (RuleProdList l, RuleProd e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern RuleProdList OrderedInsertRuleProdList (RuleProdList l, RuleProd e, RuleProdCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern RuleProdListPtr RefEndConsRuleProdList (RuleProdListPtr addr, RuleProd e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern RuleProdListPtr RefEndAppRuleProdList (RuleProdListPtr addr, RuleProdList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInRuleProdList (RuleProd e, RuleProdList l, RuleProdCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern RuleProdList AddToSetRuleProdList (RuleProd e, RuleProdList l, RuleProdCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. */

extern RuleProdList AddToOrderedSetRuleProdList 
       (RuleProd e, RuleProdList l, RuleProdCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is checked whether it already contains e using the compare
    * function cmpfct. l is assumed to be ordered increasingly in the sense of
    * cmpfct. */

extern RuleProdList MapRuleProdList (RuleProdList l, RuleProdMapFct f);
   /* Returns a new RuleProdList obtained by applying f to each element of l. */

extern int CompRuleProdList (RuleProdList l1, RuleProdList l2, RuleProdCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern RuleProd SumRuleProdList (RuleProdList l, RuleProdSumFct f, RuleProd a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlRuleProdList ();
extern RuleProdList ConsRuleProdList ();
extern RuleProd HeadRuleProdList ();
extern RuleProdList TailRuleProdList ();
extern int LengthRuleProdList ();
extern RuleProd IthElemRuleProdList ();
extern RuleProdList CopyRuleProdList ();
extern RuleProdList AppRuleProdList ();
extern RuleProdList AppElRuleProdList ();
extern void InsertAfterRuleProdList ();
extern RuleProdList OrderedInsertRuleProdList ();
extern RuleProdListPtr RefEndConsRuleProdList ();
extern RuleProdListPtr RefEndAppRuleProdList ();
extern int ElemInRuleProdList ();
extern RuleProdList AddToSetRuleProdList ();
extern RuleProdList MapRuleProdList ();
extern int CompRuleProdList ();
extern RuleProd SumRuleProdList ();

#endif

#ifdef MONITOR
#define DAPTO_RESULTRuleProdList(l) DAPTO_RESULT_PTR(l)
#define DAPTO_ARGRuleProdList(l)    DAPTO_ARG_PTR (l, RuleProdList)
#endif

#endif
