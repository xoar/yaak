/*
** $Id: wrt_tabs.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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

/******************************************************************************/
/* filename: wrt_tabs.h                       first edit   :  29 .  6 . 89    */
/* author  : Christian Zeitel                 last change  :  10 .  7 . 90    */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the interface between the calling module build_tabs and the        *
 *  answering module wrt_tabs.						       *
 *									       *
 ******************************************************************************/

extern void write_copa(/* opttype *opt_data; optkindtype optkind;  */
		       /* readtype pt_data ; char         addinfo; */);

  /*   Prints out all important datas for the concrete parser on file "ptabs.h"
   *
   *    on entry-
   *       *opt_data contains all important informations about the optimized 
   *       parse tables, optkind contains the selected optimization-method
   *       pt_data  contains  all  datas  which  are  needes  to
   *       construct the concrete parser and if addinfo is not zero, 
   *       additional information about the generating process is printed 
   *       on standard-output at various points.
   *    on exit-
   *       all important tables needed for a tabledriven concrete Parser written
   *	   in the progamming-language C are printed out on file "ptabs.h".
   *    
   ***/
