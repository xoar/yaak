
#ifndef _TchainLIST_H
#define _TchainLIST_H

/* include header file defining Tchain if chain is set: */
#define EMPTYchainHDR
#ifndef EMPTYHDR
#include "chain.h"
#endif

typedef struct _TchainLE *TchainList;
typedef TchainList    *TchainListPtr;

#if defined(__STDC__) || defined(__cplusplus)
typedef Tchain (*TchainMapFct)(Tchain);
#else
typedef Tchain (*TchainMapFct)();
#endif
   /* Type of functions that computes a Tchain value from a Tchain value;
      supplied as arguments to calls of CopyTchainList, MapTchainList*/

#if defined(__STDC__) || defined(__cplusplus)
typedef int (*TchainCmpFctType)(Tchain, Tchain);
#else
typedef int (*TchainCmpFctType)();
#endif
   /* Type of functions that compare two Tchain values; it yields
    * -1 if the left argument is less than the right,
    *  0 if the arguments are equal,
    * 1  if the left argument is greater than the right;
    * If Tchain is char* strcmp() can be used here)
    * supplied as arguments to calls of OrderedInsertTchainList,
    * ElemInTchainList, AddToSetTchainList, CompTchainList.
    */

#if defined(__STDC__) || defined(__cplusplus)
typedef Tchain (*TchainSumFct)(Tchain, Tchain);
#else
typedef Tchain (*TchainSumFct)();
#endif
   /* A binary function on List Elements. This can be the sum of two
    * Elements. If so, a call to SumPL returns the sum of the List. */

struct _TchainLE {
Tchain          head;
TchainList      tail;
};

#define NULLTchainList          ((TchainList)0)
#define NullTchainList()        ((TchainList)0)


#if defined(__STDC__) || defined(__cplusplus)

extern void FinlTchainList(void);
   /* Deallocates all TchainLists. */
   /* Dynamic storage is allocated on first need */

extern TchainList ConsTchainList (Tchain e, TchainList l);
   /* Constructs a TchainList of an element e and a given tail l.
    * e is the first element of the list. */

extern Tchain HeadTchainList (TchainList l);
   /* Returns the first element of the list l.
    * The list l must not be empty. */

extern TchainList TailTchainList (TchainList l);
   /* Returns the tail of the list l.
    * If l is empty, an empty list is returned. */

extern int LengthTchainList (TchainList l);
   /* Returns the number of elements in the list l. */

extern Tchain IthElemTchainList (TchainList l, int i);
   /* Returns the i-th element of the List l. The head of l
    * is referred to as 1. If the value of
    * i is greater than the length of the list, an error
    * is reported and the program exits.
    */

extern TchainList CopyTchainList (TchainList l, TchainMapFct cp);
   /* Copies the list l. Elements are copied by calls of cp. */

extern TchainList AppTchainList (TchainList l1, TchainList l2);
   /* Concatenates two lists l1 and l2. The resulting list contains l2 at
    * the end of a copy of list l1. */

extern TchainList AppElTchainList (TchainList l, Tchain e);
   /* Appends an element e to the list l.
    * The list l is not copied, it is modified as a side-effect
    * of this function. */

extern void InsertAfterTchainList (TchainList l, Tchain e);
   /* This function requires a non-empty list l. The element e is inserted
    * just after the first element of l. 
    * The list l is modified as a side-effect of this function. */

extern TchainList OrderedInsertTchainList (TchainList l, Tchain e, TchainCmpFctType fcmp);
   /* Inserts the element e into the list l maintaining l in
    * ascending order with respect to the compare fcmp. 
    * The list l is modified as a side-effect of this function. */

extern TchainListPtr RefEndConsTchainList (TchainListPtr addr, Tchain e);
   /* Appends an element e to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern TchainListPtr RefEndAppTchainList (TchainListPtr addr, TchainList l);
   /* Appends a list l to the end of a list given by its address addr.
    * The address where the next element may be appended is returned.
    * The list is modified as a side-effect of this function. */

extern int ElemInTchainList (Tchain e, TchainList l, TchainCmpFctType cmpfct);
   /* This function returns true (1) iff the element e is in the List l.
    * List elements are compared by the function cmpfct. */

extern TchainList AddToSetTchainList (Tchain e, TchainList l, TchainCmpFctType cmpfct);
   /* A list is returned that has e as an element.
    * l is check whether it already contains e using the compare
    * function cmpfct. */

extern TchainList MapTchainList (TchainList l, TchainMapFct f);
   /* Returns a new TchainList obtained by applying f to each element of l. */

extern int CompTchainList (TchainList l1, TchainList l2, TchainCmpFctType f);
   /* Compares the lists l1 and l2 lexicographically by applying f
    * to the corresponding elements. */

extern Tchain SumTchainList (TchainList l, TchainSumFct f, Tchain a);
   /* Applies the binary function f to the elements of the List:
    *   f( f(... f(a, e1), e2, ...), en)
    * If l is empty a is returned. */

#else

extern void FinlTchainList ();
extern TchainList ConsTchainList ();
extern Tchain HeadTchainList ();
extern TchainList TailTchainList ();
extern int LengthTchainList ();
extern Tchain IthElemTchainList ();
extern TchainList CopyTchainList ();
extern TchainList AppTchainList ();
extern TchainList AppElTchainList ();
extern void InsertAfterTchainList ();
extern TchainList OrderedInsertTchainList ();
extern TchainListPtr RefEndConsTchainList ();
extern TchainListPtr RefEndAppTchainList ();
extern int ElemInTchainList ();
extern TchainList AddToSetTchainList ();
extern TchainList MapTchainList ();
extern int CompTchainList ();
extern Tchain SumTchainList ();

#endif
#endif
