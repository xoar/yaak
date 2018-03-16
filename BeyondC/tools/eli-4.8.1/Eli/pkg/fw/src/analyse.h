/* $Id: analyse.h,v 1.5 1999/10/20 04:55:54 tony Exp $ */
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
/*                                   ANALYSE.H                                */
/******************************************************************************/
/*                                                                            */
/* This package exports a single function called analyse() that should be     */
/* invoked just after the parser has finished. The scanner and parser         */
/* serve only to construct a structured representation of the input file in   */
/* memory; they do not critique it beyond syntax. In contrast, analyse()      */
/* analyses the representation, checking it for "semantic" errors.  Any       */
/* problems that are found are sent to the lister package with appropriate    */
/* positioning information so that the messages appear at exactly the right   */
/* spot in the listing.                                                       */
/*                                                                            */
/******************************************************************************/

#include "style.h"

/******************************************************************************/

EXPORT void analyse P_((void));

/******************************************************************************/
/*                               End of ANALYSE.H                             */
/******************************************************************************/
