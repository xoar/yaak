#!/bin/sh
# $Id: instSpec.sh,v 2.2 1997/08/28 18:26:41 waite Exp $
# Generic module specs file
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
PKG=$1;shift; ODIN_gnrc=$1;shift;

#instSpec(.none) 'Specifications associated with the generic module'* :
#	USER
#		: gnrc

file=`expr "$ODIN_gnrc" : '\(.*\)\.gnrc'`
if test -f $file.specs
then echo "$file.specs" >instSpec
else cp /dev/null instSpec
fi
