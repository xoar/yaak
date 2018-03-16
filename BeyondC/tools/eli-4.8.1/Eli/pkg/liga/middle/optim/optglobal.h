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
/* $Id: optglobal.h,v 4.4 2000/04/03 12:49:38 peter Exp $ */
/************************************************/
/* Version : 1.0				 */
/* Module  : optglobal.h			 */
/* Contains global declarations		 */
/************************************************/


/************************************************/
/* global variables		 */
/************************************************/

extern AttrEval ligaroot;
extern Visit_Sequences optimroot;

extern FILE *ProtocolFile;
extern FILE *optim_optionfile1, *optim_optionfile2;

extern OptCollect optim_opts;


extern Boolean optimize_option;
extern Boolean protocol_option;
extern Boolean exp_incl_option;
extern Boolean no_var_option;
extern Boolean no_stack_option;
extern Boolean no_grouping_option;
extern Boolean var_group_option;
extern Boolean stack_group_option;
extern Boolean group_all_option;
extern Boolean var_list_option;
extern Boolean stack_list_option;
extern Boolean tree_list_option;
extern Boolean var_group_list_option;
extern Boolean stack_group_list_option;
extern Boolean grammar_option;

extern int max_definitions;

extern int neverusedcounter;

extern int pushcounter, popcounter, topcounter;
extern int swapcounter, clobbercounter;
extern int globvarcounter, globstackcounter, treeattrcounter, voidcounter;
extern int vargroupcounter, stackgroupcounter;

extern int totalassigns, identassigns;

extern int inclattrcounter;

/************************************************/
/* defines                   */
/************************************************/

#define		COUNTING_ATTR	1

#define         CHAINATTR           3

#define		MAX_VISITS	   10

#ifndef	FALSE
#define		FALSE	0
#endif
#ifndef	TRUE
#define		TRUE	(!FALSE)
#endif

#define		NOT_EXPANDED_INCLUDING	-1

#define		LEAVE	0
#define         VISIT   1
#define         EVAL    2

#define		PARENT_SYMBOL	0

#define		PFBPFA		1
#define		PFAPFB		2
#define		PPFA		3

#define		CONDITION      -1

#define		STORE_COUNTING_ATTR  4

#define		GLOB_VAR_OPTION		0
#define		GLOB_STACK_OPTION	1
#define		TREE_NODE_OPTION	2
#define		VAR_GROUP_OPTION	3
#define		STACK_GROUP_OPTION	4

#define		VAR_GROUP_LIST		3
#define		STACK_GROUP_LIST	4
