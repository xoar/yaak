/* $Id: misc.h,v 1.5 1999/10/20 04:56:38 tony Exp $ */
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
/*                                    MISC.H                                  */
/******************************************************************************/
/*                                                                            */
/* This package contains a ragbag of FunnelWeb-specific functions that didn't */
/* seem to have a home anywhere else.                                         */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "data.h"

/******************************************************************************/

/* The following functions each write a string to one or more output streams. */
/* The code is as follows:                                                    */
/*    wr - means write the string only.                                       */
/*    wl - means write the string followed by a '\n'.                         */
/*     s - The f_s output stream (the console/screen).                        */
/*     j - The f_j output stream (the journal file).                          */
/*     l - The f_l output stream (the listing file).                          */
/* These functions are hard wired to the f_s, f_j, and f_l global variables.  */

EXPORT void wr_s P_((char *));
EXPORT void wr_j P_((char *));
EXPORT void wr_l P_((char *));

EXPORT void wl_s P_((char *));
EXPORT void wl_j P_((char *));
EXPORT void wl_l P_((char *));

EXPORT void wr_sj P_((char *));
EXPORT void wl_sj P_((char *));

EXPORT void wr_sjl P_((char *));
EXPORT void wl_sjl P_((char *));

/******************************************************************************/

EXPORT char *chabbrev P_((int));
/* If the argument is non-printable in the range [0,127], returns a pointer   */
/* to a constant string containing the mnemonic abbreviation for the          */
/* character (e.g. 10="LF"). Otherwise returns the empty string.              */

/******************************************************************************/

EXPORT sign signof P_((long));
/* Returns -1 if its argument is negative. */
/* Returns  0 if its argument is zero.     */
/* Returns  1 if its argument is positive. */

/******************************************************************************/

EXPORT char * eq_files P_((char *,char *,bool *));
/* Performs an exact binary comparison of the files named name1 and name2.    */
/* If there is no error during the comparison, returns NULL and the boolean   */
/* parameter carries the result of the comparison with TRUE=>Files identical. */
/* If there is an error during the comparison, the boolean parameter is set   */
/* to FALSE and the function returns a pointer to a string describing the     */
/* error in terms of "the first file" and "the second file".                  */

/******************************************************************************/

EXPORT bool fexists P_((char *));
/* Returns TRUE iff a file of the name given in the parameter exists.         */
/* (Does this by attempting to open the file. If it succeeds, it closes it    */
/* again).                                                                    */

/******************************************************************************/

EXPORT char *fn_temp P_((void));
/* Creates a filename (not containing a directory component) for which there  */
/* is no corresponding file in the current directory.                         */
/* Returns a pointer to a static array containing the filename.               */
/* Each time this function is called, the new filename overwrites the old.    */
/* This function was created after it was discovered that, on some systems,   */
/* the standard library function "tmpnam" returns the name of a file in the   */
/* /tmp partition. This would not be a problem were it not for the fact that  */
/* generally, files cannot be renamed across partitions!                      */

/******************************************************************************/

EXPORT void strupper P_((char *));
/* Converts all lower case letters in the argument string to upper case.      */

/******************************************************************************/
/*                                End of MISC.H                               */
/******************************************************************************/
