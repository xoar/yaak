#!/bin/sh
# $Id: clp_out.sh.in,v 1.1 2001/05/09 20:44:05 waite Exp $
# Copyright (c) 1990, The Regents of the University of Colorado
# Copyright 1995-1998, Anthony M. Sloane

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

# EXEC (clp_out.sh) (:clp.cmpd :names) (:clp_gen :name) (+monitor)
#      (clp.c) (clp.h) (clp.specs) (clp.dapto) (+nomain)
#   => (:clp_out);
# 
# :clp_out 'Results of CLP processing' => :FILE;

ODIN_cmpd=$1;shift; ODIN_gen=$1;shift; ODIN_mon=$1;shift;
ODIN_clpc=$1;shift; ODIN_clph=$1;shift; ODIN_specs=$1;shift;
ODIN_dapto=$1;shift; ODIN_nomain=$1;shift;

touch clp_out

if test -s "$ODIN_cmpd"
then cat "$ODIN_gen" >> clp_out
elif test '' != "$ODIN_nomain"
then exit 0
else
    echo "$ODIN_clpc" >> clp_out 
    echo "$ODIN_clph" >> clp_out 
fi

echo "$ODIN_specs" >> clp_out

if test '' != "$ODIN_mon"
then echo "$ODIN_dapto" >> clp_out
fi
