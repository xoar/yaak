/* $Id: scanner.h,v 1.5 1999/10/20 04:56:48 tony Exp $ */
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
/*                                  SCANNER.H                                 */
/******************************************************************************/
/*                                                                            */
/* This package contains the scanner. When called (though the only exported   */
/* routine below), the scanner maps in the file whose filename is given in    */
/* the global option.op_f_s variable. The scanner scans the file, mapping in  */
/* any included files, and builds two lists in the global list variables      */
/* 'line_list' and 'token_list'. The line list contains a list of the lines   */
/* of the input. The token list contains a tokenized form of the input, which */
/* is used by the parser. The scanner also sends diagnostics to the lister    */
/* package which has the effect of possibly incrementing the global error     */
/* counters num_*. See data.h for more information on data structures.        */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "clock.h"

/******************************************************************************/

EXPORT void scanner P_((p_ck_t,p_ck_t));
/* The arguments are first a mapper clock, and second a scanner clock. The    */
/* scanner should turn off the scanner clock and turn on the mapper clock     */
/* when calling the mapper.                                                   */

/******************************************************************************/
/*                             End of SCANNER.H                               */
/******************************************************************************/
