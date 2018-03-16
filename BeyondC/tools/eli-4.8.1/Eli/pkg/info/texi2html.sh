#! /bin/sh
# $Id: texi2html.sh,v 2.2 2008/03/23 20:43:22 profw Exp $
# Copyright 2008, The Regents of the University of Colorado

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

# EXEC (texi2html.sh) (texi2html) (:allspecs :extract=:tnf :dir_of :vir_dir)
#      (head.html) (foot.html)
#   => (:tnfhtml);
#:tnfhtml 'HTML created from TeXInfo' => :FILE;

ODIN_texi2html=$1; shift; ODIN_tnfs=$1;shift;
ODIN_head=$1;shift; ODIN_foot=$1;shift;

mkdir tnfhtml

ODIN_RUNDIR=`pwd`
cd $ODIN_tnfs

flags="-iso -split_chapter -head $ODIN_head -foot $ODIN_foot"

# Preprocess to generate global index and xref information
for i in *.tnf
do
	$ODIN_texi2html $flags -preprocess $i
done

# Actually process
for i in *.tnf
do
    pdf=`basename $i .tnf`.pdf
    fileflags="$flags -ps $pdf"
	$ODIN_texi2html $fileflags $i </dev/null 1>MSGS 2>&1 \
      || ( mv MSGS ERRORS; echo 'texi2html failed.' >>ERRORS )
	rm -f MSGS
done	

cp *.html $ODIN_RUNDIR/tnfhtml

exit 0
