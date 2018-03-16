/* $Id: array.c,v 4.1 1997/08/29 08:31:13 peter Exp $ */
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

#include "global.h"

# define FArray(arr)	FreeHeap(arr)
	/* allocate 8 cells at a time */
# define MORECELLS 8

Boolean IDLInArray(arr, elem)
GenArray arr;
int elem;
{
    register int i;
    for (i=0; i<arr.length; i++)
	if (arr.array[i] == elem)
	    return(TRUE);
    return(FALSE);
}

GenArray IDLArraySort(arr, cmpfn)
GenArray arr;
Boolean (*cmpfn)();
{
    register int i,j;
    int tmp;
    int change;

    for (i=0; i<arr.length-1; i++){
	change = 0;
	for (j=0; j<arr.length-1-i; j++){
	    if (cmpfn(arr.array[j+1], arr.array[j])){ /* swap */
		tmp = arr.array[j+1];
		arr.array[j+1] = arr.array[j];
		arr.array[j] = tmp;
		change = 1;
	    }
	}
	if (!change) break;
    }
    return arr;
}

void IDLArrayOrderedInsert(arr, elem, cmpfn)
GenArray *arr;
int elem;
Boolean (*cmpfn)();
{
    Boolean insert = FALSE;
    int *newarray;
    int i,j;

    if (arr->length >= arr->size) { /* allocate more space */
	arr->size += MORECELLS;
	newarray = IDLNewArray(arr->size);
	for (i=0; i<arr->length; i++)
	    newarray[i] = arr->array[i];
	FArray(arr->array);
	arr->array = newarray;
    }
	
    for (i=0; i<arr->length; i++)
	if (cmpfn(arr->array[i], elem)) {
	    insert = TRUE;
	    break;
	}
    if (insert) {
	for (j=arr->length; j>i; j--)
	    arr->array[j] = arr->array[j-1];
	++(arr->length);
	arr->array[i] = elem;
    }
    else {
	arr->array[arr->length] = elem;
	++(arr->length);
    }
}


    
void IDLArrayAddFront(arr, elem)
GenArray *arr;
int elem;
{
    int i;
    int *newarray;

    if (arr->length >= arr->size) { /* allocate more space */
	arr->size += MORECELLS;
	newarray = IDLNewArray(arr->size);
	for (i=0; i<arr->length; i++)
	    newarray[i] = arr->array[i];
	FArray(arr->array);
	arr->array = newarray;
    }

    for (i=arr->length; i>0; i--)
	arr->array[i] = arr->array[i-1];
    arr->array[0] = elem;
    ++(arr->length);
}

void IDLArrayAddRear(arr, elem)
GenArray *arr;
int elem;
{
    int i;
    int *newarray;

    if (arr->length >= arr->size) { /* allocate more space */
	arr->size += MORECELLS;
	newarray = IDLNewArray(arr->size);
	for (i=0; i<arr->length; i++)
	    newarray[i] = arr->array[i];
	FArray(arr->array);
	arr->array = newarray;
    }

    ++(arr->length);
    arr->array[arr->length-1] = elem;
}

GenArray IDLArrayTail(arr)
GenArray arr;
{
    int i;
    GenArray tailarr;

    tailarr.array = IDLNewArray(arr.size);
    tailarr.size = arr.size;
    tailarr.length = arr.length - 1;
    for (i=1; i<arr.length; i++)
	tailarr.array[i-1] = arr.array[i];
    return(tailarr);
}

void IDLArrayRemoveFirstElem(arr)
GenArray *arr;
{
    int i;

    if (arr->length) {
	for (i=0; i<arr->length - 1; i++)
	    arr->array[i] = arr->array[i+1];
	--(arr->length);
    }
}

void IDLArrayRemoveElem(arr, elem)
GenArray *arr;
int elem;
{
    int i,j;
    Boolean found = FALSE;

    for (i=0; i<arr->length; i++)
	if (arr->array[i] == elem) {
	    found = TRUE;
	    break;
	}
    if (found) {
	for (j=i; j<arr->length - 1; j++)
	    arr->array[j] = arr->array[j+1];
	--(arr->length);
    }
}

GenArray IDLArrayCopy(arr)
GenArray arr;
{
	GenArray newarraystruct;
	int i;

	newarraystruct.array = IDLNewArray(arr.size);
	newarraystruct.size = arr.size;
	newarraystruct.length = arr.length;
	for (i=0; i<arr.length; i++)
	    newarraystruct.array[i] = arr.array[i];

	return(newarraystruct);
}
