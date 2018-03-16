/* $Id: data.h,v 1.15 1999/10/20 04:56:06 tony Exp $ */
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au
   BK   Basim Kadhim      kadhim@cs.colorado.edu
   WMW  William M. Waite  William.Waite@Colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   22-Jul-1992  AMS  Added record of filename that line was in to ln_t.
                     Added global filename variable.
   26-Jul-1992  AMS  Added support for remembering filename and line numbers.
   26-Jul-1992  AMS  Added RCS id.
   03-Aug-1992  AMS  Added typesetter TEXINFO.
   03-Feb-1993  BK   Changes for Linux.
   15-Oct-1993  BK   If NAME_MAX has been declared elsewhere, remove its
                     definition before setting our own.
   20-Nov-1995  WMW  Add typesetter HTML
   06-Aug-1997	WMW  Add non-product files
   01-May-1998	WMW  Add typesetters LATEX and LATEX2HTML

##############################################################################*/


/******************************************************************************/
/*                                    DATA.H                                  */
/******************************************************************************/
/*                                                                            */
/* This package (data.h, data.c) contains ALL of the global variables in      */
/* FunnelWeb. Some of the FunnelWeb packages (e.g. the lister) harbour hidden */
/* static state variables which could be considered to be a global variable,  */
/* but, these aside, this package contains all the variables that are used    */
/* directly by more than one package. In many programs, it would likely be    */
/* appropriate to have a separate package for each distinct group of shared   */
/* data so that only those packages needing a particular group of data need   */
/* see it. However, in FunnelWeb's case, the variables are so few, and their  */
/* use so widespread that they are clustered here in one package for all to   */
/* see.                                                                       */
/*                                                                            */
/* This package also contains type definitions for the central FunnelWeb data */
/* structures.                                                                */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_DATA
#define DONE_DATA

/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "style.h"
#include "clock.h"
#include "list.h"
#include "table.h"
#include "option.h"
#include "section.h"
#include "writfile.h"

/******************************************************************************/
/*                                                                            */
/* DATA TYPES                                                                 */
/* ==========                                                                 */
/* The following section contains all the data types of the global variables. */
/*                                                                            */
/******************************************************************************/

/* The following structure defines a position in the global listing of the    */
/* input data by storing a line number and a column number. The line number   */
/* is a global line number meaning that it increases continuously through     */
/* the lines of included files. The first line is line number 1. The first    */
/* (leftmost) column is column number 1.                                      */
/* We also keep the filename and the local line number. */
typedef
   struct
     {
      p_fn_t ps_filename;
      ulong ps_line;
      ulong ps_locline;
      ulong ps_column;
     } ps_t ;

typedef ps_t *p_ps_t;  /* A pointer to a position is handy too! */

/******************************************************************************/

/* A macro name is represented simply as a character array. */
#ifdef NAME_MAX
#undef NAME_MAX
#endif
#define NAME_MAX 80
typedef char name_t[NAME_MAX+1];
typedef name_t *p_name_t;

/******************************************************************************/

/* SC stands for SCrap of text. A scrap of text is a contiguous group of      */
/* printable bytes in memory. The following structure defines such a group by */
/* storing a pointer to the first and last character of the scrap.            */
/* The scrap must contain at least one character (i.e. sc_last>=sc_first).    */
typedef
   struct
     {
      char *sc_first; /* Pointer to the first byte of the scrap.              */
      char *sc_last;  /* Pointer to the last  byte of the scrap.              */
      bool  sc_white; /* TRUE iff the scrap consists entirely of whitespace.  */
     } sc_t;

typedef sc_t *p_sc_t;

/******************************************************************************/

/* LN stands for LiNe. This record holds global and local line numbers as     */
/* well as a scrap that points to the line in question. The scanner (which    */
/* generates this list) guarantees that the last character of the line scrap  */
/* is an EOL.                                                                 */
typedef
   struct
     {
      p_fn_t ln_filename;  /* File that this line was in. */
      sc_t  ln_body;    /* Scrap pointing to the line. Line ends in EOL.      */
      ulong ln_global;  /* Global line number of this line.                   */
      ulong ln_local;   /* Local  line number of this line.                   */
     } ln_t;

/* The global line list is simply a list of lines of the following type.      */
typedef p_ls_t p_lnls_t;

/******************************************************************************/

/* The following enumerated type identifies a font. */
#define FT_NORM 1
#define FT_TITL 2
#define FT_STIT 3

