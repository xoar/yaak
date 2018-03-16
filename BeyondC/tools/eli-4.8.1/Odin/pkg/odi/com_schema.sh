#! /bin/sh -f

ODIN_schemas=$1;shift; ODIN_schemadirs=$1;shift;
ODIN_dbdir=$1;shift; ODIN_incsp=$1;shift; ODIN_standin=$1;shift;

PATH=$PATH:$OS_ROOTDIR/bin; export PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OS_ROOTDIR/lib; export LD_LIBRARY_PATH

if [ "$ODIN_schemas" = "" ] ; then
  touch com_schema_standin
  exit 0; fi
schemas=`cat $ODIN_schemas`

if [ "$ODIN_dbdir" = "" ] ; then
  echo "+schema_dir must be specified" >> ERRORS
  exit 0; fi
dbdir=$ODIN_dbdir

incsp=''
for sp in `cat $ODIN_schemadirs`; do
   incsp="$incsp -I$sp"; done
if [ "$ODIN_incsp" != "" ] ; then
  for sp in `cat $ODIN_incsp`; do
      incsp="$incsp -I$sp"; done; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo "${ODINRBSHOST}OSCC -batch_schema $dbdir/com_schema $incsp $schemas"; fi
 
OSCC -batch_schema $dbdir/com_schema $incsp $schemas 2>WARNINGS \
 || { if grep -s 'Out of virtual memory' WARNINGS; then
         cat WARNINGS
         exit 1; fi
      mv WARNINGS ERRORS
      echo 'Generation of compilation schema failed' >> ERRORS; }

#select
   if [ ! -f $ODIN_standin ] ; then
      num=0
   else
      num=`cat $ODIN_standin`; fi
echo `expr $num + 1` >com_schema_standin

exit 0

