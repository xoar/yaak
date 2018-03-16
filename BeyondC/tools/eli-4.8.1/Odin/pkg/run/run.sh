#!/bin/sh

ODIN_dir=$1;shift; ODIN_cmd=$1;shift;

if [ "$ODIN_cmd" = "" ] ; then
   echo ":run requires a +cmd parameter" > ERRORS
   exit 0; fi
cmd=`cat $ODIN_cmd`

echo '#!/bin/sh' >run
echo cd $ODIN_dir >>run
echo $cmd >>run
chmod +x run

exit 0
