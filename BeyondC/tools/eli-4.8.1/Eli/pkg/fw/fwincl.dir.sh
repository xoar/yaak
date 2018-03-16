#!/bin/sh
# $Id: fwincl.dir.sh,v 2.5 1999/01/10 00:59:19 tony Exp $
# Copyright 1992, The Regents of the University of Colorado
# Copyright 1995-1999, Anthony M. Sloane

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

# EXEC (fwincl.dir.sh) (:FILE :dir)@ (.) (:FILE) (+incl) (+ignore)
#  NEEDS (fw_incl.exe)
#  => (:fwincl.dir);
#
# :fwincl.dir 'Directly included FunnelWeb file names' => :FILE;

ODIN_CURDIR=`echo $1`; shift;
PKG=$1;shift; ODIN_atomic=$1;shift; ODIN_incl=$1;shift; ODIN_ignore=$1;shift;

echo "$ODIN_CURDIR" > path

cat /dev/null > define

if test '' != "$ODIN_ignore"
then echo "$ODIN_ignore" > ignore
else echo '/usr/include' > ignore
fi

if test '' != "$ODIN_incl"
then derived="$ODIN_incl"
else derived=/dev/null
fi

("$PKG/fw_incl.exe" path define ignore $derived \
	< "$ODIN_atomic" > fwincl.dir ) > ERRORS 2>&1 || \
	echo 'Tool Failed' >> ERRORS
