#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

for dir in $(find . -name .git -prune -o \( -type d -name "*.h" -print \) \
    2>/dev/null | sort)
do
    if [ -f "$dir/prototypes.list" ]
    then
	rm -fr "$dir/prototypes"
	mkdir "$dir/prototypes"
	./protgen.rb "$dir/prototypes.list"
    fi
done
