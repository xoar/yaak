#! /bin/sh

# EXEC (bibtex.sh) (:citations)& (:texsp)
#    NEEDS (:texbasis :extract=:bib) (:texbasis :extract=:bst)
#    => (:tex.bbl);

ODIN_cite=$1;shift; ODIN_search=$1;shift;
touch tex.bbl

if [ ! -s $ODIN_cite ] ; then exit 0; fi

grep -e '\\citation' $ODIN_cite > temp
if [ ! -s temp ] ; then exit 0; fi

grep -e '\\bibdata' $ODIN_cite > temp
if [ ! -s temp ] ; then exit 0; fi

for d in `cat $ODIN_search`; do sp=$sp"$d":; done

BIBINPUTS=$sp"$BIBINPUTS"; export BIBINPUTS;

if [ "$BSTINPUTS" != '' ]
then BSTINPUTS=$sp"$BSTINPUTS";
else BSTINPUTS=$sp"$TEXINPUTS";
fi
export BSTINPUTS;

ln -s $ODIN_cite tex.aux
bibtex tex 1>MSGS 2>&1 \
  || ( mv MSGS ERRORS; echo 'bibtex failed.' >>ERRORS )

