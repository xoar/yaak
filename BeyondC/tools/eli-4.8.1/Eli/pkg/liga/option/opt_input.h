/* $Id: opt_input.h,v 4.1 1997/08/29 09:18:06 peter Exp $ */
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

/***********************************************************************\
*	input.h								*
*	Header file for input function for the option handler		*
*									*
*	Written 07/05/90 - 11/14/90	by HaDeS			*
\***********************************************************************/

#ifndef _INPUT_H_INCL
#define _INPUT_H_INCL

#define	EXPFNAME	"expand.options"
#define	ORDFNAME	"order.options"
#define	OPTFNAME	"optim.options"
#define	BEFNAME		"backend.options"

#define	BUFSIZE		128
	/* maximal length of identifiers	*/
extern	void	OptionInput();

#endif

