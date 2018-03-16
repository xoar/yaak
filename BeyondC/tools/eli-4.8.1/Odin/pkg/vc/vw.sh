#!/bin/sh

ODIN_view=$1;shift; ODIN_viewsp=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}scanning_for_view `basename $ODIN_view`; fi

viewsp=;
if [ "$ODIN_viewsp" != "" ] ; then viewsp=`cat $ODIN_viewsp`; fi

for name in `sed 's/\([^/]*\)$/(+)\1/' <$ODIN_view`; do
   dir=`expr "$name" : '\(.*\)(\+)'`
   file=`expr "$name" : '.*(\+)\(.*\)$'`
   echo ${dir}${file} >>view.source.spec
   if [ "$ODIN_VC_RCS" = yes ] ; then
      echo ${dir}RCS/${file},v >>view.source.spec
      echo ${dir}${file},v >>view.source.spec; fi
   if [ "$ODIN_VC_SCCS" = yes ] ; then
     echo ${dir}SCCS/s.${file} >>view.source.spec
     echo ${dir}s.${file} >>view.source.spec; fi
   case "$dir" in /*);; *)
      for base in $viewsp; do
	 echo ${base}/${dir}${file} >>view.source.spec
	 if [ "$ODIN_VC_RCS" = yes ] ; then
	    echo ${base}/${dir}RCS/${file},v >>view.source.spec
	    echo ${base}/${dir}${file},v >>view.source.spec; fi
	 if [ "$ODIN_VC_SCCS" = yes ] ; then
	    echo ${base}/${dir}s.${file} >>view.source.spec
	    echo ${base}/${dir}SCCS/s.${file} >>view.source.spec
            fi; done;; esac
   echo "='${dir}${file}'" >>view.source.spec; done

exit 0
