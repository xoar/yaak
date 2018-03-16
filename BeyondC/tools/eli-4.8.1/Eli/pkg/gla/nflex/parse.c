# define CHAR 257
# define NUMBER 258
# define SECTEND 259
# define SCDECL 260
# define XSCDECL 261
# define WHITESPACE 262
# define NAME 263
# define PREVCCL 264

#include "flexdef.h"
#include "misc.h"
#include "sym.h"
#include "ccl.h"
#include "ecs.h"
#include "nfa.h"
#include "yylex.h"

int pat, scnum, eps, headcnt, trailcnt, anyccl, lastchar, i, actvp, rulelen;
int trlcontxt, xcluflg, cclsorted, varlength;
unsigned char clower();

static int madeany = false;  /* whether we've made the '.' character class */

#ifdef __cplusplus
#  include <stdio.h>
#  include <yacc.h>
#endif	/* __cplusplus */ 
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif

/* __YYSCLASS defines the scoping/storage class for global objects
 * that are NOT renamed by the -p option.  By default these names
 * are going to be 'static' so that multi-definition errors
 * will not occur with multiple parsers.
 * If you want (unsupported) access to internal names you need
 * to define this to be null so it implies 'extern' scope.
 * This should not be used in conjunction with -p.
 */
#ifndef __YYSCLASS
# define __YYSCLASS static
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval;
__YYSCLASS YYSTYPE yyval;
typedef int yytabelem;
# define YYERRCODE 256



/* synerr - report a syntax error
 *
 * synopsis
 *    char str[];
 *    synerr( str );
 */

void
synerr( str )
char str[];

    {
    syntaxerror = true;
    fprintf( stderr, "Syntax error at flex line %d:  %s\n", linenum, str );
    }


/* yyerror - eat up an error message from the parser
 *
 * synopsis
 *    char msg[];
 *    yyerror( msg );
 */

void
yyerror( msg )
char msg[];

    {
    }
__YYSCLASS yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 2,
	259, 4,
	260, 4,
	261, 4,
	-2, 0,
-1, 11,
	0, 1,
	-2, 14,
	};
# define YYNPROD 51
# define YYLAST 268
__YYSCLASS yytabelem yyact[]={

    29,    29,    29,    45,    16,    71,    30,    30,    30,    56,
    44,    15,    26,    26,    26,    33,     7,     8,     9,    77,
    12,    75,    67,    64,    63,    78,    22,     4,    72,    42,
    79,    66,    55,    39,    48,    49,    54,    41,    62,    25,
    41,    74,    24,    20,    35,    10,    52,    27,    23,    43,
    18,    17,    13,    14,     6,    50,    61,    32,    32,    32,
    19,    36,    37,    38,    47,    11,    46,     5,     3,     2,
     1,    58,    59,     0,    53,     0,     0,     0,     0,     0,
    57,     0,     0,    60,     0,     0,    47,     0,     0,     0,
     0,    70,    69,     0,     0,     0,     0,     0,     0,     0,
    47,     0,     0,     0,     0,     0,     0,     0,     0,    73,
     0,     0,     0,     0,    40,    51,     0,    40,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    76,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    68,    68,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    21,    31,    31,    31,     0,     0,     0,     0,
    28,    28,    28,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    65,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    34 };
__YYSCLASS yytabelem yypact[]={

 -3000, -3000,  -229,  -243,    35, -3000,  -242, -3000, -3000, -3000,
 -3000, -3000,  -252,   -34,     5, -3000, -3000,    34,   -33,   -32,
    -7, -3000,  -253,   -32,   -32,    -8, -3000, -3000, -3000, -3000,
   -32, -3000,   -62, -3000,  -254, -3000,   -32,    -7,    -7, -3000,
   -32, -3000, -3000,    -6, -3000, -3000,   -32,    -8, -3000, -3000,
 -3000,  -234,   -11,   -10,   -71, -3000, -3000,    -7, -3000, -3000,
   -32, -3000,  -258,   -16, -3000, -3000, -3000, -3000,    -4,   -72,
 -3000, -3000,  -106, -3000,  -232, -3000,   -95, -3000, -3000, -3000 };
__YYSCLASS yytabelem yypgo[]={

     0,    70,    69,    68,    67,    65,    54,    53,    52,    51,
    50,    43,    33,    49,    42,    48,    39,    47,    46,    36 };
