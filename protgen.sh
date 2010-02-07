#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR="."    # Default top level directory to start from.
fi

for dir in $(find "$STARTDIR" -name .git -prune -o \
    \( -type d -name "*.h" -print \) 2>/dev/null | sort)
do
    if [ -f "$dir/prototypes.list" ]
    then
	rm -fr "$dir/prototypes"
	mkdir "$dir/prototypes"
	./protgen.rb "$dir/prototypes.list"
    fi
done
