#!/bin/sh
# $Id: tpOut.sh,v 1.3 2000/08/23 02:49:45 waite Exp $
# Copyright 1998, The Regents of the University of Colorado

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

# EXEC (tpOut.sh) (:tp.cmpd :names) (:tpGen :name)
#   => (:tpOut);

ODIN_spec_names=$1;shift; ODIN_product_name=$1;shift;
touch tpOut

if test -s "$ODIN_spec_names"
then cp $ODIN_product_name tpOut
else :
fi
