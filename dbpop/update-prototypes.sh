#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Unless explicitly provided, use current directory as the default one.
if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR=".."
fi

# First the prototypes tests that passed.
for prot in $(find "$STARTDIR" -name .git -prune -o \
    \( -type f -name "log.passed-prototypes" -exec cat {} \; \) 2>/dev/null | sort)
do
    func=$(echo "$prot" | awk -F '^(t_)|(_prot)$' ' { print $2 }')
    echo "UPDATE psx_functions SET prototype = 'yes'  WHERE function_name = '$func';"
done

# Next the prototypes tests that failed.
for prot in $(find "$STARTDIR" -name .git -prune -o \
    \( -type f -name "log.failed-prototypes" -exec cat {} \; \) 2>/dev/null | sort)
do
    func=$(echo "$prot" | awk -F '^(t_)|(_prot)$' ' { print $2 }')
    echo "UPDATE psx_functions SET prototype = 'no'  WHERE function_name = '$func';"
done
