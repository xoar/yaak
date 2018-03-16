

#include "ProdSymbolList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP ProdSymbolListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlProdSymbolList (void)
#else
void FinlProdSymbolList ()
#endif
{
    if (ProdSymbolListSpace != (DynP)0)
    {  obstack_free(&(ProdSymbolListSpace->space), ProdSymbolListSpace->baseptr);
       ProdSymbolListSpace->baseptr = obstack_alloc(&(ProdSymbolListSpace->space), 0);
    }
}/* FinlProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList ConsProdSymbolList (ProdSymbol e, ProdSymbolList l)
#else
ProdSymbolList ConsProdSymbolList (e, l)
        ProdSymbol      e;
        ProdSymbolList  l;
#endif
{
    ProdSymbolList      h;

    if (ProdSymbolListSpace == (DynP)0)
    {   ProdSymbolListSpace = (DynP) malloc (sizeof(Dyn));
        if (ProdSymbolListSpace == (DynP)0)
        {  message (DEADLY, "no space for ProdSymbolList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(ProdSymbolListSpace->space));
        ProdSymbolListSpace->baseptr =
                obstack_alloc(&(ProdSymbolListSpace->space), 0);
    }

    h = (ProdSymbolList)obstack_alloc(&(ProdSymbolListSpace->space),
                                  sizeof (struct _ProdSymbolLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbol HeadProdSymbolList (ProdSymbolList l)
#else
ProdSymbol HeadProdSymbolList (l)
        ProdSymbolList  l;
#endif
{
    if (l == NULLProdSymbolList)
    {
        message (DEADLY, "HeadProdSymbolList: empty list", 0, (POSITION*)0);
        /* return ((ProdSymbol)0); */
    } /* if */
    return (l->head);
}/* HeadProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList TailProdSymbolList (ProdSymbolList l)
#else
ProdSymbolList TailProdSymbolList (l)
        ProdSymbolList  l;
#endif
{
    return ((l==NULLProdSymbolList) ? NULLProdSymbolList : l->tail);
}/* TailProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthProdSymbolList (ProdSymbolList l)
#else
int LengthProdSymbolList (l)
        ProdSymbolList  l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbol IthElemProdSymbolList (ProdSymbolList l, int i)
#else
ProdSymbol IthElemProdSymbolList (l, i)
        ProdSymbolList  l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLProdSymbolList))
        message (DEADLY, "IthElemProdSymbolList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthProdSymbolList */


#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList CopyProdSymbolList (ProdSymbolList l, ProdSymbolMapFct cp)
#else
ProdSymbolList CopyProdSymbolList (l, cp)
        ProdSymbolList l;
        ProdSymbolMapFct        cp;
