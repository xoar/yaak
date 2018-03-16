#!/bin/sh
# $Id: index.sh,v 2.3 2008/03/10 14:24:27 asloane Exp $
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

# EXEC (index.sh) (:tnfndx) (texinfo/texindex.exe)
#   => (:tnfsndx);

ODIN_ndx=$1;shift; ODIN_texindex=$1;shift;
mkdir tnfsndx

for f in `ls $ODIN_ndx`
do
  if [ -s $ODIN_ndx/$f ]
  then
    cp $ODIN_ndx/$f tnfsndx
    $ODIN_texindex tnfsndx/$f
    rm -f tnfsndx/$f
  else :
  fi
done
