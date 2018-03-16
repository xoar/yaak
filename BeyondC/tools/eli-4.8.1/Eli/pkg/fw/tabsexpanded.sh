#!/bin/sh
# $Id: tabsexpanded.sh,v 2.5 2002/05/08 15:00:53 waite Exp $
# Copyright 1994, The Regents of the University of Colorado
# Copyright 1995, Anthony M. Sloane

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

# EXEC (tabsexpanded.sh) (:LIST :labels) (:LIST :ls)
#   NEEDS ($ODINCACHE/PKGS/skeleton/paste.exe)
#   => (:tabsexpanded);
#
# :tabsexpanded 'Odinfile defining files with expanded tabs' => :FILE;

ODIN_labels=$1;shift; ODIN_ls=$1;shift;

$ODINCACHE/PKGS/skeleton/paste.exe $ODIN_labels $ODIN_ls \
  | $ODINCACHE/PKGS/skeleton/sed.exe -e \
      's;^\([^	]*\)	\(.*\);%\1==\2 :expandtabs;' \
  > tabsexpanded
