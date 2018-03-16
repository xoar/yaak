/*
** $Id: tabsopttype.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: tabsopttype.h                    first edit   : 28 . 9 . 89      */
/* author  : Christian Zeitel                 last change  : 10 . 7 . 90      */
/******************************************************************************/

/******************************** CONTENTS ************************************* *                                                                             * *  This file contains two typedefinitions :				       *
 *  "opttpye" is the typedefinition for the interface between the modules      *
 *  <optimize parsertables> and <print parsertables> of the generator for      *
 *  the tabledriven LALR(1)-parser. 					       *
 *  "optkindtype" is typedefinition for selecting a special optimization-      *
 *  method by the user.							       *
 *									       *
 ******************************************************************************/
 

typedef  struct  {

        char *ttaboptkind; /* name for terminaltableoptimization    */
        char *ntaboptkind; /* name for nonterminaltableoptimization */
        char  chainrule;   /* if notzero the chainrule-elimination  */
                           /* is performed, isn't implemented yet   */
        
} optkindtype;




typedef  struct  {

		union  {
		/* the variable "ttabopt" contains the datas needed for a */
		/* special optimization-method for the  terminal-table    */
		
		  	 struct  { 
		  	 
		  	 	short *sigrowind,
		  	 	      *sigrowptr,
		  	 	       sigmaxrowind,
		  	 	      *sigcolind,
		  	 	      *sigcolptr,
		  	 	       sigmaxcolind,
		  	 	      
		  	 	      *rowind,
		  	 	       maxrowind,
		  	 	      *colind,
		  	 	       maxcolind,
		  	 	       
		  	 	      *ttab,
		  	 	      
		  	 	      *convtermlist;
		  	 	       
		  	 } GCS; /* Graph Colouring Scheme      */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 	
		  	 	short *sigrowind,
		  	 	      *sigrowptr,
		  	 	       sigmaxrowind,
		  	 	      *sigcolind,
		  	 	      *sigcolptr,
		  	 	       sigmaxcolind,
		  	 
		  	 	      *decrow,
		  	 	      *deccol,
		  	 	      *rowval,
		  	 	      *colval,
		  	 	       elrows,
		  	 	       elcols,
		  	 	       scans,
		  	 	      
		  	 	      *convtermlist;
		  	 	
		  	 } LES; /* Line Elimination Scheme     */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 
		  	        short *sigrowind,
		  	 	      *sigrowptr,
		  	 	       sigmaxrowind,
		  	 	      *sigcolind,
		  	 	      *sigcolptr,
		  	 	       sigmaxcolind,
		  	 
		  	              *ttab;
				int   *rowptr,
			               size;
				
				short *convtermlist;

		  	 } RDS; /* Row Displacement Scheme     */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short *firstptr,
				      *lastptr;
				int   *rowptr;

				short *convtermlist;

		  	 } SDS; /* Significant Distance Scheme */
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short  *rowptr,
		  	 	       *rowind,
		  	 	        maxrowind;
		  	 	        
		  	 } RCS; /* Row Collumn Scheme         */
		  	  
		} ttabopt;
		
		
		
		
		union  {
		/* the variable "ntabopt" contains the datas needed for a */
		/* special optimization-method for the nonterminal-table  */
		
		  	 struct  { 
		  	 	      
		  	 	short *rowind,
		  	 	       maxrowind,
		  	 	      *colind,
		  	 	       maxcolind,
		  	 	      
		  	 	      *ntab;
		  	 	       
		  	 } GCS; /* Graph Colouring Scheme       */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short *decrow,
		  	 	      *deccol,
		  	 	      *rowval,
		  	 	      *colval,
		  	 	       elrows,
		  	 	       elcols,
		  	 	       scans;
		  	 	
		  	 } LES; /* Line Elimination Scheme      */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short *ntab;
                                int   *rowptr,
                                       size;
		  	 	
		  	 } RDS; /* Row Displacement Scheme          */
		  	 
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short *firstptr,
                                      *lastptr;
                                int   *rowptr;
		  	 	
		  	 } SDS; /* Significant Distance Scheme  */
		  	 
		  	 
		  	 struct  {
		  	 
		  	 	short  *rowptr,
		  	 	       *rowind,
		  	 	        maxrowind;
		  	 	        
		  	 } RCS; /* Row Collumn Scheme          */
		  	 
		  	 
		} ntabopt;
		
		
		
} opttype;
