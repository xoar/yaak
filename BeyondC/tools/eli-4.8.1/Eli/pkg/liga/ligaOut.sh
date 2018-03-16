#!/bin/sh
# $Id: ligaOut.sh,v 2.4 1997/08/29 08:13:57 peter Exp $
# Copyright (c) 1990, The Regents of the University of Colorado

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

ODIN_RUNDIR=`pwd`;
PKG=$1;shift; ODIN_e62=$1;shift; ODIN_e63=$1;shift; ODIN_BottomUp=$1;shift;

#EXEC (ligaOut.sh) (.) (:lido.cmpd :names) (:ligaBe :name) (:BottomUp :name)
#  => (:ligaOut);
#    :ligaOut 'LIGA input exists then request products of LIGA' => :FILE;


if test -s "$ODIN_e62"
then cat "$ODIN_e63" "$ODIN_BottomUp" > ligaOut
else  echo $PKG/Frames/dfltattr.reqmod > ligaOut
fi
