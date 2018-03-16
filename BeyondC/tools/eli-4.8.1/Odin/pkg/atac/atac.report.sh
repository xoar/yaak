#!/bin/sh

ODIN_data=$1;shift; ODIN_trace=$1;shift; ODIN_flags=$1;shift
PATH=$ATACHOME/bin:$PATH; export PATH

atacflags=""
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_atac_flags`"; fi

#when running, set ATAC_NOCOMPRESS

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}atac -s $flags `basename $ODIN_trace` `cat $ODIN_data`; fi

atac -s $flags $ODIN_trace `cat $ODIN_data` >atac.report 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo "atac failed" >>ERRORS; }

exit 0
