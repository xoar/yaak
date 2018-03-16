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

#include "global.h"

static char rcsid[]="$Id: basics.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

#define MarkRoutine(name, type) void name(t) type t; {}

	/* representations for strings (one) */
MarkRoutine(MString, String)
MarkRoutine(UString, String)
	/* representations for booleans (one) */
MarkRoutine(MBoolean, Boolean)
MarkRoutine(UBoolean, Boolean)
	/* representations for integers */
MarkRoutine(Mint, int)
MarkRoutine(Uint, int)
MarkRoutine(Mchar, char)
MarkRoutine(Uchar, char)
MarkRoutine(Mshort, short)
MarkRoutine(Ushort, short)
MarkRoutine(Mlong, long)
MarkRoutine(Ulong, long)
MarkRoutine(Mu_int, u_int)
MarkRoutine(Uu_int, u_int)
MarkRoutine(Mu_char, u_char)
MarkRoutine(Uu_char, u_char)
MarkRoutine(Mu_short, u_short)
MarkRoutine(Uu_short, u_short)
MarkRoutine(Mu_long, u_long)
MarkRoutine(Uu_long, u_long)
	/* representations for rationals */
MarkRoutine(Mfloat, float)
MarkRoutine(Ufloat, float)
MarkRoutine(Mdouble, double)
MarkRoutine(Udouble, double)
