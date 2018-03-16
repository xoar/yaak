#!/bin/sh
# $Id: makeinfo.sh,v 2.5 2004/06/22 12:35:22 profw Exp $
# Copyright 1994, The Regents of the University of Colorado

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

# EXEC (makeinfo.sh) (texinfo/makeinfo.exe) (:tnf) tnf_dir tnf_node
#   => (:tnf_dir) (:tnf_node);

ODIN_makeinfo=$1;shift; ODIN_tnf=$1;shift;
ODIN_dir=$1;shift; ODIN_node=$1;shift;
mkdir $ODIN_dir; touch $ODIN_node

if test ! -s $ODIN_tnf; then exit 0; fi

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -n -e '/@setfilename/s/@setfilename \(.*\)$/(\1)/p' $ODIN_tnf \
	> $ODIN_node

cd $ODIN_dir

$SED -e '/^@egfiles/s;\.;'"$ODIN_dir"';' $ODIN_tnf > TEXINFO

$ODIN_makeinfo TEXINFO 1>/dev/null 2>ERROR

if test -s ERROR
then
	$SED -e '1i\
(|'"$ODIN_tnf"'|line_err|
			s;^[^:]*:\([0-9]*\):;'"$ODIN_tnf"' \1 0;
			$a\
|)' ERROR > ../ERRORS
else
	rm TEXINFO ERROR
fi
