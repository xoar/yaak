#!/bin/sh
# $Id: std_err.sh,v 2.5 2004/06/21 14:01:00 profw Exp $
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

# EXEC (std_err.sh) (+hookvalue) (:FILE) (+docref)
#   => (:std_err);

ODIN_HOOK=$1;shift; ODIN_atomic=$1;shift; ODIN_docref=$1;shift;

if test -z "$ODIN_docref"
then cp "$ODIN_HOOK" std_err
else $ODINCACHE/PKGS/skeleton/sed.exe -f $ODIN_atomic $ODIN_HOOK >std_err
fi
