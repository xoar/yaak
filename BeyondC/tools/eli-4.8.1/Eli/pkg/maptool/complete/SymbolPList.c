

#include "SymbolPList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP SymbolPListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlSymbolPList (void)
#else
void FinlSymbolPList ()
#endif
{
    if (SymbolPListSpace != (DynP)0)
    {  obstack_free(&(SymbolPListSpace->space), SymbolPListSpace->baseptr);
       SymbolPListSpace->baseptr = obstack_alloc(&(SymbolPListSpace->space), 0);
    }
}/* FinlSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList ConsSymbolPList (SymbolP e, SymbolPList l)
#else
SymbolPList ConsSymbolPList (e, l)
        SymbolP e;
        SymbolPList     l;
#endif
{
    SymbolPList h;

    if (SymbolPListSpace == (DynP)0)
    {   SymbolPListSpace = (DynP) malloc (sizeof(Dyn));
        if (SymbolPListSpace == (DynP)0)
        {  message (DEADLY, "no space for SymbolPList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(SymbolPListSpace->space));
        SymbolPListSpace->baseptr =
                obstack_alloc(&(SymbolPListSpace->space), 0);
    }

    h = (SymbolPList)obstack_alloc(&(SymbolPListSpace->space),
                                  sizeof (struct _SymbolPLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolP HeadSymbolPList (SymbolPList l)
#else
SymbolP HeadSymbolPList (l)
        SymbolPList     l;
#endif
{
    if (l == NULLSymbolPList)
    {
        message (DEADLY, "HeadSymbolPList: empty list", 0, (POSITION*)0);
        /* return ((SymbolP)0); */
    } /* if */
    return (l->head);
}/* HeadSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList TailSymbolPList (SymbolPList l)
#else
SymbolPList TailSymbolPList (l)
        SymbolPList     l;
#endif
{
    return ((l==NULLSymbolPList) ? NULLSymbolPList : l->tail);
}/* TailSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthSymbolPList (SymbolPList l)
#else
int LengthSymbolPList (l)
        SymbolPList     l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolP IthElemSymbolPList (SymbolPList l, int i)
#else
SymbolP IthElemSymbolPList (l, i)
        SymbolPList     l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLSymbolPList))
        message (DEADLY, "IthElemSymbolPList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthSymbolPList */


#if defined(__STDC__) || defined(__cplusplus)
SymbolPList CopySymbolPList (SymbolPList l, SymbolPMapFct cp)
#else
SymbolPList CopySymbolPList (l, cp)
        SymbolPList l;
        SymbolPMapFct   cp;
#endif
{
    SymbolPList NewList=NULLSymbolPList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsSymbolPList (cp (l->head), NULLSymbolPList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopySymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList AppSymbolPList (SymbolPList l1, SymbolPList l2)
#else
SymbolPList AppSymbolPList (l1, l2)
        SymbolPList     l1, l2;
#endif
{
    SymbolPList NewList;
    SymbolPList *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsSymbolPList (l1->head, NULLSymbolPList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList AppElSymbolPList (SymbolPList l, SymbolP e)
#else
SymbolPList AppElSymbolPList (l, e)
        SymbolPList     l;
        SymbolP e;
#endif
{
    SymbolPList res = l;
    if (!l)
        return (ConsSymbolPList (e, NULLSymbolPList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsSymbolPList (e, NULLSymbolPList);

    return (res);
} /* AppElSymbolPList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterSymbolPList (SymbolPList l, SymbolP e)
#else
void InsertAfterSymbolPList (l, e)
        SymbolPList     l;
        SymbolP e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterSymbolPList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsSymbolPList (e, l->tail);
}/* InsertAfterSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList OrderedInsertSymbolPList (SymbolPList l, SymbolP e, SymbolPCmpFctType fcmp)
#else
SymbolPList OrderedInsertSymbolPList (l, e, fcmp)
        SymbolPList     l;
        SymbolP e;
        SymbolPCmpFctType fcmp;
#endif
{
    SymbolPList p;
    if (!l)
        return (ConsSymbolPList (e, NULLSymbolPList));
    if (fcmp (e, l->head) <= 0)
        return (ConsSymbolPList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsSymbolPList (e, p->tail);
    return (l);
}/* OrderedInsertSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPListPtr RefEndConsSymbolPList (SymbolPListPtr addr, SymbolP e)
#else
SymbolPListPtr RefEndConsSymbolPList (addr, e)
        SymbolPListPtr  addr;
        SymbolP         e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsSymbolPList: no SymbolPList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsSymbolPList (e, NULLSymbolPList);
    return (&((*addr)->tail));
}/* RefEndConsSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPListPtr RefEndAppSymbolPList (SymbolPListPtr addr, SymbolPList l)
#else
SymbolPListPtr RefEndAppSymbolPList (addr, l)
        SymbolPListPtr  addr;
        SymbolPList             l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppSymbolPList: no SymbolPList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInSymbolPList (SymbolP e, SymbolPList l, SymbolPCmpFctType fcmp)
#else
int ElemInSymbolPList (e, l, fcmp)
        SymbolP e;
        SymbolPList     l;
        SymbolPCmpFctType       fcmp;
#endif
{
    while (l != NULLSymbolPList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList AddToSetSymbolPList (SymbolP e, SymbolPList l, SymbolPCmpFctType fcmp)
#else
SymbolPList AddToSetSymbolPList (e, l, fcmp)
        SymbolP e;
        SymbolPList     l;
        SymbolPCmpFctType       fcmp;
#endif
{
    if (ElemInSymbolPList (e, l, fcmp))
        return (l);
    else
        return (ConsSymbolPList (e, l));
}/* AddToSetSymbolPList */


#if defined(__STDC__) || defined(__cplusplus)
SymbolPList AddToOrderedSetSymbolPList (SymbolP e, SymbolPList l, SymbolPCmpFctType fcmp)
#else
SymbolPList AddToOrderedSetSymbolPList (e, l, fcmp)
        SymbolP  e;
        SymbolPList      l;
        SymbolPCmpFctType fcmp;
#endif
{   int test;
    SymbolPList  p;
    if (!l)
        return (ConsSymbolPList (e, NULLSymbolPList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsSymbolPList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsSymbolPList (e, p->tail);
    return (l);
}/* AddToOrderedSetSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolPList MapSymbolPList (SymbolPList l, SymbolPMapFct f)
#else
SymbolPList MapSymbolPList (l, f)
        SymbolPList     l;
        SymbolPMapFct f;
#endif
{
    SymbolPList NewList = NULLSymbolPList;
    SymbolPList last = NULLSymbolPList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsSymbolPList ((f (l->head)), NULLSymbolPList);
            last = NewList;
        }
        else
        {
            last->tail = ConsSymbolPList ((f (l->head)), NULLSymbolPList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
int CompSymbolPList (SymbolPList l1, SymbolPList l2, SymbolPCmpFctType fcmp)
#else
int CompSymbolPList (l1, l2, fcmp)
        SymbolPList     l1, l2;
        SymbolPCmpFctType fcmp;
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
}/* CompSymbolPList */

#if defined(__STDC__) || defined(__cplusplus)
SymbolP SumSymbolPList (SymbolPList l, SymbolPSumFct f, SymbolP a)
#else
SymbolP SumSymbolPList (l, f, a)
        SymbolPList     l;
        SymbolP ((*f) ());
        SymbolP a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumSymbolPList */
