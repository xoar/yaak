#!/bin/sh
# $Id: oil_out.sh,v 2.7 2010/03/18 19:30:46 profw Exp $
# Copyright 2007, The Regents of the University of Colorado

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

# EXEC (oil_out.sh) (:oil.cmpd :names) (:oil_gen :name) (oil.specs)
#   => (:oil_out);

ODIN_spec_names=$1;shift; ODIN_product_name=$1;shift; ODIN_specs=$1;shift;

if test -s "$ODIN_spec_names"
then
  echo $ODIN_specs > oil_out
  cat $ODIN_product_name >> oil_out
else touch oil_out 
fi
