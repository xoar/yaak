/*
** $Id: opthelptype.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: opthelptype.h                    first edit   :  3 .11 . 89      */
/* author  : Christian Zeitel                 last change  : 10 . 7 . 90      */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *  									       *
 *  This file contains the typedefinitions for the different optimization-     *
 *  methods.								       *
 *									       *
 ******************************************************************************/

/******************************************************/
/* typedefinition for interface to optimization-module*/
/******************************************************/

typedef short  *readtype[];

/******************************************************/
/* typedefinitions needed for optimization-method GCS */
/******************************************************/
 
typedef  struct  {
 
                short             degree,
                                  nodeindex,
                                  colourindex;
                struct succtype  *adjlist;
                                
}  nodetype;


typedef  struct succtype  {

                nodetype  *info;
         struct succtype  *next;
         
} adjlisttype;

typedef  short  *partitiontype[];

typedef  nodetype *graphtype[];



/******************************************************/
/* typedefinition needed for optimization-method LES  */
/******************************************************/

typedef  struct  {
                
                short  *decrow,
                       *deccol,
                       *rowval,
                       *colval,
                        elrows,
                        elcols,
                        scans;
                        
} lestype;





/******************************************************/
/* typedefinition needed for optimization-method RDS  */
/******************************************************/

typedef  struct  {
                
                short  *optab;
                
                int    *rowptr,
                	size;
                	
} rdstype;





/******************************************************/
/* typedefinition needed for optimization-method SDS  */
/******************************************************/

typedef  struct  {
                
                short  *first,
                       *last;
                
                int    *rowptr;
                
} sdstype;




/******************************************************/
/* typedefinition needed for optimization-method RCS  */
/******************************************************/

typedef  struct  {
                
                short  *rowptr,
                       *rowind,
                        maxrowind;
                        
} rcstype;

