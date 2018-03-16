static char RCSid[] = "$Id: gla_be.c,v 1.20 2013/11/12 18:48:28 profw Exp $";
/* Copyright (c) 1989, The Regents of the University of Colorado */

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

#include "dj.h"
#include <stdlib.h>
#include "obstack.h"

void readBackendData (char*);

#define ERR(msg)	fprintf (stderr, "%s", msg)

FILE *FlexStateFd;
int Nstates;
int *AcceptStates;
char *Targets;

int EofCode, LitCount, NonLitCount, NTokens;

char **Yname;
char **YauxScanner;
char **Yprocessor;
char **Ypattern;
short *YextCode;

FILE *Ft, *Fc, *Fe;

/* command line options */

int PrintTokens=0;	/* To gen a scanner that prints tokens.  Takes an optional
			   int argument that causes the assoc array to be larger than
			   just Ntokens -- incase token codes are not dense.  */
int TransFlg = 0;	/* Print Transition table */
int PartitFlg = 0;	/* Print Partition table */
int AcceptFlg = 0;	/* Print Accepting states */
int OverlapFlg = 0;	/* Warn of token code overlaps */
int MonitorFlg = 0;	/* Output monitoring code */

/*
 * diags
 */

void diags()
{
	int i;

	if (TransFlg)
		prtTrans();
	if (PartitFlg)
		prtAllPartitions();
	if (AcceptFlg) {
		printf("Accepting states:\n");
		for (i = 0; i < Nstates; i++)
			printf("%3d",i);
		printf("\n");
		for(i = 0; i < Nstates; i++)
			printf("%3d",AcceptStates[i]);
		printf("\n");
	}
}

/*
 * main
 */

int
main(argc,argv)
int argc; char **argv;
{
	int verbose = 0;
	char *progname;
	size_t count;
        FILE *fd;

	progname = argv[0];
	while (argc > 1) {
		if (argv[1][0] == '+' || argv[1][0] == '-')
			switch (argv[1][1]) {
			case 'd': sscanf (&argv[1][2], "%d", &PrintTokens);
				  if (PrintTokens <= 0) PrintTokens = 1;
				  break;
			case 'v': verbose++; break;
			case 'w': OverlapFlg++; break;
			case 'A': AcceptFlg++; break;
                        case 'M': MonitorFlg++; break;
			case 'P': PartitFlg++; break;
			case 'T': TransFlg++; break;
			default: 
				fprintf(stderr, "%s: unknown option '%c'\n", 
					progname, argv[1][1]);
			}
		else
			break;
		argc--;
		argv++;
	}

	if (argc != 5) {
		fprintf(stderr, "Usage %s [options] backend_data", progname);
		ERR(" lastdfa.binary accept.binary flex.binary\n" );
		ERR("  -d scanner will output the token stream.\n");
		ERR("  -dsiz as above, but up to SIZ non-compact tokens.\n");
		ERR("  -v give verbose statistics.\n");
		ERR("  -A print out array of Accepting states.\n");
		ERR("  -M include monitoring code.\n");
		ERR("  -T print out Transition table.\n");
		ERR("  -P print out Partition table.\n");
		exit(1);
	}

	readBackendData (argv[1]);

	fd = fopen(argv[2],"rb");
	if (!fd) { perror("lastdfa.binary"); exit(2); }

	/* machine dependent stuff -- we are about to read binary data */
	assert(sizeof(int) == sizeof(Nstates));
	count = fread((void*)&Nstates, sizeof(int), (size_t)1, fd);
	if (count != 1) {
		(void)fprintf(stderr,
			      "Read %d elements for NStates\n",
			      (int)count);
		exit(10);
	}
	if (fclose(fd) != 0) {perror("lastdfa.binary"); exit(2); }
	if (verbose)
		printf("Number of states based on lastdfa.binary = %d\n", Nstates);
	
	AcceptStates = (int *) malloc((unsigned)Nstates * sizeof(int));
	if (AcceptStates == NULL) {
		printf("no memory for AcceptStates\n");
		exit(5);
	}

	fd = fopen(argv[3],"rb");
	if (!fd) { perror("accept.binary"); exit(2); }
	count = fread((void*)AcceptStates, sizeof(int), (size_t)Nstates, fd);
	if (count != Nstates) {
		(void)fprintf(stderr,
			      "Read %d elements for AcceptStates, expected %d\n",
			      (int)count, (int)(Nstates*sizeof(int)));
		exit(10);
	}
	if (fclose(fd) != 0) {perror("accept.binary"); exit(2); }

	FlexStateFd = fopen(argv[4],"rb");
	if (!FlexStateFd) { perror("flex.binary"); exit(2); }

	Fc = fopen("xcode.h", "w");
	if (!Fc) { perror("xcode.h"); exit(2); }
	Ft = fopen("xtables.h", "w");
	if (!Ft) { perror("xtables.h"); exit(2); }
	Fe = fopen("externs", "w");
	if (!Fe) { perror("externs"); exit(2); }
	writeConstants(Ft);
	makeAllPartitions();
	if (fclose(FlexStateFd) != 0) {perror("flex.binary"); exit(2); }
	diags();	/* optional diagnostic printing */
	genCases();

	return 0;

}

