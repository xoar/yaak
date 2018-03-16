#!/bin/sh

ODIN_lib=$1;shift; ODIN_libsp=$1;shift;

lib_names=''
if [ "$ODIN_lib" != "" ] ; then lib_names=`cat $ODIN_lib`; fi
flags=''; bases=''
if [ "$ODIN_libsp" != "" ] ; then
   flags=`cat $ODIN_libsp | sed 's/^/-L/'`
   bases="$bases `cat $ODIN_libsp`"; fi

if [ "$ODINVERBOSE" != "" -a "$lib_names" != "" ] ; then
   echo ${ODINRBSHOST}scan_for_libraries "("$lib_names")" in "("$bases")"; fi

touch libraries.view_desc
for lib_name in `echo $lib_names | sed 's/-L /-L/g'`; do
   case $lib_name in
      /* )
	 echo "'$lib_name'" >>libraries.view_desc
         echo "=''"  >>libraries.view_desc
	 flags="$flags $lib_name";;
      -L* )
         bases="$bases `expr $lib_name : '..\(.*\)'`"
         flags="$flags $lib_name";;
      -* )
         flags="$flags $lib_name";;
      * )
	 for lib_base in $bases $ODIN_LIB_SP; do
            for ext in `echo so sl a`; do
	       lib=$lib_base/lib${lib_name}.$ext
	       echo "'$lib'" >>libraries.view_desc
	       filepat=$lib.[0-9]*.[0-9]*
               file=`echo $filepat`
	       if [ "$filepat" != "$file" ] ; then
		  echo "'$file'" >>libraries.view_desc; fi; done; done
         str=$lib_name
         echo "='$str'" >>libraries.view_desc
         flags="$flags -l$lib_name";; esac; done

echo $flags >library_flags

exit 0
