#!/bin/sh

ODIN_FILE=$1;shift; ODIN_dir=$1;shift; ODIN_sed=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}generate_header_file `basename $ODIN_FILE`; fi

cc -E -I$ODIN_dir $ODIN_FILE | sed -n -f $ODIN_sed >c.h 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'header generation failed' >>ERRORS; }

exit 0
