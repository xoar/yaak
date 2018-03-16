#!/bin/sh

ODIN_dbdir=$1;shift; ODIN_objs=$1;shift; ODIN_libs=$1;shift;

PATH=${PATH}:${OS_ROOTDIR}/bin; export PATH
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${OS_ROOTDIR}/lib; export LD_LIBRARY_PATH

if [ "${ODIN_dbdir}" = "" ] ; then
  touch schema.C
  exit 0; fi
dbdir=${ODIN_dbdir}

objs=`cat ${ODIN_objs}`

libs=''
if [ "${ODIN_libs}" != "" ]; then
   libs=`cat ${ODIN_libs}`; fi

if [ "${ODINVERBOSE}" != "" ]; then
   echo ${ODINRBSHOST}os_prelink ${schema_C} ${dbdir}/com_schema ${dbdir}/app_schema $objs $libs; fi

os_prelink schema.C ${dbdir}/com_schema ${dbdir}/app_schema $objs $libs 2>WARNINGS \
 || { mv WARNINGS ERRORS
      echo 'Generation of application schema failed' >>ERRORS; }

exit 0
