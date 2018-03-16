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
** $Id: errtst.c,v 1.3 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: errtst.c,v 1.3 1997/08/29 08:38:08 mjung Exp $";

/******************************************************************************/
/* filename: errtst.c                         first edit   :  30 . 6 . 89     */
/* author  : Christian Zeitel                 last change  :  30 . 6 . 89     */
/******************************************************************************/

/**********************  tests the error-module error *************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void errmsg();

int main (argc, argv)

  int   argc;
  char *argv[];

{   int  mn , etn;

    mn  = atoi(argv[1]);
    etn = atoi(argv[2]);

    errmsg(mn, etn, 1, argv[3]);

}

    



    
    
