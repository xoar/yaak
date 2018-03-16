/* (C) Copyright 1997 University of Paderborn */

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

/*
** $Id: list.c,v 1.7 1997/08/29 08:38:08 mjung Exp $
*/

static char rcs_id[]= "$Id: list.c,v 1.7 1997/08/29 08:38:08 mjung Exp $";

#include <stdio.h>
#include "global.h"

#define ENDLIST NULL
#define FIRST(l) l
#define NEXT(l) l->next


	/* allocation and de-allocation routines for list cells */

# define NCGenList (pGenList)GetListCell((int)sizeof(struct GenList))
# define XCGenList(c) (c)

/***********************************************************************
 *
 * Function IDLListInsertAfter
 *
 * Purpose:  insert element p2 after element p1 in list
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListInsertAfter(p1, p2)
pGenList p1, p2;
{

    if (p1 != ENDLIST) {
	if (p2 != ENDLIST) NEXT(p2) = NEXT(p1);
	NEXT(p1) = p2;
	return(p1);
    }
    else return(p2);

}






/***********************************************************************
 *
 * Function IDLListAddRear
 *
 * Purpose:  add element p to end of list l
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListAddRear(l, value)
pGenList l;
someptr value;
{


	register pGenList t, last_t;
	register pGenList p;

	p = NCGenList;
	p->value = value;

	last_t = NULL;
	for (t = FIRST(l); t!=ENDLIST; t=NEXT(t)) 
		last_t = t;

	if (last_t == NULL)   /* list is empty */
		FIRST(l) = p;
	else NEXT(last_t) = p;
	NEXT(p) = ENDLIST;

	return(l);
}




/***********************************************************************
 *
 * Function IDLListAddFront
 *
 * Purpose: add element p to front of list l
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListAddFront(l, value)
pGenList l;
someptr value;
{
	pGenList p;

	p = NCGenList;
	p->value = value;

	NEXT(p) = FIRST(l);
	FIRST(l) = p;

	return(l);
}





/***********************************************************************
 *
 * Function IDLListRetrieveFirst
 *
 * Purpose: access the first element in list l
 *
 * Returns: the first element if list is non-empty else 0
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

someptr IDLListRetrieveFirst(l)
pGenList l;
{

	register pGenList tl;

	tl = FIRST(l);
	if (tl == ENDLIST)
	    return(0);
	else return(tl->value);
}

/***********************************************************************
 *
 * Function IDLListRetrieveLast
 *
 * Purpose: access the last element in list l
 *
 * Returns: the last element if list is non-empty else 0
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

someptr IDLListRetrieveLast(l)
pGenList l;
{

	register pGenList tl, lasttl;

	lasttl = ENDLIST;
	for (tl = FIRST(l); tl != ENDLIST; tl = NEXT(tl))
		lasttl = tl;
	if (lasttl == ENDLIST)
	    return(0);
	else return(lasttl->value);
}



/***********************************************************************
 *
 * Function IDLListRetrieveIth
 *
 * Purpose: access the ith element given by index in list l
 *
 * Returns: the ith element if list contains index number of elements else 0
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

someptr IDLListRetrieveIth(l, index)
pGenList l;
int index;
{
	register pGenList tl;
	register int count;
	someptr ithelem=0;

	count=1;
	for (tl=l; tl!=NULL; tl=tl->next)
	    if (count==index) {
		ithelem=tl->value;
		break;
	    }
	    else ++count;

	return(ithelem);
}

/***********************************************************************
 *
 * Function IDLListTail
 *
 * Purpose: Return the remainder of the list after the first cell.
 *
 * Returns: the remainder of the list after the first cell if list is 
 *	    nonempty else NULL
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

pGenList IDLListTail(l)
pGenList l;
{
	register pGenList tl;
	pGenList tail=NULL;

	if (l)
	    tail=l->next;
	return(tail);
}


/***********************************************************************
 *
 * Function IDLListLastCell
 *
 * Purpose: access the last cell in list l
 *
 * Returns: the last cell 
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

pGenList IDLListLastCell(l)
pGenList l;
{

	register pGenList tl, lasttl;

	lasttl = ENDLIST;
	for (tl = FIRST(l); tl != ENDLIST; tl = NEXT(tl))
		lasttl = tl;
	return(lasttl);
}


/***********************************************************************
 *
 * Function IDLListConnect
 *
 * Purpose:  connect two lists and return the result
 *
 * Returns: the concatenated lists
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

pGenList IDLListConnect(l1, l2)
pGenList l1, l2;
{
	pGenList IDLListLastCell();
	pGenList last_l1;



	if (l1 == ENDLIST)
		return(l2);
	else if (l2 == ENDLIST)
		return(l1);
	else {
		last_l1 = IDLListLastCell(l1);
		NEXT(last_l1) = l2;
		return(l1);
	}
	
}



/***********************************************************************
 *
 * Function IDLListReverse
 *
 * Purpose: Reverse the order of the elements in list and 
 *	    return the result
 *
 * Returns: the reversed list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListReverse(l)
pGenList l;
{	register pGenList pr, nx;
	pr=NULL;
	for (; l; l->next=pr, pr=l, l=nx)
	    if (l) nx = l->next;
	return pr;
}


/***********************************************************************
 *
 * Function IDLListRemoveCell
 *
 * Purpose: remove cell with value 'value' from list l
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListRemoveCell(l, value)
pGenList l;
someptr value;
{

	register pGenList tl, prev_tl;


	prev_tl = NULL;
	for (tl=FIRST(l); tl!=ENDLIST; tl=NEXT(tl))
		if (tl->value == value) {
			if (prev_tl == NULL)   /* delete from front */
				l = NEXT(l);
			else NEXT(prev_tl) = NEXT(tl);
			
			XCGenList(tl);
			break;
		}
		else prev_tl = tl;

	return(l);
}


