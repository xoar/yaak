#!/bin/sh
# $Id: etaErr.sh,v 1.2 2008/03/01 18:59:06 profw Exp $
# Copyright 1992, The Regents of the University of Colorado
# Copyright 1995, Anthony M. Sloane
# Copyright 1997, University of Paderborn
#
# This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

# EXEC (fwErr.sh) (.) (+hookvalue) (:fwMap) (:fwGen :direlms :ls)
#     (:fwGen :labels)
#   => (:fwErr);
#
# :Err 'Map line errors in FunnelWeb output' => :line_err;

PKG=$1;shift; ODIN_HOOK=$1;shift; ODIN_etaMap=$1;shift; ODIN_etaGen=$1;shift;
ODIN_labels=$1;shift;

"$ODINCACHE/PKGS/skeleton/err_map.exe" "$ODIN_labels" "$ODIN_etaGen" \
		"$ODIN_etaMap" \
	| $ODINCACHE/PKGS/skeleton/sed.exe \
		-e 's/^\([^ ]* [^ ]* [^ ]* [^ ]* [^ ]*\) \(.*\)/\2 \1/' \
	> map

$ODINCACHE/PKGS/fw/fw_errors.exe map mapped etaErr < $ODIN_HOOK

if test -s mapped
then
	cat mapped \
		| $ODINCACHE/PKGS/skeleton/cat-n.exe \
		| sort -k 2,2 -k 3n,4 -k 1n,1 \
		| $ODINCACHE/PKGS/skeleton/line_err.exe \
		>> etaErr
fi
