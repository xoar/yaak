#! /bin/sh

# EXEC (tex.sh) (:fmtcmd) (:rootName) (:texsp) (:tex.vtd :texauxin.vtd :vir_dir)&
#    NEEDS (:texbasis :extract=:tex) (:texbasis :extract=:sty)
#      (:texbasis :extract=:cls)
#      (:tex.vtd :texauxin.vtd :vir_tgt.list)&
#    => (:dvi) (:texpdf) (:tex.log) (:citations) (:indexntry) (:texauxout);

ODIN_fmtcmd=$1;shift; ODIN_root=$1;shift; ODIN_search=$1;shift; ODIN_aux=$1;shift;
mkdir texauxout

for d in `cat $ODIN_search`; do sp=$sp"$d":; done
TEXINPUTS=.:$sp"$TEXINPUTS"; export TEXINPUTS;

if [ -d "$ODIN_aux" ]
then
  if [ "`ls $ODIN_aux`" != '' ]
  then cp $ODIN_aux/* texauxout; chmod +w texauxout/*
  fi
fi

cd ./texauxout
`cat $ODIN_fmtcmd` `cat $ODIN_root`.tex </dev/null 1>../MSGS 2>&1 \
  || ( mv ../MSGS ../ERRORS; echo 'formatter failed.' >>../ERRORS )
cd ..

if [ -f texauxout/*.dvi ] ; then mv texauxout/*.dvi dvi; fi
if [ -f texauxout/*.pdf ] ; then mv texauxout/*.pdf texpdf; fi
if [ -f texauxout/*.log ]
then mv texauxout/*.log tex.log
else touch tex.log
fi

touch citations
for f in `ls texauxout/*.aux 2>/dev/null`
do
  grep -e '\\citation' $f >> citations
  grep -e '\\bibstyle' $f >> citations
  grep -e '\\bibdata'  $f >> citations
done

if [ -f texauxout/*.idx ]
then cp texauxout/*.idx indexntry
else touch indexntry
fi

if [ -d "$ODIN_aux" ] && ( diff $ODIN_aux texauxout > /dev/null )
then :
else rm -f dvi texpdf
fi

rm -f texauxout/*.bbl  texauxout/*.ind

