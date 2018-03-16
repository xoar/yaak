#!/bin/bash

#find the folder of this file and place the path in dir

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  TOOLPATHDIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$TOOLPATHDIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
TOOLPATHDIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

cd "$TOOLPATHDIR/eli-4.8.1"
./configure --prefix "$TOOLPATHDIR/eli-4.8.1/bin"
make
make install
