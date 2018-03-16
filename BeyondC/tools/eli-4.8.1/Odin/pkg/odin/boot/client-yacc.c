
/*  A Bison parser, made from /net/tantalum/home/tantalum/gclemm/.ODIN/tantalum/FILES/l/client.ygi.66466.y
 by  GNU Bison version 1.25
  */

#define OCBISON 1  /* Identify Bison output.  */

#define	WORDTK	2
#define	HOSTWD	3
#define	OBJTID	4
#define	EXCLPT	5
#define	SCOLON	6
#define	QUESMK	7
#define	PERCNT	8
#define	LANGLE	9
#define	RANGLE	10
#define	COLON	11
#define	LPAREN	12
#define	RPAREN	13
#define	PLUS	14
#define	EQUALS	15
#define	SLASH	16


#include "inc/GMC.h"
extern int num_ParseErrors;
tp_Nod OC_Parse() {tp_Nod Nod;
num_ParseErrors = 0; Init_Lex(); Init_ConstructTree();
(void)ocparse(); Nod = End_ConstructTree();
return Nod;}
void ocerror(GMC_ARG(char*, s)) GMC_DCL(char*, s) 
{num_ParseErrors++; ParseError(s);}
int oclex() {return OC_Lex();}
#ifndef OCSTYPE
#define OCSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	OCFINAL		83
#define	OCFLAG		-32768
#define	OCNTBASE	18

#define OCTRANSLATE(x) ((unsigned)(x) <= 257 ? octranslate[x] : 40)

static const char octranslate[] = {     0,
     2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
    12,    13,    14,    15,    16,    17,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2
};

#if OCDEBUG != 0
static const short ocprhs[] = {     0,
     0,     2,     6,     8,     9,    11,    13,    15,    17,    19,
    22,    24,    27,    29,    34,    38,    42,    46,    49,    52,
    55,    59,    63,    65,    67,    70,    74,    77,    79,    81,
    83,    86,    89,    92,    95,    98,   101,   105,   110,   113,
   119,   122,   124,   127,   129,   130,   133,   136,   138,   140,
   144,   146,   148,   150,   152,   155,   157,   159,   161
};

static const short ocrhs[] = {    19,
     0,    19,     7,    20,     0,    20,     0,     0,    21,     0,
    22,     0,    23,     0,    24,     0,    25,     0,    25,    36,
     0,    36,     0,    25,     6,     0,     6,     0,    25,     6,
    12,    35,     0,     6,    12,    35,     0,    25,    11,    25,
     0,    25,    10,    25,     0,    25,    11,     0,    25,    10,
     0,    35,    16,     0,    35,    16,    25,     0,    35,    16,
    36,     0,    26,     0,    27,     0,    26,    28,     0,    13,
    26,    14,     0,    13,    14,     0,    35,     0,    39,     0,
    17,     0,    17,    35,     0,    12,    33,     0,     8,    37,
     0,    37,     8,     0,     9,    35,     0,    16,    35,     0,
    15,    34,    29,     0,    15,    13,    25,    14,     0,    12,
    33,     0,    12,    33,    16,    12,    33,     0,    17,    35,
     0,    17,     0,     9,    35,     0,    30,     0,     0,    16,
    31,     0,    31,    32,     0,    32,     0,    35,     0,    13,
    25,    14,     0,    35,     0,    35,     0,     8,     0,    37,
     0,     6,     8,     0,    38,     0,     3,     0,     4,     0,
     5,     0
};

#endif

#if OCDEBUG != 0
static const short ocrline[] = { 0,
    31,    35,    39,    43,    44,    46,    48,    50,    54,    58,
    61,    63,    66,    68,    73,    79,    83,    87,    90,    95,
    98,   102,   108,   112,   114,   117,   123,   126,   128,   130,
   132,   135,   138,   141,   144,   147,   152,   156,   161,   164,
   170,   173,   175,   180,   183,   187,   192,   195,   199,   201,
   207,   211,   215,   217,   221,   224,   228,   230,   232
};
#endif


#if OCDEBUG != 0 || defined (OCERROR_VERBOSE)

static const char * const octname[] = {   "$","error","$undefined.","WORDTK",
"HOSTWD","OBJTID","EXCLPT","SCOLON","QUESMK","PERCNT","LANGLE","RANGLE","COLON",
"LPAREN","RPAREN","PLUS","EQUALS","SLASH","xCommand","xCommand_1","xSingleCommand",
"xQuery","xExecute","xCopy","xVariable","xOdinExpr","xOdinExpr1","xRoot","xOperation",
"xOperation_1","xPrmVals","xPrmVals_1","xPrmVal","xFileType","xPrmType","xWord",
"xEPString","WORDTKleaf","HOSTWDleaf","OBJTIDleaf", NULL
};
#endif

