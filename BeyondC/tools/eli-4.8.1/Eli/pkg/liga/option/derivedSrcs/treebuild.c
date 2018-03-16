static char RCSid[] = "$Id: treebuild.c,v 2.1 2013/11/13 15:27:28 pfahler Exp $";
/* Build a tree using an Eli-generated scanner/parser */
/* Copyright 2013, The Regents of the University of Colorado */

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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "eliproto.h"
#include "pdl_gen.h"
#include "source.h"
#include "csm.h"
#include "clp.h"
#include "clpintf.h"
#ifdef MONITOR
#include "dapto.h"
#include "dapto_dapto.h"
#endif

extern void Zerteiler ELI_ARG((void));

void
#ifdef PROTO_OK
TREEBUILD(void)
#else
TREEBUILD();
#endif
{ CONST char *infilename;

  infilename = StringTable (GetClpValue (CLP_InputFile, 0));
  if (*infilename == '\0') initBuf("stdin", 0);
  else {
    int infile = open(infilename, 0);
    if (infile == -1) {
      ClpOpenError(infilename, strerror(errno));
      exit(2);
    }
    initBuf (infilename, infile);
#ifdef MONITOR
    _dapto_source_changed (infilename, 1, 1, 1, 1, 1);
#endif
  }
  Zerteiler();
}
