

#include "RuleProdList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP RuleProdListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlRuleProdList (void)
#else
void FinlRuleProdList ()
#endif
{
    if (RuleProdListSpace != (DynP)0)
    {  obstack_free(&(RuleProdListSpace->space), RuleProdListSpace->baseptr);
       RuleProdListSpace->baseptr = obstack_alloc(&(RuleProdListSpace->space), 0);
    }
}/* FinlRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList ConsRuleProdList (RuleProd e, RuleProdList l)
#else
RuleProdList ConsRuleProdList (e, l)
        RuleProd        e;
        RuleProdList    l;
#endif
{
    RuleProdList        h;

    if (RuleProdListSpace == (DynP)0)
    {   RuleProdListSpace = (DynP) malloc (sizeof(Dyn));
        if (RuleProdListSpace == (DynP)0)
        {  message (DEADLY, "no space for RuleProdList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(RuleProdListSpace->space));
        RuleProdListSpace->baseptr =
                obstack_alloc(&(RuleProdListSpace->space), 0);
    }

    h = (RuleProdList)obstack_alloc(&(RuleProdListSpace->space),
                                  sizeof (struct _RuleProdLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProd HeadRuleProdList (RuleProdList l)
#else
RuleProd HeadRuleProdList (l)
        RuleProdList    l;
#endif
{
    if (l == NULLRuleProdList)
    {
        message (DEADLY, "HeadRuleProdList: empty list", 0, (POSITION*)0);
        /* return ((RuleProd)0); */
    } /* if */
    return (l->head);
}/* HeadRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList TailRuleProdList (RuleProdList l)
#else
RuleProdList TailRuleProdList (l)
        RuleProdList    l;
#endif
{
    return ((l==NULLRuleProdList) ? NULLRuleProdList : l->tail);
}/* TailRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthRuleProdList (RuleProdList l)
#else
int LengthRuleProdList (l)
        RuleProdList    l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProd IthElemRuleProdList (RuleProdList l, int i)
#else
RuleProd IthElemRuleProdList (l, i)
        RuleProdList    l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLRuleProdList))
        message (DEADLY, "IthElemRuleProdList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthRuleProdList */


#if defined(__STDC__) || defined(__cplusplus)
RuleProdList CopyRuleProdList (RuleProdList l, RuleProdMapFct cp)
#else
RuleProdList CopyRuleProdList (l, cp)
        RuleProdList l;
        RuleProdMapFct  cp;
#endif
{
    RuleProdList NewList=NULLRuleProdList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsRuleProdList (cp (l->head), NULLRuleProdList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList AppRuleProdList (RuleProdList l1, RuleProdList l2)
#else
RuleProdList AppRuleProdList (l1, l2)
        RuleProdList    l1, l2;
#endif
{
    RuleProdList        NewList;
    RuleProdList        *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsRuleProdList (l1->head, NULLRuleProdList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList AppElRuleProdList (RuleProdList l, RuleProd e)
#else
RuleProdList AppElRuleProdList (l, e)
        RuleProdList    l;
        RuleProd        e;
#endif
{
    RuleProdList        res = l;
    if (!l)
        return (ConsRuleProdList (e, NULLRuleProdList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsRuleProdList (e, NULLRuleProdList);

    return (res);
} /* AppElRuleProdList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterRuleProdList (RuleProdList l, RuleProd e)
#else
void InsertAfterRuleProdList (l, e)
        RuleProdList    l;
        RuleProd        e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterRuleProdList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsRuleProdList (e, l->tail);
}/* InsertAfterRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList OrderedInsertRuleProdList (RuleProdList l, RuleProd e, RuleProdCmpFctType fcmp)
#else
RuleProdList OrderedInsertRuleProdList (l, e, fcmp)
        RuleProdList    l;
        RuleProd        e;
        RuleProdCmpFctType fcmp;
#endif
{
    RuleProdList        p;
    if (!l)
        return (ConsRuleProdList (e, NULLRuleProdList));
    if (fcmp (e, l->head) <= 0)
        return (ConsRuleProdList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsRuleProdList (e, p->tail);
    return (l);
}/* OrderedInsertRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdListPtr RefEndConsRuleProdList (RuleProdListPtr addr, RuleProd e)
#else
RuleProdListPtr RefEndConsRuleProdList (addr, e)
        RuleProdListPtr addr;
        RuleProd                e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsRuleProdList: no RuleProdList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsRuleProdList (e, NULLRuleProdList);
    return (&((*addr)->tail));
}/* RefEndConsRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdListPtr RefEndAppRuleProdList (RuleProdListPtr addr, RuleProdList l)
#else
RuleProdListPtr RefEndAppRuleProdList (addr, l)
        RuleProdListPtr addr;
        RuleProdList            l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppRuleProdList: no RuleProdList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInRuleProdList (RuleProd e, RuleProdList l, RuleProdCmpFctType fcmp)
#else
int ElemInRuleProdList (e, l, fcmp)
        RuleProd        e;
        RuleProdList    l;
        RuleProdCmpFctType      fcmp;
#endif
{
    while (l != NULLRuleProdList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList AddToSetRuleProdList (RuleProd e, RuleProdList l, RuleProdCmpFctType fcmp)
#else
RuleProdList AddToSetRuleProdList (e, l, fcmp)
        RuleProd        e;
        RuleProdList    l;
        RuleProdCmpFctType      fcmp;
#endif
{
    if (ElemInRuleProdList (e, l, fcmp))
        return (l);
    else
        return (ConsRuleProdList (e, l));
}/* AddToSetRuleProdList */


#if defined(__STDC__) || defined(__cplusplus)
RuleProdList AddToOrderedSetRuleProdList (RuleProd e, RuleProdList l, RuleProdCmpFctType fcmp)
#else
RuleProdList AddToOrderedSetRuleProdList (e, l, fcmp)
        RuleProd  e;
        RuleProdList      l;
        RuleProdCmpFctType fcmp;
#endif
{   int test;
    RuleProdList  p;
    if (!l)
        return (ConsRuleProdList (e, NULLRuleProdList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsRuleProdList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsRuleProdList (e, p->tail);
    return (l);
}/* AddToOrderedSetRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProdList MapRuleProdList (RuleProdList l, RuleProdMapFct f)
#else
RuleProdList MapRuleProdList (l, f)
        RuleProdList    l;
        RuleProdMapFct f;
#endif
{
    RuleProdList NewList = NULLRuleProdList;
    RuleProdList last = NULLRuleProdList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsRuleProdList ((f (l->head)), NULLRuleProdList);
            last = NewList;
        }
        else
        {
            last->tail = ConsRuleProdList ((f (l->head)), NULLRuleProdList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
int CompRuleProdList (RuleProdList l1, RuleProdList l2, RuleProdCmpFctType fcmp)
#else
int CompRuleProdList (l1, l2, fcmp)
        RuleProdList    l1, l2;
        RuleProdCmpFctType fcmp;
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
}/* CompRuleProdList */

#if defined(__STDC__) || defined(__cplusplus)
RuleProd SumRuleProdList (RuleProdList l, RuleProdSumFct f, RuleProd a)
#else
RuleProd SumRuleProdList (l, f, a)
        RuleProdList    l;
        RuleProd ((*f) ());
        RuleProd        a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumRuleProdList */
