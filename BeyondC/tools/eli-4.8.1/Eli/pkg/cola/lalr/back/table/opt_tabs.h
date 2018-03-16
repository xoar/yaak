/*
** $Id: opt_tabs.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: opt_tabs.h                       first edit   : 29 . 6 . 89      */
/* author  : Christian Zeitel                 last change  : 23 . 1 . 90      */
/******************************************************************************/

/******************************** CONTENTS ************************************* *                                                                             * *  This is the interface between the calling module build_tabs and the        * *  answering module opt_tabs.                                                 * *                                                                             * ******************************************************************************/

extern  void optim_copa(/* readtype pt_data; opttype *opt_data;           */
			/* optkindtype optkind; char optinfo, addinfo;    */);

  /*   Optimizes the parsing-tables.
   *
   *   on entry-
   *      pt_data contains the not-optimized parsing-tables and 
   *      all the other important informations for the concrete parser.
   *      *opt_data contains the interface to module wrt_tabs and is
   *      uninitialized on entry. optkind  points to two names which determine 
   *      how to optimize the parsing-tables. If optinfo is not zero additional
   *	  information about the optimization-process is printed out on file
   *	  "opt.out". If addinfo is not zero, additional information about the
   *      generating process is printed to standard-output at various points. 
   *   on exit-
   *      opt_data is the interface to optimization. It contains the optimized  
   *      parsing-tables optimized with the methods given by the value of
   *	  optkind.
   * 
   ***/  
