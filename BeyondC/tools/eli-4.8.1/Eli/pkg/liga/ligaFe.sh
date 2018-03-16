#!/bin/sh
# $Id: ligaFe.sh,v 2.5 1997/08/29 08:13:57 peter Exp $
# Copyright, 1990, The University of Paderborn

# This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  

PKG=$1;shift; ODIN_e64=$1;shift;
 
#ligaFe 'LIGA frontend: LIDO analysis'*:
#        USER
#                : (:lido.cmpd :cpp)

"$ODINCACHE/PKGS/liga/ligaFe.exe" "$ODIN_e64" 1> ERROR 2>&1
mv liga.out ligaFe

if test -s core
then
        echo '".", line 0:0 DEADLY: LIGA Frontend failed' >> ERROR
fi

if test -s ERROR
then
	$ODINCACHE/PKGS/skeleton/sed.exe -n -f "$ODINCACHE/PKGS/liga/mess_sort" ERROR
fi

if test -s WARN
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/front.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e64"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		WARN >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
fi

if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/front.err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_e64"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
else :
fi
