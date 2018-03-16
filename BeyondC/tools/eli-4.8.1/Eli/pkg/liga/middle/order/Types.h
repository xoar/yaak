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
/* $Id: Types.h,v 1.2 1997/08/29 09:16:01 peter Exp $ */
#ifndef TYPES_H
#define TYPES_H

/*********
Includes
*********/

#ifndef GORTO

#include <string.h>
#include "LIGA.h"
#include "LIGAMacros.h"

#else

#include <string.h>
#include <X11/Intrinsic.h>
#define String IDLString
#define Boolean IDLBoolean
#include "LIGA.h"
#include "LIGAMacros.h"
#undef String
#undef Boolean

#endif

/* set.h only to provide type BITVECTOR: */
#include "set.h"
#include "bool.h"

/*****************
Macro Definitions
*****************/

#define WORD_LENGTH (sizeof(unsigned int)*8)

/* ref_tab item tags */
#define EMPTY -1
#define SYMB 0
#define PROD 1
#define ATTR 2


/* graph states */
#define DIRECT 		0
#define TRANSITIVE	1
#define INDUCED		2
#define ARRANGED	3
#define PARTITIONED 	4

/* visit classes */
#define	VSASSIG 	0
#define VSCOND 		1
#define VSVISIT 	2


#ifdef GORTO
/* Dependency types */
#define T_DIR           0x1     /* direct                        */
#define T_TRAN          0x2     /* transitive                    */
#define T_IND           0x4     /* induced                       */
#define T_ARR           0x8     /* arranged                      */
#define T_PART          0x10    /* partitioned                   */
#define T_MASK          0x1f    /* mask including all bits       */

/* Flags used to set marks at dependencies */
#define T_MARK          0x20    /* dependency marked             */
#define T_FOLLOWED      0x40    /* origin marked                 */

/* States of attributes */
#define A_HIDDEN        0x1     /* hidden attribute              */
#define A_CRITICAL      0x2     /* critical attribute            */

/* States of symbols and productions */
#define S_CYCLIC        0x1     /* cyclic                        */
#define S_ARRANGED      0x2     /* arranged                      */
#define S_CHANGED       0x4     /* changed                       */
#define S_PARTITIONED   0x8     /* partitions computed           */
#define S_VISIT_SEQ     0x10    /* visit sequence computed       */
#define S_FORCED        0x20    /* partition forced              */
#define S_REDISPLAYED   0x40    /* redisplay already forced      */
#endif

/***************
Type Definitions
***************/

typedef BITVECTOR *BITMATRIX;	/* BITMATRIX is the internal data
				 * representation of attribute dependency
				 * graphs */

/*************************************************
Data Structure for Symbol Occurence Nodes in Rules
*************************************************/

typedef struct slnode
{/* node structure of the list of symbol occurrences of a production */
   int sid;	/* did of the symbol */
   int pid;	/* did of the production */
   int start_row;	/* the starting row of the attribute occurrences of
			 * this symbol occurrence in the init-dp */
   int start_col;	/* the starting colume of the attribute occurrences
			 * of this symbol occurrence in the init-dp */
   struct slnode *right;	/* right points to the next symbol in the
				 * production */
   struct slnode *down;	/* down points to the next symbol with the same sid  */
#ifdef GORTO
   Position y;  /* y-coordinate in the drawn graph */
   short ord;   /* number of symbol instance     */
#endif
} SLNODE;

/***************************************************
 Data structures used for computing visit sequences
****************************************************/

typedef struct
{
   int aid, apos; /* attribute did and rel. pos    */
   int sid, sno;  /* symbol did and number         */
   Call idldef;   /* pointer to the idl definition */
} ASSIGINFO;

typedef struct
{
   Call idldef;	/* pointer to the idl definition */
} CONDINFO;

typedef struct
{
   BITVECTOR evalset;
   int vssid; /* symbol did */
   int vssno; /* symbol number */
   int vsord; /* number of visit */
} VISITINFO;

typedef struct vselem
{
   BITVECTOR deps;      /* attribute dependencies        */
   struct vselem *next; /* next elem in visit-sequence   */
   int vscls;	        /* VSASSIG | VSCOND | VSVISIT */
   union
   {
      ASSIGINFO assig;
      CONDINFO cond;
      VISITINFO visit;
   } vsinfo;
} VSELEM;

typedef VSELEM *VSPTR;

/******************************************
 Data Structures for the Reference Table
*******************************************/

#ifdef GORTO
/******************************************
 Data types for the Gorto variant only
*******************************************/

/************************************************************************
 *		Internal representation of arrange options		*
 ************************************************************************/

typedef struct arrange_node
{
   String comment;
   int did;
   SLNODE *fromNode, *toNode;
   int fromAid, toAid;
   struct arrange_node *next;
} ARRANGE_NODE;


/************************************************************************
 *     Representation of dependencies and dependency graphs for GORTO	*
 ************************************************************************/

/* detail information for direct dependencies */
typedef struct
{
   int row;	/* position in the lido source */
} DIRECT_DETAIL;

/* detail information for arranged dependencies */
typedef union
{
   ARRANGE_NODE *node;	/* pointer to internal arrange node */
} ARRANGE_DETAIL;

/* detail information for induced dependencies */
typedef struct
{
   SLNODE *from;	/* the symbol instance from which this dependency was
			 * induced	      */
} INDUCED_DETAIL;

/* detail information for transitive dependencies */
typedef struct
{
   int over_atno;
} TRANSITIVE_DETAIL;

