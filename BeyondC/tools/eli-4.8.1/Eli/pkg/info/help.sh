#!/bin/sh
# $Id: help.sh,v 2.6 2004/06/29 15:05:45 profw Exp $
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

# EXEC (help.sh) (help_header) (help_trailer) (hypermsg.exe) (:filtered)
#      (:errfiles :list :pasted)
#   => (:help_tnf);

ODIN_header=$1;shift; ODIN_trailer=$1;shift; ODIN_hypermsg=$1;shift;
ODIN_sorted_errors=$1;shift; ODIN_files=$1;shift;
touch help_tnf

if test ! -s "$ODIN_sorted_errors"; then exit 0; fi

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e 's,\([^	]*\)	\(.*\),/Messages for /s;\1;\2;,' $ODIN_files \
	> SCRIPT

cat $ODIN_header > help_tnf
$ODIN_hypermsg $ODIN_sorted_errors | $SED -f SCRIPT >> help_tnf
cat $ODIN_trailer >> help_tnf
