#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# If no argument is given, print usage.
if [ -z "$1" ]
then
    echo "usage: $0 <header>"
    echo "To get a list of available headers, please run getheaders.sh"
    exit 1
fi

find . -name .git -prune -o \( -name "$1" -type d -exec cat {}/tfile \; \) \
    2>/dev/null | sort
