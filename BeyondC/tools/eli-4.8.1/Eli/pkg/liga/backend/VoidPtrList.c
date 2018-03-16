/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
#include "VoidPtrList.h"
#include "err.h"
#include "DynSpace.h"

static POSITION coord = {0, 0};

void*	VoidPtrListSpace = (void *) 0;

#if defined(__STDC__) || defined(__cplusplus)
void FinlVoidPtrList (void)
#else
void FinlVoidPtrList ()
#endif
{
    if (VoidPtrListSpace)
	DynClear (VoidPtrListSpace);
}/* FinlVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList ConsVoidPtrList (VoidPtr e, VoidPtrList l)
#else
VoidPtrList ConsVoidPtrList (e, l)
	VoidPtr	e;
	VoidPtrList	l;
#endif
{
    VoidPtrList	h;

    if (! VoidPtrListSpace) VoidPtrListSpace = InitDynSpace ();

    h = (VoidPtrList) DynAlloc (VoidPtrListSpace, sizeof (struct _VoidPtrLE));
    h->head = e;
    h->tail= l;
    return (h);
}/* ConsVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtr HeadVoidPtrList (VoidPtrList l)
#else
VoidPtr HeadVoidPtrList (l)
	VoidPtrList	l;
#endif
{
    if (l == NULLVoidPtrList)
    {
	message (DEADLY, "HeadVoidPtrList: empty list", 0, &coord);
	/* return ((VoidPtr)0); */
    } /* if */
    return (l->head);
}/* HeadVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList TailVoidPtrList (VoidPtrList l)
#else
VoidPtrList TailVoidPtrList (l)
	VoidPtrList	l;
#endif
{
    return ((l==NULLVoidPtrList) ? NULLVoidPtrList : l->tail);
}/* TailVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
int LengthVoidPtrList (VoidPtrList l)
#else
int LengthVoidPtrList (l)
	VoidPtrList	l;
#endif
{
    int	res = 0;

    for (; l; l = l->tail)
	res++;
    return (res);
}/* LengthVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtr IthElemVoidPtrList (VoidPtrList l, int i)
#else
VoidPtr IthElemVoidPtrList (l, i)
	VoidPtrList	l;
	int	i;
#endif
{
    while ((i>1) && l)
    {
	i--;
	l = l->tail;
    }

    if ((i<=0) || (l==NULLVoidPtrList))
	message (DEADLY, "IthElemVoidPtrList: no such element", 0, &coord);
    return (l->head);
}/* IthVoidPtrList */


#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList CopyVoidPtrList (VoidPtrList l, VoidPtrMapFct cp)
#else
VoidPtrList CopyVoidPtrList (l, cp)
	VoidPtrList l;
	VoidPtrMapFct	cp;
#endif
{
    VoidPtrList New=NULLVoidPtrList, *addr = &New;

    while (l)
    {
	(*addr) = ConsVoidPtrList (cp (l->head), NULLVoidPtrList);
	addr = &((*addr)->tail);
	l = l->tail;
    }
    return (New);
}/* CopyVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList AppVoidPtrList (VoidPtrList l1, VoidPtrList l2)
#else
VoidPtrList AppVoidPtrList (l1, l2)
	VoidPtrList	l1, l2;
#endif
{
    VoidPtrList	New;
    VoidPtrList	*addr = &New;

    if (!l1) return (l2);
    if (!l2) return (l1);

    while (l1) {
	(*addr) = ConsVoidPtrList (l1->head, NULLVoidPtrList);
	addr = &((*addr)->tail);
	l1 = l1->tail;
    }
    (*addr) = l2;

    return (New);
}/* AppVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList AppElVoidPtrList (VoidPtrList l, VoidPtr e)
#else
VoidPtrList AppElVoidPtrList (l, e)
	VoidPtrList	l;
	VoidPtr	e;
#endif
{
    VoidPtrList	res = l;
    if (!l)
	return (ConsVoidPtrList (e, NULLVoidPtrList));

    while (l->tail)
	l = l->tail;
    l->tail = ConsVoidPtrList (e, NULLVoidPtrList);

    return (res);
} /* AppElVoidPtrList */


#if defined(__STDC__) || defined(__cplusplus)
void InsertAfterVoidPtrList (VoidPtrList l, VoidPtr e)
#else
void InsertAfterVoidPtrList (l, e)
	VoidPtrList	l;
	VoidPtr	e;
