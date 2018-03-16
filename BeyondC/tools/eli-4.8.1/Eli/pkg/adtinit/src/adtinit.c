static char RCSid[] = "$Id: adtinit.c,v 1.14 2013/11/11 04:19:21 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "csm.h"
#include "idn.h"

int
#if defined(__cplusplus) || defined(__STDC__)
main(int argc, char *argv[])
#else
main(argc,argv)
int argc; char *argv[];
#endif
{	char line[BUFSIZ];
	char *codefile=NULL, *symbfile=NULL;
	int cl, code, length;
	FILE *f, *h, *fopen();

	while (argc > 1 && *argv[1] == '-') {
		switch (*(++argv[1])) {
		case 'f': dofold = 1; break;
		case 'c': argc--; argv++; codefile = argv[1]; break;
		case 's': argc--; argv++; symbfile = argv[1]; break;
		default: fprintf(stderr, "Invalid option -%s\n", argv[1]);
		}
		argc--; argv++;
	}

	if (symbfile != NULL) {
		if ((f = fopen(symbfile, "r")) == NULL) {
			fprintf(stderr, "Cannot open file %s\n", symbfile);
			exit(1);
		}

		while (fgets(line, BUFSIZ, f) != NULL) {
			char str[BUFSIZ];
			int ndx;

			sscanf(line, " %d %d%*c%[^\n]", &code, &length, str);

			if (code != 0 || (strchr(str,' ') == 0 && length>0))
				mkidn(str,length,&code,&ndx);
			else (void)stostr(str, length);
		}
		(void)fclose(f);
	}

	if (codefile != NULL) {
		if ((f = fopen(codefile, "r")) == NULL) {
			fprintf(stderr, "Cannot open file %s\n", codefile);
			exit(1);
		}

		while (fgets(line, BUFSIZ, f) != NULL) {
			char str[BUFSIZ];
			int ndx;

			sscanf(line, " %d %*d %d %d%*c%[^\n]", &cl, &code, &length, str);
			if (cl == 5) mkidn(str,length,&code,&ndx);
		}
		(void)fclose(f);
	}

	h = fopen("csmtbl.h", "w"); savestr(h); (void)fclose(h);

	h = fopen("idntbl.h", "w");
	(void)fprintf(h, "int dofold = %d;\n", dofold); saveidn(h);
	(void)fclose(h);
	return 0;
}
