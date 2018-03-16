#ifndef YYERRCODE
#define YYERRCODE 256
#endif

#define ERROR 257
#define K_TERM 258
#define K_GRAM 259
#define K_START 260
#define K_PPERCENT 261
#define INT 262
#define ID 263
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
extern YYSTYPE yylval;
