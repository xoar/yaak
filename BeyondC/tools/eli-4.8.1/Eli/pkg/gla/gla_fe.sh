#!/bin/sh
# $Id: gla_fe.sh,v 2.6 2003/06/22 01:45:48 waite Exp $
# Copyright 1991, The Regents of the University of Colorado

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

#  EXEC (gla_fe.sh) (.) (:scan_spec :list :cpp)
#    NEEDS (gla_fe.exe) (gla.err)
#    => (:flex_spec) (:backend_data);

PKG=$1;shift; ODIN_glaspec=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e '/^#/s;.*;{&};' $ODIN_glaspec >INFILE

$PKG/gla_fe.exe INFILE 1>listing 2>ERROR

if test -s ERROR
then
	grep 'WARNING:' ERROR > WARN
	if test -s WARN
	then
		echo '(|'"$PKG/gla.err"'|std_err|' >> WARNINGS
		echo '(|'"$ODIN_glaspec"'|line_err|' >> WARNINGS
		$SED -e '/^  *(/d
			s/WARNING: //
			s/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' WARN \
			>> WARNINGS
		echo '|)' >> WARNINGS
		echo '|)' >> WARNINGS
	fi

	grep -v 'WARNING:' ERROR > ERR
	if test -s ERR
	then
		echo '(|'"$PKG/gla.err"'|std_err|' >> ERRORS
		echo '(|'"$ODIN_glaspec"'|line_err|' >> ERRORS
		$SED -e '/^  *(/d
			s/ERROR: //
			s/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' ERR \
			>> ERRORS
		echo '|)' >> ERRORS
		echo '|)' >> ERRORS
	fi
fi

if test -s xflex.l && test -s backend.data
then
	cp xflex.l flex_spec
	cp backend.data backend_data
else
        echo '(|'"$PKG/gla.err"'|std_err|' >> ERRORS
        echo '(|'"$ODIN_glaspec"'|line_err|' >> ERRORS
	$SED -e 's/^/. 0 0 /' listing >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
fi
