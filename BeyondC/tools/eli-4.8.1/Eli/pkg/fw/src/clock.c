static char RCSid[] = "$Id: clock.c,v 1.5 1999/10/20 04:55:58 tony Exp $";
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
/*                                  CLOCK.C                                   */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "clock.h"
#include "machin.h"

/******************************************************************************/

#define MAGIC_HEAD (565854L)
#define MAGIC_TAIL (256194L)

/******************************************************************************/

LOCAL void ck_check P_((p_ck_t));
LOCAL void ck_check(p_ck)
p_ck_t p_ck;
{
 as_cold(p_ck!=NULL,"ck_check: Clock pointer is NULL.");
 as_cold(p_ck->ck_mhead==MAGIC_HEAD,
         "ck_check: Magic number at head of record is incorrect.");
 as_cold(p_ck->ck_mtail==MAGIC_TAIL,
         "ck_check: Magic number at tail of record is incorrect.");
}

/******************************************************************************/

EXPORT void ck_ini(p_ck)
p_ck_t p_ck;
{
 p_ck->ck_mhead = MAGIC_HEAD;
 p_ck->ck_run   = FALSE;
 p_ck->ck_csum  = 0.0;
 p_ck->ck_rsum  = 0.0;
 /* ck_csta and ck_rsta are undefined in a stopped clock. */
 p_ck->ck_mtail = MAGIC_TAIL;
}

/******************************************************************************/

EXPORT void ck_start(p_ck)
p_ck_t p_ck;
{
 ck_check(p_ck);
 as_cold(!p_ck->ck_run,"ck_start: Clock is already running!");
 p_ck->ck_run  = TRUE;
 p_ck->ck_csta = tim_cpu();
 p_ck->ck_rsta = tim_real();
}

/******************************************************************************/

EXPORT void ck_stop(p_ck)
p_ck_t p_ck;
{
 ck_check(p_ck);
 as_cold(p_ck->ck_run,"ck_stop: Clock is already stopped!");
 p_ck->ck_run  = FALSE;
 p_ck->ck_csum += tim_cpu () - p_ck->ck_csta;
 p_ck->ck_rsum += tim_real() - p_ck->ck_rsta;
}

/******************************************************************************/

EXPORT float ck_cpu(p_ck)
p_ck_t p_ck;
{
 ck_check(p_ck);
 as_cold(!p_ck->ck_run,"ck_cpu: Clock is running.");
 return p_ck->ck_csum;
}

/******************************************************************************/

EXPORT float ck_real(p_ck)
p_ck_t p_ck;
{
 ck_check(p_ck);
 as_cold(!p_ck->ck_run,"ck_real: Clock is running.");
 return p_ck->ck_rsum;
}

/******************************************************************************/
/*                              End of CLOCK.H                                */
/******************************************************************************/
