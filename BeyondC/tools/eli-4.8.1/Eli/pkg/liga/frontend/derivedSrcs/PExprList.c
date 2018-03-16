

#include "PExprList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP PExprListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlPExprList (void)
#else
void FinlPExprList ()
#endif
{
    if (PExprListSpace != (DynP)0)
    {  obstack_free(&(PExprListSpace->space), PExprListSpace->baseptr);
       PExprListSpace->baseptr = obstack_alloc(&(PExprListSpace->space), 0);
    }
}/* FinlPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList ConsPExprList (PExpr e, PExprList l)
#else
PExprList ConsPExprList (e, l)
        PExpr   e;
        PExprList       l;
#endif
{
    PExprList   h;

    if (PExprListSpace == (DynP)0)
    {   PExprListSpace = (DynP) malloc (sizeof(Dyn));
        if (PExprListSpace == (DynP)0)
        {  message (DEADLY, "no space for PExprList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(PExprListSpace->space));
        PExprListSpace->baseptr =
                obstack_alloc(&(PExprListSpace->space), 0);
    }

    h = (PExprList)obstack_alloc(&(PExprListSpace->space),
                                  sizeof (struct _PExprLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExpr HeadPExprList (PExprList l)
#else
PExpr HeadPExprList (l)
        PExprList       l;
#endif
{
    if (l == NULLPExprList)
    {
        message (DEADLY, "HeadPExprList: empty list", 0, (POSITION*)0);
        /* return ((PExpr)0); */
    } /* if */
    return (l->head);
}/* HeadPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList TailPExprList (PExprList l)
#else
PExprList TailPExprList (l)
        PExprList       l;
#endif
{
    return ((l==NULLPExprList) ? NULLPExprList : l->tail);
}/* TailPExprList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthPExprList (PExprList l)
#else
int LengthPExprList (l)
        PExprList       l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExpr IthElemPExprList (PExprList l, int i)
#else
PExpr IthElemPExprList (l, i)
        PExprList       l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLPExprList))
        message (DEADLY, "IthElemPExprList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthPExprList */


#if defined(__STDC__) || defined(__cplusplus)
PExprList CopyPExprList (PExprList l, PExprMapFct cp)
#else
PExprList CopyPExprList (l, cp)
        PExprList l;
        PExprMapFct     cp;
#endif
{
    PExprList NewList=NULLPExprList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsPExprList (cp (l->head), NULLPExprList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList AppPExprList (PExprList l1, PExprList l2)
#else
PExprList AppPExprList (l1, l2)
        PExprList       l1, l2;
#endif
{
    PExprList   NewList;
    PExprList   *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsPExprList (l1->head, NULLPExprList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList AppElPExprList (PExprList l, PExpr e)
#else
PExprList AppElPExprList (l, e)
        PExprList       l;
        PExpr   e;
#endif
{
    PExprList   res = l;
    if (!l)
        return (ConsPExprList (e, NULLPExprList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsPExprList (e, NULLPExprList);

    return (res);
} /* AppElPExprList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterPExprList (PExprList l, PExpr e)
#else
void InsertAfterPExprList (l, e)
        PExprList       l;
        PExpr   e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterPExprList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsPExprList (e, l->tail);
}/* InsertAfterPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList OrderedInsertPExprList (PExprList l, PExpr e, PExprCmpFctType fcmp)
#else
PExprList OrderedInsertPExprList (l, e, fcmp)
        PExprList       l;
        PExpr   e;
        PExprCmpFctType fcmp;
#endif
{
    PExprList   p;
    if (!l)
        return (ConsPExprList (e, NULLPExprList));
    if (fcmp (e, l->head) <= 0)
        return (ConsPExprList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsPExprList (e, p->tail);
    return (l);
}/* OrderedInsertPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprListPtr RefEndConsPExprList (PExprListPtr addr, PExpr e)
#else
PExprListPtr RefEndConsPExprList (addr, e)
        PExprListPtr    addr;
        PExpr           e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsPExprList: no PExprList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsPExprList (e, NULLPExprList);
    return (&((*addr)->tail));
}/* RefEndConsPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprListPtr RefEndAppPExprList (PExprListPtr addr, PExprList l)
#else
PExprListPtr RefEndAppPExprList (addr, l)
        PExprListPtr    addr;
        PExprList               l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppPExprList: no PExprList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppPExprList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInPExprList (PExpr e, PExprList l, PExprCmpFctType fcmp)
#else
int ElemInPExprList (e, l, fcmp)
        PExpr   e;
        PExprList       l;
        PExprCmpFctType fcmp;
#endif
{
    while (l != NULLPExprList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList AddToSetPExprList (PExpr e, PExprList l, PExprCmpFctType fcmp)
#else
PExprList AddToSetPExprList (e, l, fcmp)
        PExpr   e;
        PExprList       l;
        PExprCmpFctType fcmp;
#endif
{
    if (ElemInPExprList (e, l, fcmp))
        return (l);
    else
        return (ConsPExprList (e, l));
}/* AddToSetPExprList */


#if defined(__STDC__) || defined(__cplusplus)
PExprList AddToOrderedSetPExprList (PExpr e, PExprList l, PExprCmpFctType fcmp)
#else
PExprList AddToOrderedSetPExprList (e, l, fcmp)
        PExpr  e;
        PExprList      l;
        PExprCmpFctType fcmp;
#endif
{   int test;
    PExprList  p;
    if (!l)
        return (ConsPExprList (e, NULLPExprList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsPExprList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsPExprList (e, p->tail);
    return (l);
}/* AddToOrderedSetPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExprList MapPExprList (PExprList l, PExprMapFct f)
#else
PExprList MapPExprList (l, f)
        PExprList       l;
        PExprMapFct f;
#endif
{
    PExprList NewList = NULLPExprList;
    PExprList last = NULLPExprList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsPExprList ((f (l->head)), NULLPExprList);
            last = NewList;
        }
        else
        {
            last->tail = ConsPExprList ((f (l->head)), NULLPExprList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapPExprList */

#if defined(__STDC__) || defined(__cplusplus)
int CompPExprList (PExprList l1, PExprList l2, PExprCmpFctType fcmp)
#else
int CompPExprList (l1, l2, fcmp)
        PExprList       l1, l2;
        PExprCmpFctType fcmp;
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
}/* CompPExprList */

#if defined(__STDC__) || defined(__cplusplus)
PExpr SumPExprList (PExprList l, PExprSumFct f, PExpr a)
#else
PExpr SumPExprList (l, f, a)
        PExprList       l;
        PExpr ((*f) ());
        PExpr   a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumPExprList */
