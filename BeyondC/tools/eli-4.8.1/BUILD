#! /bin/sh
# build Eli and Odin

USAGE="usage: BUILD [-quiet] [-notest] [-nobrowsers]"
quiet=0; examples=1; browsers=1

while [ $# -gt 0 ] ; do
   case $1 in
      # Don't prompt for anything.
      -quiet)
         quiet=1; browsers=0; shift;;
      # Don't test the examples after Eli is built.
      -notest)
         examples=0; shift;;
      # Don't try testing the browsers before building the rest of the system.
      -nobrowsers)
         browsers=0; shift;;
      *)
         echo $USAGE; exit 1;;
   esac
done

if (echo "testing\c"; echo 1,2,3) | grep c >/dev/null; then
  if (echo -n testing; echo 1,2,3) | sed s/-n/xn/ | grep xn >/dev/null; then
    start= end='
' tab='        '
  else
    start=-n end= tab=
  fi
else
  start= end='\c' tab=
fi

tmp=`pwd`/insttmp.$$
rm -f $tmp

if test ! -s Eli/pkg/Adt/config.h; then cp Eli/config.h Eli/pkg/Adt; fi

if test ! -d bin; then mkdir bin; fi
if test ! -x bin/eli
then
  cwd=`echo \`pwd\` | sed -e 's;/tmp_mnt;;'`
  sed -e "s;ELIPKG;$cwd/Eli/pkg;
s;ODINSH;$cwd/Odin/bin/odin;" eli.sh > bin/eli
  chmod +x bin/eli
fi

if test "$quiet" = "1"
then
   slog=n
else
   slog=y
fi

if test "$browsers" = "1"
then
	echo ""
	echo "Building info browsers..."

	ELISYS=`pwd`/Eli

	if test "$slog" = "y"
	then
		(cd ./Eli/pkg/info/texinfo; \
		 make clean; \
		 make ELISYS=$ELISYS || cp /dev/null $tmp) \
			2>&1 | tee Browser.log
	else
		(cd ./Eli/pkg/info/texinfo; \
		 make clean; \
		 make ELISYS=$ELISYS || cp /dev/null $tmp) \
			> Browser.log 2>&1
	fi

	if test -f $tmp
	then
		rm -f $tmp
		cat <<-END

Could not construct the info browsers.  This probably is a result of an
incorrect configuration.  The result of the make can be found in the file
Browser.log.
		END
		exit 1
	fi

	# Bring up the info browsers with some test data to see if they work.
	if test -x Eli/pkg/info/texinfo/tclinfo.exe || \
	   test -x Eli/pkg/info/texinfo/xinfotool.exe
	then
		echo ""
		if test "$DISPLAY" = '' -a "$WINDOW_PARENT" = ''
		then
			cat <<-END

The system is configured to include a windowed browser, but you have
not set your DISPLAY variable.  Please set your DISPLAY variable and try
again.
			END
			exit 1
		fi
		cat <<-END

The system is configured to include a windowed browser.  The browser should
come up with some test nodes.  Follow the instructions in the nodes to
verify that the browser is working properly.

		END
		Eli/pkg/info/info.sh -d . -f -n '(testwin)'
		if test $? -ne 0
		then
			cat <<-END

Your system is not properly configured.  Check that you have the right
versions of the X11 and Tcl/Tk libraries and includes.

			END
			exit 1
		fi
		response=x
		while test "$response" = "x"
		do
			echo ""
			echo "Did the browser work properly and did you reach the panel that indicated"
			echo $start "you had finished? [y/n] " $end
			read response
			if test "$response" = "n"
			then
				cat <<-END

Your system is not properly configured.  Check that you have the right
versions of the X11 and Tcl/Tk libraries and includes.

				END
				exit 1
			elif test "$response" != "y"
			then
				echo "Invalid response."
				response=x
			fi
		done
	fi

	cat <<-END

Eli includes an info browser based on the curses library.  The browser should
come up with some test nodes.  Press enter to bring up the browser, then
follow the instructions in the nodes to verify that the browser is working
properly.

	END
	echo $start Press ENTER to continue... $end

	read response

	DISPLAY=
	export DISPLAY
	Eli/pkg/info/info.sh -d . -f -n '(testcurses)'

	if test $? -ne 0
	then
		echo ""
		echo "Your system is not properly configured."
		exit 1
	fi

	response=x
	while test "$response" = "x"
	do
		echo ""
		echo "Did the browser work properly and did you reach the panel that indicated you"
		echo $start "had finished? [y/n] " $end

		read response
		if test "$response" = "n"
		then
			echo ""
			echo "Your system is not properly configured."
			exit 1
		elif test "$response" != "y"
		then
			echo "Invalid response."
			response=x
		fi
	done
fi

if test "$quiet" = "0"
then
	echo ""
	echo "No further questions must be answered..."
	echo ""
fi

echo "Checking object symbol classification..."
if test "$slog" = "y"
then
	(cd ./Eli/pkg/eli/ofiles; make; ./try.exe || \
	 cp /dev/null $tmp) 2>&1 | tee ofiles.log
else
	(cd ./Eli/pkg/eli/ofiles; make; ./try.exe || \
	 cp /dev/null $tmp) > ofiles.log 2>&1
fi

if test -f $tmp
then
	rm -f $tmp
	echo ""
	echo "Symbols cannot be classified.  Check the file ofiles.log for details."
	exit 1
fi

echo ""
echo "Building Odin (this will take a while)..."
if test "$slog" = "y"
then
	(cd ./Odin; ./INSTALL `pwd` || cp /dev/null $tmp) 2>&1 | tee Odin.log
else
	(cd ./Odin; ./INSTALL `pwd` || cp /dev/null $tmp) > Odin.log 2>&1
fi

if test -f $tmp
then
	rm -f $tmp
	echo ""
	echo "Build of Odin failed.  Check the file Odin.log for details."
	exit 1
fi

PATH=`pwd`/bin:$PATH
export PATH

echo ""
echo "Making the Eli packages (this takes a long time) ..."

makearg="DESTDIR=`pwd`"
if test "$examples" = 1
then
	makearg="$makearg all"
else
	makearg="$makearg notest"
fi

if test "$slog" = "y"
then
	(cd ./Eli; make $makearg || cp /dev/null $tmp) 2>&1 | tee Eli.log
else
	(cd ./Eli; make $makearg || cp /dev/null $tmp) > Eli.log 2>&1
fi

if test -f $tmp
then
	rm -f $tmp
	echo ""
	echo "Make of Eli failed.  Check the file Eli.log for details."
	exit 1
fi

cat <<-END

Construction is complete.  A number of log files with .log extensions have
been left in this directory.  These may be useful in diagnosing any further
problems you may encounter.

A 'bin' subdirectory has been created in this directory.  To use Eli,
either put that directory on your path or move the 'eli' script it
contains to a directory that is already on your path.

Eli comes with extensive documentation in HTML and PDF forms that can be
found in the doc/Eli directory.  The documentation can also be accessed
using the command

	eli '?'

END
