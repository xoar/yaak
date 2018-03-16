

#include "DefTableKeyList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP DefTableKeyListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlDefTableKeyList (void)
#else
void FinlDefTableKeyList ()
#endif
{
    if (DefTableKeyListSpace != (DynP)0)
    {  obstack_free(&(DefTableKeyListSpace->space), DefTableKeyListSpace->baseptr);
       DefTableKeyListSpace->baseptr = obstack_alloc(&(DefTableKeyListSpace->space), 0);
    }
}/* FinlDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList ConsDefTableKeyList (DefTableKey e, DefTableKeyList l)
#else
DefTableKeyList ConsDefTableKeyList (e, l)
        DefTableKey     e;
        DefTableKeyList l;
#endif
{
    DefTableKeyList     h;

    if (DefTableKeyListSpace == (DynP)0)
    {   DefTableKeyListSpace = (DynP) malloc (sizeof(Dyn));
        if (DefTableKeyListSpace == (DynP)0)
        {  message (DEADLY, "no space for DefTableKeyList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(DefTableKeyListSpace->space));
        DefTableKeyListSpace->baseptr =
                obstack_alloc(&(DefTableKeyListSpace->space), 0);
    }

    h = (DefTableKeyList)obstack_alloc(&(DefTableKeyListSpace->space),
                                  sizeof (struct _DefTableKeyLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKey HeadDefTableKeyList (DefTableKeyList l)
#else
DefTableKey HeadDefTableKeyList (l)
        DefTableKeyList l;
#endif
{
    if (l == NULLDefTableKeyList)
    {
        message (DEADLY, "HeadDefTableKeyList: empty list", 0, (POSITION*)0);
        /* return ((DefTableKey)0); */
    } /* if */
    return (l->head);
}/* HeadDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList TailDefTableKeyList (DefTableKeyList l)
#else
DefTableKeyList TailDefTableKeyList (l)
        DefTableKeyList l;
#endif
{
    return ((l==NULLDefTableKeyList) ? NULLDefTableKeyList : l->tail);
}/* TailDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthDefTableKeyList (DefTableKeyList l)
#else
int LengthDefTableKeyList (l)
        DefTableKeyList l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKey IthElemDefTableKeyList (DefTableKeyList l, int i)
#else
DefTableKey IthElemDefTableKeyList (l, i)
        DefTableKeyList l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLDefTableKeyList))
        message (DEADLY, "IthElemDefTableKeyList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthDefTableKeyList */


#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList CopyDefTableKeyList (DefTableKeyList l, DefTableKeyMapFct cp)
#else
DefTableKeyList CopyDefTableKeyList (l, cp)
        DefTableKeyList l;
        DefTableKeyMapFct       cp;
