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
/* $Id: Main.h,v 4.2 1997/08/29 08:06:05 peter Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Main/Main.h					*
 *									*
 *	CONTENTS:	Shared Header-File for the directory Main	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


/************************************************************************
 *				Actions.c				*
 ************************************************************************/

EXTERN void ActionMenuPopup();
	/* Action */

EXTERN void ActionCloseWindow();
	/* Action */


/************************************************************************
 *				MainList.c				*
 ************************************************************************/

EXTERN void ProdUpdateList();
EXTERN void SymbUpdateList();

EXTERN void ProdCreateList();
	/* Widget	hpaned, father;	*/

EXTERN void SymbCreateList();
	/* Widget	hpaned, father;	*/

EXTERN void SetListMasks();


/************************************************************************
 *			       MainWindow.c				*
 ************************************************************************/

EXTERN Widget Toplevel, StateLabel, LidoMenuItem;

EXTERN void CreateWidgets();


/************************************************************************
 *				 Order.c				*
 ************************************************************************/

/* Possible states of this tool */
typedef enum {
	DirectRules,		/* Constructing direct rule graphs	*/
	DirectSymbols,		/* Constructing direct symbol graphs	*/
	ReadOrderOptions,	/* Reading order options		*/
	TransitiveGraphs,	/* Constructing transitive graphs	*/
	InducedGraphs,		/* Constructing induced graphs		*/
	ArrangeOptions,		/* Introducing arrange options		*/
	ArrangedGraphs,		/* Computing arranged graphs		*/
	Partitions,		/* Computing partitions			*/
	PartitionedGraphs,	/* Constructing partitioned graphs	*/
	VisitSequences,		/* Constructing visit sequences		*/
	Lifetimes,		/* Computing attribute lifetimes	*/
	ReftabAdditions,	/* Computing ref_tab additions		*/

	HideAttribute,		/* Awaiting an attribute name to hide	*/
	UnHideAttribute,	/* Awaiting an attribute name to unhide	*/
	
	DpyDirectGraphs,	/* Displaying direct graphs		*/
	DpyTransitiveGraphs,	/* Displaying transitive graphs		*/
	DpyInducedGraphs,	/* Displaying induced graphs		*/
	DpyArrangedGraphs,	/* Displaying arranged graphs		*/
	DpyPartitionedGraphs,	/* Displaying partitioned graphs	*/
	DpyVisitSequences,	/* Displaying visit sequences		*/

	ConstructOutput,	/* Constructing IDL output structure	*/
	Output,			/* Writing output files			*/
	Finish			/* Writing output files			*/
} STATE;

EXTERN FILE *LCL;
EXTERN STATE state;
EXTERN Boolean Cyclic, DepRemoved;

EXTERN void SetState();

EXTERN void CallOrder();

EXTERN void RecomputeCB();
	/* Callback		*/

EXTERN void UpdatePartition();
	/* SYMBENTRY	*symb;	*/

EXTERN void UpdateVisitSequence();
	/* PRODENTRY	*prod;	*/

EXTERN void QuitCB();
	/* Callback		*/

EXTERN void CtlQuitCB();
	/* Callback		*/


/************************************************************************
 *			     OrderStrategy.c				*
 ************************************************************************/

EXTERN	bool	AUTOMATICALLY, ARRANGE, PARSE_TIME,
		TREE_BOTTOM_UP, TREE_TOP_DOWN, TREE_COMPLETE,
                DEFAULT_TREE_COMPLETE;
EXTERN	bool	PART_EARLY, PART_LATE, PART_BRANCH_AND_BOUND;

EXTERN void CreateTopoMenu();
	/* Widget	father;	*/

EXTERN void CreatePartMenu();
	/* Widget	father;	*/


/************************************************************************
 *			         Reftab.c				*
 ************************************************************************/

EXTERN void ComputeRefTabAdditions();
