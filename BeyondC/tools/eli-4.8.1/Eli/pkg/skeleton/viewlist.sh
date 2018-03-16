#! /bin/sh
# $Id: viewlist.sh,v 2.6 2003/06/30 02:30:09 waite Exp $
# Copyright 1996, The Regents of the University of Colorado

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

# EXEC (viewlist.sh) (sed.exe) (:LIST :dir_of :vir_dir) (doview)
#   NEEDS (:LIST)
#   => (:viewlist);

SED=$1;shift; ODIN_compound=$1;shift; ODIN_doview=$1;shift;

$SED -e "s;ODIN_compound;$ODIN_compound;g" $ODIN_doview > viewlist
chmod +x viewlist