#endif
{
    if (!l)
	message (ERROR, "InserAfterVoidPtrList: null list", 0, &coord);
    else
	l->tail = ConsVoidPtrList (e, l->tail);
}/* InsertAfterVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList OrderedInsertVoidPtrList (VoidPtrList l, VoidPtr e, VoidPtrCmpFctType fcmp)
#else
VoidPtrList OrderedInsertVoidPtrList (l, e, fcmp)
	VoidPtrList	l;
	VoidPtr	e;
	VoidPtrCmpFctType fcmp;
#endif
{
    VoidPtrList	p;
    if (!l)
	return (ConsVoidPtrList (e, NULLVoidPtrList));
    if (fcmp (e, l->head) <= 0)
	return (ConsVoidPtrList (e, l));
    p = l;
    while (p->tail && (fcmp (e, p->tail->head) > 0))
	p = p->tail;
    p->tail = ConsVoidPtrList (e, p->tail);
    return (l);
}/* OrderedInsertVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrListPtr RefEndConsVoidPtrList (VoidPtrListPtr addr, VoidPtr e)
#else
VoidPtrListPtr RefEndConsVoidPtrList (addr, e)
	VoidPtrListPtr	addr;
	VoidPtr		e;
#endif
{
    if (!addr)
    {
	message (ERROR, "RefEndConsVoidPtrList: no VoidPtrList ref", 0, &coord);
	return (addr);
    }
    (*addr) = ConsVoidPtrList (e, NULLVoidPtrList);
    return (&((*addr)->tail));
}/* RefEndConsVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrListPtr RefEndAppVoidPtrList (VoidPtrListPtr addr, VoidPtrList l)
#else
VoidPtrListPtr RefEndAppVoidPtrList (addr, l)
	VoidPtrListPtr	addr;
	VoidPtrList		l;
#endif
{
    if (!addr) {
	message (ERROR, "RefEndAppVoidPtrList: no VoidPtrList ref", 0, &coord);
	return (addr);
    }
    if (!l)
	return addr;

    (*addr) = l;

    while (l->tail)
	l = l->tail;
    return (&(l->tail));
}/* RefEndAppVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
int ElemInVoidPtrList (VoidPtr e, VoidPtrList l, VoidPtrCmpFctType fcmp)
#else
int ElemInVoidPtrList (e, l, fcmp)
	VoidPtr	e;
	VoidPtrList	l;
	VoidPtrCmpFctType	fcmp;
#endif
{
    while (l != NULLVoidPtrList) {
	if (fcmp (e, l->head) == 0)
	    return (1);
	l = l->tail;
    }
    return (0);
}/* ElemInVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList AddToSetVoidPtrList (VoidPtr e, VoidPtrList l, VoidPtrCmpFctType fcmp)
#else
VoidPtrList AddToSetVoidPtrList (e, l, fcmp)
	VoidPtr	e;
	VoidPtrList	l;
	VoidPtrCmpFctType	fcmp;
#endif
{
    if (ElemInVoidPtrList (e, l, fcmp))
	return (l);
    else
	return (ConsVoidPtrList (e, l));
}/* AddToSetVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtrList MapVoidPtrList (VoidPtrList l, VoidPtrMapFct f)
#else
VoidPtrList MapVoidPtrList (l, f)
	VoidPtrList	l;
        VoidPtrMapFct f;
#endif
{
    VoidPtrList New = NULLVoidPtrList;
    VoidPtrList last = NULLVoidPtrList;

    while (l)
    {
	if (!New) {
	    New = ConsVoidPtrList ((f (l->head)), NULLVoidPtrList);
	    last = New;
	}
	else
	{
	    last->tail = ConsVoidPtrList ((f (l->head)), NULLVoidPtrList);
	    last = last->tail;
	}
	l = l->tail;
    }
    return (New);
}/* MapVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
int CompVoidPtrList (VoidPtrList l1, VoidPtrList l2, VoidPtrCmpFctType fcmp)
#else
int CompVoidPtrList (l1, l2, fcmp)
	VoidPtrList	l1, l2;
	VoidPtrCmpFctType fcmp;
#endif
{
    int	res = 0;
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
}/* CompVoidPtrList */

#if defined(__STDC__) || defined(__cplusplus)
VoidPtr SumVoidPtrList (VoidPtrList l, VoidPtrSumFct f, VoidPtr a)
#else
VoidPtr SumVoidPtrList (l, f, a)
	VoidPtrList	l;
	VoidPtr ((*f) ());
	VoidPtr	a;
#endif
{
    while (l) {
	a = (f (a, l->head));
	l = l->tail;
    }
    return (a);
}/* SumVoidPtrList */