/* The following enumerated type identifies a horizontal alignment. */
#define LR_LEFT 1
#define LR_RIGH 2
#define LR_CENT 3

/* We want to pack a font and an alignment into the tk_gen byte of the token  */
/* record (we could create a new field, but as none of the other token kinds  */
/* require an extra field, we choose to pack instead. The formula is this:    */
/* Packed byte=LRFT_PACK*FONT+ALIGNMENT.                                      */
#define LRFT_PACK 10

/******************************************************************************/

/* The following enumerated type identifies the kind of a token. */
#define TK_TEXT  1   /*      Text segment.          */
#define TK_NSEC  2   /*  @A..New section.           */
#define TK_MDEF  3   /*  @$  Macro definition.      */
#define TK_NDEF  23  /*  @N  File definition.       */
#define TK_FDEF  4   /*  @O  File definition.       */
#define TK_ONAM  5   /*  @<  Open name.             */
#define TK_CNAM  6   /*  @>  Close name.            */
#define TK_ODEF  7   /*  @{  Open definition.       */
#define TK_CDEF  8   /*  @}  Close definition.      */
#define TK_OPAR  9   /*  @(  Open parameter list.   */
#define TK_CPAR 10   /*  @)  Close parameter list.  */
#define TK_COMA 11   /*  @,  Comma.                 */
#define TK_QUOT 12   /*  @"  Quote.                 */
#define TK_PARM 13   /*  @1  Parameter.             */
#define TK_ZERO 14   /*  @Z  Zero calls allowed.    */
#define TK_MANY 15   /*  @M  Many calls allowed.    */
#define TK_NAME 16   /*  @#  Self contained name.   */
#define TK_EMPH 17   /*  @/  Emphasize text.        */
#define TK_NPAG 18   /*  @t..Newpage.               */
#define TK_TOCS 19   /*  @t..Table of contents.     */
#define TK_SKIP 20   /*  @t..Vertical skip.         */
#define TK_TITL 21   /*  @t..Title text.            */
#define TK_EOF  22   /*      End of file.           */
typedef ubyte tk_k_t;

/* The following structure conveys all the information about a single token.  */
/* As well as the kind of token, the parser needs to know where the token is  */
/* in the input file and what the text of the token is if it is a text token. */
/* Some other tokens have a numeric attribute associated with them and the    */
/* tk_gen field provides a place for this. The attributes are:                */
/*    TK_PARM - The number of the parameter [1,9].                            */
/*    TK_NAME - The number of the character forming the name [0,255].         */
/*    TK_NSEC - The level of the section [0,5]. 0=@*, 1=@A, 2=@B,..,5=@E.     */
/*    TK_SKIP - Number of millimetres to skip vertically [0,255].             */
/*    TK_TITL - Font and alignment packed into byte as specified earlier.     */
/*              tk_sc is the text to be set as a title.                       */
typedef
   struct
     {
      tk_k_t tk_kind;  /* Kind of this token.                                 */
      ps_t   tk_ps;    /* Position of the first character of this token.      */
      sc_t   tk_sc;    /* Scrap constituting token.                           */
      ubyte  tk_gen;   /* General token attribute.                            */
     } tk_t;

typedef tk_t *p_tk_t;	  /* A pointer to a token. */

typedef p_ls_t p_tkls_t;  /* A list of tokens. */

/******************************************************************************/

typedef p_ls_t p_scls_t;  /* List of scraps.                                  */
typedef p_ls_t p_scll_t;  /* List of list of scraps =TEXT.                    */

typedef p_ls_t p_ells_t;  /* List of pointers to elements = EXPRESSION.       */
typedef p_ls_t p_elll_t;  /* List of list of pointers to elements.            */
typedef p_ls_t p_ell3_t;  /* List of list of list of pointers to elements.    */

/******************************************************************************/

/* This structure's signature is BP for Body Part. FunnelWeb macros can       */
/* be defined in a series of "+=" definitions scattered through the input     */
/* file. The definition of the macro is the concatenation of all the parts.   */
/* The contributory part of a part consists of a single expression.           */
/* Throughout the document, body parts (definition parts) are numbered        */
/* sequentially by a sequence number.                                         */
typedef
   struct
    {
     p_ells_t bp_ex;  /* Expression that is logically appended to definition. */
     ulong    bp_seq; /* Sequence number of body part.                        */
     ps_t     bp_ps;  /* Position at which the definition appears.            */
    } bp_t;

typedef bp_t *p_bp_t;

/* A list of body parts constitutes the full body of a macro. */
typedef p_ls_t p_bpls_t;

