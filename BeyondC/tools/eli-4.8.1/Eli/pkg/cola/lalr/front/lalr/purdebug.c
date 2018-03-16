/*
** $Id: purdebug.c,v 1.4 1997/08/29 08:38:08 mjung Exp $
*/
#ifndef DEBUG_PUR
static char rcs_id[]= "$Id: purdebug.c,v 1.4 1997/08/29 08:38:08 mjung Exp $";
#endif

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
/* File: purdebug.c	First Edit: 27.04.89	  Last Edit: 27.04.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: ??.04.89	From: Karl-Josef Prott			   */
/*									   */
/* This file is implemented only for debugging purposes!		   */
/***************************************************************************/


#ifndef purdebug_DEF
#define purdebug_DEF



#define	F_NAME	"DEBUG"	/* name of the file of debugging output */


FILE	*DEB;	/* file of debugging output */


void	DebugInit()
{
  if ( (DEB = fopen(F_NAME, "w"))  ==  (FILE *)NULL )
    {
      (void)fprintf(stderr, "Cannot open file '%s' for writing debugging \
informations.\n", F_NAME);
      exit(1);
    }

  return;
}  /* end of DebugInit() */


#define	DebugClose()	(fclose(DEB))


void	DebugState(q, state, succarr, final)
unsigned short	q;
PurStatetype	state;
ARRSEQnodetype	succarr;
nodetype	final;
{
unsigned short	index;
situationtype	*situation;
SEQnodetype	list;

  (void)fprintf(DEB, "\n\nSTATE: %d\tactlg: %d\tmainno: %d\tfinal: %d",
		q, state.actlg, state.mainno, final);
  (void)fprintf(DEB, "\tsucc(1):");
  if ( list = succarr[1] )
    do
      (void)fprintf(DEB, " %d,", list->node);
    while( list = list->next );
  else
    (void)fprintf(DEB, " nil");
  (void)fprintf(DEB, "\n");
  for ( index = 0, situation = state.item;
	index <= state.actlg;
	index++, situation++
      )
    {
      (void)fprintf(DEB, "    ruledid: %d\trulepos: %d\tl_ahead: %s\t",
		    rulenoofitem( (*situation->itptr) ),
		    situation->pos,
		    PrintSet(situation->lookahead));
      (void)fprintf(DEB, "node: %d\tsucc:", index+2);
      if ( list = succarr[index+2] )
	do
	  (void)fprintf(DEB, " %d,", list->node);
	while( list = list->next );
      else
	(void)fprintf(DEB, " nil");
      (void)fprintf(DEB, "\n");
    }  /* end of for */
}  /* end of DebugState() */


void	DebugSubgraph(termind, final, nodearr, domarr)
Indextype	termind;
nodetype	final;
Boolean		*nodearr;
ARRnodetype	domarr;
{
  nodetype	node;

  (void)fprintf(DEB, "\n\tSubgraph: %d\n\t    NODES:", termind);
  for ( node = 1; node <= final; node++ )
    if ( nodearr[node] )
      (void)fprintf(DEB, " %d,", node);
  (void)fprintf(DEB, "\n\t    DOM:");
  for ( node = final; node > 1; node = domarr[node] )
    (void)fprintf(DEB, " d(%d)=%d,", node, domarr[node]);
  (void)fprintf(DEB, "\n");

  return;
}  /* end of DebugSubgraph() */


#endif  /* of  purdebug_DEF */
