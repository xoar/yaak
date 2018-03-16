/* $Id: option_enums.h,v 4.5 2007/02/22 09:13:06 peter Exp $ */
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
/***********************************************************************\
*	option_enums.h							*
*	enumerator types for the LIGA options				*
*									*
*	Written 06/20/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#ifndef _OPT_ENUMS_H_INCL
#define _OPT_ENUMS_H_INCL


typedef	enum {
	expopt_error,
	const_attr_name, incl_attr_name,
	chain_pre_name, chain_post_name,
	includings_separate, exp_info, including_on, including_off
} expoptflag;

typedef enum {
	ordopt_error,
	part_early, part_late, top_early, top_late,
	direct_symb, trans_symb, ind_symb,
	direct_rule, trans_rule, ind_rule, part_rule,
	partition, visit_seq,
	tree_compl, tree_up, tree_down,
	arr_auto, arr_fast, for_symb, in_rule
} ordoptflag;

typedef enum {
	optopt_error,
	opt_no_incl, opt_tree,
	opt_off, opt_info, more_globals, no_vars, no_stack,
	group_vars, group_stacks, group_all, no_grouping, 
	attr_glob_stack, attr_glob_var, attr_group_stack, attr_group_var,
	attr_treenode, opt_do_incl
} optoptflag;

typedef enum {
	beopt_error,
	readable, keep_tree, free_tree, tree_top_down, exp_no_incl,
	case_split, atstacks, nodestacks, do_exp_incl
} beoptflag;

typedef enum {
	lt_error,
	exp_ltype, ord_ltype, opt_ltype, be_ltype
} listtype;

#endif

