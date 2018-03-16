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
/* $Id: OutStr.h,v 4.1 1997/08/29 09:02:13 peter Exp $ */
/* Copyright, 1992, AG-Kastens, University Of Paderborn */

extern	void	C_outstr(/* FILE *fs; char *s; */);
extern	void	C_outchar(/* FILE *fs; char *s; */);
extern	void	P_outstr(/* FILE *fs; char *s; */);
extern	void	outstr(/* FILE *fs; char *s; */);
