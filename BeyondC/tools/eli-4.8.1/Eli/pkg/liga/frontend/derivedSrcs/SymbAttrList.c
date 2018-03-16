

#include "SymbAttrList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP SymbAttrListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlSymbAttrList (void)
#else
void FinlSymbAttrList ()
#endif
{
    if (SymbAttrListSpace != (DynP)0)
    {  obstack_free(&(SymbAttrListSpace->space), SymbAttrListSpace->baseptr);
       SymbAttrListSpace->baseptr = obstack_alloc(&(SymbAttrListSpace->space), 0);
    }
}/* FinlSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList ConsSymbAttrList (SymbAttr e, SymbAttrList l)
#else
SymbAttrList ConsSymbAttrList (e, l)
        SymbAttr        e;
        SymbAttrList    l;
#endif
{
    SymbAttrList        h;

    if (SymbAttrListSpace == (DynP)0)
    {   SymbAttrListSpace = (DynP) malloc (sizeof(Dyn));
        if (SymbAttrListSpace == (DynP)0)
        {  message (DEADLY, "no space for SymbAttrList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(SymbAttrListSpace->space));
        SymbAttrListSpace->baseptr =
                obstack_alloc(&(SymbAttrListSpace->space), 0);
    }

    h = (SymbAttrList)obstack_alloc(&(SymbAttrListSpace->space),
                                  sizeof (struct _SymbAttrLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttr HeadSymbAttrList (SymbAttrList l)
#else
SymbAttr HeadSymbAttrList (l)
        SymbAttrList    l;
#endif
{
    if (l == NULLSymbAttrList)
    {
        message (DEADLY, "HeadSymbAttrList: empty list", 0, (POSITION*)0);
        /* return ((SymbAttr)0); */
    } /* if */
    return (l->head);
}/* HeadSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList TailSymbAttrList (SymbAttrList l)
#else
SymbAttrList TailSymbAttrList (l)
        SymbAttrList    l;
#endif
{
    return ((l==NULLSymbAttrList) ? NULLSymbAttrList : l->tail);
}/* TailSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthSymbAttrList (SymbAttrList l)
#else
int LengthSymbAttrList (l)
        SymbAttrList    l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttr IthElemSymbAttrList (SymbAttrList l, int i)
#else
SymbAttr IthElemSymbAttrList (l, i)
        SymbAttrList    l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLSymbAttrList))
        message (DEADLY, "IthElemSymbAttrList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthSymbAttrList */


#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList CopySymbAttrList (SymbAttrList l, SymbAttrMapFct cp)
#else
SymbAttrList CopySymbAttrList (l, cp)
        SymbAttrList l;
        SymbAttrMapFct  cp;