/******************************************************************************/

/* The following structure summarizes a macro CALL. Each macro table entry    */
/* contains a field ma_calls which contains a list of these structures. The   */
/* list is used to generate diagnostics (e.g. if a call has the wrong number  */
/* of parameters) and also to give cross reference information in the typeset */
/* documentation.                                                             */
typedef
   struct
     {
      ulong mc_seq;   /* Sequence number of body part containing call.        */
      ps_t  mc_ps;    /* Position at which the call occurred.                 */
      ulong mc_npar;  /* Number of parameters in call.                        */
     } mc_t;

typedef mc_t *p_mc_t;

/* A list of calls summarizes the entire usage of a macro in a document.      */
typedef p_ls_t p_mcls_t;

/******************************************************************************/

/* This structure stores the definition of a single macro. The first field    */
/* md_isdef indicates whether a definition for this macro has so far been     */
/* seen. If it has, md_isdef=TRUE and the remaining fields are well defined.  */
typedef
   struct
     {
      bool     md_isdef;  /* TRUE iff the macro is defined.                   */
      ps_t     md_ps;     /* isdef=> Position of first definition part.       */
      ubyte    md_npar;   /* isdef=> Number of params specified in defn.      */
      bool     md_isadd;  /* isdef=> TRUE iff additively defined.             */
      bool     md_iszer;  /* isdef=> TRUE iff zero calls allowed.             */
      bool     md_isman;  /* isdef=> TRUE iff many calls allowed.             */
      bool     md_isfil;  /* isdef=> TRUE iff macro is bound to a prod. file. */
      bool     md_isnop;  /* isdef=> TRUE iff macro is bound to a non-p file. */
      p_bpls_t md_body;   /* isdef=> Body of the macro (list of parts).       */
     } md_t;

/******************************************************************************/

/* The following structure contains the full information about a macro.       */
typedef
   struct
     {
      name_t   ma_name;   /* Name of the macro.                               */
      p_mcls_t ma_calls;  /* List of calls of this macro in the document.     */
      md_t     ma_defn;   /* Definition of this macro.                        */
      p_ell3_t ma_actn;   /* Used by tangle. List of actual parameter lists.  */
      uword    ma_level;  /* Used by analyser. Depth of deepest call.         */
     } ma_t;

/* A pointer to the comprehensive macro structure defined above is the way    */
/* that FunnelWeb refers to macros internally.                                */
typedef ma_t *p_ma_t;

/******************************************************************************/

/* An expression consists of a sequence of ELEMENTS each of which can         */
/* be one of three kinds:                                                     */
/*                                                                            */
/*    1. A block of text.                                                     */
/*    2. An invocation of another macro.                                      */
/*    3. A parameter of the current macro.                                    */
/*                                                                            */
/* The following enumerated type identifies one of these three alternatives.  */
#define EL_TEXT 1
#define EL_INVC 2
#define EL_PARM 3
typedef ubyte el_k_t;

/* The following rather messy structure contains information about a single   */
/* element. As mentioned above, an element can be one of three kinds and the  */
/* following structure should, strictly speaking, be defined as a C union so  */
/* as to emphasize the mutually exclusive nature of most of its fields.       */
/* At one stage this structure did contain a union, however, it introduced    */
/* more mess than it brought clarity (because of the extra two subnames) and  */
/* was eventually dropped.                                                    */
/* A few fields deserve some explanation:                                     */
/*    el_pretx and el_postx hold the exact whitespace appearing between       */
/*       actual parameters in a macro call. This enables the call to be       */
/*       formatted properly in the typeset output.                            */
/*    el_which is part of the macro parameter element (e.g. @1) and points to */
/*       the macro within which the @1 appears. Strictly speaking this should */
/*       not be necessary, but it is convenient for the tangler to have this  */
/*       information when it is half way through expanding an expression.     */
typedef
   struct
     {
      el_k_t   el_kind;  /* Indicates what kind of element structure holds.   */

      p_tkls_t el_text;  /* EL_TEXT => List of tokens forming a text chunk.   */

      p_ma_t   el_p_mac; /* EL_INVC => Pointer to macro being invoked.        */
      p_elll_t el_parls; /* EL_INVC => List of actual parameters.             */
      p_scll_t el_pretx; /* EL_INVC => Text before each parameter.            */
      p_scll_t el_postx; /* EL_INVC => Text after  each parameter.            */

      p_ma_t   el_which; /* EL_PARM => Macro in which this element appears.   */
      ubyte    el_parno; /* EL_PARM => Parameter number of this actual param. */
     } el_t;

