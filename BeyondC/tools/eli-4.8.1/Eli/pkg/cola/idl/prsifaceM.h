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

/* $Id: prsifaceM.h,v 1.5 1997/08/29 08:38:08 mjung Exp $ */
/* Class Attribute accessing macros */

#ifndef PRSIFACEM_H
#define PRSIFACEM_H

#define CMR_DT_indexOfEntrytype(AEntrytype) AEntrytype.IDLclassCommon->CMR_DT_index

/* Node Attribute  accessing macros */

#define EntriesOfRowtype(ARowtype) ARowtype->Entries
#define ErrsymbOfRowtype(ARowtype) ARowtype->Errsymb
#define ParsingTabOfabsparsertype(Aabsparsertype) Aabsparsertype->ParsingTab
#define IsDetermOfabsparsertype(Aabsparsertype) Aabsparsertype->IsDeterm
#define CMR_DT_indexOfaccept(Aaccept) Aaccept->CMR_DT_index
#define CMR_DT_indexOfreduce(Areduce) Areduce->CMR_DT_index
#define RuleOfreduce(Areduce) Areduce->Rule
#define CMR_DT_indexOfshift(Ashift) Ashift->CMR_DT_index
#define NextStateOfshift(Ashift) Ashift->NextState
#define CMR_DT_indexOfshiftred(Ashiftred) Ashiftred->CMR_DT_index
#define RuleOfshiftred(Ashiftred) Ashiftred->Rule

/* Widening Conversion macros */

extern Entrytype IDLtempEntrytype;
#define shiftToEntrytype(Ashift) \
	(IDLtempEntrytype.Vshift = Ashift, IDLtempEntrytype)
#define reduceToEntrytype(Areduce) \
	(IDLtempEntrytype.Vreduce = Areduce, IDLtempEntrytype)
#define shiftredToEntrytype(Ashiftred) \
	(IDLtempEntrytype.Vshiftred = Ashiftred, IDLtempEntrytype)
#define acceptToEntrytype(Aaccept) \
	(IDLtempEntrytype.Vaccept = Aaccept, IDLtempEntrytype)


/* Narrowing Conversion macros */

#define EntrytypeToshift(AEntrytype) \
	((typeof(AEntrytype)==Kshift) ? AEntrytype.Vshift :\
	(ConversionError("Entrytype","shift"), AEntrytype.Vshift))
#define EntrytypeToreduce(AEntrytype) \
	((typeof(AEntrytype)==Kreduce) ? AEntrytype.Vreduce :\
	(ConversionError("Entrytype","reduce"), AEntrytype.Vreduce))
#define EntrytypeToshiftred(AEntrytype) \
	((typeof(AEntrytype)==Kshiftred) ? AEntrytype.Vshiftred :\
	(ConversionError("Entrytype","shiftred"), AEntrytype.Vshiftred))
#define EntrytypeToaccept(AEntrytype) \
	((typeof(AEntrytype)==Kaccept) ? AEntrytype.Vaccept :\
	(ConversionError("Entrytype","accept"), AEntrytype.Vaccept))

#endif
