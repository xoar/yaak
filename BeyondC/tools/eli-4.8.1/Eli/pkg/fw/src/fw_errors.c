/*
 * $Id: fw_errors.c,v 1.15 2013/05/20 02:49:57 profw Exp $
 * Assign errors to their real locations.
 */

/* Copyright, 1992-1997, The Regents of the University of Colorado */
 
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

/*
 * Input is two streams.  First is a list of errors in the standard format
 * on stdin:
 *	filename line col message...
 * Second is a list of mapping lines:
 *      fromfile fromline fromcol fromind tofile tosline toscol toeline toecol
 * Tosline and toscol give the start of the region and toeline and
 * toecol give the first character after the region.
 *
 * Output on standard output is a list of errors in standard format based on
 * the input errors where every reference to a line and col in a tofile has
 * been mapped to the corresponding line and col in a fromfile.  Errors that
 * do not reference a part of any tofile are left unchanged.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map_entry *map;
struct map_entry {
	char *fromfile;
	int fromline, fromcol, fromind;
	char *tofile;
	int tosline, toscol, toeline, toecol;
	map next;
};

/* The map entries */
map entries;

/* The current error */
char errfile[BUFSIZ], errmsg[BUFSIZ];
int errline, errcol;

/* The mapping file */
FILE *mapfil;

/* The output files */
FILE *fmapped;
FILE *funmapped;

/*
 * map_error
 */

void map_error (lineno, line)
int lineno;
char *line;
{
	fprintf (stderr, "fw_errors: bad map line %d: %s", lineno, line);
	exit (1);
}

/*
 * read_map_entries
 */

void read_map_entries ()
{
	char line [BUFSIZ], buf [BUFSIZ], *cp;
	int count, eof;
	map entry;

	entries = (map) 0;
	for (count = 1; ; count++) {
		if (fgets (line, BUFSIZ, mapfil) == NULL)
			break;
		if ((entry = (map) malloc (sizeof (*entry))) == (map) NULL) {
			fprintf (stderr, "fw_errors: can't malloc map entry\n");
			exit (1);
		}
		/* Overkill on memory usage here */
		if ((entry->fromfile = (char *) malloc (strlen (line))) ==
				NULL) {
			fprintf (stderr, "fw_errors: can't malloc fromfile\n");
			exit (1);
		}
		if ((entry->tofile = (char *) malloc (strlen (line))) ==
				NULL) {
			fprintf (stderr, "fw_errors: can't malloc tofile\n");
			exit (1);
		}
		if (sscanf (line, "%s %d %d %d %s %d %d %d %d\n",
			    entry->fromfile, &entry->fromline, &entry->fromcol,
			    &entry->fromind,
			    entry->tofile, &entry->tosline, &entry->toscol,
			    &entry->toeline, &entry->toecol) != 9)
			map_error (count, line);
		entry->next = entries;
		entries = entry;
	}
}

/*
 * in_range
 */

int in_range (entry)
map entry;
{			
        if (strcmp (entry->tofile, errfile) != 0)
	        return 0;
	if (errline == entry->tosline) {
	        if (errcol == 0)
		        return 1;
		if (errline == entry->toeline)
		        return ((errcol >= entry->toscol) &&
				(errcol <= entry->toecol));
	        return (errcol >= entry->toscol);
        }
	if (errline == entry->toeline)
	        return (errcol <= entry->toecol);
	return ((errline > entry->tosline) && (errline < entry->toeline));
}

/*
 * check_error_entry
 */

int check_error_entry (entryp)
map *entryp;
{
	int ret;
	map entry;

	/* Read the next error */
	ret = fscanf (stdin, "%s %d %d", errfile, &errline, &errcol);
	if (ret == EOF)
		return 1;
	fgets (errmsg, BUFSIZ, stdin);
	
	/* See if it's mappable */
	for (entry = entries; entry != (map) 0; entry = entry->next)
		if (in_range (entry)) {
			*entryp = entry;
			return 0;
		}
	*entryp = (map) 0;
	return 0;
}

/*
 * output_error
 */

void output_error (output, filename, line, col, msg)
FILE *output;
char *filename, *msg;
int line, col;
{
	fprintf (output, "%s %d %d%s", filename, line, col, msg);
}

/*
 * output_mapped_error
 */

void output_mapped_error (entry)
map entry;
{
	output_error (fmapped,
		      entry->fromfile, 
		      entry->fromline + (errline - entry->tosline),
		      errcol == 0 ?
			      0 :
			      errcol + (errline == entry->tosline ?
					entry->fromcol - entry->toscol :
					-entry->fromind),
		      errmsg);
}

/*
 * main
 */

int main (argc, argv)
int argc;
char *argv[];
{
	int eof;
	map entry;

	if (argc != 4) {
		fprintf (stderr, "usage: fw_errors mapfile mapped_errors unmapped_errors<errfile\n");
		exit (1);
	}

	/* Open the map file */
	if ((mapfil = fopen (argv[1], "r")) == (FILE *) NULL) {
		fprintf (stderr, "fw_errors: can't read '%s'\n",
			 argv[1]);
		exit (1);
	}

	/* Open the output file for mapped errors */
	if ((fmapped = fopen (argv[2], "w")) == (FILE *) NULL) {
	  fprintf (stderr, "fw_errors: can't open output file '%s'\n",
		   argv[2]);
	  exit (1);
	}

	/* Open the output file for unmapped errors */
	if ((funmapped = fopen (argv[3], "w")) == (FILE *) NULL) {
	  fprintf (stderr, "fw_errors: can't open output file '%s'\n",
		   argv[3]);
	  exit (1);
	}

	/* First read the map */
	read_map_entries ();

	/* Loop reading errors and mapping them */
	for (;;) {
		eof = check_error_entry (&entry);
		if (eof)
			break;
		if (entry) {
			/* Output the mapped error */
			output_mapped_error (entry);
		} else {
			/* Output the error unchanged */
			output_error (funmapped, errfile, errline,
				      errcol, errmsg);
		}
	}

	/* Close the map file */
	fclose (mapfil);

	/* Close the output files */
	fclose (fmapped);
	fclose (funmapped);

	exit (0);
}

 