/***********************************************************************
 *
 * Function IDLListRemoveFirstCell
 *
 * Purpose: remove the first cell from the list
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

pGenList IDLListRemoveFirstCell(l)
pGenList l;
{
	pGenList first;

	if (l!=ENDLIST){
		first = FIRST(l);
		l = NEXT(l);
		XCGenList(first);
	}

	return(l);
}

/***********************************************************************
 *
 * Function IDLListRemoveLastCell
 *
 * Purpose: remove the last cell from a list
 *
 * Returns: the list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListRemoveLastCell(l)
pGenList l;
{

	register pGenList prev, tl;

	
	if (FIRST(l)!=ENDLIST) {
	
	    if (NEXT(l) == ENDLIST) { /* only one in list */
		XCGenList(FIRST(l));
		FIRST(l) = ENDLIST;
	    }
	    else {
		prev = FIRST(l);
		for (tl=FIRST(l); NEXT(tl)!=ENDLIST; tl=NEXT(tl)){
		    prev = tl;
		}
		NEXT(prev) = ENDLIST;
		XCGenList(tl);
	    }
	}
	return(l);
}

/***********************************************************************
 *
 * Function IDLInList
 *
 * Purpose: check if a value exists in a list
 *
 * Returns: TRUE if value exists, else FALSE
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/

Boolean IDLInList(l, value)
pGenList l;
someptr value;
{

	register pGenList tl;

	for (tl=FIRST(l); tl!=ENDLIST; tl=NEXT(tl))
		if (tl->value == value)
			return(TRUE);

	return(FALSE);
}

/***********************************************************************
 *
 * Function IDLListOrderedInsert
 *
 * Purpose: insert a value into the correct position in a sorted list
 *
 * Returns: the sorted list 
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListOrderedInsert( list, val, compfn)
pGenList list;
someptr val;
Boolean (*compfn)();	/* returns true if 2nd arg should be before 1st */
{


	register pGenList prev_tl,tl;	/* traversals of list */
	pGenList newcell;		/* new cell added to list */
	Boolean inserted;		/* indicator if new cell has been 
					   inserted */

	newcell = NCGenList;
	newcell -> value = val;

	inserted = FALSE;
	prev_tl = NULL;

	/* check for empty list */

	if (list == ENDLIST) {
	     list = newcell;
	     NEXT(newcell) = ENDLIST;
	     inserted =  TRUE;
	}
	else for (tl=FIRST(list); tl!=ENDLIST && !inserted; tl=NEXT(tl))
		if (compfn(tl->value, val)) {
			if (prev_tl == NULL) {	/* insert at front */
				NEXT(newcell) = FIRST(list);
				FIRST(list) = newcell;
			}
			else {
				NEXT(prev_tl) = newcell;
				NEXT(newcell) = tl;
			}

			inserted = TRUE;
		}
		else prev_tl = tl;



	if (!inserted) {	/* insert at end */
		NEXT(newcell) = ENDLIST;
		NEXT(prev_tl) = newcell;
	}
				
	return(list);
}

/***********************************************************************
 *
 * Function IDLListSort
 *
 * Purpose: Sort a list
 *
 * Returns: the sorted list
 *
 * Errors Checked For: none
 *
 * Assumptions/Limitations: none
 *
 **********************************************************************/
pGenList IDLListSort( list, compfn)
pGenList list;
Boolean (*compfn)(); 	/* returns true if 2nd arg should be before 1st */
{

	register pGenList tl1, prev_tl1;
	register pGenList tl2, prev_tl2;

	prev_tl1 = NULL;
	for (tl1 = FIRST(list); tl1 != ENDLIST; tl1 = NEXT(tl1)){
		prev_tl2 = tl1;
		for (tl2 = NEXT(tl1); tl2 != ENDLIST; tl2 = NEXT(tl2)) {
		    if (compfn(tl1->value, tl2->value)) {
			    if (prev_tl1 == NULL){ /* insert at front */
				    list = tl2;
			    }
			    else NEXT(prev_tl1) = tl2;

			    NEXT(prev_tl2) = NEXT(tl2);
			    NEXT(tl2) = tl1;
			    tl1 = tl2;
			    tl2 = NEXT(tl1);
		    }
		    if (tl2 == ENDLIST)
			break;
		    prev_tl2 = tl2;
		}
		prev_tl1 = tl1;
	}

	return(list);
}

/* return the length of the list */
int IDLListLength(l)
pGenList l;
{
	register pGenList tl;
	register int len;

	len = 0;
	for (tl=l; tl!=ENDLIST; tl=NEXT(tl))
	    ++len;
	return(len);
}

pGenList IDLListCopy(l)
pGenList l;
{
	register pGenList tl, tl2;
	pGenList newcell;
	pGenList newlist=ENDLIST;

	for (tl=l; tl!=ENDLIST; tl=NEXT(tl)){
		newcell = NCGenList;
		newcell->value = tl->value;
		newcell->next = ENDLIST;  /* inserted by Kalle */
		if (newlist == ENDLIST) {
		    newlist = newcell;
		}
		else {
		    tl2->next = newcell;
		}
		tl2 = newcell;
	}

	return(newlist);
}
