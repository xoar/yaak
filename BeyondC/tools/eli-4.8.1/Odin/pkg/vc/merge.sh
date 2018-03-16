#!/bin/sh

ODIN_names=$1;shift; ODIN_ops=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}apply_ops `basename $ODIN_names` `basename $ODIN_ops`; fi

sed -e '/\\$/N' -e '/\\$/!s/\n/(++EOL++)/g' <$ODIN_ops >ops 2>>ERRORS

($ODIN_PASTE -d'\0' $ODIN_names ops | sed 's/(++EOL++)/\
/g') >view.names 2>>ERRORS

exit 0
