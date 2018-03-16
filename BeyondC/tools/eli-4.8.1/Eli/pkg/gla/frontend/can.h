/* "$Id: can.h,v 1.3 1997/09/11 19:38:37 waite Exp $" */
/* Copyright 1992, The Regents of the University of Colorado */

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

/* Canned description module interface */

typedef struct {		/* Canned description */
	char *Lname;		   /* Name of the canned description */
	char *Lpattern;		   /* Regular expression */
	char *Lscanner;		   /* Auxiliary scanner (NULL if none) */
	char *Lprocessor;	   /* Processor (NULL if none) */
} CannedDescr;

typedef CannedDescr *CannedDescrPtr;

extern CannedDescr *NullDescr;

/***/
#if defined(__STDC__) || defined(__cplusplus)
extern CannedDescrPtr libLookup(char *s);
#else
extern CannedDescrPtr libLookup();
#endif

/* Obtain an index to a canned description
 *    On entry-
 *       s names the canned description desired
 *    If s names a valid canned description then on exit-
 *       libLookup is the address of the canned description
 *    Otherwise on exit-
 *       libLookup is NullDescr
 ***/
