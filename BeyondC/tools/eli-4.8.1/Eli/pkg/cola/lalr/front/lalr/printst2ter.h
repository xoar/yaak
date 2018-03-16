/* 
 * $Id: printst2ter.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
 */

/* (C) Copyright 1997 University of Paderborn */

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

#ifndef __PRINTSTATE2TERMS_H__
#define __PRINTSTATE2TERMS_H__

#ifndef ARGS
#if defined (__cplusplus) || defined(__STDC__)
#define ARGS(args)      args
#else
#define ARGS(args)      ()
#endif
#endif

#include "comar.h"
#include "prsiface.h"

#define	MAXTERMINALS	5
#define FILENAME	"State2Terms.c"

extern	void    printstate2terms ARGS((absparsertype autom, p_comar cmr));

#endif
