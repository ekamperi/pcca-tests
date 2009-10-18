#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Unless explicitly provided, use current directory as the default one.
if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR="."
fi

# Get host operating system name.
OS=$(uname | tr '[:upper:]' '[:lower:]')

find "$STARTDIR" -name .git -prune -o \( -type f -name "README.$OS" -print \) \
    2>/dev/null