__YYSCLASS yytabelem yyr1[]={

     0,     1,     2,     3,     3,     3,     4,     6,     6,     7,
     7,     7,     5,     5,     8,     9,     9,     9,     9,     9,
    10,    13,    13,    13,    12,    12,    11,    11,    11,    15,
    14,    14,    16,    16,    16,    16,    16,    16,    16,    16,
    16,    16,    16,    16,    17,    17,    19,    19,    19,    18,
    18 };
__YYSCLASS yytabelem yyr2[]={

     0,     8,     1,    10,     0,     5,     2,     3,     3,     7,
     3,     3,     8,     0,     1,     9,     7,     7,     5,     3,
     6,     7,     3,     3,     3,     1,     7,     5,     3,     5,
     5,     3,     5,     5,     5,    13,    11,     9,     3,     3,
     3,     7,     7,     3,     7,     9,     9,     5,     1,     5,
     1 };
__YYSCLASS yytabelem yychk[]={

 -3000,    -1,    -2,    -3,   256,    -4,    -6,   259,   260,   261,
    10,    -5,   262,    -8,    -7,   263,   256,    -9,   -10,    94,
   -11,   256,    60,   -15,   -14,   -16,    46,   -17,   264,    34,
    40,   257,    91,    10,   262,    10,    94,   -11,   -11,   -12,
   124,    47,    36,   -13,   263,   256,   -14,   -16,    42,    43,
    63,   123,   -18,   -11,   -19,    94,   263,   -11,   -12,   -12,
   -14,    62,    44,   258,    34,   257,    41,    93,   257,   -19,
   -12,   263,    44,   125,    45,    93,   258,   125,   257,   125 };
__YYSCLASS yytabelem yydef[]={

     2,    -2,    -2,     0,     0,    13,     0,     6,     7,     8,
     5,    -2,     0,     0,     0,    10,    11,     0,     0,     0,
    25,    19,     0,     0,    28,    31,    38,    39,    40,    50,
     0,    43,    48,     3,     0,    12,     0,    25,    25,    18,
     0,    29,    24,     0,    22,    23,    27,    30,    32,    33,
    34,     0,     0,     0,     0,    48,     9,    25,    16,    17,
    26,    20,     0,     0,    41,    49,    42,    44,    47,     0,
    15,    21,     0,    37,     0,    45,     0,    36,    46,    35 };