static const short ocr1[] = {     0,
    18,    19,    19,    20,    20,    20,    20,    20,    21,    22,
    22,    22,    22,    22,    22,    23,    23,    23,    23,    24,
    24,    24,    25,    26,    26,    26,    27,    27,    27,    27,
    27,    27,    27,    27,    27,    27,    28,    28,    28,    28,
    28,    28,    28,    29,    29,    30,    31,    31,    32,    32,
    33,    34,    35,    35,    36,    36,    37,    38,    39
};

static const short ocr2[] = {     0,
     1,     3,     1,     0,     1,     1,     1,     1,     1,     2,
     1,     2,     1,     4,     3,     3,     3,     2,     2,     2,
     3,     3,     1,     1,     2,     3,     2,     1,     1,     1,
     2,     2,     2,     2,     2,     2,     3,     4,     2,     5,
     2,     1,     2,     1,     0,     2,     2,     1,     1,     3,
     1,     1,     1,     1,     2,     1,     1,     1,     1
};

static const short ocdefact[] = {     4,
    57,    58,    59,    13,    53,     0,     0,     0,     0,    30,
     1,     3,     5,     6,     7,     8,     9,    23,    24,    28,
    11,    54,    56,    29,    55,     0,    33,    53,    35,    54,
    32,    51,    27,     0,    28,    36,    31,     4,    12,    19,
    18,    10,     0,     0,     0,    42,    25,    20,    34,    15,
    26,     2,     0,    17,    16,    43,    39,     0,    45,    52,
    41,     0,    21,    22,    14,     0,     0,     0,    37,    44,
     0,    38,     0,    46,    48,    49,    40,     0,    47,    50,
     0,     0,     0
};

static const short ocdefgoto[] = {    81,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    47,
    69,    70,    74,    75,    31,    59,    35,    21,    30,    23,
    24
};

static const short ocpact[] = {    73,
-32768,-32768,-32768,     9,    21,    27,    27,   103,    27,    27,
    -4,-32768,-32768,-32768,-32768,-32768,   132,    45,-32768,    -2,
-32768,    31,-32768,-32768,-32768,    27,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    19,-32768,-32768,-32768,    73,    15,   118,
   118,-32768,    27,    27,     5,    27,-32768,    88,-32768,-32768,
-32768,-32768,    27,-32768,-32768,-32768,    24,   118,    25,-32768,
-32768,    34,-32768,-32768,-32768,    35,    36,    12,-32768,-32768,
    27,-32768,   118,    12,-32768,-32768,-32768,    41,-32768,-32768,
    48,    56,-32768
};

static const short ocpgoto[] = {-32768,
-32768,    20,-32768,-32768,-32768,-32768,   -36,    53,-32768,-32768,
-32768,-32768,-32768,   -11,   -42,-32768,     0,   -16,    11,-32768,
-32768
};


#define	OCLAST		143


static const short octable[] = {    20,
    42,    57,    38,    54,    55,    29,    32,     1,    36,    37,
    22,    63,    28,    48,     1,    27,    25,    58,    22,    28,
    26,    67,    25,     1,    73,    50,    53,    43,    77,     1,
    44,    64,    51,    45,    28,    46,    78,    20,    49,    66,
    68,    25,    56,    32,    60,    61,    71,    82,    22,    72,
    22,    22,    65,    43,    80,    83,    44,    52,    22,    45,
    34,    46,    79,     0,     0,     0,     0,    76,    22,     0,
    32,     0,     0,    76,     0,     1,     2,     3,     4,     0,
     5,     6,     0,    22,     7,     8,     0,     0,     9,    10,
     1,     2,     3,    62,     0,     5,     6,     0,     0,     7,
     8,     0,     0,     9,    10,     1,     0,     3,     0,     0,
     5,     6,     0,     0,     7,     8,    33,     0,     9,    10,
     1,     0,     3,     0,     0,     5,     6,     0,     0,     7,
     8,     0,     0,     9,    10,     2,     0,    39,     0,     0,
     0,    40,    41
};

