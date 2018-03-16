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
static char RCSid[] = "$Id: idn.c,v 4.2 1999/07/08 16:53:28 uwe Exp $";
/* Copyright 1989, The Regents of the University of Colorado
 * Permission is granted to use any portion of this file for any purpose,
 * commercial or otherwise, provided that this notice remains unchanged.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "err.h"
#include "idn.h"
#include "csm.h"


	/* Types local to the identifier table */

typedef struct chainelt {	/* Lookup mechanism */
	struct chainelt *nxt;	   /* Chain link */
	int len;		   /* Length */
	int typ;		   /* Terminal */
	int dat;		   /* Corresponding identifier */
} CHAIN;

#include "idntbl.h"


#ifndef NOPRINT

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
prtidnv(FILE *d, int i)
#else
void
prtidnv(d, i)
FILE *d; int i;
#endif
/* Print an identifier
 *    On exit-
 *       The identifier encoded by i has been added to the current
 *          line of d.
 ***/
{
	fprintf(d, " \"");
	(void) prtstcon(d, strng[i]);
	(void) putc('"', d);
}

#ifdef SAVE
/**/
#if defined(__cplusplus) || defined(__STDC__)
void
savchain(FILE *d, CHAIN *p, int k, int i)
#else
void
savchain(d, p, k, i)
FILE *d; CHAIN *p; int k, i;
#endif
/* Print a chain of hash entries
 *    On entry-
 *       the chain to be printed is attached to hash[k]
 *       i is the index of the first block of the chain pointed to by p
 *    On exit-
 *       The chain pointed to by p has been printed on file d
 **/
{
	if (p != (CHAIN *)0) {
		savchain(d, p->nxt, k, i+1);
		fprintf(d, "static CHAIN h%dl%d = {", k, i);
		if (p->nxt == (CHAIN *)0) fprintf(d, "NULL");
		else fprintf(d, "&h%dl%d", k, i+1);
		fprintf(d, ",%d,%d,%d};\n", p->len, p->typ, p->dat);
	}
}

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
saveidn(FILE *d)
#else
void
saveidn(d)
FILE *d;
#endif
/* Save the current identifier table state
 *    On exit-
 *       File d is a symbolic encoding of the current state, suitable
 *          for inclusion in the identifier table module
 ***/
{
	int k;

	fprintf(d, "#define HTSIZE %d\n", HTSIZE);

	for (k = 0; k < HTSIZE; k++) savchain(d, hash[k], k, 0);

	fprintf(d, "\nstatic CHAIN *hash[HTSIZE]={\n");
	for (k = 0; k < HTSIZE; k++) {
		if (hash[k] == (CHAIN *)0) fprintf(d, "\tNULL");
		else fprintf(d, "\t&h%dl0", k);
		if (k < HTSIZE-1) fprintf(d, ",\n");
	}
	fprintf(d, "};\n\n");
}
#endif

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
dmpidn(FILE *d)
#else
void
dmpidn(d)
FILE *d;
#endif
/* Dump the identifier table
 *    On exit-
 *       The entire identifier table has been written to d
 ***/
{
	int i, j;
	CHAIN *p;

	fprintf(d,"\n Identifier table contents-\n");
	j = 0;
	for (i = 0; i < HTSIZE; i++) {
		p = hash[i];
		if (p) {
			if (j == i-1)
				fprintf(d,"   Bin %d\n",j);
			else if (j < i)
				fprintf(d,"   Bins %d-%d empty\n",j,i-1);
			j = i+1;
			fprintf(d,"   Bin %d\n",i);
			do {
				fprintf(d, "Id=%d, Term=%d, Str=%d:\"",
					p->dat, p->typ, p->len);
				(void) prtstcon(d, strng[p->dat]);
				fprintf(d, "\"\n");
				p = p->nxt;
			} while (p);
		}
	}
	if (j == HTSIZE-1)
		fprintf(d,"   Bin %d\n",j);
	else if (j < HTSIZE-1)
		fprintf(d,"   Bins %d-%d empty\n", j, HTSIZE-1);
	(void)putc('\n',d);
}

#endif

/***/
#if defined(__cplusplus) || defined(__STDC__)
void
mkidn(char *c, int l, int *t, int *s)
#else
void
mkidn(c, l, t, s)
char *c; int l, *t; int *s;
#endif
/* Obtain the internal coding of an identifier or keyword
 *    On entry-
 *       c points to the identifier or keyword
 *       l=length of the identifier or keyword
 *       t points to a location containing the initial terminal code
 *    If the identifier or keyword has appeared previously then on exit-
 *       t has been set to the terminal code given on its first appearance
 *       s has been set to the internal coding set on its first appearance
 *    Otherwise on exit-
 *       t remains unchanged
 *       s has been set to a new internal coding
 ***/
{
	register CHAIN *ent;
	register int test;
#ifndef NOFOLD
	char fold[BUFSIZ];

	if (dofold) {
		register char x;
		register char *p = fold;
		register char *q = c;
		register int i = l;

		while (i--) *p++ = islower(x = toascii(*q++))?toupper(x):x;
		c = fold;
	}
#endif

        /* check for null string */
        if (l == 0) {
                *s = 0;
                return;
        }
        /* check for illegal values */
        if (l < 0) {
                message(DEADLY, "Negative length in mkidn", 0, &curpos);
        }
        /* string length l >= 1 */
	test = 1;
	if (l == 1) {
		ent = (CHAIN *) &hash[*c];
		if (ent->nxt != (CHAIN *)0) {
			ent = ent->nxt;
			test = 1 - ent->len;
		}
	} else {
		{
			register char *cr = c;
			register int key = 0;
			register int lr = l;

			do key += *cr++; while (--lr);
			ent = (CHAIN *) &hash[key & 0xFF];
		}

		do {
			if (ent->nxt == (CHAIN *)0) break;
			ent = ent->nxt;
			if ((test = l - ent->len) == 0) {
				register char *cr = c;
				register char *p = strng[ent->dat];
				register int lr = l;

				do ; while (*cr++ == *p++ && --lr);
				test = cr[-1] - p[-1];
			}
		} while (test > 0);
	}
	if (test != 0) {
		CHAIN *temp;

		if ((temp = (CHAIN *) malloc(sizeof(CHAIN))) == (CHAIN *)0) {
			message(DEADLY, "Memory overflow in mkidn", 0, &curpos);
		}
		temp->nxt = ent->nxt; ent->nxt = temp;
		if (test < 0) {
			temp->len = ent->len;
			temp->typ = ent->typ;
			temp->dat = ent->dat;
		} else ent = temp;
		ent->len = l; ent->typ = *t; ent->dat = stostr(c,l);
	} else {
	  if (ent->typ != 0) *t = ent->typ;
	  if (c == CsmStrPtr) obstack_free(Csm_obstk, c);
	}
	*s = ent->dat;
}
