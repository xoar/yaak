#!/bin/sh
# $Id: filter.sh,v 2.4 2006/06/29 10:49:02 pfahler Exp $
# Copyright 1996, The Regents of the University of Colorado

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

reqfiles=$1;shift; genlabels=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e 's/^/L	L	/' $genlabels > labeltmp
$SED -e 's/^/R	/' $reqfiles > reqtemp

cat reqtemp labeltmp | \
	sort -k 3 | \
	uniq -u -f 2 | \
	$SED \
		-e '/^L	/d' \
		-e 's/R	\([^	]*\)	.*$/\1/' \
		> framespecs

exit 0
