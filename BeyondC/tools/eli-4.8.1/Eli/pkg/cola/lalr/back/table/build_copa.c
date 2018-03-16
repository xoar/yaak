/*
** $Id: build_copa.c,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: build_copa.c,v 1.6 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: build_copa.c                     first edit   :  6 .  6 . 89     */
/* author  : Christian Zeitel                 last  change : 21 .  9 . 90     */
/******************************************************************************/

/************************* INTRODUCTION ****************************************
 *									       *
 * This module constructs the optimized parsing tables for a concrete LALR(1)- *
 * parser, based on the  abstract parser, constructed by Karl-Josef Prott, if  *
 * macro TABDRIV is set. If macro DIRPROG is set, this module constructs code  *
 * for a directly programmed concrete parser.			      	       *
 *									       *
 * INPUT :                                                                     *
 * ------                                                                      *
 *  -the internal IDL-C COMAR-datastructure in parameter Comar_root            *
 *  -the internal IDL-structure of the abstract parser in parameter Abs_parser *
 *  -name(s) which determine the table-optimization if option TABDRIV is set   *
 *   else they determine the code-optimization .			       *
 *                                                                             *
 * If parameter addinfo = 1, at various points the programm reports about      *
 * sucessfully finished operations which are printed on standardoutput.        *
 *                                                                             *
 * If parameter optinfo = 1, file "opt.out" with additional informations about *
 * the results of the selected optimization-method is printed out.             *
 *                                                                             *
 * OUTPUT : if macro TABDRIV is set :					       *
 * -------- the tables needed by the parser are printed on file "ptabs.h"      *
 *          if macro DIRPROG is set :				               *
 *          the code for the directly programmed parser in file "pcode.h"      *
 *									       *
 ******************************* CONTENTS **************************************
 *                                                                             *
 *  The main-function can be devided into three essential steps:               *
 *                                                                             *
 *  STEP    1: filter out all imformations, which are important for	       *
 *  ---------  constructing the  concrete parser in it's compiler-generation - *
 *             environment. This section is realized by function rd_absprs     *
 *             ( introduced by interfacefile rd_absprs.h ).                    *
 *                                                                             *
 *                                                                             *
 *  STEP    2: if macro TABDRIV is set, optimize the parsing-tables by         *
 *  ---------- optimization-options given by the two names in parameter        *
 *             optkind. If macro DIRPROG is set, optimize the generated        *
 *             code with the methods named in the componetnts of optkind.      *
 *	       This section is realized by function optim_copa .	       *
 *          								       *
 *                                                                             *
 *  STEP    3: If macro  TABDRIV is set,the generated parse-tables are printed *
 *  __________ on file "ptabs.h". If macro DIRPROG is set, the generated code  *
 *   	       for a directly programmed parser is printed on file "pcode.h"   *
 *	       and additional tables for error-recovery are printed on file    *
 *	       "ptabs.h. This section is realized by function write_copa       *
 *	       ( introduced by interfacefile  wrt_tabs.h ).                    *
 *									       *
 *                                                                             *
 ******************************* INTERFACES ************************************
 *                                                                             *
 * The three sections pointed out above are canned in three modules; the       *
 * interfaces between them are:                                                *
 *                                                                             *
 *  (1) <=> (2) : The interface is an array of pointers which point to short   *
 *   -----------  values or to lists of short values. It contains at least 13  *
 *                entries. A more exact description of tese entries is given   *
 *                in module rd_absprs.                                         *
 *                                                                             *
 *  (2) <=> (3) : The interface depends on the kind of the generated parser.   *
 *  ------------  If option TABDRIV is set, opttype is documented in file      *
 *                "tabsopttype.h", if option DIRPROG is set it is documented   *
 *		  in file "codeopttype.h".				       *
 *                                                                             *
 ******************************* TYPEDEFINITION *******************************/

#ifdef  TABDRIV

typedef  short  *readtype[]; /* type of interfacevector to optimizationmodule */

#endif

/******************************* INCLUDE-FILES ********************************/

#include <stdio.h>

#include "comar.h"    /* Interface to COMAR-IDL-C-structure of the CFG */

#include "prsiface.h" /* Interface to the IDL-C-structure of the       */
		      /* abstract parser                               */

#ifdef  TABDRIV       /* a tabledriven parser is generated  */

#include "tabsopttype.h"/* definition of type opt(kind)type for tables */

#include "rd_absprs.h"/* Interface to module rd_absprs 	  	       */

#include "opt_tabs.h" /* Interface to optimization-module for tables   */

#include "wrt_tabs.h" /* Interface to printig-module for tables        */

#endif

#ifdef  DIRPROG	         /* a directly programmed parser is generated  */

#include "codeopttype.h" /* definition of type opt(kind)type for code  */

#include "rd_absprs.h"/* Interface to module rd_absprs 	  	       */

#include "opt_codes.h"   /* Interface to optimization-module for code  */

#include "wrt_codes.h"   /* Interface to printig-module for code       */

#endif

#include "error.h"    /* Interface to error-logging for the parsergenerator */

/************************ INTERNAL DECLARATIONS *******************************/

void build_copa( addinfo, optinfo, optkind, Comar_root, Abs_parser )

	char          addinfo,    /* determines,if additional information is */
				  /* printed out during generation-process   */
	              optinfo;    /* determines,if additional information is */
	              		  /* printed out during table optimization   */
	optkindtype   optkind;    /* determines the table/code-optimization  */

	p_comar       Comar_root; /* keeps internal IDL-C-COMAR-structure    */

	absparsertype Abs_parser; /* keeps the internal structure of the     */
				  /* abstract parser			     */

{

   readtype        *pt_data;        /* interface from SECTION1 to SECTION2 */

   opttype          opt_data;       /* interface from SECTION2 to SECTION3 */

/*==================== STEP 1   : FILTER INFORMATIONSD FROM IDL-STRUCTURES ===*/

    if(addinfo)
   	  printf("C**module build_copa:started!\n");

    if(! Abs_parser->IsDeterm) /* no deterministic parser  */
			errmsg(BUILD_COPA, NDETERR, ABORT, DUMMY);

    pt_data = rd_absprs(
                         NULL,
                         Comar_root,
                         Abs_parser,
                         optkind.chainrule,
                         addinfo
                       );
   /* righthandsides of productions are read on chainrule-elimination */

   if(addinfo)
          printf("C**module build_copa:rd_absprs ended successfully!\n");

/*==================== STEP 2   : OPTIMIZE TABLES  OR CODE  ==================*/

   optim_copa( *pt_data, &opt_data, optkind, optinfo, addinfo );

   if(addinfo)
          printf("C**module build_copa:optim_copa ended successfully!\n");


/*==================== STEP 3:    PRINT TABLES  OR CODE     ==================*/

   write_copa( &opt_data, optkind, *pt_data, addinfo );

   if(addinfo)
          printf("C**module build_copa:write_copa ended successfully!\n");

}/* build_copa */
