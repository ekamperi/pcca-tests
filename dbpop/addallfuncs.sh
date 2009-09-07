#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Unless explicitly provided, use .. directory as the default one.
if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR=".."
fi

find "$STARTDIR" -name .git -prune -o \( -type d -name "*.h" -exec \
    ./addheaderfuncs.sh {}/functions.list \; \) 2>/dev/null | sort
