/* $Id: writfile.h,v 1.5 1999/10/20 04:57:14 tony Exp $ */
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
/*                                   WRITFILE.H                               */
/******************************************************************************/
/*                                                                            */
/* Introduction                                                               */
/* ------------                                                               */
/* This package performs all of FunnelWeb's file output.                      */
/* FunnelWeb performs lots of output to lots of different files:              */
/*                                                                            */
/*    - Standard output (to write to the screen).                             */
/*    - The journal file.                                                     */
/*    - The listing file.                                                     */
/*    - The tangle output files.                                              */
/*    - The weave output file.                                                */
/*                                                                            */
/* Error Detection                                                            */
/* ---------------                                                            */
/* As we are serious about detecting errors, every call to every IO function  */
/* must have its status checked. Unfortunately this makes everything very     */
/* messy. Having to check result statuses and react to them can be very       */
/* awkward in deeply nested pieces of code, particularly as C does not have   */
/* exceptions. As a result, the policy adopted in FunnelWeb is to RECORD when */
/* an error occurs on an output stream and silently shut down that stream.    */
/* Then later, at a convenient time, the error status of the stream can be    */
/* checked, and an error message issued.                                      */
/*                                                                            */
/* The C libraries make an effort to be helpful here by providing the ferror  */
/* function. However, it is not useful here for two reasons:                  */
/*                                                                            */
/*    1. Some calls (e.g. fwrite) are not listed as setting the error status. */
/*    2. It is not guaranteed that IO calls to a stream with error status     */
/*       will not cause a crash.                                              */
/*    3. Even if ferror were used, it may not be supported by older compilers.*/
/*                                                                            */
/* This package was created to take care of the vexing problems of IO errors  */
/* in output streams. It is a layer above the ANSI file library that provides */
/* the elementary calls for writing. It differs in that if an error occurs,   */
/* the package records that fact and simply ignores all further operations    */
/* on the file. At any time, it is possible to find out whether a file is in  */
/* normal mode or error mode. All this means that a piece of code can use     */
/* this package to create and write to a file without worrying about errors.  */
/* Then later, when the dust settles, the package can check the status  of    */
/* the file, and take appropriate action if an error has been detected.       */
/*                                                                            */
/* Text vs Binary                                                             */
/* --------------                                                             */
/* This package translates all '\n' (contained in the data it has been given  */
/* to write) into the appropriate environment specific representation.        */
/*                                                                            */
/* Facts About WF Objects                                                     */
/* ----------------------                                                     */
/* - A WF object is either in NORMAL or ERROR mode.                           */
/* - A WF object in NORMAL mode is also either in OPEN or CLOSED mode.        */
/* - The term "raise an error" means bomb the program with a message.         */
/* - The comments attached to the functions given below are meant to be read  */
/*   sequentially with each action or check being performed before the next.  */
/* - This package can not guarantee to detect uninitialized WF objects. The   */
/*   reason is that policing is performed using magic number mechanism and it */
/*   is possible that a piece of random memory may contain just the right     */
/*   numbers to fool the package.                                             */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_WRITFILE
#define DONE_WRITFILE

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* We really don't want to show all the guts of this record here, but as      */
/* users of the package have to be able to declare objects of this type and   */
/* make them the right size, it seems as if we have no choice.                */
typedef struct
  {
   ulong  wf_mhead;   /* Helps detect uninitialized and corrupted records.    */
   bool   wf_iserr;   /* TRUE=>ERROR,   FALSE=>NORMAL.                        */
   bool   wf_isope;   /* TRUE=>OPEN,    FALSE=>CLOSED.                        */
   bool   wf_istxt;   /* TRUE=>TEXT,    FALSE=>BINARY.                        */
   FILE  *wf_pfile;   /* Pointer to the file object.                          */
   ulong  wf_mtail;   /* Helps detect uninitialized and  corrupted records.   */
  } wf_t;

typedef wf_t *p_wf_t;

/******************************************************************************/

EXPORT void wf_ini P_((p_wf_t,bool));
/* Initializes a WF to a well defined state in accordance with the boolean.   */
/*    FALSE => State=(ERROR).                                                 */
/*    TRUE  => State=(NORMAL,CLOSED).                                         */
/* wf_ini must be applied to a WF before any other operation.                 */
/* It can be re-applied repeatedly.                                           */

EXPORT void wf_att P_((p_wf_t,FILE *));
/* If WF is uninitialized, raises an error (probably).                        */
/* If WF is in ERROR mode, returns with no effect.                            */
/* If WF is OPEN, raises an error.                                            */
/* Attaches an already opened output file to the specified FW object.         */
/* Changes the WF to the OPEN state.                                          */
/* The memory that the second parameter points to must be stable.             */

EXPORT void wf_ope P_((p_wf_t,char *));
/* If WF is uninitialized, raises an error (probably).                        */
/* If WF is in ERROR mode, returns with no effect.                            */
/* If WF is OPEN, raises an error.                                            */
/* Creates an output file of the specified name and prepares it for writing.  */
/* Changes the WF to the OPEN state.                                          */
/* Sets the WF to the ERROR state if the file cannot be opened for writing.   */

EXPORT void wf_chr P_((p_wf_t,intchar));
/* If WF is uninitialized, raises an error (probably).                        */
/* If WF is in ERROR mode, returns with no effect.                            */
/* If WF is CLOSED, raises an error.                                          */
/* Writes the specified character to the output file associated with WF.      */
/* Sets WF to the ERROR state if an error occurs during the write.            */

EXPORT void wf_wr P_((p_wf_t,char *));
/* Same as wf_chr except that it writes an entire string.                     */

EXPORT void wf_wl P_((p_wf_t,char *));
/* Same as wf_wr except that appends a '\n'.                                  */

EXPORT void wf_blk P_((p_wf_t,char *,size_t));
/* Same as wf_wr but writes a block of bytes whose address is given by the    */
/* second parameter and whose length (in bytes) is given by the third         */
/* parameter.                                                                 */

EXPORT void wf_clo P_((p_wf_t));
/* If WF is uninitialized, raises an error (probably).                        */
/* If WF is in ERROR mode, returns with no effect.                            */
/* If WF is CLOSED, raises an error.                                          */
/* Flushes and closes the output file attached to WF.                         */
/* Sets WF to the CLOSED state.                                               */
/* Sets WF to the ERROR state if an error occurs during the close.            */

EXPORT bool wf_err P_((p_wf_t));
/* If WF is uninitialized, raises an error (probably).                        */
/* Returns TRUE iff WF is in the ERROR state, otherwise FALSE.                */
/* This function can be called at any time so long as the WF is initialized.  */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                              End of WRITFILE.H                             */
/******************************************************************************/
