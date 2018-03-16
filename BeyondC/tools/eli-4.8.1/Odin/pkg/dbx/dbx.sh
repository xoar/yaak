#!/bin/sh

ODIN_exe=$1;shift; ODIN_core=$1;shift; ODIN_gnu=$1;shift

debugger=dbx
if [ "$ODIN_gnu" != "" ] ; then debugger=gdb; fi

echo '#!/bin/sh' >dbx
echo "$debugger" "$ODIN_exe" $ODIN_core >>dbx
chmod +x dbx

exit 0
