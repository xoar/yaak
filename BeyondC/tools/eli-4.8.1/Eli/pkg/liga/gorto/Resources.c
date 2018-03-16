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
/* $Id: Resources.c,v 4.1 1997/08/29 08:06:05 peter Exp $ */
static char rcs_id[]= "$Id: Resources.c,v 4.1 1997/08/29 08:06:05 peter Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Resources.c				*
 *									*
 *	CONTENTS:	Resource specification				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* This file contains the specification of the complete set of Gorto
 * resources. 
 */

#include "Misc.h"
#include "Main.h"
#include <X11/StringDefs.h>


/************************************************************************
 *			   Resource description				*
 ************************************************************************/

#define offs(n) XtOffset (tResources *, n)
XtResource resource_list[] = {
      /* Fonts */
	{"boldFont", XtCFont, XtRFontStruct, sizeof (XFontStruct *),
	 offs (bold_font), XtRString, XtDefaultFont},
	{"attributeFont", XtCFont, XtRFontStruct, sizeof (XFontStruct *),
	 offs (font), XtRString, XtDefaultFont},
	{"criticalFont", XtCFont, XtRFontStruct, sizeof (XFontStruct *),
	 offs (critical_font), XtRString, XtDefaultFont},

      /* Dependency graph layout */
	{"textPadding", "Padding", XtRInt, sizeof (int),
	 offs (text_pad), XtRImmediate, (caddr_t) 2},
	{"synthesizedIndent", "Indent", XtRInt, sizeof (int),
	 offs (synt_indent), XtRImmediate, (caddr_t) 15},
	{"symbolvPadding", "Padding", XtRInt, sizeof (int),
	 offs (symb_v_pad), XtRImmediate, (caddr_t) 10},
	{"symbolhPadding", "Padding", XtRInt, sizeof (int),
	 offs (symb_h_pad), XtRImmediate, (caddr_t) 5},
	{"arrowWidth", "ArrowWidth", XtRInt, sizeof (int),
	 offs (arrow_width), XtRImmediate, (caddr_t) 3},
	{"arrowHeight", "ArrowHeight", XtRInt, sizeof (int),
	 offs (arrow_height), XtRImmediate, (caddr_t) 9},
	{"arrowLength", "ArrowLength", XtRInt, sizeof (int),
	 offs (arrow_length), XtRImmediate, (caddr_t) 30},
	{"depColumnWidth", "DepColumnWidth", XtRInt, sizeof (int),
	 offs (dep_width), XtRImmediate, (caddr_t) 3},
	{"depFaseLength", "DepFaseLength", XtRInt, sizeof (int),
	 offs (dep_fase), XtRImmediate, (caddr_t) 5},

      /* Boolean flags */
	{"sortProdList", "SortList", XtRBoolean, sizeof(Boolean),
	 offs (sort_prod_list), XtRImmediate, False},
	{"sortSymbolList", "SortList", XtRBoolean, sizeof(Boolean),
	 offs (sort_symb_list), XtRImmediate, False},
	{"leftSymbol", "LeftSymbol", XtRBoolean, sizeof(Boolean),
	 offs (left_symbol), XtRImmediate, False},
	{"makeTitleBars", "MakeTitleBars", XtRBoolean, sizeof (Boolean),
	 offs (make_titles), XtRImmediate, (caddr_t) False},
	{"showPartDeps", "ShowPartDeps", XtRBoolean, sizeof (Boolean),
	 offs (show_part_deps), XtRImmediate, (caddr_t) False},

      /* Colors */
	{"directDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (d_pixel), XtRString, "XtDefaultForeground"},
	{"inducedDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (i_pixel), XtRString, "XtDefaultForeground"},
	{"arrangedDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (a_pixel), XtRString, "XtDefaultForeground"},
	{"arrangedInducedDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (ai_pixel), XtRString, "XtDefaultForeground"},
	{"partitionedDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (p_pixel), XtRString, "XtDefaultForeground"},
	{"inducedPartitionedDepColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (ip_pixel), XtRString, "XtDefaultForeground"},

	{"attrColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (at_pixel), XtRString, "XtDefaultForeground"},
	{"includingAttrColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (at_i_pixel), XtRString, "XtDefaultForeground"},
	{"constituentAttrColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (at_co_pixel), XtRString, "XtDefaultForeground"},
	{"chainAttrColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (at_ch_pixel), XtRString, "XtDefaultForeground"},
	{"symbolColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (symb_pixel), XtRString, "XtDefaultForeground"},
	{"visitColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (visit_pixel), XtRString,"XtDefaultForeground"},
	{"conditionColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (cond_pixel), XtRString,"XtDefaultForeground"},
	{"lineColor", XtCForeground, XtRPixel, sizeof(Pixel),
	 offs (line_pixel), XtRString, "XtDefaultForeground"},

      /* File names */
        {"lidoName", "LidoName", XtRString, sizeof(String),
         offs (lido_name), XtRString, NULL},
	{"inputName", "InputName", XtRString, sizeof(String),
	 offs (input_name), XtRString, NULL},
	{"outputName", "OutputName", XtRString, sizeof(String),
	 offs (output_name), XtRString, NULL},
	{"controlName", "ControlName", XtRString, sizeof(String),
	 offs (control_name), XtRString, NULL},
	{"lclName", "LclName", XtRString, sizeof(String),
	 offs (lcl_name), XtRString, NULL},

      /* Stuff */
        {"selectWidth", "SelectWidth", XtRInt, sizeof(int),
         offs (select_width), XtRImmediate, (caddr_t) 3},
	{"wmPushDown", "WmPushDown", XtRInt, sizeof(int),
	 offs (wm_push_down), XtRImmediate, (caddr_t) 0},

      /* Strings */
	{"emptyListString", "EmptyListString", XtRString, sizeof(String),
	 offs (str_empty), XtRImmediate, (caddr_t) "<empty>"},
	{"directRuleState", "DirectRuleState", XtRString, sizeof(String),
	 offs (str_direct_rules), XtRImmediate, (caddr_t) "direct rules"},
	{"directSymbolState", "DirectSymbolState", XtRString, sizeof(String),
	 offs (str_direct_symbols), XtRImmediate, (caddr_t) "direct symbols"},
	{"optionState", "OptionState", XtRString, sizeof(String),
	 offs (str_options), XtRImmediate, (caddr_t) "order options"},
	{"transitiveState", "TransitiveState", XtRString, sizeof(String),
	 offs (str_transitive), XtRImmediate, (caddr_t) "transitive graphs"},
	{"inducedState", "InducedState", XtRString, sizeof(String),
	 offs (str_induced), XtRImmediate, (caddr_t) "induced graphs"},
	{"arrangeOptionState", "ArrangeOptionState", XtRString, sizeof(String),
	 offs (str_arrange_option), XtRImmediate, (caddr_t) "arrange option"},
	{"arrangedState", "ArrangedState", XtRString, sizeof(String),
	 offs (str_arrange), XtRImmediate, (caddr_t) "arranged graphs"},
	{"partitionState", "PartitionState", XtRString, sizeof(String),
	 offs (str_partition), XtRImmediate, (caddr_t) "partitions"},
	{"partitionedState", "PartitionedState", XtRString, sizeof(String),
	 offs (str_partitioned), XtRImmediate, (caddr_t) "partitioned graphs"},
	{"visitSeqState", "VisitSeqState", XtRString, sizeof(String),
	 offs (str_visitseq), XtRImmediate, (caddr_t) "visit sequences"},
	{"lifetimeState", "LifetimeState", XtRString, sizeof(String),
	 offs (str_lifetime), XtRImmediate, (caddr_t) "lifetimes"},
	{"infoState", "InfoState", XtRString, sizeof(String),
	 offs (str_info), XtRImmediate, (caddr_t) "display information"},
	{"hideState", "HideState", XtRString, sizeof(String),
	 offs (str_hide), XtRImmediate, (caddr_t) "hide attribute"},
	{"unhideState", "UnhideState", XtRString, sizeof(String),
	 offs (str_unhide), XtRImmediate, (caddr_t) "unhide attribute"},
	{"directDisplay", "DirectDisplay", XtRString, sizeof(String),
	 offs (str_direct_dpy), XtRImmediate, (caddr_t) "direct display"},
	{"transitiveDisplay", "TransitiveDisplay", XtRString, sizeof(String),
	 offs (str_transitive_dpy), XtRImmediate,(caddr_t)"transitive display"},
	{"inducedDisplay", "InducedDisplay", XtRString, sizeof(String),
	 offs (str_induced_dpy), XtRImmediate, (caddr_t) "induced display"},
	{"arrangedDisplay", "ArrangedDisplay", XtRString, sizeof(String),
	 offs (str_arranged_dpy), XtRImmediate, (caddr_t) "arranged display"},
	{"partDisplay", "PartDisplay", XtRString, sizeof(String),
	 offs (str_part_dpy), XtRImmediate, (caddr_t) "partition display"},
	{"visitSeqDisplay", "VisitSeqDisplay", XtRString, sizeof(String),
	 offs (str_vs_dpy), XtRImmediate, (caddr_t) "visit sequence display"},
	{"constructIDLState", "ConstructIDLState", XtRString, sizeof(String),
	 offs (str_idl), XtRImmediate, (caddr_t) "idl structure"},
	{"ouputState", "OuputState", XtRString, sizeof(String),
	 offs (str_output), XtRImmediate, (caddr_t) "output files"},
	{"finishState", "FinishState", XtRString, sizeof(String),
	 offs (str_finish), XtRImmediate, (caddr_t) "leave gorto"},
	{"noRecomputeString", "NoRecomputeString", XtRString, sizeof(String),
	 offs (str_no_recomp), XtRImmediate, (caddr_t) "not necessary"},
	{"ruleString", "RuleString", XtRString, sizeof(String),
	 offs (str_rule), XtRImmediate, (caddr_t) "rule"},
	{"symbolString", "SymbolString", XtRString, sizeof(String),
	 offs (str_symbol), XtRImmediate, (caddr_t) "symbol"},
	{"transferString", "TransferString", XtRString, sizeof(String),
	 offs (str_transfer), XtRImmediate, (caddr_t) "transfer dependency"},
	{"includingString", "IncludingString", XtRString, sizeof(String),
	 offs (str_including), XtRImmediate, (caddr_t) "including dependency"},
	{"constituentString", "ConstituentString", XtRString, sizeof(String),
	 offs (str_constituent),XtRImmediate,(caddr_t)"constituent dependency"},
	{"chainString", "ChainString", XtRString, sizeof(String),
	 offs (str_chain), XtRImmediate, (caddr_t) "chain dependency"},
	{"unknownDepString", "UnknownDepString", XtRString, sizeof(String),
	 offs (str_unknown_dep), XtRImmediate, (caddr_t) "unknown dependency"},
	{"cyclicString", "CyclicString", XtRString, sizeof(String),
	 offs (str_cyclic), XtRImmediate, (caddr_t) "cyclic"},
	{"arrangedString", "ArrangedString", XtRString, sizeof(String),
	 offs (str_arranged), XtRImmediate, (caddr_t) "arranged"},
	{"changedString", "ChangedString", XtRString, sizeof(String),
	 offs (str_changed), XtRImmediate, (caddr_t) "changed"},
	{"partitionedString", "PartitionedString", XtRString, sizeof(String),
	 offs (str_part), XtRImmediate, (caddr_t) "partitioned"},
	{"visitSeqString", "VisitSeqString", XtRString, sizeof(String),
	 offs (str_vs), XtRImmediate, (caddr_t) "visit-sequence"},
	{"forcedString", "ForcedString", XtRString, sizeof(String),
	 offs (str_forced), XtRImmediate, (caddr_t) "forced"},
	{"cycleMessage", "CycleMessage", XtRString, sizeof(String),
	 offs (cycle_msg), XtRImmediate, (caddr_t) "would yield cycle"},
	{"noBmNFMessage", "NoBmNFMessage", XtRString, sizeof(String),
	 offs (no_bmnf_msg), XtRImmediate, (caddr_t) "no BmNF occurence"},
};
#undef offs


PUBLIC tResources Res;
PUBLIC int AttrHeight, CrAttrHeight;


/************************************************************************
 *			       ReadResources				*
 ************************************************************************/

/* Fills the global struct Res and computes AttrHeight and CrAttrHeight. */

PUBLIC void ReadResources()
{
	XtGetApplicationResources (Toplevel, (caddr_t) &Res,
				resource_list, XtNumber (resource_list),
				(ArgList)NULL, 0);
	AttrHeight   = Res.font->ascent + Res.font->descent +
			2*Res.text_pad + 1;
	CrAttrHeight = Res.critical_font->ascent + Res.critical_font->descent +
			2*Res.text_pad + 1;
} /* ReadResources() */
