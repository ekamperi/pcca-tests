#!/bin/sh
#
# I have tried to read the source of this script a month after I wrote it
# and found it difficult to understand what was doing. Here is the deal:
#
# We have a template file in the current directory, called `template.c'.
# This is NOT compilable by default. We use it as a skeleton file, where
# we replace some of its contents to turn it into compilable. We then
# build it and run it as any other regular test case in our src tree.
#
# So what exactly do we replace?
#
# We replace _POSIX_MYSYMBOL and _SC_MYMBOL with the real symbols, which
# are stored in the `ffile'. Actually we store only the _POSIX symbols
# and we use sed(1) to generate the _SC equivalents.

while read posix_symbol
do
  # We replace the _POSIX part with _SC to get the name of the argument
  # that we will be passing to sysconf(3).
  sc_symbol=$(echo $posix_symbol | sed 's/_POSIX/_SC/')

  # Construct C source file name (we use lowercase).
  c_file=$(echo "$posix_symbol.c" | tr '[:upper:]' '[:lower:]')

  # Inject the right symbols into the C source file.
  sed "s/_POSIX_MYSYMBOL/$posix_symbol/g" template.c > "tmp$c_file"
  sed "s/_SC_MYSYMBOL/$sc_symbol/g" "tmp$c_file" > "$c_file"
  rm -f "tmp$c_file"

  # Compile
  gcc "$c_file" #>/dev/null 2>/dev/null
  rm "$c_file"

  printf "/unistd.h/t$c_file: "
  ./a.out
  rm a.out
done < ffile
