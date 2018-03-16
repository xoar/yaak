#!/bin/sh

ODIN_idl=$1;shift; ODIN_hdir=$1;shift; ODIN_a=$1;shift;

name=`basename $ODIN_idl .idl`
hdir=`cat $ODIN_hdir`
a=`cat $ODIN_a`

echo "$name.h == $hdir/$name.h" >>idl_targets
echo "${name}C.H == $hdir/${name}C.H" >>idl_targets
echo "${name}S.H == $hdir/${name}S.H" >>idl_targets
echo "lib$name.a == %lib$name.a" >>idl_targets
echo "%lib$name.a == $a" >>idl_targets

exit 0
