/*
** $Id: build_tdcopa.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* author  : Christian Zeitel                 last  change :  8  . 8 . 90     */
/******************************************************************************/

typedef  struct  {						       
									       
      		char *ttaboptkind; /* name for terminaltableoptimization    */ 
      		char *ntaboptkind; /* name for nonterminaltableoptimization */ 
       		char  chainrule;   /* if notzero the chainrule-elimination  */
                                   /* is performed, isn't implemented yet   */
                                   /* and should so always be set to zero   */
      									      
} optkindtype;	/* determines T-and N-table optimization */
 	

extern void build_copa(/* char addinfo, optinfo; optkindtype  optkind;   */
                       /* p_comar Comar_root; absparsertype Abs_parser;  */);
                       
/*******************************************************************************
 *									       *
 *  build_copa constructs parts of a concrete LALR(1)-parser. Its a backend    *
 *  for the frontend constructed by Karl-Josef Prott, which constructs a so-   *
 *  called abstract parser. This backend implements parse-tables for a table-  *
 *  driven concrete parser.						       *
 *									       *
 * INPUT :                                                                     *
 * ------ 								       *
 * 1.if parameter addinfo = 1, at various points the programm prints reports   *
 *   about sucessfully terminated modules or functions to stdout.              *
 *									       *
 * 2.if parameter optinfo = 1, additional informations about the results of    *
 *   the selected optimization-method are printed on file "opt.out".           *
 * 									       *
 * 3.optkind is a parameter of C-type optkindtype. 			       *
 *   The components *ttaboptkind and *ntaboptkind have the following range :   *
 *   { "GCSA", "GCSB", "LESA", "LESB", "RDS", "SDS", "RCSA", "RCSB" }. The     *
 *   different strings stand for following optimization-methods :              *
 *									       *
 *   "GCSA"/"GCSB" : Graph Colouring Scheme				       *
 *   "LESA"/"LESB" : Line Elimination Scheme				       *
 *   "RDS"         : Row Displacement Scheme				       *
 *   "SDS"         : significant distance Scheme			       *
 *   "RCSA"/"RCSB" : Row Collumn Scheme					       *
 *									       *
 *   All this schemes are described in :				       *
 *   "Optimization of Parser Tables for Portable Compilers", P. Denker, K.     *
 *   Duerre und J. Heuft, TOPLAS 6 (4), S.564-572, 1984                        *
 *   The letters A and B stand for refinements of the corresponding optimiza-  *
 *   tion method.							       *
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
 * OUTPUT : 			      					       *
 * -------- the tables for the tabledriven parser are printed on file          *
 *          "ptabs.h" which is included by module "tdcore.c".                  *
 *									       *
 *          Further a file with name "seminf.h" is generated.                  *
 *          It contains semantic informations about the terminal-symbols       *
 *          and is included by the parserframe in module "parser.c".           *
 *									       *
 ******************************************************************************/
 
