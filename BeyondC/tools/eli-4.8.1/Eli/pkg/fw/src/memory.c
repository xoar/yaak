static char RCSid[] = "$Id: memory.c,v 1.5 1999/10/20 04:56:33 tony Exp $";
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
/*                                  MEMORY.C                                  */
/******************************************************************************/
/*                                                                            */
/* Implementation Overview                                                    */
/* -----------------------                                                    */
/* One of the tasks of this Memory Management (MM) package is to keep track   */
/* of the memory that it has allocated so that it can all be deallocated      */
/* later, in one go. To do this, the package keeps a linked list whose        */
/* elements describe the blocks allocated. Two linked lists are kept, one for */
/* temporary blocks and one for permanent blocks. Only the list for the       */
/* temporary blocks is used for deallocation. Permanent blocks are arranged   */
/* in a list so that the code for temporary blocks is also applicable.        */
/*                                                                            */
/* In order to avoid many calls to malloc() for small blocks of memory        */
/* (legend has it that some implementations of malloc() are very slow in this */
/* case), the MM package keeps a spare temporary and permanent block of       */
/* length MM_BLOCK from which it allocates small blocks. Small is defined as  */
/* <=MM_BLOCK/16. A separate malloc call is made for "Large" blocks greater   */
/* than MM_BLOCK bytes. "Large" blocks less than MM_BLOCK bytes may or may    */
/* not be allocated from a buffer block, depending on how much space is       */
/* available. See the code for the full details.                              */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "machin.h"
#include "memory.h"

/******************************************************************************/

/* The environ.h file contains a definition for ALIGN_POWER which is the      */
/* exponent of the power of two corresponding to the machine's alignment      */
/* requirements. The following two constants convert that constant to more    */
/* useful forms. These definitions should never need to be changed.           */
#define ALIGN_SIZE (1L<<ALIGN_POWER)
#define ALIGN_MASK (ALIGN_SIZE-1)

/* Because standard malloc() can be slow on some systems for large numbers of */
/* calls requesting small blocks of memory, FunnelWeb's memory management     */
/* package MM_* allocates memory in sizeable blocks and then allocates        */
/* smaller blocks from these big blocks without reference to malloc(). The    */
/* following #define tells the MM package how big the sizeable allocated      */
/* blocks should be. The rule is then: if the requested block is greater than */
/* MM_BLOCK/16, allocate it directly using malloc(), otherwise peel off some  */
/* memory from the latest sizeable block allocated.                           */
/* In practice, MM_BLOCK should be chosen to be about 1/10 to 1/20 of the     */
/* memory available to FunnelWeb. The disadvantage of making it big is that   */
/* when memory is tight, MM will be unable to allocate a full block and about */
/* half a block of memory will be unusable. The disadvantage of making it too */
/* small is that the linked lists tracking memory allocations will grow long  */
/* and it will take a long time to free up memory between invocations of      */
/* FunnelWeb proper. The value is not critical. A value of 31K should work    */
/* well on most systems. 31K is chosen instead of 32K just to be on the safe  */
/* side of 16 bits (so who's paranoid?).                                      */
#define MM_BLOCK (31L*1024L)

/* This definition provides the definition of the size of a "big" block; that */
/* is, one that should possibly be treated differently from the others.       */
/* The rule we use is that a big block is 1/16 of the standard block size.    */
/* This results in a maximum memory wastage of 1/16 or about 7%.              */
#define MM_BIG (MM_BLOCK >> 4)

/* Magic numbers help us to detect corruptions. */
#define MAGIC_HEAD  (83716343L)
#define MAGIC_TAIL  (11172363L)

/* Set MEMTRACE to TRUE to trace all memory operations. */
#define MEMTRACE FALSE

/******************************************************************************/

/* The following structures define a type for the linked lists that keep      */
/* track of the allocated blocks.                                             */
typedef struct mm_t_
  {
   ulong         mm_mhead; /* Magic number protecting beginning of record.    */
   ubyte_       *mm_pblok; /* Pointer to the allocated block.                 */
   ubyte_       *mm_pfree; /* Pointer to next free byte in block (ALIGNED).   */
   ulong         mm_nfree; /* Number of unused bytes available in the block.  */
   struct mm_t_ *mm_pnext; /* Pointer to the header for the next block.       */
   ulong         mm_mtail; /* Magic number protecting end of record.          */
  } mm_t;

