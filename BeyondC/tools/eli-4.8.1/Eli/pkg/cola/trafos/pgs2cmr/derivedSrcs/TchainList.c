

#include "TchainList.h"
#include "err.h"
#include "DynSpace.h"

static POSITION coord = {0, 0};

static void*    TchainListSpace = (void *) 0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlTchainList (void)
#else
void FinlTchainList ()
#endif
{
    if (TchainListSpace)
        DynClear (TchainListSpace);
}/* FinlTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList ConsTchainList (Tchain e, TchainList l)
#else
TchainList ConsTchainList (e, l)
        Tchain  e;
        TchainList      l;
#endif
{
    TchainList  h;

    if (! TchainListSpace) TchainListSpace = InitDynSpace ();

    h = (TchainList) DynAlloc (TchainListSpace, sizeof (struct _TchainLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsTchainList */

#if defined(__STDC__) || defined(__cplusplus)
Tchain HeadTchainList (TchainList l)
#else
Tchain HeadTchainList (l)
        TchainList      l;
#endif
{
    if (l == NULLTchainList)
    {
        message (DEADLY, "HeadTchainList: empty list", 0, &coord);
        /* return ((Tchain)0); */
    } /* if */
    return (l->head);
}/* HeadTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList TailTchainList (TchainList l)
#else
TchainList TailTchainList (l)
        TchainList      l;
#endif
{
    return ((l==NULLTchainList) ? NULLTchainList : l->tail);
}/* TailTchainList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthTchainList (TchainList l)
#else
int LengthTchainList (l)
        TchainList      l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthTchainList */

#if defined(__STDC__) || defined(__cplusplus)
Tchain IthElemTchainList (TchainList l, int i)
#else
Tchain IthElemTchainList (l, i)
        TchainList      l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLTchainList))
        message (DEADLY, "IthElemTchainList: no such element", 0, &coord);
    return (l->head);
}/* IthTchainList */


#if defined(__STDC__) || defined(__cplusplus)
TchainList CopyTchainList (TchainList l, TchainMapFct cp)
#else
TchainList CopyTchainList (l, cp)
        TchainList l;
        TchainMapFct    cp;
#endif
{
    TchainList New=NULLTchainList, *addr = &New;

    while (l)
    {
        (*addr) = ConsTchainList (cp (l->head), NULLTchainList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (New);
}/* CopyTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList AppTchainList (TchainList l1, TchainList l2)
#else
TchainList AppTchainList (l1, l2)
        TchainList      l1, l2;
#endif
{
    TchainList  New;
    TchainList  *addr = &New;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsTchainList (l1->head, NULLTchainList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (New);
}/* AppTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList AppElTchainList (TchainList l, Tchain e)
#else
TchainList AppElTchainList (l, e)
        TchainList      l;
        Tchain  e;
#endif
{
    TchainList  res = l;
    if (!l)
        return (ConsTchainList (e, NULLTchainList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsTchainList (e, NULLTchainList);

    return (res);
} /* AppElTchainList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterTchainList (TchainList l, Tchain e)
#else
void InsertAfterTchainList (l, e)
        TchainList      l;
        Tchain  e;
#endif
{
    if (!l)
        message (ERROR, "InserAfterTchainList: null list", 0, &coord);
    else
        l->tail = ConsTchainList (e, l->tail);
}/* InsertAfterTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList OrderedInsertTchainList (TchainList l, Tchain e, TchainCmpFctType fcmp)
#else
TchainList OrderedInsertTchainList (l, e, fcmp)
        TchainList      l;
        Tchain  e;
        TchainCmpFctType fcmp;
#endif
{
    TchainList  p;
    if (!l)
        return (ConsTchainList (e, NULLTchainList));
    if (fcmp (e, l->head) <= 0)
        return (ConsTchainList (e, l));
    p = l;
    while (p->tail && (fcmp (e, l->tail->head) > 0))
        p = p->tail;
    p->tail = ConsTchainList (e, p->tail);
    return (l);
}/* OrderedInsertTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainListPtr RefEndConsTchainList (TchainListPtr addr, Tchain e)
#else
TchainListPtr RefEndConsTchainList (addr, e)
        TchainListPtr   addr;
        Tchain          e;
#endif
{
    if (!addr)
    {
        message (ERROR, "RefEndConsTchainList: no TchainList ref", 0, &coord);
        return (addr);
    }
    (*addr) = ConsTchainList (e, NULLTchainList);
    return (&((*addr)->tail));
}/* RefEndConsTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainListPtr RefEndAppTchainList (TchainListPtr addr, TchainList l)
#else
TchainListPtr RefEndAppTchainList (addr, l)
        TchainListPtr   addr;
        TchainList              l;
#endif
{
    if (!addr) {
        message (ERROR, "RefEndAppTchainList: no TchainList ref", 0, &coord);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppTchainList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInTchainList (Tchain e, TchainList l, TchainCmpFctType fcmp)
#else
int ElemInTchainList (e, l, fcmp)
        Tchain  e;
        TchainList      l;
        TchainCmpFctType        fcmp;
#endif
{
    while (l != NULLTchainList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList AddToSetTchainList (Tchain e, TchainList l, TchainCmpFctType fcmp)
#else
TchainList AddToSetTchainList (e, l, fcmp)
        Tchain  e;
        TchainList      l;
        TchainCmpFctType        fcmp;
#endif
{
    if (ElemInTchainList (e, l, fcmp))
        return (l);
    else
        return (ConsTchainList (e, l));
}/* AddToSetTchainList */

#if defined(__STDC__) || defined(__cplusplus)
TchainList MapTchainList (TchainList l, TchainMapFct f)
#else
TchainList MapTchainList (l, f)
        TchainList      l;
        TchainMapFct f;
#endif
{
    TchainList New = NULLTchainList;
    TchainList last = NULLTchainList;

    while (l)
    {
        if (!New) {
            New = ConsTchainList ((f (l->head)), NULLTchainList);
            last = New;
        }
        else
        {
            last->tail = ConsTchainList ((f (l->head)), NULLTchainList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (New);
}/* MapTchainList */

#if defined(__STDC__) || defined(__cplusplus)
int CompTchainList (TchainList l1, TchainList l2, TchainCmpFctType fcmp)
#else
int CompTchainList (l1, l2, fcmp)
        TchainList      l1, l2;
        TchainCmpFctType fcmp;
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
}/* CompTchainList */

#if defined(__STDC__) || defined(__cplusplus)
Tchain SumTchainList (TchainList l, TchainSumFct f, Tchain a)
#else
Tchain SumTchainList (l, f, a)
        TchainList      l;
        Tchain ((*f) ());
        Tchain  a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumTchainList */
