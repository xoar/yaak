/* $Id: mapper.h,v 1.5 1999/10/20 04:56:32 tony Exp $ */
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
/*                                  MAPPER.H                                  */
/******************************************************************************/
/*                                                                            */
/* The mapper is the first of FunnelWeb's four front end processors: (mapper, */
/* scanner, parser, analyser). The sole task of the mapper is, given the      */
/* name of a file, to create an image of that file in memory. This approach   */
/* is not wasteful of memory at all because FunnelWeb requires random access  */
/* to each input file at all times anyway so it can scramble the text around. */
/*                                                                            */
/******************************************************************************/

#include "style.h"

/******************************************************************************/

EXPORT char *map_file P_((char *,char **,ulong *));
/* Allocates a block of memory and places a Unix text stream representation   */
/* (with EOL marking end of line and no character marking end of file) of the */
/* file 'p_name' in the block of memory. Returns a pointer to the address and */
/* len of the file in the mem block in the parameters (pp_mem and p_length).  */
/* Returns NULL upon success or a pointer to an error message string upon     */
/* failure. Note: Parameters are: p_name, pp_mem, p_length.                   */
/* Note: Allocates enough memory so that there is guaranteed to be at least   */
/* two extra bytes of spare memory at the end of the mapped file. The         */
/* scanner uses this space to put EOL and EOF characters.                     */
/* Note: The mapper grabs its memory using mm_temp, so it can be recycled     */
/* as part of a call to mm_zapt.                                              */

/******************************************************************************/
/*                               End of MAPPER.H                              */
/******************************************************************************/
