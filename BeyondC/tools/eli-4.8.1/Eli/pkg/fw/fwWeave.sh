#!/bin/sh
# $Id: fwWeave.sh,v 2.11 2007/01/09 23:27:46 profw Exp $
# Copyright 2007, The Regents of the University of Colorado
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

# :fwTex 'TeX representation of a FunnelWeb specification'? => :FILE;
# :fwTexinfo 'Texinfo representation of a FunnelWeb specification' => <:tnf>;
# :fwHtml 'HTML representation of a FunnelWeb specification'? => :FILE;

# EXEC (fwWeave.sh) (fw.exe)
#      (:fw :label)
#      (:fw_srcs :ls)
#      (:fw_srcs :labels)
#      (:fw_srcs :tabsexpanded :vir_dir)
#      (+chapter)
#   NEEDS (:fw_srcs :map=:expandtabs) ($ODINCACHE/PKGS/skeleton/sed.exe)
#         ($ODINCACHE/PKGS/skeleton/err_map.exe)
#   => (:fwTex) (:fwTexinfo) (:fwHtml) (:fwRep);

ODIN_fw=$1;shift; ODIN_fwlabel=$1;shift; ODIN_fw_srcs=$1;shift;
ODIN_fw_srcslabels=$1;shift; ODIN_dir=$1;shift; ODIN_chapter=$1;shift;
touch fwTex fwTexinfo fwHtml

SED=$ODINCACHE/PKGS/skeleton/sed.exe

label=`cat "$ODIN_fwlabel"`
source=$ODIN_dir/$label
srcfile=`echo $label | $SED -e 's/\.[^.]*$//'`

if test "$ODIN_chapter" != ''; then fwA='+A'; else fwA='-A'; fi

cp $source $srcfile.fw

"$ODIN_fw" $fwA -I"$ODIN_dir"/ +T -O +Q +U $srcfile.fw \
	1>/dev/null 2>&1

if test $? -ne 0
then
 	$SED -n 's;^"'$srcfile.fw'";"'$source'";
		s;^"'$ODIN_dir'/\([^"]*\)", line \([0-9]*\):\([0-9]*\);\1 \2 \3;
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
		}' $srcfile.lis
fi

if test -f $srcfile.tnf
then
  mv $srcfile.tnf fwTexinfo
  echo ':fwTexinfo' > fwRep
elif test -f $srcfile.tex
then
  mv $srcfile.tex fwTex
  echo ':fwTex' > fwRep
elif test -f $srcfile.html
then
  mv $srcfile.html fwHtml
  echo ':fwHtml' > fwRep
fi

if test -s ERROR
then "$ODINCACHE/PKGS/skeleton/err_map.exe" "$ODIN_fw_srcslabels" \
	"$ODIN_fw_srcs" ERROR >>ERRORS
fi

if test -s WARNING
then "$ODINCACHE/PKGS/skeleton/err_map.exe" "$ODIN_fw_srcslabels" \
	"$ODIN_fw_srcs" WARNING >>WARNINGS
else :
fi