typedef struct { unsigned char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

__YYSCLASS yytoktype yytoks[] =
{
	"CHAR",	257,
	"NUMBER",	258,
	"SECTEND",	259,
	"SCDECL",	260,
	"XSCDECL",	261,
	"WHITESPACE",	262,
	"NAME",	263,
	"PREVCCL",	264,
	"-unknown-",	-1	/* ends search */
};

__YYSCLASS char * yyreds[] =
{
	"-no such reduction-",
	"goal : initlex sect1 sect1end sect2",
	"initlex : /* empty */",
	"sect1 : sect1 startconddecl WHITESPACE namelist1 '\n'",
	"sect1 : /* empty */",
	"sect1 : error '\n'",
	"sect1end : SECTEND",
	"startconddecl : SCDECL",
	"startconddecl : XSCDECL",
	"namelist1 : namelist1 WHITESPACE NAME",
	"namelist1 : NAME",
	"namelist1 : error",
	"sect2 : sect2 initforrule flexrule '\n'",
	"sect2 : /* empty */",
	"initforrule : /* empty */",
	"flexrule : scon '^' re eol",
	"flexrule : scon re eol",
	"flexrule : '^' re eol",
	"flexrule : re eol",
	"flexrule : error",
	"scon : '<' namelist2 '>'",
	"namelist2 : namelist2 ',' NAME",
	"namelist2 : NAME",
	"namelist2 : error",
	"eol : '$'",
	"eol : /* empty */",
	"re : re '|' series",
	"re : re2 series",
	"re : series",
	"re2 : re '/'",
	"series : series singleton",
	"series : singleton",
	"singleton : singleton '*'",
	"singleton : singleton '+'",
	"singleton : singleton '?'",
	"singleton : singleton '{' NUMBER ',' NUMBER '}'",
	"singleton : singleton '{' NUMBER ',' '}'",
	"singleton : singleton '{' NUMBER '}'",
	"singleton : '.'",
	"singleton : fullccl",
	"singleton : PREVCCL",
	"singleton : '"' string '"'",
	"singleton : '(' re ')'",
	"singleton : CHAR",
	"fullccl : '[' ccl ']'",
	"fullccl : '[' '^' ccl ']'",
	"ccl : ccl CHAR '-' CHAR",
	"ccl : ccl CHAR",
	"ccl : /* empty */",
	"string : string CHAR",
	"string : /* empty */",
};
#endif /* YYDEBUG */
#define YYFLAG  (-3000)
/* @(#) $Revision: 70.10 $ */    

/*
** Skeleton parser driver for yacc output
*/

#if defined(NLS) && !defined(NL_SETN)
#include <msgbuf.h>
#endif

#ifndef nl_msg
#define nl_msg(i,s) (s)
#endif

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab

#ifndef __RUNTIME_YYMAXDEPTH
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#else
#define YYACCEPT	{free_stacks(); return(0);}
#define YYABORT		{free_stacks(); return(1);}
#endif

#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( (nl_msg(30001,"syntax error - cannot backup")) );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
/* define for YYFLAG now generated by yacc program. */
/*#define YYFLAG		(FLAGVAL)*/

/*
** global variables used by the parser
*/
# ifndef __RUNTIME_YYMAXDEPTH
__YYSCLASS YYSTYPE yyv[ YYMAXDEPTH ];	/* value stack */
__YYSCLASS int yys[ YYMAXDEPTH ];		/* state stack */
# else
__YYSCLASS YYSTYPE *yyv;			/* pointer to malloc'ed value stack */
__YYSCLASS int *yys;			/* pointer to malloc'ed stack stack */

#if defined(__STDC__) || defined (__cplusplus)
#include <stdlib.h>
#else
	extern char *malloc();
	extern char *realloc();
	extern void free();
#endif /* __STDC__ or __cplusplus */


static int allocate_stacks(); 
static void free_stacks();
# ifndef YYINCREMENT
# define YYINCREMENT (YYMAXDEPTH/2) + 10
# endif
# endif	/* __RUNTIME_YYMAXDEPTH */
long  yymaxdepth = YYMAXDEPTH;

__YYSCLASS YYSTYPE *yypv;			/* top of value stack */
__YYSCLASS int *yyps;			/* top of state stack */

__YYSCLASS int yystate;			/* current state */
__YYSCLASS int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
__YYSCLASS int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */

	/*
	** Initialize externals - yyparse may be called more than once
	*/
# ifdef __RUNTIME_YYMAXDEPTH
	if (allocate_stacks()) YYABORT;
# endif
	yypv = &yyv[0]; yypv--;
	yyps = &yys[0]; yyps--;
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
# ifndef __RUNTIME_YYMAXDEPTH
			yyerror( (nl_msg(30002,"yacc stack overflow")) );
			YYABORT;
# else
			/* save old stack bases to recalculate pointers */
			YYSTYPE * yyv_old = yyv;
			int * yys_old = yys;
			yymaxdepth += YYINCREMENT;
			yys = (int *) realloc(yys, yymaxdepth * sizeof(int));
			yyv = (YYSTYPE *) realloc(yyv, yymaxdepth * sizeof(YYSTYPE));
			if (yys==0 || yyv==0) {
			    yyerror( (nl_msg(30002,"yacc stack overflow")) );
			    YYABORT;
			    }
			/* Reset pointers into stack */
			yy_ps = (yy_ps - yys_old) + yys;
			yyps = (yyps - yys_old) + yys;
			yy_pv = (yy_pv - yyv_old) + yyv;
			yypv = (yypv - yyv_old) + yyv;
# endif

		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( (nl_msg(30003,"syntax error")) );
				yynerrs++;
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 2:
{
			/* initialize for processing rules */

			/* create default DFA start condition */
			scinstal( (unsigned char *)"INITIAL", false );
			} break;
case 5:
{ synerr( "unknown error processing section 1" ); } break;
case 7:
{
			/* these productions are separate from the s1object
			 * rule because the semantics must be done before
			 * we parse the remainder of an s1object
			 */

			xcluflg = false;
			} break;
case 8:
{ xcluflg = true; } break;
case 9:
{ scinstal( nmstr, xcluflg ); } break;
case 10:
{ scinstal( nmstr, xcluflg ); } break;
case 11:
{ synerr( "bad start condition list" ); } break;
case 14:
{
			/* initialize for a parse of one rule */
			trlcontxt = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			} break;
case 15:
{
			pat = link_machines( yypvt[-1], yypvt[-0] );
			add_accept( pat, headcnt, trailcnt );

			for ( i = 1; i <= actvp; ++i )
			    scbol[actvsc[i]] = mkbranch( scbol[actvsc[i]], pat );
			} break;
case 16:
{
			pat = link_machines( yypvt[-1], yypvt[-0] );
			add_accept( pat, headcnt, trailcnt );

			for ( i = 1; i <= actvp; ++i )
			    scset[actvsc[i]] = mkbranch( scset[actvsc[i]], pat );
			} break;
case 17:
{
			pat = link_machines( yypvt[-1], yypvt[-0] );
			add_accept( pat, headcnt, trailcnt );

			/* add to all non-exclusive start conditions,
			 * including the default (0) start condition
			 */

			for ( i = 1; i <= lastsc; ++i )
			    if ( ! scxclu[i] )
				scbol[i] = mkbranch( scbol[i], pat );
			} break;
case 18:
{
			pat = link_machines( yypvt[-1], yypvt[-0] );
			add_accept( pat, headcnt, trailcnt );

			for ( i = 1; i <= lastsc; ++i )
			    if ( ! scxclu[i] )
				scset[i] = mkbranch( scset[i], pat );
			} break;
case 19:
{ synerr( "unrecognized rule" ); } break;
case 21:
{
			if ( (scnum = sclookup( nmstr )) == 0 )
			    synerr( "undeclared start condition" );

			else
			    actvsc[++actvp] = scnum;
			} break;
case 22:
{
			if ( (scnum = sclookup( nmstr )) == 0 )
			    synerr( "undeclared start condition" );
			else
			    actvsc[actvp = 1] = scnum;
			} break;
case 23:
{ synerr( "bad start condition list" ); } break;
case 24:
{
			if ( trlcontxt )
			    {
			    synerr( "trailing context used twice" );
			    yyval = mkstate( SYM_EPSILON );
			    }
			else
			    {
			    trlcontxt = true;

			    if ( ! varlength )
				headcnt = rulelen;

			    ++rulelen;
			    trailcnt = 1;

			    eps = mkstate( SYM_EPSILON );
			    yyval = link_machines( eps, mkstate( '\n' ) );
			    }
			} break;
case 25:
{
		        yyval = mkstate( SYM_EPSILON );

			if ( trlcontxt )
			    {
			    if ( varlength && headcnt == 0 )
				/* both head and trail are variable-length */
				synerr( "illegal trailing context" );

			    else
				trailcnt = rulelen;
			    }
		        } break;
case 26:
{
			varlength = true;

			yyval = mkor( yypvt[-2], yypvt[-0] );
			} break;
case 27:
{ yyval = link_machines( yypvt[-1], yypvt[-0] ); } break;
case 28:
{ yyval = yypvt[-0]; } break;
case 29:
{
			/* this rule is separate from the others for "re" so
			 * that the reduction will occur before the trailing
			 * series is parsed
			 */

			if ( trlcontxt )
			    synerr( "trailing context used twice" );
			else
			    trlcontxt = true;

			if ( varlength )
			    /* the trailing context had better be fixed-length */
			    varlength = false;
			else
			    headcnt = rulelen;

			rulelen = 0;
			yyval = yypvt[-1];
			} break;
case 30:
{
			/* this is where concatenation of adjacent patterns
			 * gets done
			 */
			yyval = link_machines( yypvt[-1], yypvt[-0] );
			} break;
case 31:
{ yyval = yypvt[-0]; } break;
case 32:
{
			varlength = true;

			yyval = mkclos( yypvt[-1] );
			} break;
case 33:
{
			varlength = true;

			yyval = mkposcl( yypvt[-1] );
			} break;
case 34:
{
			varlength = true;

			yyval = mkopt( yypvt[-1] );
			} break;
case 35:
{
			varlength = true;

			if ( yypvt[-3] > yypvt[-1] || yypvt[-3] <= 0 )
			    {
			    synerr( "bad iteration values" );
			    yyval = yypvt[-5];
			    }
			else
			    yyval = mkrep( yypvt[-5], yypvt[-3], yypvt[-1] );
			} break;
case 36:
{
			varlength = true;

			if ( yypvt[-2] <= 0 )
			    {
			    synerr( "iteration value must be positive" );
			    yyval = yypvt[-4];
			    }

			else
			    yyval = mkrep( yypvt[-4], yypvt[-2], INFINITY );
			} break;
case 37:
{
			/* the singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			if ( yypvt[-1] <= 0 )
			    {
			    synerr( "iteration value must be positive" );
			    yyval = yypvt[-3];
			    }

			else
			    yyval = link_machines( yypvt[-3], copysingl( yypvt[-3], yypvt[-1] - 1 ) );
			} break;
case 38:
{
			if ( ! madeany )
			    {
			    /* create the '.' character class */
			    anyccl = cclinit();
			    ccladd( anyccl, '\n' );
			    cclnegate( anyccl );

			    if ( useecs )
				mkeccl( ccltbl + cclmap[anyccl],
					ccllen[anyccl], nextecm,
					ecgroup, CSIZE );
			    
			    madeany = true;
			    }

			++rulelen;

			yyval = mkstate( -anyccl );
			} break;