typedef mm_t *p_mm_t;      /* Handy to have a pointer type too.               */

/* The following two local variables point to the head of the temporary and   */
/* permanent block lists. The first block in each list is that list's buffer. */
LOCVAR p_mm_t p_perm = NULL;
LOCVAR p_mm_t p_temp = NULL;

/******************************************************************************/

LOCAL void mm_check P_((p_mm_t));
LOCAL void mm_check(p_mm)
/* Checks the magic numbers in the specified block header object. */
p_mm_t p_mm;
{
 as_cold(p_mm!=NULL,"mm_check: Null pointer.");
 as_cold(p_mm->mm_mhead==MAGIC_HEAD,"mm_check: Corrupted header.");
 as_cold(p_mm->mm_mtail==MAGIC_TAIL,"mm_check: Corrupted trailer.");
}

/******************************************************************************/

LOCAL void mm_align P_((p_mm_t));
LOCAL void mm_align(p_mm)
/* Some machines are very fussy about the memory alignment of allocated       */
/* objects. To solve this problem, the mm_pfree pointer is always kept at an  */
/* "aligned" address. This function accepts a pointer to the header of a      */
/* block whose mm_pfree pointer is possibly unaligned and consumes bytes      */
/* until mm_pfree is aligned.                                                 */
p_mm_t p_mm;
{
 ubyte bump;
 ubyte consume;

 mm_check(p_mm);

 /* Work out how many bytes are sticking out over the alignment boundary. */
 bump = ((ulong) p_mm->mm_pfree) & ALIGN_MASK;

 /* Return if the block is already aligned. */
 if (bump==0) return;

 /* Otherwise work out how many bytes we have to consume to become realigned. */
 consume=ALIGN_SIZE-bump;

 /* If there are not enough bytes left in the block to allow the free pointer */
 /* to be aligned, then simply set the available bytes to zero and return. It */
 /* doesn't matter if we don't achieve alignment in this case as if           */
 /* mm_nfree==0, nothing can ever be allocated at the misaligned address.     */
 if (consume>p_mm->mm_nfree) {p_mm->mm_nfree=0; return;}

 /* Consume the bytes required to align the free pointer. */
 p_mm->mm_pfree += consume;
 p_mm->mm_nfree -= consume;

 /* Check that we have properly aligned the free pointer. */
 as_cold((((ulong) p_mm->mm_pfree) & ALIGN_MASK)==0,
         "mm_align: Failed to align.");
}

/******************************************************************************/

LOCAL p_mm_t mm_newblk P_((size_t));
LOCAL p_mm_t mm_newblk(blk_len)
/* Creates a new block containing (after alignment) at least blk_len bytes.   */
/* Returns a pointer to the header for the block.                             */
size_t blk_len;
{
 p_mm_t  p_mm;
 ubyte_ *p_bl;

 /* Allocate the header and the block itself. Because we are guaranteeing     */
 /* that the resultant block will have at least blk_len bytes free, we have   */
 /* to take into account alignment and add in ALIGN_SIZE when requesting mem. */
 p_mm=(p_mm_t  ) malloc((size_t)         sizeof(mm_t));
 p_bl=(ubyte_ *) malloc((size_t) (blk_len+ALIGN_SIZE));
 if (p_mm==NULL || p_bl==NULL)
   {
    fprintf(stderr,"mm_newblk: Out of memory!\n");
    fprintf(stderr,"FunnelWeb doesn't cope well when it runs out of memory.\n");
    fprintf(stderr,"It falls in a heap just as it is about to now.\n");
    as_bomb("Stand by for an ungraceful termination!");
   }

 /* Fill in the fields of the block header. */
 p_mm->mm_mhead = MAGIC_HEAD;
 p_mm->mm_pblok = p_bl;
 p_mm->mm_pfree = p_bl;
 p_mm->mm_nfree = blk_len+ALIGN_SIZE;
 p_mm->mm_pnext = NULL;
 p_mm->mm_mtail = MAGIC_TAIL;

 /* Align the free pointer in the header block. */
 mm_align(p_mm);

 /* Return a pointer to the header block we created. */
 return p_mm;
}

/******************************************************************************/

