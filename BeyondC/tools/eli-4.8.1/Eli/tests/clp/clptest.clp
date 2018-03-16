/* $Id: clptest.clp,v 1.8 1996/12/20 16:12:43 kadhim Exp $ */

terminator "--";
usage "-h";
CompileOnly "-c" boolean "Just compile, don't link";
MacroPackage "-m" "mac" with strings "Load this macro package";
OutputFile "-o" string "Produce output in this file";
InputFile input "File to be processed";
GenAssembly "-S" boolean "Generate assembly language output";
TmpFile "-temp=" joinedto string "Store temporary files in this directory";
WideListing "-w" booleans;
Extra "-x" boolean "A required option";
NumCopies "-@" int "Print this many copies";
NumCols "-C" with int "Use this many colours";
NumZaps "-z" "-Zap" "whammo" with ints "Zap this many times";
NumLines "-" joinedto ints "Output this number of lines from the head";
Others positionals "Other positional parameters";
open error format "sorry %p could not open %f doo %%de %adoo";
