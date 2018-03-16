#! /bin/sh

# EXEC (texsp.sh) (:tex.vtd :vir_dir)@ (:dir)@ (+texsearch)
#   => (:texsp);

ODIN_vir_dir=$1;shift; ODIN_dir=$1;shift; ODIN_texsearch=$1;shift;

echo $ODIN_vir_dir > texsp
if [ "$ODIN_texsearch" = '' ]
then echo $ODIN_dir >> texsp
elif [ "$ODIN_texsearch" != ' ' ]
then
  for d in `cat $ODIN_texsearch`
  do
    case $d in
    /*) echo $d >> texsp ;;
    *)  echo "$d must be an absolute path name" >> ERRORS ;;
    esac
  done
else :
fi

