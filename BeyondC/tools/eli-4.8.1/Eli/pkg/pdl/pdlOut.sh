#!/bin/sh
# $Id: pdlOut.sh,v 2.6 2010/02/26 17:51:00 profw Exp $
# Copyright 1992-2010, The Regents of the University of Colorado

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

# EXEC (pdlOut.sh) (:pdl.cmpd :names) (:pdlGen :name)
#      (deftbl.head) (deftbl.save.eta) (deftbl.reqmod) (pdl.dapto) (pdl.tcl)
#   => (:pdlOut);
# :pdlOut 'Results of PDL processing' => :FILE;

ODIN_e150=$1;shift; ODIN_e151=$1;shift;

if test -s "$ODIN_e150"
then
  cat $ODIN_e151 > pdlOut
  while test $# -ne 0
  do
    echo "$1" >> pdlOut
    shift
  done
else cp /dev/null pdlOut 
fi
