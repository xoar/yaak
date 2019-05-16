#!/bin/bash

#find the folder of this file and place the path in dir

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

export ODIN_LOCALIPC=1
export PATH=$PATH:$DIR/tools/eli-4.8.1/bin/bin
export PATH=$PATH:$DIR/tools/eli-4.8.1/bin

cd $DIR

eli -r "unparser.specs +cc='g++':exe:help"