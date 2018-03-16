#!/bin/sh
# $Id: ligaMe.sh,v 2.8 1999/04/29 09:54:20 cogito Exp $
# Copyright, 1993, The University of Paderborn

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

PKG=$1;shift; ODIN_ligaFe=$1;shift; ODIN_exp_option=$1;shift; 
ODIN_ord_option=$1;shift; ODIN_optUoption=$1;shift; ODIN_e66=$1;shift; 
ODIN_e67=$1;shift; ODIN_RunGorto=$1;shift;
 
#EXEC (ligaMe.sh) (.) (:ligaFe) (:exp_option) (:ord_option) (:optUoption) 
#                     (:lido.cmpd :cpp) (:lido.cmpd :cpp_tab) (+RunGorto)
#  => (:MeIdl) (:MeInfo) (:MeBottomUp);
#    :MeIdl 'IDL interface between Middle and Backend' => :FILE;
#    :MeInfo 'Protocol file of LIGAs Middle pass'? => :FILE;
#    :MeBottomUp 'Rules with BottomUp constraints' => :FILE;

cp /dev/null MeBottomUp

LIGAME="$ODINCACHE/PKGS/liga/ligaMe.exe \
		-i $ODIN_ligaFe \
		-c $ODIN_exp_option \
		-d $ODIN_ord_option \
		-t optEoption \
		-e $ODIN_optUoption optEoption \
		-l $ODIN_e67 \
		-o MeIdl \
		-p MeInfo \
		-b MeBottomUp"

if test '' != "$ODIN_RunGorto"
then	$LIGAME -g > /dev/null 2> ERROR
else	$LIGAME    > /dev/null 2> ERROR
fi

if test -s core
then
        echo '".", line 0:0 DEADLY: LIGA Middle pass failed' >> ERROR
fi

# delete Notes, put Warnings into WARN, others into ERRS
if test -s ERROR
then
   $ODINCACHE/PKGS/skeleton/sed.exe -n -f "$ODINCACHE/PKGS/liga/mess_sort" ERROR
fi

if test -s ERRS
then
    echo '(|'"$ODINCACHE/PKGS/liga/Info/middle.err"'|std_err|' > ERRORS
    echo '(|'"$ODIN_e66"'|line_err|' >> ERRORS
    $ODINCACHE/PKGS/skeleton/sed.exe 's@^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)@'"$ODIN_e66"' \2 \3@'\
	ERRS >> ERRORS
    echo '|)' >> ERRORS
    echo '|)' >> ERRORS
fi

if test -s WARN
then
    echo '(|'"$ODINCACHE/PKGS/liga/Info/middle.err"'|std_err|' > WARNINGS
    echo '(|'"$ODIN_e66"'|line_err|' >> WARNINGS
    $ODINCACHE/PKGS/skeleton/sed.exe 's@^"\([^"]*\)",  line \([0-9]*\):\([0-9]*\)@'"$ODIN_e66"' \2 \3@'\
	WARN >> WARNINGS
    echo '|)' >> WARNINGS
    echo '|)' >> WARNINGS
fi

exit 0
