#!/bin/sh

ODIN_FILE=$1;shift; ODIN_dir=$1;shift; ODIN_home=$1;shift;
ODIN_incsp=$1;shift; ODIN_ignore=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}scan_for_includes `basename $ODIN_FILE`; fi

incsp="$ODIN_home"
if [ "$ODIN_incsp" != "" ] ; then incsp="$incsp `cat $ODIN_incsp`"; fi
incsp="$incsp $ODIN_IDL_I"
for header in $incsp; do
   case $header in /*);; *)
      echo "Search path entry must be absolute: $header" >>ERRORS;;
      esac; done

sed -n -e '/^[ 	]*#[ 	]*include/s/^[^"]*"\([^"]*\)".*$/\1/w local' \
       -e '/^[ 	]*#[ 	]*include/s/^[^<]*<\([^>]*\)>.*$/\1/w global' \
       -e '/import[ 	]*"/s/import[ 	]*"\(.*\)"[^"]*$/\1/w local1' \
   <$ODIN_FILE 2>>ERRORS

if [ -f local1 ] ; then sed 's/"[ 	]*,[ 	]*"/ /g' <local1 >>local; fi

touch idl_inc.view_desc
for kind in local global; do
   dirs=$incsp
   if [ $kind = local ] ; then dirs="$ODIN_dir $dirs"; fi
   for name in `cat $kind`; do
      case $name in
         /* )
            echo "$name" >>idl_inc.view_desc
            echo "=''" >>idl_inc.view_desc;;
         * )
	    for header in $dirs; do
	       echo "$header/$name" >>idl_inc.view_desc; done
            echo "=''" >>idl_inc.view_desc;; esac; done; done \
 || echo 'IDL include scanning failed' >>ERRORS

if [ -f idl_inc.view_desc ] ; then
   if [ "$ODIN_ignore" != "" ] ; then
      egrep -v -f $ODIN_ignore -v <idl_inc.view_desc >tmp
      mv tmp idl_inc.view_desc; fi
   if [ "$ODIN_IGNORE" != "" ] ; then
      egrep -v -e $ODIN_IGNORE <idl_inc.view_desc >tmp
      mv tmp idl_inc.view_desc; fi
   sed -e "/=''/!s/\(.*\)/'\1'/" < idl_inc.view_desc > tmp
   mv tmp idl_inc.view_desc; fi

exit 0
