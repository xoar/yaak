#! /bin/sh
# $Id: tnfauxin.sh,v 2.2 2007/01/09 23:03:33 profw Exp $
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

# EXEC (tnfauxin.sh) (:rootName) (:tnfaux) (:tnfsndx)
#   => (:tnfauxin.vtd);

ODIN_root=$1;shift; ODIN_aux=$1;shift; ODIN_ndx=$1;shift; ODIN_bbl=$1;shift;
touch tnfauxin.vtd

for f in `ls $ODIN_aux`; do echo "%$f==$ODIN_aux/$f" >> tnfauxin.vtd; done

for f in `ls $ODIN_ndx`; do echo "%$f==$ODIN_ndx/$f" >> tnfauxin.vtd; done
