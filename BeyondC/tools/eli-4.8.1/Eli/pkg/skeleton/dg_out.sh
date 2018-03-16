#!/bin/sh
# $Id: dg_out.sh,v 2.4 2002/05/08 15:01:05 waite Exp $
# Copyright 1997, The Regents of the University of Colorado

# This file is part of the Eli translator construction system.

# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.

# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.

# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

# dg_out <
#    dg.lst "Derivation Graph listing"
#    dg.c "Derivation Graph tables (code)"
#    dg.tab "Derivation Graph tables (text)"
#    > "Derivation Graph tables"*
#		: dg_in

ln -s dg.c DG.c
ln -s dg.tab DRVGRF

("$ODINCACHE/PKGS/dg.exe" <`cat "$ODIN_dg_in"` >dg.lst) 1>ERROR 2>&1
if test $? -ne 0
then echo '. 0 0 Derivation graph compiler failed' >ERRORS
fi

if test -s ERROR
then
	echo '(|'"$ODIN_dg_in"'|line_err|' >ERRORS
	$ODINCACHE/PKGS/skeleton/sed.exe -n -e '/line/{
			s/\(.*\)line \([0-9]*\),/. \2 0 \1/p
			d
		}
		s/^/0 0 /p' ERROR >>ERRORS
	echo '|)' >>ERRORS
else :
fi
