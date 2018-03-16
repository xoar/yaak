

#include "PatElemList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP PatElemListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlPatElemList (void)
#else
void FinlPatElemList ()
#endif
{
    if (PatElemListSpace != (DynP)0)
    {  obstack_free(&(PatElemListSpace->space), PatElemListSpace->baseptr);
       PatElemListSpace->baseptr = obstack_alloc(&(PatElemListSpace->space), 0);
    }
}/* FinlPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList ConsPatElemList (PatElem e, PatElemList l)
#else
PatElemList ConsPatElemList (e, l)
        PatElem e;
        PatElemList     l;
#endif
{
    PatElemList h;

    if (PatElemListSpace == (DynP)0)
    {   PatElemListSpace = (DynP) malloc (sizeof(Dyn));
        if (PatElemListSpace == (DynP)0)
        {  message (DEADLY, "no space for PatElemList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(PatElemListSpace->space));
        PatElemListSpace->baseptr =
                obstack_alloc(&(PatElemListSpace->space), 0);
    }

    h = (PatElemList)obstack_alloc(&(PatElemListSpace->space),
                                  sizeof (struct _PatElemLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElem HeadPatElemList (PatElemList l)
#else
PatElem HeadPatElemList (l)
        PatElemList     l;
#endif
{
    if (l == NULLPatElemList)
    {
        message (DEADLY, "HeadPatElemList: empty list", 0, (POSITION*)0);
        /* return ((PatElem)0); */
    } /* if */
    return (l->head);
}/* HeadPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList TailPatElemList (PatElemList l)
#else
PatElemList TailPatElemList (l)
        PatElemList     l;
#endif
{
    return ((l==NULLPatElemList) ? NULLPatElemList : l->tail);
}/* TailPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthPatElemList (PatElemList l)
#else
int LengthPatElemList (l)
        PatElemList     l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElem IthElemPatElemList (PatElemList l, int i)
#else
PatElem IthElemPatElemList (l, i)
        PatElemList     l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLPatElemList))
        message (DEADLY, "IthElemPatElemList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthPatElemList */


#if defined(__STDC__) || defined(__cplusplus)
PatElemList CopyPatElemList (PatElemList l, PatElemMapFct cp)
#else
PatElemList CopyPatElemList (l, cp)
        PatElemList l;
        PatElemMapFct   cp;
#endif
{
    PatElemList NewList=NULLPatElemList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsPatElemList (cp (l->head), NULLPatElemList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList AppPatElemList (PatElemList l1, PatElemList l2)
#else
PatElemList AppPatElemList (l1, l2)
        PatElemList     l1, l2;
#endif
{
    PatElemList NewList;
    PatElemList *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsPatElemList (l1->head, NULLPatElemList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList AppElPatElemList (PatElemList l, PatElem e)
#else
PatElemList AppElPatElemList (l, e)
        PatElemList     l;
        PatElem e;
#endif
{
    PatElemList res = l;
    if (!l)
        return (ConsPatElemList (e, NULLPatElemList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsPatElemList (e, NULLPatElemList);

    return (res);
} /* AppElPatElemList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterPatElemList (PatElemList l, PatElem e)
#else
void InsertAfterPatElemList (l, e)
        PatElemList     l;
        PatElem e;
#endif
{
    if (!l)
        message (DEADLY, "InsertAfterPatElemList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsPatElemList (e, l->tail);
}/* InsertAfterPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList OrderedInsertPatElemList (PatElemList l, PatElem e, PatElemCmpFctType fcmp)
#else
PatElemList OrderedInsertPatElemList (l, e, fcmp)
        PatElemList     l;
        PatElem e;
        PatElemCmpFctType fcmp;
#endif
{
    PatElemList p;
    if (!l)
        return (ConsPatElemList (e, NULLPatElemList));
    if (fcmp (e, l->head) <= 0)
        return (ConsPatElemList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsPatElemList (e, p->tail);
    return (l);
}/* OrderedInsertPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemListPtr RefEndConsPatElemList (PatElemListPtr addr, PatElem e)
#else
PatElemListPtr RefEndConsPatElemList (addr, e)
        PatElemListPtr  addr;
        PatElem         e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsPatElemList: no PatElemList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsPatElemList (e, NULLPatElemList);
    return (&((*addr)->tail));
}/* RefEndConsPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemListPtr RefEndAppPatElemList (PatElemListPtr addr, PatElemList l)
#else
PatElemListPtr RefEndAppPatElemList (addr, l)
        PatElemListPtr  addr;
        PatElemList             l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppPatElemList: no PatElemList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInPatElemList (PatElem e, PatElemList l, PatElemCmpFctType fcmp)
#else
int ElemInPatElemList (e, l, fcmp)
        PatElem e;
        PatElemList     l;
        PatElemCmpFctType       fcmp;
#endif
{
    while (l != NULLPatElemList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList AddToSetPatElemList (PatElem e, PatElemList l, PatElemCmpFctType fcmp)
#else
PatElemList AddToSetPatElemList (e, l, fcmp)
        PatElem e;
        PatElemList     l;
        PatElemCmpFctType       fcmp;
#endif
{
    if (ElemInPatElemList (e, l, fcmp))
        return (l);
    else
        return (ConsPatElemList (e, l));
}/* AddToSetPatElemList */


#if defined(__STDC__) || defined(__cplusplus)
PatElemList AddToOrderedSetPatElemList (PatElem e, PatElemList l, PatElemCmpFctType fcmp)
#else
PatElemList AddToOrderedSetPatElemList (e, l, fcmp)
        PatElem  e;
        PatElemList      l;
        PatElemCmpFctType fcmp;
#endif
{   int test;
    PatElemList  p;
    if (!l)
        return (ConsPatElemList (e, NULLPatElemList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsPatElemList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsPatElemList (e, p->tail);
    return (l);
}/* AddToOrderedSetPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElemList MapPatElemList (PatElemList l, PatElemMapFct f)
#else
PatElemList MapPatElemList (l, f)
        PatElemList     l;
        PatElemMapFct f;
#endif
{
    PatElemList NewList = NULLPatElemList;
    PatElemList last = NULLPatElemList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsPatElemList ((f (l->head)), NULLPatElemList);
            last = NewList;
        }
        else
        {
            last->tail = ConsPatElemList ((f (l->head)), NULLPatElemList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
int CompPatElemList (PatElemList l1, PatElemList l2, PatElemCmpFctType fcmp)
#else
int CompPatElemList (l1, l2, fcmp)
        PatElemList     l1, l2;
        PatElemCmpFctType fcmp;
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
}/* CompPatElemList */

#if defined(__STDC__) || defined(__cplusplus)
PatElem SumPatElemList (PatElemList l, PatElemSumFct f, PatElem a)
#else
PatElem SumPatElemList (l, f, a)
        PatElemList     l;
        PatElem ((*f) ());
        PatElem a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumPatElemList */
