#! /bin/sh
# $Id: fwSpec.sh,v 1.2 2002/05/08 15:00:53 waite Exp $
# Copyright 1997-1998, The Regents of the University of Colorado

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

# EXEC (fwSpec.sh) (fwSpec.sed)
#      (:fwGen :direlms :extract=:specs :labels)
#      (:fwGen :direlms :pasted)
#      (:fwGen)
#   NEEDS (:fwGen :direlms :extract=:specs) ($ODINCACHE/PKGS/skeleton/sed)
#   => (:fwSpec);

# :fwSpec 'Massaged specs files from a FunnelWeb file' => :DERIVED-DIRECTORY;

ODIN_sed=$1;shift;
ODIN_fwGenlabels=$1;shift; ODIN_fwGenFiles=$1;shift; ODIN_fwGen=$1;shift;
mkdir fwSpec

$ODINCACHE/PKGS/skeleton/sed.exe -f $ODIN_sed $ODIN_fwGenFiles > script

for file in `cat $ODIN_fwGenlabels`
do
	$ODINCACHE/PKGS/cpp/cpp.exe -I$ODIN_fwGen $ODIN_fwGen/$file \
		| $ODINCACHE/PKGS/skeleton/sed.exe -f script \
		> fwSpec/$file 2>> ERRORS
done
