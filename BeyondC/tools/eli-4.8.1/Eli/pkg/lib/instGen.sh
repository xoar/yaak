#!/bin/sh
# $Id: instGen.sh,v 2.5 2002/05/08 15:00:58 waite Exp $
# Generic module files
# Copyright 1992, University of Paderborn

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
PKG=$1;shift; ODIN_gnrc=$1;shift; ODIN_instance=$1;shift; ODIN_referto=$1;shift;  mkdir instGen;

#instGen[.none] 'Files generated from generic specification'* :
#	USER
#		: gnrc
#		+ instance
#		+ referto

cd ./instGen

if test '' != "$ODIN_instance"; then instance="$ODIN_instance"; fi
space=`expr "$instance" : '.*\( \).'`
if test "$space" = ' '
then
	echo "Illegal space in +instance='$instance'" > $ODIN_RUNDIR/ERRORS
	exit 0
fi

if test '' != "$ODIN_referto"; then referto="$ODIN_referto"; fi

sh "$ODIN_gnrc" $ODINCACHE/PKGS/skeleton/sed.exe "$instance" "$referto" \
    > $ODIN_RUNDIR/ERROR

if test -s $ODIN_RUNDIR/ERROR
then
    mv $ODIN_RUNDIR/ERROR $ODIN_RUNDIR/ERRORS
fi
