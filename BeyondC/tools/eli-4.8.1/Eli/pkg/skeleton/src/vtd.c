static char rcsid[]="$Id: vtd.c,v 2.2 2007/02/21 15:10:00 profw Exp $";
/* Copyright, 1991, The Regents of the University of Colorado */

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
#include <string.h>

int
main(argc,argv)
int argc; char *argv[];
/* Make a virtual target definition file from corresponding lines of two files
 *    On entry-
 *       argv[1]=name of the file containing "column 1" lines
 *       argv[2]=name of the file containing "column 2" lines
 *    On exit-
 *       standard output="two-column" material
 */
{
	char col1[BUFSIZ], col2[BUFSIZ];
	FILE *f, *g, *fopen();

	if (argc != 3) {
		(void)fprintf(stderr, "Usage %s file1 file2\n", argv[0]);
		return 1;
	}

	if ((f = fopen(argv[1], "r")) == NULL) {
		(void)fprintf(stderr, "Could not open file %s\n", argv[1]);
		return 1;
	}

	if ((g = fopen(argv[2], "r")) == NULL) {
		(void)fprintf(stderr, "Could not open file %s\n", argv[2]);
		return 1;
	}

	while (fgets(col1, BUFSIZ, f) != NULL) {
		if (fgets(col2, BUFSIZ, g) == NULL) {
			(void)fprintf(stderr, "%s: unexpected EOF\n", argv[2]);
			return 1;
		}
		col1[strlen(col1)-1] = '\0';
		(void)printf("%%%s == %s", col1, col2);
	}

	if (fgets(col2, BUFSIZ, g) != NULL) {
		(void)fprintf(stderr, "%s: unexpected EOF\n", argv[1]);
		return 1;
	}

	return 0;
}
