#! /bin/sh
# $Id: mapBuOut.sh,v 2.2 1997/08/28 18:26:48 waite Exp $
# Copyright 1997, The Regents of the University of Colorado

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

ODIN_lido=$1;shift;
ODIN_BottomUp=$1;shift;
ODIN_mapBuPgram=$1;shift;

# EXEC (mapBuOut.sh) (:lido.cmpd :names) (:LIST :extract=:MeBottomUp :cat)
#                    (:mapBuPgram :name)
#   => (:mapBuOut);
# :mapBuOut 'Output from Maptool step with bottomup constraints' => :FILE;

if test -s "$ODIN_lido" -a -s "$ODIN_BottomUp"
then
	cat "$ODIN_mapBuPgram" > mapBuOut
else
	cp /dev/null mapBuOut
fi

exit 0
