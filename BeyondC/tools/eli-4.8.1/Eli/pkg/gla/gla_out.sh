#!/bin/sh
# $Id: gla_out.sh,v 2.6 2010/02/26 17:50:57 profw Exp $
# Copyright 1990, The Regents of the University of Colorado

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

# EXEC (gla_out.sh) (:scan_spec :list :names) (:gla_be :name)
#      (gla.specs) (dfltscan.reqmod)
#   => (:gla_out);

ODIN_glafiles=$1;shift; ODIN_scanner=$1;shift;
ODIN_gla_specs=$1;shift; ODIN_dfltscan_reqmod=$1;shift;

if test -s $ODIN_glafiles
then
  cat $ODIN_scanner $ODIN_gla_reqmod > gla_out
  echo $ODIN_gla_specs >> gla_out 
else echo $ODIN_dfltscan_reqmod > gla_out 
fi
