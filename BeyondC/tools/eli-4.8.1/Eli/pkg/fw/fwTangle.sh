#!/bin/sh
# $Id: fwTangle.sh,v 2.8 2002/05/08 15:00:53 waite Exp $
# Copyright 1992, The Regents of the University of Colorado
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

# EXEC (fwTangle.sh) (fw.exe)
#      (:fw :label)
#      (:fw_srcs :ls)
#      (:fw_srcs :labels)
#      (:fw_srcs :tabsexpanded :vir_dir)
#   NEEDS (:fw_srcs :map=:expandtabs) ($ODINCACHE/PKGS/skeleton/sed.exe)
#         ($ODINCACHE/PKGS/skeleton/err_map.exe)
#   => (:fwGen) (:fwMap) (:fwNop);

# :fwGen 'Objects generated from a FunnelWeb specification'
#    => :DERIVED-DIRECTORY;
# :fwMap 'Mapping from output objects to FunnelWeb specification' => :FILE;

ODIN_fw=$1;shift; ODIN_fwlabel=$1;shift; ODIN_fw_srcs=$1;shift;
ODIN_fw_srcslabels=$1;shift; ODIN_dir=$1;shift;

mkdir fwGen

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$ODIN_fw +F"$ODIN_dir"/`cat $ODIN_fwlabel` +I"$ODIN_dir"/ +L./l +OfwGen/ +U./m \
  +N./n 1>/dev/null 2>&1

if test $? -ne 0
then
  $SED -n -e \
    's;^"'$ODIN_dir'/\([^"]*\)", line \([0-9]*\):\([0-9]*\);\1 \2 \3;
    /WARNING/{
      s/WARNING: //
      w WARNING
      d
    }
    /ERROR/{
      s/ERROR: //
      w ERROR
      d
    }
    /DEADLY/{
      s/DEADLY: //
      w ERROR
      d
    }' l.lis

  if test -s ERROR
  then $ODINCACHE/PKGS/skeleton/err_map.exe $ODIN_fw_srcslabels \
    $ODIN_fw_srcs ERROR >ERRORS
  fi
  
  if test -s WARNING
  then $ODINCACHE/PKGS/skeleton/err_map.exe $ODIN_fw_srcslabels \
    $ODIN_fw_srcs WARNING >WARNINGS
  fi
fi

$SED -e "s;^$ODIN_dir/\([^ ]*\);\1;
  s;fwGen/;;" m.map > map
$ODINCACHE/PKGS/skeleton/err_map.exe $ODIN_fw_srcslabels $ODIN_fw_srcs map \
  | $SED -e \
      's/^\([^ ]* [^ ]* [^ ]* [^ ]*\) \(.*\)/\2 \1/' \
  > fwMap

mv n.nop fwNop
