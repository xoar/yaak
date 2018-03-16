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
/* $Id: visit.h,v 1.2 1997/08/29 09:16:01 peter Exp $ */
#ifndef VISIT_H
#define VISIT_H

#include "Types.h"

extern void visitsequence();
extern void rulevisitsequence(); /* for gorto */
extern void write_dataStruct();
extern VSPTR createcondition(); /* for initdp.c */
extern void VSSetDepend (/* VSPTR vselem; SLNODE *symptr; int attrpos */);

#endif