typedef el_t *p_el_t;

/******************************************************************************/

/* A document component (represented by the DC_ data structures (see below)   */
/* can be one of three things: a lump of text, a typesetter-generic           */
/* typesetting directive, or a macro definition. The second of these consists */
/* of a whole collection of typesetting commands and so rather than           */
/* cluttering up the dc_ record, they have been separated out here.           */
#define TY_NSEC 1   /* New section.                                           */
#define TY_OLIT 2   /* Open  literal.                                         */
#define TY_CLIT 3   /* Close literal.                                         */
#define TY_OEMP 4   /* Open  emphasise.                                       */
#define TY_CEMP 5   /* Close emphasise.                                       */
#define TY_NPAG 6   /* New page.                                              */
#define TY_TOCS 7   /* Table of contents.                                     */
#define TY_SKIP 8   /* Skip vertical.                                         */
#define TY_TITL 9   /* Title.                                                 */
typedef ubyte ty_k_t;

typedef
   struct
     {
      ty_k_t   ty_kind;  /* Kind of this typesetting directive.               */
      sn_t     ty_sn;    /* TY_NSEC=> Hierarchical section number.            */
      bool     ty_isnam; /* TY_NSEC=> TRUE iff the section is named.          */
      name_t   ty_name;  /* TY_NSEC=> ty_isnam=> Name of section.             */

      uword    ty_mm;    /* TY_SKIP=> Millimetres to skip.                    */

      ubyte    ty_font;  /* TY_TITL=> Font in which to write title.           */
      ubyte    ty_align; /* TY_TITL=> Alignment with which to write title.    */
      sc_t     ty_sc;    /* TY_TITL=> Scrap that is title text.               */
     } ty_t;

typedef ty_t *p_ty_t;

/******************************************************************************/

/* The document list contains a representation of the input document in the   */
/* form in which it was fed to FunnelWeb. This structured representation of   */
/* the input is used by the weaver to generate the typeset output.            */
/* Here, a document is represented by a list of DOCUMENT COMPONENTs (DC) each */
/* of which contains information about a major chunk of the document. The     */
/* following enumerated type dc_k_t (document component kind type) is used to */
/* indicate which kind of component each list element contains.               */
#define DC_TEXT 1   /* Text component consists of a block of text.            */
#define DC_TYPE 2   /* Typesettting component affecting document typesetting. */
#define DC_MACR 3   /* A MACRo definition.                                    */
typedef ubyte dc_k_t;

/* The following structure stores a single document component. Like the el_t  */
/* type, the dc_t type should really be a union type, but a union construct   */
/* has been avoided to make the naming simpler.                               */
typedef
   struct
     {
      ps_t     dc_ps;    /* Position of this component.                       */
      dc_k_t   dc_kind;  /* Kind of this component.                           */

      p_scls_t dc_text;  /* DC_TEXT=> Text segment constituting this compnt.  */

      ty_t     dc_ty;    /* DC_TYPE=> Typesetting object record.              */

      p_ma_t   dc_p_ma;  /* DC_MACR=> Pointer to the macro defined.           */
      ulong    dc_part;  /* DC_MACR=> Part number of this part of macro defn. */
     } dc_t;

typedef dc_t *p_dc_t;

/* A list of document components constitutes the global document list         */
/* declared later.                                                            */
typedef p_ls_t p_dcls_t;

/******************************************************************************/

/* This enumerated type identifies a typesetter.                              */
/*    TR_NONE - No specific typesetter specified.                             */
/*    TR_TEX  - The TeX typesetter.                                           */
/*    TR_TEXINFO - FSF Texinfo (uses TeX).				      */
/*    TR_HTML - Any World-Wide Web browser				      */
/*    TR_LATEX - LaTeX macros (uses TeX)				      */
/*    TR_L2HTML - Latex2html converter      				      */
#define TR_NONE 1
#define TR_TEX  2
#define TR_TEXINFO 3
#define TR_HTML 4
#define TR_LATEX 5
#define TR_L2HTML 6
/* Add more typesetters here later. */
typedef ubyte tr_k_t;


/******************************************************************************/
/*                                                                            */
/* VARIABLES                                                                  */
/* =========                                                                  */
/* This section contains external declarations of the global variables.       */
/* The global variables themselves appear in DATA.C.                          */
/*                                                                            */
/******************************************************************************/

