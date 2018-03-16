#! /bin/sh
# $Id: mapOut.sh,v 2.5 2005/06/08 15:18:24 profw Exp $
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

# EXEC (mapOut.sh) (:lido.cmpd :names) (:con.cmpd :names)
#                  (:mapFe :name) (:mapBe :name)
#                  (:mapPgram :name) (treestack.h)
#  => (:mapOut);
#:mapOut 'Output from Maptool step' => :FILE;

ODIN_lido=$1;shift; ODIN_con=$1;shift;
ODIN_mapFe=$1;shift; ODIN_mapBe=$1;shift;
ODIN_mapPgram=$1;shift; ODIN_treestack=$1;shift;

if test -s "$ODIN_con" -o -s "$ODIN_lido"
then cat $ODIN_mapFe $ODIN_mapPgram > mapOut
fi
  
if test -s "$ODIN_lido"
then cat $ODIN_mapBe >> mapOut
elif test -s "$ODIN_con"
then echo $ODIN_treestack >> mapOut
else cat /dev/null > mapOut
fi
