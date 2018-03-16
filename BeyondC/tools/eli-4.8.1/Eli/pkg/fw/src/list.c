static char RCSid[] = "$Id: list.c,v 1.5 1999/10/20 04:56:18 tony Exp $";
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.

##############################################################################*/


/******************************************************************************/
/*                                    LIST.C                                  */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "machin.h"
#include "memory.h"

/******************************************************************************/

/* In order to catch uninitialized and corrupted lists, the first and last    */
/* fields of legitimate list objects contain magic numbers. The following     */
/* #defines give the values of these numbers. The first thing that each       */
/* function of this package does is to check the two magic number fields of   */
/* the list it has just been passed, and bomb the package if the fields have  */
/* the wrong values. This technique is likely to pick uninitialized lists,    */
/* as well as lists that have been partially overwritten.                     */
#define MAGIC_HEAD_VALUE  (97673812L)
#define MAGIC_TAIL_VALUE  (49357294L)

/******************************************************************************/

typedef struct node_t_      /* Structure used to compose the list proper.     */
  {
   struct node_t_ *p_prev;  /* Points to adjacent node closer to head.        */
   struct node_t_ *p_next;  /* Points to adjacent node closer to tail.        */
   p_void          p_data;  /* Points to data in heap for this element.       */
  }
  node_t;

typedef node_t *p_node_t;   /* Pointer to node type.                          */

typedef struct              /* Main list object containing all the goodies.   */
  {
   ulong    magic_head;     /* Helpful in catching list object corruptions.   */
   p_node_t p_head;         /* Points to the head of the list (or NULL).      */
   p_node_t p_tail;         /* Points to the tail of the list (or NULL).      */
   p_node_t p_mark;         /* Points to the marked element   (or NULL).      */
   size_t   data_bytes;     /* Number of bytes in this list's data elements.  */
   ulong    length;         /* Number of elements in this list.               */
   ulong    magic_tail;     /* Helpful in catching list object corruptions.   */
  }
  ls_t;

typedef ls_t *p_ls_t;       /* Main list view type.                           */

typedef p_void    p_lsel_t; /* Escalating pointers to data elements!          */
typedef p_lsel_t *pp_lsel_t;

/* We need the function prototypes from list.h. The #define ensures that the  */
/* abstract exported definition of a list is not visible to us here.          */
#define INLISTC
#include "list.h"

/******************************************************************************/

LOCAL void ls_check P_((p_ls_t));
LOCAL void ls_check(p_ls)
/* Accepts a pointer to a list and performs a series of checks to make sure   */
/* that the list has not been corrupted in some way.                          */
/* This function is the sort of function that is normally turned off in       */
/* production versions. However, we are too scared to in FunnelWeb because    */
/* lists are not typesafe and are used throughout the program.                */
p_ls_t p_ls;
{
 as_cold(p_ls!=NULL,"ls_check: List pointer is NULL.");
 as_cold(p_ls->magic_head==MAGIC_HEAD_VALUE,
         "ls_check: Magic number at head of record is incorrect.");
 as_cold(p_ls->magic_tail==MAGIC_TAIL_VALUE,
         "ls_check: Magic number at tail of record is incorrect.");
}

/******************************************************************************/

EXPORT p_ls_t ls_cre (data_bytes)
size_t data_bytes;
{
 p_ls_t p_ls;

 p_ls=(p_ls_t) mm_temp(sizeof(ls_t));
 p_ls->magic_head = MAGIC_HEAD_VALUE;
 p_ls->p_head     = NULL;
 p_ls->p_tail     = NULL;
 p_ls->p_mark     = NULL;
 p_ls->data_bytes = data_bytes;
 p_ls->length     = 0;
 p_ls->magic_tail = MAGIC_TAIL_VALUE;
 return p_ls;
}

/******************************************************************************/

EXPORT void ls_add(p_ls,p_lsel)
p_ls_t p_ls;
p_void p_lsel;
{
 p_node_t p_node;

 AS_HCODE(ls_check(p_ls);)

 /* Create the list node and the data node hanging off it. Copy the data in. */
 p_node        =(p_node_t) mm_temp(sizeof(node_t));
 p_node->p_data=(p_void)   mm_temp(p_ls->data_bytes);
 memcpy(p_node->p_data,p_lsel,p_ls->data_bytes);

 /* Attach the new node to the tail of the list. */

 p_node->p_prev=p_ls->p_tail;      /* Pointers in the new node itself. */
 p_node->p_next=NULL;

 if (p_ls->p_head == NULL)         /* Headside pointer pointing to new node. */
   p_ls->p_head=p_node;
 else
   p_ls->p_tail->p_next=p_node;

 p_ls->p_tail=p_node;              /* Tailside pointer pointing to new node. */

 /* Inc the length. */
 p_ls->length++;
}

/******************************************************************************/

