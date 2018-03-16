#!/bin/sh
# $Id: all_info.sh,v 2.7 2008/03/10 13:30:09 asloane Exp $
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

# EXEC (all_info.sh) (:level_0_specs :extract=:tnf :ls)
#      (texinfo/makeinfo.exe)
#   NEEDS (:level_0_specs :extract=:tnf)
#   => (:gindex_tnf) (:index_info);

ODIN_tnf=$1;shift; ODIN_makeinfo=$1;shift;

# Build a special info file representing the merged indexes of the others

cat <<END > gindex.tnf
\input texinfo   @c -*-texinfo-*-
@comment Copyright, 1989, The Regents of the University of Colorado
@comment %**start of header
@setfilename gindex
@settitle Global Index
@setchapternewpage odd
@comment %**end of header

@node top, , , (dir)
@unnumbered Global Index
@menu
END

# Note: The tab character used in two places below must be a character
# that is otherwise guaranteed not to appear in the index entries.

touch tmp
for i in `cat $ODIN_tnf`
do
	j=`basename $i .tnf`
	$ODINCACHE/PKGS/skeleton/sed.exe -n -e '/^[ 	]*@node[ 	]/{
		s/^[ 	]*@node[ 	][ 	]*\([^,]*\).*$/('$j')\1/
		h
		}
		/^@.index/{
			s/ *$//
			G
			s/^@.index *\(.*\)\n\(.*\)/* \1	 \2/p
		}' $i >> tmp
done
tr -d '\r' < tmp | sort -u >tmpsorted

# This mucking about arranges for duplicate entries to
# have unique numbers appended to them to make them selectable.
cat <<\END >awkscr
BEGIN{FS="	";last="";count=1}
{ if (last == $1)
    printf("%s %d:%s.\n", $1, count++, $2);
  else {
    printf("%s:%s.\n", $1, $2);
    count = 1;
    last = $1;
  }
} 
END
awk -f awkscr tmpsorted >>gindex.tnf

# End the menu.
echo '@end menu' >> gindex.tnf

# For the printed manual, use actual cross file links that are visible
echo '@iftex' >> gindex.tnf
sed -n -e 's/^\* \([^(]*\)(\([^)]*\))\(.*\)$/\1: @xref{\3,,,\2,\2}@*/p' tmpsorted >> gindex.tnf
echo '@end iftex' >> gindex.tnf

# End the file
echo '@bye' >> gindex.tnf

# Turn gindex.tnf into the gindex info file

$ODIN_makeinfo +no-split gindex.tnf > /dev/null 2> Report

if [ -s Report ]
then
	grep 'Warning' Report > WARNINGS
	grep -v 'Warning' Report > ERRORS
else :
fi

# Make gindex.tnf available as a product

mv gindex.tnf gindex_tnf

# Add gindex to the output list

if test -f gindex
then
	mv gindex index_info
else
	cp /dev/null index_info
fi
