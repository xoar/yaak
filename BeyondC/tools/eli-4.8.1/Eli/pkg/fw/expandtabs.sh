#!/bin/sh
# $Id: expandtabs.sh,v 2.4 1998/10/12 02:38:28 tony Exp $
# Copyright 1994, The Regents of the University of Colorado
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

# EXEC (expandtabs.sh) (.) (:FILE)
#   NEEDS ($ODINCACHE/PKGS/skeleton/eliexpand.exe)
#   => (:expandtabs);
#
# :expandtabs 'Text file with tabs replaced by sequences of spaces' => :FILE;

PKG=$1;shift; ODIN_tabs=$1;shift;

$ODINCACHE/PKGS/skeleton/eliexpand.exe $ODIN_tabs > expandtabs
