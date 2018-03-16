/* $Id: memory.h,v 1.5 1999/10/20 04:56:35 tony Exp $ */
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
/*                                  MEMORY.H                                  */
/******************************************************************************/
/*                                                                            */
/* Introduction                                                               */
/* ------------                                                               */
/* This package provides a memory management facility for FunnelWeb.          */
/* The conventional MALLOC does not suit the needs of FunnelWeb. The          */
/* following notes give an idea of why:                                       */
/*                                                                            */
/* 1. At the times where FunnelWeb requires memory, it is nearly always       */
/*    the case that failure to provide the memory should result in a bomb.    */
/*    It therefore makes sense to wrap MALLOC up inside another function      */
/*    that, at the very least, checks the status from malloc and bombs        */
/*    the program if the requested memory is not available.                   */
/*                                                                            */
/* 2. Because FunnelWeb proper can be invoked an indefinite number of         */
/*    times from the FunnelWeb command interpreter, it is very important      */
/*    to reclaim all the memory used by each invocation. This could be        */
/*    done by explicitly tearing apart the data structures constructed        */
/*    for each run. However, this is very messy, requiring detailed           */
/*    knowledge of the data structures. A far simpler, safer scheme is to     */
/*    arrange for a memory manager to keep track of all the memory that it    */
/*    allocates and to provide a single call to free it all. This facility    */
/*    is provided by this package.                                            */
/*                                                                            */
/* 3. In addition to the TEMPORARY memory allocations described in (2) above, */
/*    it should also be possible to make permanent allocations.               */
/*                                                                            */
/* 4. FunnelWeb uses linked lists a lot and hence will make many requests     */
/*    for small chunks of memory (e.g 10 bytes). Legend has it that some      */
/*    malloc libraries are very inefficient in this case, and that it is      */
/*    better to use malloc to allocate a large chunk of memory and dole it    */
/*    out yourself. This package does this too.                               */
/*                                                                            */
/* For all these reasons, FunnelWeb memory management has been handed over to */
/* this package which provides services that satisfy the conditions outlined  */
/* above.                                                                     */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_MEMORY
#define DONE_MEMORY

/******************************************************************************/

#include "style.h"

/******************************************************************************/

EXPORT p_void mm_perm P_((size_t));
/* Allocates a block of memory of the specified size (specified in bytes) and */
/* returns a pointer to the new block of memory. Bombs the program if the     */
/* memory is not available. Memory allocated using mm_perm is permanently     */
/* allocated and cannot be freed.                                             */

EXPORT p_void mm_temp P_((size_t));
/* Allocates a block of memory of the specified size (specified in bytes) and */
/* returns a pointer to the new block of memory. Bombs the program if the     */
/* memory is not available. Memory allocated using this function can later be */
/* freed in its entirely by making a call to mm_zapt.                         */

EXPORT void mm_zapt P_((void));
/* This function can be called at any time. Its effect is to free up all the  */
/* memory allocated using mm_temp since the last call to mm_zapt or the start */
/* of the program, whichever is the more recent.                              */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                               End of MEMORY.H                              */
/******************************************************************************/
