#!/bin/sh
# $Id: infoOut.sh,v 2.4 2009/05/04 15:33:08 profw Exp $
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

# EXEC (infoOut.sh) (:level_6_specs :extract=:mapPgram :names)
#                   (:level_6_specs :parserInfo :names) (+parser)
#                   (noneInfo)
#   => (:infoOut);
# :infoOut 'Name of the parser generation information product' => :FILE;

ODIN_e119=$1;shift;
ODIN_info=$1;shift;ODIN_parser=$1;shift;
ODIN_none=$1;shift;
touch infoOut

if test -s $ODIN_e119
then
  if test -s $ODIN_info
  then cp $ODIN_info infoOut
  elif test 'none' = "$ODIN_parser"
  then echo $ODIN_none > infoOut
  else echo "Invalid parser generator name: $ODIN_parser" > ERRORS
  fi
else echo "There is no grammar to be tested for parsability" > ERRORS
fi
