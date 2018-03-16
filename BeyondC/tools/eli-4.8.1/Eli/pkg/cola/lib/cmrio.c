/*
** $Id: cmrio.c,v 1.3 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: cmrio.c,v 1.3 1997/08/29 08:38:08 mjung Exp $";

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

/***************************************************************************/
/* File: cmrio.c	First Edit: 17.10.88	  Last Edit: 08.11.88      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/***************************************************************************/


#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "cmrlib.h"
#include "cmrio.h"

  
/* Exported Routines: */

ERR cmrlib_write(filename, tool_info, c)
char *filename;
char *tool_info;
p_comar c;
{
  FILE	*f;

  if ( (f = fopen(filename,"w")) == (FILE *)NULL )
    return(CMR_OPNERR);

  (void)fprintf(f, "--%s\n", tool_info);
  OUTPUT(f,c);

  (void)fclose(f);

  return(CMR_SUCCESS);
}		/* cmrlib_write */


ERR cmrlib_read(filename, tool_info, c)
char *filename;
char *tool_info;
p_comar *c;
{
  FILE *f;
  int nl;

  if ((f = fopen(filename, "r")) == (FILE *)NULL)
    return(CMR_OPNERR);

  /* obtain tool information */
  if (fgetc(f) != '-' || fgetc(f) != '-' ||
		fgets(tool_info, MAX_TOOL_INFO, f) == (char *)NULL)
	return(CMR_RDERR);
  nl = strlen(tool_info) - 1;
  if (tool_info[nl] == '\n')
    tool_info[nl] = '\0';

  *c = INPUT(f);

  return(CMR_SUCCESS);
}		/* cmrlib_read */


