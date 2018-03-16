#!/bin/sh
# $Id: hypertext.sh,v 2.5 2009/08/17 17:45:45 profw Exp $
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

# EXEC (hypertext.sh) (.) (:help_dir) (:help_node) output
#   => (:help); 

PKG=$1;shift; ODIN_dir=$1;shift; ODIN_node=$1;shift;  ODIN_output=$1;shift;
touch $ODIN_output

if test ! -s $ODIN_node; then exit 0; fi

echo "#! /bin/sh

cd $ODIN_dir
$PKG/info.sh \
	-d .:$PKG/manuals:$PKG \
	-f \
	-n '`cat $ODIN_node`'" > $ODIN_output

chmod +x $ODIN_output
