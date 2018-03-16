#!/bin/sh
# $Id: tex_input.sh,v 2.8 2004/08/20 13:19:59 profw Exp $
# Copyright 2004, The Regents of the University of Colorado

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

# EXEC (tex_input.sh) (:tnf) (+single)
#   => (:tex_input);

ODIN_tnf=$1;shift; ODIN_single=$1;shift;

touch script

if test '' != "$ODIN_single"
then
  echo '/^@setchapternewpage/s/odd/on/
        /^@headings/s/double/single/
        /^@titlepage/,/^@end titlepage/s/^\@page/@comment/' >> script
elif test "`$ODINCACHE/PKGS/skeleton/sed.exe -n -e '/^@titlepage/,/^@end titlepage/s/^@page/page/p' $ODIN_tnf`" = ''
then
  echo '/^@end titlepage/i\
@page' >> script
fi

if grep '^@contents' $ODIN_tnf > /dev/null
then
  echo '/^@contents/d
        /^@end titlepage/a\
@contents' >> script
fi

$ODINCACHE/PKGS/skeleton/sed.exe -f script $ODIN_tnf > tex_input
