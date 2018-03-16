#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 "gram.y"
char rcsid_gram[] = "$Id: y.tab.c,v 1.2 2004/02/03 20:10:58 waite Exp $";

#include <stdio.h>
#include "b.h"
#include "fe.h"
#line 9 "gram.y"
typedef union {
	int y_int;
	char *y_string;
	Arity y_arity;
	Binding y_binding;
	PatternAST y_patternAST;
	RuleAST y_ruleAST;
	List y_list;
	IntList y_intlist;
} YYSTYPE;
#line 34 "y.tab.c"
#define YYERRCODE 256
#define ERROR 257
#define K_TERM 258
#define K_GRAM 259
#define K_START 260
#define K_PPERCENT 261
#define INT 262
#define ID 263
const short yylhs[] = {                                        -1,
    0,    0,   11,    7,    7,    1,    1,    1,   10,   10,
    9,    9,    2,    8,    8,    5,    6,    6,    6,    3,
    3,    4,    4,    4,
};
const short yylen[] = {                                         2,
    1,    2,    3,    0,    2,    2,    2,    2,    0,    2,
    0,    2,    3,    0,    2,    7,    1,    4,    6,    0,
    4,    0,    3,    2,
};
const short yydefred[] = {                                      4,
    0,    0,    0,   11,    9,    0,   14,    5,    2,    0,
    0,    8,    0,    0,   12,   10,    0,   15,    0,    0,
   13,    0,    0,    0,    0,    0,    0,   18,    0,    0,
    0,    0,    0,   16,   19,    0,    0,    0,   24,    0,
   21,   23,
};
const short yydgoto[] = {                                       1,
    8,   15,   31,   38,   18,   23,    2,   13,   10,   11,
    3,
};
const short yysindex[] = {                                      0,
    0, -247, -252,    0,    0, -244,    0,    0,    0, -242,
 -236,    0, -234,  -41,    0,    0,  -28,    0, -231, -230,
    0,  -12,  -29, -230, -228,  -37,   -5,    0, -230, -226,
  -22,   -3,  -44,    0,    0,  -44, -223,   -1,    0,  -44,
    0,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,   41,    0,    0,    0,    0,    0,    0, -243,
 -235,    0,    1,    0,    0,    0,    0,    0,    0,    0,
    0,  -39,    0,    0,    0,    0,  -17,    0,    0,    0,
    0,    0,    2,    0,    0,    2,    0,    0,    0,    2,
    0,    0,
};
const short yygindex[] = {                                      0,
    0,    0,    0,  -30,    0,  -21,    0,    0,    0,    0,
    0,
};
#define YYTABLESIZE 262
const short yytable[] = {                                      37,
    3,   17,   26,   28,   17,   39,   29,   32,    9,   42,
    4,    5,    6,    7,    6,    6,    6,    6,   12,   19,
   14,   17,    7,    7,    7,    7,   16,   24,   17,   20,
   21,   25,   22,   27,   30,   33,   34,   35,   40,   41,
    1,   20,   22,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   36,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,
};
const short yycheck[] = {                                      44,
    0,   41,   24,   41,   44,   36,   44,   29,  261,   40,
  258,  259,  260,  261,  258,  259,  260,  261,  263,   61,
  263,   61,  258,  259,  260,  261,  263,   40,  263,   58,
  262,   61,  263,  262,   40,  262,   59,   41,  262,   41,
    0,   59,   41,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  261,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 263
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ERROR",
"K_TERM","K_GRAM","K_START","K_PPERCENT","INT","ID",
};
const char * const yyrule[] = {
"$accept : full",
"full : spec",
"full : spec K_PPERCENT",
"spec : decls K_PPERCENT rules",
"decls :",
"decls : decls decl",
"decl : K_TERM bindinglist",
"decl : K_GRAM grammarlist",
"decl : K_START ID",
"grammarlist :",
"grammarlist : grammarlist ID",
"bindinglist :",
"bindinglist : bindinglist binding",
"binding : ID '=' INT",
"rules :",
"rules : rules rule",
"rule : ID ':' pattern '=' INT cost ';'",
"pattern : ID",
"pattern : ID '(' pattern ')'",
"pattern : ID '(' pattern ',' pattern ')'",
"cost :",
"cost : '(' INT costtail ')'",
"costtail :",
"costtail : ',' INT costtail",
"costtail : INT costtail",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
#line 44 "gram.y"
{ yyfinished(); }
break;
case 3:
#line 48 "gram.y"
 { doSpec(yyvsp[-2].y_list, yyvsp[0].y_list); }
break;
case 4:
#line 51 "gram.y"
 { yyval.y_list = 0; }
break;
case 5:
#line 52 "gram.y"
 { yyval.y_list = newList(yyvsp[0].y_arity, yyvsp[-1].y_list); }
break;
case 6:
#line 55 "gram.y"
 { yyval.y_arity = newArity(-1, yyvsp[0].y_list); }
break;
case 7:
#line 56 "gram.y"
 { yyval.y_arity = 0; doGram(yyvsp[0].y_list); }
break;
case 8:
#line 57 "gram.y"
 { yyval.y_arity = 0; doStart(yyvsp[0].y_string); }
break;
case 9:
#line 60 "gram.y"
 { yyval.y_list = 0; }
break;
case 10:
#line 61 "gram.y"
 { yyval.y_list = newList(yyvsp[0].y_string, yyvsp[-1].y_list); }
break;
case 11:
#line 64 "gram.y"
 { yyval.y_list = 0; }
break;
case 12:
#line 65 "gram.y"
 { yyval.y_list = newList(yyvsp[0].y_binding, yyvsp[-1].y_list); }
break;
case 13:
#line 68 "gram.y"
 { yyval.y_binding = newBinding(yyvsp[-2].y_string, yyvsp[0].y_int); }
break;
case 14:
#line 71 "gram.y"
 { yyval.y_list = 0; }
break;
case 15:
#line 72 "gram.y"
 { yyval.y_list = newList(yyvsp[0].y_ruleAST, yyvsp[-1].y_list); }
break;
case 16:
#line 75 "gram.y"
 { yyval.y_ruleAST = newRuleAST(yyvsp[-6].y_string, yyvsp[-4].y_patternAST, yyvsp[-2].y_int, yyvsp[-1].y_intlist); }
break;
case 17:
#line 78 "gram.y"
 { yyval.y_patternAST = newPatternAST(yyvsp[0].y_string, 0); }
break;
case 18:
#line 79 "gram.y"
 { yyval.y_patternAST = newPatternAST(yyvsp[-3].y_string, newList(yyvsp[-1].y_patternAST,0)); }
break;
case 19:
#line 80 "gram.y"
 { yyval.y_patternAST = newPatternAST(yyvsp[-5].y_string, newList(yyvsp[-3].y_patternAST, newList(yyvsp[-1].y_patternAST, 0))); }
break;
case 20:
#line 83 "gram.y"
 { yyval.y_intlist = 0; }
break;
case 21:
#line 84 "gram.y"
 { yyval.y_intlist = newIntList(yyvsp[-2].y_int, yyvsp[-1].y_intlist); }
break;
case 22:
#line 87 "gram.y"
 { yyval.y_intlist = 0; }
break;
case 23:
#line 88 "gram.y"
 { yyval.y_intlist = newIntList(yyvsp[-1].y_int, yyvsp[0].y_intlist); }
break;
case 24:
#line 89 "gram.y"
 { yyval.y_intlist = newIntList(yyvsp[-1].y_int, yyvsp[0].y_intlist); }
break;
#line 498 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
