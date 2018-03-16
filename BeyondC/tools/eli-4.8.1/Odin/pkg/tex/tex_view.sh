#! /bin/sh

# EXEC (tex_view.sh) (:texnames) (+texsppt) => (:tex.view_desc);

ODIN_files=$1;shift; ODIN_search=$1;shift;
touch tex.view_desc
if [ ! -s $ODIN_files -o "$ODIN_search" = '' -o "$ODIN_search" = ' ' ]
then exit 0
fi

for f in `cat $ODIN_files`
do
  for d in `cat $ODIN_search`
  do echo "$d/$f" >> tex.view_desc
  done
  echo "=''" >> tex.view_desc
done

