#!/bin/sh

ODIN_FILE=$1;shift; ODIN_home=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}scan_for_includes `basename $ODIN_FILE`; fi

(sed -n 's/^\.so[	 ]*\(.*\)$/\1/p' <$ODIN_FILE \
   | sed "s,^\([^/]\),$ODIN_home/\1," >so_inc_spec) 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'scan_for_includes failed' >>ERRORS; }

exit 0
