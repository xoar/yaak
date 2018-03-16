#! /bin/sh

# EXEC (texauxin.sh) (:rootName) (:texauxout)& (:tex.bbl) (:tex.ind)
#   => (:texauxin.vtd);

ODIN_root=$1;shift; ODIN_aux=$1;shift; ODIN_bbl=$1;shift; ODIN_ind=$1;shift;
touch texauxin.vtd

if [ -d $ODIN_aux ]
then for f in `ls $ODIN_aux`; do echo "%$f==$ODIN_aux/$f" >> texauxin.vtd; done
fi

echo "%`cat $ODIN_root`.bbl==$ODIN_bbl" >> texauxin.vtd
echo "%`cat $ODIN_root`.ind==$ODIN_ind" >> texauxin.vtd

