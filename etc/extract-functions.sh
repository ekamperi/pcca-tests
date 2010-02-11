#!/bin/sh
#
# This script iterates over the entire test suite. For every functional test
# case it encounters, it extracts the functions that are called from within
# that particular test.
#
# The output is saved in a file named exactly as the test source file, with the
# .cflow string appended to it. E.g., t_mq_open.c will give birth to
# t_mq_open.c.cflow

# Exit immediately if any untested command fails in non-interactive mode.
set -e

if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR=".."    # Default top level directory to start from.
fi

# Note: Skip the prototype tests, as they don't audit functionality.
# I.e., no assert(), no party.
for file in $(find "$STARTDIR" -name .git -prune -o  \
    \( -type f -name "t_*.c" -print \) 2>/dev/null | \
    grep -v "_prot.c$")
do
    # Paranoia
    rm -f "$file.cflow"
    rm -f "$file.cflow.tmp"

    # Extract the functions that are called from within this particular C file.
    # But skip assert(), printf() and anything that contains < > symbols.
    cflow "$file" | egrep -v '<|>|assert|printf' | sort > "$file.cflow"

    # Remove leading whitespace and trailing () from every function/line.
    # Note: Don't be tempted to use the more common, but severy less portable,
    # ^[ \t] construct. Nor use sed -i. They are both gnu-isms and will break
    # to bsdland.
    sed 's/^[[:blank:]]\{1,\}\(.*\)()$/\1/g' "$file.cflow" > "$file.cflow.tmp"
    mv "$file.cflow.tmp" "$file.cflow"
    rm -f "$file.cflow.tmp"

    # Debugging purposes
    echo "$file"
    cat "$file.cflow"
done
