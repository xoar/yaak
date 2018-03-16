/*
** $Id: cmrio.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
*/

/* (C) Copyright 1997 University of Paderborn */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/***************************************************************************/
/* File: cmrio.h	First Edit: 17.10.88	  Last Edit: 08.11.88      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/* Last Change: Kalle  (05.02.90)                                          */
/***************************************************************************/


#ifndef cmrio_DEF
#define cmrio_DEF

#include "cmrlib.h"  /* because of type ERR */

/* Maximum tool-information line length (first line) */
#define MAX_TOOL_INFO 127

/* errorcodes */
#define CMR_OPNERR  -2
#define CMR_RDERR   -4


/* exported routines: */

/* cmrlib-write - write ASCII comar representation of COMAR structure t
 *	entry:	*name == filename for writing COMAR-data-structure
 *		*tool_info does not contain '\n'.
 *		*c == an initialized COMAR internal structure
 *	exit:	(return == CMR_SUCCESS) ==> 
 *		  *tool_info augmented with '\n' has been written to a file 
 *		  named 'filename', followed by the ASCII represent. of *c.
 *		    
 *		(return == one of the errorcodes), if an error occured
 */
extern ERR cmrlib_write( /* char *filename; char *tool_info; p_comar c */ );


/* cmrlib-read - read ASCII comar representation into new COMAR structure
 *	entry:	*filename == name of external COMAR file.
 *		tool_info addresses a buffer with length >= MAX_TOOL_INFO
 *		c addresses an new, empty COMAR specification.
 *		( Think of call by reference: p_comar *(!) c )
 *	exit:	(cmrlib_read == CMR_SUCCESS) ==> 
 *		    *c == COMAR structure containing the internal
 *		     representation for the contents of file 'filename'.
 *		    *tool_info == the first line from that file, containing
 *		     tool-specific information.
 *		(return == one of the errorcodes), if an error occured
 */
extern ERR cmrlib_read( /* char *filename; char *tool_info; p_comar *c */ );


#endif   /* of cmrio_DEF */
