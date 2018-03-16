/*
** $Id: optfunc.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: optfunc.h                        first edit   : 28 .  8 . 89     */
/* author  : Christian Zeitel                 last  change : 23 .  3 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
*                                                                              *
*  This is the interface between the calling module opt_tabs and the           *
*  answering module optfunc.                                                   *
*                                                                              *
*******************************************************************************/

/*  in  all of the following functions the parameters have the same meaning :
 *
 *  - pt_data  :  the interfacevector to optimization which contains all impor-
 *		  tant informations for the concrete parser.
 *  - opt_data :  contains the optimized parsertables.
 *
 *  - optinfo  :  if it is set to 1, additional information about the optimiza-
 * 		  tion-process is printed on file "opt.out".
 *  - addinfo  :  if it is set to 1, additional information about the genera-
 *		  tion-process is printed out a various points.
 *
 * All the different optimization - methods are described in
 *  "Optimization of Parser Tables for Portable Compilers", P. Denker, K.
 *        Duerre and J. Heuft, TOPLAS 6 (4), S.564-572, 1984
 *
 ***/
 
/*  optimization-functions for the terminaltable */

		       
		       
extern void  Tmk_GCSopt( /* readtype pt_data; opttype *opt_data; */
		         /* char optinfo; FILE *fp_opt;          */
		         /* char addinfo; char sortinfo;         */ );
/* the Graph Colouring Scheme is performed */
/* if sortinfo =1, the nodes of the collisiongraph */
/* are ordered by decreasing degree		   */

		       
		       
extern void  Tmk_LESopt( /* readtype pt_data; opttype **opt_data; */
		         /* char optinfo; FILE *fp_opt;		  */
		         /* char addinfo; char ordrinfo;          */ );
/* the Line Elemination Scheme is performed */
/* if orderinfo =1, the algorithm tries to  */
/* eliminate columns first at beginning     */      

		       
		       
extern void  Tmk_RDSopt( /* readtype pt_data; opttype *opt_data;      */
		         /* char optinfo; FILE *fp_opt; char addinfo; */ );
/* the Row Displacement Scheme is performed */

		       
		       
extern void  Tmk_SDSopt( /* readtype pt_data; opttype *opt_data;      */
		         /* char optinfo; FILE *fp_opt; char addinfo; */ );
/* the Significant Distance Scheme is performed */
		       
		       
		       
extern void  Tmk_RCSopt( /* readtype pt_data; opttype *opt_data; */
		         /* char optinfo; FILE *fp_opt;          */
		         /* char addinfo; char mrginfo;          */ );
/* the Row Column Scheme is performed */




/*  optimization-functions for the nonterminaltable */

		       
		       
extern void  Nmk_GCSopt( /* readtype pt_data; opttype *opt_data; */
		         /* char optinfo; FILE *fp_opt; 	 */
		         /* char addinfo; char sortinfo;         */ );
/* the Graph Colouring Scheme is performed */
/* if sortinfo =1, the nodes of the collisiongraph */
/* are ordered by decreasing degree		   */

		       
		       
extern void  Nmk_LESopt( /* readtype pt_data; opttype *opt_data; */
		         /* char optinfo; FILE *fp_opt; 	 */
		         /* char addinfo; char orderinfo;        */ );
/* the Line Elemination Scheme is performed */
/* if orderinfo =1, the algorithm tries to  */
/* eliminate columns first at beginning     */

		       
		       
extern void  Nmk_RDSopt( /* readtype pt_data; opttype *opt_data;      */
		         /* char optinfo; FILE *fp_opt; char addinfo; */ );
/* the Row Displacement Scheme is performed */

		       
		       
extern void  Nmk_SDSopt( /* readtype pt_data; opttype *opt_data;      */
		         /* char optinfo; FILE *fp_opt; char addinfo; */ );
/* the Significant Distance Scheme is performed */
		       
		       
extern void  Nmk_RCSopt( /* readtype pt_data; opttype *opt_data; */
		         /* char optinfo; FILE *fp_opt;          */
		         /* char addinfo; char mrginfo;          */ );
/* the Row Column Scheme is perfomed */