case 39:
{
			if ( ! cclsorted )
			    /* sort characters for fast searching.  We use a
			     * shell sort since this list could be large.
			     */
			    cshell( ccltbl + cclmap[yypvt[-0]], ccllen[yypvt[-0]] );

			if ( useecs )
			    mkeccl( ccltbl + cclmap[yypvt[-0]], ccllen[yypvt[-0]],
				    nextecm, ecgroup, CSIZE );
				     
			++rulelen;

			yyval = mkstate( -yypvt[-0] );
			} break;
case 40:
{
			++rulelen;

			yyval = mkstate( -yypvt[-0] );
			} break;
case 41:
{ yyval = yypvt[-1]; } break;
case 42:
{ yyval = yypvt[-1]; } break;
case 43:
{
			++rulelen;

			if ( yypvt[-0] == '\0' )
			    synerr( "null in rule" );

			if ( caseins && yypvt[-0] >= 'A' && yypvt[-0] <= 'Z' )
			    yypvt[-0] = clower( yypvt[-0] );

			yyval = mkstate( yypvt[-0] );
			} break;
case 44:
{ yyval = yypvt[-1]; } break;
case 45:
{
			/* *Sigh* - to be compatible Unix lex, negated ccls
			 * match newlines
			 */
#ifdef NOTDEF
			ccladd( yypvt[-1], '\n' ); /* negated ccls don't match '\n' */
			cclsorted = false; /* because we added the newline */
#endif
			cclnegate( yypvt[-1] );
			yyval = yypvt[-1];
			} break;