/* This #ifndef is part of a mechanism that makes the following definitions   */
/* visible to other modules declared as "extern", and visible to data.c       */
/* declared as ordinary declarations. This prevents inconsistencies.          */
#ifndef EXTERN
#define EXTERN extern
#endif

/* This global options variable holds the options that were transmitted to    */
/* FunnelWeb proper through the command line.                                 */
EXTERN GLOVAR op_t option;

/* The following option variable is set by the scanner and is used by the     */
/* tangler. It determines whether the tangler will use natural indenting.     */
/* TRUE => Tangler should use space indenting. FALSE=>No indenting.           */
EXTERN GLOVAR bool tgindent;

/* The following option variable is set by the scanner and is used by the     */
/* tangler. It sets a limit on the length of the lines of the product files   */
/* generated by tangle. A value of TGMAXINF indicates that no checking need   */
/* be performed.                                                              */
#define TGMAXINF (ULONG_MAX)
EXTERN GLOVAR ulong tglinmax;

/* The following variable is written by the scanner and read by weave. It     */
/* stores the typesetter format possibly specified by the user in the input.  */
EXTERN GLOVAR tr_k_t tr_codes;

/* The following five lists and tables constitute the major data structures   */
/* that are communicated between the major components of FunnelWeb.           */
/* The TOKEN_LIST contains a tokenized representation of the input file.      */
/* The LINE_LIST contains a list of the lines of the input file.              */
/* The DOCUMENT_LIST contains a structured representation of the input file.  */
/* The MACRO_TABLE describes the macros defined in the input file.            */
/* The FILE_TABLE identifies macros that are connected to product files.      */
/*                                        Created By  Used By                 */
/*                                        ----------  -------                 */
EXTERN GLOVAR p_tkls_t token_list;     /*    Scanner  Parser                  */
EXTERN GLOVAR p_lnls_t line_list;      /*    Scanner  Lister                  */
EXTERN GLOVAR p_dcls_t document_list;  /*     Parser  Weaver                  */
EXTERN GLOVAR p_tb_t   macro_table;    /*     Parser  Tangler, Weaver         */
EXTERN GLOVAR p_tb_t   file_table;     /*     Parser  Tangler, Weaver         */

/* Three output streams are accessible globally.                              */
/* The SCREEN FILE is connected to standard output (the user screen).         */
/* The JOURNAL FILE logs FunnelWeb command language transactions.             */
/* The LISTING FILE is created by an single invocation of FunnelWeb proper.   */
/* The MAPPING FILE is created when +U is used.				      */
EXTERN GLOVAR wf_t f_s;  /* Screen  file. */
EXTERN GLOVAR wf_t f_j;  /* Journal file. */
EXTERN GLOVAR wf_t f_l;  /* Listing file. */
EXTERN GLOVAR wf_t f_m;  /* Mapping file. */
EXTERN GLOVAR wf_t f_n;  /* Non-product file list file. */

/* Many of the FunnelWeb IO functions accept a single string as a parameter.  */
/* This means that sprintf and a temporary string must be used in order to    */
/* produce parameterized formatted output. Rather than declare temporary      */
/* strings in each local function, we declare them globally.                  */
EXTERN GLOVAR char linet1[2000];

/* Definitions of Diagnostic Levels                                           */
/* --------------------------------                                           */
/* A WARNING has no effect except to cause a message to be issued.            */
/* An ERROR causes FunnelWeb to abort to the shell at the end of the phase.   */
/*    Example: An error during scanning means that the FunnelWeb run will     */
/*    terminate to the shell at the end of the scanning phase.                */
/* A SEVERE ERROR causes FunnelWeb to abort to the shell immediately.         */
/* A FATAL ERROR causes FunnelWeb to abort to the OS immediately.             */

/* The following variables count diagnostics over a single FunnelWeb run.     */
EXTERN GLOVAR ulong num_war;  /* Number of      warnings.                     */
EXTERN GLOVAR ulong num_err;  /* Number of        errors.                     */
EXTERN GLOVAR ulong num_sev;  /* Number of severe errors.                     */

/* The following variables count diagnostics over multiple FunnelWeb runs.    */
EXTERN GLOVAR ulong sum_war;  /* Number of      warnings.                     */
EXTERN GLOVAR ulong sum_err;  /* Number of        errors.                     */
EXTERN GLOVAR ulong sum_sev;  /* Number of severe errors.                     */
EXTERN GLOVAR ulong sum_fat;  /* Number of fatal  errors.                     */

/* The file that is currently being processed. */
EXTERN GLOVAR p_fn_t filename;

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                 End of DATA.H                              */
/******************************************************************************/
