#!/bin/sh
# $Id: gdb.sh,v 2.6 2001/05/09 20:45:25 waite Exp $
# Copyright 2001, The Regents of the University of Colorado

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

# EXEC (gdb.sh) (:sources :dir_of :vir_dir)
#      (:sources +incl=(:includes) :map=:incl.all :union :dir_of :vir_dir)
#      (:exe) (+core)
#   NEEDS (:sources) (:sources +incl=(:includes) :map=:incl.all :union)
#   => (:gdb);

echo '#! /bin/sh' > gdb
echo '${ELI_DEBUGGER-gdb}' -d $1 -d $2 $3 $4 >> gdb
echo 'exit 0' >> gdb

chmod +x gdb

exit 0