case 46:
{
			if ( yypvt[-2] > yypvt[-0] )
			    synerr( "negative range in character class" );

			else
			    {
			    if ( caseins )
				{
				if ( yypvt[-2] >= 'A' && yypvt[-2] <= 'Z' )
				    yypvt[-2] = clower( yypvt[-2] );
				if ( yypvt[-0] >= 'A' && yypvt[-0] <= 'Z' )
				    yypvt[-0] = clower( yypvt[-0] );
				}

			    for ( i = yypvt[-2]; i <= yypvt[-0]; ++i )
			        ccladd( yypvt[-3], i );

			    /* keep track if this ccl is staying in alphabetical
			     * order
			     */
			    cclsorted = cclsorted && (yypvt[-2] > lastchar);
			    lastchar = yypvt[-0];
			    }
			
			yyval = yypvt[-3];
			} break;
case 47:
{
			if ( caseins )
			    if ( yypvt[-0] >= 'A' && yypvt[-0] <= 'Z' )
				yypvt[-0] = clower( yypvt[-0] );

			ccladd( yypvt[-1], yypvt[-0] );
			cclsorted = cclsorted && (yypvt[-0] > lastchar);
			lastchar = yypvt[-0];
			yyval = yypvt[-1];
			} break;
case 48:
{
			cclsorted = true;
			lastchar = 0;
			yyval = cclinit();
			} break;
case 49:
{
			if ( caseins )
			    if ( yypvt[-0] >= 'A' && yypvt[-0] <= 'Z' )
				yypvt[-0] = clower( yypvt[-0] );

			++rulelen;

			yyval = link_machines( yypvt[-1], mkstate( yypvt[-0] ) );
			} break;
case 50:
{ yyval = mkstate( SYM_EPSILON ); } break;
	}
	goto yystack;		/* reset registers in driver code */
}

# ifdef __RUNTIME_YYMAXDEPTH

static int allocate_stacks() {
	/* allocate the yys and yyv stacks */
	yys = (int *) malloc(yymaxdepth * sizeof(int));
	yyv = (YYSTYPE *) malloc(yymaxdepth * sizeof(YYSTYPE));

	if (yys==0 || yyv==0) {
	   yyerror( (nl_msg(30004,"unable to allocate space for yacc stacks")) );
	   return(1);
	   }
	else return(0);

}


static void free_stacks() {
	if (yys!=0) free((char *) yys);
	if (yyv!=0) free((char *) yyv);
}

# endif  /* defined(__RUNTIME_YYMAXDEPTH) */

