#! /bin/sh
# $Id: fwSel.sh,v 2.5 2002/05/08 15:00:53 waite Exp $
# Copyright 1997-1998, The Regents of the University of Colorado

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

# EXEC (fwSel.sh) (:fw.cmpd :map=:fwNop :cat) (:fwAll :pasted)
#   NEEDS ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:fwSel);

ODIN_nop=$1;shift; ODIN_pasted=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e 's;.*;/	&$/d;' $ODIN_nop > script
$SED -f script $ODIN_pasted \
	| $SED -e 's/	.*//' \
	> fwSel
