#!/bin/sh

while read posix_symbol
do
  # In `ffile' we store the symbolic constants as defined in <unistd.h>.
  # We replace the _POSIX part with _SC to get the name of the argument
  # that we will pass to sysconf(3).
  sc_symbol=$(echo $posix_symbol | sed 's/_POSIX/_SC/')

  # Construct C source file name (we use lowercase).
  c_file=$(echo "$posix_symbol.c" | tr '[:upper:]' '[:lower:]')

  # Inject the right symbols into the C source file.
  sed "s/_POSIX_MYSYMBOL/$posix_symbol/g" test.c > "tmp$c_file"
  sed "s/_SC_MYSYMBOL/$sc_symbol/g" "tmp$c_file" > "$c_file"
  rm -f "tmp$c_file"

  # Compile
  gcc "$c_file" #>/dev/null 2>/dev/null
  rm "$c_file"

  printf "/unistd.h/t$c_file: "
  ./a.out
  rm a.out
done < ffile
