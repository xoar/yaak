/* $Id: table.h,v 1.5 1999/10/20 04:56:55 tony Exp $ */
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
/*                                   TABLE.H                                  */
/******************************************************************************/
/*                                                                            */
/* Introduction                                                               */
/* ------------                                                               */
/* This table package (table.h and table.c) implements a table abstraction.   */
/*                                                                            */
/* Facts about Tables                                                         */
/* ------------------                                                         */
/* - A TABLE stores zero or more (KEY,VALUE) PAIRS.                           */
/* - The user decides the types of keys and values and provides a             */
/*   COMPARISON FUNCTION providing a complete ordering of the set of keys.    */
/* - The comparison function must be consistent between calls.                */
/* - Tables store pairs in key order.                                         */
/* - A table cannot store more than one pair with the same key.               */
/* - Pairs can be added, but not deleted.                                     */
/* - A table can return the value corresponding to a given key.               */
/* - The pairs in a table can be read sequentially in key order. At all       */
/*   times, the table has an imaginary MARKER positioned on one of its pairs  */
/*   (or after the last pair). You can move the marker to the first pair and  */
/*   you can move the marker to the next pair, reading the pair as you go.    */
/*   Upon table creation, a table's marker is at the end-of-table position.   */
/* - If you try to perform an illegal operation on a table, the table package */
/*   will call "error" to write out an error message and bomb the program.    */
/* - Tables store copies of (key,value) pairs. They do not hold pointers to   */
/*   outside data (unless your keys or values are pointers themselves).       */
/* - If the keys are pointers themselves and point to other data which is     */
/*   used by the comparison function, then that data must not be modified     */
/*   in a way that will change the order of pairs in the table.               */
/* - A table can hold from zero to about 2^31 pairs.                          */
/* - The identifier "tb" is used as an abbreviation for "table".              */
/* - The identifier "ky" is used as an abbreviation for "key".                */
/* - The identifier "vl" is used as an abbreviation for "value".              */
/* - The author would like to use longer names, but has chosen to use the     */
/*   abbreviations so as to enhance the portability of the code.              */
/* - IMPORTANT: Tables get all their memory using mm_temp calls.              */
/*                                                                            */
/* How To Use This Table Package                                              */
/* -----------------------------                                              */
/* 1. Include this .H file in your program file.                              */
/* 2. Identify the key and value types that you are going to use.             */
/* 3. Define a function (having two parameters being pointers to keys)        */
/*    that compares two keys and returns [-1,0,1] accordingly.                */
/* 4. Define a variable of type p_tb as a view to a table.                    */
/* 5. Use the tb_* functions to perform the desired operations.               */
/*    Start with a call to tb_cre and (optionally) end with a call to tb_des. */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_TABLE
#define DONE_TABLE

/******************************************************************************/

#include <stddef.h>
#include "style.h"

/******************************************************************************/

/* Hide the exported abstract definition of a table from the table.c package. */
/* Table.c defines INTABLEC so as to prevent itself from seeing the following */
/* definitions. It defines its own more concrete definitions.                 */
#ifndef INTABLEC

/* The functions of the table abstraction pass keys and values exclusively    */
/* using pointers. These two definitions define types for these pointers.     */
/* Although the two types are both 'p_void', the different types are useful   */
/* to indicate what is expected in each position of the parameter lists.      */
typedef p_void p_tbky_t;
typedef p_void p_tbvl_t;

/* Define a type for a function to compare two keys. Such functions are       */
/* needed to organize the storage of (key,value) pairs inside the table.      */
/* Given the arguments are (a,b), the function should return:                 */
/*    -1 if a<b                                                               */
/*     0 if a==b                                                              */
/*     1 if a>b                                                               */
/* The user must create such a function and hand it to the 'tb_create'        */
/* function when creating new a new table.                                    */
typedef sign (*p_kycm_t) P_((p_tbky_t,p_tbky_t));

/* Users manipulate tables through pointers to tables. Here the actual table  */
/* internals are hidden from the user.                                        */
typedef struct {word NEVER_USE_THIS_FIELD_UQJTKC;} tb_t;
typedef tb_t *p_tb_t;

#endif

/******************************************************************************/

/* General Notes About These Functions                                        */
/* -----------------------------------                                        */
/* - All tables, keys, and values are passed by pointer. Whether a parameter  */
/*   is read or written is determined by it's functions description.          */
/* - Each function (except tb_cre) accepts a single pointer to a table and    */
/*   each function's description is assumed to be referring to the table.     */
/* - "Raising an error" means calling the external function "error" to        */
/*   write out a message and bomb the program.                                */
/* - You must create a table using tb_cre before performing any operations    */
/*   upon it. The table operations will usually raise an error if they are    */
/*   handed a pointer that does not point to a properly CREated table.        */

/* The Functions                                                              */
/* -------------                                                              */
EXPORT p_tb_t tb_cre P_((size_t,size_t,p_kycm_t));
/* CREate. This function creates a new table and returns a pointer to the     */
/* table. The user must supply 1) the size in bytes of keys, 2) the size in   */
/* bytes of values, 3) a pointer to a function that compares two keys.        */

EXPORT bool tb_itb P_((p_tb_t,p_tbky_t));
/* InTaBle. Returns TRUE iff the given key is in the table.                   */

EXPORT void tb_loo P_((p_tb_t,p_tbky_t,p_tbvl_t));
/* LOOkup. Feed this function a table and a key and it will return (in the    */
/* p_tbvl_t parameter) the value corresponding to the key. The function       */
/* raises an error if the table does not contain the key.                     */

EXPORT void tb_ins P_((p_tb_t,p_tbky_t,p_tbvl_t));
/* INSert. Inserts the (key,value) pair into the table. Raises an error if    */
/* the key is already in the table.                                           */

EXPORT ulong tb_len P_((p_tb_t));
/* LENgth. Returns the number of pairs in the table. */

EXPORT void tb_fir P_((p_tb_t));
/* FIRst. Set's the table's marker to the first pair in the table (or the end */
/* of table position if the table is empty.                                   */

EXPORT bool tb_rea P_((p_tb_t,p_tbky_t,p_tbvl_t));
/* REAd. Returns in (p_tbky_t,p_tbvl_t) the (key,value) pair corresponding to */
/* the marker and them moves the marker onto the next pair.                   */
/* Returns TRUE  => Returned a pair.                                          */
/* Returns FALSE => Did not return a pair. No more pairs left.                */
/* of key) to be read from the table. Returns TRUE if it returns a pair       */
/* This function will not raise an error if it is called more than once with  */
/* the marker at the end of the table (it just keeps returning FALSE).        */

#if FALSE
void tb_des P_((p_tb_t));
/* DEStroy. Destroys a table, deallocating all its memory.                    */
#endif

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                 End of TABLE.H                             */
/******************************************************************************/
