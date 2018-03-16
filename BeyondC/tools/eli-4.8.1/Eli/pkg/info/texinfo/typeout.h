#ifndef TYPEOUT_H
#define TYPEOUT_H
/* $Id: typeout.h,v 1.4 1998/02/11 16:43:36 waite Exp $ */
/* Message manager interface */
/* Copyright 1998, The Regents of the University of Colorado */

#include "eliproto.h"
extern void typeout ELI_ARG((char *s, int ret));
/* Type out a string to the terminal window
 *    On entry-
 *       s=string to be typed out (must end with \n)
 *       ret=1 if typeout should return if whole string fits on one page
 *	     0 otherwise.
 ***/

#endif
