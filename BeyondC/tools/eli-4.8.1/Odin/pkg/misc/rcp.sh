#!/bin/sh

ODIN_FILE=$1;shift; ODIN_fdest=$1;shift; ODIN_ddest=$1;shift

if [ "$ODIN_fdest" != "" ] ; then
   dest=`cat $ODIN_fdest`
elif [ "$ODIN_ddest" != "" ] ; then
   dest=`cat $ODIN_ddest`/`basename $ODIN_FILE`
else
   echo "Either +f_dest or +d_dest must be specified" >>ERRORS
   exit 0; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}rcp `basename $ODIN_FILE` $dest; fi

rcp $ODIN_FILE $dest 2>>ERRORS

exit 0