/*
** In the routine  writeConstants, if PrintTokens is TRUE, we want to
** build an array of strings that reflects the user's gla specification.
** Then, when the user's scanner is run, token codes and the corresponding
** string from the specification will be reported.
**
** It is not sufficient to wrap doublequotes around his characters.
** For example, the lexical spec might be:
**                     $(((([0-9]+\.[0-9]*)|(\.[0-9]+))((e|E)(\+|\-)? ...
** but the C string needs to be:
**                    "(((([0-9]+\\.[0-9]*)|(\\.[0-9]+))((e|E)(\\+|\\-)? ..."
** and
**               $"->+"
** needs to be
**              "\"->+\""
**
** SO, when we see a backslash, we output a pair of backslashes and
** when we see a doublequote, we output  backslash doublequote.
*/

#define MAXEXPANDBUF 512

char *
expBKSLASH(in)
register char * in;	/* incomming string */
{
	static char outBuf[MAXEXPANDBUF+1];
	register char c;
	register char *out = outBuf;
	int count = 0;		/*  additional characters added to output */

	while ((c = *in++)) {
		if (c == '\\' ) {
			*out++ = '\\';
			*out++ = '\\';
			count++;
			}
		else if(c ==  '"' ) {
			*out++ = '\\';
			*out++ = '"';
			count++;
			}
		else {
			*out++ = c;
			}

		if (count+out-outBuf >= MAXEXPANDBUF)	/* firewall */
			return("expBKSLASH: very long regular expression");
		}

	*out++ = 0;
	return outBuf;
}
				
/*
 * writeConstants
 */

