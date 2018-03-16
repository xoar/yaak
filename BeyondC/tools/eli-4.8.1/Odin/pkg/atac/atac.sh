#!/bin/sh

ODIN_data=$1;shift; ODIN_trace=$1;shift; ODIN_flags=$1;shift
PATH=$ATACHOME/bin:$PATH; export PATH

atacflags=""
if [ "$ODIN_flags" != "" ] ; then atacflags="$atacflags `cat $ODIN_flags`"; fi

echo '#!/bin/sh' >>atac
echo 'PATH=$PATH:'$ATACHOME'/bin' >>atac
echo xatac $atacflags $ODIN_trace `cat $ODIN_data` >>atac
chmod +x atac

exit 0

