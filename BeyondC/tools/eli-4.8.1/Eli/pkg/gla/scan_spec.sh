#! /bin/sh
# $Id: scan_spec.sh,v 2.4 2002/05/08 15:00:55 waite Exp $
# Copyright 1990, The Regents of the University of Colorado

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

# EXEC (scan_spec.sh) (.) (:gla.cmpd :names) (:lex_code.cmpd :names)
#      (:dflt_codes :name)
#   NEEDS (separator)
#   => (:scan_spec);

PKG=$1;shift; ODIN_e95=$1;shift; ODIN_e96=$1;shift; ODIN_e97=$1;shift;

# Glue together non-literal description, separator, and literals

if test -s $ODIN_e96
then
  cat $ODIN_e95 > scan_spec
  echo $PKG/separator >> scan_spec
  cat $ODIN_e96 >> scan_spec
elif test -s $ODIN_e95
then
  cat $ODIN_e95 > scan_spec
  echo $PKG/separator >> scan_spec
  cat $ODIN_e97 >> scan_spec
else
  touch scan_spec
fi
