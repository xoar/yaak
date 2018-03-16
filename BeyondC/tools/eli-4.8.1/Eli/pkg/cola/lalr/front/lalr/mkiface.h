/*
** $Id: mkiface.h,v 1.5 1997/08/29 08:38:08 mjung Exp $
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
/* File: mkiface.h	First Edit: 04.04.89	  Last Edit: 06.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: ??.04.89	From: Karl-Josef Prott			   */
/***************************************************************************/


#ifndef mkiface_DEF
#define mkiface_DEF

/***************************************************************************/
/* Exported function:							   */
/***************************************************************************/

/* Computes abstract interface containing the transition table
 * 	- reduction to startproduction is replaced with accept
 */
extern	void	cmrtl_compute_interface(/* p_comar	c;
					   ARRstatetype	automat;
					   DID		startprod;
					   absparsertype parser
					*/);

#endif  /* of mkiface_DEF */


