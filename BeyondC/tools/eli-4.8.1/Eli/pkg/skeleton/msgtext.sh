#!/bin/sh
# $Id: msgtext.sh,v 2.8 2005/06/14 00:19:24 asloane Exp $
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

# EXEC (msgtext.sh) (sed.exe) (:filtered) (:errfiles :list :pasted)
#   => (:msgtext);

SED=$1;shift; ODIN_sorted_errors=$1;shift; ODIN_files=$1;shift;
touch msgtext

if test ! -s "$ODIN_sorted_errors"; then exit 0; fi

$SED -e "s;$ODINCACHE;"'$ODINCACHE;g
/^\. 0 0 \(.*\)$/s//\1/
/^\([^ 	]\+\) \([0-9]\+\) \([0-9]\+\) \(.*\)$/s//"\1", line \2:\3 \4/
' $ODIN_sorted_errors > msgtext
