#!/bin/sh
# $Id: extract.sh,v 2.2 1997/08/28 18:27:25 waite Exp $
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

ODIN_RUNDIR=`pwd`;
PKG=$1;shift; ODIN_labels=$1;shift; ODIN_names=$1;shift; ODIN_typekey=$1;shift;

#extract(.none) "Elements of a compound file that have a specified type" :
#	USER
#		: labels
#		: names
#		+ typekey

"$ODINCACHE/PKGS/skeleton/type_sel.exe" \
		'extract' \
		"$ODIN_typekey" \
		"$ODIN_labels" \
		"$ODIN_names" \
	> extract.l