LOCAL p_void mm_alloc P_((p_mm_t *,size_t));
LOCAL p_void mm_alloc(pp_mm,bytes)
/* 'pp_mm' must be a pointer to either p_perm or p_temp.                      */
/* 'bytes' is the number of bytes required.                                   */
/* Allocates the required memory and returns an aligned pointer to it.        */
/* Bombs the program if the memory is not available.                          */
p_mm_t *pp_mm;
size_t bytes;
{
 p_mm_t p_from;    /* Pointer to header for block from which we finally alloc.*/
 ubyte_ *p_result; /* The result pointer returned to the caller.              */

 /* If the list is empty, create a "buffer block" and put it in the list.     */
 if (*pp_mm==NULL) *pp_mm=mm_newblk((size_t) MM_BLOCK);

 /* If there is room in the current buffer block, we can allocate directly.   */
 /* Note that we may be allocating a "big" block here, but as long as it fits */
 /* into the free space of the current buffer block, we don't care.           */
 if ((*pp_mm)->mm_nfree >= bytes) {p_from = *pp_mm; goto dole_out;}

 /* At this point we know that there is not enough space in the current       */
 /* buffer block. This could mean that we have an extra big allocation on our */
 /* hands in which case, we should malloc up a block specially for this       */
 /* request. It could also mean that we are running out of space in our       */
 /* buffer block in which case a new one must be allocated.                   */
 if (bytes >= MM_BIG)
   {
    /* If the request is BIG, allocate a special block for it and insert the  */
    /* block in the block list just after the buffer block, leaving the       */
    /* buffer block the first in the block list.                              */
    p_mm_t p_tmp=mm_newblk(bytes);
    p_tmp->mm_pnext=(*pp_mm)->mm_pnext;
    (*pp_mm)->mm_pnext=p_tmp;
    p_from=p_tmp;
   }
 else
   {
    /* If the request is not big, our buffer block is probably too empty and  */
    /* so it is time to create a new one. Allocate a new buffer block and     */
    /* make it the new head of this block list. Note that by giving up on the */
    /* previous buffer, we waste at most 1/16 of the block we are giving up   */
    /* on. This cost is reasonable in exchange for all the speed this gives.  */
    p_mm_t p_tmp=mm_newblk((size_t) MM_BLOCK);
    p_tmp->mm_pnext=(*pp_mm);
    (*pp_mm)=p_tmp;
    p_from=p_tmp;
   }

 dole_out:
 /* Jump here to dole out 'bytes' bytes from block 'p_from'. */
 p_result=p_from->mm_pfree;
 p_from->mm_pfree += bytes;
 p_from->mm_nfree -= bytes;
 mm_align(p_from);

 /* Ensure that the pointer being returned is properly aligned. */
 as_cold((((ulong) p_result) & ALIGN_MASK)==0,
         "mm_alloc: Result is misaligned.");

 /* Return the result. */
 return (p_void) p_result;
}

/******************************************************************************/

EXPORT p_void mm_perm(bytes)
size_t bytes;
{
#if MEMTRACE
 printf("TRACE: mm_perm: Allocating %lu bytes of permanent memory.\n",
(ulong) bytes);
#endif
 return mm_alloc(&p_perm,bytes);
}

/******************************************************************************/

EXPORT p_void mm_temp(bytes)
size_t bytes;
{
#if MEMTRACE
 printf("TRACE: mm_temp: Allocating %lu bytes of temporary memory.\n",
(ulong) bytes);
#endif
 return mm_alloc(&p_temp,bytes);
}

/******************************************************************************/

EXPORT void mm_zapt()
/* This function frees all the memory blocks recorded in the temporary        */
/* memory list. We choose to free them rather than merely re-using them       */
/* directly because they may not all be the same size, and we want to give    */
/* the built-in memory manager a chance to smooth out the heap.               */
{
#if MEMTRACE
 printf("TRACE: mm_zapt: Attempting to release all temporary memory.\n");
#endif

 while (p_temp != NULL)
   {
    p_mm_t p_mm=p_temp;
    mm_check(p_temp);
#if MEMTRACE
    printf("TRACE: mm_zapt: Deallocating a big chunk of temporary memory.\n");
#endif
    free(p_temp->mm_pblok);
    p_temp=p_temp->mm_pnext;
    free(p_mm);
   }
}

/******************************************************************************/
/*                             End of MEMORY.C                                */
/******************************************************************************/
