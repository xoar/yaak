#!/bin/sh

ODIN_sccs=$1;shift; ODIN_date=$1;shift; ODIN_rev=$1;shift;

file=`basename $ODIN_sccs`
case $file in s.*);; *) 
   file=s.$file;; esac
ln -s $ODIN_sccs $file

flag=""
if [ "$ODIN_date" != "" ] ; then flag="$flag -c$ODIN_date"; fi
if [ "$ODIN_rev" != "" ] ; then flag="$flag -r$ODIN_rev"; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}sccs get $flag `basename $file`; fi

sccs get $flag $file 2>WARNINGS \
 || { mv WARNINGS ERRORS
      echo "sccs-get failed" >>ERRORS; }

dest=`expr "$file" : 's.\(.*\)`
if [ -f $dest ] ; then mv $dest sccs.co; fi

exit 0

