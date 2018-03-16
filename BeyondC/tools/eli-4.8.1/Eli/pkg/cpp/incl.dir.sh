#!/bin/sh
# $Id: incl.dir.sh,v 2.3 2002/05/08 15:00:50 waite Exp $
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

ODIN_CURDIR=$1;shift;
PKG=$1;shift; ODIN_atomic=$1;shift; ODIN_incl=$1;shift; ODIN_ignore=$1;shift;

# incl.dir(.null) Directly-included file names"* :
#	USER
#		: .atomic
#		+ incl
#		+ ignore

echo "$ODIN_CURDIR" > path
#echo "$ODINCACHE/PKGS" >> path

cat /dev/null > define

if test '' != "$ODIN_ignore"
then cat "$ODIN_ignore" > ignore
else echo '/usr/include' > ignore
fi

if test '' != "$ODIN_incl"
then derived="$ODIN_incl"
else derived=/dev/null
fi

("$ODINCACHE/PKGS/skeleton/get_incl.exe" path define ignore $derived \
	< "$ODIN_atomic" > incl.dir ) >ERROR 2>&1

if test -s ERROR
then $ODINCACHE/PKGS/skeleton/sed.exe 's;^\. ;'"$ODIN_atomic"' ;' ERROR >> ERRORS
else :
fi
