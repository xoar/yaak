#!/bin/sh

ODIN_exe=$1;shift; ODIN_pkgdir=$1;shift; ODIN_pkglst=$1;shift;

if [ "$ODIN_pkglst" = "" ] ; then
   echo '+pkg must be set' >>ERRORS
   exit 0; fi

if [ "$ODIN_pkgdir" = "" ] ; then
   echo '+pkg_dir must be set' >>ERRORS
   exit 0; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}`basename $ODIN_exe` $ODIN_pkgdir $ODIN_pkglst; fi

$ODIN_exe $ODIN_pkglst $ODIN_pkgdir 0 >dg.log 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'dg.exe failed' >>ERRORS; }

if [ -f DG.c ] ; then mv DG.c c; fi
if [ -f DRVGRF ] ; then mv DRVGRF dg.tab; fi
if [ -f ENV ] ; then mv ENV dg.env; fi

exit 0

