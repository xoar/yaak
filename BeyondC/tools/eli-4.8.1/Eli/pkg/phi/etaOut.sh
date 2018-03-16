#!/bin/sh
# $Id: etaOut.sh,v 1.3 1997/08/28 15:39:17 mjung Exp $
# Copyright, 1990, The Regents of the University of Colorado
# 
# This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

ODIN_RUNDIR=`pwd`;
ETA=$1;shift
GEN=etaOut;
mkdir $GEN;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

# compose files from cat specifications:
# -------------------------------------

if test -s "$ETA"
then
	# translate list of eta spec file names to list of cat commands:

	$SED -e "#n
h
/eta\..*eta$/{
	s,^.*\.\([^\.]*\)\.eta\..*$,\1.eta.h,
	b weiter
}
s,^.*\.\([^\.]*\)\.eta$,\1.eta.h,
:weiter
x
G
s,^\(.*\)\n\(.*\)$,(if test ! -s $GEN/\2; then cp /dev/null $GEN/\2; fi; echo \1 >> \2;)," $ETA > _aux

	# execute list of cat commands:
	. ./_aux


for genfile in `ls *.h`
do
        destlines=0
        for f in `cat $genfile`
        do
                cat $f >> $GEN/$genfile
                echo '' >> $GEN/$genfile
                lines=`$SED -n -e '$=' $f`
                lines=`expr $lines + 2`
                echo $genfile `expr $destlines + 1` 0 `expr $destlines + $lines` 0 $f 1 1 0 >> etaMap
                destlines=`expr $destlines + $lines - 1`
        done
done

if test ! -s etaMap
then
        cp /dev/null etaMap
fi
fi
exit 0



