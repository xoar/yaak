

#include "ElementList.h"
#include "err.h"
#include "obstack.h"

typedef struct {
  Obstack space;
  void *baseptr;
} Dyn, *DynP;

static DynP ElementListSpace = (DynP)0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlElementList (void)
#else
void FinlElementList ()
#endif
{
    if (ElementListSpace != (DynP)0)
    {  obstack_free(&(ElementListSpace->space), ElementListSpace->baseptr);
       ElementListSpace->baseptr = obstack_alloc(&(ElementListSpace->space), 0);
    }
}/* FinlElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList ConsElementList (Element e, ElementList l)
#else
ElementList ConsElementList (e, l)
        Element e;
        ElementList     l;
#endif
{
    ElementList h;

    if (ElementListSpace == (DynP)0)
    {   ElementListSpace = (DynP) malloc (sizeof(Dyn));
        if (ElementListSpace == (DynP)0)
        {  message (DEADLY, "no space for ElementList", 0, (POSITION*)0);
           exit (1);
        }
        obstack_init(&(ElementListSpace->space));
        ElementListSpace->baseptr =
                obstack_alloc(&(ElementListSpace->space), 0);
    }

    h = (ElementList)obstack_alloc(&(ElementListSpace->space),
                                  sizeof (struct _ElementLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsElementList */

#if defined(__STDC__) || defined(__cplusplus)
Element HeadElementList (ElementList l)
#else
Element HeadElementList (l)
        ElementList     l;
#endif
{
    if (l == NULLElementList)
    {
        message (DEADLY, "HeadElementList: empty list", 0, (POSITION*)0);
        /* return ((Element)0); */
    } /* if */
    return (l->head);
}/* HeadElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList TailElementList (ElementList l)
#else
ElementList TailElementList (l)
        ElementList     l;
#endif
{
    return ((l==NULLElementList) ? NULLElementList : l->tail);
}/* TailElementList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthElementList (ElementList l)
#else
int LengthElementList (l)
        ElementList     l;
#endif
{
    int res = 0;

    for (; l; l = l->tail)
        res++;
    return (res);
}/* LengthElementList */

#if defined(__STDC__) || defined(__cplusplus)
Element IthElemElementList (ElementList l, int i)
#else
Element IthElemElementList (l, i)
        ElementList     l;
        int     i;
#endif
{
    while ((i>1) && l)
    {
        i--;
        l = l->tail;
    }

    if ((i<=0) || (l==NULLElementList))
        message (DEADLY, "IthElemElementList: no such element",
                 0, (POSITION*)0);
    return (l->head);
}/* IthElementList */


#if defined(__STDC__) || defined(__cplusplus)
ElementList CopyElementList (ElementList l, ElementMapFct cp)
#else
ElementList CopyElementList (l, cp)
        ElementList l;
        ElementMapFct   cp;
