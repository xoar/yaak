#! /bin/sh

# EXEC (oneTex.sh) (:tex) (:label) => (:one_tex_vtd)

sed -e 's;\(.*\)\.[^.]*$;\1;
s;.*;%&.tex=='"$1;" $2 > one_tex_vtd

