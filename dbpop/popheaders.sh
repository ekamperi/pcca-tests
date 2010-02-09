#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Unless explicitly provided, use .. directory as the default one.
if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR=".."
fi

for header in $(find "$STARTDIR" -name .git -prune -o \
    \( -type d -name "*.h"  -print \) 2>/dev/null | sort); do
    printf "INSERT INTO psx_headers VALUES('${header#..}');\n"
done
