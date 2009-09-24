#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# If no argument is given, print usage.
if [ -z "$1" ]
then
    STARTDIR="."
else
    STARTDIR="$1"
fi

find "$STARTDIR" -name .git -prune -o \( -name "*.h" -type d -exec cat {}/tfile \; \) \
    2>/dev/null | sort
