#!/bin/sh
# $Id: err_map.sh,v 2.8 2006/06/29 10:49:02 pfahler Exp $
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

# EXEC (err_map.sh) (.) (+hookvalue) (:c_srcs :list :ls)
#      (:c_srcs :list :labels) (:c_srcs)
#   NEEDS (err_map.exe) (cat-n.exe) (line_err.exe)
#   => (:err_map);

PKG=$1;shift; ODIN_HOOK=$1;shift; ODIN_compound=$1;shift; ODIN_labels=$1;shift;

$PKG/err_map.exe $ODIN_labels $ODIN_compound $ODIN_HOOK \
	| $PKG/cat-n.exe \
	| sort -k 2,2 -k 3n,4 -k 1n,1 \
	| $PKG/line_err.exe \
	>err_map