#endif
{
    DefTableKeyList NewList=NULLDefTableKeyList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsDefTableKeyList (cp (l->head), NULLDefTableKeyList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList AppDefTableKeyList (DefTableKeyList l1, DefTableKeyList l2)
#else
DefTableKeyList AppDefTableKeyList (l1, l2)
        DefTableKeyList l1, l2;
#endif
{
    DefTableKeyList     NewList;
    DefTableKeyList     *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsDefTableKeyList (l1->head, NULLDefTableKeyList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList AppElDefTableKeyList (DefTableKeyList l, DefTableKey e)
#else
DefTableKeyList AppElDefTableKeyList (l, e)
        DefTableKeyList l;
        DefTableKey     e;
#endif
{
    DefTableKeyList     res = l;
    if (!l)
        return (ConsDefTableKeyList (e, NULLDefTableKeyList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsDefTableKeyList (e, NULLDefTableKeyList);

    return (res);
} /* AppElDefTableKeyList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterDefTableKeyList (DefTableKeyList l, DefTableKey e)
#else
void InsertAfterDefTableKeyList (l, e)
        DefTableKeyList l;
        DefTableKey     e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterDefTableKeyList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsDefTableKeyList (e, l->tail);
}/* InsertAfterDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList OrderedInsertDefTableKeyList (DefTableKeyList l, DefTableKey e, DefTableKeyCmpFctType fcmp)
#else
DefTableKeyList OrderedInsertDefTableKeyList (l, e, fcmp)
        DefTableKeyList l;
        DefTableKey     e;
        DefTableKeyCmpFctType fcmp;
#endif
{
    DefTableKeyList     p;
    if (!l)
        return (ConsDefTableKeyList (e, NULLDefTableKeyList));
    if (fcmp (e, l->head) <= 0)
        return (ConsDefTableKeyList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsDefTableKeyList (e, p->tail);
    return (l);
}/* OrderedInsertDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyListPtr RefEndConsDefTableKeyList (DefTableKeyListPtr addr, DefTableKey e)
#else
DefTableKeyListPtr RefEndConsDefTableKeyList (addr, e)
        DefTableKeyListPtr      addr;
        DefTableKey             e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsDefTableKeyList: no DefTableKeyList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsDefTableKeyList (e, NULLDefTableKeyList);
    return (&((*addr)->tail));
}/* RefEndConsDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyListPtr RefEndAppDefTableKeyList (DefTableKeyListPtr addr, DefTableKeyList l)
#else
DefTableKeyListPtr RefEndAppDefTableKeyList (addr, l)
        DefTableKeyListPtr      addr;
        DefTableKeyList         l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppDefTableKeyList: no DefTableKeyList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInDefTableKeyList (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType fcmp)
#else
int ElemInDefTableKeyList (e, l, fcmp)
        DefTableKey     e;
        DefTableKeyList l;
        DefTableKeyCmpFctType   fcmp;
#endif
{
    while (l != NULLDefTableKeyList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList AddToSetDefTableKeyList (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType fcmp)
#else
DefTableKeyList AddToSetDefTableKeyList (e, l, fcmp)
        DefTableKey     e;
        DefTableKeyList l;
        DefTableKeyCmpFctType   fcmp;
#endif
{
    if (ElemInDefTableKeyList (e, l, fcmp))
        return (l);
    else
        return (ConsDefTableKeyList (e, l));
}/* AddToSetDefTableKeyList */


#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList AddToOrderedSetDefTableKeyList (DefTableKey e, DefTableKeyList l, DefTableKeyCmpFctType fcmp)
#else
DefTableKeyList AddToOrderedSetDefTableKeyList (e, l, fcmp)
        DefTableKey  e;
        DefTableKeyList      l;
        DefTableKeyCmpFctType fcmp;
#endif
{   int test;
    DefTableKeyList  p;
    if (!l)
        return (ConsDefTableKeyList (e, NULLDefTableKeyList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsDefTableKeyList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsDefTableKeyList (e, p->tail);
    return (l);
}/* AddToOrderedSetDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKeyList MapDefTableKeyList (DefTableKeyList l, DefTableKeyMapFct f)
#else
DefTableKeyList MapDefTableKeyList (l, f)
        DefTableKeyList l;
        DefTableKeyMapFct f;
#endif
{
    DefTableKeyList NewList = NULLDefTableKeyList;
    DefTableKeyList last = NULLDefTableKeyList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsDefTableKeyList ((f (l->head)), NULLDefTableKeyList);
            last = NewList;
        }
        else
        {
            last->tail = ConsDefTableKeyList ((f (l->head)), NULLDefTableKeyList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
int CompDefTableKeyList (DefTableKeyList l1, DefTableKeyList l2, DefTableKeyCmpFctType fcmp)
#else
int CompDefTableKeyList (l1, l2, fcmp)
        DefTableKeyList l1, l2;
        DefTableKeyCmpFctType fcmp;
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
}/* CompDefTableKeyList */

#if defined(__STDC__) || defined(__cplusplus)
DefTableKey SumDefTableKeyList (DefTableKeyList l, DefTableKeySumFct f, DefTableKey a)
#else
DefTableKey SumDefTableKeyList (l, f, a)
        DefTableKeyList l;
        DefTableKey ((*f) ());
        DefTableKey     a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumDefTableKeyList */
