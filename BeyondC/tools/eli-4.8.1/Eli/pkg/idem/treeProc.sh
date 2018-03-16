#!/bin/sh
# $Id: treeProc.sh,v 2.1 2002/07/31 23:45:43 waite Exp $
# Copyright 2002, The Regents of the University of Colorado

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

# EXEC (treeProc.sh) (.) (+lang)
#   => (:treeProc);
# :treeProc 'View descriptor for tree unparser generator' => :FILE;

ODIN_pkg=$1;shift; ODIN_lang=$1;shift;

if test "$ODIN_lang" != ''
then
  case $ODIN_lang in
    /*)
      echo $ODIN_lang > treeProc
      echo "='$ODIN_lang missing'" >> treeProc ;;
    *)
      echo $ODIN_pkg/$ODIN_lang.exe > treeProc
      echo "='Illegal language: $ODIN_lang'" >> treeProc ;;
  esac
else
  echo $ODIN_pkg/Tree.exe > treeProc
  echo "='Internal error: Tree.exe missing'" >> treeProc
fi
