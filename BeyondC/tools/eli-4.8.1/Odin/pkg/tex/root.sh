#! /bin/sh

# EXEC (root.sh) (:tex.vtd) (+texroot)
#   NEEDS (:tex.vtd :vir_tgt.list)
#   => (:rootName) (:rootFileName);

ODIN_vtd=$1;shift; ODIN_root=$1;shift;

if [ "$ODIN_root" != '' -a "$ODIN_root" != ' ' ]
then echo $ODIN_root > temp
else
  tr -d ' \011' < $ODIN_vtd \
    | sed -n -e '1s/^%\(.*\)==.*/\1/p' \
    > temp
fi

if [ -s temp ]
then
  sed -e 's/.tex$//' temp > rootName
  sed -e 's/$/.tex/' rootName > rootFileName
else 
     echo 'No document root found' > ERRORS
     
fi

