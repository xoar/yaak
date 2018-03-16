#! /bin/sh
# $Id: tex.sh,v 2.16 2009/08/18 02:42:52 profw Exp $
# Copyright 2004, The Regents of the University of Colorado

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

# EXEC (tex.sh) (+usepdf) (:rootName) (:texsp)
#      (:tex.vtd :tnfauxin.vtd :vir_dir)&
#    NEEDS (:texbasis :extract=:tex) (:texbasis :extract=:sty)
#      (:tex.vtd :tnfauxin.vtd :vir_tgt.list)&
#    => (:tnfdvi) (:tnflog) (:tnfaux) (:tnfndx) (:tnfpdf);

ODIN_usepdf=$1;shift; ODIN_root=$1;shift; ODIN_search=$1;shift;
ODIN_aux=$1;shift; export ODIN_aux
mkdir tnfaux

if [ "$ODIN_usepdf" != '' ]
then fmtcmd=pdftex
else fmtcmd=tex
fi

for d in `cat $ODIN_search`; do sp=$sp"$d":; done
TEXINPUTS=.:$sp"$TEXINPUTS"; export TEXINPUTS;

if [ -d "$ODIN_aux" ]
then
  if [ "`ls $ODIN_aux`" != '' ]
  then cp $ODIN_aux/* tnfaux; chmod +w tnfaux/*
  fi
fi

cd ./tnfaux

$fmtcmd `cat $ODIN_root`.tex </dev/null 1>../MSGS 2>&1 \
  || ( mv ../MSGS ../ERRORS; echo 'formatter failed.' >>../ERRORS )

cd ..

if [ -f tnfaux/*.dvi ] ; then mv tnfaux/*.dvi tnfdvi; fi
if [ -f tnfaux/*.pdf ] ; then mv tnfaux/*.pdf tnfpdf; fi
if [ -f tnfaux/*.log ]
then mv tnfaux/*.log tnflog
else touch tex.log
fi

mkdir tnfndx
for f in `ls tnfaux/*.?? 2>/dev/null`
do cp $f tnfndx
done

if [ -d "$ODIN_aux" ] && ( diff $ODIN_aux tnfaux > /dev/null )
then :
else rm -f dvi tnfpdf
fi

rm -f tnfaux/*.??s