/* detail information */
typedef union
{
   DIRECT_DETAIL direct;
   ARRANGE_DETAIL arrange;
   INDUCED_DETAIL induced;
   TRANSITIVE_DETAIL transitive;
} DETAIL;

/* representation of a dependency */
typedef char DEPENDENCY;

/* representation of a dependency matrix */
typedef DEPENDENCY *DEP_VECTOR;
typedef DEP_VECTOR *DEP_MATRIX;
typedef DETAIL *DET_VECTOR;
typedef DET_VECTOR *DET_MATRIX;

/* production activation record */
typedef struct
{
   Position lhs_x, rhs_x;	/* x coordinate of lhs and rhs	 */
   Widget widget, state;	/* reference to created widgets	 */
} PAR;

/* symbol activation record */
typedef struct
{
   Position x, y;	/* x,y coordinates in the graph	 */
   Dimension width, height;	/* width and height		 */
   Widget widget, state;	/* reference to created widgets	 */
} SAR;

/* visit-sequence activation record */
typedef struct
{
   Position x, y;	/* x,y coordinates of vs	 */
   Widget widget;	/* reference to created widgets	 */
} VSAR;

/* attribute lifetime information */
typedef struct
{
   VSPTR last_local;	/* last local use		 */
   VSPTR last_global;	/* last global use		 */
} LIFETIME;

/* visit-sequence information record */
typedef struct
{
   VSAR *vsar;	/* activation record		 */
   String geometry;	/* x,y position of window	 */
   Dimension width, height;	/* width & height 		 */
   int length;	/* length of visit-sequence	 */
   LIFETIME *lifetimes;	/* lifetimes of attributes	 */
   VSPTR marked_elem;	/* marked element of vs		 */
} VSINFO;
#endif


/************************************************************************
 *		   Type definitions for ref_tab entries			*
 ************************************************************************/

typedef struct attrdef
{/* structure of attribute entry in the ref. table */
   Attrdef attr_def;	/* reference to the liga definition from IDL */
   int pos;	/* relative position in the bit vector */
   int bottomup;/* 1 if attribute is to be computed bottom-up */
   int part;	/* the partition no. used as "late" first */
   int symbdid; /* the did of the symbol the attr bleongs to */
#ifdef GORTO
   bool cyclic;        /* added UK */
   struct attrdef *next, *last;	/* other attrs of this symbol	 */
   int up_space;	/* available space in up dir.	 */
   int down_space;	/* available space in down dir.	 */
   short state;	/* A_HIDDEN | A_CRITICAL	 */
   Dimension width;	/* width of drawn name		 */
   int life_vsno;	/* global end of lifetime	 */
   SLNODE *life_node;	/* symbol instance of last use	 */
#endif
} ATTRENTRY;

typedef struct
{/* structure of symbol entry in the ref. table */
   Symb symb_def;	/* reference to the liga definition from IDL */
   SLNODE *hddown;	/* head pointer of symbol list with the same did */
   int attr_num;	/* number of attributes of this symbol */
   int part_num;	/* number of partitioned attribute sets */
#ifndef GORTO
   bool cyclic;
   bool changed;
   BITMATRIX init_ds;	/* initial attr. dependency graph of the symbol,
			 * which will remain unchanged.  */
   BITMATRIX ds;	/* dependency graph of this symbol which will be
			 * evolved. */
#else
   short state;	/* state of this symbol		 */
   Dimension width, height;	/* size of drawn symbol		 */
   ATTRENTRY *first_attr;	/* first attribute		 */
   ATTRENTRY *last_attr;	/* last attribute		 */
   DEP_MATRIX ds;	        /* dependency graph		 */
   DET_MATRIX ds_detail;	/* dependency details		 */
   int length;	                /* number of not hidden attrs	 */
   SAR *sar;	                /* symbol activation record	 */
   String geometry;	        /* x,y position of the window	 */
#endif
} SYMBENTRY;

typedef struct
{/* structure of production entry in the ref. table */
   Prod prod_def;	/* reference to the liga definition from IDL */
   SEQAttrrule computations; /* sequence of computations */
   int check_row;	/* index of last row of init_dp, which is used to
			 * check the well-definedness of AG */
   int check_col;	/* index of last word of init_dp and dp */
   SLNODE *hdright;	/* head pointer of symbol list of the production */
   VSPTR visitseq;	/* head pointer to the list of visit sequences */
#ifndef GORTO
   bool cyclic;
   bool changed;
   BITMATRIX init_dp;	/* initial attr. dependency graph of the production,
			 * which will remain unchanged.  */
   BITMATRIX dp;	/* dependency graph of this production which will be
			 * evolved. */
#else
   short state;	        /* state of this production	 */
   DEP_MATRIX dp;	/* dependency graph		 */
   DET_MATRIX dp_detail;/* dependency details		 */
   Dimension dep_width;	/* maximum dependency width	 */
   Dimension rhs_width;	/* width of rhs			 */
   Dimension rhs_height;/* height of rhs		 */
   PAR *par;	        /* production activation record	 */
   String geometry;	/* x,y position of the window	 */
   VSINFO *vs;	        /* visit-sequence information	 */
#endif
} PRODENTRY;

typedef struct
{
   int etag;  /* ATTR | SYMB | PROD */
   union
   {
      SYMBENTRY symb;
      PRODENTRY prod;
      ATTRENTRY attr;
   } entry;
} ALLENTRIES;

#endif