#endif
{
    ProdSymbolList NewList=NULLProdSymbolList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsProdSymbolList (cp (l->head), NULLProdSymbolList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList AppProdSymbolList (ProdSymbolList l1, ProdSymbolList l2)
#else
ProdSymbolList AppProdSymbolList (l1, l2)
        ProdSymbolList  l1, l2;
#endif
{
    ProdSymbolList      NewList;
    ProdSymbolList      *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsProdSymbolList (l1->head, NULLProdSymbolList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList AppElProdSymbolList (ProdSymbolList l, ProdSymbol e)
#else
ProdSymbolList AppElProdSymbolList (l, e)
        ProdSymbolList  l;
        ProdSymbol      e;
#endif
{
    ProdSymbolList      res = l;
    if (!l)
        return (ConsProdSymbolList (e, NULLProdSymbolList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsProdSymbolList (e, NULLProdSymbolList);

    return (res);
} /* AppElProdSymbolList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterProdSymbolList (ProdSymbolList l, ProdSymbol e)
#else
void InsertAfterProdSymbolList (l, e)
        ProdSymbolList  l;
        ProdSymbol      e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterProdSymbolList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsProdSymbolList (e, l->tail);
}/* InsertAfterProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList OrderedInsertProdSymbolList (ProdSymbolList l, ProdSymbol e, ProdSymbolCmpFctType fcmp)
#else
ProdSymbolList OrderedInsertProdSymbolList (l, e, fcmp)
        ProdSymbolList  l;
        ProdSymbol      e;
        ProdSymbolCmpFctType fcmp;
#endif
{
    ProdSymbolList      p;
    if (!l)
        return (ConsProdSymbolList (e, NULLProdSymbolList));
    if (fcmp (e, l->head) <= 0)
        return (ConsProdSymbolList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsProdSymbolList (e, p->tail);
    return (l);
}/* OrderedInsertProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolListPtr RefEndConsProdSymbolList (ProdSymbolListPtr addr, ProdSymbol e)
#else
ProdSymbolListPtr RefEndConsProdSymbolList (addr, e)
        ProdSymbolListPtr       addr;
        ProdSymbol              e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsProdSymbolList: no ProdSymbolList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsProdSymbolList (e, NULLProdSymbolList);
    return (&((*addr)->tail));
}/* RefEndConsProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolListPtr RefEndAppProdSymbolList (ProdSymbolListPtr addr, ProdSymbolList l)
#else
ProdSymbolListPtr RefEndAppProdSymbolList (addr, l)
        ProdSymbolListPtr       addr;
        ProdSymbolList          l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppProdSymbolList: no ProdSymbolList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInProdSymbolList (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType fcmp)
#else
int ElemInProdSymbolList (e, l, fcmp)
        ProdSymbol      e;
        ProdSymbolList  l;
        ProdSymbolCmpFctType    fcmp;
#endif
{
    while (l != NULLProdSymbolList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList AddToSetProdSymbolList (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType fcmp)
#else
ProdSymbolList AddToSetProdSymbolList (e, l, fcmp)
        ProdSymbol      e;
        ProdSymbolList  l;
        ProdSymbolCmpFctType    fcmp;
#endif
{
    if (ElemInProdSymbolList (e, l, fcmp))
        return (l);
    else
        return (ConsProdSymbolList (e, l));
}/* AddToSetProdSymbolList */


#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList AddToOrderedSetProdSymbolList (ProdSymbol e, ProdSymbolList l, ProdSymbolCmpFctType fcmp)
#else
ProdSymbolList AddToOrderedSetProdSymbolList (e, l, fcmp)
        ProdSymbol  e;
        ProdSymbolList      l;
        ProdSymbolCmpFctType fcmp;
#endif
{   int test;
    ProdSymbolList  p;
    if (!l)
        return (ConsProdSymbolList (e, NULLProdSymbolList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsProdSymbolList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsProdSymbolList (e, p->tail);
    return (l);
}/* AddToOrderedSetProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbolList MapProdSymbolList (ProdSymbolList l, ProdSymbolMapFct f)
#else
ProdSymbolList MapProdSymbolList (l, f)
        ProdSymbolList  l;
        ProdSymbolMapFct f;
#endif
{
    ProdSymbolList NewList = NULLProdSymbolList;
    ProdSymbolList last = NULLProdSymbolList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsProdSymbolList ((f (l->head)), NULLProdSymbolList);
            last = NewList;
        }
        else
        {
            last->tail = ConsProdSymbolList ((f (l->head)), NULLProdSymbolList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
int CompProdSymbolList (ProdSymbolList l1, ProdSymbolList l2, ProdSymbolCmpFctType fcmp)
#else
int CompProdSymbolList (l1, l2, fcmp)
        ProdSymbolList  l1, l2;
        ProdSymbolCmpFctType fcmp;
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
}/* CompProdSymbolList */

#if defined(__STDC__) || defined(__cplusplus)
ProdSymbol SumProdSymbolList (ProdSymbolList l, ProdSymbolSumFct f, ProdSymbol a)
#else
ProdSymbol SumProdSymbolList (l, f, a)
        ProdSymbolList  l;
        ProdSymbol ((*f) ());
        ProdSymbol      a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumProdSymbolList */
