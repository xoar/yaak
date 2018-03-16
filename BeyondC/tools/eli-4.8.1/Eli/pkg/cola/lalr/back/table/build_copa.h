/*
** $Id: build_copa.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: build_tdcopa.h                   first edit   :  2 .  3 . 90     */
/* author  : Christian Zeitel                 last  change : 10 .  7 . 90     */
/******************************************************************************/


extern void build_copa(/* char addinfo, optinfo; optkindtype  optkind;   */
                       /* p_comar Comar_root; absparsertype Abs_parser;  */);
                       
/*******************************************************************************
 *									       *
 *  build_copa constructs parts of a concrete LALR(1)-parser. Its a backend    *
 *  for the frontend constructed by Karl-Josef Prott, which creates a so-      *
 *  called abstract parser. The backend can implement the concrete parser in   *
 *  two different ways : by constructing parse-tables for a tabledriven parser *
 *  or by constructing code-fragments for a directly programmed parser. There- *
 *  for two different backend-implementations exist.                           *
 * 									       *
 *									       *
 * INPUT :                                                                     *
 * ------ 								       *
 * 1.if parameter addinfo = 1, at various points the programm prints reports   *
 *   about sucessfully terminated modules or functions to stdout.              *
 *									       *
 * 2.if parameter optinfo = 1, additional informations about the results of    *
 *   the selected optimization-method are printed on file "opt.out".           *
 *									       *
 * 3.parameter optkind is of type optkindtype. If a tabledriven parser is ge-  *
 *   nerated, optkindtype is declared in file "tabsopttype.h". If a directly   *
 *   programmed parser is generated, optkindtype is declared in file           *
 *   "codeopttype.							       *
 *									       *
 * 4.Comar_root contains the internal representation of the IDL-C COMAR-data-  *
 *   structure after running through the comartool "cmrtool", which inserts    *
 *   the syntaxcodes for the terminals and the productioncodes.                *
 *									       *
 * 5.Abs_parser contains the internal representation of the IDL-C-structure    *
 *   for the abstract parser.						       *
 *                                                                             *
 *                                                                             *
 *                                                                             *
 * OUTPUT : If a tabledriven parser is generated :			       *
 * -------- the tables needed by the tabledriven parser are printed on file    *
 *          "ptabs.h" which is included by module "parsercore".                *
 *									       *
 *          If a directly programmed parser is generated :	               *
 *          the code for the directly programmed parser is printed on file     *
 *          "pcode.h" and additional tables needed for error-recovery are      *
 *          printed on file "ptabs.h". Both files are included into module     *
 *          "parsercore".						       *
 *									       *
 *          In each of both cases a file with name "seminf.h" is generated.    *
 *          It contains semantic informations about the terminal-symbols and   *
 *          is included by the parserframe in module "parser".                 *
 *									       *
 ******************************************************************************/
 
