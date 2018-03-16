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

/*
** $Id: error.c,v 1.7 2007/02/23 10:53:13 peter Exp $
*/
static char rcs_id[]= "$Id: error.c,v 1.7 2007/02/23 10:53:13 peter Exp $";

/******************************************************************************/
/* filename: error.c                          first edit   :  29 . 6 . 89     */
/* author  : Christian Zeitel                 last change  :  10 . 7 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the implementation of the unique error-reporting module for the    *
 *  parsergenerator-backend and the tool cmrsasx.  		               *
 *									       *
 ******************************************************************************/
 
#include<stdio.h>
#include<stdlib.h>

#include "errtxt.h" /* contains the vectors with errortexts and modulenames */



void errmsg( modulenumber, errtextnumber, abort, addinfo )

     short modulenumber,
           errtextnumber,
           abort;
     char *addinfo;

    /*   Reports an error on file stderr and returns to the calling module, if 
     *   possible.
     *
     *    on entry-
     *       modulenumber contains the code of the module reporting the error. 
     *       errtextnumber contains the code of the errortext, which is printed
     *       to stderr.
     *       If abort is not zero, the program is aborted with exit-code 1.
     *       addinfo contains an additional textstring to specify the
     *       errormessage.
     *    on exit-
     *       the errormessage is printed on file stderr. If the calling module 
     *       can't continue its execution, the whole program ist aborted with
     *       exit-code 1 ( abort is set to a value not equal zero ).
     *    
     ***/

     { 
        void errmsg();
       
        if( (modulenumber > maxmn)  || (errtextnumber > maxetn) ||
            (modulenumber < 0) || (errtextnumber < 0)  ) 
                errmsg(0, 0, 1, "");/* received wrong errmsg */
#ifdef	DEBUG
        fprintf( ( abort ? stderr : stdout),
		 "%c%d**module %s: %s %s   !\n",
		 ( abort ? 'E' : 'W'),
		 errtextnumber,
		 module[modulenumber],
		 errtext[errtextnumber], 
		 addinfo
	       );

        if(abort) {fprintf(stderr, "program aborted with errors!\n"); exit(1); }
#else
        fprintf( ( abort ? stderr : stdout),
		 "ERROR: %s %s!\n",
		 errtext[errtextnumber], 
		 addinfo
	       );

        if(abort) { exit(1); }
#endif
     }/* errmsg */