void
writeConstants(fp)
FILE *fp;
{
	int i;

	fprintf(fp, "#define NONLITCOUNT %d\n", NonLitCount);
	fprintf(fp, "#define LITCOUNT %d\n", LitCount);
	fprintf(fp, "#define NTOKENS %d\n", NTokens);
	fprintf(fp, "#define EOFTOKEN %d\n", EofCode);

	/* declare external processors */
	fputs("#if defined(__cplusplus) || defined(__STDC__)\n", fp);
	fputs("extern void", fp);
	for (i = 1; i <= NonLitCount; i++)
		if (Yprocessor[i+LitCount]) {
			fprintf(fp," %s(const char *, int, int *, int *),\n",
				Yprocessor[i+LitCount]);
			fprintf(Fe, "s/^%s[ 	][ 	]*//p\n",
				Yprocessor[i+LitCount]);
		}
	fputs(" dummy1(char *, int, int *, int *);\n", fp);
	fputs("#else\n", fp);
	fputs("extern void", fp);
	for (i = 1; i <= NonLitCount; i++)
		if (Yprocessor[i+LitCount])
			fprintf(fp," %s(),\n", Yprocessor[i+LitCount]);
	fputs(" dummy1();\n", fp);
	fputs("#endif\n", fp);

	/* declare external auxScanners */
	fputs("#if defined(__cplusplus) || defined(__STDC__)\n", fp);
	fputs("extern char", fp);
	for (i = 1; i <= NonLitCount; i++)
		if (YauxScanner[i+LitCount]) {
			fprintf(fp," *%s(char *, int),\n",
				YauxScanner[i+LitCount]);
			fprintf(Fe, "s/^%s[ 	][ 	]*//p\n",
				YauxScanner[i+LitCount]);
		}
	fputs(" *dummy2(char *, int);\n", fp);
	fputs("#else\n", fp);
	fputs("extern char", fp);
	for (i = 1; i <= NonLitCount; i++)
		if (YauxScanner[i+LitCount])
			fprintf(fp," *%s(),\n", YauxScanner[i+LitCount]);
	fputs(" *dummy2();\n", fp);
	fputs("#endif\n", fp);
	
	/*
	** Print out an associative array for tokens strings.
	** If PrintTokens==1 then assume a dense encoding starting at 0.
	** (Eli starts codes at 1 with EOF, and NTokens does not include
	** EOF. This explains the need for NTokens+1 instead of just NTokens.)
	** We could have sorted extCode[], but it is easier 
	** to just load a new array of pointers.
	**
	** If PrintTokens>1, then use this value as array size.  This is for
	** the guy that wants tokens printed but his codes are not dense.
	**
	** While we are here, it is easy to check for token code overlaps.
	*/
	if (PrintTokens || OverlapFlg) {
		int size = PrintTokens==1? NTokens+1 : PrintTokens;
		char **sortTok =
			(char **) malloc((unsigned)(size) * sizeof(char *));
		if (sortTok == NULL) {
			printf("no memory for sortTok\n");
			exit(5);
		}
		for (i = 0; i < size; i++)
			sortTok[i] = NULL;
		for (i = 0; i < size; i++)
			if (YextCode[i] >= 0 && YextCode[i]<size) {
				/* in range */
				if (OverlapFlg &&
				    (sortTok[YextCode[i]] !=NULL))
					fprintf(stderr, "Warning: code %d reused with %s\n",
						YextCode[i] , Ypattern[i]);
				sortTok[YextCode[i]] = Ypattern[i];
			} else { /* out of range */
				if(OverlapFlg && (Ypattern[i] != NULL))
					fprintf(stderr, "Warning: code %d for %s is >= %d\n",
						YextCode[i] , Ypattern[i], size);
			}
		if (PrintTokens) {
			fputs("/* turns on printing, and give array size */\n", fp);
			fprintf(fp,"#define GLAPRINTTOKENS %d\n", size);
			fputs("int GlaPrintTokens = 1;\n", fp);
			fprintf(fp, "char *TokenStrings[%d] = {\n", size);
			for (i = 0; i < size; i++)
				fprintf(fp, "	\"%s\",	/* %d */\n",
					sortTok[i]==NULL?"":expBKSLASH(sortTok[i]), i);
			fputs("};\n", fp);
		}
	}

	/* declare array of non-literal token names */
        if (MonitorFlg) {
            fputs("#ifdef MONITOR\n", fp);
            fputs("int mon_nonlit_codes[] = {\n", fp);
            for (i = 1; i <= NonLitCount; i++) {
	        fprintf(fp, " %d,\n", YextCode[i+LitCount]);
            }
            fputs(" -1\n};\nCONST char *mon_token_names[] = {\n", fp);
            for (i = 1; i <= NonLitCount; i++) {
	        char *name = Yname[i+LitCount];
	        fprintf(fp, " \"%s\",\n", name == NULL ? "" : name);
            }
            fputs(" \"\"\n};\n#endif\n", fp);
        }
}

/*
 * readBackendData
 */

#define GETSTR(x) { \
	    char c, *t; \
	    while ((c = fgetc (fp)) != '\n') \
              obstack_1grow(&Strings, c); \
            obstack_1grow(&Strings, '\0'); \
            t = (char *)obstack_finish(&Strings); \
	    if (strcmp (t, "(null)") == 0) { \
                    obstack_free(&Strings, (void *)t); \
		    (x) = NULL; \
	    } else \
		    (x) = t; \
        }

void
readBackendData (filename)
char *filename;
{
	FILE *fp;
	int i;
	Obstack Strings;

	fp = fopen (filename, "r");
	if (!fp) { perror(filename); exit(2); }

	fscanf (fp, "%d %d %d ", &EofCode, &LitCount, &NonLitCount);
	NTokens = LitCount + NonLitCount;

	Yname = (char **)malloc(sizeof(char *) * (NTokens + 1));
	Ypattern = (char **)malloc(sizeof(char *) * (NTokens + 1));
	YauxScanner = (char **)malloc(sizeof(char *) * (NTokens + 1));
	Yprocessor = (char **)malloc(sizeof(char *) * (NTokens + 1));
	YextCode = (short *)malloc(sizeof(short) * (NTokens + 1));
	if (!Ypattern || !YauxScanner || !Yprocessor || !YextCode) {
	  fprintf(stderr, "couldn't allocate enough memory\n");
	  exit(1);
	}

	Yname[0] = Ypattern[0] = YauxScanner[0] = Yprocessor[0] = (char *)0;
	YextCode[0] = 1;

        obstack_init(&Strings);

	for (i = 1; i <= NTokens; i++) {
		GETSTR(Yname[i]);
		GETSTR(Ypattern[i]);
		GETSTR(YauxScanner[i]);
		GETSTR(Yprocessor[i]);
		fscanf (fp, "%hd\n", &(YextCode[i]));
	}

	fclose (fp);
}
