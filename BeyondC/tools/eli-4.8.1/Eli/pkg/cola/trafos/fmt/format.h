/*
** $Id: format.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
 **   Filename   :  format.h
 **
 **   Author     :  Ursula Stellmacher
 **
 **   Date       :  09.08.88
 **
 **   Last change:  12.11.88
 **
 **   task       : declaration of public funktions for formatting
 **
 **********************************************************************/

/***********************************************************************
 **  procedures and functions
 **********************************************************************/


/***********************************************************************
 **
 **  funktion   : print_prod   
 **
 **  task       : writes exactly one production into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/
extern void print_prod(  /* p_comar root , int did ,  FILE *fout_ptr ( Output-File ) */ );

/***********************************************************************
 **
 **  funktion   : print_grammar
 **
 **  task       : writes all productions into the outputfile
 **
 **  return     : void
 **
 **********************************************************************/
extern void print_grammar(  /* p_comar root , FILE *fout_ptr ( Output-File ) */ );

