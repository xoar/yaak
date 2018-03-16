

#include "intList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP intListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlintList (void)
#else
void FinlintList ()
#endif
{
    if (intListSpace != (DynP)0)
    {  obstack_free(&(intListSpace->space), intListSpace->baseptr);
       intListSpace->baseptr = obstack_alloc(&(intListSpace->space), 0);
    }
}/* FinlintList */

#if defined(__STDC__) || defined(__cplusplus)
intList ConsintList (int e, intList l)
#else
intList ConsintList (e, l)
        int     e;
        intList l;
#endif
{
    intList     h;

    if (intListSpace == (DynP)0)
    {   intListSpace = (DynP) malloc (sizeof(Dyn));
        if (intListSpace == (DynP)0)
        {  message (DEADLY, "no space for intList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(intListSpace->space));
        intListSpace->baseptr =
                obstack_alloc(&(intListSpace->space), 0);
    }

    h = (intList)obstack_alloc(&(intListSpace->space),
                                  sizeof (struct _intLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsintList */

#if defined(__STDC__) || defined(__cplusplus)
int HeadintList (intList l)
#else
int HeadintList (l)
        intList l;
#endif
{
    if (l == NULLintList)
    {
        message (DEADLY, "HeadintList: empty list", 0, (POSITION*)0);
        /* return ((int)0); */
    } /* if */
    return (l->head);
}/* HeadintList */

#if defined(__STDC__) || defined(__cplusplus)
intList TailintList (intList l)
#else
intList TailintList (l)
        intList l;
#endif
{
    return ((l==NULLintList) ? NULLintList : l->tail);
}/* TailintList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthintList (intList l)
#else
int LengthintList (l)
        intList l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthintList */

#if defined(__STDC__) || defined(__cplusplus)
int IthElemintList (intList l, int i)
#else
int IthElemintList (l, i)
        intList l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLintList))
        message (DEADLY, "IthElemintList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthintList */


#if defined(__STDC__) || defined(__cplusplus)
intList CopyintList (intList l, intMapFct cp)
#else
intList CopyintList (l, cp)
        intList l;
        intMapFct       cp;
#endif
{
    intList NewList=NULLintList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsintList (cp (l->head), NULLintList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyintList */

#if defined(__STDC__) || defined(__cplusplus)
intList AppintList (intList l1, intList l2)
#else
intList AppintList (l1, l2)
        intList l1, l2;
#endif
{
    intList     NewList;
    intList     *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsintList (l1->head, NULLintList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppintList */

#if defined(__STDC__) || defined(__cplusplus)
intList AppElintList (intList l, int e)
#else
intList AppElintList (l, e)
        intList l;
        int     e;
#endif
{
    intList     res = l;
    if (!l)
        return (ConsintList (e, NULLintList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsintList (e, NULLintList);

    return (res);
} /* AppElintList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterintList (intList l, int e)
#else
void InsertAfterintList (l, e)
        intList l;
        int     e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterintList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsintList (e, l->tail);
}/* InsertAfterintList */

#if defined(__STDC__) || defined(__cplusplus)
intList OrderedInsertintList (intList l, int e, intCmpFctType fcmp)
#else
intList OrderedInsertintList (l, e, fcmp)
        intList l;
        int     e;
        intCmpFctType fcmp;
#endif
{
    intList     p;
    if (!l)
        return (ConsintList (e, NULLintList));
    if (fcmp (e, l->head) <= 0)
        return (ConsintList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsintList (e, p->tail);
    return (l);
}/* OrderedInsertintList */

#if defined(__STDC__) || defined(__cplusplus)
intListPtr RefEndConsintList (intListPtr addr, int e)
#else
intListPtr RefEndConsintList (addr, e)
        intListPtr      addr;
        int             e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsintList: no intList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsintList (e, NULLintList);
    return (&((*addr)->tail));
}/* RefEndConsintList */

#if defined(__STDC__) || defined(__cplusplus)
intListPtr RefEndAppintList (intListPtr addr, intList l)
#else
intListPtr RefEndAppintList (addr, l)
        intListPtr      addr;
        intList         l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppintList: no intList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppintList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInintList (int e, intList l, intCmpFctType fcmp)
#else
int ElemInintList (e, l, fcmp)
        int     e;
        intList l;
        intCmpFctType   fcmp;
#endif
{
    while (l != NULLintList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInintList */

#if defined(__STDC__) || defined(__cplusplus)
intList AddToSetintList (int e, intList l, intCmpFctType fcmp)
#else
intList AddToSetintList (e, l, fcmp)
        int     e;
        intList l;
        intCmpFctType   fcmp;
#endif
{
    if (ElemInintList (e, l, fcmp))
        return (l);
    else
        return (ConsintList (e, l));
}/* AddToSetintList */


#if defined(__STDC__) || defined(__cplusplus)
intList AddToOrderedSetintList (int e, intList l, intCmpFctType fcmp)
#else
intList AddToOrderedSetintList (e, l, fcmp)
        int  e;
        intList      l;
        intCmpFctType fcmp;
#endif
{   int test;
    intList  p;
    if (!l)
        return (ConsintList (e, NULLintList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsintList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsintList (e, p->tail);
    return (l);
}/* AddToOrderedSetintList */

#if defined(__STDC__) || defined(__cplusplus)
intList MapintList (intList l, intMapFct f)
#else
intList MapintList (l, f)
        intList l;
        intMapFct f;
#endif
{
    intList NewList = NULLintList;
    intList last = NULLintList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsintList ((f (l->head)), NULLintList);
            last = NewList;
        }
        else
        {
            last->tail = ConsintList ((f (l->head)), NULLintList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapintList */

#if defined(__STDC__) || defined(__cplusplus)
int CompintList (intList l1, intList l2, intCmpFctType fcmp)
#else
int CompintList (l1, l2, fcmp)
        intList l1, l2;
        intCmpFctType fcmp;
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
}/* CompintList */

#if defined(__STDC__) || defined(__cplusplus)
int SumintList (intList l, intSumFct f, int a)
#else
int SumintList (l, f, a)
        intList l;
        int ((*f) ());
        int     a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumintList */
