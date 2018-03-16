#!/bin/sh
# $Id: fwErr.sh,v 2.8 2002/05/08 15:00:53 waite Exp $
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

# EXEC (fwErr.sh) (.) (+hookvalue) (:fwMap) (:fwGen :direlms :ls)
#     (:fwGen :labels)
#   NEEDS (fw_errors.exe) ($ODINCACHE/PKGS/skeleton/sed.exe)
#         ($ODINCACHE/PKGS/skeleton/err_map.exe)
#   => (:fwErr);
#
# :fwErr 'Map line errors in FunnelWeb output' => :line_err;

PKG=$1;shift; ODIN_HOOK=$1;shift; ODIN_fwMap=$1;shift; ODIN_fwGen=$1;shift;
ODIN_labels=$1;shift;

"$ODINCACHE/PKGS/skeleton/err_map.exe" "$ODIN_labels" "$ODIN_fwGen" \
		"$ODIN_fwMap" \
	| $ODINCACHE/PKGS/skeleton/sed.exe \
		-e 's/^\([^ ]* [^ ]* [^ ]* [^ ]* [^ ]*\) \(.*\)/\2 \1/' \
	> map

$PKG/fw_errors.exe map mapped unmapped < $ODIN_HOOK

cat mapped unmapped > fwErr

