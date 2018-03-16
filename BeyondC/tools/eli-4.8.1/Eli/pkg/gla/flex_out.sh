#!/bin/sh
# $Id: flex_out.sh,v 2.5 2002/05/08 15:00:54 waite Exp $
# Copyright 1991, The Regents of the University of Colorado

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

# EXEC (flex_out.sh) (.) (:flex_spec)
#   NEEDS (flex.exe) ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:flex_binary) (:accept_binary) (:lastdfa_binary);

PKG=$1;shift; ODIN_flex_spec=$1;shift;

$PKG/flex.exe -G -cf $ODIN_flex_spec >ERROR 2>&1
if test -s ERROR
then
  echo "(|$ODIN_flex_spec|line_err|" > ERRORS
  $ODINCACHE/PKGS/skeleton/sed.exe -e "/^Syntax error/{
      s;^.* line \([0-9][0-9]*\): \(.*\);$ODIN_flex_spec \1 0 \2;p
      d
    }
    s;^;$ODIN_flex_spec 0 0 ;" ERROR \
  >> ERRORS
  echo "|)" >> ERRORS
  cp /dev/null flex_binary
  cp /dev/null accept_binary
  cp /dev/null lastdfa_binary
else
  mv flex.binary flex_binary
  mv accept.binary accept_binary
  mv lastdfa.binary lastdfa_binary
fi
