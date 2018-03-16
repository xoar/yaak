/*
** $Id: cmrtool.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
/* filename: cmrtool.h                         first edit   :  2 . 3 . 90     */
/* author  : Christian Zeitel                  last Change  :  8 . 8 . 90     */
/******************************************************************************/

extern void cmrtool(/* p_comar Comar_root; */);

/*******************************************************************************
 *									       *
 *  cmrtool  inserts the sxcodes for the terminals and the productioncodes     *
 *  into the COMAR-datastucure.	It depends on the sacnner-generator and on the *
 *  semantic analysis. For a change of the scanner-generator or a change of    *
 *  plemented new.        						       *
 *									       *
 *  INPUT:								       *
 *  ------ 								       *
 *    Comar_root contains the internal representation of the IDL-C-COMAR-data- *
 *    structure behind the frontend.                                           *
 *									       *
 *									       *
 *  OUTPUT:								       *
 *  ------- Comar_root contains the internal representation of the IDL-C-      *
 *          COMAR-data-structure enhanced in following items :                 *
 *      (a) every definition-node for a terminal-symbol occuring in the        *
 *          scanner-specification has got a new property-node with the         *
 *          sid-index for the string "_SEM_SXCODE" or "_NOSEM_SXCODE"          *
 *          and the value of the sxccode for this terminal in the              *
 *          scanner-specification.                                             *
 *      (b) every definition-node for a production which belongs to the        *
 *          abstract syntax has got a new property-node with the sid-index     *
 *          for the string "_SEMA_PRODCODE" and the value of the production-   *
 *          code for this function.					       *
 *                                                                             *
 *          Further a file with name "semprods.h" is generated, which contains * *          an assignment from codes for semantic productions returned by the  *
 *          core to semantic actions performed in the parserframe.             *
 *									       *
 *									       *
 ******************************************************************************/  
