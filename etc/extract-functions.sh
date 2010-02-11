#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
#set -e

if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR="."    # Default top level directory to start from.
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

    # Remove leading whitespace.
    # Note: Don't be tempted to use the more common, but severy less portable,
    # ^[ \t] construct. Nor use sed -i.
    sed 's/^[[:blank:]]\{1,\}//g' "$file.cflow" > "$file.cflow.tmp"
    mv "$file.cflow.tmp" "$file.cflow"
    rm -f "$file.cflow.tmp"

    echo "$file"
    cat "$file.cflow"
done
