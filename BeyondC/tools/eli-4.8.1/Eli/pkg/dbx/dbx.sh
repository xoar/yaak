#!/bin/sh
# $Id: dbx.sh,v 2.1 2001/05/09 20:45:23 waite Exp $
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

# EXEC (dbx.sh) (:sources :dir_of :vir_dir)
#      (:sources +incl=(:includes) :map=:incl.all :union :dir_of :vir_dir)
#      (:exe) (+core)
#   NEEDS (:sources) (:sources +incl=(:includes) :map=:incl.all :union)
#   => (:gdb);

echo '#! /bin/sh' > dbx
echo '${ELI_DEBUGGER-dbx}' -I $1 -I $2 $3 $4 >> dbx
echo 'exit 0' >> dbx

chmod +x gdb

exit 0