#endif
{
    ElementList NewList=NULLElementList, *addr = &NewList;

    while (l)
    {
        (*addr) = ConsElementList (cp (l->head), NULLElementList);
        addr = &((*addr)->tail);
        l = l->tail;
    }
    return (NewList);
}/* CopyElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList AppElementList (ElementList l1, ElementList l2)
#else
ElementList AppElementList (l1, l2)
        ElementList     l1, l2;
#endif
{
    ElementList NewList;
    ElementList *addr = &NewList;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
        (*addr) = ConsElementList (l1->head, NULLElementList);
        addr = &((*addr)->tail);
        l1 = l1->tail;
    }
    (*addr) = l2;

    return (NewList);
}/* AppElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList AppElElementList (ElementList l, Element e)
#else
ElementList AppElElementList (l, e)
        ElementList     l;
        Element e;
#endif
{
    ElementList res = l;
    if (!l)
        return (ConsElementList (e, NULLElementList));

    while (l->tail)
        l = l->tail;
    l->tail = ConsElementList (e, NULLElementList);

    return (res);
} /* AppElElementList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterElementList (ElementList l, Element e)
#else
void InsertAfterElementList (l, e)
        ElementList     l;
        Element e;
#endif
{
    if (!l)
        message (DEADLY, "InserAfterElementList: null list", 0, (POSITION*)0);
    else
        l->tail = ConsElementList (e, l->tail);
}/* InsertAfterElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList OrderedInsertElementList (ElementList l, Element e, ElementCmpFctType fcmp)
#else
ElementList OrderedInsertElementList (l, e, fcmp)
        ElementList     l;
        Element e;
        ElementCmpFctType fcmp;
#endif
{
    ElementList p;
    if (!l)
        return (ConsElementList (e, NULLElementList));
    if (fcmp (e, l->head) <= 0)
        return (ConsElementList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
        p = p->tail;
    p->tail = ConsElementList (e, p->tail);
    return (l);
}/* OrderedInsertElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementListPtr RefEndConsElementList (ElementListPtr addr, Element e)
#else
ElementListPtr RefEndConsElementList (addr, e)
        ElementListPtr  addr;
        Element         e;
#endif
{
    if (!addr)
    {
        message (DEADLY, "RefEndConsElementList: no ElementList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    (*addr) = ConsElementList (e, NULLElementList);
    return (&((*addr)->tail));
}/* RefEndConsElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementListPtr RefEndAppElementList (ElementListPtr addr, ElementList l)
#else
ElementListPtr RefEndAppElementList (addr, l)
        ElementListPtr  addr;
        ElementList             l;
#endif
{
    if (!addr) {
        message (DEADLY, "RefEndAppElementList: no ElementList ref",
                 0, (POSITION*)0);
        return (addr);
    }
    if (!l)
        return addr;

    (*addr) = l;

    while (l->tail)
        l = l->tail;
    return (&(l->tail));
}/* RefEndAppElementList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInElementList (Element e, ElementList l, ElementCmpFctType fcmp)
#else
int ElemInElementList (e, l, fcmp)
        Element e;
        ElementList     l;
        ElementCmpFctType       fcmp;
#endif
{
    while (l != NULLElementList) {
        if (fcmp (e, l->head) == 0)
            return (1);
        l = l->tail;
    }
    return (0);
}/* ElemInElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList AddToSetElementList (Element e, ElementList l, ElementCmpFctType fcmp)
#else
ElementList AddToSetElementList (e, l, fcmp)
        Element e;
        ElementList     l;
        ElementCmpFctType       fcmp;
#endif
{
    if (ElemInElementList (e, l, fcmp))
        return (l);
    else
        return (ConsElementList (e, l));
}/* AddToSetElementList */


#if defined(__STDC__) || defined(__cplusplus)
ElementList AddToOrderedSetElementList (Element e, ElementList l, ElementCmpFctType fcmp)
#else
ElementList AddToOrderedSetElementList (e, l, fcmp)
        Element  e;
        ElementList      l;
        ElementCmpFctType fcmp;
#endif
{   int test;
    ElementList  p;
    if (!l)
        return (ConsElementList (e, NULLElementList));
    if ((test = fcmp (e, l->head)) < 0)
        return (ConsElementList (e, l));
    if (test == 0) return l;
    p = l;
    while (p->tail && ((test = fcmp (e, p->tail->head)) > 0))
        p = p->tail;
    if (test) p->tail = ConsElementList (e, p->tail);
    return (l);
}/* AddToOrderedSetElementList */

#if defined(__STDC__) || defined(__cplusplus)
ElementList MapElementList (ElementList l, ElementMapFct f)
#else
ElementList MapElementList (l, f)
        ElementList     l;
        ElementMapFct f;
#endif
{
    ElementList NewList = NULLElementList;
    ElementList last = NULLElementList;

    while (l)
    {
        if (!NewList) {
            NewList = ConsElementList ((f (l->head)), NULLElementList);
            last = NewList;
        }
        else
        {
            last->tail = ConsElementList ((f (l->head)), NULLElementList);
            last = last->tail;
        }
        l = l->tail;
    }
    return (NewList);
}/* MapElementList */

#if defined(__STDC__) || defined(__cplusplus)
int CompElementList (ElementList l1, ElementList l2, ElementCmpFctType fcmp)
#else
int CompElementList (l1, l2, fcmp)
        ElementList     l1, l2;
        ElementCmpFctType fcmp;
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
}/* CompElementList */

#if defined(__STDC__) || defined(__cplusplus)
Element SumElementList (ElementList l, ElementSumFct f, Element a)
#else
Element SumElementList (l, f, a)
        ElementList     l;
        Element ((*f) ());
        Element a;
#endif
{
    while (l) {
        a = (f (a, l->head));
        l = l->tail;
    }
    return (a);
}/* SumElementList */
