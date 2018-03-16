/* $Id: clock.h,v 1.5 1999/10/20 04:56:00 tony Exp $ */
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
/*                                  CLOCK.H                                   */
/******************************************************************************/
/*                                                                            */
/* This package implements a clock abstraction that is used to generate       */
/* timing statistics which are useful for performance tuning. The package     */
/* allows the measurement of both real and CPU time. This package gets its    */
/* raw information from the tim_cpu() and tim_real() functions of the machine */
/* dependent module "machin".                                                 */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_CLOCK
#define DONE_CLOCK

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* The following clock type is supposed to be an ADT so don't frob any of its */
/* fields manually!                                                           */
typedef struct
  {
   ulong ck_mhead; /* Magic number helps detect corruptions.                  */
   bool  ck_run;   /* TRUE iff the clock is running.                          */
   float ck_csum;  /* Accumulated CPU time.                                   */
   float ck_rsum;  /* Accumulated real time.                                  */
   float ck_csta;  /* ck_run => CPU  time when clock was started.             */
   float ck_rsta;  /* ck_run => Real time when clock was started.             */
   ulong ck_mtail; /* Magic number helps detect corruptions.                  */
  } ck_t;

typedef ck_t *p_ck_t;

/******************************************************************************/

EXPORT void ck_ini P_((p_ck_t));
/* Initializes the clock. After this call, the argument clock will be in the  */
/* STOPPED state and all its registers will be zero.  A clock must be         */
/* initialized before any other operations are performed on it.               */

EXPORT void ck_start P_((p_ck_t));
/* Changes the clock from the STOPPED state to the RUNNING state. Starts      */
/* accumulating real time and CPU time on its registers.                      */
/* Raises an error if the clock is not in the STOPPED state.                  */

EXPORT void ck_stop P_((p_ck_t));
/* Changes the clock from the RUNNING state to the STOPPED state. Stops       */
/* accumulating real time and CPU time on its registers.                      */
/* Raises an error if the clock is not in the RUNNING state.                  */

EXPORT float ck_cpu P_((p_ck_t));
/* Returns the number of seconds of CPU time accumulated on the clock.        */
/* Raises an error if the clock is not in the STOPPED state.                  */

EXPORT float ck_real P_((p_ck_t));
/* Returns the number of seconds of real time accumulated on the clock.       */
/* Raises an error if the clock is not in the STOPPED state.                  */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                              End of CLOCK.H                                */
/******************************************************************************/
