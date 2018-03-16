/* $Id: list.h,v 1.5 1999/10/20 04:56:20 tony Exp $ */
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
/*                                  LIST.H                                    */
/******************************************************************************/
/*                                                                            */
/* Introduction                                                               */
/* ------------                                                               */
/* This list package (list.h and list.c) implements a list abstraction.       */
/*                                                                            */
/* Facts about Lists                                                          */
/* -----------------                                                          */
/* - A LIST stores zero or more LIST ELEMENTS.                                */
/* - The user decides the type of element to be stored in each list.          */
/* - Each list stores only one type of list element; lists are homogeneous.   */
/* - Lists store copies of elements rather than pointers to elements.         */
/* - Each list can hold from zero to about 2^31 elements.                     */
/* - Each list has a HEAD end and a TAIL end.                                 */
/* - Elements can be appended and deleted only at the tail of the list.       */
/* - The elements of a list can be read sequentially from head to tail.       */
/* - A MARKER stores the current position in the list for sequential reading. */
/* - Upon list creation, the marker is positioned at the tail of the list.    */
/* - In a list of n elements, elements are numbered from 1 to n.              */
/* - Element 1 is at the head of the list. Element n is at the tail.          */
/* - The identifier "ls" is used as an abbreviation for "list".               */
/* - The identifier "el" is used as an abbreviation for "element".            */
/* - Longer names are desirable, but shorter ones have been used so as to     */
/*   enhance the portability of the package.                                  */
/* - IMPORTANT: Lists get all their memory using mm_temp calls.               */
/*                                                                            */
/* How To Use This List Package                                               */
/* ----------------------------                                               */
/* 1. Include this .H file in your program file.                              */
/* 2. Identify the type of elements to be placed in the list.                 */
/* 3. Define a variable of type p_ls as a view to a list.                     */
/* 4. Use the ls_* functions to perform the desired operations.               */
/*    Start with a call to ls_cre and (optionally) end with a call to ls_des. */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_LIST
#define DONE_LIST

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* Users manipulate lists through pointers to lists (p_ls_t). The following   */
/* declaration serves the list user of the package while hiding the           */
/* implementation details (which appear in a similar declaration in list.c).  */
/* The #ifndef stops list.c from seeing these public declarations.            */
#ifndef INLISTC
typedef struct {word NEVER_USE_THIS_FIELD_UQJTKC;} ls_yqwx; /* Don't use! */
typedef ls_yqwx *p_ls_t;
typedef p_void p_lsel_t;
typedef p_lsel_t *pp_lsel_t;
#endif

/******************************************************************************/
/*                                                                            */
/* General Notes About These Functions                                        */
/* -----------------------------------                                        */
/* - All lists and elements are passed by pointer. Whether a parameter is     */
/*   read or written is determined by it's function's description.            */
/* - Each function (except ls_cre) accepts a single pointer to a list and     */
/*   each function's description is assumed to be referring to the list.      */
/* - "Raising an error" means calling the external function "error" to        */
/*   write out a message and bomb the program.                                */
/* - You must create a list using ls_cre before performing any operations     */
/*   upon it. A list function will usually raise an error if it is            */
/*   handed a pointer that does not point to a properly CREated list.         */
/*                                                                            */
/* WARNING: This package copies values into its internal data structures      */
/* (through ls_add), but returns only POINTERS to elements when asked to      */
/* retrieve them. These pointers are valid only so long as the element        */
/* that they point to remains in the list. If the element is deleted somehow, */
/* the pointer points to garbage and becomes dangerous.                       */
/* So, if you have been handed a pointer to an element in a list (ls_nxt,     */
/* ls_loo), do not subsequently delete the element (ls_lop, ls_emp, ls_des)   */
/* and then attempt to access the element through the pointer.                */
/* One sure way to avoid the problem is always to use the pointer handed back */
/* by ls_nxt or ls_loo to copy the element immediately.                       */