static const short occheck[] = {     0,
    17,    44,     7,    40,    41,     6,     7,     3,     9,    10,
     0,    48,     8,    16,     3,     5,     8,    13,     8,     8,
    12,    58,     8,     3,    13,    26,    12,     9,    71,     3,
    12,    48,    14,    15,     8,    17,    73,    38,     8,    16,
    16,     8,    43,    44,    45,    46,    12,     0,    38,    14,
    40,    41,    53,     9,    14,     0,    12,    38,    48,    15,
     8,    17,    74,    -1,    -1,    -1,    -1,    68,    58,    -1,
    71,    -1,    -1,    74,    -1,     3,     4,     5,     6,    -1,
     8,     9,    -1,    73,    12,    13,    -1,    -1,    16,    17,
     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    12,
    13,    -1,    -1,    16,    17,     3,    -1,     5,    -1,    -1,
     8,     9,    -1,    -1,    12,    13,    14,    -1,    16,    17,
     3,    -1,     5,    -1,    -1,     8,     9,    -1,    -1,    12,
    13,    -1,    -1,    16,    17,     4,    -1,     6,    -1,    -1,
    -1,    10,    11
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef OCSTACK_USE_ALLOCA
#ifdef alloca
#define OCSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define OCSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define OCSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define OCSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define OCSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* OCSTACK_USE_ALLOCA not defined */

#ifdef OCSTACK_USE_ALLOCA
#define OCSTACK_ALLOC alloca
#else
#define OCSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define ocerrok		(ocerrstatus = 0)
#define occlearin	(occhar = OCEMPTY)
#define OCEMPTY		-2
#define OCEOF		0
#define OCACCEPT	goto ocacceptlab
#define OCABORT 	goto ocabortlab
#define OCERROR		goto ocerrlab1
/* Like OCERROR except do call ocerror.
   This remains here temporarily to ease the
   transition to the new meaning of OCERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define OCFAIL		goto ocerrlab
#define OCRECOVERING()  (!!ocerrstatus)
#define OCBACKUP(token, value) \
do								\
  if (occhar == OCEMPTY && oclen == 1)				\
    { occhar = (token), oclval = (value);			\
      occhar1 = OCTRANSLATE (occhar);				\
      OCPOPSTACK;						\
      goto ocbackup;						\
    }								\
  else								\
    { ocerror ("syntax error: cannot back up"); OCERROR; }	\
while (0)

#define OCTERROR	1
#define OCERRCODE	256

#ifndef OCPURE
#define OCLEX		oclex()
#endif

#ifdef OCPURE
#ifdef OCLSP_NEEDED
#ifdef OCLEX_PARAM
#define OCLEX		oclex(&oclval, &oclloc, OCLEX_PARAM)
#else
#define OCLEX		oclex(&oclval, &oclloc)
#endif
#else /* not OCLSP_NEEDED */
#ifdef OCLEX_PARAM
#define OCLEX		oclex(&oclval, OCLEX_PARAM)
#else
#define OCLEX		oclex(&oclval)
#endif
#endif /* not OCLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef OCPURE

int	occhar;			/*  the lookahead symbol		*/
OCSTYPE	oclval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef OCLSP_NEEDED
OCLTYPE oclloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int ocnerrs;			/*  number of parse errors so far       */
#endif  /* not OCPURE */

#if OCDEBUG != 0
int ocdebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  OCINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	OCINITDEPTH
#define OCINITDEPTH 200
#endif

/*  OCMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if OCMAXDEPTH == 0
#undef OCMAXDEPTH
#endif

#ifndef OCMAXDEPTH
#define OCMAXDEPTH 10000
#endif

/* Define __oc_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __oc_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__oc_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__oc_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define OCPARSE_PARAM as the name of an argument to be passed
   into ocparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef OCPARSE_PARAM
#ifdef __cplusplus
#define OCPARSE_PARAM_ARG void *OCPARSE_PARAM
#define OCPARSE_PARAM_DECL
#else /* not __cplusplus */
#define OCPARSE_PARAM_ARG OCPARSE_PARAM
#define OCPARSE_PARAM_DECL void *OCPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not OCPARSE_PARAM */
#define OCPARSE_PARAM_ARG
#define OCPARSE_PARAM_DECL
#endif /* not OCPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef OCPARSE_PARAM
int ocparse (void *);
#else
int ocparse (void);
#endif
#endif

int
ocparse(OCPARSE_PARAM_ARG)
     OCPARSE_PARAM_DECL
{
  register int ocstate;
  register int ocn;
  register short *ocssp;
  register OCSTYPE *ocvsp;
  int ocerrstatus;	/*  number of tokens to shift before error messages enabled */
  int occhar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	ocssa[OCINITDEPTH];	/*  the state stack			*/
  OCSTYPE ocvsa[OCINITDEPTH];	/*  the semantic value stack		*/

  short *ocss = ocssa;		/*  refer to the stacks thru separate pointers */
  OCSTYPE *ocvs = ocvsa;	/*  to allow ocoverflow to reallocate them elsewhere */

#ifdef OCLSP_NEEDED
  OCLTYPE oclsa[OCINITDEPTH];	/*  the location stack			*/
  OCLTYPE *ocls = oclsa;
  OCLTYPE *oclsp;

#define OCPOPSTACK   (ocvsp--, ocssp--, oclsp--)
#else
#define OCPOPSTACK   (ocvsp--, ocssp--)
#endif

  int ocstacksize = OCINITDEPTH;
  int ocfree_stacks = 0;

#ifdef OCPURE
  int occhar;
  OCSTYPE oclval;
  int ocnerrs;
#ifdef OCLSP_NEEDED
  OCLTYPE oclloc;
#endif
#endif

  OCSTYPE ocval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int oclen;

#if OCDEBUG != 0
  if (ocdebug)
    fprintf(stderr, "Starting parse\n");
#endif

  ocstate = 0;
  ocerrstatus = 0;
  ocnerrs = 0;
  occhar = OCEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  ocssp = ocss - 1;
  ocvsp = ocvs;
#ifdef OCLSP_NEEDED
  oclsp = ocls;
#endif

/* Push a new state, which is found in  ocstate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
ocnewstate:

  *++ocssp = ocstate;

  if (ocssp >= ocss + ocstacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      OCSTYPE *ocvs1 = ocvs;
      short *ocss1 = ocss;
#ifdef OCLSP_NEEDED
      OCLTYPE *ocls1 = ocls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = ocssp - ocss + 1;

#ifdef ocoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef OCLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if ocoverflow is a macro.  */
      ocoverflow("parser stack overflow",
		 &ocss1, size * sizeof (*ocssp),
		 &ocvs1, size * sizeof (*ocvsp),
		 &ocls1, size * sizeof (*oclsp),
		 &ocstacksize);
#else
      ocoverflow("parser stack overflow",
		 &ocss1, size * sizeof (*ocssp),
		 &ocvs1, size * sizeof (*ocvsp),
		 &ocstacksize);
#endif

      ocss = ocss1; ocvs = ocvs1;
#ifdef OCLSP_NEEDED
      ocls = ocls1;
#endif
#else /* no ocoverflow */
      /* Extend the stack our own way.  */
      if (ocstacksize >= OCMAXDEPTH)
	{
	  ocerror("parser stack overflow");
	  if (ocfree_stacks)
	    {
	      free (ocss);
	      free (ocvs);
#ifdef OCLSP_NEEDED
	      free (ocls);
#endif
	    }
	  return 2;
	}
      ocstacksize *= 2;
      if (ocstacksize > OCMAXDEPTH)
	ocstacksize = OCMAXDEPTH;
#ifndef OCSTACK_USE_ALLOCA
      ocfree_stacks = 1;
#endif
      ocss = (short *) OCSTACK_ALLOC (ocstacksize * sizeof (*ocssp));
      __oc_memcpy ((char *)ocss, (char *)ocss1,
		   size * (unsigned int) sizeof (*ocssp));
      ocvs = (OCSTYPE *) OCSTACK_ALLOC (ocstacksize * sizeof (*ocvsp));
      __oc_memcpy ((char *)ocvs, (char *)ocvs1,
		   size * (unsigned int) sizeof (*ocvsp));
#ifdef OCLSP_NEEDED
      ocls = (OCLTYPE *) OCSTACK_ALLOC (ocstacksize * sizeof (*oclsp));
      __oc_memcpy ((char *)ocls, (char *)ocls1,
		   size * (unsigned int) sizeof (*oclsp));
#endif
#endif /* no ocoverflow */

      ocssp = ocss + size - 1;
      ocvsp = ocvs + size - 1;
#ifdef OCLSP_NEEDED
      oclsp = ocls + size - 1;
#endif

#if OCDEBUG != 0
      if (ocdebug)
	fprintf(stderr, "Stack size increased to %d\n", ocstacksize);
#endif

      if (ocssp >= ocss + ocstacksize - 1)
	OCABORT;
    }

#if OCDEBUG != 0
  if (ocdebug)
    fprintf(stderr, "Entering state %d\n", ocstate);
#endif

  goto ocbackup;
 ocbackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* ocresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  ocn = ocpact[ocstate];
  if (ocn == OCFLAG)
    goto ocdefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* occhar is either OCEMPTY or OCEOF
     or a valid token in external form.  */

  if (occhar == OCEMPTY)
    {
#if OCDEBUG != 0
      if (ocdebug)
	fprintf(stderr, "Reading a token: ");
#endif
      occhar = OCLEX;
    }

  /* Convert token to internal form (in occhar1) for indexing tables with */

  if (occhar <= 0)		/* This means end of input. */
    {
      occhar1 = 0;
      occhar = OCEOF;		/* Don't call OCLEX any more */

#if OCDEBUG != 0
      if (ocdebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      occhar1 = OCTRANSLATE(occhar);

#if OCDEBUG != 0
      if (ocdebug)
	{
	  fprintf (stderr, "Next token is %d (%s", occhar, octname[occhar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef OCPRINT
	  OCPRINT (stderr, occhar, oclval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  ocn += occhar1;
  if (ocn < 0 || ocn > OCLAST || occheck[ocn] != occhar1)
    goto ocdefault;

  ocn = octable[ocn];

  /* ocn is what to do for this token type in this state.
     Negative => reduce, -ocn is rule number.
     Positive => shift, ocn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (ocn < 0)
    {
      if (ocn == OCFLAG)
	goto ocerrlab;
      ocn = -ocn;
      goto ocreduce;
    }
  else if (ocn == 0)
    goto ocerrlab;

  if (ocn == OCFINAL)
    OCACCEPT;

  /* Shift the lookahead token.  */

#if OCDEBUG != 0
  if (ocdebug)
    fprintf(stderr, "Shifting token %d (%s), ", occhar, octname[occhar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (occhar != OCEOF)
    occhar = OCEMPTY;

  *++ocvsp = oclval;
#ifdef OCLSP_NEEDED
  *++oclsp = oclloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (ocerrstatus) ocerrstatus--;

  ocstate = ocn;
  goto ocnewstate;

/* Do the default action for the current state.  */
ocdefault:

  ocn = ocdefact[ocstate];
  if (ocn == 0)
    goto ocerrlab;

/* Do a reduction.  ocn is the number of a rule to reduce with.  */
ocreduce:
  oclen = ocr2[ocn];
  if (oclen > 0)
    ocval = ocvsp[1-oclen]; /* implement default value of the action */

#if OCDEBUG != 0
  if (ocdebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       ocn, ocrline[ocn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = ocprhs[ocn]; ocrhs[i] > 0; i++)
	fprintf (stderr, "%s ", octname[ocrhs[i]]);
      fprintf (stderr, " -> %s\n", octname[ocr1[ocn]]);
    }
#endif


  switch (ocn) {

case 1:
{Action(-1,1);;
    break;}
case 2:
{Action(0,2);;
    break;}
case 4:
{Action(2,0);;
    break;}
case 10:
{Action(7,2);;
    break;}
case 11:
{Action(7,1);;
    break;}
case 12:
{Action(7,1);;
    break;}
case 13:
{Action(7,0);;
    break;}
case 14:
{Action(8,2);;
    break;}
case 15:
{Action(8,1);;
    break;}
case 16:
{Action(4,2);;
    break;}
case 17:
{Action(6,2);;
    break;}
case 18:
{Action(3,1);;
    break;}
case 19:
{Action(5,1);;
    break;}
case 20:
{Action(9,1);;
    break;}
case 21:
{Action(10,2);;
    break;}
case 22:
{Action(10,2);;
    break;}
case 23:
{Action(15,1);;
    break;}
case 25:
{Action(0,2);;
    break;}
case 27:
{Action(16,0);;
    break;}
case 30:
{Action(17,0);;
    break;}
case 31:
{Action(18,1);;
    break;}
case 32:
{Action(21,1);;
    break;}
case 33:
{Action(14,1);;
    break;}
case 34:
{Action(13,1);;
    break;}
case 35:
{Action(25,1);;
    break;}
case 36:
{Action(29,1);;
    break;}
case 37:
{Action(19,2);;
    break;}
case 38:
{Action(20,1);;
    break;}
case 39:
{Action(21,1);;
    break;}
case 40:
{Action(22,2);;
    break;}
case 41:
{Action(23,1);;
    break;}
case 42:
{Action(24,0);;
    break;}
case 43:
{Action(25,1);;
    break;}
case 45:
{Action(0,0);;
    break;}
case 46:
{Action(27,1);;
    break;}
case 47:
{Action(0,2);;
    break;}
case 50:
{Action(28,1);;
    break;}
case 53:
{Action(11,0);;
    break;}
case 55:
{Action(12,0);;
    break;}
case 57:
{Action(31,-1);;
    break;}
case 58:
{Action(30,-1);;
    break;}
case 59:
{Action(32,-1);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */

  ocvsp -= oclen;
  ocssp -= oclen;
#ifdef OCLSP_NEEDED
  oclsp -= oclen;
#endif

#if OCDEBUG != 0
  if (ocdebug)
    {
      short *ssp1 = ocss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != ocssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++ocvsp = ocval;

#ifdef OCLSP_NEEDED
  oclsp++;
  if (oclen == 0)
    {
      oclsp->first_line = oclloc.first_line;
      oclsp->first_column = oclloc.first_column;
      oclsp->last_line = (oclsp-1)->last_line;
      oclsp->last_column = (oclsp-1)->last_column;
      oclsp->text = 0;
    }
  else
    {
      oclsp->last_line = (oclsp+oclen-1)->last_line;
      oclsp->last_column = (oclsp+oclen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  ocn = ocr1[ocn];

  ocstate = ocpgoto[ocn - OCNTBASE] + *ocssp;
  if (ocstate >= 0 && ocstate <= OCLAST && occheck[ocstate] == *ocssp)
    ocstate = octable[ocstate];
  else
    ocstate = ocdefgoto[ocn - OCNTBASE];

  goto ocnewstate;

ocerrlab:   /* here on detecting error */

  if (! ocerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++ocnerrs;

#ifdef OCERROR_VERBOSE
      ocn = ocpact[ocstate];

      if (ocn > OCFLAG && ocn < OCLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -ocn if nec to avoid negative indexes in occheck.  */
	  for (x = (ocn < 0 ? -ocn : 0);
	       x < (sizeof(octname) / sizeof(char *)); x++)
	    if (occheck[x + ocn] == x)
	      size += strlen(octname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (ocn < 0 ? -ocn : 0);
		       x < (sizeof(octname) / sizeof(char *)); x++)
		    if (occheck[x + ocn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, octname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      ocerror(msg);
	      free(msg);
	    }
	  else
	    ocerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* OCERROR_VERBOSE */
	ocerror("parse error");
    }

  goto ocerrlab1;
ocerrlab1:   /* here on error raised explicitly by an action */

  if (ocerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (occhar == OCEOF)
	OCABORT;

#if OCDEBUG != 0
      if (ocdebug)
	fprintf(stderr, "Discarding token %d (%s).\n", occhar, octname[occhar1]);
#endif

      occhar = OCEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  ocerrstatus = 3;		/* Each real token shifted decrements this */

  goto ocerrhandle;

ocerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  ocn = ocdefact[ocstate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (ocn) goto ocdefault;
#endif

ocerrpop:   /* pop the current state because it cannot handle the error token */

  if (ocssp == ocss) OCABORT;
  ocvsp--;
  ocstate = *--ocssp;
#ifdef OCLSP_NEEDED
  oclsp--;
#endif

#if OCDEBUG != 0
  if (ocdebug)
    {
      short *ssp1 = ocss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != ocssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

ocerrhandle:

  ocn = ocpact[ocstate];
  if (ocn == OCFLAG)
    goto ocerrdefault;

  ocn += OCTERROR;
  if (ocn < 0 || ocn > OCLAST || occheck[ocn] != OCTERROR)
    goto ocerrdefault;

  ocn = octable[ocn];
  if (ocn < 0)
    {
      if (ocn == OCFLAG)
	goto ocerrpop;
      ocn = -ocn;
      goto ocreduce;
    }
  else if (ocn == 0)
    goto ocerrpop;

  if (ocn == OCFINAL)
    OCACCEPT;

#if OCDEBUG != 0
  if (ocdebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++ocvsp = oclval;
#ifdef OCLSP_NEEDED
  *++oclsp = oclloc;
#endif

  ocstate = ocn;
  goto ocnewstate;

 ocacceptlab:
  /* OCACCEPT comes here.  */
  if (ocfree_stacks)
    {
      free (ocss);
      free (ocvs);
#ifdef OCLSP_NEEDED
      free (ocls);
#endif
    }
  return 0;

 ocabortlab:
  /* OCABORT comes here.  */
  if (ocfree_stacks)
    {
      free (ocss);
      free (ocvs);
#ifdef OCLSP_NEEDED
      free (ocls);
#endif
    }
  return 1;
}