EXPORT void ls_lop(p_ls)
p_ls_t p_ls;
{
 /* p_node_t p_targ; ONLY NEEDED IF DEALLOCATING */

 AS_HCODE(ls_check(p_ls);)

 as_cold(p_ls->length>0,"ls_lop: List is empty.");

 /* Make a note of the node being deleted. */
 /* p_targ=p_ls->p_tail; ONLY NEEDED IF DEALLOCATED. */

 /* If the target node was the only node, stitch up the ends of the list. */
 if (--p_ls->length==0)
   {
    p_ls->p_head=NULL;
    p_ls->p_tail=NULL;
   }
 else
   { /* Unhook node from tail of list. */
    p_ls->p_tail         = p_ls->p_tail->p_prev;
    p_ls->p_tail->p_next = NULL;
   }

 /* The following two commented calls show what we WOULD have to do to        */
 /* deallocate the list node. However, in FunnelWeb, all list items are       */
 /* allocated under the mm package watermark system using mm_temp calls so    */
 /* there is no need to free up the memory here.                              */
 /* DEALLOCATE(PV p_targ->p_data);                                            */
 /* DEALLOCATE(PV p_targ);                                                    */
}

/******************************************************************************/

EXPORT ulong ls_len(p_ls)
p_ls_t p_ls;
{
 AS_HCODE(ls_check(p_ls);)
 return p_ls->length;
}

/******************************************************************************/

EXPORT void ls_fir(p_ls)
p_ls_t p_ls;
{
 ls_check(p_ls);
 p_ls->p_mark=p_ls->p_head;
}

/******************************************************************************/

EXPORT void ls_nxt(p_ls,pp_lsel)
p_ls_t    p_ls;
pp_lsel_t pp_lsel;
{
 AS_HCODE(ls_check(p_ls);)

 if (p_ls->p_mark==NULL)
   {*pp_lsel=NULL; return;}
 *pp_lsel=p_ls->p_mark->p_data;
 p_ls->p_mark=p_ls->p_mark->p_next;
}

/******************************************************************************/

EXPORT void ls_loo(p_ls,index,pp_lsel)
p_ls_t    p_ls;
ulong     index;
pp_lsel_t pp_lsel;
{
 p_node_t p;
 ulong    i;

 AS_HCODE(ls_check(p_ls);)

 p=p_ls->p_head;
 as_cold(p!=NULL,"is_loo: List is empty.");
 for(i=1;i<index;i++)
   {
    p=p->p_next;
    as_cold(p!=NULL,"is_loo: Index is too high for this list.");
   }
 *pp_lsel=p->p_data;
}

/******************************************************************************/

EXPORT void ls_tai(p_ls,pp_lsel)
p_ls_t    p_ls;
pp_lsel_t pp_lsel;
{
 AS_HCODE(ls_check(p_ls);)

 as_cold(p_ls->p_tail!=NULL,"ls_tai: List is empty.");
 *pp_lsel=p_ls->p_tail->p_data;
}

/******************************************************************************/

EXPORT void ls_emp(p_ls)
p_ls_t p_ls;
{
 AS_HCODE(ls_check(p_ls);)

 /* The following loop WOULD be required if we had to deallocate the list     */
 /* elements explicitly.  However, as all list elements are allocated using   */
 /* mm_temp, it is possible to claim them later as a block. So here, we just  */
 /* let the list items drift off into the sunset.                             */
 /* p_node_t p_curr;                */
 /* p_curr=p_ls->p_head;            */
 /* while (p_curr != NULL)          */
 /*   {                             */
 /*    p_node_t p_targ=p_curr;      */
 /*    p_curr=p_curr->p_next;       */
 /*    my_free(PV p_targ->p_data);  */
 /*    my_free(PV p_targ);          */
 /*   }                             */

 p_ls->p_head=NULL;
 p_ls->p_tail=NULL;
 p_ls->p_mark=NULL;
 p_ls->length=0;
}

/******************************************************************************/

EXPORT void ls_des(p_ls)
p_ls_t p_ls;
{
 ls_check(p_ls);

 ls_emp(p_ls);
 p_ls->magic_head=0;  /* Zap the magic numbers in case memory is reused. */
 p_ls->magic_tail=0;

 /* The following call WOULD be required if it wasn't for the MM watermark    */
 /* system of memory allocation.                                              */
 /* my_free(PV p_ls); */
}

/******************************************************************************/

EXPORT p_void ls_mar (p_ls)
p_ls_t p_ls;
{
 AS_HCODE(ls_check(p_ls);)
 return PV p_ls->p_mark;
}

/******************************************************************************/

EXPORT void ls_set(p_ls,p_m)
p_ls_t p_ls;
p_void p_m;
{
 AS_HCODE(ls_check(p_ls);)
 p_ls->p_mark=(p_node_t) p_m;
}

/******************************************************************************/
/*                                End of LIST.C                               */
/******************************************************************************/
