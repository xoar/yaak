#!/bin/sh
# $Id: ligaOption.sh,v 2.8 2008/03/03 09:18:03 peter Exp $
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

PKG=$1;shift; ODIN_e65=$1;shift; ODIN_ExpI=$1;shift; ODIN_OptimI=$1;shift;
ODIN_OrdI=$1; shift

#ligaOption <
#   exp_option 'options for LIGA expand and LIGA replincl'
#   ord_option  'options for LIGA order'*
#   optUoption  'options for LIGA optim before expand'*
#   back_option 'options for LIGA backend'*
#   > 'LIGA control language processor'* :
#        USER
#		: (:ctl.cmpd :cpp)
#               + ExpI
#               + OptimI

cat "$ODIN_e65" > input

if test '' != "$ODIN_ExpI"
then	echo 'EXPAND : INFO;' >> input
fi

if test '' != "$ODIN_OptimI"
then    echo 'OPTIM : INFO;' >> input
fi

if test '' != "$ODIN_OrdI"
then    echo 'ORDER: GRAPH DIRECT_RULE;' >> input
       echo 'ORDER: GRAPH VISIT_SEQUENCE;' >> input
fi

"$ODINCACHE/PKGS/liga/ligaOption.exe" \
        input \
        exp_option \
        ord_option \
        optUoption \
        back_option 1> ERROR 2>&1

if test -s core
then
        echo '".", line 0:0 DEADLY: Tool LIGA OPTION failed' >> ERROR
fi

if test -s ERROR
then
        $ODINCACHE/PKGS/skeleton/sed.exe -n -f "$ODINCACHE/PKGS/liga/mess_sort" ERROR
fi

if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/option.err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_e65"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
fi

if test -s WARN
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/option.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e65"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		WARN >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
fi

exit 0
