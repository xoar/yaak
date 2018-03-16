#! /bin/sh

# EXEC (makeindex.sh) (:indexntry)& (+index_flags)
#   => (:tex.ind) (:tex.ilg);

ODIN_idx=$1;shift; ODIN_flags=$1;shift

if [ -f $ODIN_idx ]
then ln -s $ODIN_idx tex.idx
else touch tex.idx
fi

if test "$ODIN_flags" != ''
then flags=`tr '
' ' ' < $ODIN_flags`
else flags=''
fi

touch tex.log

makeindex -q $flags tex.idx 2>ERRORS \
  || { echo 'makeindex failed' >> ERRORS; exit 0; }

sed -n -e '/!! Input index error /{
N
s/^.*(file = \(.*\), line = \([1-9][0-9]*\)):[^-]*-- \(.*\)$/\1 \2 0 \3/w ERR
}
/## Warning /{
N
s/^.*(input = \(.*\), line = \([1-9][0-9]*\);.*[^-]*-- \(.*\)$/\1 \2 0 \3/w WARN
}' tex.ilg

if [ -s ERR ]
then
  echo "(|$ODIN_idx|line_err|" > ERRORS
  cat ERR >> ERRORS
  echo '|)' >> ERRORS
fi

if [ -s WARN ]
then
  echo "(|$ODIN_idx|line_err|" > WARNINGS
  cat WARN >> WARNINGS
  echo '|)' >> WARNINGS
fi

exit 0