#endif
{
    SymbAttrList NewList=NULLSymbAttrList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsSymbAttrList (cp (l->head), NULLSymbAttrList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopySymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList AppSymbAttrList (SymbAttrList l1, SymbAttrList l2)
#else
SymbAttrList AppSymbAttrList (l1, l2)
        SymbAttrList    l1, l2;
#endif
{
    SymbAttrList        NewList;
    SymbAttrList        *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsSymbAttrList (l1->head, NULLSymbAttrList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList AppElSymbAttrList (SymbAttrList l, SymbAttr e)
#else
SymbAttrList AppElSymbAttrList (l, e)
        SymbAttrList    l;
        SymbAttr        e;
#endif
{
    SymbAttrList        res = l;
    if (!l)
        return (ConsSymbAttrList (e, NULLSymbAttrList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsSymbAttrList (e, NULLSymbAttrList);

    return (res);
} /* AppElSymbAttrList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterSymbAttrList (SymbAttrList l, SymbAttr e)
#else
void InsertAfterSymbAttrList (l, e)
        SymbAttrList    l;
        SymbAttr        e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterSymbAttrList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsSymbAttrList (e, l->tail);
}/* InsertAfterSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList OrderedInsertSymbAttrList (SymbAttrList l, SymbAttr e, SymbAttrCmpFctType fcmp)
#else
SymbAttrList OrderedInsertSymbAttrList (l, e, fcmp)
        SymbAttrList    l;
        SymbAttr        e;
        SymbAttrCmpFctType fcmp;
#endif
{
    SymbAttrList        p;
    if (!l)
        return (ConsSymbAttrList (e, NULLSymbAttrList));
    if (fcmp (e, l->head) <= 0)
        return (ConsSymbAttrList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsSymbAttrList (e, p->tail);
    return (l);
}/* OrderedInsertSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrListPtr RefEndConsSymbAttrList (SymbAttrListPtr addr, SymbAttr e)
#else
SymbAttrListPtr RefEndConsSymbAttrList (addr, e)
        SymbAttrListPtr addr;
        SymbAttr                e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsSymbAttrList: no SymbAttrList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsSymbAttrList (e, NULLSymbAttrList);
    return (&((*addr)->tail));
}/* RefEndConsSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrListPtr RefEndAppSymbAttrList (SymbAttrListPtr addr, SymbAttrList l)
#else
SymbAttrListPtr RefEndAppSymbAttrList (addr, l)
        SymbAttrListPtr addr;
        SymbAttrList            l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppSymbAttrList: no SymbAttrList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInSymbAttrList (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType fcmp)
#else
int ElemInSymbAttrList (e, l, fcmp)
        SymbAttr        e;
        SymbAttrList    l;
        SymbAttrCmpFctType      fcmp;
#endif
{
    while (l != NULLSymbAttrList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList AddToSetSymbAttrList (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType fcmp)
#else
SymbAttrList AddToSetSymbAttrList (e, l, fcmp)
        SymbAttr        e;
        SymbAttrList    l;
        SymbAttrCmpFctType      fcmp;
#endif
{
    if (ElemInSymbAttrList (e, l, fcmp))
        return (l);
    else
        return (ConsSymbAttrList (e, l));
}/* AddToSetSymbAttrList */


#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList AddToOrderedSetSymbAttrList (SymbAttr e, SymbAttrList l, SymbAttrCmpFctType fcmp)
#else
SymbAttrList AddToOrderedSetSymbAttrList (e, l, fcmp)
        SymbAttr  e;
        SymbAttrList      l;
        SymbAttrCmpFctType fcmp;
#endif
{   int test;
    SymbAttrList  p;
    if (!l)
        return (ConsSymbAttrList (e, NULLSymbAttrList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsSymbAttrList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsSymbAttrList (e, p->tail);
    return (l);
}/* AddToOrderedSetSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttrList MapSymbAttrList (SymbAttrList l, SymbAttrMapFct f)
#else
SymbAttrList MapSymbAttrList (l, f)
        SymbAttrList    l;
        SymbAttrMapFct f;
#endif
{
    SymbAttrList NewList = NULLSymbAttrList;
    SymbAttrList last = NULLSymbAttrList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsSymbAttrList ((f (l->head)), NULLSymbAttrList);
            last = NewList;
        }
        else
        {
            last->tail = ConsSymbAttrList ((f (l->head)), NULLSymbAttrList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
int CompSymbAttrList (SymbAttrList l1, SymbAttrList l2, SymbAttrCmpFctType fcmp)
#else
int CompSymbAttrList (l1, l2, fcmp)
        SymbAttrList    l1, l2;
        SymbAttrCmpFctType fcmp;
#endif
{
    int res = 0;
    while (l1 && l2 && (res == 0)) {
        res = (fcmp (l1->head, l2->head));
        l1 = l1->tail;
        l2 = l2->tail;
    }
    if (l1 && !l2)
        return (1);
    if (!l1 && l2)
        return (-1);
    return (res);
}/* CompSymbAttrList */

#if defined(__STDC__) || defined(__cplusplus)
SymbAttr SumSymbAttrList (SymbAttrList l, SymbAttrSumFct f, SymbAttr a)
#else
SymbAttr SumSymbAttrList (l, f, a)
        SymbAttrList    l;
        SymbAttr ((*f) ());
        SymbAttr        a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumSymbAttrList */
