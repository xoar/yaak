/* $Id: section.h,v 1.5 1999/10/20 04:56:51 tony Exp $ */
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
/*                                   SECTION.H                                */
/******************************************************************************/
/*                                                                            */
/* This package provides a very simple, very small abstraction for a section  */
/* number. A section number is a hierarchical group of numbers such as is     */
/* used to number the sections in documents. For example: 4.5.1.3 is a        */
/* section number. This package provides an abstraction for these numbers     */
/* that assists in their incrementing at different levels and in writing them */
/* out. The package also checks for hierarchical inconsistencies.             */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_SECTION
#define DONE_SECTION

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* The following constant defines the maximum number of levels that a         */
/* FunnelWeb document can have. @A corresponds to level 1.                    */
#define SECLEV_MAX 5

/* The following constant defines the maximum length of a string representing */
/* a section. This is calculated as the maximum number of levels multiplied   */
/* by 1 (for the separating dots) plus a safe size for a decimal number.      */
#define SECSTR_MAX (SECLEV_MAX*(1+10))

/* The following structure stores a single section number. The sc_level       */
/* field is the level of this field and is in the range [1,SECLEV_MAX]. The   */
/* sc_num field is defined only for elements [1,level] and contains the       */
/* hierarchy number at each level.                                            */
/* Example: For SECLEVMAX=4 and "3.4.1", level=3 and num=[?,3,4,1,?].         */
/* Note: The first question mark is for element zero which is always unknown. */
typedef struct
  {
   ulong  sn_magic;              /* Used to detect uninitialized sn objects.  */
   ubyte_ sn_lev;                /* Level number of section.                  */
   uword_ sn_num[SECLEV_MAX+1];  /* Hierarchical level numbers.               */
  } sn_t;

typedef sn_t *p_sn_t;

/******************************************************************************/

EXPORT void sn_ini P_((p_sn_t));
/* Initializes the specified section object to the empty section at level 0.  */
/* All sections must be initialized before any other operations are performed.*/

EXPORT void sn_set P_((p_sn_t,ubyte));
/* Sets the specified section to 1.1.1.1.1.1... at the given level.           */
/* Example: sn_set(p_sn,3) yields a section set to 1.1.1.                     */
/* Raises an error if the specified level is out of range.                    */

EXPORT void sn_inc P_((p_sn_t,ubyte));
/* Increments the number of the specified section object at the specified     */
/* level. This also has the effect of setting all lower levels to 0. For      */
/* example, 3.4.5.1 followed by sn_inc(&sn,2) would become 3.5.               */
/* Raises an error if the level is two or more lower than the current level   */
/* Example: You can't increment 2.4.1 at level 5.                             */
/* Raises an error if the specified level is out of range.                    */
/* Raises an error if a number at any level becomes too large (>60000).       */

EXPORT ubyte sn_lev P_((p_sn_t));
/* Returns the level number of the specified section.                         */

EXPORT void sn_str P_((p_sn_t,char *));
/* Writes a textual representation of the specified section into the given    */
/* string. The string must be able to hold at least SECSTRMAX characters.     */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                               End of SECTION.H                             */
/******************************************************************************/

