#! /bin/sh
# $Id: install.sh,v 1.1 2009/07/15 22:31:35 profw Exp $

# EXEC (install.sh) (:FILE) (+d_dest) (INSTALL)
#    => (:installpkg);

ODIN_dir=$1;shift;ODIN_dest=$1;shift;ODIN_installer=$1;shift;

echo '#! /bin/sh' > installpkg
chmod +x installpkg
echo "$ODIN_installer $ODIN_dir $ODIN_dest" >> installpkg

if test -z "$ODIN_dest"
then
  echo 'No destination specified for package installation' > ERRORS
  exit 0
fi

if test ! -d $ODIN_dest
then
  echo "Destination must be a directory" > ERRORS
  exit 0
fi

if test ! -d $ODIN_dir
then
  echo ':installpkg must be applied to a directory' > ERRORS
  exit 0
fi

if test ! -f $ODIN_dir/PKGLST -a \
  \( ! -f $ODIN_dir/`basename $ODIN_dir`.dg -o ! -f $ODIN_dir/version \)
then
  echo ':installpkg must be applied to a versioned package or collection' > ERRORS
  exit 0
fi
