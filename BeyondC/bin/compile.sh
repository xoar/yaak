#/bin/bash

#USAGE: compile filename.c output_filename (build paramters)*

#find the folder of this file and place the path in dir

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"


#make a build dir
mkdir -p buildTemp

#get the filename without the path
fileName=$(basename $1)

#important: have the same env as clang
echo "preproccess with " "cpp ${@:3} $1 > buildTemp/${fileName}_cpp"
cpp ${@:3} $1 > buildTemp/${fileName}_cpp

#add the builtin_va_list workaround
cat $DIR/processed_file_header.txt buildTemp/${fileName}_cpp > buildTemp/${fileName}_preprocessed
$DIR/unparser.specs.exe buildTemp/${fileName}_preprocessed > buildTemp/${fileName}_processed || { printf "\n\nBuild failed \n\n";exit 1;}

#delete the builtin_va_list workaround from output file
sed '/typedef char \* __builtin_va_list;/d' ./buildTemp/${fileName}_processed > buildTemp/${fileName}

#run clang
echo "test with " "clang -fsyntax-only ${@:3} buildTemp/${fileName}"
clang -fsyntax-only ${@:3} buildTemp/${fileName}

#move it to the ouput directory
cp buildTemp/${fileName} $2


