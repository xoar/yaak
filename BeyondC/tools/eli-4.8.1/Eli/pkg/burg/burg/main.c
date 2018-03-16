char rcsid_main[] = "$Id: main.c,v 1.6 2013/11/12 18:24:10 profw Exp $";

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "b.h"
#include "fe.h"
#include "be.h"

int debugTables = 0;
static int simpleTables = 0;
static int internals = 0;
static int diagnostics = 0;

static char *inFileName;
static char *outFileName;

static char version[] = "BURG, Version 1.0";

extern int main ARGS((int argc, char **argv));

int
main(argc, argv) int argc; char **argv;
{
	int i;

	for (i = 1; argv[i]; i++) {
		char **needStr = 0;
		int *needInt = 0;

		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'V':
				fprintf(stderr, "%s\n", version);
				break;
			case 'p':
				needStr = &prefix;
				break;
			case 'o':
				needStr = &outFileName;
				break;
			case 'I':
				internals = 1;
				break;
			case 'T':
				simpleTables = 1;
				break;
			case '=':
#ifdef NOLEX
				fprintf(stderr, "'%s' was not compiled to support lexicographic ordering\n", argv[0]);
#else
				lexical = 1;
#endif /* NOLEX */
				break;
			case 'O':
				needInt = &principleCost;
				break;
			case 'c':
				needInt = &prevent_divergence;
				break;
			case 'e':
				needInt = &exceptionTolerance;
				break;
			case 'd':
				diagnostics = 1;
				break;
			case 'S':
				speedflag = 1;
				break;
			case 't':
				trimflag = 1;
				break;
			case 'G':
				grammarflag = 1;
				break;
			default:
				fprintf(stderr, "Bad option (%s)\n", argv[i]);
				return 1;
			}
		} else {
			if (inFileName) {
				fprintf(stderr, "Unexpected Filename (%s) after (%s)\n", argv[i], inFileName);
				return 1;
			}
			inFileName = argv[i];
		}
		if (needInt || needStr) {
			char *v;
			char *opt = argv[i];

			if (argv[i][2]) {
				v = &argv[i][2];
			} else {
				v = argv[++i];
				if (!v) {
					fprintf(stderr, "Expection argument after %s\n", opt);
					return 1;
				}
			}
			if (needInt) {
				*needInt = atoi(v);
			} else if (needStr) {
				*needStr = v;
			}
		}
	}

	if (inFileName) {
		if(freopen(inFileName, "r", stdin)==NULL) {
			fprintf(stderr, "Failed opening (%s)", inFileName);
			return 1;
		}
	}

	if (outFileName) {
		if ((outfile = fopen(outFileName, "w")) == NULL) {
			fprintf(stderr, "Failed opening (%s)", outFileName);
			return 1;
		}
	} else {
		outfile = stdout;
	}


	yyparse();

	if (!rules) {
		fprintf(stderr, "ERROR: No rules present\n");
		return 1;
	}

	findChainRules();
	findAllPairs();
	doGrammarNts();
	build();

	debug(debugTables, foreachList((ListFn) dumpOperator_l, operators));
	debug(debugTables, printf("---final set of states ---\n"));
	debug(debugTables, dumpMapping(globalMap));


	startBurm();
	makeNts();
	if (simpleTables) {
		makeSimple();
	} else {
		makePlanks();
	}

	startOptional();
	makeLabel();
	makeKids();

	if (internals) {
		makeChild();
		makeOpLabel();
		makeStateLabel();
	}
	endOptional();

	makeOperatorVector();
	makeNonterminals();
	if (internals) {
		makeOperators();
		makeStringArray();
		makeRuleDescArray();
		makeCostArray();
		makeDeltaCostArray();
		makeStateStringArray();
		makeNonterminalArray();
		/*
		makeLHSmap();
		*/
	}
	makeClosureArray();

	if (diagnostics) {
		reportDiagnostics();
	}

	yypurge();
	 return 0;
}
