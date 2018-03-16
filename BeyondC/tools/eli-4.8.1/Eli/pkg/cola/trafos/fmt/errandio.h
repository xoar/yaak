/*
** $Id: errandio.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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


/***********************************************************************
 **
 **   Filename  :  errandio.h
 **
 **   Author    :  Ursula Stellmacher
 **
 **   Date      :  12.11.88
 **
 **   Last change:  12.11.88
 **
 **   Task       : Declaration of constants, types and functions for 
 **                input and output and for errorhandling
 **
 **********************************************************************/

/***********************************************************************
 **  constants
 **********************************************************************/

#define 	WRITE			"w"
#define   	READ			"r"

#define         S_EMPTY                  2

#define         CONNECT                  1
#define         REDUCEMOD                2
#define         NOREDUCEMOD              3 

#define         PRIVATE                  static
#define         PUBLIC


/***********************************************************************
 **  errorconstants
 **********************************************************************/

#define		FOPENERR		1
#define		PGRCALLERR		2
#define         READERROR               3
#define         WRITEERROR              4
#define         LHSPROD                 5
#define         LHSDEFTAB               6
#define         LHSSYMTAB               7
#define         RHSSYMTAB               8
#define         RHSOTHER                9
#define         INPUTERROR             10


/***************************************************************
 **  types
 ***************************************************************/

typedef unsigned int BOOL;


/***************************************************************
 ** funktions
 ***************************************************************/

/***********************************************************************
 **
 **   Function   :  error_messsage
 **
 **   Task       :  output of an errormessage and exit(0)
 **
 **********************************************************************/
extern void error_message ( /* short error_code, char *function, 
			       char *s1, char *s2 */ );

/***********************************************************************
 **
 **   Function   :  dat_open
 **
 **   Task       :  fileopening with the modus READ/WRITE
 **
 **   Return     :  FILE*
 **
 **********************************************************************/
extern FILE *dat_open ( /* char *dat_name, char *mode */ );
