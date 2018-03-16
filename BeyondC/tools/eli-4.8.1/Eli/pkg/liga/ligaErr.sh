#!/bin/sh
# $Id: ligaErr.sh,v 1.3 2003/01/07 08:27:30 peter Exp $
# Copyright 1997, The Regents of the University of Colorado

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

# EXEC (ligaErr.sh) (.) (+hookvalue) (:lido.cmpd :cpp) (:ligaBe)
#   => (:ligaErr);
#     :ligaErr 'Map line errors in LIGA output' => :line_err;

PKG=$1;shift; ODIN_HOOK=$1;shift; ODIN_newfile=$1;shift;

"$PKG/ligaErr.exe" "$ODIN_newfile" unmapped < "$ODIN_HOOK" \
	| $ODINCACHE/PKGS/skeleton/cat-n.exe \
	| sort -k 2,2 -k 3n,4 -k 1n,1 \
	| $ODINCACHE/PKGS/skeleton/line_err.exe \
	> ligaErr

if test -s unmapped
then cat unmapped >> ligaErr
else :
fi
