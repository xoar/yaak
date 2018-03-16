#! /bin/sh
# $Id: SymToMap.sh,v 2.3 2002/05/08 15:01:01 waite Exp $
# Copyright 1994, The Regents of the University of Colorado

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

ODIN_RUNDIR=`pwd`;
PKG=$1;shift; ODIN_e131=$1;shift;

# SymToMap 'Make a map file from a sym file'* :
# 	USER
# 		: (:sym.cmpd :cpp)

if test -s "$ODIN_e131"
then
	echo 'MAPSYM' > SymToMap
	$ODINCACHE/PKGS/skeleton/sed.exe -e \
          's/^# /#line /' "$ODIN_e131" >> SymToMap
else
	cat /dev/null > SymToMap
fi

exit 0
