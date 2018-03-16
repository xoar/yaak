#!/bin/sh
# $Id: cppErr.sh,v 2.8 2013/11/10 00:02:57 profw Exp $
# Copyright 1997, The Regents of the University of Colorado

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

# EXEC (cppErr.sh) (+hookvalue) (:cpp_tab) cppErr
#   => (:cppErr);

ODIN_HOOK=$1;shift; ODIN_cpp_tab=$1;shift; ODIN_out=$1;shift;

$ODINCACHE/PKGS/skeleton/sed.exe -e '/^$/d
/^[0-9][0-9]* /!s/^[^ ]* //' "$ODIN_HOOK" \
	| sort -k 1n,1 -k 2n,2 \
	| "$ODINCACHE/PKGS/skeleton/map_errors.exe" "$ODIN_cpp_tab" \
	| "$ODINCACHE/PKGS/skeleton/cat-n.exe" \
	| sort -k 2,2 -k3n,3 -k 4n,4 -k 1,1 \
	| "$ODINCACHE/PKGS/skeleton/line_err.exe" \
	> $ODIN_out