/* The Functions                                                              */
/* -------------                                                              */
EXPORT p_ls_t ls_cre P_((size_t));
/* CREate. Creates a new list and returns a pointer to the new list. The user */
/* must specify in the parameter the size of elements that are to be stored   */
/* in the list. Specify the size of elements in bytes (usually using sizeof). */
/* The sequential reading marker is set to position n+1=1=tail of the list.   */

EXPORT void ls_add P_((p_ls_t,p_lsel_t));
/* ADD. Adds a new element onto the tail of the list (at position n+1).       */
/* The user must supply in the second parameter a pointer to the element to   */
/* be added. ls_add takes a copy of the element (it knows from the earlier    */
/* call to ls_cre how many bytes to copy) and stores the copy in its own      */
/* internal data structures.                                                  */

EXPORT void ls_lop P_((p_ls_t));
/* LOP. Removes (lops) element n from the tail of the list.                   */
/* Raises an error if the list is empty.                                      */

EXPORT ulong ls_len P_((p_ls_t));
/* LENgth. Returns the number of elements in the list (n).                    */

EXPORT void ls_fir P_((p_ls_t));
/* FIRst. Sets the sequential reading marker to element 1.                    */
/* If the list is empty (n=0) the marker is placed at the tail of the list    */
/* and subsequent calls to ls_add will leave it there until the next call to  */
/* ls_fir.                                                                    */

EXPORT void ls_nxt P_((p_ls_t,pp_lsel_t));
/* NeXT. Returns the list element under the marker and advances the marker    */
/* one position towards the tail of the list.                                 */
/* The method of returning the list element is a little messy. The user       */
/* supplies a pointer to a pointer in the second parameter, and the function  */
/* writes the address of the element in the list into the pointer.            */
/* If the marker is at position n+1 upon entry to ls_nxt, the marker position */
/* doesn't change and NULL is written to the argument pointer.                */

EXPORT void ls_loo P_((p_ls_t,ulong,pp_lsel_t));
/* LOOkup. Returns (using the same mechanism as ls_nxt) the k'th element of   */
/* the specified list where k is the second (ulong) parameter and the first   */
/* element (at the head of the list) is numbered number one (1).              */
/* Raises an error if the index k is out of the range [1,n].                  */

EXPORT void ls_tai P_((p_ls_t,pp_lsel_t));
/* Lookup TAIl. Returns (using the same mechanism as ls_nxt) the tail element */
/* of the specified list.                                                     */
/* Raises an error if the list is empty.                                      */

EXPORT void ls_emp P_((p_ls_t));
/* EMPty. Empties the specified list, deallocating all the space used by the  */
/* list elements. Upon completion, the list will be empty and the list marker */
/* will be positioned at the tail of the list.                                */

EXPORT void ls_des P_((p_ls_t));
/* DEStroy. Destroys a list, destroying all its elements and deallocating all */
/* the memory used by the list.                                               */

/* Marker Functions */
/* ---------------- */
/* The following two functions ls_mar and ls_set were hacked in to this list  */
/* package when it was discovered that the tangler sometimes needs to run     */
/* more than one context down a list at the same time. The two new functions  */
/* allow the list package user to save and restore the current mark.          */
/* These functions are not tightly controlled and so care must be taken in    */
/* their use.                                                                 */

EXPORT p_void ls_mar P_((p_ls_t));
/* Returns a representation of the current list marker. */

EXPORT void ls_set P_((p_ls_t,p_void));
/* Sets the position of the marker to an earlier saved position.              */
/* Calls to this function should satisfy the following conditions:            */
/*    1. The marker argument (p_void) must be the result of an earlier call   */
/*       to ls_mar with the same list as an argument.                         */
/*    2. No part of the list should have been modified in the interim. In     */
/*       particular, this means that no calls to ls_add, ls_lop, ls_emp or    */
/*       ls_des can be made between linked calls to ls_mar and ls_set.        */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                               End of LIST.H                                */
/******************************************************************************/
