/* $Id: csmtbl.h,v 3.5 1999/03/11 15:18:45 mjung Exp $ */
/* Copyright 1989, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

	/* Character string data storage */
	/* This is an initialized obstack */

static struct {char *l; void *p; char c[1];} csm_data = {
  csm_data.c+1,
  0,
  ""
};

struct obstack csm_obstack =
  obstack_known_chunk(&csm_data, &(csm_data.c[1]), &(csm_data.c[1]),
    &(csm_data.c[1]), 4096, 1);


	/* Index data storage */
	/* This is an initialized obstack */

static struct {char **l; void *p; char *c[1];} csm_indx = {
  &(csm_indx.c[1]),
  0,
  {csm_data.c}
};

struct csmalign {char ___x; char *___d;};
static struct obstack csm_indx_obstk =
  obstack_known_chunk(&csm_indx, &(csm_indx.c[0]), &(csm_indx.c[1]),
    &(csm_indx.c[1]), 4096,
    ((PTR_INT_TYPE) ((char *) &((struct csmalign *) 0)->___d - (char *) 0)));

char **strng = csm_indx.c;		/* Pointers to the stored strings */
int numstr = 1;				/* Number of strings stored */
