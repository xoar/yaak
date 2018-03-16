#! /bin/sh
# install Eli and Odin

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

sys=$1

if test "`echo $sys | sed -n -e 's;^/.*$;/;p'`" != '/'
then
	echo "Argument to install.sh must be an absolute pathname."
	exit 1
fi

if test ! -d $sys
then
	echo "Directory $sys does not exist."
	response=n
	echo $start "Ok to create it? [y/n] " $end
	read response
	if test "$response" = "y"
	then
		(umask 002; mkdir $sys 2>/dev/null)
		if test ! -d $sys
		then
			(umask 002; mkdir -p $sys 2>/dev/null)
			if test ! -d $sys
			then
				echo ""
				echo "Could not create directory $sys"
				echo ""
			fi
		fi
	else
		exit 1
	fi
fi

echo ""
echo "Installing Odin ..."
if test "$slog" = "y"
then
	(cd ./Odin; ./INSTALL $sys || cp /dev/null $tmp) 2>&1 | tee EliInst.log
else
	(cd ./Odin; ./INSTALL $sys || cp /dev/null $tmp) > EliInst.log 2>&1
fi

if test -f $tmp
then
	rm -f $tmp
	echo ""
	echo "Installation of Odin failed.  Check the file EliInst.log for details."
	exit 1
fi

PATH=$sys/bin:$PATH
export PATH

echo ""
echo "Installing the Eli packages ..."

if test ! -d $sys/lib
then
	mkdir $sys/lib
fi
if test ! -d $sys/lib/Eli
then
	mkdir $sys/lib/Eli
fi

if test "$slog" = "y"
then
	(cd ./Eli; make install DESTDIR=$sys/lib/Eli \
		|| cp /dev/null $tmp) 2>&1 | tee -a EliInst.log
else
	(cd ./Eli; make install DESTDIR=$sys/lib/Eli \
		|| cp /dev/null $tmp) >> EliInst.log 2>&1
fi

if test -d doc
then
    if test ! -d $sys/doc
    then
        mkdir $sys/doc
    fi
    if test ! -d $sys/doc/Eli
    then
        mkdir $sys/doc/Eli
    fi
	cp -rf doc/Eli/* $sys/doc/Eli
fi

if test -f $tmp
then
	rm -f $tmp
	echo ""
	echo "Installation of Eli failed.  Check EliInst.log for more details."
	exit 1
fi

# put eli script into bin
sed -e "s;ELIPKG;$sys/lib/Eli;
s;ODINSH;$sys/bin/odin;" eli.sh > $sys/bin/eli
chmod +x $sys/bin/eli

cat <<-END

Installation is complete.  A number of log files with .log extensions have
been left in this directory.  These may be useful in diagnosing any further
problems you may encounter.

To run Eli use the shell script 'eli' in directory $sys/bin.

Eli comes with extensive documentation in HTML and PDF forms that can be
found in the $sys/doc/Eli directory.  The documentation can
also be accessed using the command

	$sys/bin/eli '?'

END
