#!/bin/sh

ODIN_roff=$1;shift; ODIN_dir=$1;shift; ODIN_mp=$1;shift;

mflag=''
if [ "$ODIN_mp" != "" ] ; then mflag=-m`cat $ODIN_mp`; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}nroff $mflag `basename $ODIN_roff`; fi

(cd $ODIN_dir; nroff $mflag <$ODIN_roff) >nroff 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'nroff failed' >>ERRORS; }

exit 0
