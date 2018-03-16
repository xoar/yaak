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
#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include "eliproto.h"
#include "global.h"


#define ENDLIST NULL
#define FIRST(l) l
#define NEXT(l) l->next


	/* allocation and de-allocation routines for list cells */

# define NCGenList (pGenList)GetListCell(sizeof(struct GenList))
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
pGenList IDLListInsertAfter ELI_ARG((pGenList, pGenList));

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
pGenList IDLListAddRear ELI_ARG((pGenList, someptr));

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
pGenList IDLListAddFront ELI_ARG((pGenList, someptr));

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
someptr IDLListRetrieveFirst ELI_ARG((pGenList));

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
someptr IDLListRetrieveLast ELI_ARG((pGenList));

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
someptr IDLListRetrieveIth ELI_ARG((pGenList, int));

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
pGenList IDLListTail ELI_ARG((pGenList));

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
pGenList IDLListLastCell ELI_ARG((pGenList));

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
pGenList IDLListConnect ELI_ARG((pGenList, pGenList));

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
pGenList IDLListReverse ELI_ARG((pGenList));

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
pGenList IDLListRemoveCell ELI_ARG((pGenList, someptr));

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
pGenList IDLListRemoveFirstCell ELI_ARG((pGenList));

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
pGenList IDLListRemoveLastCell ELI_ARG((pGenList));

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
Boolean IDLInList ELI_ARG((pGenList, someptr));

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
pGenList IDLListOrderedInsert ELI_ARG((pGenList, someptr, Boolean (*) ()));
/* Boolean ()();	returns true if 2nd arg should be before 1st */

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
pGenList IDLListSort ELI_ARG((pGenList, Boolean (*)()));

/* return the length of the list */
int IDLListLength ELI_ARG((pGenList));

pGenList IDLListCopy ELI_ARG((pGenList));

#endif
