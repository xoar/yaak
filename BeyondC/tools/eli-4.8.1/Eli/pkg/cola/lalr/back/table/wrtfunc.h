/*
** $Id: wrtfunc.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: wrtfunc.h                        first edit   : 28 .  8 . 89     */
/* author  : Christian Zeitel                 last  change : 10 .  7 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
*                                                                              *
*  This is the interface between the calling module wrt_tabs and the           *
*  answering module wrtfunc.                                                   *
*                                                                              *
*******************************************************************************/

/*  in  all of the following functions the parameters have the same meaning :
 *  - fp       :  a pointer to the file on which the parser-tables are printed.
 *
 *  - pt_data  :  the interfacevector to optimization which contains all impor-
 *		  tant informations for the concrete parser.
 *  - opt_data :  contains the optimized parsertables.
 *
 *  - addinfo  :  if it is set to YES, additional information about the genera-
 *		  tion-process is printed out at various points.
 *
 ***/
 
/*  printing-functions for the terminaltable  */
 
extern void Wrt_fixtabs( /* FILE *fp, fp_sema;              */
                         /* readtype pt_data; char addinfo; */ );

/* writes the tables not changed by optimization out on file "ptabs.h".
 * fp_sema points to a file collecting semantic informations about the
 * terminalsymbols. This file named "seminf.h" is only used by the parserframe.
 *
 ***/
 

extern void Twrt_GCStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Graph Colouring Scheme is performed */		         
		       

extern void Twrt_LEStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Line Elemination Scheme is performed */

		         
		         
extern void Twrt_RDStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Row Displacement Scheme is performed */
		         
		         
extern void Twrt_SDStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Significant Distance Scheme is performed */
		         

		         
extern void Twrt_RCStabs( /* FILE *fp; readtype pt_data;  */
		          /* opttype *opt_data;           */
		          /* char addinfo; char mrginfo;  */ );
/* the Row Column Scheme is performed */
		        


/*  printing-functions for the nonterminaltable  */


extern void Nwrt_GCStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Graph Colouring Scheme is performed */		         
		       

extern void Nwrt_LEStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Line Elimination Scheme is performed */
		         
		         
extern void Nwrt_RDStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Row Displacement Scheme is performed */
		         
		         
extern void Nwrt_SDStabs( /* FILE *fp; readtype pt_data;     */
		          /* opttype *opt_data; char addinfo;*/ );
/* the Significant Distance Scheme is performed */
		         
		         
extern void Nwrt_RCStabs( /* FILE *fp; readtype pt_data;  */
		          /* opttype *opt_data;           */
		          /* char addinfo; char mrginfo   */ );
/* the Row Column Scheme is performed */


