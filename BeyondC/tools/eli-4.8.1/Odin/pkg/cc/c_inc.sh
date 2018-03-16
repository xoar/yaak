#!/bin/sh

ODIN_FILE=$1;shift; ODIN_dir=$1;shift;
ODIN_home=$1;shift; ODIN_incsp=$1;shift; ODIN_ignore=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}scan_for_includes `basename $ODIN_FILE`; fi

incsp="$ODIN_home"
if [ "$ODIN_incsp" != "" ] ; then incsp="$incsp `cat $ODIN_incsp`"; fi
incsp="$incsp $ODIN_CC_I"
for header in $incsp; do
   case $header in /*);; *)
      echo "Search path entry must be absolute: $header" >>ERRORS;;
      esac; done

sed -n -e '/^[ 	]*#[ 	]*include/s/^[^"]*"\([^"]*\)".*$/\1/w local' \
       -e '/^[ 	]*#[ 	]*include/s/^[^<]*<\([^>]*\)>.*$/\1/w global' \
   <$ODIN_FILE 2>>ERRORS

touch c_inc.view_desc
for kind in local global; do
   dirs=$incsp
   if [ $kind = local ] ; then dirs="$ODIN_dir $dirs"; fi
   for name in `cat $kind`; do
      case $name in
         /* )
            echo "$name" >>c_inc.view_desc
            echo "=''" >>c_inc.view_desc;;
         * )
	    for header in $dirs; do
	       echo "$header/$name" >>c_inc.view_desc; done
            echo "=''" >>c_inc.view_desc;; esac; done; done \
 || echo 'C include scanning failed' >>ERRORS

if [ -f c_inc.view_desc ] ; then
   if [ "$ODIN_ignore" != "" ] ; then
      egrep -v -f $ODIN_ignore <c_inc.view_desc >tmp
      mv tmp c_inc.view_desc; fi
   if [ "$ODIN_IGNORE" != "" ] ; then
      egrep -v -e $ODIN_IGNORE <c_inc.view_desc >tmp
      mv tmp c_inc.view_desc; fi
   sed -e "/=''/!s/\(.*\)/'\1'/" < c_inc.view_desc > tmp
   mv tmp c_inc.view_desc; fi

exit 0
