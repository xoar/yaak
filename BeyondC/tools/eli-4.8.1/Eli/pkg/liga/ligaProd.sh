#! /bin/sh
# $Id: ligaProd.sh,v 2.5 2002/05/27 07:49:41 peter Exp peter $
# Copyright (c) 1993, The Regents of the University of Colorado

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

PKG=$1;shift; ODIN_e76=$1;shift;

# ligaProd 'Abstract rules extracted in LIDO notation'* :
# 	USER
# 		: (:lido.cmpd :cpp)

"$ODINCACHE/PKGS/liga/ligaProd.exe" "$ODIN_e76" 1> ERROR 2>&1
mv ligaprod mvtmp
mv mvtmp ligaProd

if test -s core
then
        echo '".", line 0:0 DEADLY: Tool ligaProd failed' >> ERROR
fi

if test -s ERROR
then
        $ODINCACHE/PKGS/skeleton/sed.exe -n -f "$ODINCACHE/PKGS/liga/mess_sort" ERROR
fi

if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/ligaProd.err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_e76"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
fi

if test -s WARN
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/ligaProd.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e76"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		WARN >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
else :
fi
