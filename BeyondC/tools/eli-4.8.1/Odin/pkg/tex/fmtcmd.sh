#! /bin/sh

# EXEC (fmtcmd.sh) (:rootFileName +texsppt=(:texsp) :texfiles :ls) (+tex) (+latex)
#      (+usepdf)
#    => (:fmtcmd);

ODIN_rootFile=$1;shift; ODIN_tex=$1;shift; ODIN_latex=$1;shift;
ODIN_pdf=$1;shift;

rootFile=`cat $ODIN_rootFile`
if [ "$rootFile" = '' ]
then echo 'The specified root file is not on the search path' > ERRORS
elif [ ! -s $rootFile ]
then echo 'The root file is empty' > ERRORS

elif [ "$ODIN_latex" != '' ]
then echo latex > fmtcmd
elif [ "$ODIN_tex" != '' ]
then echo tex > fmtcmd
elif egrep -e '^\\documentstyle' -e '^\\documentclass' $rootFile > /dev/null
then echo latex > fmtcmd
else echo tex > fmtcmd
fi

if [ "$ODIN_pdf" != '' ]
then
  sed -e 's/.*/pdf&/' fmtcmd > pdfcmd
  mv pdfcmd fmtcmd
else :
fi

