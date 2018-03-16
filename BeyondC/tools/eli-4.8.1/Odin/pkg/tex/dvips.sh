#! /bin/sh

# EXEC (dvips.sh) (:dvi) (:texsp) (+dvips_flags)
#    NEEDS (:texbasis :extract=:ps)
#    => (:texps);

ODIN_dvi=$1;shift; ODIN_search=$1;shift; ODIN_flags=$1;shift;

if test "$ODIN_flags" != ''
then flags=`tr '
' ' ' < $ODIN_flags`
else flags=''
fi

for d in `cat $ODIN_search`; do sp=$sp"$d":; done
TEXINPUTS=$sp"$TEXINPUTS"; export TEXINPUTS;

dvips $flags -o texps $ODIN_dvi 1>MSGS 2>&1 \
 || ( mv MSGS ERRORS; echo 'dvips failed.' >>ERRORS )

