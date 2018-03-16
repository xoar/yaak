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
/* $Id: Misc.h,v 4.4 1999/07/26 08:38:09 mjung Exp $ */

/*======================================================================*
 *									*
 *	FILE:		Misc/Misc.h					*
 *									*
 *	CONTENTS:	Shared Header-File for the directory Misc	*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/


#include "../middle/order/Gorto.h"
#include "../ligascel/eliproto.h"

#define PRIVATE			static
#define PUBLIC
#define EXTERN			extern

#include <stdio.h>
EXTERN FILE *In;        /* input file   */
EXTERN FILE *Out;       /* graph output */
EXTERN FILE *ProtocolFile;
EXTERN FILE *LCL;
EXTERN FILE *BuProdFile;

EXTERN short graphstate_hint;

/************************************************************************
 *			    Macro Definitions				*
 ************************************************************************/

#ifdef MAX
#undef MAX
#endif

#ifdef MIN
#undef MIN
#endif

#define MAX(a,b)		(((a)>(b)) ? (a) : (b))
#define MIN(a,b)		(((a)<(b)) ? (a) : (b))

#define PE(did)			ref_tab[did].entry.prod
#define SE(did)			ref_tab[did].entry.symb
#define AE(did)			ref_tab[did].entry.attr

#define RedisplayWidget(w)	XClearArea(dpy,XtWindow(w),0,0,0,0,True)

#if !defined(PROTO_OK)
#define const
#endif

/************************************************************************
 *				Arrange.c				*
 ************************************************************************/

EXTERN void MakeArrangeNode();
	/* int		did;			*/
	/* SLNODE	*fromNode, *toNode;	*/
	/* int		fromAid, toAid;		*/
	/* Boolean	introduce;		*/

EXTERN void ArrangeComment();
	/* String	comment;		*/

EXTERN void RemoveArrangeNode();
	/* ARRANGE_NODE	*to_remove;		*/

EXTERN void UnarrangeAttr();
	/* ATTRENTRY	*ae;			*/

EXTERN void ResetArrangeList();

EXTERN void IntroduceArrangeList();

EXTERN Boolean ArrangeListEmpty();

EXTERN void WriteArrangeList();


/************************************************************************
 *			       Bitmaps.c				*
 ************************************************************************/

EXTERN Pixmap CheckMarkBitmap, CascadeBitmap, IconBitmap;

EXTERN void LoadBitmaps();


/************************************************************************
 *			       DepLayout.c				*
 ************************************************************************/

EXTERN Dimension NormalDepWidth();
	/* int	length;				*/

EXTERN Dimension InducedDepWidth();
	/* int	length;				*/

EXTERN void DepInitiate();
	/* Window	w;			*/
	/* Region	r;			*/
	/* Position	x, y;			*/
	/* Boolean	vs;			*/

EXTERN Boolean DoDep();
	/* DEPENDENCY	*dep;			*/

	/* Position	x1, y1;			*/
	/* int		no1;			*/
	/* Dimension	width1;			*/
	/* Boolean	synt1;			*/

	/* Position	x2, y2;			*/
	/* int		no2;			*/
	/* Dimension	width2;			*/
	/* Boolean	synt2;			*/

	/* int		down1, up1, length1;	*/
	/* Boolean	lhs;			*/


/************************************************************************
 *				Drawing.c				*
 ************************************************************************/

typedef enum { Dot, Dash, Solid } DASH_STYLE;

EXTERN Display	*dpy;
EXTERN GC	gc;
EXTERN int	AttrHeight, CrAttrHeight;
EXTERN XSegment	*LineSegments, *CurrentSegment;

#define NewSegment(xx1,yy1,xx2,yy2)	\
	{ \
		CurrentSegment->x1 = xx1; \
		CurrentSegment->y1 = yy1; \
		CurrentSegment->x2 = xx2; \
		CurrentSegment->y2 = yy2; \
		CurrentSegment ++; \
	}

EXTERN void InitDrawing();
	/* int		max_segments;	*/

EXTERN void SetLineAttrs();
	/* unsigned	line_width;	*/
	/* DASH_STYLE	line_style;	*/

EXTERN void SetForeground();
	/* Pixel	col;		*/

EXTERN void SetAttrGCElems();
	/* ATTRENTRY	*ae;		*/

EXTERN void SetDepGCElems();
	/* short	type;		*/


/************************************************************************
 *				PathFind.c				*
 ************************************************************************/

EXTERN void ProdFindPath();
	/* PRODENTRY	*prod;		*/
	/* SLNODE	*node1, *node2;	*/
	/* ATTRENTRY	*ae1, *ae2;	*/
	/* int		follow_induced;	*/

EXTERN void SymbFindPath();
	/* SYMBENTRY	*symb;		*/
	/* ATTRENTRY	*ae1, *ae2;	*/
	/* int		follow_induced;	*/


/************************************************************************
 *			       Resources.c				*
 ************************************************************************/

/* Resource type */
typedef struct rc {
      /* Fonts */
        XFontStruct     *bold_font, *font, *critical_font;

      /* Paddings */
        int             text_pad, synt_indent, symb_v_pad, symb_h_pad,
			arrow_width, arrow_height, arrow_length;

      /* Boolean flags */
        Boolean         sort_prod_list, sort_symb_list, left_symbol;
	Boolean		make_titles, show_part_deps;

      /* Colors */
	Pixel		d_pixel, a_pixel, i_pixel, p_pixel, ai_pixel, ip_pixel,
			at_pixel, at_i_pixel, at_co_pixel, at_ch_pixel,
			symb_pixel, visit_pixel, cond_pixel, line_pixel;

      /* Dependency layout */
        int             dep_width, dep_fase;

      /* File names */
        String          lido_name, input_name, output_name,
			control_name, lcl_name;

      /* Stuff */
        int             select_width;
	int		wm_push_down;

      /* Strings */
	String		str_empty, str_direct_rules, str_direct_symbols,
			str_options, str_transitive, str_induced, 
			str_arrange_option, str_arrange, str_partition,
			str_partitioned, str_visitseq, str_lifetime, str_info,
			str_hide, str_unhide, str_direct_dpy,
			str_transitive_dpy, str_induced_dpy, 
			str_arranged_dpy, str_part_dpy, str_vs_dpy,
			str_idl, str_output, str_finish, str_no_recomp, str_rule,
			str_symbol, str_transfer, str_including, 
			str_constituent, str_chain, str_unknown_dep,
			str_cyclic, str_arranged, str_changed, str_part,
			str_vs, str_forced, cycle_msg, no_bmnf_msg;
} tResources;

EXTERN tResources Res;

EXTERN void ReadResources();


/************************************************************************
 *				  Util.c				*
 ************************************************************************/

/* Public variables */
EXTERN String		ProgName;
EXTERN XtAppContext	app_context;

/* Functions */
EXTERN void ProdMaskDependencies();
	/* PRODENTRY	*prod;		*/
	/* short	bitmask;	*/

EXTERN void SymbMaskDependencies();
	/* SYMBENTRY	*symb;		*/
	/* short	bitmask;	*/

EXTERN void ProdRemoveDependencies();
	/* PRODENTRY	*prod;		*/
	/* short	bitmask;	*/

EXTERN void SymbRemoveDependencies();
	/* SYMBENTRY	*symb;		*/
	/* short	bitmask;	*/

EXTERN void RedisplayGraphOfDid();
	/* int		didl		*/

EXTERN void PartDepsCB();
	/* Callback			*/
