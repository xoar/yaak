#! /bin/sh

elipkg=ELIPKG
odinsh=ODINSH

USAGE="usage: eli [-c cache] [-k] [-p pkgdir] [-r] [-R] [-s] command ..."

cmd=; keep_going=; meta_cache=; pkg_dirs=; preset=; quick=; reset=; serve=;

while [ $# -gt 0 ] ; do
   case $1 in
      # use specified cache rather than the default cache
      -c)
	 if [ $# -lt 2 ] ; then echo $USAGE; exit 1; fi
         meta_cache="-c $2"; shift;shift;;
      # keep going after build errors detected
      -k)
	 keep_going='-k'; shift;;
      # introduce a new package directory
      -p)
	 if [ $# -lt 2 ] ; then echo $USAGE; exit 1; fi
         pkg_dirs="$pkg_dirs$2:"; shift;shift;;
      # do not run the derivation graph compiler
      -q)
	 quick='-q'; shift;;
      # reset the cache (clear all derived objects)
      -r)
	 reset='-r'; shift;;
      # reset the cache and the packages (update to latest versions)
      -R)
	 preset='-R'; shift;;
      # have Odin client be its own server if there is not a server
      -s)
	 serve='-s'; shift;;
      -*)
	 echo $USAGE; exit 1;;
      *)
         break;; esac; done

ODINPATH=$pkg_dirs$ODINPATH:$elipkg
export ODINPATH

if test "$*" != ''
then $odinsh $meta_cache $keep_going $quick $reset $preset $serve "$@"
else $odinsh $meta_cache $keep_going $quick $reset $preset $serve
fi
