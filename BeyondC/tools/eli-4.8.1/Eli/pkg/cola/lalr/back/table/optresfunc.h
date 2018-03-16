/*
** $Id: optresfunc.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: optresfunc.h                     first edit   :  3 .11 . 89      */
/* author  : Christian Zeitel                 last change  : 23 . 3 . 90      */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This file contains the interface between the calling module optfunc and    *
 *  the answering module optresfunc.					       *
 *          functions:   5  |   variables:  0 |  types:  0    		       *
 *									       *
 ******************************************************************************/



extern  void print_GCSoptres( /*  FILE *fp_opt;  char tabkind;                */
			      /*  opttype *opt_data;  readtype pt_data;       */
			      /*  short *colourmap;  partitiontype partition; */
			      /*  char sortinfo, rowcol_kind;                 */
			    );
			    
  /*  prints the optimization-results of optimization-method Row-Column-Scheme
   *  on file fp_opt points to.
   *
   ***/



extern  void print_LESoptres( /* FILE *fp_opt;      char tabkind;      */ 
			      /* opttype *opt_data; readtype pt_data;  */
			      /* char orderinfo;                       */ );

  /*  prints the optimization-results of optimization-method
   *  Line-Elimination-Scheme on file fp_opt points to.
   *
   ***/





extern  void print_RDSoptres( /*  FILE *fp_opt;       char tabkind;     */
			      /*  opttype *opt_data;  readtype pt_data; */ );

  /*  prints the optimization-results of optimization-method
   *  Row-Displacement-Scheme on file fp_opt points to.
   *
   ***/




extern  void print_SDSoptres( /*  FILE *fp_opt;       char tabkind;     */
			      /*  opttype *opt_data;  readtype pt_data; */ );

  /*  prints the optimization-results of optimization-method
   *  Significant-Distance-Scheme on file fp_opt points to.
   *
   ***/





extern  void print_RCSoptres( /*  FILE *fp_opt;      char tabkind; */
			      /*  opttype *opt_data;               */
			      /*  readtype pt_data;  char mrginfo; */ );

  /*  prints the optimization-results of optimization-method
   *  Row-Column-Scheme on file fp_opt points to.
   *
   ***/
